#pragma once
#include <string>
#include <vector>

// Lightweight localization for the new menu/settings/help/about UI only.
// The active language is read from Config::language ("en" or "es").
namespace i18n {

std::string language();                     // current code, e.g. "en"
std::string tr(const std::string& key);     // translate a short key
const std::vector<std::string>& help_lines();

} // namespace i18n
