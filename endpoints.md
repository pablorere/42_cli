# 42 Intra endpoints

> Generated/maintained by the `scrape` skill (`.opencode/skills/scrape/SKILL.md`) and
> the `scraper` agent (`.opencode/agent/scraper.md`). Re-run the scraper to refresh,
> or follow the skill procedure manually.
>
> **Last verified:** 2026-09-15 against a live session (login `ppaula-s`) using
> `curl -b <cookie>` and the OpenCLI browser bridge
> (`opencli browser intra eval` / `opencli browser intra network`).

## Auth model

- Session is a Netscape-format cookie jar, path resolved by
  `network::cookie_file_path()` (`$XDG_CACHE_HOME`/`~/.cache`, default
  `~/.local/share/intra_cli/cookies.txt` loaded in).
- Login flow (`network::do_login`): `GET /users/sign_in` → extract CSRF token →
  `POST` to `auth.42.fr` (fields + `Origin: https://auth.42.fr`) → follow redirects
  to `profile.intra.42.fr`. Cookie jar is written on every request.
- Keycloak-backed session: cookie names observed are `KEYCLOAK_SESSION`,
  `KEYCLOAK_SESSION_LEGACY`, `locale`, `user.id`.
- JSON-capable endpoints accept `Accept: application/json`; some pages accept
  HTML and are scraped with `html_parser.cpp`.
- `intra.42.fr` (bare) 302-redirects to `https://profile.intra.42.fr/` once
  authenticated.

## Endpoints

| # | Host | Path | Method | Auth/Headers | Body/Query | Response | Consumer |
|---|------|------|--------|--------------|------------|----------|----------|
| 1 | profile.intra.42.fr | `/` | GET | cookie | — | HTML (302 → sign-in if no session) | `session_is_valid` |
| 2 | profile.intra.42.fr | `/v3_early_access` | GET | cookie | — | HTML/JSON flag | `network.cpp:192` |
| 3 | profile.intra.42.fr | `/v3_early_access/switch` | POST | cookie, Origin | form fields | redirect | `network.cpp:202` |
| 4 | signin.intra.42.fr | `/users/sign_in` | GET | — | — | HTML form + CSRF token | `do_login` |
| 5 | auth.42.fr | `/users/sign_in` (or relative action) | POST | Origin: `https://auth.42.fr` | username/password/authenticity_token | redirect to profile | `do_login` |
| 6 | profile.intra.42.fr | `/users/<login>` | GET | cookie, `Accept: application/json` or `text/html` | path | Profile JSON (or HTML scrape) + CDN avatar link | `fetch_profile`, `fetch_user_profile`, `fetch_user_full_name` |
| 7 | cdn.intra.42.fr | `/users/<login>` (avatar) | GET | cookie | — | image | `fetch_image` / avatar rendering |
| 8 | profile.intra.42.fr | `/slots.json?start=<iso>&end=<iso>` | GET | cookie, Referer: `/slots` | query `start`, `end` | JSON slot list `[{begin_at,end_at,id,...}]` | `fetch_slots` |
| 9 | profile.intra.42.fr | `/slots` | GET | cookie, Referer: `/slots` | — | HTML (CSRF context for mutations) | `create_slot`, `delete_slot`, `update_slot` |
| 10 | profile.intra.42.fr | `/slots.json` | POST | cookie, Origin: `https://profile.intra.42.fr` | `slot[begin_at]`, `slot[end_at]` (ISO 8601) | redirect / JSON | `create_slot` |
| 11 | profile.intra.42.fr | `/slots/<id>.json` | DELETE | cookie, Origin | path `id` | JSON | `delete_slot` |
| 12 | profile.intra.42.fr | `/slots/<ids>.json` | PATCH | cookie, Origin | path `ids` (single id for trim), `slot[end_at]` | JSON | `update_slot` (trim 15m) |
| 13 | projects.intra.42.fr | `/projects/<slug>` (or `42cursus-<slug>`) | GET | cookie | path | HTML → subjects PDF href `cdn.intra.42.fr/pdf/pdf/...` | `download_subject` |
| 14 | projects.intra.42.fr | `/project_data.json?cursus_id=21` | GET | cookie | query `cursus_id=21` | JSON holygraph tree (milestones 0..6) | `fetch_holygraph` |
| 15 | meta.intra.42.fr | `/clusters.json` | GET | cookie | — | JSON clusters (campus_id, desks/rows layout) | `fetch_clusters` |
| 16 | projects.intra.42.fr | `/users/<login>/feedbacks` | GET | cookie | path | HTML evaluation feedback (given/received, pending marks) | `fetch_feedbacks` |
| 17 | projects.intra.42.fr | `/projects/<slug>/scale_teams` or `/<slug>/scale_teams` | GET | cookie | path | HTML public evaluation records | `fetch_project_scale_teams` |
| 18 | profile.intra.42.fr | `/users/me` | GET | cookie, `Accept: application/json` | — | Profile JSON (same shape as row 6) | — (discovered; not yet consumed) |
| 19 | profile.intra.42.fr | `/users/me/skills?cursus=42cursus` | GET | cookie, `Accept: application/json` | query `cursus` | JSON `[{id,name,lvl,percent}]` | — (discovered; not yet consumed) |
| 20 | profile.intra.42.fr | `/users/me/goals?cursus=42cursus` | GET | cookie, `Accept: application/json` | query `cursus` | JSON `{container,cc_validated,edtrax_weeks[],probationary_period,next_milestone,next_milestone_days,cc_eta,cc_eta_days}` | — (discovered; not yet consumed) |
| 21 | profile.intra.42.fr | `/users/me/coalitions?cursus=42cursus` | GET | cookie, `Accept: application/json` | query `cursus` | JSON `{coalitions_user:{id,user_id,...},...}` | — (discovered; not yet consumed) |

## Verification status (2026-09-15, live session)

| Endpoint | Result |
|----------|--------|
| `GET /` (profile root) | 302 → sign-in/dashboard |
| `GET /users/<login>` (`Accept: application/json`) | **200** JSON, 728 B |
| `GET /slots.json?start&end` | **200** JSON, `[]` (no slots in range) |
| `GET /users/me` | **200** JSON |
| `GET /users/me/skills?cursus=42cursus` | **200** JSON |
| `GET /users/me/goals?cursus=42cursus` | **200** JSON |
| `GET /users/me/coalitions?cursus=42cursus` | **200** JSON |
| `GET projects /users/<login>/feedbacks` | **200** `text/html` (24.6 KB) |
| `GET meta /clusters.json` | **200** JSON, 895 B |
| `GET projects /project_data.json?cursus_id=21` | **200** JSON, 125 KB |

Mutation rows (3, 5, 10, 11, 12) are documented from `src/network.cpp` only and
remain `[unverified]` — do not replay blindly.

## Details

### 1. `GET profile.intra.42.fr/`
Used by `session_is_valid` to check a cookie still logs in. If the response
redirects to `/sign_in`, the session is expired (`fetch_profile` uses the same
page + JSON accept header at `src/network.cpp:576-590`).

### 6. `GET profile.intra.42.fr/users/<login>`
Tries JSON first (`Accept: application/json`) then falls back to the HTML page.
Verified JSON keys: `login, email, full_name, usual_full_name, location, image,
cursus, groups`. `image` is an object with `link` + `versions.{large,medium,small,micro}`
(all `https://cdn.intra.42.fr/users/...`). `location` is a cluster seat like
`c3r1s5`. HTML page also embeds the same avatar URL (parsed by `html_parser.cpp`).

### 8-12. Slot CRUD on `profile.intra.42.fr/slots*.json`
Mutations carry `Origin: https://profile.intra.42.fr`. `create_slot` POSTs
`slot[begin_at]`/`slot[end_at]` (ISO 8601), applying the +15 min preventive
offset internally. `update_slot` PATCHes `slot[end_at]` for trim (d).
`delete_slot` DELETEs by `id`.
Slots list shapes map to `struct Slot {begin_at,end_at,id,ids,title}`
(`include/types.hpp:163-169`).

### 13. Subject PDF download
Candidate slugs: `<name>` then `42cursus-<name>` (lowercased, spaces→`-`).
Find PDF href matching `cdn.intra.42.fr/pdf/pdf/` in the project page HTML,
GET it, validate `%PDF` magic, write to `subjects/<slug>.pdf`.

### 14. Holygraph `project_data.json`
`curl -s -b <cookie> "https://projects.intra.42.fr/project_data.json?cursus_id=21"`.
Returns a flat JSON array (~205 entries) of nodes; observed keys:
`id, kind, name, slug, state, final_mark, project_id, difficulty, duration, x, y, rules, description, by`.
Shapes map to `Milestone`/`HolyProject` (`types.hpp:22-38`).

### 15. Clusters `meta.intra.42.fr/clusters.json`
Feed for the cluster minimap; campus `clusters` with desks → `ClusterStudent`
(`types.hpp:41-48`, layout constants in `cluster_layout`). Observed element keys:
`host, begin_at, end_at, login, cdn_uri, image, campus_id`.

### 16-17. Feedback / scale-teams (HTML scrape)
Public pages under `projects.intra.42.fr`; parsed for `EvaluationFeedback`
(`is_given`, `is_pending`, `rating_breakdown`) and `ScaleTeamRecord`
(`types.hpp:149-160`). Pending count feeds the "action required" status hint.

### 18-21. `/users/me/*` (discovered via OpenCLI network capture)
Found while capturing the profile home page's XHRs
(`opencli browser intra network`). All return JSON and are scoped to the
authenticated user (`me`), so they need no `<login>` path segment:
- `/users/me` — same shape as row 6.
- `/users/me/skills?cursus=42cursus` — skill levels: `[{id,name,lvl,percent}]`.
- `/users/me/goals?cursus=42cursus` — milestone/CC progress (see row 20).
- `/users/me/coalitions?cursus=42cursus` — coalition membership (see row 21).

Not yet consumed by `42_cli`; candidates for the dashboard (skills radar,
next-milestone countdown, coalition badge).
