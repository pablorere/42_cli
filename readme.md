# 42_cli

`42_cli` is a native C++20 terminal client for 42 Intra (`intra.42.fr`).
It provides a fast ncurses interface for profile data, projects, slots, roadmap, and cluster presence.

## Features

- Native TUI built with ncurses
- 42 Intra authentication (credentials or session cookie)
- Dashboard, Roadmap, Slots, and Cluster tabs
- **Dashboard**: flat scrollable view — summary strip, cursus progress, action
  center, recent submissions, recent evaluations and evaluation economy
- **Slot manager**: clickable toolbar (new / −15m / delete / free-space),
  free-space gap picker (`j`/`k` or `←`/`→`), and a right-click context menu
  (copy ID / trim / delete)
- **Cluster**: live minimap with clickable room pills (C1–C4), legend, hover
  inspector and full-screen user profiles
- Full mouse support: hover highlight, click, right-click context menus, wheel scroll
- Global dynamic search for online users and projects
- Subject PDF download and in-app preview
- Inline avatar/subject images via Kitty / iTerm2 / `chafa` / ANSI half-blocks
- 10 built-in themes with interactive theme switcher
- English + Spanish (i18n), config file + environment variable overrides

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

## Update & run

Pull the latest code, do a full rebuild, install and launch in a new terminal
window (background):

```bash
make update
```

- If there are local changes or unpushed commits, they are saved to a backup
  branch. When `masterbak` already exists you are asked whether to overwrite it
  (`s`) or keep a timestamped backup (`c`), then `main` is reset to `origin/main`
  and fast-forward pulled.
- Then it runs `fclean`, `install` and opens `42_cli` in a new Ghostty window
  (falls back to another terminal emulator, overridable with
  `make update UPDATE_TERMINAL=kitty UPDATE_LAUNCH=-e`).

Launch the installed binary without updating:

```bash
make run
```

## Main menu (Esc)

Press `Esc` during normal navigation to open a centered menu:

- **Resume** (`Esc`) — close the menu and go back
- **Settings** (`s`) — edit theme, border style, slot offset, default duration,
  box glow, cookie path, startup tab, quit confirmation and language. Changes
  are staged with a `*` marker and written to `config.ini` only via **Save**
  (or `s`); leaving with unsaved changes asks to discard them.
- **Theme chooser** (`t`) — the quick live-preview theme switcher
- **Help** (`h`) — scrollable keybinding reference
- **About** (`a`) — version (from the latest git tag), repo, license, paths and
  dependency versions
- **Logout / switch account** (`l`) — confirm, delete the session cookie and
  return to the login screen
- **Quit** (`q`) — quit, requiring a second `q` by default

`Esc` closes the innermost thing first: it cancels search/inspection, then
closes a modal, and only opens the menu from normal navigation.

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
- `INTRA_SLOT_GAP`
- `INTRA_TIMEOUT`

## Keybindings (main)

- `h j k l`: Vim-style navigation
- `Tab` / `Shift-Tab` / `gt` / `gT`: switch tabs
- `1..4`: jump to Dashboard, Roadmap, Slots, Cluster
- `/`: focus the global search bar (Esc to leave); type to filter online users and projects, `Enter` opens
- `Esc`: open the main menu (Settings / Help / Resume / Quit); Esc again resumes
- Dashboard: `j`/`k` scroll the flat dashboard; `[`/`]` jump to top/bottom; `Enter`/`f` inspect feedback
- Slots: `s` create, `d` trim −15m, `D`/`x` delete, `Enter`/click the free-space button for the gap picker
- `t`: open theme chooser
- `r`: refresh data
- `p`: open subject preview
- `y`: copy selected cluster login
- `Enter` on Cluster: open the selected user's profile screen
- `q`: quit (press twice to confirm; toggle in Settings)

## Mouse

- **Click** — tabs, list rows, slot toolbar buttons, cluster desks, minimap room pills
- **Hover** — highlights rows/buttons and opens the cluster minimap inspector
- **Right-click** — slot context menu (copy ID / trim / delete) or copy a cluster login
- **Wheel** — scroll lists and the dashboard

## Documentation

- [`ARCHITECTURE.md`](ARCHITECTURE.md) — codebase internals
- [`endpoints.md`](endpoints.md) — intranet endpoint surface
- [`api42-apidoc.md`](api42-apidoc.md), [`api42-endpoints.md`](api42-endpoints.md), [`api42-examples.md`](api42-examples.md) — official API v2
- [`features.md`](features.md) — feature catalogue

## License

MIT. See [`LICENSE`](LICENSE).
