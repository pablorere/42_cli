# 42_cli — feature catalogue

> Generated from the API research in `endpoints.md`, `api42-apidoc.md`,
> `api42-endpoints.md` and `api42-examples.md`.
> Every feature lists the data source it needs. Legend:
> **I** = intranet cookie endpoint (works today, `endpoints.md`),
> **O** = official OAuth2 API v2 (needs an app + token flow, `api42-endpoints.md`),
> **L** = local/offline (no network).
> Effort: **S** (hours), **M** (a day), **L** (multi-day).

## Data sources available

| Source | What it unlocks |
|--------|-----------------|
| Intranet cookie (I) | profile, slots, clusters, holygraph, feedbacks, scale_teams, skills/goals/coalitions, events, search, project stats, locations |
| Official OAuth2 API (O) | 741 endpoints: full user/project/scale-team/feedback CRUD, coalitions, campus, events, exams, quests, achievements, titles, transactions, forum, locations, teams |
| Local cache (L) | images, profiles, offline browsing, history |

---

## 1. Profile & student card

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Skill radar / skill bars (`lvl`, `percent` per skill) | I `/users/me/skills` | M | High |
| Next-milestone countdown + CC ETA + probation flag | I `/users/me/goals` | S | High |
| Coalition badge + coalition colour | I `/users/me/coalitions` | S | Med |
| Level progression projection (to next level) | L (level + history) | M | Med |
| Wallet / correction-point ledger + sparkline | I profile + O `/v2/transactions` | M | Med |
| Achievements grid (earned / locked) | O `/v2/achievements`, `/v2/users/:id/achievements` | M | Med |
| Titles collection | O `/v2/titles`, `/v2/users/:id/titles` | S | Low |
| Campus rank / percentile | O `/v2/campus/:id/stats` | M | Med |
| Profile export (JSON/Markdown/CSV) | L + I | S | Low |
| Compare two users (skills/level/projects) | I + O | M | Med |

## 2. Slots

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Slot availability heatmap (busy hours per campus/day) | I `/slots/unavailable.json`, `/slots.json` | M | High |
| Peak-hour suggestions ("book 14:00–18:00 for fastest match") | I + L | S | Med |
| Free-space gap between slots (shipped) | L `slot_gap_minutes` | — | Done |
| Recurring / weekly slots (create N slots at once) | I `POST /slots.json` | M | Med |
| Auto-trim / auto-extend slots | I `PATCH /slots/:ids.json` | S | Low |
| Watch for open slots + desktop notification | I `/slots.json` poll | M | High |
| Book a project slot as evaluated (defense booking) | O `/v2/projects/:project_id/slots` | M | High |
| Slot conflict / overlap guard (shipped, gap) | L | — | Done |
| Calendar export of slots (.ics) | L + I | S | Med |
| Campus slot-load ranking (which campus has slots) | I + O | M | Low |

## 3. Evaluations & scale teams

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Pending-feedback inbox with inline critique | I `/users/<login>/feedbacks` | S | High |
| Rating-breakdown charts (Nice/Rigorous/Interested/Punctual) | I feedbacks | M | Med |
| Evaluation history with filters (given/received/pending) | I + O `/v2/scale_teams`, `/v2/feedbacks` | M | High |
| Auto-fill an evaluation (flags, comment template) | O `POST /v2/scale_teams/:id/feedbacks` | L | Med |
| Feedback templates / snippets | L | S | Med |
| Peer reputation (avg rating given) | I feedbacks | M | Low |
| "Who evaluated me best/worst" summary | I | S | Low |
| Scale-team scheduling view | O `/v2/scale_teams` | M | Med |

## 4. Projects & roadmap

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Holygraph with progress %, difficulty, est. hours | I `/project_data.json` | M | High |
| Project stats panel (success rate, avg lifespan, marks by campus) | I `/projects/<slug>/stats.json` | S | Med |
| Register / unregister a project | O `/v2/projects/:id/register`, `/v2/projects_users` | M | Med |
| Submission + auto-eval status | O `/v2/projects_users/:id` | M | Med |
| Team view (teammates, shared status) | O `/v2/teams`, `/v2/projects/:id/teams` | M | Med |
| Subject PDF viewer + full-text search (viewer shipped) | L + I | M | Med |
| Project dependency / unlock graph | I holygraph + O `/v2/projects` | L | Low |
| Mark projection ("grade needed to validate") | L + O | M | Med |
| Download all subjects in bulk | I | S | Low |

## 5. Cluster & presence

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Live cluster map + room heatmap (map shipped) | I `/clusters.json` | M | High |
| "Who's on campus" leaderboard | I `/clusters.json` | S | Med |
| Friend/peer presence alerts (someone arrives) | I poll `/clusters.json` | M | High |
| Location history / time-on-campus | I `/users/<login>/locations_stats.json` | M | Med |
| Campus occupancy over the day (chart) | I + O `/v2/locations` | L | Med |
| Jump to a peer's desk / copy login (shipped) | I | — | Done |
| Campus-wide search by seat | I | S | Low |

## 6. Search & navigation

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Global search (shipped: users + projects) | I `/searches/search` | — | Done |
| Extend search to coalitions/events/teams | I + O | M | Med |
| Fuzzy finder / command palette (`:` or `Ctrl-P`) | L | M | High |
| Jump history / back-stack | L | S | Med |
| Bookmarks / pinned users & projects | L | S | Med |
| Vim-style marks and registers | L | M | Low |

## 7. Notifications & events

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Notifications inbox + unread badge | I `/notifications` | M | High |
| Event calendar (campus/cursus) | O `/v2/events`, `/v2/campus/:id/events` | M | Med |
| Exam schedule | O `/v2/exams`, `/v2/users/:id/exams` | M | Med |
| Announcements feed | O `/v2/announcements` | S | Low |
| Desktop/terminal toasts for new events | L | S | Med |
| .ics export for events/exams | L + O | S | Med |

## 8. Social, coalitions & forum

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Coalition leaderboard + bloc standings | O `/v2/coalitions`, `/v2/blocs` | M | High |
| Coalition members / points | O `/v2/coalitions_users` | S | Med |
| Forum topics + messages (read) | O `/v2/topics`, `/v2/messages` | L | Med |
| Post a forum message | O `POST /v2/topics/:id/messages` | M | Low |
| Peer profile viewer (shipped user modal) | I + O | — | Done |
| Project partners / patronages | O `/v2/partnerships`, `/v2/patronages` | M | Low |
| Expertises / endorsements | O `/v2/expertises_users` | S | Low |

## 9. Economy & points

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Correction-points ledger + history | I + O `/v2/users/:id/correction_point_historics` | M | Med |
| Wallet transactions view | O `/v2/transactions` | S | Low |
| Shop / products catalogue | O `/v2/products`, `/v2/commands` | M | Low |
| Pool status / eligibility | I + O `/v2/pools`, `/v2/balances` | M | Med |
| "How many evaluations to afford X" calculator | L | S | Low |

## 10. Gamification

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Quests tracker | O `/v2/quests`, `/v2/quests_users` | M | Med |
| Achievements / badges grid | O `/v2/achievements` | M | Med |
| Titles | O `/v2/titles` | S | Low |
| Daily streak / activity heatmap (GitHub-style) | I + L | M | Med |
| Level-up celebration | L | S | Low |

## 11. Analytics

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Personal stats dashboard (evals given/received, avg grade, time-to-validate) | I feedbacks + O | L | High |
| Progress sparklines / charts | L | M | Med |
| Campus analytics (active users, projects) | O `/v2/campus/:id/stats` | M | Med |
| Export analytics (CSV/JSON) | L | S | Low |
| Time-on-campus report | I locations_stats | M | Low |

## 12. TUI / UX

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Themes (10 shipped) + user theme files | L | S | Med |
| Mouse controls + hover (shipped) | L | — | Done |
| Toast/notification system | L | S | High |
| Command palette | L | M | High |
| Split panes / resizable layout | L | L | Med |
| Config profiles (work/home) | L | S | Low |
| More i18n languages (en/es shipped) | L | M | Med |
| High-contrast / accessibility mode | L | M | Med |
| Plugin/scripting hooks | L | L | Low |
| Non-TUI subcommands (`42_cli slots --json`) | L + I | M | High |
| Export current view (JSON/CSV/Markdown) | L | S | Med |
| Image rendering (kitty/iTerm2/chafa) — WIP branch | L | — | Done* |
| Reduce-motion / no-images mode | L | S | Low |
| Keybinding remapping | L | M | Med |

## 13. Auth & accounts

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| OAuth2 app support (official API) alongside cookie | O | L | High |
| Token refresh / expiry handling | O | M | High |
| Multi-account switching | I + O | M | Med |
| 2FA / Keycloak re-auth flow polish | I | M | Med |
| Secure cookie storage permissions check | L | S | Low |

## 14. Automation

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Scheduled slot opening (open at 08:00 daily) | I | M | High |
| Watch for free slots + auto-notify | I | M | High |
| Auto-trim slots at a threshold | I | S | Low |
| Auto-sync on interval | I | S | Med |
| Rules engine (if X then Y) | L | L | Low |

## 15. Integrations

| Feature | Source | Effort | Value |
|---------|--------|--------|-------|
| Desktop notifications (notify-send / OSC) | L | S | High |
| Shell completion (bash/zsh/fish) | L | S | Med |
| Discord/Slack webhook on events | L | M | Low |
| Git integration (repos, commits) | O `/v2/gitlab_users` | M | Low |
| .ics calendar export | L | S | Med |
| Webhooks (register) | O `/v2/webhook_registeries` | M | Low |

---

## Suggested roadmap

1. **Quick wins (S, high value):** next-milestone countdown, coalition badge, pending-feedback inbox, project stats panel, notifications inbox, toasts.
2. **High value (M):** skill radar, slot heatmap + watch/notify, coalition leaderboard, personal analytics dashboard, command palette.
3. **Big swings (L):** OAuth2 API integration (unlocks sections 8/9/10 + write actions), non-TUI subcommands, auto-open slots.

## Notes

- Everything in section **O** requires an OAuth2 app + token flow (see
  `api42-apidoc.md` → Authentication); the app must be registered and scoped.
- Rate limit for the official API is **2 req/s / 1200 req/h** — batch and cache.
- The intranet cookie surface (section **I**) works today with the existing
  session and is the fastest path for read-only features.
- `*` image rendering is implemented on this branch (`feat/prettier-image-rendering`).
