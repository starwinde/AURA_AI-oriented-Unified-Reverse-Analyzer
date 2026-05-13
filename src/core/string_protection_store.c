// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "string_protection_store.h"

#include <stdio.h>
#include <stdlib.h>

#include "sqlite3.h"

static const char *kSchema =
    "CREATE TABLE IF NOT EXISTS analysis_strings ("
    "  binary_fingerprint TEXT    NOT NULL,"
    "  engine_id          TEXT    NOT NULL,"
    "  analysis_run_id    INTEGER NOT NULL DEFAULT 0,"
    "  string_id          INTEGER NOT NULL,"
    "  addr               INTEGER NOT NULL,"
    "  length             INTEGER NOT NULL,"
    "  encoding           TEXT    NOT NULL DEFAULT 'unknown',"
    "  section            TEXT    NOT NULL DEFAULT '',"
    "  original_text      TEXT    NOT NULL DEFAULT '',"
    "  source             TEXT    NOT NULL DEFAULT '',"
    "  created_at         TEXT    NOT NULL DEFAULT (datetime('now')),"
    "  PRIMARY KEY (binary_fingerprint, engine_id, string_id, addr)"
    ");"
    "CREATE TABLE IF NOT EXISTS string_overrides ("
    "  binary_fingerprint TEXT    NOT NULL,"
    "  string_addr        INTEGER NOT NULL,"
    "  original_hash      TEXT    NOT NULL,"
    "  alias              TEXT    NOT NULL DEFAULT '',"
    "  mask_token         TEXT    NOT NULL DEFAULT '',"
    "  display_mode       INTEGER NOT NULL DEFAULT 0,"
    "  created_at         TEXT    NOT NULL DEFAULT (datetime('now')),"
    "  updated_at         TEXT    NOT NULL DEFAULT (datetime('now')),"
    "  PRIMARY KEY (binary_fingerprint, string_addr, original_hash)"
    ");"
    "CREATE TABLE IF NOT EXISTS string_protection_findings ("
    "  binary_fingerprint TEXT    NOT NULL,"
    "  string_addr        INTEGER NOT NULL,"
    "  detector_id        TEXT    NOT NULL,"
    "  finding_kind       TEXT    NOT NULL,"
    "  start_offset       INTEGER NOT NULL,"
    "  end_offset         INTEGER NOT NULL,"
    "  confidence         REAL    NOT NULL,"
    "  mask_token         TEXT    NOT NULL DEFAULT '',"
    "  created_at         TEXT    NOT NULL DEFAULT (datetime('now')),"
    "  PRIMARY KEY (binary_fingerprint, string_addr, detector_id,"
    "               finding_kind, start_offset, end_offset)"
    ");";

static const char *kPutStringSql =
    "INSERT OR REPLACE INTO analysis_strings ("
    "  binary_fingerprint, engine_id, analysis_run_id, string_id, addr,"
    "  length, encoding, section, original_text, source"
    ") VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10);";

static const char *kPutOverrideSql =
    "INSERT OR REPLACE INTO string_overrides ("
    "  binary_fingerprint, string_addr, original_hash, alias, mask_token,"
    "  display_mode, created_at, updated_at"
    ") VALUES (?1, ?2, ?3, ?4, ?5, ?6,"
    "  COALESCE((SELECT created_at FROM string_overrides"
    "              WHERE binary_fingerprint = ?1 AND string_addr = ?2"
    "                AND original_hash = ?3), datetime('now')),"
    "  datetime('now'));";

static const char *kGetOverrideSql =
    "SELECT alias, mask_token, display_mode"
    "  FROM string_overrides"
    " WHERE binary_fingerprint = ?1"
    "   AND string_addr = ?2"
    "   AND original_hash = ?3;";

static const char *kPutFindingSql =
    "INSERT OR REPLACE INTO string_protection_findings ("
    "  binary_fingerprint, string_addr, detector_id, finding_kind,"
    "  start_offset, end_offset, confidence, mask_token"
    ") VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8);";

struct AuraStringProtectionStore {
    sqlite3      *db;
    sqlite3_stmt *put_string_stmt;
    sqlite3_stmt *put_override_stmt;
    sqlite3_stmt *get_override_stmt;
    sqlite3_stmt *put_finding_stmt;
};

static int prepare(sqlite3 *db, const char *sql, sqlite3_stmt **out) {
    return sqlite3_prepare_v2(db, sql, -1, out, NULL);
}

static int count_table(sqlite3 *db, const char *table) {
    if (!db || !table) return -1;
    char sql[128];
    int n = snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM %s;", table);
    if (n <= 0 || n >= (int)sizeof(sql)) return -1;
    sqlite3_stmt *st = NULL;
    if (sqlite3_prepare_v2(db, sql, -1, &st, NULL) != SQLITE_OK) return -1;
    int out = -1;
    if (sqlite3_step(st) == SQLITE_ROW) out = sqlite3_column_int(st, 0);
    sqlite3_finalize(st);
    return out;
}

AuraStringProtectionStore *aura_string_protection_store_open(const char *path) {
    if (!path) return NULL;
    AuraStringProtectionStore *s = calloc(1, sizeof(*s));
    if (!s) return NULL;

    if (sqlite3_open(path, &s->db) != SQLITE_OK) {
        if (s->db) sqlite3_close(s->db);
        free(s);
        return NULL;
    }

    sqlite3_exec(s->db, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL);
    sqlite3_busy_timeout(s->db, 5000);

    if (sqlite3_exec(s->db, kSchema, NULL, NULL, NULL) != SQLITE_OK)
        goto fail;
    if (prepare(s->db, kPutStringSql, &s->put_string_stmt) != SQLITE_OK)
        goto fail;
    if (prepare(s->db, kPutOverrideSql, &s->put_override_stmt) != SQLITE_OK)
        goto fail;
    if (prepare(s->db, kGetOverrideSql, &s->get_override_stmt) != SQLITE_OK)
        goto fail;
    if (prepare(s->db, kPutFindingSql, &s->put_finding_stmt) != SQLITE_OK)
        goto fail;

    return s;

fail:
    aura_string_protection_store_close(s);
    return NULL;
}

void aura_string_protection_store_close(AuraStringProtectionStore *s) {
    if (!s) return;
    if (s->put_string_stmt)   sqlite3_finalize(s->put_string_stmt);
    if (s->put_override_stmt) sqlite3_finalize(s->put_override_stmt);
    if (s->get_override_stmt) sqlite3_finalize(s->get_override_stmt);
    if (s->put_finding_stmt)  sqlite3_finalize(s->put_finding_stmt);
    if (s->db)                sqlite3_close(s->db);
    free(s);
}

int aura_string_protection_store_put_string(
    AuraStringProtectionStore *s, const AuraStoredStringRecord *rec) {
    if (!s || !rec) return -1;
    sqlite3_stmt *st = s->put_string_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);
    if (sqlite3_bind_text(st, 1, rec->binary_fingerprint, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 2, rec->engine_id, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 3, (sqlite3_int64)rec->analysis_run_id) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 4, (sqlite3_int64)rec->string_id) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 5, (sqlite3_int64)rec->addr) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 6, (sqlite3_int64)rec->length) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 7, rec->encoding, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 8, rec->section, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 9, rec->original_text, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 10, rec->source, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    return sqlite3_step(st) == SQLITE_DONE ? 0 : -1;
}

int aura_string_protection_store_put_override(
    AuraStringProtectionStore *s, const AuraStringOverrideRecord *rec) {
    if (!s || !rec) return -1;
    sqlite3_stmt *st = s->put_override_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);
    if (sqlite3_bind_text(st, 1, rec->binary_fingerprint, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 2, (sqlite3_int64)rec->string_addr) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 3, rec->original_hash, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 4, rec->alias, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 5, rec->mask_token, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int(st, 6, rec->display_mode) != SQLITE_OK) return -1;
    return sqlite3_step(st) == SQLITE_DONE ? 0 : -1;
}

static void copy_col_text(sqlite3_stmt *st, int col, char *dst, size_t cap) {
    if (!dst || cap == 0) return;
    const unsigned char *txt = sqlite3_column_text(st, col);
    const char *src = txt ? (const char *)txt : "";
    snprintf(dst, cap, "%s", src);
}

int aura_string_protection_store_get_override(
    AuraStringProtectionStore *s,
    const char *binary_fingerprint,
    uint64_t string_addr,
    const char *original_hash,
    AuraStringOverrideRecord *out) {
    if (!s || !binary_fingerprint || !original_hash || !out) return -1;
    sqlite3_stmt *st = s->get_override_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);
    if (sqlite3_bind_text(st, 1, binary_fingerprint, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 2, (sqlite3_int64)string_addr) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 3, original_hash, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;

    const int rc = sqlite3_step(st);
    if (rc != SQLITE_ROW) return -1;
    *out = (AuraStringOverrideRecord){0};
    snprintf(out->binary_fingerprint, sizeof(out->binary_fingerprint), "%s",
             binary_fingerprint);
    out->string_addr = string_addr;
    snprintf(out->original_hash, sizeof(out->original_hash), "%s",
             original_hash);
    copy_col_text(st, 0, out->alias, sizeof(out->alias));
    copy_col_text(st, 1, out->mask_token, sizeof(out->mask_token));
    out->display_mode = sqlite3_column_int(st, 2);
    return 0;
}

int aura_string_protection_store_put_finding(
    AuraStringProtectionStore *s, const AuraStringProtectionFinding *rec) {
    if (!s || !rec) return -1;
    sqlite3_stmt *st = s->put_finding_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);
    if (sqlite3_bind_text(st, 1, rec->binary_fingerprint, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 2, (sqlite3_int64)rec->string_addr) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 3, rec->detector_id, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 4, rec->finding_kind, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int(st, 5, rec->start_offset) != SQLITE_OK) return -1;
    if (sqlite3_bind_int(st, 6, rec->end_offset) != SQLITE_OK) return -1;
    if (sqlite3_bind_double(st, 7, rec->confidence) != SQLITE_OK) return -1;
    if (sqlite3_bind_text(st, 8, rec->mask_token, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    return sqlite3_step(st) == SQLITE_DONE ? 0 : -1;
}

int aura_string_protection_store_delete_for_fingerprint(
    AuraStringProtectionStore *s,
    const char *binary_fingerprint) {
    if (!s || !binary_fingerprint || !binary_fingerprint[0]) return -1;

    const char *sql =
        "DELETE FROM string_overrides WHERE binary_fingerprint = ?1;"
        "DELETE FROM string_protection_findings WHERE binary_fingerprint = ?1;";
    sqlite3_stmt *st = NULL;
    const char *tail = sql;
    int total_changed = 0;
    while (tail && tail[0]) {
        if (sqlite3_prepare_v2(s->db, tail, -1, &st, &tail) != SQLITE_OK)
            return -1;
        if (!st) continue;
        if (sqlite3_bind_text(st, 1, binary_fingerprint, -1,
                              SQLITE_TRANSIENT) != SQLITE_OK) {
            sqlite3_finalize(st);
            return -1;
        }
        const int rc = sqlite3_step(st);
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(st);
            return -1;
        }
        total_changed += sqlite3_changes(s->db);
        sqlite3_finalize(st);
        st = NULL;
    }
    return total_changed;
}

int aura_string_protection_store_count_strings(AuraStringProtectionStore *s) {
    return s ? count_table(s->db, "analysis_strings") : -1;
}

int aura_string_protection_store_count_overrides(AuraStringProtectionStore *s) {
    return s ? count_table(s->db, "string_overrides") : -1;
}

int aura_string_protection_store_count_findings(AuraStringProtectionStore *s) {
    return s ? count_table(s->db, "string_protection_findings") : -1;
}
