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
- Inline images (profile photos + PDF previews) with automatic protocol detection
- 10 built-in themes with interactive theme switcher
- Config file + environment variable overrides

## Terminal image support

Images are drawn with the best protocol the terminal supports, detected at
startup (no configuration required):

| Protocol | Terminals |
| --- | --- |
| Kitty graphics | Kitty, WezTerm, Ghostty |
| iTerm2 inline images (OSC 1337) | iTerm2 |
| SIXEL (built-in encoder) | foot, mlterm, contour, xterm+sixel, other sixel terminals |
| Truecolor half-blocks (▀) | any `COLORTERM=truecolor` terminal |
| 256-color / ASCII half-blocks | everything else |

Kitty and iTerm2 render at native pixel resolution; the vendored SIXEL encoder
quantizes to a 240-color palette with optional ordered dithering. When only
text cells are available, a high-quality area-averaged half-block renderer
preserves the aspect ratio. Alacritty does not support native graphics, so it
uses the half-block fallback (truecolor when `COLORTERM=truecolor`, otherwise
256-color, and finally ASCII on colorless terminals).

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
- `INTRA_TIMEOUT`

## Keybindings (main)

- `h j k l`: Vim-style navigation
- `Tab` / `Shift-Tab` / `gt` / `gT`: switch tabs
- `1..4`: jump to Dashboard, Roadmap, Slots, Cluster
- `/`: focus the global search bar (Esc to leave); type to filter online users and projects, `Enter` opens
- `Esc`: open the main menu (Settings / Help / Resume / Quit); Esc again resumes
- `s`: create slot or download subject (context dependent)
- `d`: trim last 15 minutes from selected slot
- `D` / `x`: delete selected slot block
- `t`: open theme chooser
- `r`: refresh data
- `p`: open subject preview
- `y`: copy selected cluster login
- `Enter` on Cluster: open the selected user's profile screen
- `q`: quit (press twice to confirm; toggle in Settings)

## License

MIT. See `/home/runner/work/42_cli/42_cli/LICENSE`.
