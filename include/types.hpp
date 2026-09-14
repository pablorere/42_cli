#pragma once
#include <string>
#include <vector>
#include <atomic>
#include <mutex>
#include <functional>
#include <unordered_map>
#include <cctype>
#include <cstdlib>

// ─── Tab indices ──────────────────────────────────────────────────────────────
enum class Tab { Dashboard = 0, Roadmap = 1, Slots = 2, Cluster = 3 };

// ─── Project record ───────────────────────────────────────────────────────────
struct Project {
    std::string name;
    std::string grade;   // numeric string or "N/A"
    std::string status;  // finished | in_progress | searching_a_group | waiting_for_correction
};

// ─── Holygraph Milestone Project ──────────────────────────────────────────────
struct HolyProject {
    std::string name;
    std::string state;      // done | in_progress | available | unavailable
    std::string final_mark; // "100", "125", or ""
    std::string duration;   // e.g. "about 70 hours"
    std::string difficulty; // e.g. "5775"
    std::string description;
    std::string slug;
};

// ─── Holygraph Milestone Circle ───────────────────────────────────────────────
struct Milestone {
    int  rank = 0;          // 0 to 6
    std::string name;       // "Milestone 1 - Basics"
    bool expanded = true;
    std::vector<HolyProject> projects;
};

// ─── Cluster Student Workstation ──────────────────────────────────────────────
struct ClusterStudent {
    std::string host;       // e.g. "c3r1s2"
    std::string login;      // student login
    std::string full_name;  // e.g. "Pablo Renato Paula Souza" (fetched lazily)
    std::string cdn_uri;    // avatar photo URL
    std::string begin_at;   // login timestamp
    int         campus_id = 0;
};

// ─── Cluster workstation grid geometry (8 rows x 6 seats per cluster) ─────────
namespace cluster_layout {
    constexpr int ROWS  = 8;
    constexpr int SEATS = 6;
    constexpr int CELLS = ROWS * SEATS;

    constexpr int index(int row, int seat) { return row * SEATS + seat; }
    constexpr int row_of(int idx)           { return idx / SEATS; }
    constexpr int seat_of(int idx)          { return idx % SEATS; }

    inline std::string normalize_host(const std::string& h) {
        std::string clean;
        clean.reserve(h.size());
        for (char ch : h) {
            if (ch != '-' && ch != '_' && ch != ' ')
                clean.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        }
        return clean;
    }

    inline std::string host_of(int room, int row, int seat) {
        return "c" + std::to_string(room + 1) +
               "r" + std::to_string(row + 1) +
               "s" + std::to_string(seat + 1);
    }

    inline bool occupied(const std::vector<ClusterStudent>& students,
                         int room, int row, int seat) {
        if (row < 0 || row >= ROWS || seat < 0 || seat >= SEATS) return false;
        const std::string target = host_of(room, row, seat);
        for (const auto& cs : students) {
            if (normalize_host(cs.host) == target) return true;
        }
        return false;
    }

    inline int first_occupied(const std::vector<ClusterStudent>& students, int room) {
        for (int i = 0; i < CELLS; ++i) {
            if (occupied(students, room, row_of(i), seat_of(i))) return i;
        }
        return -1;
    }

    // Nearest occupied desk to `from` in the given axis direction (dr,ds);
    // returns `from` unchanged when there is none.
    //
    // First it walks straight along the axis (same seat for vertical moves,
    // same row for horizontal) so normal navigation feels natural. When the
    // straight path is empty it falls back to the closest occupied desk in that
    // general direction, which makes isolated desks reachable too.
    inline int nearest_occupied(const std::vector<ClusterStudent>& students,
                                int room, int from, int dr, int ds) {
        if (from < 0) return first_occupied(students, room);
        if (dr == 0 && ds == 0) return from;
        int r = row_of(from), s = seat_of(from);

        for (int nr = r + dr, ns = s + ds;
             nr >= 0 && nr < ROWS && ns >= 0 && ns < SEATS;
             nr += dr, ns += ds) {
            if (occupied(students, room, nr, ns)) return index(nr, ns);
        }

        int best = -1, best_primary = 0, best_secondary = 0;
        for (int i = 0; i < CELLS; ++i) {
            int nr = row_of(i), ns = seat_of(i);
            if (!occupied(students, room, nr, ns)) continue;
            if (dr > 0 && nr <= r) continue;
            if (dr < 0 && nr >= r) continue;
            if (ds > 0 && ns <= s) continue;
            if (ds < 0 && ns >= s) continue;

            int primary   = (dr != 0) ? std::abs(nr - r) : std::abs(ns - s);
            int secondary = (dr != 0) ? std::abs(ns - s) : std::abs(nr - r);
            if (best < 0 || primary < best_primary ||
                (primary == best_primary && secondary < best_secondary)) {
                best           = i;
                best_primary   = primary;
                best_secondary = secondary;
            }
        }
        return best >= 0 ? best : from;
    }
}

// ─── Evaluation Feedback Record ───────────────────────────────────────────────
struct EvaluationFeedback {
    std::string id;
    std::string project_name;
    std::string evaluator_login;
    std::string evaluated_team;
    std::string scheduled_at;
    std::string mark;             // e.g. "100", "ok", "80%"
    std::string comment;          // Written evaluation critique
    std::string feedback_rating;  // e.g. "5 / 5"
    std::string feedback_comment; // Student's feedback on evaluator
    std::string rating_breakdown; // "Nice: 4/4, Rigorous: 4/4, ..."
    bool        is_given   = false;
    bool        is_pending = false; // Action required: feedback left to complete
};

// ─── Project Scale Team Record ────────────────────────────────────────────────
struct ScaleTeamRecord {
    std::string project_slug;
    std::string evaluator_login;
    std::string evaluated_team;
    std::string scheduled_at;
    std::string mark;
    std::string comment;
    std::string feedback_rating;
    std::string feedback_comment;
};

// ─── Slot record ──────────────────────────────────────────────────────────────
struct Slot {
    std::string begin_at;
    std::string end_at;
    std::string id;
    std::string ids;
    std::string title;
};

// ─── Student profile ──────────────────────────────────────────────────────────
struct Profile {
    std::string login;
    std::string display_name;
    std::string level;       // e.g. "12.42"
    std::string wallet;      // ₳ balance
    std::string correction_points;
    std::string location;    // e.g. e1r1p1 or "Unavailable"
    std::string avatar_url;  // CDN profile image URL
    std::vector<Project>            projects;
    std::vector<Slot>               slots;
    std::vector<Milestone>          roadmap;
    std::vector<ClusterStudent>     cluster_students;
    std::vector<EvaluationFeedback> feedbacks;
    std::vector<ScaleTeamRecord>    project_scale_teams;
    int                             pending_feedbacks_count = 0;
};

// ─── Lazily fetched full profile for a cluster student, keyed by login ───────
struct ClusterProfileEntry {
    Profile profile;
    bool    loading = false;
    bool    loaded  = false;
};

// ─── Subject (PDF) preview payload produced by the worker ────────────────────
struct SubjectPreview {
    std::string              path;         // absolute/relative PDF path
    int                      page      = 0;   // 0-based page number
    int                      page_count = 1;
    bool                     is_image  = false;
    std::string              image_key;    // key registered in image_renderer
    std::vector<std::string> text_lines;
    bool                     loading   = false;
    bool                     ready     = false;
    std::string              error;
};

// ─── Shared state between UI thread and network worker ───────────────────────
struct SharedState {
    std::mutex       mtx;
    Profile          profile;
    std::string      status_msg;     // displayed in bottom bar centre
    std::string      error_msg;
    bool             data_ready   = false;
    bool             loading      = false;
    bool             slot_pending = false;
    SubjectPreview   preview;
    std::unordered_map<std::string, ClusterProfileEntry> cluster_profiles;
    std::atomic<bool> quit        {false};
};

// ─── Network task kinds ───────────────────────────────────────────────────────
enum class NetTaskKind {
    Login,
    CookieLogin,
    FetchProfile,
    FetchSlots,
    CreateSlot,
    DeleteSlot,
    TrimSlot15m,
    DownloadSubject,
    FetchHolygraph,
    FetchClusters,
    FetchImage,
    FetchFeedbacks,
    FetchScaleTeams,
    FetchClusterUser,
    FetchClusterProfile,
    LoadSubjectPreview,
};

struct NetTask {
    NetTaskKind kind{NetTaskKind::FetchProfile};
    std::string param1{};
    std::string param2{};
    std::string param3{};
    std::string param4{};

    NetTask() = default;
    NetTask(NetTaskKind k, std::string p1 = "", std::string p2 = "", std::string p3 = "", std::string p4 = "")
        : kind(k), param1(std::move(p1)), param2(std::move(p2)), param3(std::move(p3)), param4(std::move(p4)) {}
};

