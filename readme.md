# 42_cli

`42_cli` is a native C++20 terminal client for 42 Intra (`intra.42.fr`).
It provides a fast ncurses interface for profile data, projects, slots, roadmap, and cluster presence.

## Features

- Native TUI built with ncurses
- 42 Intra authentication (credentials or session cookie)
- Dashboard, Roadmap, Slots, and Cluster tabs
- Global dynamic search for online users and projects
- Dashboard cluster minimap with hover inspector and per-user profile screen
- Slot creation, trimming, and deletion (beginner-friendly high-contrast view)
- Subject PDF download and in-app preview
- 10 built-in themes with interactive theme switcher
- Config file + environment variable overrides

## Requirements

- Linux environment
- `g++` with C++20 support
- `libcurl`
- `ncursesw`
- `pthread`

## Build

```bash
make
```

Binary output:

```bash
./42_cli
```

## Install

```bash
make install
```

Optional install prefix:

```bash
make install PREFIX=$HOME/.local
```

## CLI options

```text
Usage: ./42_cli [OPTIONS]

Options:
  -t, --theme <id|index>   Set theme by slug or number (1-10)
  --list-themes            List available themes and exit
  -c, --config <file>      Path to custom config.ini
  -k, --cookie <file>      Path to cookies.txt
  --login <login>          Headless credential login; pair with --password
  --password <password>    Password for --login (prints result and exits)
  -h, --help               Show help and exit
```

## Default config and data paths

- Config file: `$XDG_CONFIG_HOME/intra_cli/config.ini`
- Data dir: `$XDG_DATA_HOME/intra_cli`
- Default cookie file: `$XDG_DATA_HOME/intra_cli/cookies.txt`

Fallbacks when XDG variables are missing:

- `~/.config/intra_cli/config.ini`
- `~/.local/share/intra_cli/cookies.txt`

## Environment overrides

- `INTRA_THEME`
- `INTRA_BORDER_STYLE`
- `INTRA_COOKIE_PATH`
- `INTRA_SLOT_OFFSET`
- `INTRA_TIMEOUT`

## Keybindings (main)

- `h j k l`: Vim-style navigation
- `Tab` / `Shift-Tab` / `gt` / `gT`: switch tabs
- `1..4`: jump to Dashboard, Roadmap, Slots, Cluster
- `/`: focus the global search bar (Esc to leave); type to filter online users and projects, `Enter` opens
- `s`: create slot or download subject (context dependent)
- `d`: trim last 15 minutes from selected slot
- `D` / `x`: delete selected slot block
- `t`: open theme chooser
- `r`: refresh data
- `p`: open subject preview
- `y`: copy selected cluster login
- `Enter` on Cluster: open the selected user's profile screen
- `q`: quit

## License

MIT. See `/home/runner/work/42_cli/42_cli/LICENSE`.
