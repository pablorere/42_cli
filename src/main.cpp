#include "types.hpp"
#include "renderer.hpp"
#include "network.hpp"
#include "network_worker.hpp"
#include "theme.hpp"
#include "config.hpp"
#include "cache.hpp"
#include "image_renderer.hpp"
#include "clipboard.hpp"
#include "pdf_preview.hpp"
#include "i18n.hpp"

#include <ncurses.h>
#include <string>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <csignal>
#include <atomic>
#include <sys/stat.h>

// ─── Global quit flag (signal handler) ───────────────────────────────────────
static std::atomic<bool> g_quit{false};
static void handle_sigint(int) { g_quit.store(true); }

// Parse a cluster host like "c3r1s2" into 0-based room/row/seat.
static bool parse_host_desk(const std::string& host, int& room, int& row, int& seat) {
    std::string h;
    h.reserve(host.size());
    for (char c : host) {
        if (c != '-' && c != '_' && c != ' ')
            h += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    size_t i = 1;
    auto read_num = [&](int& out) -> bool {
        int v = 0; bool any = false;
        while (i < h.size() && std::isdigit(static_cast<unsigned char>(h[i]))) {
            v = v * 10 + (h[i] - '0'); ++i; any = true;
        }
        out = v;
        return any;
    };
    if (h.size() < 3 || h[0] != 'c') return false;
    int r1 = 0, r2 = 0, r3 = 0;
    if (!read_num(r1)) return false;
    if (i >= h.size() || h[i] != 'r') return false;
    ++i;
    if (!read_num(r2)) return false;
    if (i >= h.size() || h[i] != 's') return false;
    ++i;
    if (!read_num(r3)) return false;
    room = r1 - 1; row = r2 - 1; seat = r3 - 1;
    return room >= 0 && room < 4 &&
           row >= 0 && row < cluster_layout::ROWS &&
           seat >= 0 && seat < cluster_layout::SEATS;
}

// ─── CLI Help & List Themes ───────────────────────────────────────────────────
static void print_help(const char* prog) {
    std::cout << "Intra 42 TUI — Lightweight Native C++20 Client for intra.42.fr\n\n"
              << "Usage: " << prog << " [OPTIONS]\n\n"
              << "Options:\n"
              << "  -t, --theme <id|index>   Set theme by slug (e.g. nord, dracula) or number (1-10)\n"
              << "  --list-themes            List all 10 available themes and exit\n"
              << "  -c, --config <file>      Path to custom config.ini\n"
              << "  -k, --cookie <file>      Path to cookies.txt\n"
              << "  --login <login>          Headless credential login; pair with --password\n"
              << "  --password <password>    Password for --login (prints result and exits)\n"
              << "  -h, --help               Show this help message and exit\n\n"
              << "Navigation & Keybindings:\n"
              << "  h, j, k, l               Vim movement across tabs, trees, and lists\n"
              << "  [ / ]                    Cycle Dashboard subviews (Overview, Scale Teams, Points & Pool)\n"
              << "  Enter / f                Inspect pending feedback details / critique breakdown in Dashboard\n"
              << "  Tab / Shift-Tab / gt/gT  Next / previous tab (4 tabs)\n"
              << "  /                        Focus global search (online users + projects)\n"
              << "  1, 2, 3, 4               Direct jump to Dashboard, Roadmap, Slots, Cluster\n"
              << "  Space / Enter            Toggle milestone in Roadmap / open user profile in Cluster\n"
              << "  d                        Trim last 15m from slot / Download PDF subject\n"
              << "  D / x                    Delete entire slot block\n"
              << "  s                        Create slot (+offset) / Download PDF subject\n"
              << "  t                        Open interactive Theme Chooser modal\n"
              << "  Esc                      Open the main menu (Settings, Help, Resume, Quit)\n"
              << "  r                        Refresh/sync data from intra\n"
              << "  p                        Open downloaded subject preview (Roadmap)\n"
              << "  Enter                    Project action menu (preview / external / download)\n"
              << "  y                        Copy selected cluster user's login to clipboard\n"
              << "  Mouse                    Click tabs/lists/desks; wheel scrolls; right-click copies login\n"
              << "  q                        Quit application (press twice to confirm)\n";
}

static void list_themes() {
    std::cout << "Available Themes for 42_cli:\n";
    const auto& themes = theme::get_all_themes();
    for (size_t i = 0; i < themes.size(); ++i) {
        std::cout << "  [" << std::right << std::setw(2) << (i + 1) << "] "
                  << std::left << std::setw(24) << themes[i].id
                  << themes[i].display_name;
        if (i == 0) std::cout << " (Default)";
        std::cout << "\n";
    }
}

// Cycle a string value through a list of options (dir = -1 / +1).
static std::string cycle_choice(const std::vector<std::string>& options,
                                const std::string& current, int dir) {
    if (options.empty()) return current;
    int idx = 0;
    for (int i = 0; i < (int)options.size(); ++i) {
        if (options[i] == current) { idx = i; break; }
    }
    idx = (idx + dir) % (int)options.size();
    if (idx < 0) idx += (int)options.size();
    return options[idx];
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    // 1. Initialize configuration with defaults, disk file, and env overrides
    Config::get().ensure_defaults();
    Config::get().load();
    Config::get().apply_env_overrides();

    // 2. Parse CLI arguments
    std::string cli_user;
    std::string cli_pass;
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            print_help(argv[0]);
            return 0;
        }
        if (arg == "--list-themes") {
            list_themes();
            return 0;
        }
        if ((arg == "-t" || arg == "--theme") && i + 1 < argc) {
            std::string theme_arg = argv[++i];
            const auto& pal = theme::get_theme(theme_arg);
            Config::get().theme = pal.id;
        } else if ((arg == "-c" || arg == "--config") && i + 1 < argc) {
            std::string config_path = argv[++i];
            Config::get().load(config_path);
        } else if ((arg == "-k" || arg == "--cookie") && i + 1 < argc) {
            Config::get().cookie_path = argv[++i];
        } else if (arg == "--login" && i + 1 < argc) {
            cli_user = argv[++i];
        } else if (arg == "--password" && i + 1 < argc) {
            cli_pass = argv[++i];
        }
    }

    // 2b. Headless credential login (testing / scripting helper).
    if (!cli_user.empty() || !cli_pass.empty()) {
        if (cli_user.empty() || cli_pass.empty()) {
            std::cerr << "error: --login and --password must be used together\n";
            return 2;
        }
        network::global_init();

        const std::string cookie = network::cookie_file_path();
        std::string login_err;
        if (!network::do_login(cli_user, cli_pass, cookie, login_err)) {
            std::cerr << "login failed: " << login_err << "\n";
            network::global_cleanup();
            return 1;
        }

        Profile prof;
        std::string prof_err;
        if (!network::fetch_profile(cookie, prof, prof_err)) {
            std::cerr << "logged in, but profile fetch failed: " << prof_err << "\n";
            network::global_cleanup();
            return 1;
        }

        std::cout << "logged in as @" << prof.login;
        if (!prof.display_name.empty() && prof.display_name != prof.login)
            std::cout << " (" << prof.display_name << ")";
        std::cout << "\n";
        network::global_cleanup();
        return 0;
    }

    std::signal(SIGINT, handle_sigint);

    network::global_init();

    SharedState    state;
    NetworkWorker  worker(state);
    Renderer       renderer;

    auto tab_from_code = [](const std::string& code) -> Tab {
        if (code == "roadmap") return Tab::Roadmap;
        if (code == "slots")   return Tab::Slots;
        if (code == "cluster") return Tab::Cluster;
        return Tab::Dashboard;
    };

    Tab  current_tab  = tab_from_code(Config::get().start_tab);
    Tab  prev_tab     = Tab::Dashboard;
    int  dash_subview = 0; // 0: Overview, 1: Scale Teams, 2: Points & Pool
    int  dash_sel     = 0;
    bool dash_inspect = false;
    int  slot_sel     = 0;
    int  tree_sel     = 0;
    int  cluster_sel  = -1;  // -1 when the current cluster has nobody online
    int  cluster_room = 2; // Default to Cluster 3 (index 2) where students are online
    int  minimap_hover = -1; // room*CELLS+desk of the hovered dashboard minimap desk
    bool        user_modal_open  = false;   // full-screen user profile modal
    std::string user_modal_login;
    SearchState search;                     // global dynamic search

    auto cluster_snapshot = [&]() {
        std::lock_guard<std::mutex> lk(state.mtx);
        return state.profile.cluster_students;
    };

    // Snap the cluster cursor onto an occupied desk (first one if the current
    // selection is none or became vacant). Leaves -1 when the cluster is empty.
    auto snap_cluster_selection = [&]() {
        std::vector<ClusterStudent> cs = cluster_snapshot();
        int r = (cluster_sel >= 0) ? cluster_layout::row_of(cluster_sel) : -1;
        int s = (cluster_sel >= 0) ? cluster_layout::seat_of(cluster_sel) : -1;
        if (cluster_sel < 0 || !cluster_layout::occupied(cs, cluster_room, r, s)) {
            cluster_sel = cluster_layout::first_occupied(cs, cluster_room);
        }
    };

    auto enqueue_cluster_image_if_needed = [&](int room, int sel) {
        if (sel < 0) return;
        int r = cluster_layout::row_of(sel);
        int s = cluster_layout::seat_of(sel);
        std::string target = cluster_layout::host_of(room, r, s);
        std::lock_guard<std::mutex> lk(state.mtx);
        for (const auto& cs : state.profile.cluster_students) {
            if (cluster_layout::normalize_host(cs.host) == target) {
                if (!cs.cdn_uri.empty() && !image_renderer::has_image(cs.cdn_uri)) {
                    worker.enqueue({ NetTaskKind::FetchImage, cs.cdn_uri, "" });
                }
                if (cs.full_name.empty()) {
                    worker.enqueue({ NetTaskKind::FetchClusterUser, cs.login, "" });
                }
                break;
            }
        }
    };

    auto login_at_desk = [&](int room, int idx) -> std::string {
        if (idx < 0) return {};
        std::string target = cluster_layout::host_of(room, cluster_layout::row_of(idx), cluster_layout::seat_of(idx));
        std::lock_guard<std::mutex> lk(state.mtx);
        for (const auto& cs : state.profile.cluster_students) {
            if (cluster_layout::normalize_host(cs.host) == target) return cs.login;
        }
        return {};
    };

    auto cluster_student_at = [&](int room, int idx) -> ClusterStudent {
        if (idx < 0) return {};
        std::string target = cluster_layout::host_of(room, cluster_layout::row_of(idx), cluster_layout::seat_of(idx));
        std::lock_guard<std::mutex> lk(state.mtx);
        for (const auto& cs : state.profile.cluster_students) {
            if (cluster_layout::normalize_host(cs.host) == target) return cs;
        }
        return {};
    };

    // Enqueue a fetch (and cache) of a student's full public profile.
    auto request_user_profile = [&](const std::string& login, const std::string& cdn_uri) {
        if (login.empty()) return;
        {
            std::lock_guard<std::mutex> lk(state.mtx);
            auto& entry = state.cluster_profiles[login];
            if (!entry.loaded) entry.loading = true;
            state.status_msg = "Cargando perfil de @" + login + "…";
        }
        if (!cdn_uri.empty() && !image_renderer::has_image(cdn_uri))
            worker.enqueue({ NetTaskKind::FetchImage, cdn_uri, "" });
        worker.enqueue({ NetTaskKind::FetchClusterProfile, login, "" });
    };

    // Open the full-screen profile modal for a cluster desk and load its data.
    auto open_user_profile = [&](int room, int idx) {
        ClusterStudent cs = cluster_student_at(room, idx);
        if (cs.login.empty()) return;
        user_modal_login = cs.login;
        user_modal_open  = true;
        request_user_profile(cs.login, cs.cdn_uri);
    };

    auto open_user_profile_by_login = [&](const std::string& login, const std::string& cdn) {
        if (login.empty()) return;
        user_modal_login = login;
        user_modal_open  = true;
        request_user_profile(login, cdn);
    };

    auto copy_cluster_login = [&](int idx) {
        std::string login = login_at_desk(cluster_room, idx);
        if (login.empty()) return;
        clipboard::copy(login);
        std::lock_guard<std::mutex> lk(state.mtx);
        state.status_msg = "Copied @" + login + " to clipboard";
    };

    // Name/slug of the currently selected roadmap project, or "".
    auto selected_project_name = [&]() -> std::string {
        std::lock_guard<std::mutex> lk(state.mtx);
        if (current_tab == Tab::Roadmap) {
            int idx = 0;
            for (const auto& ms : state.profile.roadmap) {
                if (idx == tree_sel) return {}; // milestone row
                idx++;
                if (ms.expanded) {
                    for (const auto& pr : ms.projects) {
                        if (idx == tree_sel)
                            return !pr.slug.empty() ? pr.slug : pr.name;
                        idx++;
                    }
                }
            }
        }
        return {};
    };

    // Theme Chooser Modal state
    bool theme_switcher_open = false;
    int  theme_sel           = theme::get_theme_index(Config::get().theme);
    std::string prev_theme   = Config::get().theme;

    // Subject preview / action menu state
    bool        subject_modal_open = false;
    int         subject_scroll     = 0;
    std::string preview_project;             // project whose PDF is currently previewed
    bool        action_menu_open   = false;
    int         action_menu_sel    = 0;
    std::string action_target;               // project name for the action menu
    std::vector<std::pair<std::string, bool>> action_items;

    // Esc (pause) menu state
    MenuState menu;
    Config    settings_saved;                // snapshot for dirty tracking / discard
    bool      quit_armed = false;
    std::chrono::steady_clock::time_point quit_armed_at;

    enum class ConfirmKind { None, Logout, DiscardSettings };
    ConfirmKind confirm_kind = ConfirmKind::None;
    int         edit_setting = -1;           // settings row currently being edited

    // Settings row indices
    enum {
        SET_THEME = 0, SET_BORDER, SET_OFFSET, SET_DURATION, SET_GLOW,
        SET_COOKIE, SET_START_TAB, SET_CONFIRM_QUIT, SET_LANGUAGE, SET_SAVE
    };
    // Root menu row indices
    enum {
        ROOT_RESUME = 0, ROOT_SETTINGS, ROOT_THEME, ROOT_HELP,
        ROOT_ABOUT, ROOT_LOGOUT, ROOT_QUIT
    };

    auto open_action_menu = [&](const std::string& name) {
        if (name.empty()) return;
        action_target = name;
        std::string pdf;
        bool has_pdf = pdf_preview::subject_pdf_path(name, pdf);
        action_items = {
            { "Abrir preview",  has_pdf },
            { "Abrir externo",  has_pdf },
            { "Descargar PDF", !has_pdf },
            { "Coming soon",    false   },
        };
        action_menu_sel  = has_pdf ? 0 : 2;
        action_menu_open = true;
    };

    // Activate a search result: users open their profile, projects open the
    // same context menu used elsewhere.
    auto run_search_result = [&](const SearchResult& r) {
        if (r.kind == SearchResult::Kind::User)
            open_user_profile_by_login(r.key, r.cdn);
        else
            open_action_menu(r.key);
    };

    // Rebuild the dynamic search results from the current snapshot (users
    // online + projects from recent submissions and the roadmap).
    auto rebuild_search_results = [&]() {
        search.results.clear();
        if (search.query.empty()) { search.sel = 0; return; }

        std::string q = search.query;
        for (auto& c : q) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        auto matches = [&](const std::string& s) {
            std::string t = s;
            for (auto& c : t) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            return t.find(q) != std::string::npos;
        };

        std::lock_guard<std::mutex> lk(state.mtx);
        const Profile& prof = state.profile;

        for (const auto& cs : prof.cluster_students) {
            if (search.results.size() >= 40) break;
            std::string name = cs.full_name;
            auto itp = state.cluster_profiles.find(cs.login);
            if (name.empty() && itp != state.cluster_profiles.end())
                name = itp->second.profile.display_name;
            if (!matches(cs.login) && !matches(name)) continue;

            SearchResult r;
            r.kind     = SearchResult::Kind::User;
            r.title    = name.empty() ? cs.login : (cs.login + " — " + name);
            r.subtitle = cs.host;
            r.key      = cs.login;
            r.cdn      = cs.cdn_uri;
            int room = -1, row = -1, seat = -1;
            if (parse_host_desk(cs.host, room, row, seat)) {
                r.room = room;
                r.desk = cluster_layout::index(row, seat);
            }
            search.results.push_back(std::move(r));
        }

        auto add_project = [&](const std::string& name, const std::string& slug,
                               const std::string& sub) {
            if (name.empty() || search.results.size() >= 40) return;
            if (!matches(name) && (slug.empty() || !matches(slug))) return;
            std::string key = !slug.empty() ? slug : name;
            for (const auto& e : search.results) {
                if (e.kind == SearchResult::Kind::Project && e.key == key) return;
            }
            SearchResult r;
            r.kind     = SearchResult::Kind::Project;
            r.title    = name;
            r.subtitle = sub;
            r.key      = key;
            search.results.push_back(std::move(r));
        };
        for (const auto& pr : prof.projects)
            add_project(pr.name, "", pr.grade.empty() ? pr.status : pr.grade);
        for (const auto& ms : prof.roadmap)
            for (const auto& pr : ms.projects)
                add_project(pr.name, pr.slug, pr.state);

        if (search.sel >= (int)search.results.size())
            search.sel = (int)search.results.size() - 1;
        if (search.sel < 0) search.sel = 0;
    };

    // Queue a preview load and mark the shared preview as loading immediately so
    // the UI reflects it even while the worker is busy with an initial sync.
    auto request_preview = [&](const std::string& pdf, int page) {
        {
            std::lock_guard<std::mutex> lk(state.mtx);
            state.preview          = SubjectPreview{};
            state.preview.path     = pdf;
            state.preview.page     = page;
            state.preview.loading  = true;
        }
        worker.enqueue({ NetTaskKind::LoadSubjectPreview, pdf, std::to_string(page) });
    };

    // Execute the action at index `idx` of the currently open action menu.
    // Shared by keyboard (Enter) and mouse selection so both paths stay in sync.
    auto run_action = [&](int idx) {
        if (idx < 0 || idx >= (int)action_items.size()) return;
        if (!action_items[idx].second) return;
        if (idx == 0) {
            std::string pdf;
            if (pdf_preview::subject_pdf_path(action_target, pdf)) {
                request_preview(pdf, 0);
                subject_modal_open = true;
                subject_scroll     = 0;
            }
        } else if (idx == 1) {
            std::string pdf;
            if (pdf_preview::subject_pdf_path(action_target, pdf)) {
                std::string cmd = "xdg-open '" + pdf + "' >/dev/null 2>&1 &";
                int rc = std::system(cmd.c_str());
                (void)rc;
                std::lock_guard<std::mutex> lk(state.mtx);
                state.status_msg = "Opening subject externally…";
            }
        } else if (idx == 2) {
            worker.enqueue({ NetTaskKind::DownloadSubject, action_target, "" });
        }
    };

    // Login state
    bool login_mode     = false;
    int  login_method   = 0; // 0: Credentials, 1: Cookie String, 2: Cookie File
    int  active_field   = 0; // 0: User, 1: Pass
    std::string user_buf;
    std::string pass_buf;
    std::string cookie_buf;
    std::string detected_file = network::find_available_cookie_file();

    // ── Esc menu helpers ──────────────────────────────────────────────────────
    const std::vector<std::string> kBorderStyles = { "rounded", "sharp", "double" };
    const std::vector<std::string> kTabCodes     = { "dashboard", "roadmap", "slots", "cluster" };
    const std::vector<std::string> kLangCodes    = { "en", "es" };

    auto refresh_dirty = [&]() {
        const Config& c = Config::get();
        menu.dirty = c.theme            != settings_saved.theme          ||
                     c.border_style     != settings_saved.border_style   ||
                     c.offset_minutes   != settings_saved.offset_minutes ||
                     c.default_duration != settings_saved.default_duration ||
                     c.enable_box_glow  != settings_saved.enable_box_glow ||
                     c.cookie_path      != settings_saved.cookie_path    ||
                     c.start_tab        != settings_saved.start_tab      ||
                     c.confirm_quit     != settings_saved.confirm_quit   ||
                     c.language         != settings_saved.language;
    };

    auto build_root_menu = [&]() {
        menu.root_items = {
            { i18n::tr("resume"),        "", "",  true, false, false },
            { i18n::tr("settings"),      "", "s", true, false, false },
            { i18n::tr("theme_chooser"), "", "t", true, false, false },
            { i18n::tr("help"),          "", "h", true, false, false },
            { i18n::tr("about"),         "", "a", true, false, false },
            { i18n::tr("logout"),        "", "l", true, false, false },
            { i18n::tr("quit"),          "", "q", true, false, false },
        };
    };

    auto build_settings_menu = [&]() {
        const Config& c = Config::get();
        const std::string border_label = i18n::tr("border_" + c.border_style);
        const std::string tab_label    = i18n::tr("tab_" + c.start_tab);
        const std::string lang_label   = (c.language == "es") ? i18n::tr("lang_es")
                                                              : i18n::tr("lang_en");
        menu.settings_items = {
            { i18n::tr("set_theme"),        theme::get_theme(c.theme).display_name, "", true, c.theme            != settings_saved.theme,          false },
            { i18n::tr("set_border"),       border_label,                          "", true, c.border_style     != settings_saved.border_style,   false },
            { i18n::tr("set_offset"),       std::to_string(c.offset_minutes),      "", true, c.offset_minutes   != settings_saved.offset_minutes, false },
            { i18n::tr("set_duration"),     std::to_string(c.default_duration),    "", true, c.default_duration != settings_saved.default_duration, false },
            { i18n::tr("set_glow"),         i18n::tr(c.enable_box_glow ? "on" : "off"), "", true, c.enable_box_glow != settings_saved.enable_box_glow, false },
            { i18n::tr("set_cookie"),       Config::get_effective_cookie_path(),   "", true, c.cookie_path      != settings_saved.cookie_path,    false },
            { i18n::tr("set_start_tab"),    tab_label,                             "", true, c.start_tab        != settings_saved.start_tab,      false },
            { i18n::tr("set_confirm_quit"), i18n::tr(c.confirm_quit ? "on" : "off"), "", true, c.confirm_quit   != settings_saved.confirm_quit,   false },
            { i18n::tr("set_language"),     lang_label,                            "", true, c.language         != settings_saved.language,       false },
            { i18n::tr("save"),             "", "s", true, false, true },
        };
    };

    auto open_menu = [&]() {
        menu.page         = MenuPage::Root;
        menu.sel          = ROOT_RESUME;
        menu.scroll       = 0;
        menu.dirty        = false;
        menu.confirm_open = false;
        menu.edit_open    = false;
    };

    auto open_settings = [&]() {
        settings_saved = Config::get();
        menu.page      = MenuPage::Settings;
        menu.sel       = SET_THEME;
        menu.scroll    = 0;
        menu.dirty     = false;
    };

    auto save_settings = [&]() {
        Config::get().save();
        settings_saved = Config::get();
        refresh_dirty();
        std::lock_guard<std::mutex> lk(state.mtx);
        state.status_msg = i18n::tr("msg_settings_saved");
    };

    auto discard_settings = [&]() {
        Config::get() = settings_saved;
        theme::apply_theme_to_ncurses(theme::get_theme(Config::get().theme));
        refresh_dirty();
        std::lock_guard<std::mutex> lk(state.mtx);
        state.status_msg = i18n::tr("msg_settings_discarded");
    };

    auto adjust_setting = [&](int idx, int dir) {
        Config& c = Config::get();
        switch (idx) {
            case SET_THEME: {
                const auto& all = theme::get_all_themes();
                int cur = theme::get_theme_index(c.theme);
                int nx  = (cur + dir) % (int)all.size();
                if (nx < 0) nx += (int)all.size();
                c.theme = all[nx].id;
                theme::apply_theme_to_ncurses(all[nx]);
                break;
            }
            case SET_BORDER:       c.border_style     = cycle_choice(kBorderStyles, c.border_style, dir); break;
            case SET_OFFSET:       c.offset_minutes   = std::clamp(c.offset_minutes + dir * 5, 0, 600); break;
            case SET_DURATION:     c.default_duration = std::clamp(c.default_duration + dir * 5, 5, 600); break;
            case SET_GLOW:         c.enable_box_glow  = !c.enable_box_glow; break;
            case SET_START_TAB:    c.start_tab        = cycle_choice(kTabCodes, c.start_tab, dir); break;
            case SET_CONFIRM_QUIT: c.confirm_quit     = !c.confirm_quit; break;
            case SET_LANGUAGE:     c.language         = cycle_choice(kLangCodes, c.language, dir); break;
            default: break;
        }
        refresh_dirty();
    };

    auto open_edit = [&](int idx) {
        Config& c = Config::get();
        if (idx == SET_OFFSET) {
            edit_setting   = idx;
            menu.edit_title = i18n::tr("set_offset");
            menu.edit_value = std::to_string(c.offset_minutes);
            menu.edit_open  = true;
        } else if (idx == SET_DURATION) {
            edit_setting   = idx;
            menu.edit_title = i18n::tr("set_duration");
            menu.edit_value = std::to_string(c.default_duration);
            menu.edit_open  = true;
        } else if (idx == SET_COOKIE) {
            edit_setting   = idx;
            menu.edit_title = i18n::tr("set_cookie");
            menu.edit_value = c.cookie_path;
            menu.edit_open  = true;
        }
    };

    auto commit_edit = [&]() {
        Config& c = Config::get();
        try {
            if (edit_setting == SET_OFFSET)
                c.offset_minutes = std::clamp(std::stoi(menu.edit_value), 0, 600);
            else if (edit_setting == SET_DURATION)
                c.default_duration = std::clamp(std::stoi(menu.edit_value), 5, 600);
            else if (edit_setting == SET_COOKIE)
                c.cookie_path = menu.edit_value;
        } catch (...) {}
        menu.edit_open = false;
        edit_setting   = -1;
        refresh_dirty();
    };

    auto try_quit = [&]() {
        if (!Config::get().confirm_quit) { g_quit.store(true); return; }
        auto now = std::chrono::steady_clock::now();
        if (quit_armed && (now - quit_armed_at) < std::chrono::seconds(3)) {
            g_quit.store(true);
        } else {
            quit_armed    = true;
            quit_armed_at = now;
            std::lock_guard<std::mutex> lk(state.mtx);
            state.status_msg = i18n::tr("msg_quit_armed");
        }
    };

    auto do_logout = [&]() {
        const std::string cookie = Config::get_effective_cookie_path();
        if (!cookie.empty()) std::remove(cookie.c_str());
        {
            std::lock_guard<std::mutex> lk(state.mtx);
            state.profile = Profile{};
            state.cluster_profiles.clear();
            state.preview = SubjectPreview{};
            state.data_ready = false;
            state.loading    = false;
            state.error_msg.clear();
            state.status_msg = i18n::tr("msg_logged_out");
        }
        login_mode = true;
        image_renderer::clear_kitty_images();
    };

    auto activate_root_menu = [&]() {
        switch (menu.sel) {
            case ROOT_RESUME:   menu.page = MenuPage::None; break;
            case ROOT_SETTINGS: open_settings(); break;
            case ROOT_THEME:
                theme_sel = theme::get_theme_index(Config::get().theme);
                prev_theme = Config::get().theme;
                theme_switcher_open = true;
                break;
            case ROOT_HELP:     menu.page = MenuPage::Help; menu.scroll = 0; break;
            case ROOT_ABOUT:    menu.page = MenuPage::About; break;
            case ROOT_LOGOUT:
                menu.confirm_open   = true;
                confirm_kind        = ConfirmKind::Logout;
                menu.confirm_title  = i18n::tr("logout_confirm_title");
                menu.confirm_msg    = i18n::tr("logout_confirm_msg");
                break;
            case ROOT_QUIT:     menu.page = MenuPage::None; try_quit(); break;
            default: break;
        }
    };

    // ── Session detection on startup ──────────────────────────────────────────
    // New behaviour: a cached session cookie + cached profile data lets us boot
    // straight into the dashboard and sync in the background. The login screen is
    // only shown when no session can be restored, or when the server explicitly
    // reports the session as expired.
    {
        std::string cookie = network::cookie_file_path();

        auto cookie_file_ready = [](const std::string& path) -> bool {
            struct stat st;
            return !path.empty() && stat(path.c_str(), &st) == 0 && st.st_size > 50;
        };

        Profile cached_profile;
        const bool have_cache = cache::load_profile(cached_profile);

        auto adopt_cache = [&]() {
            if (!have_cache) return;
            std::lock_guard<std::mutex> lk(state.mtx);
            state.profile    = cached_profile;
            state.data_ready = true;
        };

        if (cookie_file_ready(cookie)) {
            // Session present → skip the blocking validity probe entirely and
            // render cached data immediately; the worker refreshes asynchronously.
            adopt_cache();
            {
                std::lock_guard<std::mutex> lk(state.mtx);
                state.loading    = true;
                state.status_msg = have_cache ? "Offline data loaded — syncing…"
                                              : "Checking 42 session…";
            }
            worker.enqueue({ NetTaskKind::FetchProfile, "", "" });
        } else {
            // No default cookie: try any other cookie file on the machine first.
            std::string auto_err;
            if (!detected_file.empty() &&
                network::login_with_cookie(detected_file, cookie, auto_err) &&
                cookie_file_ready(cookie))
            {
                adopt_cache();
                std::lock_guard<std::mutex> lk(state.mtx);
                state.loading    = true;
                state.status_msg = "Restoring session…";
                worker.enqueue({ NetTaskKind::FetchProfile, "", "" });
            } else {
                if (!detected_file.empty()) {
                    login_method = 2;
                }
                login_mode = true;
                std::lock_guard<std::mutex> lk(state.mtx);
                state.status_msg = "Please connect to 42 intra";
            }
        }

        // Warm the in-memory image cache from disk so avatars render offline.
        cache::load_all_cached_images();

        // Restore any previously fetched cluster student profiles.
        std::unordered_map<std::string, Profile> cached_cluster_profiles;
        if (cache::load_all_cluster_profiles(cached_cluster_profiles) > 0) {
            std::lock_guard<std::mutex> lk(state.mtx);
            for (auto& kv : cached_cluster_profiles) {
                auto& entry   = state.cluster_profiles[kv.first];
                entry.profile = std::move(kv.second);
                entry.loaded  = true;
                entry.loading = false;
            }
        }
    }

    // ── Main event loop ───────────────────────────────────────────────────────
    while (!g_quit.load() && !state.quit.load()) {

        // Check if data is ready or if we need to switch out of login_mode
        {
            std::lock_guard<std::mutex> lk(state.mtx);
            if (state.data_ready && login_mode) {
                login_mode = false;
            } else if (!state.data_ready && !state.loading && !login_mode) {
                login_mode = true;
            }
        }

        if (current_tab != prev_tab) {
            image_renderer::clear_kitty_images();
            minimap_hover = -1;
            prev_tab = current_tab;
            if (current_tab == Tab::Cluster) {
                snap_cluster_selection();
                enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
            }
        }

        // ── Subject preview auto-load for the selected project ────────────────
        if (!login_mode) {
            std::string sel_proj;
            if (current_tab == Tab::Roadmap)
                sel_proj = selected_project_name();
            if (sel_proj != preview_project) {
                preview_project = sel_proj;
                subject_scroll  = 0;
                std::string pdf;
                if (!sel_proj.empty() && pdf_preview::subject_pdf_path(sel_proj, pdf)) {
                    request_preview(pdf, 0);
                } else {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    state.preview = SubjectPreview{};
                }
            }
        }

        SubjectPreview preview_snap;
        {
            std::lock_guard<std::mutex> lk(state.mtx);
            preview_snap = state.preview;
        }

        rebuild_search_results();
        bool preview_panel = !login_mode && !subject_modal_open &&
                             !action_menu_open && !theme_switcher_open &&
                             menu.page == MenuPage::None &&
                             (current_tab == Tab::Roadmap);

        // Refresh the menu contents (labels/values) right before drawing.
        if (menu.page != MenuPage::None) {
            build_root_menu();
            if (menu.page == MenuPage::Settings) build_settings_menu();
        }

        // Draw the current frame
        renderer.draw(state, current_tab,
                      slot_sel, tree_sel, cluster_sel,
                      login_mode, login_method, active_field,
                      user_buf, pass_buf, cookie_buf, detected_file,
                      theme_switcher_open, theme_sel,
                      dash_subview, dash_sel, dash_inspect,
                      cluster_room,
                      preview_panel, preview_snap,
                      subject_modal_open, subject_scroll,
                      action_menu_open, action_items, action_menu_sel,
                      minimap_hover,
                      user_modal_open, user_modal_login,
                      search, menu);

        int ch = getch();
        if (ch == ERR) continue;

        // Any key other than q disarms the pending quit confirmation.
        if (ch != 'q' && ch != 'Q') quit_armed = false;

        // Resize event
        if (ch == KEY_RESIZE) {
            image_renderer::clear_kitty_images();
            renderer.refresh_now();
            continue;
        }

        // ── Esc menu (pause menu) input handling ──────────────────────────────
        if (menu.page != MenuPage::None) {
            // Single-value edit popup
            if (menu.edit_open) {
                if (ch == 27) { menu.edit_open = false; edit_setting = -1; continue; }
                if (ch == '\n' || ch == KEY_ENTER) { commit_edit(); continue; }
                if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
                    if (!menu.edit_value.empty()) menu.edit_value.pop_back();
                    continue;
                }
                if (ch >= 32 && ch < 127) {
                    menu.edit_value += static_cast<char>(ch);
                }
                continue;
            }

            // Confirmation dialog
            if (menu.confirm_open) {
                if (ch == KEY_MOUSE) {
                    MEVENT ev;
                    if (getmouse(&ev) == OK &&
                        (ev.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_RELEASED))) {
                        MouseHit hit = renderer.hit_test(ev.y, ev.x);
                        if (hit.action == MouseAction::ConfirmChoice) {
                            ch = (hit.index == 0) ? 'y' : 'n';
                        }
                    } else {
                        continue;
                    }
                }
                if (ch == 'y' || ch == 'Y') {
                    ConfirmKind kind = confirm_kind;
                    menu.confirm_open = false;
                    confirm_kind      = ConfirmKind::None;
                    if (kind == ConfirmKind::Logout) {
                        menu.page = MenuPage::None;
                        do_logout();
                    } else if (kind == ConfirmKind::DiscardSettings) {
                        discard_settings();
                        menu.page = MenuPage::Root;
                    }
                    continue;
                }
                if (ch == 'n' || ch == 'N' || ch == 27 || ch == 'q' || ch == 'Q') {
                    menu.confirm_open = false;
                    confirm_kind      = ConfirmKind::None;
                    continue;
                }
                continue;
            }

            // Mouse (all menu pages)
            if (ch == KEY_MOUSE) {
                MEVENT ev;
                if (getmouse(&ev) == OK) {
                    if (ev.bstate & (BUTTON4_PRESSED | BUTTON4_CLICKED)) {
                        if (menu.page == MenuPage::Help)
                            menu.scroll = std::max(0, menu.scroll - 1);
                        else if (menu.sel > 0 && menu.page != MenuPage::About)
                            menu.sel--;
                    } else if (ev.bstate & (BUTTON5_PRESSED | BUTTON5_CLICKED)) {
                        if (menu.page == MenuPage::Help)
                            menu.scroll++;
                        else if (menu.page == MenuPage::Root &&
                                 menu.sel + 1 < (int)menu.root_items.size())
                            menu.sel++;
                        else if (menu.page == MenuPage::Settings &&
                                 menu.sel + 1 < (int)menu.settings_items.size())
                            menu.sel++;
                    } else if (ev.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_RELEASED)) {
                        MouseHit hit = renderer.hit_test(ev.y, ev.x);
                        if (hit.action == MouseAction::MenuItem &&
                            hit.index >= 0 && hit.index < (int)menu.root_items.size()) {
                            menu.sel = hit.index;
                            activate_root_menu();
                        } else if (hit.action == MouseAction::SettingsRow &&
                                   hit.index >= 0 && hit.index < (int)menu.settings_items.size()) {
                            menu.sel = hit.index;
                            if (menu.sel == SET_SAVE) save_settings();
                            else open_edit(menu.sel);
                        }
                    }
                }
                continue;
            }

            // Keyboard — Root
            if (menu.page == MenuPage::Root) {
                const int n = (int)menu.root_items.size();
                if (ch == 'j' || ch == KEY_DOWN) { menu.sel = (menu.sel + 1) % n; continue; }
                if (ch == 'k' || ch == KEY_UP)   { menu.sel = (menu.sel + n - 1) % n; continue; }
                if (ch == '\n' || ch == KEY_ENTER) { activate_root_menu(); continue; }
                if (ch == 27) { menu.page = MenuPage::None; continue; }
                switch (ch) {
                    case 's': case 'S': menu.sel = ROOT_SETTINGS;     activate_root_menu(); break;
                    case 't': case 'T': menu.sel = ROOT_THEME;        activate_root_menu(); break;
                    case 'h': case 'H': menu.sel = ROOT_HELP;         activate_root_menu(); break;
                    case 'a': case 'A': menu.sel = ROOT_ABOUT;        activate_root_menu(); break;
                    case 'l': case 'L': menu.sel = ROOT_LOGOUT;       activate_root_menu(); break;
                    case 'q': case 'Q': menu.sel = ROOT_QUIT;         activate_root_menu(); break;
                    default: break;
                }
                continue;
            }

            // Keyboard — Settings
            if (menu.page == MenuPage::Settings) {
                const int n = (int)menu.settings_items.size();
                if (ch == 'j' || ch == KEY_DOWN) { menu.sel = (menu.sel + 1) % n; continue; }
                if (ch == 'k' || ch == KEY_UP)   { menu.sel = (menu.sel + n - 1) % n; continue; }
                if (ch == 'h' || ch == KEY_LEFT)  { adjust_setting(menu.sel, -1); continue; }
                if (ch == 'l' || ch == KEY_RIGHT) { adjust_setting(menu.sel, +1); continue; }
                if (ch == 's' || ch == 'S') { save_settings(); continue; }
                if (ch == '\n' || ch == KEY_ENTER) {
                    if (menu.sel == SET_SAVE) save_settings();
                    else open_edit(menu.sel);
                    continue;
                }
                if (ch == 27) {
                    if (menu.dirty) {
                        menu.confirm_open  = true;
                        confirm_kind       = ConfirmKind::DiscardSettings;
                        menu.confirm_title = i18n::tr("discard_confirm_title");
                        menu.confirm_msg   = i18n::tr("discard_confirm_msg");
                    } else {
                        menu.page = MenuPage::Root;
                    }
                    continue;
                }
                continue;
            }

            // Keyboard — Help
            if (menu.page == MenuPage::Help) {
                if (ch == 'j' || ch == KEY_DOWN)  { menu.scroll++; continue; }
                if (ch == 'k' || ch == KEY_UP)    { menu.scroll = std::max(0, menu.scroll - 1); continue; }
                if (ch == KEY_NPAGE)              { menu.scroll += 10; continue; }
                if (ch == KEY_PPAGE)              { menu.scroll = std::max(0, menu.scroll - 10); continue; }
                if (ch == 27 || ch == '\n' || ch == KEY_ENTER) { menu.page = MenuPage::Root; continue; }
                continue;
            }

            // Keyboard — About
            if (menu.page == MenuPage::About) {
                if (ch == 27 || ch == '\n' || ch == KEY_ENTER) { menu.page = MenuPage::Root; continue; }
                continue;
            }
        }

        // ── Full-screen user profile modal ────────────────────────────────────
        if (user_modal_open) {
            if (ch == 27 || ch == 'q' || ch == 'Q' || ch == 'x' || ch == 'X') {
                user_modal_open = false;
                user_modal_login.clear();
            }
            continue;
        }

        // ── Theme Switcher Modal input handling ───────────────────────────────
        if (theme_switcher_open) {
            const auto& all_themes = theme::get_all_themes();
            const int total_th = static_cast<int>(all_themes.size());

            if (ch == KEY_MOUSE) {
                MEVENT ev;
                if (getmouse(&ev) == OK) {
                    if (ev.bstate & (BUTTON4_PRESSED | BUTTON4_CLICKED)) {
                        theme_sel = (theme_sel + total_th - 1) % total_th;
                        theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                    } else if (ev.bstate & (BUTTON5_PRESSED | BUTTON5_CLICKED)) {
                        theme_sel = (theme_sel + 1) % total_th;
                        theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                    } else {
                        MouseHit hit = renderer.hit_test(ev.y, ev.x);
                        if (hit.action == MouseAction::ThemeRow &&
                            hit.index >= 0 && hit.index < total_th) {
                            theme_sel = hit.index;
                            theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                        }
                    }
                }
                continue;
            }

            if (ch == 'j' || ch == KEY_DOWN) {
                theme_sel = (theme_sel + 1) % total_th;
                theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                continue;
            }
            if (ch == 'k' || ch == KEY_UP) {
                theme_sel = (theme_sel + total_th - 1) % total_th;
                theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                continue;
            }
            if (ch >= '1' && ch <= '9') {
                int direct_idx = ch - '1';
                if (direct_idx < total_th) {
                    theme_sel = direct_idx;
                    theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                }
                continue;
            }
            if (ch == '0' && total_th >= 10) {
                theme_sel = 9;
                theme::apply_theme_to_ncurses(all_themes[theme_sel]);
                continue;
            }
            if (ch == '\n' || ch == KEY_ENTER) {
                // Confirm and save theme
                auto chosen = all_themes[theme_sel];
                Config::get().theme = chosen.id;
                Config::get().save();
                theme::apply_theme_to_ncurses(chosen);
                {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    state.status_msg = "Theme set: " + chosen.display_name;
                }
                theme_switcher_open = false;
                continue;
            }
            if (ch == 27 || ch == 'q' || ch == 'Q' || ch == 't' || ch == 'T') {
                // Cancel and restore previous theme
                theme::apply_theme_to_ncurses(theme::get_theme(prev_theme));
                theme_switcher_open = false;
                continue;
            }
            continue;
        }

        // ── Project action menu ───────────────────────────────────────────────
        if (action_menu_open) {
            int n = (int)action_items.size();
            if (ch == KEY_MOUSE) {
                MEVENT ev;
                if (getmouse(&ev) == OK) {
                    if (ev.bstate & (BUTTON4_PRESSED | BUTTON4_CLICKED)) {
                        if (n) action_menu_sel = (action_menu_sel + n - 1) % n;
                    } else if (ev.bstate & (BUTTON5_PRESSED | BUTTON5_CLICKED)) {
                        if (n) action_menu_sel = (action_menu_sel + 1) % n;
                    } else if (ev.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_RELEASED)) {
                        MouseHit hit = renderer.hit_test(ev.y, ev.x);
                        if (hit.action == MouseAction::ActionRow &&
                            hit.index >= 0 && hit.index < n) {
                            action_menu_sel = hit.index;
                            if (action_items[hit.index].second) {
                                run_action(hit.index);
                                action_menu_open = false;
                            }
                        } else {
                            action_menu_open = false;
                        }
                    }
                }
                continue;
            }
            if (ch == 'j' || ch == KEY_DOWN) {
                if (n) action_menu_sel = (action_menu_sel + 1) % n;
                continue;
            }
            if (ch == 'k' || ch == KEY_UP) {
                if (n) action_menu_sel = (action_menu_sel + n - 1) % n;
                continue;
            }
            if (ch >= '1' && ch <= '4' && (ch - '1') < n) {
                action_menu_sel = ch - '1';
                continue;
            }
            if (ch == '\n' || ch == KEY_ENTER) {
                run_action(action_menu_sel);
                action_menu_open = false;
                continue;
            }
            if (ch == 27 || ch == 'q' || ch == 'Q') {
                action_menu_open = false;
                continue;
            }
            continue;
        }

        // ── Subject preview modal ─────────────────────────────────────────────
        if (subject_modal_open) {
            SubjectPreview pv;
            {
                std::lock_guard<std::mutex> lk(state.mtx);
                pv = state.preview;
            }
            if (ch == 27 || ch == 'q' || ch == 'Q') { subject_modal_open = false; continue; }
            if (ch == 'j' || ch == KEY_DOWN) { subject_scroll += 3; continue; }
            if (ch == 'k' || ch == KEY_UP) {
                subject_scroll = std::max(0, subject_scroll - 3);
                continue;
            }
            if (ch == 'n' || ch == KEY_RIGHT || ch == ']') {
                int np = pv.page + 1;
                if (pv.page_count > 0 && np >= pv.page_count) continue;
                if (!pv.path.empty())
                    request_preview(pv.path, np);
                subject_scroll = 0;
                continue;
            }
            if (ch == 'p' || ch == KEY_LEFT || ch == '[') {
                int np = pv.page - 1;
                if (np < 0) continue;
                if (!pv.path.empty())
                    request_preview(pv.path, np);
                subject_scroll = 0;
                continue;
            }
            continue;
        }

        // ── Global dynamic search input ───────────────────────────────────────
        if (search.focus) {
            if (ch == KEY_MOUSE) {
                MEVENT ev;
                if (getmouse(&ev) == OK) {
                    MouseHit hit = renderer.hit_test(ev.y, ev.x);
                    if (hit.action == MouseAction::SearchResult &&
                        hit.index >= 0 && hit.index < (int)search.results.size()) {
                        search.sel = hit.index;
                        run_search_result(search.results[hit.index]);
                        search.focus = false;
                        search.query.clear();
                        search.results.clear();
                    }
                }
                continue;
            }
            if (ch == 27) { // Esc: clear query first, then leave search
                if (!search.query.empty()) {
                    search.query.clear();
                    search.sel = 0;
                } else {
                    search.focus = false;
                }
                continue;
            }
            if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
                if (!search.query.empty()) search.query.pop_back();
                search.sel = 0;
                continue;
            }
            if (ch == KEY_UP)   { if (search.sel > 0) search.sel--; continue; }
            if (ch == KEY_DOWN) {
                if (search.sel + 1 < (int)search.results.size()) search.sel++;
                continue;
            }
            if (ch == '\n' || ch == KEY_ENTER) {
                if (search.sel >= 0 && search.sel < (int)search.results.size())
                    run_search_result(search.results[search.sel]);
                search.focus = false;
                search.query.clear();
                search.results.clear();
                continue;
            }
            if (ch >= 32 && ch < 127) {
                search.query += static_cast<char>(ch);
                search.sel = 0;
                continue;
            }
            continue; // swallow anything else while typing
        }

        // ── Login mode input handling ─────────────────────────────────────────
        if (login_mode) {
            // Clear error on new user input
            {
                std::lock_guard<std::mutex> lk(state.mtx);
                if (!state.error_msg.empty())
                    state.error_msg.clear();
            }

            if (ch == KEY_MOUSE) {
                MEVENT ev;
                if (getmouse(&ev) == OK) {
                    MouseHit hit = renderer.hit_test(ev.y, ev.x);
                    if (hit.action == MouseAction::LoginMethod &&
                        hit.index >= 0 && hit.index <= 2) {
                        login_method = hit.index;
                        active_field = 0;
                    } else if (hit.action == MouseAction::LoginField) {
                        if (login_method == 0 && (hit.index == 0 || hit.index == 1))
                            active_field = hit.index;
                        else
                            active_field = 0;
                    }
                }
                continue;
            }

            if (ch == 3 || ch == 27) { // Ctrl+C or Escape
                g_quit.store(true);
                break;
            }

            // Active field is empty? (used so typed digits inside a field are
            // treated as text, while empty fields still allow mode shortcuts)
            bool field_empty = false;
            if (login_method == 0)
                field_empty = (active_field == 0) ? user_buf.empty() : pass_buf.empty();
            else
                field_empty = cookie_buf.empty();

            // Method switching shortcuts: F1-F3 always switch, number keys only
            // while the active input field is empty.
            if (ch == KEY_F(1) || (ch == '1' && field_empty)) {
                login_method = 0; active_field = 0; continue;
            }
            if (ch == KEY_F(2) || (ch == '2' && field_empty)) {
                login_method = 1; active_field = 0; continue;
            }
            if (ch == KEY_F(3) || (ch == '3' && field_empty)) {
                login_method = 2; active_field = 0;
                continue;
            }

            // Tab / Down: next input field
            if (ch == '\t' || ch == KEY_DOWN) {
                if (login_method == 0) active_field = (active_field + 1) % 2;
                continue;
            }
            // Shift-Tab / Up: previous input field (2 fields → ±1 are equivalent)
            if (ch == KEY_BTAB || ch == KEY_UP) {
                if (login_method == 0) active_field = (active_field + 1) % 2;
                continue;
            }

            // Enter / Return: Submit or jump to next field
            if (ch == '\n' || ch == KEY_ENTER) {
                if (login_method == 0) {
                    if (active_field == 0 && !user_buf.empty() && pass_buf.empty()) {
                        active_field = 1;
                    } else if (!user_buf.empty() && !pass_buf.empty()) {
                        worker.enqueue({ NetTaskKind::Login, user_buf, pass_buf });
                        pass_buf.clear();
                    }
                } else if (login_method == 1) {
                    if (!cookie_buf.empty()) {
                        worker.enqueue({ NetTaskKind::CookieLogin, cookie_buf, "" });
                    }
                } else if (login_method == 2) {
                    std::string target = cookie_buf.empty() ? detected_file : cookie_buf;
                    if (!target.empty()) {
                        worker.enqueue({ NetTaskKind::CookieLogin, target, "" });
                    }
                }
                continue;
            }

            // Backspace handling
            if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
                if (login_method == 0) {
                    if (active_field == 0 && !user_buf.empty()) user_buf.pop_back();
                    else if (active_field == 1 && !pass_buf.empty()) pass_buf.pop_back();
                } else {
                    if (!cookie_buf.empty()) cookie_buf.pop_back();
                }
                continue;
            }

            // Printable characters
            if (ch >= 32 && ch < 127) {
                if (login_method == 0) {
                    if (active_field == 0) user_buf += static_cast<char>(ch);
                    else pass_buf += static_cast<char>(ch);
                } else {
                    cookie_buf += static_cast<char>(ch);
                }
            }
            continue;
        }

        // ── Normal navigation mode ────────────────────────────────────────────
        int slot_count = 0, tree_count = 0;
        {
            std::lock_guard<std::mutex> lk(state.mtx);
            slot_count    = static_cast<int>(state.profile.slots.size());
            for (const auto& ms : state.profile.roadmap) {
                tree_count++;
                if (ms.expanded) tree_count += static_cast<int>(ms.projects.size());
            }
        }

        // Shared vertical movement used by keyboard (j/k) and mouse wheel.
        auto move_vertical = [&](int dir) {
            if (current_tab == Tab::Dashboard) {
                if (dash_subview == 1) {
                    int fb_count = 0;
                    {
                        std::lock_guard<std::mutex> lk(state.mtx);
                        fb_count = (int)state.profile.feedbacks.size();
                    }
                    if (fb_count > 0)
                        dash_sel = std::clamp(dash_sel + dir, 0, fb_count - 1);
                }
            } else if (current_tab == Tab::Slots && slot_count > 0) {
                slot_sel = std::clamp(slot_sel + dir, 0, slot_count - 1);
            } else if (current_tab == Tab::Roadmap && tree_count > 0) {
                tree_sel = std::clamp(tree_sel + dir, 0, tree_count - 1);
            } else if (current_tab == Tab::Cluster) {
                std::vector<ClusterStudent> cs = cluster_snapshot();
                int next = cluster_layout::nearest_occupied(cs, cluster_room, cluster_sel, dir, 0);
                if (next != cluster_sel) {
                    cluster_sel = next;
                    image_renderer::clear_kitty_images();
                    enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
                }
            }
        };

        // ── Mouse input (normal navigation mode) ──────────────────────────────
        if (ch == KEY_MOUSE) {
            MEVENT ev;
            if (getmouse(&ev) == OK) {
                // Track the hovered dashboard minimap desk (motion + clicks).
                MouseHit hover_hit = renderer.hit_test(ev.y, ev.x);
                minimap_hover = (hover_hit.action == MouseAction::DashMinimap)
                                    ? hover_hit.index : -1;

                if (ev.bstate & (BUTTON4_PRESSED | BUTTON4_CLICKED)) {
                    move_vertical(-1);
                    continue;
                }
                if (ev.bstate & (BUTTON5_PRESSED | BUTTON5_CLICKED)) {
                    move_vertical(+1);
                    continue;
                }
                if (ev.bstate & (BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_RELEASED)) {
                    MouseHit hit = renderer.hit_test(ev.y, ev.x);
                    switch (hit.action) {
                    case MouseAction::TabBar:
                        if (hit.index >= 0 && hit.index < 4)
                            current_tab = static_cast<Tab>(hit.index);
                        break;
                    case MouseAction::DashSubview:
                        dash_subview = std::clamp(hit.index, 0, 2);
                        dash_sel = 0;
                        break;
                    case MouseAction::ListRow:
                        if (current_tab == Tab::Dashboard && dash_subview == 1)
                            dash_sel = hit.index;
                        else if (current_tab == Tab::Slots)
                            slot_sel = hit.index;
                        else if (current_tab == Tab::Roadmap)
                            tree_sel = hit.index;
                        break;
                    case MouseAction::ClusterRoom:
                        if (hit.index >= 0 && hit.index < 4) {
                            cluster_room = hit.index;
                            image_renderer::clear_kitty_images();
                            snap_cluster_selection();
                            enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
                        }
                        break;
                    case MouseAction::ClusterDesk:
                        if (hit.index >= 0 && hit.index < cluster_layout::CELLS) {
                            std::vector<ClusterStudent> cs = cluster_snapshot();
                            if (cluster_layout::occupied(cs, cluster_room,
                                    cluster_layout::row_of(hit.index),
                                    cluster_layout::seat_of(hit.index))) {
                                cluster_sel = hit.index;
                                image_renderer::clear_kitty_images();
                                enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
                            }
                        }
                        break;
                    case MouseAction::DashMinimap:
                        if (hit.index >= 0) {
                            int mroom = hit.index / cluster_layout::CELLS;
                            int mdesk = hit.index % cluster_layout::CELLS;
                            open_user_profile(mroom, mdesk);
                        }
                        break;
                    case MouseAction::SearchBar:
                        search.focus = true;
                        search.sel   = 0;
                        break;
                    case MouseAction::SearchResult:
                        if (hit.index >= 0 && hit.index < (int)search.results.size()) {
                            search.sel = hit.index;
                            run_search_result(search.results[hit.index]);
                            search.focus = false;
                            search.query.clear();
                            search.results.clear();
                        }
                        break;
                    default:
                        break;
                    }
                } else if (ev.bstate & (BUTTON3_PRESSED | BUTTON3_CLICKED)) {
                    MouseHit hit = renderer.hit_test(ev.y, ev.x);
                    if (hit.action == MouseAction::ClusterDesk && hit.index >= 0)
                        copy_cluster_login(hit.index);
                }
            }
            continue;
        }

        switch (ch) {

        // ── Quit ──────────────────────────────────────────────────────────────
        case 'q':
        case 'Q':
            if (dash_inspect) {
                dash_inspect = false;
                break;
            }
            try_quit();
            break;

        case 27: // Escape
            if (dash_inspect) {
                dash_inspect = false;
                break;
            }
            open_menu();
            break;

        case 'f':
        case 'F':
            if (current_tab == Tab::Dashboard) {
                dash_inspect = !dash_inspect;
                break;
            }
            break;

        case '[':
            if (current_tab == Tab::Dashboard) {
                dash_subview = (dash_subview + 2) % 3;
                dash_sel = 0;
            } else if (current_tab == Tab::Cluster) {
                cluster_room = (cluster_room + 3) % 4;
                image_renderer::clear_kitty_images();
                snap_cluster_selection();
                enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
            }
            break;

        case ']':
            if (current_tab == Tab::Dashboard) {
                dash_subview = (dash_subview + 1) % 3;
                dash_sel = 0;
            } else if (current_tab == Tab::Cluster) {
                cluster_room = (cluster_room + 1) % 4;
                image_renderer::clear_kitty_images();
                snap_cluster_selection();
                enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
            }
            break;

        case 'c':
        case 'C':
            if (current_tab == Tab::Cluster) {
                cluster_room = (cluster_room + 1) % 4;
                image_renderer::clear_kitty_images();
                snap_cluster_selection();
                enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
            }
            break;

        // ── Copy selected cluster user's login ────────────────────────────────
        case 'y':
        case 'Y':
            if (current_tab == Tab::Cluster && cluster_sel >= 0)
                copy_cluster_login(cluster_sel);
            break;

        // ── Theme Switcher ────────────────────────────────────────────────────
        case 't':
        case 'T':
            theme_switcher_open = true;
            theme_sel = theme::get_theme_index(Config::get().theme);
            prev_theme = Config::get().theme;
            break;

        // ── Vim movement ──────────────────────────────────────────────────────
        case 'j': case KEY_DOWN:
            move_vertical(+1);
            break;

        case 'k': case KEY_UP:
            move_vertical(-1);
            break;

        case 'h': case KEY_LEFT:
            if (current_tab == Tab::Cluster) {
                std::vector<ClusterStudent> cs = cluster_snapshot();
                int next = cluster_layout::nearest_occupied(cs, cluster_room, cluster_sel, 0, -1);
                if (next != cluster_sel) {
                    cluster_sel = next;
                    image_renderer::clear_kitty_images();
                    enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
                }
            } else if (current_tab != Tab::Dashboard) {
                current_tab = static_cast<Tab>(static_cast<int>(current_tab) - 1);
            }
            break;

        case 'l': case KEY_RIGHT:
            if (current_tab == Tab::Cluster) {
                std::vector<ClusterStudent> cs = cluster_snapshot();
                int next = cluster_layout::nearest_occupied(cs, cluster_room, cluster_sel, 0, +1);
                if (next != cluster_sel) {
                    cluster_sel = next;
                    image_renderer::clear_kitty_images();
                    enqueue_cluster_image_if_needed(cluster_room, cluster_sel);
                }
            } else if (current_tab != Tab::Cluster) {
                current_tab = static_cast<Tab>(static_cast<int>(current_tab) + 1);
            }
            break;

        // ── Tab switching ─────────────────────────────────────────────────────
        case '\t':
            current_tab = static_cast<Tab>((static_cast<int>(current_tab) + 1) % 4);
            break;

        case 'g':
        {
            int next = getch();
            if (next == 't') current_tab = static_cast<Tab>((static_cast<int>(current_tab) + 1) % 4);
            else if (next == 'T') current_tab = static_cast<Tab>((static_cast<int>(current_tab) + 3) % 4);
            break;
        }

        case KEY_BTAB:
            current_tab = static_cast<Tab>((static_cast<int>(current_tab) + 3) % 4);
            break;

        case '1': current_tab = Tab::Dashboard; break;
        case '2': current_tab = Tab::Roadmap;   break;
        case '3': current_tab = Tab::Slots;     break;
        case '4': current_tab = Tab::Cluster;   break;

        // ── Global search focus ────────────────────────────────────────────────
        case '/':
            search.focus = true;
            search.sel   = 0;
            break;

        // ── Refresh data ──────────────────────────────────────────────────────
        case 'r': case 'R':
        {
            bool loading = false;
            {
                std::lock_guard<std::mutex> lk(state.mtx);
                loading = state.loading;
                state.error_msg.clear();
            }
            if (!loading)
                worker.enqueue({ NetTaskKind::FetchProfile, "", "" });
            break;
        }

        // ── Toggle Roadmap / Download in Projects or Roadmap ─────────────────
        case ' ': case '\n': case KEY_ENTER:
        {
            if (current_tab == Tab::Dashboard) {
                dash_inspect = !dash_inspect;
                break;
            }

            if (current_tab == Tab::Cluster) {
                if (cluster_sel >= 0)
                    open_user_profile(cluster_room, cluster_sel);
                break;
            }

            if (current_tab == Tab::Roadmap) {
                bool is_project = false;
                std::string proj_name;
                {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    int cur_idx = 0;
                    for (size_t m = 0; m < state.profile.roadmap.size() && !is_project; ++m) {
                        if (cur_idx == tree_sel) {
                            state.profile.roadmap[m].expanded = !state.profile.roadmap[m].expanded;
                            break;
                        }
                        cur_idx++;
                        if (state.profile.roadmap[m].expanded) {
                            for (size_t p = 0; p < state.profile.roadmap[m].projects.size(); ++p) {
                                if (cur_idx == tree_sel) {
                                    const auto& pr = state.profile.roadmap[m].projects[p];
                                    proj_name  = !pr.slug.empty() ? pr.slug : pr.name;
                                    is_project = true;
                                    break;
                                }
                                cur_idx++;
                            }
                        }
                    }
                }
                if (is_project) open_action_menu(proj_name);
                break;
            }

            break;
        }

        // ── 'p': open the downloaded subject preview ──────────────────────────
        case 'p':
        case 'P':
        {
            if (current_tab == Tab::Roadmap) {
                std::string name = selected_project_name();
                std::string pdf;
                if (!name.empty() && pdf_preview::subject_pdf_path(name, pdf)) {
                    request_preview(pdf, 0);
                    subject_modal_open = true;
                    subject_scroll = 0;
                } else {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    state.status_msg = "No downloaded subject for this project";
                }
            }
            break;
        }

        // ── 'd': Trim -15m in Slots / Download subject in Projects & Roadmap ──
        case 'd':
        {
            if (current_tab == Tab::Slots && slot_count > 0 && slot_sel >= 0 && slot_sel < slot_count) {
                Slot s;
                {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    s = state.profile.slots[slot_sel];
                }
                std::string sub_ids = !s.ids.empty() ? s.ids : s.id;
                worker.enqueue({ NetTaskKind::TrimSlot15m, s.id, sub_ids, s.begin_at, s.end_at });
            } else if (current_tab == Tab::Roadmap) {
                std::lock_guard<std::mutex> lk(state.mtx);
                int cur_idx = 0;
                for (size_t m = 0; m < state.profile.roadmap.size(); ++m) {
                    if (cur_idx == tree_sel) {
                        state.profile.roadmap[m].expanded = !state.profile.roadmap[m].expanded;
                        break;
                    }
                    cur_idx++;
                    if (state.profile.roadmap[m].expanded) {
                        bool found = false;
                        for (size_t p = 0; p < state.profile.roadmap[m].projects.size(); ++p) {
                            if (cur_idx == tree_sel) {
                                const auto& pr = state.profile.roadmap[m].projects[p];
                                std::string target = !pr.slug.empty() ? pr.slug : pr.name;
                                worker.enqueue({ NetTaskKind::DownloadSubject, target, "" });
                                found = true;
                                break;
                            }
                            cur_idx++;
                        }
                        if (found) break;
                    }
                }
            }
            break;
        }

        // ── 'D' / 'x': Delete entire slot block ──────────────────────────────
        case 'D': case 'x': case 'X':
        {
            if (current_tab == Tab::Slots && slot_count > 0 && slot_sel >= 0 && slot_sel < slot_count) {
                std::string target_id;
                {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    const auto& s = state.profile.slots[slot_sel];
                    target_id = !s.ids.empty() ? s.ids : s.id;
                }
                if (!target_id.empty()) {
                    worker.enqueue({ NetTaskKind::DeleteSlot, target_id, "" });
                    if (slot_sel > 0 && slot_sel == slot_count - 1)
                        slot_sel--;
                }
            }
            break;
        }

        // ── 's': Add slot (Slots/Dashboard) or Download Subject (Roadmap)
        case 's': case 'S':
        {
            if (current_tab == Tab::Roadmap) {
                std::lock_guard<std::mutex> lk(state.mtx);
                int cur_idx = 0;
                for (size_t m = 0; m < state.profile.roadmap.size(); ++m) {
                    if (cur_idx == tree_sel) {
                        state.profile.roadmap[m].expanded = !state.profile.roadmap[m].expanded;
                        break;
                    }
                    cur_idx++;
                    if (state.profile.roadmap[m].expanded) {
                        bool found = false;
                        for (size_t p = 0; p < state.profile.roadmap[m].projects.size(); ++p) {
                            if (cur_idx == tree_sel) {
                                const auto& pr = state.profile.roadmap[m].projects[p];
                                std::string target = !pr.slug.empty() ? pr.slug : pr.name;
                                worker.enqueue({ NetTaskKind::DownloadSubject, target, "" });
                                found = true;
                                break;
                            }
                            cur_idx++;
                        }
                        if (found) break;
                    }
                }
            } else {
                bool pending = false;
                {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    pending = state.slot_pending;
                    state.error_msg.clear();
                }
                if (pending) break;

                int offset   = Config::get().offset_minutes;
                int duration = Config::get().default_duration;

                {
                    std::lock_guard<std::mutex> lk(state.mtx);
                    state.slot_pending = true;
                    state.status_msg = "Finding next non-overlapping slot...";
                }
                worker.enqueue({ NetTaskKind::CreateSlot, std::to_string(offset), std::to_string(duration) });
                current_tab = Tab::Slots;
            }
            break;
        }

        default:
            break;
        }
    }

    image_renderer::clear_kitty_images();
    worker.stop();
    network::global_cleanup();
    return 0;
}
