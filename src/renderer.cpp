#include "renderer.hpp"
#include "types.hpp"
#include "theme.hpp"
#include "config.hpp"
#include "image_renderer.hpp"
#include "network.hpp"

#include <ncurses.h>
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

    // Enable mouse reporting (clicks + scroll wheel).
    mousemask(ALL_MOUSE_EVENTS, nullptr);
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
                    int project_sel, int slot_sel, int tree_sel, int cluster_sel,
                    bool login_mode, int login_method, int active_field,
                    const std::string& login_buf, const std::string& pass_buf,
                    const std::string& cookie_buf, const std::string& detected_file,
                    bool theme_switcher_open, int theme_sel,
                    int dash_subview, int dash_sel, bool dash_inspect,
                    int cluster_room,
                    bool preview_panel,
                    const SubjectPreview& preview,
                    bool subject_modal,
                    int subject_scroll,
                    bool action_menu_open,
                    const std::vector<std::pair<std::string, bool>>& action_items,
                    int action_sel)
{
    getmaxyx(stdscr, rows_, cols_);
    erase();
    hitboxes_.clear();
    preview_img_ = ImageBox{};

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
    {
        std::lock_guard<std::mutex> lk(state.mtx);
        prof       = state.profile;
        status_msg = state.status_msg;
        error_msg  = state.error_msg;
        loading    = state.loading;
        data_ready = state.data_ready;
    }

    int content_top    = 2;
    int content_bottom = rows_ - 2;
    int left_w         = compute_left_panel_w(cols_);

    if (login_mode || (!data_ready && !loading)) {
        draw_login_prompt(login_method, active_field,
                          login_buf, pass_buf, cookie_buf, detected_file,
                          error_msg, loading, status_msg);
    } else {
        draw_tab_bar(current_tab, loading);

        switch (current_tab) {
            case Tab::Dashboard:
                draw_dashboard(prof, dash_subview, dash_sel, dash_inspect, content_top, content_bottom, left_w);
                break;
            case Tab::Projects:
                draw_projects(prof, project_sel, content_top, content_bottom, left_w,
                              preview_panel, preview);
                break;
            case Tab::Slots:
                draw_slots(prof, slot_sel, content_top, content_bottom, left_w);
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

        int avail_h = content_bottom - content_top;
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

// Simple overload wrapper
void Renderer::draw(SharedState& state, Tab current_tab,
                    int project_sel, int slot_sel,
                    bool login_mode, const std::string& login_buf,
                    bool password_mode, const std::string& pass_buf)
{
    draw(state, current_tab, project_sel, slot_sel, 0, 0,
         login_mode, 0, password_mode ? 1 : 0,
         login_buf, pass_buf, "", "", false, 0, 0, 0, false, 0);
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
        { "2", "PROJECTS",  Tab::Projects  },
        { "3", "SLOTS",     Tab::Slots     },
        { "4", "ROADMAP",   Tab::Roadmap   },
        { "5", "CLUSTER",   Tab::Cluster   },
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

    // Horizontal frame line below tab bar
    const auto& bc = get_border_chars();
    attron(COLOR_PAIR(CP_BORDER));
    mvaddstr(1, 0, bc.t_left);
    hline_box(1, 1, cols_ - 2);
    mvaddstr(1, cols_ - 1, bc.t_right);
    attroff(COLOR_PAIR(CP_BORDER));
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
        hints = " j/k:Sel  s:AddSlot  d:Trim-15m  D:DelAll  t:Theme  q:Quit ";
    else if (current_tab == Tab::Projects)
        hints = " j/k:Scroll  p:Preview  Enter:Menu  d/s:PDF  t:Theme  q:Quit ";
    else if (current_tab == Tab::Roadmap)
        hints = " j/k:Nav  Enter:Actions  p:Preview  d/s:PDF  t:Theme  q:Quit ";
    else if (current_tab == Tab::Cluster)
        hints = " j/k:Select  y:Copylogin  r:Sync  t:Theme  q:Quit ";
    else
        hints = " 1-5:Tabs  s:QuickSlot  t:Theme  r:Sync  q:Quit ";

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
void Renderer::draw_dashboard(const Profile& p, int subview, int sel, bool inspect, int top, int bottom, int left_w) {
    draw_profile_panel(p, top, bottom, left_w);

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

    int row = top;

    // Sub-menu Navigation Strip
    {
        attron(COLOR_PAIR(CP_BORDER));
        mvprintw(row, rx + 2, "%s─ VIEW: ", bc.tl);
        attroff(COLOR_PAIR(CP_BORDER));

        struct SubViewDef { int id; const char* name; };
        const SubViewDef subviews[] = {
            { 0, "[1: Overview]" },
            { 1, "[2: Scale Teams]" },
            { 2, "[3: Points & Pool]" }
        };

        int sx = rx + 12;
        for (const auto& sv : subviews) {
            bool active = (sv.id == subview);
            add_hitbox(row, sx, 1, (int)strlen(sv.name), MouseAction::DashSubview, sv.id);
            if (active) {
                attron(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
            } else {
                attron(COLOR_PAIR(CP_DIM));
            }
            mvprintw(row, sx, "%s", sv.name);
            if (active) {
                attroff(COLOR_PAIR(CP_TAB_ACTIVE) | A_BOLD);
            } else {
                attroff(COLOR_PAIR(CP_DIM));
            }
            sx += (int)strlen(sv.name) + 2;
        }

        attron(COLOR_PAIR(CP_BORDER));
        mvprintw(row, sx, "─%s", bc.tr);
        attroff(COLOR_PAIR(CP_BORDER));

        attron(COLOR_PAIR(CP_DIM));
        if (cols_ - 26 > sx + 1) {
            mvprintw(row, cols_ - 26, "([/] to cycle subviews)");
        }
        attroff(COLOR_PAIR(CP_DIM));

        row += 2;
    }

    if (subview == 0) {
        // ─────────────────────────────────────────────────────────────────────
        // SUBVIEW 0: OVERVIEW
        // ─────────────────────────────────────────────────────────────────────

        // 1. Cursus Level & Progress Hero Card
        {
            int card_h = 4;
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(row, rx + 2, bc.tl);
            hline_box(row, rx + 3, rw - 6);
            mvaddstr(row, rx + rw - 3, bc.tr);

            for (int ch = 1; ch < card_h; ++ch) {
                mvaddstr(row + ch, rx + 2, bc.v);
                fill_row(row + ch, rx + 3, rw - 6);
                mvaddstr(row + ch, rx + rw - 3, bc.v);
            }

            mvaddstr(row + card_h, rx + 2, bc.bl);
            hline_box(row + card_h, rx + 3, rw - 6);
            mvaddstr(row + card_h, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));

            float lvl = 0.f;
            try { lvl = std::stof(p.level); } catch (...) {}
            float frac = lvl - static_cast<int>(lvl);
            if (frac < 0.f) frac = 0.f;
            if (frac > 1.f) frac = 1.f;

            // Line 1: Header
            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprintw(row + 1, rx + 4, "◆ 42 CURSUS LEVEL: %s", p.level.c_str());
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            attron(COLOR_PAIR(CP_VALUE));
            std::string quick_stats = "Wallet: " + (p.wallet.empty() ? "0" : p.wallet) + " ₳  │  Eval Points: " + 
                                      (p.correction_points.empty() ? "0" : p.correction_points) + "  │  Seat: " + 
                                      (p.location.empty() ? "—" : p.location);
            mvprint_clip(row + 1, rx + 30, quick_stats, rw - 34);
            attroff(COLOR_PAIR(CP_VALUE));

            // Line 2: Progress bar in theme colors
            int bar_w = rw - 24;
            if (bar_w > 10) {
                int filled = static_cast<int>(frac * bar_w);
                mvaddstr(row + 2, rx + 4, "Progress: [");
                attron(COLOR_PAIR(CP_PROGRESS) | A_BOLD);
                for (int i = 0; i < filled; ++i) mvaddstr(row + 2, rx + 15 + i, "█");
                attroff(COLOR_PAIR(CP_PROGRESS) | A_BOLD);

                attron(COLOR_PAIR(CP_DIM));
                for (int i = filled; i < bar_w; ++i) mvaddstr(row + 2, rx + 15 + i, "░");
                attroff(COLOR_PAIR(CP_DIM));
                mvaddch(row + 2, rx + 15 + bar_w, ']');

                char pct_str[16];
                snprintf(pct_str, sizeof(pct_str), " %d%%", (int)(frac * 100.f));
                attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                mvprintw(row + 2, rx + 17 + bar_w, "%s", pct_str);
                attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            }

            // Line 3: Active Slots summary
            attron(COLOR_PAIR(CP_DIM));
            std::string slots_summary = "Active Slots: " + std::to_string(p.slots.size()) + " available  │  Safety offset: +" + std::to_string(Config::get().offset_minutes) + "m";
            mvprint_clip(row + 3, rx + 4, slots_summary, rw - 8);
            attroff(COLOR_PAIR(CP_DIM));

            row += card_h + 1;
        }

        // 2. Correction Points & Economics Card
        {
            int card_h = 3;
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(row, rx + 2, bc.tl);
            hline_box(row, rx + 3, rw - 6);
            mvaddstr(row, rx + rw - 3, bc.tr);

            for (int ch = 1; ch < card_h; ++ch) {
                mvaddstr(row + ch, rx + 2, bc.v);
                fill_row(row + ch, rx + 3, rw - 6);
                mvaddstr(row + ch, rx + rw - 3, bc.v);
            }

            mvaddstr(row + card_h, rx + 2, bc.bl);
            hline_box(row + card_h, rx + 3, rw - 6);
            mvaddstr(row + card_h, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));

            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprintw(row, rx + 4, " CORRECTION POINTS METRICS ");
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            // Row 1: Balance & evaluation rights
            attron(COLOR_PAIR(CP_LABEL));
            mvprintw(row + 1, rx + 4, "Balance: ");
            attroff(COLOR_PAIR(CP_LABEL));

            attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            std::string pts_str = (p.correction_points.empty() ? "0" : p.correction_points) + " Points";
            mvprintw(row + 1, rx + 13, "%-12s", pts_str.c_str());
            attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);

            attron(COLOR_PAIR(CP_VALUE));
            std::string elig = "✔ Can request up to " + (p.correction_points.empty() ? "0" : p.correction_points) + " peer project evaluations";
            mvprint_clip(row + 1, rx + 28, elig, rw - 32);
            attroff(COLOR_PAIR(CP_VALUE));

            // Row 2: Economics
            attron(COLOR_PAIR(CP_DIM));
            std::string econ = "Economics: +1 pt earned per evaluation given  │  -1 pt per project submission  │  Pool: Healthy";
            mvprint_clip(row + 2, rx + 4, econ, rw - 8);
            attroff(COLOR_PAIR(CP_DIM));

            row += card_h + 1;
        }

        // 3. Notification / Action Center
        bool has_pending = (p.pending_feedbacks_count > 0);
        const EvaluationFeedback* pending_fb = nullptr;
        for (const auto& fb : p.feedbacks) {
            if (fb.is_pending) {
                has_pending = true;
                pending_fb = &fb;
                break;
            }
        }
        if (!pending_fb && !p.feedbacks.empty() && p.pending_feedbacks_count > 0) {
            pending_fb = &p.feedbacks.front();
        }

        if (has_pending) {
            int card_h = 3;
            attron(COLOR_PAIR(CP_WARN));
            mvaddstr(row, rx + 2, bc.tl);
            hline_box(row, rx + 3, rw - 6);
            mvaddstr(row, rx + rw - 3, bc.tr);

            for (int ch = 1; ch < card_h; ++ch) {
                mvaddstr(row + ch, rx + 2, bc.v);
                fill_row(row + ch, rx + 3, rw - 6);
                mvaddstr(row + ch, rx + rw - 3, bc.v);
            }

            mvaddstr(row + card_h, rx + 2, bc.bl);
            hline_box(row + card_h, rx + 3, rw - 6);
            mvaddstr(row + card_h, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_WARN));

            attron(COLOR_PAIR(CP_WARN) | A_BOLD);
            mvprintw(row, rx + 4, " 🔔 ACTION REQUIRED ");
            attroff(COLOR_PAIR(CP_WARN) | A_BOLD);

            attron(COLOR_PAIR(CP_WARN) | A_BOLD);
            std::string action_title = "▶ " + std::to_string(std::max(1, p.pending_feedbacks_count)) + " Evaluation Feedback Pending";
            if (pending_fb && !pending_fb->project_name.empty()) {
                action_title += ": " + pending_fb->project_name;
                if (!pending_fb->evaluator_login.empty()) {
                    action_title += " with @" + pending_fb->evaluator_login;
                }
            }
            mvprint_clip(row + 1, rx + 4, action_title, rw - 8);
            attroff(COLOR_PAIR(CP_WARN) | A_BOLD);

            attron(COLOR_PAIR(CP_VALUE));
            mvprint_clip(row + 2, rx + 4, "Press [Enter] or [f] to inspect feedback critique & rating breakdown", rw - 8);
            attroff(COLOR_PAIR(CP_VALUE));

            row += card_h + 1;
        } else {
            attron(COLOR_PAIR(CP_SUCCESS));
            mvprintw(row, rx + 2, "● Notifications: All evaluation feedbacks completed (Sync with [r])");
            attroff(COLOR_PAIR(CP_SUCCESS));
            row += 2;
        }

        // 4. Recent Project Submissions Table Header
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprintw(row, rx + 2, "◆ Recent Project Submissions");
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
        row++;

        attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        fill_row(row, rx + 2, rw - 4);
        std::string hdr = pad(" #  PROJECT", rw - 26) + pad("GRADE", 10) + "STATUS";
        mvprint_clip(row, rx + 2, hdr, rw - 4);
        attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        row++;

        int count = 0;
        for (const auto& pr : p.projects) {
            if (row >= bottom - 1) break;

            bool ok   = (pr.status == "finished" && pr.grade != "N/A" && !pr.grade.empty());
            bool fail = (pr.status == "finished" && !ok);
            bool prog = (pr.status == "in_progress");

            int cp = ok ? CP_SUCCESS : (fail ? CP_FAIL : (prog ? CP_IN_PROG : CP_WARN));

            char idx_buf[16];
            snprintf(idx_buf, sizeof(idx_buf), "%02d", count + 1);

            std::string grade_str = pr.grade.empty() ? "N/A" : pr.grade;
            std::string status_badge = ok ? "[FINISHED]" : (prog ? "[IN PROGRESS]" : "[" + pr.status + "]");

            attron(COLOR_PAIR(CP_DIM));
            mvprintw(row, rx + 2, " %s ", idx_buf);
            attroff(COLOR_PAIR(CP_DIM));

            attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
            mvprint_clip(row, rx + 6, pr.name, rw - 30);
            attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

            attron(COLOR_PAIR(cp) | A_BOLD);
            mvprintw(row, rx + rw - 22, "%-8s", grade_str.c_str());
            mvprint_clip(row, rx + rw - 14, status_badge, 12);
            attroff(COLOR_PAIR(cp) | A_BOLD);

            row++;
            count++;
        }

        if (count == 0) {
            attron(COLOR_PAIR(CP_DIM));
            mvprintw(row + 1, rx + 4, "No projects loaded. Press 'r' to sync data from intra.");
            attroff(COLOR_PAIR(CP_DIM));
        }

        // 5. Feedback Inspector Modal overlay if active
        if (inspect) {
            const EvaluationFeedback* target_fb = pending_fb;
            if (!target_fb && !p.feedbacks.empty()) {
                target_fb = &p.feedbacks.front();
            }

            int mw = std::min(rw - 4, 76);
            int mh = std::min(bottom - top - 4, 16);
            int mx = rx + (rw - mw) / 2;
            int my = top + 3;

            attron(COLOR_PAIR(CP_MODAL_BG));
            for (int r = my; r <= my + mh; ++r) {
                fill_row(r, mx, mw);
            }
            attroff(COLOR_PAIR(CP_MODAL_BG));

            attron(COLOR_PAIR(CP_BORDER) | A_BOLD);
            mvaddstr(my, mx, bc.tl);
            hline_box(my, mx + 1, mw - 2);
            mvaddstr(my, mx + mw - 1, bc.tr);

            for (int r = my + 1; r < my + mh; ++r) {
                mvaddstr(r, mx, bc.v);
                mvaddstr(r, mx + mw - 1, bc.v);
            }

            mvaddstr(my + mh, mx, bc.bl);
            hline_box(my + mh, mx + 1, mw - 2);
            mvaddstr(my + mh, mx + mw - 1, bc.br);
            attroff(COLOR_PAIR(CP_BORDER) | A_BOLD);

            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprintw(my, mx + 4, " 📋 EVALUATION FEEDBACK INSPECTOR ");
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            if (target_fb) {
                attron(COLOR_PAIR(CP_LABEL));
                mvprintw(my + 2, mx + 3, "Project   :");
                attroff(COLOR_PAIR(CP_LABEL));
                attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
                mvprintw(my + 2, mx + 16, "%s", target_fb->project_name.c_str());
                attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

                attron(COLOR_PAIR(CP_LABEL));
                mvprintw(my + 3, mx + 3, "Evaluator :");
                attroff(COLOR_PAIR(CP_LABEL));
                attron(COLOR_PAIR(CP_VALUE));
                mvprintw(my + 3, mx + 16, "@%s", target_fb->evaluator_login.empty() ? "peer" : target_fb->evaluator_login.c_str());
                attroff(COLOR_PAIR(CP_VALUE));

                attron(COLOR_PAIR(CP_LABEL));
                mvprintw(my + 4, mx + 3, "Date & Mark:");
                attroff(COLOR_PAIR(CP_LABEL));
                attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
                mvprintw(my + 4, mx + 16, "%s  [Grade: %s]", target_fb->scheduled_at.empty() ? "Recent" : target_fb->scheduled_at.c_str(),
                         target_fb->mark.empty() ? "Pending" : target_fb->mark.c_str());
                attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);

                attron(COLOR_PAIR(CP_LABEL));
                mvprintw(my + 5, mx + 3, "Breakdown :");
                attroff(COLOR_PAIR(CP_LABEL));
                attron(COLOR_PAIR(CP_VALUE));
                mvprint_clip(my + 5, mx + 16, target_fb->rating_breakdown.empty() ? "Nice: 4/4  Rigorous: 4/4  Interested: 4/4  Punctual: 4/4" : target_fb->rating_breakdown, mw - 19);
                attroff(COLOR_PAIR(CP_VALUE));

                attron(COLOR_PAIR(CP_LABEL));
                mvprintw(my + 7, mx + 3, "Peer Review / Critique:");
                attroff(COLOR_PAIR(CP_LABEL));

                attron(COLOR_PAIR(CP_VALUE));
                std::string comment = target_fb->comment.empty() ? "No written critique recorded." : target_fb->comment;
                int crow = my + 8;
                for (size_t i = 0; i < comment.size() && crow < my + mh - 2; i += mw - 8) {
                    mvprint_clip(crow++, mx + 4, comment.substr(i, mw - 8), mw - 8);
                }
                attroff(COLOR_PAIR(CP_VALUE));

                if (!target_fb->feedback_comment.empty()) {
                    attron(COLOR_PAIR(CP_LABEL));
                    mvprint_clip(crow, mx + 3, "Student Feedback: " + target_fb->feedback_comment, mw - 6);
                    attroff(COLOR_PAIR(CP_LABEL));
                }
            } else {
                attron(COLOR_PAIR(CP_DIM));
                mvprintw(my + 4, mx + 4, "No evaluation feedback record selected.");
                attroff(COLOR_PAIR(CP_DIM));
            }

            attron(COLOR_PAIR(CP_BORDER));
            hline_box(my + mh - 2, mx + 1, mw - 2);
            attroff(COLOR_PAIR(CP_BORDER));

            attron(COLOR_PAIR(CP_DIM));
            mvprintw(my + mh - 1, mx + 4, "Press [Enter] or [Esc] to close inspector");
            attroff(COLOR_PAIR(CP_DIM));
        }

    } else if (subview == 1) {
        // ─────────────────────────────────────────────────────────────────────
        // SUBVIEW 1: SCALE TEAMS & EVALUATIONS
        // ─────────────────────────────────────────────────────────────────────
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprintw(row, rx + 2, "◆ Campus Peer Evaluations & Scale Teams History");
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
        row++;

        // Table header
        attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        fill_row(row, rx + 2, rw - 4);
        std::string hdr = pad("   #  DATE", 16) + pad("PROJECT", 22) + pad("PEER", 16) + pad("GRADE", 10) + "FEEDBACK";
        mvprint_clip(row, rx + 2, hdr, rw - 4);
        attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
        row++;

        int total_records = (int)p.feedbacks.size();
        int max_items = std::max(1, (bottom - row - 7));
        int safe_sel = std::clamp(sel, 0, std::max(0, total_records - 1));

        int start_idx = 0;
        if (safe_sel >= max_items) {
            start_idx = safe_sel - max_items + 1;
        }

        for (int i = 0; i < max_items && (start_idx + i) < total_records; ++i) {
            int idx = start_idx + i;
            const auto& fb = p.feedbacks[idx];
            bool is_active = (idx == safe_sel);
            add_hitbox(row, rx + 2, 1, rw - 4, MouseAction::ListRow, idx);

            int cp = is_active ? CP_ROW_SEL : ((idx % 2 == 0) ? CP_DEFAULT : CP_MODAL_BG);
            attron(COLOR_PAIR(cp));
            fill_row(row, rx + 2, rw - 4);

            char num_buf[16];
            snprintf(num_buf, sizeof(num_buf), "%02d", idx + 1);

            std::string date_str = fb.scheduled_at.empty() ? "Recent" : fb.scheduled_at.substr(0, 10);
            std::string line = (is_active ? "> " : "  ") + std::string(num_buf) + "  " +
                               pad(date_str, 10) + "  " +
                               pad(fb.project_name.empty() ? "Project" : fb.project_name, 20) + "  @" +
                               pad(fb.evaluator_login.empty() ? "peer" : fb.evaluator_login, 13) + "  " +
                               pad(fb.mark.empty() ? "N/A" : fb.mark, 8) + "  " +
                               (fb.feedback_rating.empty() ? "★★★★★" : fb.feedback_rating);

            mvprint_clip(row, rx + 2, line, rw - 4);
            attroff(COLOR_PAIR(cp));
            row++;
        }

        if (total_records == 0) {
            attron(COLOR_PAIR(CP_DIM));
            mvprintw(row + 1, rx + 4, "No evaluation history loaded. Press 'r' to sync from intra.");
            attroff(COLOR_PAIR(CP_DIM));
            row += 3;
        }

        // Detail preview pane at the bottom
        int detail_top = bottom - 6;
        if (detail_top > row) {
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(detail_top, rx + 2, bc.tl);
            hline_box(detail_top, rx + 3, rw - 6);
            mvaddstr(detail_top, rx + rw - 3, bc.tr);
            for (int r = detail_top + 1; r < bottom; ++r) {
                mvaddstr(r, rx + 2, bc.v);
                fill_row(r, rx + 3, rw - 6);
                mvaddstr(r, rx + rw - 3, bc.v);
            }
            mvaddstr(bottom, rx + 2, bc.bl);
            hline_box(bottom, rx + 3, rw - 6);
            mvaddstr(bottom, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));

            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprintw(detail_top, rx + 4, " EVALUATION DETAIL ");
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            if (safe_sel >= 0 && safe_sel < total_records) {
                const auto& cur = p.feedbacks[safe_sel];
                attron(COLOR_PAIR(CP_VALUE) | A_BOLD);
                mvprintw(detail_top + 1, rx + 4, "Critique: %s", cur.comment.empty() ? "No written critique." : cur.comment.c_str());
                attroff(COLOR_PAIR(CP_VALUE) | A_BOLD);

                attron(COLOR_PAIR(CP_LABEL));
                mvprintw(detail_top + 2, rx + 4, "Breakdown: ");
                attroff(COLOR_PAIR(CP_LABEL));
                attron(COLOR_PAIR(CP_SUCCESS));
                mvprint_clip(detail_top + 2, rx + 15, cur.rating_breakdown.empty() ? "Nice: 4/4  Rigorous: 4/4  Interested: 4/4  Punctual: 4/4" : cur.rating_breakdown, rw - 20);
                attroff(COLOR_PAIR(CP_SUCCESS));

                if (!cur.feedback_comment.empty()) {
                    attron(COLOR_PAIR(CP_DIM));
                    mvprint_clip(detail_top + 3, rx + 4, "Student note: " + cur.feedback_comment, rw - 8);
                    attroff(COLOR_PAIR(CP_DIM));
                }
            } else {
                attron(COLOR_PAIR(CP_DIM));
                mvprintw(detail_top + 2, rx + 4, "Select an evaluation row using j/k to view feedback notes");
                attroff(COLOR_PAIR(CP_DIM));
            }
        }

    } else if (subview == 2) {
        // ─────────────────────────────────────────────────────────────────────
        // SUBVIEW 2: CORRECTION POINTS & CAMPUS POOL ECONOMICS
        // ─────────────────────────────────────────────────────────────────────
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprintw(row, rx + 2, "◆ Correction Points Economics & Campus Pool");
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
        row += 2;

        // Card 1: Balance & Status
        {
            int card_h = 5;
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(row, rx + 2, bc.tl);
            hline_box(row, rx + 3, rw - 6);
            mvaddstr(row, rx + rw - 3, bc.tr);
            for (int ch = 1; ch < card_h; ++ch) {
                mvaddstr(row + ch, rx + 2, bc.v);
                fill_row(row + ch, rx + 3, rw - 6);
                mvaddstr(row + ch, rx + rw - 3, bc.v);
            }
            mvaddstr(row + card_h, rx + 2, bc.bl);
            hline_box(row + card_h, rx + 3, rw - 6);
            mvaddstr(row + card_h, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));

            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprintw(row, rx + 4, " CURRENT BALANCE ");
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            attron(COLOR_PAIR(CP_LABEL));
            mvprintw(row + 1, rx + 4, "Available Points   :");
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_SUCCESS) | A_BOLD);
            mvprintw(row + 1, rx + 26, "%s points", p.correction_points.empty() ? "0" : p.correction_points.c_str());
            attroff(COLOR_PAIR(CP_SUCCESS) | A_BOLD);

            attron(COLOR_PAIR(CP_LABEL));
            mvprintw(row + 2, rx + 4, "Wallet (Altarian ₳):");
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_WARN) | A_BOLD);
            mvprintw(row + 2, rx + 26, "%s ₳", p.wallet.empty() ? "0" : p.wallet.c_str());
            attroff(COLOR_PAIR(CP_WARN) | A_BOLD);

            attron(COLOR_PAIR(CP_LABEL));
            mvprintw(row + 3, rx + 4, "Submission Rights  :");
            attroff(COLOR_PAIR(CP_LABEL));
            attron(COLOR_PAIR(CP_VALUE));
            mvprintw(row + 3, rx + 26, "Eligible to request %s project evaluations", p.correction_points.empty() ? "0" : p.correction_points.c_str());
            attroff(COLOR_PAIR(CP_VALUE));

            row += card_h + 2;
        }

        // Card 2: Rules & Economics Explanation
        {
            int card_h = 7;
            attron(COLOR_PAIR(CP_BORDER));
            mvaddstr(row, rx + 2, bc.tl);
            hline_box(row, rx + 3, rw - 6);
            mvaddstr(row, rx + rw - 3, bc.tr);
            for (int ch = 1; ch < card_h; ++ch) {
                mvaddstr(row + ch, rx + 2, bc.v);
                fill_row(row + ch, rx + 3, rw - 6);
                mvaddstr(row + ch, rx + rw - 3, bc.v);
            }
            mvaddstr(row + card_h, rx + 2, bc.bl);
            hline_box(row + card_h, rx + 3, rw - 6);
            mvaddstr(row + card_h, rx + rw - 3, bc.br);
            attroff(COLOR_PAIR(CP_BORDER));

            attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
            mvprintw(row, rx + 4, " 42 EVALUATION RULES & CAMPUS POOL ");
            attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);

            attron(COLOR_PAIR(CP_SUCCESS));
            mvprintw(row + 1, rx + 4, "● Earning Points   : +1 point awarded for every peer evaluation completed as corrector.");
            attroff(COLOR_PAIR(CP_SUCCESS));

            attron(COLOR_PAIR(CP_WARN));
            mvprintw(row + 2, rx + 4, "● Spending Points  : -1 point deducted per evaluation required when submitting a project.");
            attroff(COLOR_PAIR(CP_WARN));

            attron(COLOR_PAIR(CP_VALUE));
            mvprintw(row + 3, rx + 4, "● Campus Pool      : Redistributes points to students with 0 points based on activity.");
            mvprintw(row + 4, rx + 4, "● Slot Tip         : Opening slots during peak hours (14:00 - 18:00) yields fastest matches.");
            mvprintw(row + 5, rx + 4, "● Anti-Collision   : Intra enforces a +%dm offset between slot creation and defense time.", Config::get().offset_minutes);
            attroff(COLOR_PAIR(CP_VALUE));

            row += card_h + 1;
        }
    }
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
void Renderer::draw_slots(const Profile& p, int sel, int top, int bottom, int left_w) {
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

    attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
    mvprintw(row, rx + 2, "◆ Peer-Evaluation Slots Management");
    attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
    row++;

    // Safety rule banner
    attron(COLOR_PAIR(CP_DIM));
    std::string rule_banner = "Press [s] AddSlot  │  [d] Trim -15m  │  [D] DeleteAll (offset +" +
                              std::to_string(Config::get().offset_minutes) + "m)";
    mvprint_clip(row, rx + 2, rule_banner, rw - 4);
    attroff(COLOR_PAIR(CP_DIM));
    row++;

    // Table Header
    attron(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    fill_row(row, rx + 2, rw - 4);
    std::string hdr = pad("   #  DATE", 16) + pad("TIME RANGE", 18) + pad("STATUS", 16) + "ACTION";
    mvprint_clip(row, rx + 2, hdr, rw - 4);
    attroff(COLOR_PAIR(CP_HEADER_ROW) | A_BOLD);
    row++;

    int total = (int)p.slots.size();
    if (total == 0) {
        attron(COLOR_PAIR(CP_DIM));
        mvprintw(row + 2, rx + 4, "No peer-evaluation slots currently open.");
        mvprintw(row + 3, rx + 4, "Press 's' to create one (+%d min safety offset will be applied).", Config::get().offset_minutes);
        attroff(COLOR_PAIR(CP_DIM));
        return;
    }

    auto extract_date = [](const std::string& iso) -> std::string {
        if (iso.size() >= 10) return iso.substr(0, 10);
        return iso;
    };
    auto extract_time = [](const std::string& iso) -> std::string {
        if (iso.size() >= 16) return iso.substr(11, 5);
        return iso;
    };

    for (int i = 0; i < total && (row < bottom - 3); ++i) {
        const auto& sl = p.slots[i];
        bool is_sel = (i == sel);
        add_hitbox(row, rx + 2, 1, rw - 4, MouseAction::ListRow, i);

        std::string date_str  = extract_date(sl.begin_at);
        std::string range_str = extract_time(sl.begin_at) + " → " + extract_time(sl.end_at);
        std::string status    = sl.title.empty() ? "Available" : sl.title;
        bool is_avail         = (status == "Available");
        int status_cp         = is_avail ? CP_SUCCESS : CP_WARN;
        std::string badge     = "[" + status + "]";

        if (is_sel) {
            attron(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
            fill_row(row, rx + 2, rw - 4);
            mvprintw(row, rx + 2, " ▶ %02d  %-12s %-16s %-14s [d:-15m D:Del]",
                     i + 1, date_str.c_str(), range_str.c_str(), badge.c_str());
            attroff(COLOR_PAIR(CP_ROW_SEL) | A_BOLD);
        } else {
            attron(COLOR_PAIR(CP_DIM));
            mvprintw(row, rx + 2, "   %02d", i + 1);
            attroff(COLOR_PAIR(CP_DIM));

            attron(COLOR_PAIR(CP_VALUE));
            mvprintw(row, rx + 8, "%-12s", date_str.c_str());
            mvprintw(row, rx + 22, "%-16s", range_str.c_str());
            attroff(COLOR_PAIR(CP_VALUE));

            attron(COLOR_PAIR(status_cp) | A_BOLD);
            mvprintw(row, rx + 40, "%-14s", badge.c_str());
            attroff(COLOR_PAIR(status_cp) | A_BOLD);

            attron(COLOR_PAIR(CP_DIM));
            mvprintw(row, rx + rw - 17, "[d:-15m D:Del]");
            attroff(COLOR_PAIR(CP_DIM));
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

        const auto& sl = p.slots[sel];
        std::string detail = "Slot #" + (!sl.id.empty() ? sl.id : sl.ids) +
                             "  │  " + extract_date(sl.begin_at) + " " + extract_time(sl.begin_at) +
                             " to " + extract_time(sl.end_at) +
                             "  │  " + (sl.title.empty() ? "Available" : sl.title) +
                             "  │  [d] Trim -15m  [D] Delete All";
        attron(COLOR_PAIR(CP_TITLE) | A_BOLD);
        mvprint_clip(drow + 1, rx + 4, detail, rw - 8);
        attroff(COLOR_PAIR(CP_TITLE) | A_BOLD);
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
