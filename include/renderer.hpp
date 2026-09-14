#pragma once
#include "types.hpp"
#include <string>
#include <vector>
#include <utility>

// ─── Mouse hit-testing ────────────────────────────────────────────────────────
// ─── Global dynamic search ────────────────────────────────────────────────────
struct SearchResult {
    enum class Kind { User, Project };
    Kind        kind = Kind::User;
    std::string title;     // "@login — Name" or project name
    std::string subtitle;  // seat / grade
    std::string key;       // login (user) or project name (project)
    std::string cdn;       // avatar URL for users (optional)
    int         room = -1; // user's room (0-3), -1 if unknown
    int         desk = -1; // user's desk index, -1 if unknown
};

struct SearchState {
    bool                      focus = false;
    std::string               query;
    int                       sel = 0;
    std::vector<SearchResult> results;
};

enum class MouseAction {
    None,
    TabBar,       // index = tab (0-3)
    DashSubview,  // index = subview (0-2)
    ListRow,      // index = absolute row in the active tab's list
    ClusterRoom,  // index = room (0-3)
    ClusterDesk,  // index = desk (0-47)
    DashMinimap,  // index = room * CELLS + desk (dashboard minimap)
    SearchBar,    // global search bar
    SearchResult, // index = result index
    LoginMethod,  // index = login method (0-2)
    LoginField,   // index = field (0-1)
    ThemeRow,     // index = theme (0-9)
    ActionRow,    // index = project action menu row
    MenuItem,     // index = root menu row
    SettingsRow,  // index = settings row (offset by scroll)
    ConfirmChoice,// index = 0 (yes) / 1 (no)
};

// ─── Main (Esc) menu ──────────────────────────────────────────────────────────
enum class MenuPage { None, Root, Settings, Help, About };

struct MenuEntry {
    std::string label;
    std::string value;      // right-aligned value for settings rows
    std::string shortcut;   // optional single-key hint shown in brackets
    bool        enabled  = true;
    bool        modified = false;
    bool        is_save  = false;
};

struct MenuState {
    MenuPage     page   = MenuPage::None;
    int          sel    = 0;   // selected row (Root / Settings)
    int          scroll = 0;   // first visible row / help scroll offset
    bool         dirty  = false;
    std::vector<MenuEntry> root_items;
    std::vector<MenuEntry> settings_items;

    // Confirmation dialog layered over the menu
    bool        confirm_open  = false;
    std::string confirm_title;
    std::string confirm_msg;

    // Single-value edit popup layered over the menu
    bool        edit_open  = false;
    std::string edit_title;
    std::string edit_value;
};

struct MouseHit {
    MouseAction action = MouseAction::None;
    int         index  = -1;
};

/**
 * TUI renderer — wraps ncurses and draws the three-tab layout.
 * All draw methods must be called from the UI (main) thread only.
 */
class Renderer {
public:
    Renderer();
    ~Renderer();

    // Non-copyable
    Renderer(const Renderer&)            = delete;
    Renderer& operator=(const Renderer&) = delete;

    /**
     * Draw one full frame.
     * Takes a snapshot of SharedState under its mutex.
     */
    // Shared do-nothing menu used when a caller omits the menu argument.
    inline static MenuState default_menu_{};

    void draw(SharedState& state, Tab current_tab,
              int slot_sel, int tree_sel, int cluster_sel,
              bool login_mode, int login_method, int active_field,
              const std::string& login_buf, const std::string& pass_buf,
              const std::string& cookie_buf, const std::string& detected_file,
              bool theme_switcher_open = false, int theme_sel = 0,
              int dash_subview = 0, int dash_sel = 0, bool dash_inspect = false,
              int cluster_room = 0,
              bool preview_panel = false,
              const SubjectPreview& preview = SubjectPreview{},
              bool subject_modal = false,
              int subject_scroll = 0,
              bool action_menu_open = false,
              const std::vector<std::pair<std::string, bool>>& action_items = {},
              int action_sel = 0,
              int minimap_hover = -1,
              bool user_modal_open = false,
              const std::string& user_modal_login = std::string(),
              const SearchState& search = SearchState{},
              MenuState& menu = default_menu_);

    void refresh_now();

    int terminal_cols() const;
    int terminal_rows() const;

    /** Resolve a screen cell to a clickable target from the last drawn frame. */
    MouseHit hit_test(int y, int x) const;

private:
    struct Hitbox {
        int         y = 0, x = 0, h = 1, w = 0;
        MouseAction action = MouseAction::None;
        int         index  = -1;
    };

    void add_hitbox(int y, int x, int h, int w, MouseAction action, int index) {
        hitboxes_.push_back({y, x, h, w, action, index});
    }

    void draw_tab_bar(Tab current_tab, bool loading);
    void draw_search_bar(const SearchState& s, int row);
    void draw_search_results(const SearchState& s, int top, int bottom);
    void draw_status_bar(const std::string& login,
                         const std::string& status_msg,
                         const std::string& error_msg,
                         Tab tab);

    void draw_profile_panel(const Profile& p, int top, int bottom, int width);

    void draw_dashboard(const Profile& p, int subview, int sel, bool inspect, int top, int bottom, int left_w);
    void draw_projects (const Profile& p, int sel, int top, int bottom, int left_w,
                        bool preview_panel, const SubjectPreview& pv);
    void draw_slots    (const Profile& p, int sel, int top, int bottom, int left_w);
    void draw_roadmap  (Profile& p, int sel, int top, int bottom, int left_w,
                        bool preview_panel, const SubjectPreview& pv);
    void draw_cluster  (const Profile& p, int room, int sel, int top, int bottom, int left_w);
    void draw_cluster_minimap(const Profile& p, int top, int bottom, int panel_w, int hovered);
    void draw_cluster_tooltip(const Profile& p,
                              const std::unordered_map<std::string, ClusterProfileEntry>& profiles,
                              int top, int bottom, int panel_w);

    void draw_login_prompt(int login_method, int active_field,
                           const std::string& user_buf,
                           const std::string& pass_buf,
                           const std::string& cookie_buf,
                           const std::string& detected_file,
                           const std::string& error_msg,
                           bool loading, const std::string& status_msg);

    void draw_theme_switcher(int active_idx);

    // Esc menu + sub-screens
    void draw_main_menu(MenuState& menu);
    void draw_settings(MenuState& menu);
    void draw_help(MenuState& menu);
    void draw_about();
    void draw_confirm_dialog(const MenuState& menu);
    void draw_edit_popup(const MenuState& menu);

    // Subject (PDF) preview
    struct ImageBox { int row = 0, col = 0, w = 0, h = 0; bool visible = false; };
    ImageBox draw_subject_panel(const SubjectPreview& pv, int x, int top, int bottom, int w);
    ImageBox draw_subject_modal(const SubjectPreview& pv, int scroll);
    void draw_action_menu(const std::vector<std::pair<std::string, bool>>& items, int sel);
    void draw_user_modal(const Profile& p,
                         const std::unordered_map<std::string, ClusterProfileEntry>& profiles,
                         const std::string& login);

    std::vector<Hitbox> hitboxes_;
    ImageBox            preview_img_;
    std::string         image_sig_;

    // Hover geometry for the dashboard cluster minimap (screen cell of the
    // hovered desk) so the tooltip can be anchored without recomputing layout.
    struct MinimapBox { int y = 0, x = 0, w = 0; bool valid = false; };
    MinimapBox          minimap_hover_box_;
    int                 minimap_hover_ = -1;

    // Avatar box for the full-screen user profile modal, so the image renderer
    // can place the viewed user's photo inside its frame (and suppress the base
    // dashboard/cluster photos while the modal is open).
    ImageBox            user_modal_avatar_box_;
    std::string         user_modal_avatar_key_;

    int cols_{80};
    int rows_{24};
};
