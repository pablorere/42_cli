#include "html_parser.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace html_parser {

// ─── Helpers ─────────────────────────────────────────────────────────────────

static std::string to_lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

/**
 * Decode HTML entities in a string.
 */
static std::string decode_entities(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    size_t i = 0;
    while (i < s.size()) {
        if (s[i] == '&') {
            size_t semi = s.find(';', i);
            if (semi != std::string::npos) {
                std::string entity = s.substr(i + 1, semi - i - 1);
                if (entity == "amp")       { out += '&'; i = semi + 1; continue; }
                if (entity == "lt")        { out += '<'; i = semi + 1; continue; }
                if (entity == "gt")        { out += '>'; i = semi + 1; continue; }
                if (entity == "quot")      { out += '"'; i = semi + 1; continue; }
                if (entity == "apos")      { out += '\''; i = semi + 1; continue; }
                if (entity.size() > 1 && entity[0] == '#') {
                    // numeric entity
                    long code = 0;
                    try {
                        if (entity.size() > 2 && entity[1] == 'x')
                            code = std::stol(entity.substr(2), nullptr, 16);
                        else
                            code = std::stol(entity.substr(1));
                    } catch (...) { code = 0; }
                    if (code > 0 && code < 128) out += static_cast<char>(code);
                    i = semi + 1; continue;
                }
            }
        }
        out += s[i++];
    }
    return out;
}

/**
 * Extract the value of a quoted attribute within a raw tag string.
 *   tag_str  – e.g.  <input name="authenticity_token" value="abc123" ...>
 *   attr     – e.g.  "value"
 */
static std::string attr_from_tag(const std::string& tag_str, const std::string& attr) {
    std::string lower_tag = to_lower(tag_str);
    std::string lower_attr = to_lower(attr) + "=";
    size_t pos = lower_tag.find(lower_attr);
    if (pos == std::string::npos) return {};
    pos += lower_attr.size();
    if (pos >= tag_str.size()) return {};

    char delim = tag_str[pos];
    if (delim == '"' || delim == '\'') {
        ++pos;
        size_t end = tag_str.find(delim, pos);
        if (end == std::string::npos) return {};
        return decode_entities(tag_str.substr(pos, end - pos));
    }
    // unquoted value
    size_t end = pos;
    while (end < tag_str.size() && !std::isspace((unsigned char)tag_str[end]) && tag_str[end] != '>')
        ++end;
    return decode_entities(tag_str.substr(pos, end - pos));
}

// ─── Public API ──────────────────────────────────────────────────────────────

std::string get_attr_value(const std::string& html,
                           const std::string& attr_name,
                           const std::string& value_attr)
{
    // Search for any tag that contains attr_name="..." (or attr_name=...)
    std::string lower_html = to_lower(html);
    std::string needle = to_lower(attr_name) + "=";
    // Also handle name="attr_name" content="..."  (meta CSRF pattern)
    {
        // Check name="attr_name" pattern first
        std::string name_pat = "name=\"" + to_lower(attr_name) + "\"";
        size_t pos = 0;
        while ((pos = lower_html.find(name_pat, pos)) != std::string::npos) {
            // Walk back to find the '<' opening this tag
            size_t tag_start = lower_html.rfind('<', pos);
            size_t tag_end   = lower_html.find('>', pos);
            if (tag_start == std::string::npos || tag_end == std::string::npos) { pos++; continue; }
            std::string tag = html.substr(tag_start, tag_end - tag_start + 1);
            std::string val = attr_from_tag(tag, value_attr);
            if (!val.empty()) return val;
            pos++;
        }
    }
    {
        // value attr on an input whose name matches
        std::string name_pat = "name=\"" + to_lower(attr_name) + "\"";
        // already tried above — now try without quotes
        std::string name_pat2 = "name=" + to_lower(attr_name);
        size_t pos = 0;
        while ((pos = lower_html.find(name_pat2, pos)) != std::string::npos) {
            size_t tag_start = lower_html.rfind('<', pos);
            size_t tag_end   = lower_html.find('>', pos);
            if (tag_start == std::string::npos || tag_end == std::string::npos) { pos++; continue; }
            std::string tag = html.substr(tag_start, tag_end - tag_start + 1);
            std::string val = attr_from_tag(tag, value_attr);
            if (!val.empty()) return val;
            pos++;
        }
    }
    return {};
}

std::string get_text_by_class(const std::string& html, const std::string& css_class) {
    std::string lower_html = to_lower(html);
    std::string needle = "class=\"" + to_lower(css_class) + "\"";
    size_t pos = lower_html.find(needle);
    if (pos == std::string::npos) {
        // try partial class match
        needle = to_lower(css_class);
        pos = lower_html.find(needle);
        if (pos == std::string::npos) return {};
    }
    // find the closing '>' of this opening tag
    size_t tag_end = html.find('>', pos);
    if (tag_end == std::string::npos) return {};
    // find the closing tag (simple heuristic — no nesting)
    size_t text_start = tag_end + 1;
    size_t close_tag  = html.find('<', text_start);
    if (close_tag == std::string::npos) return {};
    std::string inner = html.substr(text_start, close_tag - text_start);
    // trim whitespace
    size_t s = inner.find_first_not_of(" \t\r\n");
    size_t e = inner.find_last_not_of(" \t\r\n");
    if (s == std::string::npos) return {};
    return decode_entities(inner.substr(s, e - s + 1));
}

std::string get_data_attr(const std::string& html, const std::string& data_name) {
    std::string lower_html = to_lower(html);
    std::string attr = "data-" + to_lower(data_name) + "=";
    size_t pos = lower_html.find(attr);
    if (pos == std::string::npos) return {};
    size_t tag_start = lower_html.rfind('<', pos);
    size_t tag_end   = lower_html.find('>', pos);
    if (tag_start == std::string::npos || tag_end == std::string::npos) return {};
    std::string tag = html.substr(tag_start, tag_end - tag_start + 1);
    return attr_from_tag(tag, "data-" + data_name);
}

std::string url_encode(const std::string& raw) {
    std::ostringstream out;
    for (unsigned char c : raw) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            out << c;
        } else {
            out << '%' << std::uppercase << std::hex << std::setw(2)
                << std::setfill('0') << static_cast<int>(c);
        }
    }
    return out.str();
}

} // namespace html_parser
