// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_store.c — Phase 4B SQLite-backed override store implementation.
 *
 * Single table `overrides`, row-oriented (D-2 = SQLite row).
 * Natural composite primary key derived from AuraOverrideKey fields.
 * Prepared statements are kept on the AuraOverrideStore handle so that
 * hot paths (put/get/delete/count) avoid re-parsing SQL per call.
 */

#include "override_store.h"
#include "override_store_internal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

/* ─────────────────────────────────────────────────────────────────────
 * Schema
 *
 * Field naming mirrors AuraOverrideKey member layout to keep adapter
 * boilerplate trivial. payload_kind / payload_text are appended after
 * the key fields.
 *
 * PK is the natural identity tuple so INSERT OR REPLACE collapses
 * "same target, new payload" into an update — preserving created_at via
 * the COALESCE trick in the put() prepared statement.
 * ───────────────────────────────────────────────────────────────────── */
static const char *kOverridesSchema =
    "CREATE TABLE IF NOT EXISTS overrides ("
    "  bf_file_size            INTEGER NOT NULL,"
    "  bf_sha256               BLOB    NOT NULL,"
    "  bf_format_kind          TEXT    NOT NULL,"
    "  bf_image_base           INTEGER NOT NULL DEFAULT 0,"
    "  bf_text_section_hash    BLOB    NOT NULL,"
    "  engine_id               TEXT    NOT NULL,"
    "  engine_version          TEXT    NOT NULL,"
    "  body_schema_version     INTEGER NOT NULL DEFAULT 0,"
    "  norm_record_schema_ver  INTEGER NOT NULL DEFAULT 0,"
    "  request_type            INTEGER NOT NULL,"
    "  function_stable_id      INTEGER NOT NULL,"
    "  target_kind             INTEGER NOT NULL,"
    "  target_stable_id        INTEGER NOT NULL,"
    "  target_addr             INTEGER NOT NULL DEFAULT 0,"
    "  engine_record_source_id INTEGER NOT NULL DEFAULT 0,"
    "  confidence              INTEGER NOT NULL,"
    "  payload_kind            INTEGER NOT NULL,"
    "  payload_text            TEXT    NOT NULL DEFAULT '',"
    "  status                  INTEGER NOT NULL DEFAULT 0,"
    "  created_at              TEXT    NOT NULL DEFAULT (datetime('now')),"
    "  updated_at              TEXT    NOT NULL DEFAULT (datetime('now')),"
    "  PRIMARY KEY (bf_sha256, engine_id, request_type,"
    "               function_stable_id, target_kind, target_stable_id)"
    ");";

/* INSERT OR REPLACE preserving created_at when a row already exists.
 * SQLite's REPLACE deletes and re-inserts, so created_at is recomputed
 * from a sub-select against the existing PK. */
static const char *kPutSql =
    "INSERT OR REPLACE INTO overrides ("
    "  bf_file_size, bf_sha256, bf_format_kind, bf_image_base,"
    "  bf_text_section_hash, engine_id, engine_version,"
    "  body_schema_version, norm_record_schema_ver, request_type,"
    "  function_stable_id, target_kind, target_stable_id, target_addr,"
    "  engine_record_source_id, confidence,"
    "  payload_kind, payload_text, status,"
    "  created_at, updated_at"
    ") VALUES ("
    "  ?1, ?2, ?3, ?4,"
    "  ?5, ?6, ?7,"
    "  ?8, ?9, ?10,"
    "  ?11, ?12, ?13, ?14,"
    "  ?15, ?16,"
    "  ?17, ?18, ?19,"
    "  COALESCE("
    "    (SELECT created_at FROM overrides"
    "       WHERE bf_sha256 = ?2 AND engine_id = ?6"
    "         AND request_type = ?10 AND function_stable_id = ?11"
    "         AND target_kind = ?12 AND target_stable_id = ?13),"
    "    datetime('now')),"
    "  datetime('now')"
    ");";

static const char *kGetSql =
    "SELECT bf_file_size, bf_sha256, bf_format_kind, bf_image_base,"
    "       bf_text_section_hash, engine_id, engine_version,"
    "       body_schema_version, norm_record_schema_ver, request_type,"
    "       function_stable_id, target_kind, target_stable_id, target_addr,"
    "       engine_record_source_id, confidence,"
    "       payload_kind, payload_text, status"
    "  FROM overrides"
    " WHERE bf_sha256 = ?1 AND engine_id = ?2"
    "   AND request_type = ?3 AND function_stable_id = ?4"
    "   AND target_kind = ?5 AND target_stable_id = ?6;";

static const char *kDeleteSql =
    "DELETE FROM overrides"
    " WHERE bf_sha256 = ?1 AND engine_id = ?2"
    "   AND request_type = ?3 AND function_stable_id = ?4"
    "   AND target_kind = ?5 AND target_stable_id = ?6;";

static const char *kCountSql = "SELECT COUNT(*) FROM overrides;";

static const char *kSetStatusSql =
    "UPDATE overrides SET status = ?7,"
    "  updated_at = datetime('now')"
    " WHERE bf_sha256 = ?1 AND engine_id = ?2"
    "   AND request_type = ?3 AND function_stable_id = ?4"
    "   AND target_kind = ?5 AND target_stable_id = ?6;";

static const char *kCountByStatusSql =
    "SELECT COUNT(*) FROM overrides WHERE status = ?1;";

/* List ACTIVE rows for a given binary fingerprint + engine_id (used by
 * AuraOverrideView in 4C.1). */
static const char *kListActiveByFpEngineSql =
    "SELECT function_stable_id, target_kind, target_stable_id,"
    "       payload_kind, payload_text"
    "  FROM overrides"
    " WHERE bf_sha256 = ?1 AND engine_id = ?2 AND status = 1;";

/* List ALL rows for a given (binary fingerprint, engine_id), returning
 * the full row in column order matching the get statement so the
 * shared row-decode helper can be reused (used by Phase 4E.1). */
static const char *kListAllByFpEngineSql =
    "SELECT bf_file_size, bf_sha256, bf_format_kind, bf_image_base,"
    "       bf_text_section_hash, engine_id, engine_version,"
    "       body_schema_version, norm_record_schema_ver, request_type,"
    "       function_stable_id, target_kind, target_stable_id, target_addr,"
    "       engine_record_source_id, confidence,"
    "       payload_kind, payload_text, status"
    "  FROM overrides"
    " WHERE bf_sha256 = ?1 AND engine_id = ?2;";

/* ─────────────────────────────────────────────────────────────────────
 * Handle
 * ───────────────────────────────────────────────────────────────────── */

struct AuraOverrideStore {
    sqlite3      *db;
    sqlite3_stmt *put_stmt;
    sqlite3_stmt *get_stmt;
    sqlite3_stmt *del_stmt;
    sqlite3_stmt *count_stmt;
    sqlite3_stmt *set_status_stmt;
    sqlite3_stmt *count_status_stmt;
    sqlite3_stmt *list_active_stmt;
    sqlite3_stmt *list_all_stmt;
};

/* ─────────────────────────────────────────────────────────────────────
 * Open / Close
 * ───────────────────────────────────────────────────────────────────── */

static int prepare(sqlite3 *db, const char *sql, sqlite3_stmt **out)
{
    return sqlite3_prepare_v2(db, sql, -1, out, NULL);
}

AuraOverrideStore *aura_override_store_open(const char *path)
{
    if (!path) return NULL;

    AuraOverrideStore *s = calloc(1, sizeof(*s));
    if (!s) return NULL;

    if (sqlite3_open(path, &s->db) != SQLITE_OK) {
        if (s->db) sqlite3_close(s->db);
        free(s);
        return NULL;
    }

    /* Phase 11.3.2: WAL journal mode allows concurrent reads with the
     * project_binaries handle on the same .aura.db file (GUI opens both).
     * Best-effort — if the platform doesn't support WAL we fall through
     * to the default rollback journal. busy_timeout adds a 5s grace
     * window for serialized writes between the two handles. */
    sqlite3_exec(s->db, "PRAGMA journal_mode=WAL;",   NULL, NULL, NULL);
    sqlite3_busy_timeout(s->db, 5000);

    if (sqlite3_exec(s->db, kOverridesSchema, NULL, NULL, NULL) != SQLITE_OK)
        goto fail;

    if (prepare(s->db, kPutSql,                &s->put_stmt)          != SQLITE_OK) goto fail;
    if (prepare(s->db, kGetSql,                &s->get_stmt)          != SQLITE_OK) goto fail;
    if (prepare(s->db, kDeleteSql,             &s->del_stmt)          != SQLITE_OK) goto fail;
    if (prepare(s->db, kCountSql,              &s->count_stmt)        != SQLITE_OK) goto fail;
    if (prepare(s->db, kSetStatusSql,          &s->set_status_stmt)   != SQLITE_OK) goto fail;
    if (prepare(s->db, kCountByStatusSql,      &s->count_status_stmt) != SQLITE_OK) goto fail;
    if (prepare(s->db, kListActiveByFpEngineSql, &s->list_active_stmt) != SQLITE_OK) goto fail;
    if (prepare(s->db, kListAllByFpEngineSql,    &s->list_all_stmt)    != SQLITE_OK) goto fail;

    return s;

fail:
    aura_override_store_close(s);
    return NULL;
}

void aura_override_store_close(AuraOverrideStore *s)
{
    if (!s) return;
    if (s->put_stmt)          sqlite3_finalize(s->put_stmt);
    if (s->get_stmt)          sqlite3_finalize(s->get_stmt);
    if (s->del_stmt)          sqlite3_finalize(s->del_stmt);
    if (s->count_stmt)        sqlite3_finalize(s->count_stmt);
    if (s->set_status_stmt)   sqlite3_finalize(s->set_status_stmt);
    if (s->count_status_stmt) sqlite3_finalize(s->count_status_stmt);
    if (s->list_active_stmt)  sqlite3_finalize(s->list_active_stmt);
    if (s->list_all_stmt)     sqlite3_finalize(s->list_all_stmt);
    if (s->db)                sqlite3_close(s->db);
    free(s);
}

/* ─────────────────────────────────────────────────────────────────────
 * Bind helpers
 * ───────────────────────────────────────────────────────────────────── */

/* Bind the 6 PK columns into a SELECT/DELETE statement (positions 1..6). */
static int bind_pk_for_lookup(sqlite3_stmt *stmt, const AuraOverrideKey *k)
{
    int rc = SQLITE_OK;
    rc = sqlite3_bind_blob(stmt, 1, k->binary_fingerprint.sha256, 32, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return rc;
    rc = sqlite3_bind_text(stmt, 2, k->engine_id, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return rc;
    rc = sqlite3_bind_int (stmt, 3, (int)k->request_type);
    if (rc != SQLITE_OK) return rc;
    rc = sqlite3_bind_int64(stmt, 4, (sqlite3_int64)k->function_stable_id);
    if (rc != SQLITE_OK) return rc;
    rc = sqlite3_bind_int (stmt, 5, (int)k->target_kind);
    if (rc != SQLITE_OK) return rc;
    rc = sqlite3_bind_int64(stmt, 6, (sqlite3_int64)k->target_stable_id);
    return rc;
}

/* ─────────────────────────────────────────────────────────────────────
 * Put
 * ───────────────────────────────────────────────────────────────────── */

int aura_override_store_put(AuraOverrideStore        *s,
                            const AuraOverrideRecord *rec)
{
    if (!s || !rec) return -1;

    sqlite3_stmt *st = s->put_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    const AuraOverrideKey         *k  = &rec->key;
    const AuraOverrideBinaryFingerprint *fp = &k->binary_fingerprint;
    const AuraOverridePayload     *pl = &rec->payload;

    int rc = SQLITE_OK;

    rc = sqlite3_bind_int64(st, 1, (sqlite3_int64)fp->file_size);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_blob (st, 2, fp->sha256, 32, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text (st, 3, fp->format_kind, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 4, (sqlite3_int64)fp->image_base);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_blob (st, 5, fp->text_section_hash, 32, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text (st, 6, k->engine_id, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text (st, 7, k->engine_version, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 8, (sqlite3_int64)k->body_schema_version);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 9, (sqlite3_int64)k->normalized_record_schema_version);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int  (st, 10, (int)k->request_type);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 11, (sqlite3_int64)k->function_stable_id);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int  (st, 12, (int)k->target_kind);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 13, (sqlite3_int64)k->target_stable_id);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 14, (sqlite3_int64)k->target_addr);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 15, (sqlite3_int64)k->engine_record_source_id);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int  (st, 16, (int)k->confidence);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int  (st, 17, (int)pl->kind);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text (st, 18, pl->text, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int  (st, 19, (int)rec->status);
    if (rc != SQLITE_OK) return -1;

    rc = sqlite3_step(st);
    sqlite3_reset(st);
    return (rc == SQLITE_DONE) ? 0 : -1;
}

/* ─────────────────────────────────────────────────────────────────────
 * Get
 * ───────────────────────────────────────────────────────────────────── */

static void copy_blob32(const void *src, int src_len, uint8_t dst[32])
{
    memset(dst, 0, 32);
    if (!src || src_len <= 0) return;
    int n = src_len < 32 ? src_len : 32;
    memcpy(dst, src, (size_t)n);
}

static void copy_text(const unsigned char *src, char *dst, size_t cap)
{
    if (cap == 0) return;
    if (!src) {
        dst[0] = '\0';
        return;
    }
    size_t i = 0;
    for (; i + 1 < cap && src[i]; i++) dst[i] = (char)src[i];
    dst[i] = '\0';
}

/* Decode a row from a statement positioned at SQLITE_ROW into `out`.
 * The statement must have the same column order as kGetSql /
 * kListAllByFpEngineSql (19 columns). */
static void decode_row(sqlite3_stmt *st, AuraOverrideRecord *out)
{
    memset(out, 0, sizeof(*out));
    AuraOverrideKey               *k  = &out->key;
    AuraOverrideBinaryFingerprint *fp = &k->binary_fingerprint;
    AuraOverridePayload           *pl = &out->payload;

    fp->file_size = (uint64_t)sqlite3_column_int64(st, 0);
    copy_blob32(sqlite3_column_blob(st, 1),
                sqlite3_column_bytes(st, 1),
                fp->sha256);
    copy_text(sqlite3_column_text(st, 2),
              fp->format_kind, sizeof(fp->format_kind));
    fp->image_base = (uint64_t)sqlite3_column_int64(st, 3);
    copy_blob32(sqlite3_column_blob(st, 4),
                sqlite3_column_bytes(st, 4),
                fp->text_section_hash);

    copy_text(sqlite3_column_text(st, 5),
              k->engine_id, sizeof(k->engine_id));
    copy_text(sqlite3_column_text(st, 6),
              k->engine_version, sizeof(k->engine_version));
    k->body_schema_version              = (uint32_t)sqlite3_column_int64(st, 7);
    k->normalized_record_schema_version = (uint32_t)sqlite3_column_int64(st, 8);
    k->request_type                     = (AuraEngineRequestType)sqlite3_column_int(st, 9);
    k->function_stable_id               = (uint64_t)sqlite3_column_int64(st, 10);
    k->target_kind                      = (AuraOverrideTargetKind)sqlite3_column_int(st, 11);
    k->target_stable_id                 = (uint64_t)sqlite3_column_int64(st, 12);
    k->target_addr                      = (uint64_t)sqlite3_column_int64(st, 13);
    k->engine_record_source_id          = (uint64_t)sqlite3_column_int64(st, 14);
    k->confidence                       = (AuraOverrideConfidence)sqlite3_column_int(st, 15);

    pl->kind = (AuraOverridePayloadKind)sqlite3_column_int(st, 16);
    copy_text(sqlite3_column_text(st, 17),
              pl->text, sizeof(pl->text));
    out->status = (AuraOverrideStatus)sqlite3_column_int(st, 18);
}

int aura_override_store_get(AuraOverrideStore     *s,
                            const AuraOverrideKey *key,
                            AuraOverrideRecord    *out)
{
    if (!s || !key || !out) return -1;

    sqlite3_stmt *st = s->get_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_pk_for_lookup(st, key) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }

    int rc = sqlite3_step(st);
    if (rc == SQLITE_DONE) {
        sqlite3_reset(st);
        return 1;
    }
    if (rc != SQLITE_ROW) {
        sqlite3_reset(st);
        return -1;
    }

    decode_row(st, out);
    sqlite3_reset(st);
    return 0;
}

/* ─────────────────────────────────────────────────────────────────────
 * Delete
 * ───────────────────────────────────────────────────────────────────── */

int aura_override_store_delete(AuraOverrideStore     *s,
                               const AuraOverrideKey *key)
{
    if (!s || !key) return -1;

    sqlite3_stmt *st = s->del_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_pk_for_lookup(st, key) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }

    int rc = sqlite3_step(st);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(st);
        return -1;
    }

    int changes = sqlite3_changes(s->db);
    sqlite3_reset(st);
    return (changes > 0) ? 0 : 1;
}

/* ─────────────────────────────────────────────────────────────────────
 * Count
 * ───────────────────────────────────────────────────────────────────── */

int aura_override_store_count(AuraOverrideStore *s)
{
    if (!s) return -1;

    sqlite3_stmt *st = s->count_stmt;
    sqlite3_reset(st);

    int rc = sqlite3_step(st);
    if (rc != SQLITE_ROW) {
        sqlite3_reset(st);
        return -1;
    }

    int n = sqlite3_column_int(st, 0);
    sqlite3_reset(st);
    return n;
}

/* ─────────────────────────────────────────────────────────────────────
 * Status APIs (Phase 4C.3)
 * ───────────────────────────────────────────────────────────────────── */

int aura_override_store_set_status(AuraOverrideStore     *s,
                                   const AuraOverrideKey *key,
                                   AuraOverrideStatus     status)
{
    if (!s || !key) return -1;

    sqlite3_stmt *st = s->set_status_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_pk_for_lookup(st, key) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }
    if (sqlite3_bind_int(st, 7, (int)status) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }

    int rc = sqlite3_step(st);
    if (rc != SQLITE_DONE) {
        sqlite3_reset(st);
        return -1;
    }

    int changes = sqlite3_changes(s->db);
    sqlite3_reset(st);
    return (changes > 0) ? 0 : 1;
}

int aura_override_store_count_by_status(AuraOverrideStore  *s,
                                        AuraOverrideStatus  status)
{
    if (!s) return -1;

    sqlite3_stmt *st = s->count_status_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (sqlite3_bind_int(st, 1, (int)status) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }

    int rc = sqlite3_step(st);
    if (rc != SQLITE_ROW) {
        sqlite3_reset(st);
        return -1;
    }

    int n = sqlite3_column_int(st, 0);
    sqlite3_reset(st);
    return n;
}

/* ─────────────────────────────────────────────────────────────────────
 * Internal: list ACTIVE rows for AuraOverrideView (4C.1).
 *
 * Type + signature in override_store_internal.h, shared with
 * override_view.c. Not part of the public override_store.h surface.
 * ───────────────────────────────────────────────────────────────────── */

int aura__override_store_iter_active(
    AuraOverrideStore                   *s,
    const AuraOverrideBinaryFingerprint *fp,
    const char                          *engine_id,
    aura_override_store_active_cb        cb,
    void                                *user)
{
    if (!s || !fp || !engine_id || !cb) return -1;

    sqlite3_stmt *st = s->list_active_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (sqlite3_bind_blob(st, 1, fp->sha256, 32, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_text(st, 2, engine_id, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }

    int rc;
    while ((rc = sqlite3_step(st)) == SQLITE_ROW) {
        AuraOverrideStoreActiveRow row;
        memset(&row, 0, sizeof(row));
        row.function_stable_id = (uint64_t)sqlite3_column_int64(st, 0);
        row.target_kind        = (AuraOverrideTargetKind)sqlite3_column_int(st, 1);
        row.target_stable_id   = (uint64_t)sqlite3_column_int64(st, 2);
        row.payload.kind       = (AuraOverridePayloadKind)sqlite3_column_int(st, 3);
        copy_text(sqlite3_column_text(st, 4),
                  row.payload.text, sizeof(row.payload.text));
        if (cb(&row, user) != 0) {
            sqlite3_reset(st);
            return 0;
        }
    }

    sqlite3_reset(st);
    return (rc == SQLITE_DONE) ? 0 : -1;
}

/* Phase 4E.1: walk all rows for (fp, engine_id) regardless of status. */
int aura__override_store_iter_by_fp_engine(
    AuraOverrideStore                   *s,
    const AuraOverrideBinaryFingerprint *fp,
    const char                          *engine_id,
    aura_override_store_record_cb        cb,
    void                                *user)
{
    if (!s || !fp || !engine_id || !cb) return -1;

    sqlite3_stmt *st = s->list_all_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (sqlite3_bind_blob(st, 1, fp->sha256, 32, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_text(st, 2, engine_id, -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        sqlite3_reset(st);
        return -1;
    }

    int rc;
    while ((rc = sqlite3_step(st)) == SQLITE_ROW) {
        AuraOverrideRecord row;
        decode_row(st, &row);
        if (cb(&row, user) != 0) {
            sqlite3_reset(st);
            return 0;
        }
    }

    sqlite3_reset(st);
    return (rc == SQLITE_DONE) ? 0 : -1;
}
