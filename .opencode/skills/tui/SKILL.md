---
name: tui
description: >-
  Use when implementing, modifying or auditing the ncurses-based TUI of 42_cli.
  Covers the render-then-paint architecture (renderer.cpp/main.cpp), theme usage,
  keybindings, mouse handling, resize/KEY_RESIZE flow, hit-testing, and the
  thread boundary between UI and network worker. Essential context for any UI
  change in this codebase.
---

# TUI Skill — 42_cli ncurses conventions

## Architecture overview

`42_cli` uses a single-threaded render loop with blocking `getch()`:

```
main.cpp loop (UI thread):
  while (!quit) {
      draw(state, ...)   →  renderer.draw(...)   (all rendering here)
      ch = getch()       →  blocking, timeout(80)
      handle input
      push network tasks →  state.mtx locked for short writes only
  }
```

Network I/O runs on a worker thread (`network_worker.cpp`) — **never** call
`http_get`, `http_post`, libcurl, or any ncurses function from the network
thread.

## Key files

| File | Role |
|------|------|
| `src/renderer.cpp` | All drawing — 3 500+ lines, split into `draw_*` methods + hitboxes |
| `src/main.cpp` | Input loop, tab state, menu/modal logic, task dispatch |
| `src/network_worker.cpp` | Background fetch queue, calls `network::` functions |
| `src/network.cpp` | libcurl wrappers + HTTP logic |
| `src/theme.cpp` | 10 theme palettes, `apply_theme_to_ncurses()` |
| `src/image_renderer.cpp` | Kitty/iterm2 protocol, inline avatar images |
| `include/types.hpp` | Core structs: `Profile`, `SharedState`, `Tab`, `NetTask`, `ClusterStudent` |
| `include/renderer.hpp` | `Renderer` class, `Hitbox`, `MouseAction`, `MenuState` enums |
| `include/theme.hpp` | `ThemePalette` struct, 10 themed color pairs |

## ncurses init (renderer.cpp constructor)

```cpp
setlocale(LC_ALL, "");
initscr();
cbreak(); noecho(); keypad(stdscr, TRUE);
curs_set(0); timeout(80);
mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);
mouseinterval(0);
// colors via theme::apply_theme_to_ncurses(pal)
```

Key detail: **no `set_escdelay()` is currently called** — the AGENTS.md
recommends `set_escdelay(25)` for low-latency Esc. This is a known gap.

## Render model: render-then-paint

`renderer.draw()` builds `hitboxes_[]` via `add_hitbox()` during rendering, then
`hit_test(y,x)` does a reverse-order lookup (overlays win). Always add hitboxes
in the same order as draw calls; add new ones only for new clickable regions.

## Theme system

10 palettes in `ThemePalette`: `bg_primary`, `bg_secondary`, `fg_text`,
`fg_muted`, `border`, `accent`, `success`, `warning`, `error`, `enable_box_glow`.
Colors are resolved at init by `apply_theme_to_ncurses()` as `init_pair()`. Always
use the theme's semantic keys (`PAL_BORDER`, `PAL_ACCENT`, etc.) not raw colors.

## Keybinding conventions

| Key | Action |
|-----|--------|
| `h` / `j` / `k` / `l` | Vim-style navigation (must work in every view) |
| `Tab` / `Shift-Tab` / `gt` / `gT` | Switch tabs |
| `1..4` | Jump to Dashboard / Roadmap / Slots / Cluster |
| `/` | Focus global search bar; `Esc` to leave |
| `Esc` | Close innermost layer first: search → modal → menu |
| `s` | Create slot or download subject (context-dependent) |
| `d` | Trim last 15 min from slot |
| `D` / `x` | Delete slot block |
| `t` | Open theme chooser |
| `r` | Refresh |
| `p` | Subject preview |
| `y` | Copy cluster login |
| `Enter` | Open profile on Cluster |
| `q` | Quit (double-press required unless disabled in settings) |

Mouse: all mouse actions go through `Renderer::hit_test()` → `MouseAction` enum.

## Resize handling

`KEY_RESIZE` is caught at `main.cpp:850`:
```cpp
if (ch == KEY_RESIZE) {
    image_renderer::clear_kitty_images();
    renderer.refresh_now();  // doupdate() — forces a full redraw
    continue;
}
```
`getmaxyx(stdscr, rows_, cols_)` is called at every `draw()` invocation so
geometry is always fresh.

## Thread boundary

`SharedState::mtx` protects reads/writes. The UI thread locks it briefly to
snapshot data or push a `NetTask`; the worker thread locks it briefly to write
results. Never hold the lock during a render call or during a blocking network
call.

## Adding new views

1. Add a new `draw_<name>(...)` method to `Renderer` (declared in `renderer.hpp`).
2. Add a new `MouseAction` enum variant if the view is clickable.
3. Add hitboxes with `add_hitbox()` during draw.
4. Wire input in `main.cpp` to call the draw method with appropriate args.
5. Add the new params to the giant `Renderer::draw(...)` signature — this is
   acceptable; the class is intentionally one flat draw path.

## TUX audit

Always run `tux-advisor --audit src/` after UI changes to verify:
- `set_escdelay(25)` presence and low Esc latency
- `h`/`j`/`k`/`l` + arrow key coverage
- `KEY_RESIZE` / `SIGWINCH` dynamic recalculation
- High-contrast color pair usage in new views