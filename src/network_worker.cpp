#include "network_worker.hpp"
#include "network.hpp"
#include "types.hpp"
#include "config.hpp"
#include "cache.hpp"
#include "image_renderer.hpp"
#include "pdf_preview.hpp"
#include <string>
#include <chrono>
#include <thread>

// ─── Image loading: on-disk cache first, network fallback ─────────────────────
static void load_or_fetch_image(const std::string& url, const std::string& cookie) {
    if (url.empty() || image_renderer::has_image(url)) return;

    std::string cached;
    if (cache::load_image_bytes(url, cached) &&
        image_renderer::load_image_from_bytes(url, cached)) {
        return;
    }

    std::string img_data, img_err;
    if (network::fetch_image(url, cookie, img_data, img_err)) {
        cache::save_image_bytes(url, img_data);
        image_renderer::load_image_from_bytes(url, img_data);
    }
}

// ─── Carry previously fetched full names over a fresh cluster snapshot ───────
static void merge_cluster_names(SharedState& state, std::vector<ClusterStudent>& cs) {
    std::lock_guard<std::mutex> lk(state.mtx);
    for (auto& n : cs) {
        for (const auto& o : state.profile.cluster_students) {
            if (o.login == n.login && !o.full_name.empty()) {
                n.full_name = o.full_name;
                break;
            }
        }
    }
}

// ─── Persist the current profile snapshot to the on-disk cache ────────────────
static void persist_state(SharedState& state) {
    Profile snapshot;
    {
        std::lock_guard<std::mutex> lk(state.mtx);
        snapshot = state.profile;
    }
    cache::save_profile(snapshot);
}

// ─── Constructor / Destructor ─────────────────────────────────────────────────

NetworkWorker::NetworkWorker(SharedState& state)
    : state_(state)
    , running_(true)
    , thread_([this]{ run(); })
{}

NetworkWorker::~NetworkWorker() {
    stop();
}

// ─── Public interface ─────────────────────────────────────────────────────────

void NetworkWorker::enqueue(NetTask task) {
    {
        std::lock_guard<std::mutex> lk(q_mtx_);
        queue_.push(std::move(task));
    }
    q_cv_.notify_one();
}

void NetworkWorker::stop() {
    running_.store(false);
    q_cv_.notify_all();
    if (thread_.joinable())
        thread_.join();
}

// ─── Worker thread loop ───────────────────────────────────────────────────────

void NetworkWorker::run() {
    while (running_.load()) {
        NetTask task;
        {
            std::unique_lock<std::mutex> lk(q_mtx_);
            q_cv_.wait(lk, [this]{
                return !queue_.empty() || !running_.load();
            });
            if (!running_.load() && queue_.empty()) break;
            task = std::move(queue_.front());
            queue_.pop();
        }
        handle(task);
    }
}

// ─── Task dispatch ────────────────────────────────────────────────────────────

void NetworkWorker::handle(const NetTask& task) {
    const std::string cookie = network::cookie_file_path();

    switch (task.kind) {

    case NetTaskKind::Login: {
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Authenticating with Keycloak…";
        }
        std::string err;
        bool ok = network::do_login(task.param1, task.param2, cookie, err);
        if (ok) {
            Profile prof;
            std::string prof_err;
            bool pok = network::fetch_profile(cookie, prof, prof_err);

            std::vector<Slot> slots;
            std::string slot_err;
            network::fetch_slots(cookie, slots, slot_err);

            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                if (pok) {
                    state_.profile       = std::move(prof);
                    state_.profile.slots = std::move(slots);
                    state_.status_msg    = "Logged in as " + state_.profile.login;
                } else {
                    state_.status_msg = "Logged in — profile fetch failed: " + prof_err;
                }
                state_.data_ready = true;
                state_.loading    = false;
            }
            if (pok) persist_state(state_);
        } else {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.error_msg  = err;
            state_.status_msg = "Login failed: " + err;
            state_.loading    = false;
        }
        break;
    }

    case NetTaskKind::CookieLogin: {
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Validating session cookie…";
        }
        std::string err;
        bool ok = network::login_with_cookie(task.param1, cookie, err);
        if (ok) {
            Profile prof;
            std::string prof_err;
            bool pok = network::fetch_profile(cookie, prof, prof_err);

            std::vector<Slot> slots;
            std::string slot_err;
            network::fetch_slots(cookie, slots, slot_err);

            std::vector<Milestone> ms;
            std::string ms_err;
            network::fetch_holygraph(cookie, ms, ms_err);

            std::vector<ClusterStudent> cs;
            std::string cs_err;
            network::fetch_clusters(cookie, cs, cs_err);
            merge_cluster_names(state_, cs);

            std::vector<EvaluationFeedback> fbs;
            int pending_fbs = 0;
            std::string fb_err;
            network::fetch_feedbacks(cookie, prof.login, fbs, pending_fbs, fb_err);

            load_or_fetch_image(prof.avatar_url, cookie);

            // Pre-load online cluster student avatars (up to 10)
            for (size_t i = 0; i < cs.size() && i < 10; ++i) {
                load_or_fetch_image(cs[i].cdn_uri, cookie);
            }

            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                if (pok) {
                    state_.profile                         = std::move(prof);
                    state_.profile.slots                   = std::move(slots);
                    state_.profile.roadmap                 = std::move(ms);
                    state_.profile.cluster_students        = std::move(cs);
                    state_.profile.feedbacks               = std::move(fbs);
                    state_.profile.pending_feedbacks_count = pending_fbs;
                    state_.status_msg                      = "Session restored for " + state_.profile.login;
                } else {
                    state_.status_msg = "Session valid, profile fetch warning: " + prof_err;
                }
                state_.data_ready = true;
                state_.loading    = false;
            }
            if (pok) persist_state(state_);
        } else {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.error_msg  = err;
            state_.status_msg = "Cookie validation failed: " + err;
            state_.loading    = false;
        }
        break;
    }

    case NetTaskKind::FetchProfile: {
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Refreshing profile…";
        }
        Profile prof;
        std::string err;
        bool ok = network::fetch_profile(cookie, prof, err);

        std::vector<Slot> slots;
        std::string slot_err;
        network::fetch_slots(cookie, slots, slot_err);

        std::vector<Milestone> ms;
        std::string ms_err;
        network::fetch_holygraph(cookie, ms, ms_err);

        std::vector<ClusterStudent> cs;
        std::string cs_err;
        network::fetch_clusters(cookie, cs, cs_err);
        merge_cluster_names(state_, cs);

        std::vector<EvaluationFeedback> fbs;
        int pending_fbs = 0;
        std::string fb_err;
        network::fetch_feedbacks(cookie, prof.login, fbs, pending_fbs, fb_err);

        load_or_fetch_image(prof.avatar_url, cookie);

        // Pre-load online cluster student avatars (up to 10)
        for (size_t i = 0; i < cs.size() && i < 10; ++i) {
            load_or_fetch_image(cs[i].cdn_uri, cookie);
        }

        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            if (ok) {
                state_.profile                         = std::move(prof);
                state_.profile.slots                   = std::move(slots);
                state_.profile.roadmap                 = std::move(ms);
                state_.profile.cluster_students        = std::move(cs);
                state_.profile.feedbacks               = std::move(fbs);
                state_.profile.pending_feedbacks_count = pending_fbs;
                state_.data_ready                      = true;
                state_.status_msg                      = "Data refreshed (" + std::to_string(state_.profile.projects.size()) + " projects)";
            } else {
                state_.error_msg  = err;
                state_.status_msg = "Refresh failed: " + err;
                if (err.find("Session expired") != std::string::npos) {
                    state_.data_ready = false;
                }
            }
            state_.loading = false;
        }
        if (ok) persist_state(state_);
        break;
    }

    case NetTaskKind::FetchSlots: {
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Loading slots…";
        }
        std::vector<Slot> slots;
        std::string err;
        bool ok = network::fetch_slots(cookie, slots, err);

        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            if (ok) {
                state_.profile.slots = std::move(slots);
                state_.status_msg    = "Slots updated (" + std::to_string(state_.profile.slots.size()) + " open)";
            } else {
                state_.status_msg = "Slot fetch failed: " + err;
            }
            state_.loading = false;
        }
        if (ok) persist_state(state_);
        break;
    }

    case NetTaskKind::CreateSlot: {
        int base_offset = Config::get().offset_minutes;
        int duration    = Config::get().default_duration;

        try {
            if (!task.param1.empty() && task.param1.find('T') == std::string::npos) {
                base_offset = std::stoi(task.param1);
            }
            if (!task.param2.empty()) {
                duration = std::stoi(task.param2);
            }
        } catch (...) {}

        // 1. Sync latest slots from intra to have exact existing active windows
        std::vector<Slot> current_slots;
        std::string fetch_err;
        if (network::fetch_slots(cookie, current_slots, fetch_err)) {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.profile.slots = current_slots;
        } else {
            std::lock_guard<std::mutex> lk(state_.mtx);
            current_slots = state_.profile.slots;
        }

        time_t now_utc = std::time(nullptr);
        std::vector<std::pair<time_t, time_t>> existing_windows;
        for (const auto& s : current_slots) {
            time_t b = network::parse_iso8601(s.begin_at);
            time_t e = network::parse_iso8601(s.end_at);
            if (b > 0 && e > b && e > now_utc) {
                existing_windows.push_back({b, e});
            }
        }

        auto has_overlap = [&](time_t b, time_t e) -> bool {
            for (const auto& w : existing_windows) {
                if (network::slots_overlap(b, e, w.first, w.second)) {
                    return true;
                }
            }
            return false;
        };

        int current_offset = base_offset;

        // 2. Advance current_offset past any existing slots to prevent overlapping
        int skip_overlap = 0;
        while (skip_overlap < 96) { // search up to 24 hours ahead
            time_t b = 0, e = 0;
            network::get_slot_time_points(current_offset, duration, b, e);
            if (!has_overlap(b, e)) {
                break;
            }
            current_offset += 15;
            skip_overlap++;
        }

        bool ok = false;
        std::string last_err;
        std::string success_time;
        int success_offset = current_offset;

        // 3. Auto-increment retry loop: up to 16 attempts (+15m each)
        const int max_retries = 16;
        for (int attempt = 1; attempt <= max_retries && !state_.quit.load(); ++attempt) {
            // Keep advancing if offset now overlaps with any existing slot
            while (skip_overlap < 96) {
                time_t b = 0, e = 0;
                network::get_slot_time_points(current_offset, duration, b, e);
                if (!has_overlap(b, e)) {
                    break;
                }
                current_offset += 15;
                skip_overlap++;
            }

            std::string times = network::iso_time_offset(current_offset, duration);
            size_t sep = times.find('|');
            if (sep == std::string::npos) break;
            std::string begin_at = times.substr(0, sep);
            std::string end_at   = times.substr(sep + 1);
            std::string disp_time = network::slot_display_time(current_offset);

            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.slot_pending = true;
                state_.loading      = true;
                if (attempt == 1) {
                    state_.status_msg = "Creating slot at " + disp_time + " (+" + std::to_string(current_offset) + "m, no overlap)...";
                } else {
                    state_.status_msg = "Retrying at " + disp_time + " (+" + std::to_string(current_offset) + "m, attempt " +
                                        std::to_string(attempt) + "/" + std::to_string(max_retries) + ")...";
                }
            }

            last_err.clear();
            ok = network::create_slot(cookie, begin_at, end_at, last_err);
            if (ok) {
                success_time   = disp_time;
                success_offset = current_offset;
                break;
            }

            // Update error and notify user that offset is being increased
            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.error_msg  = last_err;
                state_.status_msg = disp_time + " rejected: " + last_err + ". Increasing offset (+15m)...";
            }

            current_offset += 15;
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }

        if (ok) {
            std::vector<Slot> slots;
            std::string serr;
            network::fetch_slots(cookie, slots, serr);

            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.profile.slots = std::move(slots);
                state_.status_msg    = "✔ Slot opened for " + success_time + " (+" + std::to_string(success_offset) + "m, non-overlapping)";
                state_.error_msg.clear();
                state_.slot_pending  = false;
                state_.loading      = false;
            }
            persist_state(state_);
        } else {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.error_msg    = last_err;
            state_.status_msg   = "✖ Slot creation failed after retries: " + last_err;
            state_.slot_pending = false;
            state_.loading      = false;
        }
        break;
    }

    case NetTaskKind::DeleteSlot: {
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Cancelling slot…";
        }
        std::string err;
        bool ok = network::delete_slot(cookie, task.param1, err);

        if (ok) {
            std::vector<Slot> slots;
            std::string serr;
            network::fetch_slots(cookie, slots, serr);

            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.profile.slots = std::move(slots);
                state_.status_msg    = "Slot cancelled";
                state_.loading      = false;
            }
            persist_state(state_);
        } else {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.error_msg  = err;
            state_.status_msg = "Failed to cancel slot: " + err;
            state_.loading    = false;
        }
        break;
    }

    case NetTaskKind::TrimSlot15m: {
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Trimming last 15m from slot…";
        }

        std::string err;
        time_t begin_t = network::parse_iso8601(task.param3);
        time_t end_t   = network::parse_iso8601(task.param4);
        time_t dur_sec = end_t - begin_t;

        bool ok = false;
        bool was_deleted = false;
        // If slot duration is 30 minutes or less, trimming deletes it completely
        // because 42 intra enforces a minimum slot block duration of 30 minutes.
        if (dur_sec <= 1800 || task.param2.find(',') == std::string::npos) {
            ok = network::delete_slot(cookie, task.param2, err);
            was_deleted = true;
        } else {
            time_t new_end_t = end_t - 900;
            std::string new_end_at = network::format_iso8601(new_end_t);
            ok = network::update_slot(cookie, task.param1, task.param2, task.param3, new_end_at, err);
        }

        if (ok) {
            std::vector<Slot> slots;
            std::string serr;
            network::fetch_slots(cookie, slots, serr);

            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.profile.slots = std::move(slots);
                state_.status_msg    = was_deleted ? "✔ Removed slot block (minimum 30m reached)" : "✔ Trimmed 15 minutes from slot";
                state_.error_msg.clear();
                state_.loading      = false;
            }
            persist_state(state_);
        } else {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.error_msg  = err;
            state_.status_msg = "Failed to trim slot: " + err;
            state_.loading    = false;
        }
        break;
    }

    case NetTaskKind::DownloadSubject: {
        std::string proj_name = task.param1;
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading    = true;
            state_.status_msg = "Downloading subject for " + proj_name + "…";
        }

        std::string out_file;
        std::string err;
        bool ok = network::download_subject(cookie, proj_name, out_file, err);

        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            if (ok) {
                state_.status_msg = "✔ Subject saved: " + out_file;
                state_.error_msg.clear();
            } else {
                state_.error_msg  = err;
                state_.status_msg = "Download failed: " + err;
            }
            state_.loading = false;
        }
        if (ok) {
            // Refresh the on-screen preview now that the PDF exists.
            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.preview          = SubjectPreview{};
                state_.preview.path     = out_file;
                state_.preview.loading  = true;
            }
            enqueue({ NetTaskKind::LoadSubjectPreview, out_file, "0" });
        }
        break;
    }

    case NetTaskKind::FetchHolygraph: {
        std::vector<Milestone> ms;
        std::string err;
        bool ok = network::fetch_holygraph(cookie, ms, err);
        if (ok) {
            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.profile.roadmap = std::move(ms);
            }
            persist_state(state_);
        }
        break;
    }

    case NetTaskKind::FetchClusters: {
        std::vector<ClusterStudent> cs;
        std::string err;
        bool ok = network::fetch_clusters(cookie, cs, err);
        if (ok) {
            merge_cluster_names(state_, cs);
            for (size_t i = 0; i < cs.size() && i < 15; ++i) {
                load_or_fetch_image(cs[i].cdn_uri, cookie);
            }
            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.profile.cluster_students = std::move(cs);
            }
            persist_state(state_);
        }
        break;
    }

    case NetTaskKind::FetchImage: {
        load_or_fetch_image(task.param1, cookie);
        break;
    }

    case NetTaskKind::FetchClusterUser: {
        const std::string login = task.param1;
        if (login.empty()) break;

        std::string full_name, err;
        if (network::fetch_user_full_name(cookie, login, full_name, err) && !full_name.empty()) {
            bool changed = false;
            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                for (auto& cs : state_.profile.cluster_students) {
                    if (cs.login == login && cs.full_name != full_name) {
                        cs.full_name = full_name;
                        changed = true;
                    }
                }
            }
            if (changed) persist_state(state_);
        }
        break;
    }

    case NetTaskKind::LoadSubjectPreview: {
        const std::string path = task.param1;
        if (path.empty()) break;
        int page = 0;
        try { if (!task.param2.empty()) page = std::stoi(task.param2); } catch (...) {}

        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.preview.path    = path;
            state_.preview.page    = page;
            state_.preview.loading = true;
            state_.preview.ready   = false;
            state_.preview.error.clear();
        }

        int pages = pdf_preview::page_count(path);
        std::string png;
        bool is_image = pdf_preview::render_page_png(path, page, png);
        const std::string key = "pdf:" + path + ":" + std::to_string(page);
        if (is_image) is_image = image_renderer::load_image_from_bytes(key, png);

        std::vector<std::string> lines;
        bool is_text = false;
        if (!is_image) is_text = pdf_preview::extract_page_text(path, page, lines);

        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.preview.page_count = pages > 0 ? pages : (page + 1);
            state_.preview.is_image   = is_image;
            state_.preview.image_key  = is_image ? key : std::string();
            state_.preview.text_lines = is_image ? std::vector<std::string>{} : lines;
            state_.preview.ready      = is_image || is_text;
            state_.preview.loading    = false;
            if (!state_.preview.ready)
                state_.preview.error  = "Could not render PDF preview";
        }
        break;
    }

    case NetTaskKind::FetchFeedbacks: {
        std::string login = task.param1;
        if (login.empty()) {
            std::lock_guard<std::mutex> lk(state_.mtx);
            login = state_.profile.login;
        }
        std::vector<EvaluationFeedback> fbs;
        int pending_fbs = 0;
        std::string fb_err;
        bool ok = network::fetch_feedbacks(cookie, login, fbs, pending_fbs, fb_err);
        if (ok) {
            {
                std::lock_guard<std::mutex> lk(state_.mtx);
                state_.profile.feedbacks = std::move(fbs);
                state_.profile.pending_feedbacks_count = pending_fbs;
                state_.status_msg = "Feedbacks updated (" + std::to_string(state_.profile.feedbacks.size()) + ")";
            }
            persist_state(state_);
        }
        break;
    }

    case NetTaskKind::FetchScaleTeams: {
        std::string slug = task.param1;
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            state_.loading = true;
            state_.status_msg = "Loading evaluations for " + slug + "…";
        }
        std::vector<ScaleTeamRecord> teams;
        std::string st_err;
        bool ok = network::fetch_project_scale_teams(cookie, slug, teams, st_err);
        {
            std::lock_guard<std::mutex> lk(state_.mtx);
            if (ok) {
                state_.profile.project_scale_teams = std::move(teams);
                state_.status_msg = "Evaluations loaded for " + slug + " (" + std::to_string(state_.profile.project_scale_teams.size()) + ")";
            } else {
                state_.status_msg = "Evaluations fetch failed: " + st_err;
            }
            state_.loading = false;
        }
        if (ok) persist_state(state_);
        break;
    }

    } // switch
}
