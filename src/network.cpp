#include "network.hpp"
#include "html_parser.hpp"
#include "types.hpp"
#include "config.hpp"

#include <curl/curl.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <regex>
#include <sys/stat.h>
#include <unistd.h>

// ─── Write callback for libcurl ───────────────────────────────────────────────
static size_t write_cb(char* ptr, size_t size, size_t nmemb, void* userdata) {
    std::string* out = reinterpret_cast<std::string*>(userdata);
    out->append(ptr, size * nmemb);
    return size * nmemb;
}

// ─── Common browser User-Agent ────────────────────────────────────────────────
static constexpr const char* UA =
    "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 "
    "(KHTML, like Gecko) Chrome/124.0.0.0 Safari/537.36";

namespace network {

// ─── libcurl global lifecycle ─────────────────────────────────────────────────
void global_init()    { curl_global_init(CURL_GLOBAL_DEFAULT); }
void global_cleanup() { curl_global_cleanup(); }

static void mkdir_p_file(const std::string& path) {
    size_t pos = path.find_last_of('/');
    if (pos == std::string::npos) return;
    std::string dir = path.substr(0, pos);
    std::string current;
    for (size_t i = 0; i < dir.size(); ++i) {
        current += dir[i];
        if (dir[i] == '/' || i == dir.size() - 1) {
            struct stat st;
            if (stat(current.c_str(), &st) != 0) {
                mkdir(current.c_str(), 0700);
            }
        }
    }
}

// ─── Cookie file path ─────────────────────────────────────────────────────────
std::string cookie_file_path() {
    return Config::get_effective_cookie_path();
}

// ─── Check well-known cookie locations ────────────────────────────────────────
std::string find_available_cookie_file() {
    const char* home = std::getenv("HOME");
    std::string home_str = home ? home : "";

    const std::string paths[] = {
        Config::get_effective_cookie_path(),
        Config::get_default_cookie_path(),
        home_str + "/.local/share/intra_cli/cookies.txt",
        home_str + "/.cache/intra_cookies.txt",
        home_str + "/.cache/AppImage-Cache/intra_cookies.txt",
        "/tmp/42cookies.txt",
        "/tmp/intra_cookies.txt"
    };
    for (const auto& p : paths) {
        if (p.empty()) continue;
        struct stat st;
        if (stat(p.c_str(), &st) == 0 && st.st_size > 50) {
            return p;
        }
    }
    return {};
}

// ─── Set permissions on the cookie file (0600) ────────────────────────────────
static void secure_cookie_file(const std::string& path) {
    if (!path.empty()) {
        chmod(path.c_str(), S_IRUSR | S_IWUSR);
    }
}

// ─── Shared curl setup helper ─────────────────────────────────────────────────
static CURL* make_curl(const std::string& cookie_file, std::string& body) {
    if (!cookie_file.empty()) {
        mkdir_p_file(cookie_file);
    }
    CURL* c = curl_easy_init();
    if (!c) return nullptr;
    long timeout_sec = Config::get().timeout > 0 ? static_cast<long>(Config::get().timeout) : 15L;
    curl_easy_setopt(c, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(c, CURLOPT_WRITEDATA,     &body);
    curl_easy_setopt(c, CURLOPT_USERAGENT,     UA);
    curl_easy_setopt(c, CURLOPT_COOKIEJAR,     cookie_file.c_str());
    curl_easy_setopt(c, CURLOPT_COOKIEFILE,    cookie_file.c_str());
    curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(c, CURLOPT_MAXREDIRS,     10L);
    curl_easy_setopt(c, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(c, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(c, CURLOPT_TIMEOUT,       timeout_sec);
    return c;
}

// ─── HTTP GET with custom Accept header ───────────────────────────────────────
static std::string http_get_with_accept(const std::string& url,
                                        const std::string& cookie_file,
                                        const std::string& accept_hdr)
{
    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) return {};

    struct curl_slist* headers = nullptr;
    if (!accept_hdr.empty())
        headers = curl_slist_append(headers, ("Accept: " + accept_hdr).c_str());

    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    if (headers)
        curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);

    curl_easy_perform(c);
    if (headers) curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);
    return body;
}

// ─── HTTP GET ─────────────────────────────────────────────────────────────────
std::string http_get(const std::string& url, const std::string& cookie_file) {
    return http_get_with_accept(url, cookie_file, "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
}

// ─── HTTP POST ────────────────────────────────────────────────────────────────
std::string http_post(const std::string& url,
                      const std::string& fields,
                      const std::string& referer,
                      const std::string& cookie_file)
{
    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) return {};

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");

    curl_easy_setopt(c, CURLOPT_URL,        url.c_str());
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, fields.c_str());
    if (!referer.empty())
        curl_easy_setopt(c, CURLOPT_REFERER, referer.c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);

    curl_easy_perform(c);
    curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);
    return body;
}

// ─── HTTP POST (JSON) ─────────────────────────────────────────────────────────
[[maybe_unused]] static std::string http_post_json(const std::string& url,
                                                  const std::string& json_body,
                                                  const std::string& csrf_token,
                                                  const std::string& cookie_file)
{
    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) return {};

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "Accept: application/json, text/plain, */*");
    headers = curl_slist_append(headers, ("X-CSRF-Token: " + csrf_token).c_str());
    headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");

    curl_easy_setopt(c, CURLOPT_URL,        url.c_str());
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, json_body.c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(c, CURLOPT_REFERER,    "https://profile.intra.42.fr/slots");

    curl_easy_perform(c);
    curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);
    return body;
}

// ─── Switch off Profile V3 Early Access if enabled ────────────────────────────
static void ensure_classic_profile(const std::string& cookie_file) {
    const std::string check_url = "https://profile.intra.42.fr/v3_early_access";
    std::string html = http_get(check_url, cookie_file);
    if (html.find("/v3_early_access/switch") == std::string::npos) return;

    std::string csrf = html_parser::get_attr_value(html, "csrf-token", "content");
    if (csrf.empty())
        csrf = html_parser::get_attr_value(html, "authenticity_token", "value");

    if (!csrf.empty()) {
        std::string fields = "authenticity_token=" + html_parser::url_encode(csrf);
        http_post("https://profile.intra.42.fr/v3_early_access/switch",
                  fields, check_url, cookie_file);
    }
}

// ─── Session validity check ───────────────────────────────────────────────────
bool session_is_valid(const std::string& cookie_file) {
    if (access(cookie_file.c_str(), F_OK) != 0) return false;

    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) return false;

    curl_easy_setopt(c, CURLOPT_URL, "https://profile.intra.42.fr");
    curl_easy_setopt(c, CURLOPT_FOLLOWLOCATION, 1L);

    char* effective_url = nullptr;
    CURLcode res = curl_easy_perform(c);
    curl_easy_getinfo(c, CURLINFO_EFFECTIVE_URL, &effective_url);
    long http_code = 0;
    curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &http_code);
    std::string eff = effective_url ? effective_url : "";
    curl_easy_cleanup(c);

    if (res != CURLE_OK || http_code != 200) return false;

    // Reject if redirected to authentication / keycloak
    if (eff.find("auth.42.fr") != std::string::npos ||
        eff.find("signin.intra.42.fr") != std::string::npos ||
        eff.find("sign_in") != std::string::npos ||
        eff.find("users/auth") != std::string::npos ||
        body.find("kc-form-login") != std::string::npos ||
        body.find("Sign in to Realm") != std::string::npos)
    {
        unlink(cookie_file.c_str());
        return false;
    }

    if (eff.find("intra.42.fr") == std::string::npos) {
        unlink(cookie_file.c_str());
        return false;
    }

    return true;
}

// ─── Helper: extract Keycloak error message ───────────────────────────────────
static std::string extract_keycloak_error(const std::string& body) {
    auto extract_between = [&](const std::string& marker) -> std::string {
        size_t ep = body.find(marker);
        if (ep == std::string::npos) return {};
        size_t ts = body.find('>', ep);
        if (ts == std::string::npos) return {};
        size_t te = body.find('<', ts + 1);
        if (te == std::string::npos) return {};
        std::string t = body.substr(ts + 1, te - ts - 1);
        size_t s = t.find_first_not_of(" \t\r\n");
        size_t e = t.find_last_not_of(" \t\r\n");
        if (s == std::string::npos) return {};
        return t.substr(s, e - s + 1);
    };

    std::string err = extract_between("id=\"input-error\"");
    if (err.empty()) err = extract_between("input-error");
    if (err.empty()) err = extract_between("id=\"kc-feedback-text\"");
    if (err.empty()) err = extract_between("kc-feedback-text");
    if (err.empty()) err = extract_between("alert-error");
    return err;
}

// ─── Full login flow (Keycloak / auth.42.fr) ─────────────────────────────────
bool do_login(const std::string& username,
              const std::string& password,
              const std::string& cookie_file,
              std::string&       error_out)
{
    unlink(cookie_file.c_str());

    const std::string entry_url = "https://signin.intra.42.fr/users/sign_in";
    std::string page_body;
    CURL* c1 = make_curl(cookie_file, page_body);
    if (!c1) {
        error_out = "Failed to initialize curl";
        return false;
    }

    curl_easy_setopt(c1, CURLOPT_URL, entry_url.c_str());
    curl_easy_setopt(c1, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res1 = curl_easy_perform(c1);
    char* eff1_ptr = nullptr;
    curl_easy_getinfo(c1, CURLINFO_EFFECTIVE_URL, &eff1_ptr);
    std::string keycloak_effective_url = eff1_ptr ? eff1_ptr : "";
    curl_easy_cleanup(c1);

    if (res1 != CURLE_OK || page_body.empty()) {
        error_out = "Could not reach signin.intra.42.fr";
        return false;
    }

    std::string action_url;
    {
        std::string lower = page_body;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        size_t form_pos = lower.find("<form");
        if (form_pos == std::string::npos) {
            error_out = "Could not find login form on authentication page";
            return false;
        }

        size_t act_pos = lower.find("action=", form_pos);
        if (act_pos == std::string::npos) {
            error_out = "Could not find form action attribute";
            return false;
        }

        act_pos += 7;
        char delim = page_body[act_pos];
        if (delim == '"' || delim == '\'') act_pos++;
        size_t act_end = page_body.find(delim, act_pos);
        if (act_end == std::string::npos) act_end = page_body.find(' ', act_pos);
        action_url = page_body.substr(act_pos, act_end - act_pos);

        std::string decoded;
        for (size_t i = 0; i < action_url.size(); ) {
            if (action_url.substr(i, 5) == "&amp;") {
                decoded += '&';
                i += 5;
            } else {
                decoded += action_url[i++];
            }
        }
        action_url = decoded;
    }

    if (action_url.empty()) {
        error_out = "Invalid login form action URL";
        return false;
    }
    if (action_url.rfind("http", 0) != 0) {
        if (action_url[0] == '/')
            action_url = "https://auth.42.fr" + action_url;
        else
            action_url = "https://auth.42.fr/" + action_url;
    }

    std::string post_fields =
        "username="      + html_parser::url_encode(username) +
        "&password="     + html_parser::url_encode(password) +
        "&credentialId=" +
        "&login=Sign+In";

    struct curl_slist* post_hdrs = nullptr;
    post_hdrs = curl_slist_append(post_hdrs, "Content-Type: application/x-www-form-urlencoded");
    post_hdrs = curl_slist_append(post_hdrs, "Origin: https://auth.42.fr");

    std::string post_body;
    CURL* c2 = make_curl(cookie_file, post_body);
    if (!c2) {
        curl_slist_free_all(post_hdrs);
        error_out = "Curl initialization failed";
        return false;
    }

    curl_easy_setopt(c2, CURLOPT_URL,            action_url.c_str());
    curl_easy_setopt(c2, CURLOPT_POSTFIELDS,     post_fields.c_str());
    curl_easy_setopt(c2, CURLOPT_REFERER,        keycloak_effective_url.c_str());
    curl_easy_setopt(c2, CURLOPT_HTTPHEADER,     post_hdrs);
    // Let libcurl follow the whole Keycloak chain on its own:
    //   POST credentials → 302 callback → profile.intra.42.fr
    // Relying on CURLINFO_REDIRECT_URL + substring matching proved fragile:
    // an unexpected/relative Location made a valid login look like a 302 error.
    curl_easy_setopt(c2, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode post_res = curl_easy_perform(c2);
    long http_code = 0;
    curl_easy_getinfo(c2, CURLINFO_RESPONSE_CODE, &http_code);
    char* eff2_ptr = nullptr;
    curl_easy_getinfo(c2, CURLINFO_EFFECTIVE_URL, &eff2_ptr);
    std::string final_url = eff2_ptr ? eff2_ptr : "";

    curl_slist_free_all(post_hdrs);
    curl_easy_cleanup(c2);
    secure_cookie_file(cookie_file);

    if (post_res != CURLE_OK) {
        error_out = std::string("Network error: ") + curl_easy_strerror(post_res);
        return false;
    }

    const bool on_profile =
        http_code == 200 &&
        final_url.find("profile.intra.42.fr") != std::string::npos &&
        final_url.find("auth.42.fr") == std::string::npos;

    if (on_profile) {
        ensure_classic_profile(cookie_file);
        return true;
    }

    // Still on the identity provider: a required action / 2FA gate, or a bad
    // credential response rendered by Keycloak.
    if (final_url.find("auth.42.fr") != std::string::npos) {
        error_out = extract_keycloak_error(post_body);
        if (error_out.empty())
            error_out = "Keycloak requires 2FA/OTP. Please use Cookie Login.";
        return false;
    }

    error_out = extract_keycloak_error(post_body);
    if (error_out.empty()) {
        if (post_body.find("kc-feedback-text") != std::string::npos ||
            post_body.find("input-error") != std::string::npos)
        {
            error_out = "Invalid username or password";
        } else {
            error_out = "Authentication failed (HTTP " + std::to_string(http_code) + ")";
        }
    }
    return false;
}

// ─── Login with cookie ────────────────────────────────────────────────────────
bool login_with_cookie(const std::string& cookie_input,
                       const std::string& cookie_file,
                       std::string&       error_out)
{
    std::string val = cookie_input;
    size_t s = val.find_first_not_of(" \t\r\n");
    size_t e = val.find_last_not_of(" \t\r\n");
    if (s == std::string::npos) {
        error_out = "Cookie input is empty";
        return false;
    }
    val = val.substr(s, e - s + 1);

    struct stat st;
    if (stat(val.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
        if (val != cookie_file) {
            mkdir_p_file(cookie_file);
            std::ifstream src(val, std::ios::binary);
            std::ofstream dst(cookie_file, std::ios::binary);
            dst << src.rdbuf();
            dst.close();
            src.close();
            secure_cookie_file(cookie_file);
        }

        if (session_is_valid(cookie_file)) {
            ensure_classic_profile(cookie_file);
            return true;
        } else {
            error_out = "Cookie file loaded but session is expired or invalid";
            return false;
        }
    }

    if (val.rfind("_intra_42_session_production=", 0) == 0) {
        val = val.substr(29);
    } else if (val.rfind("_intra_42_session=", 0) == 0) {
        val = val.substr(18);
    }
    if (!val.empty() && val.back() == ';') {
        val.pop_back();
    }

    mkdir_p_file(cookie_file);
    std::ofstream out(cookie_file, std::ios::trunc);
    if (!out.is_open()) {
        error_out = "Could not write to cookie file: " + cookie_file;
        return false;
    }

    out << "# Netscape HTTP Cookie File\n"
        << "# Generated by 42_cli\n"
        << ".intra.42.fr\tTRUE\t/\tTRUE\t2147483647\t_intra_42_session_production\t" << val << "\n"
        << ".intra.42.fr\tTRUE\t/\tTRUE\t2147483647\t_intra_42_session\t" << val << "\n"
        << "profile.intra.42.fr\tFALSE\t/\tTRUE\t2147483647\t_intra_42_session_production\t" << val << "\n"
        << "profile.intra.42.fr\tFALSE\t/\tTRUE\t2147483647\t_intra_42_session\t" << val << "\n";
    out.close();
    secure_cookie_file(cookie_file);

    if (session_is_valid(cookie_file)) {
        ensure_classic_profile(cookie_file);
        return true;
    }

    error_out = "Invalid session cookie or session has expired";
    return false;
}

// ─── Profile scraper ──────────────────────────────────────────────────────────
bool fetch_profile(const std::string& cookie_file, Profile& out, std::string& error_out) {
    const std::string base_url = "https://profile.intra.42.fr";
    std::string html = http_get(base_url, cookie_file);
    if (html.empty()) {
        error_out = "Network error connecting to profile page";
        return false;
    }

    if (html.find("kc-form-login") != std::string::npos ||
        html.find("Sign in to Realm") != std::string::npos)
    {
        error_out = "Session expired — please log in again";
        return false;
    }

    // If Profile V3 React shell is returned, switch to classic Rails view
    if (html.find("<div id=\"root\">") != std::string::npos ||
        html.find("profile-v3.intra.42.fr") != std::string::npos)
    {
        ensure_classic_profile(cookie_file);
        html = http_get(base_url, cookie_file);
    }

    // 1. Extract login from JavaScript config
    std::string user_login;
    {
        size_t p = html.find("\"login\":");
        if (p != std::string::npos) {
            size_t q1 = html.find('"', p + 8);
            if (q1 != std::string::npos) {
                size_t q2 = html.find('"', q1 + 1);
                if (q2 != std::string::npos)
                    user_login = html.substr(q1 + 1, q2 - q1 - 1);
            }
        }
    }
    if (user_login.empty()) {
        user_login = html_parser::get_data_attr(html, "login");
    }

    out.login = user_login.empty() ? "42student" : user_login;
    out.display_name = out.login;
    out.level = "0.0";
    out.location = "Unavailable";
    out.wallet = "0";
    out.correction_points = "0";

    // 2. Fetch JSON endpoint: https://profile.intra.42.fr/users/<login> with Accept: application/json
    if (!user_login.empty()) {
        std::string json_body = http_get_with_accept(
            "https://profile.intra.42.fr/users/" + user_login,
            cookie_file,
            "application/json"
        );

        if (!json_body.empty() && json_body[0] == '{') {
            // Full name
            size_t fn = json_body.find("\"full_name\":\"");
            if (fn != std::string::npos) {
                fn += 13;
                size_t fe = json_body.find('"', fn);
                if (fe != std::string::npos) out.display_name = json_body.substr(fn, fe - fn);
            }

            // Cluster location / seat
            size_t loc_p = json_body.find("\"location\":");
            if (loc_p != std::string::npos) {
                loc_p += 11;
                if (json_body.substr(loc_p, 4) != "null") {
                    if (json_body[loc_p] == '"') loc_p++;
                    size_t loce = json_body.find_first_of("\",", loc_p);
                    if (loce != std::string::npos) out.location = json_body.substr(loc_p, loce - loc_p);
                }
            }

            // Cursus level e.g. "42cursus":{"level":4.62}
            size_t lp = json_body.find("\"level\":");
            if (lp != std::string::npos) {
                lp += 8;
                size_t le = json_body.find_first_of(",}", lp);
                if (le != std::string::npos) {
                    std::string lvl = json_body.substr(lp, le - lp);
                    if (!lvl.empty() && lvl != "null") out.level = lvl;
                }
            }

            // Avatar image URL
            size_t ip = json_body.find("\"link\":\"https://cdn.intra.42.fr/users/");
            if (ip != std::string::npos) {
                ip += 8;
                size_t ie = json_body.find('"', ip);
                if (ie != std::string::npos) out.avatar_url = json_body.substr(ip, ie - ip);
            }
        }
    }

    // 3. Fetch HTML page: https://profile.intra.42.fr/users/<login> with Accept: text/html
    std::string user_html = html;
    if (!user_login.empty()) {
        std::string html_page = http_get_with_accept(
            "https://profile.intra.42.fr/users/" + user_login,
            cookie_file,
            "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
        );
        if (!html_page.empty() && html_page.size() > 5000) {
            user_html = html_page;
        }
    }

    // Avatar from HTML if not in JSON
    if (out.avatar_url.empty()) {
        size_t ap = user_html.find("https://cdn.intra.42.fr/users/");
        if (ap != std::string::npos) {
            size_t ae = user_html.find_first_of("\"') ", ap);
            if (ae != std::string::npos) out.avatar_url = user_html.substr(ap, ae - ap);
        }
    }

    // Fallback level from HTML if not extracted from JSON
    if (out.level == "0.0") {
        std::regex re_lvl("level\\s*([0-9]+)\\s*-\\s*([0-9]+)%", std::regex::icase);
        std::smatch m;
        if (std::regex_search(user_html, m, re_lvl) && m.size() >= 3) {
            out.level = m[1].str() + "." + m[2].str();
        }
    }

    // Wallet from HTML
    {
        size_t wp = user_html.find("user-wallet-value");
        if (wp != std::string::npos) {
            size_t start = user_html.find('>', wp);
            if (start != std::string::npos) {
                size_t end = user_html.find('<', start + 1);
                if (end != std::string::npos) {
                    std::string raw = user_html.substr(start + 1, end - start - 1);
                    std::string clean;
                    for (char ch : raw) {
                        if (isdigit(ch)) clean += ch;
                    }
                    if (!clean.empty()) out.wallet = clean;
                }
            }
        }
    }

    // Correction points from HTML
    {
        size_t cp = user_html.find("user-correction-point-value");
        if (cp != std::string::npos) {
            size_t start = user_html.find('>', cp);
            if (start != std::string::npos) {
                size_t end = user_html.find('<', start + 1);
                if (end != std::string::npos) {
                    std::string raw = user_html.substr(start + 1, end - start - 1);
                    std::string clean;
                    for (char ch : raw) {
                        if (isdigit(ch)) clean += ch;
                    }
                    if (!clean.empty()) out.correction_points = clean;
                }
            }
        }
    }

    // Campus fallback if seat is Unavailable
    if (out.location == "Unavailable") {
        size_t lp = user_html.find("title='Campus'");
        if (lp == std::string::npos) lp = user_html.find("title=\"Campus\"");
        if (lp != std::string::npos) {
            size_t s1 = user_html.find("<span", lp);
            if (s1 != std::string::npos) {
                size_t s2 = user_html.find("<span", s1 + 5);
                if (s2 != std::string::npos) {
                    size_t start = user_html.find('>', s2);
                    size_t end   = user_html.find('<', start + 1);
                    if (start != std::string::npos && end != std::string::npos) {
                        std::string loc = user_html.substr(start + 1, end - start - 1);
                        size_t b = loc.find_first_not_of(" \t\r\n");
                        size_t e = loc.find_last_not_of(" \t\r\n");
                        if (b != std::string::npos) out.location = loc.substr(b, e - b + 1);
                    }
                }
            }
        }
    }

    // 4. Parse all Projects from HTML
    out.projects.clear();
    {
        size_t search_pos = 0;
        const std::string marker = "main-project-item";
        while (true) {
            size_t block_start = user_html.find(marker, search_pos);
            if (block_start == std::string::npos) break;

            size_t next_block = user_html.find(marker, block_start + marker.size());
            std::string block = user_html.substr(block_start, (next_block != std::string::npos ? next_block - block_start : 1000));

            Project p;

            // Name
            size_t title_p = block.find("marked-title");
            if (title_p != std::string::npos) {
                size_t a_start = block.find('>', title_p);
                if (a_start != std::string::npos) {
                    size_t a_inner = block.find('>', a_start + 1);
                    size_t a_end   = block.find('<', a_inner + 1);
                    if (a_inner != std::string::npos && a_end != std::string::npos)
                        p.name = block.substr(a_inner + 1, a_end - a_inner - 1);
                }
            }
            if (p.name.empty()) {
                size_t dp = block.find("data-project=");
                if (dp != std::string::npos) {
                    char q = block[dp + 13];
                    size_t de = block.find(q, dp + 14);
                    if (de != std::string::npos)
                        p.name = block.substr(dp + 14, de - dp - 14);
                }
            }

            // Grade
            size_t pull_r = block.find("pull-right");
            if (pull_r != std::string::npos) {
                size_t gs = block.find('>', pull_r);
                size_t ge = block.find('<', gs + 1);
                if (gs != std::string::npos && ge != std::string::npos) {
                    std::string g = block.substr(gs + 1, ge - gs - 1);
                    size_t b = g.find_first_not_of(" \t\r\n");
                    size_t e = g.find_last_not_of(" \t\r\n");
                    if (b != std::string::npos) p.grade = g.substr(b, e - b + 1);
                }
            }

            if (p.grade.empty()) p.grade = "N/A";
            p.status = (p.grade != "N/A") ? "finished" : "in_progress";

            if (!p.name.empty()) {
                // Avoid duplicates
                bool duplicate = false;
                for (const auto& existing : out.projects) {
                    if (existing.name == p.name) { duplicate = true; break; }
                }
                if (!duplicate) out.projects.push_back(std::move(p));
            }

            search_pos = block_start + marker.size();
        }

        // Also look for active project in sidebar (e.g. CPP Module 04)
        size_t act_p = user_html.find("Your projects");
        if (act_p != std::string::npos) {
            size_t act_end = user_html.find("</div>", act_p + 100);
            if (act_end != std::string::npos) {
                size_t a_tag = user_html.find("<a", act_p);
                if (a_tag != std::string::npos && a_tag < act_end) {
                    size_t text_start = user_html.find('>', a_tag);
                    if (text_start != std::string::npos) {
                        size_t text_end = user_html.find('<', text_start + 1);
                        if (text_end != std::string::npos) {
                            std::string aname = user_html.substr(text_start + 1, text_end - text_start - 1);
                            size_t b = aname.find_first_not_of(" \t\r\n");
                            size_t e = aname.find_last_not_of(" \t\r\n");
                            if (b != std::string::npos) {
                                aname = aname.substr(b, e - b + 1);
                                bool duplicate = false;
                                for (auto& existing : out.projects) {
                                    if (existing.name == aname) {
                                        existing.status = "in_progress";
                                        duplicate = true;
                                        break;
                                    }
                                }
                                if (!duplicate && !aname.empty()) {
                                    out.projects.insert(out.projects.begin(), { aname, "N/A", "in_progress" });
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return true;
}

// ─── Format time as ISO 8601 string for slots URL parameters ─────────────────
static std::string format_iso_time(time_t t) {
    struct tm* tm_info = gmtime(&t);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S+00:00", tm_info);
    return std::string(buf);
}

// ─── Slots scraper ────────────────────────────────────────────────────────────
bool fetch_slots(const std::string& cookie_file,
                 std::vector<Slot>& out,
                 std::string&       error_out)
{
    time_t now = std::time(nullptr);
    time_t t_start = now - 2 * 86400;   // 2 days ago
    time_t t_end   = now + 14 * 86400;  // 14 days ahead

    std::string start_str = format_iso_time(t_start);
    std::string end_str   = format_iso_time(t_end);

    std::string url = "https://profile.intra.42.fr/slots.json?start=" +
                      html_parser::url_encode(start_str) +
                      "&end=" + html_parser::url_encode(end_str);

    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) {
        error_out = "Curl init failed";
        return false;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");

    curl_easy_setopt(c, CURLOPT_URL, url.c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(c);
    long http_code = 0;
    curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &http_code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);

    if (res != CURLE_OK || http_code != 200) {
        error_out = "Failed to fetch slots (HTTP " + std::to_string(http_code) + ")";
        return false;
    }

    out.clear();
    size_t pos = 0;
    while (true) {
        size_t obj = body.find('{', pos);
        if (obj == std::string::npos) break;
        size_t obj_end = body.find('}', obj);
        if (obj_end == std::string::npos) break;
        std::string chunk = body.substr(obj, obj_end - obj + 1);

        auto extract_json_val = [&](const std::string& key) -> std::string {
            std::string k = "\"" + key + "\":";
            size_t p = chunk.find(k);
            if (p == std::string::npos) return {};
            p += k.size();
            while (p < chunk.size() && (chunk[p] == ' ' || chunk[p] == '\t')) ++p;
            if (p >= chunk.size()) return {};
            if (chunk[p] == '"') {
                p++;
                size_t e = chunk.find('"', p);
                if (e == std::string::npos) return {};
                return chunk.substr(p, e - p);
            } else {
                size_t e = chunk.find_first_of(",}", p);
                if (e == std::string::npos) return {};
                return chunk.substr(p, e - p);
            }
        };

        Slot s;
        s.id       = extract_json_val("id");
        s.ids      = extract_json_val("ids");
        s.begin_at = extract_json_val("start");
        if (s.begin_at.empty()) s.begin_at = extract_json_val("begin_at");
        s.end_at   = extract_json_val("end");
        if (s.end_at.empty()) s.end_at = extract_json_val("end_at");
        s.title    = extract_json_val("title");

        if (s.ids.empty() && !s.id.empty()) s.ids = s.id;

        if (!s.begin_at.empty()) {
            out.push_back(std::move(s));
        }

        pos = obj_end + 1;
    }

    return true;
}

// ─── Slot creation ────────────────────────────────────────────────────
bool create_slot(const std::string& cookie_file,
                 const std::string& begin_at,
                 const std::string& end_at,
                 std::string&       error_out)
{
    const std::string slots_page = "https://profile.intra.42.fr/slots";
    std::string html = http_get(slots_page, cookie_file);
    if (html.empty()) {
        error_out = "Could not load slots page to retrieve CSRF token";
        return false;
    }

    std::string csrf = html_parser::get_attr_value(html, "csrf-token", "content");
    if (csrf.empty())
        csrf = html_parser::get_attr_value(html, "authenticity_token", "value");
    if (csrf.empty()) {
        error_out = "Could not extract CSRF token from slots page";
        return false;
    }

    const std::string create_url = "https://profile.intra.42.fr/slots.json";
    std::string post_fields =
        "slot[begin_at]=" + html_parser::url_encode(begin_at) +
        "&slot[end_at]="   + html_parser::url_encode(end_at);

    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) {
        error_out = "Curl init failed";
        return false;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, ("X-CSRF-Token: " + csrf).c_str());
    headers = curl_slist_append(headers, "Origin: https://profile.intra.42.fr");

    curl_easy_setopt(c, CURLOPT_URL,        create_url.c_str());
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(c, CURLOPT_REFERER,    slots_page.c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(c);
    long http_code = 0;
    curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &http_code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);

    if (res != CURLE_OK) {
        error_out = std::string("Curl error: ") + curl_easy_strerror(res);
        return false;
    }

    if (http_code == 200 || http_code == 201) {
        if (body.find("\"status\":200") != std::string::npos ||
            body.find("created") != std::string::npos) {
            return true;
        }
    }

    // Parse error message from JSON response
    size_t msg_pos = body.find("\"message\":");
    if (msg_pos != std::string::npos) {
        size_t vs = body.find('"', msg_pos + 10);
        size_t ve = body.find('"', vs + 1);
        if (vs != std::string::npos && ve != std::string::npos) {
            error_out = body.substr(vs + 1, ve - vs - 1);
            return false;
        }
    }

    size_t err_pos = body.find("\"error\":");
    if (err_pos != std::string::npos) {
        size_t vs = body.find('"', err_pos + 8);
        size_t ve = body.find('"', vs + 1);
        if (vs != std::string::npos && ve != std::string::npos) {
            error_out = body.substr(vs + 1, ve - vs - 1);
            return false;
        }
    }

    error_out = "Server rejected slot creation (HTTP " + std::to_string(http_code) + ")";
    return false;
}

// ─── Slot deletion ────────────────────────────────────────────────────
bool delete_slot(const std::string& cookie_file,
                 const std::string& slot_id,
                 std::string&       error_out)
{
    if (slot_id.empty()) {
        error_out = "Invalid slot ID";
        return false;
    }

    const std::string slots_page = "https://profile.intra.42.fr/slots";
    std::string html = http_get(slots_page, cookie_file);
    if (html.empty()) {
        error_out = "Could not load slots page";
        return false;
    }

    std::string csrf = html_parser::get_attr_value(html, "csrf-token", "content");
    if (csrf.empty())
        csrf = html_parser::get_attr_value(html, "authenticity_token", "value");
    if (csrf.empty()) {
        error_out = "Could not extract CSRF token";
        return false;
    }

    const std::string target_url = "https://profile.intra.42.fr/slots/" + slot_id + ".json";
    std::string post_fields = "_method=delete&confirm=true&ids=" + html_parser::url_encode(slot_id);

    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) {
        error_out = "Curl init failed";
        return false;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, ("X-CSRF-Token: " + csrf).c_str());
    headers = curl_slist_append(headers, "Origin: https://profile.intra.42.fr");

    curl_easy_setopt(c, CURLOPT_URL,        target_url.c_str());
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(c, CURLOPT_REFERER,    slots_page.c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(c);
    long http_code = 0;
    curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &http_code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);

    if (res != CURLE_OK) {
        error_out = std::string("Curl error: ") + curl_easy_strerror(res);
        return false;
    }

    if (http_code == 200) {
        return true;
    }

    error_out = "Failed to cancel slot (HTTP " + std::to_string(http_code) + ")";
    return false;
}

bool update_slot(const std::string& cookie_file,
                 const std::string& slot_id,
                 const std::string& slot_ids,
                 const std::string& begin_at,
                 const std::string& new_end_at,
                 std::string&       error_out)
{
    if (slot_id.empty() || slot_ids.empty()) {
        error_out = "Invalid slot ID";
        return false;
    }

    const std::string slots_page = "https://profile.intra.42.fr/slots";
    std::string html = http_get(slots_page, cookie_file);
    if (html.empty()) {
        error_out = "Could not load slots page";
        return false;
    }

    std::string csrf = html_parser::get_attr_value(html, "csrf-token", "content");
    if (csrf.empty())
        csrf = html_parser::get_attr_value(html, "authenticity_token", "value");
    if (csrf.empty()) {
        error_out = "Could not extract CSRF token";
        return false;
    }

    const std::string target_url = "https://profile.intra.42.fr/slots/" + slot_ids + ".json";
    std::string post_fields = "ids=" + html_parser::url_encode(slot_ids) +
                              "&_method=put" +
                              "&slot[begin_at]=" + html_parser::url_encode(begin_at) +
                              "&slot[end_at]=" + html_parser::url_encode(new_end_at);

    std::string body;
    CURL* c = make_curl(cookie_file, body);
    if (!c) {
        error_out = "Curl init failed";
        return false;
    }

    struct curl_slist* headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    headers = curl_slist_append(headers, "X-Requested-With: XMLHttpRequest");
    headers = curl_slist_append(headers, "Accept: application/json");
    headers = curl_slist_append(headers, ("X-CSRF-Token: " + csrf).c_str());
    headers = curl_slist_append(headers, "Origin: https://profile.intra.42.fr");

    curl_easy_setopt(c, CURLOPT_URL,        target_url.c_str());
    curl_easy_setopt(c, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(c, CURLOPT_REFERER,    slots_page.c_str());
    curl_easy_setopt(c, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(c);
    long http_code = 0;
    curl_easy_getinfo(c, CURLINFO_RESPONSE_CODE, &http_code);
    curl_slist_free_all(headers);
    curl_easy_cleanup(c);
    secure_cookie_file(cookie_file);

    if (res != CURLE_OK) {
        error_out = std::string("Curl error: ") + curl_easy_strerror(res);
        return false;
    }

    if (http_code == 200 && (body.find("\"status\":200") != std::string::npos || body.find("updated") != std::string::npos)) {
        return true;
    }

    size_t msg_pos = body.find("\"message\":");
    if (msg_pos != std::string::npos) {
        size_t vs = body.find('"', msg_pos + 10);
        size_t ve = body.find('"', vs + 1);
        if (vs != std::string::npos && ve != std::string::npos) {
            error_out = body.substr(vs + 1, ve - vs - 1);
            return false;
        }
    }

    error_out = "Server rejected update (HTTP " + std::to_string(http_code) + ")";
    return false;
}

bool download_subject(const std::string& cookie_file,
                      const std::string& project_name,
                      std::string&       out_filename,
                      std::string&       error_out)
{
    if (project_name.empty()) {
        error_out = "Project name is empty";
        return false;
    }

    std::string norm = project_name;
    for (char& ch : norm) {
        if (ch == ' ') ch = '-';
        else ch = (char)tolower((unsigned char)ch);
    }

    std::vector<std::string> candidates = { norm, "42cursus-" + norm };
    std::string pdf_url;
    std::string used_slug = norm;

    for (const auto& slug : candidates) {
        std::string url = "https://projects.intra.42.fr/projects/" + slug;
        std::string html = http_get(url, cookie_file);
        if (html.find("The page you were looking for doesn't exist") != std::string::npos) continue;

        size_t pos = 0;
        while ((pos = html.find("cdn.intra.42.fr/pdf/pdf/", pos)) != std::string::npos) {
            size_t href_start = html.rfind("href=\"", pos);
            if (href_start != std::string::npos && href_start >= (pos > 15 ? pos - 15 : 0)) {
                size_t href_end = html.find('"', pos);
                if (href_end != std::string::npos) {
                    pdf_url = html.substr(href_start + 6, href_end - (href_start + 6));
                    used_slug = slug;
                    break;
                }
            }
            pos += 24;
        }
        if (!pdf_url.empty()) break;
    }

    if (pdf_url.empty()) {
        error_out = "Could not find subject PDF for " + project_name;
        return false;
    }

    mkdir_p_file("subjects/.keep");
    std::string dest = "subjects/" + used_slug + ".pdf";

    std::string pdf_data = http_get(pdf_url, cookie_file);
    if (pdf_data.size() < 100 || pdf_data.substr(0, 4) != "%PDF") {
        error_out = "Downloaded file is not a valid PDF";
        return false;
    }

    std::ofstream ofs(dest, std::ios::binary);
    if (!ofs) {
        error_out = "Could not write to " + dest;
        return false;
    }
    ofs.write(pdf_data.data(), (std::streamsize)pdf_data.size());
    ofs.close();

    out_filename = dest;
    return true;
}

bool fetch_holygraph(const std::string& cookie_file,
                     std::vector<Milestone>& out,
                     std::string&            error_out)
{
    std::string data = http_get("https://projects.intra.42.fr/project_data.json?cursus_id=21", cookie_file);
    if (data.size() < 100) {
        error_out = "Failed to fetch Holygraph data";
        return false;
    }

    auto extract_field = [](const std::string& chunk, const std::string& key) -> std::string {
        std::string k = "\"" + key + "\":";
        size_t p = chunk.find(k);
        if (p == std::string::npos) return {};
        p += k.size();
        while (p < chunk.size() && (chunk[p] == ' ' || chunk[p] == '\t')) ++p;
        if (p >= chunk.size()) return {};
        if (chunk[p] == '"') {
            p++;
            size_t e = chunk.find('"', p);
            if (e == std::string::npos) return {};
            return chunk.substr(p, e - p);
        } else {
            size_t e = chunk.find_first_of(",}", p);
            if (e == std::string::npos) return {};
            return chunk.substr(p, e - p);
        }
    };

    out.clear();
    out.resize(7);
    out[0] = { 0, "Milestone 0 - Outer Circle / Electives", false, {} };
    out[1] = { 1, "Milestone 1 - Fundamentals (C Basics)",  true,  {} };
    out[2] = { 2, "Milestone 2 - Unix Logic & Algorithms", true,  {} };
    out[3] = { 3, "Milestone 3 - Architecture & Concurrency", true, {} };
    out[4] = { 4, "Milestone 4 - OOP & Networking",        true,  {} };
    out[5] = { 5, "Milestone 5 - Web, IRC & Virtualization", true, {} };
    out[6] = { 6, "Milestone 6 - Final Transcendence",     true,  {} };

    size_t pos = 0;
    while (true) {
        size_t obj = data.find('{', pos);
        if (obj == std::string::npos) break;
        size_t obj_end = data.find('}', obj);
        if (obj_end == std::string::npos) break;
        std::string chunk = data.substr(obj, obj_end - obj + 1);

        std::string name = extract_field(chunk, "name");
        std::string state = extract_field(chunk, "state");
        std::string mark = extract_field(chunk, "final_mark");
        std::string duration = extract_field(chunk, "duration");
        std::string difficulty = extract_field(chunk, "difficulty");
        std::string desc = extract_field(chunk, "description");
        std::string rules = extract_field(chunk, "rules");

        if (mark == "null") mark.clear();

        int rank = 0;
        if (rules.find("rank-00") != std::string::npos) rank = 1;
        else if (rules.find("rank-01") != std::string::npos) rank = 2;
        else if (rules.find("rank-02") != std::string::npos) rank = 3;
        else if (rules.find("rank-03") != std::string::npos) rank = 4;
        else if (rules.find("rank-04") != std::string::npos) rank = 5;
        else if (rules.find("rank-05") != std::string::npos) rank = 6;

        if (!name.empty() && name.find("exam") == std::string::npos) {
            HolyProject hp;
            hp.name = name;
            hp.state = state;
            hp.final_mark = mark;
            hp.duration = duration;
            hp.difficulty = difficulty;
            hp.description = desc;
            hp.slug = name;
            for (char& c : hp.slug) {
                if (c == ' ') c = '-';
                else c = (char)tolower((unsigned char)c);
            }

            bool duplicate = false;
            for (const auto& existing : out[rank].projects) {
                if (existing.name == hp.name) { duplicate = true; break; }
            }
            if (!duplicate) {
                out[rank].projects.push_back(std::move(hp));
            }
        }

        pos = obj_end + 1;
    }

    return true;
}

bool fetch_clusters(const std::string& cookie_file,
                    std::vector<ClusterStudent>& out,
                    std::string&                 error_out)
{
    std::string json = http_get("https://meta.intra.42.fr/clusters.json", cookie_file);
    if (json.empty() || json.find('[') == std::string::npos) {
        error_out = "Failed to fetch cluster data";
        return false;
    }

    auto extract_field = [](const std::string& chunk, const std::string& key) -> std::string {
        std::string k = "\"" + key + "\":";
        size_t p = chunk.find(k);
        if (p == std::string::npos) return {};
        p += k.size();
        while (p < chunk.size() && (chunk[p] == ' ' || chunk[p] == '\t')) ++p;
        if (p >= chunk.size()) return {};
        if (chunk[p] == '"') {
            p++;
            size_t e = chunk.find('"', p);
            if (e == std::string::npos) return {};
            return chunk.substr(p, e - p);
        } else {
            size_t e = chunk.find_first_of(",}", p);
            if (e == std::string::npos) return {};
            return chunk.substr(p, e - p);
        }
    };

    out.clear();
    size_t pos = 0;
    while (true) {
        size_t obj = json.find('{', pos);
        if (obj == std::string::npos) break;
        size_t obj_end = json.find('}', obj);
        if (obj_end == std::string::npos) break;
        std::string chunk = json.substr(obj, obj_end - obj + 1);

        ClusterStudent cs;
        cs.host     = extract_field(chunk, "host");
        cs.login    = extract_field(chunk, "login");
        cs.cdn_uri  = extract_field(chunk, "cdn_uri");
        cs.begin_at = extract_field(chunk, "begin_at");
        try {
            std::string cid = extract_field(chunk, "campus_id");
            if (!cid.empty()) cs.campus_id = std::stoi(cid);
        } catch (...) {}

        if (!cs.host.empty() && !cs.login.empty()) {
            out.push_back(std::move(cs));
        }

        pos = obj_end + 1;
    }

    return true;
}

bool fetch_user_full_name(const std::string& cookie_file,
                          const std::string& login,
                          std::string&       out_full_name,
                          std::string&       error_out)
{
    if (login.empty()) {
        error_out = "Login is empty";
        return false;
    }

    std::string json_body = http_get_with_accept(
        "https://profile.intra.42.fr/users/" + login,
        cookie_file,
        "application/json"
    );
    if (json_body.empty() || json_body[0] != '{') {
        error_out = "Failed to fetch profile for " + login;
        return false;
    }

    size_t p = json_body.find("\"full_name\":\"");
    if (p == std::string::npos) {
        error_out = "No full_name in profile for " + login;
        return false;
    }
    p += 13;
    size_t e = json_body.find('"', p);
    if (e == std::string::npos) {
        error_out = "Malformed full_name for " + login;
        return false;
    }
    out_full_name = json_body.substr(p, e - p);
    return !out_full_name.empty();
}

bool fetch_image(const std::string& url,
                 const std::string& cookie_file,
                 std::string&       out_data,
                 std::string&       error_out)
{
    if (url.empty()) {
        error_out = "Image URL is empty";
        return false;
    }
    out_data = http_get(url, cookie_file);
    if (out_data.empty()) {
        error_out = "Failed to download image";
        return false;
    }
    return true;
}

std::string format_iso8601(time_t t) {
    struct tm* tm_info = localtime(&t);
    char base[32];
    std::strftime(base, sizeof(base), "%Y-%m-%dT%H:%M:%S", tm_info);
    char tz[16];
    std::strftime(tz, sizeof(tz), "%z", tm_info);
    std::string tz_str = tz;
    if (tz_str.size() == 5) {
        tz_str = tz_str.substr(0, 3) + ":" + tz_str.substr(3);
    } else if (tz_str.empty()) {
        tz_str = "+00:00";
    }
    return std::string(base) + tz_str;
}

time_t parse_iso8601(const std::string& str) {
    if (str.size() < 19) return 0;
    struct tm tm_val = {};
    int year = 0, mon = 0, day = 0, hour = 0, min = 0, sec = 0;
    if (sscanf(str.c_str(), "%4d-%2d-%2dT%2d:%2d:%2d", &year, &mon, &day, &hour, &min, &sec) != 6) {
        return 0;
    }
    tm_val.tm_year  = year - 1900;
    tm_val.tm_mon   = mon - 1;
    tm_val.tm_mday  = day;
    tm_val.tm_hour  = hour;
    tm_val.tm_min   = min;
    tm_val.tm_sec   = sec;
    tm_val.tm_isdst = 0;

    time_t t = timegm(&tm_val);

    size_t tz_pos = str.find_first_of("+-Z", 19);
    if (tz_pos != std::string::npos) {
        if (str[tz_pos] == '+' || str[tz_pos] == '-') {
            int tz_h = 0, tz_m = 0;
            int sign = (str[tz_pos] == '+') ? 1 : -1;
            if (sscanf(str.c_str() + tz_pos + 1, "%2d:%2d", &tz_h, &tz_m) >= 1) {
                int offset_sec = sign * (tz_h * 3600 + tz_m * 60);
                t -= offset_sec;
            }
        }
    }
    return t;
}

void get_slot_time_points(int offset_minutes, int duration_minutes, time_t& out_begin, time_t& out_end) {
    using namespace std::chrono;
    auto now = system_clock::now() + minutes(offset_minutes);
    auto now_min = duration_cast<minutes>(now.time_since_epoch()).count();
    long rounded  = ((now_min / 15) + 1) * 15;
    auto begin_tp = system_clock::time_point(minutes(rounded));

    out_begin = system_clock::to_time_t(begin_tp);
    out_end   = out_begin + duration_minutes * 60;
}

bool slots_overlap(time_t b1, time_t e1, time_t b2, time_t e2) {
    return (b1 < e2) && (e1 > b2);
}

std::string iso_time_offset(int offset_minutes, int duration_minutes) {
    time_t begin_t = 0, end_t = 0;
    get_slot_time_points(offset_minutes, duration_minutes, begin_t, end_t);
    return format_iso8601(begin_t) + "|" + format_iso8601(end_t);
}

std::string slot_display_time(int offset_minutes) {
    time_t begin_t = 0, end_t = 0;
    get_slot_time_points(offset_minutes, 30, begin_t, end_t);
    struct tm* tm_info = localtime(&begin_t);
    char buf[16];
    std::strftime(buf, sizeof(buf), "%H:%M", tm_info);
    return std::string(buf);
}

static std::string strip_html_tags(const std::string& input) {
    std::string out;
    bool in_tag = false;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '<') in_tag = true;
        else if (input[i] == '>') in_tag = false;
        else if (!in_tag) {
            if (input[i] == '\n' || input[i] == '\r' || input[i] == '\t') {
                if (!out.empty() && out.back() != ' ') out.push_back(' ');
            } else {
                out.push_back(input[i]);
            }
        }
    }
    size_t s = out.find_first_not_of(" ");
    if (s == std::string::npos) return "";
    size_t e = out.find_last_not_of(" ");
    return out.substr(s, e - s + 1);
}

bool fetch_feedbacks(const std::string& cookie_file,
                     const std::string& user_login,
                     std::vector<EvaluationFeedback>& feedbacks_out,
                     int& pending_count_out,
                     std::string& error_out)
{
    feedbacks_out.clear();
    pending_count_out = 0;

    if (user_login.empty()) {
        error_out = "Login is empty";
        return false;
    }

    std::string url = "https://projects.intra.42.fr/users/" + user_login + "/feedbacks";
    std::string html = http_get(url, cookie_file);
    if (html.empty()) {
        error_out = "Failed to load feedbacks page";
        return false;
    }

    // Parse list items: <li class='table-item scaleteam-list-item'>
    const std::string item_marker = "scaleteam-list-item";
    size_t pos = 0;
    while ((pos = html.find(item_marker, pos)) != std::string::npos) {
        size_t block_start = html.rfind("<li", pos);
        size_t block_end   = html.find("</li>", pos);
        if (block_start == std::string::npos || block_end == std::string::npos) {
            pos += item_marker.size();
            continue;
        }

        std::string block = html.substr(block_start, block_end - block_start);
        pos = block_end + 5;

        EvaluationFeedback fb;

        // 1. Evaluator and Evaluated team
        size_t b1 = block.find("data-tooltip-login=\"");
        if (b1 != std::string::npos) {
            b1 += 20;
            size_t b1_end = block.find('"', b1);
            if (b1_end != std::string::npos) {
                fb.evaluator_login = block.substr(b1, b1_end - b1);
            }
        }

        size_t b2 = block.find("data-tooltip-login=\"", b1 != std::string::npos ? b1 : 0);
        if (b2 != std::string::npos) {
            b2 += 20;
            size_t b2_end = block.find('"', b2);
            if (b2_end != std::string::npos) {
                fb.evaluated_team = block.substr(b2, b2_end - b2);
            }
        }

        // 2. Scheduled date
        size_t sch_pos = block.find("scheduled on");
        if (sch_pos != std::string::npos) {
            size_t b_start = block.find("<b>", sch_pos);
            size_t b_end   = block.find("</b>", b_start);
            if (b_start != std::string::npos && b_end != std::string::npos) {
                fb.scheduled_at = strip_html_tags(block.substr(b_start + 3, b_end - (b_start + 3)));
            }
        }

        // 3. Project name & mark
        size_t pull_right = block.find("pull-right");
        if (pull_right != std::string::npos) {
            size_t pr_b = block.find("<b>", pull_right);
            size_t pr_e = block.find("</b>", pr_b);
            if (pr_b != std::string::npos && pr_e != std::string::npos) {
                fb.project_name = strip_html_tags(block.substr(pr_b + 3, pr_e - (pr_b + 3)));
            }

            size_t rate_b = block.find("<code class='rating'", pull_right);
            if (rate_b != std::string::npos) {
                size_t close_tag = block.find('>', rate_b);
                size_t code_end  = block.find("</code>", close_tag);
                if (close_tag != std::string::npos && code_end != std::string::npos) {
                    fb.mark = strip_html_tags(block.substr(close_tag + 1, code_end - (close_tag + 1)));
                }
            }
        }

        if (fb.mark.empty()) {
            size_t fmark = block.find("final-mark");
            if (fmark != std::string::npos) {
                size_t rate = block.find("<div class='rating'>", fmark);
                size_t rend = block.find("</div>", rate);
                if (rate != std::string::npos && rend != std::string::npos) {
                    fb.mark = strip_html_tags(block.substr(rate + 20, rend - (rate + 20)));
                }
            }
        }

        // 4. Evaluator critique comment
        size_t comm_pos = block.find("<div class='comment'>");
        if (comm_pos != std::string::npos) {
            size_t comm_end = block.find("</div>", comm_pos);
            if (comm_end != std::string::npos) {
                fb.comment = strip_html_tags(block.substr(comm_pos + 21, comm_end - (comm_pos + 21)));
            }
        }

        // 5. Student feedback & rating breakdown
        size_t fb_pos = block.find("<div class='feedback'>");
        if (fb_pos != std::string::npos) {
            size_t title_pos = block.find("title='", fb_pos);
            if (title_pos != std::string::npos && title_pos < fb_pos + 200) {
                title_pos += 7;
                size_t title_end = block.find('\'', title_pos);
                if (title_end != std::string::npos) {
                    std::string raw_title = block.substr(title_pos, title_end - title_pos);
                    // Replace &#x000A; with comma
                    size_t ent = 0;
                    while ((ent = raw_title.find("&#x000A;")) != std::string::npos) {
                        raw_title.replace(ent, 8, "  │  ");
                    }
                    fb.rating_breakdown = raw_title;
                }
            }

            size_t r_pos = block.find("<div class='rating'", fb_pos);
            if (r_pos != std::string::npos) {
                size_t r_close = block.find('>', r_pos);
                size_t r_end   = block.find("</div>", r_close);
                if (r_close != std::string::npos && r_end != std::string::npos) {
                    fb.feedback_rating = strip_html_tags(block.substr(r_close + 1, r_end - (r_close + 1)));
                }
            }

            size_t fc_pos = block.find("<div class='comment'>", fb_pos);
            if (fc_pos != std::string::npos) {
                size_t fc_end = block.find("</div>", fc_pos);
                if (fc_end != std::string::npos) {
                    fb.feedback_comment = strip_html_tags(block.substr(fc_pos + 21, fc_end - (fc_pos + 21)));
                }
            }
        }

        // Check if pending action (e.g. form to fill feedback or waiting)
        if (block.find("new_feedback") != std::string::npos ||
            block.find("Waiting for feedback") != std::string::npos ||
            (fb_pos != std::string::npos && fb.feedback_rating.empty() && fb.feedback_comment.empty()))
        {
            fb.is_pending = true;
            pending_count_out++;
        }

        fb.is_given = (fb.evaluator_login == user_login);
        feedbacks_out.push_back(std::move(fb));
    }

    return true;
}

bool fetch_project_scale_teams(const std::string& cookie_file,
                               const std::string& project_slug,
                               std::vector<ScaleTeamRecord>& scale_teams_out,
                               std::string& error_out)
{
    scale_teams_out.clear();
    if (project_slug.empty()) {
        error_out = "Project slug is empty";
        return false;
    }

    std::string norm = project_slug;
    for (char& c : norm) {
        if (c == ' ') c = '-';
        else c = (char)tolower((unsigned char)c);
    }

    std::string url = "https://projects.intra.42.fr/" + norm + "/scale_teams";
    std::string html = http_get(url, cookie_file);
    if (html.empty() || html.find("The page you were looking for doesn't exist") != std::string::npos) {
        url = "https://projects.intra.42.fr/projects/" + norm + "/scale_teams";
        html = http_get(url, cookie_file);
    }

    if (html.empty()) {
        error_out = "Failed to load project scale teams";
        return false;
    }

    const std::string item_marker = "scaleteam-list-item";
    size_t pos = 0;
    while ((pos = html.find(item_marker, pos)) != std::string::npos) {
        size_t block_start = html.rfind("<li", pos);
        size_t block_end   = html.find("</li>", pos);
        if (block_start == std::string::npos || block_end == std::string::npos) {
            pos += item_marker.size();
            continue;
        }

        std::string block = html.substr(block_start, block_end - block_start);
        pos = block_end + 5;

        ScaleTeamRecord rec;
        rec.project_slug = norm;

        // Evaluator
        size_t b1 = block.find("data-tooltip-login=\"");
        if (b1 != std::string::npos) {
            b1 += 20;
            size_t b1_end = block.find('"', b1);
            if (b1_end != std::string::npos) rec.evaluator_login = block.substr(b1, b1_end - b1);
        }

        // Evaluated
        size_t b2 = block.find("data-tooltip-login=\"", b1 != std::string::npos ? b1 : 0);
        if (b2 != std::string::npos) {
            b2 += 20;
            size_t b2_end = block.find('"', b2);
            if (b2_end != std::string::npos) rec.evaluated_team = block.substr(b2, b2_end - b2);
        }

        // Scheduled on
        size_t sch_pos = block.find("scheduled on");
        if (sch_pos != std::string::npos) {
            size_t b_start = block.find("<b>", sch_pos);
            size_t b_end   = block.find("</b>", b_start);
            if (b_start != std::string::npos && b_end != std::string::npos) {
                rec.scheduled_at = strip_html_tags(block.substr(b_start + 3, b_end - (b_start + 3)));
            }
        }

        // Mark
        size_t rate_b = block.find("<code class='rating'");
        if (rate_b != std::string::npos) {
            size_t close_tag = block.find('>', rate_b);
            size_t code_end  = block.find("</code>", close_tag);
            if (close_tag != std::string::npos && code_end != std::string::npos) {
                rec.mark = strip_html_tags(block.substr(close_tag + 1, code_end - (close_tag + 1)));
            }
        }
        if (rec.mark.empty()) {
            size_t fmark = block.find("final-mark");
            if (fmark != std::string::npos) {
                size_t rate = block.find("<div class='rating'>", fmark);
                size_t rend = block.find("</div>", rate);
                if (rate != std::string::npos && rend != std::string::npos) {
                    rec.mark = strip_html_tags(block.substr(rate + 20, rend - (rate + 20)));
                }
            }
        }

        // Evaluator comment
        size_t comm_pos = block.find("<div class='comment'>");
        if (comm_pos != std::string::npos) {
            size_t comm_end = block.find("</div>", comm_pos);
            if (comm_end != std::string::npos) {
                rec.comment = strip_html_tags(block.substr(comm_pos + 21, comm_end - (comm_pos + 21)));
            }
        }

        // Student feedback
        size_t fb_pos = block.find("<div class='feedback'>");
        if (fb_pos != std::string::npos) {
            size_t r_pos = block.find("<div class='rating'", fb_pos);
            if (r_pos != std::string::npos) {
                size_t r_close = block.find('>', r_pos);
                size_t r_end   = block.find("</div>", r_close);
                if (r_close != std::string::npos && r_end != std::string::npos) {
                    rec.feedback_rating = strip_html_tags(block.substr(r_close + 1, r_end - (r_close + 1)));
                }
            }

            size_t fc_pos = block.find("<div class='comment'>", fb_pos);
            if (fc_pos != std::string::npos) {
                size_t fc_end = block.find("</div>", fc_pos);
                if (fc_end != std::string::npos) {
                    rec.feedback_comment = strip_html_tags(block.substr(fc_pos + 21, fc_end - (fc_pos + 21)));
                }
            }
        }

        scale_teams_out.push_back(std::move(rec));
    }

    return true;
}

} // namespace network
