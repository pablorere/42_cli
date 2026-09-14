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
#pragma GCC diagnostic pop

namespace image_renderer {

static std::mutex s_img_mtx;
static std::unordered_map<std::string, DecodedImage> s_img_cache;
static std::unordered_map<std::string, std::string>  s_png_cache; // Real PNG payload for Kitty Protocol

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
    return true;
}

bool has_image(const std::string& key) {
    std::lock_guard<std::mutex> lk(s_img_mtx);
    return s_img_cache.find(key) != s_img_cache.end();
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

void render_halfblock(const std::string& key,
                      int screen_row, int screen_col,
                      int box_w, int box_h,
                      int term_rows, int term_cols)
{
    if (box_w <= 0 || box_h <= 0) return;
    if (!clamp_box_to_terminal(screen_row, screen_col, box_w, box_h, term_rows, term_cols))
        return;

    DecodedImage img;
    {
        std::lock_guard<std::mutex> lk(s_img_mtx);
        auto it = s_img_cache.find(key);
        if (it == s_img_cache.end()) return;
        img = it->second;
    }

    int img_w = img.width;
    int img_h = img.height;
    if (img_w <= 0 || img_h <= 0 || img.rgb.empty()) return;

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

    // Center image inside the allocated box:
    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    // High-quality area-averaging box filter
    auto sample_box = [&](int x0, int x1, int y0, int y1, int& out_r, int& out_g, int& out_b) {
        x0 = std::clamp(x0, 0, img_w - 1);
        x1 = std::clamp(x1, x0 + 1, img_w);
        y0 = std::clamp(y0, 0, img_h - 1);
        y1 = std::clamp(y1, y0 + 1, img_h);

        uint64_t r_sum = 0, g_sum = 0, b_sum = 0;
        int count = 0;
        for (int y = y0; y < y1; ++y) {
            for (int x = x0; x < x1; ++x) {
                size_t idx = static_cast<size_t>(y * img_w + x) * 3;
                r_sum += img.rgb[idx];
                g_sum += img.rgb[idx + 1];
                b_sum += img.rgb[idx + 2];
                count++;
            }
        }
        if (count > 0) {
            out_r = static_cast<int>(r_sum / count);
            out_g = static_cast<int>(g_sum / count);
            out_b = static_cast<int>(b_sum / count);
        } else {
            size_t idx = static_cast<size_t>(y0 * img_w + x0) * 3;
            out_r = img.rgb[idx];
            out_g = img.rgb[idx + 1];
            out_b = img.rgb[idx + 2];
        }
    };

    // Render image rows
    for (int y = 0; y < render_rows; ++y) {
        int py_top = y * 2;
        int py_bot = y * 2 + 1;

        int src_y0_top = py_top * img_h / render_ph;
        int src_y1_top = (py_top + 1) * img_h / render_ph;
        int src_y0_bot = py_bot * img_h / render_ph;
        int src_y1_bot = (py_bot + 1) * img_h / render_ph;

        int term_row = (screen_row + pad_top + y) + 1;
        int term_col = (screen_col + pad_left) + 1;
        printf("\033[%d;%dH", term_row, term_col);

        for (int x = 0; x < render_cols; ++x) {
            int src_x0 = x * img_w / render_cols;
            int src_x1 = (x + 1) * img_w / render_cols;

            int r1 = 0, g1 = 0, b1 = 0;
            int r2 = 0, g2 = 0, b2 = 0;
            sample_box(src_x0, src_x1, src_y0_top, src_y1_top, r1, g1, b1);
            sample_box(src_x0, src_x1, src_y0_bot, src_y1_bot, r2, g2, b2);

            printf("\033[38;2;%d;%d;%d;48;2;%d;%d;%dm▀", r1, g1, b1, r2, g2, b2);
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
