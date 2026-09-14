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
#include <unistd.h>

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

// Optional external `chafa` bridge: cached ANSI/sixel art for terminals that
// support neither Kitty nor the iTerm2 protocol (e.g. xterm, foot).
static std::unordered_map<std::string, std::string> s_chafa_cache;
static constexpr size_t kChafaCacheLimit = 32;

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

bool supports_iterm2_images() {
    static int cached_result = -1;
    if (cached_result != -1) return cached_result == 1;

    cached_result = 0;
    const char* term_prog = std::getenv("TERM_PROGRAM");
    if (term_prog) {
        std::string tp(term_prog);
        if (tp == "iTerm.app" || tp == "WezTerm" || tp == "mintty") cached_result = 1;
    }
    const char* lc_term = std::getenv("LC_TERMINAL");
    if (lc_term && std::string(lc_term) == "iTerm2") cached_result = 1;

    const char* term = std::getenv("TERM");
    if (term && std::string(term).find("konsole") != std::string::npos) cached_result = 1;

    return cached_result == 1;
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
    for (auto it = s_chafa_cache.begin(); it != s_chafa_cache.end();) {
        if (it->first.rfind(prefix, 0) == 0) it = s_chafa_cache.erase(it);
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

// Fits an image inside a cell box, preserving physical aspect ratio. Terminal
// cells are ~1:2 (width:height), so one cell row equals two cell columns.
static void fit_box_cells(int img_w, int img_h, int box_w, int box_h,
                          int& render_rows, int& render_cols)
{
    double aspect = (img_h > 0) ? static_cast<double>(img_w) / static_cast<double>(img_h) : 1.0;

    render_rows = box_h;
    render_cols = static_cast<int>(std::round((render_rows * 2) * aspect));
    if (render_cols > box_w) {
        render_cols = box_w;
        render_rows = static_cast<int>(std::round(render_cols / (2.0 * aspect)));
    }
    if (render_rows < 1) render_rows = 1;
    if (render_cols < 1) render_cols = 1;
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

    int render_rows = 0, render_cols = 0;
    fit_box_cells(img_w, img_h, box_w, box_h, render_rows, render_cols);

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

// iTerm2 inline-image protocol (OSC 1337). Supported by iTerm2, WezTerm,
// Konsole, mintty and a handful of others. Images are anchored to the text
// cells, so they are cleared automatically when ncurses repaints the region
// (no explicit delete escape is needed, unlike Kitty).
void render_iterm2(const std::string& key,
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

    int render_rows = 0, render_cols = 0;
    fit_box_cells(img_w, img_h, box_w, box_h, render_rows, render_cols);

    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    int term_row = (screen_row + pad_top) + 1;
    int term_col = (screen_col + pad_left) + 1;

    std::string b64 = base64_encode(png_data);
    if (b64.empty()) return;

    printf("\033[%d;%dH", term_row, term_col);
    // inline=1, width/height in character cells, explicit size (aspect already
    // preserved by fit_box_cells). Terminated by BEL.
    printf("\033]1337;File=inline=1;width=%d;height=%d;preserveAspectRatio=0:%s\a",
           render_cols, render_rows, b64.c_str());
    printf("\033[?25l\033[1;1H");
    fflush(stdout);
}

// ─── Optional chafa bridge ───────────────────────────────────────────────────
static bool executable_on_path(const char* name) {
    const char* path = std::getenv("PATH");
    if (!path) return false;
    const std::string p(path);
    size_t start = 0;
    while (start <= p.size()) {
        size_t end = p.find(':', start);
        std::string dir = (end == std::string::npos) ? p.substr(start) : p.substr(start, end - start);
        if (dir.empty()) dir = ".";
        if (access((dir + "/" + name).c_str(), X_OK) == 0) return true;
        if (end == std::string::npos) break;
        start = end + 1;
    }
    return false;
}

bool supports_chafa() {
    static int cached = -1;
    if (cached == -1) cached = executable_on_path("chafa") ? 1 : 0;
    return cached == 1;
}

// Runs chafa on the cached PNG and memoizes its rendered output for (key, size).
static bool get_chafa_art(const std::string& key, int cols, int rows, std::string& out) {
    if (cols <= 0 || rows <= 0) return false;
    const std::string ck = scaled_cache_key(key, cols, rows);

    std::string png;
    {
        std::lock_guard<std::mutex> lk(s_img_mtx);
        auto it = s_chafa_cache.find(ck);
        if (it != s_chafa_cache.end()) { out = it->second; return true; }
        auto pit = s_png_cache.find(key);
        if (pit == s_png_cache.end()) return false;
        png = pit->second;
    }
    if (png.empty()) return false;

    // chafa reads a file; stage the PNG in a private temp file.
    char tmpl[] = "/tmp/42cli-chafa-XXXXXX";
    int fd = mkstemp(tmpl);
    if (fd < 0) return false;
    size_t off = 0;
    while (off < png.size()) {
        ssize_t n = write(fd, png.data() + off, png.size() - off);
        if (n <= 0) { close(fd); unlink(tmpl); return false; }
        off += static_cast<size_t>(n);
    }
    close(fd);

    std::string cmd = "chafa --format=symbols --symbols=block --size " +
                      std::to_string(cols) + "x" + std::to_string(rows) +
                      " " + tmpl + " 2>/dev/null";
    std::string art;
    if (FILE* pipe = popen(cmd.c_str(), "r")) {
        char buf[4096];
        size_t got;
        while ((got = fread(buf, 1, sizeof(buf), pipe)) > 0) art.append(buf, got);
        pclose(pipe);
    }
    unlink(tmpl);
    if (art.empty()) return false;

    std::lock_guard<std::mutex> lk(s_img_mtx);
    if (s_chafa_cache.size() >= kChafaCacheLimit) s_chafa_cache.clear();
    s_chafa_cache[ck] = art;
    out = std::move(art);
    return true;
}

void render_chafa(const std::string& key,
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

    int render_rows = 0, render_cols = 0;
    fit_box_cells(img_w, img_h, box_w, box_h, render_rows, render_cols);

    std::string art;
    if (!get_chafa_art(key, render_cols, render_rows, art)) return;

    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    // chafa emits newline-separated rows; blit each one at an explicit cursor
    // position so the art stays anchored inside its box.
    int row = screen_row + pad_top + 1;
    int col = screen_col + pad_left + 1;
    size_t start = 0;
    while (start < art.size() && row < screen_row + pad_top + render_rows + 1) {
        size_t nl = art.find('\n', start);
        std::string line = (nl == std::string::npos) ? art.substr(start) : art.substr(start, nl - start);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        printf("\033[%d;%dH%s", row, col, line.c_str());
        ++row;
        if (nl == std::string::npos) break;
        start = nl + 1;
    }
    printf("\033[0m\033[?25l\033[1;1H");
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
    } else if (supports_iterm2_images()) {
        render_iterm2(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
    } else if (supports_chafa()) {
        render_chafa(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
    } else {
        render_halfblock(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
    }
}

} // namespace image_renderer
