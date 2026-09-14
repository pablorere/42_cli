#pragma once
#include <string>
#include <vector>

namespace image_renderer {

struct DecodedImage {
    int width = 0;
    int height = 0;
    std::vector<unsigned char> rgb; // 3 bytes per pixel (R, G, B)
};

/**
 * Auto-detects if the running terminal supports native GPU pixel graphics
 * via the Kitty Graphics Protocol (Ghostty, Kitty, WezTerm).
 */
bool supports_kitty_graphics();

/**
 * Loads and caches an image from raw memory bytes (JPEG / PNG).
 * Caches both decoded RGB buffer and raw payload for native graphics.
 * Returns true on success.
 */
bool load_image_from_bytes(const std::string& key, const std::string& data);

/**
 * Returns true if image with key is loaded in memory cache.
 */
bool has_image(const std::string& key);

/**
 * Unified image renderer:
 * Automatically uses Kitty Graphics Protocol (native screen pixel density,
 * zero pixelation) in Ghostty/Kitty/WezTerm, or falls back to 24-bit ANSI
 * truecolor half-blocks (▀) with clean aspect ratio downsampling.
 *
 * term_rows / term_cols are the current terminal dimensions (in cells). When
 * non-zero the image box is clamped so it can never be drawn past the screen
 * edge (which would wrap/crush the picture on small or freshly-resized
 * terminals). Pass 0 to disable clamping.
 */
void render_image(const std::string& key,
                  int screen_row, int screen_col,
                  int width_chars, int height_chars,
                  int term_rows = 0, int term_cols = 0);

/**
 * Renders an image using 24-bit ANSI truecolor half-blocks (▀)
 * directly into the terminal at 1-indexed (screen_row, screen_col).
 */
void render_halfblock(const std::string& key,
                      int screen_row, int screen_col,
                      int width_chars, int height_chars,
                      int term_rows = 0, int term_cols = 0);

/**
 * Clears all Kitty protocol graphics currently displayed on the terminal.
 * Should be called when switching tabs or exiting.
 */
void clear_kitty_images();

} // namespace image_renderer
