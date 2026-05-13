#include "gateway_cache.h"

extern "C" {
#include "sha256.h"
#include "sqlite3.h"
}

#include <cstdlib>
#include <filesystem>

namespace aura::safety_gateway {
namespace fs = std::filesystem;

std::string defaultGatewayCachePath() {
    const char* env = std::getenv("AURA_SAFETY_GATEWAY_CACHE");
    if (env && env[0]) return env;
    return (fs::current_path() / ".aura" / "safety-gateway-cache.sqlite").string();
}

std::string gatewayContentHash(const GatewayPayloadItem& item) {
    const std::string material = item.kind + "\n" + item.text;
    uint8_t digest[AURA_SHA256_DIGEST_LEN];
    AuraSha256Ctx ctx;
    aura_sha256_init(&ctx);
    aura_sha256_update(&ctx, material.data(), material.size());
    aura_sha256_final(&ctx, digest);
    char hex[AURA_SHA256_DIGEST_LEN * 2 + 1];
    aura_sha256_hex(digest, hex);
    return hex;
}

namespace {

void ensureParentDirectory(const std::string& cache_path) {
    const auto parent = fs::path(cache_path).parent_path();
    if (!parent.empty()) {
        fs::create_directories(parent);
    }
}

bool ensureSchema(sqlite3* db) {
    const char* sql =
        "CREATE TABLE IF NOT EXISTS gateway_cache ("
        "content_hash TEXT NOT NULL,"
        "policy_hash TEXT NOT NULL,"
        "kind TEXT NOT NULL,"
        "category TEXT NOT NULL,"
        "action TEXT NOT NULL,"
        "protected_text TEXT NOT NULL,"
        "detector_summary TEXT NOT NULL,"
        "created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "last_seen_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,"
        "hit_count INTEGER NOT NULL DEFAULT 0,"
        "PRIMARY KEY (content_hash, policy_hash, kind));";
    return sqlite3_exec(db, sql, nullptr, nullptr, nullptr) == SQLITE_OK;
}

}  // namespace

bool lookupGatewayCache(const std::string& cache_path,
                        const GatewayCacheKey& key,
                        GatewayCacheEntry* out) {
    if (!out || cache_path.empty()) return false;
    ensureParentDirectory(cache_path);
    sqlite3* db = nullptr;
    if (sqlite3_open(cache_path.c_str(), &db) != SQLITE_OK) return false;
    if (!ensureSchema(db)) {
        sqlite3_close(db);
        return false;
    }

    const char* sql =
        "SELECT category, action, protected_text, detector_summary "
        "FROM gateway_cache WHERE content_hash=? AND policy_hash=? AND kind=?;";
    sqlite3_stmt* stmt = nullptr;
    bool found = false;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, key.content_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, key.policy_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, key.kind.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            out->key = key;
            out->category = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            out->action = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            out->protected_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            out->detector_summary = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
            found = true;
        }
    }
    sqlite3_finalize(stmt);

    if (found) {
        const char* update_sql =
            "UPDATE gateway_cache SET last_seen_at=CURRENT_TIMESTAMP, hit_count=hit_count+1 "
            "WHERE content_hash=? AND policy_hash=? AND kind=?;";
        sqlite3_stmt* update = nullptr;
        if (sqlite3_prepare_v2(db, update_sql, -1, &update, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(update, 1, key.content_hash.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(update, 2, key.policy_hash.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(update, 3, key.kind.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(update);
        }
        sqlite3_finalize(update);
    }

    sqlite3_close(db);
    return found;
}

bool storeGatewayCache(const std::string& cache_path,
                       const GatewayCacheEntry& entry) {
    if (cache_path.empty()) return false;
    ensureParentDirectory(cache_path);
    sqlite3* db = nullptr;
    if (sqlite3_open(cache_path.c_str(), &db) != SQLITE_OK) return false;
    if (!ensureSchema(db)) {
        sqlite3_close(db);
        return false;
    }

    const char* sql =
        "INSERT INTO gateway_cache(content_hash, policy_hash, kind, category, action, protected_text, detector_summary) "
        "VALUES(?,?,?,?,?,?,?) "
        "ON CONFLICT(content_hash, policy_hash, kind) DO UPDATE SET "
        "category=excluded.category, action=excluded.action, protected_text=excluded.protected_text, "
        "detector_summary=excluded.detector_summary, last_seen_at=CURRENT_TIMESTAMP;";
    sqlite3_stmt* stmt = nullptr;
    bool ok = false;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, entry.key.content_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, entry.key.policy_hash.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, entry.key.kind.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, entry.category.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, entry.action.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 6, entry.protected_text.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 7, entry.detector_summary.c_str(), -1, SQLITE_TRANSIENT);
        ok = sqlite3_step(stmt) == SQLITE_DONE;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return ok;
}

}  // namespace aura::safety_gateway
