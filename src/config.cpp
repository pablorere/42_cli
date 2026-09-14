#include "config.hpp"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <sys/stat.h>
#include <unistd.h>

static void mkdir_p(const std::string& dir, mode_t mode = 0755) {
    if (dir.empty()) return;
    std::string current;
    for (size_t i = 0; i < dir.size(); ++i) {
        if (dir[i] == '/' && !current.empty()) {
            struct stat st;
            if (stat(current.c_str(), &st) != 0) {
                mkdir(current.c_str(), mode);
            }
        }
        current += dir[i];
    }
    struct stat st;
    if (stat(current.c_str(), &st) != 0) {
        mkdir(current.c_str(), mode);
    }
}

static std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    auto end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

Config& Config::get() {
    static Config instance;
    return instance;
}

std::string Config::get_config_dir() {
    const char* xdg = std::getenv("XDG_CONFIG_HOME");
    if (xdg && *xdg) {
        return std::string(xdg) + "/intra_cli";
    }
    const char* home = std::getenv("HOME");
    if (home && *home) {
        return std::string(home) + "/.config/intra_cli";
    }
    return "/tmp/intra_cli";
}

std::string Config::get_config_file_path() {
    return get_config_dir() + "/config.ini";
}

std::string Config::get_data_dir() {
    const char* xdg = std::getenv("XDG_DATA_HOME");
    if (xdg && *xdg) {
        return std::string(xdg) + "/intra_cli";
    }
    const char* home = std::getenv("HOME");
    if (home && *home) {
        return std::string(home) + "/.local/share/intra_cli";
    }
    return "/tmp/intra_cli";
}

std::string Config::get_default_cookie_path() {
    return get_data_dir() + "/cookies.txt";
}

std::string Config::get_effective_cookie_path() {
    const char* env_path = std::getenv("INTRA_COOKIE_PATH");
    if (env_path && *env_path) {
        return std::string(env_path);
    }
    if (!get().cookie_path.empty()) {
        return get().cookie_path;
    }
    return get_default_cookie_path();
}

bool Config::load(const std::string& path) {
    std::string file_path = path.empty() ? get_config_file_path() : path;
    std::ifstream file(file_path);
    if (!file.is_open()) return false;

    std::string current_section;
    std::string line;

    while (std::getline(file, line)) {
        std::string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == ';' || trimmed[0] == '#') continue;

        if (trimmed.front() == '[' && trimmed.back() == ']') {
            current_section = trimmed.substr(1, trimmed.size() - 2);
            std::transform(current_section.begin(), current_section.end(), current_section.begin(), ::tolower);
            continue;
        }

        size_t eq = trimmed.find('=');
        if (eq == std::string::npos) continue;

        std::string key = trim(trimmed.substr(0, eq));
        std::string val = trim(trimmed.substr(eq + 1));
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);

        if (current_section == "general") {
            if (key == "theme") theme = val;
            else if (key == "border_style") border_style = val;
        } else if (current_section == "slots") {
            try {
                if (key == "offset_minutes") offset_minutes = std::stoi(val);
                else if (key == "default_duration") default_duration = std::stoi(val);
            } catch (...) {}
        } else if (current_section == "network") {
            if (key == "timeout") {
                try { timeout = std::stoi(val); } catch (...) {}
            } else if (key == "cookie_path") {
                cookie_path = val;
            }
        } else if (current_section == "ui") {
            if (key == "enable_box_glow") {
                std::string lower_val = val;
                std::transform(lower_val.begin(), lower_val.end(), lower_val.begin(), ::tolower);
                enable_box_glow = (lower_val == "true" || lower_val == "1" || lower_val == "yes");
            } else if (key == "language") {
                language = val;
                std::transform(language.begin(), language.end(), language.begin(), ::tolower);
            } else if (key == "start_tab") {
                start_tab = val;
                std::transform(start_tab.begin(), start_tab.end(), start_tab.begin(), ::tolower);
            } else if (key == "confirm_quit") {
                std::string lower_val = val;
                std::transform(lower_val.begin(), lower_val.end(), lower_val.begin(), ::tolower);
                confirm_quit = (lower_val == "true" || lower_val == "1" || lower_val == "yes");
            }
        }
    }

    return true;
}

bool Config::save(const std::string& path) {
    std::string file_path = path.empty() ? get_config_file_path() : path;
    std::string dir = file_path.substr(0, file_path.find_last_of('/'));
    mkdir_p(dir, 0755);

    std::ofstream out(file_path);
    if (!out.is_open()) return false;

    out << "# Intra 42 TUI Configuration\n\n";
    out << "[general]\n";
    out << "theme = " << theme << "\n";
    out << "border_style = " << border_style << "\n\n";

    out << "[slots]\n";
    out << "offset_minutes = " << offset_minutes << "\n";
    out << "default_duration = " << default_duration << "\n\n";

    out << "[network]\n";
    out << "timeout = " << timeout << "\n";
    out << "cookie_path = " << cookie_path << "\n\n";

    out << "[ui]\n";
    out << "enable_box_glow = " << (enable_box_glow ? "true" : "false") << "\n";
    out << "language = " << language << "\n";
    out << "start_tab = " << start_tab << "\n";
    out << "confirm_quit = " << (confirm_quit ? "true" : "false") << "\n";

    return true;
}

void Config::ensure_defaults() {
    std::string path = get_config_file_path();
    struct stat st;
    if (stat(path.c_str(), &st) != 0) {
        save(path);
    }

    std::string data_dir = get_data_dir();
    mkdir_p(data_dir, 0700);

    // If default cookies.txt does not exist, but detected legacy cookie exists, copy it with 0600
    std::string default_cookie = get_default_cookie_path();
    if (stat(default_cookie.c_str(), &st) != 0) {
        const char* home = std::getenv("HOME");
        std::string home_str = home ? home : "";
        const std::string legacy_paths[] = {
            home_str + "/.cache/AppImage-Cache/intra_cookies.txt",
            home_str + "/.cache/intra_cookies.txt",
            "/tmp/42cookies.txt",
            "/tmp/intra_cookies.txt"
        };
        for (const auto& lp : legacy_paths) {
            struct stat lst;
            if (stat(lp.c_str(), &lst) == 0 && lst.st_size > 50) {
                std::ifstream src(lp, std::ios::binary);
                std::ofstream dst(default_cookie, std::ios::binary);
                if (src.is_open() && dst.is_open()) {
                    dst << src.rdbuf();
                    dst.close();
                    src.close();
                    chmod(default_cookie.c_str(), 0600);
                }
                break;
            }
        }
    } else {
        chmod(default_cookie.c_str(), 0600);
    }
}

void Config::apply_env_overrides() {
    const char* env_theme = std::getenv("INTRA_THEME");
    if (env_theme && *env_theme) theme = env_theme;

    const char* env_border = std::getenv("INTRA_BORDER_STYLE");
    if (env_border && *env_border) border_style = env_border;

    const char* env_cookie = std::getenv("INTRA_COOKIE_PATH");
    if (env_cookie && *env_cookie) cookie_path = env_cookie;

    const char* env_offset = std::getenv("INTRA_SLOT_OFFSET");
    if (env_offset && *env_offset) {
        try { offset_minutes = std::stoi(env_offset); } catch (...) {}
    }

    const char* env_timeout = std::getenv("INTRA_TIMEOUT");
    if (env_timeout && *env_timeout) {
        try { timeout = std::stoi(env_timeout); } catch (...) {}
    }
}
