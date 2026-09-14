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
 * Terminal graphics protocol selected for the current session.
 * Ordered from richest to most portable.
 */
enum class ImageProtocol {
    None,
    Kitty,
    ITerm2,
    Sixel,
    HalfBlock,
    Ansi256,
};

/**
 * Detects the best available inline-image protocol for the running terminal.
 * The result is cached after the first call. Order:
 *   Kitty env (Kitty/WezTerm/Ghostty) -> iTerm2 -> sixel -> truecolor
 *   half-blocks -> 256-color / ASCII fallback.
 */
ImageProtocol detect_protocol();

/**
 * Runs the one-time terminal capability probes (sixel query, cell pixel size)
 * and caches their results. Call this before ncurses takes over stdin so the
 * probe replies cannot be confused with user input.
 */
void warm_up();

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
 * Fetches the pixel dimensions of a cached image.
 * Returns false when the key is unknown.
 */
bool image_dimensions(const std::string& key, int& out_w, int& out_h);

/**
 * Unified image renderer:
 * Automatically picks the best protocol for the terminal (Kitty/iTerm2/Sixel
 * native graphics, or truecolor/256-color/ASCII half-block fallbacks) with
 * clean aspect-ratio downsampling.
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
 * Clears any images currently displayed on the terminal. Kitty graphics are
 * deleted with an explicit graphics escape; sixel/iTerm2/half-block backends
 * request a full ncurses repaint (see take_repaint_request()).
 * Should be called when switching tabs or exiting.
 */
void clear_images();

/**
 * Returns true once after clear_images() when the active backend needs the
 * caller to force a full ncurses repaint (sixel/iTerm2 and half-block draw
 * outside the ncurses cell model). The flag is reset on read.
 */
bool take_repaint_request();

} // namespace image_renderer
