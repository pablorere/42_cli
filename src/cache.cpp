#include "cache.hpp"
#include "config.hpp"
#include "image_renderer.hpp"

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace cache {

// ─────────────────────────────────────────────────────────────────────────────
// Filesystem helpers
// ─────────────────────────────────────────────────────────────────────────────
static void mkdir_p(const std::string& dir, mode_t mode = 0755) {
    if (dir.empty()) return;
    std::string current;
    for (size_t i = 0; i < dir.size(); ++i) {
        current += dir[i];
        if (dir[i] == '/' || i == dir.size() - 1) {
            struct stat st;
            if (stat(current.c_str(), &st) != 0) {
                mkdir(current.c_str(), mode);
            }
        }
    }
}

std::string cache_dir() {
    return Config::get_data_dir() + "/cache";
}

std::string images_dir() {
    return cache_dir() + "/images";
}

static std::string profile_cache_path() {
    return cache_dir() + "/profile.json";
}

// ─────────────────────────────────────────────────────────────────────────────
// Minimal JSON writer
// ─────────────────────────────────────────────────────────────────────────────
static std::string json_escape(const std::string& s) {
    std::string out;
    out.reserve(s.size() + 8);
    for (unsigned char c : s) {
        switch (c) {
            case '"':  out += "\\\""; break;
            case '\\': out += "\\\\"; break;
            case '\b': out += "\\b";  break;
            case '\f': out += "\\f";  break;
            case '\n': out += "\\n";  break;
            case '\r': out += "\\r";  break;
            case '\t': out += "\\t";  break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    std::snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned>(c));
                    out += buf;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    return out;
}

static void put_str(std::ostringstream& o, const char* k, const std::string& v) {
    o << '"' << k << "\":\"" << json_escape(v) << '"';
}
static void put_int(std::ostringstream& o, const char* k, int v) {
    o << '"' << k << "\":" << v;
}
static void put_bool(std::ostringstream& o, const char* k, bool v) {
    o << '"' << k << "\":" << (v ? "true" : "false");
}

// ─────────────────────────────────────────────────────────────────────────────
// Minimal JSON parser
// ─────────────────────────────────────────────────────────────────────────────
struct JVal {
    enum T { Null, Bool, Num, Str, Arr, Obj } t = Null;
    bool b = false;
    double n = 0;
    std::string s;
    std::vector<JVal> arr;
    std::vector<std::pair<std::string, JVal>> obj;

    const JVal* find(const std::string& key) const {
        if (t != Obj) return nullptr;
        for (const auto& kv : obj)
            if (kv.first == key) return &kv.second;
        return nullptr;
    }
    std::string str_or(const std::string& def = "") const { return t == Str ? s : def; }
    int         int_or(int def = 0) const { return t == Num ? static_cast<int>(n) : def; }
    bool        bool_or(bool def = false) const { return t == Bool ? b : def; }
};

static const JVal* jchild(const JVal& v, const char* k) { return v.find(k); }
static std::string jstr(const JVal& v, const char* k, const std::string& def = "") {
    const JVal* c = jchild(v, k);
    return c ? c->str_or(def) : def;
}
static int jint(const JVal& v, const char* k, int def = 0) {
    const JVal* c = jchild(v, k);
    return c ? c->int_or(def) : def;
}
static bool jbool(const JVal& v, const char* k, bool def = false) {
    const JVal* c = jchild(v, k);
    return c ? c->bool_or(def) : def;
}

struct JParser {
    const std::string& src;
    size_t pos = 0;
    bool   ok  = true;

    explicit JParser(const std::string& in) : src(in) {}

    void skip_ws() {
        while (pos < src.size()) {
            char c = src[pos];
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') ++pos;
            else break;
        }
    }

    bool consume(char c) {
        skip_ws();
        if (pos < src.size() && src[pos] == c) { ++pos; return true; }
        return false;
    }

    std::string parse_string() {
        std::string out;
        if (pos >= src.size() || src[pos] != '"') { ok = false; return out; }
        ++pos;
        while (pos < src.size()) {
            char c = src[pos++];
            if (c == '"') return out;
            if (c == '\\') {
                if (pos >= src.size()) { ok = false; return out; }
                char e = src[pos++];
                switch (e) {
                    case '"':  out += '"';  break;
                    case '\\': out += '\\'; break;
                    case '/':  out += '/';  break;
                    case 'b':  out += '\b'; break;
                    case 'f':  out += '\f'; break;
                    case 'n':  out += '\n'; break;
                    case 'r':  out += '\r'; break;
                    case 't':  out += '\t'; break;
                    case 'u': {
                        if (pos + 4 > src.size()) { ok = false; return out; }
                        unsigned cp = 0;
                        for (int i = 0; i < 4; ++i) {
                            char h = src[pos++];
                            cp <<= 4;
                            if (h >= '0' && h <= '9')      cp |= static_cast<unsigned>(h - '0');
                            else if (h >= 'a' && h <= 'f') cp |= static_cast<unsigned>(h - 'a' + 10);
                            else if (h >= 'A' && h <= 'F') cp |= static_cast<unsigned>(h - 'A' + 10);
                            else { ok = false; return out; }
                        }
                        if (cp < 0x80) {
                            out += static_cast<char>(cp);
                        } else if (cp < 0x800) {
                            out += static_cast<char>(0xC0 | (cp >> 6));
                            out += static_cast<char>(0x80 | (cp & 0x3F));
                        } else {
                            out += static_cast<char>(0xE0 | (cp >> 12));
                            out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
                            out += static_cast<char>(0x80 | (cp & 0x3F));
                        }
                        break;
                    }
                    default: out += e; break;
                }
            } else {
                out += c;
            }
        }
        ok = false;
        return out;
    }

    JVal parse_value(int depth = 0) {
        JVal v;
        if (depth > 200) { ok = false; return v; }
        skip_ws();
        if (pos >= src.size()) { ok = false; return v; }
        char c = src[pos];

        if (c == '"') {
            v.t = JVal::Str;
            v.s = parse_string();
        } else if (c == '{') {
            v.t = JVal::Obj;
            ++pos;
            if (consume('}')) return v;
            while (ok) {
                skip_ws();
                std::string key = parse_string();
                if (!ok) break;
                if (!consume(':')) { ok = false; break; }
                JVal child = parse_value(depth + 1);
                if (!ok) break;
                v.obj.emplace_back(std::move(key), std::move(child));
                skip_ws();
                if (consume(',')) continue;
                if (consume('}')) break;
                ok = false;
                break;
            }
        } else if (c == '[') {
            v.t = JVal::Arr;
            ++pos;
            if (consume(']')) return v;
            while (ok) {
                JVal child = parse_value(depth + 1);
                if (!ok) break;
                v.arr.push_back(std::move(child));
                skip_ws();
                if (consume(',')) continue;
                if (consume(']')) break;
                ok = false;
                break;
            }
        } else if (c == 't' && src.compare(pos, 4, "true") == 0) {
            v.t = JVal::Bool; v.b = true; pos += 4;
        } else if (c == 'f' && src.compare(pos, 5, "false") == 0) {
            v.t = JVal::Bool; v.b = false; pos += 5;
        } else if (c == 'n' && src.compare(pos, 4, "null") == 0) {
            v.t = JVal::Null; pos += 4;
        } else {
            size_t start = pos;
            if (pos < src.size() && (src[pos] == '-' || src[pos] == '+')) ++pos;
            while (pos < src.size()) {
                char d = src[pos];
                if ((d >= '0' && d <= '9') || d == '.' || d == 'e' || d == 'E' ||
                    d == '-' || d == '+') ++pos;
                else break;
            }
            if (pos == start) { ok = false; return v; }
            v.t = JVal::Num;
            try { v.n = std::stod(src.substr(start, pos - start)); } catch (...) { v.n = 0; }
        }
        return v;
    }
};

static bool parse_json(const std::string& text, JVal& out) {
    JParser p(text);
    out = p.parse_value();
    if (!p.ok) return false;
    p.skip_ws();
    return true;
}

// ─────────────────────────────────────────────────────────────────────────────
// Profile (de)serialization
// ─────────────────────────────────────────────────────────────────────────────
static std::string serialize_profile(const Profile& p) {
    std::ostringstream o;
    o << "{";
    put_str(o, "login", p.login); o << ",";
    put_str(o, "display_name", p.display_name); o << ",";
    put_str(o, "level", p.level); o << ",";
    put_str(o, "wallet", p.wallet); o << ",";
    put_str(o, "correction_points", p.correction_points); o << ",";
    put_str(o, "location", p.location); o << ",";
    put_str(o, "avatar_url", p.avatar_url); o << ",";
    put_int(o, "pending_feedbacks_count", p.pending_feedbacks_count); o << ",";

    o << "\"projects\":[";
    for (size_t i = 0; i < p.projects.size(); ++i) {
        if (i) o << ",";
        const auto& x = p.projects[i];
        o << "{"; put_str(o, "name", x.name); o << ",";
        put_str(o, "grade", x.grade); o << ",";
        put_str(o, "status", x.status); o << "}";
    }
    o << "],";

    o << "\"slots\":[";
    for (size_t i = 0; i < p.slots.size(); ++i) {
        if (i) o << ",";
        const auto& x = p.slots[i];
        o << "{"; put_str(o, "begin_at", x.begin_at); o << ",";
        put_str(o, "end_at", x.end_at); o << ",";
        put_str(o, "id", x.id); o << ",";
        put_str(o, "ids", x.ids); o << ",";
        put_str(o, "title", x.title); o << "}";
    }
    o << "],";

    o << "\"roadmap\":[";
    for (size_t i = 0; i < p.roadmap.size(); ++i) {
        if (i) o << ",";
        const auto& m = p.roadmap[i];
        o << "{"; put_int(o, "rank", m.rank); o << ",";
        put_str(o, "name", m.name); o << ",";
        put_bool(o, "expanded", m.expanded); o << ",";
        o << "\"projects\":[";
        for (size_t j = 0; j < m.projects.size(); ++j) {
            if (j) o << ",";
            const auto& x = m.projects[j];
            o << "{"; put_str(o, "name", x.name); o << ",";
            put_str(o, "state", x.state); o << ",";
            put_str(o, "final_mark", x.final_mark); o << ",";
            put_str(o, "duration", x.duration); o << ",";
            put_str(o, "difficulty", x.difficulty); o << ",";
            put_str(o, "description", x.description); o << ",";
            put_str(o, "slug", x.slug); o << "}";
        }
        o << "]}";
    }
    o << "],";

    o << "\"cluster_students\":[";
    for (size_t i = 0; i < p.cluster_students.size(); ++i) {
        if (i) o << ",";
        const auto& x = p.cluster_students[i];
        o << "{"; put_str(o, "host", x.host); o << ",";
        put_str(o, "login", x.login); o << ",";
        put_str(o, "full_name", x.full_name); o << ",";
        put_str(o, "cdn_uri", x.cdn_uri); o << ",";
        put_str(o, "begin_at", x.begin_at); o << ",";
        put_int(o, "campus_id", x.campus_id); o << "}";
    }
    o << "],";

    o << "\"feedbacks\":[";
    for (size_t i = 0; i < p.feedbacks.size(); ++i) {
        if (i) o << ",";
        const auto& x = p.feedbacks[i];
        o << "{"; put_str(o, "id", x.id); o << ",";
        put_str(o, "project_name", x.project_name); o << ",";
        put_str(o, "evaluator_login", x.evaluator_login); o << ",";
        put_str(o, "evaluated_team", x.evaluated_team); o << ",";
        put_str(o, "scheduled_at", x.scheduled_at); o << ",";
        put_str(o, "mark", x.mark); o << ",";
        put_str(o, "comment", x.comment); o << ",";
        put_str(o, "feedback_rating", x.feedback_rating); o << ",";
        put_str(o, "feedback_comment", x.feedback_comment); o << ",";
        put_str(o, "rating_breakdown", x.rating_breakdown); o << ",";
        put_bool(o, "is_given", x.is_given); o << ",";
        put_bool(o, "is_pending", x.is_pending); o << "}";
    }
    o << "],";

    o << "\"project_scale_teams\":[";
    for (size_t i = 0; i < p.project_scale_teams.size(); ++i) {
        if (i) o << ",";
        const auto& x = p.project_scale_teams[i];
        o << "{"; put_str(o, "project_slug", x.project_slug); o << ",";
        put_str(o, "evaluator_login", x.evaluator_login); o << ",";
        put_str(o, "evaluated_team", x.evaluated_team); o << ",";
        put_str(o, "scheduled_at", x.scheduled_at); o << ",";
        put_str(o, "mark", x.mark); o << ",";
        put_str(o, "comment", x.comment); o << ",";
        put_str(o, "feedback_rating", x.feedback_rating); o << ",";
        put_str(o, "feedback_comment", x.feedback_comment); o << "}";
    }
    o << "]";

    o << "}";
    return o.str();
}

static void load_profile_from(const JVal& root, Profile& out) {
    out = Profile{};
    out.login             = jstr(root, "login");
    out.display_name      = jstr(root, "display_name");
    out.level             = jstr(root, "level");
    out.wallet            = jstr(root, "wallet");
    out.correction_points = jstr(root, "correction_points");
    out.location          = jstr(root, "location");
    out.avatar_url        = jstr(root, "avatar_url");
    out.pending_feedbacks_count = jint(root, "pending_feedbacks_count", 0);

    if (const JVal* a = jchild(root, "projects"); a && a->t == JVal::Arr) {
        for (const auto& e : a->arr) {
            Project x;
            x.name   = jstr(e, "name");
            x.grade  = jstr(e, "grade");
            x.status = jstr(e, "status");
            out.projects.push_back(std::move(x));
        }
    }

    if (const JVal* a = jchild(root, "slots"); a && a->t == JVal::Arr) {
        for (const auto& e : a->arr) {
            Slot x;
            x.begin_at = jstr(e, "begin_at");
            x.end_at   = jstr(e, "end_at");
            x.id       = jstr(e, "id");
            x.ids      = jstr(e, "ids");
            x.title    = jstr(e, "title");
            out.slots.push_back(std::move(x));
        }
    }

    if (const JVal* a = jchild(root, "roadmap"); a && a->t == JVal::Arr) {
        for (const auto& e : a->arr) {
            Milestone m;
            m.rank     = jint(e, "rank", 0);
            m.name     = jstr(e, "name");
            m.expanded = jbool(e, "expanded", true);
            if (const JVal* pl = jchild(e, "projects"); pl && pl->t == JVal::Arr) {
                for (const auto& pe : pl->arr) {
                    HolyProject x;
                    x.name        = jstr(pe, "name");
                    x.state       = jstr(pe, "state");
                    x.final_mark  = jstr(pe, "final_mark");
                    x.duration    = jstr(pe, "duration");
                    x.difficulty  = jstr(pe, "difficulty");
                    x.description = jstr(pe, "description");
                    x.slug        = jstr(pe, "slug");
                    m.projects.push_back(std::move(x));
                }
            }
            out.roadmap.push_back(std::move(m));
        }
    }

    if (const JVal* a = jchild(root, "cluster_students"); a && a->t == JVal::Arr) {
        for (const auto& e : a->arr) {
            ClusterStudent x;
            x.host      = jstr(e, "host");
            x.login     = jstr(e, "login");
            x.full_name = jstr(e, "full_name");
            x.cdn_uri   = jstr(e, "cdn_uri");
            x.begin_at  = jstr(e, "begin_at");
            x.campus_id = jint(e, "campus_id", 0);
            out.cluster_students.push_back(std::move(x));
        }
    }

    if (const JVal* a = jchild(root, "feedbacks"); a && a->t == JVal::Arr) {
        for (const auto& e : a->arr) {
            EvaluationFeedback x;
            x.id               = jstr(e, "id");
            x.project_name     = jstr(e, "project_name");
            x.evaluator_login  = jstr(e, "evaluator_login");
            x.evaluated_team   = jstr(e, "evaluated_team");
            x.scheduled_at     = jstr(e, "scheduled_at");
            x.mark             = jstr(e, "mark");
            x.comment          = jstr(e, "comment");
            x.feedback_rating  = jstr(e, "feedback_rating");
            x.feedback_comment = jstr(e, "feedback_comment");
            x.rating_breakdown = jstr(e, "rating_breakdown");
            x.is_given         = jbool(e, "is_given", false);
            x.is_pending       = jbool(e, "is_pending", false);
            out.feedbacks.push_back(std::move(x));
        }
    }

    if (const JVal* a = jchild(root, "project_scale_teams"); a && a->t == JVal::Arr) {
        for (const auto& e : a->arr) {
            ScaleTeamRecord x;
            x.project_slug     = jstr(e, "project_slug");
            x.evaluator_login  = jstr(e, "evaluator_login");
            x.evaluated_team   = jstr(e, "evaluated_team");
            x.scheduled_at     = jstr(e, "scheduled_at");
            x.mark             = jstr(e, "mark");
            x.comment          = jstr(e, "comment");
            x.feedback_rating  = jstr(e, "feedback_rating");
            x.feedback_comment = jstr(e, "feedback_comment");
            out.project_scale_teams.push_back(std::move(x));
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Profile cache API
// ─────────────────────────────────────────────────────────────────────────────
bool save_profile(const Profile& p) {
    mkdir_p(cache_dir(), 0700);
    const std::string path = profile_cache_path();
    const std::string tmp  = path + ".tmp";

    std::ofstream out(tmp, std::ios::binary | std::ios::trunc);
    if (!out.is_open()) return false;
    out << serialize_profile(p);
    out.close();
    if (!out) { std::remove(tmp.c_str()); return false; }

    chmod(tmp.c_str(), S_IRUSR | S_IWUSR);
    if (std::rename(tmp.c_str(), path.c_str()) != 0) {
        std::remove(tmp.c_str());
        return false;
    }
    return true;
}

bool load_profile(Profile& out) {
    std::ifstream in(profile_cache_path(), std::ios::binary);
    if (!in.is_open()) return false;

    std::ostringstream ss;
    ss << in.rdbuf();
    const std::string txt = ss.str();
    if (txt.size() < 3) return false;

    JVal root;
    if (!parse_json(txt, root) || root.t != JVal::Obj) return false;

    try {
        load_profile_from(root, out);
    } catch (...) {
        return false;
    }
    return true;
}

bool profile_cache_exists() {
    struct stat st;
    return stat(profile_cache_path().c_str(), &st) == 0 && st.st_size > 2;
}

void purge_profile() {
    std::remove(profile_cache_path().c_str());
}

// ─────────────────────────────────────────────────────────────────────────────
// Image byte cache API
// ─────────────────────────────────────────────────────────────────────────────
static uint64_t fnv1a(const std::string& s) {
    uint64_t h = 1469598103934665603ULL;
    for (unsigned char c : s) {
        h ^= c;
        h *= 1099511628211ULL;
    }
    return h;
}

static std::string image_path_for(const std::string& url) {
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%016llx",
                  static_cast<unsigned long long>(fnv1a(url)));
    return images_dir() + "/" + buf + ".img";
}

bool save_image_bytes(const std::string& url, const std::string& data) {
    if (url.empty() || data.empty()) return false;
    mkdir_p(images_dir(), 0700);

    const std::string path = image_path_for(url);
    const std::string tmp  = path + ".tmp";

    std::ofstream out(tmp, std::ios::binary | std::ios::trunc);
    if (!out.is_open()) return false;
    out << url << "\n";
    out.write(data.data(), static_cast<std::streamsize>(data.size()));
    out.close();
    if (!out) { std::remove(tmp.c_str()); return false; }

    chmod(tmp.c_str(), S_IRUSR | S_IWUSR);
    if (std::rename(tmp.c_str(), path.c_str()) != 0) {
        std::remove(tmp.c_str());
        return false;
    }
    return true;
}

bool load_image_bytes(const std::string& url, std::string& out) {
    if (url.empty()) return false;
    std::ifstream in(image_path_for(url), std::ios::binary);
    if (!in.is_open()) return false;

    std::string first;
    std::getline(in, first);
    if (first.empty()) return false;

    std::ostringstream ss;
    ss << in.rdbuf();
    out = ss.str();
    return !out.empty();
}

bool image_cache_exists(const std::string& url) {
    if (url.empty()) return false;
    struct stat st;
    return stat(image_path_for(url).c_str(), &st) == 0 && st.st_size > 1;
}

int load_all_cached_images() {
    DIR* d = opendir(images_dir().c_str());
    if (!d) return 0;

    int count = 0;
    struct dirent* ent;
    while ((ent = readdir(d)) != nullptr) {
        const std::string name = ent->d_name;
        if (name.size() < 4 || name.substr(name.size() - 4) != ".img") continue;

        std::ifstream in(images_dir() + "/" + name, std::ios::binary);
        if (!in.is_open()) continue;

        std::string url;
        std::getline(in, url);
        if (url.empty()) continue;

        std::ostringstream ss;
        ss << in.rdbuf();
        const std::string data = ss.str();
        if (data.empty()) continue;

        if (image_renderer::load_image_from_bytes(url, data)) ++count;
    }
    closedir(d);
    return count;
}

} // namespace cache
