# 42_cli UI/UX Mockups

This document contains terminal UI proposals for the core features of `42_cli`. The designs use standard Unicode box-drawing characters (which work perfectly with `ncursesw`) and assume a modern aesthetic.

---

## 1. Curriculum 'Holy Graph' (Roadmap Tab)

**UX Problem:** Drawing a massive 2D graph in a terminal is chaotic and hard to navigate with a keyboard.
**Solution:** A Miller-column or strictly hierarchical horizontal tree that clearly shows unlock dependencies. We can use color to denote status (`CP_SUCCESS` for done, `CP_DIM` for locked).

### ASCII Mockup
```text
┌─ ROADMAP ─────────────────────────────────────────────────────────────┐
│ 🔍 Search project...                                  [Level 4.2] 24% │
├───────────────────────────────────────────────────────────────────────┤
│                                                                       │
│  [CORE TIER 1]           [CORE TIER 2]           [CORE TIER 3]        │
│                                                                       │
│  🟢 libft ──────┬──────> 🟢 ft_printf ────┬────> 🔒 minitalk          │
│  (100/100)      │        (115/100)        │      (Locked)             │
│                 │                         │                           │
│                 └──────> 🔵 get_next_line │                           │
│                          (In Progress)    │                           │
│                                           └────> 🔒 pipex             │
│                                                  (Locked)             │
│                                                                       │
│                                                                       │
├───────────────────────────────────────────────────────────────────────┤
│ 💡 get_next_line: Read a line from a fd | Evaluators needed: 2        │
└───────────────────────────────────────────────────────────────────────┘
```
**UX Flow:**
- Use `h/j/k/l` or arrow keys to move the active cursor (highlighted in `CP_ROW_SEL`).
- The bottom panel updates instantly to show the description and requirements of the hovered project.
- Press `Enter` to open the full project PDF or register for it.

---

## 2. Peer-to-Peer Evaluations (Slots Tab)

**UX Problem:** Mixing available slots, upcoming evaluations, and past feedback into one list is confusing.
**Solution:** A split-pane layout. The left pane acts as a timeline/filter, and the right pane shows detailed actionable items.

### ASCII Mockup
```text
┌─ EVALUATIONS ─────────────────────────────────────────────────────────┐
│ [1] My Slots    [2] Upcoming Evals    [3] Past Feedback               │
├─────────────────────────┬─────────────────────────────────────────────┤
│ TODAY, SEP 15           │ 🟢 YOU ARE EVALUATING                       │
│  10:00 - 10:45          │                                             │
│  14:00 - 15:30 (Booked) │ User:      johndoe (Level 3.1)              │
│  16:00 - 17:00          │ Project:   ft_printf                        │
│                         │ Location:  e2r1p4                           │
│ TOMORROW, SEP 16        │ Time:      14:00 - 14:45 (in 2 hours)       │
│  09:00 - 12:00          │                                             │
│  13:00 - 14:00          │ [ Enter ] View Profile    [ c ] Cancel      │
│                         ├─────────────────────────────────────────────┤
│                         │ ⚠️ EVALUATION TIPS                          │
│                         │ Remember to check for memory leaks using    │
│                         │ valgrind before grading the project!        │
└─────────────────────────┴─────────────────────────────────────────────┘
```
**UX Flow:**
- `Tab` cycles focus between the top filter row, the left timeline, and the right action pane.
- When on "My Slots" (left), pressing `s` opens the slot creation modal.
- The right pane provides quick context so you don't have to navigate to a user's profile just to see where they sit.

---

## 3. Real-time Notifications Drawer

**UX Problem:** Popups interrupt the user's workflow. We need a way to show alerts (grades, new messages) without breaking focus.
**Solution:** A persistent indicator in the top-right or bottom-right corner, and a slide-out drawer triggered by a hotkey (e.g., `n`).

### ASCII Mockup (Drawer Open)
```text
┌─ DASHBOARD ───────────────────────────────────────────┬─ NOTIFICATIONS ─┐
│                                                       │                 │
│                                                       │ 🔴 NEW GRADE    │
│  [ Dashboard Content ... ]                            │ ft_printf: 115  │
│                                                       │ 2 mins ago      │
│                                                       │ ─────────────── │
│                                                       │ 🔵 UPCOMING     │
│                                                       │ Eval in 15 mins │
│                                                       │ e2r1p4          │
│                                                       │ ─────────────── │
│                                                       │ ⚪ SYSTEM       │
│                                                       │ Update available│
│                                                       │                 │
└───────────────────────────────────────────────────────┴─────────────────┘
```
**UX Flow:**
- When a new notification arrives, a subtle badge appears: `(🔔 1)`.
- Pressing `n` slides the drawer out from the right (by adjusting the width of the main view `cols_ - drawer_width`).
- Pressing `n` again or `Esc` closes it.

---

## 4. Leaderboard & Coalitions

**UX Problem:** Data-heavy tables can look boring in the terminal.
**Solution:** Utilize the existing inline-image support for avatars (if possible in the grid) and use progress bars for visual flair.

### ASCII Mockup
```text
┌─ LEADERBOARD ─────────────────────────────────────────────────────────┐
│  🏆 THE FEDERATION : 142,030 pts  |  🛡️ THE ALLIANCE : 138,500 pts    │
├───────────────────────────────────────────────────────────────────────┤
│ RANK  USER        COALITION    LEVEL      PROGRESS                    │
│ ───────────────────────────────────────────────────────────────────── │
│  #1   johndoe     Federation   14.2  [██████████████████··]           │
│  #2   janedoe     Alliance     13.8  [██████████████······]           │
│  #3   pablo       Federation   12.1  [██████████··········]           │
│  #4   alice       Order        11.9  [█████████···········]           │
│                                                                       │
└───────────────────────────────────────────────────────────────────────┘
```
**UX Flow:**
- Simple vertical scrolling list.
- The coalition names at the top act as a toggle filter (click or press `1`/`2` to filter the list by coalition).
- Selecting a row and pressing `Enter` opens their profile modal.
