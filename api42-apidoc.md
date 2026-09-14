# 42 API v2 — `api.intra.42.fr` (scraped documentation)

> Scraped from <https://api.intra.42.fr/apidoc> on 2026-09-15 via the OpenCLI
> browser bridge (`opencli browser api extract`) over the authenticated session.
> The apidoc is a custom renderer (`moon_raker.js`), **not** Swagger — no
> machine-readable spec is served. This file is a distilled transcription:
> **97 resources / 741 endpoints**.
>
> Companion to `endpoints.md`, which documents the **cookie-scraped intranet**
> endpoints 42_cli uses today. This file documents the **official OAuth2 API**,
> which 42_cli does **not** use yet.

## Overview

- RESTful, JSON over HTTPS, OAuth 2.0.
- Base URL: `https://api.intra.42.fr/v2` (current version **2.0**).
- All timestamps ISO 8601; blank fields are `null` (never omitted).
- Stats at scrape time: 741 endpoints · 940,367 tokens issued · ~110 ms avg.

## Authentication (OAuth 2.0)

- Register an application: <https://profile.intra.42.fr/oauth/applications/new>
  → yields a **client uid** + **client secret** (secret is server-side only).
- **Client Credentials flow** (server-side, no user):

  ```bash
  curl -X POST --data "grant_type=client_credentials&client_id=UID&client_secret=SECRET" \
       https://api.intra.42.fr/oauth/token
  # => {"access_token":"...","token_type":"bearer","expires_in":7200,"scope":"public","created_at":...}
  ```

- Send the token as `Authorization: Bearer <token>` (or `?access_token=<token>`).
- Token introspection: `GET https://api.intra.42.fr/oauth/token/info`.
- Scopes: a wrong/insufficient scope returns `403` with
  `WWW-Authenticate: Bearer ... error="insufficient scope"`.

### Authorization Code flow (Web Application flow)

To act **on behalf of a user** (3rd-party web app):

1. **Redirect** the user to `GET https://api.intra.42.fr/oauth/authorize` with
   `client_id`, `redirect_uri`, `response_type=code`, `scope` (space-separated),
   `state` (random, anti-CSRF):
   `.../oauth/authorize?client_id=…&redirect_uri=…&response_type=code&scope=public&state=…`
2. **42 redirects back** to `redirect_uri?code=…&state=…` — verify `state` matches.
3. **Exchange the code** (server-side, secure connection):

   ```bash
   curl -F grant_type=authorization_code -F client_id=… -F client_secret=… \
        -F code=… -F redirect_uri=… -X POST https://api.intra.42.fr/oauth/token
   ```

4. **Call the API** with `Authorization: Bearer <token>`.

> If the user already holds a valid token for the app, the consent screen is
> skipped and the previous scopes are reused.

## Guides

| Guide | Path | Covers |
|-------|------|--------|
| Specification | `/apidoc/guides/specification` | version, auth, errors, scopes, pagination, filtering, sorting, rate limits, JSON-API (decommissioned) |
| Getting started | `/apidoc/guides/getting_started` | create app, credentials, client-credentials flow, pagination, limits, roles |
| Web application flow | `/apidoc/guides/web_application_flow` | OAuth2 authorization-code flow (authorize → code → token) |
| Contributing | `/apidoc/guides/contributing` | contributing to the docs |
| Readme | `/apidoc/guides/README` | documentation index |

## Conventions

### Errors
`400` malformed · `401` unauthorized · `403` forbidden · `404` not found ·
`422` unprocessable · `500` server error · connection refused → not using HTTPS.

### Pagination
- All resources are paginated on the **index** method; 30 items by default.
- `?page=N&per_page=M` or `?page[number]=N&page[size]=M`. `per_page`/`page[size]`
  can go up to **100**, but *not every endpoint* supports the maximum.
- Response headers: `Link` (`first`/`prev`/`next`/`last`), `X-Page` (current page),
  `X-Per-Page` (page length), `X-Total` (page count).

### Filtering
- `?filter[field]=v1,v2` (comma-separated values), e.g.
  `GET /v2/users?filter[pool_year]=2013&filter[pool_month]=september,july`.

### Sorting
- `?sort=kind,-login` — comma-separated, applied in order; `-` prefix = descending.

### Rate limiting
- Default **2 requests/second** and **1200 requests/hour** per application.
- Roles (`x-application-roles`): Alpha, Beta, Official App, Certified App,
  Moderator, Basic Tutor, Basic Staff. Official/Certified raise the limit.

### JSON-API format (decommissioned)
- The API also supports the JSON-API format (alpha-stage): request it with
  `Content-Type: application/vnd.api+json`. Marked **decommissioned** in the docs.

### Token introspection
- `GET https://api.intra.42.fr/oauth/token/info` with `Authorization: Bearer <token>`
  returns `{resource_owner_id, scopes, expires_in_seconds, application, created_at}`.

## Resources & endpoints

> `[restricted]` = the docs mark it with `_vpn_key_` (needs an elevated app role).

### Accreditations
- `GET /v2/accreditations`  `[restricted]`
- `GET /v2/accreditations/:id`
- `POST /v2/accreditations`  `[restricted]`
- `PATCH /v2/accreditations/:id`  `[restricted]`
- `PUT /v2/accreditations/:id`  `[restricted]`
- `DELETE /v2/accreditations/:id`  `[restricted]`

### Achievements
- `GET /v2/achievements`
- `GET /v2/cursus/:cursus_id/achievements`
- `GET /v2/campus/:campus_id/achievements`
- `GET /v2/titles/:title_id/achievements`
- `GET /v2/achievements/:id`
- `POST /v2/achievements`  `[restricted]`
- `PATCH /v2/achievements/:id`  `[restricted]`
- `PUT /v2/achievements/:id`  `[restricted]`
- `DELETE /v2/achievements/:id`  `[restricted]`

### Achievements users
- `GET /v2/achievements/:achievement_id/achievements_users`
- `GET /v2/achievements_users`
- `GET /v2/achievements_users/:id`
- `POST /v2/achievements_users`  `[restricted]`
- `PATCH /v2/achievements_users/:id`  `[restricted]`
- `PUT /v2/achievements_users/:id`  `[restricted]`
- `DELETE /v2/achievements_users/:id`  `[restricted]`

### Alumnized users
- `GET /v2/alumnized_users`  `[restricted]`

### Amendments
- `GET /v2/amendments`
- `GET /v2/users/:user_id/amendments`
- `GET /v2/internships/:internship_id/amendments`
- `GET /v2/amendments/:id`
- `POST /v2/amendments`  `[restricted]`
- `DELETE /v2/amendments/:id`  `[restricted]`

### Announcements
- `GET /v2/announcements/graph(/on/:field(/by/:interval)`
- `GET /v2/announcements/:id`
- `POST /v2/announcements`  `[restricted]`
- `POST /v2/cursus/:cursus_id/announcements`  `[restricted]`
- `PATCH /v2/announcements/:id`  `[restricted]`
- `PUT /v2/announcements/:id`  `[restricted]`
- `DELETE /v2/announcements/:id`  `[restricted]`

### Anti grav units
- `GET /v2/anti_grav_units`  `[restricted]`
- `GET /v2/anti_grav_units/:id`  `[restricted]`

### Anti grav units users
- `GET /v2/anti_grav_units_users`  `[restricted]`
- `GET /v2/users/:user_id/anti_grav_units_users`  `[restricted]`
- `GET /v2/campus/:campus_id/anti_grav_units_users`  `[restricted]`
- `GET /v2/anti_grav_units_users/:id`  `[restricted]`
- `POST /v2/anti_grav_units_users`  `[restricted]`
- `PATCH /v2/anti_grav_units_users/:id`  `[restricted]`
- `PUT /v2/anti_grav_units_users/:id`  `[restricted]`

### Apps
- `GET /v2/apps`
- `GET /v2/users/:user_id/apps`
- `GET /v2/apps/:id`

### Attachments
- `GET /v2/project_sessions/:project_session_id/attachments`
- `GET /v2/projects/:project_id/attachments`
- `GET /v2/attachments`
- `GET /v2/project_sessions/:project_session_id/attachments/:id`
- `GET /v2/attachments/:id`
- `POST /v2/projects/:project_id/attachments`  `[restricted]`
- `PATCH /v2/attachments/:id`  `[restricted]`
- `PUT /v2/attachments/:id`  `[restricted]`
- `DELETE /v2/attachments/:id`  `[restricted]`

### Balances
- `GET /v2/balances`  `[restricted]`
- `GET /v2/pools/:pool_id/balances`  `[restricted]`
- `GET /v2/balances/:id`  `[restricted]`
- `GET /v2/pools/:pool_id/balances/:id`  `[restricted]`
- `PATCH /v2/balances/:id`  `[restricted]`
- `PUT /v2/balances/:id`  `[restricted]`
- `PATCH /v2/pools/:pool_id/balances/:id`  `[restricted]`
- `PUT /v2/pools/:pool_id/balances/:id`  `[restricted]`

### Bloc deadlines
- `GET /v2/bloc_deadlines`  `[restricted]`
- `GET /v2/blocs/:bloc_id/bloc_deadlines`  `[restricted]`
- `GET /v2/bloc_deadlines/:id`  `[restricted]`
- `POST /v2/bloc_deadlines`  `[restricted]`
- `PATCH /v2/bloc_deadlines/:id`  `[restricted]`
- `PUT /v2/bloc_deadlines/:id`  `[restricted]`

### Blocs
- `GET /v2/blocs`
- `GET /v2/blocs/:id`

### Broadcasts
- `GET /v2/campus/:campus_id/broadcasts`

### Campus
- `GET /v2/campus`
- `GET /v2/campus/:id`
- `POST /v2/campus`  `[restricted]`
- `PATCH /v2/campus/:id`  `[restricted]`
- `PUT /v2/campus/:id`  `[restricted]`
- `GET /v2/campus/:campus_id/stats`

### Campus users
- `GET /v2/campus_users`
- `GET /v2/users/:user_id/campus_users`
- `GET /v2/campus_users/:id`
- `POST /v2/campus_users`  `[restricted]`
- `POST /v2/users/:user_id/campus_users`  `[restricted]`
- `POST /v2/campus_users/:id/set_as_primary`  `[restricted]`

### Certificates
- `GET /v2/certificates`  `[restricted]`
- `GET /v2/certificates/:id`  `[restricted]`

### Certificates users
- `GET /v2/certificates_users`  `[restricted]`
- `GET /v2/certificates/:certificate_id/certificates_users`  `[restricted]`
- `GET /v2/users/:user_id/certificates_users`  `[restricted]`
- `GET /v2/certificates_users/:id`  `[restricted]`
- `DELETE /v2/certificates_users/:id`  `[restricted]`

### Closes
- `GET /v2/closes`  `[restricted]`
- `GET /v2/users/:user_id/closes`  `[restricted]`
- `GET /v2/closes/:id`  `[restricted]`
- `POST /v2/closes`  `[restricted]`
- `POST /v2/users/:user_id/closes`  `[restricted]`
- `PATCH /v2/closes/:id`  `[restricted]`
- `PUT /v2/closes/:id`  `[restricted]`
- `DELETE /v2/closes/:id`  `[restricted]`
- `PATCH /v2/closes/:id/unclose`  `[restricted]`
- `PUT /v2/closes/:id/unclose`  `[restricted]`
- `PATCH /v2/closes/:id/close`  `[restricted]`
- `PUT /v2/closes/:id/close`  `[restricted]`

### Clusters
- `GET /v2/clusters`  `[restricted]`
- `GET /v2/clusters/:id`  `[restricted]`

### Coalitions
- `GET /v2/coalitions`
- `GET /v2/users/:user_id/coalitions`
- `GET /v2/blocs/:bloc_id/coalitions`
- `GET /v2/coalitions/:id`
- `POST /v2/coalitions`  `[restricted]`
- `PATCH /v2/coalitions/:id`  `[restricted]`
- `PUT /v2/coalitions/:id`  `[restricted]`

### Coalitions users
- `GET /v2/coalitions/:coalition_id/coalitions_users`
- `GET /v2/coalitions_users`
- `GET /v2/users/:user_id/coalitions_users`
- `GET /v2/coalitions_users/:id`
- `POST /v2/coalitions_users`  `[restricted]`
- `PATCH /v2/coalitions_users/:id`  `[restricted]`
- `PUT /v2/coalitions_users/:id`  `[restricted]`
- `DELETE /v2/coalitions_users/:id`  `[restricted]`

### Commands
- `GET /v2/products/:product_id/commands`
- `GET /v2/campus/:campus_id/products/:product_id/commands`

### Community services
- `GET /v2/community_services/graph(/on/:field(/by/:interval)`
- `GET /v2/closes/:close_id/community_services`
- `GET /v2/community_services`
- `GET /v2/community_services/:id`
- `PUT /v2/community_services/:id/validate`  `[restricted]`
- `PATCH /v2/community_services/:id/validate`  `[restricted]`
- `PUT /v2/community_services/:id/invalidate`  `[restricted]`
- `PATCH /v2/community_services/:id/invalidate`  `[restricted]`
- `POST /v2/community_services`  `[restricted]`
- `PATCH /v2/community_services/:id`  `[restricted]`
- `PUT /v2/community_services/:id`  `[restricted]`
- `DELETE /v2/community_services/:id`  `[restricted]`

### Companies
- `GET /v2/companies`  `[restricted]`
- `GET /v2/companies/:id`  `[restricted]`
- `GET /v2/companies/:company_id/subscribed_users`  `[restricted]`
- `GET /v2/companies/:company_id/internships_users`  `[restricted]`

### Correction point historics
- `GET /v2/users/:user_id/correction_point_historics`

### Cursus
- `GET /v2/cursus`
- `GET /v2/cursus/:id`
- `POST /v2/cursus`  `[restricted]`
- `PATCH /v2/cursus/:id`  `[restricted]`
- `PUT /v2/cursus/:id`  `[restricted]`
- `DELETE /v2/cursus/:id`  `[restricted]`

### Cursus users
- `GET /v2/cursus_users/graph(/on/:field(/by/:interval)`
- `GET /v2/cursus_users`
- `GET /v2/users/:user_id/cursus_users`
- `GET /v2/cursus/:cursus_id/cursus_users`
- `GET /v2/cursus_users/:id`
- `POST /v2/cursus_users`  `[restricted]`
- `POST /v2/users/:user_id/cursus_users`  `[restricted]`
- `PATCH /v2/cursus_users/:id`  `[restricted]`
- `PUT /v2/cursus_users/:id`  `[restricted]`
- `DELETE /v2/cursus_users/:id`  `[restricted]`

### Dashes
- `GET /v2/dashes/graph(/on/:field(/by/:interval)`
- `GET /v2/dashes`  `[restricted]`
- `GET /v2/dashes/:id`  `[restricted]`
- `POST /v2/dashes`  `[restricted]`
- `PATCH /v2/dashes/:id`  `[restricted]`
- `PUT /v2/dashes/:id`  `[restricted]`
- `DELETE /v2/dashes/:id`  `[restricted]`

### Dashes users
- `GET /v2/dashes_users/graph(/on/:field(/by/:interval)`
- `GET /v2/dashes_users`
- `GET /v2/dashes/:dash_id/dashes_users`
- `GET /v2/dashes_users/:id`
- `POST /v2/dashes_users`  `[restricted]`
- `PATCH /v2/dashes_users/:id`  `[restricted]`
- `PUT /v2/dashes_users/:id`  `[restricted]`
- `DELETE /v2/dashes_users/:id`  `[restricted]`

### Endpoints
- `GET /v2/endpoints`  `[restricted]`
- `GET /v2/endpoints/:id`  `[restricted]`
- `POST /v2/endpoints`  `[restricted]`
- `PATCH /v2/endpoints/:id`  `[restricted]`
- `PUT /v2/endpoints/:id`  `[restricted]`
- `DELETE /v2/endpoints/:id`  `[restricted]`
- `POST /v2/endpoints/:id/callback`  `[restricted]`

### Evaluations
- `GET /v2/evaluations`  `[restricted]`
- `GET /v2/evaluations/:id`  `[restricted]`
- `POST /v2/evaluations`  `[restricted]`
- `PATCH /v2/evaluations/:id`  `[restricted]`
- `PUT /v2/evaluations/:id`  `[restricted]`
- `DELETE /v2/evaluations/:id`  `[restricted]`

### Events
- `GET /v2/events/graph(/on/:field(/by/:interval)`
- `GET /v2/cursus/:cursus_id/events`
- `GET /v2/campus/:campus_id/events`
- `GET /v2/campus/:campus_id/cursus/:cursus_id/events`
- `GET /v2/users/:user_id/events`
- `GET /v2/events`
- `GET /v2/events/:id`
- `POST /v2/events`  `[restricted]`
- `PATCH /v2/events/:id`  `[restricted]`
- `PUT /v2/events/:id`  `[restricted]`
- `DELETE /v2/events/:id`  `[restricted]`

### Events users
- `GET /v2/users/:user_id/events_users`
- `GET /v2/events/:event_id/events_users`
- `GET /v2/events_users`
- `GET /v2/events_users/:id`
- `POST /v2/events_users`
- `PATCH /v2/events_users/:id`
- `PUT /v2/events_users/:id`
- `DELETE /v2/events_users/:id`

### Exams
- `GET /v2/exams/graph(/on/:field(/by/:interval)`
- `GET /v2/cursus/:cursus_id/exams`
- `GET /v2/campus/:campus_id/exams`
- `GET /v2/campus/:campus_id/cursus/:cursus_id/exams`
- `GET /v2/users/:user_id/exams`
- `GET /v2/projects/:project_id/exams`
- `GET /v2/exams`
- `GET /v2/exams/:id`
- `POST /v2/exams`  `[restricted]`
- `PATCH /v2/exams/:id`  `[restricted]`
- `PUT /v2/exams/:id`  `[restricted]`
- `DELETE /v2/exams/:id`  `[restricted]`

### Exams users
- `GET /v2/exams/:exam_id/exams_users`  `[restricted]`
- `POST /v2/exams/:exam_id/exams_users`  `[restricted]`
- `DELETE /v2/exams/:exam_id/exams_users/:id`  `[restricted]`

### Experiences
- `GET /v2/experiences`  `[restricted]`
- `GET /v2/campus/:campus_id/experiences`  `[restricted]`
- `GET /v2/projects_users/:projects_user_id/experiences`  `[restricted]`
- `GET /v2/users/:user_id/experiences`  `[restricted]`
- `GET /v2/skills/:skill_id/experiences`  `[restricted]`
- `GET /v2/partnerships_users/:partnerships_user_id/experiences`  `[restricted]`
- `GET /v2/experiences/:id`  `[restricted]`
- `POST /v2/experiences`  `[restricted]`
- `PATCH /v2/experiences/:id`  `[restricted]`
- `PUT /v2/experiences/:id`  `[restricted]`
- `DELETE /v2/experiences/:id`  `[restricted]`

### Expertises
- `GET /v2/expertises`
- `GET /v2/expertises/:id`
- `POST /v2/expertises`  `[restricted]`
- `PATCH /v2/expertises/:id`  `[restricted]`
- `PUT /v2/expertises/:id`  `[restricted]`
- `DELETE /v2/expertises/:id`  `[restricted]`

### Expertises users
- `GET /v2/expertises/:expertise_id/expertises_users`
- `GET /v2/users/:user_id/expertises_users`
- `GET /v2/expertises_users`
- `GET /v2/expertises_users/:id`
- `POST /v2/expertises/:expertise_id/expertises_users`
- `POST /v2/users/:user_id/expertises_users`
- `POST /v2/expertises_users`
- `PATCH /v2/expertises_users/:id`
- `PUT /v2/expertises_users/:id`
- `DELETE /v2/expertises_users/:id`

### Feedbacks
- `GET /v2/events/:event_id/feedbacks`
- `GET /v2/feedbacks`
- `GET /v2/scale_teams/:scale_team_id/feedbacks`
- `GET /v2/events/:event_id/feedbacks/:id`
- `GET /v2/feedbacks/:id`
- `GET /v2/scale_teams/:scale_team_id/feedbacks/:id`
- `POST /v2/events/:event_id/feedbacks`
- `POST /v2/feedbacks`
- `POST /v2/scale_teams/:scale_team_id/feedbacks`
- `PATCH /v2/events/:event_id/feedbacks/:id`
- `PUT /v2/events/:event_id/feedbacks/:id`
- `PATCH /v2/feedbacks/:id`
- `PUT /v2/feedbacks/:id`
- `PATCH /v2/scale_teams/:scale_team_id/feedbacks/:id`
- `PUT /v2/scale_teams/:scale_team_id/feedbacks/:id`
- `DELETE /v2/events/:event_id/feedbacks/:id`
- `DELETE /v2/feedbacks/:id`
- `DELETE /v2/scale_teams/:scale_team_id/feedbacks/:id`

### Flags
- `GET /v2/flags`

### Flash users
- `GET /v2/flashes/:flash_id/flash_users`  `[restricted]`
- `GET /v2/flash_users`  `[restricted]`
- `GET /v2/flashes/:flash_id/flash_users/:id`  `[restricted]`
- `GET /v2/flash_users/:id`  `[restricted]`
- `POST /v2/flashes/:flash_id/flash_users`  `[restricted]`
- `POST /v2/flash_users`  `[restricted]`

### Flashes
- `GET /v2/flashes`  `[restricted]`
- `GET /v2/flashes/:id`  `[restricted]`
- `POST /v2/flashes`  `[restricted]`

### Gitlab users
- `GET /v2/users/:user_id/gitlab_users`  `[restricted]`

### Groups
- `GET /v2/groups`
- `GET /v2/users/:user_id/groups`
- `GET /v2/groups/:id`
- `POST /v2/groups`  `[restricted]`
- `PATCH /v2/groups/:id`  `[restricted]`
- `PUT /v2/groups/:id`  `[restricted]`
- `DELETE /v2/groups/:id`  `[restricted]`

### Groups users
- `GET /v2/groups_users`
- `GET /v2/groups/:group_id/groups_users`
- `GET /v2/users/:user_id/groups_users`
- `GET /v2/groups_users/:id`
- `POST /v2/groups_users`  `[restricted]`
- `PATCH /v2/groups_users/:id`  `[restricted]`
- `PUT /v2/groups_users/:id`  `[restricted]`
- `DELETE /v2/groups_users/:id`  `[restricted]`

### Internships
- `GET /v2/internships`  `[restricted]`
- `GET /v2/users/:user_id/internships`  `[restricted]`
- `POST /v2/internships`  `[restricted]`
- `PATCH /v2/internships/:id`  `[restricted]`
- `PUT /v2/internships/:id`  `[restricted]`
- `PATCH /v2/users/:user_id/internships/:id`  `[restricted]`
- `PUT /v2/users/:user_id/internships/:id`  `[restricted]`
- `GET /v2/internships/:id`  `[restricted]`
- `GET /v2/users/:user_id/internships/:id`  `[restricted]`
- `DELETE /v2/internships/:id`  `[restricted]`

### Journals
- `GET /v2/campus/:campus_id/journals`  `[restricted]`

### Languages
- `GET /v2/languages/graph(/on/:field(/by/:interval)`
- `GET /v2/languages`
- `GET /v2/languages/:id`
- `POST /v2/languages`  `[restricted]`
- `PATCH /v2/languages/:id`  `[restricted]`
- `PUT /v2/languages/:id`  `[restricted]`
- `DELETE /v2/languages/:id`  `[restricted]`

### Languages users
- `GET /v2/languages_users/graph(/on/:field(/by/:interval)`
- `GET /v2/users/:user_id/languages_users`
- `GET /v2/languages_users`
- `GET /v2/users/:user_id/languages_users/:id`
- `GET /v2/languages_users/:id`
- `POST /v2/users/:user_id/languages_users`  `[restricted]`
- `POST /v2/languages_users`  `[restricted]`
- `PATCH /v2/users/:user_id/languages_users/:id`  `[restricted]`
- `PUT /v2/users/:user_id/languages_users/:id`  `[restricted]`
- `PATCH /v2/languages_users/:id`  `[restricted]`
- `PUT /v2/languages_users/:id`  `[restricted]`
- `DELETE /v2/users/:user_id/languages_users/:id`  `[restricted]`
- `DELETE /v2/languages_users/:id`  `[restricted]`

### Levels
- `GET /v2/levels`  `[restricted]`
- `GET /v2/cursus/:cursus_id/levels`  `[restricted]`

### Locations
- `GET /v2/locations/graph(/on/:field(/by/:interval)`
- `GET /v2/locations`
- `GET /v2/users/:user_id/locations`
- `GET /v2/campus/:campus_id/locations`
- `GET /v2/locations/:id`
- `POST /v2/locations`  `[restricted]`
- `POST /v2/users/:user_id/locations`  `[restricted]`
- `PATCH /v2/locations/:id`  `[restricted]`
- `PUT /v2/locations/:id`  `[restricted]`
- `PATCH /v2/users/:user_id/locations/:id`  `[restricted]`
- `PUT /v2/users/:user_id/locations/:id`  `[restricted]`
- `DELETE /v2/locations/:id`  `[restricted]`
- `DELETE /v2/campus/:campus_id/locations/end_all`  `[restricted]`

### Mailings
- `GET /v2/mailings`  `[restricted]`
- `GET /v2/users/:user_id/mailings`  `[restricted]`
- `GET /v2/mailings/:id`  `[restricted]`
- `POST /v2/mailings`  `[restricted]`
- `PATCH /v2/mailings/:id`  `[restricted]`
- `PUT /v2/mailings/:id`  `[restricted]`
- `DELETE /v2/mailings/:id`  `[restricted]`

### Notes
- `GET /v2/users/:user_id/notes`
- `GET /v2/campus/:campus_id/notes`
- `GET /v2/notes`
- `GET /v2/notes/:id`
- `POST /v2/notes`
- `PATCH /v2/notes/:id`
- `PUT /v2/notes/:id`
- `DELETE /v2/notes/:id`

### Notions
- `GET /v2/cursus/:cursus_id/notions`
- `GET /v2/tags/:tag_id/notions`
- `GET /v2/notions`
- `GET /v2/notions/:id`
- `POST /v2/notions`  `[restricted]`
- `PATCH /v2/notions/:id`  `[restricted]`
- `PUT /v2/notions/:id`  `[restricted]`
- `DELETE /v2/notions/:id`  `[restricted]`

### Offers
- `GET /v2/offers`
- `GET /v2/offers/:id`
- `POST /v2/offers`  `[restricted]`

### Offers users
- `GET /v2/offers/:offer_id/offers_users`  `[restricted]`
- `GET /v2/users/:user_id/offers_users`  `[restricted]`
- `GET /v2/offers_users`  `[restricted]`
- `GET /v2/offers_users/:id`  `[restricted]`

### Params project sessions rules
- `GET /v2/project_sessions_rules/:project_sessions_rule_id/params_project_sessions_rules`  `[restricted]`
- `GET /v2/params_project_sessions_rules`  `[restricted]`
- `GET /v2/params_project_sessions_rules/:id`  `[restricted]`
- `POST /v2/project_sessions_rules/:project_sessions_rule_id/params_project_sessions_rules`  `[restricted]`
- `POST /v2/params_project_sessions_rules`  `[restricted]`
- `PATCH /v2/params_project_sessions_rules/:id`  `[restricted]`
- `PUT /v2/params_project_sessions_rules/:id`  `[restricted]`

### Partnerships
- `GET /v2/partnerships`
- `GET /v2/partnerships/:id`
- `POST /v2/partnerships`  `[restricted]`
- `PATCH /v2/partnerships/:id`  `[restricted]`
- `PUT /v2/partnerships/:id`  `[restricted]`
- `DELETE /v2/partnerships/:id`  `[restricted]`

### Partnerships users
- `GET /v2/partnerships/:partnership_id/partnerships_users`
- `GET /v2/partnerships_users`
- `GET /v2/partnerships_users/:id`
- `POST /v2/partnerships/:partnership_id/partnerships_users`  `[restricted]`
- `POST /v2/partnerships_users`  `[restricted]`
- `PATCH /v2/partnerships_users/:id`  `[restricted]`
- `PUT /v2/partnerships_users/:id`  `[restricted]`
- `DELETE /v2/partnerships_users/:id`  `[restricted]`

### Patronages
- `GET /v2/patronages`  `[restricted]`
- `GET /v2/users/:user_id/patronages`  `[restricted]`
- `GET /v2/patronages/:id`  `[restricted]`
- `POST /v2/patronages`  `[restricted]`
- `POST /v2/users/:user_id/patronages`  `[restricted]`
- `PATCH /v2/patronages/:id`  `[restricted]`
- `PUT /v2/patronages/:id`  `[restricted]`
- `DELETE /v2/patronages/:id`  `[restricted]`

### Patronages reports
- `GET /v2/patronages_reports/graph(/on/:field(/by/:interval)`
- `GET /v2/patronages_reports`  `[restricted]`
- `GET /v2/users/:user_id/patronages_reports`  `[restricted]`
- `GET /v2/patronages/:patronage_id/patronages_reports`  `[restricted]`
- `GET /v2/reports/:report_id/patronages_reports`  `[restricted]`
- `GET /v2/patronages_reports/:id`  `[restricted]`
- `POST /v2/patronages_reports`  `[restricted]`
- `POST /v2/users/:user_id/patronages_reports`  `[restricted]`
- `POST /v2/patronages/:patronage_id/patronages_reports`  `[restricted]`
- `POST /v2/reports/:report_id/patronages_reports`  `[restricted]`
- `PATCH /v2/patronages_reports/:id`  `[restricted]`
- `PUT /v2/patronages_reports/:id`  `[restricted]`
- `DELETE /v2/patronages_reports/:id`  `[restricted]`

### Pools
- `GET /v2/pools`  `[restricted]`
- `GET /v2/pools/:id`  `[restricted]`
- `POST /v2/pools/:id/points/add`  `[restricted]`
- `DELETE /v2/pools/:id/points/remove`  `[restricted]`

### Products
- `GET /v2/products`
- `GET /v2/campus/:campus_id/products`
- `GET /v2/products/:id`
- `GET /v2/campus/:campus_id/products/:id`
- `POST /v2/products`  `[restricted]`
- `POST /v2/campus/:campus_id/products`  `[restricted]`
- `PATCH /v2/products/:id`  `[restricted]`
- `PUT /v2/products/:id`  `[restricted]`
- `PATCH /v2/campus/:campus_id/products/:id`  `[restricted]`
- `PUT /v2/campus/:campus_id/products/:id`  `[restricted]`
- `DELETE /v2/products/:id`  `[restricted]`
- `DELETE /v2/campus/:campus_id/products/:id`  `[restricted]`

### Project data
- `GET /v2/project_data`
- `GET /v2/project_sessions/:project_session_id/project_data`
- `GET /v2/project_data/:id`
- `POST /v2/project_data`  `[restricted]`
- `PATCH /v2/project_data/:id`  `[restricted]`
- `PUT /v2/project_data/:id`  `[restricted]`
- `DELETE /v2/project_data/:id`  `[restricted]`

### Project sessions
- `GET /v2/projects/:project_id/project_sessions/graph(/on/:field(/by/:interval)`
- `GET /v2/project_sessions/graph(/on/:field(/by/:interval)`
- `GET /v2/projects/:project_id/project_sessions`
- `GET /v2/project_sessions`
- `GET /v2/project_sessions/:id`

### Project sessions rules
- `GET /v2/project_sessions/:project_session_id/project_sessions_rules`  `[restricted]`
- `GET /v2/project_sessions_rules`  `[restricted]`
- `GET /v2/project_sessions_rules/:id`  `[restricted]`
- `POST /v2/project_sessions/:project_session_id/project_sessions_rules`  `[restricted]`
- `POST /v2/project_sessions_rules`  `[restricted]`
- `PATCH /v2/project_sessions_rules/:id`  `[restricted]`
- `PUT /v2/project_sessions_rules/:id`  `[restricted]`

### Project sessions skills
- `GET /v2/project_sessions_skills`
- `GET /v2/project_sessions/:project_session_id/project_sessions_skills`
- `GET /v2/skills/:skill_id/project_sessions_skills`
- `GET /v2/project_sessions_skills/:id`
- `GET /v2/project_sessions/:project_session_id/project_sessions_skills/:id`

### Projects
- `GET /v2/cursus/:cursus_id/projects`
- `GET /v2/projects/:project_id/projects`
- `GET /v2/projects`
- `GET /v2/me/projects`
- `GET /v2/projects/:id`
- `POST /v2/projects`  `[restricted]`
- `PATCH /v2/projects/:id`  `[restricted]`
- `PUT /v2/projects/:id`  `[restricted]`
- `DELETE /v2/projects/:id`  `[restricted]`
- `PATCH /v2/projects/:id/retry`
- `PUT /v2/projects/:id/retry`

### Projects users
- `GET /v2/projects/:project_id/projects_users/graph(/on/:field(/by/:interval)`
- `GET /v2/users/:user_id/projects_users/graph(/on/:field(/by/:interval)`
- `GET /v2/projects_users/graph(/on/:field(/by/:interval)`
- `GET /v2/projects/:project_id/projects_users`
- `GET /v2/users/:user_id/projects_users`
- `GET /v2/projects_users`
- `GET /v2/projects_users/:id`
- `POST /v2/projects/:project_id/projects_users`
- `POST /v2/users/:user_id/projects_users`
- `POST /v2/projects_users`
- `POST /v2/projects/:project_id/register`
- `PATCH /v2/projects_users/:id`  `[restricted]`
- `PUT /v2/projects_users/:id`  `[restricted]`
- `DELETE /v2/projects_users/:id`
- `PATCH /v2/projects_users/:id/compile`
- `PUT /v2/projects_users/:id/compile`
- `PATCH /v2/projects_users/:id/retry`
- `PUT /v2/projects_users/:id/retry`
- `POST /v2/projects_users/register_childs_and_scales`
- `DELETE /v2/projects_users/reset`
- `PATCH /v2/projects_users/scale`

### Quests
- `GET /v2/quests`  `[restricted]`
- `GET /v2/cursus/:cursus_id/quests`  `[restricted]`
- `GET /v2/campus/:campus_id/quests`  `[restricted]`
- `GET /v2/users/:user_id/quests`  `[restricted]`
- `GET /v2/quests/:id`  `[restricted]`
- `POST /v2/quests`  `[restricted]`
- `PATCH /v2/quests/:id`  `[restricted]`
- `PUT /v2/quests/:id`  `[restricted]`
- `DELETE /v2/quests/:id`  `[restricted]`

### Quests users
- `GET /v2/quests_users/graph(/on/:field(/by/:interval)`
- `GET /v2/quests/:quest_id/quests_users`
- `GET /v2/users/:user_id/quests_users`
- `GET /v2/quests_users`
- `GET /v2/quests_users/:id`
- `POST /v2/quests_users`  `[restricted]`
- `PATCH /v2/quests_users/:id`  `[restricted]`
- `PUT /v2/quests_users/:id`  `[restricted]`
- `DELETE /v2/quests_users/:id`  `[restricted]`

### Roles
- `GET /v2/roles`
- `GET /v2/users/:user_id/roles`
- `GET /v2/roles/:id`
- `POST /v2/roles`  `[restricted]`
- `PATCH /v2/roles/:id`  `[restricted]`
- `PUT /v2/roles/:id`  `[restricted]`
- `DELETE /v2/roles/:id`  `[restricted]`

### Roles entities
- `GET /v2/roles_entities/graph(/on/:field(/by/:interval)`
- `GET /v2/roles/:role_id/roles_entities`
- `GET /v2/roles_entities`
- `GET /v2/roles_entities/:id`
- `POST /v2/roles_entities`  `[restricted]`
- `PATCH /v2/roles_entities/:id`  `[restricted]`
- `PUT /v2/roles_entities/:id`  `[restricted]`
- `DELETE /v2/roles_entities/:id`  `[restricted]`

### Rules
- `GET /v2/rules`  `[restricted]`
- `GET /v2/project_sessions/:project_session_id/rules`  `[restricted]`
- `GET /v2/rules/:id`  `[restricted]`
- `POST /v2/rules`  `[restricted]`
- `POST /v2/project_sessions/:project_session_id/rules`  `[restricted]`
- `PATCH /v2/rules/:id`  `[restricted]`
- `PUT /v2/rules/:id`  `[restricted]`
- `DELETE /v2/rules/:id`  `[restricted]`

### Scale teams
- `GET /v2/scale_teams/graph(/on/:field(/by/:interval)`
- `GET /v2/projects/:project_id/scale_teams/graph(/on/:field(/by/:interval)`
- `GET /v2/users/:user_id/scale_teams/graph(/on/:field(/by/:interval)`
- `GET /v2/project_sessions/:project_session_id/scale_teams`
- `GET /v2/scale_teams`
- `GET /v2/projects/:project_id/scale_teams`
- `GET /v2/users/:user_id/scale_teams/as_corrector`
- `GET /v2/users/:user_id/scale_teams/as_corrected`
- `GET /v2/users/:user_id/scale_teams`
- `GET /v2/me/scale_teams/as_corrector`
- `GET /v2/me/scale_teams/as_corrected`
- `GET /v2/me/scale_teams`
- `GET /v2/project_sessions/:project_session_id/scale_teams/:id`
- `GET /v2/scale_teams/:id`
- `POST /v2/project_sessions/:project_session_id/scale_teams`
- `POST /v2/scale_teams`
- `PATCH /v2/project_sessions/:project_session_id/scale_teams/:id`
- `PUT /v2/project_sessions/:project_session_id/scale_teams/:id`
- `PATCH /v2/scale_teams/:id`
- `PUT /v2/scale_teams/:id`
- `DELETE /v2/project_sessions/:project_session_id/scale_teams/:id`
- `DELETE /v2/scale_teams/:id`
- `POST /v2/scale_teams/multiple_create`  `[restricted]`

### Scales
- `GET /v2/project_sessions/:project_session_id/scales`  `[restricted]`
- `GET /v2/scales`  `[restricted]`
- `GET /v2/projects/:project_id/scales`  `[restricted]`
- `GET /v2/users/:user_id/scales`  `[restricted]`
- `GET /v2/scales/:id`  `[restricted]`
- `POST /v2/scales`  `[restricted]`
- `PATCH /v2/scales/:id`  `[restricted]`
- `PUT /v2/scales/:id`  `[restricted]`
- `DELETE /v2/scales/:id`  `[restricted]`

### Scores
- `GET /v2/scores`  `[restricted]`
- `GET /v2/coalitions/:coalition_id/scores`  `[restricted]`
- `GET /v2/coalitions_users/:coalitions_user_id/scores`  `[restricted]`
- `GET /v2/blocs/:bloc_id/scores`  `[restricted]`
- `GET /v2/scores/:id`  `[restricted]`
- `GET /v2/coalitions/:coalition_id/scores/:id`  `[restricted]`
- `GET /v2/coalitions_users/:coalitions_user_id/scores/:id`  `[restricted]`
- `GET /v2/blocs/:bloc_id/scores/:id`  `[restricted]`
- `POST /v2/coalitions/:coalition_id/scores`  `[restricted]`
- `DELETE /v2/coalitions/:coalition_id/scores/:id`  `[restricted]`

### Search
- `POST /v2/search/users`  `[restricted]`
- `POST /v2/search/projects`  `[restricted]`

### Skills
- `GET /v2/skills`
- `GET /v2/cursus/:cursus_id/skills`
- `GET /v2/skills`
- `GET /v2/skills/:id`
- `GET /v2/skills/:id`
- `POST /v2/skills`  `[restricted]`
- `POST /v2/skills`  `[restricted]`
- `PATCH /v2/skills/:id`  `[restricted]`
- `PUT /v2/skills/:id`  `[restricted]`
- `PATCH /v2/skills/:id`  `[restricted]`
- `PUT /v2/skills/:id`  `[restricted]`
- `DELETE /v2/skills/:id`  `[restricted]`
- `DELETE /v2/skills/:id`  `[restricted]`

### Slots
- `GET /v2/slots/graph(/on/:field(/by/:interval)`
- `GET /v2/projects/:project_id/slots/graph(/on/:field(/by/:interval)`
- `GET /v2/users/:user_id/slots/graph(/on/:field(/by/:interval)`
- `GET /v2/slots`
- `GET /v2/projects/:project_id/slots`
- `GET /v2/users/:user_id/slots`
- `GET /v2/me/slots`
- `GET /v2/slots/:id`
- `POST /v2/slots`
- `PATCH /v2/slots/:id`
- `PUT /v2/slots/:id`
- `DELETE /v2/slots/:id`

### Squads
- `POST /v2/blocs/:bloc_id/squads`  `[restricted]`
- `DELETE /v2/blocs/:bloc_id/squads/:id`  `[restricted]`
- `DELETE /v2/squads/:id`  `[restricted]`
- `GET /v2/blocs/:bloc_id/squads`  `[restricted]`
- `GET /v2/blocs/:bloc_id/squads/:id`  `[restricted]`
- `GET /v2/squads/:id`  `[restricted]`
- `PATCH /v2/squads/:id`  `[restricted]`
- `PUT /v2/squads/:id`  `[restricted]`

### Squads users
- `POST /v2/blocs/:bloc_id/squads_users`  `[restricted]`
- `DELETE /v2/blocs/:bloc_id/squads_users/:id`  `[restricted]`
- `DELETE /v2/squads_users/:id`  `[restricted]`
- `GET /v2/blocs/:bloc_id/squads_users`  `[restricted]`
- `PATCH /v2/squads_users/:id`  `[restricted]`
- `PUT /v2/squads_users/:id`  `[restricted]`

### Subnotions
- `GET /v2/notions/:notion_id/subnotions`
- `GET /v2/subnotions`
- `GET /v2/subnotions/:id`
- `POST /v2/subnotions`  `[restricted]`
- `PATCH /v2/subnotions/:id`  `[restricted]`
- `PUT /v2/subnotions/:id`  `[restricted]`
- `DELETE /v2/subnotions/:id`  `[restricted]`

### Tags
- `GET /v2/projects/:project_id/tags`
- `GET /v2/issues/:issue_id/tags`
- `GET /v2/notions/:notion_id/tags`
- `GET /v2/cursus/:cursus_id/tags`
- `GET /v2/users/:user_id/tags`
- `GET /v2/tags`
- `GET /v2/tags/:id`
- `POST /v2/tags`  `[restricted]`
- `PATCH /v2/tags/:id`  `[restricted]`
- `PUT /v2/tags/:id`  `[restricted]`
- `DELETE /v2/tags/:id`  `[restricted]`

### Tags users
- `GET /v2/tags_users`
- `GET /v2/users/:user_id/tags_users`
- `GET /v2/cursus/:cursus_id/tags_users`
- `GET /v2/campus/:campus_id/tags_users`
- `GET /v2/tags/:tag_id/tags_users`
- `GET /v2/tags_users/:id`
- `POST /v2/tags_users`  `[restricted]`
- `PATCH /v2/tags_users/:id`  `[restricted]`
- `PUT /v2/tags_users/:id`  `[restricted]`
- `DELETE /v2/tags_users/:id`  `[restricted]`

### Teams
- `GET /v2/cursus/:cursus_id/teams/graph(/on/:field(/by/:interval)`
- `GET /v2/users/:user_id/teams/graph(/on/:field(/by/:interval)`
- `GET /v2/users/:user_id/projects/:project_id/teams/graph(/on/:field(/by/:interval)`
- `GET /v2/teams/graph(/on/:field(/by/:interval)`
- `GET /v2/projects/:project_id/teams/graph(/on/:field(/by/:interval)`
- `GET /v2/cursus/:cursus_id/teams`
- `GET /v2/users/:user_id/teams`
- `GET /v2/users/:user_id/projects/:project_id/teams`
- `GET /v2/teams`
- `GET /v2/projects/:project_id/teams`
- `GET /v2/project_sessions/:project_session_id/teams`
- `GET /v2/me/teams`
- `GET /v2/teams/:id`
- `POST /v2/teams`
- `PATCH /v2/teams/:id`
- `PUT /v2/teams/:id`
- `DELETE /v2/teams/:id`
- `POST /v2/teams/:id/reset_team_uploads`

### Teams uploads
- `GET /v2/teams/:team_id/teams_uploads`
- `GET /v2/teams_uploads`
- `GET /v2/teams_uploads/:id`
- `POST /v2/teams_uploads`  `[restricted]`
- `PATCH /v2/teams_uploads/:id`  `[restricted]`
- `PUT /v2/teams_uploads/:id`  `[restricted]`
- `DELETE /v2/teams_uploads/:id`  `[restricted]`
- `POST /v2/teams_uploads/multiple_create`  `[restricted]`

### Teams users
- `GET /v2/teams_users`
- `GET /v2/users/:user_id/teams_users`
- `GET /v2/teams/:team_id/teams_users`
- `GET /v2/teams_users/:id`
- `POST /v2/teams_users`  `[restricted]`
- `PATCH /v2/teams_users/:id`  `[restricted]`
- `PUT /v2/teams_users/:id`  `[restricted]`
- `DELETE /v2/teams_users/:id`  `[restricted]`

### Titles
- `GET /v2/titles`
- `GET /v2/users/:user_id/titles`
- `GET /v2/titles/:id`
- `POST /v2/titles`  `[restricted]`
- `PATCH /v2/titles/:id`  `[restricted]`
- `PUT /v2/titles/:id`  `[restricted]`
- `DELETE /v2/titles/:id`  `[restricted]`

### Titles users
- `GET /v2/titles/:title_id/titles_users`
- `GET /v2/users/:user_id/titles_users`
- `GET /v2/titles_users`
- `GET /v2/titles_users/:id`
- `POST /v2/titles_users`  `[restricted]`
- `PATCH /v2/titles_users/:id`  `[restricted]`
- `PUT /v2/titles_users/:id`  `[restricted]`
- `DELETE /v2/titles_users/:id`  `[restricted]`

### Transactions
- `GET /v2/transactions`  `[restricted]`
- `GET /v2/users/:user_id/transactions`  `[restricted]`
- `GET /v2/transactions/:id`  `[restricted]`
- `POST /v2/transactions`  `[restricted]`
- `DELETE /v2/transactions/:id`  `[restricted]`

### Translations
- `GET /v2/translations`
- `GET /v2/translations/:id`
- `POST /v2/translations`  `[restricted]`
- `PATCH /v2/translations/:id`  `[restricted]`
- `PUT /v2/translations/:id`  `[restricted]`
- `DELETE /v2/translations/:id`  `[restricted]`
- `POST /v2/translations/upload`  `[restricted]`

### User candidatures
- `GET /v2/user_candidatures`  `[restricted]`
- `GET /v2/users/:user_id/user_candidature`  `[restricted]`
- `GET /v2/user_candidatures/:id`  `[restricted]`
- `POST /v2/users/:user_id/user_candidature`  `[restricted]`
- `POST /v2/user_candidatures`  `[restricted]`
- `PATCH /v2/users/:user_id/user_candidature`  `[restricted]`
- `PUT /v2/users/:user_id/user_candidature`  `[restricted]`
- `PATCH /v2/user_candidatures/:id`  `[restricted]`
- `PUT /v2/user_candidatures/:id`  `[restricted]`

### Users
- `GET /v2/users/graph(/on/:field(/by/:interval)`
- `POST /v2/users/:id/correction_points/add`  `[restricted]`
- `DELETE /v2/users/:id/correction_points/remove`  `[restricted]`
- `GET /v2/users/:id/locations_stats`
- `GET /v2/users/:id/exam`  `[restricted]`
- `GET /v2/coalitions/:coalition_id/users`
- `GET /v2/dashes/:dash_id/users`
- `GET /v2/events/:event_id/users`
- `GET /v2/accreditations/:accreditation_id/users`
- `GET /v2/teams/:team_id/users`
- `GET /v2/projects/:project_id/users`
- `GET /v2/partnerships/:partnership_id/users`
- `GET /v2/expertises/:expertise_id/users`
- `GET /v2/users`
- `GET /v2/cursus/:cursus_id/users`
- `GET /v2/campus/:campus_id/users`
- `GET /v2/achievements/:achievement_id/users`
- `GET /v2/titles/:title_id/users`
- `GET /v2/quests/:quest_id/users`
- `GET /v2/groups/:group_id/users`
- `GET /v2/users/:id`
- `POST /v2/users`  `[restricted]`
- `PATCH /v2/users/:id`  `[restricted]`
- `PUT /v2/users/:id`  `[restricted]`
- `GET /v2/me`
- `POST /v2/users/:id/free_past_agu`  `[restricted]`
- `POST /v2/users/:user_id/unfreeze`  `[restricted]`
- `POST /v2/users/:id/set_primary_campus`  `[restricted]`
- `POST /v2/users/:id/alumnize`  `[restricted]`
- `POST /v2/users/:id/dealumnize`  `[restricted]`
- `DELETE /v2/users/:id/otp_settings/remove`  `[restricted]`
- `GET /v2/staff`  `[restricted]`
- `GET /v2/users/:user_id/projects_users/registration`

### Waitlists
- `GET /v2/waitlists`  `[restricted]`
- `GET /v2/events/:event_id/waitlist`  `[restricted]`
- `GET /v2/exams/:exam_id/waitlist`  `[restricted]`
- `GET /v2/waitlists/:id`  `[restricted]`
- `DELETE /v2/waitlists/:id`  `[restricted]`

### Webhook registeries
- `POST /v2/webhook_registeries/:id/deactivate`  `[restricted]`

## Relevance to 42_cli

42_cli currently **scrapes the intranet with a session cookie** (`endpoints.md`).
The official API below could replace most of it, but needs an OAuth2 app
registration + token lifecycle (client credentials), so it is a larger change.

| 42_cli feature | Cookie-scraped today | Official API v2 equivalent |
|----------------|----------------------|----------------------------|
| Profile / student card | `GET profile /users/<login>` | `GET /v2/me`, `GET /v2/users/:id` |
| Slots (list/create/trim/delete) | `profile /slots.json` CRUD | `GET /v2/me/slots`, `GET /v2/users/:user_id/slots`, `POST /v2/slots`, `PATCH|PUT /v2/slots/:id`, `DELETE /v2/slots/:id` |
| Cluster minimap | `meta /clusters.json` | `GET /v2/clusters`, `GET /v2/clusters/:id` *(restricted)* |
| Projects / subjects | `projects /projects/<slug>` HTML | `GET /v2/projects`, `GET /v2/projects/:id`, `GET /v2/me/projects` |
| Holygraph / cursus | `projects /project_data.json` | `GET /v2/cursus/:cursus_id/projects`, `GET /v2/projects` |
| Feedback (pending) | `projects /users/<login>/feedbacks` HTML | `GET /v2/feedbacks`, `GET /v2/me/scale_teams/as_corrected` |
| Scale teams / evaluations | `projects /projects/<slug>/scale_teams` HTML | `GET /v2/scale_teams`, `GET /v2/me/scale_teams`, `GET /v2/users/:user_id/scale_teams` |
| Coalitions *(new)* | — | `GET /v2/coalitions`, `GET /v2/users/:user_id/coalitions` |
| Locations / presence *(new)* | — | `GET /v2/locations`, `GET /v2/users/:user_id/locations` |
| Campus *(new)* | — | `GET /v2/campus`, `GET /v2/campus/:id` |
