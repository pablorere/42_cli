#include "theme.hpp"
#include <ncurses.h>
#include <algorithm>
#include <cctype>

namespace theme {

static const std::vector<ThemePalette> s_themes = {
    // 1. Catppuccin Mocha
    {
        "catppuccin_mocha",
        "Catppuccin Mocha",
        0x1e1e2e, // bg_primary
        0x181825, // bg_secondary
        0xcdd6f4, // fg_text
        0x6c7086, // fg_muted
        0x89b4fa, // border (Blue)
        0xcba6f7, // accent (Mauve)
        0xa6e3a1, // success (Green)
        0xf9e2af, // warning (Peach/Yellow)
        0xf38ba8, // error (Red)
        false
    },
    // 2. Nord
    {
        "nord",
        "Nord",
        0x2e3440, // bg_primary (nord0)
        0x242933, // bg_secondary
        0xe5e9f0, // fg_text (nord5)
        0x4c566a, // fg_muted (nord3)
        0x88c0d0, // border (nord8 Frost)
        0x81a1c1, // accent (nord9)
        0xa3be8c, // success (nord14 Green)
        0xebcb8b, // warning (nord13 Yellow)
        0xbf616a, // error (nord11 Red)
        false
    },
    // 3. Gruvbox Dark
    {
        "gruvbox_dark",
        "Gruvbox Dark",
        0x282828, // bg_primary
        0x1d2021, // bg_secondary
        0xebdbb2, // fg_text
        0x928374, // fg_muted
        0xfe8019, // border (Orange)
        0xd3869b, // accent (Purple)
        0xb8bb26, // success (Green)
        0xfabd2f, // warning (Yellow)
        0xfb4934, // error (Red)
        false
    },
    // 4. Dracula
    {
        "dracula",
        "Dracula",
        0x282a36, // bg_primary
        0x1e1f29, // bg_secondary
        0xf8f8f2, // fg_text
        0x6272a4, // fg_muted (Comment)
        0xbd93f9, // border (Purple)
        0xff79c6, // accent (Pink)
        0x50fa7b, // success (Green)
        0xf1fa8c, // warning (Yellow)
        0xff5555, // error (Red)
        false
    },
    // 5. Tokyo Night
    {
        "tokyo_night",
        "Tokyo Night",
        0x1a1b26, // bg_primary
        0x16161e, // bg_secondary
        0xc0caf5, // fg_text
        0x565f89, // fg_muted
        0x7aa2f7, // border (Blue)
        0xbb9af7, // accent (Purple)
        0x9ece6a, // success (Green)
        0xe0af68, // warning (Yellow)
        0xf7768e, // error (Red)
        false
    },
    // 6. Matrix Phosphor
    {
        "matrix_phosphor",
        "Matrix Phosphor",
        0x0d110d, // bg_primary
        0x050805, // bg_secondary
        0x00ff66, // fg_text
        0x005522, // fg_muted
        0x00cc44, // border
        0x33ff88, // accent
        0x00ff66, // success
        0x88ff00, // warning
        0xff3333, // error
        true
    },
    // 7. Solarized Dark
    {
        "solarized_dark",
        "Solarized Dark",
        0x002b36, // bg_primary (base03)
        0x073642, // bg_secondary (base02)
        0x839496, // fg_text (base0)
        0x586e75, // fg_muted (base01)
        0x268bd2, // border (Blue)
        0x2aa198, // accent (Cyan)
        0x859900, // success (Green)
        0xb58900, // warning (Yellow)
        0xdc322f, // error (Red)
        false
    },
    // 8. Amber CRT
    {
        "amber_crt",
        "Amber CRT",
        0x140e04, // bg_primary
        0x0d0902, // bg_secondary
        0xffb000, // fg_text
        0x805800, // fg_muted
        0xff9900, // border
        0xffcc00, // accent
        0xffb000, // success
        0xffd700, // warning
        0xff3300, // error
        true
    },
    // 9. Cyberpunk Synthwave
    {
        "cyberpunk_synthwave",
        "Cyberpunk Synthwave",
        0x18122b, // bg_primary
        0x110b20, // bg_secondary
        0xfcee09, // fg_text (Neon Yellow)
        0x635985, // fg_muted
        0x05d9e8, // border (Neon Cyan)
        0xff2a85, // accent (Neon Pink)
        0x00ff9f, // success (Neon Mint)
        0xfcee09, // warning
        0xff0055, // error
        true
    },
    // 10. Monochrome Paper
    {
        "monochrome_paper",
        "Monochrome Paper",
        0x1a1a1a, // bg_primary
        0x121212, // bg_secondary
        0xe0e0e0, // fg_text
        0x757575, // fg_muted
        0xcccccc, // border
        0xffffff, // accent
        0xe0e0e0, // success
        0xaaaaaa, // warning
        0xffffff, // error
        false
    }
};

const std::vector<ThemePalette>& get_all_themes() {
    return s_themes;
}

static std::string normalize_slug(const std::string& input) {
    std::string norm;
    for (char ch : input) {
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            norm += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return norm;
}

int get_theme_index(const std::string& id_or_index) {
    if (id_or_index.empty()) return 0;

    // Check if numeric (1 to 10)
    try {
        int idx = std::stoi(id_or_index);
        if (idx >= 1 && idx <= static_cast<int>(s_themes.size())) {
            return idx - 1;
        }
    } catch (...) {}

    std::string norm = normalize_slug(id_or_index);
    for (size_t i = 0; i < s_themes.size(); ++i) {
        if (normalize_slug(s_themes[i].id) == norm ||
            normalize_slug(s_themes[i].display_name) == norm) {
            return static_cast<int>(i);
        }
    }
    return 0; // Default to Catppuccin Mocha
}

const ThemePalette& get_theme(const std::string& id_or_index) {
    int idx = get_theme_index(id_or_index);
    return s_themes[idx];
}

static short rgb_to_256(uint32_t rgb) {
    if (COLORS < 256) {
        uint8_t r = (rgb >> 16) & 0xFF;
        uint8_t g = (rgb >> 8) & 0xFF;
        uint8_t b = rgb & 0xFF;
        if (r > 180 && g > 180 && b > 180) return COLOR_WHITE;
        if (r < 60 && g < 60 && b < 60) return COLOR_BLACK;
        if (r > 150 && g > 150 && b < 100) return COLOR_YELLOW;
        if (r > 150 && g < 100 && b > 150) return COLOR_MAGENTA;
        if (r < 100 && g > 150 && b > 150) return COLOR_CYAN;
        if (r > 150 && g < 100 && b < 100) return COLOR_RED;
        if (r < 100 && g > 150 && b < 100) return COLOR_GREEN;
        if (r < 100 && g < 100 && b > 150) return COLOR_BLUE;
        return COLOR_WHITE;
    }

    uint8_t r = (rgb >> 16) & 0xFF;
    uint8_t g = (rgb >> 8) & 0xFF;
    uint8_t b = rgb & 0xFF;

    if (r == g && g == b) {
        if (r < 8) return 16;
        if (r > 248) return 231;
        return static_cast<short>(232 + ((r - 8) * 24 / 240));
    }

    auto get_cube_idx = [](uint8_t v) -> int {
        if (v < 48) return 0;
        if (v < 115) return 1;
        return (v - 35) / 40;
    };
    int ri = get_cube_idx(r);
    int gi = get_cube_idx(g);
    int bi = get_cube_idx(b);
    return static_cast<short>(16 + 36 * ri + 6 * gi + bi);
}

void apply_theme_to_ncurses(const ThemePalette& palette) {
    if (!has_colors()) return;

    short c_bg_pri   = rgb_to_256(palette.bg_primary);
    short c_bg_sec   = rgb_to_256(palette.bg_secondary);
    short c_fg_text  = rgb_to_256(palette.fg_text);
    short c_fg_muted = rgb_to_256(palette.fg_muted);
    short c_border   = rgb_to_256(palette.border);
    short c_accent   = rgb_to_256(palette.accent);
    short c_success  = rgb_to_256(palette.success);
    short c_warning  = rgb_to_256(palette.warning);
    short c_error    = rgb_to_256(palette.error);

    // Color pair indices as defined in renderer
    init_pair(1,  c_fg_text,  -1);         // CP_DEFAULT
    init_pair(2,  c_bg_pri,   c_accent);   // CP_TAB_ACTIVE
    init_pair(3,  c_accent,   -1);         // CP_TAB_IDLE
    init_pair(4,  c_bg_pri,   c_accent);   // CP_ROW_SEL
    init_pair(5,  c_bg_pri,   c_accent);   // CP_STATUS_L
    init_pair(6,  c_fg_text,  c_bg_sec);   // CP_STATUS_C
    init_pair(7,  c_bg_pri,   c_border);   // CP_STATUS_R
    init_pair(8,  c_border,   -1);         // CP_BORDER
    init_pair(9,  c_accent,   -1);         // CP_LABEL
    init_pair(10, c_fg_text,  -1);         // CP_VALUE
    init_pair(11, c_success,  -1);         // CP_SUCCESS
    init_pair(12, c_error,    -1);         // CP_FAIL
    init_pair(13, c_fg_muted, -1);         // CP_DIM
    init_pair(14, c_warning,  -1);         // CP_WARN
    init_pair(15, c_accent,   -1);         // CP_TITLE
    init_pair(16, c_fg_text,  c_bg_sec);   // CP_MODAL_BG
    init_pair(17, c_success,  -1);         // CP_PROGRESS (foreground: success, bg: theme default)
    init_pair(18, c_bg_pri,   c_accent);   // CP_HEADER_ROW
    init_pair(19, c_accent,   -1);         // CP_IN_PROG
    init_pair(20, c_bg_pri,   c_success);  // CP_BADGE_PASS
    init_pair(21, c_fg_text,  c_error);    // CP_BADGE_FAIL
    init_pair(22, c_accent,   -1);         // CP_ACCENT
    init_pair(23, c_bg_sec,   c_success);  // CP_PILL_SUCCESS
    init_pair(24, c_bg_sec,   c_warning);  // CP_PILL_WARN
    init_pair(25, c_bg_sec,   c_error);    // CP_PILL_FAIL
    init_pair(26, c_bg_sec,   c_accent);   // CP_PILL_ACCENT
}

} // namespace theme
