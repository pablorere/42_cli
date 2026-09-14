#pragma once
#include <string>

namespace sixel {

/**
 * Encodes a tightly packed RGB24 image (3 bytes per pixel, row-major) into a
 * complete DEC SIXEL graphics string, including the DCS introducer (ESC P q)
 * and the string terminator (ESC \). No external library or terminal I/O is
 * performed here; callers position the cursor and write the returned bytes.
 *
 * The encoder quantizes to a 6×6×6 color cube plus a 24-step grayscale ramp and
 * emits single-color bands separated by `$`/`-`. When `dither` is true a light
 * 4×4 ordered dither is applied before quantization, trading a few extra
 * palette entries for smoother gradients.
 *
 * Returns an empty string for invalid input.
 */
std::string encode(const unsigned char* rgb, int width, int height,
                   bool dither = false);

} // namespace sixel
