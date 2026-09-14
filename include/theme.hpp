#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace theme {

struct ThemePalette {
    std::string id;
    std::string display_name;
    uint32_t bg_primary;
    uint32_t bg_secondary;
    uint32_t fg_text;
    uint32_t fg_muted;
    uint32_t border;
    uint32_t accent;
    uint32_t success;
    uint32_t warning;
    uint32_t error;
    bool enable_box_glow;
};

// ─── List of all 10 themes ───────────────────────────────────────────────────
const std::vector<ThemePalette>& get_all_themes();

// ─── Lookup theme by slug or 1-based index string ────────────────────────────
const ThemePalette& get_theme(const std::string& id_or_index);
int get_theme_index(const std::string& id_or_index);

// ─── Initialize ncurses color pairs for a given palette ──────────────────────
void apply_theme_to_ncurses(const ThemePalette& palette);

} // namespace theme
