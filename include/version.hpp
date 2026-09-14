#pragma once

// APP_VERSION is normally injected by the build system from the latest git
// release tag (see Makefile). The fallback keeps ad-hoc builds working.
#ifndef APP_VERSION
#define APP_VERSION "0.0.0"
#endif

// APP_REPO is injected by the build system from the git origin remote.
#ifndef APP_REPO
#define APP_REPO ""
#endif

#define APP_NAME "42_cli"
#define APP_LICENSE "MIT"
