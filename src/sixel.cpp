#include "sixel.hpp"

#include <cstdio>
#include <vector>
#include <algorithm>

namespace sixel {

namespace {

const int kCubeLevels  = 6;   // 6×6×6 = 216 cube colors
const int kCubeColors  = kCubeLevels * kCubeLevels * kCubeLevels;
const int kGrayCount   = 24;  // 24-step grayscale ramp
const int kPaletteSize = kCubeColors + kGrayCount; // 240

// 4×4 ordered (Bayer) dither matrix, values 0..15.
const int kBayer[4][4] = {
    {  0,  8,  2, 10 },
    { 12,  4, 14,  6 },
    {  3, 11,  1,  9 },
    { 15,  7, 13,  5 },
};

inline int clamp255(int v) {
    return v < 0 ? 0 : (v > 255 ? 255 : v);
}

inline int level_value(int level) { return level * 51; } // 0,51,...,255

// Maps an RGB triple to a palette index in [0, 240):
//   0..215   -> 6×6×6 color cube
//   216..239 -> 24-step grayscale ramp
int quantize(int r, int g, int b) {
    int ri = (r * (kCubeLevels - 1) + 127) / 255;
    int gi = (g * (kCubeLevels - 1) + 127) / 255;
    int bi = (b * (kCubeLevels - 1) + 127) / 255;
    int cr = level_value(ri), cg = level_value(gi), cb = level_value(bi);
    int cube_err = (r - cr) * (r - cr) + (g - cg) * (g - cg) + (b - cb) * (b - cb);

    int gray  = (r * 299 + g * 587 + b * 114) / 1000;
    int gidx  = (gray - 8 + 5) / 10;
    if (gidx < 0) gidx = 0;
    if (gidx > kGrayCount - 1) gidx = kGrayCount - 1;
    int gv = 8 + gidx * 10;
    int gray_err = (r - gv) * (r - gv) + (g - gv) * (g - gv) + (b - gv) * (b - gv);

    if (gray_err < cube_err) return kCubeColors + gidx;
    return ri * 36 + gi * 6 + bi;
}

void palette_rgb(int index, int& r, int& g, int& b) {
    if (index < kCubeColors) {
        r = level_value(index / 36);
        g = level_value((index / 6) % 6);
        b = level_value(index % 6);
    } else {
        int v = 8 + (index - kCubeColors) * 10;
        r = g = b = v;
    }
}

inline int percent(int v) { return (v * 100 + 127) / 255; }

} // namespace

std::string encode(const unsigned char* rgb, int width, int height, bool dither) {
    if (!rgb || width <= 0 || height <= 0) return std::string();

    const std::size_t pixels = static_cast<std::size_t>(width) * height;

    std::vector<unsigned char> index(pixels);
    bool used[kPaletteSize] = {false};

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::size_t p = (static_cast<std::size_t>(y) * width + x) * 3;
            int r = rgb[p], g = rgb[p + 1], b = rgb[p + 2];
            if (dither) {
                int d = (kBayer[y & 3][x & 3] - 7) * 4;
                r = clamp255(r + d);
                g = clamp255(g + d);
                b = clamp255(b + d);
            }
            int qi = quantize(r, g, b);
            index[static_cast<std::size_t>(y) * width + x] = static_cast<unsigned char>(qi);
            used[qi] = true;
        }
    }

    std::string out;
    out.reserve(pixels / 4 + 512);
    out += "\033Pq";

    char scratch[64];
    std::snprintf(scratch, sizeof(scratch), "\"1;1;%d;%d", width, height);
    out += scratch;

    // Define only the palette entries that actually appear in the image.
    for (int i = 0; i < kPaletteSize; ++i) {
        if (!used[i]) continue;
        int r, g, b;
        palette_rgb(i, r, g, b);
        std::snprintf(scratch, sizeof(scratch), "#%d;2;%d;%d;%d",
                      i, percent(r), percent(g), percent(b));
        out += scratch;
    }

    // Emit the image as horizontal 6-pixel bands. Within a band each palette
    // color is written as its own pass (separated by `$` so passes overlay);
    // `?` leaves pixels transparent for colors that are absent in that column.
    std::string pass;
    for (int band = 0; band < height; band += 6) {
        bool band_used[kPaletteSize] = {false};
        for (int k = 0; k < 6; ++k) {
            int y = band + k;
            if (y >= height) break;
            const unsigned char* row = &index[static_cast<std::size_t>(y) * width];
            for (int x = 0; x < width; ++x) band_used[row[x]] = true;
        }

        int total = 0;
        for (int i = 0; i < kPaletteSize; ++i) if (band_used[i]) ++total;

        int emitted = 0;
        for (int ci = 0; ci < kPaletteSize; ++ci) {
            if (!band_used[ci]) continue;

            pass.clear();
            pass.reserve(static_cast<std::size_t>(width));
            for (int x = 0; x < width; ++x) {
                int bits = 0;
                for (int k = 0; k < 6; ++k) {
                    int y = band + k;
                    if (y >= height) break;
                    if (index[static_cast<std::size_t>(y) * width + x] == ci)
                        bits |= (1 << k);
                }
                pass += static_cast<char>(63 + bits);
            }

            std::size_t begin = 0, end = pass.size();
            while (begin < end && pass[begin] == '?') ++begin;
            while (end > begin && pass[end - 1] == '?') --end;
            if (begin == end) continue;

            out += '#';
            std::snprintf(scratch, sizeof(scratch), "%d", ci);
            out += scratch;
            out.append(pass, begin, end - begin);

            ++emitted;
            if (emitted < total) out += '$';
        }
        out += '-';
    }

    out += "\033\\";
    return out;
}

} // namespace sixel
