// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "artifact_cache.h"

#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

static const char *kSchema =
    "CREATE TABLE IF NOT EXISTS analysis_artifacts ("
    "  binary_fingerprint TEXT NOT NULL,"
    "  engine_id TEXT NOT NULL,"
    "  engine_version TEXT NOT NULL DEFAULT '',"
    "  request_type INTEGER NOT NULL,"
    "  artifact_kind TEXT NOT NULL,"
    "  backend TEXT NOT NULL DEFAULT '',"
    "  schema_version INTEGER NOT NULL,"
    "  function_addr INTEGER NOT NULL DEFAULT 0,"
    "  window_addr INTEGER NOT NULL DEFAULT 0,"
    "  window_count INTEGER NOT NULL DEFAULT 0,"
    "  options_hash TEXT NOT NULL DEFAULT '',"
    "  payload_json TEXT NOT NULL,"
    "  created_at TEXT NOT NULL DEFAULT (datetime('now')),"
    "  updated_at TEXT NOT NULL DEFAULT (datetime('now')),"
    "  PRIMARY KEY ("
    "    binary_fingerprint, engine_id, engine_version, request_type,"
    "    artifact_kind, backend, schema_version, function_addr,"
    "    window_addr, window_count, options_hash"
    "  )"
    ");";

static const char *kPutSql =
    "INSERT INTO analysis_artifacts ("
    "  binary_fingerprint, engine_id, engine_version, request_type,"
    "  artifact_kind, backend, schema_version, function_addr,"
    "  window_addr, window_count, options_hash, payload_json"
    ") VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12)"
    " ON CONFLICT ("
    "  binary_fingerprint, engine_id, engine_version, request_type,"
    "  artifact_kind, backend, schema_version, function_addr,"
    "  window_addr, window_count, options_hash"
    ") DO UPDATE SET"
    "  payload_json = excluded.payload_json,"
    "  updated_at = datetime('now');";

static const char *kGetSql =
    "SELECT payload_json FROM analysis_artifacts"
    " WHERE binary_fingerprint = ?1"
    "   AND engine_id = ?2"
    "   AND engine_version = ?3"
    "   AND request_type = ?4"
    "   AND artifact_kind = ?5"
    "   AND backend = ?6"
    "   AND schema_version = ?7"
    "   AND function_addr = ?8"
    "   AND window_addr = ?9"
    "   AND window_count = ?10"
    "   AND options_hash = ?11;";

struct AuraArtifactCache {
    sqlite3      *db;
    sqlite3_stmt *put_stmt;
    sqlite3_stmt *get_stmt;
};

typedef struct AuraArtifactCacheKeyLengths {
    int binary_fingerprint;
    int engine_id;
    int engine_version;
    int artifact_kind;
    int backend;
    int options_hash;
} AuraArtifactCacheKeyLengths;

static int bounded_text_len(const char *s, size_t cap) {
    if (!s) return -1;
    for (size_t i = 0; i < cap; ++i) {
        if (s[i] == '\0') return (int)i;
    }
    return -1;
}

static int collect_key_lengths(const AuraArtifactCacheKey *key,
                               AuraArtifactCacheKeyLengths *lengths) {
    if (!key || !lengths) return -1;

    lengths->binary_fingerprint = bounded_text_len(
        key->binary_fingerprint, sizeof(key->binary_fingerprint));
    lengths->engine_id =
        bounded_text_len(key->engine_id, sizeof(key->engine_id));
    lengths->engine_version = bounded_text_len(
        key->engine_version, sizeof(key->engine_version));
    lengths->artifact_kind =
        bounded_text_len(key->artifact_kind, sizeof(key->artifact_kind));
    lengths->backend = bounded_text_len(key->backend, sizeof(key->backend));
    lengths->options_hash =
        bounded_text_len(key->options_hash, sizeof(key->options_hash));

    return lengths->binary_fingerprint >= 0 &&
                   lengths->engine_id >= 0 &&
                   lengths->engine_version >= 0 &&
                   lengths->artifact_kind >= 0 &&
                   lengths->backend >= 0 &&
                   lengths->options_hash >= 0
               ? 0
               : -1;
}

static int key_valid(const AuraArtifactCacheKey *key) {
    AuraArtifactCacheKeyLengths lengths;
    return collect_key_lengths(key, &lengths) == 0 &&
           lengths.binary_fingerprint > 0 &&
           lengths.engine_id > 0 &&
           lengths.artifact_kind > 0 &&
           key->request_type >= 0 &&
           key->schema_version > 0;
}

static int bind_key(sqlite3_stmt *st, const AuraArtifactCacheKey *key) {
    AuraArtifactCacheKeyLengths lengths;
    if (collect_key_lengths(key, &lengths) != 0) return -1;

    int rc = sqlite3_bind_text(st, 1, key->binary_fingerprint,
                               lengths.binary_fingerprint,
                               SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 2, key->engine_id, lengths.engine_id,
                           SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 3, key->engine_version, lengths.engine_version,
                           SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int(st, 4, key->request_type);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 5, key->artifact_kind, lengths.artifact_kind,
                           SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 6, key->backend, lengths.backend,
                           SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int(st, 7, key->schema_version);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 8, (sqlite3_int64)key->function_addr);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 9, (sqlite3_int64)key->window_addr);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int(st, 10, key->window_count);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 11, key->options_hash, lengths.options_hash,
                           SQLITE_TRANSIENT);
    return rc == SQLITE_OK ? 0 : -1;
}

static int prepare(sqlite3 *db, const char *sql, sqlite3_stmt **out) {
    return sqlite3_prepare_v2(db, sql, -1, out, NULL);
}

AuraArtifactCache *aura_artifact_cache_open(const char *db_path) {
    if (!db_path) return NULL;

    AuraArtifactCache *cache = calloc(1, sizeof(*cache));
    if (!cache) return NULL;

    if (sqlite3_open(db_path, &cache->db) != SQLITE_OK) {
        if (cache->db) sqlite3_close(cache->db);
        free(cache);
        return NULL;
    }

    sqlite3_exec(cache->db, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL);
    sqlite3_busy_timeout(cache->db, 5000);

    if (sqlite3_exec(cache->db, kSchema, NULL, NULL, NULL) != SQLITE_OK)
        goto fail;
    if (prepare(cache->db, kPutSql, &cache->put_stmt) != SQLITE_OK)
        goto fail;
    if (prepare(cache->db, kGetSql, &cache->get_stmt) != SQLITE_OK)
        goto fail;

    return cache;

fail:
    aura_artifact_cache_close(cache);
    return NULL;
}

void aura_artifact_cache_close(AuraArtifactCache *cache) {
    if (!cache) return;
    if (cache->put_stmt) sqlite3_finalize(cache->put_stmt);
    if (cache->get_stmt) sqlite3_finalize(cache->get_stmt);
    if (cache->db) sqlite3_close(cache->db);
    free(cache);
}

int aura_artifact_cache_put(AuraArtifactCache          *cache,
                            const AuraArtifactCacheKey *key,
                            const char                 *payload_json) {
    if (!cache || !key_valid(key) || !payload_json) return -1;

    sqlite3_stmt *st = cache->put_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_key(st, key) != 0) return -1;
    if (sqlite3_bind_text(st, 12, payload_json, -1, SQLITE_TRANSIENT) !=
        SQLITE_OK)
        return -1;

    return sqlite3_step(st) == SQLITE_DONE ? 0 : -1;
}

int aura_artifact_cache_get(AuraArtifactCache          *cache,
                            const AuraArtifactCacheKey *key,
                            char                      **out_payload_json) {
    if (out_payload_json) *out_payload_json = NULL;
    if (!cache || !key_valid(key) || !out_payload_json) return -1;

    sqlite3_stmt *st = cache->get_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_key(st, key) != 0) return -1;

    int rc = sqlite3_step(st);
    if (rc == SQLITE_DONE) return 0;
    if (rc != SQLITE_ROW) return -1;

    const unsigned char *text = sqlite3_column_text(st, 0);
    if (!text) return -1;

    size_t len = strlen((const char *)text);
    char *copy = malloc(len + 1u);
    if (!copy) return -1;
    memcpy(copy, text, len + 1u);

    *out_payload_json = copy;
    return 1;
}

void aura_artifact_cache_free_payload(char *payload_json) {
    free(payload_json);
}
