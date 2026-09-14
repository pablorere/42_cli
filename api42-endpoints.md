# 42 API v2 — endpoint reference (scraped)

> Scraped 2026-09-15 from the per-endpoint detail pages via the OpenCLI browser
> bridge: **538 pages / 741 endpoint variants**. Source:
> `https://api.intra.42.fr/apidoc/2.0/<resource>/<action>.html`.
>
> Companion to `api42-apidoc.md` (guides, auth, conventions, resource index).
> `Auth/scope` is transcribed from each page's *Notes*; params from its *Params* table.

## accreditations

### `POST /v2/accreditations`
Create an accreditation
- **Auth/scope:** assignment This action requires one of theses roles: Basic tutor, Basic staff
- **Params:**
  - `accreditation` optional (Hash) — 
  - `accreditation[name]` required (String) — The name.
  - `accreditation[user_id]` required (Fixnum) — The user id.
  - `accreditation[cursus_id]` required (Fixnum) — The cursus id.
  - `accreditation[validated]` optional (enum) — true, false. Is it validated ?
  - `accreditation[difficulty]` required (Fixnum) — The difficulty.
  - `accreditation[accreditations_skills_attributes]` optional (n) — Array of nested elements The accreditations skills attributes.
  - `accreditation[accreditations_skills_attributes][skill_id]` required (Fixnum) — The skill id.
  - `accreditation[accreditations_skills_attributes][value]` required (Float) — The value.
  - `accreditation[accreditations_skills_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/accreditations/:id`
Destroy an accreditation
- **Auth/scope:** assignment This action requires one of theses roles: Basic tutor, Basic staff
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/accreditations`
Return all the accreditations
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, user_id, cursus_id, difficulty, validated, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on accreditations on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, name, user_id, cursus_id, difficulty, validated, created_at, updated_at. Filtering on one or more fields More Example: To filter on accreditations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) user_id (standard field) cursus_id (standard field) difficulty (standard field) validated (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, name, user_id, cursus_id, difficulty, validated, created_at, updated_at. Select on a particular range More Example: To range on accreditations with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id name user_id cursus_id difficulty validated created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/accreditations/:id`
Get an accreditation
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/accreditations/:id`
Update an accreditation
- **Auth/scope:** assignment This action requires one of theses roles: Basic tutor, Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `accreditation` optional (Hash) — 
  - `accreditation[name]` optional (String) — The name.
  - `accreditation[user_id]` optional (Fixnum) — The user id.
  - `accreditation[cursus_id]` optional (Fixnum) — The cursus id.
  - `accreditation[validated]` optional (enum) — true, false. Is it validated ?
  - `accreditation[difficulty]` optional (Fixnum) — The difficulty.
  - `accreditation[accreditations_skills_attributes]` optional (n) — Array of nested elements The accreditations skills attributes.
  - `accreditation[accreditations_skills_attributes][skill_id]` optional (Fixnum) — The skill id.
  - `accreditation[accreditations_skills_attributes][value]` optional (Float) — The value.
  - `accreditation[accreditations_skills_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/accreditations/:id`
Update an accreditation
- **Auth/scope:** assignment This action requires one of theses roles: Basic tutor, Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `accreditation` optional (Hash) — 
  - `accreditation[name]` optional (String) — The name.
  - `accreditation[user_id]` optional (Fixnum) — The user id.
  - `accreditation[cursus_id]` optional (Fixnum) — The cursus id.
  - `accreditation[validated]` optional (enum) — true, false. Is it validated ?
  - `accreditation[difficulty]` optional (Fixnum) — The difficulty.
  - `accreditation[accreditations_skills_attributes]` optional (n) — Array of nested elements The accreditations skills attributes.
  - `accreditation[accreditations_skills_attributes][skill_id]` optional (Fixnum) — The skill id.
  - `accreditation[accreditations_skills_attributes][value]` optional (Float) — The value.
  - `accreditation[accreditations_skills_attributes][_destroy]` optional (String) — The destroy.


## achievements

### `POST /v2/achievements`
Create an achievement
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `achievement` optional (Hash) — 
  - `achievement[name]` required (String) — The name.
  - `achievement[internal_name]` required (String) — The internal name.
  - `achievement[description]` required (String) — The description. Maximum length is 140.
  - `achievement[pedago]` optional (enum) — true, false. Is it pedago ? Default to false.
  - `achievement[visible]` optional (enum) — true, false. Is it visible ? Default to false.
  - `achievement[nbr_of_success]` optional (Fixnum) — The nbr of success.
  - `achievement[parent_id]` optional (Fixnum) — The parent id.
  - `achievement[image_cache]` optional (String) — The image cache.
  - `achievement[image]` optional (File) — The image.
  - `achievement[kind]` required (enum) — project, social, scolarity, pedagogy. The kind.
  - `achievement[title_id]` optional (Fixnum) — The title id.
  - `achievement[tier]` required (enum) — none, easy, medium, hard, challenge. The tier.
  - `achievement[lg]` optional (String) — The language id.
  - `achievement[position]` optional (Fixnum) — The position.
  - `achievement[reward]` optional (String) — The reward.
  - `achievement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `achievement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `achievement[community_services_attributes]` optional (n) — Array of nested elements The community services attributes.
  - `achievement[community_services_attributes][duration]` required (Fixnum) — The duration.
  - `achievement[community_services_attributes][occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `achievement[community_services_attributes][id]` optional (Fixnum) — The id.
  - `achievement[community_services_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/achievements/:id`
Destroy an achievement
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/achievements`
Return all the achievements
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `title_id` optional (String) — The title id or slug
  - `sort` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. The sort field. Sorted by id asc by default. More Example: To sort on achievements on the fields reward on a descending order and title_id on a ascending order: ...&sort=-reward,title_id
  - `filter` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Filtering on one or more fields More Example: To filter on achievements with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) internal_name (standard field) kind (standard field) tier (standard field) description (standard field) pedago (standard field) visible (standard field) nbr_of_success (standard field) parent_id (standard field) image (standard field) created_at (standard field) updated_at (standard field) slug (standard field) position (standard field) reward (standard field) title_id (standard field)
  - `range` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Select on a particular range More Example: To range on achievements with the title_id field between min_value and max_value: ...&range[title_id]=min_value,max_value Rangeable fields: id name internal_name kind tier description pedago visible nbr_of_success parent_id image created_at updated_at slug position reward title_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/achievements`
Return all the achievements of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `title_id` optional (String) — The title id or slug
  - `sort` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. The sort field. Sorted by id asc by default. More Example: To sort on achievements on the fields reward on a descending order and title_id on a ascending order: ...&sort=-reward,title_id
  - `filter` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Filtering on one or more fields More Example: To filter on achievements with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) internal_name (standard field) kind (standard field) tier (standard field) description (standard field) pedago (standard field) visible (standard field) nbr_of_success (standard field) parent_id (standard field) image (standard field) created_at (standard field) updated_at (standard field) slug (standard field) position (standard field) reward (standard field) title_id (standard field)
  - `range` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Select on a particular range More Example: To range on achievements with the title_id field between min_value and max_value: ...&range[title_id]=min_value,max_value Rangeable fields: id name internal_name kind tier description pedago visible nbr_of_success parent_id image created_at updated_at slug position reward title_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/achievements`
Return all the achievements of the given Campus
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `title_id` optional (String) — The title id or slug
  - `sort` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. The sort field. Sorted by id asc by default. More Example: To sort on achievements on the fields reward on a descending order and title_id on a ascending order: ...&sort=-reward,title_id
  - `filter` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Filtering on one or more fields More Example: To filter on achievements with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) internal_name (standard field) kind (standard field) tier (standard field) description (standard field) pedago (standard field) visible (standard field) nbr_of_success (standard field) parent_id (standard field) image (standard field) created_at (standard field) updated_at (standard field) slug (standard field) position (standard field) reward (standard field) title_id (standard field)
  - `range` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Select on a particular range More Example: To range on achievements with the title_id field between min_value and max_value: ...&range[title_id]=min_value,max_value Rangeable fields: id name internal_name kind tier description pedago visible nbr_of_success parent_id image created_at updated_at slug position reward title_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/titles/:title_id/achievements`
Return all the achievements of the given Title
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `title_id` optional (String) — The title id or slug
  - `sort` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. The sort field. Sorted by id asc by default. More Example: To sort on achievements on the fields reward on a descending order and title_id on a ascending order: ...&sort=-reward,title_id
  - `filter` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Filtering on one or more fields More Example: To filter on achievements with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) internal_name (standard field) kind (standard field) tier (standard field) description (standard field) pedago (standard field) visible (standard field) nbr_of_success (standard field) parent_id (standard field) image (standard field) created_at (standard field) updated_at (standard field) slug (standard field) position (standard field) reward (standard field) title_id (standard field)
  - `range` optional (enum) — id, name, internal_name, kind, tier, description, pedago, visible, nbr_of_success, parent_id, image, created_at, updated_at, slug, position, reward, title_id. Select on a particular range More Example: To range on achievements with the title_id field between min_value and max_value: ...&range[title_id]=min_value,max_value Rangeable fields: id name internal_name kind tier description pedago visible nbr_of_success parent_id image created_at updated_at slug position reward title_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/achievements/:id`
Get an achievement
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/achievements/:id`
Update an achievement
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `id` required (String) — The requested id
  - `achievement` optional (Hash) — 
  - `achievement[name]` optional (String) — The name.
  - `achievement[internal_name]` optional (String) — The internal name.
  - `achievement[description]` optional (String) — The description. Maximum length is 140.
  - `achievement[pedago]` optional (enum) — true, false. Is it pedago ? Default to false.
  - `achievement[visible]` optional (enum) — true, false. Is it visible ? Default to false.
  - `achievement[nbr_of_success]` optional (Fixnum) — The nbr of success.
  - `achievement[parent_id]` optional (Fixnum) — The parent id.
  - `achievement[image_cache]` optional (String) — The image cache.
  - `achievement[image]` optional (File) — The image.
  - `achievement[kind]` optional (enum) — project, social, scolarity, pedagogy. The kind.
  - `achievement[title_id]` optional (Fixnum) — The title id.
  - `achievement[tier]` optional (enum) — none, easy, medium, hard, challenge. The tier.
  - `achievement[lg]` optional (String) — The language id.
  - `achievement[position]` optional (Fixnum) — The position.
  - `achievement[reward]` optional (String) — The reward.
  - `achievement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `achievement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `achievement[community_services_attributes]` optional (n) — Array of nested elements The community services attributes.
  - `achievement[community_services_attributes][duration]` optional (Fixnum) — The duration.
  - `achievement[community_services_attributes][occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `achievement[community_services_attributes][id]` optional (Fixnum) — The id.
  - `achievement[community_services_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/achievements/:id`
Update an achievement
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `id` required (String) — The requested id
  - `achievement` optional (Hash) — 
  - `achievement[name]` optional (String) — The name.
  - `achievement[internal_name]` optional (String) — The internal name.
  - `achievement[description]` optional (String) — The description. Maximum length is 140.
  - `achievement[pedago]` optional (enum) — true, false. Is it pedago ? Default to false.
  - `achievement[visible]` optional (enum) — true, false. Is it visible ? Default to false.
  - `achievement[nbr_of_success]` optional (Fixnum) — The nbr of success.
  - `achievement[parent_id]` optional (Fixnum) — The parent id.
  - `achievement[image_cache]` optional (String) — The image cache.
  - `achievement[image]` optional (File) — The image.
  - `achievement[kind]` optional (enum) — project, social, scolarity, pedagogy. The kind.
  - `achievement[title_id]` optional (Fixnum) — The title id.
  - `achievement[tier]` optional (enum) — none, easy, medium, hard, challenge. The tier.
  - `achievement[lg]` optional (String) — The language id.
  - `achievement[position]` optional (Fixnum) — The position.
  - `achievement[reward]` optional (String) — The reward.
  - `achievement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `achievement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `achievement[community_services_attributes]` optional (n) — Array of nested elements The community services attributes.
  - `achievement[community_services_attributes][duration]` optional (Fixnum) — The duration.
  - `achievement[community_services_attributes][occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `achievement[community_services_attributes][id]` optional (Fixnum) — The id.
  - `achievement[community_services_attributes][_destroy]` optional (String) — The destroy.


## achievements_users

### `POST /v2/achievements_users`
Create an achievements user
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `achievements_user` optional (Hash) — 
  - `achievements_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given achievement.
  - `achievements_user[achievement_id]` required (Fixnum) — The achievement id.
  - `achievements_user[nbr_of_success]` optional (Fixnum) — The nbr of success.
  - `achievements_user[rewarded]` optional (enum) — true, false. Is it rewarded ? Default to false.

### `DELETE /v2/achievements_users/:id`
Destroy an achievements user
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/achievements/:achievement_id/achievements_users`
Return all the achievements users of the given Achievement
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `achievement_id` optional (String) — The achievement id or slug
  - `sort` optional (enum) — id, user_id, achievement_id, nbr_of_success, created_at, updated_at, rewarded. The sort field. Sorted by id desc by default. More Example: To sort on achievements users on the fields updated_at on a descending order and rewarded on a ascending order: ...&sort=-updated_at,rewarded
  - `filter` optional (enum) — id, user_id, achievement_id, nbr_of_success, created_at, updated_at, rewarded. Filtering on one or more fields More Example: To filter on achievements users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) achievement_id (standard field) nbr_of_success (standard field) created_at (standard field) updated_at (standard field) rewarded (standard field)
  - `range` optional (enum) — id, user_id, achievement_id, nbr_of_success, created_at, updated_at, rewarded. Select on a particular range More Example: To range on achievements users with the rewarded field between min_value and max_value: ...&range[rewarded]=min_value,max_value Rangeable fields: id user_id achievement_id nbr_of_success created_at updated_at rewarded
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/achievements_users`
Return all the achievements users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `achievement_id` optional (String) — The achievement id or slug
  - `sort` optional (enum) — id, user_id, achievement_id, nbr_of_success, created_at, updated_at, rewarded. The sort field. Sorted by id desc by default. More Example: To sort on achievements users on the fields updated_at on a descending order and rewarded on a ascending order: ...&sort=-updated_at,rewarded
  - `filter` optional (enum) — id, user_id, achievement_id, nbr_of_success, created_at, updated_at, rewarded. Filtering on one or more fields More Example: To filter on achievements users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) achievement_id (standard field) nbr_of_success (standard field) created_at (standard field) updated_at (standard field) rewarded (standard field)
  - `range` optional (enum) — id, user_id, achievement_id, nbr_of_success, created_at, updated_at, rewarded. Select on a particular range More Example: To range on achievements users with the rewarded field between min_value and max_value: ...&range[rewarded]=min_value,max_value Rangeable fields: id user_id achievement_id nbr_of_success created_at updated_at rewarded
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/achievements_users/:id`
Get an achievements user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/achievements_users/:id`
Update an achievements user
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `id` required (String) — The requested id
  - `achievements_user` optional (Hash) — 
  - `achievements_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given achievement.
  - `achievements_user[achievement_id]` optional (Fixnum) — The achievement id.
  - `achievements_user[nbr_of_success]` optional (Fixnum) — The nbr of success.
  - `achievements_user[rewarded]` optional (enum) — true, false. Is it rewarded ? Default to false.

### `PUT /v2/achievements_users/:id`
Update an achievements user
- **Auth/scope:** assignment This action requires one of theses roles: Achievements manager
- **Params:**
  - `id` required (String) — The requested id
  - `achievements_user` optional (Hash) — 
  - `achievements_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given achievement.
  - `achievements_user[achievement_id]` optional (Fixnum) — The achievement id.
  - `achievements_user[nbr_of_success]` optional (Fixnum) — The nbr of success.
  - `achievements_user[rewarded]` optional (enum) — true, false. Is it rewarded ? Default to false.


## alumnized_users

### `GET /v2/alumnized_users`
Get all alumnized users for a given campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `alumnized_since` optional (DateTime) — The date since the user was alumnized
  - `campus_id` required (Integer) — The campus ID


## amendments

### `POST /v2/amendments`
Create an amendment
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `amendment` optional (Hash) — 
  - `amendment[internship_id]` required (Fixnum) — The internship id.
  - `amendment[end_at]` optional (String) — The end at.
  - `amendment[kind]` required (enum) — prolongation, shortening, breach, salary_change, other. The kind.
  - `amendment[origin]` optional (enum) — company, student, school. The origin.
  - `amendment[convention]` optional (File) — The convention.
  - `amendment[salary]` optional (String) — The salary.
  - `amendment[currency]` optional (String) — The currency.
  - `amendment[effective_date]` required (DateTime) — The effective date.

### `DELETE /v2/amendments/:id`
Destroy an amendment
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `amendment` optional (Hash) — 
  - `amendment[internship_id]` optional (Fixnum) — The internship id.
  - `amendment[end_at]` optional (String) — The end at.
  - `amendment[kind]` optional (enum) — prolongation, shortening, breach, salary_change, other. The kind.
  - `amendment[origin]` optional (enum) — company, student, school. The origin.
  - `amendment[convention]` optional (File) — The convention.
  - `amendment[salary]` optional (String) — The salary.
  - `amendment[currency]` optional (String) — The currency.
  - `amendment[effective_date]` optional (DateTime) — The effective date.

### `GET /v2/amendments`
Return all the amendments
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `internship_id` optional (String) — The internship id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `amendment` optional (Hash) — 
  - `amendment[internship_id]` optional (Fixnum) — The internship id.
  - `amendment[end_at]` optional (String) — The end at.
  - `amendment[kind]` optional (enum) — prolongation, shortening, breach, salary_change, other. The kind.
  - `amendment[origin]` optional (enum) — company, student, school. The origin.
  - `amendment[convention]` optional (File) — The convention.
  - `amendment[salary]` optional (String) — The salary.
  - `amendment[currency]` optional (String) — The currency.
  - `amendment[effective_date]` optional (DateTime) — The effective date.

### `GET /v2/users/:user_id/amendments`
Return all the amendments of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `internship_id` optional (String) — The internship id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `amendment` optional (Hash) — 
  - `amendment[internship_id]` optional (Fixnum) — The internship id.
  - `amendment[end_at]` optional (String) — The end at.
  - `amendment[kind]` optional (enum) — prolongation, shortening, breach, salary_change, other. The kind.
  - `amendment[origin]` optional (enum) — company, student, school. The origin.
  - `amendment[convention]` optional (File) — The convention.
  - `amendment[salary]` optional (String) — The salary.
  - `amendment[currency]` optional (String) — The currency.
  - `amendment[effective_date]` optional (DateTime) — The effective date.

### `GET /v2/internships/:internship_id/amendments`
Return all the amendments of the given Internship
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `internship_id` optional (String) — The internship id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `amendment` optional (Hash) — 
  - `amendment[internship_id]` optional (Fixnum) — The internship id.
  - `amendment[end_at]` optional (String) — The end at.
  - `amendment[kind]` optional (enum) — prolongation, shortening, breach, salary_change, other. The kind.
  - `amendment[origin]` optional (enum) — company, student, school. The origin.
  - `amendment[convention]` optional (File) — The convention.
  - `amendment[salary]` optional (String) — The salary.
  - `amendment[currency]` optional (String) — The currency.
  - `amendment[effective_date]` optional (DateTime) — The effective date.

### `GET /v2/amendments/:id`
Get an amendment
- **Params:**
  - `id` required (String) — The requested id
  - `amendment` optional (Hash) — 
  - `amendment[internship_id]` optional (Fixnum) — The internship id.
  - `amendment[end_at]` optional (String) — The end at.
  - `amendment[kind]` optional (enum) — prolongation, shortening, breach, salary_change, other. The kind.
  - `amendment[origin]` optional (enum) — company, student, school. The origin.
  - `amendment[convention]` optional (File) — The convention.
  - `amendment[salary]` optional (String) — The salary.
  - `amendment[currency]` optional (String) — The currency.
  - `amendment[effective_date]` optional (DateTime) — The effective date.


## announcements

### `POST /v2/announcements`
Create an announcement
- **Auth/scope:** assignment This action requires one of theses roles: Community manager
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `announcement` optional (Hash) — 
  - `announcement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `announcement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `announcement[author]` required (String) — The author.
  - `announcement[title]` required (String) — The title.
  - `announcement[text]` required (String) — The text.
  - `announcement[kind]` optional (String) — The kind.
  - `announcement[expire_at]` required (Fixnum) — The expire at. .
  - `announcement[image]` optional (String) — The image.

### `POST /v2/cursus/:cursus_id/announcements`
Create an announcement for the given Cursus
- **Auth/scope:** assignment This action requires one of theses roles: Community manager
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `announcement` optional (Hash) — 
  - `announcement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `announcement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `announcement[author]` required (String) — The author.
  - `announcement[title]` required (String) — The title.
  - `announcement[text]` required (String) — The text.
  - `announcement[kind]` optional (String) — The kind.
  - `announcement[expire_at]` required (Fixnum) — The expire at. .
  - `announcement[image]` optional (String) — The image.

### `DELETE /v2/announcements/:id`
Destroy an announcement
- **Auth/scope:** assignment This action requires one of theses roles: Community manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/announcements/graph(/on/:field(/by/:interval))`
Return grouped temporal data on announcements
- **Params:**
  - `field` optional (enum) — created_at, updated_at, expire_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, author, title, text, kind, created_at, updated_at, image, expire_at, link, notificable_id, notificable_type. The sort field. Sorted by expire_at desc, id desc by default. More Example: To sort on announcements on the fields notificable_id on a descending order and notificable_type on a ascending order: ...&sort=-notificable_id,notificable_type
  - `filter` optional (enum) — id, author, title, text, kind, created_at, updated_at, image, expire_at, link, notificable_id, notificable_type, expire. Filtering on one or more fields More Example: To filter on announcements with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) author (standard field) title (standard field) text (standard field) kind (standard field) created_at (standard field) updated_at (standard field) image (standard field) expire_at (standard field) link (standard field) notificable_id (standard field) notificable_type (standard field) expire (standard field)
  - `range` optional (enum) — id, author, title, text, kind, created_at, updated_at, image, expire_at, link, notificable_id, notificable_type. Select on a particular range More Example: To range on announcements with the notificable_type field between min_value and max_value: ...&range[notificable_type]=min_value,max_value Rangeable fields: id author title text kind created_at updated_at image expire_at link notificable_id notificable_type

### `GET /v2/announcements/:id`
Get an announcement
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/announcements/:id`
Update an announcement
- **Auth/scope:** assignment This action requires one of theses roles: Community manager
- **Params:**
  - `id` required (String) — The requested id
  - `announcement` optional (Hash) — 
  - `announcement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `announcement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `announcement[author]` optional (String) — The author.
  - `announcement[title]` optional (String) — The title.
  - `announcement[text]` optional (String) — The text.
  - `announcement[kind]` optional (String) — The kind.
  - `announcement[expire_at]` optional (Fixnum) — The expire at. .
  - `announcement[image]` optional (String) — The image.

### `PUT /v2/announcements/:id`
Update an announcement
- **Auth/scope:** assignment This action requires one of theses roles: Community manager
- **Params:**
  - `id` required (String) — The requested id
  - `announcement` optional (Hash) — 
  - `announcement[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `announcement[campus_ids]` optional (n) — array of Integer The campus ids.
  - `announcement[author]` optional (String) — The author.
  - `announcement[title]` optional (String) — The title.
  - `announcement[text]` optional (String) — The text.
  - `announcement[kind]` optional (String) — The kind.
  - `announcement[expire_at]` optional (Fixnum) — The expire at. .
  - `announcement[image]` optional (String) — The image.


## anti_grav_units

### `GET /v2/anti_grav_units`
Return all the anti grav units
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff

### `GET /v2/anti_grav_units/:id`
Get an anti grav unit
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id


## anti_grav_units_users

### `POST /v2/anti_grav_units_users`
Create an anti grav units user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `anti_grav_units_user` optional (Hash) — 
  - `anti_grav_units_user[user_id]` required (Integer) — Freezed user id
  - `anti_grav_units_user[anti_grav_unit_id]` optional (Integer) — Must refer to the AntiGravUnit related.
  - `anti_grav_units_user[begin_date]` optional (Date) — The date when the agu started, defaulted to Today
  - `anti_grav_units_user[expected_end_date]` required (Date) — The date when the agu will be automatically stopped
  - `anti_grav_units_user[reason]` optional (String) — The reason of this freeze
  - `anti_grav_units_user[is_free]` optional (String) — If true, the agu will not consume one of 3 user agu, can be overlapped with other agus

### `GET /v2/anti_grav_units_users`
Return all the anti grav units users
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id. The sort field. Sorted by id desc by default. More Example: To sort on anti grav units users on the fields anti_grav_unit_id on a descending order and internship_id on a ascending order: ...&sort=-anti_grav_unit_id,internship_id
  - `filter` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id, cursus_id, active. Filtering on one or more fields More Example: To filter on anti grav units users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) close_id (standard field) is_free (standard field) reason (standard field) end_date (standard field) expected_end_date (standard field) begin_date (standard field) anti_grav_unit_id (standard field) internship_id (standard field) cursus_id : Only return agu users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active : .
  - `range` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id. Select on a particular range More Example: To range on anti grav units users with the internship_id field between min_value and max_value: ...&range[internship_id]=min_value,max_value Rangeable fields: id user_id created_at updated_at close_id is_free reason end_date expected_end_date begin_date anti_grav_unit_id internship_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/anti_grav_units_users`
Return all the anti grav units users of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id. The sort field. Sorted by id desc by default. More Example: To sort on anti grav units users on the fields anti_grav_unit_id on a descending order and internship_id on a ascending order: ...&sort=-anti_grav_unit_id,internship_id
  - `filter` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id, cursus_id, active. Filtering on one or more fields More Example: To filter on anti grav units users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) close_id (standard field) is_free (standard field) reason (standard field) end_date (standard field) expected_end_date (standard field) begin_date (standard field) anti_grav_unit_id (standard field) internship_id (standard field) cursus_id : Only return agu users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active : .
  - `range` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id. Select on a particular range More Example: To range on anti grav units users with the internship_id field between min_value and max_value: ...&range[internship_id]=min_value,max_value Rangeable fields: id user_id created_at updated_at close_id is_free reason end_date expected_end_date begin_date anti_grav_unit_id internship_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/anti_grav_units_users`
Return all the anti grav units users of the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id. The sort field. Sorted by id desc by default. More Example: To sort on anti grav units users on the fields anti_grav_unit_id on a descending order and internship_id on a ascending order: ...&sort=-anti_grav_unit_id,internship_id
  - `filter` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id, cursus_id, active. Filtering on one or more fields More Example: To filter on anti grav units users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) close_id (standard field) is_free (standard field) reason (standard field) end_date (standard field) expected_end_date (standard field) begin_date (standard field) anti_grav_unit_id (standard field) internship_id (standard field) cursus_id : Only return agu users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active : .
  - `range` optional (enum) — id, user_id, created_at, updated_at, close_id, is_free, reason, end_date, expected_end_date, begin_date, anti_grav_unit_id, internship_id. Select on a particular range More Example: To range on anti grav units users with the internship_id field between min_value and max_value: ...&range[internship_id]=min_value,max_value Rangeable fields: id user_id created_at updated_at close_id is_free reason end_date expected_end_date begin_date anti_grav_unit_id internship_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/anti_grav_units_users/:id`
Get an anti grav units user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/anti_grav_units_users/:id`
Update an anti grav units user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `anti_grav_units_user` optional (Hash) — 
  - `anti_grav_units_user[user_id]` optional (Integer) — Freezed user id
  - `anti_grav_units_user[anti_grav_unit_id]` optional (Integer) — Must refer to the AntiGravUnit related.
  - `anti_grav_units_user[begin_date]` optional (Date) — The date when the agu started, defaulted to Today
  - `anti_grav_units_user[expected_end_date]` optional (Date) — The date when the agu will be automatically stopped
  - `anti_grav_units_user[reason]` optional (String) — The reason of this freeze
  - `anti_grav_units_user[is_free]` optional (String) — If true, the agu will not consume one of 3 user agu, can be overlapped with other agus

### `PUT /v2/anti_grav_units_users/:id`
Update an anti grav units user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `anti_grav_units_user` optional (Hash) — 
  - `anti_grav_units_user[user_id]` optional (Integer) — Freezed user id
  - `anti_grav_units_user[anti_grav_unit_id]` optional (Integer) — Must refer to the AntiGravUnit related.
  - `anti_grav_units_user[begin_date]` optional (Date) — The date when the agu started, defaulted to Today
  - `anti_grav_units_user[expected_end_date]` optional (Date) — The date when the agu will be automatically stopped
  - `anti_grav_units_user[reason]` optional (String) — The reason of this freeze
  - `anti_grav_units_user[is_free]` optional (String) — If true, the agu will not consume one of 3 user agu, can be overlapped with other agus


## apps

### `GET /v2/apps`
Get all the public and owned applications
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner .
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, token, user_id, created_at, updated_at, allowed_origins. The sort field. Sorted by id desc by default. More Example: To sort on apps on the fields updated_at on a descending order and allowed_origins on a ascending order: ...&sort=-updated_at,allowed_origins
  - `filter` optional (enum) — id, name, uid, owner_id, website. Filtering on one or more fields More Example: To filter on apps with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) uid (standard field) owner_id (standard field) website (standard field)
  - `range` optional (enum) — id, name, uid, owner_id, website. Select on a particular range More Example: To range on apps with the website field between min_value and max_value: ...&range[website]=min_value,max_value Rangeable fields: id name uid owner_id website
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/apps`
Get all the public and owned applications
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner .
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, token, user_id, created_at, updated_at, allowed_origins. The sort field. Sorted by id desc by default. More Example: To sort on apps on the fields updated_at on a descending order and allowed_origins on a ascending order: ...&sort=-updated_at,allowed_origins
  - `filter` optional (enum) — id, name, uid, owner_id, website. Filtering on one or more fields More Example: To filter on apps with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) uid (standard field) owner_id (standard field) website (standard field)
  - `range` optional (enum) — id, name, uid, owner_id, website. Select on a particular range More Example: To range on apps with the website field between min_value and max_value: ...&range[website]=min_value,max_value Rangeable fields: id name uid owner_id website
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/apps/:id`
Get a public or owned application
- **Params:**
  - `id` required (String) — The requested id


## attachments

### `POST /v2/projects/:project_id/attachments`
Create an attachment for the given Project
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `project_id` required (String) — The project id or slug
  - `attachment` optional (Hash) — 
  - `attachment[kind]` required (enum) — code, pdf, link, document, video. The kind of the attachment
  - `attachment[language_id]` optional (Fixnum) — The attachment language
  - `attachment[untranslatable]` optional (enum) — true, false. Is this attachment untranslatable
  - `attachment[attachable_attributes]` required (n) — Array of nested elements The attachment file
  - `attachment[attachable_attributes][name]` required (String) — The name of the attachment
  - `attachment[attachable_attributes][attachable_type]` required (enum) — code, pdf, link, document, video. The type of the attachment, need the file linked with the same param (see below)
  - `attachment[attachable_attributes][pdf]` optional (File) — The attached pdf file
  - `attachment[attachable_attributes][video]` optional (File) — The attached video file

### `DELETE /v2/attachments/:id`
Destroy an attachment
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/project_sessions/:project_session_id/attachments`
Return all the attachments of the given Project session
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. The sort field. Sorted by id asc by default. More Example: To sort on attachments on the fields untranslatable on a descending order and attachments_structure_id on a ascending order: ...&sort=-untranslatable,attachments_structure_id
  - `filter` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. Filtering on one or more fields More Example: To filter on attachments with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) attachable_id (standard field) attachable_type (standard field) kind (standard field) created_at (standard field) updated_at (standard field) language_id (standard field) user_id (standard field) default (standard field) up_to_date (standard field) container_id (standard field) container_type (standard field) base_id (standard field) untranslatable (standard field) attachments_structure_id (standard field)
  - `range` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. Select on a particular range More Example: To range on attachments with the attachments_structure_id field between min_value and max_value: ...&range[attachments_structure_id]=min_value,max_value Rangeable fields: id attachable_id attachable_type kind created_at updated_at language_id user_id default up_to_date container_id container_type base_id untranslatable attachments_structure_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/attachments`
Return all the attachments of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. The sort field. Sorted by id asc by default. More Example: To sort on attachments on the fields untranslatable on a descending order and attachments_structure_id on a ascending order: ...&sort=-untranslatable,attachments_structure_id
  - `filter` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. Filtering on one or more fields More Example: To filter on attachments with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) attachable_id (standard field) attachable_type (standard field) kind (standard field) created_at (standard field) updated_at (standard field) language_id (standard field) user_id (standard field) default (standard field) up_to_date (standard field) container_id (standard field) container_type (standard field) base_id (standard field) untranslatable (standard field) attachments_structure_id (standard field)
  - `range` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. Select on a particular range More Example: To range on attachments with the attachments_structure_id field between min_value and max_value: ...&range[attachments_structure_id]=min_value,max_value Rangeable fields: id attachable_id attachable_type kind created_at updated_at language_id user_id default up_to_date container_id container_type base_id untranslatable attachments_structure_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/attachments`
Return all the attachments
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. The sort field. Sorted by id asc by default. More Example: To sort on attachments on the fields untranslatable on a descending order and attachments_structure_id on a ascending order: ...&sort=-untranslatable,attachments_structure_id
  - `filter` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. Filtering on one or more fields More Example: To filter on attachments with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) attachable_id (standard field) attachable_type (standard field) kind (standard field) created_at (standard field) updated_at (standard field) language_id (standard field) user_id (standard field) default (standard field) up_to_date (standard field) container_id (standard field) container_type (standard field) base_id (standard field) untranslatable (standard field) attachments_structure_id (standard field)
  - `range` optional (enum) — id, attachable_id, attachable_type, kind, created_at, updated_at, language_id, user_id, default, up_to_date, container_id, container_type, base_id, untranslatable, attachments_structure_id. Select on a particular range More Example: To range on attachments with the attachments_structure_id field between min_value and max_value: ...&range[attachments_structure_id]=min_value,max_value Rangeable fields: id attachable_id attachable_type kind created_at updated_at language_id user_id default up_to_date container_id container_type base_id untranslatable attachments_structure_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions/:project_session_id/attachments/:id`
Get an attachment of the given Id, associated with the given Project session
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id

### `GET /v2/attachments/:id`
Get an attachment
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id

### `PATCH /v2/attachments/:id`
Update an attachment
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `attachment` optional (Hash) — 
  - `attachment[kind]` optional (enum) — code, pdf, link, document, video. The kind of the attachment
  - `attachment[language_id]` optional (Fixnum) — The attachment language
  - `attachment[untranslatable]` optional (enum) — true, false. Is this attachment untranslatable
  - `attachment[attachable_attributes]` optional (n) — Array of nested elements The attachment file
  - `attachment[attachable_attributes][name]` optional (String) — The name of the attachment
  - `attachment[attachable_attributes][attachable_type]` optional (enum) — code, pdf, link, document, video. The type of the attachment, need the file linked with the same param (see below)
  - `attachment[attachable_attributes][pdf]` optional (File) — The attached pdf file
  - `attachment[attachable_attributes][video]` optional (File) — The attached video file

### `PUT /v2/attachments/:id`
Update an attachment
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `attachment` optional (Hash) — 
  - `attachment[kind]` optional (enum) — code, pdf, link, document, video. The kind of the attachment
  - `attachment[language_id]` optional (Fixnum) — The attachment language
  - `attachment[untranslatable]` optional (enum) — true, false. Is this attachment untranslatable
  - `attachment[attachable_attributes]` optional (n) — Array of nested elements The attachment file
  - `attachment[attachable_attributes][name]` optional (String) — The name of the attachment
  - `attachment[attachable_attributes][attachable_type]` optional (enum) — code, pdf, link, document, video. The type of the attachment, need the file linked with the same param (see below)
  - `attachment[attachable_attributes][pdf]` optional (File) — The attached pdf file
  - `attachment[attachable_attributes][video]` optional (File) — The attached video file


## balances

### `GET /v2/balances`
Return all the balances
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `pool_id` optional (String) — The pool id
  - `sort` optional (enum) — id, begin_at, end_at, created_at, updated_at, pool_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on balances on the fields updated_at on a descending order and pool_id on a ascending order: ...&sort=-updated_at,pool_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, updated_at, pool_id, future, end. Filtering on one or more fields More Example: To filter on balances with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) updated_at (standard field) pool_id (standard field) future : Return only balances which begins in the future. Can be one of: true, false end (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `GET /v2/pools/:pool_id/balances`
Return all the balances of the given Pool
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `pool_id` optional (String) — The pool id
  - `sort` optional (enum) — id, begin_at, end_at, created_at, updated_at, pool_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on balances on the fields updated_at on a descending order and pool_id on a ascending order: ...&sort=-updated_at,pool_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, updated_at, pool_id, future, end. Filtering on one or more fields More Example: To filter on balances with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) updated_at (standard field) pool_id (standard field) future : Return only balances which begins in the future. Can be one of: true, false end (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `GET /v2/balances/:id`
Get a balance
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `pool_id` optional (String) — The pool id
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `GET /v2/pools/:pool_id/balances/:id`
Get a balance of the given Id, associated with the given Pool
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `pool_id` optional (String) — The pool id
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `PATCH /v2/balances/:id`
Update a balance
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `pool_id` optional (String) — The pool id
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `PUT /v2/balances/:id`
Update a balance
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `pool_id` optional (String) — The pool id
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `PATCH /v2/pools/:pool_id/balances/:id`
Update a balance for the given Id, associated with the given Pool
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `pool_id` optional (String) — The pool id
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.

### `PUT /v2/pools/:pool_id/balances/:id`
Update a balance for the given Id, associated with the given Pool
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `pool_id` optional (String) — The pool id
  - `balance` optional (Hash) — 
  - `balance[begin_at]` optional (Fixnum) — The begin at. Must be before end at. .
  - `balance[end_at]` optional (Fixnum) — The end at. .
  - `balance[pool_id]` optional (Fixnum) — The pool id.


## bloc_deadlines

### `POST /v2/bloc_deadlines`
Create a bloc deadline
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_deadline` optional (Hash) — 
  - `bloc_deadline[bloc_id]` required (Fixnum) — The bloc id.
  - `bloc_deadline[begin_at]` required (DateTime) — The begin at.
  - `bloc_deadline[end_at]` required (DateTime) — The end at.
  - `bloc_deadline[coalition_id]` optional (Fixnum) — The coalition id.

### `GET /v2/bloc_deadlines`
Return all the bloc deadlines
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, bloc_id, begin_at, end_at, created_at, updated_at, coalition_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on bloc deadlines on the fields updated_at on a descending order and coalition_id on a ascending order: ...&sort=-updated_at,coalition_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/blocs/:bloc_id/bloc_deadlines`
Return all the bloc deadlines of the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, bloc_id, begin_at, end_at, created_at, updated_at, coalition_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on bloc deadlines on the fields updated_at on a descending order and coalition_id on a ascending order: ...&sort=-updated_at,coalition_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/bloc_deadlines/:id`
Get a bloc deadline
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/bloc_deadlines/:id`
Update a bloc deadline
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `bloc_deadline` optional (Hash) — 
  - `bloc_deadline[bloc_id]` optional (Fixnum) — The bloc id.
  - `bloc_deadline[begin_at]` optional (DateTime) — The begin at.
  - `bloc_deadline[end_at]` optional (DateTime) — The end at.
  - `bloc_deadline[coalition_id]` optional (Fixnum) — The coalition id.

### `PUT /v2/bloc_deadlines/:id`
Update a bloc deadline
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `bloc_deadline` optional (Hash) — 
  - `bloc_deadline[bloc_id]` optional (Fixnum) — The bloc id.
  - `bloc_deadline[begin_at]` optional (DateTime) — The begin at.
  - `bloc_deadline[end_at]` optional (DateTime) — The end at.
  - `bloc_deadline[coalition_id]` optional (Fixnum) — The coalition id.


## blocs

### `GET /v2/blocs`
Return all the blocs
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, cursus_id, campus_id, squad_size, created_at, updated_at, coalition_delay, repeat_deadline_delay. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on blocs on the fields coalition_delay on a descending order and repeat_deadline_delay on a ascending order: ...&sort=-coalition_delay,repeat_deadline_delay
  - `filter` optional (enum) — id, cursus_id, campus_id, squad_size, created_at, updated_at, coalition_delay, repeat_deadline_delay. Filtering on one or more fields More Example: To filter on blocs with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) cursus_id (standard field) campus_id (standard field) squad_size (standard field) created_at (standard field) updated_at (standard field) coalition_delay (standard field) repeat_deadline_delay (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/blocs/:id`
Get a bloc
- **Params:**
  - `id` required (String) — The requested id


## broadcasts

### `GET /v2/campus/:campus_id/broadcasts`
Return all the broadcasts of the given Campus
- **Auth/scope:** This resource is paginated by 30 items This action requires a token resource owner .
- **Params:**
  - `campus_id` required (String) — The campus id or slug
  - `sort` optional (enum) — id, campus_id, tag_id, content, pinned_until, hidden_at, url, created_at, updated_at, content_html, position. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on broadcasts on the fields content_html on a descending order and position on a ascending order: ...&sort=-content_html,position
  - `filter` optional (enum) — id, campus_id, tag_id, content, pinned_until, hidden_at, url, created_at, updated_at, content_html, position, hidden. Filtering on one or more fields More Example: To filter on broadcasts with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) campus_id (standard field) tag_id (standard field) content (standard field) pinned_until (standard field) hidden_at (standard field) url (standard field) created_at (standard field) updated_at (standard field) content_html (standard field) position (standard field) hidden (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## campus

### `POST /v2/campus`
Create a campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `campus` optional (Hash) — 
  - `campus[name]` required (String) — The name. Must be unique.
  - `campus[time_zone]` required (enum) — Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Honolulu, America/Juneau, America/Los_Angeles, America/Tijuana, America/Phoenix, America/Chihuahua, America/Mazatlan, America/Denver, America/Guatemala, America/Chicago, America/Mexico_City, America/Mexico_City, America/Monterrey, America/Regina, America/Bogota, America/New_York, America/Indiana/Indianapolis, America/Lima, America/Lima, America/Halifax, America/Caracas, America/Guyana, America/La_Paz, America/Santiago, America/St_Johns, America/Sao_Paulo, America/Argentina/Buenos_Aires, America/Godthab, America/Montevideo, Atlantic/South_Georgia, Atlantic/Azores, Atlantic/Cape_Verde, Europe/London, Europe/Lisbon, Europe/London, Africa/Monrovia, Etc/UTC, Europe/Amsterdam, Europe/Belgrade, Europe/Berlin, Europe/Zurich, Europe/Prague, Europe/Brussels, Europe/Budapest, Africa/Casablanca, Europe/Copenhagen, Europe/Dublin, Europe/Belgrade, Europe/Madrid, Europe/Paris, Europe/Prague, Europe/Rome, Europe/Belgrade, Europe/Belgrade, Europe/Stockholm, Europe/Vienna, Europe/Warsaw, Africa/Algiers, Europe/Belgrade, Europe/Zurich, Europe/Athens, Europe/Bucharest, Africa/Cairo, Africa/Maputo, Europe/Helsinki, Asia/Jerusalem, Europe/Kaliningrad, Europe/Kiev, Africa/Johannesburg, Europe/Riga, Europe/Sofia, Europe/Tallinn, Europe/Vilnius, Asia/Baghdad, Europe/Istanbul, Asia/Riyadh, Europe/Minsk, Europe/Moscow, Africa/Nairobi, Asia/Riyadh, Europe/Moscow, Asia/Tehran, Asia/Dubai, Asia/Baku, Asia/Dubai, Europe/Samara, Asia/Tbilisi, Europe/Volgograd, Asia/Yerevan, Asia/Kabul, Asia/Yekaterinburg, Asia/Karachi, Asia/Karachi, Asia/Tashkent, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Colombo, Asia/Kathmandu, Asia/Almaty, Asia/Dhaka, Asia/Dhaka, Asia/Urumqi, Asia/Yangon, Asia/Bangkok, Asia/Bangkok, Asia/Jakarta, Asia/Krasnoyarsk, Asia/Novosibirsk, Asia/Shanghai, Asia/Shanghai, Asia/Hong_Kong, Asia/Irkutsk, Asia/Kuala_Lumpur, Australia/Perth, Asia/Singapore, Asia/Taipei, Asia/Ulaanbaatar, Asia/Tokyo, Asia/Tokyo, Asia/Seoul, Asia/Tokyo, Asia/Yakutsk, Australia/Adelaide, Australia/Darwin, Australia/Brisbane, Australia/Melbourne, Pacific/Guam, Australia/Hobart, Australia/Melbourne, Pacific/Port_Moresby, Australia/Sydney, Asia/Vladivostok, Asia/Magadan, Pacific/Noumea, Pacific/Guadalcanal, Asia/Srednekolymsk, Pacific/Auckland, Pacific/Fiji, Asia/Kamchatka, Pacific/Majuro, Pacific/Auckland, Pacific/Chatham, Pacific/Tongatapu, Pacific/Apia, Pacific/Fakaofo. The time zone.
  - `campus[language_id]` required (Fixnum) — The language id.
  - `campus[main_email]` optional (String) — The main email.
  - `campus[endpoint_id]` optional (Fixnum) — The endpoint id.
  - `campus[vogsphere_id]` optional (Fixnum) — The vogsphere id.
  - `campus[content_email]` required (String) — The content email. Default to greetings first name and welcome at 42, in this email you'll find information that will allow you to log on the computers at school and start smoothly. please don't lose this email and don't delete it else you'll not be able to start working as fast as other students at the beginning of the piscine. here are your login and your password to connect at 42 : login : login password : password as stipulated in the charter you agreed on when registering for the piscine, you are responsible for this login and the use that will be done of it. best regards, 42 campus .
  - `campus[tig_email]` required (String) — The tig email. Default to hi, your account has been closed for the following reason: “ reason ”. to unclose your account, you must choose a date for your community services hererl schedule ). your community services will last ** duration hours. warning: do not set your community services on national holiday, otherwise your community services duration will be doubled. meet the bocal at start at . if you are late or missing, your community services duration will be doubled. .
  - `campus[time_of_community_service_started]` required (String) — The time of community service started.
  - `campus[companies_mail]` optional (String) — The companies mail.
  - `campus[address]` required (String) — The address.
  - `campus[zip]` required (String) — The zip.
  - `campus[city]` required (String) — The city.
  - `campus[country]` required (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `campus[pro_needs_validation]` optional (enum) — true, false. Is it pro needs validation ? Default to false.
  - `campus[open_to_job_offers]` optional (enum) — true, false. Is it open to job offers ?
  - `campus[logo]` optional (File) — The logo.
  - `campus[website]` required (String) — The website.
  - `campus[facebook]` optional (String) — The facebook.
  - `campus[twitter]` optional (String) — The twitter.
  - `campus[display_name]` required (String) — The display name.
  - `campus[email_extension]` optional (String) — The email extension.
  - `campus[help_url]` optional (String) — The help url.
  - `campus[logo_cache]` optional (String) — The logo cache.
  - `campus[default_hidden_phone]` optional (enum) — true, false. Is it default hidden phone ? Default to false.
  - `campus[minimum_slot_duration]` optional (Fixnum) — The minimum slot duration. Default to 30.
  - `campus[manual_alumnization_before_first_internship]` optional (enum) — true, false. Is it manual alumnization before first internship ? Default to true.
  - `campus[public]` optional (enum) — true, false. Is it public ? Default to false.

### `GET /v2/campus`
Return all the campus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, created_at, updated_at, time_zone, language_id, slug, main_email, endpoint_id, vogsphere_id, content_email, time_of_community_service_started, companies_mail, address, zip, city, country, pro_needs_validation, logo, website, facebook, twitter, display_name, email_extension, help_url, active, open_to_job_offers, default_hidden_phone, tig_email, minimum_slot_duration, alumni_system, manual_alumnization_before_first_internship, public. The sort field. Sorted by id desc by default. More Example: To sort on campus on the fields manual_alumnization_before_first_internship on a descending order and public on a ascending order: ...&sort=-manual_alumnization_before_first_internship,public
  - `filter` optional (enum) — id, name, created_at, updated_at, time_zone, language_id, slug, main_email, endpoint_id, vogsphere_id, content_email, time_of_community_service_started, companies_mail, address, zip, city, country, pro_needs_validation, logo, website, facebook, twitter, display_name, email_extension, help_url, active, open_to_job_offers, default_hidden_phone, tig_email, minimum_slot_duration, alumni_system, manual_alumnization_before_first_internship, public. Filtering on one or more fields More Example: To filter on campus with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) time_zone (standard field) language_id (standard field) slug (standard field) main_email (standard field) endpoint_id (standard field) vogsphere_id (standard field) content_email (standard field) time_of_community_service_started (standard field) companies_mail (standard field) address (standard field) zip (standard field) city (standard field) country (standard field) pro_needs_validation (standard field) logo (standard field) website (standard field) facebook (standard field) twitter (standard field) display_name (standard field) email_extension (standard field) help_url (standard field) active (standard field) open_to_job_offers (standard field) default_hidden_phone (standard field) tig_email (standard field) minimum_slot_duration (standard field) alumni_system (standard field) manual_alumnization_before_first_internship (standard field) public (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, time_zone, language_id, slug, main_email, endpoint_id, vogsphere_id, content_email, time_of_community_service_started, companies_mail, address, zip, city, country, pro_needs_validation, logo, website, facebook, twitter, display_name, email_extension, help_url, active, open_to_job_offers, default_hidden_phone, tig_email, minimum_slot_duration, alumni_system, manual_alumnization_before_first_internship, public. Select on a particular range More Example: To range on campus with the public field between min_value and max_value: ...&range[public]=min_value,max_value Rangeable fields: id name created_at updated_at time_zone language_id slug main_email endpoint_id vogsphere_id content_email time_of_community_service_started companies_mail address zip city country pro_needs_validation logo website facebook twitter display_name email_extension help_url active open_to_job_offers default_hidden_phone tig_email minimum_slot_duration alumni_system manual_alumnization_before_first_internship public
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:id`
Get a campus
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/campus/:campus_id/stats`
for the given Campus
- **Params:**
  - `campus` optional (Hash) — 
  - `campus[name]` optional (String) — The name. Must be unique.
  - `campus[time_zone]` optional (enum) — Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Honolulu, America/Juneau, America/Los_Angeles, America/Tijuana, America/Phoenix, America/Chihuahua, America/Mazatlan, America/Denver, America/Guatemala, America/Chicago, America/Mexico_City, America/Mexico_City, America/Monterrey, America/Regina, America/Bogota, America/New_York, America/Indiana/Indianapolis, America/Lima, America/Lima, America/Halifax, America/Caracas, America/Guyana, America/La_Paz, America/Santiago, America/St_Johns, America/Sao_Paulo, America/Argentina/Buenos_Aires, America/Godthab, America/Montevideo, Atlantic/South_Georgia, Atlantic/Azores, Atlantic/Cape_Verde, Europe/London, Europe/Lisbon, Europe/London, Africa/Monrovia, Etc/UTC, Europe/Amsterdam, Europe/Belgrade, Europe/Berlin, Europe/Zurich, Europe/Prague, Europe/Brussels, Europe/Budapest, Africa/Casablanca, Europe/Copenhagen, Europe/Dublin, Europe/Belgrade, Europe/Madrid, Europe/Paris, Europe/Prague, Europe/Rome, Europe/Belgrade, Europe/Belgrade, Europe/Stockholm, Europe/Vienna, Europe/Warsaw, Africa/Algiers, Europe/Belgrade, Europe/Zurich, Europe/Athens, Europe/Bucharest, Africa/Cairo, Africa/Maputo, Europe/Helsinki, Asia/Jerusalem, Europe/Kaliningrad, Europe/Kiev, Africa/Johannesburg, Europe/Riga, Europe/Sofia, Europe/Tallinn, Europe/Vilnius, Asia/Baghdad, Europe/Istanbul, Asia/Riyadh, Europe/Minsk, Europe/Moscow, Africa/Nairobi, Asia/Riyadh, Europe/Moscow, Asia/Tehran, Asia/Dubai, Asia/Baku, Asia/Dubai, Europe/Samara, Asia/Tbilisi, Europe/Volgograd, Asia/Yerevan, Asia/Kabul, Asia/Yekaterinburg, Asia/Karachi, Asia/Karachi, Asia/Tashkent, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Colombo, Asia/Kathmandu, Asia/Almaty, Asia/Dhaka, Asia/Dhaka, Asia/Urumqi, Asia/Yangon, Asia/Bangkok, Asia/Bangkok, Asia/Jakarta, Asia/Krasnoyarsk, Asia/Novosibirsk, Asia/Shanghai, Asia/Shanghai, Asia/Hong_Kong, Asia/Irkutsk, Asia/Kuala_Lumpur, Australia/Perth, Asia/Singapore, Asia/Taipei, Asia/Ulaanbaatar, Asia/Tokyo, Asia/Tokyo, Asia/Seoul, Asia/Tokyo, Asia/Yakutsk, Australia/Adelaide, Australia/Darwin, Australia/Brisbane, Australia/Melbourne, Pacific/Guam, Australia/Hobart, Australia/Melbourne, Pacific/Port_Moresby, Australia/Sydney, Asia/Vladivostok, Asia/Magadan, Pacific/Noumea, Pacific/Guadalcanal, Asia/Srednekolymsk, Pacific/Auckland, Pacific/Fiji, Asia/Kamchatka, Pacific/Majuro, Pacific/Auckland, Pacific/Chatham, Pacific/Tongatapu, Pacific/Apia, Pacific/Fakaofo. The time zone.
  - `campus[language_id]` optional (Fixnum) — The language id.
  - `campus[main_email]` optional (String) — The main email.
  - `campus[endpoint_id]` optional (Fixnum) — The endpoint id.
  - `campus[vogsphere_id]` optional (Fixnum) — The vogsphere id.
  - `campus[content_email]` optional (String) — The content email. Default to greetings first name and welcome at 42, in this email you'll find information that will allow you to log on the computers at school and start smoothly. please don't lose this email and don't delete it else you'll not be able to start working as fast as other students at the beginning of the piscine. here are your login and your password to connect at 42 : login : login password : password as stipulated in the charter you agreed on when registering for the piscine, you are responsible for this login and the use that will be done of it. best regards, 42 campus .
  - `campus[tig_email]` optional (String) — The tig email. Default to hi, your account has been closed for the following reason: “ reason ”. to unclose your account, you must choose a date for your community services hererl schedule ). your community services will last ** duration hours. warning: do not set your community services on national holiday, otherwise your community services duration will be doubled. meet the bocal at start at . if you are late or missing, your community services duration will be doubled. .
  - `campus[time_of_community_service_started]` optional (String) — The time of community service started.
  - `campus[companies_mail]` optional (String) — The companies mail.
  - `campus[address]` optional (String) — The address.
  - `campus[zip]` optional (String) — The zip.
  - `campus[city]` optional (String) — The city.
  - `campus[country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `campus[pro_needs_validation]` optional (enum) — true, false. Is it pro needs validation ? Default to false.
  - `campus[open_to_job_offers]` optional (enum) — true, false. Is it open to job offers ?
  - `campus[logo]` optional (File) — The logo.
  - `campus[website]` optional (String) — The website.
  - `campus[facebook]` optional (String) — The facebook.
  - `campus[twitter]` optional (String) — The twitter.
  - `campus[display_name]` optional (String) — The display name.
  - `campus[email_extension]` optional (String) — The email extension.
  - `campus[help_url]` optional (String) — The help url.
  - `campus[logo_cache]` optional (String) — The logo cache.
  - `campus[default_hidden_phone]` optional (enum) — true, false. Is it default hidden phone ? Default to false.
  - `campus[minimum_slot_duration]` optional (Fixnum) — The minimum slot duration. Default to 30.
  - `campus[manual_alumnization_before_first_internship]` optional (enum) — true, false. Is it manual alumnization before first internship ? Default to true.
  - `campus[public]` optional (enum) — true, false. Is it public ? Default to false.

### `PATCH /v2/campus/:id`
Update a campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus` optional (Hash) — 
  - `campus[name]` optional (String) — The name. Must be unique.
  - `campus[time_zone]` optional (enum) — Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Honolulu, America/Juneau, America/Los_Angeles, America/Tijuana, America/Phoenix, America/Chihuahua, America/Mazatlan, America/Denver, America/Guatemala, America/Chicago, America/Mexico_City, America/Mexico_City, America/Monterrey, America/Regina, America/Bogota, America/New_York, America/Indiana/Indianapolis, America/Lima, America/Lima, America/Halifax, America/Caracas, America/Guyana, America/La_Paz, America/Santiago, America/St_Johns, America/Sao_Paulo, America/Argentina/Buenos_Aires, America/Godthab, America/Montevideo, Atlantic/South_Georgia, Atlantic/Azores, Atlantic/Cape_Verde, Europe/London, Europe/Lisbon, Europe/London, Africa/Monrovia, Etc/UTC, Europe/Amsterdam, Europe/Belgrade, Europe/Berlin, Europe/Zurich, Europe/Prague, Europe/Brussels, Europe/Budapest, Africa/Casablanca, Europe/Copenhagen, Europe/Dublin, Europe/Belgrade, Europe/Madrid, Europe/Paris, Europe/Prague, Europe/Rome, Europe/Belgrade, Europe/Belgrade, Europe/Stockholm, Europe/Vienna, Europe/Warsaw, Africa/Algiers, Europe/Belgrade, Europe/Zurich, Europe/Athens, Europe/Bucharest, Africa/Cairo, Africa/Maputo, Europe/Helsinki, Asia/Jerusalem, Europe/Kaliningrad, Europe/Kiev, Africa/Johannesburg, Europe/Riga, Europe/Sofia, Europe/Tallinn, Europe/Vilnius, Asia/Baghdad, Europe/Istanbul, Asia/Riyadh, Europe/Minsk, Europe/Moscow, Africa/Nairobi, Asia/Riyadh, Europe/Moscow, Asia/Tehran, Asia/Dubai, Asia/Baku, Asia/Dubai, Europe/Samara, Asia/Tbilisi, Europe/Volgograd, Asia/Yerevan, Asia/Kabul, Asia/Yekaterinburg, Asia/Karachi, Asia/Karachi, Asia/Tashkent, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Colombo, Asia/Kathmandu, Asia/Almaty, Asia/Dhaka, Asia/Dhaka, Asia/Urumqi, Asia/Yangon, Asia/Bangkok, Asia/Bangkok, Asia/Jakarta, Asia/Krasnoyarsk, Asia/Novosibirsk, Asia/Shanghai, Asia/Shanghai, Asia/Hong_Kong, Asia/Irkutsk, Asia/Kuala_Lumpur, Australia/Perth, Asia/Singapore, Asia/Taipei, Asia/Ulaanbaatar, Asia/Tokyo, Asia/Tokyo, Asia/Seoul, Asia/Tokyo, Asia/Yakutsk, Australia/Adelaide, Australia/Darwin, Australia/Brisbane, Australia/Melbourne, Pacific/Guam, Australia/Hobart, Australia/Melbourne, Pacific/Port_Moresby, Australia/Sydney, Asia/Vladivostok, Asia/Magadan, Pacific/Noumea, Pacific/Guadalcanal, Asia/Srednekolymsk, Pacific/Auckland, Pacific/Fiji, Asia/Kamchatka, Pacific/Majuro, Pacific/Auckland, Pacific/Chatham, Pacific/Tongatapu, Pacific/Apia, Pacific/Fakaofo. The time zone.
  - `campus[language_id]` optional (Fixnum) — The language id.
  - `campus[main_email]` optional (String) — The main email.
  - `campus[endpoint_id]` optional (Fixnum) — The endpoint id.
  - `campus[vogsphere_id]` optional (Fixnum) — The vogsphere id.
  - `campus[content_email]` optional (String) — The content email. Default to greetings first name and welcome at 42, in this email you'll find information that will allow you to log on the computers at school and start smoothly. please don't lose this email and don't delete it else you'll not be able to start working as fast as other students at the beginning of the piscine. here are your login and your password to connect at 42 : login : login password : password as stipulated in the charter you agreed on when registering for the piscine, you are responsible for this login and the use that will be done of it. best regards, 42 campus .
  - `campus[tig_email]` optional (String) — The tig email. Default to hi, your account has been closed for the following reason: “ reason ”. to unclose your account, you must choose a date for your community services hererl schedule ). your community services will last ** duration hours. warning: do not set your community services on national holiday, otherwise your community services duration will be doubled. meet the bocal at start at . if you are late or missing, your community services duration will be doubled. .
  - `campus[time_of_community_service_started]` optional (String) — The time of community service started.
  - `campus[companies_mail]` optional (String) — The companies mail.
  - `campus[address]` optional (String) — The address.
  - `campus[zip]` optional (String) — The zip.
  - `campus[city]` optional (String) — The city.
  - `campus[country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `campus[pro_needs_validation]` optional (enum) — true, false. Is it pro needs validation ? Default to false.
  - `campus[open_to_job_offers]` optional (enum) — true, false. Is it open to job offers ?
  - `campus[logo]` optional (File) — The logo.
  - `campus[website]` optional (String) — The website.
  - `campus[facebook]` optional (String) — The facebook.
  - `campus[twitter]` optional (String) — The twitter.
  - `campus[display_name]` optional (String) — The display name.
  - `campus[email_extension]` optional (String) — The email extension.
  - `campus[help_url]` optional (String) — The help url.
  - `campus[logo_cache]` optional (String) — The logo cache.
  - `campus[default_hidden_phone]` optional (enum) — true, false. Is it default hidden phone ? Default to false.
  - `campus[minimum_slot_duration]` optional (Fixnum) — The minimum slot duration. Default to 30.
  - `campus[manual_alumnization_before_first_internship]` optional (enum) — true, false. Is it manual alumnization before first internship ? Default to true.
  - `campus[public]` optional (enum) — true, false. Is it public ? Default to false.

### `PUT /v2/campus/:id`
Update a campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus` optional (Hash) — 
  - `campus[name]` optional (String) — The name. Must be unique.
  - `campus[time_zone]` optional (enum) — Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Pago_Pago, Pacific/Honolulu, America/Juneau, America/Los_Angeles, America/Tijuana, America/Phoenix, America/Chihuahua, America/Mazatlan, America/Denver, America/Guatemala, America/Chicago, America/Mexico_City, America/Mexico_City, America/Monterrey, America/Regina, America/Bogota, America/New_York, America/Indiana/Indianapolis, America/Lima, America/Lima, America/Halifax, America/Caracas, America/Guyana, America/La_Paz, America/Santiago, America/St_Johns, America/Sao_Paulo, America/Argentina/Buenos_Aires, America/Godthab, America/Montevideo, Atlantic/South_Georgia, Atlantic/Azores, Atlantic/Cape_Verde, Europe/London, Europe/Lisbon, Europe/London, Africa/Monrovia, Etc/UTC, Europe/Amsterdam, Europe/Belgrade, Europe/Berlin, Europe/Zurich, Europe/Prague, Europe/Brussels, Europe/Budapest, Africa/Casablanca, Europe/Copenhagen, Europe/Dublin, Europe/Belgrade, Europe/Madrid, Europe/Paris, Europe/Prague, Europe/Rome, Europe/Belgrade, Europe/Belgrade, Europe/Stockholm, Europe/Vienna, Europe/Warsaw, Africa/Algiers, Europe/Belgrade, Europe/Zurich, Europe/Athens, Europe/Bucharest, Africa/Cairo, Africa/Maputo, Europe/Helsinki, Asia/Jerusalem, Europe/Kaliningrad, Europe/Kiev, Africa/Johannesburg, Europe/Riga, Europe/Sofia, Europe/Tallinn, Europe/Vilnius, Asia/Baghdad, Europe/Istanbul, Asia/Riyadh, Europe/Minsk, Europe/Moscow, Africa/Nairobi, Asia/Riyadh, Europe/Moscow, Asia/Tehran, Asia/Dubai, Asia/Baku, Asia/Dubai, Europe/Samara, Asia/Tbilisi, Europe/Volgograd, Asia/Yerevan, Asia/Kabul, Asia/Yekaterinburg, Asia/Karachi, Asia/Karachi, Asia/Tashkent, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Kolkata, Asia/Colombo, Asia/Kathmandu, Asia/Almaty, Asia/Dhaka, Asia/Dhaka, Asia/Urumqi, Asia/Yangon, Asia/Bangkok, Asia/Bangkok, Asia/Jakarta, Asia/Krasnoyarsk, Asia/Novosibirsk, Asia/Shanghai, Asia/Shanghai, Asia/Hong_Kong, Asia/Irkutsk, Asia/Kuala_Lumpur, Australia/Perth, Asia/Singapore, Asia/Taipei, Asia/Ulaanbaatar, Asia/Tokyo, Asia/Tokyo, Asia/Seoul, Asia/Tokyo, Asia/Yakutsk, Australia/Adelaide, Australia/Darwin, Australia/Brisbane, Australia/Melbourne, Pacific/Guam, Australia/Hobart, Australia/Melbourne, Pacific/Port_Moresby, Australia/Sydney, Asia/Vladivostok, Asia/Magadan, Pacific/Noumea, Pacific/Guadalcanal, Asia/Srednekolymsk, Pacific/Auckland, Pacific/Fiji, Asia/Kamchatka, Pacific/Majuro, Pacific/Auckland, Pacific/Chatham, Pacific/Tongatapu, Pacific/Apia, Pacific/Fakaofo. The time zone.
  - `campus[language_id]` optional (Fixnum) — The language id.
  - `campus[main_email]` optional (String) — The main email.
  - `campus[endpoint_id]` optional (Fixnum) — The endpoint id.
  - `campus[vogsphere_id]` optional (Fixnum) — The vogsphere id.
  - `campus[content_email]` optional (String) — The content email. Default to greetings first name and welcome at 42, in this email you'll find information that will allow you to log on the computers at school and start smoothly. please don't lose this email and don't delete it else you'll not be able to start working as fast as other students at the beginning of the piscine. here are your login and your password to connect at 42 : login : login password : password as stipulated in the charter you agreed on when registering for the piscine, you are responsible for this login and the use that will be done of it. best regards, 42 campus .
  - `campus[tig_email]` optional (String) — The tig email. Default to hi, your account has been closed for the following reason: “ reason ”. to unclose your account, you must choose a date for your community services hererl schedule ). your community services will last ** duration hours. warning: do not set your community services on national holiday, otherwise your community services duration will be doubled. meet the bocal at start at . if you are late or missing, your community services duration will be doubled. .
  - `campus[time_of_community_service_started]` optional (String) — The time of community service started.
  - `campus[companies_mail]` optional (String) — The companies mail.
  - `campus[address]` optional (String) — The address.
  - `campus[zip]` optional (String) — The zip.
  - `campus[city]` optional (String) — The city.
  - `campus[country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `campus[pro_needs_validation]` optional (enum) — true, false. Is it pro needs validation ? Default to false.
  - `campus[open_to_job_offers]` optional (enum) — true, false. Is it open to job offers ?
  - `campus[logo]` optional (File) — The logo.
  - `campus[website]` optional (String) — The website.
  - `campus[facebook]` optional (String) — The facebook.
  - `campus[twitter]` optional (String) — The twitter.
  - `campus[display_name]` optional (String) — The display name.
  - `campus[email_extension]` optional (String) — The email extension.
  - `campus[help_url]` optional (String) — The help url.
  - `campus[logo_cache]` optional (String) — The logo cache.
  - `campus[default_hidden_phone]` optional (enum) — true, false. Is it default hidden phone ? Default to false.
  - `campus[minimum_slot_duration]` optional (Fixnum) — The minimum slot duration. Default to 30.
  - `campus[manual_alumnization_before_first_internship]` optional (enum) — true, false. Is it manual alumnization before first internship ? Default to true.
  - `campus[public]` optional (enum) — true, false. Is it public ? Default to false.


## campus_users

### `POST /v2/campus_users`
Create a campus user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_user` optional (Hash) — 
  - `campus_user[campus_id]` required (Fixnum) — The campus id.
  - `campus_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given campus.
  - `campus_user[is_primary]` optional (enum) — true, false. Is it is primary ? Default to false.

### `POST /v2/users/:user_id/campus_users`
Create a campus user for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_user` optional (Hash) — 
  - `campus_user[campus_id]` required (Fixnum) — The campus id.
  - `campus_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given campus.
  - `campus_user[is_primary]` optional (enum) — true, false. Is it is primary ? Default to false.

### `GET /v2/campus_users`
Return all the campus users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, campus_id, is_primary, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on campus users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, campus_id, is_primary, created_at, updated_at. Filtering on one or more fields More Example: To filter on campus users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) campus_id (standard field) is_primary (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, user_id, campus_id, is_primary, created_at, updated_at. Select on a particular range More Example: To range on campus users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id campus_id is_primary created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/campus_users`
Return all the campus users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, campus_id, is_primary, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on campus users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, campus_id, is_primary, created_at, updated_at. Filtering on one or more fields More Example: To filter on campus users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) campus_id (standard field) is_primary (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, user_id, campus_id, is_primary, created_at, updated_at. Select on a particular range More Example: To range on campus users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id campus_id is_primary created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `POST /v2/campus_users/:id/set_as_primary`
- **Auth/scope:** assignment This action requires one of theses roles: 42network

### `GET /v2/campus_users/:id`
Get a campus user
- **Params:**
  - `id` required (String) — The requested id


## certificates

### `GET /v2/certificates`
Return all the certificates
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `certificate` optional (Hash) — 
  - `certificate[name]` optional (String) — The name. Must be unique.
  - `certificate[content]` optional (String) — The content.
  - `certificate[total_certificate_number]` optional (Fixnum) — The total certificate number.
  - `certificate[image]` optional (File) — The image.
  - `certificate[cursus_id]` optional (Fixnum) — The cursus id.

### `GET /v2/certificates/:id`
Get a certificate
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `certificate` optional (Hash) — 
  - `certificate[name]` optional (String) — The name. Must be unique.
  - `certificate[content]` optional (String) — The content.
  - `certificate[total_certificate_number]` optional (Fixnum) — The total certificate number.
  - `certificate[image]` optional (File) — The image.
  - `certificate[cursus_id]` optional (Fixnum) — The cursus id.


## certificates_users

### `DELETE /v2/certificates_users/:id`
Destroy a certificates user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `certificates_user` optional (Hash) — 
  - `certificates_user[certificate_id]` optional (Fixnum) — The certificate id. Must be unique in the scope of a given user.
  - `certificates_user[user_id]` optional (Fixnum) — The user id.
  - `certificates_user[certificate_number]` optional (Fixnum) — The certificate number.
  - `certificates_user[qrcode]` optional (File) — The qrcode.
  - `certificates_user[pdf]` optional (File) — The pdf.
  - `certificates_user[certified_at]` optional (String) — The certified at.

### `GET /v2/certificates_users`
Return all the certificates users
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `certificate_id` optional (String) — The certificate id
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `certificates_user` optional (Hash) — 
  - `certificates_user[certificate_id]` optional (Fixnum) — The certificate id. Must be unique in the scope of a given user.
  - `certificates_user[user_id]` optional (Fixnum) — The user id.
  - `certificates_user[certificate_number]` optional (Fixnum) — The certificate number.
  - `certificates_user[qrcode]` optional (File) — The qrcode.
  - `certificates_user[pdf]` optional (File) — The pdf.
  - `certificates_user[certified_at]` optional (String) — The certified at.

### `GET /v2/certificates/:certificate_id/certificates_users`
Return all the certificates users of the given Certificate
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `certificate_id` optional (String) — The certificate id
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `certificates_user` optional (Hash) — 
  - `certificates_user[certificate_id]` optional (Fixnum) — The certificate id. Must be unique in the scope of a given user.
  - `certificates_user[user_id]` optional (Fixnum) — The user id.
  - `certificates_user[certificate_number]` optional (Fixnum) — The certificate number.
  - `certificates_user[qrcode]` optional (File) — The qrcode.
  - `certificates_user[pdf]` optional (File) — The pdf.
  - `certificates_user[certified_at]` optional (String) — The certified at.

### `GET /v2/users/:user_id/certificates_users`
Return all the certificates users of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `certificate_id` optional (String) — The certificate id
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `certificates_user` optional (Hash) — 
  - `certificates_user[certificate_id]` optional (Fixnum) — The certificate id. Must be unique in the scope of a given user.
  - `certificates_user[user_id]` optional (Fixnum) — The user id.
  - `certificates_user[certificate_number]` optional (Fixnum) — The certificate number.
  - `certificates_user[qrcode]` optional (File) — The qrcode.
  - `certificates_user[pdf]` optional (File) — The pdf.
  - `certificates_user[certified_at]` optional (String) — The certified at.

### `GET /v2/certificates_users/:id`
Get a certificates user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `certificates_user` optional (Hash) — 
  - `certificates_user[certificate_id]` optional (Fixnum) — The certificate id. Must be unique in the scope of a given user.
  - `certificates_user[user_id]` optional (Fixnum) — The user id.
  - `certificates_user[certificate_number]` optional (Fixnum) — The certificate number.
  - `certificates_user[qrcode]` optional (File) — The qrcode.
  - `certificates_user[pdf]` optional (File) — The pdf.
  - `certificates_user[certified_at]` optional (String) — The certified at.


## closes

### `PATCH /v2/closes/:id/close`
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PUT /v2/closes/:id/close`
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `POST /v2/closes`
Create a close
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `close` optional (Hash) — 
  - `close[user_id]` required (Fixnum) — The closed user
  - `close[closer_id]` required (Fixnum) — The closer, defaults to the token owner if there is one
  - `close[kind]` required (enum) — agu, other, deserter, black_hole, serious_misconduct, social_security, non_admitted, pace_unknown. The close kind
  - `close[reason]` required (String) — The reason of this close
  - `close[end_at]` optional (DateTime) — When the close will be end
  - `close[community_services_attributes]` optional (n) — Array of nested elements The linked community service(s)
  - `close[community_services_attributes][duration]` required (enum) — 7200, 14400, 28800. The community service duration in seconds. Must be 2 hours, 4 hours or 8 hours.
  - `close[community_services_attributes][occupation]` optional (String) — The community service occupation

### `POST /v2/users/:user_id/closes`
Create a close for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `close` optional (Hash) — 
  - `close[user_id]` required (Fixnum) — The closed user
  - `close[closer_id]` required (Fixnum) — The closer, defaults to the token owner if there is one
  - `close[kind]` required (enum) — agu, other, deserter, black_hole, serious_misconduct, social_security, non_admitted, pace_unknown. The close kind
  - `close[reason]` required (String) — The reason of this close
  - `close[end_at]` optional (DateTime) — When the close will be end
  - `close[community_services_attributes]` optional (n) — Array of nested elements The linked community service(s)
  - `close[community_services_attributes][duration]` required (enum) — 7200, 14400, 28800. The community service duration in seconds. Must be 2 hours, 4 hours or 8 hours.
  - `close[community_services_attributes][occupation]` optional (String) — The community service occupation

### `DELETE /v2/closes/:id`
Destroy a close
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id
  - `close` optional (Hash) — 
  - `close[user_id]` optional (Fixnum) — The closed user
  - `close[closer_id]` optional (Fixnum) — The closer, defaults to the token owner if there is one
  - `close[kind]` optional (enum) — agu, other, deserter, black_hole, serious_misconduct, social_security, non_admitted, pace_unknown. The close kind
  - `close[reason]` optional (String) — The reason of this close
  - `close[end_at]` optional (DateTime) — When the close will be end
  - `close[community_services_attributes]` optional (n) — Array of nested elements The linked community service(s)
  - `close[community_services_attributes][duration]` optional (enum) — 7200, 14400, 28800. The community service duration in seconds. Must be 2 hours, 4 hours or 8 hours.
  - `close[community_services_attributes][occupation]` optional (String) — The community service occupation

### `GET /v2/closes`
Return all the closes
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items group_work Requires following application scopes: tig
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, closer_id, reason, state, created_at, updated_at, kind, end_at, jid. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on closes on the fields end_at on a descending order and jid on a ascending order: ...&sort=-end_at,jid
  - `filter` optional (enum) — id, user_id, closer_id, reason, state, created_at, updated_at, kind, end_at, jid, campus_id, end. Filtering on one or more fields More Example: To filter on closes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) closer_id (standard field) reason (standard field) state (standard field) created_at (standard field) updated_at (standard field) kind (standard field) end_at (standard field) jid (standard field) campus_id : . end (standard field)
  - `range` optional (enum) — id, user_id, closer_id, reason, state, created_at, updated_at, kind, end_at, jid. Select on a particular range More Example: To range on closes with the jid field between min_value and max_value: ...&range[jid]=min_value,max_value Rangeable fields: id user_id closer_id reason state created_at updated_at kind end_at jid
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/closes`
Return all the closes of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items group_work Requires following application scopes: tig
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, closer_id, reason, state, created_at, updated_at, kind, end_at, jid. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on closes on the fields end_at on a descending order and jid on a ascending order: ...&sort=-end_at,jid
  - `filter` optional (enum) — id, user_id, closer_id, reason, state, created_at, updated_at, kind, end_at, jid, campus_id, end. Filtering on one or more fields More Example: To filter on closes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) closer_id (standard field) reason (standard field) state (standard field) created_at (standard field) updated_at (standard field) kind (standard field) end_at (standard field) jid (standard field) campus_id : . end (standard field)
  - `range` optional (enum) — id, user_id, closer_id, reason, state, created_at, updated_at, kind, end_at, jid. Select on a particular range More Example: To range on closes with the jid field between min_value and max_value: ...&range[jid]=min_value,max_value Rangeable fields: id user_id closer_id reason state created_at updated_at kind end_at jid
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/closes/:id`
Get a close
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/closes/:id/unclose`
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PUT /v2/closes/:id/unclose`
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/closes/:id`
Update a close
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id
  - `close` optional (Hash) — 
  - `close[user_id]` optional (Fixnum) — The closed user
  - `close[closer_id]` optional (Fixnum) — The closer, defaults to the token owner if there is one
  - `close[kind]` optional (enum) — agu, other, deserter, black_hole, serious_misconduct, social_security, non_admitted, pace_unknown. The close kind
  - `close[reason]` optional (String) — The reason of this close
  - `close[end_at]` optional (DateTime) — When the close will be end
  - `close[community_services_attributes]` optional (n) — Array of nested elements The linked community service(s)
  - `close[community_services_attributes][duration]` optional (enum) — 7200, 14400, 28800. The community service duration in seconds. Must be 2 hours, 4 hours or 8 hours.
  - `close[community_services_attributes][occupation]` optional (String) — The community service occupation

### `PUT /v2/closes/:id`
Update a close
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id
  - `close` optional (Hash) — 
  - `close[user_id]` optional (Fixnum) — The closed user
  - `close[closer_id]` optional (Fixnum) — The closer, defaults to the token owner if there is one
  - `close[kind]` optional (enum) — agu, other, deserter, black_hole, serious_misconduct, social_security, non_admitted, pace_unknown. The close kind
  - `close[reason]` optional (String) — The reason of this close
  - `close[end_at]` optional (DateTime) — When the close will be end
  - `close[community_services_attributes]` optional (n) — Array of nested elements The linked community service(s)
  - `close[community_services_attributes][duration]` optional (enum) — 7200, 14400, 28800. The community service duration in seconds. Must be 2 hours, 4 hours or 8 hours.
  - `close[community_services_attributes][occupation]` optional (String) — The community service occupation


## clusters

### `GET /v2/clusters`
Return all the clusters
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, campus_id, created_at, updated_at, image. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on clusters on the fields updated_at on a descending order and image on a ascending order: ...&sort=-updated_at,image
  - `filter` optional (enum) — id, name, campus_id, created_at, updated_at, image. Filtering on one or more fields More Example: To filter on clusters with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) campus_id (standard field) created_at (standard field) updated_at (standard field) image (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `cluster` optional (Hash) — 
  - `cluster[name]` optional (String) — The name.
  - `cluster[campus_id]` optional (Fixnum) — The campus id.
  - `cluster[image]` optional (File) — The image.

### `GET /v2/clusters/:id`
Get a cluster
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `cluster` optional (Hash) — 
  - `cluster[name]` optional (String) — The name.
  - `cluster[campus_id]` optional (Fixnum) — The campus id.
  - `cluster[image]` optional (File) — The image.


## coalitions

### `POST /v2/coalitions`
Create a coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` required (Fixnum) — The bloc id.
  - `coalition[user_id]` required (Fixnum) — The user id.
  - `coalition[name]` required (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` required (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` required (String) — The color.
  - `coalition[cover]` optional (File) — The cover.

### `GET /v2/coalitions`
Return all the coalitions
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, bloc_id, user_id, name, image, slug, created_at, updated_at, color, cover. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on coalitions on the fields color on a descending order and cover on a ascending order: ...&sort=-color,cover
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` optional (Fixnum) — The bloc id.
  - `coalition[user_id]` optional (Fixnum) — The user id.
  - `coalition[name]` optional (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` optional (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` optional (String) — The color.
  - `coalition[cover]` optional (File) — The cover.

### `GET /v2/users/:user_id/coalitions`
Return all the coalitions of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, bloc_id, user_id, name, image, slug, created_at, updated_at, color, cover. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on coalitions on the fields color on a descending order and cover on a ascending order: ...&sort=-color,cover
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` optional (Fixnum) — The bloc id.
  - `coalition[user_id]` optional (Fixnum) — The user id.
  - `coalition[name]` optional (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` optional (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` optional (String) — The color.
  - `coalition[cover]` optional (File) — The cover.

### `GET /v2/blocs/:bloc_id/coalitions`
Return all the coalitions of the given Bloc
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, bloc_id, user_id, name, image, slug, created_at, updated_at, color, cover. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on coalitions on the fields color on a descending order and cover on a ascending order: ...&sort=-color,cover
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` optional (Fixnum) — The bloc id.
  - `coalition[user_id]` optional (Fixnum) — The user id.
  - `coalition[name]` optional (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` optional (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` optional (String) — The color.
  - `coalition[cover]` optional (File) — The cover.

### `GET /v2/coalitions/:id`
Get a coalition
- **Params:**
  - `id` required (String) — The requested id
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` optional (Fixnum) — The bloc id.
  - `coalition[user_id]` optional (Fixnum) — The user id.
  - `coalition[name]` optional (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` optional (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` optional (String) — The color.
  - `coalition[cover]` optional (File) — The cover.

### `PATCH /v2/coalitions/:id`
Update a coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` optional (Fixnum) — The bloc id.
  - `coalition[user_id]` optional (Fixnum) — The user id.
  - `coalition[name]` optional (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` optional (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` optional (String) — The color.
  - `coalition[cover]` optional (File) — The cover.

### `PUT /v2/coalitions/:id`
Update a coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalition` optional (Hash) — 
  - `coalition[bloc_id]` optional (Fixnum) — The bloc id.
  - `coalition[user_id]` optional (Fixnum) — The user id.
  - `coalition[name]` optional (String) — The name. Must be unique in the scope of a given bloc.
  - `coalition[image]` optional (File) — The image.
  - `coalition[slug]` optional (String) — The slug.
  - `coalition[color]` optional (String) — The color.
  - `coalition[cover]` optional (File) — The cover.


## coalitions_users

### `POST /v2/coalitions_users`
Create a coalitions user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` required (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` required (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `DELETE /v2/coalitions_users/:id`
Destroy a coalitions user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `GET /v2/coalitions/:coalition_id/coalitions_users`
Return all the coalitions users of the given Coalition
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on coalitions users on the fields this_year_score on a descending order and this_year_score_updated_at on a ascending order: ...&sort=-this_year_score,this_year_score_updated_at
  - `filter` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at, this_year_score_updated. Filtering on one or more fields More Example: To filter on coalitions users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) coalition_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) this_year_score (standard field) this_year_score_updated_at (standard field) this_year_score_updated (standard field)
  - `range` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at. Select on a particular range More Example: To range on coalitions users with the this_year_score_updated_at field between min_value and max_value: ...&range[this_year_score_updated_at]=min_value,max_value Rangeable fields: id coalition_id user_id created_at updated_at this_year_score this_year_score_updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `GET /v2/coalitions_users`
Return all the coalitions users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on coalitions users on the fields this_year_score on a descending order and this_year_score_updated_at on a ascending order: ...&sort=-this_year_score,this_year_score_updated_at
  - `filter` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at, this_year_score_updated. Filtering on one or more fields More Example: To filter on coalitions users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) coalition_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) this_year_score (standard field) this_year_score_updated_at (standard field) this_year_score_updated (standard field)
  - `range` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at. Select on a particular range More Example: To range on coalitions users with the this_year_score_updated_at field between min_value and max_value: ...&range[this_year_score_updated_at]=min_value,max_value Rangeable fields: id coalition_id user_id created_at updated_at this_year_score this_year_score_updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `GET /v2/users/:user_id/coalitions_users`
Return all the coalitions users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on coalitions users on the fields this_year_score on a descending order and this_year_score_updated_at on a ascending order: ...&sort=-this_year_score,this_year_score_updated_at
  - `filter` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at, this_year_score_updated. Filtering on one or more fields More Example: To filter on coalitions users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) coalition_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) this_year_score (standard field) this_year_score_updated_at (standard field) this_year_score_updated (standard field)
  - `range` optional (enum) — id, coalition_id, user_id, created_at, updated_at, this_year_score, this_year_score_updated_at. Select on a particular range More Example: To range on coalitions users with the this_year_score_updated_at field between min_value and max_value: ...&range[this_year_score_updated_at]=min_value,max_value Rangeable fields: id coalition_id user_id created_at updated_at this_year_score this_year_score_updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `GET /v2/coalitions_users/:id`
Get a coalitions user
- **Params:**
  - `id` required (String) — The requested id
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `PATCH /v2/coalitions_users/:id`
Update a coalitions user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.

### `PUT /v2/coalitions_users/:id`
Update a coalitions user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalitions_user` optional (Hash) — 
  - `coalitions_user[coalition_id]` optional (Fixnum) — The coalition id.
  - `coalitions_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given coalition.
  - `coalitions_user[this_year_score]` optional (Fixnum) — The this year score.
  - `coalitions_user[this_year_score_updated_at]` optional (DateTime) — The this year score updated at.


## commands

### `GET /v2/products/:product_id/commands`
Return all the commands of the given Product
- **Params:**
  - `product_id` optional (String) — The product id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, created_at, updated_at, product_id, user_id, owner_id, used, validator_id, validated_at. The sort field. Sorted by id desc by default. More Example: To sort on commands on the fields validator_id on a descending order and validated_at on a ascending order: ...&sort=-validator_id,validated_at
  - `filter` optional (enum) — id, created_at, updated_at, product_id, user_id, owner_id, used, validator_id, validated_at, validated. Filtering on one or more fields More Example: To filter on commands with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) created_at (standard field) updated_at (standard field) product_id (standard field) user_id (standard field) owner_id (standard field) used (standard field) validator_id (standard field) validated_at (standard field) validated (standard field)
  - `range` optional (enum) — id, created_at, updated_at, product_id, user_id, owner_id, used, validator_id, validated_at. Select on a particular range More Example: To range on commands with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id created_at updated_at product_id user_id owner_id used validator_id validated_at

### `GET /v2/campus/:campus_id/products/:product_id/commands`
Return all the commands of the given Product, associated with the given Campus
- **Params:**
  - `product_id` optional (String) — The product id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, created_at, updated_at, product_id, user_id, owner_id, used, validator_id, validated_at. The sort field. Sorted by id desc by default. More Example: To sort on commands on the fields validator_id on a descending order and validated_at on a ascending order: ...&sort=-validator_id,validated_at
  - `filter` optional (enum) — id, created_at, updated_at, product_id, user_id, owner_id, used, validator_id, validated_at, validated. Filtering on one or more fields More Example: To filter on commands with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) created_at (standard field) updated_at (standard field) product_id (standard field) user_id (standard field) owner_id (standard field) used (standard field) validator_id (standard field) validated_at (standard field) validated (standard field)
  - `range` optional (enum) — id, created_at, updated_at, product_id, user_id, owner_id, used, validator_id, validated_at. Select on a particular range More Example: To range on commands with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id created_at updated_at product_id user_id owner_id used validator_id validated_at


## community_services

### `POST /v2/community_services`
Create a community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `community_service` optional (Hash) — 
  - `community_service[duration]` required (Fixnum) — The duration.
  - `community_service[occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `community_service[schedule_at]` optional (Fixnum) — The schedule at. Must be after today. Must be before 2 weeks from now.
  - `community_service[close_id]` optional (Fixnum) — The close id.
  - `community_service[tiger_id]` optional (Fixnum) — The tiger id.

### `DELETE /v2/community_services/:id`
Destroy a community service
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id
  - `community_service` optional (Hash) — 
  - `community_service[duration]` optional (Fixnum) — The duration.
  - `community_service[occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `community_service[schedule_at]` optional (Fixnum) — The schedule at. Must be after today. Must be before 2 weeks from now.
  - `community_service[close_id]` optional (Fixnum) — The close id.
  - `community_service[tiger_id]` optional (Fixnum) — The tiger id.

### `GET /v2/community_services/graph(/on/:field(/by/:interval))`
Return grouped temporal data on community services
- **Params:**
  - `field` optional (enum) — created_at, updated_at, schedule_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on community services on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at, campus_id, schedule. Filtering on one or more fields More Example: To filter on community services with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) close_id (standard field) tiger_id (standard field) duration (standard field) schedule_at (standard field) occupation (standard field) token (standard field) state (standard field) created_at (standard field) updated_at (standard field) campus_id : . schedule (standard field)
  - `range` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at. Select on a particular range More Example: To range on community services with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id close_id tiger_id duration schedule_at occupation token state created_at updated_at

### `GET /v2/closes/:close_id/community_services`
Return all the community services of the given Close
- **Auth/scope:** This resource is paginated by 30 items group_work Requires following application scopes: tig
- **Params:**
  - `close_id` optional (String) — The close id
  - `sort` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on community services on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at, campus_id, schedule. Filtering on one or more fields More Example: To filter on community services with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) close_id (standard field) tiger_id (standard field) duration (standard field) schedule_at (standard field) occupation (standard field) token (standard field) state (standard field) created_at (standard field) updated_at (standard field) campus_id : . schedule (standard field)
  - `range` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at. Select on a particular range More Example: To range on community services with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id close_id tiger_id duration schedule_at occupation token state created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/community_services`
Return all the community services
- **Auth/scope:** This resource is paginated by 30 items group_work Requires following application scopes: tig
- **Params:**
  - `close_id` optional (String) — The close id
  - `sort` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on community services on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at, campus_id, schedule. Filtering on one or more fields More Example: To filter on community services with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) close_id (standard field) tiger_id (standard field) duration (standard field) schedule_at (standard field) occupation (standard field) token (standard field) state (standard field) created_at (standard field) updated_at (standard field) campus_id : . schedule (standard field)
  - `range` optional (enum) — id, close_id, tiger_id, duration, schedule_at, occupation, token, state, created_at, updated_at. Select on a particular range More Example: To range on community services with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id close_id tiger_id duration schedule_at occupation token state created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `PUT /v2/community_services/:id/invalidate`
Invalidate the given community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/community_services/:id/invalidate`
Invalidate the given community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/community_services/:id`
Get a community service
- **Auth/scope:** group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/community_services/:id`
Update a community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id
  - `community_service` optional (Hash) — 
  - `community_service[duration]` optional (Fixnum) — The duration.
  - `community_service[occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `community_service[schedule_at]` optional (Fixnum) — The schedule at. Must be after today. Must be before 2 weeks from now.
  - `community_service[close_id]` optional (Fixnum) — The close id.
  - `community_service[tiger_id]` optional (Fixnum) — The tiger id.

### `PUT /v2/community_services/:id`
Update a community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id
  - `community_service` optional (Hash) — 
  - `community_service[duration]` optional (Fixnum) — The duration.
  - `community_service[occupation]` optional (String) — The occupation. Maximum length is 255. Allow blank length is true.
  - `community_service[schedule_at]` optional (Fixnum) — The schedule at. Must be after today. Must be before 2 weeks from now.
  - `community_service[close_id]` optional (Fixnum) — The close id.
  - `community_service[tiger_id]` optional (Fixnum) — The tiger id.

### `PUT /v2/community_services/:id/validate`
Validate the given community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/community_services/:id/validate`
Validate the given community service
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff group_work Requires following application scopes: tig
- **Params:**
  - `id` required (String) — The requested id


## companies

### `GET /v2/companies`
Return all the companies
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, slug, sector, other_sector, size, phone, address, zip, city, country, website_url, owner_id, created_at, updated_at, latitude, longitude, siret, pro_id, owner_type, administrative_email. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on companies on the fields owner_type on a descending order and administrative_email on a ascending order: ...&sort=-owner_type,administrative_email
  - `filter` optional (enum) — id, name, slug, sector, other_sector, size, phone, address, zip, city, country, website_url, owner_id, created_at, updated_at, latitude, longitude, siret, pro_id, owner_type, administrative_email, offer_id, expertise_id. Filtering on one or more fields More Example: To filter on companies with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) slug (standard field) sector (standard field) other_sector (standard field) size (standard field) phone (standard field) address (standard field) zip (standard field) city (standard field) country (standard field) website_url (standard field) owner_id (standard field) created_at (standard field) updated_at (standard field) latitude (standard field) longitude (standard field) siret (standard field) pro_id (standard field) owner_type (standard field) administrative_email (standard field) offer_id : Company that posted this offer. expertise_id : Find a company by expertise id.
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/companies/:company_id/internships_users`
for the given Company
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `company_id` required (String) — The company id or slug
  - `company` optional (Hash) — 
  - `company[name]` optional (String) — The name. Maximum length is 255. Must be unique.
  - `company[slug]` optional (String) — The slug. Maximum length is 255.
  - `company[sector]` optional (enum) — agro, audit, banque, commerce, comm, edition, industrie, info, luxe, pharma, services, culture, immobilier, other. The sector.
  - `company[other_sector]` optional (String) — The other sector. Maximum length is 255.
  - `company[size]` optional (enum) — small, medium, large, xlarge. The size.
  - `company[phone]` optional (String) — The phone. Maximum length is 255.
  - `company[address]` optional (String) — The address. Maximum length is 255.
  - `company[zip]` optional (String) — The zip. Maximum length is 255.
  - `company[city]` optional (String) — The city. Maximum length is 255.
  - `company[country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `company[website_url]` optional (String) — The website url. Maximum length is 255.
  - `company[owner_id]` optional (Fixnum) — The owner id.
  - `company[latitude]` optional (Float) — The latitude.
  - `company[longitude]` optional (Float) — The longitude.
  - `company[siret]` optional (String) — The siret.
  - `company[pro_id]` optional (Fixnum) — The pro id.
  - `company[owner_type]` optional (String) — The owner type.
  - `company[administrative_email]` optional (String) — The administrative email.

### `GET /v2/companies/:id`
Get a company
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/companies/:company_id/subscribed_users`
for the given Company
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `company_id` required (String) — The company id or slug
  - `company` optional (Hash) — 
  - `company[name]` optional (String) — The name. Maximum length is 255. Must be unique.
  - `company[slug]` optional (String) — The slug. Maximum length is 255.
  - `company[sector]` optional (enum) — agro, audit, banque, commerce, comm, edition, industrie, info, luxe, pharma, services, culture, immobilier, other. The sector.
  - `company[other_sector]` optional (String) — The other sector. Maximum length is 255.
  - `company[size]` optional (enum) — small, medium, large, xlarge. The size.
  - `company[phone]` optional (String) — The phone. Maximum length is 255.
  - `company[address]` optional (String) — The address. Maximum length is 255.
  - `company[zip]` optional (String) — The zip. Maximum length is 255.
  - `company[city]` optional (String) — The city. Maximum length is 255.
  - `company[country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `company[website_url]` optional (String) — The website url. Maximum length is 255.
  - `company[owner_id]` optional (Fixnum) — The owner id.
  - `company[latitude]` optional (Float) — The latitude.
  - `company[longitude]` optional (Float) — The longitude.
  - `company[siret]` optional (String) — The siret.
  - `company[pro_id]` optional (Fixnum) — The pro id.
  - `company[owner_type]` optional (String) — The owner type.
  - `company[administrative_email]` optional (String) — The administrative email.


## correction_point_historics

### `GET /v2/users/:user_id/correction_point_historics`
Return all the correction point historics of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` required (String) — The user id or slug
  - `sort` optional (enum) — id, user_data_id, scale_team_id, reason, sum, created_at, updated_at, total. The sort field. Sorted by id asc by default. More Example: To sort on correction point historics on the fields updated_at on a descending order and total on a ascending order: ...&sort=-updated_at,total
  - `filter` optional (enum) — id, user_data_id, scale_team_id, reason, sum, created_at, updated_at, total. Filtering on one or more fields More Example: To filter on correction point historics with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_data_id (standard field) scale_team_id (standard field) reason (standard field) sum (standard field) created_at (standard field) updated_at (standard field) total (standard field)
  - `range` optional (enum) — id, user_data_id, scale_team_id, reason, sum, created_at, updated_at, total. Select on a particular range More Example: To range on correction point historics with the total field between min_value and max_value: ...&range[total]=min_value,max_value Rangeable fields: id user_data_id scale_team_id reason sum created_at updated_at total
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## cursus

### `POST /v2/cursus`
Create a cursus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `cursus` optional (Hash) — 
  - `cursus[name]` required (String) — The name. Must be unique.
  - `cursus[kind]` optional (enum) — main, main_deprecated, piscine, piscine_deprecated, piscine_community, test, external, external_deprecated, professional_training, professional_training_deprecated. The kind.
  - `cursus[skill_ids]` optional (n) — array of Integer The skill ids.

### `DELETE /v2/cursus/:id`
Destroy a cursus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/cursus`
Return all the cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, created_at, updated_at, slug, kind, restricted, is_subscriptable. The sort field. Sorted by id desc by default. More Example: To sort on cursus on the fields restricted on a descending order and is_subscriptable on a ascending order: ...&sort=-restricted,is_subscriptable
  - `filter` optional (enum) — id, name, created_at, updated_at, slug, kind, restricted, is_subscriptable. Filtering on one or more fields More Example: To filter on cursus with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field) kind (standard field) restricted (standard field) is_subscriptable (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug, kind, restricted, is_subscriptable. Select on a particular range More Example: To range on cursus with the is_subscriptable field between min_value and max_value: ...&range[is_subscriptable]=min_value,max_value Rangeable fields: id name created_at updated_at slug kind restricted is_subscriptable
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:id`
Get a cursus
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/cursus/:id`
Update a cursus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `cursus` optional (Hash) — 
  - `cursus[name]` optional (String) — The name. Must be unique.
  - `cursus[kind]` optional (enum) — main, main_deprecated, piscine, piscine_deprecated, piscine_community, test, external, external_deprecated, professional_training, professional_training_deprecated. The kind.
  - `cursus[skill_ids]` optional (n) — array of Integer The skill ids.

### `PUT /v2/cursus/:id`
Update a cursus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `cursus` optional (Hash) — 
  - `cursus[name]` optional (String) — The name. Must be unique.
  - `cursus[kind]` optional (enum) — main, main_deprecated, piscine, piscine_deprecated, piscine_community, test, external, external_deprecated, professional_training, professional_training_deprecated. The kind.
  - `cursus[skill_ids]` optional (n) — array of Integer The skill ids.


## cursus_users

### `POST /v2/cursus_users`
Create a cursus user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_user` optional (Hash) — 
  - `cursus_user[cursus_id]` required (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `cursus_user[user_id]` required (Fixnum) — The user id.
  - `cursus_user[end_at]` optional (Fixnum) — The end at… .
  - `cursus_user[begin_at]` required (Fixnum) — The begin at…
  - `cursus_user[has_coalition]` required (enum) — true, false. Is it has coalition ? Default to true.
  - `cursus_user[skip_begin_validation]` optional (String) — The skip begin validation.

### `POST /v2/users/:user_id/cursus_users`
Create a cursus user for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_user` optional (Hash) — 
  - `cursus_user[cursus_id]` required (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `cursus_user[user_id]` required (Fixnum) — The user id.
  - `cursus_user[end_at]` optional (Fixnum) — The end at… .
  - `cursus_user[begin_at]` required (Fixnum) — The begin at…
  - `cursus_user[has_coalition]` required (enum) — true, false. Is it has coalition ? Default to true.
  - `cursus_user[skip_begin_validation]` optional (String) — The skip begin validation.

### `DELETE /v2/cursus_users/:id`
Destroy a cursus user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/cursus_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on cursus users
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on cursus users on the fields blackholed_at on a descending order and level on a ascending order: ...&sort=-blackholed_at,level
  - `filter` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level, active, campus_id, end, future, blackholed. Filtering on one or more fields More Example: To filter on cursus users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) cursus_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) end_at (standard field) begin_at (standard field) has_coalition (standard field) blackholed_at (standard field) level (standard field) active : Only return active cursus_users. Can be one of: true, false campus_id : Return cursus_users with primary campus of user equal to him. end (standard field) future : Return only cursus users which begins in the future. Can be one of: true, false blackholed (standard field)
  - `range` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. Select on a particular range More Example: To range on cursus users with the level field between min_value and max_value: ...&range[level]=min_value,max_value Rangeable fields: id cursus_id user_id created_at updated_at end_at begin_at has_coalition blackholed_at level

### `GET /v2/cursus_users`
Return all the cursus users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on cursus users on the fields blackholed_at on a descending order and level on a ascending order: ...&sort=-blackholed_at,level
  - `filter` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level, active, campus_id, end, future, blackholed. Filtering on one or more fields More Example: To filter on cursus users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) cursus_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) end_at (standard field) begin_at (standard field) has_coalition (standard field) blackholed_at (standard field) level (standard field) active : Only return active cursus_users. Can be one of: true, false campus_id : Return cursus_users with primary campus of user equal to him. end (standard field) future : Return only cursus users which begins in the future. Can be one of: true, false blackholed (standard field)
  - `range` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. Select on a particular range More Example: To range on cursus users with the level field between min_value and max_value: ...&range[level]=min_value,max_value Rangeable fields: id cursus_id user_id created_at updated_at end_at begin_at has_coalition blackholed_at level
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/cursus_users`
Return all the cursus users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on cursus users on the fields blackholed_at on a descending order and level on a ascending order: ...&sort=-blackholed_at,level
  - `filter` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level, active, campus_id, end, future, blackholed. Filtering on one or more fields More Example: To filter on cursus users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) cursus_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) end_at (standard field) begin_at (standard field) has_coalition (standard field) blackholed_at (standard field) level (standard field) active : Only return active cursus_users. Can be one of: true, false campus_id : Return cursus_users with primary campus of user equal to him. end (standard field) future : Return only cursus users which begins in the future. Can be one of: true, false blackholed (standard field)
  - `range` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. Select on a particular range More Example: To range on cursus users with the level field between min_value and max_value: ...&range[level]=min_value,max_value Rangeable fields: id cursus_id user_id created_at updated_at end_at begin_at has_coalition blackholed_at level
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/cursus_users`
Return all the cursus users of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on cursus users on the fields blackholed_at on a descending order and level on a ascending order: ...&sort=-blackholed_at,level
  - `filter` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level, active, campus_id, end, future, blackholed. Filtering on one or more fields More Example: To filter on cursus users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) cursus_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) end_at (standard field) begin_at (standard field) has_coalition (standard field) blackholed_at (standard field) level (standard field) active : Only return active cursus_users. Can be one of: true, false campus_id : Return cursus_users with primary campus of user equal to him. end (standard field) future : Return only cursus users which begins in the future. Can be one of: true, false blackholed (standard field)
  - `range` optional (enum) — id, cursus_id, user_id, created_at, updated_at, end_at, begin_at, has_coalition, blackholed_at, level. Select on a particular range More Example: To range on cursus users with the level field between min_value and max_value: ...&range[level]=min_value,max_value Rangeable fields: id cursus_id user_id created_at updated_at end_at begin_at has_coalition blackholed_at level
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus_users/:id`
Get a cursus user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/cursus_users/:id`
Update a cursus user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `cursus_user` optional (Hash) — 
  - `cursus_user[cursus_id]` optional (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `cursus_user[user_id]` optional (Fixnum) — The user id.
  - `cursus_user[end_at]` optional (Fixnum) — The end at… .
  - `cursus_user[begin_at]` optional (Fixnum) — The begin at…
  - `cursus_user[has_coalition]` optional (enum) — true, false. Is it has coalition ? Default to true.
  - `cursus_user[skip_begin_validation]` optional (String) — The skip begin validation.

### `PUT /v2/cursus_users/:id`
Update a cursus user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `cursus_user` optional (Hash) — 
  - `cursus_user[cursus_id]` optional (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `cursus_user[user_id]` optional (Fixnum) — The user id.
  - `cursus_user[end_at]` optional (Fixnum) — The end at… .
  - `cursus_user[begin_at]` optional (Fixnum) — The begin at…
  - `cursus_user[has_coalition]` optional (enum) — true, false. Is it has coalition ? Default to true.
  - `cursus_user[skip_begin_validation]` optional (String) — The skip begin validation.


## dashes

### `POST /v2/dashes`
Create a dash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `dash` optional (Hash) — 
  - `dash[name]` required (String) — The name. Must be unique in the scope of a given cursus.
  - `dash[description]` required (String) — The description.
  - `dash[slug]` optional (String) — The slug.
  - `dash[cursus_id]` required (Fixnum) — The cursus id.
  - `dash[campus_id]` required (Fixnum) — The campus id.
  - `dash[skill_id]` required (Fixnum) — The skill id.
  - `dash[nbr_xp]` required (String) — The nbr xp.
  - `dash[begin_at]` required (Fixnum) — The begin at. Must be after today.
  - `dash[duration]` required (Fixnum) — The duration.

### `DELETE /v2/dashes/:id`
Destroy a dash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/dashes/graph(/on/:field(/by/:interval))`
Return grouped temporal data on dashes
- **Params:**
  - `field` optional (enum) — created_at, updated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, name, description, cursus_id, skill_id, nbr_xp, slug, begin_at, duration, created_at, updated_at, campus_id. The sort field. Sorted by id desc by default. More Example: To sort on dashes on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, name, description, cursus_id, skill_id, nbr_xp, slug, begin_at, duration, created_at, updated_at, campus_id, future. Filtering on one or more fields More Example: To filter on dashes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) cursus_id (standard field) skill_id (standard field) nbr_xp (standard field) slug (standard field) begin_at (standard field) duration (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) future : Return only dashes which begins in the future. Can be one of: true, false
  - `range` optional (enum) — id, name, description, cursus_id, skill_id, nbr_xp, slug, begin_at, duration, created_at, updated_at, campus_id. Select on a particular range More Example: To range on dashes with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id name description cursus_id skill_id nbr_xp slug begin_at duration created_at updated_at campus_id

### `GET /v2/dashes`
Return all the dashes
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, description, cursus_id, skill_id, nbr_xp, slug, begin_at, duration, created_at, updated_at, campus_id. The sort field. Sorted by id desc by default. More Example: To sort on dashes on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, name, description, cursus_id, skill_id, nbr_xp, slug, begin_at, duration, created_at, updated_at, campus_id, future. Filtering on one or more fields More Example: To filter on dashes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) cursus_id (standard field) skill_id (standard field) nbr_xp (standard field) slug (standard field) begin_at (standard field) duration (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) future : Return only dashes which begins in the future. Can be one of: true, false
  - `range` optional (enum) — id, name, description, cursus_id, skill_id, nbr_xp, slug, begin_at, duration, created_at, updated_at, campus_id. Select on a particular range More Example: To range on dashes with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id name description cursus_id skill_id nbr_xp slug begin_at duration created_at updated_at campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/dashes/:id`
Get a dash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/dashes/:id`
Update a dash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `dash` optional (Hash) — 
  - `dash[name]` optional (String) — The name. Must be unique in the scope of a given cursus.
  - `dash[description]` optional (String) — The description.
  - `dash[slug]` optional (String) — The slug.
  - `dash[cursus_id]` optional (Fixnum) — The cursus id.
  - `dash[campus_id]` optional (Fixnum) — The campus id.
  - `dash[skill_id]` optional (Fixnum) — The skill id.
  - `dash[nbr_xp]` optional (String) — The nbr xp.
  - `dash[begin_at]` optional (Fixnum) — The begin at. Must be after today.
  - `dash[duration]` optional (Fixnum) — The duration.

### `PUT /v2/dashes/:id`
Update a dash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `dash` optional (Hash) — 
  - `dash[name]` optional (String) — The name. Must be unique in the scope of a given cursus.
  - `dash[description]` optional (String) — The description.
  - `dash[slug]` optional (String) — The slug.
  - `dash[cursus_id]` optional (Fixnum) — The cursus id.
  - `dash[campus_id]` optional (Fixnum) — The campus id.
  - `dash[skill_id]` optional (Fixnum) — The skill id.
  - `dash[nbr_xp]` optional (String) — The nbr xp.
  - `dash[begin_at]` optional (Fixnum) — The begin at. Must be after today.
  - `dash[duration]` optional (Fixnum) — The duration.


## dashes_users

### `POST /v2/dashes_users`
Create a dashes user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `dashes_user` optional (Hash) — 
  - `dashes_user[dash_id]` required (Fixnum) — The dash id. Must be unique in the scope of a given user.
  - `dashes_user[user_id]` required (Fixnum) — The user id.
  - `dashes_user[repo_url]` optional (String) — The repo url.
  - `dashes_user[repo_uuid]` optional (String) — The repo uuid.
  - `dashes_user[final_mark]` optional (Fixnum) — The final mark.

### `DELETE /v2/dashes_users/:id`
Destroy a dashes user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/dashes_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on dashes users
- **Params:**
  - `field` optional (enum) — created_at, updated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on dashes users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. Filtering on one or more fields More Example: To filter on dashes users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) dash_id (standard field) user_id (standard field) repo_uuid (standard field) repo_url (standard field) final_mark (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. Select on a particular range More Example: To range on dashes users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id dash_id user_id repo_uuid repo_url final_mark created_at updated_at

### `GET /v2/dashes_users`
Return all the dashes users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `dash_id` optional (String) — The dash id or slug
  - `sort` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on dashes users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. Filtering on one or more fields More Example: To filter on dashes users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) dash_id (standard field) user_id (standard field) repo_uuid (standard field) repo_url (standard field) final_mark (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. Select on a particular range More Example: To range on dashes users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id dash_id user_id repo_uuid repo_url final_mark created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/dashes/:dash_id/dashes_users`
Return all the dashes users of the given Dash
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `dash_id` optional (String) — The dash id or slug
  - `sort` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on dashes users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. Filtering on one or more fields More Example: To filter on dashes users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) dash_id (standard field) user_id (standard field) repo_uuid (standard field) repo_url (standard field) final_mark (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, dash_id, user_id, repo_uuid, repo_url, final_mark, created_at, updated_at. Select on a particular range More Example: To range on dashes users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id dash_id user_id repo_uuid repo_url final_mark created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/dashes_users/:id`
Get a dashes user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/dashes_users/:id`
Update a dashes user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `dashes_user` optional (Hash) — 
  - `dashes_user[dash_id]` optional (Fixnum) — The dash id. Must be unique in the scope of a given user.
  - `dashes_user[user_id]` optional (Fixnum) — The user id.
  - `dashes_user[repo_url]` optional (String) — The repo url.
  - `dashes_user[repo_uuid]` optional (String) — The repo uuid.
  - `dashes_user[final_mark]` optional (Fixnum) — The final mark.

### `PUT /v2/dashes_users/:id`
Update a dashes user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `dashes_user` optional (Hash) — 
  - `dashes_user[dash_id]` optional (Fixnum) — The dash id. Must be unique in the scope of a given user.
  - `dashes_user[user_id]` optional (Fixnum) — The user id.
  - `dashes_user[repo_url]` optional (String) — The repo url.
  - `dashes_user[repo_uuid]` optional (String) — The repo uuid.
  - `dashes_user[final_mark]` optional (Fixnum) — The final mark.


## endpoints

### `POST /v2/endpoints/:id/callback`
Callback for an endpoint
- **Auth/scope:** assignment This action requires one of theses roles: 42network
- **Params:**
  - `url` required (String) — The url of the endpoint
  - `user_id` required (Integer) — The user id
  - `initial_data` required (Hash) — The initial data sent to the endpoint
  - `response_data` required (Hash) — The response data from the endpoint

### `POST /v2/endpoints`
Create an endpoint
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `endpoint` optional (Hash) — 
  - `endpoint[id]` optional (Fixnum) — The id.
  - `endpoint[url]` required (String) — The url.
  - `endpoint[secret]` optional (String) — The secret.
  - `endpoint[description]` optional (String) — The description.
  - `endpoint[created_at]` optional (DateTime) — The created at.
  - `endpoint[updated_at]` optional (DateTime) — The updated at.

### `DELETE /v2/endpoints/:id`
Destroy an endpoint
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/endpoints`
Return all the endpoints
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, url, secret, description, created_at, updated_at, active. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on endpoints on the fields updated_at on a descending order and active on a ascending order: ...&sort=-updated_at,active
  - `filter` optional (enum) — id, url, secret, description, created_at, updated_at, active. Filtering on one or more fields More Example: To filter on endpoints with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) url (standard field) secret (standard field) description (standard field) created_at (standard field) updated_at (standard field) active (standard field)
  - `range` optional (enum) — id, url, secret, description, created_at, updated_at, active. Select on a particular range More Example: To range on endpoints with the active field between min_value and max_value: ...&range[active]=min_value,max_value Rangeable fields: id url secret description created_at updated_at active
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/endpoints/:id`
Get an endpoint
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/endpoints/:id`
Update an endpoint
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `endpoint` optional (Hash) — 
  - `endpoint[id]` optional (Fixnum) — The id.
  - `endpoint[url]` optional (String) — The url.
  - `endpoint[secret]` optional (String) — The secret.
  - `endpoint[description]` optional (String) — The description.
  - `endpoint[created_at]` optional (DateTime) — The created at.
  - `endpoint[updated_at]` optional (DateTime) — The updated at.

### `PUT /v2/endpoints/:id`
Update an endpoint
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `endpoint` optional (Hash) — 
  - `endpoint[id]` optional (Fixnum) — The id.
  - `endpoint[url]` optional (String) — The url.
  - `endpoint[secret]` optional (String) — The secret.
  - `endpoint[description]` optional (String) — The description.
  - `endpoint[created_at]` optional (DateTime) — The created at.
  - `endpoint[updated_at]` optional (DateTime) — The updated at.


## evaluations

### `POST /v2/evaluations`
Create an evaluation
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `evaluation` optional (Hash) — 
  - `evaluation[kind]` optional (enum) — scale, upload. The kind.

### `DELETE /v2/evaluations/:id`
Destroy an evaluation
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/evaluations`
Return all the evaluations
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, position, kind, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on evaluations on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, position, kind, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on evaluations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) position (standard field) kind (standard field) created_at (standard field) updated_at (standard field) campus_id : .
  - `range` optional (enum) — id, position, kind, created_at, updated_at. Select on a particular range More Example: To range on evaluations with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id position kind created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/evaluations/:id`
Get an evaluation
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/evaluations/:id`
Update an evaluation
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `evaluation` optional (Hash) — 
  - `evaluation[kind]` optional (enum) — scale, upload. The kind.

### `PUT /v2/evaluations/:id`
Update an evaluation
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `evaluation` optional (Hash) — 
  - `evaluation[kind]` optional (enum) — scale, upload. The kind.


## events

### `POST /v2/events`
Create an event
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `event` optional (Hash) — 
  - `event[name]` required (String) — The name.
  - `event[begin_at]` required (Fixnum) — The begin at. .
  - `event[end_at]` required (Fixnum) — The end at. . Beginning must be after ending.
  - `event[description]` required (String) — The description.
  - `event[location]` optional (String) — The location. Maximum length is 255.
  - `event[kind]` required (enum) — pedago, rush, piscine, partnership, meet, conference, meet_up, event, association, speed_working, hackathon, workshop, challenge, other, extern. The kind.
  - `event[max_people]` optional (Fixnum) — The max people.
  - `event[prohibition_of_cancellation]` optional (Fixnum) — The prohibition of cancellation.
  - `event[activate_waitlist]` optional (String) — The activate waitlist.
  - `event[events_themes_attributes]` optional (n) — Array of nested elements The events themes attributes.
  - `event[events_themes_attributes][id]` optional (Fixnum) — The id.
  - `event[events_themes_attributes][theme_id]` required (Fixnum) — The theme id. Must be unique in the scope of a given event.
  - `event[events_themes_attributes][_destroy]` optional (String) — The destroy.
  - `event[events_themes_attributes][theme_attributes]` optional (n) — Array of nested elements The theme attributes.
  - `event[events_themes_attributes][theme_attributes][id]` optional (Fixnum) — The id.
  - `event[events_themes_attributes][theme_attributes][name]` required (String) — The name. Must be unique.
  - `event[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `event[campus_ids]` optional (n) — array of Integer The campus ids.

### `DELETE /v2/events/:id`
Destroy an event
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/events/graph(/on/:field(/by/:interval))`
Return grouped temporal data on events
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on events on the fields difficulty on a descending order and remote on a ascending order: ...&sort=-difficulty,remote
  - `filter` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote, future, end. Filtering on one or more fields More Example: To filter on events with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) name (standard field) description (standard field) location (standard field) kind (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) prohibition_of_cancellation (standard field) difficulty (standard field) remote (standard field) future : Return only events which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. Select on a particular range More Example: To range on events with the remote field between min_value and max_value: ...&range[remote]=min_value,max_value Rangeable fields: id begin_at end_at name description location kind max_people created_at updated_at prohibition_of_cancellation difficulty remote

### `GET /v2/cursus/:cursus_id/events`
Return all the events of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on events on the fields difficulty on a descending order and remote on a ascending order: ...&sort=-difficulty,remote
  - `filter` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote, future, end. Filtering on one or more fields More Example: To filter on events with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) name (standard field) description (standard field) location (standard field) kind (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) prohibition_of_cancellation (standard field) difficulty (standard field) remote (standard field) future : Return only events which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. Select on a particular range More Example: To range on events with the remote field between min_value and max_value: ...&range[remote]=min_value,max_value Rangeable fields: id begin_at end_at name description location kind max_people created_at updated_at prohibition_of_cancellation difficulty remote
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/events`
Return all the events of the given Campus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on events on the fields difficulty on a descending order and remote on a ascending order: ...&sort=-difficulty,remote
  - `filter` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote, future, end. Filtering on one or more fields More Example: To filter on events with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) name (standard field) description (standard field) location (standard field) kind (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) prohibition_of_cancellation (standard field) difficulty (standard field) remote (standard field) future : Return only events which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. Select on a particular range More Example: To range on events with the remote field between min_value and max_value: ...&range[remote]=min_value,max_value Rangeable fields: id begin_at end_at name description location kind max_people created_at updated_at prohibition_of_cancellation difficulty remote
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/cursus/:cursus_id/events`
Return all the events of the given Cursus, associated with the given Campus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on events on the fields difficulty on a descending order and remote on a ascending order: ...&sort=-difficulty,remote
  - `filter` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote, future, end. Filtering on one or more fields More Example: To filter on events with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) name (standard field) description (standard field) location (standard field) kind (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) prohibition_of_cancellation (standard field) difficulty (standard field) remote (standard field) future : Return only events which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. Select on a particular range More Example: To range on events with the remote field between min_value and max_value: ...&range[remote]=min_value,max_value Rangeable fields: id begin_at end_at name description location kind max_people created_at updated_at prohibition_of_cancellation difficulty remote
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/events`
Return all the events of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on events on the fields difficulty on a descending order and remote on a ascending order: ...&sort=-difficulty,remote
  - `filter` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote, future, end. Filtering on one or more fields More Example: To filter on events with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) name (standard field) description (standard field) location (standard field) kind (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) prohibition_of_cancellation (standard field) difficulty (standard field) remote (standard field) future : Return only events which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. Select on a particular range More Example: To range on events with the remote field between min_value and max_value: ...&range[remote]=min_value,max_value Rangeable fields: id begin_at end_at name description location kind max_people created_at updated_at prohibition_of_cancellation difficulty remote
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events`
Return all the events
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on events on the fields difficulty on a descending order and remote on a ascending order: ...&sort=-difficulty,remote
  - `filter` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote, future, end. Filtering on one or more fields More Example: To filter on events with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) name (standard field) description (standard field) location (standard field) kind (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) prohibition_of_cancellation (standard field) difficulty (standard field) remote (standard field) future : Return only events which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, name, description, location, kind, max_people, created_at, updated_at, prohibition_of_cancellation, difficulty, remote. Select on a particular range More Example: To range on events with the remote field between min_value and max_value: ...&range[remote]=min_value,max_value Rangeable fields: id begin_at end_at name description location kind max_people created_at updated_at prohibition_of_cancellation difficulty remote
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events/:id`
Get an event
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/events/:id`
Update an event
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `id` required (String) — The requested id
  - `event` optional (Hash) — 
  - `event[name]` optional (String) — The name.
  - `event[begin_at]` optional (Fixnum) — The begin at. .
  - `event[end_at]` optional (Fixnum) — The end at. . Beginning must be after ending.
  - `event[description]` optional (String) — The description.
  - `event[location]` optional (String) — The location. Maximum length is 255.
  - `event[kind]` optional (enum) — pedago, rush, piscine, partnership, meet, conference, meet_up, event, association, speed_working, hackathon, workshop, challenge, other, extern. The kind.
  - `event[max_people]` optional (Fixnum) — The max people.
  - `event[prohibition_of_cancellation]` optional (Fixnum) — The prohibition of cancellation.
  - `event[activate_waitlist]` optional (String) — The activate waitlist.
  - `event[events_themes_attributes]` optional (n) — Array of nested elements The events themes attributes.
  - `event[events_themes_attributes][id]` optional (Fixnum) — The id.
  - `event[events_themes_attributes][theme_id]` optional (Fixnum) — The theme id. Must be unique in the scope of a given event.
  - `event[events_themes_attributes][_destroy]` optional (String) — The destroy.
  - `event[events_themes_attributes][theme_attributes]` optional (n) — Array of nested elements The theme attributes.
  - `event[events_themes_attributes][theme_attributes][id]` optional (Fixnum) — The id.
  - `event[events_themes_attributes][theme_attributes][name]` optional (String) — The name. Must be unique.
  - `event[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `event[campus_ids]` optional (n) — array of Integer The campus ids.

### `PUT /v2/events/:id`
Update an event
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `id` required (String) — The requested id
  - `event` optional (Hash) — 
  - `event[name]` optional (String) — The name.
  - `event[begin_at]` optional (Fixnum) — The begin at. .
  - `event[end_at]` optional (Fixnum) — The end at. . Beginning must be after ending.
  - `event[description]` optional (String) — The description.
  - `event[location]` optional (String) — The location. Maximum length is 255.
  - `event[kind]` optional (enum) — pedago, rush, piscine, partnership, meet, conference, meet_up, event, association, speed_working, hackathon, workshop, challenge, other, extern. The kind.
  - `event[max_people]` optional (Fixnum) — The max people.
  - `event[prohibition_of_cancellation]` optional (Fixnum) — The prohibition of cancellation.
  - `event[activate_waitlist]` optional (String) — The activate waitlist.
  - `event[events_themes_attributes]` optional (n) — Array of nested elements The events themes attributes.
  - `event[events_themes_attributes][id]` optional (Fixnum) — The id.
  - `event[events_themes_attributes][theme_id]` optional (Fixnum) — The theme id. Must be unique in the scope of a given event.
  - `event[events_themes_attributes][_destroy]` optional (String) — The destroy.
  - `event[events_themes_attributes][theme_attributes]` optional (n) — Array of nested elements The theme attributes.
  - `event[events_themes_attributes][theme_attributes][id]` optional (Fixnum) — The id.
  - `event[events_themes_attributes][theme_attributes][name]` optional (String) — The name. Must be unique.
  - `event[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `event[campus_ids]` optional (n) — array of Integer The campus ids.


## events_users

### `POST /v2/events_users`
Create an events user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced staff, Events manager .
- **Params:**
  - `events_user` optional (Hash) — 
  - `events_user[event_id]` required (Fixnum) — The event id.
  - `events_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given event.

### `DELETE /v2/events_users/:id`
Destroy an events user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced staff, Events manager .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/users/:user_id/events_users`
Return all the events users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `event_id` optional (String) — The event id
  - `sort` optional (enum) — id, event_id, user_id, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on events users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, event_id, user_id, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on events users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) event_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id : .
  - `range` optional (enum) — id, event_id, user_id, created_at, updated_at. Select on a particular range More Example: To range on events users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id event_id user_id created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events/:event_id/events_users`
Return all the events users of the given Event
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `event_id` optional (String) — The event id
  - `sort` optional (enum) — id, event_id, user_id, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on events users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, event_id, user_id, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on events users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) event_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id : .
  - `range` optional (enum) — id, event_id, user_id, created_at, updated_at. Select on a particular range More Example: To range on events users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id event_id user_id created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events_users`
Return all the events users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `event_id` optional (String) — The event id
  - `sort` optional (enum) — id, event_id, user_id, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on events users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, event_id, user_id, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on events users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) event_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id : .
  - `range` optional (enum) — id, event_id, user_id, created_at, updated_at. Select on a particular range More Example: To range on events users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id event_id user_id created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events_users/:id`
Get an events user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/events_users/:id`
Update an events user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced staff, Events manager .
- **Params:**
  - `id` required (String) — The requested id
  - `events_user` optional (Hash) — 
  - `events_user[event_id]` optional (Fixnum) — The event id.
  - `events_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given event.

### `PUT /v2/events_users/:id`
Update an events user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced staff, Events manager .
- **Params:**
  - `id` required (String) — The requested id
  - `events_user` optional (Hash) — 
  - `events_user[event_id]` optional (Fixnum) — The event id.
  - `events_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given event.


## exams

### `POST /v2/exams`
Create an exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `exam` optional (Hash) — 
  - `exam[name]` required (String) — The name.
  - `exam[begin_at]` required (Fixnum) — The begin at. .
  - `exam[end_at]` required (Fixnum) — The end at. . Beginning must be after ending.
  - `exam[location]` required (String) — The location.
  - `exam[ip_range]` required (String) — The ip range. Maximum length is 255.
  - `exam[visible]` optional (enum) — true, false. Is it visible ? Default to true.
  - `exam[max_people]` optional (Fixnum) — The max people.
  - `exam[campus_id]` required (Fixnum) — The campus id.
  - `exam[activate_waitlist]` optional (String) — The activate waitlist.
  - `exam[prohibition_of_cancellation]` optional (Fixnum) — The prohibition of cancellation.
  - `exam[project_ids]` optional (n) — array of Integer The project ids.

### `DELETE /v2/exams/:id`
Destroy an exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/exams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on exams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation

### `GET /v2/cursus/:cursus_id/exams`
Return all the exams of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/exams`
Return all the exams of the given Campus
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/cursus/:cursus_id/exams`
Return all the exams of the given Cursus, associated with the given Campus
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/exams`
Return all the exams of the given User
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/exams`
Return all the exams of the given Project
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/exams`
Return all the exams
- **Auth/scope:** This resource is paginated by 30 items This action have additional content with a token resource owner or an application with one of theses role(s): Basic staff .
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on exams on the fields validator_id on a descending order and prohibition_of_cancellation on a ascending order: ...&sort=-validator_id,prohibition_of_cancellation
  - `filter` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation, future, end, validated. Filtering on one or more fields More Example: To filter on exams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) location (standard field) ip_range (standard field) max_people (standard field) created_at (standard field) updated_at (standard field) visible (standard field) name (standard field) campus_id (standard field) validated_at (standard field) validator_id (standard field) prohibition_of_cancellation (standard field) future : Return only exams which begins in the future. Can be one of: true, false end (standard field) validated (standard field)
  - `range` optional (enum) — id, begin_at, end_at, location, ip_range, max_people, created_at, updated_at, visible, name, campus_id, validated_at, validator_id, prohibition_of_cancellation. Select on a particular range More Example: To range on exams with the prohibition_of_cancellation field between min_value and max_value: ...&range[prohibition_of_cancellation]=min_value,max_value Rangeable fields: id begin_at end_at location ip_range max_people created_at updated_at visible name campus_id validated_at validator_id prohibition_of_cancellation
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/exams/:id`
Get an exam
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/exams/:id`
Update an exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `exam` optional (Hash) — 
  - `exam[name]` optional (String) — The name.
  - `exam[begin_at]` optional (Fixnum) — The begin at. .
  - `exam[end_at]` optional (Fixnum) — The end at. . Beginning must be after ending.
  - `exam[location]` optional (String) — The location.
  - `exam[ip_range]` optional (String) — The ip range. Maximum length is 255.
  - `exam[visible]` optional (enum) — true, false. Is it visible ? Default to true.
  - `exam[max_people]` optional (Fixnum) — The max people.
  - `exam[campus_id]` optional (Fixnum) — The campus id.
  - `exam[activate_waitlist]` optional (String) — The activate waitlist.
  - `exam[prohibition_of_cancellation]` optional (Fixnum) — The prohibition of cancellation.
  - `exam[project_ids]` optional (n) — array of Integer The project ids.

### `PUT /v2/exams/:id`
Update an exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `exam` optional (Hash) — 
  - `exam[name]` optional (String) — The name.
  - `exam[begin_at]` optional (Fixnum) — The begin at. .
  - `exam[end_at]` optional (Fixnum) — The end at. . Beginning must be after ending.
  - `exam[location]` optional (String) — The location.
  - `exam[ip_range]` optional (String) — The ip range. Maximum length is 255.
  - `exam[visible]` optional (enum) — true, false. Is it visible ? Default to true.
  - `exam[max_people]` optional (Fixnum) — The max people.
  - `exam[campus_id]` optional (Fixnum) — The campus id.
  - `exam[activate_waitlist]` optional (String) — The activate waitlist.
  - `exam[prohibition_of_cancellation]` optional (Fixnum) — The prohibition of cancellation.
  - `exam[project_ids]` optional (n) — array of Integer The project ids.


## exams_users

### `POST /v2/exams/:exam_id/exams_users`
Create an exams user for the given Exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `exam_id` required (String) — The exam id

### `DELETE /v2/exams/:exam_id/exams_users/:id`
Destroy an exams user for the given Id, associated with the given Exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `exam_id` required (String) — The exam id
  - `id` required (String) — The requested id

### `GET /v2/exams/:exam_id/exams_users`
Return all the exams users of the given Exam
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `exam_id` required (String) — The exam id
  - `sort` optional (enum) — id, exam_id, user_id, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on exams users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, exam_id, user_id, created_at, updated_at. Filtering on one or more fields More Example: To filter on exams users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) exam_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## experiences

### `POST /v2/experiences`
Create an experience
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `experience` optional (Hash) — 
  - `experience[id]` optional (Fixnum) — The id.
  - `experience[user_id]` required (Fixnum) — The user id.
  - `experience[skill_id]` required (Fixnum) — The skill id.
  - `experience[experiancable_id]` required (Fixnum) — The experiancable id.
  - `experience[experiancable_type]` optional (String) — The experiancable type.
  - `experience[experience]` required (Fixnum) — The experience.
  - `experience[created_at]` optional (DateTime) — The created at.
  - `experience[cursus_id]` required (Fixnum) — The cursus id.

### `DELETE /v2/experiences/:id`
Destroy an experience
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/experiences`
Return all the experiences
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `projects_user_id` optional (String) — The projects_user id
  - `user_id` optional (String) — The user id or slug
  - `skill_id` optional (String) — The skill id or slug
  - `partnerships_user_id` optional (String) — The partnerships_user id
  - `sort` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on experiences on the fields cursus_id on a descending order and is_bonus on a ascending order: ...&sort=-cursus_id,is_bonus
  - `filter` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus, campus_id. Filtering on one or more fields More Example: To filter on experiences with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) skill_id (standard field) experiancable_id (standard field) experiancable_type (standard field) experience (standard field) created_at (standard field) cursus_id (standard field) is_bonus (standard field) campus_id : Returns experiences of primary users from the given campus..
  - `range` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. Select on a particular range More Example: To range on experiences with the is_bonus field between min_value and max_value: ...&range[is_bonus]=min_value,max_value Rangeable fields: id user_id skill_id experiancable_id experiancable_type experience created_at cursus_id is_bonus
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/experiences`
Return all the experiences of the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `projects_user_id` optional (String) — The projects_user id
  - `user_id` optional (String) — The user id or slug
  - `skill_id` optional (String) — The skill id or slug
  - `partnerships_user_id` optional (String) — The partnerships_user id
  - `sort` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on experiences on the fields cursus_id on a descending order and is_bonus on a ascending order: ...&sort=-cursus_id,is_bonus
  - `filter` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus, campus_id. Filtering on one or more fields More Example: To filter on experiences with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) skill_id (standard field) experiancable_id (standard field) experiancable_type (standard field) experience (standard field) created_at (standard field) cursus_id (standard field) is_bonus (standard field) campus_id : Returns experiences of primary users from the given campus..
  - `range` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. Select on a particular range More Example: To range on experiences with the is_bonus field between min_value and max_value: ...&range[is_bonus]=min_value,max_value Rangeable fields: id user_id skill_id experiancable_id experiancable_type experience created_at cursus_id is_bonus
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects_users/:projects_user_id/experiences`
Return all the experiences of the given Projects user
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `projects_user_id` optional (String) — The projects_user id
  - `user_id` optional (String) — The user id or slug
  - `skill_id` optional (String) — The skill id or slug
  - `partnerships_user_id` optional (String) — The partnerships_user id
  - `sort` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on experiences on the fields cursus_id on a descending order and is_bonus on a ascending order: ...&sort=-cursus_id,is_bonus
  - `filter` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus, campus_id. Filtering on one or more fields More Example: To filter on experiences with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) skill_id (standard field) experiancable_id (standard field) experiancable_type (standard field) experience (standard field) created_at (standard field) cursus_id (standard field) is_bonus (standard field) campus_id : Returns experiences of primary users from the given campus..
  - `range` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. Select on a particular range More Example: To range on experiences with the is_bonus field between min_value and max_value: ...&range[is_bonus]=min_value,max_value Rangeable fields: id user_id skill_id experiancable_id experiancable_type experience created_at cursus_id is_bonus
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/experiences`
Return all the experiences of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `projects_user_id` optional (String) — The projects_user id
  - `user_id` optional (String) — The user id or slug
  - `skill_id` optional (String) — The skill id or slug
  - `partnerships_user_id` optional (String) — The partnerships_user id
  - `sort` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on experiences on the fields cursus_id on a descending order and is_bonus on a ascending order: ...&sort=-cursus_id,is_bonus
  - `filter` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus, campus_id. Filtering on one or more fields More Example: To filter on experiences with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) skill_id (standard field) experiancable_id (standard field) experiancable_type (standard field) experience (standard field) created_at (standard field) cursus_id (standard field) is_bonus (standard field) campus_id : Returns experiences of primary users from the given campus..
  - `range` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. Select on a particular range More Example: To range on experiences with the is_bonus field between min_value and max_value: ...&range[is_bonus]=min_value,max_value Rangeable fields: id user_id skill_id experiancable_id experiancable_type experience created_at cursus_id is_bonus
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/skills/:skill_id/experiences`
Return all the experiences of the given Skill
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `projects_user_id` optional (String) — The projects_user id
  - `user_id` optional (String) — The user id or slug
  - `skill_id` optional (String) — The skill id or slug
  - `partnerships_user_id` optional (String) — The partnerships_user id
  - `sort` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on experiences on the fields cursus_id on a descending order and is_bonus on a ascending order: ...&sort=-cursus_id,is_bonus
  - `filter` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus, campus_id. Filtering on one or more fields More Example: To filter on experiences with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) skill_id (standard field) experiancable_id (standard field) experiancable_type (standard field) experience (standard field) created_at (standard field) cursus_id (standard field) is_bonus (standard field) campus_id : Returns experiences of primary users from the given campus..
  - `range` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. Select on a particular range More Example: To range on experiences with the is_bonus field between min_value and max_value: ...&range[is_bonus]=min_value,max_value Rangeable fields: id user_id skill_id experiancable_id experiancable_type experience created_at cursus_id is_bonus
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/partnerships_users/:partnerships_user_id/experiences`
Return all the experiences of the given Partnerships user
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `projects_user_id` optional (String) — The projects_user id
  - `user_id` optional (String) — The user id or slug
  - `skill_id` optional (String) — The skill id or slug
  - `partnerships_user_id` optional (String) — The partnerships_user id
  - `sort` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on experiences on the fields cursus_id on a descending order and is_bonus on a ascending order: ...&sort=-cursus_id,is_bonus
  - `filter` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus, campus_id. Filtering on one or more fields More Example: To filter on experiences with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) skill_id (standard field) experiancable_id (standard field) experiancable_type (standard field) experience (standard field) created_at (standard field) cursus_id (standard field) is_bonus (standard field) campus_id : Returns experiences of primary users from the given campus..
  - `range` optional (enum) — id, user_id, skill_id, experiancable_id, experiancable_type, experience, created_at, cursus_id, is_bonus. Select on a particular range More Example: To range on experiences with the is_bonus field between min_value and max_value: ...&range[is_bonus]=min_value,max_value Rangeable fields: id user_id skill_id experiancable_id experiancable_type experience created_at cursus_id is_bonus
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/experiences/:id`
Get an experience
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/experiences/:id`
Update an experience
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `experience` optional (Hash) — 
  - `experience[id]` optional (Fixnum) — The id.
  - `experience[user_id]` optional (Fixnum) — The user id.
  - `experience[skill_id]` optional (Fixnum) — The skill id.
  - `experience[experiancable_id]` optional (Fixnum) — The experiancable id.
  - `experience[experiancable_type]` optional (String) — The experiancable type.
  - `experience[experience]` optional (Fixnum) — The experience.
  - `experience[created_at]` optional (DateTime) — The created at.
  - `experience[cursus_id]` optional (Fixnum) — The cursus id.

### `PUT /v2/experiences/:id`
Update an experience
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `experience` optional (Hash) — 
  - `experience[id]` optional (Fixnum) — The id.
  - `experience[user_id]` optional (Fixnum) — The user id.
  - `experience[skill_id]` optional (Fixnum) — The skill id.
  - `experience[experiancable_id]` optional (Fixnum) — The experiancable id.
  - `experience[experiancable_type]` optional (String) — The experiancable type.
  - `experience[experience]` optional (Fixnum) — The experience.
  - `experience[created_at]` optional (DateTime) — The created at.
  - `experience[cursus_id]` optional (Fixnum) — The cursus id.


## expertises

### `POST /v2/expertises`
Create an expertise
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `expertise` optional (Hash) — 
  - `expertise[name]` required (String) — The name. Must be unique.
  - `expertise[slug]` required (String) — The slug.
  - `expertise[kind]` required (enum) — languages, frameworks, databases, admin_sys, other. The kind.

### `DELETE /v2/expertises/:id`
Destroy an expertise
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/expertises`
Return all the expertises
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, slug, created_at, updated_at, kind. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on expertises on the fields updated_at on a descending order and kind on a ascending order: ...&sort=-updated_at,kind
  - `filter` optional (enum) — id, name, slug, created_at, updated_at, kind. Filtering on one or more fields More Example: To filter on expertises with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) slug (standard field) created_at (standard field) updated_at (standard field) kind (standard field)
  - `range` optional (enum) — id, name, slug, created_at, updated_at, kind. Select on a particular range More Example: To range on expertises with the kind field between min_value and max_value: ...&range[kind]=min_value,max_value Rangeable fields: id name slug created_at updated_at kind
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/expertises/:id`
Get an expertise
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/expertises/:id`
Update an expertise
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `expertise` optional (Hash) — 
  - `expertise[name]` optional (String) — The name. Must be unique.
  - `expertise[slug]` optional (String) — The slug.
  - `expertise[kind]` optional (enum) — languages, frameworks, databases, admin_sys, other. The kind.

### `PUT /v2/expertises/:id`
Update an expertise
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `expertise` optional (Hash) — 
  - `expertise[name]` optional (String) — The name. Must be unique.
  - `expertise[slug]` optional (String) — The slug.
  - `expertise[kind]` optional (enum) — languages, frameworks, databases, admin_sys, other. The kind.


## expertises_users

### `POST /v2/expertises/:expertise_id/expertises_users`
Create an expertises user for the given Expertise
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `expertise_id` optional (String) — The expertise id or slug
  - `user_id` optional (String) — The user id or slug
  - `expertises_user` optional (Hash) — 
  - `expertises_user[expertise_id]` required (Fixnum) — The expertise id. Must be unique in the scope of a given user.
  - `expertises_user[user_id]` required (Fixnum) — The user id.
  - `expertises_user[interested]` optional (enum) — true, false. Is it interested ? Default to false.
  - `expertises_user[value]` required (Fixnum) — The value.
  - `expertises_user[contact_me]` optional (enum) — true, false. Is it contact me ? Default to false.

### `POST /v2/users/:user_id/expertises_users`
Create an expertises user for the given User
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `expertise_id` optional (String) — The expertise id or slug
  - `user_id` optional (String) — The user id or slug
  - `expertises_user` optional (Hash) — 
  - `expertises_user[expertise_id]` required (Fixnum) — The expertise id. Must be unique in the scope of a given user.
  - `expertises_user[user_id]` required (Fixnum) — The user id.
  - `expertises_user[interested]` optional (enum) — true, false. Is it interested ? Default to false.
  - `expertises_user[value]` required (Fixnum) — The value.
  - `expertises_user[contact_me]` optional (enum) — true, false. Is it contact me ? Default to false.

### `POST /v2/expertises_users`
Create an expertises user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `expertise_id` optional (String) — The expertise id or slug
  - `user_id` optional (String) — The user id or slug
  - `expertises_user` optional (Hash) — 
  - `expertises_user[expertise_id]` required (Fixnum) — The expertise id. Must be unique in the scope of a given user.
  - `expertises_user[user_id]` required (Fixnum) — The user id.
  - `expertises_user[interested]` optional (enum) — true, false. Is it interested ? Default to false.
  - `expertises_user[value]` required (Fixnum) — The value.
  - `expertises_user[contact_me]` optional (enum) — true, false. Is it contact me ? Default to false.

### `DELETE /v2/expertises_users/:id`
Destroy an expertises user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/expertises/:expertise_id/expertises_users`
Return all the expertises users of the given Expertise
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `expertise_id` optional (String) — The expertise id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. The sort field. Sorted by id desc by default. More Example: To sort on expertises users on the fields updated_at on a descending order and contact_me on a ascending order: ...&sort=-updated_at,contact_me
  - `filter` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. Filtering on one or more fields More Example: To filter on expertises users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) expertise_id (standard field) user_id (standard field) interested (standard field) value (standard field) created_at (standard field) updated_at (standard field) contact_me (standard field)
  - `range` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. Select on a particular range More Example: To range on expertises users with the contact_me field between min_value and max_value: ...&range[contact_me]=min_value,max_value Rangeable fields: id expertise_id user_id interested value created_at updated_at contact_me
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/expertises_users`
Return all the expertises users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `expertise_id` optional (String) — The expertise id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. The sort field. Sorted by id desc by default. More Example: To sort on expertises users on the fields updated_at on a descending order and contact_me on a ascending order: ...&sort=-updated_at,contact_me
  - `filter` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. Filtering on one or more fields More Example: To filter on expertises users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) expertise_id (standard field) user_id (standard field) interested (standard field) value (standard field) created_at (standard field) updated_at (standard field) contact_me (standard field)
  - `range` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. Select on a particular range More Example: To range on expertises users with the contact_me field between min_value and max_value: ...&range[contact_me]=min_value,max_value Rangeable fields: id expertise_id user_id interested value created_at updated_at contact_me
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/expertises_users`
Return all the expertises users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `expertise_id` optional (String) — The expertise id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. The sort field. Sorted by id desc by default. More Example: To sort on expertises users on the fields updated_at on a descending order and contact_me on a ascending order: ...&sort=-updated_at,contact_me
  - `filter` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. Filtering on one or more fields More Example: To filter on expertises users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) expertise_id (standard field) user_id (standard field) interested (standard field) value (standard field) created_at (standard field) updated_at (standard field) contact_me (standard field)
  - `range` optional (enum) — id, expertise_id, user_id, interested, value, created_at, updated_at, contact_me. Select on a particular range More Example: To range on expertises users with the contact_me field between min_value and max_value: ...&range[contact_me]=min_value,max_value Rangeable fields: id expertise_id user_id interested value created_at updated_at contact_me
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/expertises_users/:id`
Get an expertises user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/expertises_users/:id`
Update an expertises user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id
  - `expertises_user` optional (Hash) — 
  - `expertises_user[expertise_id]` optional (Fixnum) — The expertise id. Must be unique in the scope of a given user.
  - `expertises_user[user_id]` optional (Fixnum) — The user id.
  - `expertises_user[interested]` optional (enum) — true, false. Is it interested ? Default to false.
  - `expertises_user[value]` optional (Fixnum) — The value.
  - `expertises_user[contact_me]` optional (enum) — true, false. Is it contact me ? Default to false.

### `PUT /v2/expertises_users/:id`
Update an expertises user
- **Auth/scope:** This action requires a token resource owner scoped on profile with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id
  - `expertises_user` optional (Hash) — 
  - `expertises_user[expertise_id]` optional (Fixnum) — The expertise id. Must be unique in the scope of a given user.
  - `expertises_user[user_id]` optional (Fixnum) — The user id.
  - `expertises_user[interested]` optional (enum) — true, false. Is it interested ? Default to false.
  - `expertises_user[value]` optional (Fixnum) — The value.
  - `expertises_user[contact_me]` optional (enum) — true, false. Is it contact me ? Default to false.


## feedbacks

### `POST /v2/events/:event_id/feedbacks`
Create a feedback for the given Event
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` required (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` required (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` required (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `POST /v2/feedbacks`
Create a feedback
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` required (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` required (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` required (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `POST /v2/scale_teams/:scale_team_id/feedbacks`
Create a feedback for the given Scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` required (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` required (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` required (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/events/:event_id/feedbacks/:id`
Destroy a feedback for the given Id, associated with the given Event
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id

### `DELETE /v2/feedbacks/:id`
Destroy a feedback
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id

### `DELETE /v2/scale_teams/:scale_team_id/feedbacks/:id`
Destroy a feedback for the given Id, associated with the given Scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id

### `GET /v2/events/:event_id/feedbacks`
Return all the feedbacks of the given Event
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `event_id` optional (String) — The event id
  - `scale_team_id` optional (String) — The scale_team id
  - `sort` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on feedbacks on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on feedbacks with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) feedbackable_type (standard field) feedbackable_id (standard field) comment (standard field) rating (standard field) created_at (standard field) updated_at (standard field) campus_id : Only return feedbacks of specific campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78
  - `range` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at. Select on a particular range More Example: To range on feedbacks with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id feedbackable_type feedbackable_id comment rating created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/feedbacks`
Return all the feedbacks
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `event_id` optional (String) — The event id
  - `scale_team_id` optional (String) — The scale_team id
  - `sort` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on feedbacks on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on feedbacks with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) feedbackable_type (standard field) feedbackable_id (standard field) comment (standard field) rating (standard field) created_at (standard field) updated_at (standard field) campus_id : Only return feedbacks of specific campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78
  - `range` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at. Select on a particular range More Example: To range on feedbacks with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id feedbackable_type feedbackable_id comment rating created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/scale_teams/:scale_team_id/feedbacks`
Return all the feedbacks of the given Scale team
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `event_id` optional (String) — The event id
  - `scale_team_id` optional (String) — The scale_team id
  - `sort` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on feedbacks on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at, campus_id. Filtering on one or more fields More Example: To filter on feedbacks with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) feedbackable_type (standard field) feedbackable_id (standard field) comment (standard field) rating (standard field) created_at (standard field) updated_at (standard field) campus_id : Only return feedbacks of specific campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78
  - `range` optional (enum) — id, user_id, feedbackable_type, feedbackable_id, comment, rating, created_at, updated_at. Select on a particular range More Example: To range on feedbacks with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id feedbackable_type feedbackable_id comment rating created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events/:event_id/feedbacks/:id`
Get a feedback of the given Id, associated with the given Event
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id

### `GET /v2/feedbacks/:id`
Get a feedback
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id

### `GET /v2/scale_teams/:scale_team_id/feedbacks/:id`
Get a feedback of the given Id, associated with the given Scale team
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id

### `PATCH /v2/events/:event_id/feedbacks/:id`
Update a feedback for the given Id, associated with the given Event
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` optional (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` optional (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` optional (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/events/:event_id/feedbacks/:id`
Update a feedback for the given Id, associated with the given Event
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` optional (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` optional (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` optional (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `PATCH /v2/feedbacks/:id`
Update a feedback
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` optional (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` optional (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` optional (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/feedbacks/:id`
Update a feedback
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` optional (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` optional (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` optional (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `PATCH /v2/scale_teams/:scale_team_id/feedbacks/:id`
Update a feedback for the given Id, associated with the given Scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` optional (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` optional (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` optional (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/scale_teams/:scale_team_id/feedbacks/:id`
Update a feedback for the given Id, associated with the given Scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Basic staff .
- **Params:**
  - `event_id` optional (String) — The event id
  - `id` required (String) — The requested id
  - `scale_team_id` optional (String) — The scale_team id
  - `feedback` optional (Hash) — 
  - `feedback[comment]` optional (String) — The comment. Maximum length is 1024.
  - `feedback[feedbackable_type]` optional (String) — The feedbackable type.
  - `feedback[feedbackable_id]` optional (Fixnum) — The feedbackable id.
  - `feedback[rating]` optional (Fixnum) — The rating.
  - `feedback[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given feedbackable.
  - `feedback[feedback_details_attributes]` optional (n) — Array of nested elements The feedback details attributes.
  - `feedback[feedback_details_attributes][id]` optional (Fixnum) — The id.
  - `feedback[feedback_details_attributes][rate]` optional (Fixnum) — The rate.
  - `feedback[feedback_details_attributes][kind]` optional (enum) — punctuality, interested, rigorous, nice, accuracy, interesting, quality, pertinent. The kind.
  - `feedback[feedback_details_attributes][_destroy]` optional (String) — The destroy.


## flags

### `GET /v2/flags`
Return all the flags
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, positive, icon, created_at, updated_at. The sort field. Sorted by name asc, id desc by default. More Example: To sort on flags on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, name, positive, icon, created_at, updated_at. Filtering on one or more fields More Example: To filter on flags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) positive (standard field) icon (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, name, positive, icon, created_at, updated_at. Select on a particular range More Example: To range on flags with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id name positive icon created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## flash_users

### `POST /v2/flashes/:flash_id/flash_users`
Create a flash user for the given Flash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `flash_id` optional (String) — The flash id
  - `flash_user` optional (Hash) — 
  - `flash_user[user_id]` required (Fixnum) — The user id.
  - `flash_user[flash_id]` required (Fixnum) — The flash id.
  - `flash_user[seen]` optional (enum) — true, false. Is it seen ? Default to false.
  - `flash_user[end_at]` optional (DateTime) — The end at.

### `POST /v2/flash_users`
Create a flash user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `flash_id` optional (String) — The flash id
  - `flash_user` optional (Hash) — 
  - `flash_user[user_id]` required (Fixnum) — The user id.
  - `flash_user[flash_id]` required (Fixnum) — The flash id.
  - `flash_user[seen]` optional (enum) — true, false. Is it seen ? Default to false.
  - `flash_user[end_at]` optional (DateTime) — The end at.

### `GET /v2/flashes/:flash_id/flash_users`
Return all the flash users of the given Flash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `flash_id` optional (String) — The flash id
  - `sort` optional (enum) — id, user_id, flash_id, seen, created_at, updated_at, end_at. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on flash users on the fields updated_at on a descending order and end_at on a ascending order: ...&sort=-updated_at,end_at
  - `filter` optional (enum) — id, user_id, flash_id, seen, created_at, updated_at, end_at, end. Filtering on one or more fields More Example: To filter on flash users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) flash_id (standard field) seen (standard field) created_at (standard field) updated_at (standard field) end_at (standard field) end (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/flash_users`
Return all the flash users
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `flash_id` optional (String) — The flash id
  - `sort` optional (enum) — id, user_id, flash_id, seen, created_at, updated_at, end_at. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on flash users on the fields updated_at on a descending order and end_at on a ascending order: ...&sort=-updated_at,end_at
  - `filter` optional (enum) — id, user_id, flash_id, seen, created_at, updated_at, end_at, end. Filtering on one or more fields More Example: To filter on flash users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) flash_id (standard field) seen (standard field) created_at (standard field) updated_at (standard field) end_at (standard field) end (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/flashes/:flash_id/flash_users/:id`
Get a flash user of the given Id, associated with the given Flash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `flash_id` optional (String) — The flash id
  - `id` required (String) — The requested id

### `GET /v2/flash_users/:id`
Get a flash user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `flash_id` optional (String) — The flash id
  - `id` required (String) — The requested id


## flashes

### `POST /v2/flashes`
Create a flash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `flash` optional (Hash) — 
  - `flash[content]` required (String) — The content.
  - `flash[selector]` optional (String) — The selector.
  - `flash[identifier]` required (String) — The identifier.
  - `flash[title]` required (String) — The title.
  - `flash[url]` optional (String) — The url.
  - `flash[duration]` required (Fixnum) — The duration.

### `GET /v2/flashes`
Return all the flashes
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, content, selector, created_at, updated_at, identifier, title, url, duration. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on flashes on the fields url on a descending order and duration on a ascending order: ...&sort=-url,duration
  - `filter` optional (enum) — id, content, selector, created_at, updated_at, identifier, title, url, duration. Filtering on one or more fields More Example: To filter on flashes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) content (standard field) selector (standard field) created_at (standard field) updated_at (standard field) identifier (standard field) title (standard field) url (standard field) duration (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/flashes/:id`
Get a flash
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id


## gitlab_users

### `GET /v2/users/:user_id/gitlab_users`
Return all the gitlab users of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `user_id` required (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, public_key, created_at, updated_at, name, fingerprint. The sort field. Sorted by id asc by default. More Example: To sort on gitlab users on the fields name on a descending order and fingerprint on a ascending order: ...&sort=-name,fingerprint
  - `filter` optional (enum) — id, user_id, public_key, created_at, updated_at, name, fingerprint. Filtering on one or more fields More Example: To filter on gitlab users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) public_key (standard field) created_at (standard field) updated_at (standard field) name (standard field) fingerprint (standard field)
  - `range` optional (enum) — id, user_id, public_key, created_at, updated_at, name, fingerprint. Select on a particular range More Example: To range on gitlab users with the fingerprint field between min_value and max_value: ...&range[fingerprint]=min_value,max_value Rangeable fields: id user_id public_key created_at updated_at name fingerprint
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## groups

### `POST /v2/groups`
Create a group
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `group` optional (Hash) — 
  - `group[name]` required (String) — The name.
  - `group[color]` required (String) — The color.
  - `group[kind]` optional (enum) — important, normal, hidden. The kind. Default to important.

### `DELETE /v2/groups/:id`
Destroy a group
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/groups`
Return all the groups
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/groups`
Return all the groups of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/groups/:id`
Get a group
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/groups/:id`
Update a group
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `group` optional (Hash) — 
  - `group[name]` optional (String) — The name.
  - `group[color]` optional (String) — The color.
  - `group[kind]` optional (enum) — important, normal, hidden. The kind. Default to important.

### `PUT /v2/groups/:id`
Update a group
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `group` optional (Hash) — 
  - `group[name]` optional (String) — The name.
  - `group[color]` optional (String) — The color.
  - `group[kind]` optional (enum) — important, normal, hidden. The kind. Default to important.


## groups_users

### `POST /v2/groups_users`
Create a groups user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `groups_user` optional (Hash) — 
  - `groups_user[group_id]` required (Fixnum) — The group id. Must be unique in the scope of a given user.
  - `groups_user[user_id]` required (Fixnum) — The user id.

### `DELETE /v2/groups_users/:id`
Destroy a groups user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/groups_users`
Return all the groups users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `group_id` optional (String) — The group id
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/groups/:group_id/groups_users`
Return all the groups users of the given Group
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `group_id` optional (String) — The group id
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/groups_users`
Return all the groups users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `group_id` optional (String) — The group id
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/groups_users/:id`
Get a groups user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/groups_users/:id`
Update a groups user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `groups_user` optional (Hash) — 
  - `groups_user[group_id]` optional (Fixnum) — The group id. Must be unique in the scope of a given user.
  - `groups_user[user_id]` optional (Fixnum) — The user id.

### `PUT /v2/groups_users/:id`
Update a groups user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `groups_user` optional (Hash) — 
  - `groups_user[group_id]` optional (Fixnum) — The group id. Must be unique in the scope of a given user.
  - `groups_user[user_id]` optional (Fixnum) — The user id.


## internships

### `POST /v2/internships`
Create an internship
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `internship` optional (Hash) — 
  - `internship[user_id]` optional (Fixnum) — The user id.
  - `internship[administration_id]` required (Fixnum) — The administration id.
  - `internship[offer_id]` optional (Fixnum) — The offer id.
  - `internship[language_id]` required (Fixnum) — The language id.
  - `internship[state]` optional (enum) — none, need_validation, invalidated, generated, uploaded, ended, broke, canceled. The state.
  - `internship[days]` required (String) — The days.
  - `internship[user_address]` required (String) — The user address.
  - `internship[user_postal]` required (String) — The user postal.
  - `internship[user_city]` required (String) — The user city.
  - `internship[user_country]` required (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The user country.
  - `internship[company_name]` required (String) — The company name.
  - `internship[company_boss_user_first_name]` required (String) — The company boss user first name.
  - `internship[company_boss_user_last_name]` required (String) — The company boss user last name.
  - `internship[company_boss_user_email]` required (String) — The company boss user email.
  - `internship[company_boss_user_phone]` required (String) — The company boss user phone.
  - `internship[company_user_first_name]` required (String) — The company user first name.
  - `internship[company_user_last_name]` required (String) — The company user last name.
  - `internship[company_user_post]` required (String) — The company user post.
  - `internship[company_user_email]` required (String) — The company user email.
  - `internship[company_user_phone]` required (String) — The company user phone.
  - `internship[company_address]` required (String) — The company address.
  - `internship[company_postal]` required (String) — The company postal.
  - `internship[company_city]` required (String) — The company city.
  - `internship[company_country]` required (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The company country.
  - `internship[company_siret]` required (String) — The company siret.
  - `internship[internship_address]` required (String) — The internship address.
  - `internship[internship_postal]` required (String) — The internship postal.
  - `internship[internship_city]` required (String) — The internship city.
  - `internship[internship_country]` required (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The internship country.
  - `internship[contract_type]` required (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `internship[subject]` required (String) — The subject. Maximum length is 280. Allow blank length is true. Allow nil length is true.
  - `internship[start_at]` required (Fixnum) — The start at…
  - `internship[end_at]` required (DateTime) — The end at.
  - `internship[duration]` required (Fixnum) — The duration.
  - `internship[nb_days]` optional (Fixnum) — The nb days.
  - `internship[nb_hours]` required (Fixnum) — The nb hours.
  - `internship[movement]` optional (String) — The movement.
  - `internship[salary]` required (Fixnum) — The salary.
  - `internship[currency]` required (enum) — eur, aed, dol, chf, rub, zar, gbp, yen, can, mad, krw, thb, try, amd, mur, myr, pln, czk. The currency.
  - `internship[breach_at]` optional (DateTime) — The breach at.
  - `internship[convention]` optional (File) — The convention.
  - `internship[anti_grav_units_user_id]` optional (Fixnum) — The anti grav units user id.

### `DELETE /v2/internships/:id`
Destroy an internship
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `internship` optional (Hash) — 
  - `internship[user_id]` optional (Fixnum) — The user id.
  - `internship[administration_id]` optional (Fixnum) — The administration id.
  - `internship[offer_id]` optional (Fixnum) — The offer id.
  - `internship[language_id]` optional (Fixnum) — The language id.
  - `internship[state]` optional (enum) — none, need_validation, invalidated, generated, uploaded, ended, broke, canceled. The state.
  - `internship[days]` optional (String) — The days.
  - `internship[user_address]` optional (String) — The user address.
  - `internship[user_postal]` optional (String) — The user postal.
  - `internship[user_city]` optional (String) — The user city.
  - `internship[user_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The user country.
  - `internship[company_name]` optional (String) — The company name.
  - `internship[company_boss_user_first_name]` optional (String) — The company boss user first name.
  - `internship[company_boss_user_last_name]` optional (String) — The company boss user last name.
  - `internship[company_boss_user_email]` optional (String) — The company boss user email.
  - `internship[company_boss_user_phone]` optional (String) — The company boss user phone.
  - `internship[company_user_first_name]` optional (String) — The company user first name.
  - `internship[company_user_last_name]` optional (String) — The company user last name.
  - `internship[company_user_post]` optional (String) — The company user post.
  - `internship[company_user_email]` optional (String) — The company user email.
  - `internship[company_user_phone]` optional (String) — The company user phone.
  - `internship[company_address]` optional (String) — The company address.
  - `internship[company_postal]` optional (String) — The company postal.
  - `internship[company_city]` optional (String) — The company city.
  - `internship[company_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The company country.
  - `internship[company_siret]` optional (String) — The company siret.
  - `internship[internship_address]` optional (String) — The internship address.
  - `internship[internship_postal]` optional (String) — The internship postal.
  - `internship[internship_city]` optional (String) — The internship city.
  - `internship[internship_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The internship country.
  - `internship[contract_type]` optional (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `internship[subject]` optional (String) — The subject. Maximum length is 280. Allow blank length is true. Allow nil length is true.
  - `internship[start_at]` optional (Fixnum) — The start at…
  - `internship[end_at]` optional (DateTime) — The end at.
  - `internship[duration]` optional (Fixnum) — The duration.
  - `internship[nb_days]` optional (Fixnum) — The nb days.
  - `internship[nb_hours]` optional (Fixnum) — The nb hours.
  - `internship[movement]` optional (String) — The movement.
  - `internship[salary]` optional (Fixnum) — The salary.
  - `internship[currency]` optional (enum) — eur, aed, dol, chf, rub, zar, gbp, yen, can, mad, krw, thb, try, amd, mur, myr, pln, czk. The currency.
  - `internship[breach_at]` optional (DateTime) — The breach at.
  - `internship[convention]` optional (File) — The convention.
  - `internship[anti_grav_units_user_id]` optional (Fixnum) — The anti grav units user id.

### `GET /v2/internships`
Return all the internships
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, administration_id, offer_id, language_id, state, days, user_address, user_postal, user_city, user_country, company_name, company_boss_user_first_name, company_boss_user_last_name, company_boss_user_email, company_boss_user_phone, company_user_first_name, company_user_last_name, company_user_post, company_user_email, company_user_phone, company_address, company_postal, company_city, company_country, company_siret, internship_address, internship_postal, internship_city, internship_country, contract_type, subject, start_at, end_at, duration, nb_days, nb_hours, movement, salary, currency, breach_at, convention, created_at, updated_at, anti_grav_units_user_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on internships on the fields updated_at on a descending order and anti_grav_units_user_id on a ascending order: ...&sort=-updated_at,anti_grav_units_user_id
  - `filter` optional (enum) — id, user_id, administration_id, offer_id, language_id, state, days, user_address, user_postal, user_city, user_country, company_name, company_boss_user_first_name, company_boss_user_last_name, company_boss_user_email, company_boss_user_phone, company_user_first_name, company_user_last_name, company_user_post, company_user_email, company_user_phone, company_address, company_postal, company_city, company_country, company_siret, internship_address, internship_postal, internship_city, internship_country, contract_type, subject, start_at, end_at, duration, nb_days, nb_hours, movement, salary, currency, breach_at, convention, created_at, updated_at, anti_grav_units_user_id, start, end, breach. Filtering on one or more fields More Example: To filter on internships with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) administration_id (standard field) offer_id (standard field) language_id (standard field) state (standard field) days (standard field) user_address (standard field) user_postal (standard field) user_city (standard field) user_country (standard field) company_name (standard field) company_boss_user_first_name (standard field) company_boss_user_last_name (standard field) company_boss_user_email (standard field) company_boss_user_phone (standard field) company_user_first_name (standard field) company_user_last_name (standard field) company_user_post (standard field) company_user_email (standard field) company_user_phone (standard field) company_address (standard field) company_postal (standard field) company_city (standard field) company_country (standard field) company_siret (standard field) internship_address (standard field) internship_postal (standard field) internship_city (standard field) internship_country (standard field) contract_type (standard field) subject (standard field) start_at (standard field) end_at (standard field) duration (standard field) nb_days (standard field) nb_hours (standard field) movement (standard field) salary (standard field) currency (standard field) breach_at (standard field) convention (standard field) created_at (standard field) updated_at (standard field) anti_grav_units_user_id (standard field) start (standard field) end (standard field) breach (standard field)
  - `range` optional (enum) — id, user_id, administration_id, offer_id, language_id, state, days, user_address, user_postal, user_city, user_country, company_name, company_boss_user_first_name, company_boss_user_last_name, company_boss_user_email, company_boss_user_phone, company_user_first_name, company_user_last_name, company_user_post, company_user_email, company_user_phone, company_address, company_postal, company_city, company_country, company_siret, internship_address, internship_postal, internship_city, internship_country, contract_type, subject, start_at, end_at, duration, nb_days, nb_hours, movement, salary, currency, breach_at, convention, created_at, updated_at, anti_grav_units_user_id. Select on a particular range More Example: To range on internships with the anti_grav_units_user_id field between min_value and max_value: ...&range[anti_grav_units_user_id]=min_value,max_value Rangeable fields: id user_id administration_id offer_id language_id state days user_address user_postal user_city user_country company_name company_boss_user_first_name company_boss_user_last_name company_boss_user_email company_boss_user_phone company_user_first_name company_user_last_name company_user_post company_user_email company_user_phone company_address company_postal company_city company_country company_siret internship_address internship_postal internship_city internship_country contract_type subject start_at end_at duration nb_days nb_hours movement salary currency breach_at convention created_at updated_at anti_grav_units_user_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/internships`
Return all the internships of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, administration_id, offer_id, language_id, state, days, user_address, user_postal, user_city, user_country, company_name, company_boss_user_first_name, company_boss_user_last_name, company_boss_user_email, company_boss_user_phone, company_user_first_name, company_user_last_name, company_user_post, company_user_email, company_user_phone, company_address, company_postal, company_city, company_country, company_siret, internship_address, internship_postal, internship_city, internship_country, contract_type, subject, start_at, end_at, duration, nb_days, nb_hours, movement, salary, currency, breach_at, convention, created_at, updated_at, anti_grav_units_user_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on internships on the fields updated_at on a descending order and anti_grav_units_user_id on a ascending order: ...&sort=-updated_at,anti_grav_units_user_id
  - `filter` optional (enum) — id, user_id, administration_id, offer_id, language_id, state, days, user_address, user_postal, user_city, user_country, company_name, company_boss_user_first_name, company_boss_user_last_name, company_boss_user_email, company_boss_user_phone, company_user_first_name, company_user_last_name, company_user_post, company_user_email, company_user_phone, company_address, company_postal, company_city, company_country, company_siret, internship_address, internship_postal, internship_city, internship_country, contract_type, subject, start_at, end_at, duration, nb_days, nb_hours, movement, salary, currency, breach_at, convention, created_at, updated_at, anti_grav_units_user_id, start, end, breach. Filtering on one or more fields More Example: To filter on internships with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) administration_id (standard field) offer_id (standard field) language_id (standard field) state (standard field) days (standard field) user_address (standard field) user_postal (standard field) user_city (standard field) user_country (standard field) company_name (standard field) company_boss_user_first_name (standard field) company_boss_user_last_name (standard field) company_boss_user_email (standard field) company_boss_user_phone (standard field) company_user_first_name (standard field) company_user_last_name (standard field) company_user_post (standard field) company_user_email (standard field) company_user_phone (standard field) company_address (standard field) company_postal (standard field) company_city (standard field) company_country (standard field) company_siret (standard field) internship_address (standard field) internship_postal (standard field) internship_city (standard field) internship_country (standard field) contract_type (standard field) subject (standard field) start_at (standard field) end_at (standard field) duration (standard field) nb_days (standard field) nb_hours (standard field) movement (standard field) salary (standard field) currency (standard field) breach_at (standard field) convention (standard field) created_at (standard field) updated_at (standard field) anti_grav_units_user_id (standard field) start (standard field) end (standard field) breach (standard field)
  - `range` optional (enum) — id, user_id, administration_id, offer_id, language_id, state, days, user_address, user_postal, user_city, user_country, company_name, company_boss_user_first_name, company_boss_user_last_name, company_boss_user_email, company_boss_user_phone, company_user_first_name, company_user_last_name, company_user_post, company_user_email, company_user_phone, company_address, company_postal, company_city, company_country, company_siret, internship_address, internship_postal, internship_city, internship_country, contract_type, subject, start_at, end_at, duration, nb_days, nb_hours, movement, salary, currency, breach_at, convention, created_at, updated_at, anti_grav_units_user_id. Select on a particular range More Example: To range on internships with the anti_grav_units_user_id field between min_value and max_value: ...&range[anti_grav_units_user_id]=min_value,max_value Rangeable fields: id user_id administration_id offer_id language_id state days user_address user_postal user_city user_country company_name company_boss_user_first_name company_boss_user_last_name company_boss_user_email company_boss_user_phone company_user_first_name company_user_last_name company_user_post company_user_email company_user_phone company_address company_postal company_city company_country company_siret internship_address internship_postal internship_city internship_country contract_type subject start_at end_at duration nb_days nb_hours movement salary currency breach_at convention created_at updated_at anti_grav_units_user_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/internships/:id`
Get an internship
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug

### `GET /v2/users/:user_id/internships/:id`
Get an internship of the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug

### `PATCH /v2/internships/:id`
Update an internship
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `internship` optional (Hash) — 
  - `internship[user_id]` optional (Fixnum) — The user id.
  - `internship[administration_id]` optional (Fixnum) — The administration id.
  - `internship[offer_id]` optional (Fixnum) — The offer id.
  - `internship[language_id]` optional (Fixnum) — The language id.
  - `internship[state]` optional (enum) — none, need_validation, invalidated, generated, uploaded, ended, broke, canceled. The state.
  - `internship[days]` optional (String) — The days.
  - `internship[user_address]` optional (String) — The user address.
  - `internship[user_postal]` optional (String) — The user postal.
  - `internship[user_city]` optional (String) — The user city.
  - `internship[user_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The user country.
  - `internship[company_name]` optional (String) — The company name.
  - `internship[company_boss_user_first_name]` optional (String) — The company boss user first name.
  - `internship[company_boss_user_last_name]` optional (String) — The company boss user last name.
  - `internship[company_boss_user_email]` optional (String) — The company boss user email.
  - `internship[company_boss_user_phone]` optional (String) — The company boss user phone.
  - `internship[company_user_first_name]` optional (String) — The company user first name.
  - `internship[company_user_last_name]` optional (String) — The company user last name.
  - `internship[company_user_post]` optional (String) — The company user post.
  - `internship[company_user_email]` optional (String) — The company user email.
  - `internship[company_user_phone]` optional (String) — The company user phone.
  - `internship[company_address]` optional (String) — The company address.
  - `internship[company_postal]` optional (String) — The company postal.
  - `internship[company_city]` optional (String) — The company city.
  - `internship[company_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The company country.
  - `internship[company_siret]` optional (String) — The company siret.
  - `internship[internship_address]` optional (String) — The internship address.
  - `internship[internship_postal]` optional (String) — The internship postal.
  - `internship[internship_city]` optional (String) — The internship city.
  - `internship[internship_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The internship country.
  - `internship[contract_type]` optional (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `internship[subject]` optional (String) — The subject. Maximum length is 280. Allow blank length is true. Allow nil length is true.
  - `internship[start_at]` optional (Fixnum) — The start at…
  - `internship[end_at]` optional (DateTime) — The end at.
  - `internship[duration]` optional (Fixnum) — The duration.
  - `internship[nb_days]` optional (Fixnum) — The nb days.
  - `internship[nb_hours]` optional (Fixnum) — The nb hours.
  - `internship[movement]` optional (String) — The movement.
  - `internship[salary]` optional (Fixnum) — The salary.
  - `internship[currency]` optional (enum) — eur, aed, dol, chf, rub, zar, gbp, yen, can, mad, krw, thb, try, amd, mur, myr, pln, czk. The currency.
  - `internship[breach_at]` optional (DateTime) — The breach at.
  - `internship[convention]` optional (File) — The convention.
  - `internship[anti_grav_units_user_id]` optional (Fixnum) — The anti grav units user id.

### `PUT /v2/internships/:id`
Update an internship
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `internship` optional (Hash) — 
  - `internship[user_id]` optional (Fixnum) — The user id.
  - `internship[administration_id]` optional (Fixnum) — The administration id.
  - `internship[offer_id]` optional (Fixnum) — The offer id.
  - `internship[language_id]` optional (Fixnum) — The language id.
  - `internship[state]` optional (enum) — none, need_validation, invalidated, generated, uploaded, ended, broke, canceled. The state.
  - `internship[days]` optional (String) — The days.
  - `internship[user_address]` optional (String) — The user address.
  - `internship[user_postal]` optional (String) — The user postal.
  - `internship[user_city]` optional (String) — The user city.
  - `internship[user_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The user country.
  - `internship[company_name]` optional (String) — The company name.
  - `internship[company_boss_user_first_name]` optional (String) — The company boss user first name.
  - `internship[company_boss_user_last_name]` optional (String) — The company boss user last name.
  - `internship[company_boss_user_email]` optional (String) — The company boss user email.
  - `internship[company_boss_user_phone]` optional (String) — The company boss user phone.
  - `internship[company_user_first_name]` optional (String) — The company user first name.
  - `internship[company_user_last_name]` optional (String) — The company user last name.
  - `internship[company_user_post]` optional (String) — The company user post.
  - `internship[company_user_email]` optional (String) — The company user email.
  - `internship[company_user_phone]` optional (String) — The company user phone.
  - `internship[company_address]` optional (String) — The company address.
  - `internship[company_postal]` optional (String) — The company postal.
  - `internship[company_city]` optional (String) — The company city.
  - `internship[company_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The company country.
  - `internship[company_siret]` optional (String) — The company siret.
  - `internship[internship_address]` optional (String) — The internship address.
  - `internship[internship_postal]` optional (String) — The internship postal.
  - `internship[internship_city]` optional (String) — The internship city.
  - `internship[internship_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The internship country.
  - `internship[contract_type]` optional (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `internship[subject]` optional (String) — The subject. Maximum length is 280. Allow blank length is true. Allow nil length is true.
  - `internship[start_at]` optional (Fixnum) — The start at…
  - `internship[end_at]` optional (DateTime) — The end at.
  - `internship[duration]` optional (Fixnum) — The duration.
  - `internship[nb_days]` optional (Fixnum) — The nb days.
  - `internship[nb_hours]` optional (Fixnum) — The nb hours.
  - `internship[movement]` optional (String) — The movement.
  - `internship[salary]` optional (Fixnum) — The salary.
  - `internship[currency]` optional (enum) — eur, aed, dol, chf, rub, zar, gbp, yen, can, mad, krw, thb, try, amd, mur, myr, pln, czk. The currency.
  - `internship[breach_at]` optional (DateTime) — The breach at.
  - `internship[convention]` optional (File) — The convention.
  - `internship[anti_grav_units_user_id]` optional (Fixnum) — The anti grav units user id.

### `PATCH /v2/users/:user_id/internships/:id`
Update an internship for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `internship` optional (Hash) — 
  - `internship[user_id]` optional (Fixnum) — The user id.
  - `internship[administration_id]` optional (Fixnum) — The administration id.
  - `internship[offer_id]` optional (Fixnum) — The offer id.
  - `internship[language_id]` optional (Fixnum) — The language id.
  - `internship[state]` optional (enum) — none, need_validation, invalidated, generated, uploaded, ended, broke, canceled. The state.
  - `internship[days]` optional (String) — The days.
  - `internship[user_address]` optional (String) — The user address.
  - `internship[user_postal]` optional (String) — The user postal.
  - `internship[user_city]` optional (String) — The user city.
  - `internship[user_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The user country.
  - `internship[company_name]` optional (String) — The company name.
  - `internship[company_boss_user_first_name]` optional (String) — The company boss user first name.
  - `internship[company_boss_user_last_name]` optional (String) — The company boss user last name.
  - `internship[company_boss_user_email]` optional (String) — The company boss user email.
  - `internship[company_boss_user_phone]` optional (String) — The company boss user phone.
  - `internship[company_user_first_name]` optional (String) — The company user first name.
  - `internship[company_user_last_name]` optional (String) — The company user last name.
  - `internship[company_user_post]` optional (String) — The company user post.
  - `internship[company_user_email]` optional (String) — The company user email.
  - `internship[company_user_phone]` optional (String) — The company user phone.
  - `internship[company_address]` optional (String) — The company address.
  - `internship[company_postal]` optional (String) — The company postal.
  - `internship[company_city]` optional (String) — The company city.
  - `internship[company_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The company country.
  - `internship[company_siret]` optional (String) — The company siret.
  - `internship[internship_address]` optional (String) — The internship address.
  - `internship[internship_postal]` optional (String) — The internship postal.
  - `internship[internship_city]` optional (String) — The internship city.
  - `internship[internship_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The internship country.
  - `internship[contract_type]` optional (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `internship[subject]` optional (String) — The subject. Maximum length is 280. Allow blank length is true. Allow nil length is true.
  - `internship[start_at]` optional (Fixnum) — The start at…
  - `internship[end_at]` optional (DateTime) — The end at.
  - `internship[duration]` optional (Fixnum) — The duration.
  - `internship[nb_days]` optional (Fixnum) — The nb days.
  - `internship[nb_hours]` optional (Fixnum) — The nb hours.
  - `internship[movement]` optional (String) — The movement.
  - `internship[salary]` optional (Fixnum) — The salary.
  - `internship[currency]` optional (enum) — eur, aed, dol, chf, rub, zar, gbp, yen, can, mad, krw, thb, try, amd, mur, myr, pln, czk. The currency.
  - `internship[breach_at]` optional (DateTime) — The breach at.
  - `internship[convention]` optional (File) — The convention.
  - `internship[anti_grav_units_user_id]` optional (Fixnum) — The anti grav units user id.

### `PUT /v2/users/:user_id/internships/:id`
Update an internship for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `internship` optional (Hash) — 
  - `internship[user_id]` optional (Fixnum) — The user id.
  - `internship[administration_id]` optional (Fixnum) — The administration id.
  - `internship[offer_id]` optional (Fixnum) — The offer id.
  - `internship[language_id]` optional (Fixnum) — The language id.
  - `internship[state]` optional (enum) — none, need_validation, invalidated, generated, uploaded, ended, broke, canceled. The state.
  - `internship[days]` optional (String) — The days.
  - `internship[user_address]` optional (String) — The user address.
  - `internship[user_postal]` optional (String) — The user postal.
  - `internship[user_city]` optional (String) — The user city.
  - `internship[user_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The user country.
  - `internship[company_name]` optional (String) — The company name.
  - `internship[company_boss_user_first_name]` optional (String) — The company boss user first name.
  - `internship[company_boss_user_last_name]` optional (String) — The company boss user last name.
  - `internship[company_boss_user_email]` optional (String) — The company boss user email.
  - `internship[company_boss_user_phone]` optional (String) — The company boss user phone.
  - `internship[company_user_first_name]` optional (String) — The company user first name.
  - `internship[company_user_last_name]` optional (String) — The company user last name.
  - `internship[company_user_post]` optional (String) — The company user post.
  - `internship[company_user_email]` optional (String) — The company user email.
  - `internship[company_user_phone]` optional (String) — The company user phone.
  - `internship[company_address]` optional (String) — The company address.
  - `internship[company_postal]` optional (String) — The company postal.
  - `internship[company_city]` optional (String) — The company city.
  - `internship[company_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The company country.
  - `internship[company_siret]` optional (String) — The company siret.
  - `internship[internship_address]` optional (String) — The internship address.
  - `internship[internship_postal]` optional (String) — The internship postal.
  - `internship[internship_city]` optional (String) — The internship city.
  - `internship[internship_country]` optional (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The internship country.
  - `internship[contract_type]` optional (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `internship[subject]` optional (String) — The subject. Maximum length is 280. Allow blank length is true. Allow nil length is true.
  - `internship[start_at]` optional (Fixnum) — The start at…
  - `internship[end_at]` optional (DateTime) — The end at.
  - `internship[duration]` optional (Fixnum) — The duration.
  - `internship[nb_days]` optional (Fixnum) — The nb days.
  - `internship[nb_hours]` optional (Fixnum) — The nb hours.
  - `internship[movement]` optional (String) — The movement.
  - `internship[salary]` optional (Fixnum) — The salary.
  - `internship[currency]` optional (enum) — eur, aed, dol, chf, rub, zar, gbp, yen, can, mad, krw, thb, try, amd, mur, myr, pln, czk. The currency.
  - `internship[breach_at]` optional (DateTime) — The breach at.
  - `internship[convention]` optional (File) — The convention.
  - `internship[anti_grav_units_user_id]` optional (Fixnum) — The anti grav units user id.


## journals

### `GET /v2/campus/:campus_id/journals`
Return all the journals of the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff This resource is paginated by 30 items
- **Params:**
  - `begin_at` required (String) — begin_at must be before or equal to end_at, your date range must be 124 days maximum
  - `end_at` required (String) — end_at must be after or equal to begin_at, your date range must be 124 days maximum
  - `campus_id` required (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, item_type, item_id, cursus_id, campus_id, reason, created_at, updated_at, event_at, alumni, closed. The sort field. Sorted by id desc by default. More Example: To sort on journals on the fields alumni on a descending order and closed on a ascending order: ...&sort=-alumni,closed
  - `filter` optional (enum) — id, user_id, item_type, item_id, cursus_id, campus_id, reason, created_at, updated_at, event_at, alumni, closed, event. Filtering on one or more fields More Example: To filter on journals with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) item_type (standard field) item_id (standard field) cursus_id (standard field) campus_id (standard field) reason (standard field) created_at (standard field) updated_at (standard field) event_at (standard field) alumni (standard field) closed (standard field) event (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## languages

### `POST /v2/languages`
Create a language
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `language` optional (Hash) — 
  - `language[name]` optional (String) — The name.
  - `language[identifier]` optional (String) — The identifier.

### `DELETE /v2/languages/:id`
Destroy a language
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/languages/graph(/on/:field(/by/:interval))`
Return grouped temporal data on languages
- **Params:**
  - `field` optional (enum) — created_at, updated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, name, identifier, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on languages on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, name, identifier, created_at, updated_at. Filtering on one or more fields More Example: To filter on languages with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) identifier (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, name, identifier, created_at, updated_at. Select on a particular range More Example: To range on languages with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id name identifier created_at updated_at

### `GET /v2/languages`
Return all the languages
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, identifier, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on languages on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, name, identifier, created_at, updated_at. Filtering on one or more fields More Example: To filter on languages with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) identifier (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, name, identifier, created_at, updated_at. Select on a particular range More Example: To range on languages with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id name identifier created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/languages/:id`
Get a language
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/languages/:id`
Update a language
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `language` optional (Hash) — 
  - `language[name]` optional (String) — The name.
  - `language[identifier]` optional (String) — The identifier.

### `PUT /v2/languages/:id`
Update a language
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `language` optional (Hash) — 
  - `language[name]` optional (String) — The name.
  - `language[identifier]` optional (String) — The identifier.


## languages_users

### `POST /v2/users/:user_id/languages_users`
Create a languages user for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `languages_user` optional (Hash) — 
  - `languages_user[language_id]` required (Fixnum) — The language id.
  - `languages_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given language.
  - `languages_user[position]` optional (Fixnum) — The position.

### `POST /v2/languages_users`
Create a languages user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `languages_user` optional (Hash) — 
  - `languages_user[language_id]` required (Fixnum) — The language id.
  - `languages_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given language.
  - `languages_user[position]` optional (Fixnum) — The position.

### `DELETE /v2/users/:user_id/languages_users/:id`
Destroy a languages user for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id

### `DELETE /v2/languages_users/:id`
Destroy a languages user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id

### `GET /v2/languages_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on languages users
- **Params:**
  - `field` optional (enum) — created_at, updated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, language_id, user_id, position, created_at. The sort field. Sorted by id desc by default. More Example: To sort on languages users on the fields position on a descending order and created_at on a ascending order: ...&sort=-position,created_at
  - `filter` optional (enum) — id, language_id, user_id, position, created_at. Filtering on one or more fields More Example: To filter on languages users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) language_id (standard field) user_id (standard field) position (standard field) created_at (standard field)
  - `range` optional (enum) — id, language_id, user_id, position, created_at. Select on a particular range More Example: To range on languages users with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id language_id user_id position created_at

### `GET /v2/users/:user_id/languages_users`
Return all the languages users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, language_id, user_id, position, created_at. The sort field. Sorted by id desc by default. More Example: To sort on languages users on the fields position on a descending order and created_at on a ascending order: ...&sort=-position,created_at
  - `filter` optional (enum) — id, language_id, user_id, position, created_at. Filtering on one or more fields More Example: To filter on languages users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) language_id (standard field) user_id (standard field) position (standard field) created_at (standard field)
  - `range` optional (enum) — id, language_id, user_id, position, created_at. Select on a particular range More Example: To range on languages users with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id language_id user_id position created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/languages_users`
Return all the languages users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, language_id, user_id, position, created_at. The sort field. Sorted by id desc by default. More Example: To sort on languages users on the fields position on a descending order and created_at on a ascending order: ...&sort=-position,created_at
  - `filter` optional (enum) — id, language_id, user_id, position, created_at. Filtering on one or more fields More Example: To filter on languages users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) language_id (standard field) user_id (standard field) position (standard field) created_at (standard field)
  - `range` optional (enum) — id, language_id, user_id, position, created_at. Select on a particular range More Example: To range on languages users with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id language_id user_id position created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/languages_users/:id`
Get a languages user of the given Id, associated with the given User
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id

### `GET /v2/languages_users/:id`
Get a languages user
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id

### `PATCH /v2/users/:user_id/languages_users/:id`
Update a languages user for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `languages_user` optional (Hash) — 
  - `languages_user[language_id]` optional (Fixnum) — The language id.
  - `languages_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given language.
  - `languages_user[position]` optional (Fixnum) — The position.

### `PUT /v2/users/:user_id/languages_users/:id`
Update a languages user for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `languages_user` optional (Hash) — 
  - `languages_user[language_id]` optional (Fixnum) — The language id.
  - `languages_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given language.
  - `languages_user[position]` optional (Fixnum) — The position.

### `PATCH /v2/languages_users/:id`
Update a languages user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `languages_user` optional (Hash) — 
  - `languages_user[language_id]` optional (Fixnum) — The language id.
  - `languages_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given language.
  - `languages_user[position]` optional (Fixnum) — The position.

### `PUT /v2/languages_users/:id`
Update a languages user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `languages_user` optional (Hash) — 
  - `languages_user[language_id]` optional (Fixnum) — The language id.
  - `languages_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given language.
  - `languages_user[position]` optional (Fixnum) — The position.


## levels

### `GET /v2/levels`
Return all the levels
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, lvl, xp, cursus_id, created_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on levels on the fields cursus_id on a descending order and created_at on a ascending order: ...&sort=-cursus_id,created_at
  - `filter` optional (enum) — id, lvl, xp, cursus_id, created_at. Filtering on one or more fields More Example: To filter on levels with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) lvl (standard field) xp (standard field) cursus_id (standard field) created_at (standard field)
  - `range` optional (enum) — id, lvl, xp, cursus_id, created_at. Select on a particular range More Example: To range on levels with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id lvl xp cursus_id created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/levels`
Return all the levels of the given Cursus
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, lvl, xp, cursus_id, created_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on levels on the fields cursus_id on a descending order and created_at on a ascending order: ...&sort=-cursus_id,created_at
  - `filter` optional (enum) — id, lvl, xp, cursus_id, created_at. Filtering on one or more fields More Example: To filter on levels with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) lvl (standard field) xp (standard field) cursus_id (standard field) created_at (standard field)
  - `range` optional (enum) — id, lvl, xp, cursus_id, created_at. Select on a particular range More Example: To range on levels with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id lvl xp cursus_id created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## locations

### `POST /v2/locations`
Create a location
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `location` optional (Hash) — 
  - `location[user_id]` required (Fixnum) — The user id.
  - `location[begin_at]` optional (DateTime) — The begin at. If not set default value is the current date.
  - `location[end_at]` optional (DateTime) — The end at.
  - `location[primary]` optional (enum) — true, false. Is it primary?
  - `location[host]` required (String) — The host. Must be unique in the scope of a given campus_id and end_at.
  - `location[campus_id]` required (Fixnum) — The campus id.

### `POST /v2/users/:user_id/locations`
Create a location for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `location` optional (Hash) — 
  - `location[user_id]` required (Fixnum) — The user id.
  - `location[begin_at]` optional (DateTime) — The begin at. If not set default value is the current date.
  - `location[end_at]` optional (DateTime) — The end at.
  - `location[primary]` optional (enum) — true, false. Is it primary?
  - `location[host]` required (String) — The host. Must be unique in the scope of a given campus_id and end_at.
  - `location[campus_id]` required (Fixnum) — The campus id.

### `DELETE /v2/locations/:id`
Destroy a location
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id

### `DELETE /v2/campus/:campus_id/locations/end_all`
End all locations.
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `campus_id` required (String) — The campus id or slug

### `GET /v2/locations/graph(/on/:field(/by/:interval))`
Return grouped temporal data on locations
- **Params:**
  - `field` optional (enum) — begin_at, end_at. The date field to graph on. Default to begin_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on locations on the fields host on a descending order and campus_id on a ascending order: ...&sort=-host,campus_id
  - `filter` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id, active, inactive, future, end. Filtering on one or more fields More Example: To filter on locations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) end_at (standard field) primary (standard field) host (standard field) campus_id (standard field) active : Keep only active locations. Can be one of: true, false inactive : Keep only inactive locations. Can be one of: true, false future : Return only locations which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. Select on a particular range More Example: To range on locations with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id user_id begin_at end_at primary host campus_id

### `GET /v2/locations`
Return all the locations
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on locations on the fields host on a descending order and campus_id on a ascending order: ...&sort=-host,campus_id
  - `filter` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id, active, inactive, future, end. Filtering on one or more fields More Example: To filter on locations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) end_at (standard field) primary (standard field) host (standard field) campus_id (standard field) active : Keep only active locations. Can be one of: true, false inactive : Keep only inactive locations. Can be one of: true, false future : Return only locations which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. Select on a particular range More Example: To range on locations with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id user_id begin_at end_at primary host campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/locations`
Return all the locations of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on locations on the fields host on a descending order and campus_id on a ascending order: ...&sort=-host,campus_id
  - `filter` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id, active, inactive, future, end. Filtering on one or more fields More Example: To filter on locations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) end_at (standard field) primary (standard field) host (standard field) campus_id (standard field) active : Keep only active locations. Can be one of: true, false inactive : Keep only inactive locations. Can be one of: true, false future : Return only locations which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. Select on a particular range More Example: To range on locations with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id user_id begin_at end_at primary host campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/locations`
Return all the locations of the given Campus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on locations on the fields host on a descending order and campus_id on a ascending order: ...&sort=-host,campus_id
  - `filter` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id, active, inactive, future, end. Filtering on one or more fields More Example: To filter on locations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) end_at (standard field) primary (standard field) host (standard field) campus_id (standard field) active : Keep only active locations. Can be one of: true, false inactive : Keep only inactive locations. Can be one of: true, false future : Return only locations which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, user_id, begin_at, end_at, primary, host, campus_id. Select on a particular range More Example: To range on locations with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id user_id begin_at end_at primary host campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/locations/:id`
Get a location
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/locations/:id`
Update a location
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `location` optional (Hash) — 
  - `location[user_id]` optional (Fixnum) — The user id.
  - `location[begin_at]` optional (Fixnum) — The begin at. .
  - `location[end_at]` optional (Fixnum) — The end at. .
  - `location[primary]` optional (enum) — true, false. Is it primary ?
  - `location[host]` optional (String) — The host. Must be unique in the scope of a given campus id and end at.
  - `location[campus_id]` optional (Fixnum) — The campus id.

### `PUT /v2/locations/:id`
Update a location
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `location` optional (Hash) — 
  - `location[user_id]` optional (Fixnum) — The user id.
  - `location[begin_at]` optional (Fixnum) — The begin at. .
  - `location[end_at]` optional (Fixnum) — The end at. .
  - `location[primary]` optional (enum) — true, false. Is it primary ?
  - `location[host]` optional (String) — The host. Must be unique in the scope of a given campus id and end at.
  - `location[campus_id]` optional (Fixnum) — The campus id.

### `PATCH /v2/users/:user_id/locations/:id`
Update a location for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `location` optional (Hash) — 
  - `location[user_id]` optional (Fixnum) — The user id.
  - `location[begin_at]` optional (Fixnum) — The begin at. .
  - `location[end_at]` optional (Fixnum) — The end at. .
  - `location[primary]` optional (enum) — true, false. Is it primary ?
  - `location[host]` optional (String) — The host. Must be unique in the scope of a given campus id and end at.
  - `location[campus_id]` optional (Fixnum) — The campus id.

### `PUT /v2/users/:user_id/locations/:id`
Update a location for the given Id, associated with the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id
  - `user_id` optional (String) — The user id or slug
  - `location` optional (Hash) — 
  - `location[user_id]` optional (Fixnum) — The user id.
  - `location[begin_at]` optional (Fixnum) — The begin at. .
  - `location[end_at]` optional (Fixnum) — The end at. .
  - `location[primary]` optional (enum) — true, false. Is it primary ?
  - `location[host]` optional (String) — The host. Must be unique in the scope of a given campus id and end at.
  - `location[campus_id]` optional (Fixnum) — The campus id.


## mailings

### `POST /v2/mailings`
Create a new mail
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Avanced staff
- **Params:**
  - `mailing` optional (Hash) — 
  - `mailing[subject]` required (String) — The subject of the mail
  - `mailing[content]` required (String) — The content of the mail, supports Markdown.
  - `mailing[from]` required (String) — The mail sender, with the sender <sender@email> format. If none, set from [email protected]
  - `mailing[to]` optional (n) — array of any type An array of emails for the mail’s to field
  - `mailing[cc]` optional (n) — array of any type An array of emails for the mail’s cc field
  - `mailing[bcc]` optional (n) — array of any type An array of emails for the mail’s bcc field
  - `mailing[title]` optional (String) — The title of the mail. If none, set to the subject
  - `mailing[subtitle]` optional (String) — The subtitle of the mail
  - `mailing[identifier]` optional (String) — The identifier of the mail, used with meta
  - `mailing[meta]` optional (Hash) — The meta of the mail
  - `at` optional (DateTime) — The time to send the mail. If none, send it now.

### `DELETE /v2/mailings/:id`
Destroy a mailing
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/mailings`
Return all the mailings
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, subject, created_at, updated_at, identifier, meta, title, subtitle, attachment, from, to, cc, bcc, content, html_content, attachments. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on mailings on the fields html_content on a descending order and attachments on a ascending order: ...&sort=-html_content,attachments
  - `filter` optional (enum) — id, subject, created_at, updated_at, identifier, meta, title, subtitle, attachment, from, to, cc, bcc, content, html_content, attachments. Filtering on one or more fields More Example: To filter on mailings with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) subject (standard field) created_at (standard field) updated_at (standard field) identifier (standard field) meta (standard field) title (standard field) subtitle (standard field) attachment (standard field) from (standard field) to (standard field) cc (standard field) bcc (standard field) content (standard field) html_content (standard field) attachments (standard field)
  - `range` optional (enum) — id, subject, created_at, updated_at, identifier, meta, title, subtitle, attachment, from, to, cc, bcc, content, html_content, attachments. Select on a particular range More Example: To range on mailings with the attachments field between min_value and max_value: ...&range[attachments]=min_value,max_value Rangeable fields: id subject created_at updated_at identifier meta title subtitle attachment from to cc bcc content html_content attachments
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/mailings`
Return all the mailings of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, subject, created_at, updated_at, identifier, meta, title, subtitle, attachment, from, to, cc, bcc, content, html_content, attachments. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on mailings on the fields html_content on a descending order and attachments on a ascending order: ...&sort=-html_content,attachments
  - `filter` optional (enum) — id, subject, created_at, updated_at, identifier, meta, title, subtitle, attachment, from, to, cc, bcc, content, html_content, attachments. Filtering on one or more fields More Example: To filter on mailings with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) subject (standard field) created_at (standard field) updated_at (standard field) identifier (standard field) meta (standard field) title (standard field) subtitle (standard field) attachment (standard field) from (standard field) to (standard field) cc (standard field) bcc (standard field) content (standard field) html_content (standard field) attachments (standard field)
  - `range` optional (enum) — id, subject, created_at, updated_at, identifier, meta, title, subtitle, attachment, from, to, cc, bcc, content, html_content, attachments. Select on a particular range More Example: To range on mailings with the attachments field between min_value and max_value: ...&range[attachments]=min_value,max_value Rangeable fields: id subject created_at updated_at identifier meta title subtitle attachment from to cc bcc content html_content attachments
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/mailings/:id`
Get a mailing
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/mailings/:id`
Update a mailing
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `mailing` optional (Hash) — 
  - `mailing[subject]` optional (String) — The subject of the mail
  - `mailing[content]` optional (String) — The content of the mail, supports Markdown.
  - `mailing[from]` optional (String) — The mail sender, with the sender <sender@email> format. If none, set from [email protected]
  - `mailing[to]` optional (n) — array of any type An array of emails for the mail’s to field
  - `mailing[cc]` optional (n) — array of any type An array of emails for the mail’s cc field
  - `mailing[bcc]` optional (n) — array of any type An array of emails for the mail’s bcc field
  - `mailing[title]` optional (String) — The title of the mail. If none, set to the subject
  - `mailing[subtitle]` optional (String) — The subtitle of the mail
  - `mailing[identifier]` optional (String) — The identifier of the mail, used with meta
  - `mailing[meta]` optional (Hash) — The meta of the mail
  - `at` optional (DateTime) — The time to send the mail. If none, send it now.

### `PUT /v2/mailings/:id`
Update a mailing
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `mailing` optional (Hash) — 
  - `mailing[subject]` optional (String) — The subject of the mail
  - `mailing[content]` optional (String) — The content of the mail, supports Markdown.
  - `mailing[from]` optional (String) — The mail sender, with the sender <sender@email> format. If none, set from [email protected]
  - `mailing[to]` optional (n) — array of any type An array of emails for the mail’s to field
  - `mailing[cc]` optional (n) — array of any type An array of emails for the mail’s cc field
  - `mailing[bcc]` optional (n) — array of any type An array of emails for the mail’s bcc field
  - `mailing[title]` optional (String) — The title of the mail. If none, set to the subject
  - `mailing[subtitle]` optional (String) — The subtitle of the mail
  - `mailing[identifier]` optional (String) — The identifier of the mail, used with meta
  - `mailing[meta]` optional (Hash) — The meta of the mail
  - `at` optional (DateTime) — The time to send the mail. If none, send it now.


## notes

### `POST /v2/notes`
Create a note
- **Auth/scope:** create POST /v2/notes Create a note Notes This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `note` optional (Hash) — 
  - `note[user_id]` required (Fixnum) — The user who receives the note.
  - `note[subject]` optional (String) — The subject.
  - `note[content]` optional (String) — The content.
  - `note[kind]` optional (enum) — manual, black_hole, school_record. The kind.
  - `note[approved_at]` optional (DateTime) — Must be an Advanced Note manager to create or edit this field.
  - `note[approver_id]` optional (Fixnum) — The id of the user approving the note. Must be an Advanced Note manager to create or edit this field.

### `DELETE /v2/notes/:id`
Destroy a note
- **Auth/scope:** destroy DELETE /v2/notes/:id Destroy a note Notes This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/users/:user_id/notes`
Return all the notes of the given User
- **Auth/scope:** index GET /v2/users/:user_id/notes Return all the notes of the given User GET /v2/campus/:campus_id/notes Return all the notes of the given Campus GET /v2/notes Return all the notes Notes This resource is paginated by 30 items This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on notes on the fields approver_id on a descending order and from_user_id on a ascending order: ...&sort=-approver_id,from_user_id
  - `filter` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id, approved. Filtering on one or more fields More Example: To filter on notes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) from (standard field) subject (standard field) content (standard field) created_at (standard field) updated_at (standard field) kind (standard field) approved_at (standard field) approver_id (standard field) from_user_id (standard field) approved (standard field)
  - `range` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id. Select on a particular range More Example: To range on notes with the from_user_id field between min_value and max_value: ...&range[from_user_id]=min_value,max_value Rangeable fields: id user_id from subject content created_at updated_at kind approved_at approver_id from_user_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/notes`
Return all the notes of the given Campus
- **Auth/scope:** index GET /v2/users/:user_id/notes Return all the notes of the given User GET /v2/campus/:campus_id/notes Return all the notes of the given Campus GET /v2/notes Return all the notes Notes This resource is paginated by 30 items This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on notes on the fields approver_id on a descending order and from_user_id on a ascending order: ...&sort=-approver_id,from_user_id
  - `filter` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id, approved. Filtering on one or more fields More Example: To filter on notes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) from (standard field) subject (standard field) content (standard field) created_at (standard field) updated_at (standard field) kind (standard field) approved_at (standard field) approver_id (standard field) from_user_id (standard field) approved (standard field)
  - `range` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id. Select on a particular range More Example: To range on notes with the from_user_id field between min_value and max_value: ...&range[from_user_id]=min_value,max_value Rangeable fields: id user_id from subject content created_at updated_at kind approved_at approver_id from_user_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/notes`
Return all the notes
- **Auth/scope:** index GET /v2/users/:user_id/notes Return all the notes of the given User GET /v2/campus/:campus_id/notes Return all the notes of the given Campus GET /v2/notes Return all the notes Notes This resource is paginated by 30 items This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on notes on the fields approver_id on a descending order and from_user_id on a ascending order: ...&sort=-approver_id,from_user_id
  - `filter` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id, approved. Filtering on one or more fields More Example: To filter on notes with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) from (standard field) subject (standard field) content (standard field) created_at (standard field) updated_at (standard field) kind (standard field) approved_at (standard field) approver_id (standard field) from_user_id (standard field) approved (standard field)
  - `range` optional (enum) — id, user_id, from, subject, content, created_at, updated_at, kind, approved_at, approver_id, from_user_id. Select on a particular range More Example: To range on notes with the from_user_id field between min_value and max_value: ...&range[from_user_id]=min_value,max_value Rangeable fields: id user_id from subject content created_at updated_at kind approved_at approver_id from_user_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/notes/:id`
Get a note
- **Auth/scope:** show GET /v2/notes/:id Get a note Notes This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/notes/:id`
Update a note
- **Auth/scope:** update PATCH /v2/notes/:id Update a note PUT /v2/notes/:id Update a note Notes This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `id` required (String) — The requested id
  - `note` optional (Hash) — 
  - `note[user_id]` optional (Fixnum) — The user who receives the note.
  - `note[subject]` optional (String) — The subject.
  - `note[content]` optional (String) — The content.
  - `note[kind]` optional (enum) — manual, black_hole, school_record. The kind.
  - `note[approved_at]` optional (DateTime) — Must be an Advanced Note manager to create or edit this field.
  - `note[approver_id]` optional (Fixnum) — The id of the user approving the note. Must be an Advanced Note manager to create or edit this field.

### `PUT /v2/notes/:id`
Update a note
- **Auth/scope:** update PATCH /v2/notes/:id Update a note PUT /v2/notes/:id Update a note Notes This action requires a token resource owner or an application with one of theses role(s): Notes manager, Advanced notes manager .
- **Params:**
  - `id` required (String) — The requested id
  - `note` optional (Hash) — 
  - `note[user_id]` optional (Fixnum) — The user who receives the note.
  - `note[subject]` optional (String) — The subject.
  - `note[content]` optional (String) — The content.
  - `note[kind]` optional (enum) — manual, black_hole, school_record. The kind.
  - `note[approved_at]` optional (DateTime) — Must be an Advanced Note manager to create or edit this field.
  - `note[approver_id]` optional (Fixnum) — The id of the user approving the note. Must be an Advanced Note manager to create or edit this field.


## notions

### `POST /v2/notions`
Create a notion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `notion` optional (Hash) — 
  - `notion[name]` required (String) — The name. Must be unique.
  - `notion[tag_ids]` optional (n) — array of Integer The tag ids.
  - `notion[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `notion[subnotions_attributes]` optional (n) — Array of nested elements The subnotions attributes.
  - `notion[subnotions_attributes][id]` optional (Fixnum) — The id.
  - `notion[subnotions_attributes][name]` required (String) — The name. Must be unique in the scope of a given notion.
  - `notion[subnotions_attributes][_destroy]` optional (String) — The destroy.
  - `notion[subnotions_attributes][attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `notion[subnotions_attributes][attachments_attributes][id]` optional (Fixnum) — The id.
  - `notion[subnotions_attributes][attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `notion[subnotions_attributes][attachments_attributes][_destroy]` optional (String) — The destroy.
  - `notion[subnotions_attributes][attachments_attributes][language_id]` required (Fixnum) — The language id.
  - `notion[subnotions_attributes][attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `notion[subnotions_attributes][attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.

### `DELETE /v2/notions/:id`
Destroy a notion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/cursus/:cursus_id/notions`
Return all the notions of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, name, created_at, updated_at, slug. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on notions on the fields updated_at on a descending order and slug on a ascending order: ...&sort=-updated_at,slug
  - `filter` optional (enum) — id, name, created_at, updated_at, slug. Filtering on one or more fields More Example: To filter on notions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug. Select on a particular range More Example: To range on notions with the slug field between min_value and max_value: ...&range[slug]=min_value,max_value Rangeable fields: id name created_at updated_at slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/tags/:tag_id/notions`
Return all the notions of the given Tag
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, name, created_at, updated_at, slug. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on notions on the fields updated_at on a descending order and slug on a ascending order: ...&sort=-updated_at,slug
  - `filter` optional (enum) — id, name, created_at, updated_at, slug. Filtering on one or more fields More Example: To filter on notions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug. Select on a particular range More Example: To range on notions with the slug field between min_value and max_value: ...&range[slug]=min_value,max_value Rangeable fields: id name created_at updated_at slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/notions`
Return all the notions
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, name, created_at, updated_at, slug. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on notions on the fields updated_at on a descending order and slug on a ascending order: ...&sort=-updated_at,slug
  - `filter` optional (enum) — id, name, created_at, updated_at, slug. Filtering on one or more fields More Example: To filter on notions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug. Select on a particular range More Example: To range on notions with the slug field between min_value and max_value: ...&range[slug]=min_value,max_value Rangeable fields: id name created_at updated_at slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/notions/:id`
Get a notion
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/notions/:id`
Update a notion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `id` required (String) — The requested id
  - `notion` optional (Hash) — 
  - `notion[name]` optional (String) — The name. Must be unique.
  - `notion[tag_ids]` optional (n) — array of Integer The tag ids.
  - `notion[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `notion[subnotions_attributes]` optional (n) — Array of nested elements The subnotions attributes.
  - `notion[subnotions_attributes][id]` optional (Fixnum) — The id.
  - `notion[subnotions_attributes][name]` optional (String) — The name. Must be unique in the scope of a given notion.
  - `notion[subnotions_attributes][_destroy]` optional (String) — The destroy.
  - `notion[subnotions_attributes][attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `notion[subnotions_attributes][attachments_attributes][id]` optional (Fixnum) — The id.
  - `notion[subnotions_attributes][attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `notion[subnotions_attributes][attachments_attributes][_destroy]` optional (String) — The destroy.
  - `notion[subnotions_attributes][attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `notion[subnotions_attributes][attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `notion[subnotions_attributes][attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.

### `PUT /v2/notions/:id`
Update a notion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `id` required (String) — The requested id
  - `notion` optional (Hash) — 
  - `notion[name]` optional (String) — The name. Must be unique.
  - `notion[tag_ids]` optional (n) — array of Integer The tag ids.
  - `notion[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `notion[subnotions_attributes]` optional (n) — Array of nested elements The subnotions attributes.
  - `notion[subnotions_attributes][id]` optional (Fixnum) — The id.
  - `notion[subnotions_attributes][name]` optional (String) — The name. Must be unique in the scope of a given notion.
  - `notion[subnotions_attributes][_destroy]` optional (String) — The destroy.
  - `notion[subnotions_attributes][attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `notion[subnotions_attributes][attachments_attributes][id]` optional (Fixnum) — The id.
  - `notion[subnotions_attributes][attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `notion[subnotions_attributes][attachments_attributes][_destroy]` optional (String) — The destroy.
  - `notion[subnotions_attributes][attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `notion[subnotions_attributes][attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `notion[subnotions_attributes][attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.


## offers

### `POST /v2/offers`
Create an offer
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `offer` optional (Hash) — 
  - `offer[title]` required (String) — The title. Maximum length is 255.
  - `offer[little_description]` required (String) — The little description. Maximum length is 140. Allow blank length is true. Allow nil length is true.
  - `offer[big_description]` required (String) — The big description.
  - `offer[salary]` optional (String) — The salary. Maximum length is 255. Allow blank length is true. Allow nil length is true.
  - `offer[contract_type]` required (enum) — freelance, apprentice_ship, cdd, cdi, stage, cdd_partiel, cdi_partiel, stage_partiel, crea_startup. The contract type.
  - `offer[email]` required (String) — The email.
  - `offer[address]` required (String) — The address.
  - `offer[city]` required (String) — The city.
  - `offer[zip]` required (String) — The zip.
  - `offer[country]` required (enum) — Afghanistan, Åland Islands, Albania, Algeria, American Samoa, Andorra, Angola, Anguilla, Antarctica, Antigua and Barbuda, Argentina, Armenia, Aruba, Australia, Austria, Azerbaijan, Bahamas, Bahrain, Bangladesh, Barbados, Belarus, Belgium, Belize, Benin, Bermuda, Bhutan, Bolivia, Plurinational State of, Bonaire, Sint Eustatius and Saba, Bosnia and Herzegovina, Botswana, Bouvet Island, Brazil, British Indian Ocean Territory, Brunei Darussalam, Bulgaria, Burkina Faso, Burundi, Cambodia, Cameroon, Canada, Cape Verde, Cayman Islands, Central African Republic, Chad, Chile, China, Christmas Island, Cocos (Keeling) Islands, Colombia, Comoros, Congo, Congo, The Democratic Republic of the, Cook Islands, Costa Rica, Côte d'Ivoire, Croatia, Cuba, Curaçao, Cyprus, Czech Republic, Denmark, Djibouti, Dominica, Dominican Republic, Ecuador, Egypt, El Salvador, Equatorial Guinea, Eritrea, Estonia, Ethiopia, Falkland Islands (Malvinas), Faroe Islands, Fiji, Finland, France, French Guiana, French Polynesia, French Southern Territories, Gabon, Gambia, Georgia, Germany, Ghana, Gibraltar, Greece, Greenland, Grenada, Guadeloupe, Guam, Guatemala, Guernsey, Guinea, Guinea-Bissau, Guyana, Haiti, Heard Island and McDonald Islands, Holy See (Vatican City State), Honduras, Hong Kong, Hungary, Iceland, India, Indonesia, Iran, Islamic Republic of, Iraq, Ireland, Isle of Man, Israel, Italy, Jamaica, Japan, Jersey, Jordan, Kazakhstan, Kenya, Kiribati, Korea, Democratic People's Republic of, Korea, Republic of, Kuwait, Kyrgyzstan, Lao People's Democratic Republic, Latvia, Lebanon, Lesotho, Liberia, Libya, Liechtenstein, Lithuania, Luxembourg, Macao, Macedonia, Republic of, Madagascar, Malawi, Malaysia, Maldives, Mali, Malta, Marshall Islands, Martinique, Mauritania, Mauritius, Mayotte, Mexico, Micronesia, Federated States of, Moldova, Republic of, Monaco, Mongolia, Montenegro, Montserrat, Morocco, Mozambique, Myanmar, Namibia, Nauru, Nepal, Netherlands, New Caledonia, New Zealand, Nicaragua, Niger, Nigeria, Niue, Norfolk Island, Northern Mariana Islands, Norway, Oman, Pakistan, Palau, Palestine, State of, Panama, Papua New Guinea, Paraguay, Peru, Philippines, Pitcairn, Poland, Portugal, Puerto Rico, Qatar, Réunion, Romania, Russian Federation, Rwanda, Saint Barthélemy, Saint Helena, Ascension and Tristan da Cunha, Saint Kitts and Nevis, Saint Lucia, Saint Martin (French part), Saint Pierre and Miquelon, Saint Vincent and the Grenadines, Samoa, San Marino, Sao Tome and Principe, Saudi Arabia, Senegal, Serbia, Seychelles, Sierra Leone, Singapore, Sint Maarten (Dutch part), Slovakia, Slovenia, Solomon Islands, Somalia, South Africa, South Georgia and the South Sandwich Islands, Spain, Sri Lanka, Sudan, Suriname, South Sudan, Svalbard and Jan Mayen, Swaziland, Sweden, Switzerland, Syrian Arab Republic, Taiwan, Tajikistan, Tanzania, United Republic of, Thailand, Timor-Leste, Togo, Tokelau, Tonga, Trinidad and Tobago, Tunisia, Turkey, Turkmenistan, Turks and Caicos Islands, Tuvalu, Uganda, Ukraine, United Arab Emirates, United Kingdom, United States, United States Minor Outlying Islands, Uruguay, Uzbekistan, Vanuatu, Venezuela, Bolivarian Republic of, Viet Nam, Virgin Islands, British, Virgin Islands, U.S., Wallis and Futuna, Western Sahara, Yemen, Zambia, Zimbabwe. The country.
  - `offer[latitude]` optional (Float) — The latitude.
  - `offer[longitude]` optional (Float) — The longitude.
  - `offer[valid_at]` required (Fixnum) — The valid at. .
  - `offer[invalid_at]` required (Fixnum) — The invalid at. Must be after the ‘valid at’ date.
  - `offer[min_duration]` required (Fixnum) — The min duration.
  - `offer[max_duration]` optional (Fixnum) — The max duration.
  - `offer[document]` optional (File) — The document.
  - `offer[slug]` optional (String) — The slug.
  - `offer[pro_id]` optional (Fixnum) — The pro id.
  - `offer[company_id]` optional (Fixnum) — The company id.
  - `offer[target]` required (enum) — student, student_and_alumni. The target.

### `GET /v2/offers`
Return all the offers
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, title, little_description, big_description, salary, contract_type, email, address, city, zip, country, latitude, longitude, valid_at, invalid_at, min_duration, max_duration, document, slug, created_at, updated_at, pro_id, company_id, target. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on offers on the fields company_id on a descending order and target on a ascending order: ...&sort=-company_id,target
  - `filter` optional (enum) — id, title, little_description, big_description, salary, contract_type, email, address, city, zip, country, latitude, longitude, valid_at, invalid_at, min_duration, max_duration, document, slug, created_at, updated_at, pro_id, company_id, target, contract_type, target, expertise_id, campus_id, country, expertise, reported, user_id, valid, invalid. Filtering on one or more fields More Example: To filter on offers with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) title (standard field) little_description (standard field) big_description (standard field) salary (standard field) contract_type : Filter by contract type. email (standard field) address (standard field) city (standard field) zip (standard field) country : Filter by campus id. latitude (standard field) longitude (standard field) valid_at (standard field) invalid_at (standard field) min_duration (standard field) max_duration (standard field) document (standard field) slug (standard field) created_at (standard field) updated_at (standard field) pro_id (standard field) company_id (standard field) target : Filter by target. contract_type : Filter by contract type. target : Filter by target. expertise_id : Filter by expertise id. campus_id : Filter by campus_id. country : Filter by campus id. expertise : Filter by expertise name. reported : Shows only reported offers. user_id : Show offers which a specific user susbcribe to. valid (standard field) invalid (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/offers/:id`
Get an offer
- **Params:**
  - `id` required (String) — The requested id


## offers_users

### `GET /v2/offers/:offer_id/offers_users`
Return all the offers users of the given Offer
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager This resource is paginated by 30 items
- **Params:**
  - `offer_id` optional (String) — The offer id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, offer_id, user_id, validated_at, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on offers users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, offer_id, user_id, validated_at, created_at, updated_at, validated. Filtering on one or more fields More Example: To filter on offers users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) offer_id (standard field) user_id (standard field) validated_at (standard field) created_at (standard field) updated_at (standard field) validated (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/offers_users`
Return all the offers users of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager This resource is paginated by 30 items
- **Params:**
  - `offer_id` optional (String) — The offer id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, offer_id, user_id, validated_at, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on offers users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, offer_id, user_id, validated_at, created_at, updated_at, validated. Filtering on one or more fields More Example: To filter on offers users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) offer_id (standard field) user_id (standard field) validated_at (standard field) created_at (standard field) updated_at (standard field) validated (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/offers_users`
Return all the offers users
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager This resource is paginated by 30 items
- **Params:**
  - `offer_id` optional (String) — The offer id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, offer_id, user_id, validated_at, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on offers users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, offer_id, user_id, validated_at, created_at, updated_at, validated. Filtering on one or more fields More Example: To filter on offers users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) offer_id (standard field) user_id (standard field) validated_at (standard field) created_at (standard field) updated_at (standard field) validated (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/offers_users/:id`
Get an offers user
- **Auth/scope:** assignment This action requires one of theses roles: Companies manager
- **Params:**
  - `id` required (String) — The requested id


## params_project_sessions_rules

### `POST /v2/project_sessions_rules/:project_sessions_rule_id/params_project_sessions_rules`
Create a params project sessions rule for the given Project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects Params Param name Description project_sessions_rule_id optional . Must be String The project_sessions_rule id params_project_sessions_rule optional , nil allowed . Must be a Hash params_project_sessions_rule[id] optional , nil allowed . Must be Fixnum The id. params_project_sessions_rule[param_id
- **Params:**
  - `project_sessions_rule_id` optional (String) — The project_sessions_rule id
  - `params_project_sessions_rule` optional (Hash) — 
  - `params_project_sessions_rule[id]` optional (Fixnum) — The id.
  - `params_project_sessions_rule[param_id]` required (Fixnum) — The param id.
  - `params_project_sessions_rule[value]` optional (String) — The value.
  - `params_project_sessions_rule[project_sessions_rule_id]` optional (Fixnum) — The project sessions rule id.

### `POST /v2/params_project_sessions_rules`
Create a params project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects Params Param name Description project_sessions_rule_id optional . Must be String The project_sessions_rule id params_project_sessions_rule optional , nil allowed . Must be a Hash params_project_sessions_rule[id] optional , nil allowed . Must be Fixnum The id. params_project_sessions_rule[param_id
- **Params:**
  - `project_sessions_rule_id` optional (String) — The project_sessions_rule id
  - `params_project_sessions_rule` optional (Hash) — 
  - `params_project_sessions_rule[id]` optional (Fixnum) — The id.
  - `params_project_sessions_rule[param_id]` required (Fixnum) — The param id.
  - `params_project_sessions_rule[value]` optional (String) — The value.
  - `params_project_sessions_rule[project_sessions_rule_id]` optional (Fixnum) — The project sessions rule id.

### `GET /v2/project_sessions_rules/:project_sessions_rule_id/params_project_sessions_rules`
Return all the params project sessions rules of the given Project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items Params Param name Description project_sessions_rule_id optional . Must be String The project_sessions_rule id sort optional . Must be one of: id, param_id, project_sessions_rule_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on params project sessions rule
- **Params:**
  - `project_sessions_rule_id` optional (String) — The project_sessions_rule id
  - `sort` optional (enum) — id, param_id, project_sessions_rule_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on params project sessions rules on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, param_id, project_sessions_rule_id, value, created_at, updated_at. Filtering on one or more fields More Example: To filter on params project sessions rules with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) param_id (standard field) project_sessions_rule_id (standard field) value (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, param_id, project_sessions_rule_id, value, created_at, updated_at. Select on a particular range More Example: To range on params project sessions rules with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id param_id project_sessions_rule_id value created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/params_project_sessions_rules`
Return all the params project sessions rules
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items Params Param name Description project_sessions_rule_id optional . Must be String The project_sessions_rule id sort optional . Must be one of: id, param_id, project_sessions_rule_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on params project sessions rule
- **Params:**
  - `project_sessions_rule_id` optional (String) — The project_sessions_rule id
  - `sort` optional (enum) — id, param_id, project_sessions_rule_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on params project sessions rules on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, param_id, project_sessions_rule_id, value, created_at, updated_at. Filtering on one or more fields More Example: To filter on params project sessions rules with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) param_id (standard field) project_sessions_rule_id (standard field) value (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, param_id, project_sessions_rule_id, value, created_at, updated_at. Select on a particular range More Example: To range on params project sessions rules with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id param_id project_sessions_rule_id value created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/params_project_sessions_rules/:id`
Get a params project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor Params Param name Description id required . Must be String The requested id
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/params_project_sessions_rules/:id`
Update a params project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects Params Param name Description id required . Must be String The requested id params_project_sessions_rule optional , nil allowed . Must be a Hash params_project_sessions_rule[id] optional , nil allowed . Must be Fixnum The id. params_project_sessions_rule[param_id] optional . Must be Fixnum
- **Params:**
  - `id` required (String) — The requested id
  - `params_project_sessions_rule` optional (Hash) — 
  - `params_project_sessions_rule[id]` optional (Fixnum) — The id.
  - `params_project_sessions_rule[param_id]` optional (Fixnum) — The param id.
  - `params_project_sessions_rule[value]` optional (String) — The value.
  - `params_project_sessions_rule[project_sessions_rule_id]` optional (Fixnum) — The project sessions rule id.

### `PUT /v2/params_project_sessions_rules/:id`
Update a params project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects Params Param name Description id required . Must be String The requested id params_project_sessions_rule optional , nil allowed . Must be a Hash params_project_sessions_rule[id] optional , nil allowed . Must be Fixnum The id. params_project_sessions_rule[param_id] optional . Must be Fixnum
- **Params:**
  - `id` required (String) — The requested id
  - `params_project_sessions_rule` optional (Hash) — 
  - `params_project_sessions_rule[id]` optional (Fixnum) — The id.
  - `params_project_sessions_rule[param_id]` optional (Fixnum) — The param id.
  - `params_project_sessions_rule[value]` optional (String) — The value.
  - `params_project_sessions_rule[project_sessions_rule_id]` optional (Fixnum) — The project sessions rule id.


## partnerships

### `POST /v2/partnerships`
Create a partnership
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `partnership` optional (Hash) — 
  - `partnership[name]` required (String) — The name. Must be unique.
  - `partnership[description]` required (String) — The description.
  - `partnership[difficulty]` required (Fixnum) — The difficulty.
  - `partnership[file]` optional (File) — The file.
  - `partnership[cursus_id]` required (Fixnum) — The cursus id.
  - `partnership[user_ids]` optional (n) — array of Integer The user ids.
  - `partnership[partnerships_skills_attributes]` optional (n) — Array of nested elements The partnerships skills attributes.
  - `partnership[partnerships_skills_attributes][id]` optional (Fixnum) — The id.
  - `partnership[partnerships_skills_attributes][skill_id]` required (Fixnum) — The skill id.
  - `partnership[partnerships_skills_attributes][value]` required (Float) — The value.
  - `partnership[partnerships_skills_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/partnerships/:id`
Destroy a partnership
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/partnerships`
Return all the partnerships
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, name, description, difficulty, created_at, updated_at, slug, file, cursus_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on partnerships on the fields file on a descending order and cursus_id on a ascending order: ...&sort=-file,cursus_id
  - `filter` optional (enum) — id, name, description, difficulty, created_at, updated_at, slug, file, cursus_id, tier, difficulty. Filtering on one or more fields More Example: To filter on partnerships with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) difficulty : Filter on a project's tier. Can be one of: 0, 1, 2, 3, 4, 5, 6, 7 created_at (standard field) updated_at (standard field) slug (standard field) file (standard field) cursus_id (standard field) tier : Filter on a project's tier. Can be one of: 0, 1, 2, 3, 4, 5, 6, 7 difficulty : Filter on a project's tier. Can be one of: 0, 1, 2, 3, 4, 5, 6, 7
  - `range` optional (enum) — id, name, description, difficulty, created_at, updated_at, slug, file, cursus_id, difficulty. Select on a particular range More Example: To range on partnerships with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id name description difficulty created_at updated_at slug file cursus_id difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/partnerships/:id`
Get a partnership
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/partnerships/:id`
Update a partnership
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `partnership` optional (Hash) — 
  - `partnership[name]` optional (String) — The name. Must be unique.
  - `partnership[description]` optional (String) — The description.
  - `partnership[difficulty]` optional (Fixnum) — The difficulty.
  - `partnership[file]` optional (File) — The file.
  - `partnership[cursus_id]` optional (Fixnum) — The cursus id.
  - `partnership[user_ids]` optional (n) — array of Integer The user ids.
  - `partnership[partnerships_skills_attributes]` optional (n) — Array of nested elements The partnerships skills attributes.
  - `partnership[partnerships_skills_attributes][id]` optional (Fixnum) — The id.
  - `partnership[partnerships_skills_attributes][skill_id]` optional (Fixnum) — The skill id.
  - `partnership[partnerships_skills_attributes][value]` optional (Float) — The value.
  - `partnership[partnerships_skills_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/partnerships/:id`
Update a partnership
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `partnership` optional (Hash) — 
  - `partnership[name]` optional (String) — The name. Must be unique.
  - `partnership[description]` optional (String) — The description.
  - `partnership[difficulty]` optional (Fixnum) — The difficulty.
  - `partnership[file]` optional (File) — The file.
  - `partnership[cursus_id]` optional (Fixnum) — The cursus id.
  - `partnership[user_ids]` optional (n) — array of Integer The user ids.
  - `partnership[partnerships_skills_attributes]` optional (n) — Array of nested elements The partnerships skills attributes.
  - `partnership[partnerships_skills_attributes][id]` optional (Fixnum) — The id.
  - `partnership[partnerships_skills_attributes][skill_id]` optional (Fixnum) — The skill id.
  - `partnership[partnerships_skills_attributes][value]` optional (Float) — The value.
  - `partnership[partnerships_skills_attributes][_destroy]` optional (String) — The destroy.


## partnerships_users

### `POST /v2/partnerships/:partnership_id/partnerships_users`
Create a partnerships user for the given Partnership
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `partnership_id` optional (String) — The partnership id or slug
  - `partnerships_user` optional (Hash) — 
  - `partnerships_user[partnership_id]` required (Fixnum) — The partnership id. Must be unique in the scope of a given user.
  - `partnerships_user[user_id]` required (Fixnum) — The user id.
  - `partnerships_user[final_mark]` optional (Fixnum) — The final mark.

### `POST /v2/partnerships_users`
Create a partnerships user
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `partnership_id` optional (String) — The partnership id or slug
  - `partnerships_user` optional (Hash) — 
  - `partnerships_user[partnership_id]` required (Fixnum) — The partnership id. Must be unique in the scope of a given user.
  - `partnerships_user[user_id]` required (Fixnum) — The user id.
  - `partnerships_user[final_mark]` optional (Fixnum) — The final mark.

### `DELETE /v2/partnerships_users/:id`
Destroy a partnerships user
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/partnerships/:partnership_id/partnerships_users`
Return all the partnerships users of the given Partnership
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `partnership_id` optional (String) — The partnership id or slug
  - `sort` optional (enum) — id, partnership_id, user_id, created_at, updated_at, final_mark. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on partnerships users on the fields updated_at on a descending order and final_mark on a ascending order: ...&sort=-updated_at,final_mark
  - `filter` optional (enum) — id, partnership_id, user_id, created_at, updated_at, final_mark. Filtering on one or more fields More Example: To filter on partnerships users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) partnership_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) final_mark (standard field)
  - `range` optional (enum) — id, partnership_id, user_id, created_at, updated_at, final_mark. Select on a particular range More Example: To range on partnerships users with the final_mark field between min_value and max_value: ...&range[final_mark]=min_value,max_value Rangeable fields: id partnership_id user_id created_at updated_at final_mark
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/partnerships_users`
Return all the partnerships users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `partnership_id` optional (String) — The partnership id or slug
  - `sort` optional (enum) — id, partnership_id, user_id, created_at, updated_at, final_mark. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on partnerships users on the fields updated_at on a descending order and final_mark on a ascending order: ...&sort=-updated_at,final_mark
  - `filter` optional (enum) — id, partnership_id, user_id, created_at, updated_at, final_mark. Filtering on one or more fields More Example: To filter on partnerships users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) partnership_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) final_mark (standard field)
  - `range` optional (enum) — id, partnership_id, user_id, created_at, updated_at, final_mark. Select on a particular range More Example: To range on partnerships users with the final_mark field between min_value and max_value: ...&range[final_mark]=min_value,max_value Rangeable fields: id partnership_id user_id created_at updated_at final_mark
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/partnerships_users/:id`
Get a partnerships user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/partnerships_users/:id`
Update a partnerships user
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `partnerships_user` optional (Hash) — 
  - `partnerships_user[partnership_id]` optional (Fixnum) — The partnership id. Must be unique in the scope of a given user.
  - `partnerships_user[user_id]` optional (Fixnum) — The user id.
  - `partnerships_user[final_mark]` optional (Fixnum) — The final mark.

### `PUT /v2/partnerships_users/:id`
Update a partnerships user
- **Auth/scope:** assignment This action requires one of theses roles: Student tutor, Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `partnerships_user` optional (Hash) — 
  - `partnerships_user[partnership_id]` optional (Fixnum) — The partnership id. Must be unique in the scope of a given user.
  - `partnerships_user[user_id]` optional (Fixnum) — The user id.
  - `partnerships_user[final_mark]` optional (Fixnum) — The final mark.


## patronages

### `POST /v2/patronages`
Create a patronage
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage` optional (Hash) — 
  - `patronage[user_id]` required (Fixnum) — The user id.
  - `patronage[godfather_id]` required (Fixnum) — The godfather id.
  - `patronage[ongoing]` optional (enum) — true, false. Is it ongoing ? Default to true.

### `POST /v2/users/:user_id/patronages`
Create a patronage for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage` optional (Hash) — 
  - `patronage[user_id]` required (Fixnum) — The user id.
  - `patronage[godfather_id]` required (Fixnum) — The godfather id.
  - `patronage[ongoing]` optional (enum) — true, false. Is it ongoing ? Default to true.

### `DELETE /v2/patronages/:id`
Destroy a patronage
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/patronages`
Return all the patronages
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, godfather_id, ongoing, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, godfather_id, ongoing, created_at, updated_at. Filtering on one or more fields More Example: To filter on patronages with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) godfather_id (standard field) ongoing (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, user_id, godfather_id, ongoing, created_at, updated_at. Select on a particular range More Example: To range on patronages with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id godfather_id ongoing created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/patronages`
Return all the patronages of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, godfather_id, ongoing, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, user_id, godfather_id, ongoing, created_at, updated_at. Filtering on one or more fields More Example: To filter on patronages with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) godfather_id (standard field) ongoing (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, user_id, godfather_id, ongoing, created_at, updated_at. Select on a particular range More Example: To range on patronages with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id user_id godfather_id ongoing created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/patronages/:id`
Get a patronage
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/patronages/:id`
Update a patronage
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `patronage` optional (Hash) — 
  - `patronage[user_id]` optional (Fixnum) — The user id.
  - `patronage[godfather_id]` optional (Fixnum) — The godfather id.
  - `patronage[ongoing]` optional (enum) — true, false. Is it ongoing ? Default to true.

### `PUT /v2/patronages/:id`
Update a patronage
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `patronage` optional (Hash) — 
  - `patronage[user_id]` optional (Fixnum) — The user id.
  - `patronage[godfather_id]` optional (Fixnum) — The godfather id.
  - `patronage[ongoing]` optional (enum) — true, false. Is it ongoing ? Default to true.


## patronages_reports

### `POST /v2/patronages_reports`
Create a patronages report
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `patronages_report` optional (Hash) — 
  - `patronages_report[user_id]` optional (Fixnum) — The user id.
  - `patronages_report[begin_at]` optional (DateTime) — The begin at.
  - `patronages_report[patronage_id]` required (Fixnum) — The patronage id.
  - `patronages_report[report_id]` required (Fixnum) — The report id.
  - `patronages_report[validated_at]` optional (DateTime) — The validated at.
  - `patronages_report[comment]` optional (String) — The comment.
  - `patronages_report[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `patronages_report[answers_attributes][question_id]` required (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `patronages_report[answers_attributes][value]` optional (Fixnum) — The value.
  - `patronages_report[answers_attributes][answer]` optional (String) — The answer.
  - `patronages_report[answers_attributes][id]` optional (Fixnum) — The id.

### `POST /v2/users/:user_id/patronages_reports`
Create a patronages report for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `patronages_report` optional (Hash) — 
  - `patronages_report[user_id]` optional (Fixnum) — The user id.
  - `patronages_report[begin_at]` optional (DateTime) — The begin at.
  - `patronages_report[patronage_id]` required (Fixnum) — The patronage id.
  - `patronages_report[report_id]` required (Fixnum) — The report id.
  - `patronages_report[validated_at]` optional (DateTime) — The validated at.
  - `patronages_report[comment]` optional (String) — The comment.
  - `patronages_report[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `patronages_report[answers_attributes][question_id]` required (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `patronages_report[answers_attributes][value]` optional (Fixnum) — The value.
  - `patronages_report[answers_attributes][answer]` optional (String) — The answer.
  - `patronages_report[answers_attributes][id]` optional (Fixnum) — The id.

### `POST /v2/patronages/:patronage_id/patronages_reports`
Create a patronages report for the given Patronage
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `patronages_report` optional (Hash) — 
  - `patronages_report[user_id]` optional (Fixnum) — The user id.
  - `patronages_report[begin_at]` optional (DateTime) — The begin at.
  - `patronages_report[patronage_id]` required (Fixnum) — The patronage id.
  - `patronages_report[report_id]` required (Fixnum) — The report id.
  - `patronages_report[validated_at]` optional (DateTime) — The validated at.
  - `patronages_report[comment]` optional (String) — The comment.
  - `patronages_report[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `patronages_report[answers_attributes][question_id]` required (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `patronages_report[answers_attributes][value]` optional (Fixnum) — The value.
  - `patronages_report[answers_attributes][answer]` optional (String) — The answer.
  - `patronages_report[answers_attributes][id]` optional (Fixnum) — The id.

### `POST /v2/reports/:report_id/patronages_reports`
Create a patronages report for the given Report
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `patronages_report` optional (Hash) — 
  - `patronages_report[user_id]` optional (Fixnum) — The user id.
  - `patronages_report[begin_at]` optional (DateTime) — The begin at.
  - `patronages_report[patronage_id]` required (Fixnum) — The patronage id.
  - `patronages_report[report_id]` required (Fixnum) — The report id.
  - `patronages_report[validated_at]` optional (DateTime) — The validated at.
  - `patronages_report[comment]` optional (String) — The comment.
  - `patronages_report[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `patronages_report[answers_attributes][question_id]` required (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `patronages_report[answers_attributes][value]` optional (Fixnum) — The value.
  - `patronages_report[answers_attributes][answer]` optional (String) — The answer.
  - `patronages_report[answers_attributes][id]` optional (Fixnum) — The id.

### `DELETE /v2/patronages_reports/:id`
Destroy a patronages report
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/patronages_reports/graph(/on/:field(/by/:interval))`
Return grouped temporal data on patronages reports
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at, validated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages reports on the fields report_id on a descending order and validated_at on a ascending order: ...&sort=-report_id,validated_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at, future, validated. Filtering on one or more fields More Example: To filter on patronages reports with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) patronage_id (standard field) report_id (standard field) validated_at (standard field) future : Return only patronages reports which begins in the future. Can be one of: true, false validated (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. Select on a particular range More Example: To range on patronages reports with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at patronage_id report_id validated_at

### `GET /v2/patronages_reports`
Return all the patronages reports
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages reports on the fields report_id on a descending order and validated_at on a ascending order: ...&sort=-report_id,validated_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at, future, validated. Filtering on one or more fields More Example: To filter on patronages reports with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) patronage_id (standard field) report_id (standard field) validated_at (standard field) future : Return only patronages reports which begins in the future. Can be one of: true, false validated (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. Select on a particular range More Example: To range on patronages reports with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at patronage_id report_id validated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/patronages_reports`
Return all the patronages reports of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages reports on the fields report_id on a descending order and validated_at on a ascending order: ...&sort=-report_id,validated_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at, future, validated. Filtering on one or more fields More Example: To filter on patronages reports with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) patronage_id (standard field) report_id (standard field) validated_at (standard field) future : Return only patronages reports which begins in the future. Can be one of: true, false validated (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. Select on a particular range More Example: To range on patronages reports with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at patronage_id report_id validated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/patronages/:patronage_id/patronages_reports`
Return all the patronages reports of the given Patronage
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages reports on the fields report_id on a descending order and validated_at on a ascending order: ...&sort=-report_id,validated_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at, future, validated. Filtering on one or more fields More Example: To filter on patronages reports with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) patronage_id (standard field) report_id (standard field) validated_at (standard field) future : Return only patronages reports which begins in the future. Can be one of: true, false validated (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. Select on a particular range More Example: To range on patronages reports with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at patronage_id report_id validated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/reports/:report_id/patronages_reports`
Return all the patronages reports of the given Report
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `patronage_id` optional (String) — The patronage id
  - `report_id` optional (String) — The report id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on patronages reports on the fields report_id on a descending order and validated_at on a ascending order: ...&sort=-report_id,validated_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at, future, validated. Filtering on one or more fields More Example: To filter on patronages reports with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) patronage_id (standard field) report_id (standard field) validated_at (standard field) future : Return only patronages reports which begins in the future. Can be one of: true, false validated (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, patronage_id, report_id, validated_at. Select on a particular range More Example: To range on patronages reports with the validated_at field between min_value and max_value: ...&range[validated_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at patronage_id report_id validated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/patronages_reports/:id`
Get a patronages report
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/patronages_reports/:id`
Update a patronages report
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `id` required (String) — The requested id
  - `patronages_report` optional (Hash) — 
  - `patronages_report[user_id]` optional (Fixnum) — The user id.
  - `patronages_report[begin_at]` optional (DateTime) — The begin at.
  - `patronages_report[patronage_id]` optional (Fixnum) — The patronage id.
  - `patronages_report[report_id]` optional (Fixnum) — The report id.
  - `patronages_report[validated_at]` optional (DateTime) — The validated at.
  - `patronages_report[comment]` optional (String) — The comment.
  - `patronages_report[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `patronages_report[answers_attributes][question_id]` optional (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `patronages_report[answers_attributes][value]` optional (Fixnum) — The value.
  - `patronages_report[answers_attributes][answer]` optional (String) — The answer.
  - `patronages_report[answers_attributes][id]` optional (Fixnum) — The id.

### `PUT /v2/patronages_reports/:id`
Update a patronages report
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `id` required (String) — The requested id
  - `patronages_report` optional (Hash) — 
  - `patronages_report[user_id]` optional (Fixnum) — The user id.
  - `patronages_report[begin_at]` optional (DateTime) — The begin at.
  - `patronages_report[patronage_id]` optional (Fixnum) — The patronage id.
  - `patronages_report[report_id]` optional (Fixnum) — The report id.
  - `patronages_report[validated_at]` optional (DateTime) — The validated at.
  - `patronages_report[comment]` optional (String) — The comment.
  - `patronages_report[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `patronages_report[answers_attributes][question_id]` optional (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `patronages_report[answers_attributes][value]` optional (Fixnum) — The value.
  - `patronages_report[answers_attributes][answer]` optional (String) — The answer.
  - `patronages_report[answers_attributes][id]` optional (Fixnum) — The id.


## pools

### `POST /v2/pools/:id/points/add`
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `points` required (number) — . Number of points to be added. Points can be negative.

### `GET /v2/pools`
Return all the pools
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, current_points, max_points, created_at, updated_at, cursus_id, campus_id. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on pools on the fields cursus_id on a descending order and campus_id on a ascending order: ...&sort=-cursus_id,campus_id
  - `filter` optional (enum) — id, current_points, max_points, created_at, updated_at, cursus_id, campus_id. Filtering on one or more fields More Example: To filter on pools with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) current_points (standard field) max_points (standard field) created_at (standard field) updated_at (standard field) cursus_id (standard field) campus_id (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `DELETE /v2/pools/:id/points/remove`
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `points` required (number) — . Number of points to be removed. Points are converted to absolute values and decremented by that point.

### `GET /v2/pools/:id`
Get a pool
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id


## products

### `POST /v2/products`
Create a product
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` required (String) — The name. Must be unique.
  - `product[description]` required (String) — The description.
  - `product[price]` required (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` required (Fixnum) — The category id.
  - `product[kind]` required (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` required (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` required (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `POST /v2/campus/:campus_id/products`
Create a product for the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` required (String) — The name. Must be unique.
  - `product[description]` required (String) — The description.
  - `product[price]` required (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` required (Fixnum) — The category id.
  - `product[kind]` required (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` required (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` required (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/products/:id`
Destroy a product
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` optional (String) — The name. Must be unique.
  - `product[description]` optional (String) — The description.
  - `product[price]` optional (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` optional (Fixnum) — The category id.
  - `product[kind]` optional (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` optional (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/campus/:campus_id/products/:id`
Destroy a product for the given Id, associated with the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` optional (String) — The name. Must be unique.
  - `product[description]` optional (String) — The description.
  - `product[price]` optional (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` optional (Fixnum) — The category id.
  - `product[kind]` optional (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` optional (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `GET /v2/products`
Return all the products
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, name, description, price, quantity, begin_at, end_at, category_id, created_at, updated_at, kind, slug, image, is_uniq, one_time_purchase. The sort field. Sorted by id desc by default. More Example: To sort on products on the fields is_uniq on a descending order and one_time_purchase on a ascending order: ...&sort=-is_uniq,one_time_purchase
  - `filter` optional (enum) — id, name, description, price, quantity, begin_at, end_at, category_id, created_at, updated_at, kind, slug, image, is_uniq, one_time_purchase, future, end. Filtering on one or more fields More Example: To filter on products with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) price (standard field) quantity (standard field) begin_at (standard field) end_at (standard field) category_id (standard field) created_at (standard field) updated_at (standard field) kind (standard field) slug (standard field) image (standard field) is_uniq (standard field) one_time_purchase (standard field) future : Return only products which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, name, description, price, quantity, begin_at, end_at, category_id, created_at, updated_at, kind, slug, image, is_uniq, one_time_purchase. Select on a particular range More Example: To range on products with the one_time_purchase field between min_value and max_value: ...&range[one_time_purchase]=min_value,max_value Rangeable fields: id name description price quantity begin_at end_at category_id created_at updated_at kind slug image is_uniq one_time_purchase

### `GET /v2/campus/:campus_id/products`
Return all the products of the given Campus
- **Params:**
  - `campus_id` optional (String) — The campus id or slug
  - `sort` optional (enum) — id, name, description, price, quantity, begin_at, end_at, category_id, created_at, updated_at, kind, slug, image, is_uniq, one_time_purchase. The sort field. Sorted by id desc by default. More Example: To sort on products on the fields is_uniq on a descending order and one_time_purchase on a ascending order: ...&sort=-is_uniq,one_time_purchase
  - `filter` optional (enum) — id, name, description, price, quantity, begin_at, end_at, category_id, created_at, updated_at, kind, slug, image, is_uniq, one_time_purchase, future, end. Filtering on one or more fields More Example: To filter on products with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) price (standard field) quantity (standard field) begin_at (standard field) end_at (standard field) category_id (standard field) created_at (standard field) updated_at (standard field) kind (standard field) slug (standard field) image (standard field) is_uniq (standard field) one_time_purchase (standard field) future : Return only products which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, name, description, price, quantity, begin_at, end_at, category_id, created_at, updated_at, kind, slug, image, is_uniq, one_time_purchase. Select on a particular range More Example: To range on products with the one_time_purchase field between min_value and max_value: ...&range[one_time_purchase]=min_value,max_value Rangeable fields: id name description price quantity begin_at end_at category_id created_at updated_at kind slug image is_uniq one_time_purchase

### `GET /v2/products/:id`
Get a product
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug

### `GET /v2/campus/:campus_id/products/:id`
Get a product of the given Id, associated with the given Campus
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug

### `PATCH /v2/products/:id`
Update a product
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` optional (String) — The name. Must be unique.
  - `product[description]` optional (String) — The description.
  - `product[price]` optional (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` optional (Fixnum) — The category id.
  - `product[kind]` optional (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` optional (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/products/:id`
Update a product
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` optional (String) — The name. Must be unique.
  - `product[description]` optional (String) — The description.
  - `product[price]` optional (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` optional (Fixnum) — The category id.
  - `product[kind]` optional (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` optional (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `PATCH /v2/campus/:campus_id/products/:id`
Update a product for the given Id, associated with the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` optional (String) — The name. Must be unique.
  - `product[description]` optional (String) — The description.
  - `product[price]` optional (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` optional (Fixnum) — The category id.
  - `product[kind]` optional (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` optional (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/campus/:campus_id/products/:id`
Update a product for the given Id, associated with the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Shop manager, Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `campus_id` optional (String) — The campus id or slug
  - `product` optional (Hash) — 
  - `product[name]` optional (String) — The name. Must be unique.
  - `product[description]` optional (String) — The description.
  - `product[price]` optional (Fixnum) — The price.
  - `product[quantity]` optional (Fixnum) — The quantity.
  - `product[begin_at]` optional (DateTime) — The begin at.
  - `product[end_at]` optional (DateTime) — The end at.
  - `product[category_id]` optional (Fixnum) — The category id.
  - `product[kind]` optional (enum) — user, manager, auto. The kind.
  - `product[slug]` optional (String) — The slug.
  - `product[image]` optional (File) — The image.
  - `product[is_uniq]` optional (enum) — true, false. Is it is uniq ?
  - `product[one_time_purchase]` optional (enum) — true, false. Is it one time purchase ?
  - `product[campus_products_attributes]` optional (n) — Array of nested elements The campus products attributes.
  - `product[campus_products_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `product[campus_products_attributes][_destroy]` optional (String) — The destroy.


## project_data

### `POST /v2/project_data`
Create a project datum
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects

### `DELETE /v2/project_data/:id`
Destroy a project datum
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/project_data`
Return all the project data
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, coordinates, created_at, updated_at, by, kind, project_session_id. The sort field. Sorted by id desc by default. More Example: To sort on project data on the fields kind on a descending order and project_session_id on a ascending order: ...&sort=-kind,project_session_id
  - `filter` optional (enum) — id, coordinates, created_at, updated_at, by, kind, project_session_id. Filtering on one or more fields More Example: To filter on project data with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) coordinates (standard field) created_at (standard field) updated_at (standard field) by (standard field) kind (standard field) project_session_id (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions/:project_session_id/project_data`
Return all the project data of the given Project session
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, coordinates, created_at, updated_at, by, kind, project_session_id. The sort field. Sorted by id desc by default. More Example: To sort on project data on the fields kind on a descending order and project_session_id on a ascending order: ...&sort=-kind,project_session_id
  - `filter` optional (enum) — id, coordinates, created_at, updated_at, by, kind, project_session_id. Filtering on one or more fields More Example: To filter on project data with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) coordinates (standard field) created_at (standard field) updated_at (standard field) by (standard field) kind (standard field) project_session_id (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_data/:id`
Get a project datum
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/project_data/:id`
Update a project datum
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `project_data` optional (Hash) — 
  - `project_data[coordinates]` optional (String) — The project coordinates for the graph as a string, such as: “[x, y]”
  - `project_data[kind]` optional (enum) — project, rush, exam, first_internship, second_internship, big_project, piscine, part_time.
  - `project_data[project_session_id]` optional (Fixnum) — 
  - `project_data[by]` optional (String) — The link path, under the “[[project_id, x1, y1, x2, y2], []]” format

### `PUT /v2/project_data/:id`
Update a project datum
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `project_data` optional (Hash) — 
  - `project_data[coordinates]` optional (String) — The project coordinates for the graph as a string, such as: “[x, y]”
  - `project_data[kind]` optional (enum) — project, rush, exam, first_internship, second_internship, big_project, piscine, part_time.
  - `project_data[project_session_id]` optional (Fixnum) — 
  - `project_data[by]` optional (String) — The link path, under the “[[project_id, x1, y1, x2, y2], []]” format


## project_sessions

### `GET /v2/projects/:project_id/project_sessions/graph(/on/:field(/by/:interval))`
Return grouped temporal data on project sessions
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, minimum_mark, team_behaviour, commit, difficulty, description, objectives, divisor. The sort field. Sorted by id desc by default. More Example: To sort on project sessions on the fields objectives on a descending order and divisor on a ascending order: ...&sort=-objectives,divisor
  - `filter` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty, future, end. Filtering on one or more fields More Example: To filter on project sessions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) campus_id (standard field) cursus_id (standard field) estimate_time (standard field) created_at (standard field) updated_at (standard field) begin_at (standard field) end_at (standard field) max_people (standard field) duration_days (standard field) terminating_after (standard field) solo (standard field) is_subscriptable (standard field) team_behaviour (standard field) difficulty : Filter on difficulty. future : Return only project sessions which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty. Select on a particular range More Example: To range on project sessions with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id project_id campus_id cursus_id estimate_time created_at updated_at begin_at end_at max_people duration_days terminating_after solo is_subscriptable team_behaviour difficulty

### `GET /v2/project_sessions/graph(/on/:field(/by/:interval))`
Return grouped temporal data on project sessions
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, minimum_mark, team_behaviour, commit, difficulty, description, objectives, divisor. The sort field. Sorted by id desc by default. More Example: To sort on project sessions on the fields objectives on a descending order and divisor on a ascending order: ...&sort=-objectives,divisor
  - `filter` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty, future, end. Filtering on one or more fields More Example: To filter on project sessions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) campus_id (standard field) cursus_id (standard field) estimate_time (standard field) created_at (standard field) updated_at (standard field) begin_at (standard field) end_at (standard field) max_people (standard field) duration_days (standard field) terminating_after (standard field) solo (standard field) is_subscriptable (standard field) team_behaviour (standard field) difficulty : Filter on difficulty. future : Return only project sessions which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty. Select on a particular range More Example: To range on project sessions with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id project_id campus_id cursus_id estimate_time created_at updated_at begin_at end_at max_people duration_days terminating_after solo is_subscriptable team_behaviour difficulty

### `GET /v2/projects/:project_id/project_sessions`
Return all the project sessions of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, minimum_mark, team_behaviour, commit, difficulty, description, objectives, divisor. The sort field. Sorted by id desc by default. More Example: To sort on project sessions on the fields objectives on a descending order and divisor on a ascending order: ...&sort=-objectives,divisor
  - `filter` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty, future, end. Filtering on one or more fields More Example: To filter on project sessions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) campus_id (standard field) cursus_id (standard field) estimate_time (standard field) created_at (standard field) updated_at (standard field) begin_at (standard field) end_at (standard field) max_people (standard field) duration_days (standard field) terminating_after (standard field) solo (standard field) is_subscriptable (standard field) team_behaviour (standard field) difficulty : Filter on difficulty. future : Return only project sessions which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty. Select on a particular range More Example: To range on project sessions with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id project_id campus_id cursus_id estimate_time created_at updated_at begin_at end_at max_people duration_days terminating_after solo is_subscriptable team_behaviour difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions`
Return all the project sessions
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, minimum_mark, team_behaviour, commit, difficulty, description, objectives, divisor. The sort field. Sorted by id desc by default. More Example: To sort on project sessions on the fields objectives on a descending order and divisor on a ascending order: ...&sort=-objectives,divisor
  - `filter` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty, future, end. Filtering on one or more fields More Example: To filter on project sessions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) campus_id (standard field) cursus_id (standard field) estimate_time (standard field) created_at (standard field) updated_at (standard field) begin_at (standard field) end_at (standard field) max_people (standard field) duration_days (standard field) terminating_after (standard field) solo (standard field) is_subscriptable (standard field) team_behaviour (standard field) difficulty : Filter on difficulty. future : Return only project sessions which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, project_id, campus_id, cursus_id, estimate_time, created_at, updated_at, begin_at, end_at, max_people, duration_days, terminating_after, solo, is_subscriptable, team_behaviour, difficulty. Select on a particular range More Example: To range on project sessions with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id project_id campus_id cursus_id estimate_time created_at updated_at begin_at end_at max_people duration_days terminating_after solo is_subscriptable team_behaviour difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions/:id`
Get a project session
- **Params:**
  - `id` required (String) — The requested id


## project_sessions_rules

### `POST /v2/project_sessions/:project_session_id/project_sessions_rules`
Create a project sessions rule for the given Project session
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_sessions_rule` optional (Hash) — 
  - `project_sessions_rule[id]` optional (Fixnum) — The id.
  - `project_sessions_rule[rule_id]` required (Fixnum) — The rule id.
  - `project_sessions_rule[required]` optional (enum) — true, false. Is it required ?
  - `project_sessions_rule[project_session_id]` required (Fixnum) — The project session id.
  - `project_sessions_rule[params_project_sessions_rules_attributes]` optional (n) — Array of nested elements The params project sessions rules attributes.
  - `project_sessions_rule[params_project_sessions_rules_attributes][id]` optional (Fixnum) — The id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][param_id]` required (Fixnum) — The param id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][value]` optional (String) — The value.
  - `project_sessions_rule[params_project_sessions_rules_attributes][_destroy]` optional (String) — The destroy.

### `POST /v2/project_sessions_rules`
Create a project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_sessions_rule` optional (Hash) — 
  - `project_sessions_rule[id]` optional (Fixnum) — The id.
  - `project_sessions_rule[rule_id]` required (Fixnum) — The rule id.
  - `project_sessions_rule[required]` optional (enum) — true, false. Is it required ?
  - `project_sessions_rule[project_session_id]` required (Fixnum) — The project session id.
  - `project_sessions_rule[params_project_sessions_rules_attributes]` optional (n) — Array of nested elements The params project sessions rules attributes.
  - `project_sessions_rule[params_project_sessions_rules_attributes][id]` optional (Fixnum) — The id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][param_id]` required (Fixnum) — The param id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][value]` optional (String) — The value.
  - `project_sessions_rule[params_project_sessions_rules_attributes][_destroy]` optional (String) — The destroy.

### `GET /v2/project_sessions/:project_session_id/project_sessions_rules`
Return all the project sessions rules of the given Project session
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, rule_id, created_at, updated_at, required, position, project_session_id. The sort field. Sorted by id desc by default. More Example: To sort on project sessions rules on the fields position on a descending order and project_session_id on a ascending order: ...&sort=-position,project_session_id
  - `filter` optional (enum) — id, rule_id, created_at, updated_at, required, position, project_session_id. Filtering on one or more fields More Example: To filter on project sessions rules with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) rule_id (standard field) created_at (standard field) updated_at (standard field) required (standard field) position (standard field) project_session_id (standard field)
  - `range` optional (enum) — id, rule_id, created_at, updated_at, required, position, project_session_id. Select on a particular range More Example: To range on project sessions rules with the project_session_id field between min_value and max_value: ...&range[project_session_id]=min_value,max_value Rangeable fields: id rule_id created_at updated_at required position project_session_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions_rules`
Return all the project sessions rules
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, rule_id, created_at, updated_at, required, position, project_session_id. The sort field. Sorted by id desc by default. More Example: To sort on project sessions rules on the fields position on a descending order and project_session_id on a ascending order: ...&sort=-position,project_session_id
  - `filter` optional (enum) — id, rule_id, created_at, updated_at, required, position, project_session_id. Filtering on one or more fields More Example: To filter on project sessions rules with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) rule_id (standard field) created_at (standard field) updated_at (standard field) required (standard field) position (standard field) project_session_id (standard field)
  - `range` optional (enum) — id, rule_id, created_at, updated_at, required, position, project_session_id. Select on a particular range More Example: To range on project sessions rules with the project_session_id field between min_value and max_value: ...&range[project_session_id]=min_value,max_value Rangeable fields: id rule_id created_at updated_at required position project_session_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions_rules/:id`
Get a project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/project_sessions_rules/:id`
Update a project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `project_sessions_rule` optional (Hash) — 
  - `project_sessions_rule[id]` optional (Fixnum) — The id.
  - `project_sessions_rule[rule_id]` optional (Fixnum) — The rule id.
  - `project_sessions_rule[required]` optional (enum) — true, false. Is it required ?
  - `project_sessions_rule[project_session_id]` optional (Fixnum) — The project session id.
  - `project_sessions_rule[params_project_sessions_rules_attributes]` optional (n) — Array of nested elements The params project sessions rules attributes.
  - `project_sessions_rule[params_project_sessions_rules_attributes][id]` optional (Fixnum) — The id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][param_id]` optional (Fixnum) — The param id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][value]` optional (String) — The value.
  - `project_sessions_rule[params_project_sessions_rules_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/project_sessions_rules/:id`
Update a project sessions rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `project_sessions_rule` optional (Hash) — 
  - `project_sessions_rule[id]` optional (Fixnum) — The id.
  - `project_sessions_rule[rule_id]` optional (Fixnum) — The rule id.
  - `project_sessions_rule[required]` optional (enum) — true, false. Is it required ?
  - `project_sessions_rule[project_session_id]` optional (Fixnum) — The project session id.
  - `project_sessions_rule[params_project_sessions_rules_attributes]` optional (n) — Array of nested elements The params project sessions rules attributes.
  - `project_sessions_rule[params_project_sessions_rules_attributes][id]` optional (Fixnum) — The id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][param_id]` optional (Fixnum) — The param id.
  - `project_sessions_rule[params_project_sessions_rules_attributes][value]` optional (String) — The value.
  - `project_sessions_rule[params_project_sessions_rules_attributes][_destroy]` optional (String) — The destroy.


## project_sessions_skills

### `GET /v2/project_sessions_skills`
Return all the project sessions skills
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `skill_id` optional (String) — The skill id or slug
  - `sort` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on project sessions skills on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. Filtering on one or more fields More Example: To filter on project sessions skills with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_session_id (standard field) skill_id (standard field) value (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. Select on a particular range More Example: To range on project sessions skills with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id project_session_id skill_id value created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions/:project_session_id/project_sessions_skills`
Return all the project sessions skills of the given Project session
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `skill_id` optional (String) — The skill id or slug
  - `sort` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on project sessions skills on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. Filtering on one or more fields More Example: To filter on project sessions skills with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_session_id (standard field) skill_id (standard field) value (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. Select on a particular range More Example: To range on project sessions skills with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id project_session_id skill_id value created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/skills/:skill_id/project_sessions_skills`
Return all the project sessions skills of the given Skill
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `skill_id` optional (String) — The skill id or slug
  - `sort` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on project sessions skills on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. Filtering on one or more fields More Example: To filter on project sessions skills with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_session_id (standard field) skill_id (standard field) value (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, project_session_id, skill_id, value, created_at, updated_at. Select on a particular range More Example: To range on project sessions skills with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id project_session_id skill_id value created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions_skills/:id`
Get a project sessions skill
- **Params:**
  - `id` required (String) — The requested id
  - `project_session_id` optional (String) — The project_session id

### `GET /v2/project_sessions/:project_session_id/project_sessions_skills/:id`
Get a project sessions skill of the given Id, associated with the given Project session
- **Params:**
  - `id` required (String) — The requested id
  - `project_session_id` optional (String) — The project_session id


## projects

### `POST /v2/projects`
Create a project
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `project` optional (Hash) — 
  - `project[name]` required (String) — The name.
  - `project[terminating_after]` optional (String) — The terminating after.
  - `project[exam]` optional (enum) — true, false. Is it exam ? Default to false.
  - `project[has_mark]` optional (enum) — true, false. Is it has mark ? Default to true.
  - `project[repository]` required (String) — The repository.
  - `project[git_id]` optional (Fixnum) — The git id.
  - `project[has_git]` optional (enum) — true, false. Is it has git ? Default to true.
  - `project[is_subscriptable]` optional (String) — The is subscriptable.
  - `project[inherited_team]` optional (enum) — true, false. Is it inherited team ? Default to false.
  - `project[minimum_mark]` optional (String) — The minimum mark.
  - `project[parent_id]` optional (Fixnum) — The parent id.
  - `project[max_people]` optional (String) — The max people.
  - `project[visible]` optional (enum) — true, false. Is it visible ? Default to false.
  - `project[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `project[campus_ids]` optional (n) — array of Integer The campus ids.
  - `project[authors_user_ids]` optional (n) — array of Integer The authors user ids.
  - `project[notion_ids]` optional (n) — array of Integer The notion ids.
  - `project[project_sessions_attributes]` optional (n) — Array of nested elements The project sessions attributes.
  - `project[project_sessions_attributes][id]` optional (Fixnum) — The id.
  - `project[project_sessions_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `project[project_sessions_attributes][cursus_id]` optional (Fixnum) — The cursus id.
  - `project[project_sessions_attributes][estimate_time]` optional (Fixnum) — The estimate time.
  - `project[project_sessions_attributes][created_at]` optional (DateTime) — The created at.
  - `project[project_sessions_attributes][updated_at]` optional (DateTime) — The updated at.
  - `project[project_sessions_attributes][begin_at]` optional (DateTime) — The begin at.
  - `project[project_sessions_attributes][end_at]` optional (DateTime) — The end at.
  - `project[project_sessions_attributes][max_people]` optional (Fixnum) — The max people.
  - `project[project_sessions_attributes][duration_days]` optional (Fixnum) — The duration days.
  - `project[project_sessions_attributes][terminating_after]` optional (Fixnum) — The terminating after.
  - `project[project_sessions_attributes][solo]` optional (enum) — true, false. Is it solo ? Default to false.
  - `project[project_sessions_attributes][is_subscriptable]` optional (enum) — true, false. Is it is subscriptable ? Default to true.
  - `project[project_sessions_attributes][minimum_mark]` required (Fixnum) — The minimum mark.
  - `project[project_sessions_attributes][team_behaviour]` required (enum) — user, upload, by_rule, none. The team behaviour.
  - `project[project_sessions_attributes][_destroy]` optional (String) — The destroy.
  - `project[evaluations_attributes]` optional (n) — Array of nested elements The evaluations attributes.
  - `project[evaluations_attributes][id]` optional (Fixnum) — The id.
  - `project[evaluations_attributes][kind]` optional (enum) — scale, upload. The kind.
  - `project[evaluations_attributes][_destroy]` optional (String) — The destroy.
  - `project[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `project[attachments_attributes][id]` optional (Fixnum) — The id.
  - `project[attachments_attributes][language_id]` required (Fixnum) — The language id.
  - `project[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `project[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `project[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `project[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.
  - `project[projects_rules_attributes]` optional (n) — Array of nested elements The projects rules attributes.

### `DELETE /v2/projects/:id`
Destroy a project
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/cursus/:cursus_id/projects`
Return all the projects of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, repository, git_id, cached_repository_path. The sort field. Sorted by position asc, id desc by default. More Example: To sort on projects on the fields git_id on a descending order and cached_repository_path on a ascending order: ...&sort=-git_id,cached_repository_path
  - `filter` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, description, repository, git_id, difficulty. Filtering on one or more fields More Example: To filter on projects with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) visible (standard field) exam (standard field) parent_id (standard field) slug (standard field) inherited_team (standard field) position (standard field) has_git (standard field) has_mark (standard field) description (standard field) repository : Filter on repository name. git_id : Filter on git identifier. difficulty : Filter on project sessions difficulty.
  - `range` optional (enum) — id, name, created_at, updated_at, parent_id, slug, position, description, difficulty. Select on a particular range More Example: To range on projects with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id name created_at updated_at parent_id slug position description difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/projects`
Return all the projects of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, repository, git_id, cached_repository_path. The sort field. Sorted by position asc, id desc by default. More Example: To sort on projects on the fields git_id on a descending order and cached_repository_path on a ascending order: ...&sort=-git_id,cached_repository_path
  - `filter` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, description, repository, git_id, difficulty. Filtering on one or more fields More Example: To filter on projects with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) visible (standard field) exam (standard field) parent_id (standard field) slug (standard field) inherited_team (standard field) position (standard field) has_git (standard field) has_mark (standard field) description (standard field) repository : Filter on repository name. git_id : Filter on git identifier. difficulty : Filter on project sessions difficulty.
  - `range` optional (enum) — id, name, created_at, updated_at, parent_id, slug, position, description, difficulty. Select on a particular range More Example: To range on projects with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id name created_at updated_at parent_id slug position description difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects`
Return all the projects
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, repository, git_id, cached_repository_path. The sort field. Sorted by position asc, id desc by default. More Example: To sort on projects on the fields git_id on a descending order and cached_repository_path on a ascending order: ...&sort=-git_id,cached_repository_path
  - `filter` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, description, repository, git_id, difficulty. Filtering on one or more fields More Example: To filter on projects with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) visible (standard field) exam (standard field) parent_id (standard field) slug (standard field) inherited_team (standard field) position (standard field) has_git (standard field) has_mark (standard field) description (standard field) repository : Filter on repository name. git_id : Filter on git identifier. difficulty : Filter on project sessions difficulty.
  - `range` optional (enum) — id, name, created_at, updated_at, parent_id, slug, position, description, difficulty. Select on a particular range More Example: To range on projects with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id name created_at updated_at parent_id slug position description difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/me/projects`
Return all the projects for the current resource owner
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `project_id` optional (String) — The project id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, repository, git_id, cached_repository_path. The sort field. Sorted by position asc, id desc by default. More Example: To sort on projects on the fields git_id on a descending order and cached_repository_path on a ascending order: ...&sort=-git_id,cached_repository_path
  - `filter` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, description, repository, git_id, difficulty. Filtering on one or more fields More Example: To filter on projects with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) visible (standard field) exam (standard field) parent_id (standard field) slug (standard field) inherited_team (standard field) position (standard field) has_git (standard field) has_mark (standard field) description (standard field) repository : Filter on repository name. git_id : Filter on git identifier. difficulty : Filter on project sessions difficulty.
  - `range` optional (enum) — id, name, created_at, updated_at, parent_id, slug, position, description, difficulty. Select on a particular range More Example: To range on projects with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id name created_at updated_at parent_id slug position description difficulty
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `PATCH /v2/projects/:id/retry`
Retry the project user for the current resource owner
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .

### `PUT /v2/projects/:id/retry`
Retry the project user for the current resource owner
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .

### `GET /v2/projects/:id`
Get a project
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/projects/:id`
Update a project
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `project` optional (Hash) — 
  - `project[name]` optional (String) — The name.
  - `project[terminating_after]` optional (String) — The terminating after.
  - `project[exam]` optional (enum) — true, false. Is it exam ? Default to false.
  - `project[has_mark]` optional (enum) — true, false. Is it has mark ? Default to true.
  - `project[repository]` optional (String) — The repository.
  - `project[git_id]` optional (Fixnum) — The git id.
  - `project[has_git]` optional (enum) — true, false. Is it has git ? Default to true.
  - `project[is_subscriptable]` optional (String) — The is subscriptable.
  - `project[inherited_team]` optional (enum) — true, false. Is it inherited team ? Default to false.
  - `project[minimum_mark]` optional (String) — The minimum mark.
  - `project[parent_id]` optional (Fixnum) — The parent id.
  - `project[max_people]` optional (String) — The max people.
  - `project[visible]` optional (enum) — true, false. Is it visible ? Default to false.
  - `project[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `project[campus_ids]` optional (n) — array of Integer The campus ids.
  - `project[authors_user_ids]` optional (n) — array of Integer The authors user ids.
  - `project[notion_ids]` optional (n) — array of Integer The notion ids.
  - `project[project_sessions_attributes]` optional (n) — Array of nested elements The project sessions attributes.
  - `project[project_sessions_attributes][id]` optional (Fixnum) — The id.
  - `project[project_sessions_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `project[project_sessions_attributes][cursus_id]` optional (Fixnum) — The cursus id.
  - `project[project_sessions_attributes][estimate_time]` optional (Fixnum) — The estimate time.
  - `project[project_sessions_attributes][created_at]` optional (DateTime) — The created at.
  - `project[project_sessions_attributes][updated_at]` optional (DateTime) — The updated at.
  - `project[project_sessions_attributes][begin_at]` optional (DateTime) — The begin at.
  - `project[project_sessions_attributes][end_at]` optional (DateTime) — The end at.
  - `project[project_sessions_attributes][max_people]` optional (Fixnum) — The max people.
  - `project[project_sessions_attributes][duration_days]` optional (Fixnum) — The duration days.
  - `project[project_sessions_attributes][terminating_after]` optional (Fixnum) — The terminating after.
  - `project[project_sessions_attributes][solo]` optional (enum) — true, false. Is it solo ? Default to false.
  - `project[project_sessions_attributes][is_subscriptable]` optional (enum) — true, false. Is it is subscriptable ? Default to true.
  - `project[project_sessions_attributes][minimum_mark]` optional (Fixnum) — The minimum mark.
  - `project[project_sessions_attributes][team_behaviour]` optional (enum) — user, upload, by_rule, none. The team behaviour.
  - `project[project_sessions_attributes][_destroy]` optional (String) — The destroy.
  - `project[evaluations_attributes]` optional (n) — Array of nested elements The evaluations attributes.
  - `project[evaluations_attributes][id]` optional (Fixnum) — The id.
  - `project[evaluations_attributes][kind]` optional (enum) — scale, upload. The kind.
  - `project[evaluations_attributes][_destroy]` optional (String) — The destroy.
  - `project[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `project[attachments_attributes][id]` optional (Fixnum) — The id.
  - `project[attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `project[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `project[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `project[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `project[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.
  - `project[projects_rules_attributes]` optional (n) — Array of nested elements The projects rules attributes.

### `PUT /v2/projects/:id`
Update a project
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `project` optional (Hash) — 
  - `project[name]` optional (String) — The name.
  - `project[terminating_after]` optional (String) — The terminating after.
  - `project[exam]` optional (enum) — true, false. Is it exam ? Default to false.
  - `project[has_mark]` optional (enum) — true, false. Is it has mark ? Default to true.
  - `project[repository]` optional (String) — The repository.
  - `project[git_id]` optional (Fixnum) — The git id.
  - `project[has_git]` optional (enum) — true, false. Is it has git ? Default to true.
  - `project[is_subscriptable]` optional (String) — The is subscriptable.
  - `project[inherited_team]` optional (enum) — true, false. Is it inherited team ? Default to false.
  - `project[minimum_mark]` optional (String) — The minimum mark.
  - `project[parent_id]` optional (Fixnum) — The parent id.
  - `project[max_people]` optional (String) — The max people.
  - `project[visible]` optional (enum) — true, false. Is it visible ? Default to false.
  - `project[cursus_ids]` optional (n) — array of Integer The cursus ids.
  - `project[campus_ids]` optional (n) — array of Integer The campus ids.
  - `project[authors_user_ids]` optional (n) — array of Integer The authors user ids.
  - `project[notion_ids]` optional (n) — array of Integer The notion ids.
  - `project[project_sessions_attributes]` optional (n) — Array of nested elements The project sessions attributes.
  - `project[project_sessions_attributes][id]` optional (Fixnum) — The id.
  - `project[project_sessions_attributes][campus_id]` optional (Fixnum) — The campus id.
  - `project[project_sessions_attributes][cursus_id]` optional (Fixnum) — The cursus id.
  - `project[project_sessions_attributes][estimate_time]` optional (Fixnum) — The estimate time.
  - `project[project_sessions_attributes][created_at]` optional (DateTime) — The created at.
  - `project[project_sessions_attributes][updated_at]` optional (DateTime) — The updated at.
  - `project[project_sessions_attributes][begin_at]` optional (DateTime) — The begin at.
  - `project[project_sessions_attributes][end_at]` optional (DateTime) — The end at.
  - `project[project_sessions_attributes][max_people]` optional (Fixnum) — The max people.
  - `project[project_sessions_attributes][duration_days]` optional (Fixnum) — The duration days.
  - `project[project_sessions_attributes][terminating_after]` optional (Fixnum) — The terminating after.
  - `project[project_sessions_attributes][solo]` optional (enum) — true, false. Is it solo ? Default to false.
  - `project[project_sessions_attributes][is_subscriptable]` optional (enum) — true, false. Is it is subscriptable ? Default to true.
  - `project[project_sessions_attributes][minimum_mark]` optional (Fixnum) — The minimum mark.
  - `project[project_sessions_attributes][team_behaviour]` optional (enum) — user, upload, by_rule, none. The team behaviour.
  - `project[project_sessions_attributes][_destroy]` optional (String) — The destroy.
  - `project[evaluations_attributes]` optional (n) — Array of nested elements The evaluations attributes.
  - `project[evaluations_attributes][id]` optional (Fixnum) — The id.
  - `project[evaluations_attributes][kind]` optional (enum) — scale, upload. The kind.
  - `project[evaluations_attributes][_destroy]` optional (String) — The destroy.
  - `project[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `project[attachments_attributes][id]` optional (Fixnum) — The id.
  - `project[attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `project[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `project[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `project[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `project[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.
  - `project[projects_rules_attributes]` optional (n) — Array of nested elements The projects rules attributes.


## projects_users

### `PATCH /v2/projects_users/:id/compile`
Compile a projects user
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_users_id` required (Fixnum) — The projects_user id

### `PUT /v2/projects_users/:id/compile`
Compile a projects user
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_users_id` required (Fixnum) — The projects_user id

### `POST /v2/projects/:project_id/projects_users`
Create a projects user for the given Project
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` required (Fixnum) — The project id.
  - `projects_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.

### `POST /v2/users/:user_id/projects_users`
Create a projects user for the given User
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` required (Fixnum) — The project id.
  - `projects_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.

### `POST /v2/projects_users`
Create a projects user
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` required (Fixnum) — The project id.
  - `projects_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.

### `POST /v2/projects/:project_id/register`
Create a projects user for the given Project
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` required (Fixnum) — The project id.
  - `projects_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.

### `DELETE /v2/projects_users/:id`
Destroy a projects user
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/projects/:project_id/projects_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on projects users
- **Params:**
  - `field` optional (enum) — created_at, updated_at, retriable_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `filter` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status, cursus, campus, retriable, marked. Filtering on one or more fields More Example: To filter on projects users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field) final_mark (standard field) retriable_at (standard field) marked_at (standard field) status (standard field) cursus : Only return projects users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return projects users with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 retriable (standard field) marked (standard field)
  - `range` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status. Select on a particular range More Example: To range on projects users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id user_id created_at updated_at occurrence final_mark retriable_at marked_at status

### `GET /v2/users/:user_id/projects_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on projects users
- **Params:**
  - `field` optional (enum) — created_at, updated_at, retriable_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `filter` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status, cursus, campus, retriable, marked. Filtering on one or more fields More Example: To filter on projects users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field) final_mark (standard field) retriable_at (standard field) marked_at (standard field) status (standard field) cursus : Only return projects users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return projects users with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 retriable (standard field) marked (standard field)
  - `range` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status. Select on a particular range More Example: To range on projects users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id user_id created_at updated_at occurrence final_mark retriable_at marked_at status

### `GET /v2/projects_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on projects users
- **Params:**
  - `field` optional (enum) — created_at, updated_at, retriable_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `filter` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status, cursus, campus, retriable, marked. Filtering on one or more fields More Example: To filter on projects users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field) final_mark (standard field) retriable_at (standard field) marked_at (standard field) status (standard field) cursus : Only return projects users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return projects users with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 retriable (standard field) marked (standard field)
  - `range` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status. Select on a particular range More Example: To range on projects users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id user_id created_at updated_at occurrence final_mark retriable_at marked_at status

### `GET /v2/projects/:project_id/projects_users`
Return all the projects users of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `filter` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status, cursus, campus, retriable, marked. Filtering on one or more fields More Example: To filter on projects users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field) final_mark (standard field) retriable_at (standard field) marked_at (standard field) status (standard field) cursus : Only return projects users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return projects users with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 retriable (standard field) marked (standard field)
  - `range` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status. Select on a particular range More Example: To range on projects users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id user_id created_at updated_at occurrence final_mark retriable_at marked_at status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/projects_users`
Return all the projects users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `filter` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status, cursus, campus, retriable, marked. Filtering on one or more fields More Example: To filter on projects users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field) final_mark (standard field) retriable_at (standard field) marked_at (standard field) status (standard field) cursus : Only return projects users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return projects users with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 retriable (standard field) marked (standard field)
  - `range` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status. Select on a particular range More Example: To range on projects users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id user_id created_at updated_at occurrence final_mark retriable_at marked_at status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects_users`
Return all the projects users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `filter` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status, cursus, campus, retriable, marked. Filtering on one or more fields More Example: To filter on projects users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field) final_mark (standard field) retriable_at (standard field) marked_at (standard field) status (standard field) cursus : Only return projects users with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return projects users with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 retriable (standard field) marked (standard field)
  - `range` optional (enum) — id, project_id, user_id, created_at, updated_at, occurrence, final_mark, retriable_at, marked_at, status. Select on a particular range More Example: To range on projects users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id user_id created_at updated_at occurrence final_mark retriable_at marked_at status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `POST /v2/projects_users/register_childs_and_scales`
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): 42network, Advanced tutor .
- **Params:**
  - `scales` optional (Hash) — The scales to apply to the sub projects
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` required (Fixnum) — The project id.
  - `projects_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.

### `DELETE /v2/projects_users/reset`
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): 42network .
- **Params:**
  - `user_id` required (Fixnum) — The user id
  - `project_id` required (Fixnum) — The project id

### `PATCH /v2/projects_users/:id/retry`
Retry a projects user
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `id` required (Fixnum) — The projects_user id
  - `force` optional (enum) — true, false. Will force the retry if true

### `PUT /v2/projects_users/:id/retry`
Retry a projects user
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor, Advanced staff .
- **Params:**
  - `id` required (Fixnum) — The projects_user id
  - `force` optional (enum) — true, false. Will force the retry if true

### `PATCH /v2/projects_users/scale`
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): 42network .
- **Params:**
  - `user_id` required (Fixnum) — The user id
  - `project_id` required (Fixnum) — The project id
  - `scale` required (Fixnum) — The scale to apply to the project

### `GET /v2/projects_users/:id`
Get a projects user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/projects_users/:id`
Update a projects user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` optional (Fixnum) — The project id.
  - `projects_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.

### `PUT /v2/projects_users/:id`
Update a projects user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `projects_user` optional (Hash) — 
  - `projects_user[id]` optional (Fixnum) — The id.
  - `projects_user[project_id]` optional (Fixnum) — The project id.
  - `projects_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given project.
  - `projects_user[created_at]` optional (DateTime) — The created at.
  - `projects_user[updated_at]` optional (DateTime) — The updated at.
  - `projects_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.
  - `projects_user[final_mark]` optional (Fixnum) — The final mark.
  - `projects_user[retriable_at]` optional (DateTime) — The retriable at.
  - `projects_user[marked_at]` optional (DateTime) — The marked at.
  - `projects_user[status]` optional (String) — The status. Default to unknown.
  - `projects_user[skip_check_permission]` optional (String) — The skip check permission.


## quests

### `POST /v2/quests`
Create a quest
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `quest` optional (Hash) — 
  - `quest[id]` optional (Fixnum) — The id.
  - `quest[name]` required (String) — The name.
  - `quest[slug]` optional (String) — The slug.
  - `quest[kind]` required (enum) — main, optional, mandatory, repeatable, cursus_version. The kind.
  - `quest[internal_name]` optional (String) — The internal name.
  - `quest[duration]` required (Fixnum) — The duration.
  - `quest[ancestry]` optional (String) — The ancestry.
  - `quest[description]` required (String) — The description.
  - `quest[guild_size]` optional (Fixnum) — The guild size.
  - `quest[guild_prct]` optional (Fixnum) — The guild prct.
  - `quest[cursus_id]` required (Fixnum) — The cursus id.
  - `quest[campus_id]` optional (Fixnum) — The campus id.
  - `quest[certificate_id]` optional (Fixnum) — The certificate id.
  - `quest[created_at]` optional (DateTime) — The created at.
  - `quest[updated_at]` optional (DateTime) — The updated at.
  - `quest[grade_id]` optional (Fixnum) — The grade id.
  - `quest[position]` optional (Fixnum) — The position.
  - `quest[tries_number]` required (Fixnum) — The tries number.
  - `quest[success_number]` required (Fixnum) — The success number.
  - `quest[close_on_fail]` optional (enum) — true, false. Is it close on fail ?
  - `quest[mails_from]` required (String) — The mails from.
  - `quest[parent_id]` optional (String) — The parent id.

### `DELETE /v2/quests/:id`
Destroy a quest
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/quests`
Return all the quests
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, slug, kind, internal_name, duration, ancestry, description, guild_size, guild_prct, cursus_id, campus_id, created_at, updated_at, grade_id, position, mails, certificate_id, unlock_all_projects, tries_number, success_number, close_on_fail, mails_from. The sort field. Sorted by id asc by default. More Example: To sort on quests on the fields close_on_fail on a descending order and mails_from on a ascending order: ...&sort=-close_on_fail,mails_from
  - `filter` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Filtering on one or more fields More Example: To filter on quests with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) slug (standard field) kind (standard field) internal_name (standard field) description (standard field) cursus_id (standard field) campus_id (standard field) created_at (standard field) updated_at (standard field) grade_id (standard field) position (standard field)
  - `range` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Select on a particular range More Example: To range on quests with the position field between min_value and max_value: ...&range[position]=min_value,max_value Rangeable fields: id name slug kind internal_name description cursus_id campus_id created_at updated_at grade_id position
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/quests`
Return all the quests of the given Cursus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, slug, kind, internal_name, duration, ancestry, description, guild_size, guild_prct, cursus_id, campus_id, created_at, updated_at, grade_id, position, mails, certificate_id, unlock_all_projects, tries_number, success_number, close_on_fail, mails_from. The sort field. Sorted by id asc by default. More Example: To sort on quests on the fields close_on_fail on a descending order and mails_from on a ascending order: ...&sort=-close_on_fail,mails_from
  - `filter` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Filtering on one or more fields More Example: To filter on quests with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) slug (standard field) kind (standard field) internal_name (standard field) description (standard field) cursus_id (standard field) campus_id (standard field) created_at (standard field) updated_at (standard field) grade_id (standard field) position (standard field)
  - `range` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Select on a particular range More Example: To range on quests with the position field between min_value and max_value: ...&range[position]=min_value,max_value Rangeable fields: id name slug kind internal_name description cursus_id campus_id created_at updated_at grade_id position
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/quests`
Return all the quests of the given Campus
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, slug, kind, internal_name, duration, ancestry, description, guild_size, guild_prct, cursus_id, campus_id, created_at, updated_at, grade_id, position, mails, certificate_id, unlock_all_projects, tries_number, success_number, close_on_fail, mails_from. The sort field. Sorted by id asc by default. More Example: To sort on quests on the fields close_on_fail on a descending order and mails_from on a ascending order: ...&sort=-close_on_fail,mails_from
  - `filter` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Filtering on one or more fields More Example: To filter on quests with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) slug (standard field) kind (standard field) internal_name (standard field) description (standard field) cursus_id (standard field) campus_id (standard field) created_at (standard field) updated_at (standard field) grade_id (standard field) position (standard field)
  - `range` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Select on a particular range More Example: To range on quests with the position field between min_value and max_value: ...&range[position]=min_value,max_value Rangeable fields: id name slug kind internal_name description cursus_id campus_id created_at updated_at grade_id position
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/quests`
Return all the quests of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, slug, kind, internal_name, duration, ancestry, description, guild_size, guild_prct, cursus_id, campus_id, created_at, updated_at, grade_id, position, mails, certificate_id, unlock_all_projects, tries_number, success_number, close_on_fail, mails_from. The sort field. Sorted by id asc by default. More Example: To sort on quests on the fields close_on_fail on a descending order and mails_from on a ascending order: ...&sort=-close_on_fail,mails_from
  - `filter` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Filtering on one or more fields More Example: To filter on quests with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) slug (standard field) kind (standard field) internal_name (standard field) description (standard field) cursus_id (standard field) campus_id (standard field) created_at (standard field) updated_at (standard field) grade_id (standard field) position (standard field)
  - `range` optional (enum) — id, name, slug, kind, internal_name, description, cursus_id, campus_id, created_at, updated_at, grade_id, position. Select on a particular range More Example: To range on quests with the position field between min_value and max_value: ...&range[position]=min_value,max_value Rangeable fields: id name slug kind internal_name description cursus_id campus_id created_at updated_at grade_id position
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/quests/:id`
Get a quest
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/quests/:id`
Update a quest
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `quest` optional (Hash) — 
  - `quest[id]` optional (Fixnum) — The id.
  - `quest[name]` optional (String) — The name.
  - `quest[slug]` optional (String) — The slug.
  - `quest[kind]` optional (enum) — main, optional, mandatory, repeatable, cursus_version. The kind.
  - `quest[internal_name]` optional (String) — The internal name.
  - `quest[duration]` optional (Fixnum) — The duration.
  - `quest[ancestry]` optional (String) — The ancestry.
  - `quest[description]` optional (String) — The description.
  - `quest[guild_size]` optional (Fixnum) — The guild size.
  - `quest[guild_prct]` optional (Fixnum) — The guild prct.
  - `quest[cursus_id]` optional (Fixnum) — The cursus id.
  - `quest[campus_id]` optional (Fixnum) — The campus id.
  - `quest[certificate_id]` optional (Fixnum) — The certificate id.
  - `quest[created_at]` optional (DateTime) — The created at.
  - `quest[updated_at]` optional (DateTime) — The updated at.
  - `quest[grade_id]` optional (Fixnum) — The grade id.
  - `quest[position]` optional (Fixnum) — The position.
  - `quest[tries_number]` optional (Fixnum) — The tries number.
  - `quest[success_number]` optional (Fixnum) — The success number.
  - `quest[close_on_fail]` optional (enum) — true, false. Is it close on fail ?
  - `quest[mails_from]` optional (String) — The mails from.
  - `quest[parent_id]` optional (String) — The parent id.

### `PUT /v2/quests/:id`
Update a quest
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `quest` optional (Hash) — 
  - `quest[id]` optional (Fixnum) — The id.
  - `quest[name]` optional (String) — The name.
  - `quest[slug]` optional (String) — The slug.
  - `quest[kind]` optional (enum) — main, optional, mandatory, repeatable, cursus_version. The kind.
  - `quest[internal_name]` optional (String) — The internal name.
  - `quest[duration]` optional (Fixnum) — The duration.
  - `quest[ancestry]` optional (String) — The ancestry.
  - `quest[description]` optional (String) — The description.
  - `quest[guild_size]` optional (Fixnum) — The guild size.
  - `quest[guild_prct]` optional (Fixnum) — The guild prct.
  - `quest[cursus_id]` optional (Fixnum) — The cursus id.
  - `quest[campus_id]` optional (Fixnum) — The campus id.
  - `quest[certificate_id]` optional (Fixnum) — The certificate id.
  - `quest[created_at]` optional (DateTime) — The created at.
  - `quest[updated_at]` optional (DateTime) — The updated at.
  - `quest[grade_id]` optional (Fixnum) — The grade id.
  - `quest[position]` optional (Fixnum) — The position.
  - `quest[tries_number]` optional (Fixnum) — The tries number.
  - `quest[success_number]` optional (Fixnum) — The success number.
  - `quest[close_on_fail]` optional (enum) — true, false. Is it close on fail ?
  - `quest[mails_from]` optional (String) — The mails from.
  - `quest[parent_id]` optional (String) — The parent id.


## quests_users

### `POST /v2/quests_users`
Create a quests user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `quests_user` optional (Hash) — 
  - `quests_user[quest_id]` required (Fixnum) — The quest id. Must be unique in the scope of a given user.
  - `quests_user[user_id]` required (Fixnum) — The user id.
  - `quests_user[end_at]` optional (DateTime) — The end at.
  - `quests_user[validated_at]` optional (DateTime) — The validated at.
  - `quests_user[prct]` optional (Fixnum) — The prct.
  - `quests_user[advancement]` optional (String) — The advancement.

### `DELETE /v2/quests_users/:id`
Destroy a quests user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/quests_users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on quests users
- **Params:**
  - `field` optional (enum) — created_at, updated_at, end_at, validated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on quests users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at, campus_id, end, validated. Filtering on one or more fields More Example: To filter on quests users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) quest_id (standard field) user_id (standard field) end_at (standard field) validated_at (standard field) prct (standard field) advancement (standard field) created_at (standard field) updated_at (standard field) campus_id : Return quests_users with primary campus of user equal to him. end (standard field) validated (standard field)
  - `range` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. Select on a particular range More Example: To range on quests users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id quest_id user_id end_at validated_at prct advancement created_at updated_at

### `GET /v2/quests/:quest_id/quests_users`
Return all the quests users of the given Quest
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `quest_id` optional (String) — The quest id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on quests users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at, campus_id, end, validated. Filtering on one or more fields More Example: To filter on quests users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) quest_id (standard field) user_id (standard field) end_at (standard field) validated_at (standard field) prct (standard field) advancement (standard field) created_at (standard field) updated_at (standard field) campus_id : Return quests_users with primary campus of user equal to him. end (standard field) validated (standard field)
  - `range` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. Select on a particular range More Example: To range on quests users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id quest_id user_id end_at validated_at prct advancement created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/quests_users`
Return all the quests users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `quest_id` optional (String) — The quest id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on quests users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at, campus_id, end, validated. Filtering on one or more fields More Example: To filter on quests users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) quest_id (standard field) user_id (standard field) end_at (standard field) validated_at (standard field) prct (standard field) advancement (standard field) created_at (standard field) updated_at (standard field) campus_id : Return quests_users with primary campus of user equal to him. end (standard field) validated (standard field)
  - `range` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. Select on a particular range More Example: To range on quests users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id quest_id user_id end_at validated_at prct advancement created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/quests_users`
Return all the quests users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `quest_id` optional (String) — The quest id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on quests users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at, campus_id, end, validated. Filtering on one or more fields More Example: To filter on quests users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) quest_id (standard field) user_id (standard field) end_at (standard field) validated_at (standard field) prct (standard field) advancement (standard field) created_at (standard field) updated_at (standard field) campus_id : Return quests_users with primary campus of user equal to him. end (standard field) validated (standard field)
  - `range` optional (enum) — id, quest_id, user_id, end_at, validated_at, prct, advancement, created_at, updated_at. Select on a particular range More Example: To range on quests users with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id quest_id user_id end_at validated_at prct advancement created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/quests_users/:id`
Get a quests user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/quests_users/:id`
Update a quests user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `quests_user` optional (Hash) — 
  - `quests_user[quest_id]` optional (Fixnum) — The quest id. Must be unique in the scope of a given user.
  - `quests_user[user_id]` optional (Fixnum) — The user id.
  - `quests_user[end_at]` optional (DateTime) — The end at.
  - `quests_user[validated_at]` optional (DateTime) — The validated at.
  - `quests_user[prct]` optional (Fixnum) — The prct.
  - `quests_user[advancement]` optional (String) — The advancement.

### `PUT /v2/quests_users/:id`
Update a quests user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `quests_user` optional (Hash) — 
  - `quests_user[quest_id]` optional (Fixnum) — The quest id. Must be unique in the scope of a given user.
  - `quests_user[user_id]` optional (Fixnum) — The user id.
  - `quests_user[end_at]` optional (DateTime) — The end at.
  - `quests_user[validated_at]` optional (DateTime) — The validated at.
  - `quests_user[prct]` optional (Fixnum) — The prct.
  - `quests_user[advancement]` optional (String) — The advancement.


## roles

### `POST /v2/roles`
Create a role
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `role` optional (Hash) — 
  - `role[name]` optional (String) — The name. Must be unique.
  - `role[description]` required (String) — The description.

### `DELETE /v2/roles/:id`
Destroy a role
- **Auth/scope:** assignment This action requires one of theses roles: Intrateam
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/roles`
Return all the roles
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, description, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on roles on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, name, description, created_at, updated_at. Filtering on one or more fields More Example: To filter on roles with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, name, description, created_at, updated_at. Select on a particular range More Example: To range on roles with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id name description created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/roles`
Return all the roles of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, description, created_at, updated_at. The sort field. Sorted by id desc by default. More Example: To sort on roles on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, name, description, created_at, updated_at. Filtering on one or more fields More Example: To filter on roles with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) description (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, name, description, created_at, updated_at. Select on a particular range More Example: To range on roles with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id name description created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/roles/:id`
Get a role
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/roles/:id`
Update a role
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `role` optional (Hash) — 
  - `role[name]` optional (String) — The name. Must be unique.
  - `role[description]` optional (String) — The description.

### `PUT /v2/roles/:id`
Update a role
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `role` optional (Hash) — 
  - `role[name]` optional (String) — The name. Must be unique.
  - `role[description]` optional (String) — The description.


## roles_entities

### `POST /v2/roles_entities`
Create a roles entity
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `roles_entity` optional (Hash) — 
  - `roles_entity[role_id]` required (Fixnum) — The role id. Must be unique in the scope of a given entity id and entity type.
  - `roles_entity[entity_id]` required (Fixnum) — The entity id.
  - `roles_entity[expires_at]` optional (DateTime) — The expires at.
  - `roles_entity[entity_type]` optional (enum) — Doorkeeper::Application. The entity type.

### `DELETE /v2/roles_entities/:id`
Destroy a roles entity
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/roles_entities/graph(/on/:field(/by/:interval))`
Return grouped temporal data on roles entities
- **Params:**
  - `field` optional (enum) — created_at, updated_at, expires_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type. The sort field. Sorted by id desc by default. More Example: To sort on roles entities on the fields updated_at on a descending order and entity_type on a ascending order: ...&sort=-updated_at,entity_type
  - `filter` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type, expires. Filtering on one or more fields More Example: To filter on roles entities with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) role_id (standard field) entity_id (standard field) expires_at (standard field) created_at (standard field) updated_at (standard field) entity_type (standard field) expires (standard field)
  - `range` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type. Select on a particular range More Example: To range on roles entities with the entity_type field between min_value and max_value: ...&range[entity_type]=min_value,max_value Rangeable fields: id role_id entity_id expires_at created_at updated_at entity_type

### `GET /v2/roles/:role_id/roles_entities`
Return all the roles entities of the given Role
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `role_id` optional (String) — The role id
  - `sort` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type. The sort field. Sorted by id desc by default. More Example: To sort on roles entities on the fields updated_at on a descending order and entity_type on a ascending order: ...&sort=-updated_at,entity_type
  - `filter` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type, expires. Filtering on one or more fields More Example: To filter on roles entities with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) role_id (standard field) entity_id (standard field) expires_at (standard field) created_at (standard field) updated_at (standard field) entity_type (standard field) expires (standard field)
  - `range` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type. Select on a particular range More Example: To range on roles entities with the entity_type field between min_value and max_value: ...&range[entity_type]=min_value,max_value Rangeable fields: id role_id entity_id expires_at created_at updated_at entity_type
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/roles_entities`
Return all the roles entities
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `role_id` optional (String) — The role id
  - `sort` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type. The sort field. Sorted by id desc by default. More Example: To sort on roles entities on the fields updated_at on a descending order and entity_type on a ascending order: ...&sort=-updated_at,entity_type
  - `filter` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type, expires. Filtering on one or more fields More Example: To filter on roles entities with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) role_id (standard field) entity_id (standard field) expires_at (standard field) created_at (standard field) updated_at (standard field) entity_type (standard field) expires (standard field)
  - `range` optional (enum) — id, role_id, entity_id, expires_at, created_at, updated_at, entity_type. Select on a particular range More Example: To range on roles entities with the entity_type field between min_value and max_value: ...&range[entity_type]=min_value,max_value Rangeable fields: id role_id entity_id expires_at created_at updated_at entity_type
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/roles_entities/:id`
Get a roles entity
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/roles_entities/:id`
Update a roles entity
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `roles_entity` optional (Hash) — 
  - `roles_entity[role_id]` optional (Fixnum) — The role id. Must be unique in the scope of a given entity id and entity type.
  - `roles_entity[entity_id]` optional (Fixnum) — The entity id.
  - `roles_entity[expires_at]` optional (DateTime) — The expires at.
  - `roles_entity[entity_type]` optional (enum) — Doorkeeper::Application. The entity type.

### `PUT /v2/roles_entities/:id`
Update a roles entity
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Advanced staff
- **Params:**
  - `id` required (String) — The requested id
  - `roles_entity` optional (Hash) — 
  - `roles_entity[role_id]` optional (Fixnum) — The role id. Must be unique in the scope of a given entity id and entity type.
  - `roles_entity[entity_id]` optional (Fixnum) — The entity id.
  - `roles_entity[expires_at]` optional (DateTime) — The expires at.
  - `roles_entity[entity_type]` optional (enum) — Doorkeeper::Application. The entity type.


## rules

### `POST /v2/rules`
Create a rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `rule` optional (Hash) — 
  - `rule[id]` optional (Fixnum) — The id.
  - `rule[kind]` required (enum) — inscription, retry_inscription, correction, final_compilation, eval_compilation, retriable, group_validation, team_generation, experience_modification. The kind.
  - `rule[name]` required (String) — The name. Must be unique in the scope of a given kind.
  - `rule[description]` optional (String) — The description.
  - `rule[created_at]` optional (DateTime) — The created at.
  - `rule[updated_at]` optional (DateTime) — The updated at.
  - `rule[slug]` optional (String) — The slug.
  - `rule[internal_name]` optional (String) — The internal name.
  - `rule[params_attributes]` optional (n) — Array of nested elements The params attributes.
  - `rule[params_attributes][id]` optional (Fixnum) — The id.
  - `rule[params_attributes][name]` required (String) — The name.
  - `rule[params_attributes][default_value]` optional (String) — The default value.
  - `rule[params_attributes][rule_id]` optional (Fixnum) — The rule id.
  - `rule[params_attributes][data_type]` required (enum) — string, parsed_string, integer, array. The data type.
  - `rule[params_attributes][_destroy]` optional (String) — The destroy.

### `POST /v2/project_sessions/:project_session_id/rules`
Create a rule for the given Project session
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `rule` optional (Hash) — 
  - `rule[id]` optional (Fixnum) — The id.
  - `rule[kind]` required (enum) — inscription, retry_inscription, correction, final_compilation, eval_compilation, retriable, group_validation, team_generation, experience_modification. The kind.
  - `rule[name]` required (String) — The name. Must be unique in the scope of a given kind.
  - `rule[description]` optional (String) — The description.
  - `rule[created_at]` optional (DateTime) — The created at.
  - `rule[updated_at]` optional (DateTime) — The updated at.
  - `rule[slug]` optional (String) — The slug.
  - `rule[internal_name]` optional (String) — The internal name.
  - `rule[params_attributes]` optional (n) — Array of nested elements The params attributes.
  - `rule[params_attributes][id]` optional (Fixnum) — The id.
  - `rule[params_attributes][name]` required (String) — The name.
  - `rule[params_attributes][default_value]` optional (String) — The default value.
  - `rule[params_attributes][rule_id]` optional (Fixnum) — The rule id.
  - `rule[params_attributes][data_type]` required (enum) — string, parsed_string, integer, array. The data type.
  - `rule[params_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/rules/:id`
Destroy a rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/rules`
Return all the rules
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, kind, name, description, created_at, updated_at, slug, internal_name. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on rules on the fields slug on a descending order and internal_name on a ascending order: ...&sort=-slug,internal_name
  - `filter` optional (enum) — id, kind, name, description, created_at, updated_at, slug, internal_name. Filtering on one or more fields More Example: To filter on rules with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) kind (standard field) name (standard field) description (standard field) created_at (standard field) updated_at (standard field) slug (standard field) internal_name (standard field)
  - `range` optional (enum) — id, kind, name, description, created_at, updated_at, slug, internal_name. Select on a particular range More Example: To range on rules with the internal_name field between min_value and max_value: ...&range[internal_name]=min_value,max_value Rangeable fields: id kind name description created_at updated_at slug internal_name
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions/:project_session_id/rules`
Return all the rules of the given Project session
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, kind, name, description, created_at, updated_at, slug, internal_name. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on rules on the fields slug on a descending order and internal_name on a ascending order: ...&sort=-slug,internal_name
  - `filter` optional (enum) — id, kind, name, description, created_at, updated_at, slug, internal_name. Filtering on one or more fields More Example: To filter on rules with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) kind (standard field) name (standard field) description (standard field) created_at (standard field) updated_at (standard field) slug (standard field) internal_name (standard field)
  - `range` optional (enum) — id, kind, name, description, created_at, updated_at, slug, internal_name. Select on a particular range More Example: To range on rules with the internal_name field between min_value and max_value: ...&range[internal_name]=min_value,max_value Rangeable fields: id kind name description created_at updated_at slug internal_name
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/rules/:id`
Get a rule
- **Auth/scope:** assignment This action requires one of theses roles: Basic staff
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/rules/:id`
Update a rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `rule` optional (Hash) — 
  - `rule[id]` optional (Fixnum) — The id.
  - `rule[kind]` optional (enum) — inscription, retry_inscription, correction, final_compilation, eval_compilation, retriable, group_validation, team_generation, experience_modification. The kind.
  - `rule[name]` optional (String) — The name. Must be unique in the scope of a given kind.
  - `rule[description]` optional (String) — The description.
  - `rule[created_at]` optional (DateTime) — The created at.
  - `rule[updated_at]` optional (DateTime) — The updated at.
  - `rule[slug]` optional (String) — The slug.
  - `rule[internal_name]` optional (String) — The internal name.
  - `rule[params_attributes]` optional (n) — Array of nested elements The params attributes.
  - `rule[params_attributes][id]` optional (Fixnum) — The id.
  - `rule[params_attributes][name]` optional (String) — The name.
  - `rule[params_attributes][default_value]` optional (String) — The default value.
  - `rule[params_attributes][rule_id]` optional (Fixnum) — The rule id.
  - `rule[params_attributes][data_type]` optional (enum) — string, parsed_string, integer, array. The data type.
  - `rule[params_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/rules/:id`
Update a rule
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `rule` optional (Hash) — 
  - `rule[id]` optional (Fixnum) — The id.
  - `rule[kind]` optional (enum) — inscription, retry_inscription, correction, final_compilation, eval_compilation, retriable, group_validation, team_generation, experience_modification. The kind.
  - `rule[name]` optional (String) — The name. Must be unique in the scope of a given kind.
  - `rule[description]` optional (String) — The description.
  - `rule[created_at]` optional (DateTime) — The created at.
  - `rule[updated_at]` optional (DateTime) — The updated at.
  - `rule[slug]` optional (String) — The slug.
  - `rule[internal_name]` optional (String) — The internal name.
  - `rule[params_attributes]` optional (n) — Array of nested elements The params attributes.
  - `rule[params_attributes][id]` optional (Fixnum) — The id.
  - `rule[params_attributes][name]` optional (String) — The name.
  - `rule[params_attributes][default_value]` optional (String) — The default value.
  - `rule[params_attributes][rule_id]` optional (Fixnum) — The rule id.
  - `rule[params_attributes][data_type]` optional (enum) — string, parsed_string, integer, array. The data type.
  - `rule[params_attributes][_destroy]` optional (String) — The destroy.


## scale_teams

### `POST /v2/project_sessions/:project_session_id/scale_teams`
Create a scale team for the given Project session
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `scale_team` optional (Hash) — 
  - `scale_team[team_id]` required (Fixnum) — The team id.
  - `scale_team[user_id]` optional (Fixnum) — The user id.
  - `scale_team[scale_id]` required (Fixnum) — The scale id.
  - `scale_team[comment]` required (String) — The comment. Maximum length is 2048.
  - `scale_team[flag_id]` optional (Fixnum) — The flag id.
  - `scale_team[final_mark]` optional (Fixnum) — The final mark.
  - `scale_team[truant_id]` optional (Fixnum) — The truant id.
  - `scale_team[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `scale_team[answers_attributes][question_id]` required (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `scale_team[answers_attributes][value]` optional (Fixnum) — The value.
  - `scale_team[answers_attributes][id]` optional (Fixnum) — The id.

### `POST /v2/scale_teams`
Create a scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `scale_team` optional (Hash) — 
  - `scale_team[team_id]` required (Fixnum) — The team id.
  - `scale_team[user_id]` optional (Fixnum) — The user id.
  - `scale_team[scale_id]` required (Fixnum) — The scale id.
  - `scale_team[comment]` required (String) — The comment. Maximum length is 2048.
  - `scale_team[flag_id]` optional (Fixnum) — The flag id.
  - `scale_team[final_mark]` optional (Fixnum) — The final mark.
  - `scale_team[truant_id]` optional (Fixnum) — The truant id.
  - `scale_team[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `scale_team[answers_attributes][question_id]` required (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `scale_team[answers_attributes][value]` optional (Fixnum) — The value.
  - `scale_team[answers_attributes][id]` optional (Fixnum) — The id.

### `DELETE /v2/project_sessions/:project_session_id/scale_teams/:id`
Destroy a scale team for the given Id, associated with the given Project session
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id

### `DELETE /v2/scale_teams/:id`
Destroy a scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id

### `GET /v2/scale_teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on scale teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at

### `GET /v2/projects/:project_id/scale_teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on scale teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at

### `GET /v2/users/:user_id/scale_teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on scale teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, begin_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at

### `GET /v2/project_sessions/:project_session_id/scale_teams`
Return all the scale teams of the given Project session
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/scale_teams`
Return all the scale teams
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/scale_teams`
Return all the scale teams of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/scale_teams/as_corrector`
Return all the scale teams of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/scale_teams/as_corrected`
Return all the scale teams of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/scale_teams`
Return all the scale teams of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/me/scale_teams/as_corrector`
Return all the scale teams for the current resource owner
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/me/scale_teams/as_corrected`
Return all the scale teams for the current resource owner
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/me/scale_teams`
Return all the scale teams for the current resource owner
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. The sort field. Sorted by begin_at desc, id desc by default. More Example: To sort on scale teams on the fields internship_id on a descending order and filled_at on a ascending order: ...&sort=-internship_id,filled_at
  - `filter` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at, campus_id, cursus_id, feedback_rating, future, filled. Filtering on one or more fields More Example: To filter on scale teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) begin_at (standard field) created_at (standard field) updated_at (standard field) scale_id (standard field) team_id (standard field) comment (standard field) old_feedback (standard field) feedback_rating : . final_mark (standard field) truant_id (standard field) flag_id (standard field) token (standard field) ip (standard field) internship_id (standard field) filled_at (standard field) campus_id : . cursus_id : . feedback_rating : . future : Return only scale teams which begins in the future. Can be one of: true, false filled (standard field)
  - `range` optional (enum) — id, user_id, begin_at, created_at, updated_at, scale_id, team_id, comment, old_feedback, feedback_rating, final_mark, truant_id, flag_id, token, ip, internship_id, filled_at. Select on a particular range More Example: To range on scale teams with the filled_at field between min_value and max_value: ...&range[filled_at]=min_value,max_value Rangeable fields: id user_id begin_at created_at updated_at scale_id team_id comment old_feedback feedback_rating final_mark truant_id flag_id token ip internship_id filled_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `POST /v2/scale_teams/multiple_create`
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `scale_teams` optional (n) — Array of nested elements

### `GET /v2/project_sessions/:project_session_id/scale_teams/:id`
Get a scale team of the given Id, associated with the given Project session
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id

### `GET /v2/scale_teams/:id`
Get a scale team
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id

### `PATCH /v2/project_sessions/:project_session_id/scale_teams/:id`
Update a scale team for the given Id, associated with the given Project session
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id
  - `scale_team` optional (Hash) — 
  - `scale_team[team_id]` optional (Fixnum) — The team id.
  - `scale_team[user_id]` optional (Fixnum) — The user id.
  - `scale_team[scale_id]` optional (Fixnum) — The scale id.
  - `scale_team[comment]` optional (String) — The comment. Maximum length is 2048.
  - `scale_team[flag_id]` optional (Fixnum) — The flag id.
  - `scale_team[final_mark]` optional (Fixnum) — The final mark.
  - `scale_team[truant_id]` optional (Fixnum) — The truant id.
  - `scale_team[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `scale_team[answers_attributes][question_id]` optional (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `scale_team[answers_attributes][value]` optional (Fixnum) — The value.
  - `scale_team[answers_attributes][id]` optional (Fixnum) — The id.

### `PUT /v2/project_sessions/:project_session_id/scale_teams/:id`
Update a scale team for the given Id, associated with the given Project session
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id
  - `scale_team` optional (Hash) — 
  - `scale_team[team_id]` optional (Fixnum) — The team id.
  - `scale_team[user_id]` optional (Fixnum) — The user id.
  - `scale_team[scale_id]` optional (Fixnum) — The scale id.
  - `scale_team[comment]` optional (String) — The comment. Maximum length is 2048.
  - `scale_team[flag_id]` optional (Fixnum) — The flag id.
  - `scale_team[final_mark]` optional (Fixnum) — The final mark.
  - `scale_team[truant_id]` optional (Fixnum) — The truant id.
  - `scale_team[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `scale_team[answers_attributes][question_id]` optional (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `scale_team[answers_attributes][value]` optional (Fixnum) — The value.
  - `scale_team[answers_attributes][id]` optional (Fixnum) — The id.

### `PATCH /v2/scale_teams/:id`
Update a scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id
  - `scale_team` optional (Hash) — 
  - `scale_team[team_id]` optional (Fixnum) — The team id.
  - `scale_team[user_id]` optional (Fixnum) — The user id.
  - `scale_team[scale_id]` optional (Fixnum) — The scale id.
  - `scale_team[comment]` optional (String) — The comment. Maximum length is 2048.
  - `scale_team[flag_id]` optional (Fixnum) — The flag id.
  - `scale_team[final_mark]` optional (Fixnum) — The final mark.
  - `scale_team[truant_id]` optional (Fixnum) — The truant id.
  - `scale_team[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `scale_team[answers_attributes][question_id]` optional (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `scale_team[answers_attributes][value]` optional (Fixnum) — The value.
  - `scale_team[answers_attributes][id]` optional (Fixnum) — The id.

### `PUT /v2/scale_teams/:id`
Update a scale team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `id` required (String) — The requested id
  - `scale_team` optional (Hash) — 
  - `scale_team[team_id]` optional (Fixnum) — The team id.
  - `scale_team[user_id]` optional (Fixnum) — The user id.
  - `scale_team[scale_id]` optional (Fixnum) — The scale id.
  - `scale_team[comment]` optional (String) — The comment. Maximum length is 2048.
  - `scale_team[flag_id]` optional (Fixnum) — The flag id.
  - `scale_team[final_mark]` optional (Fixnum) — The final mark.
  - `scale_team[truant_id]` optional (Fixnum) — The truant id.
  - `scale_team[answers_attributes]` optional (n) — Array of nested elements The answers attributes.
  - `scale_team[answers_attributes][question_id]` optional (Fixnum) — The question id. Must be unique in the scope of a given scalable entity.
  - `scale_team[answers_attributes][value]` optional (Fixnum) — The value.
  - `scale_team[answers_attributes][id]` optional (Fixnum) — The id.


## scales

### `POST /v2/scales`
Create a scale
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `scale` optional (Hash) — 
  - `scale[name]` required (String) — The name. Must be unique in the scope of a given evaluation.
  - `scale[lg]` optional (String) — The language id.
  - `scale[is_primary]` optional (enum) — true, false. Is it is primary ? Default to false.
  - `scale[is_external]` optional (enum) — true, false. Is it is external ? Default to false.
  - `scale[manual_subscription]` optional (enum) — true, false. Is it manual subscription ? Default to false.
  - `scale[comment]` optional (String) — The comment.
  - `scale[introduction_md]` optional (String) — The introduction md.
  - `scale[disclaimer_md]` optional (String) — The disclaimer md.
  - `scale[guidelines_md]` required (String) — The guidelines md.
  - `scale[correction_number]` required (Fixnum) — The correction number.
  - `scale[duration]` required (Fixnum) — The duration.
  - `scale[free]` optional (enum) — true, false. Is it free ?
  - `scale[evaluation_id]` optional (Fixnum) — The evaluation id.
  - `scale[flag_ids]` optional (n) — array of Integer The flag ids.
  - `scale[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `scale[attachments_attributes][id]` optional (Fixnum) — The id.
  - `scale[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `scale[attachments_attributes][language_id]` required (Fixnum) — The language id.
  - `scale[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `scale[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `scale[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.
  - `scale[sections_attributes]` optional (n) — Array of nested elements The sections attributes.
  - `scale[sections_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][description]` optional (String) — The description.
  - `scale[sections_attributes][questions_attributes]` optional (n) — Array of nested elements The questions attributes.
  - `scale[sections_attributes][questions_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][questions_attributes][name]` required (String) — The name.
  - `scale[sections_attributes][questions_attributes][kind]` required (enum) — standard, bonus. The kind.
  - `scale[sections_attributes][questions_attributes][rating]` required (enum) — bool, multi, text. The rating.
  - `scale[sections_attributes][questions_attributes][guidelines]` required (String) — The guidelines.
  - `scale[sections_attributes][questions_attributes][_destroy]` optional (String) — The destroy.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes]` optional (n) — Array of nested elements The questions skills attributes.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][skill_id]` required (Fixnum) — The skill id.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][percentage]` required (Fixnum) — The percentage.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][_destroy]` optional (String) — The destroy.
  - `scale[sections_attributes][name]` required (String) — The name.
  - `scale[sections_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/scales/:id`
Destroy a scale
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/project_sessions/:project_session_id/scales`
Return all the scales of the given Project session
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. The sort field. Sorted by name asc, id desc by default. More Example: To sort on scales on the fields is_external on a descending order and free on a ascending order: ...&sort=-is_external,free
  - `filter` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Filtering on one or more fields More Example: To filter on scales with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) comment (standard field) introduction_md (standard field) disclaimer_md (standard field) guidelines_md (standard field) created_at (standard field) updated_at (standard field) evaluation_id (standard field) is_primary (standard field) correction_number (standard field) duration (standard field) manual_subscription (standard field) is_external (standard field) free (standard field)
  - `range` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Select on a particular range More Example: To range on scales with the free field between min_value and max_value: ...&range[free]=min_value,max_value Rangeable fields: id name comment introduction_md disclaimer_md guidelines_md created_at updated_at evaluation_id is_primary correction_number duration manual_subscription is_external free
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/scales`
Return all the scales
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. The sort field. Sorted by name asc, id desc by default. More Example: To sort on scales on the fields is_external on a descending order and free on a ascending order: ...&sort=-is_external,free
  - `filter` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Filtering on one or more fields More Example: To filter on scales with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) comment (standard field) introduction_md (standard field) disclaimer_md (standard field) guidelines_md (standard field) created_at (standard field) updated_at (standard field) evaluation_id (standard field) is_primary (standard field) correction_number (standard field) duration (standard field) manual_subscription (standard field) is_external (standard field) free (standard field)
  - `range` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Select on a particular range More Example: To range on scales with the free field between min_value and max_value: ...&range[free]=min_value,max_value Rangeable fields: id name comment introduction_md disclaimer_md guidelines_md created_at updated_at evaluation_id is_primary correction_number duration manual_subscription is_external free
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/scales`
Return all the scales of the given Project
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. The sort field. Sorted by name asc, id desc by default. More Example: To sort on scales on the fields is_external on a descending order and free on a ascending order: ...&sort=-is_external,free
  - `filter` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Filtering on one or more fields More Example: To filter on scales with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) comment (standard field) introduction_md (standard field) disclaimer_md (standard field) guidelines_md (standard field) created_at (standard field) updated_at (standard field) evaluation_id (standard field) is_primary (standard field) correction_number (standard field) duration (standard field) manual_subscription (standard field) is_external (standard field) free (standard field)
  - `range` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Select on a particular range More Example: To range on scales with the free field between min_value and max_value: ...&range[free]=min_value,max_value Rangeable fields: id name comment introduction_md disclaimer_md guidelines_md created_at updated_at evaluation_id is_primary correction_number duration manual_subscription is_external free
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/scales`
Return all the scales of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `project_session_id` optional (String) — The project_session id
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. The sort field. Sorted by name asc, id desc by default. More Example: To sort on scales on the fields is_external on a descending order and free on a ascending order: ...&sort=-is_external,free
  - `filter` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Filtering on one or more fields More Example: To filter on scales with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) comment (standard field) introduction_md (standard field) disclaimer_md (standard field) guidelines_md (standard field) created_at (standard field) updated_at (standard field) evaluation_id (standard field) is_primary (standard field) correction_number (standard field) duration (standard field) manual_subscription (standard field) is_external (standard field) free (standard field)
  - `range` optional (enum) — id, name, comment, introduction_md, disclaimer_md, guidelines_md, created_at, updated_at, evaluation_id, is_primary, correction_number, duration, manual_subscription, is_external, free. Select on a particular range More Example: To range on scales with the free field between min_value and max_value: ...&range[free]=min_value,max_value Rangeable fields: id name comment introduction_md disclaimer_md guidelines_md created_at updated_at evaluation_id is_primary correction_number duration manual_subscription is_external free
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/scales/:id`
Get a scale
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/scales/:id`
Update a scale
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `scale` optional (Hash) — 
  - `scale[name]` optional (String) — The name. Must be unique in the scope of a given evaluation.
  - `scale[lg]` optional (String) — The language id.
  - `scale[is_primary]` optional (enum) — true, false. Is it is primary ? Default to false.
  - `scale[is_external]` optional (enum) — true, false. Is it is external ? Default to false.
  - `scale[manual_subscription]` optional (enum) — true, false. Is it manual subscription ? Default to false.
  - `scale[comment]` optional (String) — The comment.
  - `scale[introduction_md]` optional (String) — The introduction md.
  - `scale[disclaimer_md]` optional (String) — The disclaimer md.
  - `scale[guidelines_md]` optional (String) — The guidelines md.
  - `scale[correction_number]` optional (Fixnum) — The correction number.
  - `scale[duration]` optional (Fixnum) — The duration.
  - `scale[free]` optional (enum) — true, false. Is it free ?
  - `scale[evaluation_id]` optional (Fixnum) — The evaluation id.
  - `scale[flag_ids]` optional (n) — array of Integer The flag ids.
  - `scale[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `scale[attachments_attributes][id]` optional (Fixnum) — The id.
  - `scale[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `scale[attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `scale[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `scale[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `scale[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.
  - `scale[sections_attributes]` optional (n) — Array of nested elements The sections attributes.
  - `scale[sections_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][description]` optional (String) — The description.
  - `scale[sections_attributes][questions_attributes]` optional (n) — Array of nested elements The questions attributes.
  - `scale[sections_attributes][questions_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][questions_attributes][name]` optional (String) — The name.
  - `scale[sections_attributes][questions_attributes][kind]` optional (enum) — standard, bonus. The kind.
  - `scale[sections_attributes][questions_attributes][rating]` optional (enum) — bool, multi, text. The rating.
  - `scale[sections_attributes][questions_attributes][guidelines]` optional (String) — The guidelines.
  - `scale[sections_attributes][questions_attributes][_destroy]` optional (String) — The destroy.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes]` optional (n) — Array of nested elements The questions skills attributes.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][skill_id]` optional (Fixnum) — The skill id.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][percentage]` optional (Fixnum) — The percentage.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][_destroy]` optional (String) — The destroy.
  - `scale[sections_attributes][name]` optional (String) — The name.
  - `scale[sections_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/scales/:id`
Update a scale
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `scale` optional (Hash) — 
  - `scale[name]` optional (String) — The name. Must be unique in the scope of a given evaluation.
  - `scale[lg]` optional (String) — The language id.
  - `scale[is_primary]` optional (enum) — true, false. Is it is primary ? Default to false.
  - `scale[is_external]` optional (enum) — true, false. Is it is external ? Default to false.
  - `scale[manual_subscription]` optional (enum) — true, false. Is it manual subscription ? Default to false.
  - `scale[comment]` optional (String) — The comment.
  - `scale[introduction_md]` optional (String) — The introduction md.
  - `scale[disclaimer_md]` optional (String) — The disclaimer md.
  - `scale[guidelines_md]` optional (String) — The guidelines md.
  - `scale[correction_number]` optional (Fixnum) — The correction number.
  - `scale[duration]` optional (Fixnum) — The duration.
  - `scale[free]` optional (enum) — true, false. Is it free ?
  - `scale[evaluation_id]` optional (Fixnum) — The evaluation id.
  - `scale[flag_ids]` optional (n) — array of Integer The flag ids.
  - `scale[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `scale[attachments_attributes][id]` optional (Fixnum) — The id.
  - `scale[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `scale[attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `scale[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `scale[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `scale[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.
  - `scale[sections_attributes]` optional (n) — Array of nested elements The sections attributes.
  - `scale[sections_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][description]` optional (String) — The description.
  - `scale[sections_attributes][questions_attributes]` optional (n) — Array of nested elements The questions attributes.
  - `scale[sections_attributes][questions_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][questions_attributes][name]` optional (String) — The name.
  - `scale[sections_attributes][questions_attributes][kind]` optional (enum) — standard, bonus. The kind.
  - `scale[sections_attributes][questions_attributes][rating]` optional (enum) — bool, multi, text. The rating.
  - `scale[sections_attributes][questions_attributes][guidelines]` optional (String) — The guidelines.
  - `scale[sections_attributes][questions_attributes][_destroy]` optional (String) — The destroy.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes]` optional (n) — Array of nested elements The questions skills attributes.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][id]` optional (Fixnum) — The id.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][skill_id]` optional (Fixnum) — The skill id.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][percentage]` optional (Fixnum) — The percentage.
  - `scale[sections_attributes][questions_attributes][questions_skills_attributes][_destroy]` optional (String) — The destroy.
  - `scale[sections_attributes][name]` optional (String) — The name.
  - `scale[sections_attributes][_destroy]` optional (String) — The destroy.


## scores

### `POST /v2/coalitions/:coalition_id/scores`
Create a score for the given Coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `coalition_id` required (String) — The coalition id or slug

### `DELETE /v2/coalitions/:coalition_id/scores/:id`
Destroy a score for the given Id, associated with the given Coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `coalition_id` required (String) — The coalition id or slug
  - `id` required (String) — The requested id

### `GET /v2/scores`
Return all the scores
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, coalitions_user_id, calculation_id, reason, created_at, updated_at, coalition_id, scoreable_id, scoreable_type, value. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on scores on the fields scoreable_type on a descending order and value on a ascending order: ...&sort=-scoreable_type,value
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/coalitions/:coalition_id/scores`
Return all the scores of the given Coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, coalitions_user_id, calculation_id, reason, created_at, updated_at, coalition_id, scoreable_id, scoreable_type, value. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on scores on the fields scoreable_type on a descending order and value on a ascending order: ...&sort=-scoreable_type,value
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/coalitions_users/:coalitions_user_id/scores`
Return all the scores of the given Coalitions user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, coalitions_user_id, calculation_id, reason, created_at, updated_at, coalition_id, scoreable_id, scoreable_type, value. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on scores on the fields scoreable_type on a descending order and value on a ascending order: ...&sort=-scoreable_type,value
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/blocs/:bloc_id/scores`
Return all the scores of the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id
  - `sort` optional (enum) — id, coalitions_user_id, calculation_id, reason, created_at, updated_at, coalition_id, scoreable_id, scoreable_type, value. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on scores on the fields scoreable_type on a descending order and value on a ascending order: ...&sort=-scoreable_type,value
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/scores/:id`
Get a score
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id

### `GET /v2/coalitions/:coalition_id/scores/:id`
Get a score of the given Id, associated with the given Coalition
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id

### `GET /v2/coalitions_users/:coalitions_user_id/scores/:id`
Get a score of the given Id, associated with the given Coalitions user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id

### `GET /v2/blocs/:bloc_id/scores/:id`
Get a score of the given Id, associated with the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `coalition_id` optional (String) — The coalition id or slug
  - `coalitions_user_id` optional (String) — The coalitions_user id
  - `bloc_id` optional (String) — The bloc id


## search

### `POST /v2/search/projects`
Search projects
- **Auth/scope:** assignment This action requires one of theses roles: 42network This resource is paginated by 30 items
- **Params:**
  - `query` optional (String) — A free text search on the name and the slug
  - `filter` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, description, repository, git_id, difficulty. Filtering on one or more fields More Example: To filter on search with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) visible (standard field) exam (standard field) parent_id (standard field) slug (standard field) inherited_team (standard field) position (standard field) has_git (standard field) has_mark (standard field) description (standard field) repository : Filter on repository name. git_id : Filter on git identifier. difficulty : Filter on project sessions difficulty.
  - `search` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, description. Search on one or more fields More Example: To search on search with the description matching the word 'framework': ...&search=in:description%20framework
  - `range` optional (enum) — id, name, created_at, updated_at, parent_id, slug, position, description, difficulty. Select on a particular range More Example: To range on search with the difficulty field between min_value and max_value: ...&range[difficulty]=min_value,max_value Rangeable fields: id name created_at updated_at parent_id slug position description difficulty
  - `sort` optional (enum) — id, name, created_at, updated_at, visible, exam, parent_id, slug, inherited_team, position, has_git, has_mark, repository, git_id, cached_repository_path. The sort field. Sorted by position asc, id desc by default. More Example: To sort on search on the fields git_id on a descending order and cached_repository_path on a ascending order: ...&sort=-git_id,cached_repository_path
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `POST /v2/search/users`
Search users
- **Auth/scope:** assignment This action requires one of theses roles: 42network This resource is paginated by 30 items
- **Params:**
  - `query` optional (String) — A free text search on the login, first name, usual first name and last name
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on search with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `search` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Search on one or more fields More Example: To search on search with the status matching the word 'framework': ...&search=in:status%20framework
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on search with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on search on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100


## skills

### `POST /v2/skills`
Create a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `skill` optional (Hash) — 
  - `skill[name]` required (String) — The name. Must be unique.

### `POST /v2/skills`
Create a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `skill` optional (Hash) — 
  - `skill[name]` required (String) — The name. Must be unique.

### `DELETE /v2/skills/:id`
Destroy a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `id` required (String) — The requested id

### `DELETE /v2/skills/:id`
Destroy a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/skills`
Return all the skills
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, slug. The sort field. Sorted by name asc, id desc by default. More Example: To sort on skills on the fields updated_at on a descending order and slug on a ascending order: ...&sort=-updated_at,slug
  - `filter` optional (enum) — id, name, created_at, updated_at, slug. Filtering on one or more fields More Example: To filter on skills with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug. Select on a particular range More Example: To range on skills with the slug field between min_value and max_value: ...&range[slug]=min_value,max_value Rangeable fields: id name created_at updated_at slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/skills`
Return all the skills of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, slug. The sort field. Sorted by name asc, id desc by default. More Example: To sort on skills on the fields updated_at on a descending order and slug on a ascending order: ...&sort=-updated_at,slug
  - `filter` optional (enum) — id, name, created_at, updated_at, slug. Filtering on one or more fields More Example: To filter on skills with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug. Select on a particular range More Example: To range on skills with the slug field between min_value and max_value: ...&range[slug]=min_value,max_value Rangeable fields: id name created_at updated_at slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/skills`
Return all the skills
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, slug. The sort field. Sorted by name asc, id desc by default. More Example: To sort on skills on the fields updated_at on a descending order and slug on a ascending order: ...&sort=-updated_at,slug
  - `filter` optional (enum) — id, name, created_at, updated_at, slug. Filtering on one or more fields More Example: To filter on skills with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field)
  - `range` optional (enum) — id, name, created_at, updated_at, slug. Select on a particular range More Example: To range on skills with the slug field between min_value and max_value: ...&range[slug]=min_value,max_value Rangeable fields: id name created_at updated_at slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/skills/:id`
Get a skill
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/skills/:id`
Get a skill
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/skills/:id`
Update a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `id` required (String) — The requested id
  - `skill` optional (Hash) — 
  - `skill[name]` optional (String) — The name. Must be unique.

### `PUT /v2/skills/:id`
Update a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `id` required (String) — The requested id
  - `skill` optional (Hash) — 
  - `skill[name]` optional (String) — The name. Must be unique.

### `PATCH /v2/skills/:id`
Update a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `id` required (String) — The requested id
  - `skill` optional (Hash) — 
  - `skill[name]` optional (String) — The name. Must be unique.

### `PUT /v2/skills/:id`
Update a skill
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, 42network
- **Params:**
  - `id` required (String) — The requested id
  - `skill` optional (Hash) — 
  - `skill[name]` optional (String) — The name. Must be unique.


## slots

### `POST /v2/slots`
Create a slot
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `slot` optional (Hash) — 
  - `slot[user_id]` required (Fixnum) — The user wich set this slot
  - `slot[begin_at]` required (DateTime) — The beginning of the slot
  - `slot[end_at]` required (DateTime) — The ending of the slot
  - `slot[scale_team_id]` optional (Fixnum) — The defense linked to this slot

### `DELETE /v2/slots/:id`
Destroy a slot
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/slots/graph(/on/:field(/by/:interval))`
Return grouped temporal data on slots
- **Params:**
  - `field` optional (enum) — created_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at

### `GET /v2/projects/:project_id/slots/graph(/on/:field(/by/:interval))`
Return grouped temporal data on slots
- **Params:**
  - `field` optional (enum) — created_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at

### `GET /v2/users/:user_id/slots/graph(/on/:field(/by/:interval))`
Return grouped temporal data on slots
- **Params:**
  - `field` optional (enum) — created_at, begin_at, end_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at

### `GET /v2/slots`
Return all the slots
- **Auth/scope:** This resource is paginated by 30 items This action requires a token resource owner scoped on projects with enough privileges .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/slots`
Return all the slots of the given Project
- **Auth/scope:** This resource is paginated by 30 items This action requires a token resource owner scoped on projects with enough privileges .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/slots`
Return all the slots of the given User
- **Auth/scope:** This resource is paginated by 30 items This action requires a token resource owner scoped on projects with enough privileges .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/me/slots`
Return all the slots for the current resource owner
- **Auth/scope:** This resource is paginated by 30 items This action requires a token resource owner scoped on projects with enough privileges .
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, begin_at, end_at, user_id, created_at, scale_team_id. The sort field. Sorted by id desc by default. More Example: To sort on slots on the fields created_at on a descending order and scale_team_id on a ascending order: ...&sort=-created_at,scale_team_id
  - `filter` optional (enum) — id, begin_at, end_at, created_at, campus_id, future, end. Filtering on one or more fields More Example: To filter on slots with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) begin_at (standard field) end_at (standard field) created_at (standard field) campus_id : . future : Return only slots which begins in the future. Can be one of: true, false end (standard field)
  - `range` optional (enum) — id, begin_at, end_at, created_at. Select on a particular range More Example: To range on slots with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id begin_at end_at created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/slots/:id`
Get a slot
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges .
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/slots/:id`
Update a slot
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id
  - `slot` optional (Hash) — 
  - `slot[user_id]` optional (Fixnum) — The user wich set this slot
  - `slot[begin_at]` optional (DateTime) — The beginning of the slot
  - `slot[end_at]` optional (DateTime) — The ending of the slot
  - `slot[scale_team_id]` optional (Fixnum) — The defense linked to this slot

### `PUT /v2/slots/:id`
Update a slot
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id
  - `slot` optional (Hash) — 
  - `slot[user_id]` optional (Fixnum) — The user wich set this slot
  - `slot[begin_at]` optional (DateTime) — The beginning of the slot
  - `slot[end_at]` optional (DateTime) — The ending of the slot
  - `slot[scale_team_id]` optional (Fixnum) — The defense linked to this slot


## squads

### `POST /v2/blocs/:bloc_id/squads`
Create a squad for the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` required (String) — The bloc id
  - `squad` optional (Hash) — 
  - `squad[bloc_id]` required (Fixnum) — The bloc id
  - `squad[locked_at]` optional (DateTime) — When the squad was locked
  - `squad[squads_users_attributes]` optional (n) — array of any type The users registration to this squad

### `DELETE /v2/blocs/:bloc_id/squads/:id`
Destroy a squad for the given Id, associated with the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `id` required (String) — The requested id

### `DELETE /v2/squads/:id`
Destroy a squad
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `id` required (String) — The requested id

### `GET /v2/blocs/:bloc_id/squads`
Return all the squads of the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `bloc_id` required (String) — The bloc id
  - `sort` optional (enum) — id, bloc_id, locked_at, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on squads on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, bloc_id, locked_at, created_at, updated_at, locked. Filtering on one or more fields More Example: To filter on squads with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) bloc_id (standard field) locked_at (standard field) created_at (standard field) updated_at (standard field) locked (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/blocs/:bloc_id/squads/:id`
Get a squad of the given Id, associated with the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `id` required (String) — The requested id

### `GET /v2/squads/:id`
Get a squad
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `id` required (String) — The requested id

### `PATCH /v2/squads/:id`
Update a squad
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PUT /v2/squads/:id`
Update a squad
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id


## squads_users

### `POST /v2/blocs/:bloc_id/squads_users`
Create a squads user for the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` required (String) — The bloc id

### `DELETE /v2/blocs/:bloc_id/squads_users/:id`
Destroy a squads user for the given Id, associated with the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `id` required (String) — The requested id

### `DELETE /v2/squads_users/:id`
Destroy a squads user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `bloc_id` optional (String) — The bloc id
  - `id` required (String) — The requested id

### `GET /v2/blocs/:bloc_id/squads_users`
Return all the squads users of the given Bloc
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor This resource is paginated by 30 items
- **Params:**
  - `bloc_id` required (String) — The bloc id
  - `sort` optional (enum) — id, squad_id, user_id, leader, validated, created_at, updated_at. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on squads users on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, squad_id, user_id, leader, validated, created_at, updated_at. Filtering on one or more fields More Example: To filter on squads users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) squad_id (standard field) user_id (standard field) leader (standard field) validated (standard field) created_at (standard field) updated_at (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `PATCH /v2/squads_users/:id`
Update a squads user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PUT /v2/squads_users/:id`
Update a squads user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id


## subnotions

### `POST /v2/subnotions`
Create a subnotion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `subnotion` optional (Hash) — 
  - `subnotion[id]` optional (Fixnum) — The id.
  - `subnotion[name]` required (String) — The name. Must be unique in the scope of a given notion.
  - `subnotion[notion_id]` optional (Fixnum) — The notion id.
  - `subnotion[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `subnotion[attachments_attributes][id]` optional (Fixnum) — The id.
  - `subnotion[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `subnotion[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `subnotion[attachments_attributes][language_id]` required (Fixnum) — The language id.
  - `subnotion[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `subnotion[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.

### `DELETE /v2/subnotions/:id`
Destroy a subnotion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/notions/:notion_id/subnotions`
Return all the subnotions of the given Notion
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `notion_id` optional (String) — The notion id or slug
  - `sort` optional (enum) — id, notion_id, name, created_at, updated_at, slug, position. The sort field. Sorted by name asc, id desc by default. More Example: To sort on subnotions on the fields slug on a descending order and position on a ascending order: ...&sort=-slug,position
  - `filter` optional (enum) — id, notion_id, name, created_at, updated_at, slug, position. Filtering on one or more fields More Example: To filter on subnotions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) notion_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field) position (standard field)
  - `range` optional (enum) — id, notion_id, name, created_at, updated_at, slug, position. Select on a particular range More Example: To range on subnotions with the position field between min_value and max_value: ...&range[position]=min_value,max_value Rangeable fields: id notion_id name created_at updated_at slug position
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/subnotions`
Return all the subnotions
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `notion_id` optional (String) — The notion id or slug
  - `sort` optional (enum) — id, notion_id, name, created_at, updated_at, slug, position. The sort field. Sorted by name asc, id desc by default. More Example: To sort on subnotions on the fields slug on a descending order and position on a ascending order: ...&sort=-slug,position
  - `filter` optional (enum) — id, notion_id, name, created_at, updated_at, slug, position. Filtering on one or more fields More Example: To filter on subnotions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) notion_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) slug (standard field) position (standard field)
  - `range` optional (enum) — id, notion_id, name, created_at, updated_at, slug, position. Select on a particular range More Example: To range on subnotions with the position field between min_value and max_value: ...&range[position]=min_value,max_value Rangeable fields: id notion_id name created_at updated_at slug position
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/subnotions/:id`
Get a subnotion
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/subnotions/:id`
Update a subnotion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `id` required (String) — The requested id
  - `subnotion` optional (Hash) — 
  - `subnotion[id]` optional (Fixnum) — The id.
  - `subnotion[name]` optional (String) — The name. Must be unique in the scope of a given notion.
  - `subnotion[notion_id]` optional (Fixnum) — The notion id.
  - `subnotion[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `subnotion[attachments_attributes][id]` optional (Fixnum) — The id.
  - `subnotion[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `subnotion[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `subnotion[attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `subnotion[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `subnotion[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.

### `PUT /v2/subnotions/:id`
Update a subnotion
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor, Video manager
- **Params:**
  - `id` required (String) — The requested id
  - `subnotion` optional (Hash) — 
  - `subnotion[id]` optional (Fixnum) — The id.
  - `subnotion[name]` optional (String) — The name. Must be unique in the scope of a given notion.
  - `subnotion[notion_id]` optional (Fixnum) — The notion id.
  - `subnotion[attachments_attributes]` optional (n) — Array of nested elements The attachments attributes.
  - `subnotion[attachments_attributes][id]` optional (Fixnum) — The id.
  - `subnotion[attachments_attributes][kind]` optional (enum) — code, pdf, link, document, video. The kind.
  - `subnotion[attachments_attributes][_destroy]` optional (String) — The destroy.
  - `subnotion[attachments_attributes][language_id]` optional (Fixnum) — The language id.
  - `subnotion[attachments_attributes][untranslatable]` optional (enum) — true, false. Is it untranslatable ? Default to false.
  - `subnotion[attachments_attributes][attachable_attributes]` optional (n) — Array of nested elements The attachable attributes.


## tags

### `POST /v2/tags`
Create a tag
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `tag` optional (Hash) — 
  - `tag[name]` required (String) — The name. Must be unique.
  - `tag[tags_users_attributes]` optional (n) — Array of nested elements The tags users attributes.
  - `tag[tags_users_attributes][user_id]` required (Fixnum) — The user id.
  - `tag[tags_users_attributes][id]` optional (Fixnum) — The id.
  - `tag[tags_users_attributes][_destroy]` optional (String) — The destroy.
  - `tag[cursus_ids]` optional (n) — array of Integer The cursus ids.

### `DELETE /v2/tags/:id`
Destroy a tag
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/projects/:project_id/tags`
Return all the tags of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `issue_id` optional (String) — The issue id
  - `notion_id` optional (String) — The notion id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. The sort field. Sorted by name asc, id desc by default. More Example: To sort on tags on the fields kind on a descending order and description on a ascending order: ...&sort=-kind,description
  - `filter` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description, cursus_id. Filtering on one or more fields More Example: To filter on tags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) pinner_id (standard field) kind (standard field) description (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. Select on a particular range More Example: To range on tags with the description field between min_value and max_value: ...&range[description]=min_value,max_value Rangeable fields: id name created_at updated_at pinner_id kind description
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/issues/:issue_id/tags`
Return all the tags of the given Issue
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `issue_id` optional (String) — The issue id
  - `notion_id` optional (String) — The notion id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. The sort field. Sorted by name asc, id desc by default. More Example: To sort on tags on the fields kind on a descending order and description on a ascending order: ...&sort=-kind,description
  - `filter` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description, cursus_id. Filtering on one or more fields More Example: To filter on tags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) pinner_id (standard field) kind (standard field) description (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. Select on a particular range More Example: To range on tags with the description field between min_value and max_value: ...&range[description]=min_value,max_value Rangeable fields: id name created_at updated_at pinner_id kind description
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/notions/:notion_id/tags`
Return all the tags of the given Notion
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `issue_id` optional (String) — The issue id
  - `notion_id` optional (String) — The notion id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. The sort field. Sorted by name asc, id desc by default. More Example: To sort on tags on the fields kind on a descending order and description on a ascending order: ...&sort=-kind,description
  - `filter` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description, cursus_id. Filtering on one or more fields More Example: To filter on tags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) pinner_id (standard field) kind (standard field) description (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. Select on a particular range More Example: To range on tags with the description field between min_value and max_value: ...&range[description]=min_value,max_value Rangeable fields: id name created_at updated_at pinner_id kind description
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/tags`
Return all the tags of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `issue_id` optional (String) — The issue id
  - `notion_id` optional (String) — The notion id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. The sort field. Sorted by name asc, id desc by default. More Example: To sort on tags on the fields kind on a descending order and description on a ascending order: ...&sort=-kind,description
  - `filter` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description, cursus_id. Filtering on one or more fields More Example: To filter on tags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) pinner_id (standard field) kind (standard field) description (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. Select on a particular range More Example: To range on tags with the description field between min_value and max_value: ...&range[description]=min_value,max_value Rangeable fields: id name created_at updated_at pinner_id kind description
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/tags`
Return all the tags of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `issue_id` optional (String) — The issue id
  - `notion_id` optional (String) — The notion id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. The sort field. Sorted by name asc, id desc by default. More Example: To sort on tags on the fields kind on a descending order and description on a ascending order: ...&sort=-kind,description
  - `filter` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description, cursus_id. Filtering on one or more fields More Example: To filter on tags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) pinner_id (standard field) kind (standard field) description (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. Select on a particular range More Example: To range on tags with the description field between min_value and max_value: ...&range[description]=min_value,max_value Rangeable fields: id name created_at updated_at pinner_id kind description
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/tags`
Return all the tags
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `project_id` optional (String) — The project id or slug
  - `issue_id` optional (String) — The issue id
  - `notion_id` optional (String) — The notion id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. The sort field. Sorted by name asc, id desc by default. More Example: To sort on tags on the fields kind on a descending order and description on a ascending order: ...&sort=-kind,description
  - `filter` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description, cursus_id. Filtering on one or more fields More Example: To filter on tags with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) name (standard field) created_at (standard field) updated_at (standard field) pinner_id (standard field) kind (standard field) description (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, name, created_at, updated_at, pinner_id, kind, description. Select on a particular range More Example: To range on tags with the description field between min_value and max_value: ...&range[description]=min_value,max_value Rangeable fields: id name created_at updated_at pinner_id kind description
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/tags/:id`
Get a tag
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/tags/:id`
Update a tag
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `tag` optional (Hash) — 
  - `tag[name]` optional (String) — The name. Must be unique.
  - `tag[tags_users_attributes]` optional (n) — Array of nested elements The tags users attributes.
  - `tag[tags_users_attributes][user_id]` optional (Fixnum) — The user id.
  - `tag[tags_users_attributes][id]` optional (Fixnum) — The id.
  - `tag[tags_users_attributes][_destroy]` optional (String) — The destroy.
  - `tag[cursus_ids]` optional (n) — array of Integer The cursus ids.

### `PUT /v2/tags/:id`
Update a tag
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `tag` optional (Hash) — 
  - `tag[name]` optional (String) — The name. Must be unique.
  - `tag[tags_users_attributes]` optional (n) — Array of nested elements The tags users attributes.
  - `tag[tags_users_attributes][user_id]` optional (Fixnum) — The user id.
  - `tag[tags_users_attributes][id]` optional (Fixnum) — The id.
  - `tag[tags_users_attributes][_destroy]` optional (String) — The destroy.
  - `tag[cursus_ids]` optional (n) — array of Integer The cursus ids.


## tags_users

### `POST /v2/tags_users`
Create a tags user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor

### `DELETE /v2/tags_users/:id`
Destroy a tags user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/tags_users`
Return all the tags users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. The sort field. Sorted by id asc by default. More Example: To sort on tags users on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id, cursus_id. Filtering on one or more fields More Example: To filter on tags users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) tag_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. Select on a particular range More Example: To range on tags users with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id tag_id user_id created_at updated_at campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/tags_users`
Return all the tags users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. The sort field. Sorted by id asc by default. More Example: To sort on tags users on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id, cursus_id. Filtering on one or more fields More Example: To filter on tags users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) tag_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. Select on a particular range More Example: To range on tags users with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id tag_id user_id created_at updated_at campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/cursus/:cursus_id/tags_users`
Return all the tags users of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. The sort field. Sorted by id asc by default. More Example: To sort on tags users on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id, cursus_id. Filtering on one or more fields More Example: To filter on tags users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) tag_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. Select on a particular range More Example: To range on tags users with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id tag_id user_id created_at updated_at campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/campus/:campus_id/tags_users`
Return all the tags users of the given Campus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. The sort field. Sorted by id asc by default. More Example: To sort on tags users on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id, cursus_id. Filtering on one or more fields More Example: To filter on tags users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) tag_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. Select on a particular range More Example: To range on tags users with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id tag_id user_id created_at updated_at campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/tags/:tag_id/tags_users`
Return all the tags users of the given Tag
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `tag_id` optional (String) — The tag id
  - `sort` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. The sort field. Sorted by id asc by default. More Example: To sort on tags users on the fields updated_at on a descending order and campus_id on a ascending order: ...&sort=-updated_at,campus_id
  - `filter` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id, cursus_id. Filtering on one or more fields More Example: To filter on tags users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) tag_id (standard field) user_id (standard field) created_at (standard field) updated_at (standard field) campus_id (standard field) cursus_id : . Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87
  - `range` optional (enum) — id, tag_id, user_id, created_at, updated_at, campus_id. Select on a particular range More Example: To range on tags users with the campus_id field between min_value and max_value: ...&range[campus_id]=min_value,max_value Rangeable fields: id tag_id user_id created_at updated_at campus_id
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/tags_users/:id`
Get a tags user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/tags_users/:id`
Update a tags user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `PUT /v2/tags_users/:id`
Update a tags user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id


## teams

### `POST /v2/teams`
Create a team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `team` optional (Hash) — 
  - `team[project_id]` required (Fixnum) — The project id.
  - `team[name]` optional (String) — The name. Maximum length is 255.
  - `team[created_at]` optional (DateTime) — The created at.
  - `team[updated_at]` optional (DateTime) — The updated at.
  - `team[locked_at]` optional (DateTime) — The locked at.
  - `team[closed_at]` optional (DateTime) — The closed at.
  - `team[final_mark]` optional (Fixnum) — The final mark.
  - `team[repo_url]` optional (String) — The repo url.
  - `team[repo_uuid]` optional (String) — The repo uuid.
  - `team[deadline_at]` optional (Fixnum) — The deadline at. Must be after today.
  - `team[terminating_at]` optional (DateTime) — The terminating at.
  - `team[project_session_id]` optional (Fixnum) — The project session id.
  - `team[teams_users_attributes]` optional (n) — Array of nested elements The teams users attributes.
  - `team[teams_users_attributes][user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given team.
  - `team[teams_users_attributes][leader]` optional (enum) — true, false. Is it leader ? Default to false.
  - `team[teams_users_attributes][validated]` optional (enum) — true, false. Is it validated ? Default to false.
  - `team[teams_users_attributes][occurrence]` optional (Fixnum) — The occurrence. Default to 0.

### `DELETE /v2/teams/:id`
Destroy a team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/cursus/:cursus_id/teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, locked_at, closed_at, deadline_at, terminating_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status

### `GET /v2/users/:user_id/teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, locked_at, closed_at, deadline_at, terminating_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status

### `GET /v2/users/:user_id/projects/:project_id/teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, locked_at, closed_at, deadline_at, terminating_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status

### `GET /v2/teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, locked_at, closed_at, deadline_at, terminating_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status

### `GET /v2/projects/:project_id/teams/graph(/on/:field(/by/:interval))`
Return grouped temporal data on teams
- **Params:**
  - `field` optional (enum) — created_at, updated_at, locked_at, closed_at, deadline_at, terminating_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status

### `GET /v2/cursus/:cursus_id/teams`
Return all the teams of the given Cursus
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/teams`
Return all the teams of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/projects/:project_id/teams`
Return all the teams of the given Project, associated with the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/teams`
Return all the teams
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/projects/:project_id/teams`
Return all the teams of the given Project
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/project_sessions/:project_session_id/teams`
Return all the teams of the given Project session
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/me/teams`
Return all the teams for the current resource owner
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `cursus_id` optional (String) — The cursus id or slug
  - `user_id` optional (String) — The user id or slug
  - `project_id` optional (String) — The project id or slug
  - `project_session_id` optional (String) — The project_session id
  - `sort` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. The sort field. Sorted by id asc by default. More Example: To sort on teams on the fields project_session_id on a descending order and status on a ascending order: ...&sort=-project_session_id,status
  - `filter` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status, cursus, active_cursus, campus, primary_campus, locked, closed, deadline, terminating, with_mark. Filtering on one or more fields More Example: To filter on teams with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) project_id (standard field) name (standard field) created_at (standard field) updated_at (standard field) locked_at (standard field) closed_at (standard field) final_mark (standard field) repo_url (standard field) repo_uuid (standard field) deadline_at (standard field) terminating_at (standard field) project_session_id (standard field) status (standard field) cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 active_cursus : Only return teams with users in the given cursus. Can be one of: 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47, 48, 49, 50, 51, 52, 53, 54, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87 campus : Only return teams with users in the given campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 primary_campus : Only return teams with users having the campus as a primary campus. Can be one of: 1, 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78 locked (standard field) closed (standard field) deadline (standard field) terminating (standard field) with_mark : Return only teams with a final_mark. Can be one of: true, false
  - `range` optional (enum) — id, project_id, name, created_at, updated_at, locked_at, closed_at, final_mark, repo_url, repo_uuid, deadline_at, terminating_at, project_session_id, status. Select on a particular range More Example: To range on teams with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id project_id name created_at updated_at locked_at closed_at final_mark repo_url repo_uuid deadline_at terminating_at project_session_id status
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `POST /v2/teams/:id/reset_team_uploads`
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/teams/:id`
Get a team
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/teams/:id`
Update a team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id
  - `team` optional (Hash) — 
  - `team[project_id]` optional (Fixnum) — The project id.
  - `team[name]` optional (String) — The name. Maximum length is 255.
  - `team[created_at]` optional (DateTime) — The created at.
  - `team[updated_at]` optional (DateTime) — The updated at.
  - `team[locked_at]` optional (DateTime) — The locked at.
  - `team[closed_at]` optional (DateTime) — The closed at.
  - `team[final_mark]` optional (Fixnum) — The final mark.
  - `team[repo_url]` optional (String) — The repo url.
  - `team[repo_uuid]` optional (String) — The repo uuid.
  - `team[deadline_at]` optional (Fixnum) — The deadline at. Must be after today.
  - `team[terminating_at]` optional (DateTime) — The terminating at.
  - `team[project_session_id]` optional (Fixnum) — The project session id.
  - `team[teams_users_attributes]` optional (n) — Array of nested elements The teams users attributes.
  - `team[teams_users_attributes][user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given team.
  - `team[teams_users_attributes][leader]` optional (enum) — true, false. Is it leader ? Default to false.
  - `team[teams_users_attributes][validated]` optional (enum) — true, false. Is it validated ? Default to false.
  - `team[teams_users_attributes][occurrence]` optional (Fixnum) — The occurrence. Default to 0.

### `PUT /v2/teams/:id`
Update a team
- **Auth/scope:** This action requires a token resource owner scoped on projects with enough privileges or an application with one of theses role(s): Advanced tutor .
- **Params:**
  - `id` required (String) — The requested id
  - `team` optional (Hash) — 
  - `team[project_id]` optional (Fixnum) — The project id.
  - `team[name]` optional (String) — The name. Maximum length is 255.
  - `team[created_at]` optional (DateTime) — The created at.
  - `team[updated_at]` optional (DateTime) — The updated at.
  - `team[locked_at]` optional (DateTime) — The locked at.
  - `team[closed_at]` optional (DateTime) — The closed at.
  - `team[final_mark]` optional (Fixnum) — The final mark.
  - `team[repo_url]` optional (String) — The repo url.
  - `team[repo_uuid]` optional (String) — The repo uuid.
  - `team[deadline_at]` optional (Fixnum) — The deadline at. Must be after today.
  - `team[terminating_at]` optional (DateTime) — The terminating at.
  - `team[project_session_id]` optional (Fixnum) — The project session id.
  - `team[teams_users_attributes]` optional (n) — Array of nested elements The teams users attributes.
  - `team[teams_users_attributes][user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given team.
  - `team[teams_users_attributes][leader]` optional (enum) — true, false. Is it leader ? Default to false.
  - `team[teams_users_attributes][validated]` optional (enum) — true, false. Is it validated ? Default to false.
  - `team[teams_users_attributes][occurrence]` optional (Fixnum) — The occurrence. Default to 0.


## teams_uploads

### `POST /v2/teams_uploads`
Create a teams upload
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `teams_upload` optional (Hash) — 
  - `teams_upload[team_id]` required (Fixnum) — The team id. Must be unique in the scope of a given upload.
  - `teams_upload[upload_id]` required (Fixnum) — The upload id.
  - `teams_upload[final_mark]` optional (Fixnum) — The final mark.
  - `teams_upload[comment]` optional (String) — The comment.

### `DELETE /v2/teams_uploads/:id`
Destroy a teams upload
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/teams/:team_id/teams_uploads`
Return all the teams uploads of the given Team
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `team_id` optional (String) — The team id
  - `sort` optional (enum) — id, team_id, upload_id, final_mark, comment, created_at, updated_at. The sort field. Sorted by id asc by default. More Example: To sort on teams uploads on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, team_id, upload_id, final_mark, comment, created_at, updated_at. Filtering on one or more fields More Example: To filter on teams uploads with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) team_id (standard field) upload_id (standard field) final_mark (standard field) comment (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, team_id, upload_id, final_mark, comment, created_at, updated_at. Select on a particular range More Example: To range on teams uploads with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id team_id upload_id final_mark comment created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/teams_uploads`
Return all the teams uploads
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `team_id` optional (String) — The team id
  - `sort` optional (enum) — id, team_id, upload_id, final_mark, comment, created_at, updated_at. The sort field. Sorted by id asc by default. More Example: To sort on teams uploads on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, team_id, upload_id, final_mark, comment, created_at, updated_at. Filtering on one or more fields More Example: To filter on teams uploads with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) team_id (standard field) upload_id (standard field) final_mark (standard field) comment (standard field) created_at (standard field) updated_at (standard field)
  - `range` optional (enum) — id, team_id, upload_id, final_mark, comment, created_at, updated_at. Select on a particular range More Example: To range on teams uploads with the updated_at field between min_value and max_value: ...&range[updated_at]=min_value,max_value Rangeable fields: id team_id upload_id final_mark comment created_at updated_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `POST /v2/teams_uploads/multiple_create`
Create multiple teams uploads
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `teams_uploads` optional (n) — Array of nested elements An array of teams_uploads

### `GET /v2/teams_uploads/:id`
Get a teams upload
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/teams_uploads/:id`
Update a teams upload
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `teams_upload` optional (Hash) — 
  - `teams_upload[team_id]` optional (Fixnum) — The team id. Must be unique in the scope of a given upload.
  - `teams_upload[upload_id]` optional (Fixnum) — The upload id.
  - `teams_upload[final_mark]` optional (Fixnum) — The final mark.
  - `teams_upload[comment]` optional (String) — The comment.

### `PUT /v2/teams_uploads/:id`
Update a teams upload
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor group_work Requires following application scopes: projects
- **Params:**
  - `id` required (String) — The requested id
  - `teams_upload` optional (Hash) — 
  - `teams_upload[team_id]` optional (Fixnum) — The team id. Must be unique in the scope of a given upload.
  - `teams_upload[upload_id]` optional (Fixnum) — The upload id.
  - `teams_upload[final_mark]` optional (Fixnum) — The final mark.
  - `teams_upload[comment]` optional (String) — The comment.


## teams_users

### `POST /v2/teams_users`
Create a teams user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `teams_user` optional (Hash) — 
  - `teams_user[team_id]` required (Fixnum) — The team id.
  - `teams_user[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given team.
  - `teams_user[leader]` optional (enum) — true, false. Is it leader ? Default to false.
  - `teams_user[validated]` optional (enum) — true, false. Is it validated ? Default to false.
  - `teams_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.

### `DELETE /v2/teams_users/:id`
Destroy a teams user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/teams_users`
Return all the teams users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `team_id` optional (String) — The team id
  - `sort` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. The sort field. Sorted by id desc by default. More Example: To sort on teams users on the fields updated_at on a descending order and occurrence on a ascending order: ...&sort=-updated_at,occurrence
  - `filter` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. Filtering on one or more fields More Example: To filter on teams users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) team_id (standard field) user_id (standard field) leader (standard field) validated (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field)
  - `range` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. Select on a particular range More Example: To range on teams users with the occurrence field between min_value and max_value: ...&range[occurrence]=min_value,max_value Rangeable fields: id team_id user_id leader validated created_at updated_at occurrence
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/teams_users`
Return all the teams users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `team_id` optional (String) — The team id
  - `sort` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. The sort field. Sorted by id desc by default. More Example: To sort on teams users on the fields updated_at on a descending order and occurrence on a ascending order: ...&sort=-updated_at,occurrence
  - `filter` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. Filtering on one or more fields More Example: To filter on teams users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) team_id (standard field) user_id (standard field) leader (standard field) validated (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field)
  - `range` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. Select on a particular range More Example: To range on teams users with the occurrence field between min_value and max_value: ...&range[occurrence]=min_value,max_value Rangeable fields: id team_id user_id leader validated created_at updated_at occurrence
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/teams/:team_id/teams_users`
Return all the teams users of the given Team
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `team_id` optional (String) — The team id
  - `sort` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. The sort field. Sorted by id desc by default. More Example: To sort on teams users on the fields updated_at on a descending order and occurrence on a ascending order: ...&sort=-updated_at,occurrence
  - `filter` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. Filtering on one or more fields More Example: To filter on teams users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) team_id (standard field) user_id (standard field) leader (standard field) validated (standard field) created_at (standard field) updated_at (standard field) occurrence (standard field)
  - `range` optional (enum) — id, team_id, user_id, leader, validated, created_at, updated_at, occurrence. Select on a particular range More Example: To range on teams users with the occurrence field between min_value and max_value: ...&range[occurrence]=min_value,max_value Rangeable fields: id team_id user_id leader validated created_at updated_at occurrence
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/teams_users/:id`
Get a teams user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/teams_users/:id`
Update a teams user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `id` required (String) — The requested id
  - `teams_user` optional (Hash) — 
  - `teams_user[team_id]` optional (Fixnum) — The team id.
  - `teams_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given team.
  - `teams_user[leader]` optional (enum) — true, false. Is it leader ? Default to false.
  - `teams_user[validated]` optional (enum) — true, false. Is it validated ? Default to false.
  - `teams_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.

### `PUT /v2/teams_users/:id`
Update a teams user
- **Auth/scope:** assignment This action requires one of theses roles: Tutor
- **Params:**
  - `id` required (String) — The requested id
  - `teams_user` optional (Hash) — 
  - `teams_user[team_id]` optional (Fixnum) — The team id.
  - `teams_user[user_id]` optional (Fixnum) — The user id. Must be unique in the scope of a given team.
  - `teams_user[leader]` optional (enum) — true, false. Is it leader ? Default to false.
  - `teams_user[validated]` optional (enum) — true, false. Is it validated ? Default to false.
  - `teams_user[occurrence]` optional (Fixnum) — The occurrence. Default to 0.


## titles

### `POST /v2/titles`
Create a title
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `title` optional (Hash) — 
  - `title[name]` required (String) — The name.

### `DELETE /v2/titles/:id`
Destroy a title
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/titles`
Return all the titles
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/titles`
Return all the titles of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/titles/:id`
Get a title
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/titles/:id`
Update a title
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `title` optional (Hash) — 
  - `title[name]` optional (String) — The name.

### `PUT /v2/titles/:id`
Update a title
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `title` optional (Hash) — 
  - `title[name]` optional (String) — The name.


## titles_users

### `POST /v2/titles_users`
Create a titles user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `titles_user` optional (Hash) — 
  - `titles_user[title_id]` required (Fixnum) — The title id. Must be unique in the scope of a given user.
  - `titles_user[user_id]` required (Fixnum) — The user id.

### `DELETE /v2/titles_users/:id`
Destroy a titles user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/titles/:title_id/titles_users`
Return all the titles users of the given Title
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `title_id` optional (String) — The title id or slug
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/titles_users`
Return all the titles users of the given User
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `title_id` optional (String) — The title id or slug
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/titles_users`
Return all the titles users
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `title_id` optional (String) — The title id or slug
  - `user_id` optional (String) — The user id or slug
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/titles_users/:id`
Get a titles user
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/titles_users/:id`
Update a titles user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `titles_user` optional (Hash) — 
  - `titles_user[title_id]` optional (Fixnum) — The title id. Must be unique in the scope of a given user.
  - `titles_user[user_id]` optional (Fixnum) — The user id.

### `PUT /v2/titles_users/:id`
Update a titles user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `titles_user` optional (Hash) — 
  - `titles_user[title_id]` optional (Fixnum) — The title id. Must be unique in the scope of a given user.
  - `titles_user[user_id]` optional (Fixnum) — The user id.


## transactions

### `POST /v2/transactions`
Create a transaction
- **Auth/scope:** assignment This action requires one of theses roles: Transactions manager
- **Params:**
  - `transaction` optional (Hash) — 
  - `transaction[id]` optional (Fixnum) — The id.
  - `transaction[value]` required (Fixnum) — The value.
  - `transaction[user_id]` required (Fixnum) — The user id. Must be unique in the scope of a given transactable type and transactable.
  - `transaction[transactable_id]` optional (Fixnum) — The transactable id.
  - `transaction[transactable_type]` required (String) — The transactable type.
  - `transaction[reason]` required (String) — The reason.

### `DELETE /v2/transactions/:id`
Destroy a transaction
- **Auth/scope:** assignment This action requires one of theses roles: Transactions manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/transactions`
Return all the transactions
- **Auth/scope:** assignment This action requires one of theses roles: Transactions manager This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, value, user_id, transactable_id, transactable_type, created_at, reason. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on transactions on the fields created_at on a descending order and reason on a ascending order: ...&sort=-created_at,reason
  - `filter` optional (enum) — id, value, user_id, transactable_id, transactable_type, created_at, reason. Filtering on one or more fields More Example: To filter on transactions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) value (standard field) user_id (standard field) transactable_id (standard field) transactable_type (standard field) created_at (standard field) reason (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/transactions`
Return all the transactions of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Transactions manager This resource is paginated by 30 items
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `sort` optional (enum) — id, value, user_id, transactable_id, transactable_type, created_at, reason. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on transactions on the fields created_at on a descending order and reason on a ascending order: ...&sort=-created_at,reason
  - `filter` optional (enum) — id, value, user_id, transactable_id, transactable_type, created_at, reason. Filtering on one or more fields More Example: To filter on transactions with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) value (standard field) user_id (standard field) transactable_id (standard field) transactable_type (standard field) created_at (standard field) reason (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/transactions/:id`
Get a transaction
- **Auth/scope:** assignment This action requires one of theses roles: Transactions manager
- **Params:**
  - `id` required (String) — The requested id


## translations

### `POST /v2/translations`
Create a translation
- **Auth/scope:** assignment This action requires one of theses roles: Translater
- **Params:**
  - `translation` optional (Hash) — 
  - `translation[id]` optional (Fixnum) — The id.
  - `translation[translatable_id]` required (Fixnum) — The translatable id.
  - `translation[translatable_type]` optional (String) — The translatable type.
  - `translation[language_id]` required (Fixnum) — The language id. Must be unique in the scope of a given translatable type and translatable.
  - `translation[fields]` required (String) — The fields.
  - `translation[created_at]` optional (DateTime) — The created at.
  - `translation[updated_at]` optional (DateTime) — The updated at.
  - `translation[user_id]` optional (Fixnum) — The user id.
  - `translation[default]` optional (enum) — true, false. Is it default ? Default to false.
  - `translation[up_to_date]` optional (enum) — true, false. Is it up to date ? Default to true.
  - `translation[translations_structure_id]` optional (Fixnum) — The translations structure id.
  - `translation[file]` optional (String) — The file.

### `DELETE /v2/translations/:id`
Destroy a translation
- **Auth/scope:** assignment This action requires one of theses roles: Translater
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/translations`
Return all the translations
- **Auth/scope:** This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, translatable_id, translatable_type, language_id, fields, created_at, updated_at, user_id, default, up_to_date, translations_structure_id. The sort field. Sorted by id desc by default. More Example: To sort on translations on the fields up_to_date on a descending order and translations_structure_id on a ascending order: ...&sort=-up_to_date,translations_structure_id
  - `filter` optional (enum) — id, translatable_id, translatable_type, language_id, fields, created_at, updated_at, user_id, default, up_to_date, translations_structure_id. Filtering on one or more fields More Example: To filter on translations with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) translatable_id (standard field) translatable_type (standard field) language_id (standard field) fields (standard field) created_at (standard field) updated_at (standard field) user_id (standard field) default (standard field) up_to_date (standard field) translations_structure_id (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/translations/:id`
Get a translation
- **Params:**
  - `id` required (String) — The requested id

### `PATCH /v2/translations/:id`
Update a translation
- **Auth/scope:** assignment This action requires one of theses roles: Translater
- **Params:**
  - `id` required (String) — The requested id
  - `translation` optional (Hash) — 
  - `translation[id]` optional (Fixnum) — The id.
  - `translation[translatable_id]` optional (Fixnum) — The translatable id.
  - `translation[translatable_type]` optional (String) — The translatable type.
  - `translation[language_id]` optional (Fixnum) — The language id. Must be unique in the scope of a given translatable type and translatable.
  - `translation[fields]` optional (String) — The fields.
  - `translation[created_at]` optional (DateTime) — The created at.
  - `translation[updated_at]` optional (DateTime) — The updated at.
  - `translation[user_id]` optional (Fixnum) — The user id.
  - `translation[default]` optional (enum) — true, false. Is it default ? Default to false.
  - `translation[up_to_date]` optional (enum) — true, false. Is it up to date ? Default to true.
  - `translation[translations_structure_id]` optional (Fixnum) — The translations structure id.
  - `translation[file]` optional (String) — The file.

### `PUT /v2/translations/:id`
Update a translation
- **Auth/scope:** assignment This action requires one of theses roles: Translater
- **Params:**
  - `id` required (String) — The requested id
  - `translation` optional (Hash) — 
  - `translation[id]` optional (Fixnum) — The id.
  - `translation[translatable_id]` optional (Fixnum) — The translatable id.
  - `translation[translatable_type]` optional (String) — The translatable type.
  - `translation[language_id]` optional (Fixnum) — The language id. Must be unique in the scope of a given translatable type and translatable.
  - `translation[fields]` optional (String) — The fields.
  - `translation[created_at]` optional (DateTime) — The created at.
  - `translation[updated_at]` optional (DateTime) — The updated at.
  - `translation[user_id]` optional (Fixnum) — The user id.
  - `translation[default]` optional (enum) — true, false. Is it default ? Default to false.
  - `translation[up_to_date]` optional (enum) — true, false. Is it up to date ? Default to true.
  - `translation[translations_structure_id]` optional (Fixnum) — The translations structure id.
  - `translation[file]` optional (String) — The file.

### `POST /v2/translations/upload`
Upload a file translation
- **Auth/scope:** assignment This action requires one of theses roles: Translater
- **Params:**
  - `file` required (File) — yml or json


## user_candidatures

### `POST /v2/users/:user_id/user_candidature`
Create a user candidature for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `user_candidature` optional (Hash) — 
  - `user_candidature[id]` optional (Fixnum) — The id.
  - `user_candidature[user_id]` optional (Fixnum) — The user id.
  - `user_candidature[birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user_candidature[gender]` optional (enum) — male, female, other. The gender.
  - `user_candidature[zip_code]` optional (String) — The zip code.
  - `user_candidature[country]` optional (String) — The country.
  - `user_candidature[phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user_candidature[birth_city]` optional (String) — The birth city.
  - `user_candidature[birth_country]` optional (String) — The birth country.
  - `user_candidature[postal_street]` optional (String) — The postal street.
  - `user_candidature[postal_complement]` optional (String) — The postal complement.
  - `user_candidature[postal_city]` optional (String) — The postal city.
  - `user_candidature[postal_zip_code]` optional (String) — The postal zip code.
  - `user_candidature[email]` optional (String) — The email.
  - `user_candidature[postal_country]` optional (String) — The postal country.
  - `user_candidature[contact_affiliation]` optional (String) — The contact affiliation.
  - `user_candidature[contact_last_name]` optional (String) — The contact last name.
  - `user_candidature[contact_first_name]` optional (String) — The contact first name.
  - `user_candidature[contact_phone1]` optional (String) — The contact phone1.
  - `user_candidature[contact_phone2]` optional (String) — The contact phone2.
  - `user_candidature[max_level_memory]` optional (Fixnum) — The max level memory.
  - `user_candidature[max_level_logic]` optional (Fixnum) — The max level logic.
  - `user_candidature[other_information]` optional (String) — The other information.
  - `user_candidature[language]` optional (String) — The language.
  - `user_candidature[meeting_date]` optional (DateTime) — The meeting date.
  - `user_candidature[piscine_date]` optional (String) — The piscine date.
  - `user_candidature[pin]` optional (String) — The pin.
  - `user_candidature[phone]` optional (String) — The phone.

### `POST /v2/user_candidatures`
Create a user candidature
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `user_candidature` optional (Hash) — 
  - `user_candidature[id]` optional (Fixnum) — The id.
  - `user_candidature[user_id]` optional (Fixnum) — The user id.
  - `user_candidature[birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user_candidature[gender]` optional (enum) — male, female, other. The gender.
  - `user_candidature[zip_code]` optional (String) — The zip code.
  - `user_candidature[country]` optional (String) — The country.
  - `user_candidature[phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user_candidature[birth_city]` optional (String) — The birth city.
  - `user_candidature[birth_country]` optional (String) — The birth country.
  - `user_candidature[postal_street]` optional (String) — The postal street.
  - `user_candidature[postal_complement]` optional (String) — The postal complement.
  - `user_candidature[postal_city]` optional (String) — The postal city.
  - `user_candidature[postal_zip_code]` optional (String) — The postal zip code.
  - `user_candidature[email]` optional (String) — The email.
  - `user_candidature[postal_country]` optional (String) — The postal country.
  - `user_candidature[contact_affiliation]` optional (String) — The contact affiliation.
  - `user_candidature[contact_last_name]` optional (String) — The contact last name.
  - `user_candidature[contact_first_name]` optional (String) — The contact first name.
  - `user_candidature[contact_phone1]` optional (String) — The contact phone1.
  - `user_candidature[contact_phone2]` optional (String) — The contact phone2.
  - `user_candidature[max_level_memory]` optional (Fixnum) — The max level memory.
  - `user_candidature[max_level_logic]` optional (Fixnum) — The max level logic.
  - `user_candidature[other_information]` optional (String) — The other information.
  - `user_candidature[language]` optional (String) — The language.
  - `user_candidature[meeting_date]` optional (DateTime) — The meeting date.
  - `user_candidature[piscine_date]` optional (String) — The piscine date.
  - `user_candidature[pin]` optional (String) — The pin.
  - `user_candidature[phone]` optional (String) — The phone.

### `GET /v2/user_candidatures`
Return all the user candidatures
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, user_id, birth_date, gender, zip_code, country, birth_city, birth_country, postal_street, postal_complement, postal_city, postal_zip_code, postal_country, contact_affiliation, contact_last_name, contact_first_name, contact_phone1, contact_phone2, max_level_memory, max_level_logic, other_information, language, meeting_date, piscine_date, created_at, updated_at, phone, email, pin, phone_country_code, hidden_phone. The sort field. Sorted by created_at desc, id desc by default. More Example: To sort on user candidatures on the fields phone_country_code on a descending order and hidden_phone on a ascending order: ...&sort=-phone_country_code,hidden_phone
  - `filter` optional (enum) — id, user_id, birth_date, gender, country, birth_country, postal_country, piscine_date, email, campus_id. Filtering on one or more fields More Example: To filter on user candidatures with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) user_id (standard field) birth_date (standard field) gender (standard field) country (standard field) birth_country (standard field) postal_country (standard field) piscine_date (standard field) email : . campus_id : .
  - `range` optional (enum) — id, user_id, birth_date, gender, country, birth_country, postal_country, piscine_date, updated_at, created_at. Select on a particular range More Example: To range on user candidatures with the created_at field between min_value and max_value: ...&range[created_at]=min_value,max_value Rangeable fields: id user_id birth_date gender country birth_country postal_country piscine_date updated_at created_at
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/users/:user_id/user_candidature`
Get a user candidature of the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id

### `GET /v2/user_candidatures/:id`
Get a user candidature
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id

### `PATCH /v2/users/:user_id/user_candidature`
Update a user candidature for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `user_candidature` optional (Hash) — 
  - `user_candidature[id]` optional (Fixnum) — The id.
  - `user_candidature[user_id]` optional (Fixnum) — The user id.
  - `user_candidature[birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user_candidature[gender]` optional (enum) — male, female, other. The gender.
  - `user_candidature[zip_code]` optional (String) — The zip code.
  - `user_candidature[country]` optional (String) — The country.
  - `user_candidature[phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user_candidature[birth_city]` optional (String) — The birth city.
  - `user_candidature[birth_country]` optional (String) — The birth country.
  - `user_candidature[postal_street]` optional (String) — The postal street.
  - `user_candidature[postal_complement]` optional (String) — The postal complement.
  - `user_candidature[postal_city]` optional (String) — The postal city.
  - `user_candidature[postal_zip_code]` optional (String) — The postal zip code.
  - `user_candidature[email]` optional (String) — The email.
  - `user_candidature[postal_country]` optional (String) — The postal country.
  - `user_candidature[contact_affiliation]` optional (String) — The contact affiliation.
  - `user_candidature[contact_last_name]` optional (String) — The contact last name.
  - `user_candidature[contact_first_name]` optional (String) — The contact first name.
  - `user_candidature[contact_phone1]` optional (String) — The contact phone1.
  - `user_candidature[contact_phone2]` optional (String) — The contact phone2.
  - `user_candidature[max_level_memory]` optional (Fixnum) — The max level memory.
  - `user_candidature[max_level_logic]` optional (Fixnum) — The max level logic.
  - `user_candidature[other_information]` optional (String) — The other information.
  - `user_candidature[language]` optional (String) — The language.
  - `user_candidature[meeting_date]` optional (DateTime) — The meeting date.
  - `user_candidature[piscine_date]` optional (String) — The piscine date.
  - `user_candidature[pin]` optional (String) — The pin.
  - `user_candidature[phone]` optional (String) — The phone.

### `PUT /v2/users/:user_id/user_candidature`
Update a user candidature for the given User
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `user_candidature` optional (Hash) — 
  - `user_candidature[id]` optional (Fixnum) — The id.
  - `user_candidature[user_id]` optional (Fixnum) — The user id.
  - `user_candidature[birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user_candidature[gender]` optional (enum) — male, female, other. The gender.
  - `user_candidature[zip_code]` optional (String) — The zip code.
  - `user_candidature[country]` optional (String) — The country.
  - `user_candidature[phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user_candidature[birth_city]` optional (String) — The birth city.
  - `user_candidature[birth_country]` optional (String) — The birth country.
  - `user_candidature[postal_street]` optional (String) — The postal street.
  - `user_candidature[postal_complement]` optional (String) — The postal complement.
  - `user_candidature[postal_city]` optional (String) — The postal city.
  - `user_candidature[postal_zip_code]` optional (String) — The postal zip code.
  - `user_candidature[email]` optional (String) — The email.
  - `user_candidature[postal_country]` optional (String) — The postal country.
  - `user_candidature[contact_affiliation]` optional (String) — The contact affiliation.
  - `user_candidature[contact_last_name]` optional (String) — The contact last name.
  - `user_candidature[contact_first_name]` optional (String) — The contact first name.
  - `user_candidature[contact_phone1]` optional (String) — The contact phone1.
  - `user_candidature[contact_phone2]` optional (String) — The contact phone2.
  - `user_candidature[max_level_memory]` optional (Fixnum) — The max level memory.
  - `user_candidature[max_level_logic]` optional (Fixnum) — The max level logic.
  - `user_candidature[other_information]` optional (String) — The other information.
  - `user_candidature[language]` optional (String) — The language.
  - `user_candidature[meeting_date]` optional (DateTime) — The meeting date.
  - `user_candidature[piscine_date]` optional (String) — The piscine date.
  - `user_candidature[pin]` optional (String) — The pin.
  - `user_candidature[phone]` optional (String) — The phone.

### `PATCH /v2/user_candidatures/:id`
Update a user candidature
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `user_candidature` optional (Hash) — 
  - `user_candidature[id]` optional (Fixnum) — The id.
  - `user_candidature[user_id]` optional (Fixnum) — The user id.
  - `user_candidature[birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user_candidature[gender]` optional (enum) — male, female, other. The gender.
  - `user_candidature[zip_code]` optional (String) — The zip code.
  - `user_candidature[country]` optional (String) — The country.
  - `user_candidature[phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user_candidature[birth_city]` optional (String) — The birth city.
  - `user_candidature[birth_country]` optional (String) — The birth country.
  - `user_candidature[postal_street]` optional (String) — The postal street.
  - `user_candidature[postal_complement]` optional (String) — The postal complement.
  - `user_candidature[postal_city]` optional (String) — The postal city.
  - `user_candidature[postal_zip_code]` optional (String) — The postal zip code.
  - `user_candidature[email]` optional (String) — The email.
  - `user_candidature[postal_country]` optional (String) — The postal country.
  - `user_candidature[contact_affiliation]` optional (String) — The contact affiliation.
  - `user_candidature[contact_last_name]` optional (String) — The contact last name.
  - `user_candidature[contact_first_name]` optional (String) — The contact first name.
  - `user_candidature[contact_phone1]` optional (String) — The contact phone1.
  - `user_candidature[contact_phone2]` optional (String) — The contact phone2.
  - `user_candidature[max_level_memory]` optional (Fixnum) — The max level memory.
  - `user_candidature[max_level_logic]` optional (Fixnum) — The max level logic.
  - `user_candidature[other_information]` optional (String) — The other information.
  - `user_candidature[language]` optional (String) — The language.
  - `user_candidature[meeting_date]` optional (DateTime) — The meeting date.
  - `user_candidature[piscine_date]` optional (String) — The piscine date.
  - `user_candidature[pin]` optional (String) — The pin.
  - `user_candidature[phone]` optional (String) — The phone.

### `PUT /v2/user_candidatures/:id`
Update a user candidature
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Advanced tutor
- **Params:**
  - `user_id` optional (String) — The user id or slug
  - `id` required (String) — The requested id
  - `user_candidature` optional (Hash) — 
  - `user_candidature[id]` optional (Fixnum) — The id.
  - `user_candidature[user_id]` optional (Fixnum) — The user id.
  - `user_candidature[birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user_candidature[gender]` optional (enum) — male, female, other. The gender.
  - `user_candidature[zip_code]` optional (String) — The zip code.
  - `user_candidature[country]` optional (String) — The country.
  - `user_candidature[phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user_candidature[birth_city]` optional (String) — The birth city.
  - `user_candidature[birth_country]` optional (String) — The birth country.
  - `user_candidature[postal_street]` optional (String) — The postal street.
  - `user_candidature[postal_complement]` optional (String) — The postal complement.
  - `user_candidature[postal_city]` optional (String) — The postal city.
  - `user_candidature[postal_zip_code]` optional (String) — The postal zip code.
  - `user_candidature[email]` optional (String) — The email.
  - `user_candidature[postal_country]` optional (String) — The postal country.
  - `user_candidature[contact_affiliation]` optional (String) — The contact affiliation.
  - `user_candidature[contact_last_name]` optional (String) — The contact last name.
  - `user_candidature[contact_first_name]` optional (String) — The contact first name.
  - `user_candidature[contact_phone1]` optional (String) — The contact phone1.
  - `user_candidature[contact_phone2]` optional (String) — The contact phone2.
  - `user_candidature[max_level_memory]` optional (Fixnum) — The max level memory.
  - `user_candidature[max_level_logic]` optional (Fixnum) — The max level logic.
  - `user_candidature[other_information]` optional (String) — The other information.
  - `user_candidature[language]` optional (String) — The language.
  - `user_candidature[meeting_date]` optional (DateTime) — The meeting date.
  - `user_candidature[piscine_date]` optional (String) — The piscine date.
  - `user_candidature[pin]` optional (String) — The pin.
  - `user_candidature[phone]` optional (String) — The phone.


## users

### `POST /v2/users/:id/correction_points/add`
Add an evaluation point
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The user login
  - `reason` required (String) — The reason of this evaluation point addition
  - `amount` optional (String) — The amount you want to add, if not specified it will add 1 point

### `GET /v2/users/:user_id/projects_users/registration`
Get all allowed registration projects for a user

### `POST /v2/users/:id/alumnize`
Alumnize user
- **Auth/scope:** assignment This action requires one of theses roles: 42network

### `POST /v2/users`
Create a user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `user` optional (Hash) — 
  - `user[login]` optional (String) — The login. Default to . Must be unique.
  - `user[email]` required (String) — The email. Default to . Must be unique.
  - `user[first_name]` required (String) — The first name.
  - `user[last_name]` required (String) — The last name.
  - `user[usual_first_name]` required (String) — The usual first name. Maximum length is 42.
  - `user[password]` optional (String) — The password.
  - `user[pool_year]` required (String) — The pool year.
  - `user[pool_month]` required (String) — The pool month.
  - `user[kind]` required (enum) — admin, student, external. The kind.
  - `user[status]` optional (String) — The status.
  - `user[image]` optional (File) — The image. Allow blank length is true. Allow nil length is true. Minimum length is 3072. Maximum length is 1048576.
  - `user[campus_id]` optional (String) — The campus id.
  - `user[cursus_id]` optional (String) — The cursus id.
  - `user[email_stop]` optional (enum) — true, false. Is it email stop ? Default to false.
  - `user[skip_welcome_mail]` optional (String) — The skip welcome mail.
  - `user[user_candidature_attributes]` optional (n) — Array of nested elements The user candidature attributes.
  - `user[user_candidature_attributes][id]` optional (Fixnum) — The id.
  - `user[user_candidature_attributes][user_id]` optional (Fixnum) — The user id.
  - `user[user_candidature_attributes][birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user[user_candidature_attributes][gender]` optional (enum) — male, female, other. The gender.
  - `user[user_candidature_attributes][zip_code]` optional (String) — The zip code.
  - `user[user_candidature_attributes][country]` optional (String) — The country.
  - `user[user_candidature_attributes][phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user[user_candidature_attributes][birth_city]` optional (String) — The birth city.
  - `user[user_candidature_attributes][birth_country]` optional (String) — The birth country.
  - `user[user_candidature_attributes][postal_street]` optional (String) — The postal street.
  - `user[user_candidature_attributes][postal_complement]` optional (String) — The postal complement.
  - `user[user_candidature_attributes][postal_city]` optional (String) — The postal city.
  - `user[user_candidature_attributes][postal_zip_code]` optional (String) — The postal zip code.
  - `user[user_candidature_attributes][postal_country]` optional (String) — The postal country.
  - `user[user_candidature_attributes][contact_affiliation]` optional (String) — The contact affiliation.
  - `user[user_candidature_attributes][contact_last_name]` optional (String) — The contact last name.
  - `user[user_candidature_attributes][contact_first_name]` optional (String) — The contact first name.
  - `user[user_candidature_attributes][contact_phone1]` optional (String) — The contact phone1.
  - `user[user_candidature_attributes][contact_phone2]` optional (String) — The contact phone2.
  - `user[user_candidature_attributes][max_level_memory]` optional (Fixnum) — The max level memory.
  - `user[user_candidature_attributes][max_level_logic]` optional (Fixnum) — The max level logic.
  - `user[user_candidature_attributes][other_information]` optional (String) — The other information.
  - `user[user_candidature_attributes][language]` optional (String) — The language.
  - `user[user_candidature_attributes][meeting_date]` optional (DateTime) — The meeting date.
  - `user[user_candidature_attributes][piscine_date]` optional (String) — The piscine date.
  - `user[user_candidature_attributes][email]` optional (String) — The email.
  - `user[user_candidature_attributes][pin]` optional (String) — The pin.
  - `user[user_candidature_attributes][phone]` optional (String) — The phone.
  - `user[cursus_users_attributes]` optional (n) — Array of nested elements The cursus users attributes.
  - `user[cursus_users_attributes][id]` optional (Fixnum) — The id.
  - `user[cursus_users_attributes][cursus_id]` required (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `user[cursus_users_attributes][end_at]` optional (Fixnum) — The end at… .
  - `user[cursus_users_attributes][begin_at]` required (Fixnum) — The begin at…
  - `user[cursus_users_attributes][_destroy]` optional (String) — The destroy.
  - `user[languages_users_attributes]` optional (n) — Array of nested elements The languages users attributes.
  - `user[languages_users_attributes][id]` optional (Fixnum) — The id.
  - `user[languages_users_attributes][language_id]` required (Fixnum) — The language id.
  - `user[languages_users_attributes][position]` optional (Fixnum) — The position.
  - `user[languages_users_attributes][_destroy]` optional (String) — The destroy.

### `DELETE /v2/users/:id/otp_settings/remove`
Deactivate 2FA
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff

### `POST /v2/users/:id/dealumnize`
- **Auth/scope:** assignment This action requires one of theses roles: 42network

### `GET /v2/users/:id/exam`
Show the exam status for the requested user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor

### `POST /v2/users/:id/free_past_agu`
free past agu to user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff
- **Params:**
  - `id` required (String) — The user login
  - `duration` required (String) — Blackhole delay duration in day
  - `reason` optional (String) — Optional reason for the freeze.

### `GET /v2/users/graph(/on/:field(/by/:interval))`
Return grouped temporal data on users
- **Params:**
  - `field` optional (enum) — created_at, updated_at. The date field to graph on. Default to created_at.
  - `interval` optional (enum) — day, week, month, quarter, year, hour_of_day, day_of_week, day_of_month, month_of_year. The interval to graph by. Default to month_of_year.
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/coalitions/:coalition_id/users`
Return all the users of the given Coalition
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/dashes/:dash_id/users`
Return all the users of the given Dash
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/events/:event_id/users`
Return all the users of the given Event
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/accreditations/:accreditation_id/users`
Return all the users of the given Accreditation
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/teams/:team_id/users`
Return all the users of the given Team
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/projects/:project_id/users`
Return all the users of the given Project
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/partnerships/:partnership_id/users`
Return all the users of the given Partnership
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/expertises/:expertise_id/users`
Return all the users of the given Expertise
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/users`
Return all the users
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/cursus/:cursus_id/users`
Return all the users of the given Cursus
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/campus/:campus_id/users`
Return all the users of the given Campus
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/achievements/:achievement_id/users`
Return all the users of the given Achievement
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/titles/:title_id/users`
Return all the users of the given Title
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/quests/:quest_id/users`
Return all the users of the given Quest
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/groups/:group_id/users`
Return all the users of the given Group
- **Params:**
  - `coalition_id` optional (String) — The coalition id or slug
  - `dash_id` optional (String) — The dash id or slug
  - `event_id` optional (String) — The event id
  - `accreditation_id` optional (String) — The accreditation id
  - `team_id` optional (String) — The team id
  - `project_id` optional (String) — The project id or slug
  - `partnership_id` optional (String) — The partnership id or slug
  - `expertise_id` optional (String) — The expertise id or slug
  - `cursus_id` optional (String) — The cursus id or slug
  - `campus_id` optional (String) — The campus id or slug
  - `achievement_id` optional (String) — The achievement id or slug
  - `title_id` optional (String) — The title id or slug
  - `quest_id` optional (String) — The quest id or slug
  - `group_id` optional (String) — The group id
  - `sort` optional (enum) — id, login, email, encrypted_password, reset_password_token, reset_password_sent_at, created_at, updated_at, image, first_name, last_name, pool_year, pool_month, kind, status, otp_secret_key, otp_tmp, otp_activated, otp_backup_passwords, slack_team, slack_login, slack_mail, slack_code_validation, slack_validated_at, token_id, email_stop, linked_user_id, usual_first_name, last_seen_at, password_changed_at, encrypted_single_usage_password, first_warn_anon_sent_at, second_warn_anon_sent_at, alumnized_at, anonymized_at. The sort field. Sorted by id desc by default. More Example: To sort on users on the fields alumnized_at on a descending order and anonymized_at on a ascending order: ...&sort=-alumnized_at,anonymized_at
  - `filter` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status, primary_campus_id, first_name, last_name, alumni?, staff?. Filtering on one or more fields More Example: To filter on users with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) login (standard field) email (standard field) created_at (standard field) updated_at (standard field) pool_year (standard field) pool_month (standard field) kind (standard field) status (standard field) primary_campus_id : . first_name : . last_name : . alumni? : . staff? : .
  - `range` optional (enum) — id, login, email, created_at, updated_at, pool_year, pool_month, kind, status. Select on a particular range More Example: To range on users with the status field between min_value and max_value: ...&range[status]=min_value,max_value Rangeable fields: id login email created_at updated_at pool_year pool_month kind status

### `GET /v2/users/:id/locations_stats`
Get location stats of a User.
- **Params:**
  - `begin_at` optional (String) — 
  - `end_at` optional (String) — 
  - `time_zone` optional (String) — The timezone you want to see the locations with. Defaults to the target user’s timezone.

### `GET /v2/me`
Show the current resource owner
- **Auth/scope:** This action requires a token resource owner .

### `DELETE /v2/users/:id/correction_points/remove`
Remove a evaluation point
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The user login
  - `reason` required (String) — The reason of this evaluation point removal
  - `amount` optional (String) — The amount you want to remove, if not specified it will remove 1 point

### `POST /v2/users/:id/set_primary_campus`
Set primary campus
- **Auth/scope:** assignment This action requires one of theses roles: 42network
- **Params:**
  - `campus_id` required (Integer) — The campus id

### `GET /v2/users/:id`
Get a user
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/staff`
Get all staff
- **Auth/scope:** assignment This action requires one of theses roles: 42network

### `POST /v2/users/:user_id/unfreeze`
Unfreeze user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff

### `PATCH /v2/users/:id`
Update a user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `user` optional (Hash) — 
  - `user[login]` optional (String) — The login. Default to . Must be unique.
  - `user[email]` optional (String) — The email. Default to . Must be unique.
  - `user[first_name]` optional (String) — The first name.
  - `user[last_name]` optional (String) — The last name.
  - `user[usual_first_name]` optional (String) — The usual first name. Maximum length is 42.
  - `user[password]` optional (String) — The password.
  - `user[pool_year]` optional (String) — The pool year.
  - `user[pool_month]` optional (String) — The pool month.
  - `user[kind]` optional (enum) — admin, student, external. The kind.
  - `user[status]` optional (String) — The status.
  - `user[image]` optional (File) — The image. Allow blank length is true. Allow nil length is true. Minimum length is 3072. Maximum length is 1048576.
  - `user[campus_id]` optional (String) — The campus id.
  - `user[cursus_id]` optional (String) — The cursus id.
  - `user[email_stop]` optional (enum) — true, false. Is it email stop ? Default to false.
  - `user[skip_welcome_mail]` optional (String) — The skip welcome mail.
  - `user[user_candidature_attributes]` optional (n) — Array of nested elements The user candidature attributes.
  - `user[user_candidature_attributes][id]` optional (Fixnum) — The id.
  - `user[user_candidature_attributes][user_id]` optional (Fixnum) — The user id.
  - `user[user_candidature_attributes][birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user[user_candidature_attributes][gender]` optional (enum) — male, female, other. The gender.
  - `user[user_candidature_attributes][zip_code]` optional (String) — The zip code.
  - `user[user_candidature_attributes][country]` optional (String) — The country.
  - `user[user_candidature_attributes][phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user[user_candidature_attributes][birth_city]` optional (String) — The birth city.
  - `user[user_candidature_attributes][birth_country]` optional (String) — The birth country.
  - `user[user_candidature_attributes][postal_street]` optional (String) — The postal street.
  - `user[user_candidature_attributes][postal_complement]` optional (String) — The postal complement.
  - `user[user_candidature_attributes][postal_city]` optional (String) — The postal city.
  - `user[user_candidature_attributes][postal_zip_code]` optional (String) — The postal zip code.
  - `user[user_candidature_attributes][postal_country]` optional (String) — The postal country.
  - `user[user_candidature_attributes][contact_affiliation]` optional (String) — The contact affiliation.
  - `user[user_candidature_attributes][contact_last_name]` optional (String) — The contact last name.
  - `user[user_candidature_attributes][contact_first_name]` optional (String) — The contact first name.
  - `user[user_candidature_attributes][contact_phone1]` optional (String) — The contact phone1.
  - `user[user_candidature_attributes][contact_phone2]` optional (String) — The contact phone2.
  - `user[user_candidature_attributes][max_level_memory]` optional (Fixnum) — The max level memory.
  - `user[user_candidature_attributes][max_level_logic]` optional (Fixnum) — The max level logic.
  - `user[user_candidature_attributes][other_information]` optional (String) — The other information.
  - `user[user_candidature_attributes][language]` optional (String) — The language.
  - `user[user_candidature_attributes][meeting_date]` optional (DateTime) — The meeting date.
  - `user[user_candidature_attributes][piscine_date]` optional (String) — The piscine date.
  - `user[user_candidature_attributes][email]` optional (String) — The email.
  - `user[user_candidature_attributes][pin]` optional (String) — The pin.
  - `user[user_candidature_attributes][phone]` optional (String) — The phone.
  - `user[cursus_users_attributes]` optional (n) — Array of nested elements The cursus users attributes.
  - `user[cursus_users_attributes][id]` optional (Fixnum) — The id.
  - `user[cursus_users_attributes][cursus_id]` optional (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `user[cursus_users_attributes][end_at]` optional (Fixnum) — The end at… .
  - `user[cursus_users_attributes][begin_at]` optional (Fixnum) — The begin at…
  - `user[cursus_users_attributes][_destroy]` optional (String) — The destroy.
  - `user[languages_users_attributes]` optional (n) — Array of nested elements The languages users attributes.
  - `user[languages_users_attributes][id]` optional (Fixnum) — The id.
  - `user[languages_users_attributes][language_id]` optional (Fixnum) — The language id.
  - `user[languages_users_attributes][position]` optional (Fixnum) — The position.
  - `user[languages_users_attributes][_destroy]` optional (String) — The destroy.

### `PUT /v2/users/:id`
Update a user
- **Auth/scope:** assignment This action requires one of theses roles: Advanced tutor
- **Params:**
  - `id` required (String) — The requested id
  - `user` optional (Hash) — 
  - `user[login]` optional (String) — The login. Default to . Must be unique.
  - `user[email]` optional (String) — The email. Default to . Must be unique.
  - `user[first_name]` optional (String) — The first name.
  - `user[last_name]` optional (String) — The last name.
  - `user[usual_first_name]` optional (String) — The usual first name. Maximum length is 42.
  - `user[password]` optional (String) — The password.
  - `user[pool_year]` optional (String) — The pool year.
  - `user[pool_month]` optional (String) — The pool month.
  - `user[kind]` optional (enum) — admin, student, external. The kind.
  - `user[status]` optional (String) — The status.
  - `user[image]` optional (File) — The image. Allow blank length is true. Allow nil length is true. Minimum length is 3072. Maximum length is 1048576.
  - `user[campus_id]` optional (String) — The campus id.
  - `user[cursus_id]` optional (String) — The cursus id.
  - `user[email_stop]` optional (enum) — true, false. Is it email stop ? Default to false.
  - `user[skip_welcome_mail]` optional (String) — The skip welcome mail.
  - `user[user_candidature_attributes]` optional (n) — Array of nested elements The user candidature attributes.
  - `user[user_candidature_attributes][id]` optional (Fixnum) — The id.
  - `user[user_candidature_attributes][user_id]` optional (Fixnum) — The user id.
  - `user[user_candidature_attributes][birth_date]` optional (Fixnum) — The birth date. Must be at least 13 years ago. must be at most 99 years ago.
  - `user[user_candidature_attributes][gender]` optional (enum) — male, female, other. The gender.
  - `user[user_candidature_attributes][zip_code]` optional (String) — The zip code.
  - `user[user_candidature_attributes][country]` optional (String) — The country.
  - `user[user_candidature_attributes][phone_country_code]` optional (enum) — AD, AE, AF, AG, AI, AL, AM, AN, AO, AQ, AR, AS, AT, AU, AW, AX, AZ, BA, BB, BD, BE, BF, BG, BH, BI, BJ, BL, BM, BN, BO, BQ, BR, BS, BT, BV, BW, BY, BZ, CA, CC, CD, CF, CG, CH, CI, CK, CL, CM, CN, CO, CR, CU, CV, CW, CX, CY, CZ, DE, DJ, DK, DM, DO, DZ, EC, EE, EG, EH, ER, ES, ET, FI, FJ, FK, FM, FO, FR, GA, GB, GD, GE, GF, GG, GH, GI, GL, GM, GN, GP, GQ, GR, GS, GT, GU, GW, GY, HK, HM, HN, HR, HT, HU, ID, IE, IL, IM, IN, IO, IQ, IR, IS, IT, JE, JM, JO, JP, KE, KG, KH, KI, KM, KN, KP, KR, KW, KY, KZ, LA, LB, LC, LI, LK, LR, LS, LT, LU, LV, LY, MA, MC, MD, ME, MF, MG, MH, MK, ML, MM, MN, MO, MP, MQ, MR, MS, MT, MU, MV, MW, MX, MY, MZ, NA, NC, NE, NF, NG, NI, NL, NO, NP, NR, NU, NZ, OM, PA, PE, PF, PG, PH, PK, PL, PM, PN, PR, PS, PT, PW, PY, QA, RE, RO, RS, RU, RW, SA, SB, SC, SD, SE, SG, SH, SI, SJ, SK, SL, SM, SN, SO, SR, SS, ST, SV, SX, SY, SZ, TC, TD, TF, TG, TH, TJ, TK, TL, TM, TN, TO, TR, TT, TV, TW, TZ, UA, UG, UM, US, UY, UZ, VA, VC, VE, VG, VI, VN, VU, WF, WS, XK, YE, YT, ZA, ZM, ZW, . The phone country code.
  - `user[user_candidature_attributes][birth_city]` optional (String) — The birth city.
  - `user[user_candidature_attributes][birth_country]` optional (String) — The birth country.
  - `user[user_candidature_attributes][postal_street]` optional (String) — The postal street.
  - `user[user_candidature_attributes][postal_complement]` optional (String) — The postal complement.
  - `user[user_candidature_attributes][postal_city]` optional (String) — The postal city.
  - `user[user_candidature_attributes][postal_zip_code]` optional (String) — The postal zip code.
  - `user[user_candidature_attributes][postal_country]` optional (String) — The postal country.
  - `user[user_candidature_attributes][contact_affiliation]` optional (String) — The contact affiliation.
  - `user[user_candidature_attributes][contact_last_name]` optional (String) — The contact last name.
  - `user[user_candidature_attributes][contact_first_name]` optional (String) — The contact first name.
  - `user[user_candidature_attributes][contact_phone1]` optional (String) — The contact phone1.
  - `user[user_candidature_attributes][contact_phone2]` optional (String) — The contact phone2.
  - `user[user_candidature_attributes][max_level_memory]` optional (Fixnum) — The max level memory.
  - `user[user_candidature_attributes][max_level_logic]` optional (Fixnum) — The max level logic.
  - `user[user_candidature_attributes][other_information]` optional (String) — The other information.
  - `user[user_candidature_attributes][language]` optional (String) — The language.
  - `user[user_candidature_attributes][meeting_date]` optional (DateTime) — The meeting date.
  - `user[user_candidature_attributes][piscine_date]` optional (String) — The piscine date.
  - `user[user_candidature_attributes][email]` optional (String) — The email.
  - `user[user_candidature_attributes][pin]` optional (String) — The pin.
  - `user[user_candidature_attributes][phone]` optional (String) — The phone.
  - `user[cursus_users_attributes]` optional (n) — Array of nested elements The cursus users attributes.
  - `user[cursus_users_attributes][id]` optional (Fixnum) — The id.
  - `user[cursus_users_attributes][cursus_id]` optional (Fixnum) — The cursus id. Must be unique in the scope of a given user.
  - `user[cursus_users_attributes][end_at]` optional (Fixnum) — The end at… .
  - `user[cursus_users_attributes][begin_at]` optional (Fixnum) — The begin at…
  - `user[cursus_users_attributes][_destroy]` optional (String) — The destroy.
  - `user[languages_users_attributes]` optional (n) — Array of nested elements The languages users attributes.
  - `user[languages_users_attributes][id]` optional (Fixnum) — The id.
  - `user[languages_users_attributes][language_id]` optional (Fixnum) — The language id.
  - `user[languages_users_attributes][position]` optional (Fixnum) — The position.
  - `user[languages_users_attributes][_destroy]` optional (String) — The destroy.


## waitlists

### `DELETE /v2/waitlists/:id`
Destroy a waitlist
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `id` required (String) — The requested id

### `GET /v2/waitlists`
Return all the waitlists
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager This resource is paginated by 30 items
- **Params:**
  - `sort` optional (enum) — id, waitlistable_id, waitlistable_type, created_at, updated_at. The sort field. Sorted by created_at asc, id desc by default. More Example: To sort on waitlists on the fields created_at on a descending order and updated_at on a ascending order: ...&sort=-created_at,updated_at
  - `filter` optional (enum) — id, waitlistable_id, waitlistable_type, created_at, updated_at. Filtering on one or more fields More Example: To filter on waitlists with the id field matching a_value or another_value: ...&filter[id]=a_value,another_value Filterable fields: id (standard field) waitlistable_id (standard field) waitlistable_type (standard field) created_at (standard field) updated_at (standard field)
  - `page` optional (Hash) — The pagination params, as a hash
  - `page[number]` optional (Fixnum) — The current page
  - `page[size]` optional (Fixnum) — The number of items per page, defaults to 30, maximum 100

### `GET /v2/events/:event_id/waitlist`
Get a waitlist of the given Event
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `event_id` optional (String) — The event id
  - `exam_id` optional (String) — The exam id
  - `id` required (String) — The requested id

### `GET /v2/exams/:exam_id/waitlist`
Get a waitlist of the given Exam
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `event_id` optional (String) — The event id
  - `exam_id` optional (String) — The exam id
  - `id` required (String) — The requested id

### `GET /v2/waitlists/:id`
Get a waitlist
- **Auth/scope:** assignment This action requires one of theses roles: Advanced staff, Events manager
- **Params:**
  - `event_id` optional (String) — The event id
  - `exam_id` optional (String) — The exam id
  - `id` required (String) — The requested id


## webhook_registeries

### `POST /v2/webhook_registeries/:id/deactivate`
- **Auth/scope:** assignment This action requires one of theses roles: Network
- **Params:**
  - `id` required (String) — The requested id

