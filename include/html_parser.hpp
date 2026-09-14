#pragma once
#include <string>

namespace html_parser {

/**
 * Extract the value of the first attribute matching `attr_name`
 * from the raw HTML string.
 * E.g.  get_attr_value(html, "authenticity_token", "value")
 *        get_attr_value(html, "csrf-token", "content")
 */
std::string get_attr_value(const std::string& html,
                           const std::string& attr_name,
                           const std::string& value_attr = "value");

/**
 * Extract inner text between the first matching opening tag that
 * contains the given css-class and its paired closing tag.
 */
std::string get_text_by_class(const std::string& html, const std::string& css_class);

/**
 * Extract the value of a data-* attribute on the first element that has it.
 */
std::string get_data_attr(const std::string& html, const std::string& data_name);

/**
 * Minimal URL-encoding (percent-encode special chars).
 */
std::string url_encode(const std::string& raw);

} // namespace html_parser
