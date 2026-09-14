#include "renderer.hpp"
#include "types.hpp"
#include "theme.hpp"
#include "config.hpp"
#include "image_renderer.hpp"
#include "network.hpp"
#include "i18n.hpp"
#include "version.hpp"

#include <ncurses.h>
#include <curl/curl.h>
#include <clocale>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <mutex>

// ─────────────────────────────────────────────────────────────────────────────
// Color pair indices
// ─────────────────────────────────────────────────────────────────────────────
enum ColorPair {
    CP_DEFAULT      = 1,
    CP_TAB_ACTIVE   = 2,
    CP_TAB_IDLE     = 3,
    CP_ROW_SEL      = 4,
    CP_STATUS_L     = 5,
    CP_STATUS_C     = 6,
    CP_STATUS_R     = 7,
    CP_BORDER       = 8,
    CP_LABEL        = 9,
    CP_VALUE        = 10,
    CP_SUCCESS      = 11,
    CP_FAIL         = 12,
    CP_DIM          = 13,
    CP_WARN         = 14,
    CP_TITLE        = 15,
    CP_MODAL_BG     = 16,
    CP_PROGRESS     = 17,
    CP_HEADER_ROW   = 18,
    CP_IN_PROG      = 19,
    CP_BADGE_PASS   = 20,
    CP_BADGE_FAIL   = 21,
    CP_ACCENT       = 22,
    // Filled pill badges: dark text on a saturated background.
    CP_PILL_SUCCESS = 23,
    CP_PILL_WARN    = 24,
    CP_PILL_FAIL    = 25,
    CP_PILL_ACCENT  = 26,
};

// ─────────────────────────────────────────────────────────────────────────────
// Border Style Definitions
// ─────────────────────────────────────────────────────────────────────────────
struct BorderChars {
    const char* h;
    const char* v;
    const char* tl;
    const char* tr;
    const char* bl;
    const char* br;
    const char* t_left;
    const char* t_right;
    const char* t_up;
    const char* t_down;
    const char* cross;
};

static const BorderChars& get_border_chars() {
    static const BorderChars rounded = { "─", "│", "╭", "╮", "╰", "╯", "├", "┤", "┬", "┴", "┼" };
    static const BorderChars sharp   = { "─", "│", "┌", "┐", "└", "┘", "├", "┤", "┬", "┴", "┼" };
    static const BorderChars dbl     = { "═", "║", "╔", "╗", "╚", "╝", "╠", "╣", "╦", "╩", "╬" };

    const std::string& style = Config::get().border_style;
    if (style == "sharp") return sharp;
    if (style == "double") return dbl;
    return rounded;
}

// ─────────────────────────────────────────────────────────────────────────────
// Constructor & Destructor
// ─────────────────────────────────────────────────────────────────────────────
Renderer::Renderer() {
    std::setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(80);
    set_escdelay(25);   // low-latency Esc (search → modal → menu layering)

    // Enable mouse reporting (clicks, scroll wheel + motion for hover).
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
    mouseinterval(0);

    if (has_colors()) {
        start_color();
        use_default_colors();
        const auto& pal = theme::get_theme(Config::get().theme);
        theme::apply_theme_to_ncurses(pal);
    }

    getmaxyx(stdscr, rows_, cols_);
}

Renderer::~Renderer() {
    endwin();
}

int Renderer::terminal_cols() const { return cols_; }
int Renderer::terminal_rows() const { return rows_; }
void Renderer::refresh_now() { doupdate(); }

MouseHit Renderer::hit_test(int y, int x) const {
    // Reverse order so overlays (e.g. theme modal) win over the base screen.
    for (auto it = hitboxes_.rbegin(); it != hitboxes_.rend(); ++it) {
        if (y >= it->y && y < it->y + it->h &&
            x >= it->x && x < it->x + it->w)
        {
            return {it->action, it->index};
        }
    }
    return {};
}

// ─────────────────────────────────────────────────────────────────────────────
// Helpers
// ─────────────────────────────────────────────────────────────────────────────

static void mvprint_clip(int row, int col, const std::string& s, int max_w) {
    if (max_w <= 0) return;
    std::string out = s;
    if ((int)out.size() > max_w) {
        size_t cut = static_cast<size_t>(max_w > 1 ? max_w - 1 : 1);
        while (cut > 0 && (static_cast<unsigned char>(out[cut]) & 0xC0) == 0x80) {
            cut--;
        }
        out = out.substr(0, cut) + "…";
    }
    mvprintw(row, col, "%s", out.c_str());
}

static void fill_row(int row, int col, int width) {
    for (int i = 0; i < width; ++i) mvaddch(row, col + i, ' ');
}

static void hline_box(int row, int col, int width) {
    const auto& bc = get_border_chars();
    for (int i = 0; i < width; ++i) mvaddstr(row, col + i, bc.h);
}

static std::string pad(const std::string& s, int w) {
    if ((int)s.size() >= w) return s.substr(0, w);
    return s + std::string(w - s.size(), ' ');
}

// Draw a filled "pill" badge: ` text ` with a dark-on-colour background pair.
static void draw_pill(int row, int x, const std::string& text, int cp) {
    std::string s = " " + text + " ";
    attron(COLOR_PAIR(cp) | A_BOLD);
    mvaddstr(row, x, s.c_str());
    attroff(COLOR_PAIR(cp) | A_BOLD);
}

// Defined later in the file; used by the slot-manager overlays below.
static void draw_modal_frame(int by, int bx, int box_h, int box_w, const std::string& title);

static std::string normalize_host(const std::string& h) {
    std::string clean;
    clean.reserve(h.size());
    for (char ch : h) {
        if (ch != '-' && ch != '_' && ch != ' ') {
            clean.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
    }
    return clean;
}

static const ClusterStudent* get_student_at_desk(const std::vector<ClusterStudent>& students, int room, int r, int s) {
    std::string target = "c" + std::to_string(room + 1) + "r" + std::to_string(r + 1) + "s" + std::to_string(s + 1);
    for (const auto& cs : students) {
        if (normalize_host(cs.host) == target) {
            return &cs;
        }
    }
    return nullptr;
}

static int count_students_in_room(const std::vector<ClusterStudent>& students, int room) {
    int count = 0;
    std::string prefix = "c" + std::to_string(room + 1);
    for (const auto& cs : students) {
        if (normalize_host(cs.host).rfind(prefix, 0) == 0) {
            count++;
        }
    }
    return count;
}

// Room index (0-3) encoded in a profile location such as "c3r1s2"; -1 if the
// location is unavailable or uses a non-cluster format (e.g. piscine "e1r1p1").
static int room_from_location(const std::string& loc) {
    std::string clean = normalize_host(loc);
    if (clean.size() < 3 || clean[0] != 'c') return -1;
    size_t i = 1;
    if (!std::isdigit(static_cast<unsigned char>(clean[i]))) return -1;
    int room = 0;
    while (i < clean.size() && std::isdigit(static_cast<unsigned char>(clean[i]))) {
        room = room * 10 + (clean[i] - '0');
        ++i;
    }
    if (i >= clean.size() || clean[i] != 'r') return -1;
    return room - 1;
}

static int busiest_room(const std::vector<ClusterStudent>& students) {
    int best = 0, best_count = -1;
    for (int r = 0; r < 4; ++r) {
        int c = count_students_in_room(students, r);
        if (c > best_count) { best_count = c; best = r; }
    }
    return best;
}

// "LUN 14 SEP" style label from an ISO 8601 date (best effort).
static std::string slot_day_label(const std::string& iso) {
    if (iso.size() < 10) return iso;
    int y = std::atoi(iso.substr(0, 4).c_str());
    int m = std::atoi(iso.substr(5, 2).c_str());
    int d = std::atoi(iso.substr(8, 2).c_str());
    if (m < 1 || m > 12) return iso.substr(0, 10);
    std::tm tm{};
    tm.tm_year = y - 1900;
    tm.tm_mon  = m - 1;
    tm.tm_mday = d;
    std::mktime(&tm);
    static const char* wd[] = { "DOM", "LUN", "MAR", "MIE", "JUE", "VIE", "SAB" };
    static const char* mo[] = { "ENE", "FEB", "MAR", "ABR", "MAY", "JUN",
                                "JUL", "AGO", "SEP", "OCT", "NOV", "DIC" };
    return std::string(wd[tm.tm_wday]) + " " + std::to_string(d) + " " + mo[m - 1];
}

// Compact human duration between two ISO timestamps (e.g. "30 min", "1h 15m").
static std::string slot_duration_label(const std::string& begin, const std::string& end) {
    if (begin.size() < 16 || end.size() < 16) return "";
    int bh = std::atoi(begin.substr(11, 2).c_str());
    int bm = std::atoi(begin.substr(14, 2).c_str());
    int eh = std::atoi(end.substr(11, 2).c_str());
    int em = std::atoi(end.substr(14, 2).c_str());
    int mins = (eh * 60 + em) - (bh * 60 + bm);
    if (mins <= 0) return "";
    if (mins % 60 == 0) return std::to_string(mins / 60) + "h";
    if (mins > 60) return std::to_string(mins / 60) + "h " + std::to_string(mins % 60) + "m";
    return std::to_string(mins) + " min";
}

// Numeric duration in minutes between two ISO timestamps (0 if malformed).
static int slot_duration_minutes(const std::string& begin, const std::string& end) {
    if (begin.size() < 16 || end.size() < 16) return 0;
    int bh = std::atoi(begin.substr(11, 2).c_str());
    int bm = std::atoi(begin.substr(14, 2).c_str());
    int eh = std::atoi(end.substr(11, 2).c_str());
    int em = std::atoi(end.substr(14, 2).c_str());
    int mins = (eh * 60 + em) - (bh * 60 + bm);
    return mins > 0 ? mins : 0;
}

// "2h 30m" style compact total from a raw minute count.
static std::string minutes_label(int mins) {
    if (mins <= 0) return "0m";
    if (mins % 60 == 0) return std::to_string(mins / 60) + "h";
    if (mins > 60) return std::to_string(mins / 60) + "h " + std::to_string(mins % 60) + "m";
    return std::to_string(mins) + "m";
}

// Rows reserved for the dashboard minimap panel (border + 8 grid rows + border).
// Only granted when the student card keeps a usable minimum height.
static int reserve_map_rows(int top, int bottom) {
    const int map_rows = 13;
    const int min_card = 12;
    if (bottom - top >= map_rows + min_card) return map_rows;
    return 0;
}

// Shared geometry for the cluster "LIVE WORKSTATION INSPECTOR" photo frame so
// both the frame (draw_cluster) and the image (draw) agree and stay on screen.
struct ClusterPhotoBox {
    int  pfx     = 0;
    int  pfy     = 0;
    int  pfw     = 0;
    int  pfh     = 0;
    bool visible = false;
};

static ClusterPhotoBox cluster_photo_box(int rx, int rw, int drow, int card_h) {
    ClusterPhotoBox b;
    b.pfx = rx + 4;
    b.pfy = drow + 1;

    const int text_min = 32;                       // reserve room for inspector text
    const int max_w    = rw - (b.pfx - rx) - text_min - 2;
    b.pfw = std::clamp(max_w, 8, 18);
    b.pfh = std::min(8, card_h - 2);
    b.visible = (b.pfw >= 10 && b.pfh >= 5);
    return b;
}

static int compute_left_panel_w(int cols) {
    if (cols < 50) return std::max(14, cols / 3);
    int lw = std::clamp(cols * 28 / 100, 22, 38);
    if (cols - lw < 26) lw = std::max(18, cols - 26);
    return lw;
}

static std::string format_active_since(const std::string& begin_at) {
    if (begin_at.empty()) return "—";
    time_t t = network::parse_iso8601(begin_at);
    if (t <= 0) {
        if (begin_at.size() >= 16) {
            return begin_at.substr(0, 10) + " " + begin_at.substr(11, 5);
        }
        return begin_at;
    }

    struct tm lt{};
    localtime_r(&t, &lt);
    char time_buf[32];
    std::strftime(time_buf, sizeof(time_buf), "%H:%M", &lt);

    time_t now = std::time(nullptr);
    double diff = std::difftime(now, t);
    if (diff < 0) {
        return std::string(time_buf) + " (just now)";
    }

    long diff_sec = static_cast<long>(diff);
    long hours = diff_sec / 3600;
    long mins  = (diff_sec % 3600) / 60;

    if (hours >= 24) {
        long days = hours / 24;
        hours = hours % 24;
        return std::string(time_buf) + " (" + std::to_string(days) + "d " + std::to_string(hours) + "h ago)";
    } else if (hours > 0) {
        return std::string(time_buf) + " (" + std::to_string(hours) + "h " + std::to_string(mins) + "m ago)";
    } else {
        return std::string(time_buf) + " (" + std::to_string(mins) + "m ago)";
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Top-level Draw
// ─────────────────────────────────────────────────────────────────────────────

void Renderer::draw(SharedState& state, Tab current_tab,
                    int slot_sel, int tree_sel, int cluster_sel,
                    bool login_mode, int login_method, int active_field,
                    const std::string& login_buf, const std::string& pass_buf,
                    const std::string& cookie_buf, const std::string& detected_file,
                    bool theme_switcher_open, int theme_sel,
                    bool dash_inspect, int dash_scroll, int minimap_room,
                    int cluster_room,
                    bool preview_panel,
                    const SubjectPreview& preview,
                    bool subject_modal,
                    int subject_scroll,
                    bool action_menu_open,
                    const std::vector<std::pair<std::string, bool>>& action_items,
                    int action_sel,
                    int minimap_hover,
                    int slot_hover,
                    int slot_btn_hover,
                    const SlotUiState& slot_ui,
                    bool user_modal_open,
                    const std::string& user_modal_login,
                    const SearchState& search,
                    MenuState& menu)
{
    getmaxyx(stdscr, rows_, cols_);
    erase();
    hitboxes_.clear();
    preview_img_ = ImageBox{};
    minimap_hover_ = minimap_hover;
    minimap_hover_box_ = MinimapBox{};
    user_modal_avatar_box_ = ImageBox{};
    user_modal_avatar_key_.clear();

    // Not enough room to lay out anything meaningful — tell the user instead of
    // rendering a crushed interface.
    if (rows_ < 15 || cols_ < 40) {
        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvprint_clip(rows_ / 2, 0, "  Terminal too small — resize to at least 40 columns × 15 rows", cols_);
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
        refresh();
        return;
    }

    Profile     prof;
    std::string status_msg;
    std::string error_msg;
    bool        loading      = false;
    bool        data_ready   = false;
    std::unordered_map<std::string, ClusterProfileEntry> cluster_profiles;
    {
        std::lock_guard<std::mutex> lk(state.mtx);
        prof             = state.profile;
        status_msg       = state.status_msg;
        error_msg        = state.error_msg;
        loading          = state.loading;
        data_ready       = state.data_ready;
        cluster_profiles = state.cluster_profiles;
    }

    int content_top    = 3;
    int content_bottom = rows_ - 2;
    int left_w         = compute_left_panel_w(cols_);

    if (login_mode || (!data_ready && !loading)) {
        draw_login_prompt(login_method, active_field,
                          login_buf, pass_buf, cookie_buf, detected_file,
                          error_msg, loading, status_msg);
    } else {
        draw_tab_bar(current_tab, loading);
        draw_search_bar(search, 1);

        switch (current_tab) {
            case Tab::Dashboard:
                draw_dashboard(prof, dash_inspect, dash_scroll, minimap_room,
                               content_top, content_bottom, left_w);
                break;
            case Tab::Slots:
                draw_slots(prof, slot_sel, slot_hover, slot_btn_hover,
                           content_top, content_bottom, left_w);
                break;
            case Tab::Roadmap:
                draw_roadmap(prof, tree_sel, content_top, content_bottom, left_w,
                             preview_panel, preview);
                break;
            case Tab::Cluster:
                draw_cluster(prof, cluster_room, cluster_sel, content_top, content_bottom, left_w);
                break;
        }

        draw_status_bar(prof.login, status_msg, error_msg, current_tab);
        draw_search_results(search, content_top, content_bottom);
    }

    // Floating cluster inspector for the hovered dashboard minimap desk.
    if (!login_mode && data_ready && current_tab == Tab::Dashboard &&
        !theme_switcher_open && !subject_modal && !action_menu_open && !user_modal_open &&
        menu.page == MenuPage::None &&
        !search.focus &&
        minimap_hover_ >= 0 && minimap_hover_box_.valid) {
        draw_cluster_tooltip(prof, cluster_profiles, content_top, content_bottom, left_w);
    }

    if (theme_switcher_open) {
        curs_set(0);
        draw_theme_switcher(theme_sel);
    }

    if (subject_modal) {
        curs_set(0);
        preview_img_ = draw_subject_modal(preview, subject_scroll);
    }

    if (action_menu_open && !action_items.empty()) {
        curs_set(0);
        draw_action_menu(action_items, action_sel);
    }

    if (!login_mode && user_modal_open && !user_modal_login.empty()) {
        curs_set(0);
        draw_user_modal(prof, cluster_profiles, user_modal_login);
    }

    // Slot manager overlays: context menu first, then the free-space picker on top.
    if (!login_mode && data_ready && current_tab == Tab::Slots &&
        !theme_switcher_open && !subject_modal && !action_menu_open && !user_modal_open &&
        menu.page == MenuPage::None && !search.focus) {
        if (slot_ui.ctx_open) {
            curs_set(0);
            draw_slot_context_menu(slot_ui);
        }
        if (slot_ui.gap_picker_open) {
            curs_set(0);
            draw_gap_picker(slot_ui.gap_minutes);
        }
    }

    // Esc menu (drawn above the base screen; theme chooser wins if both are up).
    if (!login_mode && menu.page != MenuPage::None && !theme_switcher_open) {
        curs_set(0);
        switch (menu.page) {
            case MenuPage::Root:     draw_main_menu(menu); break;
            case MenuPage::Settings: draw_settings(menu);  break;
            case MenuPage::Help:     draw_help(menu);      break;
            case MenuPage::About:    draw_about();         break;
            case MenuPage::None:     break;
        }
        if (menu.confirm_open) draw_confirm_dialog(menu);
        if (menu.edit_open)    draw_edit_popup(menu);
    }

    refresh();

    // Render photos after ncurses refresh(). Kitty graphics persist on the
    // terminal independently of ncurses, so whenever the set or placement of
    // images changes we must delete the previous ones or stale pictures would
    // stay painted on screen (e.g. after closing the preview modal).
    if (!login_mode && data_ready) {
        struct Placement {
            std::string key;
            int row, col, w, h;
        };
        std::vector<Placement> placements;

        if (preview_img_.visible && preview.is_image && !preview.image_key.empty()) {
            placements.push_back({preview.image_key, preview_img_.row, preview_img_.col,
                                  preview_img_.w, preview_img_.h});
        }

        // Full-screen overlays hide the base dashboard/cluster photos so they
        // never float on top of the modal.
        const bool suppress_base = user_modal_open || subject_modal;

        if (!suppress_base) {
            int card_bottom = content_bottom;
            if (current_tab == Tab::Dashboard) {
                int map_rows = reserve_map_rows(content_top, content_bottom);
                if (map_rows > 0) card_bottom = content_bottom - map_rows;
            }
            int avail_h = card_bottom - content_top;
            if (avail_h >= 20 && left_w >= 24 && !prof.avatar_url.empty()) {
                int avatar_h = (avail_h >= 24) ? 7 : 6;
                placements.push_back({prof.avatar_url, content_top + 2, 3,
                                      left_w - 6, avatar_h - 1});
            }

            if (current_tab == Tab::Cluster && cluster_sel >= 0 && !prof.cluster_students.empty()) {
                int sel_r = cluster_layout::row_of(cluster_sel);
                int sel_s = cluster_layout::seat_of(cluster_sel);
                const auto* cs = get_student_at_desk(prof.cluster_students, cluster_room, sel_r, sel_s);
                if (cs && !cs->cdn_uri.empty()) {
                    const int card_h = 10;
                    const int drow   = content_bottom - card_h;
                    ClusterPhotoBox box = cluster_photo_box(left_w, cols_ - left_w, drow, card_h);
                    if (box.visible) {
                        placements.push_back({cs->cdn_uri, box.pfy + 1, box.pfx + 1,
                                              box.pfw - 2, box.pfh - 1});
                    }
                }
            }
        }

        // The user profile modal shows the viewed student's own photo.
        if (user_modal_open && user_modal_avatar_box_.visible &&
            !user_modal_avatar_key_.empty() &&
            image_renderer::has_image(user_modal_avatar_key_)) {
            placements.push_back({user_modal_avatar_key_,
                                  user_modal_avatar_box_.row, user_modal_avatar_box_.col,
                                  user_modal_avatar_box_.w, user_modal_avatar_box_.h});
        }

        std::string sig;
        for (const auto& p : placements) {
            sig += p.key;
            sig += ':';
            sig += std::to_string(p.row);
            sig += ',';
            sig += std::to_string(p.col);
            sig += ',';
            sig += std::to_string(p.w);
            sig += ',';
            sig += std::to_string(p.h);
            sig += ';';
        }
        if (sig != image_sig_) {
            image_renderer::clear_kitty_images();
            image_sig_ = sig;
        }

        for (const auto& p : placements)
            image_renderer::render_image(p.key, p.row, p.col, p.w, p.h, rows_, cols_);
    } else if (!image_sig_.empty()) {
        image_renderer::clear_kitty_images();
        image_sig_.clear();
    }

    curs_set(0);
    std::fputs("\033[?25l", stdout);
    std::fflush(stdout);
}

// ─────────────────────────────────────────────────────────────────────────────
// Tab Bar
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_tab_bar(Tab current_tab, bool loading) {
    attron(COLOR_PAIR(CP_TAB_IDLE));
    fill_row(0, 0, cols_);
    attroff(COLOR_PAIR(CP_TAB_IDLE));

    // Brand logo on the left
    attron(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
    mvprintw(0, 1, " 42 INTRA ");
    attroff(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);

    struct TabDef { const char* key; const char* label; Tab tab; };
    const TabDef tabs[] = {
        { "1", "DASHBOARD", Tab::Dashboard },
        { "2", "ROADMAP",   Tab::Roadmap   },
        { "3", "SLOTS",     Tab::Slots     },
        { "4", "CLUSTER",   Tab::Cluster   },
    };

    int x = 14;
    for (auto& t : tabs) {
        bool active = (current_tab == t.tab);
        std::string label_str = "[" + std::string(t.key) + "] " + t.label;
        int tab_w = (int)label_str.size() + 4;
        add_hitbox(0, x, 1, tab_w, MouseAction::TabBar, static_cast<int>(t.tab));

        if (active) {
            attron(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
            mvprintw(0, x, "  %s  ", label_str.c_str());
            attroff(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
            x += (int)label_str.size() + 5;
        } else {
            attron(COLOR_PAIR(CP_TAB_IDLE));
            mvprintw(0, x, "  %s  ", label_str.c_str());
            attroff(COLOR_PAIR(CP_TAB_IDLE));
            x += (int)label_str.size() + 4;
        }
    }

    // Right side: network status indicator (only when it fits)
    {
        std::string right_status = loading ? "⟳ Syncing..." : "● connected";
        int cp = loading ? CP_WARN : CP_SUCCESS;
        int status_x = cols_ - (int)right_status.size() - 2;
        if (status_x > x + 1) {
            attron(COLOR_PAIR(cp) | A_BOLD);
            mvprintw(0, status_x, "%s", right_status.c_str());
            attroff(COLOR_PAIR(cp) | A_BOLD);
        }
    }

}

// ─────────────────────────────────────────────────────────────────────────────
// Global dynamic search bar + results dropdown
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_search_bar(const SearchState& s, int row) {
    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(s.focus ? CP_TAB_ACTIVE : CP_TAB_IDLE));
    fill_row(row, 0, cols_);
    attroff(COLOR_PAIR(s.focus ? CP_TAB_ACTIVE : CP_TAB_IDLE));

    std::string label = "  ⌕ Buscar: ";
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(row, 1, label, cols_ - 2);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    int qx = 1 + (int)label.size();
    std::string q = s.query;
    if (s.focus) q += "▏";
    attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
    mvprint_clip(row, qx, q.empty() ? "(escribe para filtrar)" : q, cols_ - qx - 34);
    attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

    std::string right;
    if (s.focus) {
        right = "  " + std::to_string(s.results.size()) +
                " resultado(s)  ·  ↑/↓ mover  ·  Enter abrir  ·  Esc salir  ";
    } else {
        right = "  pulsa [/] para buscar usuarios online y proyectos  ";
    }
    int rxx = cols_ - (int)right.size() - 1;
    if (rxx > qx + 6) {
        attron(COLOR_PAIR(s.focus ? CP_TAB_ACTIVE : CP_DIM));
        mvprint_clip(row, rxx, right, cols_ - rxx - 1);
        attroff(COLOR_PAIR(s.focus ? CP_TAB_ACTIVE : CP_DIM));
    }

    add_hitbox(row, 0, 1, cols_, MouseAction::SearchBar, 0);

    // Separator line below the search bar
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(row + 1, 0, bc.t_left);
    hline_box(row + 1, 1, cols_ - 2);
    mvaddstr(row + 1, cols_ - 1, bc.t_right);
    attroff(COLOR_PAIR(CP_BORDER));
}

void Renderer::draw_search_results(const SearchState& s, int top, int bottom) {
    if (!s.focus || s.results.empty()) return;

    const auto& bc = get_border_chars();
    int bw = std::min(cols_ - 4, 80);
    if (bw < 30) return;
    int bx = 2;

    int n = std::min((int)s.results.size(), bottom - top - 2);
    if (n < 1) return;
    int bh = n + 2; // top border + rows + bottom border

    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = top; r <= top + bh; ++r) fill_row(r, bx, bw);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(top, bx, bc.tl);
    hline_box(top, bx + 1, bw - 2);
    mvaddstr(top, bx + bw - 1, bc.tr);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(top, bx + 2, " RESULTADOS · usuarios online y proyectos ", bw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    int y = top + 1;
    for (int i = 0; i < n; ++i) {
        const auto& r = s.results[i];
        bool is_sel = (i == s.sel);
        add_hitbox(y, bx, 1, bw, MouseAction::SearchResult, i);

        if (is_sel) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(y, bx + 1, bw - 2);
            std::string line = " ▶ " + r.title;
            mvprint_clip(y, bx + 2, line, bw - 22);
            mvprint_clip(y, bx + bw - 20, r.subtitle, 19);
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            bool is_user = (r.kind == SearchResult::Kind::User);
            attron(COLOR_PAIR(is_user ? CP_SUCCESS : CP_TITLE) | A_BOLD);
            std::string line = std::string(is_user ? " ● @" : " ▸ ") + r.title;
            mvprint_clip(y, bx + 2, line, bw - 22);
            attroff(COLOR_PAIR(is_user ? CP_SUCCESS : CP_TITLE) | A_BOLD);

            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(y, bx + bw - 20, r.subtitle, 19);
            attroff(COLOR_PAIR(CP_DIM));
        }
        ++y;
    }

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(y, bx, bc.bl);
    hline_box(y, bx + 1, bw - 2);
    mvaddstr(y, bx + bw - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);
}

// ─────────────────────────────────────────────────────────────────────────────
// Status Bar
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_status_bar(const std::string& login,
                               const std::string& status_msg,
                               const std::string& error_msg,
                               Tab current_tab)
{
    int row = rows_ - 1;

    std::string hints;
    if (current_tab == Tab::Dashboard)
        hints = " [/]:Subviews  j/k:Nav  Enter/f:Inspect  r:Sync  t:Theme  q:Quit ";
    else if (current_tab == Tab::Slots)
        hints = i18n::tr("hint_slots");
    else if (current_tab == Tab::Roadmap)
        hints = " j/k:Nav  Enter:Actions  p:Preview  d/s:PDF  t:Theme  q:Quit ";
    else if (current_tab == Tab::Cluster)
        hints = " j/k:Select  y:Copylogin  r:Sync  t:Theme  q:Quit ";
    else
        hints = " 1-4:Tabs  s:QuickSlot  t:Theme  r:Sync  q:Quit ";

    int hints_w = (int)hints.size();
    std::string tag = " @" + (login.empty() ? "42" : login) + " ";
    int tag_w = (int)tag.size();
    int centre_w = cols_ - hints_w - tag_w;

    if (centre_w < 10) {
        // Fallback for narrow terminal
        attron(COLOR_PAIR(CP_STATUS_C));
        fill_row(row, 0, cols_);
        mvprint_clip(row, 0, !error_msg.empty() ? "⚠ " + error_msg : status_msg, cols_);
        attroff(COLOR_PAIR(CP_STATUS_C));
        return;
    }

    // Left segment
    attron(COLOR_PAIR(CP_STATUS_L) | A_BOLD);
    mvprintw(row, 0, "%s", tag.c_str());
    attroff(COLOR_PAIR(CP_STATUS_L) | A_BOLD);

    // Centre segment
    if (!error_msg.empty()) {
        attron(COLOR_PAIR(CP_FAIL) | A_BOLD);
        fill_row(row, tag_w, centre_w);
        mvprint_clip(row, tag_w + 1, "⚠ " + error_msg, centre_w - 2);
        attroff(COLOR_PAIR(CP_FAIL) | A_BOLD);
    } else {
        attron(COLOR_PAIR(CP_STATUS_C));
        fill_row(row, tag_w, centre_w);
        mvprint_clip(row, tag_w + 1, "ℹ " + status_msg, centre_w - 2);
        attroff(COLOR_PAIR(CP_STATUS_C));
    }

    // Right segment
    attron(COLOR_PAIR(CP_STATUS_R));
    mvprintw(row, tag_w + centre_w, "%s", hints.c_str());
    attroff(COLOR_PAIR(CP_STATUS_R));
}

// ─────────────────────────────────────────────────────────────────────────────
// Left Profile Panel
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_profile_panel(const Profile& p, int top, int bottom, int panel_w) {
    if (bottom <= top || panel_w < 20) return;

    const auto& bc = get_border_chars();

    // Outer border
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, 0, bc.tl);
    hline_box(top, 1, panel_w - 2);
    mvaddstr(top, panel_w - 1, bc.t_up);

    for (int r = top + 1; r < bottom; ++r) {
        mvaddstr(r, 0, bc.v);
        mvaddstr(r, panel_w - 1, bc.v);
    }

    mvaddstr(bottom, 0, bc.bl);
    hline_box(bottom, 1, panel_w - 2);
    mvaddstr(bottom, panel_w - 1, bc.t_down);
    attroff(COLOR_PAIR(CP_BORDER));

    // Title badge
    {
        std::string title = " STUDENT CARD ";
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprintw(top, (panel_w - (int)title.size()) / 2, "%s", title.c_str());
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    }

    int row = top + 1;
    int iw  = panel_w - 4;

    auto print_line = [&](const std::string& label, const std::string& val, int val_cp = CP_VALUE) {
        if (row >= bottom) return;
        mvaddstr(row, 0, bc.v);
        fill_row(row, 1, panel_w - 2);
        attron(COLOR_PAIR(CP_LABEL));
        mvprintw(row, 2, "%-12s", label.c_str());
        attroff(COLOR_PAIR(CP_LABEL));

        attron(COLOR_PAIR(val_cp) | A_BOLD);
        mvprint_clip(row, 15, val, panel_w - 17);
        attroff(COLOR_PAIR(val_cp) | A_BOLD);

        mvaddstr(row, panel_w - 1, bc.v);
        ++row;
    };

    auto divider = [&]() {
        if (row >= bottom) return;
        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(row, 0, bc.t_left);
        hline_box(row, 1, panel_w - 2);
        mvaddstr(row, panel_w - 1, bc.t_right);
        attroff(COLOR_PAIR(CP_BORDER));
        ++row;
    };

    auto blank = [&]() {
        if (row >= bottom) return;
        mvaddstr(row, 0, bc.v);
        fill_row(row, 1, panel_w - 2);
        mvaddstr(row, panel_w - 1, bc.v);
        ++row;
    };

    // Avatar Photo Frame if space permits
    int avail_h = bottom - top;
    if (avail_h >= 20 && panel_w >= 24) {
        int avatar_h = (avail_h >= 24) ? 7 : 6;
        int avatar_w = panel_w - 6;

        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(row, 2, bc.tl);
        hline_box(row, 3, avatar_w);
        mvaddstr(row, 3 + avatar_w, bc.tr);
        for (int ah = 1; ah < avatar_h; ++ah) {
            mvaddstr(row + ah, 2, bc.v);
            fill_row(row + ah, 3, avatar_w);
            mvaddstr(row + ah, 3 + avatar_w, bc.v);
        }
        mvaddstr(row + avatar_h, 2, bc.bl);
        hline_box(row + avatar_h, 3, avatar_w);
        mvaddstr(row + avatar_h, 3 + avatar_w, bc.br);
        attroff(COLOR_PAIR(CP_BORDER));

        if (!image_renderer::has_image(p.avatar_url)) {
            attron(COLOR_PAIR(CP_DIM));
            std::string placeholder = "[PHOTO]";
            mvprintw(row + avatar_h / 2, 3 + (avatar_w - (int)placeholder.size()) / 2, "%s", placeholder.c_str());
            attroff(COLOR_PAIR(CP_DIM));
        }

        row += avatar_h + 1;
    }

    // User header avatar / name
    {
        std::string login_display = p.login.empty() ? "—" : "@" + p.login;
        std::string name_display  = p.display_name.empty() ? "" : p.display_name;

        mvaddstr(row, 0, bc.v);
        fill_row(row, 1, panel_w - 2);
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprint_clip(row, 2, "◆ " + login_display, iw);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvaddstr(row, panel_w - 1, bc.v);
        ++row;

        if (!name_display.empty() && name_display != p.login && row < bottom) {
            mvaddstr(row, 0, bc.v);
            fill_row(row, 1, panel_w - 2);
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(row, 4, name_display, iw - 2);
            attroff(COLOR_PAIR(CP_DIM));
            mvaddstr(row, panel_w - 1, bc.v);
            ++row;
        }
    }

    divider();

    // Metrics
    print_line("Cursus Level", p.level, CP_SUCCESS);

    // Progress Bar for Level
    if (row < bottom) {
        float lvl = 0.f;
        try { lvl = std::stof(p.level); } catch (...) {}
        float frac = lvl - static_cast<int>(lvl);
        if (frac < 0.f) frac = 0.f;
        if (frac > 1.f) frac = 1.f;

        int bar_w = panel_w - 6;
        int filled = static_cast<int>(frac * bar_w);

        mvaddstr(row, 0, bc.v);
        fill_row(row, 1, panel_w - 2);

        // Draw progress bracket [████░░░░]
        mvaddch(row, 2, '[');
        attron(COLOR_PAIR(CP_PROGRESS) | A_BOLD);
        for (int i = 0; i < filled; ++i) mvaddstr(row, 3 + i, "█");
        attroff(COLOR_PAIR(CP_PROGRESS) | A_BOLD);

        attron(COLOR_PAIR(CP_DIM));
        for (int i = filled; i < bar_w; ++i) mvaddstr(row, 3 + i, "░");
        attroff(COLOR_PAIR(CP_DIM));
        mvaddch(row, 3 + bar_w, ']');

        // Centered percentage
        char pct[16];
        snprintf(pct, sizeof(pct), " %d%% ", (int)(frac * 100.f));
        int px = 3 + (bar_w - (int)strlen(pct)) / 2;
        attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
        mvprintw(row, px, "%s", pct);
        attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

        mvaddstr(row, panel_w - 1, bc.v);
        ++row;
    }

    divider();

    print_line("Wallet", p.wallet + " \xE2\x82\xB3", CP_WARN); // ₳
    print_line("Eval Points", p.correction_points + " pts", CP_SUCCESS);

    std::string loc = p.location.empty() ? "Unavailable" : p.location;
    bool at_desk = (loc != "Unavailable");
    print_line("Cluster Seat", (at_desk ? "● " : "○ ") + loc, at_desk ? CP_SUCCESS : CP_DIM);

    divider();

    // Stats
    int finished = 0, in_prog = 0, waiting = 0;
    for (const auto& pr : p.projects) {
        if (pr.status == "finished") ++finished;
        else if (pr.status == "in_progress") ++in_prog;
        else ++waiting;
    }

    print_line("Validated", std::to_string(finished) + " projects", CP_SUCCESS);
    print_line("In Progress", std::to_string(in_prog) + " projects", CP_IN_PROG);
    print_line("Waiting", std::to_string(waiting) + " projects", CP_WARN);
    print_line("Slots Open", std::to_string(p.slots.size()) + " available", CP_VALUE);

    while (row < bottom) blank();
}

// ─────────────────────────────────────────────────────────────────────────────
// Tab 1: Dashboard
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_dashboard(const Profile& p, bool inspect, int scroll, int minimap_room,
                              int top, int bottom, int left_w) {
    int map_rows    = reserve_map_rows(top, bottom);
    int card_bottom = (map_rows > 0) ? bottom - map_rows : bottom;
    draw_profile_panel(p, top, card_bottom, left_w);
    if (map_rows > 0)
        draw_cluster_minimap(p, card_bottom + 1, bottom, left_w, minimap_hover_, minimap_room);

    int rx = left_w;
    int rw = cols_ - rx;
    if (rw < 10) return;

    const auto& bc = get_border_chars();

    // Right frame border
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, cols_ - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) mvaddstr(r, cols_ - 1, bc.v);
    mvaddstr(bottom, cols_ - 1, bc.br);
    hline_box(bottom, rx, rw - 1);
    attroff(COLOR_PAIR(CP_BORDER));

    auto fmt_d = [](std::string s, int n) {
        auto pos = s.find("%d");
        if (pos != std::string::npos) s.replace(pos, 2, std::to_string(n));
        return s;
    };

    int pending = p.pending_feedbacks_count;
    for (const auto& fb : p.feedbacks)
        if (fb.is_pending) { pending = std::max(pending, 1); break; }

    // ── Fixed header ─────────────────────────────────────────────────────────
    std::string title = "◆ " + i18n::tr("dash_title");
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(top, rx + 2, title, rw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    if (pending > 0)
        draw_pill(top, rx + rw - 16, "⚠ " + std::to_string(pending) + " " + i18n::tr("stat_pending"), CP_PILL_WARN);

    // ── Scrollable content ───────────────────────────────────────────────────
    const int vtop    = top + 2;   // first content row
    const int vbottom = bottom;    // exclusive
    int crow = vtop;

    auto sy  = [&](int vr) { return vr - scroll; };
    auto vis = [&](int vr) { int s = vr - scroll; return s >= vtop && s < vbottom; };

    // Boxed card with a filled title bar. `body_h` = body rows inside the card.
    auto card_frame = [&](int v, const std::string& ct, int body_h) {
        int total = body_h + 3;   // top border + title bar + body + bottom border
        for (int i = 0; i < total; ++i) {
            if (!vis(v + i)) continue;
            int y = sy(v + i);
            if (i == 0) {
                attron(COLOR_PAIR(CP_BORDER));
                mvaddstr(y, rx + 2, bc.tl);
                hline_box(y, rx + 3, rw - 6);
                mvaddstr(y, rx + rw - 3, bc.tr);
                attroff(COLOR_PAIR(CP_BORDER));
            } else if (i == total - 1) {
                attron(COLOR_PAIR(CP_BORDER));
                mvaddstr(y, rx + 2, bc.bl);
                hline_box(y, rx + 3, rw - 6);
                mvaddstr(y, rx + rw - 3, bc.br);
                attroff(COLOR_PAIR(CP_BORDER));
            } else {
                attron(COLOR_PAIR(CP_BORDER));
                mvaddstr(y, rx + 2, bc.v);
                mvaddstr(y, rx + rw - 3, bc.v);
                attroff(COLOR_PAIR(CP_BORDER));
                attron(COLOR_PAIR(CP_MODAL_BG));
                fill_row(y, rx + 3, rw - 6);
                attroff(COLOR_PAIR(CP_MODAL_BG));
            }
        }
        if (vis(v + 1)) {
            int y = sy(v + 1);
            attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
            fill_row(y, rx + 3, rw - 6);
            mvprint_clip(y, rx + 4, ct, rw - 8);
            attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        }
    };
    auto put = [&](int vr, int xoff, const std::string& s, int cp, int attr = 0) {
        if (!vis(vr)) return;
        attron(COLOR_PAIR(cp) | attr);
        mvprint_clip(sy(vr), rx + 4 + xoff, s, rw - 8 - xoff);
        attroff(COLOR_PAIR(cp) | attr);
    };

    // ── 1. Summary strip ─────────────────────────────────────────────────────
    {
        int v = crow;
        if (vis(v)) {
            int y = sy(v);
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(y, rx + 2, bc.tl); hline_box(y, rx + 3, rw - 6); mvaddstr(y, rx + rw - 3, bc.tr);
            attroff(COLOR_PAIR(CP_BORDER));
        }
        if (vis(v + 1)) {
            int y = sy(v + 1);
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(y, rx + 2, bc.v); mvaddstr(y, rx + rw - 3, bc.v);
            attroff(COLOR_PAIR(CP_BORDER));
            attron(COLOR_PAIR(CP_MODAL_BG)); fill_row(y, rx + 3, rw - 6); attroff(COLOR_PAIR(CP_MODAL_BG));
            int sx = rx + 4;
            auto st = [&](const std::string& lbl, const std::string& val, int cp) {
                attron(COLOR_PAIR(CP_DIM));
                mvprint_clip(y, sx, lbl + " ", rw - (sx - rx) - 2);
                attroff(COLOR_PAIR(CP_DIM));
                sx += (int)lbl.size() + 1;
                attron(COLOR_PAIR(cp) | A_BOLD);
                mvprint_clip(y, sx, val, rw - (sx - rx) - 2);
                attroff(COLOR_PAIR(cp) | A_BOLD);
                sx += (int)val.size() + 3;
            };
            st(i18n::tr("stat_level"), p.level.empty() ? "—" : p.level, CP_SUCCESS);
            st(i18n::tr("stat_wallet"), (p.wallet.empty() ? "0" : p.wallet) + "₳", CP_WARN);
            st(i18n::tr("stat_eval"), p.correction_points.empty() ? "0" : p.correction_points, CP_SUCCESS);
            st(i18n::tr("stat_seat"), p.location.empty() ? "—" : p.location, CP_VALUE);
            st(i18n::tr("stat_slots"), std::to_string(p.slots.size()), CP_VALUE);
            st(i18n::tr("stat_pending"), std::to_string(pending), pending > 0 ? CP_WARN : CP_DIM);
        }
        if (vis(v + 2)) {
            int y = sy(v + 2);
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(y, rx + 2, bc.bl); hline_box(y, rx + 3, rw - 6); mvaddstr(y, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));
        }
        crow += 4;
    }

    // ── 2. Cursus level ──────────────────────────────────────────────────────
    {
        int v = crow;
        card_frame(v, "◆ " + i18n::tr("cursus_title") + "  " + p.level, 1);
        if (vis(v + 2)) {
            int y = sy(v + 2);
            float lvl = 0.f;
            try { lvl = std::stof(p.level); } catch (...) {}
            float frac = lvl - static_cast<int>(lvl);
            if (frac < 0.f) frac = 0.f;
            if (frac > 1.f) frac = 1.f;
            int bar_w = rw - 20;
            if (bar_w > 8) {
                int filled = static_cast<int>(frac * bar_w);
                attron(COLOR_PAIR(CP_DIM));
                mvaddstr(y, rx + 4, "Progress: [");
                attroff(COLOR_PAIR(CP_DIM));
                attron(COLOR_PAIR(CP_PROGRESS) | A_BOLD);
                for (int i = 0; i < filled; ++i) mvaddstr(y, rx + 15 + i, "█");
                attroff(COLOR_PAIR(CP_PROGRESS) | A_BOLD);
                attron(COLOR_PAIR(CP_DIM));
                for (int i = filled; i < bar_w; ++i) mvaddstr(y, rx + 15 + i, "░");
                attroff(COLOR_PAIR(CP_DIM));
                mvaddch(y, rx + 15 + bar_w, ']');
                attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                mvprintw(y, rx + 17 + bar_w, "%d%%", static_cast<int>(frac * 100.f));
                attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            }
        }
        crow += 5;
    }

    // ── 3. Action center ─────────────────────────────────────────────────────
    if (pending > 0) {
        int v = crow;
        card_frame(v, "⚠ " + i18n::tr("dash_action_title"), 1);
        if (vis(v + 2)) {
            int y = sy(v + 2);
            put(v + 2, 0, fmt_d(i18n::tr("dash_action_msg"), pending), CP_VALUE);
            std::string rv = " " + i18n::tr("review") + " ";
            int bx = rx + rw - 3 - (int)rv.size();
            if (bx > rx + 4) {
                add_hitbox(y, bx, 1, (int)rv.size(), MouseAction::DashReview, 0);
                attron(COLOR_PAIR(CP_PILL_ACCENT) | A_BOLD);
                mvaddstr(y, bx, rv.c_str());
                attroff(COLOR_PAIR(CP_PILL_ACCENT) | A_BOLD);
            }
        }
        crow += 5;
    }

    // ── 4. Recent submissions ────────────────────────────────────────────────
    {
        int count = std::min((int)p.projects.size(), 6);
        int body_h = (count == 0) ? 2 : count + 1;
        int v = crow;
        card_frame(v, "◆ " + i18n::tr("recent_submissions"), body_h);
        if (vis(v + 2)) {
            int y = sy(v + 2);
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(y, rx + 4, "#  " + i18n::tr("hdr_project"), 20);
            mvprint_clip(y, rx + rw - 26, i18n::tr("hdr_grade"), 6);
            mvprint_clip(y, rx + rw - 18, i18n::tr("hdr_status"), 14);
            attroff(COLOR_PAIR(CP_DIM));
        }
        int shown = 0;
        for (const auto& pr : p.projects) {
            if (shown >= 6) break;
            int vr = v + 3 + shown;
            if (!vis(vr)) { ++shown; continue; }
            int y = sy(vr);
            bool ok   = (pr.status == "finished" && pr.grade != "N/A" && !pr.grade.empty());
            bool fail = (pr.status == "finished" && !ok);
            bool prog = (pr.status == "in_progress");
            std::string badge = ok ? i18n::tr("status_pass")
                                 : (prog ? i18n::tr("status_inprogress")
                                         : (fail ? i18n::tr("status_fail") : i18n::tr("status_waiting")));
            int pill_cp = ok ? CP_PILL_SUCCESS : (prog ? CP_PILL_WARN : (fail ? CP_PILL_FAIL : CP_DIM));
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(y, rx + 4, pad(std::to_string(shown + 1), 2), 3);
            attroff(COLOR_PAIR(CP_DIM));
            attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
            mvprint_clip(y, rx + 9, pr.name, rw - 46);
            attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);
            std::string grade = pr.grade.empty() ? "N/A" : pr.grade;
            attron(COLOR_PAIR(ok ? CP_SUCCESS : (prog ? CP_DIM : CP_FAIL)) | A_BOLD);
            mvprint_clip(y, rx + rw - 26, grade, 6);
            attroff(COLOR_PAIR(ok ? CP_SUCCESS : (prog ? CP_DIM : CP_FAIL)) | A_BOLD);
            draw_pill(y, rx + rw - 18, badge, pill_cp);
            ++shown;
        }
        if (count == 0) put(v + 3, 0, "No projects loaded — press 'r' to sync.", CP_DIM);
        crow += body_h + 4;
    }

    // ── 5. Recent evaluations ────────────────────────────────────────────────
    {
        int count = std::min((int)p.feedbacks.size(), 5);
        int body_h = (count == 0) ? 2 : count + 1;
        int v = crow;
        card_frame(v, "◆ " + i18n::tr("recent_evaluations"), body_h);
        if (vis(v + 2)) {
            int y = sy(v + 2);
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(y, rx + 4, "#  " + i18n::tr("hdr_project"), 22);
            mvprint_clip(y, rx + 30, i18n::tr("hdr_peer"), 14);
            mvprint_clip(y, rx + rw - 24, i18n::tr("hdr_grade"), 6);
            mvprint_clip(y, rx + rw - 15, i18n::tr("hdr_feedback"), 9);
            attroff(COLOR_PAIR(CP_DIM));
        }
        int shown = 0;
        for (const auto& fb : p.feedbacks) {
            if (shown >= 5) break;
            int vr = v + 3 + shown;
            if (!vis(vr)) { ++shown; continue; }
            int y = sy(vr);
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(y, rx + 4, pad(std::to_string(shown + 1), 2), 3);
            attroff(COLOR_PAIR(CP_DIM));
            attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
            mvprint_clip(y, rx + 9, fb.project_name, 20);
            attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);
            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(y, rx + 30, "@" + fb.evaluator_login, 14);
            attroff(COLOR_PAIR(CP_VALUE));
            attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            mvprint_clip(y, rx + rw - 24, fb.mark.empty() ? "N/A" : fb.mark, 6);
            attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            attron(COLOR_PAIR(CP_WARN));
            mvprint_clip(y, rx + rw - 15, fb.feedback_rating.empty() ? "★★★★★" : fb.feedback_rating, 9);
            attroff(COLOR_PAIR(CP_WARN));
            ++shown;
        }
        if (count == 0) put(v + 3, 0, "No evaluations yet.", CP_DIM);
        crow += body_h + 4;
    }

    // ── 6. Evaluation economy ────────────────────────────────────────────────
    {
        int v = crow;
        card_frame(v, "◆ " + i18n::tr("eval_economy"), 2);
        if (vis(v + 2)) {
            std::string l1 = i18n::tr("avail") + ": " + (p.correction_points.empty() ? "0" : p.correction_points) +
                             " pts   " + i18n::tr("stat_wallet") + ": " + (p.wallet.empty() ? "0" : p.wallet) +
                             " ₳   " + i18n::tr("can_request") + ": " + (p.correction_points.empty() ? "0" : p.correction_points) + " evals";
            attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
            mvprint_clip(sy(v + 2), rx + 4, l1, rw - 8);
            attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);
        }
        if (vis(v + 3)) {
            std::string l2 = i18n::tr("econ_earn") + "   │   " + i18n::tr("econ_spend") + "   │   " + i18n::tr("econ_pool");
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(sy(v + 3), rx + 4, l2, rw - 8);
            attroff(COLOR_PAIR(CP_DIM));
        }
        crow += 6;
    }

    // ── Feedback inspector overlay ───────────────────────────────────────────
    if (inspect) {
        const EvaluationFeedback* fb = nullptr;
        for (const auto& f : p.feedbacks) if (f.is_pending) { fb = &f; break; }
        if (!fb && !p.feedbacks.empty()) fb = &p.feedbacks.front();

        int mw = std::min(rw - 4, 70);
        int mh = std::min(bottom - top - 4, 13);
        int mx = rx + (rw - mw) / 2;
        int my = top + 2;
        if (mw >= 30) {
            draw_modal_frame(my, mx, mh, mw, " " + i18n::tr("dash_action_title"));
            if (fb) {
                int r = my + 2;
                auto row = [&](const std::string& lbl, const std::string& val, int vcp = CP_VALUE) {
                    if (r >= my + mh - 1) return;
                    attron(COLOR_PAIR(CP_LABEL));
                    mvprint_clip(r, mx + 3, lbl, 13);
                    attroff(COLOR_PAIR(CP_LABEL));
                    attron(COLOR_PAIR(vcp) | A_BOLD);
                    mvprint_clip(r, mx + 17, val, mw - 19);
                    attroff(COLOR_PAIR(vcp) | A_BOLD);
                    ++r;
                };
                row(i18n::tr("hdr_project"), fb->project_name);
                row(i18n::tr("tip_student"), "@" + (fb->evaluator_login.empty() ? "peer" : fb->evaluator_login));
                row(i18n::tr("hdr_grade"), fb->mark.empty() ? "Pending" : fb->mark, CP_SUCCESS);
                if (!fb->comment.empty()) {
                    std::string c = fb->comment;
                    for (size_t i = 0; i < c.size() && r < my + mh - 2; i += (size_t)(mw - 6)) {
                        attron(COLOR_PAIR(CP_VALUE));
                        mvprint_clip(r++, mx + 4, c.substr(i, mw - 6), mw - 6);
                        attroff(COLOR_PAIR(CP_VALUE));
                    }
                }
            } else {
                attron(COLOR_PAIR(CP_DIM));
                mvprint_clip(my + 3, mx + 4, "No feedback selected.", mw - 8);
                attroff(COLOR_PAIR(CP_DIM));
            }
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(my + mh - 1, mx + 3, "[Enter] / [Esc] close", mw - 6);
            attroff(COLOR_PAIR(CP_DIM));
        }
    }

    dash_scroll_max_ = std::max(0, crow - bottom);
}

// ─────────────────────────────────────────────────────────────────────────────
// Tab 2: Projects
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_projects(const Profile& p, int sel, int top, int bottom, int left_w,
                             bool preview_panel, const SubjectPreview& pv) {
    draw_profile_panel(p, top, bottom, left_w);

    int rx = left_w;
    int full_rw = cols_ - rx;
    if (full_rw < 10) return;

    int panel_w = 0;
    if (preview_panel) {
        panel_w = std::clamp(full_rw * 45 / 100, 30, 64);
        if (full_rw - panel_w < 24) panel_w = 0;
    }
    int rw = full_rw - panel_w;

    const auto& bc = get_border_chars();

    // Right frame border
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, rx + rw - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) mvaddstr(r, rx + rw - 1, bc.v);
    mvaddstr(bottom, rx + rw - 1, bc.br);
    hline_box(bottom, rx, rw - 1);
    attroff(COLOR_PAIR(CP_BORDER));

    int row = top;

    // Header title
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    std::string p_title = "◆ Projects Cursus Explorer (" + std::to_string(p.projects.size()) + " total)";
    mvprint_clip(row, rx + 2, p_title, rw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    row++;

    // Table Columns
    attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    fill_row(row, rx + 2, rw - 4);
    std::string hdr = pad("   #  PROJECT NAME", rw - 26) + pad("GRADE", 10) + "STATUS";
    mvprint_clip(row, rx + 2, hdr, rw - 4);
    attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    row++;

    int max_visible = bottom - row - 3;
    if (max_visible < 3) max_visible = 3;

    int total = (int)p.projects.size();
    int start = 0;
    if (sel >= max_visible) {
        start = sel - max_visible + 1;
    }

    for (int i = start; i < total && (row < bottom - 3); ++i) {
        const auto& pr = p.projects[i];
        bool is_sel = (i == sel);
        add_hitbox(row, rx + 2, 1, rw - 4, MouseAction::ListRow, i);

        bool ok   = (pr.status == "finished" && pr.grade != "N/A" && !pr.grade.empty());
        bool fail = (pr.status == "finished" && !ok);
        bool prog = (pr.status == "in_progress");

        if (is_sel) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(row, rx + 2, rw - 4);
            mvprintw(row, rx + 2, " ▶ %02d  %-*s %-8s %s",
                     i + 1, rw - 31, pr.name.c_str(),
                     pr.grade.c_str(), pr.status.c_str());
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            int cp = ok ? CP_SUCCESS : (fail ? CP_FAIL : (prog ? CP_IN_PROG : CP_WARN));
            char num[32];
            snprintf(num, sizeof(num), "   %02d", i + 1);

            attron(COLOR_PAIR(CP_DIM));
            mvprintw(row, rx + 2, "%s", num);
            attroff(COLOR_PAIR(CP_DIM));

            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(row, rx + 9, pr.name, rw - 33);
            attroff(COLOR_PAIR(CP_VALUE));

            attron(COLOR_PAIR(cp) | A_BOLD);
            mvprintw(row, rx + rw - 22, "%-8s", pr.grade.c_str());
            mvprint_clip(row, rx + rw - 14, pr.status, 12);
            attroff(COLOR_PAIR(cp) | A_BOLD);
        }
        row++;
    }

    // Detail Preview Box at bottom
    if (sel >= 0 && sel < total && bottom - 3 > top) {
        int drow = bottom - 3;
        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(drow, rx + 2, bc.tl);
        hline_box(drow, rx + 3, rw - 6);
        mvaddstr(drow, rx + rw - 3, bc.tr);

        mvaddstr(drow + 1, rx + 2, bc.v);
        fill_row(drow + 1, rx + 3, rw - 6);
        mvaddstr(drow + 1, rx + rw - 3, bc.v);

        mvaddstr(drow + 2, rx + 2, bc.bl);
        hline_box(drow + 2, rx + 3, rw - 6);
        mvaddstr(drow + 2, rx + rw - 3, bc.br);
        attroff(COLOR_PAIR(CP_BORDER));

        const auto& pr = p.projects[sel];
        std::string detail = "Project: " + pr.name + "  │  Grade: " + pr.grade + "  │  Status: " + pr.status;
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprint_clip(drow + 1, rx + 4, detail, rw - 8);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    }

    if (panel_w > 0)
        preview_img_ = draw_subject_panel(pv, rx + rw, top, bottom, panel_w);
}

// ─────────────────────────────────────────────────────────────────────────────
// Tab 3: Slots
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_slots(const Profile& p, int sel, int hover, int btn_hover,
                          int top, int bottom, int left_w) {
    draw_profile_panel(p, top, bottom, left_w);

    int rx = left_w;
    int rw = cols_ - rx;
    if (rw < 10) return;

    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, cols_ - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) mvaddstr(r, cols_ - 1, bc.v);
    mvaddstr(bottom, cols_ - 1, bc.br);
    hline_box(bottom, rx, rw - 1);
    attroff(COLOR_PAIR(CP_BORDER));

    int total = (int)p.slots.size();
    int gap   = Config::get().slot_gap_minutes;
    int row   = top;

    auto extract_time = [](const std::string& iso) -> std::string {
        if (iso.size() >= 16) return iso.substr(11, 5);
        return iso;
    };
    // Substitute the first "%d" in a translated template with an integer.
    auto fmt_d = [](std::string s, int n) {
        auto pos = s.find("%d");
        if (pos != std::string::npos) s.replace(pos, 2, std::to_string(n));
        return s;
    };

    // ── Header + live count badge ─────────────────────────────────────────────
    std::string title = "◆ " + i18n::tr("slot_title");
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(row, rx + 2, title, rw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    draw_pill(row, rx + 2 + (int)title.size() + 2,
              std::to_string(total) + " " + i18n::tr("slot_open_badge"), CP_PILL_SUCCESS);
    row += 2;

    // ── Subtitle ──────────────────────────────────────────────────────────────
    attron(COLOR_PAIR(CP_VALUE));
    mvprint_clip(row, rx + 2, i18n::tr("slot_subtitle"), rw - 4);
    attroff(COLOR_PAIR(CP_VALUE));
    row += 2;

    // ── Summary strip ─────────────────────────────────────────────────────────
    int total_mins = 0;
    std::string min_begin;
    for (const auto& sl : p.slots) {
        total_mins += slot_duration_minutes(sl.begin_at, sl.end_at);
        if (min_begin.empty() || sl.begin_at < min_begin) min_begin = sl.begin_at;
    }
    std::string next_label = "—";
    if (!min_begin.empty())
        next_label = slot_day_label(min_begin).substr(0, 3) + " " + extract_time(min_begin);

    if (row < bottom - 2) {
        int sx = rx + 2;
        auto stat = [&](const std::string& label, const std::string& value, int cp) {
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(row, sx, label + " ", rw - (sx - rx) - 2);
            attroff(COLOR_PAIR(CP_DIM));
            sx += (int)label.size() + 1;
            attron(COLOR_PAIR(cp) | A_BOLD);
            mvprint_clip(row, sx, value, rw - (sx - rx) - 2);
            attroff(COLOR_PAIR(cp) | A_BOLD);
            sx += (int)value.size() + 3;
        };
        stat(i18n::tr("stat_open"),  std::to_string(total), CP_VALUE);
        stat(i18n::tr("stat_total"), minutes_label(total_mins), CP_VALUE);
        stat(i18n::tr("stat_next"),  next_label, CP_SUCCESS);
        stat(i18n::tr("stat_gap"),   std::to_string(gap) + "m", CP_WARN);
        row += 2;
    }

    // ── Toolbar (clickable buttons) ───────────────────────────────────────────
    bool have_sel = (total > 0 && sel >= 0 && sel < total);
    auto draw_button = [&](int y, int& x, int index, const std::string& label, int pill_cp, bool enabled) {
        std::string text = " " + label + " ";
        int w = (int)text.size();
        if (x + w > rx + rw - 2) return;
        bool hov = (btn_hover == index) && enabled;
        if (enabled) {
            attron(COLOR_PAIR(hov ? CP_ROW_SEL : pill_cp) | A_BOLD);
            mvaddstr(y, x, text.c_str());
            attroff(COLOR_PAIR(hov ? CP_ROW_SEL : pill_cp) | A_BOLD);
            add_hitbox(y, x, 1, w, MouseAction::SlotBtn, index);
        } else {
            attron(COLOR_PAIR(CP_DIM));
            mvaddstr(y, x, text.c_str());
            attroff(COLOR_PAIR(CP_DIM));
        }
        x += w + 2;
    };

    if (row < bottom - 2) {
        int bx = rx + 2;
        draw_button(row, bx, 0, i18n::tr("btn_new_slot"), CP_PILL_ACCENT, true);
        draw_button(row, bx, 1, i18n::tr("btn_trim"), CP_PILL_WARN, have_sel);
        draw_button(row, bx, 2, i18n::tr("btn_delete"), CP_PILL_FAIL, have_sel);
        draw_button(row, bx, 3, i18n::tr("btn_gap") + ": " + std::to_string(gap) + "m", CP_PILL_SUCCESS, true);
        row += 2;
    }

    // ── Separator ─────────────────────────────────────────────────────────────
    if (row < bottom) {
        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(row, rx, bc.t_left);
        hline_box(row, rx + 1, rw - 2);
        mvaddstr(row, rx + rw - 1, bc.t_right);
        attroff(COLOR_PAIR(CP_BORDER));
        row++;
    }

    // ── Empty state ───────────────────────────────────────────────────────────
    if (total == 0) {
        int cy = row + 2;
        if (cy + 3 < bottom) {
            attron(COLOR_PAIR(CP_WARN) | A_BOLD);
            mvprint_clip(cy, rx + 4, "◇  " + i18n::tr("slot_empty_title"), rw - 8);
            attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(cy + 1, rx + 4, i18n::tr("slot_empty_sub"), rw - 8);
            attroff(COLOR_PAIR(CP_VALUE));
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(cy + 2, rx + 4,
                         fmt_d(i18n::tr("slot_empty_offset"), Config::get().offset_minutes),
                         rw - 8);
            attroff(COLOR_PAIR(CP_DIM));

            int bx = rx + 4;
            draw_button(cy + 3, bx, 0, i18n::tr("btn_new_slot"), CP_PILL_ACCENT, true);
        }
        return;
    }

    // ── Slot list: single-line cards, one blank row between ───────────────────
    for (int i = 0; i < total && row < bottom - 1; ++i) {
        const auto& sl = p.slots[i];
        bool is_sel = (i == sel);
        bool is_hov = (i == hover && !is_sel);
        bool is_avail = (sl.title.empty() || sl.title == "Available");
        std::string status = is_avail ? i18n::tr("status_available") : i18n::tr("status_reserved");
        int  stripe = (i % 2 == 0) ? CP_DEFAULT : CP_MODAL_BG;
        int  bg = is_sel ? CP_ROW_SEL : stripe;

        attron(COLOR_PAIR(bg));
        fill_row(row, rx + 2, rw - 4);
        attroff(COLOR_PAIR(bg));

        add_hitbox(row, rx + 2, 1, rw - 4, MouseAction::ListRow, i);

        // Marker: ▶ selected, ▏ hovered.
        if (is_sel) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            mvprint_clip(row, rx + 2, "▶ ", 2);
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else if (is_hov) {
            attron(COLOR_PAIR(CP_ACCENT) | A_BOLD);
            mvprint_clip(row, rx + 2, "▏ ", 2);
            attroff(COLOR_PAIR(CP_ACCENT) | A_BOLD);
        }

        // Index
        attron(COLOR_PAIR(bg) | A_BOLD);
        mvprint_clip(row, rx + 5, "#" + pad(std::to_string(i + 1), 2), 3);
        attroff(COLOR_PAIR(bg) | A_BOLD);

        // Status pill (filled badge — never colour-only)
        {
            int pill_cp = is_avail ? CP_PILL_SUCCESS : CP_PILL_WARN;
            int pc = is_sel ? CP_ROW_SEL : pill_cp;
            attron(COLOR_PAIR(pc) | A_BOLD);
            mvprint_clip(row, rx + 10, " " + status + " ", 13);
            attroff(COLOR_PAIR(pc) | A_BOLD);
        }

        // Day
        attron(COLOR_PAIR(bg) | (is_sel ? A_BOLD : 0));
        mvprint_clip(row, rx + 24, slot_day_label(sl.begin_at), 14);
        attroff(COLOR_PAIR(bg) | (is_sel ? A_BOLD : 0));

        // Time range
        attron(COLOR_PAIR(is_sel ? CP_ROW_SEL : CP_TITLE) | A_BOLD);
        mvprint_clip(row, rx + 39, extract_time(sl.begin_at) + " → " + extract_time(sl.end_at), 15);
        attroff(COLOR_PAIR(is_sel ? CP_ROW_SEL : CP_TITLE) | A_BOLD);

        // Duration
        attron(COLOR_PAIR(is_sel ? CP_ROW_SEL : CP_DIM));
        mvprint_clip(row, rx + 55, slot_duration_label(sl.begin_at, sl.end_at), 8);
        attroff(COLOR_PAIR(is_sel ? CP_ROW_SEL : CP_DIM));

        // ID (right-aligned when there is room)
        std::string id = !sl.id.empty() ? sl.id : sl.ids;
        if (!id.empty()) {
            std::string idlabel = "ID " + id;
            int ix = rx + rw - 2 - (int)idlabel.size() - 1;
            if (ix > rx + 64) {
                attron(COLOR_PAIR(is_sel ? CP_ROW_SEL : CP_DIM));
                mvprint_clip(row, ix, idlabel, (int)idlabel.size());
                attroff(COLOR_PAIR(is_sel ? CP_ROW_SEL : CP_DIM));
            }
        }

        row += (i == total - 1) ? 1 : 2;
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Slot manager overlays: free-space picker + right-click context menu
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_gap_picker(int gap_minutes) {
    const int box_w = 48;
    const int box_h = 9;
    int bx = (cols_ - box_w) / 2;
    int by = (rows_ - box_h) / 2;
    if (bx < 0) bx = 0;
    if (by < 0) by = 0;

    draw_modal_frame(by, bx, box_h, box_w, i18n::tr("gap_title"));

    attron(COLOR_PAIR(CP_VALUE));
    mvprint_clip(by + 2, bx + 3, i18n::tr("gap_sub"), box_w - 6);
    attroff(COLOR_PAIR(CP_VALUE));

    // Stepper: ◀ [ value ] ▶
    int centre   = bx + box_w / 2;
    int minus_x  = centre - 14;
    int plus_x   = centre + 11;
    std::string val = std::to_string(gap_minutes) + " " + i18n::tr("gap_minutes");

    add_hitbox(by + 4, minus_x, 1, 3, MouseAction::GapMinus, 0);
    add_hitbox(by + 4, plus_x, 1, 3, MouseAction::GapPlus, 0);

    attron(COLOR_PAIR(CP_WARN) | A_BOLD);
    mvprint_clip(by + 4, minus_x, "◀", 2);
    attroff(COLOR_PAIR(CP_WARN) | A_BOLD);

    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(by + 4, centre - (int)val.size() / 2, val, (int)val.size());
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    attron(COLOR_PAIR(CP_WARN) | A_BOLD);
    mvprint_clip(by + 4, plus_x, "▶", 2);
    attroff(COLOR_PAIR(CP_WARN) | A_BOLD);

    // Hint line
    attron(COLOR_PAIR(CP_DIM));
    std::string hint = i18n::tr("gap_hint");
    mvprint_clip(by + 5, bx + (box_w - (int)hint.size()) / 2, hint, box_w - 4);
    attroff(COLOR_PAIR(CP_DIM));

    // Confirm / cancel
    std::string ok = "[Enter] " + i18n::tr("confirm");
    std::string ko = "[Esc] " + i18n::tr("cancel");
    int ok_x = bx + box_w / 2 - (int)ok.size() - 3;
    int ko_x = bx + box_w / 2 + 3;
    add_hitbox(by + 7, ok_x, 1, (int)ok.size(), MouseAction::GapConfirm, 0);
    add_hitbox(by + 7, ko_x, 1, (int)ko.size(), MouseAction::GapCancel, 0);

    attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
    mvprint_clip(by + 7, ok_x, ok, (int)ok.size());
    attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
    attron(COLOR_PAIR(CP_DIM));
    mvprint_clip(by + 7, ko_x, ko, (int)ko.size());
    attroff(COLOR_PAIR(CP_DIM));
}

void Renderer::draw_slot_context_menu(const SlotUiState& ui) {
    std::vector<std::string> items = {
        i18n::tr("ctx_copy"),
        i18n::tr("ctx_trim"),
        i18n::tr("ctx_delete"),
    };
    int w = 0;
    for (const auto& it : items) w = std::max(w, (int)it.size());
    w += 5; // marker + padding
    int h = (int)items.size();

    int bx = ui.ctx_x;
    int by = ui.ctx_y;
    if (bx + w > cols_) bx = cols_ - w;
    if (by + h > rows_) by = rows_ - h;
    if (bx < 0) bx = 0;
    if (by < 0) by = 0;

    const auto& bc = get_border_chars();
    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = 0; r < h; ++r) fill_row(by + r, bx, w);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    hline_box(by, bx + 1, w - 2);
    mvaddstr(by, bx + w - 1, bc.tr);
    for (int r = 1; r < h - 1; ++r) {
        mvaddstr(by + r, bx, bc.v);
        mvaddstr(by + r, bx + w - 1, bc.v);
    }
    mvaddstr(by + h - 1, bx, bc.bl);
    hline_box(by + h - 1, bx + 1, w - 2);
    mvaddstr(by + h - 1, bx + w - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    for (int i = 0; i < h; ++i) {
        bool is_sel = (i == ui.ctx_sel);
        int cp = (i == 2) ? CP_FAIL : CP_VALUE; // delete = danger
        add_hitbox(by + i, bx + 1, 1, w - 2, MouseAction::SlotCtx, i);
        if (is_sel) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(by + i, bx + 1, w - 2);
            mvprint_clip(by + i, bx + 2, "▶ " + items[i], w - 4);
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            attron(COLOR_PAIR(cp));
            mvprint_clip(by + i, bx + 3, items[i], w - 4);
            attroff(COLOR_PAIR(cp));
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Redesigned Modern Login Dialog
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_login_prompt(int login_method, int active_field,
                                 const std::string& user_buf,
                                 const std::string& pass_buf,
                                 const std::string& cookie_buf,
                                 const std::string& detected_file,
                                 const std::string& error_msg,
                                 bool loading, const std::string& status_msg)
{
    getmaxyx(stdscr, rows_, cols_);

    const int box_w = 64;
    const int box_h = 20;
    int bx = (cols_ - box_w) / 2;
    int by = (rows_ - box_h) / 2;
    if (bx < 0) bx = 0;
    if (by < 0) by = 0;

    const auto& bc = get_border_chars();

    // Background clearing
    for (int r = by; r < by + box_h; ++r) {
        attron(COLOR_PAIR(CP_DEFAULT));
        fill_row(r, bx, box_w);
        attroff(COLOR_PAIR(CP_DEFAULT));
    }

    // Outer border
    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    mvaddstr(by, bx + box_w - 1, bc.tr);
    mvaddstr(by + box_h - 1, bx, bc.bl);
    mvaddstr(by + box_h - 1, bx + box_w - 1, bc.br);
    for (int x = bx + 1; x < bx + box_w - 1; ++x) {
        mvaddstr(by, x, bc.h);
        mvaddstr(by + box_h - 1, x, bc.h);
    }
    for (int y = by + 1; y < by + box_h - 1; ++y) {
        mvaddstr(y, bx, bc.v);
        mvaddstr(y, bx + box_w - 1, bc.v);
    }
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    // ASCII 42 Banner
    {
        const char* l1 = "  ██╗  ██╗██████╗     ██╗███╗   ██╗████████╗██████╗  █████╗  ";
        const char* l2 = "  ██║  ██║╚════██╗    ██║████╗  ██║╚══██╔══╝██╔══██╗██╔══██╗ ";
        const char* l3 = "  ███████║ █████╔╝    ██║██╔██╗ ██║   ██║   ██████╔╝███████║ ";
        const char* l4 = "  ╚════██║██╔═══╝     ██║██║╚██╗██║   ██║   ██╔══██╗██╔══██║ ";
        const char* l5 = "       ██║███████╗    ██║██║ ╚████║   ██║   ██║  ██║██║  ██║ ";
        const char* l6 = "       ╚═╝╚══════╝    ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═╝ ";

        attron(COLOR_PAIR(CP_TAB_IDLE) | A_BOLD);
        mvprintw(by + 1, bx + 1, "%s", l1);
        mvprintw(by + 2, bx + 1, "%s", l2);
        mvprintw(by + 3, bx + 1, "%s", l3);
        mvprintw(by + 4, bx + 1, "%s", l4);
        mvprintw(by + 5, bx + 1, "%s", l5);
        mvprintw(by + 6, bx + 1, "%s", l6);
        attroff(COLOR_PAIR(CP_TAB_IDLE) | A_BOLD);
    }

    // Method Selector Tabs
    {
        int ty = by + 8;
        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(ty, bx, bc.t_left);
        hline_box(ty, bx + 1, box_w - 2);
        mvaddstr(ty, bx + box_w - 1, bc.t_right);
        attroff(COLOR_PAIR(CP_BORDER));

        int mx = bx + 2;
        auto draw_tab_btn = [&](int idx, const char* label) {
            bool active = (login_method == idx);
            add_hitbox(ty, mx, 1, (int)strlen(label) + 8, MouseAction::LoginMethod, idx);
            if (active) {
                attron(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
                mvprintw(ty, mx, " [%d: %s] ", idx + 1, label);
                attroff(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
                mx += (int)strlen(label) + 9;
            } else {
                attron(COLOR_PAIR(CP_DIM));
                mvprintw(ty, mx, "  %d: %s  ", idx + 1, label);
                attroff(COLOR_PAIR(CP_DIM));
                mx += (int)strlen(label) + 8;
            }
        };

        draw_tab_btn(0, "Credentials");
        draw_tab_btn(1, "Session Cookie");
        draw_tab_btn(2, "Cookie File");
    }

    // Form content according to method
    int fy = by + 10;
    const int label_x = bx + 4;
    const int field_x = bx + 18;
    const int field_w = box_w - 22;

    // Clickable input rows (label + field)
    add_hitbox(fy, label_x, 1, field_x - label_x + field_w, MouseAction::LoginField, 0);
    if (login_method == 0)
        add_hitbox(fy + 2, label_x, 1, field_x - label_x + field_w, MouseAction::LoginField, 1);

    if (login_method == 0) {
        // Mode 0: Username & Password
        attron(active_field == 0 ? (COLOR_PAIR(CP_LABEL) | A_BOLD) : COLOR_PAIR(CP_DIM));
        mvprintw(fy, label_x, "%sUsername :", active_field == 0 ? "▶ " : "  ");
        attroff(COLOR_PAIR(CP_LABEL) | A_BOLD);

        attron(COLOR_PAIR(CP_VALUE) | (active_field == 0 ? A_UNDERLINE : 0));
        mvprintw(fy, field_x, "%-*s", field_w, user_buf.c_str());
        attroff(COLOR_PAIR(CP_VALUE) | (active_field == 0 ? A_UNDERLINE : 0));

        attron(active_field == 1 ? (COLOR_PAIR(CP_LABEL) | A_BOLD) : COLOR_PAIR(CP_DIM));
        mvprintw(fy + 2, label_x, "%sPassword :", active_field == 1 ? "▶ " : "  ");
        attroff(COLOR_PAIR(CP_LABEL) | A_BOLD);

        attron(COLOR_PAIR(CP_VALUE) | (active_field == 1 ? A_UNDERLINE : 0));
        std::string masked(pass_buf.size(), '*');
        mvprintw(fy + 2, field_x, "%-*s", field_w, masked.c_str());
        attroff(COLOR_PAIR(CP_VALUE) | (active_field == 1 ? A_UNDERLINE : 0));

        if (active_field == 0) move(fy, field_x + (int)user_buf.size());
        else move(fy + 2, field_x + (int)pass_buf.size());

    } else if (login_method == 1) {
        // Mode 1: Paste Cookie Token
        attron(COLOR_PAIR(CP_LABEL) | A_BOLD);
        mvprintw(fy, label_x, "▶ Cookie   :");
        attroff(COLOR_PAIR(CP_LABEL) | A_BOLD);

        attron(COLOR_PAIR(CP_VALUE) | A_UNDERLINE);
        mvprint_clip(fy, field_x, cookie_buf, field_w);
        attroff(COLOR_PAIR(CP_VALUE) | A_UNDERLINE);

        attron(COLOR_PAIR(CP_DIM));
        mvprintw(fy + 2, label_x + 2, "Tip: Copy _intra_42_session from browser DevTools -> Cookies");
        attroff(COLOR_PAIR(CP_DIM));

        move(fy, field_x + std::min((int)cookie_buf.size(), field_w - 1));

    } else {
        // Mode 2: Import Cookie File
        attron(COLOR_PAIR(CP_LABEL) | A_BOLD);
        mvprintw(fy, label_x, "▶ File Path:");
        attroff(COLOR_PAIR(CP_LABEL) | A_BOLD);

        std::string file_display = cookie_buf.empty() ? detected_file : cookie_buf;
        attron(COLOR_PAIR(CP_VALUE) | A_UNDERLINE);
        mvprint_clip(fy, field_x, file_display, field_w);
        attroff(COLOR_PAIR(CP_VALUE) | A_UNDERLINE);

        if (!detected_file.empty()) {
            attron(COLOR_PAIR(CP_SUCCESS));
            mvprintw(fy + 2, label_x + 2, "✔ Detected available cookie file: %s", detected_file.c_str());
            attroff(COLOR_PAIR(CP_SUCCESS));
        } else {
            attron(COLOR_PAIR(CP_DIM));
            mvprintw(fy + 2, label_x + 2, "Enter absolute path to your Netscape format cookie file");
            attroff(COLOR_PAIR(CP_DIM));
        }

        move(fy, field_x + std::min((int)file_display.size(), field_w - 1));
    }

    // Status or Error Banner
    int sy = by + 15;
    if (!error_msg.empty()) {
        attron(COLOR_PAIR(CP_FAIL) | A_BOLD);
        mvprint_clip(sy, bx + 4, "✖ " + error_msg, box_w - 8);
        attroff(COLOR_PAIR(CP_FAIL) | A_BOLD);
    } else if (loading) {
        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvprint_clip(sy, bx + 4, "⟳ " + status_msg, box_w - 8);
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
    } else {
        attron(COLOR_PAIR(CP_DIM));
        mvprint_clip(sy, bx + 4, "Ready. " + status_msg, box_w - 8);
        attroff(COLOR_PAIR(CP_DIM));
    }

    // Helper footer inside box
    int hy = by + 17;
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(hy, bx, bc.t_left);
    hline_box(hy, bx + 1, box_w - 2);
    mvaddstr(hy, bx + box_w - 1, bc.t_right);
    attroff(COLOR_PAIR(CP_BORDER));

    attron(COLOR_PAIR(CP_DIM));
    const char* legend = "[Tab] Field  │  [1/2/3] Mode  │  [Enter] Sign In  │  [Esc/Ctrl+C] Exit";
    mvprintw(hy + 1, bx + (box_w - (int)strlen(legend)) / 2, "%s", legend);
    attroff(COLOR_PAIR(CP_DIM));

    curs_set(1);
}

// ─────────────────────────────────────────────────────────────────────────────
// Interactive Theme Switcher Modal
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_theme_switcher(int active_idx) {
    const auto& themes = theme::get_all_themes();
    const int count = static_cast<int>(themes.size());
    const int box_w = 62;
    const int box_h = count + 6;
    const int bx = (cols_ - box_w) / 2;
    const int by = (rows_ - box_h) / 2;
    const auto& bc = get_border_chars();

    // Box Background
    for (int r = by; r < by + box_h; ++r) {
        attron(COLOR_PAIR(CP_DEFAULT));
        fill_row(r, bx, box_w);
        attroff(COLOR_PAIR(CP_DEFAULT));
    }

    // Outer border
    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    mvaddstr(by, bx + box_w - 1, bc.tr);
    mvaddstr(by + box_h - 1, bx, bc.bl);
    mvaddstr(by + box_h - 1, bx + box_w - 1, bc.br);
    for (int x = bx + 1; x < bx + box_w - 1; ++x) {
        mvaddstr(by, x, bc.h);
        mvaddstr(by + box_h - 1, x, bc.h);
    }
    for (int y = by + 1; y < by + box_h - 1; ++y) {
        mvaddstr(y, bx, bc.v);
        mvaddstr(y, bx + box_w - 1, bc.v);
    }

    // Header Title
    std::string title = " THEME CHOOSER ";
    mvaddstr(by, bx + (box_w - (int)title.size()) / 2, title.c_str());
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    // Subtitle instruction
    attron(COLOR_PAIR(CP_DIM));
    std::string sub = "Live preview on j/k • Enter: Save • Esc: Cancel";
    mvprint_clip(by + 1, bx + (box_w - (int)sub.size()) / 2, sub, box_w - 4);
    attroff(COLOR_PAIR(CP_DIM));

    // Divider under header
    int dy = by + 2;
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(dy, bx, bc.t_left);
    hline_box(dy, bx + 1, box_w - 2);
    mvaddstr(dy, bx + box_w - 1, bc.t_right);
    attroff(COLOR_PAIR(CP_BORDER));

    // Theme rows
    const std::string& current_saved = Config::get().theme;
    int saved_idx = theme::get_theme_index(current_saved);

    for (int i = 0; i < count; ++i) {
        int ry = by + 3 + i;
        bool is_selected = (i == active_idx);
        bool is_saved    = (i == saved_idx);
        add_hitbox(ry, bx + 1, 1, box_w - 2, MouseAction::ThemeRow, i);

        if (is_selected) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(ry, bx + 1, box_w - 2);
            mvprintw(ry, bx + 2, " ▶ [%2d] %-22s", i + 1, themes[i].display_name.c_str());
            if (is_saved) {
                mvprintw(ry, bx + 32, "[ACTIVE]");
            }
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            attron(COLOR_PAIR(CP_DEFAULT));
            fill_row(ry, bx + 1, box_w - 2);
            mvprintw(ry, bx + 4, "[%2d] %-22s", i + 1, themes[i].display_name.c_str());
            if (is_saved) {
                attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                mvprintw(ry, bx + 32, "[ACTIVE]");
                attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            }
            attroff(COLOR_PAIR(CP_DEFAULT));
        }

        // Color sample chips on the right
        attron(COLOR_PAIR(CP_ACCENT) | A_BOLD);
        mvaddstr(ry, bx + box_w - 17, "■");
        attroff(COLOR_PAIR(CP_ACCENT) | A_BOLD);

        attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
        mvaddstr(ry, bx + box_w - 13, "■");
        attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);

        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvaddstr(ry, bx + box_w - 9, "■");
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);

        attron(COLOR_PAIR(CP_FAIL) | A_BOLD);
        mvaddstr(ry, bx + box_w - 5, "■");
        attroff(COLOR_PAIR(CP_FAIL) | A_BOLD);
    }

    // Divider above footer
    int fy = by + 3 + count;
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(fy, bx, bc.t_left);
    hline_box(fy, bx + 1, box_w - 2);
    mvaddstr(fy, bx + box_w - 1, bc.t_right);
    attroff(COLOR_PAIR(CP_BORDER));

    // Footer note
    attron(COLOR_PAIR(CP_DIM));
    std::string footer = "Persists to " + Config::get_config_file_path();
    mvprint_clip(fy + 1, bx + (box_w - (int)footer.size()) / 2, footer, box_w - 4);
    attroff(COLOR_PAIR(CP_DIM));
}

// ─────────────────────────────────────────────────────────────────────────────
// Esc menu (pause menu) + Settings / Help / About sub-screens
// ─────────────────────────────────────────────────────────────────────────────
static void draw_modal_frame(int by, int bx, int box_h, int box_w,
                             const std::string& title) {
    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = by; r < by + box_h; ++r) fill_row(r, bx, box_w);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    hline_box(by, bx + 1, box_w - 2);
    mvaddstr(by, bx + box_w - 1, bc.tr);
    for (int r = by + 1; r < by + box_h - 1; ++r) {
        mvaddstr(r, bx, bc.v);
        mvaddstr(r, bx + box_w - 1, bc.v);
    }
    mvaddstr(by + box_h - 1, bx, bc.bl);
    hline_box(by + box_h - 1, bx + 1, box_w - 2);
    mvaddstr(by + box_h - 1, bx + box_w - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    if (!title.empty()) {
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprint_clip(by, bx + (box_w - (int)title.size()) / 2, title, box_w - 2);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    }
}

void Renderer::draw_main_menu(MenuState& menu) {
    const auto& items = menu.root_items;
    const int n = (int)items.size();
    int bw = 56;
    if (bw > cols_ - 4) bw = cols_ - 4;
    if (bw < 24) return;
    const int bh = n + 4;
    const int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    draw_modal_frame(by, bx, bh, bw, i18n::tr("menu_title"));

    for (int i = 0; i < n; ++i) {
        const int ry = by + 1 + i;
        const bool active = (i == menu.sel);
        add_hitbox(ry, bx + 1, 1, bw - 2, MouseAction::MenuItem, i);

        std::string text = items[i].label;
        if (!items[i].shortcut.empty())
            text = "[" + items[i].shortcut + "] " + text;

        if (active) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(ry, bx + 1, bw - 2);
            mvprint_clip(ry, bx + 3, "▶ " + text, bw - 5);
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            const int cp = items[i].enabled ? CP_VALUE : CP_DIM;
            attron(COLOR_PAIR(cp));
            mvprint_clip(ry, bx + 5, text, bw - 7);
            attroff(COLOR_PAIR(cp));
        }
    }

    attron(COLOR_PAIR(CP_DIM));
    const std::string footer = i18n::tr("menu_footer");
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 2);
    attroff(COLOR_PAIR(CP_DIM));
}

void Renderer::draw_settings(MenuState& menu) {
    const auto& items = menu.settings_items;
    const int n = (int)items.size();
    int bw = 68;
    if (bw > cols_ - 4) bw = cols_ - 4;
    if (bw < 30) return;
    int bh = n + 4;
    const int max_h = rows_ - 2;
    if (bh > max_h) bh = max_h;
    if (bh < 6) return;
    const int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    const int visible = bh - 2;
    if (menu.sel < menu.scroll) menu.scroll = menu.sel;
    if (menu.sel >= menu.scroll + visible) menu.scroll = menu.sel - visible + 1;
    if (menu.scroll < 0) menu.scroll = 0;
    if (n > visible && menu.scroll > n - visible) menu.scroll = n - visible;

    draw_modal_frame(by, bx, bh, bw, i18n::tr("settings_title"));

    for (int row = 0; row < visible; ++row) {
        const int idx = menu.scroll + row;
        if (idx >= n) break;
        const int ry = by + 1 + row;
        const MenuEntry& e = items[idx];
        const bool active = (idx == menu.sel);
        add_hitbox(ry, bx + 1, 1, bw - 2, MouseAction::SettingsRow, idx);

        const int base_cp = e.is_save ? CP_SUCCESS : (e.enabled ? CP_VALUE : CP_DIM);
        if (active) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(ry, bx + 1, bw - 2);
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            attron(COLOR_PAIR(CP_MODAL_BG));
            fill_row(ry, bx + 1, bw - 2);
            attroff(COLOR_PAIR(CP_MODAL_BG));
        }

        attron(COLOR_PAIR(base_cp) | (active ? A_BOLD : 0));
        mvprint_clip(ry, bx + 3, (active ? "▶ " : "  ") + e.label, bw / 2 + 4);
        attroff(COLOR_PAIR(base_cp) | (active ? A_BOLD : 0));

        if (!e.value.empty()) {
            std::string v = e.value;
            if (e.modified) v += " *";
            int vx = bx + bw - 2 - (int)v.size();
            if (vx < bx + bw / 2 + 2) vx = bx + bw / 2 + 2;
            const int vcp = e.modified ? CP_WARN : CP_LABEL;
            attron(COLOR_PAIR(vcp) | (active ? A_BOLD : 0));
            mvprint_clip(ry, vx, v, bx + bw - 1 - vx);
            attroff(COLOR_PAIR(vcp) | (active ? A_BOLD : 0));
        }
    }

    attron(COLOR_PAIR(CP_DIM));
    const std::string footer = i18n::tr(menu.dirty ? "settings_footer_dirty" : "settings_footer");
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 2);
    attroff(COLOR_PAIR(CP_DIM));
}

void Renderer::draw_help(MenuState& menu) {
    const auto& lines = i18n::help_lines();
    const int n = (int)lines.size();
    int bw = cols_ - 6;
    if (bw > 78) bw = 78;
    if (bw < 30) bw = cols_ - 2;
    int bh = rows_ - 4;
    if (bh < 6) bh = rows_ - 2;
    const int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    const int visible = bh - 2;
    if (menu.scroll < 0) menu.scroll = 0;
    if (n > visible && menu.scroll > n - visible) menu.scroll = n - visible;

    draw_modal_frame(by, bx, bh, bw, i18n::tr("help_title"));

    for (int row = 0; row < visible; ++row) {
        const int idx = menu.scroll + row;
        if (idx >= n) break;
        const int ry = by + 1 + row;
        const std::string& ln = lines[idx];
        const bool header = !ln.empty() && ln[0] != ' ';
        const int cp = header ? CP_TITLE : CP_VALUE;
        attron(COLOR_PAIR(cp) | (header ? A_BOLD : 0));
        mvprint_clip(ry, bx + 2, ln, bw - 4);
        attroff(COLOR_PAIR(cp) | (header ? A_BOLD : 0));
    }

    attron(COLOR_PAIR(CP_DIM));
    const std::string footer = i18n::tr("help_footer");
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 2);
    attroff(COLOR_PAIR(CP_DIM));
}

void Renderer::draw_about() {
    std::vector<std::pair<std::string, std::string>> rows = {
        {i18n::tr("about_version"), APP_VERSION},
        {i18n::tr("about_repo"),    APP_REPO[0] ? std::string(APP_REPO) : std::string("—")},
        {i18n::tr("about_license"), APP_LICENSE},
        {i18n::tr("about_config"),  Config::get_config_file_path()},
        {i18n::tr("about_data"),    Config::get_data_dir()},
        {i18n::tr("about_curl"),    std::string(curl_version())},
        {i18n::tr("about_ncurses"), std::string(curses_version())},
    };

    int bw = 68;
    if (bw > cols_ - 4) bw = cols_ - 4;
    if (bw < 30) return;
    const int bh = (int)rows.size() + 4;
    const int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    draw_modal_frame(by, bx, bh, bw, i18n::tr("about_title"));

    for (int i = 0; i < (int)rows.size(); ++i) {
        const int ry = by + 1 + i;
        attron(COLOR_PAIR(CP_LABEL) | A_BOLD);
        mvprint_clip(ry, bx + 3, rows[i].first, 20);
        attroff(COLOR_PAIR(CP_LABEL) | A_BOLD);
        attron(COLOR_PAIR(CP_VALUE));
        mvprint_clip(ry, bx + 24, rows[i].second, bw - 26);
        attroff(COLOR_PAIR(CP_VALUE));
    }

    attron(COLOR_PAIR(CP_DIM));
    const std::string footer = i18n::tr("about_footer");
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 2);
    attroff(COLOR_PAIR(CP_DIM));
}

void Renderer::draw_confirm_dialog(const MenuState& menu) {
    int bw = 58;
    if (bw > cols_ - 4) bw = cols_ - 4;
    if (bw < 30) return;
    const int bh = 7;
    const int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    draw_modal_frame(by, bx, bh, bw, menu.confirm_title);

    attron(COLOR_PAIR(CP_VALUE));
    mvprint_clip(by + 2, bx + 3, menu.confirm_msg, bw - 6);
    attroff(COLOR_PAIR(CP_VALUE));

    const std::string yes = "[Y] " + i18n::tr("yes");
    const std::string no  = "[N] " + i18n::tr("no");
    const int yx = bx + bw / 2 - 12;
    const int nx = bx + bw / 2 + 4;
    add_hitbox(by + 4, yx, 1, (int)yes.size(), MouseAction::ConfirmChoice, 0);
    add_hitbox(by + 4, nx, 1, (int)no.size(),  MouseAction::ConfirmChoice, 1);

    attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
    mvprint_clip(by + 4, yx, yes, bw);
    attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
    attron(COLOR_PAIR(CP_FAIL) | A_BOLD);
    mvprint_clip(by + 4, nx, no, bw);
    attroff(COLOR_PAIR(CP_FAIL) | A_BOLD);

    attron(COLOR_PAIR(CP_DIM));
    const std::string footer = i18n::tr("confirm_footer");
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 2);
    attroff(COLOR_PAIR(CP_DIM));
}

void Renderer::draw_edit_popup(const MenuState& menu) {
    int bw = 52;
    if (bw > cols_ - 4) bw = cols_ - 4;
    if (bw < 24) return;
    const int bh = 6;
    const int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    draw_modal_frame(by, bx, bh, bw, menu.edit_title);

    attron(COLOR_PAIR(CP_ROW_SEL));
    fill_row(by + 2, bx + 2, bw - 4);
    attroff(COLOR_PAIR(CP_ROW_SEL));
    attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
    mvprint_clip(by + 2, bx + 3, menu.edit_value + "_", bw - 6);
    attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

    attron(COLOR_PAIR(CP_DIM));
    const std::string footer = i18n::tr("edit_footer");
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 2);
    attroff(COLOR_PAIR(CP_DIM));
}

// ─────────────────────────────────────────────────────────────────────────────
// Subject (PDF) preview panel / modal + project action menu
// ─────────────────────────────────────────────────────────────────────────────
static std::string path_basename(const std::string& p) {
    size_t s = p.find_last_of('/');
    return (s == std::string::npos) ? p : p.substr(s + 1);
}

Renderer::ImageBox Renderer::draw_subject_panel(const SubjectPreview& pv,
                                                int x, int top, int bottom, int w) {
    ImageBox box;
    if (w < 14 || bottom - top < 6) return box;

    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, x, bc.tl);
    hline_box(top, x + 1, w - 2);
    mvaddstr(top, x + w - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) {
        mvaddstr(r, x, bc.v);
        fill_row(r, x + 1, w - 2);
        mvaddstr(r, x + w - 1, bc.v);
    }
    mvaddstr(bottom, x, bc.bl);
    hline_box(bottom, x + 1, w - 2);
    mvaddstr(bottom, x + w - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER));

    std::string title = " SUBJECT PREVIEW ";
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(top, x + (w - (int)title.size()) / 2, title, w - 2);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    int cx = x + 2;
    int cw = w - 4;

    if (pv.path.empty()) {
        attron(COLOR_PAIR(CP_DIM));
        mvprint_clip(top + 2, cx, "No downloaded subject for this project.", cw);
        mvprint_clip(top + 3, cx, "Press [Enter] to download it.", cw);
        attroff(COLOR_PAIR(CP_DIM));
        return box;
    }

    std::string head = path_basename(pv.path);
    if (pv.page_count > 0)
        head += "  (" + std::to_string(pv.page + 1) + "/" + std::to_string(pv.page_count) + ")";
    attron(COLOR_PAIR(CP_LABEL));
    mvprint_clip(top + 1, cx, head, cw);
    attroff(COLOR_PAIR(CP_LABEL));

    if (pv.loading) {
        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvprint_clip(top + 3, cx, "⟳ Rendering page…", cw);
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
        return box;
    }
    if (!pv.error.empty() && !pv.ready) {
        attron(COLOR_PAIR(CP_FAIL));
        mvprint_clip(top + 3, cx, "✖ " + pv.error, cw);
        attroff(COLOR_PAIR(CP_FAIL));
        return box;
    }

    if (pv.is_image) {
        box.col     = x + 1;
        box.row     = top + 2;
        box.w       = w - 2;
        box.h       = bottom - box.row - 1;
        box.visible = (box.w >= 8 && box.h >= 4);
        if (!box.visible) {
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(top + 3, cx, "[page image — widen panel]", cw);
            attroff(COLOR_PAIR(CP_DIM));
        }
    } else {
        int max_lines = bottom - (top + 2) - 1;
        for (int i = 0; i < max_lines && i < (int)pv.text_lines.size(); ++i) {
            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(top + 2 + i, cx, pv.text_lines[i], cw);
            attroff(COLOR_PAIR(CP_VALUE));
        }
    }
    return box;
}

Renderer::ImageBox Renderer::draw_subject_modal(const SubjectPreview& pv, int scroll) {
    ImageBox box;

    const int max_bw = std::min(cols_ - 4, 120);
    const int max_bh = rows_ - 4;
    if (max_bw < 30 || max_bh < 10) return box;

    // Interior limits (border + 1 cell padding on each side, and the fixed
    // header/divider/footer chrome rows).
    const int max_cw = std::max(1, max_bw - 4);
    const int max_ch = std::max(1, max_bh - 5);

    // Size the modal to its content so it looks snug instead of a fixed slab.
    int content_w = max_cw;
    int content_h = max_ch;

    if (pv.is_image && !pv.image_key.empty()) {
        int iw = 0, ih = 0;
        if (image_renderer::image_dimensions(pv.image_key, iw, ih) && iw > 0 && ih > 0) {
            // Terminal cells are ~1:2 (w:h), so a cell-accurate fit is
            // cols ≈ rows * 2 * (img_w / img_h).
            content_h = max_ch;
            content_w = static_cast<int>(
                static_cast<long long>(content_h) * 2 * iw / ih);
            if (content_w > max_cw) {
                content_w = max_cw;
                content_h = static_cast<int>(
                    static_cast<long long>(content_w) * ih / (2 * iw));
            }
            content_w = std::max(1, content_w);
            content_h = std::max(1, content_h);
        }
    } else if (!pv.text_lines.empty()) {
        size_t longest = 0;
        for (const auto& line : pv.text_lines)
            longest = std::max(longest, line.size());
        content_w = std::clamp(static_cast<int>(longest), 1, max_cw);
        content_h = std::clamp(static_cast<int>(pv.text_lines.size()), 1, max_ch);
    }

    int bw = std::clamp(content_w + 4, 30, max_bw);
    int bh = std::clamp(content_h + 5, 10, max_bh);
    int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;

    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = by; r <= by + bh; ++r) fill_row(r, bx, bw);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    hline_box(by, bx + 1, bw - 2);
    mvaddstr(by, bx + bw - 1, bc.tr);
    for (int r = by + 1; r < by + bh; ++r) {
        mvaddstr(r, bx, bc.v);
        mvaddstr(r, bx + bw - 1, bc.v);
    }
    mvaddstr(by + bh, bx, bc.bl);
    hline_box(by + bh, bx + 1, bw - 2);
    mvaddstr(by + bh, bx + bw - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    std::string title = " SUBJECT PREVIEW ";
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(by, bx + (bw - (int)title.size()) / 2, title, bw - 2);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    attron(COLOR_PAIR(CP_LABEL));
    std::string head = path_basename(pv.path);
    if (pv.page_count > 0)
        head += "  [" + std::to_string(pv.page + 1) + "/" + std::to_string(pv.page_count) + "]";
    mvprint_clip(by + 1, bx + 2, head, bw - 4);
    attroff(COLOR_PAIR(CP_LABEL));

    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(by + 2, bx, bc.t_left);
    hline_box(by + 2, bx + 1, bw - 2);
    mvaddstr(by + 2, bx + bw - 1, bc.t_right);
    attroff(COLOR_PAIR(CP_BORDER));

    int cx = bx + 2;
    int cw = bw - 4;
    int ctop = by + 3;
    int cbot = by + bh - 2; // leave footer line

    if (pv.loading) {
        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvprint_clip(ctop + 2, cx, "⟳ Rendering page…", cw);
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
    } else if (!pv.error.empty() && !pv.ready) {
        attron(COLOR_PAIR(CP_FAIL));
        mvprint_clip(ctop + 2, cx, "✖ " + pv.error, cw);
        attroff(COLOR_PAIR(CP_FAIL));
    } else if (pv.is_image) {
        box.col     = bx + 1;
        box.row     = ctop;
        box.w       = bw - 2;
        box.h       = cbot - ctop;
        box.visible = (box.w >= 10 && box.h >= 4);
    } else {
        int max_lines = cbot - ctop;
        int total = (int)pv.text_lines.size();
        if (scroll < 0) scroll = 0;
        if (scroll > std::max(0, total - max_lines)) scroll = std::max(0, total - max_lines);
        for (int i = 0; i < max_lines && (scroll + i) < total; ++i) {
            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(ctop + i, cx, pv.text_lines[scroll + i], cw);
            attroff(COLOR_PAIR(CP_VALUE));
        }
    }

    attron(COLOR_PAIR(CP_DIM));
    std::string footer = "[n/p] Page  │  [j/k] Scroll  │  [Esc] Close";
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 4);
    attroff(COLOR_PAIR(CP_DIM));

    return box;
}

void Renderer::draw_action_menu(const std::vector<std::pair<std::string, bool>>& items,
                                int sel) {
    if (items.empty()) return;

    int n  = (int)items.size();
    int bw = std::min(cols_ - 4, 52);
    int bh = n + 4;
    if (bw < 24) return;
    int bx = (cols_ - bw) / 2;
    int by = (rows_ - bh) / 2;
    if (by < 0) by = 0;

    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = by; r <= by + bh; ++r) fill_row(r, bx, bw);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    hline_box(by, bx + 1, bw - 2);
    mvaddstr(by, bx + bw - 1, bc.tr);
    for (int r = by + 1; r < by + bh; ++r) {
        mvaddstr(r, bx, bc.v);
        mvaddstr(r, bx + bw - 1, bc.v);
    }
    mvaddstr(by + bh, bx, bc.bl);
    hline_box(by + bh, bx + 1, bw - 2);
    mvaddstr(by + bh, bx + bw - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    std::string title = " PROJECT ACTIONS ";
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(by, bx + (bw - (int)title.size()) / 2, title, bw - 2);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    for (int i = 0; i < n; ++i) {
        bool enabled = items[i].second;
        bool active  = (i == sel);
        int ry = by + 1 + i;
        add_hitbox(ry, bx + 1, 1, bw - 2, MouseAction::ActionRow, i);
        if (active && enabled) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(ry, bx + 1, bw - 2);
            mvprintw(ry, bx + 2, " ▶ %d. %s", i + 1, items[i].first.c_str());
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            attron(enabled ? COLOR_PAIR(CP_VALUE) : COLOR_PAIR(CP_DIM));
            mvprintw(ry, bx + (active ? 2 : 4), "%s%d. %s", active ? "▶ " : "  ",
                     i + 1, items[i].first.c_str());
            attroff(enabled ? COLOR_PAIR(CP_VALUE) : COLOR_PAIR(CP_DIM));
        }
    }

    attron(COLOR_PAIR(CP_DIM));
    std::string footer = "[j/k] Move | [Enter] Pick | Click | [Esc] Quit";
    mvprint_clip(by + bh - 1, bx + (bw - (int)footer.size()) / 2, footer, bw - 4);
    attroff(COLOR_PAIR(CP_DIM));
}

// ─────────────────────────────────────────────────────────────────────────────
// Tab 4: Holygraph Roadmap (Milestone Tree)
// ─────────────────────────────────────────────────────────────────────────────
struct TreeRow {
    bool is_milestone;
    int  m_idx;
    int  p_idx;
};

static std::vector<TreeRow> build_visible_tree(const std::vector<Milestone>& roadmap) {
    std::vector<TreeRow> rows;
    for (int m = 0; m < (int)roadmap.size(); ++m) {
        rows.push_back({true, m, -1});
        if (roadmap[m].expanded) {
            for (int pr = 0; pr < (int)roadmap[m].projects.size(); ++pr) {
                rows.push_back({false, m, pr});
            }
        }
    }
    return rows;
}

void Renderer::draw_roadmap(Profile& p, int sel, int top, int bottom, int left_w,
                            bool preview_panel, const SubjectPreview& pv) {
    draw_profile_panel(p, top, bottom, left_w);

    int rx = left_w;
    int full_rw = cols_ - rx;
    if (full_rw < 10) return;

    int panel_w = 0;
    if (preview_panel) {
        panel_w = std::clamp(full_rw * 45 / 100, 30, 64);
        if (full_rw - panel_w < 30) panel_w = 0;
    }
    int rw = full_rw - panel_w;

    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, rx + rw - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) mvaddstr(r, rx + rw - 1, bc.v);
    mvaddstr(bottom, rx + rw - 1, bc.br);
    hline_box(bottom, rx, rw - 1);
    attroff(COLOR_PAIR(CP_BORDER));

    int row = top;

    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    std::string r_title = "◆ 42 Holygraph Curriculum Roadmap (" + std::to_string(p.roadmap.size()) + " Milestones)";
    mvprint_clip(row, rx + 2, r_title, rw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    row++;

    attron(COLOR_PAIR(CP_DIM));
    std::string hint = "Space: Toggle Milestone  │  Enter: Project Actions  │  p: Preview  │  d/s: Download";
    mvprint_clip(row, rx + 2, hint, rw - 4);
    attroff(COLOR_PAIR(CP_DIM));
    row++;

    attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    fill_row(row, rx + 2, rw - 4);
    std::string hdr = pad("   CURSUS TREE & PROJECTS", rw - 28) + pad("EST. TIME", 12) + "STATUS";
    mvprint_clip(row, rx + 2, hdr, rw - 4);
    attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    row++;

    auto visible = build_visible_tree(p.roadmap);
    int total = (int)visible.size();

    if (total == 0) {
        attron(COLOR_PAIR(CP_DIM));
        mvprint_clip(row + 2, rx + 4, "No roadmap data available. Press 'r' to sync data from intra.", rw - 8);
        attroff(COLOR_PAIR(CP_DIM));
        return;
    }

    if (sel < 0) sel = 0;
    if (sel >= total) sel = total - 1;

    int preview_h = 3;
    int max_visible = bottom - row - preview_h - 1;
    if (max_visible < 3) max_visible = 3;

    int start = 0;
    if (sel >= max_visible) {
        start = sel - max_visible + 1;
    }

    for (int i = start; i < total && (row < bottom - preview_h); ++i) {
        const auto& item = visible[i];
        bool is_sel = (i == sel);
        add_hitbox(row, rx + 2, 1, rw - 4, MouseAction::ListRow, i);

        if (item.is_milestone) {
            const auto& ms = p.roadmap[item.m_idx];
            std::string icon = ms.expanded ? "▼" : "▶";
            std::string title = icon + " " + ms.name + " (" + std::to_string(ms.projects.size()) + " projects)";

            if (is_sel) {
                attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                fill_row(row, rx + 2, rw - 4);
                mvprint_clip(row, rx + 2, " ▶ " + title, rw - 4);
                attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            } else {
                attron(COLOR_PAIR(CP_ACCENT) | A_BOLD);
                mvprint_clip(row, rx + 4, title, rw - 6);
                attroff(COLOR_PAIR(CP_ACCENT) | A_BOLD);
            }
        } else {
            const auto& pr = p.roadmap[item.m_idx].projects[item.p_idx];
            bool is_last = (item.p_idx + 1 == (int)p.roadmap[item.m_idx].projects.size());
            std::string branch = is_last ? "   └── " : "   ├── ";

            std::string badge;
            int badge_cp = CP_DIM;
            if (pr.state == "done") {
                badge = "[DONE " + (!pr.final_mark.empty() ? pr.final_mark : "100") + "]";
                badge_cp = CP_SUCCESS;
            } else if (pr.state == "in_progress") {
                badge = "[IN PROGRESS]";
                badge_cp = CP_IN_PROG;
            } else if (pr.state == "available") {
                badge = "[AVAILABLE]";
                badge_cp = CP_WARN;
            } else {
                badge = "[LOCKED]";
                badge_cp = CP_DIM;
            }

            std::string dur = pr.duration.empty() ? "—" : pr.duration;
            int name_w = std::max(5, rw - 38);

            if (is_sel) {
                attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                fill_row(row, rx + 2, rw - 4);
                mvprint_clip(row, rx + 2, " ▶ " + branch.substr(3), 7);
                mvprint_clip(row, rx + 9, pr.name, name_w);
                mvprint_clip(row, rx + rw - 24, dur, 10);
                mvprint_clip(row, rx + rw - 14, badge, 12);
                attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            } else {
                attron(COLOR_PAIR(CP_DIM));
                mvprint_clip(row, rx + 4, branch, 7);
                attroff(COLOR_PAIR(CP_DIM));

                attron(COLOR_PAIR(CP_VALUE));
                mvprint_clip(row, rx + 11, pr.name, name_w);
                attroff(COLOR_PAIR(CP_VALUE));

                attron(COLOR_PAIR(CP_DIM));
                mvprint_clip(row, rx + rw - 24, dur, 10);
                attroff(COLOR_PAIR(CP_DIM));

                attron(COLOR_PAIR(badge_cp) | A_BOLD);
                mvprint_clip(row, rx + rw - 14, badge, 12);
                attroff(COLOR_PAIR(badge_cp) | A_BOLD);
            }
        }
        row++;
    }

    // Detail Preview Box at bottom
    if (sel >= 0 && sel < total && bottom - preview_h > top) {
        int drow = bottom - preview_h;
        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(drow, rx + 2, bc.tl);
        hline_box(drow, rx + 3, rw - 6);
        mvaddstr(drow, rx + rw - 3, bc.tr);

        mvaddstr(drow + 1, rx + 2, bc.v);
        fill_row(drow + 1, rx + 3, rw - 6);
        mvaddstr(drow + 1, rx + rw - 3, bc.v);

        mvaddstr(drow + 2, rx + 2, bc.bl);
        hline_box(drow + 2, rx + 3, rw - 6);
        mvaddstr(drow + 2, rx + rw - 3, bc.br);
        attroff(COLOR_PAIR(CP_BORDER));

        const auto& cur = visible[sel];
        std::string detail;
        if (cur.is_milestone) {
            const auto& ms = p.roadmap[cur.m_idx];
            detail = "Milestone: " + ms.name + "  │  " +
                     std::to_string(ms.projects.size()) + " Projects  │  Press [Space] to " +
                     (ms.expanded ? "collapse" : "expand");
        } else {
            const auto& pr = p.roadmap[cur.m_idx].projects[cur.p_idx];
            detail = "Project: " + pr.name + "  │  XP: " + pr.difficulty +
                     "  │  Duration: " + pr.duration +
                     "  │  Press [d/s] to download PDF subject";
        }
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprint_clip(drow + 1, rx + 4, detail, rw - 8);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    }

    if (panel_w > 0)
        preview_img_ = draw_subject_panel(pv, rx + rw, top, bottom, panel_w);
}

// ─────────────────────────────────────────────────────────────────────────────
// Tab 5: Cluster Students & Workstations (4 Clusters x 8x6 Workstation Grid)
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_cluster(const Profile& p, int room, int sel, int top, int bottom, int left_w) {
    draw_profile_panel(p, top, bottom, left_w);

    int rx = left_w;
    int rw = cols_ - rx;
    if (rw < 10) return;

    const auto& bc = get_border_chars();

    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, cols_ - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) mvaddstr(r, cols_ - 1, bc.v);
    mvaddstr(bottom, cols_ - 1, bc.br);
    hline_box(bottom, rx, rw - 1);
    attroff(COLOR_PAIR(CP_BORDER));

    int row = top;

    // Header title
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    std::string c_title = "◆ Campus Cluster Workstations (8x6 Desk Grid)";
    mvprint_clip(row, rx + 2, c_title, rw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    row++;

    // 4 Cluster Room tabs
    int tab_x = rx + 2;
    for (int r = 0; r < 4; ++r) {
        int in_room = count_students_in_room(p.cluster_students, r);
        std::string room_label = "[ Cluster " + std::to_string(r + 1) + " (" + std::to_string(in_room) + ") ]";
        bool is_active_room = (r == room);
        add_hitbox(row, tab_x, 1, (int)room_label.size(), MouseAction::ClusterRoom, r);

        if (is_active_room) {
            attron(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
            mvprint_clip(row, tab_x, room_label, rw - (tab_x - rx) - 2);
            attroff(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
        } else {
            attron(COLOR_PAIR(CP_DIM));
            mvprint_clip(row, tab_x, room_label, rw - (tab_x - rx) - 2);
            attroff(COLOR_PAIR(CP_DIM));
        }
        tab_x += static_cast<int>(room_label.size()) + 2;
    }
    row++;

    // Navigation hint
    attron(COLOR_PAIR(CP_DIM));
    std::string hint = "[h/j/k/l] Desks  │  [/] or [c] Cluster (1-4)  │  [y] Copy login  │  [r] Refresh";
    mvprint_clip(row, rx + 2, hint, rw - 4);
    attroff(COLOR_PAIR(CP_DIM));
    row++;

    bool has_sel = (sel >= 0 && sel < cluster_layout::CELLS);
    if (sel >= cluster_layout::CELLS) sel = cluster_layout::CELLS - 1;
    int sel_r = has_sel ? cluster_layout::row_of(sel) : -1;
    int sel_s = has_sel ? cluster_layout::seat_of(sel) : -1;

    // 8x6 Workstation Grid (adaptive width so seats never overflow the pane)
    int label_w = 6; // "Row 1 "
    int avail_w = rw - 4 - label_w;
    int cell_w  = avail_w / cluster_layout::SEATS;
    if (cell_w > 14) cell_w = 14;
    if (cell_w < 5) {
        // Drop the row labels to buy horizontal room.
        label_w = 0;
        avail_w = rw - 4;
        cell_w  = avail_w / cluster_layout::SEATS;
    }
    bool grid_fits = (cell_w >= 5 && cell_w * cluster_layout::SEATS <= avail_w);
    int grid_x = rx + 2 + label_w;

    // Vertical budget: fit all 8 rows, shrinking or dropping the inspector card
    // on short terminals. Scrolls around the selection if even 8 rows don't fit.
    int grid_top    = row + 1; // header line sits on `row`
    int space_below = bottom - grid_top;
    int card_h      = 10;
    if (space_below - card_h < cluster_layout::ROWS) {
        card_h = space_below - cluster_layout::ROWS;
        if (card_h < 5) card_h = 0;
    }
    int grid_h = std::min(cluster_layout::ROWS, space_below - card_h);
    if (grid_h < 1) grid_h = 1;
    int start_r = 0;
    if (sel_r >= grid_h) start_r = sel_r - grid_h + 1;
    if (start_r > cluster_layout::ROWS - grid_h)
        start_r = cluster_layout::ROWS - grid_h;

    if (!grid_fits) {
        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvprint_clip(row, rx + 2,
                     "Terminal too narrow for the 8×6 desk grid — widen the window.", rw - 4);
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
        row++;
    } else {
        // Grid column headers: Seat 1 .. Seat 6
        attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        fill_row(row, rx + 2, rw - 4);
        if (label_w > 0) mvprint_clip(row, rx + 2, " DESK ", label_w);
        for (int s = 0; s < cluster_layout::SEATS; ++s) {
            std::string seat_hdr = "Seat " + std::to_string(s + 1);
            mvprint_clip(row, grid_x + s * cell_w, seat_hdr, cell_w - 1);
        }
        attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        row++;

        // Render the visible window of the 8x6 grid
        for (int rr = 0; rr < grid_h; ++rr) {
            int r = start_r + rr;
            int cur_y = grid_top + rr;
            if (cur_y >= bottom) break;

            // Row label
            if (label_w > 0) {
                attron(COLOR_PAIR(CP_LABEL) | A_BOLD);
                mvprint_clip(cur_y, rx + 2, "Row " + std::to_string(r + 1) + " ", label_w);
                attroff(COLOR_PAIR(CP_LABEL) | A_BOLD);
            }

            for (int s = 0; s < cluster_layout::SEATS; ++s) {
                int desk_idx = cluster_layout::index(r, s);
                bool is_selected = (desk_idx == sel);
                int col_x = grid_x + s * cell_w;
                add_hitbox(cur_y, col_x, 1, cell_w - 1, MouseAction::ClusterDesk, desk_idx);

                const auto* cs = get_student_at_desk(p.cluster_students, room, r, s);
                if (cs) {
                    if (is_selected) {
                        attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                        fill_row(cur_y, col_x, cell_w - 1);
                        attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                    }

                    // Green online indicator for every occupied desk.
                    attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                    mvaddstr(cur_y, col_x, "●");
                    attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);

                    std::string text = "@" + cs->login;
                    if (is_selected) {
                        attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                        mvprint_clip(cur_y, col_x + 2, text, cell_w - 3);
                        attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                    } else {
                        attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                        mvprint_clip(cur_y, col_x + 2, text, cell_w - 3);
                        attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                    }
                } else {
                    std::string text = "○ r" + std::to_string(r + 1) + "s" + std::to_string(s + 1);
                    if (is_selected) {
                        attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                        fill_row(cur_y, col_x, cell_w - 1);
                        mvprint_clip(cur_y, col_x, text, cell_w - 1);
                        attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
                    } else {
                        attron(COLOR_PAIR(CP_DIM));
                        mvprint_clip(cur_y, col_x, text, cell_w - 1);
                        attroff(COLOR_PAIR(CP_DIM));
                    }
                }
            }
        }
    }

    // Workstation Inspector Card at bottom (dropped on very short terminals)
    if (card_h >= 5) {
        int drow = bottom - card_h;
        attron(COLOR_PAIR(CP_BORDER));
        mvaddstr(drow, rx + 2, bc.tl);
        hline_box(drow, rx + 3, rw - 6);
        mvaddstr(drow, rx + rw - 3, bc.tr);

        for (int ch = 1; ch < card_h; ++ch) {
            mvaddstr(drow + ch, rx + 2, bc.v);
            fill_row(drow + ch, rx + 3, rw - 6);
            mvaddstr(drow + ch, rx + rw - 3, bc.v);
        }

        mvaddstr(drow + card_h, rx + 2, bc.bl);
        hline_box(drow + card_h, rx + 3, rw - 6);
        mvaddstr(drow + card_h, rx + rw - 3, bc.br);
        attroff(COLOR_PAIR(CP_BORDER));

        std::string expected_host = has_sel
            ? cluster_layout::host_of(room, sel_r, sel_s)
            : "";

        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        std::string card_hdr = has_sel
            ? " LIVE WORKSTATION INSPECTOR: " + expected_host + " "
            : " LIVE WORKSTATION INSPECTOR ";
        mvprint_clip(drow, rx + 4, card_hdr, rw - 8);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

        if (!has_sel) {
            attron(COLOR_PAIR(CP_DIM));
            std::string msg = "No students online in Cluster " +
                              std::to_string(room + 1) +
                              ". Use [ / ] or [c] to switch cluster.";
            mvprint_clip(drow + 2, rx + 4, msg, rw - 8);
            attroff(COLOR_PAIR(CP_DIM));
        } else {
        // Photo border frame (adaptive so it never overflows on narrow terminals).
        ClusterPhotoBox box = cluster_photo_box(rx, rw, drow, card_h);
        const int pfx = box.pfx;
        const int pfy = box.pfy;
        const int pfw = box.pfw;
        const int pfh = box.pfh;

        if (box.visible) {
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(pfy, pfx, bc.tl);
            hline_box(pfy, pfx + 1, pfw - 2);
            mvaddstr(pfy, pfx + pfw - 1, bc.tr);

            for (int h = 1; h < pfh; ++h) {
                mvaddstr(pfy + h, pfx, bc.v);
                fill_row(pfy + h, pfx + 1, pfw - 2);
                mvaddstr(pfy + h, pfx + pfw - 1, bc.v);
            }

            mvaddstr(pfy + pfh, pfx, bc.bl);
            hline_box(pfy + pfh, pfx + 1, pfw - 2);
            mvaddstr(pfy + pfh, pfx + pfw - 1, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));
        }

        const auto* cs = get_student_at_desk(p.cluster_students, room, sel_r, sel_s);
        int text_x = box.visible ? (pfx + pfw + 3) : pfx;
        int text_w = rw - (text_x - rx) - 4;

        if (cs) {
            if (box.visible && !image_renderer::has_image(cs->cdn_uri)) {
                attron(COLOR_PAIR(CP_DIM));
                std::string lbl = "[FETCHING...]";
                mvprint_clip(pfy + 3, pfx + (pfw - (int)lbl.size()) / 2, lbl, pfw - 2);
                attroff(COLOR_PAIR(CP_DIM));
            }

            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprint_clip(pfy + 1, text_x, "◆ @" + cs->login + " (Active Student)", text_w);
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            attron(COLOR_PAIR(CP_LABEL));
            mvprint_clip(pfy + 2, text_x, "Student     :", 15);
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
            mvprint_clip(pfy + 2, text_x + 15,
                         cs->full_name.empty() ? "(cargando…)" : cs->full_name, text_w - 15);
            attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

            attron(COLOR_PAIR(CP_LABEL));
            mvprint_clip(pfy + 3, text_x, "Workstation :", 15);
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(pfy + 3, text_x + 15, cs->host + " (Cluster " + std::to_string(room + 1) + ", Row " + std::to_string(sel_r + 1) + ", Seat " + std::to_string(sel_s + 1) + ")", text_w - 15);
            attroff(COLOR_PAIR(CP_VALUE));

            attron(COLOR_PAIR(CP_LABEL));
            mvprint_clip(pfy + 4, text_x, "Active Since:", 15);
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(pfy + 4, text_x + 15, format_active_since(cs->begin_at), text_w - 15);
            attroff(COLOR_PAIR(CP_VALUE));

            attron(COLOR_PAIR(CP_LABEL));
            mvprint_clip(pfy + 5, text_x, "Presence    :", 15);
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            mvprint_clip(pfy + 5, text_x + 15, "● OCCUPIED & ACTIVE", text_w - 15);
            attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
        }
        } // has_sel
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Dashboard: compact cluster minimap + hover inspector
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_cluster_minimap(const Profile& p, int top, int bottom,
                                    int panel_w, int hovered, int room_override) {
    if (bottom - top < 3 || panel_w < 20) return;

    const auto& bc = get_border_chars();

    int room = room_override;
    if (room < 0 || room >= 4) {
        room = room_from_location(p.location);
        if (room < 0 || room >= 4) room = busiest_room(p.cluster_students);
    }
    int online = count_students_in_room(p.cluster_students, room);

    // Frame
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, 0, bc.tl);
    hline_box(top, 1, panel_w - 2);
    mvaddstr(top, panel_w - 1, bc.tr);
    for (int r = top + 1; r < bottom; ++r) {
        mvaddstr(r, 0, bc.v);
        fill_row(r, 1, panel_w - 2);
        mvaddstr(r, panel_w - 1, bc.v);
    }
    mvaddstr(bottom, 0, bc.bl);
    hline_box(bottom, 1, panel_w - 2);
    mvaddstr(bottom, panel_w - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER));

    // Title + clickable room pills (row top)
    {
        std::string title = " ◆ " + i18n::tr("minimap_title");
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprint_clip(top, 2, title, panel_w - 4);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

        if (panel_w >= 30) {
            int px = panel_w - 14;
            for (int r = 0; r < 4; ++r) {
                int x = px + r * 3;
                add_hitbox(top, x, 1, 2, MouseAction::MiniRoom, r);
                if (r == room) {
                    attron(COLOR_PAIR(CP_PILL_ACCENT) | A_BOLD);
                    mvprint_clip(top, x, "C" + std::to_string(r + 1), 2);
                    attroff(COLOR_PAIR(CP_PILL_ACCENT) | A_BOLD);
                } else {
                    attron(COLOR_PAIR(CP_DIM));
                    mvprint_clip(top, x, "C" + std::to_string(r + 1), 2);
                    attroff(COLOR_PAIR(CP_DIM));
                }
            }
        }
    }

    // Online badge (row top + 1)
    {
        attron(COLOR_PAIR(CP_WARN) | A_BOLD);
        mvprint_clip(top + 1, 2, std::to_string(online) + " " + i18n::tr("minimap_online"), panel_w - 4);
        attroff(COLOR_PAIR(CP_WARN) | A_BOLD);
    }

    // Seat header (row top + 2)
    int inner_w = panel_w - 2;
    int label_w = 3;
    int cell_w  = (inner_w - label_w) / cluster_layout::SEATS;
    if (cell_w > 9) cell_w = 9;
    if (cell_w < 3) {
        label_w = 0;
        cell_w  = inner_w / cluster_layout::SEATS;
    }
    if (cell_w < 2) cell_w = 2;
    int grid_x = 1 + label_w;

    if (label_w > 0) {
        attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        mvprintw(top + 2, 1, "DSK");
        attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    }
    for (int s = 0; s < cluster_layout::SEATS; ++s) {
        int x = grid_x + s * cell_w;
        if (x >= panel_w - 1) break;
        attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        mvprint_clip(top + 2, x, "S" + std::to_string(s + 1), std::min(cell_w, panel_w - 1 - x));
        attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    }

    for (int r = 0; r < cluster_layout::ROWS; ++r) {
        int y = top + 3 + r;
        if (y >= bottom - 2) break;

        if (label_w > 0) {
            attron(COLOR_PAIR(CP_LABEL));
            mvprintw(y, 1, "R%d", r + 1);
            attroff(COLOR_PAIR(CP_LABEL));
        }

        for (int s = 0; s < cluster_layout::SEATS; ++s) {
            int desk = cluster_layout::index(r, s);
            int x    = grid_x + s * cell_w;
            if (x >= panel_w - 1) break;

            int avail = std::min(cell_w, panel_w - 1 - x);
            const auto* cs = get_student_at_desk(p.cluster_students, room, r, s);
            if (cs) {
                add_hitbox(y, x, 1, avail, MouseAction::DashMinimap,
                           room * cluster_layout::CELLS + desk);
                if (desk == hovered) minimap_hover_box_ = {y, x, avail, true};

                bool is_self = (!p.login.empty() && cs->login == p.login);
                if (is_self) {
                    attron(COLOR_PAIR(CP_ACCENT) | A_BOLD);
                    mvaddstr(y, x, "★");
                    if (cell_w >= 4) mvprint_clip(y, x + 1, "@" + cs->login, cell_w - 1);
                    attroff(COLOR_PAIR(CP_ACCENT) | A_BOLD);
                } else {
                    if (!cs->cdn_uri.empty() && image_renderer::has_image(cs->cdn_uri)) {
                        attron(COLOR_PAIR(CP_ACCENT));
                        mvaddstr(y, x, "▀");
                        attroff(COLOR_PAIR(CP_ACCENT));
                        image_renderer::render_halfblock(cs->cdn_uri, y, x,
                                                          std::min(cell_w, 4), 1,
                                                          bottom - top, cols_);
                        if (cell_w >= 4) mvprint_clip(y, x + 1, "@" + cs->login, cell_w - 1);
                    } else {
                        attron(COLOR_PAIR(CP_SUCCESS));
                        mvaddstr(y, x, "●");
                        attroff(COLOR_PAIR(CP_SUCCESS));
                        if (cell_w >= 4) mvprint_clip(y, x + 1, "@" + cs->login, cell_w - 1);
                    }
                }
            } else {
                attron(COLOR_PAIR(CP_DIM));
                mvprint_clip(y, x, "·", avail);
                attroff(COLOR_PAIR(CP_DIM));
            }
        }
    }

    // Legend footer
    if (bottom - 1 > top + 3 + cluster_layout::ROWS - 1) {
        int y = bottom - 1;
        int x = 2;
        attron(COLOR_PAIR(CP_SUCCESS));
        mvprint_clip(y, x, "● " + i18n::tr("legend_online"), panel_w - 4);
        attroff(COLOR_PAIR(CP_SUCCESS));
        x += 2 + (int)i18n::tr("legend_online").size() + 2;
        attron(COLOR_PAIR(CP_ACCENT) | A_BOLD);
        mvprint_clip(y, x, "★ " + i18n::tr("legend_you"), panel_w - 4 - (x - 2));
        attroff(COLOR_PAIR(CP_ACCENT) | A_BOLD);
        x += 2 + (int)i18n::tr("legend_you").size() + 2;
        attron(COLOR_PAIR(CP_DIM));
        mvprint_clip(y, x, "· " + i18n::tr("legend_empty"), panel_w - 4 - (x - 2));
        attroff(COLOR_PAIR(CP_DIM));
    }
}

void Renderer::draw_cluster_tooltip(
        const Profile& p,
        const std::unordered_map<std::string, ClusterProfileEntry>& profiles,
        int top, int bottom, int panel_w) {
    if (minimap_hover_ < 0 || !minimap_hover_box_.valid) return;

    int room = minimap_hover_ / cluster_layout::CELLS;
    int desk = minimap_hover_ % cluster_layout::CELLS;
    int rr   = cluster_layout::row_of(desk);
    int ss   = cluster_layout::seat_of(desk);
    if (room < 0 || room >= 4) return;

    const ClusterStudent* cs = get_student_at_desk(p.cluster_students, room, rr, ss);
    if (!cs) return;

    const ClusterProfileEntry* entry = nullptr;
    auto it = profiles.find(cs->login);
    if (it != profiles.end()) entry = &it->second;

    std::vector<std::pair<std::string, std::string>> rows;
    rows.push_back({i18n::tr("tip_student"), cs->full_name.empty() ? "(…)" : cs->full_name});
    rows.push_back({i18n::tr("tip_ws"), cs->host + "  (C" + std::to_string(room + 1) +
                    " R" + std::to_string(rr + 1) + " S" + std::to_string(ss + 1) + ")"});
    rows.push_back({i18n::tr("tip_active"), format_active_since(cs->begin_at)});
    rows.push_back({i18n::tr("tip_presence"), "● " + i18n::tr("minimap_online")});

    if (entry && entry->loaded) {
        const Profile& up = entry->profile;
        if (!up.level.empty())
            rows.push_back({i18n::tr("stat_level"), up.level});
        if (!up.location.empty() && up.location != "Unavailable")
            rows.push_back({i18n::tr("stat_seat"), up.location});
    } else if (entry && entry->loading) {
        rows.push_back({i18n::tr("tip_student"), i18n::tr("tip_fetching")});
    } else {
        rows.push_back({i18n::tr("tip_student"), i18n::tr("tip_open")});
    }

    const auto& bc = get_border_chars();

    int bx = panel_w + 2;
    int bw = cols_ - bx - 2;
    if (bw > 50) bw = 50;
    if (bw < 30) {
        bw = std::min(cols_ - 4, 50);
        bx = (cols_ - bw) / 2;
    }
    if (bw < 24 || bx < 0) return;

    int bh = (int)rows.size() + 3;
    int by = minimap_hover_box_.y - 1;
    if (by < top) by = top;
    if (by + bh > bottom) by = bottom - bh;
    if (by < top) by = top;

    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = by; r <= by + bh; ++r) fill_row(r, bx, bw);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    hline_box(by, bx + 1, bw - 2);
    mvaddstr(by, bx + bw - 1, bc.tr);
    for (int r = by + 1; r < by + bh; ++r) {
        mvaddstr(r, bx, bc.v);
        mvaddstr(r, bx + bw - 1, bc.v);
    }
    mvaddstr(by + bh, bx, bc.bl);
    hline_box(by + bh, bx + 1, bw - 2);
    mvaddstr(by + bh, bx + bw - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    std::string title = " " + i18n::tr("minimap_title") + " · @" + cs->login + " ";
    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(by, bx + 2, title, bw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    if (!cs->cdn_uri.empty() && image_renderer::has_image(cs->cdn_uri)) {
        int photo_x = bx + bw - 20;
        if (photo_x > bx + 3)
            image_renderer::render_image(cs->cdn_uri, by, photo_x, 4, 3,
                                              bottom - top, cols_);
    }

    for (size_t i = 0; i < rows.size(); ++i) {
        int ry = by + 1 + (int)i;
        attron(COLOR_PAIR(CP_LABEL));
        mvprint_clip(ry, bx + 2, rows[i].first, 13);
        attroff(COLOR_PAIR(CP_LABEL));

        bool success = (rows[i].first == i18n::tr("tip_presence"));
        attron(COLOR_PAIR(success ? CP_SUCCESS : CP_VALUE) | (success ? A_BOLD : 0));
        mvprint_clip(ry, bx + 15, rows[i].second, bw - 17);
        attroff(COLOR_PAIR(success ? CP_SUCCESS : CP_VALUE) | (success ? A_BOLD : 0));
    }

    attron(COLOR_PAIR(CP_DIM));
    mvprint_clip(by + bh - 1, bx + 2, i18n::tr("tip_footer"), bw - 4);
    attroff(COLOR_PAIR(CP_DIM));
}

// ─────────────────────────────────────────────────────────────────────────────
// Full-screen user profile modal (cluster students)
// ─────────────────────────────────────────────────────────────────────────────
void Renderer::draw_user_modal(
        const Profile& p,
        const std::unordered_map<std::string, ClusterProfileEntry>& profiles,
        const std::string& login) {
    if (login.empty()) return;

    const auto& bc = get_border_chars();
    int bx = 1, by = 1;
    int bw = cols_ - 2, bh = rows_ - 2;
    if (bw < 40 || bh < 12) return;

    attron(COLOR_PAIR(CP_MODAL_BG));
    for (int r = by; r < by + bh; ++r) fill_row(r, bx, bw);
    attroff(COLOR_PAIR(CP_MODAL_BG));

    attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
    mvaddstr(by, bx, bc.tl);
    hline_box(by, bx + 1, bw - 2);
    mvaddstr(by, bx + bw - 1, bc.tr);
    for (int r = by + 1; r < by + bh - 1; ++r) {
        mvaddstr(r, bx, bc.v);
        mvaddstr(r, bx + bw - 1, bc.v);
    }
    mvaddstr(by + bh - 1, bx, bc.bl);
    hline_box(by + bh - 1, bx + 1, bw - 2);
    mvaddstr(by + bh - 1, bx + bw - 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(by, bx + 2, " ◆ PERFIL DE @" + login + " ", bw - 4);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    const ClusterProfileEntry* entry = nullptr;
    auto it = profiles.find(login);
    if (it != profiles.end()) entry = &it->second;

    if (!entry || !entry->loaded) {
        bool loading = (entry && entry->loading);
        attron(COLOR_PAIR(loading ? CP_WARN : CP_FAIL) | A_BOLD);
        std::string msg = loading ? "⟳ Cargando perfil desde intra…"
                                  : "Sin datos de este usuario.";
        mvprint_clip(by + bh / 2, bx + (bw - (int)msg.size()) / 2, msg, bw - 4);
        attroff(COLOR_PAIR(loading ? CP_WARN : CP_FAIL) | A_BOLD);
        if (!loading) {
            attron(COLOR_PAIR(CP_DIM));
            std::string hint = "Cierra con [Esc] y vuelve a abrir el usuario para reintentar.";
            mvprint_clip(by + bh / 2 + 2, bx + (bw - (int)hint.size()) / 2, hint, bw - 4);
            attroff(COLOR_PAIR(CP_DIM));
        }
        attron(COLOR_PAIR(CP_DIM));
        mvprint_clip(by + bh - 2, bx + 2, "[Esc] Volver", bw - 4);
        attroff(COLOR_PAIR(CP_DIM));
        return;
    }

    const Profile& up = entry->profile;
    const ClusterStudent* cs = nullptr;
    for (const auto& s : p.cluster_students) {
        if (s.login == login) { cs = &s; break; }
    }

    int left_w = std::min(36, bw / 3);
    int lx = bx + 3;
    int rx = bx + left_w + 2;
    int top = by + 2;
    int bottom = by + bh - 2;

    // Avatar frame
    int av_h = 7, av_w = left_w - 4;
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(top, lx, bc.tl);
    hline_box(top, lx + 1, av_w);
    mvaddstr(top, lx + av_w + 1, bc.tr);
    for (int r = 1; r <= av_h; ++r) {
        mvaddstr(top + r, lx, bc.v);
        fill_row(top + r, lx + 1, av_w);
        mvaddstr(top + r, lx + av_w + 1, bc.v);
    }
    mvaddstr(top + av_h + 1, lx, bc.bl);
    hline_box(top + av_h + 1, lx + 1, av_w);
    mvaddstr(top + av_h + 1, lx + av_w + 1, bc.br);
    attroff(COLOR_PAIR(CP_BORDER));

    // Remember the avatar frame interior so draw() can place the real photo
    // there (and hide the base dashboard/cluster photos behind the modal).
    user_modal_avatar_box_ = ImageBox{top + 1, lx + 1, av_w, av_h, true};
    // Prefer cs->cdn_uri (cached from cluster data) over up.avatar_url
    if (cs && !cs->cdn_uri.empty() && image_renderer::has_image(cs->cdn_uri)) {
        user_modal_avatar_key_ = cs->cdn_uri;
    } else {
        user_modal_avatar_key_ = up.avatar_url;
    }

    const std::string& avatar_key = user_modal_avatar_key_;
    if (avatar_key.empty() || !image_renderer::has_image(avatar_key)) {
        attron(COLOR_PAIR(CP_DIM));
        mvprintw(top + av_h / 2 + 1, lx + (av_w - 6) / 2, "[FOTO]");
        attroff(COLOR_PAIR(CP_DIM));
    }

    int ty = top + av_h + 3;
    auto kv = [&](const char* k, const std::string& v, int cp) {
        if (ty >= bottom) return;
        attron(COLOR_PAIR(CP_LABEL));
        mvprint_clip(ty, lx, k, 11);
        attroff(COLOR_PAIR(CP_LABEL));
        attron(COLOR_PAIR(cp) | A_BOLD);
        mvprint_clip(ty, lx + 11, v, left_w - 12);
        attroff(COLOR_PAIR(cp) | A_BOLD);
        ++ty;
    };

    kv("Nombre", up.display_name.empty() ? login : up.display_name, CP_VALUE);
    kv("Login", "@" + login, CP_TITLE);
    kv("Nivel", up.level.empty() ? "—" : up.level, CP_SUCCESS);
    if (cs) {
        kv("Asiento", cs->host, CP_VALUE);
        kv("Activo", format_active_since(cs->begin_at), CP_VALUE);
    } else if (!up.location.empty() && up.location != "Unavailable") {
        kv("Ubicación", up.location, CP_VALUE);
    }

    // Right column: public projects with grades
    int max_w = bw - (rx - bx) - 4;
    if (max_w < 20) max_w = 20;

    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprint_clip(top, rx, "PROYECTOS PÚBLICOS", max_w);
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

    attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    fill_row(top + 1, rx, max_w);
    mvprint_clip(top + 1, rx, pad("PROYECTO", max_w - 18) + pad("NOTA", 7) + "ESTADO", max_w);
    attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);

    int prow = top + 2;
    if (up.projects.empty()) {
        attron(COLOR_PAIR(CP_DIM));
        mvprint_clip(prow + 1, rx + 2, "Sin proyectos públicos.", max_w);
        attroff(COLOR_PAIR(CP_DIM));
    }
    for (const auto& pr : up.projects) {
        if (prow >= bottom) break;
        bool ok   = (pr.status == "finished" && pr.grade != "N/A" && !pr.grade.empty());
        bool fail = (pr.status == "finished" && !ok);
        bool prog = (pr.status == "in_progress");
        int cp = ok ? CP_SUCCESS : (fail ? CP_FAIL : (prog ? CP_IN_PROG : CP_WARN));
        std::string badge = ok ? "APROBADO" : (prog ? "EN CURSO" : (fail ? "SUSPENDIDO" : pr.status));
        std::string grade = pr.grade.empty() ? "N/A" : pr.grade;

        attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
        mvprint_clip(prow, rx, pr.name, max_w - 16);
        attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

        attron(COLOR_PAIR(cp) | A_BOLD);
        mvprint_clip(prow, rx + max_w - 15, pad(grade, 6) + badge, 15);
        attroff(COLOR_PAIR(cp) | A_BOLD);
        ++prow;
    }

    attron(COLOR_PAIR(CP_DIM));
    mvprint_clip(by + bh - 2, bx + 2, "[Esc] Volver", bw - 4);
    attroff(COLOR_PAIR(CP_DIM));
}
