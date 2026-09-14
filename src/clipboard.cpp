#include "clipboard.hpp"

#include <cstdio>
#include <cstdlib>
#include <string>

namespace {

const char* kB64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "abcdefghijklmnopqrstuvwxyz"
                   "0123456789+/";

std::string base64_encode(const std::string& in) {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(kB64[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(kB64[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
}

void pipe_to(const char* cmd, const std::string& text) {
    FILE* p = popen(cmd, "w");
    if (!p) return;
    if (!text.empty()) fwrite(text.data(), 1, text.size(), p);
    pclose(p);
}

} // namespace

namespace clipboard {

void copy(const std::string& text) {
    if (text.empty()) return;

    // OSC 52: ESC ] 52 ; c ; <base64> BEL
    std::string seq = "\033]52;c;" + base64_encode(text) + "\a";
    std::fwrite(seq.data(), 1, seq.size(), stdout);
    std::fflush(stdout);

    // Fallback for graphical sessions that ignore OSC 52.
    if (std::getenv("WAYLAND_DISPLAY")) {
        pipe_to("wl-copy 2>/dev/null", text);
    } else if (std::getenv("DISPLAY")) {
        pipe_to("xclip -selection clipboard 2>/dev/null", text);
    }
}

} // namespace clipboard
