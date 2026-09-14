---
name: ux
description: >-
  Use when designing or redesigning any user-facing surface of 42_cli: layout,
  flow, menus, modals, focus order, confirmations, i18n strings, or look & feel.
  Enforces a design-first workflow: gather constraints, produce an ASCII
  wireframe, generate an interactive Tailwind HTML preview for approval, and only
  then delegate implementation (tui skill). Essential for any feature that
  changes what the user sees or does.
---

# UX Skill — design-first workflow for 42_cli

Every change that touches what the user sees gets a **design pass before code**.
Never jump to C++ while design questions are open.

## The 5-step workflow

### 1. Understand the request & constraints

Stop and answer: who is the user, what state are they in (logged in? in a modal?
on which tab?), what do they need to do next, and what must stay stable (the
Esc-close-inner-first rule, the `h`/`j`/`k`/`l` navigation contract, the double
`q` quit guard, the theme system).

Constraints that always apply in this app:

- Layout must fit a terminal: recompute on `KEY_RESIZE` / `SIGWINCH` (see `tui`
  skill). Nothing may hardcode a width.
- High contrast: any new view must work on all 10 `ThemePalette` themes, both
  light-on-dark and dark-on-light. No color-only signals — always pair with
  shape/text (e.g. `[x]` vs `[ ]`, borders, glyphs).
- Text must go through `i18n` strings and live demo ASCII-wide chars (line
  drawing, `✓`, `→`, `λ`-like glyphs) must render as UTF-8 in ncursesw.
- Every modal is closeable with `Esc`, every list navigable with `h/j/k/l`.

### 2. Produce an ASCII wireframe

Draw the exact screen geometry: rows, columns, borders, where each panel sits,
what the focused element looks like, what happens on hover (dashboard minimap
inspector, cluster desk tooltip). Show the idle state AND the focused/keypress
states. Label the key that triggers each transition.

Example:
```
┌─ 42_cli ── $HOME ──────────────────────────────────────┐
│  Dashboard │ Roadmap │ Slots │ Cluster                  │
│  ┌─ Projects ──────────────┐  ┌─ Holygraph ──────────┐ │
│  │ > libft      finished 100│  │ (m0) Basics          │ │
│  │   ft_printf  finished 100│  │  libft   [done]      │ │
│  │   get_next_line  in-prog │  │  ft_printf [done]    │ │
│  └──────────────────────────┘  └──────────────────────┘ │
│  [j/k move  Enter open  p preview  Esc inspect]         │
└───────────────────────────────────────────────────────────┘
```

### 3. Generate an interactive HTML preview artifact

Create an interactive mock in a standalone HTML file (Tailwind CSS via CDN) that
lets the user *feel* the flow: hover states, focus rings, modal open/close,
selection moves, key hints. Save it under `.opencode/previews/<feature>.html`
(or `/tmp/opencode/…` for ephemeral explorations) and hand the user the path.

The preview must show:
- every layout state identified in step 2,
- the focus/hover behavior,
- an annotated list of "what changed" next to it.
This is a **design artifact**, not a prototype of the code — it is thrown away
(aside from the copy kept for reference).

### 4. Get explicit approval

Present the wireframe + preview and ask: merge as-is, tweak, or scrap. Iterate
fast. Only after an explicit "approved" do you move to implementation.

### 5. Hand off to implementation

Switch to the `tui` skill for the actual ncurses implementation. Keep a running
list of touchpoints that differ from the wireframe so the reviewer can re-check
them at the end. Then run `tux-advisor --audit src/`.

## UX invariants not to break

- `Esc` closes the innermost thing first (search → inspect → modal → main menu).
- Confirmation is explicit: deleting slots, logout, quitting (`q` twice unless
  disabled). Never destroy data without a confirm.
- Settings stages changes with a `*` marker; nothing is written until Save.
- Heavy/throttleable actions (refresh, cluster rebuild) surface a loading state
  via `SharedState::status_msg` instead of blocking the UI.
- One clear "primary" button per dialog (e.g. the save row is visually marked).
- Tooltips for dense hover data (cluster minimap, desk tooltip) anchor to the
  hovered cell — don't float them unpredictably.