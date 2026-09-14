// ─── stb_image_resize2 implementation unit ───────────────────────────────────
// Isolated in its own translation unit so the vendored header's warnings never
// leak into the project's -Wall -Wextra -Werror -pedantic build. The rest of
// the codebase only sees the plain declarations from <stb_image_resize2.h>.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wcast-qual"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wduplicated-branches"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize2.h"
#pragma GCC diagnostic pop
