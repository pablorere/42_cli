#include "pdf_preview.hpp"

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>

namespace {

std::string normalize(const std::string& s) {
    std::string out;
    for (char ch : s) {
        if (ch == ' ') out.push_back('-');
        else out.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    }
    return out;
}

std::string shell_quote(const std::string& s) {
    std::string out = "'";
    for (char ch : s) {
        if (ch == '\'') out += "'\\''";
        else out.push_back(ch);
    }
    out.push_back('\'');
    return out;
}

std::string run_capture(const std::string& cmd) {
    FILE* p = popen(cmd.c_str(), "r");
    if (!p) return {};
    std::string out;
    char buf[4096];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), p)) > 0) out.append(buf, n);
    pclose(p);
    return out;
}

std::string temp_prefix() {
    static int counter = 0;
    return "/tmp/intra_preview_" + std::to_string(static_cast<long>(getpid())) +
           "_" + std::to_string(counter++);
}

} // namespace

namespace pdf_preview {

bool subject_pdf_path(const std::string& name_or_slug, std::string& out_path) {
    if (name_or_slug.empty()) return false;
    std::string norm = normalize(name_or_slug);

    const std::string candidates[] = {
        "subjects/" + norm + ".pdf",
        "subjects/42cursus-" + norm + ".pdf",
    };
    for (const auto& c : candidates) {
        struct stat st;
        if (stat(c.c_str(), &st) == 0 && S_ISREG(st.st_mode) && st.st_size > 100) {
            out_path = c;
            return true;
        }
    }
    return false;
}

int page_count(const std::string& path) {
    std::string out = run_capture("pdfinfo " + shell_quote(path) + " 2>/dev/null");
    size_t p = out.find("Pages:");
    if (p == std::string::npos) return 0;
    p += 6;
    int n = 0;
    while (p < out.size() && (out[p] == ' ' || out[p] == '\t')) ++p;
    while (p < out.size() && std::isdigit(static_cast<unsigned char>(out[p]))) {
        n = n * 10 + (out[p] - '0');
        ++p;
    }
    return n;
}

bool render_page_png(const std::string& path, int page, std::string& out_png) {
    if (page < 0) return false;
    std::string prefix = temp_prefix();
    int p = page + 1; // pdftoppm is 1-based

    const int dpi = 110;
    std::string cmd = "pdftoppm -png -singlefile -f " + std::to_string(p) +
                      " -l " + std::to_string(p) + " -r " + std::to_string(dpi) +
                      " " + shell_quote(path) + " " + shell_quote(prefix) +
                      " >/dev/null 2>&1";
    int rc = std::system(cmd.c_str());
    std::string png_path = prefix + ".png";
    if (rc != 0) {
        std::remove(png_path.c_str());
        return false;
    }

    std::ifstream in(png_path, std::ios::binary);
    if (!in.is_open()) {
        std::remove(png_path.c_str());
        return false;
    }
    std::ostringstream ss;
    ss << in.rdbuf();
    out_png = ss.str();
    in.close();
    std::remove(png_path.c_str());

    return out_png.size() > 8;
}

bool extract_page_text(const std::string& path, int page, std::vector<std::string>& out_lines) {
    if (page < 0) return false;
    int p = page + 1;
    std::string cmd = "pdftotext -layout -f " + std::to_string(p) +
                      " -l " + std::to_string(p) + " " + shell_quote(path) +
                      " - 2>/dev/null";
    std::string out = run_capture(cmd);
    out_lines.clear();
    std::string line;
    std::istringstream ss(out);
    while (std::getline(ss, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        for (char& ch : line) {
            if (ch == '\t') ch = ' ';
            if (ch < 32) ch = ' ';
        }
        out_lines.push_back(line);
    }
    return !out_lines.empty();
}

} // namespace pdf_preview
