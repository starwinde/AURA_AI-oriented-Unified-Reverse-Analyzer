#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "artifact_cache.h"

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <stdexcept>
#include <sstream>
#include <string>
#include <thread>

namespace {

class TempDb {
  public:
    explicit TempDb(const char *name)
        : dir_(makeDir(name)), db_(dir_ / "cache.db") {}

    ~TempDb() {
        cleanupSidecars(db_);
        std::error_code ec;
        std::filesystem::remove_all(dir_, ec);
    }

    const std::filesystem::path &path() const { return db_; }

  private:
    static std::filesystem::path makeDir(const char *name) {
        static std::atomic<unsigned long> counter{0};

        const auto tick = std::chrono::steady_clock::now()
                              .time_since_epoch()
                              .count();
        const auto thread_hash = std::hash<std::thread::id>{}(
            std::this_thread::get_id());

        for (unsigned attempt = 0; attempt < 64; ++attempt) {
            std::ostringstream suffix;
            suffix << name << "_" << tick << "_" << thread_hash << "_"
                   << counter.fetch_add(1) << "_" << attempt;

            std::filesystem::path dir =
                std::filesystem::temp_directory_path() / suffix.str();
            std::error_code ec;
            if (std::filesystem::create_directory(dir, ec)) return dir;
        }

        throw std::runtime_error("failed to create temporary artifact cache dir");
    }

    static void cleanupSidecars(const std::filesystem::path &db) {
        std::error_code ec;
        std::filesystem::remove(db, ec);
        std::filesystem::remove(db.string() + "-wal", ec);
        std::filesystem::remove(db.string() + "-shm", ec);
        std::filesystem::remove(db.string() + "-journal", ec);

        if (db.extension() == ".db") {
            const std::filesystem::path stem_path =
                db.parent_path() / db.stem();
            std::filesystem::remove(stem_path.string() + ".db-wal", ec);
            std::filesystem::remove(stem_path.string() + ".db-shm", ec);
            std::filesystem::remove(stem_path.string() + ".db-journal", ec);
        }
    }

    std::filesystem::path dir_;
    std::filesystem::path db_;
};

void fillWithoutTerminator(char *field, std::size_t size) {
    std::fill(field, field + size, 'x');
}

AuraArtifactCacheKey baseKey() {
    AuraArtifactCacheKey key{};
    std::snprintf(key.binary_fingerprint, sizeof(key.binary_fingerprint),
                  "%064d", 1);
    std::snprintf(key.engine_id, sizeof(key.engine_id), "rizin");
    std::snprintf(key.engine_version, sizeof(key.engine_version), "0.8.0");
    key.request_type = 2;
    std::snprintf(key.artifact_kind, sizeof(key.artifact_kind),
                  "decompile.function");
    std::snprintf(key.backend, sizeof(key.backend), "rizin/pdgj");
    key.schema_version = 1;
    key.function_addr = 0x401000;
    key.window_addr = 0;
    key.window_count = 0;
    std::snprintf(key.options_hash, sizeof(key.options_hash), "default");
    return key;
}

}  // namespace

TEST_CASE("artifact cache stores and retrieves exact key payload") {
    const TempDb db("aura_artifact_cache_exact");
    const std::string db_path = db.path().string();
    AuraArtifactCache *cache = aura_artifact_cache_open(db_path.c_str());
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    REQUIRE(aura_artifact_cache_put(cache, &key,
                                    "{\"text\":\"int main(){}\"}") == 0);

    char *payload = nullptr;
    REQUIRE(aura_artifact_cache_get(cache, &key, &payload) == 1);
    REQUIRE(payload != nullptr);
    CHECK(std::string(payload) == "{\"text\":\"int main(){}\"}");
    aura_artifact_cache_free_payload(payload);
    aura_artifact_cache_close(cache);
}

TEST_CASE("artifact cache misses on engine version and schema version drift") {
    const TempDb db("aura_artifact_cache_miss");
    const std::string db_path = db.path().string();
    AuraArtifactCache *cache = aura_artifact_cache_open(db_path.c_str());
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"ok\":true}") == 0);

    AuraArtifactCacheKey changedEngine = key;
    std::snprintf(changedEngine.engine_version,
                  sizeof(changedEngine.engine_version), "0.9.0");
    char *payload = nullptr;
    CHECK(aura_artifact_cache_get(cache, &changedEngine, &payload) == 0);
    CHECK(payload == nullptr);

    AuraArtifactCacheKey changedSchema = key;
    changedSchema.schema_version = 2;
    CHECK(aura_artifact_cache_get(cache, &changedSchema, &payload) == 0);
    CHECK(payload == nullptr);

    aura_artifact_cache_close(cache);
}

TEST_CASE("artifact cache replace keeps one latest payload") {
    const TempDb db("aura_artifact_cache_replace");
    const std::string db_path = db.path().string();
    AuraArtifactCache *cache = aura_artifact_cache_open(db_path.c_str());
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"rev\":1}") == 0);
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"rev\":2}") == 0);

    char *payload = nullptr;
    REQUIRE(aura_artifact_cache_get(cache, &key, &payload) == 1);
    REQUIRE(payload != nullptr);
    CHECK(std::string(payload) == "{\"rev\":2}");
    aura_artifact_cache_free_payload(payload);

    aura_artifact_cache_close(cache);
}

TEST_CASE("artifact cache rejects incomplete keys") {
    AuraArtifactCacheKey key = baseKey();
    key.binary_fingerprint[0] = '\0';

    AuraArtifactCache *cache = aura_artifact_cache_open(":memory:");
    REQUIRE(cache != nullptr);
    CHECK(aura_artifact_cache_put(cache, &key, "{\"bad\":true}") == -1);

    char *payload = nullptr;
    CHECK(aura_artifact_cache_get(cache, &key, &payload) == -1);
    CHECK(payload == nullptr);
    aura_artifact_cache_close(cache);
}

TEST_CASE("artifact cache accepts empty optional key fields") {
    AuraArtifactCache *cache = aura_artifact_cache_open(":memory:");
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    key.engine_version[0] = '\0';
    key.backend[0] = '\0';
    key.options_hash[0] = '\0';
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"ok\":true}") == 0);

    char *payload = nullptr;
    REQUIRE(aura_artifact_cache_get(cache, &key, &payload) == 1);
    REQUIRE(payload != nullptr);
    CHECK(std::string(payload) == "{\"ok\":true}");
    aura_artifact_cache_free_payload(payload);
    aura_artifact_cache_close(cache);
}

TEST_CASE("artifact cache rejects unterminated key fields") {
    AuraArtifactCache *cache = aura_artifact_cache_open(":memory:");
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey required = baseKey();
    fillWithoutTerminator(required.engine_id, sizeof(required.engine_id));
    CHECK(aura_artifact_cache_put(cache, &required, "{\"bad\":true}") == -1);

    AuraArtifactCacheKey optional = baseKey();
    fillWithoutTerminator(optional.backend, sizeof(optional.backend));
    CHECK(aura_artifact_cache_put(cache, &optional, "{\"bad\":true}") == -1);

    char *payload = nullptr;
    CHECK(aura_artifact_cache_get(cache, &optional, &payload) == -1);
    CHECK(payload == nullptr);

    aura_artifact_cache_close(cache);
}
