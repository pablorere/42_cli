# 42 Intra endpoints (cookie/session surface)

> Maintained by the `scrape` skill and the `scraper` agent. Refresh with the
> OpenCLI browser bridge or `curl -b <cookie>`.
>
> **Last verified:** 2026-09-15 against a live session (login `ppaula-s`) using
> `curl -b <cookie>` and `opencli browser` (`eval`/`network`). JSON endpoints
> discovered by capturing XHRs on the intranet pages and probing candidates.
>
> This is the **cookie-authenticated intranet** surface 42_cli uses today. The
> **official OAuth2 API** is documented separately in `api42-apidoc.md` /
> `api42-endpoints.md` / `api42-examples.md`.

## Auth model

- Session is a Netscape-format cookie jar; path from
  `network::cookie_file_path()` (`$XDG_DATA_HOME`/`~/.local/share`,
  default `~/.local/share/intra_cli/cookies.txt`).
- Keycloak-backed: cookie names observed `KEYCLOAK_SESSION`,
  `KEYCLOAK_SESSION_LEGACY`, `locale`, `user.id`.
- Login flow (`network::do_login`): `GET /users/sign_in` → CSRF token →
  `POST` to `auth.42.fr` (`Origin: https://auth.42.fr`) → redirect to
  `profile.intra.42.fr`.
- `intra.42.fr` (bare) 302-redirects to `https://profile.intra.42.fr/`.
- JSON endpoints accept `Accept: application/json`; others are HTML-scraped
  (`html_parser.cpp`).
- Hosts: `profile.intra.42.fr`, `projects.intra.42.fr`, `meta.intra.42.fr`,
  `cdn.intra.42.fr`, `translate.intra.42.fr`, `auth.42.fr`, `signin.intra.42.fr`.

## Endpoints

| # | Host | Path | Method | Auth/Headers | Body/Query | Response | Consumer |
|---|------|------|--------|--------------|------------|----------|----------|
| 1 | profile | `/` | GET | cookie | — | HTML (302 → sign-in) | `session_is_valid` |
| 2 | profile | `/v3_early_access` | GET | cookie | — | JSON (currently 500) | `network.cpp:192` |
| 3 | profile | `/v3_early_access/switch` | POST | cookie, Origin | form | redirect | `network.cpp:202` |
| 4 | signin | `/users/sign_in` | GET | — | — | HTML form + CSRF | `do_login` |
| 5 | auth | `/users/sign_in` | POST | Origin | username/password/authenticity_token | redirect | `do_login` |
| 6 | profile | `/users/<login>` | GET | cookie, `Accept: json`/`html` | path | Profile JSON or HTML + CDN avatar | `fetch_profile`, `fetch_user_profile`, `fetch_user_full_name` |
| 7 | profile | `/users/me` | GET | cookie, `Accept: json` | — | Profile JSON (same as 6) | — (discovered) |
| 8 | profile | `/users/me/skills?cursus=42cursus` | GET | cookie, `Accept: json` | `cursus` | `[{id,name,lvl,percent}]` | — |
| 9 | profile | `/users/<login>/skills?cursus=42cursus` | GET | cookie, `Accept: json` | `cursus` | `[{id,name,lvl,percent}]` | — |
| 10 | profile | `/users/me/goals?cursus=42cursus` | GET | cookie, `Accept: json` | `cursus` | `{container,cc_validated,edtrax_weeks[],probationary_period,next_milestone,next_milestone_days,cc_eta,cc_eta_days}` | — |
| 11 | profile | `/users/<login>/goals?cursus=42cursus` | GET | cookie, `Accept: json` | `cursus` | same as 10 | — |
| 12 | profile | `/users/me/coalitions?cursus=42cursus` | GET | cookie, `Accept: json` | `cursus` | `{coalitions_user:{…},…}` | — |
| 13 | profile | `/users/<login>/coalitions?cursus=42cursus` | GET | cookie, `Accept: json` | `cursus` | same as 12 | — |
| 14 | profile | `/events.json` | GET | cookie, `Accept: json` | — | JSON list (empty in test) | — |
| 15 | profile | `/searches/search?query=<q>` | GET | cookie, `Accept: json` | `query` | JSON search results | — |
| 16 | profile | `/slots.json?start=<iso>&end=<iso>` | GET | cookie, Referer `/slots` | `start`, `end` | `[{begin_at,end_at,id,…}]` | `fetch_slots` |
| 17 | profile | `/slots/unavailable.json` | GET | cookie | — | 204 (no content) | — |
| 18 | profile | `/slots/available.json` | GET | cookie | — | 403 (needs params) | — |
| 19 | profile | `/slots` | GET | cookie, Referer `/slots` | — | HTML (CSRF context) | `create_slot`,`delete_slot`,`update_slot` |
| 20 | profile | `/slots.json` | POST | cookie, Origin | `slot[begin_at]`,`slot[end_at]` | redirect/JSON | `create_slot` |
| 21 | profile | `/slots/<id>.json` | DELETE | cookie, Origin | path `id` | JSON | `delete_slot` |
| 22 | profile | `/slots/<ids>.json` | PATCH | cookie, Origin | path `ids`,`slot[end_at]` | JSON | `update_slot` (trim) |
| 23 | cdn | `/users/<login>` (avatar) | GET | cookie | — | image | `fetch_image` / avatars |
| 24 | projects | `/project_data.json?cursus_id=21` | GET | cookie | `cursus_id=21` | JSON holygraph array | `fetch_holygraph` |
| 25 | projects | `/projects.json` | GET | cookie | — | HTML partial (Rails view) | — |
| 26 | projects | `/projects/<slug>` (or `42cursus-<slug>`) | GET | cookie | path | HTML → subject PDF href | `download_subject` |
| 27 | projects | `/projects/<slug>/stats.json` | GET | cookie, `Accept: json` | path | `{success,average_team_lifespan,final_mark_by_campus,flags}` | — |
| 28 | projects | `/projects/<slug>/project_sessions.json` | GET | cookie | path | 403 (restricted) | — |
| 29 | projects | `/users/<login>/feedbacks` | GET | cookie | path | HTML feedback (given/received, pending) | `fetch_feedbacks` |
| 30 | projects | `/projects/<slug>/scale_teams` | GET | cookie | path | HTML public evaluation records | `fetch_project_scale_teams` |
| 31 | meta | `/clusters.json` | GET | cookie | — | `[{host,begin_at,end_at,login,cdn_uri,image,campus_id}]` | `fetch_clusters` |
| 32 | meta | `/campus/<id>/clusters.json` | GET | cookie | path | same shape as 31 | — |
| 33 | translate | `/users/<login>/locations_stats.json` | GET | cookie | path | JSON location stats | — |

## Verification status (2026-09-15, live session)

| Endpoint | Result |
|----------|--------|
| profile `/` | 302 → sign-in/dashboard |
| profile `/users/<login>` (`Accept: json`) | **200** JSON (728 B) |
| profile `/users/me` | **200** JSON |
| profile `/users/me/skills` and `/users/<login>/skills` | **200** JSON `array(6) {id,name,lvl,percent}` |
| profile `/users/me/goals`, `/users/<login>/goals` | **200** JSON |
| profile `/users/me/coalitions`, `/users/<login>/coalitions` | **200** JSON |
| profile `/events.json` | **200** JSON `[]` |
| profile `/searches/search?query=libft` | **200** JSON `[]` |
| profile `/slots.json?start&end` | **200** JSON `[]` |
| profile `/slots/unavailable.json` | **204** |
| profile `/slots/available.json` | **403** |
| projects `/project_data.json?cursus_id=21` | **200** JSON (125 KB, ~205 nodes) |
| projects `/projects/<slug>/stats.json` | **200** JSON |
| projects `/users/<login>/feedbacks` | **200** HTML (24.6 KB) |
| meta `/clusters.json` | **200** JSON (895 B, `array(4)`) |
| meta `/campus/40/clusters.json` | **200** JSON (same shape) |
| translate `/users/<login>/locations_stats.json` | **200** JSON |

Mutation rows (3, 5, 20-22) are documented from `src/network.cpp` only and remain
`[unverified]` — do not replay blindly.

## Details

### 6-7. Profile JSON
Verified keys: `login, email, full_name, usual_full_name, location, image,
cursus, groups`. `image` is `{link, versions:{large,medium,small,micro}}`
(all `https://cdn.intra.42.fr/users/...`). `location` is a seat like `c3r1s5`.

### 8-13. `/users/(me|<login>)/(skills|goals|coalitions)`
Scoped to a user; `me` = the authenticated user. `cursus=42cursus` selects the
cursus. `skills` = `[{id,name,lvl,percent}]`; `goals` = CC/milestone progress
(`next_milestone`, `cc_eta`, `edtrax_weeks[]`, `probationary_period`).

### 16-22. Slots
`fetch_slots` GETs `slots.json` with an ISO `start`/`end` range. Mutations carry
`Origin: https://profile.intra.42.fr`. `create_slot` POSTs
`slot[begin_at]`/`slot[end_at]` (ISO 8601, +offset applied internally);
`update_slot` PATCHes `slot[end_at]`; `delete_slot` DELETEs by `id`.
`/slots/unavailable.json` returns 204 (no unavailable window).

### 24. Holygraph
`project_data.json?cursus_id=21` returns a flat JSON array (~205 nodes);
observed keys `id,kind,name,slug,state,final_mark,project_id,difficulty,duration,x,y,rules,description,by`.

### 27. Project stats
`projects/<slug>/stats.json` → `{success, average_team_lifespan,
final_mark_by_campus, flags}`.

### 29-30. Feedback / scale-teams (HTML scrape)
Public pages under `projects.intra.42.fr`; parsed for `EvaluationFeedback`
(`is_given`, `is_pending`, `rating_breakdown`) and `ScaleTeamRecord`
(`types.hpp:149-160`).

### 31-32. Clusters
`meta.intra.42.fr/clusters.json` (and campus-scoped
`/campus/<id>/clusters.json`) → `array(4)` of
`{host,begin_at,end_at,login,cdn_uri,image,campus_id}`; feeds the minimap.

### 33. Locations stats
`translate.intra.42.fr/users/<login>/locations_stats.json` — location/presence
stats (different host; discovered via profile-page XHR).
