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
#include <cstdint>
#include <chrono>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>

#include "sixel.hpp"

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

// ─── Terminal capability probing ─────────────────────────────────────────────
// Some protocols (sixel) can only be confirmed by querying the terminal and
// reading its reply. This is only safe before ncurses takes over stdin, hence
// warm_up() is called from the renderer constructor.
static bool terminal_query(const char* query, std::string& reply, int timeout_ms) {
    reply.clear();
    if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO)) return false;

    struct termios oldt;
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) return false;

    struct termios raw = oldt;
    raw.c_lflag &= ~static_cast<tcflag_t>(ICANON | ECHO);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw) != 0) return false;

    tcflush(STDIN_FILENO, TCIFLUSH);
    ssize_t written = write(STDOUT_FILENO, query, std::strlen(query));
    (void)written;

    using clock = std::chrono::steady_clock;
    auto deadline = clock::now() + std::chrono::milliseconds(timeout_ms);
    char buf[256];
    while (clock::now() < deadline) {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        struct timeval tv;
        tv.tv_sec  = 0;
        tv.tv_usec = 5000;
        int r = select(STDIN_FILENO + 1, &fds, nullptr, nullptr, &tv);
        if (r > 0) {
            ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
            if (n > 0) {
                reply.append(buf, static_cast<std::size_t>(n));
                if (reply.size() > 2048) break;
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return !reply.empty();
}

// Parses a reply of the form ESC [ <lead> a ; b t and returns the pair.
static bool parse_csi_pair(const std::string& s, const std::string& lead,
                           int& a, int& b) {
    std::size_t pos = s.find(lead);
    if (pos == std::string::npos) return false;
    pos += lead.size();
    std::size_t end = s.find('t', pos);
    if (end == std::string::npos) return false;
    std::string body = s.substr(pos, end - pos);
    return std::sscanf(body.c_str(), "%d;%d", &a, &b) == 2;
}

// Terminal cell size in pixels. Queried once (CSI 14t window pixels + CSI 18t
// text-area cells), falling back to the 8×16 assumption the Kitty path makes.
static void get_cell_pixel_size(int& cw, int& ch) {
    static int cached_w = 0;
    static int cached_h = 0;
    if (cached_w <= 0 || cached_h <= 0) {
        int px_w = 0, px_h = 0, rows = 0, cols = 0;
        std::string reply;
        if (terminal_query("\033[14t\033[18t", reply, 90)) {
            parse_csi_pair(reply, "\033[4;", px_h, px_w);
            parse_csi_pair(reply, "\033[8;", rows, cols);
        }
        if (px_w > 0 && px_h > 0 && rows > 0 && cols > 0) {
            cached_w = std::max(1, px_w / cols);
            cached_h = std::max(1, px_h / rows);
        } else {
            cached_w = 8;
            cached_h = 16;
        }
    }
    cw = cached_w;
    ch = cached_h;
}

static bool env_contains(const char* name, const char* needle) {
    const char* v = std::getenv(name);
    return v != nullptr && std::strstr(v, needle) != nullptr;
}

static bool detect_kitty() {
    if (std::getenv("KITTY_WINDOW_ID") != nullptr ||
        std::getenv("KITTY_PID") != nullptr ||
        std::getenv("WEZTERM_PANE") != nullptr ||
        std::getenv("GHOSTTY_RESOURCES_DIR") != nullptr) {
        return true;
    }
    if (env_contains("TERM", "kitty") || env_contains("TERM", "ghostty")) return true;

    const char* tp = std::getenv("TERM_PROGRAM");
    if (tp != nullptr) {
        if (std::strcmp(tp, "kitty") == 0 || std::strcmp(tp, "ghostty") == 0 ||
            std::strcmp(tp, "WezTerm") == 0) {
            return true;
        }
    }
    return false;
}

static bool detect_iterm2() {
    const char* tp = std::getenv("TERM_PROGRAM");
    return tp != nullptr &&
           (std::strcmp(tp, "iTerm.app") == 0 || std::strcmp(tp, "iTerm2") == 0);
}

static bool sixel_env_hint() {
    return env_contains("TERM", "sixel") ||
           env_contains("TERM", "foot") ||
           env_contains("TERM", "mlterm") ||
           env_contains("TERM", "contour") ||
           env_contains("TERM", "yaft") ||
           env_contains("TERM_PROGRAM", "mlterm") ||
           std::getenv("SIXEL") != nullptr;
}

// XTSMGRAPHICS (CSI ? 1 ; Pa ; Pv S) is a sixel-specific geometry request; a
// well-formed reply implies the terminal implements sixel graphics.
static bool probe_sixel() {
    std::string reply;
    if (!terminal_query("\033[?1;1;0S", reply, 60)) return false;
    return reply.find("\033[?1;") != std::string::npos;
}

ImageProtocol detect_protocol() {
    static ImageProtocol cached = ImageProtocol::None;
    static bool done = false;
    if (done) return cached;

    if (detect_kitty()) {
        cached = ImageProtocol::Kitty;
    } else if (detect_iterm2()) {
        cached = ImageProtocol::ITerm2;
    } else if (sixel_env_hint() || probe_sixel()) {
        cached = ImageProtocol::Sixel;
    } else {
        const char* ct = std::getenv("COLORTERM");
        bool truecolor = ct != nullptr &&
                         (std::strstr(ct, "truecolor") != nullptr ||
                          std::strstr(ct, "24bit") != nullptr);
        cached = truecolor ? ImageProtocol::HalfBlock : ImageProtocol::Ansi256;
    }
    done = true;
    return cached;
}

void warm_up() {
    detect_protocol();
    int cw = 0, ch = 0;
    get_cell_pixel_size(cw, ch);
    // Drop any late capability replies so ncurses never reads them as keys.
    tcflush(STDIN_FILENO, TCIFLUSH);
}

static bool s_repaint_requested = false;

void clear_images() {
    if (detect_protocol() == ImageProtocol::Kitty) {
        // Delete all placed Kitty images on screen.
        printf("\033_Ga=d,d=A\033\\");
        fflush(stdout);
    } else {
        // Sixel/iTerm2 pixels and raw half-block glyphs are invisible to the
        // ncurses cell model, so the caller must force a full repaint.
        s_repaint_requested = true;
    }
}

bool take_repaint_request() {
    bool v = s_repaint_requested;
    s_repaint_requested = false;
    return v;
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

// High-quality area-averaging downsampler. Fills `out` with dw×dh RGB pixels
// sampled from the source with a box filter (each destination pixel averages
// every source pixel that maps onto it).
static void resample_area(const DecodedImage& img, int dw, int dh,
                          std::vector<unsigned char>& out) {
    out.assign(static_cast<std::size_t>(dw) * dh * 3, 0);

    for (int dy = 0; dy < dh; ++dy) {
        int sy0 = static_cast<int>(static_cast<long long>(dy) * img.height / dh);
        int sy1 = static_cast<int>(static_cast<long long>(dy + 1) * img.height / dh);
        if (sy1 <= sy0) sy1 = sy0 + 1;
        if (sy0 >= img.height) sy0 = img.height - 1;
        if (sy1 > img.height) sy1 = img.height;

        for (int dx = 0; dx < dw; ++dx) {
            int sx0 = static_cast<int>(static_cast<long long>(dx) * img.width / dw);
            int sx1 = static_cast<int>(static_cast<long long>(dx + 1) * img.width / dw);
            if (sx1 <= sx0) sx1 = sx0 + 1;
            if (sx0 >= img.width) sx0 = img.width - 1;
            if (sx1 > img.width) sx1 = img.width;

            unsigned long long rs = 0, gs = 0, bs = 0;
            int count = 0;
            for (int sy = sy0; sy < sy1; ++sy) {
                for (int sx = sx0; sx < sx1; ++sx) {
                    std::size_t p = (static_cast<std::size_t>(sy) * img.width + sx) * 3;
                    rs += img.rgb[p];
                    gs += img.rgb[p + 1];
                    bs += img.rgb[p + 2];
                    ++count;
                }
            }

            std::size_t o = (static_cast<std::size_t>(dy) * dw + dx) * 3;
            if (count > 0) {
                out[o]     = static_cast<unsigned char>(rs / count);
                out[o + 1] = static_cast<unsigned char>(gs / count);
                out[o + 2] = static_cast<unsigned char>(bs / count);
            } else {
                std::size_t p = (static_cast<std::size_t>(sy0) * img.width + sx0) * 3;
                out[o]     = img.rgb[p];
                out[o + 1] = img.rgb[p + 1];
                out[o + 2] = img.rgb[p + 2];
            }
        }
    }
}

static int rgb_to_256(int r, int g, int b) {
    int ri = (r * 5 + 127) / 255;
    int gi = (g * 5 + 127) / 255;
    int bi = (b * 5 + 127) / 255;
    return 16 + 36 * ri + 6 * gi + bi;
}

static int luminance(int r, int g, int b) {
    return (r * 299 + g * 587 + b * 114) / 1000;
}

enum class ColorMode { TrueColor, Ansi256, Ascii };

// Shared half-block renderer. Truecolor and 256-color modes emit `▀` with
// foreground = top pixel and background = bottom pixel; ASCII mode falls back
// to a luminance ramp for terminals with no color support at all.
static void render_blocks(const std::string& key,
                          int screen_row, int screen_col,
                          int box_w, int box_h,
                          int term_rows, int term_cols,
                          ColorMode mode)
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

    // Terminal character cells are roughly 1:2 (width:height), so each half-block
    // ('▀') is about square. Fit the source into the box preserving aspect ratio.
    int max_pw = box_w;
    int max_ph = box_h * 2;

    double aspect = static_cast<double>(img_w) / static_cast<double>(img_h);

    int render_ph = max_ph;
    int render_pw = static_cast<int>(std::round(render_ph * aspect));
    if (render_pw > max_pw) {
        render_pw = max_pw;
        render_ph = static_cast<int>(std::round(render_pw / aspect));
    }
    // Vertical pixels must be even (each character cell holds 2 half-blocks).
    if (render_ph % 2 != 0) render_ph--;
    if (render_ph < 2) render_ph = 2;
    if (render_pw < 1) render_pw = 1;

    int render_cols = render_pw;
    int render_rows = render_ph / 2;

    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    std::vector<unsigned char> buf;
    resample_area(img, render_cols, render_ph, buf);

    static const char kAsciiRamp[] = " .:-=+*#%@";

    for (int y = 0; y < render_rows; ++y) {
        int term_row = (screen_row + pad_top + y) + 1;
        int term_col = (screen_col + pad_left) + 1;
        printf("\033[%d;%dH", term_row, term_col);

        for (int x = 0; x < render_cols; ++x) {
            std::size_t top = (static_cast<std::size_t>(y * 2) * render_cols + x) * 3;
            std::size_t bot = (static_cast<std::size_t>(y * 2 + 1) * render_cols + x) * 3;
            int r1 = buf[top], g1 = buf[top + 1], b1 = buf[top + 2];
            int r2 = buf[bot], g2 = buf[bot + 1], b2 = buf[bot + 2];

            if (mode == ColorMode::TrueColor) {
                printf("\033[38;2;%d;%d;%d;48;2;%d;%d;%dm▀", r1, g1, b1, r2, g2, b2);
            } else if (mode == ColorMode::Ansi256) {
                printf("\033[38;5;%d;48;5;%dm▀", rgb_to_256(r1, g1, b1), rgb_to_256(r2, g2, b2));
            } else {
                int avg = (luminance(r1, g1, b1) + luminance(r2, g2, b2)) / 2;
                int ri = avg * static_cast<int>(sizeof(kAsciiRamp) - 2) / 255;
                printf("%c", kAsciiRamp[ri]);
            }
        }
    }
    printf("\033[0m\033[?25l\033[1;1H");
    fflush(stdout);
}

void render_halfblock(const std::string& key,
                      int screen_row, int screen_col,
                      int box_w, int box_h,
                      int term_rows, int term_cols)
{
    render_blocks(key, screen_row, screen_col, box_w, box_h,
                  term_rows, term_cols, ColorMode::TrueColor);
}

// 256-color half-blocks, or a plain luminance ramp when the terminal reports no
// color support. Never emits truecolor escapes on a non-truecolor terminal.
static void render_ansi256(const std::string& key,
                           int screen_row, int screen_col,
                           int box_w, int box_h,
                           int term_rows, int term_cols)
{
    bool color = env_contains("TERM", "256color") ||
                 env_contains("TERM", "xterm") ||
                 env_contains("TERM", "foot") ||
                 std::getenv("COLORTERM") != nullptr;
    render_blocks(key, screen_row, screen_col, box_w, box_h,
                  term_rows, term_cols,
                  color ? ColorMode::Ansi256 : ColorMode::Ascii);
}

// iTerm2 inline images (OSC 1337 File=...). Self-contained: the original PNG is
// base64-encoded and the terminal scales it into the requested cell box.
static void render_iterm2(const std::string& key,
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

    double aspect = static_cast<double>(img_w) / static_cast<double>(img_h);
    int render_rows = box_h;
    int render_cols = static_cast<int>(std::round((render_rows * 2) * aspect));
    if (render_cols > box_w) {
        render_cols = box_w;
        render_rows = static_cast<int>(std::round(render_cols / (2.0 * aspect)));
    }
    if (render_rows < 1) render_rows = 1;
    if (render_cols < 1) render_cols = 1;

    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;
    int term_row = (screen_row + pad_top) + 1;
    int term_col = (screen_col + pad_left) + 1;

    std::string b64 = base64_encode(png_data);
    if (b64.empty()) return;

    printf("\033[%d;%dH", term_row, term_col);
    printf("\033]1337;File=inline=1;width=%d;height=%d;preserveAspectRatio=1:%s\a",
           render_cols, render_rows, b64.c_str());
    printf("\033[?25l\033[1;1H");
    fflush(stdout);
}

// Vendored sixel backend. Resamples to the target pixel box (using the probed
// cell size) and writes a self-contained sixel stream.
static void render_sixel(const std::string& key,
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
    if (img.width <= 0 || img.height <= 0 || img.rgb.empty()) return;

    int cw = 8, ch = 16;
    get_cell_pixel_size(cw, ch);

    long long max_px_w = static_cast<long long>(box_w) * cw;
    long long max_px_h = static_cast<long long>(box_h) * ch;
    double aspect = static_cast<double>(img.width) / static_cast<double>(img.height);

    long long rw = max_px_w;
    long long rh = static_cast<long long>(std::llround(static_cast<double>(rw) / aspect));
    if (rh > max_px_h) {
        rh = max_px_h;
        rw = static_cast<long long>(std::llround(static_cast<double>(rh) * aspect));
    }
    if (rw < 1) rw = 1;
    if (rh < 1) rh = 1;

    int render_cols = static_cast<int>((rw + cw - 1) / cw);
    int render_rows = static_cast<int>((rh + ch - 1) / ch);
    if (render_cols > box_w) render_cols = box_w;
    if (render_rows > box_h) render_rows = box_h;

    int pad_left = (box_w - render_cols) / 2;
    int pad_top  = (box_h - render_rows) / 2;

    std::vector<unsigned char> buf;
    resample_area(img, static_cast<int>(rw), static_cast<int>(rh), buf);

    std::string seq = sixel::encode(buf.data(), static_cast<int>(rw), static_cast<int>(rh));
    if (seq.empty()) return;

    int term_row = (screen_row + pad_top) + 1;
    int term_col = (screen_col + pad_left) + 1;
    printf("\033[%d;%dH", term_row, term_col);
    fwrite(seq.data(), 1, seq.size(), stdout);
    printf("\033[?25l\033[1;1H");
    fflush(stdout);
}

void render_image(const std::string& key,
                  int screen_row, int screen_col,
                  int width_chars, int height_chars,
                  int term_rows, int term_cols)
{
    switch (detect_protocol()) {
        case ImageProtocol::Kitty:
            render_kitty(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
            break;
        case ImageProtocol::ITerm2:
            render_iterm2(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
            break;
        case ImageProtocol::Sixel:
            render_sixel(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
            break;
        case ImageProtocol::HalfBlock:
            render_halfblock(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
            break;
        case ImageProtocol::None:
        case ImageProtocol::Ansi256:
        default:
            render_ansi256(key, screen_row, screen_col, width_chars, height_chars, term_rows, term_cols);
            break;
    }
}

} // namespace image_renderer
