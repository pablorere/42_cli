# 42 API v2 — request/response examples (scraped)

> Scraped 2026-09-15 from the apidoc **Examples → Raw** tab of each detail page.
> **302 example blocks** from 297 pages (only some pages ship a Raw example —
> mostly `index`/`show`; `create`/`update`/`destroy` pages generally have none).
>
> Companion to `api42-apidoc.md` and `api42-endpoints.md`.

## accreditations

### `POST /v2/accreditations`

```
  "accreditation": {
    "accreditations_skills_attributes": [
      {
        "skill_id": "5",
        "value": "100.0"
      }
    ],
    "cursus_id": "2",
    "difficulty": "100.0",
    "name": "DQar",
    "user_id": "90",
    "validated": "true"
  }
}
201
{
  "id": 3,
  "name": "DQar",
  "user_id": 90,
  "cursus_id": 2,
  "validated": true,
  "difficulty": 100
}
```

### `DELETE /v2/accreditations/2` — HTTP 204

```
(no body)
```

### `GET /v2/accreditations` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Kamino",
    "user_id": 39,
    "cursus_id": 2,
    "validated": false
  },
  {
    "id": 2,
    "name": "Endor",
    "user_id": 71,
    "cursus_id": 2,
    "validated": false
  }
]
```

### `GET /v2/accreditations/2` — HTTP 200

```json
{
  "id": 2,
  "name": "Endor",
  "user_id": 71,
  "cursus_id": 2,
  "validated": false
}
```

### `PUT /v2/accreditations/2`

```
  "accreditation": {
    "accreditations_skills_attributes": [
      {
        "skill_id": "2",
        "value": "0.0"
      }
    ],
    "cursus_id": "2",
    "difficulty": "100.0",
    "name": "Kamino",
    "user_id": "59",
    "validated": "true"
  }
}
204
```


## achievements

### `POST /v2/achievements`

```
  "achievement": {
    "name": "Be a test of the API",
    "internal_name": "BeATestAPI",
    "kind": "social",
    "tier": "none",
    "description": "Be used as a test for the api",
    "image": {
      "tempfile": [],
      "original_filename": "logo.svg",
      "content_type": "image/svg+xml",
      "headers": "Content-Disposition: form-data; name=\"achievement[image]\"; filename=\"logo.svg\"\r\nContent-Type: image/svg+xml\r\nContent-Length: 2989\r\n"
    },
    "title_id": "30",
    "cursus_ids": [
      "1"
    ],
    "campus_ids": [
      "1"
    ],
    "lg": "1"
  }
}
201
{
  "id": 10,
  "name": "Be a test of the API",
  "description": "Be used as a test for the api",
  "tier": "none",
  "kind": "social",
  "visible": false,
  "image": "/uploads/achievement/image/10/logo.svg",
  "nbr_of_success": null,
  "users_url": "https://api.intra.42.fr/v2/achievements/10/users",
  "achievements": [],
  "parent": null,
  "title": null
}
```

### `DELETE /v2/achievements/8` — HTTP 204

```
(no body)
```

### `GET /v2/achievements` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Film buff",
    "description": "Regarder 1 video sur l'e-learning.",
    "tier": "none",
    "kind": "pedagogy",
    "visible": true,
    "image": "/uploads/achievement/image/1/logo.svg",
    "nbr_of_success": 1,
    "users_url": "https://api.intra.42.fr/v2/achievements/1/users",
    "achievements": [],
    "parent": null,
    "title": null
  },
  {
    "id": 3,
    "name": "Film buff",
    "description": "Regarder 21 videos sur l'e-learning.",
    "tier": "none",
    "kind": "pedagogy",
    "visible": true,
    "image": "/uploads/achievement/image/3/logo.svg",
    "nbr_of_success": 21,
    "users_url": "https://api.intra.42.fr/v2/achievements/3/users",
    "achievements": [],
    "parent": null,
    "title": null
  },
  {
    "id": 4,
    "name": "Film buff",
    "description": "Regarder 42 videos sur l'e-learning.",
    "tier": "none",
    "kind": "pedagogy",
    "visible": true,
    "image": "/uploads/achievement/image/4/logo.svg",
    "nbr_of_success": 42,
    "users_url": "https://api.intra.42.fr/v2/achievements/4/users",
    "achievements": [],
    "parent": null,
    "title": null
  }
]
```

### `GET /v2/achievements/8` — HTTP 200

```json
{
  "id": 8,
  "name": "Film buff",
  "description": "Regarder 10 videos sur l'e-learning.",
  "tier": "none",
  "kind": "pedagogy",
  "visible": true,
  "image": "/uploads/achievement/image/8/logo.svg",
  "nbr_of_success": 10,
  "users_url": "https://api.intra.42.fr/v2/achievements/8/users",
  "achievements": [],
  "parent": null,
  "title": null
}
```

### `PUT /v2/achievements/8`

```
  "achievement": {
    "name": "Be a test of the API",
    "internal_name": "BeATestAPI",
    "kind": "social",
    "tier": "none",
    "description": "Be used as a test for the api",
    "image": {
      "tempfile": [],
      "original_filename": "logo.svg",
      "content_type": "image/svg+xml",
      "headers": "Content-Disposition: form-data; name=\"achievement[image]\"; filename=\"logo.svg\"\r\nContent-Type: image/svg+xml\r\nContent-Length: 2989\r\n"
    },
    "title_id": "30",
    "cursus_ids": [
      "1"
    ],
    "campus_ids": [
      "1"
    ],
    "lg": "1"
  }
}
204
```


## achievements_users

### `POST /v2/achievements_users`

```
  "achievements_user": {
    "achievement_id": "1",
    "user_id": "29"
  }
}
201
{
  "id": 127,
  "user_id": 29,
  "login": "askywalk",
  "url": "https://api.intra.42.fr/v2/users/askywalk",
  "created_at": "2017-11-22T13:43:26.572Z"
}
```

### `DELETE /v2/achievements_users/105` — HTTP 204

```
(no body)
```

### `GET /v2/achievements_users` — HTTP 200

```json
[
  {
    "id": 126,
    "user_id": 126,
    "login": "darthcae",
    "url": "https://api.intra.42.fr/v2/users/darthcae",
    "created_at": "2017-11-22T13:41:22.464Z"
  },
  {
    "id": 125,
    "user_id": 125,
    "login": "sebulseb",
    "url": "https://api.intra.42.fr/v2/users/sebulseb",
    "created_at": "2017-11-22T13:41:22.453Z"
  },
  {
    "id": 124,
    "user_id": 124,
    "login": "hsolo2",
    "url": "https://api.intra.42.fr/v2/users/hsolo2",
    "created_at": "2017-11-22T13:41:22.442Z"
  }
]
```

### `GET /v2/achievements_users/105` — HTTP 200

```json
{
  "id": 105,
  "user_id": 105,
  "login": "yodyoda2",
  "url": "https://api.intra.42.fr/v2/users/yodyoda2",
  "created_at": "2017-11-22T13:41:22.217Z"
}
```

### `PUT /v2/achievements_users/105`

```
  "achievements_user": {
    "achievement_id": "5",
    "user_id": "30"
  }
}
204
```


## announcements

### `POST /v2/announcements`

```
  "announcement": {
    "author": "42partnerships",
    "campus_ids": [
      "1"
    ],
    "cursus_ids": [
      "1"
    ],
    "expire_at": "2017-11-22 14:13:10 UTC",
    "kind": "global",
    "text": "42partnerships revient",
    "title": "Partenariats écoles 2016"
  }
}
201
{
  "id": 5,
  "author": "42partnerships",
  "title": "Partenariats écoles 2016",
  "text": "42partnerships revient",
  "kind": "global",
  "link": null,
  "created_at": "2017-11-22T13:43:27.259Z",
  "updated_at": "2017-11-22T13:43:27.259Z",
  "expire_at": "2017-11-22T14:13:10.000Z"
}
```

### `DELETE /v2/announcements/4` — HTTP 204

```
(no body)
```

### `GET /v2/announcements/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 4
}
```

### `GET /v2/announcements/4` — HTTP 200

```json
{
  "id": 4,
  "author": "Jerrell Prohaska",
  "title": "Minnesota frogs",
  "text": "Pickled aut et repellendus ugh sed a natus. Beatae cliche knausgaard.",
  "kind": "global",
  "link": null,
  "created_at": "2017-11-22T13:41:03.321Z",
  "updated_at": "2017-11-22T13:41:03.321Z",
  "expire_at": "2017-11-03T07:42:11.309Z"
}
```

### `PUT /v2/announcements/4`

```
  "announcement": {
    "author": "42partnerships",
    "campus_ids": [
      "1"
    ],
    "cursus_ids": [
      "1"
    ],
    "expire_at": "2017-11-22 14:13:10 UTC",
    "kind": "global",
    "text": "42partnerships revient",
    "title": "Partenariats écoles 2016"
  }
}
204
```


## anti_grav_units_users

### `POST /v2/anti_grav_units_users`

```
  "anti_grav_units_user": {
    "begin_date": "2019-12-09",
    "expected_end_date": "2020-02-10",
    "user_id": 80962,
    "is_free": true,
    "anti_grav_unit_id": 1
  }
}
201
{
  "anti_grav_units_user": {
    "id": 64,
    "user_id": 18763,
    "anti_grav_unit_id": 1,
    "begin_date": "2019-12-09",
    "expected_end_date": "2020-02-10",
    "reason": "other",
    "is_free": true,
    "close_id": 65822,
    "created_at": "2019-12-09T14:17:15.986Z",
    "updated_at": "2019-12-09T14:17:15.986Z"
  }
}
```

### `GET /v2/anti_grav_units_users` — HTTP 200

```json
[
  {
    "anti_grav_units_user": {
      "id": 64,
      "expected_end_date": "2020-02-10",
      "begin_date": "2019-12-09",
      "user_id": 18763,
      "is_free": true,
      "created_at": "2019-12-09T14:17:15.986Z",
      "updated_at": "2019-12-09T14:17:15.986Z",
      "anti_grav_unit_id": 1,
      "reason": "I secured a job/internship",
      "close_id": 65822
    }
  }
]
```

### `GET /v2/anti_grav_units_users/64` — HTTP 200

```json
{
  "anti_grav_units_user": {
    "id": 64,
    "expected_end_date": "2020-02-10",
    "begin_date": "2019-12-09",
    "user_id": 18763,
    "is_free": true,
    "created_at": "2019-12-09T14:17:15.986Z",
    "updated_at": "2019-12-09T14:17:15.986Z",
    "anti_grav_unit_id": 1,
    "reason": "I secured a job/internship",
    "close_id": 65822
  }
}
```

### `PUT /v2/anti_grav_units_users/64`

```
  "anti_grav_units_user": {
    "begin_date": "2019-12-09",
    "expected_end_date": "2020-03-10",
    "is_free": false
  }
}
204
{
  "anti_grav_units_user": {
    "id": 64,
    "user_id": 18763,
    "anti_grav_unit_id": 1,
    "begin_date": "2019-12-09",
    "expected_end_date": "2020-03-10",
    "reason": "other",
    "is_free": false,
    "close_id": 65822,
    "created_at": "2019-12-09T14:17:15.986Z",
    "updated_at": "2019-12-09T14:17:15.986Z"
  }
}
```


## apps

### `GET /v2/apps` — HTTP 200

```json
[
  {
    "id": 7,
    "name": "test intrateam staff oauth application",
    "description": null,
    "image": null,
    "website": null,
    "public": true,
    "scopes": [],
    "created_at": "2017-11-22T13:43:11.377Z",
    "updated_at": "2017-11-22T13:43:11.434Z",
    "owner": {
      "id": 74,
      "login": "pamidala",
      "url": "https://api.intra.42.fr/v2/users/pamidala"
    },
    "rate_limit": 1800,
    "roles": [
      {
        "id": 16,
        "name": "Official App",
        "description": "Approved application without rate limits"
      },
      {
        "id": 7,
        "name": "Basic Staff",
        "description": "Member of the staff, can manage community services, closes, exams and access advanced student data"
      },
      {
        "id": 11,
        "name": "Advanced Staff",
        "description": "Member of the staff, with higher privileges"
      },
      {
        "id": 1,
        "name": "Intrateam",
        "description": "manage all"
      }
    ]
  },
  {
    "id": 6,
    "name": "test pedago oauth application",
    "description": null,
    "image": null,
    "website": null,
    "public": true,
    "scopes": [],
    "created_at": "2017-11-22T13:43:11.315Z",
    "updated_at": "2017-11-22T13:43:11.369Z",
    "owner": {},
    "rate_limit": 1800,
    "roles": [
      {
        "id": 16,
        "name": "Official App",
        "description": "Approved application without rate limits"
      },
      {
        "id": 7,
        "name": "Basic Staff",
        "description": "Member of the staff, can manage community services, closes, exams and access advanced student data"
      },
      {
        "id": 11,
        "name": "Advanced Staff",
        "description": "Member of the staff, with higher privileges"
      },
      {
        "id": 5,
        "name": "Advanced Tutor",
        "description": "Manage skills, cursus and all low level pedagogic data"
      }
    ]
  },
  {
    "id": 5,
    "name": "test advanced staff oauth application",
    "description": null,
    "image": null,
    "website": null,
    "public": true,
    "scopes": [],
    "created_at": "2017-11-22T13:43:11.261Z",
    "updated_at": "2017-11-22T13:43:11.307Z",
    "owner": {},
    "rate_limit": 1800,
    "roles": [
      {
        "id": 16,
        "name": "Official App",
        "description": "Approved application without rate limits"
      },
      {
        "id": 7,
        "name": "Basic Staff",
        "description": "Member of the staff, can manage community services, closes, exams and access advanced student data"
      },
      {
        "id": 11,
        "name": "Advanced Staff",
        "description": "Member of the staff, with higher privileges"
      }
    ]
  }
]
```

### `GET /v2/apps/7` — HTTP 200

```json
{
  "id": 7,
  "name": "test intrateam staff oauth application",
  "description": null,
  "image": null,
  "website": null,
  "public": true,
  "scopes": [],
  "created_at": "2017-11-22T13:43:11.377Z",
  "updated_at": "2017-11-22T13:43:11.434Z",
  "owner": {
    "id": 74,
    "login": "pamidala",
    "url": "https://api.intra.42.fr/v2/users/pamidala"
  },
  "rate_limit": 1800,
  "roles": [
    {
      "id": 16,
      "name": "Official App",
      "description": "Approved application without rate limits"
    },
    {
      "id": 7,
      "name": "Basic Staff",
      "description": "Member of the staff, can manage community services, closes, exams and access advanced student data"
    },
    {
      "id": 11,
      "name": "Advanced Staff",
      "description": "Member of the staff, with higher privileges"
    },
    {
      "id": 1,
      "name": "Intrateam",
      "description": "manage all"
    }
  ]
}
```


## attachments

### `DELETE /v2/attachments/1` — HTTP 204

```
(no body)
```

### `GET /v2/projects/4/attachments` — HTTP 200

```json
[

]
```

### `GET /v2/attachments/1` — HTTP 200

```json
{
  "id": 1,
  "name": "New Jersey zombies",
  "pdf": {
    "pdf": {
      "url": null,
      "thumb": {
        "url": null
      }
    }
  },
  "page_count": 1,
  "created_at": "2017-11-22T13:41:25.981Z",
  "pdf_processing": true,
  "slug": "new-jersey-zombies",
  "url": null,
  "thumb_url": null,
  "base_id": 1,
  "language": {
    "id": 3,
    "name": "Romanian",
    "identifier": "ro"
  },
  "type": "Pdf"
}
```


## balances

### `GET /v2/balances?page=1`

```json
[
  {
    "id": 191,
    "begin_at": "2018-06-16 10:49:28",
    "end_at": "2018-06-16 14:03:41",
    "pool_id": 21
  },
  {
    "id": 192,
    "begin_at": "2018-06-25 22:52:56",
    "end_at": "2018-07-23 22:52:56",
    "pool_id": 16
  },
  {
    "id": 193,
    "begin_at": "2018-06-28 11:56:03",
    "end_at": "2018-07-26 11:56:03",
    "pool_id": 18
  }
]
```

### `GET /v2/balances/191` — HTTP 200

```json
{
  "id": 191,
  "begin_at": "2018-06-16 10:49:28",
  "end_at": "2018-06-16 14:03:41",
  "pool_id": 21
}
```

### `PUT /v2/balances/191`

```
  "balance": {
    "begin_at": "2018-06-16 10:49:28",
    "end_at": "2018-06-16 14:03:41"
  }
}
204
```


## bloc_deadlines

### `POST /v2/bloc_deadlines`

```
  "bloc_deadline": {
    "begin_at": "2022-11-29",
    "bloc_id": "1",
    "coalition_id": "2",
    "end_at": "2023-11-29"
  }
}
201
{
  "id": 6,
  "bloc_id": 1,
  "coalition_id": 2,
  "begin_at": "2022-11-29T00:00:00.000Z",
  "end_at": "2023-11-29T00:00:00.000Z",
  "created_at": "2017-11-22T13:43:28.263Z",
  "updated_at": "2017-11-22T13:43:28.263Z"
}
```

### `GET /v2/bloc_deadlines/1` — HTTP 200

```json
{
  "id": 1,
  "bloc_id": 1,
  "coalition_id": 1,
  "begin_at": "2017-11-22T13:41:20.752Z",
  "end_at": "2018-11-22T13:41:20.752Z",
  "created_at": "2017-11-22T13:41:20.764Z",
  "updated_at": "2017-11-22T13:41:20.764Z"
}
```

### `PUT /v2/bloc_deadlines/1`

```
  "bloc_deadline": {
    "begin_at": "2022-11-29",
    "bloc_id": "1",
    "coalition_id": "2",
    "end_at": "2023-11-29"
  }
}
204
```


## blocs

### `GET /v2/blocs` — HTTP 200

```json
[
  {
    "id": 1,
    "campus_id": 5,
    "cursus_id": 1,
    "squad_size": 80,
    "created_at": "2017-11-22T13:41:20.665Z",
    "updated_at": "2017-11-22T13:41:20.665Z",
    "coalitions": [
      {
        "id": 1,
        "name": "Indiana goblins",
        "slug": "super-slug",
        "image_url": "https://admin.intra.42.fr/uploads/coalition/image/1/logo.svg",
        "color": "#1c7f08",
        "score": 54,
        "user_id": 38
      },
      {
        "id": 2,
        "name": "Kansas giants",
        "slug": "super-slug",
        "image_url": "https://admin.intra.42.fr/uploads/coalition/image/2/logo.svg",
        "color": "#087262",
        "score": 83,
        "user_id": 90
      }
    ]
  }
]
```

### `GET /v2/blocs/1` — HTTP 200

```json
{
  "id": 1,
  "campus_id": 5,
  "cursus_id": 1,
  "squad_size": 80,
  "created_at": "2017-11-22T13:41:20.665Z",
  "updated_at": "2017-11-22T13:41:20.665Z",
  "coalitions": [
    {
      "id": 1,
      "name": "Indiana goblins",
      "slug": "super-slug",
      "image_url": "https://admin.intra.42.fr/uploads/coalition/image/1/logo.svg",
      "color": "#1c7f08",
      "score": 54,
      "user_id": 38
    },
    {
      "id": 2,
      "name": "Kansas giants",
      "slug": "super-slug",
      "image_url": "https://admin.intra.42.fr/uploads/coalition/image/2/logo.svg",
      "color": "#087262",
      "score": 83,
      "user_id": 90
    }
  ]
}
```


## campus

### `POST /v2/campus`

```
  "campus": {
    "address": "42007 Mossie Forest",
    "city": "Danielton",
    "content_email": "Hi __first_name__",
    "country": "Bonaire, Sint Eustatius and Saba",
    "display_name": "42 Paris",
    "language_id": "1",
    "logo": "#<File:0x007fa9e8b2c048>",
    "name": "Argentina1",
    "time_of_community_service_started": "2017-11-22 14:00:00 +0100",
    "time_zone": "Pacific/Pago_Pago",
    "website": "http://cruickshankwehner.org/pinkie_reynolds",
    "zip": "19751-7157"
  }
}
201
{
  "id": 7,
  "name": "Argentina1",
  "time_zone": "Pacific/Pago_Pago",
  "language": {
    "id": 1,
    "name": "Français",
    "identifier": "fr"
  },
  "users_count": 0,
  "vogsphere_id": null,
  "endpoint": null
}
```

### `GET /v2/campus` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Paris",
    "time_zone": "Europe/Paris",
    "language": {
      "id": 1,
      "name": "Français",
      "identifier": "fr"
    },
    "users_count": 22997,
    "vogsphere_id": 1,
    "country": "France",
    "address": "96, boulevard Bessières",
    "zip": "75017",
    "city": "Paris",
    "website": "http://www.42.fr/",
    "facebook": "https://facebook.com/42born2code",
    "twitter": "https://twitter.com/42born2code",
    "active": true,
    "public": true,
    "email_extension": "42.fr",
    "default_hidden_phone": false,
    "endpoint": {
      "id": 33,
      "url": "https://endpoint.42paris.fr",
      "description": "42paris's new ldapkdc endpoint",
      "created_at": "2021-06-14T07:49:14.872Z",
      "updated_at": "2021-06-28T15:24:45.089Z"
    }
  },
  {
    "id": 9,
    "name": "Lyon",
    "time_zone": "Europe/Paris",
    "language": {
      "id": 1,
      "name": "Français",
      "identifier": "fr"
    },
    "users_count": 2077,
    "vogsphere_id": 4,
    "country": "France",
    "address": "Campus Région – 78 route de Paris",
    "zip": "69260",
    "city": "Charbonnières-les-Bains",
    "website": "https://www.42lyon.fr/",
    "facebook": "https://www.facebook.com/42lyon",
    "twitter": "https://twitter.com/42lyon",
    "active": true,
    "public": true,
    "email_extension": "42lyon.fr",
    "default_hidden_phone": false,
    "endpoint": {
      "id": 19,
      "url": "https://bigbro.42lyon.fr",
      "description": "42 Lyon endpoint tmp",
      "created_at": "2020-07-28T15:21:29.199Z",
      "updated_at": "2020-07-28T15:21:29.199Z"
    }
  }
]
```

### `GET /v2/campus/1` — HTTP 200

```json
{
  "id": 1,
  "name": "Paris",
  "time_zone": "Europe/Paris",
  "language": {
    "id": 1,
    "name": "Français",
    "identifier": "fr"
  },
  "users_count": 22997,
  "vogsphere_id": 1,
  "country": "France",
  "address": "96, boulevard Bessières",
  "zip": "75017",
  "city": "Paris",
  "website": "http://www.42.fr/",
  "facebook": "https://facebook.com/42born2code",
  "twitter": "https://twitter.com/42born2code",
  "active": true,
  "public": true,
  "email_extension": "42.fr",
  "default_hidden_phone": false,
  "endpoint": {
    "id": 33,
    "url": "https://endpoint.42paris.fr",
    "description": "42paris's new ldapkdc endpoint",
    "created_at": "2021-06-14T07:49:14.872Z",
    "updated_at": "2021-06-28T15:24:45.089Z"
  }
}
```

### `PUT /v2/campus/3`

```
  "campus": {
    "address": "42007 Mossie Forest",
    "city": "Danielton",
    "content_email": "Hi __first_name__",
    "country": "Bonaire, Sint Eustatius and Saba",
    "display_name": "42 Paris",
    "language_id": "3",
    "logo": "#<File:0x007fa9e98c3288>",
    "name": "Jamaica2",
    "time_of_community_service_started": "2017-11-22 14:00:00 +0100",
    "time_zone": "Asia/Kathmandu",
    "website": "http://cruickshankwehner.org/pinkie_reynolds",
    "zip": "19751-7157"
  }
}
204
```


## campus_users

### `POST /v2/campus_users`

```
  "campus_user": {
    "campus_id": "6",
    "user_id": "1"
  }
}
201
{
  "id": 127,
  "user_id": 1,
  "campus_id": 6,
  "is_primary": false
}
```

### `GET /v2/campus_users/126` — HTTP 200

```json
{
  "id": 126,
  "user_id": 126,
  "campus_id": 1,
  "is_primary": true
}
```


## closes

### `POST /v2/closes`

```
  "close": {
    "closer_id": "2",
    "kind": "other",
    "reason": "Mange des patates douces en cluster 🍠",
    "state": "close",
    "user_id": "64",
    "end_at": "2017-11-23T13:43:29.676Z"
  }
}
201
{
  "id": 3,
  "reason": "Mange des patates douces en cluster 🍠",
  "state": "close",
  "created_at": "2017-11-22T13:43:29.676Z",
  "updated_at": "2017-11-22T13:43:29.676Z",
  "community_services": [],
  "user": {
    "id": 64,
    "login": "shepalpa",
    "url": "https://api.intra.42.fr/v2/users/shepalpa"
  },
  "closer": {
    "id": 2,
    "login": "andre",
    "url": "https://api.intra.42.fr/v2/users/andre"
  }
}
```

### `DELETE /v2/closes/2` — HTTP 204

```
(no body)
```

### `GET /v2/closes` — HTTP 200

```json
[
  {
    "id": 3,
    "reason": "Connecticut giants",
    "state": "unclose",
    "created_at": "2017-11-22T13:42:20.888Z",
    "updated_at": "2017-11-22T13:42:20.987Z",
    "end_at": null,
    "community_services": [
      {
        "id": 2,
        "duration": 14400,
        "schedule_at": "2017-11-28T06:00:00.000Z",
        "occupation": "West Virginia lions",
        "state": "schedule",
        "created_at": "2017-11-22T13:42:20.944Z",
        "updated_at": "2017-11-22T13:42:21.007Z"
      }
    ],
    "user": {
      "id": 82,
      "login": "kyren",
      "url": "https://api.intra.42.fr/v2/users/kyren"
    },
    "closer": {
      "id": 2,
      "login": "andre",
      "url": "https://api.intra.42.fr/v2/users/andre"
    }
  },
  {
    "id": 2,
    "reason": "Florida druids",
    "state": "unclose",
    "created_at": "2017-11-22T13:42:20.695Z",
    "updated_at": "2017-11-22T13:42:20.857Z",
    "end_at": null,
    "community_services": [
      {
        "id": 1,
        "duration": 14400,
        "schedule_at": "2017-11-27T11:00:00.000Z",
        "occupation": "North Carolina spirits",
        "state": "schedule",
        "created_at": "2017-11-22T13:42:20.806Z",
        "updated_at": "2017-11-22T13:42:20.876Z"
      }
    ],
    "user": {
      "id": 114,
      "login": "darmaul",
      "url": "https://api.intra.42.fr/v2/users/darmaul"
    },
    "closer": {
      "id": 3,
      "login": "gargamel",
      "url": "https://api.intra.42.fr/v2/users/gargamel"
    }
  },
  {
    "id": 1,
    "reason": "Florida druids",
    "state": "unclose",
    "created_at": "2017-11-22T13:42:20.695Z",
    "updated_at": "2017-11-22T13:42:20.857Z",
    "end_at": "2017-11-24T13:42:20.857Z",
    "community_services": [],
    "user": {
      "id": 114,
      "login": "darmaul",
      "url": "https://api.intra.42.fr/v2/users/darmaul"
    },
    "closer": {
      "id": 3,
      "login": "gargamel",
      "url": "https://api.intra.42.fr/v2/users/gargamel"
    }
  }
]
```

### `GET /v2/closes/2` — HTTP 200

```json
{
  "id": 2,
  "reason": "Connecticut giants",
  "state": "unclose",
  "created_at": "2017-11-22T13:42:20.888Z",
  "updated_at": "2017-11-22T13:42:20.987Z",
  "end_at": null,
  "community_services": [
    {
      "id": 2,
      "duration": 14400,
      "schedule_at": "2017-11-28T06:00:00.000Z",
      "occupation": "West Virginia lions",
      "state": "schedule",
      "created_at": "2017-11-22T13:42:20.944Z",
      "updated_at": "2017-11-22T13:42:21.007Z"
    }
  ],
  "user": {
    "id": 82,
    "login": "kyren",
    "url": "https://api.intra.42.fr/v2/users/kyren"
  },
  "closer": {
    "id": 2,
    "login": "andre",
    "url": "https://api.intra.42.fr/v2/users/andre"
  }
}
```

### `PUT /v2/closes/2`

```
  "close": {
    "closer_id": "1",
    "kind": "other",
    "reason": "Mange des patates douces en cluster 🍠",
    "state": "close",
    "user_id": "41"
  }
}
204
```


## coalitions

### `POST /v2/coalitions`

```
  "coalition": {
    "name": "rabbits",
    "bloc_id": "1",
    "user_id": "35",
    "image": {
      "tempfile": [],
      "original_filename": "logo.svg",
      "content_type": "image/svg+xml",
      "headers": "Content-Disposition: form-data; name=\"coalition[image]\"; filename=\"logo.svg\"\r\nContent-Type: image/svg+xml\r\nContent-Length: 2989\r\n"
    },
    "color": "#4231d7"
  }
}
201
{
  "id": 3,
  "name": "rabbits",
  "slug": "rabbits",
  "image_url": "https://admin.intra.42.fr/uploads/coalition/image/3/logo.svg",
  "color": "#4231d7",
  "score": 0,
  "user_id": 35
}
```

### `GET /v2/coalitions` — HTTP 200

```json
[
  {
    "id": 2,
    "name": "Kansas giants",
    "slug": "super-slug",
    "image_url": "https://admin.intra.42.fr/uploads/coalition/image/2/logo.svg",
    "color": "#087262",
    "score": 83,
    "user_id": 90
  },
  {
    "id": 1,
    "name": "Indiana goblins",
    "slug": "super-slug",
    "image_url": "https://admin.intra.42.fr/uploads/coalition/image/1/logo.svg",
    "color": "#1c7f08",
    "score": 54,
    "user_id": 38
  }
]
```

### `GET /v2/coalitions/2` — HTTP 200

```json
{
  "id": 2,
  "name": "Kansas giants",
  "slug": "super-slug",
  "image_url": "https://admin.intra.42.fr/uploads/coalition/image/2/logo.svg",
  "color": "#087262",
  "score": 83,
  "user_id": 90
}
```

### `PUT /v2/coalitions/2`

```
  "coalition": {
    "name": "monkeys",
    "bloc_id": "1",
    "user_id": "34",
    "image": {
      "tempfile": [],
      "original_filename": "logo.svg",
      "content_type": "image/svg+xml",
      "headers": "Content-Disposition: form-data; name=\"coalition[image]\"; filename=\"logo.svg\"\r\nContent-Type: image/svg+xml\r\nContent-Length: 2989\r\n"
    },
    "color": "#f8f45d"
  }
}
204
```


## coalitions_users

### `GET /v2/coalitions_users/4` — HTTP 200

```json
{
  "id": 4,
  "coalition_id": 1,
  "user_id": 67,
  "created_at": "2017-11-22T13:42:09.775Z",
  "updated_at": "2017-11-22T13:42:09.775Z"
}
```

### `PUT /v2/coalitions_users/4`

```
  "coalitions_user": {
    "coalition_id": "2",
    "user_id": "24"
  }
}
204
```

### `POST /v2/coalitions_users`

```
  "coalitions_user": {
    "coalition_id": "2",
    "user_id": "60"
  }
}
201
{
  "id": 5,
  "coalition_id": 2,
  "user_id": 60,
  "created_at": "2017-11-22T13:43:31.350Z",
  "updated_at": "2017-11-22T13:43:31.350Z"
}
```

### `DELETE /v2/coalitions_users/4` — HTTP 204

```
(no body)
```

### `GET /v2/coalitions_users` — HTTP 200

```json
[
  {
    "id": 4,
    "coalition_id": 1,
    "user_id": 67,
    "created_at": "2017-11-22T13:42:09.775Z",
    "updated_at": "2017-11-22T13:42:09.775Z"
  },
  {
    "id": 3,
    "coalition_id": 1,
    "user_id": 25,
    "created_at": "2017-11-22T13:42:09.750Z",
    "updated_at": "2017-11-22T13:42:09.750Z"
  },
  {
    "id": 2,
    "coalition_id": 2,
    "user_id": 23,
    "created_at": "2017-11-22T13:42:09.723Z",
    "updated_at": "2017-11-22T13:42:09.723Z"
  }
]
```


## community_services

### `POST /v2/community_services.json`

```
  "community_service": {
    "close_id": "2",
    "duration": "14400",
    "occupation": "Regarder Shrek, en entier, avec Mathieu Trentin",
    "schedule_at": "2017-11-27 09:00:00 UTC",
    "tiger_id": "2"
  }
}
201
{
  "id": 3,
  "duration": 14400,
  "schedule_at": "2017-11-27T06:00:00.000Z",
  "occupation": "Regarder Shrek, en entier, avec Mathieu Trentin",
  "state": "schedule",
  "created_at": "2017-11-22T13:43:32.216Z",
  "updated_at": "2017-11-22T13:43:32.216Z",
  "close": {
    "id": 2,
    "reason": "Connecticut giants",
    "state": "unclose",
    "created_at": "2017-11-22T13:42:20.888Z",
    "updated_at": "2017-11-22T13:42:20.987Z"
  }
}
```

### `DELETE /v2/community_services/1.json` — HTTP 204

```
(no body)
```

### `GET /v2/community_services/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 2
}
```

### `GET /v2/community_services.json` — HTTP 200

```json
[
  {
    "id": 2,
    "duration": 14400,
    "schedule_at": "2017-11-28T06:00:00.000Z",
    "occupation": "West Virginia lions",
    "state": "schedule",
    "created_at": "2017-11-22T13:42:20.944Z",
    "updated_at": "2017-11-22T13:42:21.007Z",
    "close": {
      "id": 2,
      "reason": "Connecticut giants",
      "state": "unclose",
      "created_at": "2017-11-22T13:42:20.888Z",
      "updated_at": "2017-11-22T13:42:20.987Z"
    }
  },
  {
    "id": 1,
    "duration": 14400,
    "schedule_at": "2017-11-27T11:00:00.000Z",
    "occupation": "North Carolina spirits",
    "state": "schedule",
    "created_at": "2017-11-22T13:42:20.806Z",
    "updated_at": "2017-11-22T13:42:20.876Z",
    "close": {
      "id": 1,
      "reason": "Florida druids",
      "state": "unclose",
      "created_at": "2017-11-22T13:42:20.695Z",
      "updated_at": "2017-11-22T13:42:20.857Z"
    }
  }
]
```

### `GET /v2/community_services/1.json` — HTTP 200

```json
{
  "id": 1,
  "duration": 14400,
  "schedule_at": "2017-11-27T11:00:00.000Z",
  "occupation": "North Carolina spirits",
  "state": "schedule",
  "created_at": "2017-11-22T13:42:20.806Z",
  "updated_at": "2017-11-22T13:42:20.876Z",
  "close": {
    "id": 1,
    "reason": "Florida druids",
    "state": "unclose",
    "created_at": "2017-11-22T13:42:20.695Z",
    "updated_at": "2017-11-22T13:42:20.857Z"
  }
}
```

### `PUT /v2/community_services/1.json`

```
  "community_service": {
    "close_id": "2",
    "duration": "14400",
    "occupation": "Regarder Shrek, en entier, avec Mathieu Trentin",
    "schedule_at": "2017-11-27 09:00:00 UTC",
    "tiger_id": "2"
  }
}
204
```


## cursus

### `POST /v2/cursus`

```
  "cursus": {
    "name": "Oregon tigers",
    "skill_ids": [
      "11",
      "12"
    ]
  }
}
201
{
  "id": 3,
  "created_at": "2017-11-22T13:43:33.469Z",
  "name": "Oregon tigers",
  "slug": "oregon-tigers"
}
```

### `GET /v2/cursus` — HTTP 200

```json
[
  {
    "id": 2,
    "created_at": "2017-11-22T13:41:00.825Z",
    "name": "42",
    "slug": "42"
  },
  {
    "id": 1,
    "created_at": "2017-11-22T13:41:00.750Z",
    "name": "Piscine C",
    "slug": "piscine-c"
  }
]
```

### `GET /v2/cursus/2` — HTTP 200

```json
{
  "id": 2,
  "created_at": "2017-11-22T13:41:00.825Z",
  "name": "42",
  "slug": "42"
}
```

### `PUT /v2/cursus/2`

```
  "cursus": {
    "name": "Oregon kangaroos",
    "skill_ids": [
      "13",
      "14"
    ]
  }
}
204
```


## cursus_users

### `POST /v2/cursus_users`

```
  "cursus_user": {
    "begin_at": "2017-07-22 13:43:10 UTC",
    "cursus_id": "2",
    "end_at": "2018-03-22 13:43:10 UTC",
    "user_id": "1"
  }
}
201
{
  "id": 127,
  "begin_at": "2017-07-22T13:43:10.000Z",
  "end_at": "2018-03-22T13:43:10.000Z",
  "grade": null,
  "level": 0.0,
  "skills": [],
  "cursus_id": 2,
  "has_coalition": true,
  "user": {
    "id": 1,
    "login": "jeanne",
    "url": "https://api.intra.42.fr/v2/users/jeanne"
  },
  "cursus": {
    "id": 2,
    "created_at": "2017-11-22T13:41:00.825Z",
    "name": "42",
    "slug": "42"
  }
}
```

### `DELETE /v2/cursus_users/7` — HTTP 204

```
(no body)
```

### `GET /v2/cursus_users/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 126
}
```

### `GET /v2/cursus_users` — HTTP 200

```json
[
  {
    "id": 126,
    "begin_at": "2016-12-16T07:41:39.516Z",
    "end_at": null,
    "grade": "Cadet",
    "level": 0.0,
    "skills": [],
    "cursus_id": 2,
    "has_coalition": true,
    "user": {
      "id": 126,
      "login": "darthcae",
      "url": "https://api.intra.42.fr/v2/users/darthcae"
    },
    "cursus": {
      "id": 2,
      "created_at": "2017-11-22T13:41:00.825Z",
      "name": "42",
      "slug": "42"
    }
  },
  {
    "id": 125,
    "begin_at": "2017-11-10T21:38:19.158Z",
    "end_at": null,
    "grade": "Cadet",
    "level": 0.0,
    "skills": [],
    "cursus_id": 1,
    "has_coalition": true,
    "user": {
      "id": 125,
      "login": "sebulseb",
      "url": "https://api.intra.42.fr/v2/users/sebulseb"
    },
    "cursus": {
      "id": 1,
      "created_at": "2017-11-22T13:41:00.750Z",
      "name": "Piscine C",
      "slug": "piscine-c"
    }
  },
  {
    "id": 124,
    "begin_at": "2017-07-22T03:48:20.016Z",
    "end_at": null,
    "grade": "Cadet",
    "level": 0.0,
    "skills": [],
    "cursus_id": 2,
    "has_coalition": true,
    "user": {
      "id": 124,
      "login": "hsolo2",
      "url": "https://api.intra.42.fr/v2/users/hsolo2"
    },
    "cursus": {
      "id": 2,
      "created_at": "2017-11-22T13:41:00.825Z",
      "name": "42",
      "slug": "42"
    }
  }
]
```

### `GET /v2/cursus_users/7` — HTTP 200

```json
{
  "id": 7,
  "begin_at": "2017-06-13T03:05:07.756Z",
  "end_at": null,
  "grade": "Cadet",
  "level": 0.0,
  "skills": [],
  "cursus_id": 1,
  "has_coalition": true,
  "user": {
    "id": 7,
    "login": "jbinks",
    "url": "https://api.intra.42.fr/v2/users/jbinks"
  },
  "cursus": {
    "id": 1,
    "created_at": "2017-11-22T13:41:00.750Z",
    "name": "Piscine C",
    "slug": "piscine-c"
  }
}
```

### `PUT /v2/cursus_users/7`

```
  "cursus_user": {
    "begin_at": "2017-07-22 13:43:10 UTC",
    "cursus_id": "2",
    "end_at": "2018-03-22 13:43:10 UTC",
    "user_id": "1"
  }
}
204
```


## dashes

### `POST /v2/dashes`

```
  "dash": {
    "begin_at": "2017-11-25 13:43:35 UTC",
    "campus_id": "2",
    "cursus_id": "1",
    "description": "Le sujet dbon courage!",
    "duration": "20",
    "name": "Dashname",
    "nbr_xp": "20",
    "skill_id": "3",
    "slug": "dashname"
  }
}
201
{
  "id": 2,
  "name": "Dashname",
  "description": "Le sujet dbon courage!",
  "slug": "dashname",
  "cursus_id": 1,
  "campus_id": 2,
  "skill_id": 3,
  "nbr_xp": "20",
  "begin_at": "2017-11-25T13:43:35.000Z",
  "end_at": "2017-11-25T14:03:35.000Z"
}
```

### `DELETE /v2/dashes/1` — HTTP 204

```
(no body)
```

### `PUT /v2/dashes/1`

```
  "dash": {
    "begin_at": "2017-11-25 13:43:35 UTC",
    "campus_id": "1",
    "cursus_id": "2",
    "description": "Le sujet dbon courage!",
    "duration": "20",
    "name": "Dashname",
    "nbr_xp": "20",
    "skill_id": "2",
    "slug": "dashname"
  }
}
204
```


## dashes_users

### `POST /v2/dashes_users`

```
  "dashes_user": {
    "dash_id": "1",
    "user_id": "1"
  }
}
201
{
  "id": 2,
  "dash_id": 1,
  "user_id": 1,
  "repo_url": null,
  "repo_uuid": null,
  "final_mark": null
}
```

### `DELETE /v2/dashes_users/1` — HTTP 204

```
(no body)
```

### `GET /v2/dashes_users/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 1
}
```

### `GET /v2/dashes_users` — HTTP 200

```json
[
  {
    "id": 1,
    "dash_id": 1,
    "user_id": 6,
    "repo_url": null,
    "repo_uuid": null,
    "final_mark": null
  }
]
```

### `GET /v2/dashes_users/1` — HTTP 200

```json
{
  "id": 1,
  "dash_id": 1,
  "user_id": 6,
  "repo_url": null,
  "repo_uuid": null,
  "final_mark": null
}
```

### `PUT /v2/dashes_users/1`

```
  "dashes_user": {
    "dash_id": "1",
    "user_id": "1"
  }
}
204
```


## endpoints

### `GET /v2/endpoints?page=1` — HTTP 200

```json
[
  {
    "id": 1,
    "url": "http://evil.machine.ai",
    "description": "The endpoint for the evil machine",
    "created_at": "2016-05-06T08:45:06.194Z",
    "updated_at": "2016-05-06T08:45:06.194Z",
    "campus": []
  },
  {
    "id": 2,
    "url": "http://burning.endpoint.io",
    "description": "Another endpoint",
    "created_at": "2016-05-06T08:45:06.194Z",
    "updated_at": "2016-05-06T08:45:06.194Z",
    "campus": []
  },
  {
    "id": 3,
    "url": "https://intra.42.jp",
    "description": "The tokyo endpoint",
    "created_at": "2016-05-06T08:45:06.194Z",
    "updated_at": "2016-05-06T08:49:40.574Z",
    "campus": [
      {
        "id": 9,
        "name": "Tokyo",
        "time_zone": "Asia/Tokyo",
        "language": {
          "id": 2,
          "name": "English",
          "identifier": "en",
          "created_at": "2015-04-14T16:07:38.122Z",
          "updated_at": "2015-04-14T16:07:38.122Z"
        },
        "users_count": 1
      }
    ]
  }
]
```

### `GET /v2/endpoints/3` — HTTP 200

```json
{
  "id": 3,
  "url": "https://intra.42.jp",
  "description": "The tokyo endpoint",
  "created_at": "2016-05-06T08:45:06.194Z",
  "updated_at": "2016-05-06T08:49:40.574Z",
  "campus": [
    {
      "id": 9,
      "name": "Tokyo",
      "time_zone": "Asia/Tokyo",
      "language": {
        "id": 2,
        "name": "English",
        "identifier": "en",
        "created_at": "2015-04-14T16:07:38.122Z",
        "updated_at": "2015-04-14T16:07:38.122Z"
      },
      "users_count": 1
    }
  ]
}
```


## events

### `POST /v2/events`

```
  "event": {
    "begin_at": "2017-11-25 13:43:10 UTC",
    "campus_ids": [
      "1"
    ],
    "cursus_ids": [
      "1"
    ],
    "events_themes_attributes": [
      {
        "theme_id": 11
      },
      {
        "theme_attributes": {
          "name": "My awesome new theme"
        }
      },
      {
        "theme_attributes": {
          "name": "My awesome new theme 2"
        }
      }
    ],
    "activate_waitlist": "true",
    "description": "A fucking great event",
    "end_at": "2017-11-29 13:43:10 UTC",
    "kind": "workshop",
    "location": "Holodeck",
    "max_people": "120",
    "prohibition_of_cancellation": 10,
    "name": "Rainbowcat festival 🌈"
  }
}
201
{
  "id": 5,
  "name": "Rainbowcat festival 🌈",
  "description": "A fucking great event",
  "location": "Holodeck",
  "kind": "workshop",
  "max_people": 120,
  "nbr_subscribers": 0,
  "begin_at": "2017-11-25T13:43:10.000Z",
  "end_at": "2017-11-29T13:43:10.000Z",
  "campus_ids": [
    1
  ],
  "cursus_ids": [
    1
  ],
  "themes": [
    {
      "created_at": "2018-10-21T16:35:38.782Z",
      "id": 11,
      "name": "Security",
      "updated_at": "2018-10-21T16:35:38.782Z"
    },
    {
      "created_at": "2019-01-14T15:06:56.968Z",
      "id": 42,
      "name": "My awesome new theme",
      "updated_at": "2019-01-14T15:06:56.968Z"
    },
    {
      "created_at": "2019-01-14T15:06:56.968Z",
      "id": 43,
      "name": "My awesome new theme 2",
      "updated_at": "2019-01-14T15:06:56.968Z"
    }
  ],
  "waitlist": {
    "created_at": "2019-01-14T16:20:43.412Z",
    "id": 389,
    "updated_at": "2019-01-14T16:20:43.412Z",
    "waitlistable_id": 5,
    "waitlistable_type": "Event"
  },
  "prohibition_of_cancellation": 10,
  "created_at": "2017-11-22T13:43:37.609Z",
  "updated_at": "2017-11-22T13:43:37.633Z"
}
```

### `DELETE /v2/events/3` — HTTP 204

```
(no body)
```

### `GET /v2/events/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 4
}
```

### `GET /v2/events` — HTTP 200

```json
[
  {
    "id": 4,
    "name": "Oklahoma whales",
    "description": "Et selfies beard williamsburg quisquam ramps. Molestiae craft beer consectetur asperiores dolor. Small batch placeat banjo vhs mollitia aut vero. Distinctio est readymade offal tote bag +1.",
    "location": "West Wisozk",
    "kind": "rush",
    "max_people": 112,
    "nbr_subscribers": 0,
    "begin_at": "2017-11-25T13:42:10.090Z",
    "end_at": "2017-11-25T15:42:10.090Z",
    "campus_ids": [
      3
    ],
    "cursus_ids": [
      1
    ],
    "themes": [
      {
        "created_at": "2019-01-09T17:18:54.779Z",
        "id": 36,
        "name": "AI",
        "updated_at": "2019-01-09T17:18:54.779Z"
      },
      {
        "created_at": "2019-01-09T17:18:54.819Z",
        "id": 37,
        "name": "Entrepreneurship",
        "updated_at": "2019-01-09T17:18:54.819Z"
      }
    ],
    "waitlist": null,
    "prohibition_of_cancellation": 15,
    "created_at": "2017-11-22T13:42:10.110Z",
    "updated_at": "2017-11-22T13:42:10.127Z"
  },
  {
    "id": 3,
    "name": "Wyoming cattle",
    "description": "Accusantium lumbersexual pug minima you probably haven't heard of them. Dolore officiis kitsch lumbersexual temporibus twee church-key. Ramps molestiae ut esse squid. Molestiae delectus est optio. Biodiesel roof maiores iphone nobis.",
    "location": "Southern Bauch",
    "kind": "other",
    "max_people": 39,
    "nbr_subscribers": 0,
    "begin_at": "2017-11-24T13:42:10.014Z",
    "end_at": "2017-11-24T15:42:10.015Z",
    "campus_ids": [
      6
    ],
    "cursus_ids": [
      1
    ],
    "themes": [
      {
        "created_at": "2019-01-09T17:18:54.779Z",
        "id": 10,
        "name": "Meeting",
        "updated_at": "2019-01-09T17:18:54.779Z"
      },
      {
        "created_at": "2019-01-09T17:18:54.819Z",
        "id": 15,
        "name": "Association",
        "updated_at": "2019-01-09T17:18:54.819Z"
      }
    ],
    "waitlist": {
      "created_at": "2019-01-14T16:25:05.941Z",
      "id": 392,
      "updated_at": "2019-01-14T16:25:05.941Z",
      "waitlistable_id": 3,
      "waitlistable_type": "Event"
    },
    "prohibition_of_cancellation": 2,
    "created_at": "2017-11-22T13:42:10.037Z",
    "updated_at": "2017-11-22T13:42:10.082Z"
  },
  {
    "id": 2,
    "name": "Nevada sheep",
    "description": "Et tousled small batch street voluptas +1. Nisi small batch shoreditch est bicycle rights similique sed. Pbr&b sit exercitationem etsy ea. Cumque et forage reprehenderit officia quas. Chartreuse ad tacos commodi.",
    "location": "South Wisconsin Academy",
    "kind": "association",
    "max_people": 94,
    "nbr_subscribers": 0,
    "begin_at": "2017-11-23T13:42:09.970Z",
    "end_at": "2017-11-23T15:42:09.970Z",
    "campus_ids": [
      4
    ],
    "cursus_ids": [
      1
    ],
    "themes": [
      {
        "created_at": "2019-01-09T17:18:54.779Z",
        "id": 12,
        "name": "Security",
        "updated_at": "2019-01-09T17:18:54.779Z"
      },
      {
        "created_at": "2019-01-09T17:18:54.819Z",
        "id": 42,
        "name": "Recrutement",
        "updated_at": "2019-01-09T17:18:54.819Z"
      }
    ],
    "waitlist": {
      "created_at": "2019-01-14T16:25:05.941Z",
      "id": 33,
      "updated_at": "2019-01-14T16:25:05.941Z",
      "waitlistable_id": 2,
      "waitlistable_type": "Event"
    },
    "prohibition_of_cancellation": 10,
    "created_at": "2017-11-22T13:42:09.991Z",
    "updated_at": "2017-11-22T13:42:10.009Z"
  }
]
```

### `GET /v2/events/3` — HTTP 200

```json
{
  "id": 3,
  "name": "Wyoming cattle",
  "description": "Accusantium lumbersexual pug minima you probably haven't heard of them. Dolore officiis kitsch lumbersexual temporibus twee church-key. Ramps molestiae ut esse squid. Molestiae delectus est optio. Biodiesel roof maiores iphone nobis.",
  "location": "Southern Bauch",
  "kind": "other",
  "max_people": 39,
  "nbr_subscribers": 0,
  "begin_at": "2017-11-24T13:42:10.014Z",
  "end_at": "2017-11-24T15:42:10.015Z",
  "campus_ids": [
    6
  ],
  "cursus_ids": [
    1
  ],
  "themes": [
    {
      "created_at": "2019-01-09T17:18:54.779Z",
      "id": 36,
      "name": "AI",
      "updated_at": "2019-01-09T17:18:54.779Z"
    },
    {
      "created_at": "2019-01-09T17:18:54.819Z",
      "id": 37,
      "name": "Entrepreneurship",
      "updated_at": "2019-01-09T17:18:54.819Z"
    }
  ],
  "waitlist": {
    "created_at": "2019-01-14T16:25:05.941Z",
    "id": 391,
    "updated_at": "2019-01-14T16:25:05.941Z",
    "waitlistable_id": 3,
    "waitlistable_type": "Event"
  },
  "prohibition_of_cancellation": 10,
  "created_at": "2017-11-22T13:42:10.037Z",
  "updated_at": "2017-11-22T13:42:10.082Z"
}
```

### `PUT /v2/events/3`

```
  "event": {
    "begin_at": "2017-11-25 13:43:10 UTC",
    "campus_ids": [
      "1"
    ],
    "cursus_ids": [
      "1"
    ],
    "events_themes_attributes": [
      {
        "theme_attributes": {
          "name": "Association"
        }
      },
      {
        "id": 58,
        "_destroy": "true"
      }
    ],
    "description": "A fucking great event",
    "end_at": "2017-11-29 13:43:10 UTC",
    "kind": "workshop",
    "location": "Holodeck",
    "max_people": "120",
    "prohibition_of_cancellation": 10,
    "name": "Rainbowcat festival 🌈"
  }
}
204
```


## exams

### `POST /v2/exams`

```
  "exam": {
    "begin_at": "2015-07-17T15:00:00.000Z",
    "campus_id": 1,
    "end_at": "2015-07-17T19:00:00.000Z",
    "ip_range": "10.11.0.0/16,10.12.0.0/16,10.13.0.0/16,10.42.0.0/16",
    "location": "e1,e2,e3",
    "max_people": 780,
    "name": "Piscine C - Exam 01",
    "project_ids": [
      405
    ],
    "visible": "true",
    "activate_waitlist": "false"
  }
}
201
{
  "id": 42,
  "ip_range": "10.11.0.0/16,10.12.0.0/16,10.13.0.0/16,10.42.0.0/16",
  "begin_at": "2015-07-17T15:00:00.000Z",
  "end_at": "2015-07-17T19:00:00.000Z",
  "location": "e1,e2,e3",
  "max_people": 780,
  "nbr_subscribers": 594,
  "name": "Piscine C - Exam 01",
  "created_at": "2015-07-15T13:05:26.006Z",
  "updated_at": "2018-08-27T16:56:15.032Z",
  "campus": {
    "id": 1,
    "name": "Paris",
    "time_zone": "Europe/Paris",
    "language": {
      "id": 1,
      "name": "Français",
      "identifier": "fr",
      "created_at": "2014-11-02T16:43:38.466Z",
      "updated_at": "2021-10-08T16:28:44.040Z"
    },
    "users_count": 22319,
    "vogsphere_id": 1,
    "country": "France",
    "address": "96, boulevard Bessières",
    "zip": "75017",
    "city": "Paris",
    "website": "http://www.42.fr/",
    "facebook": "https://facebook.com/42born2code",
    "twitter": "https://twitter.com/42born2code",
    "active": true,
    "email_extension": "42.fr",
    "default_hidden_phone": false
  },
  "cursus": [
    {
      "id": 4,
      "created_at": "2015-05-01T17:46:08.433Z",
      "name": "Piscine C",
      "slug": "piscine-c"
    },
    {
      "id": 6,
      "created_at": "2015-09-21T12:36:09.128Z",
      "name": "Piscine C décloisonnée",
      "slug": "piscine-c-decloisonnee"
    },
    {
      "id": 13,
      "created_at": "2017-02-01T14:25:42.300Z",
      "name": "42 Labs",
      "slug": "42-labs"
    }
  ],
  "projects": [
    {
      "id": 405,
      "name": "Exam01",
      "slug": "piscine-c-exam01",
      "parent": null,
      "children": [],
      "attachments": [],
      "created_at": "2015-06-29T13:14:31.702Z",
      "updated_at": "2021-09-01T08:35:01.074Z",
      "exam": true,
      "git_id": null,
      "repository": null
    }
  ]
}
```

### `DELETE /v2/exams/1` — HTTP 204

```
(no body)
```

### `GET /v2/exams/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 2
}
```

### `GET /v2/exams` — HTTP 200

```json
[
  {
    "id": 42,
    "ip_range": "10.11.0.0/16,10.12.0.0/16,10.13.0.0/16,10.42.0.0/16",
    "begin_at": "2015-07-17T15:00:00.000Z",
    "end_at": "2015-07-17T19:00:00.000Z",
    "location": "e1, e2, e3",
    "max_people": 780,
    "nbr_subscribers": 594,
    "name": "Piscine C - Exam 01",
    "created_at": "2015-07-15T13:05:26.006Z",
    "updated_at": "2018-08-27T16:56:15.032Z",
    "campus": {
      "id": 1,
      "name": "Paris",
      "time_zone": "Europe/Paris",
      "language": {
        "id": 1,
        "name": "Français",
        "identifier": "fr",
        "created_at": "2014-11-02T16:43:38.466Z",
        "updated_at": "2021-10-08T16:28:44.040Z"
      },
      "users_count": 22319,
      "vogsphere_id": 1,
      "country": "France",
      "address": "96, boulevard Bessières",
      "zip": "75017",
      "city": "Paris",
      "website": "http://www.42.fr/",
      "facebook": "https://facebook.com/42born2code",
      "twitter": "https://twitter.com/42born2code",
      "active": true,
      "email_extension": "42.fr",
      "default_hidden_phone": false
    },
    "cursus": [
      {
        "id": 4,
        "created_at": "2015-05-01T17:46:08.433Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      },
      {
        "id": 6,
        "created_at": "2015-09-21T12:36:09.128Z",
        "name": "Piscine C décloisonnée",
        "slug": "piscine-c-decloisonnee"
      },
      {
        "id": 13,
        "created_at": "2017-02-01T14:25:42.300Z",
        "name": "42 Labs",
        "slug": "42-labs"
      }
    ],
    "projects": [
      {
        "id": 405,
        "name": "Exam01",
        "slug": "piscine-c-exam01",
        "parent": null,
        "children": [],
        "attachments": [],
        "created_at": "2015-06-29T13:14:31.702Z",
        "updated_at": "2021-09-01T08:35:01.074Z",
        "exam": true,
        "git_id": null,
        "repository": null
      }
    ]
  }
]
```

### `GET /v2/exams/1` — HTTP 200

```json
{
  "id": 42,
  "ip_range": "10.11.0.0/16,10.12.0.0/16,10.13.0.0/16,10.42.0.0/16",
  "begin_at": "2015-07-17T15:00:00.000Z",
  "end_at": "2015-07-17T19:00:00.000Z",
  "location": "e1,e2,e3",
  "max_people": 780,
  "nbr_subscribers": 594,
  "name": "Piscine C - Exam 01",
  "created_at": "2015-07-15T13:05:26.006Z",
  "updated_at": "2018-08-27T16:56:15.032Z",
  "campus": {
    "id": 1,
    "name": "Paris",
    "time_zone": "Europe/Paris",
    "language": {
      "id": 1,
      "name": "Français",
      "identifier": "fr",
      "created_at": "2014-11-02T16:43:38.466Z",
      "updated_at": "2021-10-08T16:28:44.040Z"
    },
    "users_count": 22319,
    "vogsphere_id": 1,
    "country": "France",
    "address": "96, boulevard Bessières",
    "zip": "75017",
    "city": "Paris",
    "website": "http://www.42.fr/",
    "facebook": "https://facebook.com/42born2code",
    "twitter": "https://twitter.com/42born2code",
    "active": true,
    "email_extension": "42.fr",
    "default_hidden_phone": false
  },
  "cursus": [
    {
      "id": 4,
      "created_at": "2015-05-01T17:46:08.433Z",
      "name": "Piscine C",
      "slug": "piscine-c"
    },
    {
      "id": 6,
      "created_at": "2015-09-21T12:36:09.128Z",
      "name": "Piscine C décloisonnée",
      "slug": "piscine-c-decloisonnee"
    },
    {
      "id": 13,
      "created_at": "2017-02-01T14:25:42.300Z",
      "name": "42 Labs",
      "slug": "42-labs"
    }
  ],
  "projects": [
    {
      "id": 405,
      "name": "Exam01",
      "slug": "piscine-c-exam01",
      "parent": null,
      "children": [],
      "attachments": [],
      "created_at": "2015-06-29T13:14:31.702Z",
      "updated_at": "2021-09-01T08:35:01.074Z",
      "exam": true,
      "git_id": null,
      "repository": null
    }
  ]
}
```

### `PUT /v2/exams/1`

```
  "exam": {
    "begin_at": "2017-11-25 13:43:10 UTC",
    "campus_ids": 4,
    "end_at": "2017-11-29 13:43:10 UTC",
    "ip_range": "10.20.0.0/16",
    "location": "Cluj",
    "max_people": 70,
    "name": "Rainbowcat Exam 🌈",
    "activate_waitlist": "true",
    "project_ids": [
      "3"
    ],
    "visible": "true"
  }
}
204
```


## expertises

### `POST /v2/expertises`

```
  "expertise": {
    "kind": "databases",
    "name": "West Virginia frogs"
  }
}
201
{
  "id": 11,
  "name": "West Virginia frogs",
  "slug": "west-virginia-frogs",
  "url": "https://api.intra.42.fr/v2/expertises/west-virginia-frogs",
  "kind": "databases",
  "created_at": "2017-11-22T13:43:39.345Z",
  "expertises_users_url": "https://api.intra.42.fr/v2/expertises/west-virginia-frogs/expertises_users"
}
```

### `DELETE /v2/expertises/3` — HTTP 204

```
(no body)
```

### `GET /v2/expertises` — HTTP 200

```json
[
  {
    "id": 10,
    "name": "Magic",
    "slug": "magic",
    "url": "https://api.intra.42.fr/v2/expertises/magic",
    "kind": "languages",
    "created_at": "2017-11-22T13:41:01.825Z",
    "expertises_users_url": "https://api.intra.42.fr/v2/expertises/magic/expertises_users"
  },
  {
    "id": 9,
    "name": "Elixir",
    "slug": "elixir",
    "url": "https://api.intra.42.fr/v2/expertises/elixir",
    "kind": "languages",
    "created_at": "2017-11-22T13:41:01.819Z",
    "expertises_users_url": "https://api.intra.42.fr/v2/expertises/elixir/expertises_users"
  },
  {
    "id": 8,
    "name": "iOS",
    "slug": "ios",
    "url": "https://api.intra.42.fr/v2/expertises/ios",
    "kind": "frameworks",
    "created_at": "2017-11-22T13:41:01.814Z",
    "expertises_users_url": "https://api.intra.42.fr/v2/expertises/ios/expertises_users"
  }
]
```

### `GET /v2/expertises/3` — HTTP 200

```json
{
  "id": 3,
  "name": "Android",
  "slug": "android",
  "url": "https://api.intra.42.fr/v2/expertises/android",
  "kind": "frameworks",
  "created_at": "2017-11-22T13:41:01.785Z",
  "expertises_users_url": "https://api.intra.42.fr/v2/expertises/android/expertises_users"
}
```

### `PUT /v2/expertises/3`

```
  "expertise": {
    "kind": "databases",
    "name": "South Dakota frogs"
  }
}
204
```


## expertises_users

### `POST /v2/expertises_users`

```
  "expertises_user": {
    "expertise_id": "2",
    "user_id": "106",
    "value": "1"
  }
}
201
{
  "id": 127,
  "expertise_id": 2,
  "interested": false,
  "value": 1,
  "contact_me": false,
  "created_at": "2017-11-22T13:43:39.996Z",
  "user_id": 106,
  "expertise": {
    "id": 2,
    "name": "jQuery",
    "slug": "jquery",
    "url": "https://api.intra.42.fr/v2/expertises/jquery",
    "kind": "other",
    "created_at": "2017-11-22T13:41:01.779Z",
    "expertises_users_url": "https://api.intra.42.fr/v2/expertises/jquery/expertises_users"
  },
  "user": {
    "id": 106,
    "login": "anaskywa",
    "url": "https://api.intra.42.fr/v2/users/anaskywa"
  }
}
```

### `DELETE /v2/expertises_users/3` — HTTP 204

```
(no body)
```

### `GET /v2/expertises_users` — HTTP 200

```json
[
  {
    "id": 126,
    "expertise_id": 6,
    "interested": false,
    "value": 2,
    "contact_me": false,
    "created_at": "2017-11-22T13:41:23.630Z",
    "user_id": 126,
    "expertise": {
      "id": 6,
      "name": "AngularJS",
      "slug": "angularjs",
      "url": "https://api.intra.42.fr/v2/expertises/angularjs",
      "kind": "frameworks",
      "created_at": "2017-11-22T13:41:01.803Z",
      "expertises_users_url": "https://api.intra.42.fr/v2/expertises/angularjs/expertises_users"
    },
    "user": {
      "id": 126,
      "login": "darthcae",
      "url": "https://api.intra.42.fr/v2/users/darthcae"
    }
  },
  {
    "id": 125,
    "expertise_id": 4,
    "interested": false,
    "value": 2,
    "contact_me": false,
    "created_at": "2017-11-22T13:41:23.614Z",
    "user_id": 125,
    "expertise": {
      "id": 4,
      "name": "C",
      "slug": "c",
      "url": "https://api.intra.42.fr/v2/expertises/c",
      "kind": "languages",
      "created_at": "2017-11-22T13:41:01.791Z",
      "expertises_users_url": "https://api.intra.42.fr/v2/expertises/c/expertises_users"
    },
    "user": {
      "id": 125,
      "login": "sebulseb",
      "url": "https://api.intra.42.fr/v2/users/sebulseb"
    }
  },
  {
    "id": 124,
    "expertise_id": 1,
    "interested": false,
    "value": 2,
    "contact_me": false,
    "created_at": "2017-11-22T13:41:23.598Z",
    "user_id": 124,
    "expertise": {
      "id": 1,
      "name": ".NET",
      "slug": "net",
      "url": "https://api.intra.42.fr/v2/expertises/net",
      "kind": "languages",
      "created_at": "2017-11-22T13:41:01.773Z",
      "expertises_users_url": "https://api.intra.42.fr/v2/expertises/net/expertises_users"
    },
    "user": {
      "id": 124,
      "login": "hsolo2",
      "url": "https://api.intra.42.fr/v2/users/hsolo2"
    }
  }
]
```

### `GET /v2/expertises_users/3` — HTTP 200

```json
{
  "id": 3,
  "expertise_id": 6,
  "interested": false,
  "value": 2,
  "contact_me": false,
  "created_at": "2017-11-22T13:41:22.512Z",
  "user_id": 3,
  "expertise": {
    "id": 6,
    "name": "AngularJS",
    "slug": "angularjs",
    "url": "https://api.intra.42.fr/v2/expertises/angularjs",
    "kind": "frameworks",
    "created_at": "2017-11-22T13:41:01.803Z",
    "expertises_users_url": "https://api.intra.42.fr/v2/expertises/angularjs/expertises_users"
  },
  "user": {
    "id": 3,
    "login": "gargamel",
    "url": "https://api.intra.42.fr/v2/users/gargamel"
  }
}
```

### `PUT /v2/expertises_users/3`

```
  "expertises_user": {
    "expertise_id": "6",
    "user_id": "125",
    "value": "1"
  }
}
204
```


## flash_users

### `POST /v2/flashes`

```
  "flash_user": {
    "flash_id": 1,
    "user_id": 19265,
    "end_at": "2018-07-01T18:40:57.031Z"
  }
}
201
{
  "id": 166513,
  "flash_id": 1,
  "seen": false,
  "end_at": "2018-07-01T18:40:57.031Z",
  "user": {
    "id": 19265,
    "login": "jgengo",
    "url": "http://localhost:13000/v2/users/jgengo"
  }
}
```

### `GET /v2/flash_users?page=1`

```json
[
  {
    "id": 28,
    "flash_id": 2,
    "seen": true,
    "end_at": "2016-06-13T18:40:57.031Z",
    "user": {
      "id": 10292,
      "login": "mguilbau",
      "url": "http://localhost:13000/v2/users/mguilbau"
    }
  },
  {
    "id": 29,
    "flash_id": 2,
    "seen": true,
    "end_at": "2016-06-13T18:40:57.031Z",
    "user": {
      "id": 10316,
      "login": "spuyet",
      "url": "http://localhost:13000/v2/users/spuyet"
    }
  },
  {
    "id": 30,
    "flash_id": 2,
    "seen": true,
    "end_at": "2016-06-13T18:40:57.031Z",
    "user": {
      "id": 10317,
      "login": "evoisin",
      "url": "http://localhost:13000/v2/users/evoisin"
    }
  }
]
```

### `GET /v2/flash_users/28` — HTTP 200

```json
{
  "id": 28,
  "flash_id": 2,
  "seen": true,
  "end_at": "2016-06-13T18:40:57.031Z",
  "user": {
    "id": 10292,
    "login": "mguilbau",
    "url": "http://localhost:13000/v2/users/mguilbau"
  }
}
```


## flashes

### `POST /v2/flashes`

```
  "flash": {
    "title": "Almost the end!",
    "content": "One of our member is leaving us in few days...",
    "identifier": "the_end",
    "duration": 4200
  }
}
201
{
  "id": 53,
  "title": "Almost the end!",
  "content": "One of our member is leaving us in few days...",
  "identifier": "the_end",
  "duration": 4200
}
```

### `GET /v2/flashes?page=1`

```json
[
  {
    "id": 24,
    "title": "Achievement unlocked !",
    "content": "<div class='achievement-modal'>\n<img class='achievement-modal--image' src='https://admin.intrav2.42.fr/uploads/achievement/image/83/PED010.svg' alt='achievement logo'/>\n        <div class='achievement-modal--content'>\n          <h3 class='achievement-modal--title'>Serial examiner</h3>\n          <p class='achievement-modal--desc'>Effectuer 10 soutenances en une journée en tant que correcteur.</p>\n</div>\n</div>\n",
    "identifier": "achievement-83",
    "duration": 4320,
    "selector": ""
  },
  {
    "id": 25,
    "title": "Achievement unlocked !",
    "content": "<div class='achievement-modal'>\n<img class='achievement-modal--image' src='https://admin.intrav2.42.fr/uploads/achievement/image/83/PED010.svg' alt='achievement logo'/>\n        <div class='achievement-modal--content'>\n          <h3 class='achievement-modal--title'>Serial examiner</h3>\n          <p class='achievement-modal--desc'>Effectuer 10 soutenances en une journée en tant que correcteur.</p>\n</div>\n</div>\n",
    "identifier": "achievement-84",
    "duration": 4320,
    "selector": ""
  },
  {
    "id": 26,
    "title": "Achievement unlocked !",
    "content": "<div class='achievement-modal'>\n<img class='achievement-modal--image' src='https://admin.intrav2.42.fr/uploads/achievement/image/83/PED010.svg' alt='achievement logo'/>\n        <div class='achievement-modal--content'>\n          <h3 class='achievement-modal--title'>Serial examiner</h3>\n          <p class='achievement-modal--desc'>Effectuer 10 soutenances en une journée en tant que correcteur.</p>\n</div>\n</div>\n",
    "identifier": "achievement-85",
    "duration": 4320,
    "selector": ""
  }
]
```

### `GET /v2/flashes/27` — HTTP 200

```json
{
  "id": 27,
  "title": "Achievement unlocked !",
  "content": "<div class='achievement-modal'>\n<img class='achievement-modal--image' src='https://admin.intrav2.42.fr/uploads/achievement/image/83/PED010.svg' alt='achievement logo'/>\n        <div class='achievement-modal--content'>\n          <h3 class='achievement-modal--title'>Serial examiner</h3>\n          <p class='achievement-modal--desc'>Effectuer 10 soutenances en une journée en tant que correcteur.</p>\n</div>\n</div>\n",
  "identifier": "achievement-83",
  "duration": 4320,
  "selector": ""
}
```


## groups

### `POST /v2/groups`

```
  "group": {
    "color": "#ed5462",
    "kind": "important",
    "name": "tigers"
  }
}
201
{
  "id": 5,
  "name": "tigers"
}
```

### `DELETE /v2/groups/1` — HTTP 204

```
(no body)
```

### `GET /v2/groups` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "gnomes"
  },
  {
    "id": 2,
    "name": "vampires"
  },
  {
    "id": 3,
    "name": "sons"
  }
]
```

### `GET /v2/groups/1` — HTTP 200

```json
{
  "id": 1,
  "name": "gnomes"
}
```

### `PUT /v2/groups/1`

```
  "group": {
    "color": "#ed5462",
    "kind": "important",
    "name": "tigers"
  }
}
204
```


## groups_users

### `POST /v2/groups_users`

```
  "groups_user": {
    "group_id": "3",
    "user_id": "9"
  }
}
201
{
  "id": 5,
  "user_id": 9,
  "group_id": 3,
  "created_at": "2017-11-22T13:43:41.210Z",
  "updated_at": "2017-11-22T13:43:41.210Z"
}
```

### `DELETE /v2/groups_users/4` — HTTP 204

```
(no body)
```

### `GET /v2/groups_users` — HTTP 200

```json
[
  {
    "id": 1,
    "user_id": 33,
    "group_id": 1,
    "created_at": "2017-11-22T13:42:12.972Z",
    "updated_at": "2017-11-22T13:42:12.972Z"
  },
  {
    "id": 2,
    "user_id": 119,
    "group_id": 2,
    "created_at": "2017-11-22T13:42:12.992Z",
    "updated_at": "2017-11-22T13:42:12.992Z"
  },
  {
    "id": 3,
    "user_id": 44,
    "group_id": 3,
    "created_at": "2017-11-22T13:42:13.010Z",
    "updated_at": "2017-11-22T13:42:13.010Z"
  }
]
```

### `GET /v2/groups_users/4` — HTTP 200

```json
{
  "id": 4,
  "user_id": 101,
  "group_id": 4,
  "created_at": "2017-11-22T13:42:13.028Z",
  "updated_at": "2017-11-22T13:42:13.028Z"
}
```

### `PUT /v2/groups_users/4`

```
  "groups_user": {
    "group_id": "1",
    "user_id": "97"
  }
}
204
```


## internships

### `GET /v2/internships/2350` — HTTP 200

```json
{
  "id": 2350,
  "administration_id": 1,
  "offer_id": null,
  "language_id": 1,
  "state": "uploaded",
  "days": "[\"monday\",\"tuesday\",\"wednesday\",\"thursday\",\"friday\"]",
  "user_address": "5 rue de la paix",
  "user_postal": "75001",
  "user_city": "Paris",
  "user_country": "France",
  "company_name": "Association 42",
  "company_boss_user_first_name": "FirstName",
  "company_boss_user_last_name": "LastName",
  "company_boss_user_email": "[email protected]",
  "company_boss_user_phone": "0123456789",
  "company_user_first_name": "Quentin",
  "company_user_last_name": "Bollache",
  "company_user_post": "Responsable technique et pedagogique",
  "company_user_email": "[email protected]",
  "company_user_phone": "0123456789",
  "company_address": "96 Boulevard Bessières",
  "company_postal": "75017",
  "company_city": "Paris",
  "company_country": "France",
  "company_siret": "0",
  "internship_address": "96 Boulevard Bessières",
  "internship_postal": "75017",
  "internship_city": "Paris",
  "internship_country": "France",
  "contract_type": "stage",
  "subject": "Développement de tous les sites web reliés à 42",
  "start_at": "2017-07-31T22:00:00.000Z",
  "end_at": "2018-01-30T23:00:00.000Z",
  "duration": 6,
  "nb_days": 5,
  "nb_hours": 35,
  "movement": null,
  "salary": 50000,
  "currency": "eur",
  "breach_at": null,
  "convention": {
    "convention": {
      "url": "/uploads/internship/convention/jgengo-9543c17018c04a7f99fd01bf62a478/2350/jgengo.zip"
    }
  },
  "user": {
    "id": 19265,
    "login": "jgengo",
    "url": "http://localhost:13000/v2/users/jgengo"
  }
}
```


## journals

### `GET /v2/campus/1/journals`

```
  "begin_at": "2021-12-15",
  "end_at": "2021-12-16"
}
200
[
  {
    "id": 5276532,
    "user_id": 69936,
    "cursus_id": 9,
    "campus_id": 1,
    "item_type": "Internship",
    "item_id": 11547,
    "reason": "Currently doing internship",
    "created_at": "2021-10-16T01:01:34.979Z",
    "updated_at": "2021-10-16T01:01:34.979Z",
    "event_at": "2021-10-15T01:01:31.450Z"
  },
  {
    "id": 5178542,
    "user_id": 69937,
    "item_type": "User",
    "item_id": 11547,
    "cursus_id": 9,
    "campus_id": 1,
    "reason": "Used intranet",
    "created_at": "2021-10-16T05:15:15.874Z",
    "updated_at": "2021-10-16T05:15:15.874Z",
    "event_at": "2021-10-15T05:14:13.644Z"
  },
  {
    "id": 42424242,
    "user_id": 69936,
    "item_type": "ScaleTeam",
    "item_id": 11547,
    "cursus_id": 9,
    "campus_id": 1,
    "reason": "Was evaluated by someone",
    "created_at": "2021-10-17T05:15:25.874Z",
    "updated_at": "2021-10-17T05:15:25.874Z",
    "event_at": "2021-10-16T05:02:45.644Z"
  }
]
```


## languages

### `GET /v2/languages` — HTTP 200

```json
[
  {
    "id": 3,
    "name": "Romanian",
    "identifier": "ro"
  },
  {
    "id": 2,
    "name": "English",
    "identifier": "en"
  },
  {
    "id": 1,
    "name": "Français",
    "identifier": "fr"
  }
]
```

### `GET /v2/languages/3` — HTTP 200

```json
{
  "id": 3,
  "name": "Romanian",
  "identifier": "ro"
}
```


## languages_users

### `POST /v2/languages_users`

```
  "languages_user": {
    "language_id": "3",
    "position": "1",
    "user_id": "7"
  }
}
201
{
  "id": 127,
  "language_id": 3,
  "user_id": 7,
  "position": 1,
  "created_at": "2017-11-22T13:43:42.355Z"
}
```

### `DELETE /v2/languages_users/70` — HTTP 204

```
(no body)
```

### `GET /v2/languages_users/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 126
}
```

### `GET /v2/languages_users` — HTTP 200

```json
[
  {
    "id": 126,
    "language_id": 3,
    "user_id": 126,
    "position": 1,
    "created_at": "2017-11-22T13:41:20.168Z"
  },
  {
    "id": 125,
    "language_id": 2,
    "user_id": 125,
    "position": 1,
    "created_at": "2017-11-22T13:41:20.041Z"
  },
  {
    "id": 124,
    "language_id": 3,
    "user_id": 124,
    "position": 1,
    "created_at": "2017-11-22T13:41:19.915Z"
  }
]
```

### `GET /v2/languages_users/70` — HTTP 200

```json
{
  "id": 70,
  "language_id": 2,
  "user_id": 70,
  "position": 1,
  "created_at": "2017-11-22T13:41:12.367Z"
}
```

### `PUT /v2/languages_users/70`

```
  "languages_user": {
    "language_id": "3",
    "position": "1",
    "user_id": "7"
  }
}
204
```


## locations

### `POST /v2/locations`

```
  "location": {
    "begin_at": "2017-11-22 11:43:10 UTC",
    "campus_id": "2",
    "host": "burrito",
    "user_id": "56"
  }
}
201
{
  "id": 16,
  "begin_at": "2017-11-22T11:43:10.000Z",
  "end_at": null,
  "primary": true,
  "floor": null,
  "row": null,
  "post": null,
  "host": "burrito",
  "campus_id": 2,
  "user": {
    "id": 56,
    "login": "pdameron",
    "url": "https://api.intra.42.fr/v2/users/pdameron"
  }
}
```

### `DELETE /v2/locations/4` — HTTP 204

```
(no body)
```

### `GET /v2/locations/graph/on/begin_at/by/day` — HTTP 200

```json
{
  "2017-11-13": 1,
  "2017-11-14": 1,
  "2017-11-15": 1,
  "2017-11-16": 1,
  "2017-11-17": 1,
  "2017-11-18": 2,
  "2017-11-19": 2,
  "2017-11-20": 2,
  "2017-11-21": 2,
  "2017-11-22": 2
}
```

### `GET /v2/locations` — HTTP 200

```json
[
  {
    "id": 6,
    "begin_at": "2017-11-22T13:42:10.248Z",
    "end_at": "2017-11-22T13:42:10.248Z",
    "primary": true,
    "floor": null,
    "row": null,
    "post": null,
    "host": "ariel",
    "campus_id": 1,
    "user": {
      "id": 120,
      "login": "obkenobi",
      "url": "https://api.intra.42.fr/v2/users/obkenobi"
    }
  },
  {
    "id": 1,
    "begin_at": "2017-11-22T13:42:09.406Z",
    "end_at": "2017-11-22T13:42:09.406Z",
    "primary": true,
    "floor": null,
    "row": null,
    "post": null,
    "host": "puck",
    "campus_id": 1,
    "user": {
      "id": 73,
      "login": "padmamid",
      "url": "https://api.intra.42.fr/v2/users/padmamid"
    }
  },
  {
    "id": 7,
    "begin_at": "2017-11-21T13:42:10.737Z",
    "end_at": "2017-11-21T14:42:10.737Z",
    "primary": true,
    "floor": null,
    "row": null,
    "post": null,
    "host": "ganymede",
    "campus_id": 1,
    "user": {
      "id": 53,
      "login": "dvader",
      "url": "https://api.intra.42.fr/v2/users/dvader"
    }
  }
]
```

### `GET /v2/locations/4` — HTTP 200

```json
{
  "id": 4,
  "begin_at": "2017-11-19T13:42:09.511Z",
  "end_at": "2017-11-19T16:42:09.511Z",
  "primary": true,
  "floor": null,
  "row": null,
  "post": null,
  "host": "oberon",
  "campus_id": 1,
  "user": {
    "id": 59,
    "login": "davader",
    "url": "https://api.intra.42.fr/v2/users/davader"
  }
}
```

### `PUT /v2/locations/4`

```
  "location": {
    "begin_at": "2017-11-22 11:43:10 UTC",
    "campus_id": "1",
    "host": "burrito",
    "user_id": "49"
  }
}
204
```


## mailings

### `POST /v2/mailings`

```
  "mailing": {
    "content": "Hi andre,\nYou just *won* the mego jackpot !\nCheck [this link](http://spam.prizepool-game-lottery.xxx/winner.php)",
    "from": "[email protected]",
    "identifier": "an_unique_identifier",
    "subject": "You are the super online contest winner !!!",
    "subtitle": "And it's kinda awesome",
    "title": "You won the big jackpot",
    "to": [
      "[email protected]"
    ]
  }
}
201
{
  "id": 11,
  "subject": "You are the super online contest winner !!!",
  "created_at": "2017-11-22T13:43:44.207Z",
  "updated_at": "2017-11-22T13:43:44.207Z",
  "identifier": "an_unique_identifier",
  "meta": {},
  "title": "You won the big jackpot",
  "subtitle": "And it's kinda awesome",
  "attachment": null,
  "from": "[email protected]",
  "to": [
    "[email protected]"
  ],
  "cc": null,
  "bcc": null,
  "content": "Hi andre,\nYou just *won* the mego jackpot !\nCheck [this link](http://spam.prizepool-game-lottery.xxx/winner.php)",
  "html_content": "<p>Hi andre,\nYou just <em>won</em> the mego jackpot !\nCheck <a href=\"http://spam.prizepool-game-lottery.xxx/winner.php\">this link</a></p>\n",
  "attachments": null
}
```

### `DELETE /v2/mailings/7` — HTTP 204

```
(no body)
```

### `GET /v2/mailings?page=1` — HTTP 200

```json
[
  {
    "id": 1725549,
    "subject": "Evaluation imminent",
    "created_at": "2016-04-28T12:30:10.116Z",
    "updated_at": "2016-04-28T12:30:10.116Z",
    "identifier": "imminent_correction_correctors",
    "meta": {
      "id": 268129,
      "date": "2016-04-28T14:45:00+02:00",
      "name": "Defense for ft_ls",
      "user": "Romain Baran",
      "other_user": "thifranc"
    },
    "title": "Evaluation imminent",
    "subtitle": null,
    "attachment": null,
    "from": "[email protected]",
    "to": [
      "[email protected]"
    ],
    "cc": [],
    "bcc": [],
    "content": "Hi,\nYou will review thifranc's code in 15 minutes!",
    "html_content": "<p>Hi,\nYou will review thifranc&#39;s code in 15 minutes!</p>\n",
    "attachments": null
  },
  {
    "id": 1725550,
    "subject": "Evaluation imminent",
    "created_at": "2016-04-28T12:30:11.252Z",
    "updated_at": "2016-04-28T12:30:11.252Z",
    "identifier": "imminent_correction_correcteds",
    "meta": {
      "id": 268140,
      "date": "2016-04-28T14:45:00+02:00",
      "name": "Defense for ft_traceroute",
      "user": "Jean Alexandre Bert",
      "other_user": "pnoyelle"
    },
    "title": "Evaluation imminent",
    "subtitle": null,
    "attachment": null,
    "from": "[email protected]",
    "to": [
      "[email protected]"
    ],
    "cc": [],
    "bcc": [],
    "content": "Hi,\nYour code will be reviewed by pnoyelle in 15 minutes!",
    "html_content": "<p>Hi,\nYour code will be reviewed by pnoyelle in 15 minutes!</p>\n",
    "attachments": null
  },
  {
    "id": 1725551,
    "subject": "Evaluation imminent",
    "created_at": "2016-04-28T12:30:11.292Z",
    "updated_at": "2016-04-28T12:30:11.292Z",
    "identifier": "imminent_correction_correctors",
    "meta": {
      "id": 268140,
      "date": "2016-04-28T14:45:00+02:00",
      "name": "Defense for ft_traceroute",
      "user": "Pierre Noyelle",
      "other_user": "jbert"
    },
    "title": "Evaluation imminent",
    "subtitle": null,
    "attachment": null,
    "from": "[email protected]",
    "to": [
      "[email protected]"
    ],
    "cc": [],
    "bcc": [],
    "content": "Hi,\nYou will review jbert's code in 15 minutes!",
    "html_content": "<p>Hi,\nYou will review jbert&#39;s code in 15 minutes!</p>\n",
    "attachments": null
  }
]
```

### `GET /v2/mailings/42` — HTTP 200

```json
{
  "id": 42,
  "subject": "Evaluation imminent",
  "created_at": "2016-04-28T12:30:10.116Z",
  "updated_at": "2016-04-28T12:30:10.116Z",
  "identifier": "imminent_correction_correctors",
  "meta": {
    "id": 268129,
    "date": "2016-04-28T14:45:00+02:00",
    "name": "Defense for ft_ls",
    "user": "Romain Baran",
    "other_user": "thifranc"
  },
  "title": "Evaluation imminent",
  "subtitle": null,
  "attachment": null,
  "from": "[email protected]",
  "to": [
    "[email protected]"
  ],
  "cc": [],
  "bcc": [],
  "content": "Hi,\nYou will review thifranc's code in 15 minutes!",
  "html_content": "<p>Hi,\nYou will review thifranc&#39;s code in 15 minutes!</p>\n",
  "attachments": null
}
```

### `GET /v2/mailings/7` — HTTP 200

```json
{
  "id": 7,
  "subject": "Judge me by my size, do you?",
  "created_at": "2017-11-22T13:42:11.054Z",
  "updated_at": "2017-11-22T13:42:11.054Z",
  "identifier": "spec-mail",
  "meta": {},
  "title": "I'll copy the wireless AGP pixel, that should interface the RSS application!",
  "subtitle": null,
  "attachment": null,
  "from": "[email protected]",
  "to": [
    "[email protected]"
  ],
  "cc": [],
  "bcc": [],
  "content": "Banh mi mixtape distillery gentrify post-ironic pour-over. Deep v fixie hella selfies irony direct trade paleo migas. Mumblecore kitsch hella selvage bicycle rights green juice. Keffiyeh salvia wolf vhs umami 90's. Cred lumbersexual chia hoodie pbr&b.\nSlow-carb sustainable cliche. Squid ennui kombucha yuccie biodiesel. Vhs cliche deep v mustache jean shorts trust fund fashion axe. Keffiyeh squid pbr&b fixie selvage.\nRoof blue bottle stumptown godard drinking yuccie. Craft beer artisan bushwick kale chips selvage. Kickstarter ethical asymmetrical franzen brooklyn etsy.",
  "html_content": "<p>Banh mi mixtape distillery gentrify post-ironic pour-over. Deep v fixie hella selfies irony direct trade paleo migas. Mumblecore kitsch hella selvage bicycle rights green juice. Keffiyeh salvia wolf vhs umami 90&#39;s. Cred lumbersexual chia hoodie pbr&amp;b.\nSlow-carb sustainable cliche. Squid ennui kombucha yuccie biodiesel. Vhs cliche deep v mustache jean shorts trust fund fashion axe. Keffiyeh squid pbr&amp;b fixie selvage.\nRoof blue bottle stumptown godard drinking yuccie. Craft beer artisan bushwick kale chips selvage. Kickstarter ethical asymmetrical franzen brooklyn etsy.</p>\n",
  "attachments": null
}
```

### `PUT /v2/mailings/7`

```
  "mailing": {
    "content": "Hi andre,\nYou just *won* the mego jackpot !\nCheck [this link](http://spam.prizepool-game-lottery.xxx/winner.php)",
    "from": "[email protected]",
    "identifier": "an_unique_identifier",
    "subject": "You are the super online contest winner !!!",
    "subtitle": "And it's kinda awesome",
    "title": "You won the big jackpot",
    "to": [
      "[email protected]"
    ]
  }
}
204
```


## notes

### `POST /v2/notes`

```
  "note": {
    "content": "gentrify roof beard keffiyeh squid franzen cold-pressed farm-to-table retro fingerstache hoodie health",
    "subject": "quinoa",
    "user_id": "10"
  }
}
201
{
  "id": 11,
  "from_user": {
    "id": 74,
    "login": "andre",
    "url": "https://api.intra.42.fr/v2/users/andre"
  },
  "subject": "quinoa",
  "content": "gentrify roof beard keffiyeh squid franzen cold-pressed farm-to-table retro fingerstache hoodie health",
  "created_at": "2017-11-22T13:43:47.322Z",
  "user": {
    "id": 10,
    "login": "ssebulba",
    "url": "https://api.intra.42.fr/v2/users/ssebulba"
  }
}
```

### `DELETE /v2/notes/9` — HTTP 204

```
(no body)
```

### `GET /v2/notes?page=1` — HTTP 200

```json
[
  {
    "id": 1,
    "from_user": {
      "id": 74,
      "login": "andre",
      "url": "https://api.intra.42.fr/v2/users/andre"
    },
    "subject": "Chevelure abondante",
    "content": "Mathieu n'aime pas se faire appeler princesse ♥️",
    "created_at": "2016-04-27T07:26:38.254Z",
    "user": {
      "id": 22,
      "login": "mathieu",
      "url": "https://api.intra.42.fr/v2/users/mathieu"
    }
  },
  {
    "id": 2,
    "from_user": {
      "id": 22,
      "login": "mathieu",
      "url": "https://api.intra.42.fr/v2/users/mathieu"
    },
    "subject": "Amour caché",
    "content": "Est secretement amoureux de flav️",
    "created_at": "2016-04-27T07:26:38.254Z",
    "user": {
      "id": 74,
      "login": "andre",
      "url": "https://api.intra.42.fr/v2/users/andre"
    }
  },
  {
    "id": 3,
    "from_user": {
      "id": 22,
      "login": "mathieu",
      "url": "https://api.intra.42.fr/v2/users/mathieu"
    },
    "subject": "Amour caché (2)",
    "content": "Est secretement amoureux de andré",
    "created_at": "2016-04-27T07:26:38.254Z",
    "user": {
      "id": 10935,
      "login": "fguilloc",
      "url": "https://api.intra.42.fr/v2/users/fguilloc"
    }
  }
]
```

### `GET /v2/notes/1` — HTTP 200

```json
{
  "id": 1,
  "from_user": {
    "id": 74,
    "login": "andre",
    "url": "https://api.intra.42.fr/v2/users/andre"
  },
  "subject": "Chevelure abondante",
  "content": "Mathieu n'aime pas se faire apeller princesse ♥️",
  "created_at": "2016-04-27T07:26:38.254Z",
  "user": {
    "id": 22,
    "login": "mathieu",
    "url": "https://api.intra.42.fr/v2/users/mathieu"
  }
}
```

### `GET /v2/notes/9` — HTTP 200

```json
{
  "id": 9,
  "from_user": {
    "id": 74,
    "login": "andre",
    "url": "https://api.intra.42.fr/v2/users/andre"
  },
  "subject": "We need to back up the haptic XSS feed!",
  "content": "You know, that little droid is going to cause me a lot of trouble.",
  "created_at": "2017-11-22T13:42:11.225Z",
  "user": {
    "id": 116,
    "login": "mwindu2",
    "url": "https://api.intra.42.fr/v2/users/mwindu2"
  }
}
```

### `PUT /v2/notes/9`

```
  "note": {
    "content": "waistcoat sartorial cornhole dreamcatcher pop-up scenester cleanse hammock shoreditch pug iPhone freegan",
    "subject": "swag",
    "user_id": "109"
  }
}
204
```


## notions

### `POST /v2/notions`

```
  "notion": {
    "cursus_ids": [
      "2"
    ],
    "name": "Metafiction",
    "subnotions_attributes": [
      {
        "name": "Postern of Fate"
      }
    ],
    "tag_ids": [
      "2",
      "3",
      "6"
    ]
  }
}
201
{
  "id": 11,
  "name": "Metafiction",
  "slug": "metafiction",
  "created_at": "2017-11-22T13:43:48.180Z",
  "subnotions": [
    {
      "id": 11,
      "name": "Postern of Fate",
      "slug": "postern-of-fate",
      "created_at": "2017-11-22T13:43:48.192Z",
      "notepad": null
    }
  ],
  "tags": [
    {
      "id": 2,
      "name": "Friends with Benefits",
      "kind": "project"
    },
    {
      "id": 3,
      "name": "GBmu",
      "kind": "project"
    },
    {
      "id": 6,
      "name": "Jour 13",
      "kind": "project"
    }
  ],
  "cursus": [
    {
      "id": 2,
      "created_at": "2017-11-22T13:41:00.825Z",
      "name": "42",
      "slug": "42"
    }
  ]
}
```

### `DELETE /v2/notions/3` — HTTP 204

```
(no body)
```

### `GET /v2/notions` — HTTP 200

```json
[
  {
    "id": 10,
    "name": "Piscine OCaml - D08 - Object oriented programming 2/2",
    "slug": "piscine-ocaml-d08-object-oriented-programming-2-2",
    "created_at": "2017-11-22T13:41:24.091Z",
    "subnotions": [],
    "tags": [
      {
        "id": 6,
        "name": "Jour 13",
        "kind": "project"
      }
    ],
    "cursus": [
      {
        "id": 2,
        "created_at": "2017-11-22T13:41:00.825Z",
        "name": "42",
        "slug": "42"
      }
    ]
  },
  {
    "id": 9,
    "name": "Piscine Unity - D07 - GUI 3D, navmesh and raycasting",
    "slug": "piscine-unity-d07-gui-3d-navmesh-and-raycasting",
    "created_at": "2017-11-22T13:41:24.053Z",
    "subnotions": [],
    "tags": [
      {
        "id": 7,
        "name": "Bocal",
        "kind": "general"
      }
    ],
    "cursus": [
      {
        "id": 2,
        "created_at": "2017-11-22T13:41:00.825Z",
        "name": "42",
        "slug": "42"
      }
    ]
  },
  {
    "id": 8,
    "name": "Piscine OCaml - D05 - Imperative traits",
    "slug": "piscine-ocaml-d05-imperative-traits",
    "created_at": "2017-11-22T13:41:24.021Z",
    "subnotions": [],
    "tags": [
      {
        "id": 7,
        "name": "Bocal",
        "kind": "general"
      }
    ],
    "cursus": [
      {
        "id": 1,
        "created_at": "2017-11-22T13:41:00.750Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      }
    ]
  }
]
```

### `GET /v2/notions/3` — HTTP 200

```json
{
  "id": 3,
  "name": "Piscine OCaml - D01 - MOAR functions",
  "slug": "piscine-ocaml-d01-moar-functions",
  "created_at": "2017-11-22T13:41:23.822Z",
  "subnotions": [],
  "tags": [
    {
      "id": 3,
      "name": "GBmu",
      "kind": "project"
    }
  ],
  "cursus": [
    {
      "id": 2,
      "created_at": "2017-11-22T13:41:00.825Z",
      "name": "42",
      "slug": "42"
    }
  ]
}
```

### `PUT /v2/notions/3`

```
  "notion": {
    "cursus_ids": [
      "2"
    ],
    "name": "Metafiction",
    "subnotions_attributes": [
      {
        "name": "The Millstone"
      }
    ],
    "tag_ids": [
      "1",
      "11",
      "10"
    ]
  }
}
204
```


## partnerships

### `POST /v2/partnerships`

```
  "partnership": {
    "cursus_id": "2",
    "description": "indexing the hard drive won't do anything, we need to parse the solid state PNG application!",
    "difficulty": "100",
    "name": "Western Arkansas College",
    "partnerships_skills_attributes": [
      {
        "skill_id": "2",
        "value": "100.0"
      }
    ]
  }
}
201
{
  "id": 2,
  "name": "Western Arkansas College",
  "slug": "western-arkansas-college",
  "tier": 1,
  "url": "https://api.intra.42.fr/v2/partnerships/western-arkansas-college",
  "partnerships_users_url": "https://api.intra.42.fr/v2/partnerships/western-arkansas-college/partnerships_users"
}
```

### `DELETE /v2/partnerships/1` — HTTP 204

```
(no body)
```

### `GET /v2/partnerships` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Strosin-Kiehn",
    "slug": "strosin-kiehn",
    "tier": 1,
    "url": "https://api.intra.42.fr/v2/partnerships/strosin-kiehn",
    "partnerships_users_url": "https://api.intra.42.fr/v2/partnerships/strosin-kiehn/partnerships_users"
  }
]
```

### `GET /v2/partnerships/1` — HTTP 200

```json
{
  "id": 1,
  "name": "Strosin-Kiehn",
  "slug": "strosin-kiehn",
  "tier": 1,
  "url": "https://api.intra.42.fr/v2/partnerships/strosin-kiehn",
  "partnerships_users_url": "https://api.intra.42.fr/v2/partnerships/strosin-kiehn/partnerships_users"
}
```

### `PUT /v2/partnerships/1`

```
  "partnership": {
    "description": "indexing the hard drive won't do anything, we need to parse the solid state PNG application!",
    "name": "Western Arkansas College"
  }
}
204
```


## partnerships_users

### `POST /v2/partnerships_users`

```
  "partnerships_user": {
    "partnership_id": "1",
    "user_id": "107"
  }
}
201
{
  "id": 6,
  "partnership_id": 1,
  "final_mark": null,
  "user": {
    "id": 107,
    "login": "lukeskyw",
    "url": "https://api.intra.42.fr/v2/users/lukeskyw"
  }
}
```

### `DELETE /v2/partnerships_users/5` — HTTP 204

```
(no body)
```

### `GET /v2/partnerships_users` — HTTP 200

```json
[
  {
    "id": 5,
    "partnership_id": 1,
    "final_mark": null,
    "user": {
      "id": 77,
      "login": "bofett",
      "url": "https://api.intra.42.fr/v2/users/bofett"
    }
  },
  {
    "id": 4,
    "partnership_id": 1,
    "final_mark": null,
    "user": {
      "id": 12,
      "login": "kiki-adi",
      "url": "https://api.intra.42.fr/v2/users/kiki-adi"
    }
  },
  {
    "id": 3,
    "partnership_id": 1,
    "final_mark": null,
    "user": {
      "id": 14,
      "login": "pamidala",
      "url": "https://api.intra.42.fr/v2/users/pamidala"
    }
  }
]
```

### `GET /v2/partnerships_users/5` — HTTP 200

```json
{
  "id": 5,
  "partnership_id": 1,
  "final_mark": null,
  "user": {
    "id": 77,
    "login": "bofett",
    "url": "https://api.intra.42.fr/v2/users/bofett"
  }
}
```

### `PUT /v2/partnerships_users/5`

```
  "partnerships_user": {
    "partnership_id": "1",
    "user_id": "99"
  }
}
204
```


## patronages

### `POST /v2/patronages`

```
  "patronage": {
    "godfather_id": "4",
    "user_id": "3"
  }
}
201
{
  "id": 123,
  "user_id": 3,
  "godfather_id": 4,
  "ongoing": true,
  "created_at": "2017-11-22T13:43:50.782Z",
  "updated_at": "2017-11-22T13:43:50.794Z",
  "user": {
    "id": 3,
    "login": "gargamel",
    "url": "https://api.intra.42.fr/v2/users/gargamel"
  },
  "godfather": {
    "id": 4,
    "login": "kpedro",
    "url": "https://api.intra.42.fr/v2/users/kpedro"
  }
}
```

### `DELETE /v2/patronages/113` — HTTP 204

```
(no body)
```

### `GET /v2/patronages` — HTTP 200

```json
[
  {
    "id": 122,
    "user_id": 124,
    "godfather_id": 39,
    "ongoing": true,
    "created_at": "2017-11-22T13:42:12.790Z",
    "updated_at": "2017-11-22T13:42:12.796Z",
    "user": {
      "id": 124,
      "login": "hsolo2",
      "url": "https://api.intra.42.fr/v2/users/hsolo2"
    },
    "godfather": {
      "id": 39,
      "login": "anskywal",
      "url": "https://api.intra.42.fr/v2/users/anskywal"
    }
  },
  {
    "id": 121,
    "user_id": 116,
    "godfather_id": 15,
    "ongoing": true,
    "created_at": "2017-11-22T13:42:12.779Z",
    "updated_at": "2017-11-22T13:42:12.786Z",
    "user": {
      "id": 116,
      "login": "mwindu2",
      "url": "https://api.intra.42.fr/v2/users/mwindu2"
    },
    "godfather": {
      "id": 15,
      "login": "mwindu",
      "url": "https://api.intra.42.fr/v2/users/mwindu"
    }
  },
  {
    "id": 120,
    "user_id": 123,
    "godfather_id": 96,
    "ongoing": true,
    "created_at": "2017-11-22T13:42:12.769Z",
    "updated_at": "2017-11-22T13:42:12.774Z",
    "user": {
      "id": 123,
      "login": "chewbche",
      "url": "https://api.intra.42.fr/v2/users/chewbche"
    },
    "godfather": {
      "id": 96,
      "login": "wattwatt",
      "url": "https://api.intra.42.fr/v2/users/wattwatt"
    }
  }
]
```

### `GET /v2/patronages/113` — HTTP 200

```json
{
  "id": 113,
  "user_id": 119,
  "godfather_id": 85,
  "ongoing": true,
  "created_at": "2017-11-22T13:42:12.697Z",
  "updated_at": "2017-11-22T13:42:12.704Z",
  "user": {
    "id": 119,
    "login": "hasolo",
    "url": "https://api.intra.42.fr/v2/users/hasolo"
  },
  "godfather": {
    "id": 85,
    "login": "chewchew",
    "url": "https://api.intra.42.fr/v2/users/chewchew"
  }
}
```

### `PUT /v2/patronages/113`

```
  "patronage": {
    "godfather_id": "4",
    "user_id": "3"
  }
}
204
```


## patronages_reports

### `POST /v2/patronages_reports`

```
  "patronages_report": {
    "begin_at": "2017-11-22 13:43:10 UTC",
    "patronage_id": "98",
    "report_id": "0",
    "user_id": "27"
  }
}
201
{
  "id": 127,
  "user_id": 27,
  "begin_at": "2017-11-22T13:43:10.000Z",
  "created_at": "2017-11-22T13:43:51.496Z",
  "updated_at": "2017-11-22T13:43:51.496Z",
  "patronage_id": 98,
  "report_id": 0,
  "validated_at": null,
  "patronage": {
    "id": 98,
    "user_id": 107,
    "godfather_id": 96,
    "ongoing": true,
    "created_at": "2017-11-22T13:42:12.541Z",
    "updated_at": "2017-11-22T13:43:51.499Z"
  },
  "report": {
    "id": 0,
    "name": "Final Debriefing",
    "comment": "",
    "introduction_md": "",
    "disclaimer_md": "",
    "guidelines_md": "Schlitz stumptown tacos locavore ennui chartreuse pork belly. Polaroid vice readymade everyday next level. Jean shorts venmo cold-pressed crucifix.\nRamps truffaut tousled biodiesel sriracha shoreditch ugh actually. Celiac street sartorial normcore gentrify chia fingerstache photo booth. Vinyl next level locavore stumptown truffaut vice.\nEveryday keffiyeh pinterest flannel. Five dollar toast yr listicle trust fund franzen salvia. Humblebrag umami aesthetic pour-over blog before they sold out. Humblebrag occupy deep v.",
    "created_at": "2017-11-22T13:42:11.309Z",
    "updated_at": "2017-11-22T13:42:11.416Z",
    "slug": "final-debriefing",
    "delay_days": 210
  },
  "user": {
    "id": 27,
    "login": "dcaedus",
    "url": "https://api.intra.42.fr/v2/users/dcaedus"
  },
  "answers": []
}
```

### `DELETE /v2/patronages_reports/67` — HTTP 204

```
(no body)
```

### `GET /v2/patronages_reports/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 124
}
```

### `GET /v2/patronages_reports/67` — HTTP 200

```json
{
  "id": 67,
  "user_id": 39,
  "begin_at": "2018-06-20T13:42:12.179Z",
  "created_at": "2017-11-22T13:42:12.179Z",
  "updated_at": "2017-11-22T13:42:12.179Z",
  "patronage_id": 67,
  "report_id": 0,
  "validated_at": null,
  "patronage": {
    "id": 67,
    "user_id": 63,
    "godfather_id": 39,
    "ongoing": true,
    "created_at": "2017-11-22T13:42:12.177Z",
    "updated_at": "2017-11-22T13:42:12.181Z"
  },
  "report": {
    "id": 0,
    "name": "Final Debriefing",
    "comment": "",
    "introduction_md": "",
    "disclaimer_md": "",
    "guidelines_md": "Schlitz stumptown tacos locavore ennui chartreuse pork belly. Polaroid vice readymade everyday next level. Jean shorts venmo cold-pressed crucifix.\nRamps truffaut tousled biodiesel sriracha shoreditch ugh actually. Celiac street sartorial normcore gentrify chia fingerstache photo booth. Vinyl next level locavore stumptown truffaut vice.\nEveryday keffiyeh pinterest flannel. Five dollar toast yr listicle trust fund franzen salvia. Humblebrag umami aesthetic pour-over blog before they sold out. Humblebrag occupy deep v.",
    "created_at": "2017-11-22T13:42:11.309Z",
    "updated_at": "2017-11-22T13:42:11.416Z",
    "slug": "final-debriefing",
    "delay_days": 210
  },
  "user": {
    "id": 39,
    "login": "anskywal",
    "url": "https://api.intra.42.fr/v2/users/anskywal"
  },
  "answers": []
}
```

### `PUT /v2/patronages_reports/67`

```
  "patronages_report": {
    "begin_at": "2017-11-22 13:43:10 UTC",
    "patronage_id": "112",
    "report_id": "0",
    "user_id": "53"
  }
}
204
```


## pools

### `POST /v2/pools/1/points/add`

```
  "points": 10
}

{
  "id": 25,
  "current_points": 1310,
  "max_points": 1400,
  "cursus_id": 1,
  "campus_id": 1
}
```

### `GET /v2/pools?page=1`

```json
[
  {
    "id": 25,
    "current_points": 0,
    "max_points": 400,
    "cursus_id": 1,
    "campus_id": 12
  },
  {
    "id": 19,
    "current_points": 110,
    "max_points": 400,
    "cursus_id": 1,
    "campus_id": 9
  },
  {
    "id": 18,
    "current_points": 40,
    "max_points": 600,
    "cursus_id": 1,
    "campus_id": 8
  }
]
```

### `DELETE /v2/pools/1/points/remove`

```
  "points": 10
}

{
  "id": 25,
  "current_points": 1290,
  "max_points": 1400,
  "cursus_id": 1,
  "campus_id": 1
}
```

### `GET /v2/pools/25` — HTTP 200

```json
{
  "id": 25,
  "current_points": 0,
  "max_points": 400,
  "cursus_id": 1,
  "campus_id": 12
}
```


## products

### `POST /v2/products`

```
  "product": {
    "campus_products_attributes": [
      {
        "campus_id": "5"
      }
    ],
    "name": "Chuck Norris's keyboard doesn't have a Ctrl key because nothing controls Chuck Norris.",
    "description": "Utapau",
    "price": "10",
    "quantity": "10",
    "begin_at": "2017-05-22 13:43:51 UTC",
    "end_at": "2023-11-22 13:43:51 UTC",
    "category_id": "3",
    "kind": "auto",
    "slug": "Kashyyyk",
    "image": {
      "tempfile": [],
      "original_filename": "logo.png",
      "content_type": "image/png+xml",
      "headers": "Content-Disposition: form-data; name=\"product[image]\"; filename=\"logo.png\"\r\nContent-Type: image/png+xml\r\nContent-Length: 3058\r\n"
    },
    "is_uniq": "true",
    "one_time_purchase": "true"
  }
}
201
{
  "id": 6,
  "name": "Chuck Norris's keyboard doesn't have a Ctrl key because nothing controls Chuck Norris.",
  "description": "Utapau",
  "price": 10,
  "quantity": 10,
  "begin_at": "2017-05-22T13:43:51.000Z",
  "end_at": "2023-11-22T13:43:51.000Z",
  "category_id": 3,
  "created_at": "2017-11-22T13:43:52.063Z",
  "updated_at": "2017-11-22T13:43:52.097Z",
  "kind": "auto",
  "slug": "chuck-norris-s-keyboard-doesn-t-have-a-ctrl-key-because-nothing-controls-chuck-norris",
  "image": {
    "url": "/uploads/product/image/6/logo.png",
    "thumb": {
      "url": "/uploads/product/image/6/thumb_logo.png"
    }
  },
  "is_uniq": true,
  "one_time_purchase": true
}
```

### `DELETE /v2/products/1` — HTTP 204

```
(no body)
```

### `GET /v2/products` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Jakku",
    "description": "Utapau",
    "price": 100,
    "quantity": 20,
    "begin_at": null,
    "end_at": null,
    "category_id": 1,
    "created_at": "2017-11-22T13:41:20.457Z",
    "updated_at": "2017-11-22T13:41:20.498Z",
    "kind": "auto",
    "slug": "jakku",
    "image": {
      "url": "/uploads/product/image/1/logo.png",
      "thumb": {
        "url": "/uploads/product/image/1/thumb_logo.png"
      }
    },
    "is_uniq": true,
    "one_time_purchase": false
  },
  {
    "id": 2,
    "name": "Sullust",
    "description": "Lothal",
    "price": 100,
    "quantity": 20,
    "begin_at": null,
    "end_at": null,
    "category_id": 1,
    "created_at": "2017-11-22T13:41:20.528Z",
    "updated_at": "2017-11-22T13:41:20.561Z",
    "kind": "auto",
    "slug": "sullust",
    "image": {
      "url": "/uploads/product/image/2/logo.png",
      "thumb": {
        "url": "/uploads/product/image/2/thumb_logo.png"
      }
    },
    "is_uniq": true,
    "one_time_purchase": false
  },
  {
    "id": 3,
    "name": "Geonosis",
    "description": "Naboo",
    "price": 100,
    "quantity": 20,
    "begin_at": null,
    "end_at": null,
    "category_id": 1,
    "created_at": "2017-11-22T13:41:20.590Z",
    "updated_at": "2017-11-22T13:41:20.621Z",
    "kind": "auto",
    "slug": "geonosis",
    "image": {
      "url": "/uploads/product/image/3/logo.png",
      "thumb": {
        "url": "/uploads/product/image/3/thumb_logo.png"
      }
    },
    "is_uniq": true,
    "one_time_purchase": false
  }
]
```

### `GET /v2/products/1` — HTTP 200

```json
{
  "id": 1,
  "name": "Jakku",
  "description": "Utapau",
  "price": 100,
  "quantity": 20,
  "begin_at": null,
  "end_at": null,
  "category_id": 1,
  "created_at": "2017-11-22T13:41:20.457Z",
  "updated_at": "2017-11-22T13:41:20.498Z",
  "kind": "auto",
  "slug": "jakku",
  "image": {
    "url": "/uploads/product/image/1/logo.png",
    "thumb": {
      "url": "/uploads/product/image/1/thumb_logo.png"
    }
  },
  "is_uniq": true,
  "one_time_purchase": false
}
```

### `PUT /v2/products/1`

```
  "product": {
    "campus_products_attributes": [
      {
        "campus_id": "3"
      }
    ],
    "name": "Chuck Norris programs do not accept input.",
    "description": "Kamino",
    "price": "10",
    "quantity": "10",
    "begin_at": "2017-05-22 13:43:52 UTC",
    "end_at": "2023-11-22 13:43:52 UTC",
    "category_id": "1",
    "kind": "auto",
    "slug": "DQar",
    "image": {
      "tempfile": [],
      "original_filename": "logo.png",
      "content_type": "image/png+xml",
      "headers": "Content-Disposition: form-data; name=\"product[image]\"; filename=\"logo.png\"\r\nContent-Type: image/png+xml\r\nContent-Length: 3058\r\n"
    },
    "is_uniq": "true",
    "one_time_purchase": "true"
  }
}
204
```


## project_data

### `POST /v2/project_data`

```
  "project_data": {
    "by": "[[7, 3000, 1900, 3000, 1725], [36, 3000, 1725, 3100, 1725]]",
    "coordinates": "[2350.0, 3450.0]",
    "kind": "project",
    "project_session_id": "5"
  }
}
201
{
  "id": 8,
  "coordinates": [
    2350.0,
    3450.0
  ],
  "by": [
    [
      7,
      3000,
      1900,
      3000,
      1725
    ],
    [
      36,
      3000,
      1725,
      3100,
      1725
    ]
  ],
  "kind": "project",
  "project_session_id": 5
}
```

### `GET /v2/project_data` — HTTP 200

```json
[
  {
    "id": 6,
    "coordinates": [
      73.0,
      53.0
    ],
    "by": [],
    "kind": "project",
    "project_session_id": 3
  },
  {
    "id": 4,
    "coordinates": [
      63.0,
      81.0
    ],
    "by": [],
    "kind": "exam",
    "project_session_id": 2
  },
  {
    "id": 5,
    "coordinates": [
      80.0,
      76.0
    ],
    "by": [],
    "kind": "exam",
    "project_session_id": 2
  }
]
```

### `GET /v2/project_data/1` — HTTP 200

```json
{
  "id": 1,
  "coordinates": [
    11.0,
    14.0
  ],
  "by": [],
  "kind": "rush",
  "project_session_id": 1
}
```


## project_sessions

### `GET /v2/project_sessions/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 5
}
```

### `GET /v2/project_sessions` — HTTP 200

```json
[
  {
    "id": 5,
    "solo": false,
    "begin_at": null,
    "end_at": null,
    "estimate_time": null,
    "duration_days": null,
    "terminating_after": null,
    "project_id": 5,
    "campus_id": null,
    "cursus_id": null,
    "created_at": "2017-11-22T13:41:26.911Z",
    "updated_at": "2017-11-22T13:41:26.911Z",
    "max_people": null,
    "is_subscriptable": true,
    "scales": [],
    "uploads": [],
    "team_behaviour": "user",
    "project": {
      "id": 5,
      "name": "Quarter Finals",
      "slug": "hogwarts-quidditch-cup-quarter-finals",
      "description": null,
      "parent": {
        "name": "Hogwarts Quidditch Cup",
        "id": 4,
        "slug": "hogwarts-quidditch-cup",
        "url": "https://projects.intra.42.fr/hogwarts-quidditch-cup/mine"
      },
      "children": [],
      "objectives": null,
      "tier": null,
      "attachments": [],
      "created_at": "2017-11-22T13:41:26.895Z",
      "updated_at": "2017-11-22T13:41:26.973Z",
      "exam": false
    },
    "campus": null,
    "cursus": null,
    "evaluations": [
      {
        "id": 5,
        "kind": "scale"
      }
    ]
  },
  {
    "id": 4,
    "solo": false,
    "begin_at": null,
    "end_at": null,
    "estimate_time": null,
    "duration_days": null,
    "terminating_after": null,
    "project_id": 4,
    "campus_id": null,
    "cursus_id": null,
    "created_at": "2017-11-22T13:41:26.786Z",
    "updated_at": "2017-11-22T13:41:26.786Z",
    "max_people": null,
    "is_subscriptable": true,
    "scales": [],
    "uploads": [],
    "team_behaviour": "user",
    "project": {
      "id": 4,
      "name": "Hogwarts Quidditch Cup",
      "slug": "hogwarts-quidditch-cup",
      "description": "The game starts with the referee releasing all four balls from the central circle. The Bludgers and the Snitch, having been bewitched, fly off of their own accord, the Snitch to hide itself quickly and the Bludgers to attack the nearest players. The Quaffle is thrown into the air by the referee to signal the start of play.",
      "parent": null,
      "children": [
        {
          "name": "Quarter Finals",
          "id": 5,
          "slug": "hogwarts-quidditch-cup-quarter-finals",
          "url": "https://projects.intra.42.fr/hogwarts-quidditch-cup-quarter-finals/mine"
        }
      ],
      "objectives": [
        "Quidditch"
      ],
      "tier": 1,
      "attachments": [],
      "created_at": "2017-11-22T13:41:26.765Z",
      "updated_at": "2017-11-22T13:41:26.975Z",
      "exam": false
    },
    "campus": null,
    "cursus": null,
    "evaluations": []
  },
  {
    "id": 3,
    "solo": true,
    "begin_at": null,
    "end_at": null,
    "estimate_time": 2592000,
    "duration_days": null,
    "terminating_after": null,
    "project_id": 3,
    "campus_id": null,
    "cursus_id": null,
    "created_at": "2017-11-22T13:41:26.545Z",
    "updated_at": "2017-11-22T13:41:26.545Z",
    "max_people": null,
    "is_subscriptable": true,
    "scales": [],
    "uploads": [],
    "team_behaviour": "user",
    "project": {
      "id": 3,
      "name": "Metaprogramming in OCaml",
      "slug": "metaprogramming-in-ocaml",
      "description": "Something you shouldn't see",
      "parent": null,
      "children": [],
      "objectives": [
        "Run away"
      ],
      "tier": 1,
      "attachments": [],
      "created_at": "2017-11-22T13:41:26.537Z",
      "updated_at": "2017-11-22T13:41:26.616Z",
      "exam": true
    },
    "campus": null,
    "cursus": null,
    "evaluations": [
      {
        "id": 4,
        "kind": "scale"
      }
    ]
  }
]
```

### `GET /v2/project_sessions/2` — HTTP 200

```json
{
  "id": 2,
  "solo": true,
  "begin_at": null,
  "end_at": null,
  "estimate_time": 2592000,
  "duration_days": null,
  "terminating_after": null,
  "project_id": 2,
  "campus_id": null,
  "cursus_id": null,
  "created_at": "2017-11-22T13:41:26.375Z",
  "updated_at": "2017-11-22T13:41:28.347Z",
  "max_people": null,
  "is_subscriptable": true,
  "scales": [
    {
      "id": 2,
      "correction_number": 3,
      "is_primary": true
    }
  ],
  "uploads": [],
  "team_behaviour": "user",
  "project": {
    "id": 2,
    "name": "Ordinary Wizarding Levels",
    "slug": "ordinary-wizarding-levels",
    "description": "Ordinary Wizarding Level (often abbreviated O.W.L.) is a subject-specific test taken during Hogwarts School of Witchcraft and Wizardry students' fifth year, administrated by the Wizarding Examinations Authority. The score made by a student on a particular O.W.L. determines whether or not he or she will be allowed to continue taking that subject in subsequent school years.",
    "parent": null,
    "children": [],
    "objectives": [
      "Wizarding"
    ],
    "tier": 1,
    "attachments": [],
    "created_at": "2017-11-22T13:41:26.356Z",
    "updated_at": "2017-11-22T13:41:26.441Z",
    "exam": true
  },
  "campus": null,
  "cursus": null,
  "evaluations": [
    {
      "id": 3,
      "kind": "scale"
    }
  ]
}
```


## project_sessions_skills

### `GET /v2/project_sessions_skills` — HTTP 200

```json
[
  {
    "id": 1,
    "project_session_id": 1979,
    "skill_id": 2,
    "value": 15,
    "created_at": "2019-07-03T12:21:11.956Z",
    "updated_at": "2019-07-03T12:21:11.956Z"
  }
]
```

### `GET /v2/project_sessions_skills/1` — HTTP 200

```json
{
  "id": 1,
  "project_session_id": 1979,
  "skill_id": 2,
  "value": 15,
  "created_at": "2019-07-03T12:21:11.956Z",
  "updated_at": "2019-07-03T12:21:11.956Z"
}
```


## projects

### `POST /v2/projects`

```
  "project": {
    "campus_ids": [
      "6",
      "4",
      "2"
    ],
    "cursus_ids": [
      "2"
    ],
    "description": "Cleanse williamsburg brooklyn shabby chic pinterest kickstarter diy.",
    "has_git": "true",
    "has_mark": "true",
    "is_subscriptable": "true",
    "name": "Butter In a Lordly Dish",
    "project_sessions_attributes": [
      {
        "campus_id": "",
        "cursus_id": "",
        "estimate_time": "2592000",
        "is_subscriptable": "true",
        "minimum_mark": "77",
        "solo": "true",
        "team_behaviour": "user"
      },
      {
        "campus_id": "",
        "cursus_id": "2",
        "estimate_time": "2592000",
        "is_subscriptable": "true",
        "minimum_mark": "77",
        "solo": "true",
        "team_behaviour": "user"
      }
    ],
    "visible": "true"
  }
}
201
{
  "id": 6,
  "name": "Butter In a Lordly Dish",
  "slug": "butter-in-a-lordly-dish",
  "difficulty": 5000,
  "description": "Cleanse williamsburg brooklyn shabby chic pinterest kickstarter diy.",
  "parent": null,
  "children": [],
  "objectives": null,
  "attachments": [],
  "created_at": "2017-11-22T13:43:54.544Z",
  "updated_at": "2017-11-22T13:43:54.647Z",
  "exam": false,
  "cursus": [
    {
      "id": 2,
      "created_at": "2017-11-22T13:41:00.825Z",
      "name": "42",
      "slug": "42"
    }
  ],
  "campus": [
    {
      "id": 6,
      "name": "Paris",
      "time_zone": "Europe/Paris",
      "language": {
        "id": 1,
        "name": "Français",
        "identifier": "fr",
        "created_at": "2017-11-22T13:40:59.462Z",
        "updated_at": "2017-11-22T13:40:59.462Z"
      },
      "users_count": 19,
      "vogsphere_id": 1
    },
    {
      "id": 4,
      "name": "Kiev",
      "time_zone": "Europe/Kiev",
      "language": {
        "id": 2,
        "name": "English",
        "identifier": "en",
        "created_at": "2017-11-22T13:40:59.465Z",
        "updated_at": "2017-11-22T13:40:59.465Z"
      },
      "users_count": 22,
      "vogsphere_id": null
    },
    {
      "id": 2,
      "name": "Johannesburg",
      "time_zone": "Africa/Johannesburg",
      "language": {
        "id": 2,
        "name": "English",
        "identifier": "en",
        "created_at": "2017-11-22T13:40:59.465Z",
        "updated_at": "2017-11-22T13:40:59.465Z"
      },
      "users_count": 26,
      "vogsphere_id": 1
    }
  ],
  "skills": [],
  "videos": [],
  "tags": [],
  "project_sessions": [
    {
      "id": 7,
      "solo": true,
      "begin_at": null,
      "end_at": null,
      "difficulty": 5000,
      "estimate_time": 2592000,
      "duration_days": null,
      "terminating_after": null,
      "project_id": 6,
      "campus_id": null,
      "cursus_id": null,
      "created_at": "2017-11-22T13:43:54.566Z",
      "updated_at": "2017-11-22T13:43:54.566Z",
      "max_people": null,
      "is_subscriptable": true,
      "scales": [],
      "uploads": [],
      "team_behaviour": "user",
      "minimum_mark": 77
    },
    {
      "id": 8,
      "solo": true,
      "begin_at": null,
      "end_at": null,
      "difficulty": 5000,
      "estimate_time": 2592000,
      "duration_days": null,
      "terminating_after": null,
      "project_id": 6,
      "campus_id": null,
      "cursus_id": 2,
      "created_at": "2017-11-22T13:43:54.574Z",
      "updated_at": "2017-11-22T13:43:54.574Z",
      "max_people": null,
      "is_subscriptable": true,
      "scales": [],
      "uploads": [],
      "team_behaviour": "user",
      "minimum_mark": 77
    }
  ]
}
```

### `DELETE /v2/projects/2` — HTTP 204

```
(no body)
```

### `GET /v2/cursus/1/projects` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Libft",
    "slug": "libft",
    "difficulty": 5000,
    "description": "The first project of 42 !",
    "parent": null,
    "children": [],
    "objectives": [
      "initiation"
    ],
    "attachments": [],
    "created_at": "2017-11-22T13:41:25.963Z",
    "updated_at": "2017-11-22T13:41:26.243Z",
    "exam": false,
    "cursus": [
      {
        "id": 1,
        "created_at": "2017-11-22T13:41:00.750Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      }
    ],
    "campus": [
      {
        "id": 1,
        "name": "Cluj",
        "time_zone": "Europe/Bucharest",
        "language": {
          "id": 3,
          "name": "Romanian",
          "identifier": "ro",
          "created_at": "2017-11-22T13:40:59.468Z",
          "updated_at": "2017-11-22T13:41:26.139Z"
        },
        "users_count": 28,
        "vogsphere_id": 1
      }
    ],
    "skills": [
      {
        "id": 2,
        "name": "Company experience",
        "created_at": "2017-11-22T13:41:00.305Z"
      },
      {
        "id": 1,
        "name": "Parallel computing",
        "created_at": "2017-11-22T13:41:00.257Z"
      }
    ],
    "videos": [],
    "tags": [
      {
        "id": 12,
        "name": "Libft",
        "kind": "general"
      }
    ],
    "project_sessions": [
      {
        "id": 1,
        "solo": true,
        "begin_at": null,
        "end_at": null,
        "difficulty": 5000,
        "estimate_time": 2592000,
        "duration_days": null,
        "terminating_after": null,
        "project_id": 1,
        "campus_id": null,
        "cursus_id": null,
        "created_at": "2017-11-22T13:41:26.149Z",
        "updated_at": "2017-11-22T13:42:09.376Z",
        "max_people": null,
        "is_subscriptable": true,
        "scales": [
          {
            "id": 1,
            "correction_number": 3,
            "is_primary": true
          }
        ],
        "uploads": [
          {
            "id": 1,
            "name": "Idaho kangaroos"
          }
        ],
        "team_behaviour": "user"
      }
    ]
  },
  {
    "id": 2,
    "name": "Ordinary Wizarding Levels",
    "slug": "ordinary-wizarding-levels",
    "difficulty": 5000,
    "description": "Ordinary Wizarding Level (often abbreviated O.W.L.) is a subject-specific test taken during Hogwarts School of Witchcraft and Wizardry students' fifth year, administrated by the Wizarding Examinations Authority. The score made by a student on a particular O.W.L. determines whether or not he or she will be allowed to continue taking that subject in subsequent school years.",
    "parent": null,
    "children": [],
    "objectives": [
      "Wizarding"
    ],
    "attachments": [],
    "created_at": "2017-11-22T13:41:26.356Z",
    "updated_at": "2017-11-22T13:41:26.441Z",
    "exam": true,
    "cursus": [
      {
        "id": 1,
        "created_at": "2017-11-22T13:41:00.750Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      }
    ],
    "campus": [
      {
        "id": 1,
        "name": "Cluj",
        "time_zone": "Europe/Bucharest",
        "language": {
          "id": 3,
          "name": "Romanian",
          "identifier": "ro",
          "created_at": "2017-11-22T13:40:59.468Z",
          "updated_at": "2017-11-22T13:41:26.139Z"
        },
        "users_count": 28,
        "vogsphere_id": 1
      }
    ],
    "skills": [
      {
        "id": 1,
        "name": "Parallel computing",
        "created_at": "2017-11-22T13:41:00.257Z"
      },
      {
        "id": 6,
        "name": "Basics",
        "created_at": "2017-11-22T13:41:00.448Z"
      }
    ],
    "videos": [],
    "tags": [
      {
        "id": 13,
        "name": "Ordinary Wizarding Levels",
        "kind": "general"
      }
    ],
    "project_sessions": [
      {
        "id": 2,
        "solo": true,
        "begin_at": null,
        "end_at": null,
        "difficulty": 5000,
        "estimate_time": 2592000,
        "duration_days": null,
        "terminating_after": null,
        "project_id": 2,
        "campus_id": null,
        "cursus_id": null,
        "created_at": "2017-11-22T13:41:26.375Z",
        "updated_at": "2017-11-22T13:41:28.347Z",
        "max_people": null,
        "is_subscriptable": true,
        "scales": [
          {
            "id": 2,
            "correction_number": 3,
            "is_primary": true
          }
        ],
        "uploads": [],
        "team_behaviour": "user"
      }
    ]
  },
  {
    "id": 4,
    "name": "Hogwarts Quidditch Cup",
    "slug": "hogwarts-quidditch-cup",
    "difficulty": 5000,
    "description": "The game starts with the referee releasing all four balls from the central circle. The Bludgers and the Snitch, having been bewitched, fly off of their own accord, the Snitch to hide itself quickly and the Bludgers to attack the nearest players. The Quaffle is thrown into the air by the referee to signal the start of play.",
    "parent": null,
    "children": [
      {
        "name": "Quarter Finals",
        "id": 5,
        "slug": "hogwarts-quidditch-cup-quarter-finals",
        "url": "https://projects.intra.42.fr/hogwarts-quidditch-cup-quarter-finals/mine"
      }
    ],
    "objectives": [
      "Quidditch"
    ],
    "attachments": [],
    "created_at": "2017-11-22T13:41:26.765Z",
    "updated_at": "2017-11-22T13:41:26.975Z",
    "exam": false,
    "cursus": [
      {
        "id": 1,
        "created_at": "2017-11-22T13:41:00.750Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      }
    ],
    "campus": [
      {
        "id": 1,
        "name": "Cluj",
        "time_zone": "Europe/Bucharest",
        "language": {
          "id": 3,
          "name": "Romanian",
          "identifier": "ro",
          "created_at": "2017-11-22T13:40:59.468Z",
          "updated_at": "2017-11-22T13:41:26.139Z"
        },
        "users_count": 28,
        "vogsphere_id": 1
      }
    ],
    "skills": [
      {
        "id": 6,
        "name": "Basics",
        "created_at": "2017-11-22T13:41:00.448Z"
      },
      {
        "id": 1,
        "name": "Parallel computing",
        "created_at": "2017-11-22T13:41:00.257Z"
      }
    ],
    "videos": [],
    "tags": [
      {
        "id": 15,
        "name": "Hogwarts Quidditch Cup",
        "kind": "general"
      }
    ],
    "project_sessions": [
      {
        "id": 4,
        "solo": false,
        "begin_at": null,
        "end_at": null,
        "difficulty": 5000,
        "estimate_time": null,
        "duration_days": null,
        "terminating_after": null,
        "project_id": 4,
        "campus_id": null,
        "cursus_id": null,
        "created_at": "2017-11-22T13:41:26.786Z",
        "updated_at": "2017-11-22T13:41:26.786Z",
        "max_people": null,
        "is_subscriptable": true,
        "scales": [],
        "uploads": [],
        "team_behaviour": "user"
      }
    ]
  }
]
```

### `GET /v2/projects/2` — HTTP 200

```json
{
  "id": 2,
  "name": "Ordinary Wizarding Levels",
  "slug": "ordinary-wizarding-levels",
  "difficulty": 5000,
  "description": "Ordinary Wizarding Level (often abbreviated O.W.L.) is a subject-specific test taken during Hogwarts School of Witchcraft and Wizardry students' fifth year, administrated by the Wizarding Examinations Authority. The score made by a student on a particular O.W.L. determines whether or not he or she will be allowed to continue taking that subject in subsequent school years.",
  "parent": null,
  "children": [],
  "objectives": [
    "Wizarding"
  ],
  "attachments": [],
  "created_at": "2017-11-22T13:41:26.356Z",
  "updated_at": "2017-11-22T13:41:26.441Z",
  "exam": true,
  "cursus": [
    {
      "id": 1,
      "created_at": "2017-11-22T13:41:00.750Z",
      "name": "Piscine C",
      "slug": "piscine-c"
    }
  ],
  "campus": [
    {
      "id": 1,
      "name": "Cluj",
      "time_zone": "Europe/Bucharest",
      "language": {
        "id": 3,
        "name": "Romanian",
        "identifier": "ro",
        "created_at": "2017-11-22T13:40:59.468Z",
        "updated_at": "2017-11-22T13:41:26.139Z"
      },
      "users_count": 28,
      "vogsphere_id": 1
    }
  ],
  "skills": [
    {
      "id": 6,
      "name": "Basics",
      "created_at": "2017-11-22T13:41:00.448Z"
    },
    {
      "id": 1,
      "name": "Parallel computing",
      "created_at": "2017-11-22T13:41:00.257Z"
    }
  ],
  "videos": [],
  "tags": [
    {
      "id": 13,
      "name": "Ordinary Wizarding Levels",
      "kind": "general"
    }
  ],
  "project_sessions": [
    {
      "id": 2,
      "solo": true,
      "begin_at": null,
      "end_at": null,
      "difficulty": 5000,
      "estimate_time": 2592000,
      "duration_days": null,
      "terminating_after": null,
      "project_id": 2,
      "campus_id": null,
      "cursus_id": null,
      "created_at": "2017-11-22T13:41:26.375Z",
      "updated_at": "2017-11-22T13:41:28.347Z",
      "max_people": null,
      "is_subscriptable": true,
      "scales": [
        {
          "id": 2,
          "correction_number": 3,
          "is_primary": true
        }
      ],
      "uploads": [],
      "team_behaviour": "user"
    }
  ]
}
```

### `PUT /v2/projects/2`

```
  "project": {
    "description": "Cliche kinfolk kickstarter chia.",
    "has_git": "true",
    "has_mark": "true",
    "is_subscriptable": "true",
    "name": "Butter In a Lordly Dish",
    "visible": "true"
  }
}
204
```


## projects_users

### `POST /v2/projects_users`

```
  "projects_user": {
    "project_id": "1",
    "user_id": "1"
  }
}
201
{
  "id": 69,
  "occurrence": 0,
  "final_mark": null,
  "status": "in_progress",
  "validated?": null,
  "current_team_id": 69,
  "project": {
    "id": 1,
    "name": "Libft",
    "slug": "libft",
    "parent_id": null
  },
  "cursus_ids": [
    1
  ],
  "user": {
    "id": 1,
    "login": "jeanne",
    "url": "https://api.intra.42.fr/v2/users/jeanne"
  },
  "teams": [
    {
      "id": 69,
      "name": "jeanne's group",
      "url": "https://api.intra.42.fr/v2/teams/69",
      "final_mark": null,
      "project_id": 1,
      "created_at": "2017-11-22T13:43:56.555Z",
      "updated_at": "2017-11-22T13:43:56.625Z",
      "status": "in_progress",
      "terminating_at": null,
      "users": [
        {
          "id": 1,
          "login": "jeanne",
          "url": "https://api.intra.42.fr/v2/users/jeanne",
          "leader": true,
          "occurrence": 0,
          "validated": true,
          "projects_user_id": 69
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": false,
      "repo_url": null,
      "repo_uuid": "intra-uuid-d9a02ebd-ecdb-46fd-8ce8-ecdc4ef9352c-69",
      "locked_at": "2017-11-22T13:43:56.581Z",
      "closed_at": null,
      "project_session_id": 1
    }
  ]
}
```

### `DELETE /v2/projects_users/18` — HTTP 204

```
(no body)
```

### `GET /v2/projects_users/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 68
}
```

### `GET /v2/projects_users` — HTTP 200

```json
[
  {
    "id": 1,
    "occurrence": 0,
    "final_mark": null,
    "status": "in_progress",
    "validated?": null,
    "current_team_id": 1,
    "project": {
      "id": 2,
      "name": "Ordinary Wizarding Levels",
      "slug": "ordinary-wizarding-levels",
      "parent_id": null
    },
    "cursus_ids": [
      1
    ],
    "user": {
      "id": 111,
      "login": "jabinks2",
      "url": "https://api.intra.42.fr/v2/users/jabinks2"
    },
    "teams": [
      {
        "id": 1,
        "name": "jabinks2's group",
        "url": "https://api.intra.42.fr/v2/teams/1",
        "final_mark": null,
        "project_id": 2,
        "created_at": "2017-11-22T13:41:28.447Z",
        "updated_at": "2017-11-22T13:41:28.519Z",
        "status": "in_progress",
        "terminating_at": null,
        "users": [
          {
            "id": 111,
            "login": "coundook",
            "url": "https://api.intra.42.fr/v2/users/coundook",
            "leader": true,
            "occurrence": 0,
            "validated": true,
            "projects_user_id": 1
          }
        ],
        "locked?": true,
        "validated?": null,
        "closed?": false,
        "repo_url": null,
        "repo_uuid": "intra-uuid-e8f23ddc-8e52-47a8-87e9-9bd490621cfd-1",
        "locked_at": "2017-11-22T13:41:28.487Z",
        "closed_at": null,
        "project_session_id": 2
      }
    ]
  },
  {
    "id": 2,
    "occurrence": 0,
    "final_mark": null,
    "status": "in_progress",
    "validated?": null,
    "current_team_id": 2,
    "project": {
      "id": 4,
      "name": "Hogwarts Quidditch Cup",
      "slug": "hogwarts-quidditch-cup",
      "parent_id": null
    },
    "cursus_ids": [
      1
    ],
    "user": {
      "id": 108,
      "login": "podamer2",
      "url": "https://api.intra.42.fr/v2/users/podamer2"
    },
    "teams": [
      {
        "id": 2,
        "name": "podamer2's group",
        "url": "https://api.intra.42.fr/v2/teams/2",
        "final_mark": null,
        "project_id": 4,
        "created_at": "2017-11-22T13:41:28.554Z",
        "updated_at": "2017-11-22T13:41:28.608Z",
        "status": "in_progress",
        "terminating_at": null,
        "users": [
          {
            "id": 108,
            "login": "podamer2",
            "url": "https://api.intra.42.fr/v2/users/podamer2",
            "leader": true,
            "occurrence": 0,
            "validated": true,
            "projects_user_id": 2
          }
        ],
        "locked?": false,
        "validated?": null,
        "closed?": true,
        "repo_url": null,
        "repo_uuid": "intra-uuid-ae9bdbbc-9c16-4c27-8f18-eccee5a31020-2",
        "locked_at": null,
        "closed_at": "2017-11-22T13:41:28.578Z",
        "project_session_id": 4
      }
    ]
  },
  {
    "id": 3,
    "occurrence": 0,
    "final_mark": null,
    "status": "creating_group",
    "validated?": null,
    "current_team_id": 3,
    "project": {
      "id": 5,
      "name": "Quarter Finals",
      "slug": "hogwarts-quidditch-cup-quarter-finals",
      "parent_id": 4
    },
    "cursus_ids": [
      1
    ],
    "user": {
      "id": 108,
      "login": "podamer2",
      "url": "https://api.intra.42.fr/v2/users/podamer2"
    },
    "teams": [
      {
        "id": 3,
        "name": "podamer2's group",
        "url": "https://api.intra.42.fr/v2/teams/3",
        "final_mark": null,
        "project_id": 5,
        "created_at": "2017-11-22T13:41:28.661Z",
        "updated_at": "2017-11-22T13:41:28.704Z",
        "status": "creating_group",
        "terminating_at": null,
        "users": [
          {
            "id": 108,
            "login": "podamer2",
            "url": "https://api.intra.42.fr/v2/users/podamer2",
            "leader": true,
            "occurrence": 0,
            "validated": true,
            "projects_user_id": 3
          }
        ],
        "locked?": false,
        "validated?": null,
        "closed?": false,
        "repo_url": null,
        "repo_uuid": "intra-uuid-d6aded82-d02e-4597-a33a-acd2544ec015-3",
        "locked_at": null,
        "closed_at": null,
        "project_session_id": 5
      }
    ]
  }
]
```

### `POST /v2/projects_users/register_childs_and_scales`

```
  "projects_user": {
    "user_id": 39962,
    "project_id": 2561
  },
  "scales": {
    "2562": 100,
    "2563": 115
  }
}
200
{
  "id": 3609981,
  "occurrence": 0,
  "final_mark": null,
  "status": "in_progress",
  "validated?": null,
  "current_team_id": 5598029,
  "project": {
    "id": 2561,
    "name": "Test Childs",
    "slug": "test-childs",
    "parent_id": null
  },
  "cursus_ids": [
    21
  ],
  "marked_at": null,
  "marked": false,
  "retriable_at": null,
  "created_at": "2024-07-18T12:06:40.573Z",
  "updated_at": "2024-07-18T12:06:40.573Z",
  "user": {},
  "teams": [
    {
      "id": 5598029,
      "name": "ct-39962's group",
      "url": "http://localhost:13000/v2/teams/5598029",
      "final_mark": null,
      "project_id": 2561,
      "created_at": "2024-07-18T12:06:40.638Z",
      "updated_at": "2024-07-18T12:06:40.763Z",
      "status": "in_progress",
      "terminating_at": null,
      "users": [
        {
          "id": 39962
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": true,
      "repo_url": null,
      "repo_uuid": "intra-uuid",
      "locked_at": "2024-07-18T12:06:40.720Z",
      "closed_at": "2024-07-18T12:06:40.741Z",
      "project_session_id": 11961,
      "project_gitlab_path": null
    }
  ]
}
```

### `DELETE /v2/projects_users/reset`

```
  "user_id": 39962,
  "project_id": 21
}
200
[
  "Success"
]
```

### `PATCH /v2/projects_users/scale`

```
  "user_id": 39962,
  "project_id": 21,
  "scale": 100
}
200
{}
```

### `GET /v2/projects_users/18` — HTTP 200

```json
{
  "id": 18,
  "occurrence": 0,
  "final_mark": null,
  "status": "waiting_for_correction",
  "validated?": null,
  "current_team_id": 18,
  "project": {
    "id": 1,
    "name": "Libft",
    "slug": "libft",
    "parent_id": null
  },
  "cursus_ids": [
    1
  ],
  "user": {
    "id": 25,
    "login": "bhutt",
    "url": "https://api.intra.42.fr/v2/users/bhutt"
  },
  "teams": [
    {
      "id": 18,
      "name": "bhutt's group",
      "url": "https://api.intra.42.fr/v2/teams/18",
      "final_mark": null,
      "project_id": 1,
      "created_at": "2017-11-22T13:41:30.835Z",
      "updated_at": "2017-11-22T13:41:30.920Z",
      "status": "waiting_for_correction",
      "terminating_at": null,
      "users": [
        {
          "id": 25,
          "login": "bhutt",
          "url": "https://api.intra.42.fr/v2/users/bhutt",
          "leader": true,
          "occurrence": 0,
          "validated": true,
          "projects_user_id": 18
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": true,
      "repo_url": null,
      "repo_uuid": "intra-uuid-0d4153cd-21b7-4f1a-a526-297314ddc61d-18",
      "locked_at": "2017-11-22T13:41:30.895Z",
      "closed_at": "2017-11-22T13:41:30.919Z",
      "project_session_id": 1
    }
  ]
}
```

### `PUT /v2/projects_users/18`

```
  "projects_user": {
    "project_id": "1",
    "user_id": "1"
  }
}
204
```


## quests

### `POST /v2/quests`

```
  "quest": {
    "close_on_fail": "",
    "cursus_id": "1",
    "description": "You must take a coffee.",
    "kind": "main",
    "mails": "",
    "mails_from": "",
    "name": "Take a coffee ☕️",
    "success_number": "",
    "tries_number": ""
  }
}
201
{
  "id": 2,
  "name": "Take a coffee ☕️",
  "slug": "take-a-coffee",
  "kind": "main",
  "internal_name": null,
  "description": "You must take a coffee.",
  "cursus_id": 1,
  "campus_id": null,
  "created_at": "2017-11-22T13:43:57.270Z",
  "updated_at": "2017-11-22T13:43:57.270Z",
  "grade_id": null,
  "position": 2,
  "guild_size": null,
  "guild_prct": null,
  "mails": null,
  "duration": null,
  "ancestry": null,
  "grade": null,
  "cursus": {
    "id": 1,
    "created_at": "2017-11-22T13:41:00.750Z",
    "name": "Piscine C",
    "slug": "piscine-c"
  },
  "campus": null
}
```

### `DELETE /v2/quests/1` — HTTP 204

```
(no body)
```

### `GET /v2/quests` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "Level 14",
    "slug": "level-14",
    "kind": "main",
    "internal_name": null,
    "description": "Reach the level 14.",
    "cursus_id": 2,
    "campus_id": null,
    "created_at": "2017-11-22T13:42:11.464Z",
    "updated_at": "2017-11-22T13:42:11.464Z",
    "grade_id": null,
    "position": 1,
    "grade": null,
    "cursus": {
      "id": 2,
      "created_at": "2017-11-22T13:41:00.825Z",
      "name": "42",
      "slug": "42"
    },
    "campus": null
  }
]
```

### `GET /v2/quests/1` — HTTP 200

```json
{
  "id": 1,
  "name": "Level 14",
  "slug": "level-14",
  "kind": "main",
  "internal_name": null,
  "description": "Reach the level 14.",
  "cursus_id": 2,
  "campus_id": null,
  "created_at": "2017-11-22T13:42:11.464Z",
  "updated_at": "2017-11-22T13:42:11.464Z",
  "grade_id": null,
  "position": 1,
  "grade": null,
  "cursus": {
    "id": 2,
    "created_at": "2017-11-22T13:41:00.825Z",
    "name": "42",
    "slug": "42"
  },
  "campus": null
}
```

### `PUT /v2/quests/1`

```
  "quest": {
    "close_on_fail": "",
    "cursus_id": "2",
    "description": "You must take a coffee.",
    "kind": "main",
    "mails": "",
    "mails_from": "",
    "name": "Take a coffee ☕️",
    "success_number": "",
    "tries_number": ""
  }
}
204
```


## quests_users

### `POST /v2/quests_users`

```
  "quests_user": {
    "end_at": "2017-11-24 13:43:10 UTC",
    "prct": "42",
    "quest_id": "4",
    "user_id": "117"
  }
}
201
{
  "id": 6,
  "end_at": "2017-11-24T13:43:10.000Z",
  "quest_id": 4,
  "validated_at": null,
  "prct": 42,
  "advancement": null,
  "created_at": "2017-11-22T13:43:58.265Z",
  "updated_at": "2017-11-22T13:43:58.265Z",
  "user": {
    "id": 117,
    "login": "leiorgan",
    "url": "https://api.intra.42.fr/v2/users/leiorgan"
  },
  "quest": {
    "id": 4,
    "name": "Take a coffee ☕️",
    "slug": "take-a-coffee",
    "kind": "main",
    "internal_name": null,
    "description": "You must take a coffee.",
    "cursus_id": 2,
    "campus_id": null,
    "created_at": "2017-11-22T13:43:58.221Z",
    "updated_at": "2017-11-22T13:43:58.221Z",
    "grade_id": null,
    "position": 2,
    "guild_size": null,
    "guild_prct": null,
    "mails": null,
    "duration": null,
    "ancestry": null
  }
}
```

### `DELETE /v2/quests_users/3` — HTTP 204

```
(no body)
```

### `GET /v2/quests_users/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 5
}
```

### `GET /v2/quests_users` — HTTP 200

```json
[
  {
    "id": 5,
    "end_at": null,
    "quest_id": 1,
    "validated_at": null,
    "prct": null,
    "advancement": null,
    "created_at": "2017-11-22T13:42:11.488Z",
    "updated_at": "2017-11-22T13:42:11.488Z",
    "user": {
      "id": 113,
      "login": "bhutt3",
      "url": "https://api.intra.42.fr/v2/users/bhutt3"
    },
    "quest": {
      "id": 1,
      "name": "Level 14",
      "slug": "level-14",
      "kind": "main",
      "internal_name": null,
      "description": "Reach the level 14.",
      "cursus_id": 2,
      "campus_id": null,
      "created_at": "2017-11-22T13:42:11.464Z",
      "updated_at": "2017-11-22T13:42:11.464Z",
      "grade_id": null,
      "position": 1
    }
  },
  {
    "id": 4,
    "end_at": null,
    "quest_id": 1,
    "validated_at": null,
    "prct": null,
    "advancement": null,
    "created_at": "2017-11-22T13:42:11.484Z",
    "updated_at": "2017-11-22T13:42:11.484Z",
    "user": {
      "id": 53,
      "login": "dvader",
      "url": "https://api.intra.42.fr/v2/users/dvader"
    },
    "quest": {
      "id": 1,
      "name": "Level 14",
      "slug": "level-14",
      "kind": "main",
      "internal_name": null,
      "description": "Reach the level 14.",
      "cursus_id": 2,
      "campus_id": null,
      "created_at": "2017-11-22T13:42:11.464Z",
      "updated_at": "2017-11-22T13:42:11.464Z",
      "grade_id": null,
      "position": 1
    }
  },
  {
    "id": 3,
    "end_at": null,
    "quest_id": 1,
    "validated_at": null,
    "prct": null,
    "advancement": null,
    "created_at": "2017-11-22T13:42:11.480Z",
    "updated_at": "2017-11-22T13:42:11.480Z",
    "user": {
      "id": 15,
      "login": "mwindu",
      "url": "https://api.intra.42.fr/v2/users/mwindu"
    },
    "quest": {
      "id": 1,
      "name": "Level 14",
      "slug": "level-14",
      "kind": "main",
      "internal_name": null,
      "description": "Reach the level 14.",
      "cursus_id": 2,
      "campus_id": null,
      "created_at": "2017-11-22T13:42:11.464Z",
      "updated_at": "2017-11-22T13:42:11.464Z",
      "grade_id": null,
      "position": 1
    }
  }
]
```

### `GET /v2/quests_users/3` — HTTP 200

```json
{
  "id": 3,
  "end_at": null,
  "quest_id": 1,
  "validated_at": null,
  "prct": null,
  "advancement": null,
  "created_at": "2017-11-22T13:42:11.480Z",
  "updated_at": "2017-11-22T13:42:11.480Z",
  "user": {
    "id": 15,
    "login": "mwindu",
    "url": "https://api.intra.42.fr/v2/users/mwindu"
  },
  "quest": {
    "id": 1,
    "name": "Level 14",
    "slug": "level-14",
    "kind": "main",
    "internal_name": null,
    "description": "Reach the level 14.",
    "cursus_id": 2,
    "campus_id": null,
    "created_at": "2017-11-22T13:42:11.464Z",
    "updated_at": "2017-11-22T13:42:11.464Z",
    "grade_id": null,
    "position": 1
  }
}
```

### `PUT /v2/quests_users/3`

```
  "quests_user": {
    "end_at": "2017-11-24 13:43:10 UTC",
    "prct": "42",
    "quest_id": "5",
    "user_id": "31"
  }
}
204
```


## roles

### `POST /v2/roles`

```
  "role": {
    "description": "Synchronised uniform parallelism",
    "name": "astronomer"
  }
}
201
{
  "id": 18,
  "name": "astronomer",
  "description": "Synchronised uniform parallelism"
}
```

### `DELETE /v2/roles/13` — HTTP 204

```
(no body)
```

### `GET /v2/roles` — HTTP 200

```json
[
  {
    "id": 17,
    "name": "Companies Manager",
    "description": "Manage companies"
  },
  {
    "id": 16,
    "name": "Official App",
    "description": "Approved application without rate limits"
  },
  {
    "id": 15,
    "name": "Achievements Manager",
    "description": "Manage users achievements and titles"
  }
]
```

### `GET /v2/roles/13` — HTTP 200

```json
{
  "id": 13,
  "name": "Basic Tutor",
  "description": "Manage projects, scales and all cursus related data"
}
```

### `PUT /v2/roles/13`

```
  "role": {
    "description": "Synchronised uniform parallelism",
    "name": "astronomer"
  }
}
204
```


## roles_entities

### `POST /v2/roles_entities`

```
  "roles_entity": {
    "entity_id": "8",
    "entity_type": "Doorkeeper::Application",
    "role_id": "8"
  }
}
201
{
  "id": 21,
  "entity_id": 8,
  "entity_type": "Doorkeeper::Application",
  "created_at": "2017-11-22T13:43:59.468Z",
  "expires_at": null,
  "entity": {
    "id": 8,
    "name": "test forbidden application",
    "description": null,
    "image": null,
    "website": null,
    "public": false,
    "scopes": [],
    "created_at": "2017-11-22T13:43:11.638Z",
    "updated_at": "2017-11-22T13:43:59.474Z",
    "owner": {
      "id": 116,
      "login": "mwindu2",
      "url": "https://api.intra.42.fr/v2/users/mwindu2"
    },
    "rate_limit": 1800
  },
  "role": {
    "id": 8,
    "name": "Translater",
    "description": "Ability to create and manage content translations"
  }
}
```

### `DELETE /v2/roles_entities/9` — HTTP 204

```
(no body)
```

### `GET /v2/roles_entities/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 20
}
```

### `GET /v2/roles_entities` — HTTP 200

```json
[
  {
    "id": 20,
    "entity_id": 7,
    "entity_type": "Doorkeeper::Application",
    "created_at": "2017-11-22T13:43:11.431Z",
    "expires_at": null,
    "entity": {
      "id": 7,
      "name": "test intrateam staff oauth application",
      "description": null,
      "image": null,
      "website": null,
      "public": true,
      "scopes": [],
      "created_at": "2017-11-22T13:43:11.377Z",
      "updated_at": "2017-11-22T13:43:11.434Z",
      "owner": {
        "id": 74,
        "login": "pamidala",
        "url": "https://api.intra.42.fr/v2/users/pamidala"
      },
      "rate_limit": 1800
    },
    "role": {
      "id": 1,
      "name": "Intrateam",
      "description": "manage all"
    }
  },
  {
    "id": 19,
    "entity_id": 7,
    "entity_type": "Doorkeeper::Application",
    "created_at": "2017-11-22T13:43:11.413Z",
    "expires_at": null,
    "entity": {
      "id": 7,
      "name": "test intrateam staff oauth application",
      "description": null,
      "image": null,
      "website": null,
      "public": true,
      "scopes": [],
      "created_at": "2017-11-22T13:43:11.377Z",
      "updated_at": "2017-11-22T13:43:11.434Z",
      "owner": {
        "id": 74,
        "login": "pamidala",
        "url": "https://api.intra.42.fr/v2/users/pamidala"
      },
      "rate_limit": 1800
    },
    "role": {
      "id": 11,
      "name": "Advanced Staff",
      "description": "Member of the staff, with higher privileges"
    }
  },
  {
    "id": 18,
    "entity_id": 7,
    "entity_type": "Doorkeeper::Application",
    "created_at": "2017-11-22T13:43:11.399Z",
    "expires_at": null,
    "entity": {
      "id": 7,
      "name": "test intrateam staff oauth application",
      "description": null,
      "image": null,
      "website": null,
      "public": true,
      "scopes": [],
      "created_at": "2017-11-22T13:43:11.377Z",
      "updated_at": "2017-11-22T13:43:11.434Z",
      "owner": {
        "id": 74,
        "login": "pamidala",
        "url": "https://api.intra.42.fr/v2/users/pamidala"
      },
      "rate_limit": 1800
    },
    "role": {
      "id": 7,
      "name": "Basic Staff",
      "description": "Member of the staff, can manage community services, closes, exams and access advanced student data"
    }
  }
]
```

### `GET /v2/roles_entities/9` — HTTP 200

```json
{
  "id": 9,
  "entity_id": 4,
  "entity_type": "Doorkeeper::Application",
  "created_at": "2017-11-22T13:43:11.249Z",
  "expires_at": null,
  "entity": {
    "id": 4,
    "name": "test shop staff oauth application",
    "description": null,
    "image": null,
    "website": null,
    "public": true,
    "scopes": [],
    "created_at": "2017-11-22T13:43:11.203Z",
    "updated_at": "2017-11-22T13:43:11.253Z",
    "owner": {},
    "rate_limit": 1800
  },
  "role": {
    "id": 10,
    "name": "Shop Manager",
    "description": "je suis un super manager"
  }
}
```

### `PUT /v2/roles_entities/9`

```
  "roles_entity": {
    "entity_id": "8",
    "entity_type": "Doorkeeper::Application",
    "role_id": "8"
  }
}
204
```


## rules

### `POST /v2/rules`

```
  "rule": {
    "description": "The user first name must start by the #{letter} letter",
    "internal_name": "FirstNameStartingBy",
    "kind": "inscription",
    "name": "First name starting by",
    "params_attributes": [
      {
        "data_type": "string",
        "default_value": "",
        "name": "letter"
      }
    ]
  }
}
201
{
  "id": 11,
  "kind": "inscription",
  "name": "First name starting by",
  "description": "The user first name must start by the #{letter} letter",
  "created_at": "2017-11-22T13:43:59.860Z",
  "updated_at": "2017-11-22T13:43:59.860Z",
  "slug": "inscription-first-name-starting-by",
  "internal_name": "FirstNameStartingBy",
  "params": [
    {
      "id": 1,
      "name": "letter",
      "default_value": "",
      "rule_id": 11,
      "created_at": "2017-11-22T13:43:59.863Z",
      "updated_at": "2017-11-22T13:43:59.863Z",
      "data_type": "string"
    }
  ]
}
```

### `DELETE /v2/rules/6` — HTTP 204

```
(no body)
```

### `GET /v2/rules?page=1` — HTTP 200

```json
[
  {
    "id": 34,
    "kind": "inscription",
    "name": "First name starting by",
    "description": "The user first name must start by the #{letter} letter",
    "created_at": "2016-05-31T15:00:49.898Z",
    "updated_at": "2016-05-31T15:00:49.898Z",
    "slug": "inscription-first-name-starting-by",
    "internal_name": "FirstNameStartingBy",
    "params": [
      {
        "id": 27,
        "name": "letter",
        "default_value": "",
        "rule_id": 34,
        "created_at": "2016-05-31T15:00:49.905Z",
        "updated_at": "2016-05-31T15:00:49.905Z",
        "data_type": "string"
      }
    ],
    "project_sessions_rules": []
  }
]
```

### `GET /v2/rules/34` — HTTP 200

```json
{
  "id": 34,
  "kind": "inscription",
  "name": "First name starting by",
  "description": "The user first name must start by the #{letter} letter",
  "created_at": "2016-05-31T15:00:49.898Z",
  "updated_at": "2016-05-31T15:00:49.898Z",
  "slug": "inscription-first-name-starting-by",
  "internal_name": "FirstNameStartingBy",
  "params": [
    {
      "id": 27,
      "name": "letter",
      "default_value": "",
      "rule_id": 34,
      "created_at": "2016-05-31T15:00:49.905Z",
      "updated_at": "2016-05-31T15:00:49.905Z",
      "data_type": "string"
    }
  ],
  "project_sessions_rules": []
}
```

### `GET /v2/rules/6` — HTTP 200

```json
{
  "id": 6,
  "kind": "inscription",
  "name": "Skill level min",
  "description": "be at least level %{level} at %{skill} in cursus %{cursus}",
  "created_at": "2017-11-22T13:41:01.907Z",
  "updated_at": "2017-11-22T13:41:01.907Z",
  "slug": "inscription-skill-level-min",
  "internal_name": "SkillLevelMin",
  "params": []
}
```

### `PUT /v2/rules/6`

```
  "rule": {
    "description": "The user first name must start by the #{letter} letter",
    "internal_name": "FirstNameStartingBy",
    "kind": "inscription",
    "name": "First name starting by",
    "params_attributes": [
      {
        "data_type": "string",
        "default_value": "",
        "name": "letter"
      }
    ]
  }
}
204
```


## scale_teams

### `POST /v2/scale_teams`

```
  "scale_team": {
    "begin_at": "2017-11-27 09:00:00 UTC",
    "scale_id": "1",
    "team_id": "68"
  }
}
201
{
  "id": 2,
  "scale_id": 1,
  "comment": null,
  "created_at": "2017-11-22T13:44:01.281Z",
  "updated_at": "2017-11-22T13:44:01.281Z",
  "feedback": null,
  "feedback_rating": null,
  "final_mark": null,
  "flag": {
    "id": 1,
    "name": "Ok",
    "positive": true,
    "icon": "check-4",
    "created_at": "2017-11-22T13:41:01.837Z",
    "updated_at": "2017-11-22T13:41:01.837Z"
  },
  "begin_at": null,
  "correcteds": [
    {
      "id": 125,
      "login": "sebulseb",
      "url": "https://api.intra.42.fr/v2/users/sebulseb"
    }
  ],
  "corrector": {},
  "truant": {},
  "filled_at": null,
  "scale": {
    "id": 1,
    "evaluation_id": 1,
    "name": "Utah ducks",
    "is_primary": true,
    "comment": "Perferendis maiores dreamcatcher. Pickled five dollar toast truffaut quis fashion axe.",
    "introduction_md": "Direct trade asperiores aut odit. Eius meh qui nihil reprehenderit. Before they sold out vegan molestias. Brooklyn rerum non architecto mumblecore franzen post-ironic.",
    "disclaimer_md": "Ipsa expedita gluten-free. Laboriosam ennui actually literally aut trust fund.",
    "guidelines_md": "Tumblr ethical eaque blanditiis eligendi. Dolores facere maiores hashtag pour-over architecto.",
    "created_at": "2017-11-22T13:41:27.388Z",
    "correction_number": 3,
    "duration": 1800,
    "manual_subscription": true,
    "languages": [
      {
        "id": 3,
        "name": "Romanian",
        "identifier": "ro",
        "created_at": "2017-11-22T13:40:59.468Z",
        "updated_at": "2017-11-22T13:41:26.139Z"
      }
    ]
  },
  "team": {
    "id": 68,
    "name": "sebulseb's group",
    "url": "https://api.intra.42.fr/v2/teams/68",
    "final_mark": null,
    "project_id": 1,
    "created_at": "2017-11-22T13:41:37.418Z",
    "updated_at": "2017-11-22T13:44:01.294Z",
    "status": "waiting_for_correction",
    "terminating_at": null,
    "users": [
      {
        "id": 125,
        "login": "sebulseb",
        "url": "https://api.intra.42.fr/v2/users/sebulseb",
        "leader": true,
        "occurrence": 0,
        "validated": true,
        "projects_user_id": 68
      }
    ],
    "locked?": true,
    "validated?": null,
    "closed?": true,
    "repo_url": null,
    "repo_uuid": "intra-uuid-5af5ca8d-e0dc-4791-9cfc-ed657e1984e0-68",
    "locked_at": "2017-11-22T13:41:37.471Z",
    "closed_at": "2017-11-22T13:41:37.496Z",
    "project_session_id": 1
  },
  "feedbacks": []
}
```

### `DELETE /v2/scale_teams/1` — HTTP 204

```
(no body)
```

### `GET /v2/scale_teams/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 1
}
```

### `GET /v2/scale_teams` — HTTP 200

```json
[

]
```

### `POST /v2/scale_teams/multiple_create`

```
  "scale_teams": [
    {
      "begin_at": "2017-11-27 09:00:00 UTC",
      "scale_id": "1",
      "team_id": "68"
    }
  ]
}
201
[
  {
    "id": 4,
    "scale_id": 1,
    "comment": null,
    "created_at": "2017-11-22T13:44:01.678Z",
    "updated_at": "2017-11-22T13:44:01.678Z",
    "feedback": null,
    "feedback_rating": null,
    "final_mark": null,
    "flag": {
      "id": 1,
      "name": "Ok",
      "positive": true,
      "icon": "check-4",
      "created_at": "2017-11-22T13:41:01.837Z",
      "updated_at": "2017-11-22T13:41:01.837Z"
    },
    "begin_at": "2017-11-27T09:00:00.000Z",
    "correcteds": [
      {
        "id": 125,
        "login": "sebulseb",
        "url": "https://api.intra.42.fr/v2/users/sebulseb"
      }
    ],
    "corrector": {},
    "truant": {},
    "filled_at": null,
    "scale": {
      "id": 1,
      "evaluation_id": 1,
      "name": "Utah ducks",
      "is_primary": true,
      "comment": "Perferendis maiores dreamcatcher. Pickled five dollar toast truffaut quis fashion axe.",
      "introduction_md": "Direct trade asperiores aut odit. Eius meh qui nihil reprehenderit. Before they sold out vegan molestias. Brooklyn rerum non architecto mumblecore franzen post-ironic.",
      "disclaimer_md": "Ipsa expedita gluten-free. Laboriosam ennui actually literally aut trust fund.",
      "guidelines_md": "Tumblr ethical eaque blanditiis eligendi. Dolores facere maiores hashtag pour-over architecto.",
      "created_at": "2017-11-22T13:41:27.388Z",
      "correction_number": 3,
      "duration": 1800,
      "manual_subscription": true,
      "languages": [
        {
          "id": 3,
          "name": "Romanian",
          "identifier": "ro",
          "created_at": "2017-11-22T13:40:59.468Z",
          "updated_at": "2017-11-22T13:41:26.139Z"
        }
      ]
    },
    "team": {
      "id": 68,
      "name": "sebulseb's group",
      "url": "https://api.intra.42.fr/v2/teams/68",
      "final_mark": null,
      "project_id": 1,
      "created_at": "2017-11-22T13:41:37.418Z",
      "updated_at": "2017-11-22T13:44:01.687Z",
      "status": "waiting_for_correction",
      "terminating_at": null,
      "users": [
        {
          "id": 125,
          "login": "sebulseb",
          "url": "https://api.intra.42.fr/v2/users/sebulseb",
          "leader": true,
          "occurrence": 0,
          "validated": true,
          "projects_user_id": 68
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": true,
      "repo_url": null,
      "repo_uuid": "intra-uuid-5af5ca8d-e0dc-4791-9cfc-ed657e1984e0-68",
      "locked_at": "2017-11-22T13:41:37.471Z",
      "closed_at": "2017-11-22T13:41:37.496Z",
      "project_session_id": 1
    },
    "feedbacks": []
  }
]
```

### `GET /v2/scale_teams/1` — HTTP 200

```json
{
  "id": 1,
  "scale_id": 1,
  "comment": null,
  "created_at": "2017-11-22T13:42:09.187Z",
  "updated_at": "2017-11-22T13:42:09.187Z",
  "feedback": null,
  "feedback_rating": null,
  "final_mark": null,
  "flag": {
    "id": 1,
    "name": "Ok",
    "positive": true,
    "icon": "check-4",
    "created_at": "2017-11-22T13:41:01.837Z",
    "updated_at": "2017-11-22T13:41:01.837Z"
  },
  "begin_at": "2017-11-24T18:00:00.000Z",
  "correcteds": "invisible",
  "corrector": "invisible",
  "truant": {},
  "filled_at": null,
  "scale": {
    "id": 1,
    "evaluation_id": 1,
    "name": "Utah ducks",
    "is_primary": true,
    "comment": "Perferendis maiores dreamcatcher. Pickled five dollar toast truffaut quis fashion axe.",
    "introduction_md": "Direct trade asperiores aut odit. Eius meh qui nihil reprehenderit. Before they sold out vegan molestias. Brooklyn rerum non architecto mumblecore franzen post-ironic.",
    "disclaimer_md": "Ipsa expedita gluten-free. Laboriosam ennui actually literally aut trust fund.",
    "guidelines_md": "Tumblr ethical eaque blanditiis eligendi. Dolores facere maiores hashtag pour-over architecto.",
    "created_at": "2017-11-22T13:41:27.388Z",
    "correction_number": 3,
    "duration": 1800,
    "manual_subscription": true,
    "languages": [
      {
        "id": 3,
        "name": "Romanian",
        "identifier": "ro",
        "created_at": "2017-11-22T13:40:59.468Z",
        "updated_at": "2017-11-22T13:41:26.139Z"
      }
    ]
  },
  "feedbacks": []
}
```

### `PUT /v2/scale_teams/1`

```
  "scale_team": {
    "begin_at": "2017-11-27 09:00:00 UTC",
    "scale_id": "1",
    "team_id": "68",
    "answers_attributes": [
      {
        "question_id": "1",
        "value": "1",
        "id": "1"
      },
      {
        "question_id": "2",
        "value": "1",
        "id": "2"
      }
    ]
  }
}
204
```


## scales

### `POST /v2/scales`

```
  "scale": {
    "comment": "Dolores facere letterpress. Facilis pork belly church-key rem enim ut twee.",
    "correction_number": "3",
    "disclaimer_md": "Narwhal harum et voluptatum dolor similique minus biodiesel. Mlkshk architecto sapiente harum ipsum. Ut selvage paleo. Quia franzen listicle occupy.",
    "duration": "2",
    "evaluation_id": "4",
    "guidelines_md": "Ut kickstarter aut wolf harum vel cornhole stumptown. Next level semiotics ab squid sit ethical lumbersexual. Venmo aspernatur retro letterpress quae ea pickled provident. Small batch ugh quia flexitarian.",
    "introduction_md": "Amet sed sint perferendis sriracha. Thundercats consequuntur salvia. Jean shorts church-key ut enim est selvage aut. Alias cray paleo quia ea nulla five dollar toast in. Vitae eos vegan aut inventore at dolorem quo.",
    "is_external": "false",
    "is_primary": "true",
    "lg": "3",
    "manual_subscription": "false",
    "name": "Tennessee ducks",
    "sections_attributes": [
      {
        "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
        "name": "Maine sheep",
        "questions_attributes": [
          {
            "guidelines": "Single-origin coffee chia bushwick sriracha drinking. Drinking raw denim sartorial austin echo shabby chic tilde pinterest. Raw denim retro taxidermy pbr&b small batch tilde kale chips wolf. Kombucha tousled quinoa.",
            "kind": "standard",
            "name": "South Dakota banshees",
            "questions_skills_attributes": [
              {
                "percentage": "25",
                "skill_id": "6"
              },
              {
                "percentage": "25",
                "skill_id": "1"
              }
            ],
            "rating": "bool"
          }
        ]
      },
      {
        "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
        "name": "Maine sheep",
        "questions_attributes": [
          {
            "guidelines": "Single-origin coffee chia bushwick sriracha drinking. Drinking raw denim sartorial austin echo shabby chic tilde pinterest. Raw denim retro taxidermy pbr&b small batch tilde kale chips wolf. Kombucha tousled quinoa.",
            "kind": "standard",
            "name": "South Dakota banshees",
            "questions_skills_attributes": [
              {
                "percentage": "25",
                "skill_id": "6"
              },
              {
                "percentage": "25",
                "skill_id": "1"
              }
            ],
            "rating": "bool"
          }
        ]
      },
      {
        "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
        "name": "Maine sheep",
        "questions_attributes": [
          {
            "guidelines": "Single-origin coffee chia bushwick sriracha drinking. Drinking raw denim sartorial austin echo shabby chic tilde pinterest. Raw denim retro taxidermy pbr&b small batch tilde kale chips wolf. Kombucha tousled quinoa.",
            "kind": "standard",
            "name": "South Dakota banshees",
            "questions_skills_attributes": [
              {
                "percentage": "25",
                "skill_id": "6"
              },
              {
                "percentage": "25",
                "skill_id": "1"
              }
            ],
            "rating": "bool"
          }
        ]
      },
      {
        "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
        "name": "Maine sheep",
        "questions_attributes": [
          {
            "guidelines": "Single-origin coffee chia bushwick sriracha drinking. Drinking raw denim sartorial austin echo shabby chic tilde pinterest. Raw denim retro taxidermy pbr&b small batch tilde kale chips wolf. Kombucha tousled quinoa.",
            "kind": "standard",
            "name": "South Dakota banshees",
            "questions_skills_attributes": [
              {
                "percentage": "25",
                "skill_id": "6"
              },
              {
                "percentage": "25",
                "skill_id": "1"
              }
            ],
            "rating": "bool"
          }
        ]
      }
    ]
  }
}
201
{
  "id": 3,
  "evaluation_id": 4,
  "name": "Tennessee ducks",
  "is_primary": true,
  "comment": "Dolores facere letterpress. Facilis pork belly church-key rem enim ut twee.",
  "introduction_md": "Amet sed sint perferendis sriracha. Thundercats consequuntur salvia. Jean shorts church-key ut enim est selvage aut. Alias cray paleo quia ea nulla five dollar toast in. Vitae eos vegan aut inventore at dolorem quo.",
  "disclaimer_md": "Narwhal harum et voluptatum dolor similique minus biodiesel. Mlkshk architecto sapiente harum ipsum. Ut selvage paleo. Quia franzen listicle occupy.",
  "guidelines_md": "Ut kickstarter aut wolf harum vel cornhole stumptown. Next level semiotics ab squid sit ethical lumbersexual. Venmo aspernatur retro letterpress quae ea pickled provident. Small batch ugh quia flexitarian.",
  "created_at": "2017-11-22T13:44:02.886Z",
  "correction_number": 3,
  "duration": 1800,
  "manual_subscription": true,
  "languages": [
    {
      "id": 3,
      "name": "Romanian",
      "identifier": "ro",
      "created_at": "2017-11-22T13:40:59.468Z",
      "updated_at": "2017-11-22T13:41:26.139Z"
    }
  ],
  "sections": [
    {
      "id": 6,
      "name": "Maine sheep",
      "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
      "questions": [
        {
          "name": "South Dakota banshees",
          "id": 10,
          "questions_skills": [
            {
              "id": 17,
              "question_id": 10,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:02.903Z",
              "updated_at": "2017-11-22T13:44:02.903Z"
            },
            {
              "id": 18,
              "question_id": 10,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:02.917Z",
              "updated_at": "2017-11-22T13:44:02.917Z"
            }
          ]
        }
      ]
    },
    {
      "id": 7,
      "name": "Maine sheep",
      "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
      "questions": [
        {
          "name": "South Dakota banshees",
          "id": 11,
          "questions_skills": [
            {
              "id": 19,
              "question_id": 11,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:02.991Z",
              "updated_at": "2017-11-22T13:44:02.991Z"
            },
            {
              "id": 20,
              "question_id": 11,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:03.002Z",
              "updated_at": "2017-11-22T13:44:03.002Z"
            }
          ]
        }
      ]
    },
    {
      "id": 8,
      "name": "Maine sheep",
      "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
      "questions": [
        {
          "name": "South Dakota banshees",
          "id": 12,
          "questions_skills": [
            {
              "id": 21,
              "question_id": 12,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:03.060Z",
              "updated_at": "2017-11-22T13:44:03.060Z"
            },
            {
              "id": 22,
              "question_id": 12,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:03.070Z",
              "updated_at": "2017-11-22T13:44:03.070Z"
            }
          ]
        }
      ]
    },
    {
      "id": 9,
      "name": "Maine sheep",
      "description": "Ab quidem shoreditch id fixie paleo raw denim celiac. Chartreuse vinyl pitchfork vero fixie ipsam. Dreamcatcher ut aut voluptatem mustache. Ea officia selvage qui carry. 8-bit expedita aesthetic leggings slow-carb you probably haven't heard of them xoxo.",
      "questions": [
        {
          "name": "South Dakota banshees",
          "id": 13,
          "questions_skills": [
            {
              "id": 23,
              "question_id": 13,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:03.128Z",
              "updated_at": "2017-11-22T13:44:03.128Z"
            },
            {
              "id": 24,
              "question_id": 13,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:44:03.136Z",
              "updated_at": "2017-11-22T13:44:03.136Z"
            }
          ]
        }
      ]
    }
  ],
  "evaluation": {
    "id": 4,
    "kind": "scale"
  }
}
```

### `DELETE /v2/scales/2` — HTTP 204

```
(no body)
```

### `GET /v2/scales?page=1` — HTTP 200

```json
[
  {
    "id": 531,
    "evaluation_id": 168,
    "name": "Unicooooorn !",
    "is_primary": true,
    "comment": "Banh mi dreamcatcher ad natus. Aut blog sunt nostrum est repellendus. Fingerstache hammock echo sed.",
    "introduction_md": "Chambray mumblecore non harum mustache wayfarers eius. Sartorial lumbersexual street tenetur keffiyeh. Dolorum pbr&b eveniet nihil neque dolores non. Banh mi atque officia eaque cumque.",
    "disclaimer_md": "Adipisci iusto qui laborum tote bag letterpress brooklyn. Voluptatibus fanny pack ea wayfarers.",
    "guidelines_md": "Chartreuse sequi repellendus squid franzen qui. Voluptatum sint cornhole mustache single-origin coffee typewriter. Qui omnis ramps vitae gluten-free corrupti 8-bit nam.",
    "created_at": "2016-05-04T10:45:05.519Z",
    "correction_number": 3,
    "duration": 1800,
    "manual_subscription": true,
    "languages": [
      {
        "id": 2,
        "name": "English",
        "identifier": "en",
        "created_at": "2015-04-14T16:07:38.122Z",
        "updated_at": "2015-04-14T16:07:38.122Z"
      }
    ],
    "sections": [
      {
        "id": 1975,
        "name": "Nebraska druids",
        "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
        "questions": [
          {
            "id": 5854,
            "name": "Florida buffalo",
            "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
            "rating": "bool",
            "kind": "standard",
            "created_at": "2016-05-04T10:45:05.785Z"
          }
        ]
      },
      {
        "id": 1976,
        "name": "Nebraska druids",
        "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
        "questions": [
          {
            "id": 5855,
            "name": "Florida buffalo",
            "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
            "rating": "bool",
            "kind": "standard",
            "created_at": "2016-05-04T10:45:06.131Z"
          }
        ]
      },
      {
        "id": 1977,
        "name": "Nebraska druids",
        "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
        "questions": [
          {
            "id": 5856,
            "name": "Florida buffalo",
            "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
            "rating": "bool",
            "kind": "standard",
            "created_at": "2016-05-04T10:45:06.457Z"
          }
        ]
      },
      {
        "id": 1978,
        "name": "Nebraska druids",
        "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
        "questions": [
          {
            "id": 5857,
            "name": "Florida buffalo",
            "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
            "rating": "bool",
            "kind": "standard",
            "created_at": "2016-05-04T10:45:07.035Z"
          }
        ]
      }
    ],
    "evaluation": {
      "id": 168,
      "kind": "scale"
    }
  }
]
```

### `GET /v2/scales/1` — HTTP 200

```json
{
  "id": 1,
  "evaluation_id": 168,
  "name": "Wyoming black cats",
  "is_primary": true,
  "comment": "Banh mi dreamcatcher ad natus. Aut blog sunt nostrum est repellendus. Fingerstache hammock echo sed.",
  "introduction_md": "Chambray mumblecore non harum mustache wayfarers eius. Sartorial lumbersexual street tenetur keffiyeh. Dolorum pbr&b eveniet nihil neque dolores non. Banh mi atque officia eaque cumque.",
  "disclaimer_md": "Adipisci iusto qui laborum tote bag letterpress brooklyn. Voluptatibus fanny pack ea wayfarers.",
  "guidelines_md": "Chartreuse sequi repellendus squid franzen qui. Voluptatum sint cornhole mustache single-origin coffee typewriter. Qui omnis ramps vitae gluten-free corrupti 8-bit nam.",
  "created_at": "2016-05-04T10:45:05.519Z",
  "correction_number": 3,
  "duration": 1800,
  "manual_subscription": true,
  "languages": [
    {
      "id": 2,
      "name": "English",
      "identifier": "en",
      "created_at": "2015-04-14T16:07:38.122Z",
      "updated_at": "2015-04-14T16:07:38.122Z"
    }
  ],
  "sections": [
    {
      "id": 1975,
      "name": "Nebraska druids",
      "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
      "questions": [
        {
          "id": 5854,
          "name": "Florida buffalo",
          "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
          "rating": "bool",
          "kind": "standard",
          "created_at": "2016-05-04T10:45:05.785Z"
        }
      ]
    },
    {
      "id": 1976,
      "name": "Nebraska druids",
      "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
      "questions": [
        {
          "id": 5855,
          "name": "Florida buffalo",
          "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
          "rating": "bool",
          "kind": "standard",
          "created_at": "2016-05-04T10:45:06.131Z"
        }
      ]
    },
    {
      "id": 1977,
      "name": "Nebraska druids",
      "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
      "questions": [
        {
          "id": 5856,
          "name": "Florida buffalo",
          "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
          "rating": "bool",
          "kind": "standard",
          "created_at": "2016-05-04T10:45:06.457Z"
        }
      ]
    },
    {
      "id": 1978,
      "name": "Nebraska druids",
      "description": "Rem butcher blue bottle ex cum. Knausgaard plaid quis chambray wayfarers. Vegan laboriosam occaecati chicharrones sed selfies neque.",
      "questions": [
        {
          "id": 5857,
          "name": "Florida buffalo",
          "guidelines": "Sriracha occupy farm-to-table venmo. Semiotics quinoa drinking. Craft beer viral kinfolk. Portland mumblecore diy butcher knausgaard flexitarian tacos cold-pressed. Food truck before they sold out park biodiesel.",
          "rating": "bool",
          "kind": "standard",
          "created_at": "2016-05-04T10:45:07.035Z"
        }
      ]
    }
  ],
  "evaluation": {
    "id": 168,
    "kind": "scale"
  }
}
```

### `GET /v2/scales/2` — HTTP 200

```json
{
  "id": 2,
  "evaluation_id": 3,
  "name": "Tennessee prophets",
  "is_primary": true,
  "comment": "Quidem pork belly before they sold out non vegan. Portland lo-fi sunt dolorum raw denim similique non. Accusantium consequatur quis retro. Maiores blanditiis fap chambray vice similique intelligentsia tattooed.",
  "introduction_md": "Sapiente plaid +1 ea wes anderson mlkshk mumblecore. Eaque repellendus eveniet slow-carb.",
  "disclaimer_md": "Ugh kitsch molestiae dicta keffiyeh eius tumblr gastropub. Earum repellendus sequi tilde velit error.",
  "guidelines_md": "Wolf voluptas itaque. Sunt art party farm-to-table sapiente. Ea voluptatum voluptas culpa listicle facilis.",
  "created_at": "2017-11-22T13:41:27.957Z",
  "correction_number": 3,
  "duration": 1800,
  "manual_subscription": true,
  "languages": [
    {
      "id": 3,
      "name": "Romanian",
      "identifier": "ro",
      "created_at": "2017-11-22T13:40:59.468Z",
      "updated_at": "2017-11-22T13:41:26.139Z"
    }
  ],
  "sections": [
    {
      "id": 3,
      "name": "Wyoming ants",
      "description": "Cum messenger bag praesentium hella wes anderson tofu butcher. Xoxo pabst ut quod. Tattooed adipisci bushwick. Hammock aut accusamus salvia schlitz corporis kitsch tote bag.",
      "questions": [
        {
          "name": "Idaho rabbits",
          "id": 5,
          "questions_skills": [
            {
              "id": 9,
              "question_id": 5,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.006Z",
              "updated_at": "2017-11-22T13:41:28.006Z"
            },
            {
              "id": 10,
              "question_id": 5,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.020Z",
              "updated_at": "2017-11-22T13:41:28.020Z"
            }
          ]
        },
        {
          "name": "Oklahoma elves",
          "id": 6,
          "questions_skills": [
            {
              "id": 11,
              "question_id": 6,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.064Z",
              "updated_at": "2017-11-22T13:41:28.064Z"
            },
            {
              "id": 12,
              "question_id": 6,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.068Z",
              "updated_at": "2017-11-22T13:41:28.068Z"
            }
          ]
        }
      ]
    },
    {
      "id": 4,
      "name": "New York gooses",
      "description": "Modi polaroid odio lomo chillwave. Cold-pressed everyday quasi possimus 90's flexitarian. Fingerstache ullam quia et distillery cupiditate shoreditch tousled. Quis tousled keffiyeh debitis. Earum sunt quis repellat quasi green juice knausgaard.",
      "questions": [
        {
          "name": "Virginia ghosts",
          "id": 7,
          "questions_skills": [
            {
              "id": 13,
              "question_id": 7,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.144Z",
              "updated_at": "2017-11-22T13:41:28.144Z"
            },
            {
              "id": 14,
              "question_id": 7,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.158Z",
              "updated_at": "2017-11-22T13:41:28.158Z"
            }
          ]
        },
        {
          "name": "Idaho witches",
          "id": 8,
          "questions_skills": [
            {
              "id": 15,
              "question_id": 8,
              "skill_id": 6,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.210Z",
              "updated_at": "2017-11-22T13:41:28.210Z"
            },
            {
              "id": 16,
              "question_id": 8,
              "skill_id": 1,
              "percentage": 25,
              "created_at": "2017-11-22T13:41:28.215Z",
              "updated_at": "2017-11-22T13:41:28.215Z"
            }
          ]
        }
      ]
    }
  ],
  "evaluation": {
    "id": 3,
    "kind": "scale"
  }
}
```

### `PUT /v2/scales/2`

```
  "scale": {
    "comment": "Dolores facere letterpress. Facilis pork belly church-key rem enim ut twee.",
    "disclaimer_md": "Narwhal harum et voluptatum dolor similique minus biodiesel. Mlkshk architecto sapiente harum ipsum. Ut selvage paleo. Quia franzen listicle occupy.",
    "guidelines_md": "Ut kickstarter aut wolf harum vel cornhole stumptown. Next level semiotics ab squid sit ethical lumbersexual. Venmo aspernatur retro letterpress quae ea pickled provident. Small batch ugh quia flexitarian.",
    "introduction_md": "Amet sed sint perferendis sriracha. Thundercats consequuntur salvia. Jean shorts church-key ut enim est selvage aut. Alias cray paleo quia ea nulla five dollar toast in. Vitae eos vegan aut inventore at dolorem quo."
  }
}
204
```


## scores

### `GET /v2/scores/2` — HTTP 200

```json
{
  "id": 2,
  "coalition_id": 1,
  "scoreable_id": 5,
  "scoreable_type": "Location",
  "coalitions_user_id": 3,
  "calculation_id": 3,
  "value": 54,
  "reason": "Who's the more foolish; the fool, or the fool who follows him?",
  "created_at": "2017-11-22T13:42:09.850Z",
  "updated_at": "2017-11-22T13:42:09.850Z"
}
```


## search

### `POST /v2/search/projects`

```
  "query": "libft",
  "filter": {
    "exam": false
  },
  "range": {
    "difficulty": "0,500"
  },
  "sort": "-created_at,name",
  "page": {
    "number": 1,
    "size": 30
  }
}
200
[
  {
    "id": 1,
    "name": "Libft",
    "slug": "libft"
  }
]
```

### `POST /v2/search/users`

```
  "query": "xlogin",
  "filter": {
    "primary_campus_id": 1,
    "staff?": false
  },
  "range": {
    "created_at": "2020-01-01,2021-01-01"
  },
  "sort": "-created_at,login",
  "page": {
    "number": 1,
    "size": 30
  }
}
200
[
  {
    "id": 42,
    "login": "xlogin"
  },
  {
    "id": 51,
    "login": "xlogin2"
  }
]
```


## slots

### `DELETE /v2/slots/471` — HTTP 204

```
(no body)
```

### `GET /v2/slots/graph/on/begin_at/by/day` — HTTP 200

```json
{
  "2017-11-20": 123,
  "2017-11-21": 0,
  "2017-11-22": 0,
  "2017-11-23": 0,
  "2017-11-24": 1266
}
```

### `GET /v2/slots` — HTTP 200

```json
[
  {
    "id": 27,
    "begin_at": "2017-11-24T20:15:00.000Z",
    "end_at": "2017-11-24T20:30:00.000Z",
    "scale_team": null,
    "user": "invisible"
  },
  {
    "id": 76,
    "begin_at": "2017-11-24T20:15:00.000Z",
    "end_at": "2017-11-24T20:30:00.000Z",
    "scale_team": null,
    "user": "invisible"
  },
  {
    "id": 110,
    "begin_at": "2017-11-24T20:15:00.000Z",
    "end_at": "2017-11-24T20:30:00.000Z",
    "scale_team": null,
    "user": "invisible"
  }
]
```


## squads

### `POST /v2/blocs/:id/squads`

```
  "bloc_id": 21,
  "locked_at": null,
  "squads_users_attributes": [
    {
      "user_id": 18763,
      "leader": true,
      "validated": true
    }
  ]
}
201
{
  "id": 4934,
  "bloc_id": 21,
  "locked_at": null,
  "squads_users": [
    {
      "id": 10717,
      "squad_id": 4934,
      "leader": true,
      "validated": false,
      "created_at": "2019-11-08T13:53:26.408Z",
      "updated_at": "2019-11-08T13:53:26.408Z",
      "user": {
        "id": 18763,
        "login": "gmonein"
      }
    }
  ],
  "created_at": "2019-11-08T13:53:26.404Z",
  "updated_at": "2019-11-08T13:53:26.404Z",
  "bloc": {
    "id": 21,
    "campus_id": 22,
    "cursus_id": 21,
    "squad_size": 4,
    "created_at": "2019-10-24T23:57:59.098Z",
    "updated_at": "2019-11-06T11:15:35.845Z"
  }
}
```


## subnotions

### `POST /v2/subnotions`

```
  "subnotion": {
    "name": "By Grand Central Station I Sat Down and Wept",
    "notion_id": "1"
  }
}
201
{
  "id": 15,
  "name": "By Grand Central Station I Sat Down and Wept",
  "slug": "by-grand-central-station-i-sat-down-and-wept",
  "created_at": "2017-11-22T13:44:04.723Z",
  "notepad": null,
  "attachments": [],
  "notion": {
    "id": 1,
    "name": "42run Demo",
    "slug": "42run-demo",
    "created_at": "2017-11-22T13:41:23.730Z"
  }
}
```

### `DELETE /v2/subnotions/6` — HTTP 204

```
(no body)
```

### `GET /v2/subnotions` — HTTP 200

```json
[
  {
    "id": 10,
    "name": "Conclusion",
    "slug": "piscine-php-d08-even-moar-object-oriented-programming-conclusion",
    "created_at": "2017-11-22T13:41:24.254Z",
    "notepad": null,
    "attachments": [],
    "notion": null
  },
  {
    "id": 5,
    "name": "Cosinus",
    "slug": "fract-ol-cosinus",
    "created_at": "2017-11-22T13:41:24.204Z",
    "notepad": null,
    "attachments": [],
    "notion": null
  },
  {
    "id": 4,
    "name": "Démonstration",
    "slug": "wolf3d-demonstration",
    "created_at": "2017-11-22T13:41:24.195Z",
    "notepad": null,
    "attachments": [],
    "notion": null
  }
]
```

### `GET /v2/subnotions/6` — HTTP 200

```json
{
  "id": 6,
  "name": "Julia",
  "slug": "fract-ol-julia",
  "created_at": "2017-11-22T13:41:24.215Z",
  "notepad": null,
  "attachments": [],
  "notion": null
}
```

### `PUT /v2/subnotions/6`

```
  "subnotion": {
    "name": "By Grand Central Station I Sat Down and Wept",
    "notion_id": "2"
  }
}
204
```


## tags

### `POST /v2/tags`

```
  "tag": {
    "kind": "general",
    "name": "Legend"
  }
}
201
{
  "id": 18,
  "name": "Legend",
  "kind": "general",
  "users": [],
  "subnotions": []
}
```

### `DELETE /v2/tags/6` — HTTP 204

```
(no body)
```

### `GET /v2/tags` — HTTP 200

```json
[
  {
    "id": 11,
    "name": "Archived",
    "kind": "archived",
    "users": [],
    "subnotions": []
  },
  {
    "id": 7,
    "name": "Bocal",
    "kind": "general",
    "users": [],
    "subnotions": [
      {
        "id": 1,
        "name": "Emacs",
        "slug": "piscine-c-text-editors-emacs",
        "created_at": "2017-11-22T13:41:24.154Z",
        "notepad": null
      }
    ]
  },
  {
    "id": 4,
    "name": "Colle 08",
    "kind": "project",
    "users": [],
    "subnotions": []
  }
]
```

### `GET /v2/tags/6` — HTTP 200

```json
{
  "id": 6,
  "name": "Jour 13",
  "kind": "project",
  "users": [],
  "subnotions": []
}
```

### `PUT /v2/tags/6`

```
  "tag": {
    "kind": "general",
    "name": "Legend"
  }
}
204
```


## teams

### `POST /v2/teams`

```
  "team": {
    "name": "Awesome team",
    "project_id": 688,
    "teams_users_attributes": [
      {
        "user_id": 17282,
        "leader": true
      },
      {
        "user_id": 18668
      },
      {
        "user_id": 15646
      },
      {
        "user_id": 12293
      },
      {
        "user_id": 17241
      }
    ]
  }
}
201
{
  "closed?": false,
  "closed_at": null,
  "created_at": "2019-01-29T13:46:58.977Z",
  "final_mark": null,
  "id": 2368475,
  "locked?": false,
  "locked_at": null,
  "name": "soin",
  "project_id": 688,
  "project_session_id": 431,
  "repo_url": null,
  "repo_uuid": "intra-uuid-ed68a876-be55-42ff-af85-43826f014fb5-2368475",
  "scale_teams": [],
  "status": "creating_group",
  "teams_uploads": [],
  "terminating_at": null,
  "updated_at": "2019-01-29T13:46:59.104Z",
  "url": "http://localhost:13000/v2/teams/2368475",
  "users": [
    {
      "id": 12293,
      "leader": false,
      "login": "mcanal",
      "occurrence": 0,
      "projects_user_id": 824439,
      "url": "http://localhost:13000/v2/users/mcanal",
      "validated": false
    },
    {
      "id": 15646,
      "leader": false,
      "login": "qduperon",
      "occurrence": 0,
      "projects_user_id": 802915,
      "url": "http://localhost:13000/v2/users/qduperon",
      "validated": false
    },
    {
      "id": 17241,
      "leader": false,
      "login": "mmoullec",
      "occurrence": 0,
      "projects_user_id": 1149166,
      "url": "http://localhost:13000/v2/users/mmoullec",
      "validated": false
    },
    {
      "id": 17282,
      "leader": true,
      "login": "thifranc",
      "occurrence": 0,
      "projects_user_id": 1149194,
      "url": "http://localhost:13000/v2/users/thifranc",
      "validated": false
    },
    {
      "id": 18668,
      "leader": false,
      "login": "jlasne",
      "occurrence": 0,
      "projects_user_id": 1097141,
      "url": "http://localhost:13000/v2/users/jlasne",
      "validated": false
    }
  ],
  "validated?": null
}
```

### `DELETE /v2/teams/58` — HTTP 204

```
(no body)
```

### `GET /v2/teams/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 68
}
```

### `GET /v2/teams` — HTTP 200

```json
[
  {
    "id": 1,
    "name": "jabinks2's group",
    "url": "https://api.intra.42.fr/v2/teams/1",
    "final_mark": null,
    "project_id": 2,
    "created_at": "2017-11-22T13:41:28.447Z",
    "updated_at": "2017-11-22T13:41:28.519Z",
    "status": "in_progress",
    "terminating_at": null,
    "users": [
      {
        "id": 111,
        "login": "coundook",
        "url": "https://api.intra.42.fr/v2/users/coundook",
        "leader": true,
        "occurrence": 0,
        "validated": true,
        "projects_user_id": 1
      }
    ],
    "locked?": true,
    "validated?": null,
    "closed?": false,
    "repo_url": null,
    "repo_uuid": "intra-uuid-e8f23ddc-8e52-47a8-87e9-9bd490621cfd-1",
    "locked_at": "2017-11-22T13:41:28.487Z",
    "closed_at": null,
    "project_session_id": 2,
    "scale_teams": [],
    "teams_uploads": []
  },
  {
    "id": 2,
    "name": "podamer2's group",
    "url": "https://api.intra.42.fr/v2/teams/2",
    "final_mark": null,
    "project_id": 4,
    "created_at": "2017-11-22T13:41:28.554Z",
    "updated_at": "2017-11-22T13:41:28.608Z",
    "status": "in_progress",
    "terminating_at": null,
    "users": [
      {
        "id": 108,
        "login": "podamer2",
        "url": "https://api.intra.42.fr/v2/users/podamer2",
        "leader": true,
        "occurrence": 0,
        "validated": true,
        "projects_user_id": 2
      }
    ],
    "locked?": false,
    "validated?": null,
    "closed?": true,
    "repo_url": null,
    "repo_uuid": "intra-uuid-ae9bdbbc-9c16-4c27-8f18-eccee5a31020-2",
    "locked_at": null,
    "closed_at": "2017-11-22T13:41:28.578Z",
    "project_session_id": 4,
    "scale_teams": [],
    "teams_uploads": []
  },
  {
    "id": 3,
    "name": "podamer2's group",
    "url": "https://api.intra.42.fr/v2/teams/3",
    "final_mark": null,
    "project_id": 5,
    "created_at": "2017-11-22T13:41:28.661Z",
    "updated_at": "2017-11-22T13:41:28.704Z",
    "status": "creating_group",
    "terminating_at": null,
    "users": [
      {
        "id": 108,
        "login": "podamer2",
        "url": "https://api.intra.42.fr/v2/users/podamer2",
        "leader": true,
        "occurrence": 0,
        "validated": true,
        "projects_user_id": 3
      }
    ],
    "locked?": false,
    "validated?": null,
    "closed?": false,
    "repo_url": null,
    "repo_uuid": "intra-uuid-d6aded82-d02e-4597-a33a-acd2544ec015-3",
    "locked_at": null,
    "closed_at": null,
    "project_session_id": 5,
    "scale_teams": [],
    "teams_uploads": []
  }
]
```

### `PUT /v2/teams/58`

```
  "team": {
    "origin_user_id": "125",
    "project_id": "5"
  }
}
204
```


## teams_uploads

### `POST /v2/teams_uploads`

```
  "teams_upload": {
    "comment": "The Other Side of Silence",
    "final_mark": "42",
    "team_id": "66",
    "upload_id": "1"
  }
}
201
{
  "id": 2,
  "final_mark": 42,
  "comment": "The Other Side of Silence",
  "created_at": "2017-11-22T13:44:07.389Z",
  "upload_id": 1,
  "upload": {
    "id": 1,
    "evaluation_id": 2,
    "name": "Idaho kangaroos",
    "description": "",
    "created_at": "2017-11-22T13:41:26.168Z",
    "updated_at": "2017-11-22T13:44:07.391Z"
  }
}
```

### `DELETE /v2/teams_uploads/1` — HTTP 204

```
(no body)
```

### `GET /v2/teams_uploads` — HTTP 200

```json
[
  {
    "id": 1,
    "final_mark": 55,
    "comment": "Fingerstache street 8-bit viral meditation banh mi xoxo keytar. Quinoa retro ugh organic kickstarter vegan loko disrupt. Cold-pressed keffiyeh retro.",
    "created_at": "2017-11-22T13:42:09.325Z",
    "upload_id": 1,
    "upload": {
      "id": 1,
      "evaluation_id": 2,
      "name": "Idaho kangaroos",
      "description": "",
      "created_at": "2017-11-22T13:41:26.168Z",
      "updated_at": "2017-11-22T13:42:09.328Z"
    }
  }
]
```

### `GET /v2/teams_uploads/1` — HTTP 200

```json
{
  "id": 1,
  "final_mark": 55,
  "comment": "Fingerstache street 8-bit viral meditation banh mi xoxo keytar. Quinoa retro ugh organic kickstarter vegan loko disrupt. Cold-pressed keffiyeh retro.",
  "created_at": "2017-11-22T13:42:09.325Z",
  "upload_id": 1,
  "upload": {
    "id": 1,
    "evaluation_id": 2,
    "name": "Idaho kangaroos",
    "description": "",
    "created_at": "2017-11-22T13:41:26.168Z",
    "updated_at": "2017-11-22T13:42:09.328Z"
  }
}
```

### `PUT /v2/teams_uploads/1`

```
  "teams_upload": {
    "comment": "The Other Side of Silence",
    "final_mark": "42",
    "team_id": "18",
    "upload_id": "1"
  }
}
204
```


## teams_users

### `POST /v2/teams_users`

```
  "teams_user": {
    "leader": "false",
    "occurrence": "1",
    "team_id": "68",
    "user_id": "126",
    "validated": "false"
  }
}
201
{
  "id": 71,
  "team_id": 68,
  "user_id": 126,
  "created_at": "2017-11-22T13:44:08.492Z",
  "validated": false,
  "leader": false,
  "occurrence": 0,
  "team": {
    "id": 68,
    "name": "sebulseb's group",
    "url": "https://api.intra.42.fr/v2/teams/68",
    "final_mark": null,
    "project_id": 1,
    "created_at": "2017-11-22T13:41:37.418Z",
    "updated_at": "2017-11-22T13:44:08.496Z",
    "status": "waiting_for_correction",
    "terminating_at": null,
    "users": [
      {
        "id": 125,
        "login": "sebulseb",
        "url": "https://api.intra.42.fr/v2/users/sebulseb",
        "leader": true,
        "occurrence": 0,
        "validated": true,
        "projects_user_id": 68
      },
      {
        "id": 126,
        "login": "anakskyw",
        "url": "https://api.intra.42.fr/v2/users/anakskyw",
        "leader": false,
        "occurrence": 0,
        "validated": false,
        "projects_user_id": 70
      }
    ],
    "locked?": true,
    "validated?": null,
    "closed?": true,
    "repo_url": null,
    "repo_uuid": "intra-uuid-5af5ca8d-e0dc-4791-9cfc-ed657e1984e0-68",
    "locked_at": "2017-11-22T13:41:37.471Z",
    "closed_at": "2017-11-22T13:41:37.496Z",
    "project_session_id": 1
  },
  "user": {
    "id": 126,
    "login": "darthcae",
    "url": "https://api.intra.42.fr/v2/users/darthcae"
  }
}
```

### `DELETE /v2/teams_users/3` — HTTP 204

```
(no body)
```

### `GET /v2/teams_users` — HTTP 200

```json
[
  {
    "id": 68,
    "team_id": 68,
    "user_id": 125,
    "created_at": "2017-11-22T13:41:37.430Z",
    "validated": true,
    "leader": true,
    "occurrence": 0,
    "team": {
      "id": 68,
      "name": "sebulseb's group",
      "url": "https://api.intra.42.fr/v2/teams/68",
      "final_mark": null,
      "project_id": 1,
      "created_at": "2017-11-22T13:41:37.418Z",
      "updated_at": "2017-11-22T13:42:09.246Z",
      "status": "waiting_for_correction",
      "terminating_at": null,
      "users": [
        {
          "id": 125,
          "login": "sebulseb",
          "url": "https://api.intra.42.fr/v2/users/sebulseb",
          "leader": true,
          "occurrence": 0,
          "validated": true,
          "projects_user_id": 68
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": true,
      "repo_url": null,
      "repo_uuid": "intra-uuid-5af5ca8d-e0dc-4791-9cfc-ed657e1984e0-68",
      "locked_at": "2017-11-22T13:41:37.471Z",
      "closed_at": "2017-11-22T13:41:37.496Z",
      "project_session_id": 1
    },
    "user": {
      "id": 125,
      "login": "sebulseb",
      "url": "https://api.intra.42.fr/v2/users/sebulseb"
    }
  },
  {
    "id": 67,
    "team_id": 67,
    "user_id": 119,
    "created_at": "2017-11-22T13:41:37.310Z",
    "validated": true,
    "leader": true,
    "occurrence": 0,
    "team": {
      "id": 67,
      "name": "hasolo's group",
      "url": "https://api.intra.42.fr/v2/teams/67",
      "final_mark": null,
      "project_id": 1,
      "created_at": "2017-11-22T13:41:37.298Z",
      "updated_at": "2017-11-22T13:41:37.386Z",
      "status": "waiting_for_correction",
      "terminating_at": null,
      "users": [
        {
          "id": 119,
          "login": "hasolo",
          "url": "https://api.intra.42.fr/v2/users/hasolo",
          "leader": true,
          "occurrence": 0,
          "validated": true,
          "projects_user_id": 67
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": true,
      "repo_url": null,
      "repo_uuid": "intra-uuid-4c9b8f90-9b63-4b8a-b919-4e0d664544c2-67",
      "locked_at": "2017-11-22T13:41:37.358Z",
      "closed_at": "2017-11-22T13:41:37.385Z",
      "project_session_id": 1
    },
    "user": {
      "id": 119,
      "login": "hasolo",
      "url": "https://api.intra.42.fr/v2/users/hasolo"
    }
  },
  {
    "id": 66,
    "team_id": 66,
    "user_id": 118,
    "created_at": "2017-11-22T13:41:37.187Z",
    "validated": true,
    "leader": true,
    "occurrence": 0,
    "team": {
      "id": 66,
      "name": "jarbink2's group",
      "url": "https://api.intra.42.fr/v2/teams/66",
      "final_mark": null,
      "project_id": 1,
      "created_at": "2017-11-22T13:41:37.174Z",
      "updated_at": "2017-11-22T13:41:37.263Z",
      "status": "waiting_for_correction",
      "terminating_at": null,
      "users": [
        {
          "id": 118,
          "login": "padamida",
          "url": "https://api.intra.42.fr/v2/users/padamida",
          "leader": true,
          "occurrence": 0,
          "validated": true,
          "projects_user_id": 66
        }
      ],
      "locked?": true,
      "validated?": null,
      "closed?": true,
      "repo_url": null,
      "repo_uuid": "intra-uuid-5f077c0e-351b-4d77-8334-dac656e42798-66",
      "locked_at": "2017-11-22T13:41:37.238Z",
      "closed_at": "2017-11-22T13:41:37.262Z",
      "project_session_id": 1
    },
    "user": {
      "id": 118,
      "login": "jarbink2",
      "url": "https://api.intra.42.fr/v2/users/jarbink2"
    }
  }
]
```

### `GET /v2/teams_users/3` — HTTP 200

```json
{
  "id": 3,
  "team_id": 3,
  "user_id": 108,
  "created_at": "2017-11-22T13:41:28.680Z",
  "validated": true,
  "leader": true,
  "occurrence": 0,
  "team": {
    "id": 3,
    "name": "podamer2's group",
    "url": "https://api.intra.42.fr/v2/teams/3",
    "final_mark": null,
    "project_id": 5,
    "created_at": "2017-11-22T13:41:28.661Z",
    "updated_at": "2017-11-22T13:41:28.704Z",
    "status": "creating_group",
    "terminating_at": null,
    "users": [
      {
        "id": 108,
        "login": "podamer2",
        "url": "https://api.intra.42.fr/v2/users/podamer2",
        "leader": true,
        "occurrence": 0,
        "validated": true,
        "projects_user_id": 3
      }
    ],
    "locked?": false,
    "validated?": null,
    "closed?": false,
    "repo_url": null,
    "repo_uuid": "intra-uuid-d6aded82-d02e-4597-a33a-acd2544ec015-3",
    "locked_at": null,
    "closed_at": null,
    "project_session_id": 5
  },
  "user": {
    "id": 108,
    "login": "podamer2",
    "url": "https://api.intra.42.fr/v2/users/podamer2"
  }
}
```

### `PUT /v2/teams_users/3`

```
  "teams_user": {
    "leader": "false",
    "occurrence": "1",
    "team_id": "68",
    "user_id": "126",
    "validated": "false"
  }
}
204
```


## transactions

### `POST /v2/transactions`

```
  "transaction": {
    "value": 5,
    "user_id": 123,
    "transactable_type": "Tuteur api",
    "reason": "cadeau"
  }
}
201
{
  "id": 6,
  "value": 5,
  "user_id": 123,
  "transactable_id": null,
  "transactable_type": "Tuteur api",
  "reason": "cadeau",
  "user": {
    "id": 123,
    "login": "jeanne",
    "url": "https://api.intra.42.fr/v2/users/jeanne"
  }
}
```

### `GET /v2/transactions?page=1` — HTTP 200

```json
[
  {
    "id": 1,
    "value": 150,
    "user_id": 22,
    "transactable_id": 81,
    "transactable_type": "Achievement",
    "reason": "Mathieu c'est le plus fort ♥️",
    "user": {
      "id": 22,
      "login": "mathieu",
      "url": "https://api.intra.42.fr/v2/users/mathieu"
    }
  },
  {
    "id": 2,
    "value": 666,
    "user_id": 123,
    "transactable_id": 186,
    "transactable_type": "Event",
    "reason": "Réunion entre démons.",
    "user": {
      "id": 123,
      "login": "jeanne",
      "url": "https://api.intra.42.fr/v2/users/jeanne"
    }
  },
  {
    "id": 2,
    "value": 1,
    "user_id": 12837,
    "transactable_id": null,
    "transactable_type": "Tuteur api",
    "reason": "Exam C 24 janvier",
    "user": {
      "id": 12837,
      "login": "jbailhac",
      "url": "https://api.intra.42.fr/v2/users/jbailhac"
    }
  }
]
```

### `GET /v2/transactions/1` — HTTP 200

```json
{
  "id": 1,
  "value": 150,
  "user_id": 22,
  "transactable_id": 81,
  "transactable_type": "Achievement",
  "reason": "Mathieu c'est le plus fort ♥️",
  "user": {
    "id": 22,
    "login": "mathieu",
    "url": "https://api.intra.42.fr/v2/users/mathieu"
  }
}
```


## translations

### `POST /v2/translations`

```
  "translation": {
    "fields": "{\"description\":\"You passed the Piscine test. Welcome to 42!\"}",
    "language_id": "3",
    "translatable_id": "1",
    "translatable_type": "Achievement"
  }
}
201
{
  "id": 99,
  "translatable_id": 1,
  "translatable_type": "Achievement",
  "language_id": 3,
  "fields": "{\"description\":\"You passed the Piscine test. Welcome to 42!\"}",
  "created_at": "2017-11-22T13:44:17.382Z",
  "updated_at": "2017-11-22T13:44:17.382Z",
  "user_id": null,
  "default": false,
  "up_to_date": true,
  "translations_structure_id": 6,
  "translations_structure": {
    "id": 6,
    "searchable_by": [
      "name"
    ],
    "identified_by": [
      "name"
    ],
    "structures_kind": "simple",
    "up_to_date": true,
    "fields_organisation": {
      "name": "string",
      "description": "string"
    },
    "type_name": "Achievement",
    "created_at": "2017-11-22T13:40:59.398Z",
    "updated_at": "2017-11-22T13:40:59.398Z"
  }
}
```

### `DELETE /v2/translations/3` — HTTP 204

```
(no body)
```

### `GET /v2/translations` — HTTP 200

```json
[
  {
    "id": 1,
    "translatable_id": 1,
    "translatable_type": "Tag",
    "language_id": 2,
    "fields": {
      "name": "Joburg-Final-Exam",
      "description": null
    },
    "created_at": "2017-11-22T13:40:59.699Z",
    "updated_at": "2017-11-22T13:40:59.716Z",
    "user_id": null,
    "default": true,
    "up_to_date": true,
    "translations_structure_id": 11,
    "translations_structure": {
      "id": 11,
      "searchable_by": [
        "name"
      ],
      "identified_by": [
        "name"
      ],
      "structures_kind": "simple",
      "up_to_date": true,
      "fields_organisation": {
        "name": "string",
        "description": "text"
      },
      "type_name": "Tag",
      "created_at": "2017-11-22T13:40:59.444Z",
      "updated_at": "2017-11-22T13:40:59.444Z"
    }
  },
  {
    "id": 2,
    "translatable_id": 2,
    "translatable_type": "Tag",
    "language_id": 2,
    "fields": {
      "name": "Friends with Benefits",
      "description": null
    },
    "created_at": "2017-11-22T13:40:59.747Z",
    "updated_at": "2017-11-22T13:40:59.759Z",
    "user_id": null,
    "default": true,
    "up_to_date": true,
    "translations_structure_id": 11,
    "translations_structure": {
      "id": 11,
      "searchable_by": [
        "name"
      ],
      "identified_by": [
        "name"
      ],
      "structures_kind": "simple",
      "up_to_date": true,
      "fields_organisation": {
        "name": "string",
        "description": "text"
      },
      "type_name": "Tag",
      "created_at": "2017-11-22T13:40:59.444Z",
      "updated_at": "2017-11-22T13:40:59.444Z"
    }
  },
  {
    "id": 3,
    "translatable_id": 3,
    "translatable_type": "Tag",
    "language_id": 2,
    "fields": {
      "name": "GBmu",
      "description": null
    },
    "created_at": "2017-11-22T13:40:59.783Z",
    "updated_at": "2017-11-22T13:40:59.795Z",
    "user_id": null,
    "default": true,
    "up_to_date": true,
    "translations_structure_id": 11,
    "translations_structure": {
      "id": 11,
      "searchable_by": [
        "name"
      ],
      "identified_by": [
        "name"
      ],
      "structures_kind": "simple",
      "up_to_date": true,
      "fields_organisation": {
        "name": "string",
        "description": "text"
      },
      "type_name": "Tag",
      "created_at": "2017-11-22T13:40:59.444Z",
      "updated_at": "2017-11-22T13:40:59.444Z"
    }
  }
]
```

### `GET /v2/translations/3` — HTTP 200

```json
{
  "id": 3,
  "translatable_id": 3,
  "translatable_type": "Tag",
  "language_id": 2,
  "fields": {
    "name": "GBmu",
    "description": null
  },
  "created_at": "2017-11-22T13:40:59.783Z",
  "updated_at": "2017-11-22T13:40:59.795Z",
  "user_id": null,
  "default": true,
  "up_to_date": true,
  "translations_structure_id": 11,
  "translations_structure": {
    "id": 11,
    "searchable_by": [
      "name"
    ],
    "identified_by": [
      "name"
    ],
    "structures_kind": "simple",
    "up_to_date": true,
    "fields_organisation": {
      "name": "string",
      "description": "text"
    },
    "type_name": "Tag",
    "created_at": "2017-11-22T13:40:59.444Z",
    "updated_at": "2017-11-22T13:40:59.444Z"
  }
}
```

### `PUT /v2/translations/3`

```
  "translation": {
    "fields": "{\"description\":\"You passed the Piscine test. Welcome to 42!\"}",
    "language_id": "1",
    "translatable_id": "1",
    "translatable_type": "Achievement"
  }
}
204
```


## user_candidatures

### `POST /v2/user_candidatures`

```
  "user_candidature": {
    "birth_city": "West Stefanieburgh",
    "birth_country": "Burkina Faso",
    "birth_date": "1989-01-30",
    "contact_affiliation": "other",
    "contact_first_name": "Barton",
    "contact_last_name": "Mertz",
    "contact_phone1": "0695847362",
    "contact_phone2": "0491314200",
    "country": "Honduras",
    "gender": "female",
    "language": "",
    "max_level_logic": "2",
    "max_level_memory": "1",
    "meeting_date": "2017-07-11",
    "other_information": "3",
    "pin": "4242",
    "piscine_date": "2017-11-15",
    "postal_city": "Tillmanton",
    "postal_complement": "",
    "postal_country": "Georgia",
    "postal_street": "5030 Serenity Plaza",
    "postal_zip_code": "65440",
    "user_id": "9",
    "zip_code": "37528-3874"
  }
}
201
{
  "id": 127,
  "user_id": 9,
  "birth_date": "1989-01-30",
  "gender": "female",
  "zip_code": "37528-3874",
  "country": "Honduras",
  "birth_city": "West Stefanieburgh",
  "birth_country": "Burkina Faso",
  "postal_street": "5030 Serenity Plaza",
  "postal_complement": "",
  "postal_city": "Tillmanton",
  "postal_zip_code": "65440",
  "postal_country": "Georgia",
  "contact_affiliation": "other",
  "contact_last_name": "Mertz",
  "contact_first_name": "Barton",
  "contact_phone1": "0695847362",
  "contact_phone2": "0491314200",
  "max_level_memory": 1,
  "max_level_logic": 2,
  "other_information": "3",
  "language": "",
  "meeting_date": "2017-07-11T00:00:00.000Z",
  "piscine_date": "2017-11-15",
  "created_at": "2017-11-22T13:44:17.725Z",
  "updated_at": "2017-11-22T13:44:17.725Z",
  "phone": null,
  "email": null,
  "pin": "4242",
  "phone_country_code": null,
  "hidden_phone": null
}
```

### `GET /v2/user_candidatures/23` — HTTP 200

```json
{
  "id": 23,
  "user_id": 23,
  "birth_date": "1993-05-04",
  "gender": "male",
  "zip_code": "71800-2563",
  "country": "Kashyyyk",
  "birth_city": "East Rosieland",
  "birth_country": "Kamino",
  "postal_street": "11747 Jerod Drives",
  "postal_complement": null,
  "postal_city": "Keagantown",
  "postal_zip_code": null,
  "postal_country": null,
  "contact_affiliation": null,
  "contact_last_name": null,
  "contact_first_name": null,
  "contact_phone1": null,
  "contact_phone2": null,
  "max_level_memory": null,
  "max_level_logic": null,
  "other_information": null,
  "language": null,
  "meeting_date": null,
  "piscine_date": null,
  "created_at": "2017-11-22T13:41:06.408Z",
  "updated_at": "2017-11-22T13:41:06.408Z",
  "phone": null,
  "email": "[email protected]",
  "pin": null,
  "phone_country_code": null,
  "hidden_phone": null
}
```

### `PUT /v2/user_candidatures/23`

```
  "user_candidature": {
    "birth_city": "Port Gonzalo",
    "birth_country": "Iceland",
    "birth_date": "1992-02-29",
    "contact_affiliation": "parent",
    "contact_first_name": "Lily",
    "contact_last_name": "Buckridge",
    "contact_phone1": "0695847362",
    "contact_phone2": "0491314200",
    "country": "Antarctica (the territory South of 60 deg S)",
    "gender": "female",
    "language": "",
    "max_level_logic": "2",
    "max_level_memory": "1",
    "meeting_date": "2017-01-06",
    "other_information": "3",
    "pin": "4242",
    "piscine_date": "2017-11-06",
    "postal_city": "Lake Montana",
    "postal_complement": "",
    "postal_country": "Lao People's Democratic Republic",
    "postal_street": "7646 Constantin Green",
    "postal_zip_code": "19921",
    "user_id": "46",
    "zip_code": "91297"
  }
}
204
```


## users

### `POST /v2/users`

```
  "user": {
    "campus_id": "1",
    "cursus_users_attributes": [
      {
        "begin_at": "2017-11-25 13:44:19 UTC",
        "cursus_id": "1",
        "end_at": "2018-03-22 13:43:10 UTC",
        "user_id": ""
      }
    ],
    "email": "[email protected]",
    "first_name": "Anakin",
    "kind": "student",
    "languages_users_attributes": [
      {
        "language_id": "1",
        "position": "1",
        "user_id": ""
      }
    ],
    "last_name": "Skywalker",
    "password": "totoroTOTOROOO",
    "pool_month": "may",
    "pool_year": "2017",
    "status": "admis",
    "user_candidature_attributes": {
      "birth_city": "East Adrainshire",
      "birth_country": "Iran",
      "birth_date": "1998-06-08",
      "contact_affiliation": "parent",
      "contact_first_name": "Dewayne",
      "contact_last_name": "Nader",
      "contact_phone1": "0695847362",
      "contact_phone2": "0491314200",
      "country": "Turks and Caicos Islands",
      "gender": "female",
      "language": "",
      "max_level_logic": "2",
      "max_level_memory": "1",
      "meeting_date": "2017-10-05",
      "other_information": "3",
      "pin": "4242",
      "piscine_date": "2017-11-15",
      "postal_city": "Emelyborough",
      "postal_complement": "",
      "postal_country": "Lesotho",
      "postal_street": "621 Tromp Lakes",
      "postal_zip_code": "10047",
      "user_id": "",
      "zip_code": "89457-3613"
    }
  }
}
201
{
  "id": 127,
  "login": "anakisky",
  "url": "https://api.intra.42.fr/v2/users/anakisky"
}
```

### `POST /v2/users/:id/free_past_agu`

```
  "duration": 2,
  "reason": "optional"
}
200
```

### `GET /v2/users/graph/on/created_at/by/day` — HTTP 200

```json
{
  "2017-11-22": 126
}
```

### `GET /v2/users` — HTTP 200

```json
[
  {
    "id": 39962,
    "email": "[email protected]",
    "login": "malallai",
    "first_name": "Malo",
    "last_name": "Allain",
    "usual_full_name": "Malo Allain",
    "usual_first_name": null,
    "url": "https://api.intra.42.fr/v2/users/malallai",
    "phone": "hidden",
    "displayname": "Malo Allain",
    "kind": "student",
    "image": {
      "link": "https://cdn.intra.42.fr/users/39a641ed152b654cfbff5c5864eb05c1/malallai.jpg",
      "versions": {
        "large": "https://cdn.intra.42.fr/users/a818d7a54298d333411557d0b55b61b3/large_malallai.jpg",
        "medium": "https://cdn.intra.42.fr/users/53691acd1e0ea75b782ddbe121c17423/medium_malallai.jpg",
        "small": "https://cdn.intra.42.fr/users/617de91b59fd7e59ecaf6470a4b37645/small_malallai.jpg",
        "micro": "https://cdn.intra.42.fr/users/6f74b46e2016b0e6c41fa05b5952e17c/micro_malallai.jpg"
      }
    },
    "staff?": false,
    "correction_point": 4,
    "pool_month": "august",
    "pool_year": "2018",
    "location": null,
    "wallet": 290,
    "anonymize_date": "2025-10-24T00:00:00.000+02:00",
    "data_erasure_date": "2025-10-24T00:00:00.000+02:00",
    "created_at": "2018-07-17T08:57:33.128Z",
    "updated_at": "2022-09-27T18:48:28.207Z",
    "alumnized_at": null,
    "alumni?": false,
    "active?": true
  },
  {
    "id": 26134,
    "email": "[email protected]",
    "login": "asandolo",
    "first_name": "Alexandre",
    "last_name": "Sandolo",
    "usual_full_name": "Alexandre Sandolo",
    "usual_first_name": null,
    "url": "https://api.intra.42.fr/v2/users/asandolo",
    "phone": "hidden",
    "displayname": "Alexandre Sandolo",
    "kind": "student",
    "image": {
      "link": "https://cdn.intra.42.fr/users/e6ad4cc0cd6b69c9f18cf7fb8fefda22/asandolo.jpg",
      "versions": {
        "large": "https://cdn.intra.42.fr/users/5100f27887ee3dc6c864b618ddb44b1f/large_asandolo.jpg",
        "medium": "https://cdn.intra.42.fr/users/df044745577b908566f1cdca3e927c23/medium_asandolo.jpg",
        "small": "https://cdn.intra.42.fr/users/2946d4da689a314b6ef6f090ce724a1b/small_asandolo.jpg",
        "micro": "https://cdn.intra.42.fr/users/ff75319aa7fa4332336edf9216c51e0d/micro_asandolo.jpg"
      }
    },
    "staff?": false,
    "correction_point": 4,
    "pool_month": "july",
    "pool_year": "2017",
    "location": null,
    "wallet": 1776,
    "anonymize_date": "2025-10-11T00:00:00.000+02:00",
    "data_erasure_date": "2025-10-11T00:00:00.000+02:00",
    "created_at": "2017-06-22T11:42:39.426Z",
    "updated_at": "2022-09-27T19:20:19.605Z",
    "alumnized_at": null,
    "alumni?": false,
    "active?": true
  },
  {
    "id": 20152,
    "email": "[email protected]",
    "login": "clabouri",
    "first_name": "Charles",
    "last_name": "Labourier",
    "usual_full_name": "Charles Labourier",
    "usual_first_name": null,
    "url": "https://api.intra.42.fr/v2/users/clabouri",
    "phone": "hidden",
    "displayname": "Charles Labourier",
    "kind": "student",
    "image": {
      "link": "https://cdn.intra.42.fr/users/17dd9c4ee21baf1e2b259e8de08adee2/clabouri.jpg",
      "versions": {
        "large": "https://cdn.intra.42.fr/users/d310252790c850b2fa3158ad4d97ac17/large_clabouri.jpg",
        "medium": "https://cdn.intra.42.fr/users/07b3b6ef492df6ed2148b5c6f4fb5f7d/medium_clabouri.jpg",
        "small": "https://cdn.intra.42.fr/users/a28d995d70d99b439cbcf38852b197a1/small_clabouri.jpg",
        "micro": "https://cdn.intra.42.fr/users/de2ebeba74c5ff018f47f124cb84568b/micro_clabouri.jpg"
      }
    },
    "staff?": false,
    "correction_point": 3,
    "pool_month": "august",
    "pool_year": "2016",
    "location": null,
    "wallet": 525,
    "anonymize_date": null,
    "data_erasure_date": null,
    "created_at": "2016-07-19T15:43:15.282Z",
    "updated_at": "2022-09-19T15:36:06.910Z",
    "alumnized_at": "2021-09-28T17:06:21.597Z",
    "alumni?": true,
    "active?": true
  },
  {
    "id": 14819,
    "email": "[email protected]",
    "login": "nkrouglo",
    "first_name": "Natalia",
    "last_name": "Krouglov",
    "usual_full_name": "Natalia Krouglov",
    "usual_first_name": null,
    "url": "https://api.intra.42.fr/v2/users/nkrouglo",
    "phone": "hidden",
    "displayname": "Natalia Krouglov",
    "kind": "student",
    "image": {
      "link": "https://cdn.intra.42.fr/users/04fc6c399a81d114bd479dc3a5b90ea4/nkrouglo.jpg",
      "versions": {
        "large": "https://cdn.intra.42.fr/users/594b01edc55f87bf4918a861823cc448/large_nkrouglo.jpg",
        "medium": "https://cdn.intra.42.fr/users/3b1dc67a9b58c7e8b8bd072fa9c4aa6e/medium_nkrouglo.jpg",
        "small": "https://cdn.intra.42.fr/users/2a8263df5f95515917148068fa82eb3f/small_nkrouglo.jpg",
        "micro": "https://cdn.intra.42.fr/users/7e52b8f556ada1e2cf23d5c6d6515094/micro_nkrouglo.jpg"
      }
    },
    "staff?": false,
    "correction_point": 3,
    "pool_month": "july",
    "pool_year": "2015",
    "location": null,
    "wallet": 240,
    "anonymize_date": "2024-01-08T00:00:00.000+01:00",
    "data_erasure_date": "2024-01-08T00:00:00.000+01:00",
    "created_at": "2016-01-20T00:38:39.938Z",
    "updated_at": "2022-09-19T15:35:56.534Z",
    "alumnized_at": null,
    "alumni?": false,
    "active?": false
  }
]
```

### `GET /v2/users/xlogin/locations_stats` — HTTP 200

```json
{
  "2021-03-17": "02:56:21.097917",
  "2021-03-13": "02:20:35.738681",
  "2021-03-10": "03:23:36.453802",
  "2021-03-09": "04:40:36.89249",
  "2021-03-06": "04:51:22.499393",
  "2021-03-05": "06:05:59.372873",
  "2021-03-03": "00:21:53.590291",
  "2021-02-27": "03:05:36.994655",
  "2021-02-26": "05:16:55.007148",
  "2021-02-25": "04:36:29.373432",
  "2021-02-24": "04:49:50.382865",
  "2021-02-23": "05:58:58.220621",
  "2021-02-20": "04:12:54.190362",
  "2021-02-19": "06:44:53.740148",
  "2021-02-18": "03:20:40.099337",
  "2021-02-17": "04:28:59.221241",
  "2021-02-11": "02:58:40.99942",
  "2021-01-20": "01:49:22.04"
}
```

### `GET /v2/me` — HTTP 200

```json
{
  "id": 2,
  "email": "[email protected]",
  "login": "andre",
  "first_name": "André",
  "last_name": "Aubin",
  "usual_full_name": "Juliette Aubin",
  "usual_first_name": "Juliette",
  "url": "https://api.intra.42.fr/v2/users/andre",
  "phone": null,
  "displayname": "André Aubin",
  "kind": "admin",
  "image": {
    "link": "https://cdn.intra.42.fr/users/1234567890/andre.jpg",
    "versions": {
      "large": "https://cdn.intra.42.fr/users/1234567890/large_andre.jpg",
      "medium": "https://cdn.intra.42.fr/users/1234567890/medium_andre.jpg",
      "small": "https://cdn.intra.42.fr/users/1234567890/small_andre.jpg",
      "micro": "https://cdn.intra.42.fr/users/1234567890/micro_andre.jpgg"
    }
  },
  "staff?": false,
  "correction_point": 4,
  "pool_month": "july",
  "pool_year": "2016",
  "location": null,
  "wallet": 0,
  "anonymize_date": "2021-02-20T00:00:00.000+03:00",
  "data_erasure_date": null,
  "alumni?": false,
  "active?": true,
  "groups": [],
  "cursus_users": [
    {
      "id": 2,
      "begin_at": "2017-05-14T21:37:50.172Z",
      "end_at": null,
      "grade": null,
      "level": 0.0,
      "skills": [],
      "cursus_id": 1,
      "has_coalition": true,
      "user": {
        "id": 2,
        "login": "andre",
        "url": "https://api.intra.42.fr/v2/users/andre"
      },
      "cursus": {
        "id": 1,
        "created_at": "2017-11-22T13:41:00.750Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      }
    }
  ],
  "projects_users": [],
  "languages_users": [
    {
      "id": 2,
      "language_id": 3,
      "user_id": 2,
      "position": 1,
      "created_at": "2017-11-22T13:41:03.638Z"
    }
  ],
  "achievements": [],
  "titles": [],
  "titles_users": [],
  "partnerships": [],
  "patroned": [
    {
      "id": 4,
      "user_id": 2,
      "godfather_id": 15,
      "ongoing": true,
      "created_at": "2017-11-22T13:42:11.565Z",
      "updated_at": "2017-11-22T13:42:11.572Z"
    }
  ],
  "patroning": [],
  "expertises_users": [
    {
      "id": 2,
      "expertise_id": 3,
      "interested": false,
      "value": 2,
      "contact_me": false,
      "created_at": "2017-11-22T13:41:22.504Z",
      "user_id": 2
    }
  ],
  "roles": [],
  "campus": [
    {
      "id": 1,
      "name": "Cluj",
      "time_zone": "Europe/Bucharest",
      "language": {
        "id": 3,
        "name": "Romanian",
        "identifier": "ro",
        "created_at": "2017-11-22T13:40:59.468Z",
        "updated_at": "2017-11-22T13:41:26.139Z"
      },
      "users_count": 28,
      "vogsphere_id": 1
    }
  ],
  "campus_users": [
    {
      "id": 2,
      "user_id": 2,
      "campus_id": 1,
      "is_primary": true
    }
  ]
}
```

### `GET /v2/users/2` — HTTP 200

```json
{
  "id": 2,
  "email": "[email protected]",
  "login": "andre",
  "first_name": "André",
  "last_name": "Aubin",
  "usual_full_name": "Juliette Aubin",
  "usual_first_name": "Juliette",
  "url": "https://api.intra.42.fr/v2/users/andre",
  "phone": null,
  "displayname": "André Aubin",
  "kind": "admin",
  "image": {
    "link": "https://cdn.intra.42.fr/users/1234567890/andre.jpg",
    "versions": {
      "large": "https://cdn.intra.42.fr/users/1234567890/large_andre.jpg",
      "medium": "https://cdn.intra.42.fr/users/1234567890/medium_andre.jpg",
      "small": "https://cdn.intra.42.fr/users/1234567890/small_andre.jpg",
      "micro": "https://cdn.intra.42.fr/users/1234567890/micro_andre.jpgg"
    }
  },
  "staff?": false,
  "correction_point": 4,
  "pool_month": "july",
  "pool_year": "2016",
  "location": null,
  "wallet": 0,
  "anonymize_date": "2021-02-20T00:00:00.000+03:00",
  "data_erasure_date": null,
  "alumni?": false,
  "active?": true,
  "groups": [],
  "cursus_users": [
    {
      "id": 2,
      "begin_at": "2017-05-14T21:37:50.172Z",
      "end_at": null,
      "grade": null,
      "level": 0.0,
      "skills": [],
      "cursus_id": 1,
      "has_coalition": true,
      "user": {
        "id": 2,
        "login": "andre",
        "url": "https://api.intra.42.fr/v2/users/andre"
      },
      "cursus": {
        "id": 1,
        "created_at": "2017-11-22T13:41:00.750Z",
        "name": "Piscine C",
        "slug": "piscine-c"
      }
    }
  ],
  "projects_users": [],
  "languages_users": [
    {
      "id": 2,
      "language_id": 3,
      "user_id": 2,
      "position": 1,
      "created_at": "2017-11-22T13:41:03.638Z"
    }
  ],
  "achievements": [],
  "titles": [],
  "titles_users": [],
  "partnerships": [],
  "patroned": [
    {
      "id": 4,
      "user_id": 2,
      "godfather_id": 15,
      "ongoing": true,
      "created_at": "2017-11-22T13:42:11.565Z",
      "updated_at": "2017-11-22T13:42:11.572Z"
    }
  ],
  "patroning": [],
  "expertises_users": [
    {
      "id": 2,
      "expertise_id": 3,
      "interested": false,
      "value": 2,
      "contact_me": false,
      "created_at": "2017-11-22T13:41:22.504Z",
      "user_id": 2
    }
  ],
  "roles": [],
  "campus": [
    {
      "id": 1,
      "name": "Cluj",
      "time_zone": "Europe/Bucharest",
      "language": {
        "id": 3,
        "name": "Romanian",
        "identifier": "ro",
        "created_at": "2017-11-22T13:40:59.468Z",
        "updated_at": "2017-11-22T13:41:26.139Z"
      },
      "users_count": 28,
      "vogsphere_id": 1
    }
  ],
  "campus_users": [
    {
      "id": 2,
      "user_id": 2,
      "campus_id": 1,
      "is_primary": true
    }
  ]
}
```

### `PUT /v2/users/2`

```
  "user": {
    "campus_id": "1",
    "email": "[email protected]",
    "first_name": "Anakin",
    "kind": "student",
    "last_name": "Skywalker",
    "password": "totoroTOTOROOO",
    "pool_month": "september",
    "pool_year": "2017",
    "status": "admis"
  }
}
204
```


## waitlists

### `DELETE /v2/waitlists/2` — HTTP 204

```
(no body)
```

### `GET /v2/waitlists` — HTTP 200

```json
[
  {
    "created_at": "2018-09-13T18:55:37.552Z",
    "id": 1,
    "waitlistable_id": 1669,
    "waitlistable_type": "Exam"
  },
  {
    "created_at": "2018-09-13T18:56:36.902Z",
    "id": 2,
    "waitlistable_id": 1670,
    "waitlistable_type": "Exam"
  },
  {
    "created_at": "2018-09-13T18:57:13.021Z",
    "id": 3,
    "waitlistable_id": 1671,
    "waitlistable_type": "Exam"
  },
  {
    "created_at": "2018-09-13T18:58:01.760Z",
    "id": 4,
    "waitlistable_id": 1672,
    "waitlistable_type": "Exam"
  },
  {
    "created_at": "2018-09-14T08:16:14.076Z",
    "id": 5,
    "waitlistable_id": 1673,
    "waitlistable_type": "Exam"
  },
  {
    "created_at": "2018-09-14T10:01:19.094Z",
    "id": 8,
    "waitlistable_id": 1676,
    "waitlistable_type": "Exam"
  }
]
```

### `GET /v2/events/2530/waitlist` — HTTP 200

```json
{
  "created_at": "2018-09-19T15:15:33.124Z",
  "id": 32,
  "waitlistable_id": 2530,
  "waitlistable_type": "Event"
}
```

### `GET /v2/waitlists/32` — HTTP 200

```json
{
  "created_at": "2018-09-19T15:15:33.124Z",
  "id": 32,
  "waitlistable_id": 2530,
  "waitlistable_type": "Event"
}
```

