#pragma once
#include <string>

namespace clipboard {

/**
 * Copy `text` to the system clipboard.
 *
 * Primary mechanism is the terminal OSC 52 escape sequence (works over SSH and
 * in Ghostty/Kitty/WezTerm). When a graphical session is available it also
 * pushes the text through xclip/xsel as a fallback for terminals that ignore
 * OSC 52.
 */
void copy(const std::string& text);

} // namespace clipboard
