# 42_cli — architecture

`42_cli` is a native **C++20** terminal client for 42 Intra, built on
**ncursesw + libcurl + pthread**. This document maps the codebase so changes can
be made confidently.

## Process & threading model

```
UI thread (main.cpp)                      Network worker thread (network_worker.cpp)
  while (!quit):                            while (running):
    renderer.draw(state, …)   ──snapshot──►   pop NetTask (blocking)
    ch = getch()                              network::<fn>(…)   (libcurl)
    handle input                              lock state.mtx → write results
    enqueue(NetTask)          ───────────►    unlock
```

- **One UI thread** does all drawing and input. ncurses is only ever touched here.
- **One worker thread** (`NetworkWorker`) drains a `NetTask` queue and writes
  results into `SharedState`.
- `SharedState::mtx` protects reads/writes. It is held only for short snapshot /
  write sections — **never** during a render or a blocking network call.

## Source map

| Module | Files | Responsibility |
|--------|-------|----------------|
| Core types | `include/types.hpp` | `Tab`, `Profile`, `Project`, `Milestone`/`HolyProject`, `Slot`, `ClusterStudent`, `EvaluationFeedback`, `ScaleTeamRecord`, `SubjectPreview`, `SharedState`, `NetTask`, `cluster_layout` geometry |
| Config | `config.{hpp,cpp}` | `config.ini` load/save, XDG paths, env overrides |
| Theme | `theme.{hpp,cpp}` | 10 `ThemePalette`s, `apply_theme_to_ncurses()` (256-colour pairs) |
| i18n | `i18n.{hpp,cpp}` | `tr(key)` strings (en/es) + help lines |
| Network | `network.{hpp,cpp}` | libcurl wrappers + all 42 HTTP logic (auth, profile, slots, holygraph, feedbacks, clusters, images, PDF) |
| Worker | `network_worker.{hpp,cpp}` | `NetTask` queue + thread; dispatches to `network::` |
| Cache | `cache.{hpp,cpp}` | on-disk profile JSON + image byte cache |
| HTML | `html_parser.{hpp,cpp}` | tag stripping, attribute/href extraction, url-encode |
| Images | `image_renderer.{hpp,cpp}` | protocol selection + scaled cache (see below) |
| PDF | `pdf_preview.{hpp,cpp}` | subject PDF → text/image pages |
| Clipboard | `clipboard.{hpp,cpp}` | OSC 52 + `xclip`/`xsel` copy |
| Renderer | `renderer.{hpp,cpp}` | every `draw_*` method, hitboxes, modals, images |
| Entry | `main.cpp` | input loop, tab/modal state, task dispatch |
| Vendored | `stb_image*.h`, `stb_image_resize2.h`, `stb_image_resize_impl.cpp` | decode/encode/resize |

## Rendering model — *render then paint*

1. `Renderer::draw(...)` (one flat method with a large signature) renders the
   current frame and, as it draws clickable regions, records them via
   `add_hitbox(y, x, h, w, MouseAction, index)`.
2. Overlays (theme switcher, subject modal, action menu, user modal, slot
   gap-picker / context menu, Esc menu) are drawn **after** the base screen, so
   they are later in `hitboxes_`.
3. `hit_test(y, x)` scans `hitboxes_` in **reverse** order → overlays win.
4. On `KEY_RESIZE`, `getmaxyx` is re-read every frame and the layout recomputes.

Tab dispatch lives in `Renderer::draw`; each tab has a `draw_*` method:

| Tab | Method | Highlights |
|-----|--------|-----------|
| Dashboard | `draw_dashboard` | flat, scrollable; summary strip, cursus bar, action center, submissions/evaluations/economy cards, feedback inspector |
| Roadmap | `draw_roadmap` | holygraph tree + subject preview panel |
| Slots | `draw_slots` | toolbar buttons, slot cards, `draw_gap_picker`, `draw_slot_context_menu` |
| Cluster | `draw_cluster` | 8×6 desk grid, room pills, user profile modal |
| (shared) | `draw_profile_panel`, `draw_cluster_minimap`, `draw_cluster_tooltip`, `draw_tab_bar`, `draw_search_bar`, `draw_status_bar` | |

## Input & state

- `main.cpp` holds UI state (`current_tab`, `slot_sel`, `tree_sel`, `cluster_sel`,
  `dash_scroll`, `slot_ui`, `search`, `menu`, modal flags) and a
  `SharedState state`.
- Input is handled in layers, innermost first: edit popup → confirm → menu →
  user modal → theme switcher → action menu → **slot gap-picker → slot context
  menu** → subject modal → search → login → normal navigation.
- `Esc` closes the innermost layer; `q` quits (double-press unless disabled).
- Mouse: `KEY_MOUSE` → `getmouse` → `renderer.hit_test` → `MouseAction` switch.

## Data flow

- On start: load cached profile (`cache::load_profile`), load cached images
  (`cache::load_all_cached_images`), then enqueue `FetchProfile`.
- Worker fetches, parses (JSON or HTML), and writes into `SharedState`; the UI
  thread snapshots it at the top of `draw`.
- Heavy actions (refresh, cluster rebuild, slot create) surface progress via
  `SharedState::status_msg` instead of blocking.

## Image pipeline (`image_renderer.cpp`)

Protocol selection, best-first:
1. **Kitty Graphics Protocol** (native pixels) — Ghostty/Kitty/WezTerm
2. **iTerm2 inline images** (OSC 1337) — iTerm2/WezTerm/Konsole/mintty
3. **external `chafa`** (optional, if on `PATH`)
4. **24-bit ANSI truecolor half-blocks** (`▀`) with high-quality downsampling

Decode via `stb_image`; downsampled buffers are memoised (`stb_image_resize2`,
Mitchell) in an in-memory scaled cache and persisted by `cache.cpp`.

## Config & paths

- `[general] theme, border_style` · `[slots] offset_minutes, default_duration,
  slot_gap_minutes` · `[network] timeout, cookie_path` · `[ui] enable_box_glow,
  language, start_tab, confirm_quit`.
- Config `$XDG_CONFIG_HOME/intra_cli/config.ini`; data
  `$XDG_DATA_HOME/intra_cli` (default cookie `…/cookies.txt`).
- Env overrides: `INTRA_THEME`, `INTRA_BORDER_STYLE`, `INTRA_COOKIE_PATH`,
  `INTRA_SLOT_OFFSET`, `INTRA_SLOT_GAP`, `INTRA_TIMEOUT`.

## Build

- `make` → `./42_cli`; flags `-std=c++20 -Wall -Wextra -Werror -pedantic -O2`.
- Prefers system libcurl; falls back to vendored `curl_dev_tmp/`.
- `make install` (`PREFIX=~/.local`), `make run`, `make update`.
- `set_escdelay(25)` for low-latency Esc; `mousemask(ALL_MOUSE_EVENTS |
  REPORT_MOUSE_POSITION)`; `timeout(80)` polling loop.

## Documentation index

| File | Contents |
|------|----------|
| `readme.md` | user-facing features, build, keybindings, config |
| `endpoints.md` | intranet cookie endpoint surface (live-verified) |
| `api42-apidoc.md` | official OAuth2 API v2 — guides, auth, conventions, scopes |
| `api42-endpoints.md` | official API — 741 endpoints (params + scopes) |
| `api42-examples.md` | official API — 302 request/response examples |
| `features.md` | feature catalogue mapped to endpoints |
| `AGENTS.md` | agent conventions |
| `.opencode/agent/`, `.opencode/skills/` | subagents + skills (api42, scraper, toolpick, tui, ux, scrape) |
