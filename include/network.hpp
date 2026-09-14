#pragma once
#include <string>
#include <functional>
#include "types.hpp"

namespace network {

// Callback invoked from the network worker thread when data arrives.
using DataCallback = std::function<void(const std::string& html, bool ok)>;

/**
 * Initialize libcurl globally.  Must be called once from the main thread
 * before NetworkWorker spawns its worker thread.
 */
void global_init();

/** Release libcurl global resources.  Call once at shutdown. */
void global_cleanup();

/**
 * Blocking HTTP GET.  Returns the response body.
 * cookie_file path is used for both reading and writing cookies.
 */
std::string http_get(const std::string& url, const std::string& cookie_file);

/**
 * Blocking HTTP POST (application/x-www-form-urlencoded).
 * Returns the final response body after following redirects.
 */
std::string http_post(const std::string& url,
                      const std::string& fields,
                      const std::string& referer,
                      const std::string& cookie_file);

/**
 * Returns the path where cookies are stored.
 * Respects $XDG_CACHE_HOME, falls back to ~/.cache
 */
std::string cookie_file_path();

/**
 * Returns true if the session cookie file exists and the profile page
 * responds without redirecting to /sign_in.
 */
bool session_is_valid(const std::string& cookie_file);

/**
 * Performs the full Rails login dance:
 *   1. GET sign_in page → extract CSRF token
 *   2. POST credentials
 *   3. Check redirect target
 * Returns true on success.
 */
bool do_login(const std::string& username,
              const std::string& password,
              const std::string& cookie_file,
              std::string&       error_out);

/**
 * Log in directly by importing/providing a session cookie or cookie file path.
 */
bool login_with_cookie(const std::string& cookie_input,
                       const std::string& cookie_file,
                       std::string&       error_out);

/**
 * Checks well-known locations (e.g. /tmp/42cookies.txt) for existing cookies.
 */
std::string find_available_cookie_file();

/**
 * Scrape the profile page and populate the Profile struct.
 */
bool fetch_profile(const std::string& cookie_file, Profile& out, std::string& error_out);

/**
 * Scrape slots from profile.intra.42.fr/slots (or campus equivalent).
 */
bool fetch_slots(const std::string& cookie_file,
                 std::vector<Slot>& out,
                 std::string&       error_out);

/**
 * Create a slot using begin_at / end_at (ISO 8601 strings).
 * Applies the +15-minute preventive offset internally.
 */
bool create_slot(const std::string& cookie_file,
                 const std::string& begin_at,
                 const std::string& end_at,
                 std::string&       error_out);

/**
 * Delete / cancel a slot by its ID.
 */
bool delete_slot(const std::string& cookie_file,
                 const std::string& slot_id,
                 std::string&       error_out);

/**
 * Resize/update a slot by updating its end_at time.
 * Used to remove 15m from the end of a slot.
 */
bool update_slot(const std::string& cookie_file,
                 const std::string& slot_id,
                 const std::string& slot_ids,
                 const std::string& begin_at,
                 const std::string& new_end_at,
                 std::string&       error_out);

/**
 * Download subject PDF for a given project name/slug.
 * Saves to ./subjects/<slug>.pdf.
 */
bool download_subject(const std::string& cookie_file,
                      const std::string& project_name,
                      std::string&       out_filename,
                      std::string&       error_out);

/**
 * Scrape the 42 Holygraph project tree from project_data.json.
 * Populates Milestones 0 to 6 with their status.
 */
bool fetch_holygraph(const std::string& cookie_file,
                     std::vector<Milestone>& out,
                     std::string&            error_out);

/**
 * Scrape active campus clusters and online students from meta.intra.42.fr/clusters.json.
 */
bool fetch_clusters(const std::string& cookie_file,
                    std::vector<ClusterStudent>& out,
                    std::string&                 error_out);

/**
 * Fetch a student's display name (full_name) from the profile JSON endpoint.
 */
bool fetch_user_full_name(const std::string& cookie_file,
                          const std::string& login,
                          std::string&       out_full_name,
                          std::string&       error_out);

/**
 * Fetch raw binary image from URL using session cookies.
 */
bool fetch_image(const std::string& url,
                 const std::string& cookie_file,
                 std::string&       out_data,
                 std::string&       error_out);

/**
 * Format a time_t to canonical ISO 8601 with local timezone (e.g. 2026-09-14T06:15:00+02:00)
 */
std::string format_iso8601(time_t t);

/**
 * Parse an ISO 8601 string (with or without timezone offset) into UTC time_t.
 */
time_t parse_iso8601(const std::string& str);

/**
 * Calculate begin and end time_t for a slot based on offset and duration minutes.
 */
void get_slot_time_points(int offset_minutes, int duration_minutes, time_t& out_begin, time_t& out_end);

/**
 * Returns true if two half-open time intervals [b1, e1) and [b2, e2) overlap.
 */
bool slots_overlap(time_t b1, time_t e1, time_t b2, time_t e2);

/**
 * Compute ISO 8601 strings begin_at and end_at separated by '|', rounded to 15m plus offset_minutes.
 */
std::string iso_time_offset(int offset_minutes, int duration_minutes = 30);
std::string slot_display_time(int offset_minutes);

/**
 * Scrape user peer evaluation feedback history (given & received)
 * from https://projects.intra.42.fr/users/<login>/feedbacks.
 * Calculates pending feedback count for action required alerts.
 */
bool fetch_feedbacks(const std::string& cookie_file,
                     const std::string& user_login,
                     std::vector<EvaluationFeedback>& feedbacks_out,
                     int& pending_count_out,
                     std::string& error_out);

/**
 * Scrape public campus evaluation records for a project
 * from https://projects.intra.42.fr/<slug>/scale_teams.
 */
bool fetch_project_scale_teams(const std::string& cookie_file,
                               const std::string& project_slug,
                               std::vector<ScaleTeamRecord>& scale_teams_out,
                               std::string& error_out);

} // namespace network

