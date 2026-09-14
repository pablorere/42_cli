#include "image_renderer.hpp"
#include <unordered_map>
#include <mutex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wsign-compare"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Declarations only — the implementation lives in stb_image_resize_impl.cpp.
#include "stb_image_resize2.h"
#pragma GCC diagnostic pop

namespace image_renderer {

static std::mutex s_img_mtx;
static std::unordered_map<std::string, DecodedImage> s_img_cache;
static std::unordered_map<std::string, std::string>  s_png_cache; // Real PNG payload for Kitty Protocol

// Pre-downsampled buffers for the ANSI half-block path, keyed by
// "<image-key>@<w>x<h>". Resampling is the expensive part of that path, so we
// pay it once per (image, target size) instead of on every repaint.
static std::unordered_map<std::string, DecodedImage> s_scaled_cache;
static constexpr size_t kScaledCacheLimit = 64;

static std::string scaled_cache_key(const std::string& key, int w, int h) {
    return key + "@" + std::to_string(w) + "x" + std::to_string(h);
}

static const char s_b64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

static std::string base64_encode(const std::string& in) {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(s_b64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(s_b64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

bool supports_kitty_graphics() {
    static int cached_result = -1;
    if (cached_result != -1) return cached_result == 1;

    // Check environment indicators for Ghostty, Kitty, WezTerm
    if (std::getenv("GHOSTTY_RESOURCES_DIR") != nullptr) { cached_result = 1; return true; }
    if (std::getenv("KITTY_WINDOW_ID") != nullptr)       { cached_result = 1; return true; }
    if (std::getenv("KITTY_PID") != nullptr)             { cached_result = 1; return true; }
    if (std::getenv("WEZTERM_PANE") != nullptr)          { cached_result = 1; return true; }

    const char* term = std::getenv("TERM");
    if (term) {
        std::string t(term);
        if (t.find("kitty") != std::string::npos || t.find("ghostty") != std::string::npos) {
            cached_result = 1;
            return true;
        }
    }

    const char* term_prog = std::getenv("TERM_PROGRAM");
    if (term_prog) {
        std::string tp(term_prog);
        if (tp == "ghostty" || tp == "kitty" || tp == "WezTerm") {
            cached_result = 1;
            return true;
        }
    }

    cached_result = 0;
    return false;
}

void clear_kitty_images() {
    if (supports_kitty_graphics()) {
        // Delete all placed Kitty images on screen
        printf("\033_Ga=d,d=A\033\\");
        fflush(stdout);
    }
}

bool load_image_from_bytes(const std::string& key, const std::string& data) {
    if (data.empty() || key.empty()) return false;

    // Validate magic bytes for JPEG / PNG
    bool is_jpeg = (data.size() >= 3 &&
                    static_cast<unsigned char>(data[0]) == 0xFF &&
                    static_cast<unsigned char>(data[1]) == 0xD8 &&
                    static_cast<unsigned char>(data[2]) == 0xFF);
    bool is_png  = (data.size() >= 8 &&
                    static_cast<unsigned char>(data[0]) == 0x89 &&
                    data[1] == 'P' && data[2] == 'N' && data[3] == 'G');

    if (!is_jpeg && !is_png) return false;

    int w = 0, h = 0, comp = 0;
    unsigned char* raw = stbi_load_from_memory(
        reinterpret_cast<const unsigned char*>(data.data()),
        static_cast<int>(data.size()),
        &w, &h, &comp, 3
    );

    if (!raw) return false;

    DecodedImage img;
    img.width  = w;
    img.height = h;
    img.rgb.assign(raw, raw + (w * h * 3));
    stbi_image_free(raw);

    // Prepare a genuine PNG payload for native Kitty Graphics Protocol
    std::string png_bytes;
    if (is_png) {
        png_bytes = data;
    } else {
        int png_len = 0;
        unsigned char* mem_png = stbi_write_png_to_mem(
            img.rgb.data(), img.width * 3, img.width, img.height, 3, &png_len
        );
        if (mem_png && png_len > 0) {
            png_bytes.assign(reinterpret_cast<const char*>(mem_png), png_len);
            free(mem_png);
        }
    }

    std::lock_guard<std::mutex> lk(s_img_mtx);
    s_img_cache[key] = std::move(img);
    if (!png_bytes.empty()) {
        s_png_cache[key] = std::move(png_bytes);
    }
    // Drop any stale downsampled variants of this image.
    const std::string prefix = key + "@";
    for (auto it = s_scaled_cache.begin(); it != s_scaled_cache.end();) {
        if (it->first.rfind(prefix, 0) == 0) it = s_scaled_cache.erase(it);
        else ++it;
    }
    return true;
}

bool has_image(const std::string& key) {
    std::lock_guard<std::mutex> lk(s_img_mtx);
    return s_img_cache.find(key) != s_img_cache.end();
}

bool image_dimensions(const std::string& key, int& out_w, int& out_h) {
    std::lock_guard<std::mutex> lk(s_img_mtx);
    auto it = s_img_cache.find(key);
    if (it == s_img_cache.end()) return false;
    out_w = it->second.width;
    out_h = it->second.height;
    return out_w > 0 && out_h > 0;
}

// ─── Clamp an image box to the visible terminal area ──────────────────────────
// Returns false when there is no room left to draw anything legible, so callers
// can bail out instead of emitting escapes that wrap/crush the picture.
static bool clamp_box_to_terminal(int& row, int& col,
                                  int& box_w, int& box_h,
                                  int term_rows, int term_cols)
{
    if (row < 0) row = 0;
    if (col < 0) col = 0;

    if (term_rows > 0) {
        int avail_h = term_rows - row;
        if (avail_h < 2) return false;
        if (box_h > avail_h) box_h = avail_h;
    }
    if (term_cols > 0) {
        int avail_w = term_cols - col;
        if (avail_w < 4) return false;
        if (box_w > avail_w) box_w = avail_w;
    }
    return box_w >= 4 && box_h >= 2;
}

void render_kitty(const std::string& key,
                  int screen_row, int screen_col,
                  int box_w, int box_h,
                  int term_rows, int term_cols)
{
    if (box_w <= 0 || box_h <= 0) return;
    if (!clamp_box_to_terminal(screen_row, screen_col, box_w, box_h, term_rows, term_cols))
        return;

    std::string png_data;
    int img_w = 0, img_h = 0;
    {
        std::lock_guard<std::mutex> lk(s_img_mtx);
        auto it = s_png_cache.find(key);
        if (it == s_png_cache.end()) return;
        png_data = it->second;

        auto it_img = s_img_cache.find(key);
        if (it_img != s_img_cache.end()) {
            img_w = it_img->second.width;
            img_h = it_img->second.height;
        }
    }
    if (png_data.empty() || img_w <= 0 || img_h <= 0) return;

    // Preserve 1:1 physical aspect ratio in character cells
    // In terminal cells, cell width : cell height is approximately 1:2.
    // So 1 character row in height equals 2 columns in width physical equivalent.
    double aspect = static_cast<double>(img_w) / static_cast<double>(img_h);

    int max_rows = box_h;
    int max_cols = box_w;

    int render_rows = max_rows;
    int render_cols = static_cast<int>(std::round((render_rows * 2) * aspect));
    if (render_cols > max_cols) {
        render_cols = max_cols;
        render_rows = static_cast<int>(std::round(render_cols / (2.0 * aspect)));
    }
    if (render_rows < 1) render_rows = 1;
    if (render_cols < 1) render_cols = 1;

    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    // Position cursor at 1-indexed (row, col) in terminal
    int term_row = (screen_row + pad_top) + 1;
    int term_col = (screen_col + pad_left) + 1;
    printf("\033[%d;%dH", term_row, term_col);

    std::string b64 = base64_encode(png_data);
    if (b64.empty()) return;

    // Stream base64 chunks of up to 4096 bytes via Kitty Graphics Protocol
    const size_t chunk_size = 4096;
    for (size_t i = 0; i < b64.size(); i += chunk_size) {
        size_t len = std::min(chunk_size, b64.size() - i);
        std::string chunk = b64.substr(i, len);
        bool has_more = (i + len < b64.size());

        if (i == 0) {
            // a=T (transmit and display), f=100 (real PNG), t=d (direct),
            // c=columns, r=rows, m=more
            printf("\033_Ga=T,f=100,t=d,c=%d,r=%d,m=%d;%s\033\\",
                   render_cols, render_rows, has_more ? 1 : 0, chunk.c_str());
        } else {
            // Continuation chunk
            printf("\033_Gm=%d;%s\033\\", has_more ? 1 : 0, chunk.c_str());
        }
    }
    // Park cursor away and hide cursor to eliminate blinking cursor over pictures
    printf("\033[?25l\033[1;1H");
    fflush(stdout);
}

// Returns a cached render_w x render_h RGB buffer for `key`, resampling the
// source once with stb_image_resize2 (Mitchell filter) and memoizing the result
// so repeated repaints (and window drags) are O(area) blits instead of O(area)
// resamples.
static bool get_scaled_rgb(const std::string& key, int render_w, int render_h, DecodedImage& out)
{
    if (render_w <= 0 || render_h <= 0) return false;
    const std::string sk = scaled_cache_key(key, render_w, render_h);

    std::lock_guard<std::mutex> lk(s_img_mtx);
    auto cached = s_scaled_cache.find(sk);
    if (cached != s_scaled_cache.end()) {
        out = cached->second;
        return true;
    }

    auto it = s_img_cache.find(key);
    if (it == s_img_cache.end()) return false;
    const DecodedImage& src = it->second;
    if (src.width <= 0 || src.height <= 0 || src.rgb.empty()) return false;

    DecodedImage dst;
    dst.width  = render_w;
    dst.height = render_h;
    dst.rgb.resize(static_cast<size_t>(render_w) * static_cast<size_t>(render_h) * 3);

    stbir_resize_uint8_srgb(src.rgb.data(), src.width, src.height, 0,
                            dst.rgb.data(), render_w, render_h, 0, STBIR_RGB);

    if (s_scaled_cache.size() >= kScaledCacheLimit) s_scaled_cache.clear();
    auto slot = s_scaled_cache.emplace(sk, std::move(dst)).first;
    out = slot->second;
    return true;
}

void render_halfblock(const std::string& key,
                      int screen_row, int screen_col,
                      int box_w, int box_h,
                      int term_rows, int term_cols)
{
    if (box_w <= 0 || box_h <= 0) return;
    if (!clamp_box_to_terminal(screen_row, screen_col, box_w, box_h, term_rows, term_cols))
        return;

    int img_w = 0, img_h = 0;
    {
        std::lock_guard<std::mutex> lk(s_img_mtx);
        auto it = s_img_cache.find(key);
        if (it == s_img_cache.end()) return;
        img_w = it->second.width;
        img_h = it->second.height;
    }
    if (img_w <= 0 || img_h <= 0) return;

    // Terminal character cells have an aspect ratio of approximately 1:2 (width:height).
    // Each half-block ('▀') represents 1/2 of a row vertically and 1 column horizontally,
    // which makes each half-block roughly 1:1 square.
    int max_pw = box_w;
    int max_ph = box_h * 2;

    double aspect = static_cast<double>(img_w) / static_cast<double>(img_h);

    // Fit inside box preserving source aspect ratio:
    int render_ph = max_ph;
    int render_pw = static_cast<int>(std::round(render_ph * aspect));
    if (render_pw > max_pw) {
        render_pw = max_pw;
        render_ph = static_cast<int>(std::round(render_pw / aspect));
    }
    // Vertical pixels must be even (each character cell holds 2 half-blocks)
    if (render_ph % 2 != 0) render_ph--;
    if (render_ph < 2) render_ph = 2;
    if (render_pw < 1) render_pw = 1;

    int render_cols = render_pw;
    int render_rows = render_ph / 2;

    // Resample once (memoized); the draw loop below is a straight 1:1 blit.
    DecodedImage scaled;
    if (!get_scaled_rgb(key, render_pw, render_ph, scaled)) return;

    // Center image inside the allocated box:
    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    const unsigned char* px = scaled.rgb.data();
    const int stride = render_pw * 3;

    // Render image rows
    for (int y = 0; y < render_rows; ++y) {
        int py_top = y * 2;
        int py_bot = y * 2 + 1;

        int term_row = (screen_row + pad_top + y) + 1;
        int term_col = (screen_col + pad_left) + 1;
        printf("\033[%d;%dH", term_row, term_col);

        const unsigned char* top = px + static_cast<size_t>(py_top) * stride;
        const unsigned char* bot = px + static_cast<size_t>(py_bot) * stride;

        for (int x = 0; x < render_cols; ++x) {
            const unsigned char* t = top + x * 3;
            const unsigned char* b = bot + x * 3;
            printf("\033[38;2;%d;%d;%d;48;2;%d;%d;%dm▀",
                   t[0], t[1], t[2], b[0], b[1], b[2]);
        }
    }
    printf("\033[0m\033[?25l\033[1;1H");
    fflush(stdout);
}

void render_image(const std::string& key,
                  int screen_row, int screen_col,
                  int width_chars, int height_chars,
                  int term_rows, int term_cols)
{
    if (supports_kitty_graphics()) {
        render_kitty(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
    } else {
        render_halfblock(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
    }
}

} // namespace image_renderer
