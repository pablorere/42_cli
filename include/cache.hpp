#pragma once
#include "types.hpp"
#include <string>
#include <unordered_map>

/**
 * On-disk cache.
 *
 * Persists the scraped Profile (so the TUI can render instantly on the next
 * launch, even before/without a network round-trip) and the raw bytes of every
 * image fetched through the session (so avatars survive offline restarts).
 */
namespace cache {

// ── Profile cache ────────────────────────────────────────────────────────────
bool save_profile(const Profile& p);
bool load_profile(Profile& out);
bool profile_cache_exists();
void purge_profile();

// ── Cluster student profile cache (keyed by login) ───────────────────────────
bool save_cluster_profile(const std::string& login, const Profile& p);
bool load_cluster_profile(const std::string& login, Profile& out);
int  load_all_cluster_profiles(std::unordered_map<std::string, Profile>& out);

// ── Image byte cache (keyed by source URL) ───────────────────────────────────
bool save_image_bytes(const std::string& url, const std::string& data);
bool load_image_bytes(const std::string& url, std::string& out);
bool image_cache_exists(const std::string& url);

/**
 * Reads every cached image from disk into the in-memory image_renderer cache.
 * Returns the number of images successfully loaded.
 */
int load_all_cached_images();

// ── Paths ────────────────────────────────────────────────────────────────────
std::string cache_dir();
std::string images_dir();

} // namespace cache
