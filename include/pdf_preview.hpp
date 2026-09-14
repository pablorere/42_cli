#pragma once
#include <string>
#include <vector>

namespace pdf_preview {

/**
 * Locate a previously downloaded subject PDF for a project name/slug.
 * Checks subjects/<slug>.pdf and subjects/42cursus-<slug>.pdf.
 */
bool subject_pdf_path(const std::string& name_or_slug, std::string& out_path);

/** Total number of pages (0 when it cannot be determined). */
int page_count(const std::string& path);

/** Rasterise a single page (0-based) to PNG bytes. */
bool render_page_png(const std::string& path, int page, std::string& out_png);

/** Extract the rendered text of a single page (0-based). */
bool extract_page_text(const std::string& path, int page, std::vector<std::string>& out_lines);

} // namespace pdf_preview
