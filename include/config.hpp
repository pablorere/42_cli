#pragma once
#include <string>

struct Config {
    // [general]
    std::string theme        = "catppuccin_mocha";
    std::string border_style = "rounded"; // "rounded", "sharp", "double"

    // [slots]
    int offset_minutes   = 15;
    int default_duration = 30;

    // [network]
    int timeout          = 10;
    std::string cookie_path = ""; // if empty, defaults to XDG data dir

    // [ui]
    bool enable_box_glow = false;
    std::string language = "en";       // "en", "es"
    std::string start_tab = "dashboard"; // dashboard, roadmap, slots, cluster
    bool confirm_quit    = true;       // require pressing q twice to quit

    // Singleton access
    static Config& get();

    // XDG Directory paths
    static std::string get_config_dir();
    static std::string get_config_file_path();
    static std::string get_data_dir();
    static std::string get_default_cookie_path();
    static std::string get_effective_cookie_path();

    // INI File persistence
    bool load(const std::string& path = "");
    bool save(const std::string& path = "");
    void ensure_defaults();

    // Environment variable overrides
    void apply_env_overrides();
};
