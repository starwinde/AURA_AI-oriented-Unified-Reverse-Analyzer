// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * project_binaries.c — SQLite-backed project binary registry implementation.
 * See project_binaries.h for contract.
 */

#include "project_binaries.h"

#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

static const char *kSchema =
    "CREATE TABLE IF NOT EXISTS project_binaries ("
    "  path             TEXT    NOT NULL,"
    "  fingerprint      TEXT    PRIMARY KEY,"
    "  size             INTEGER NOT NULL,"
    "  added_at         INTEGER NOT NULL,"
    "  last_analyzed_at INTEGER"
    ");";

/* INSERT OR REPLACE preserving added_at via COALESCE sub-select against
 * the existing PK row. */
static const char *kPutSql =
    "INSERT OR REPLACE INTO project_binaries"
    "  (path, fingerprint, size, added_at, last_analyzed_at)"
    " VALUES (?1, ?2, ?3,"
    "         COALESCE("
    "           (SELECT added_at FROM project_binaries WHERE fingerprint = ?2),"
    "           ?4),"
    "         ?5);";

static const char *kListSql =
    "SELECT path, fingerprint, size, added_at, COALESCE(last_analyzed_at, 0)"
    "  FROM project_binaries ORDER BY added_at ASC;";

static const char *kCountSql = "SELECT COUNT(*) FROM project_binaries;";

static const char *kMarkAnalyzedSql =
    "UPDATE project_binaries SET last_analyzed_at = ?2"
    " WHERE fingerprint = ?1;";

static const char *kRemoveSql =
    "DELETE FROM project_binaries WHERE fingerprint = ?1;";

struct AuraProjectBinaries {
    sqlite3      *db;
    sqlite3_stmt *put_stmt;
    sqlite3_stmt *list_stmt;
    sqlite3_stmt *count_stmt;
    sqlite3_stmt *mark_stmt;
    sqlite3_stmt *remove_stmt;
};

static int prepare(sqlite3 *db, const char *sql, sqlite3_stmt **out) {
    return sqlite3_prepare_v2(db, sql, -1, out, NULL);
}

AuraProjectBinaries *aura_project_binaries_open(const char *path) {
    if (!path) return NULL;

    AuraProjectBinaries *pb = calloc(1, sizeof(*pb));
    if (!pb) return NULL;

    if (sqlite3_open(path, &pb->db) != SQLITE_OK) {
        if (pb->db) sqlite3_close(pb->db);
        free(pb);
        return NULL;
    }

    /* Phase 11.3.2: WAL + busy_timeout for coexistence with the
     * override_store handle on the same .aura.db file. */
    sqlite3_exec(pb->db, "PRAGMA journal_mode=WAL;",   NULL, NULL, NULL);
    sqlite3_busy_timeout(pb->db, 5000);

    if (sqlite3_exec(pb->db, kSchema, NULL, NULL, NULL) != SQLITE_OK)
        goto fail;

    if (prepare(pb->db, kPutSql,          &pb->put_stmt)    != SQLITE_OK) goto fail;
    if (prepare(pb->db, kListSql,         &pb->list_stmt)   != SQLITE_OK) goto fail;
    if (prepare(pb->db, kCountSql,        &pb->count_stmt)  != SQLITE_OK) goto fail;
    if (prepare(pb->db, kMarkAnalyzedSql, &pb->mark_stmt)   != SQLITE_OK) goto fail;
    if (prepare(pb->db, kRemoveSql,       &pb->remove_stmt) != SQLITE_OK) goto fail;

    return pb;

fail:
    aura_project_binaries_close(pb);
    return NULL;
}

void aura_project_binaries_close(AuraProjectBinaries *pb) {
    if (!pb) return;
    if (pb->put_stmt)    sqlite3_finalize(pb->put_stmt);
    if (pb->list_stmt)   sqlite3_finalize(pb->list_stmt);
    if (pb->count_stmt)  sqlite3_finalize(pb->count_stmt);
    if (pb->mark_stmt)   sqlite3_finalize(pb->mark_stmt);
    if (pb->remove_stmt) sqlite3_finalize(pb->remove_stmt);
    if (pb->db)          sqlite3_close(pb->db);
    free(pb);
}

int aura_project_binaries_put(AuraProjectBinaries           *pb,
                              const AuraProjectBinaryRecord *rec) {
    if (!pb || !rec) return -1;
    sqlite3_stmt *st = pb->put_stmt;
    sqlite3_reset(st);

    int rc = SQLITE_OK;
    rc = sqlite3_bind_text (st, 1, rec->path,        -1, SQLITE_TRANSIENT); if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text (st, 2, rec->fingerprint, -1, SQLITE_TRANSIENT); if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 3, (sqlite3_int64)rec->size);               if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 4, (sqlite3_int64)rec->added_at);           if (rc != SQLITE_OK) return -1;
    if (rec->last_analyzed_at > 0) {
        rc = sqlite3_bind_int64(st, 5, (sqlite3_int64)rec->last_analyzed_at);
    } else {
        rc = sqlite3_bind_null(st, 5);
    }
    if (rc != SQLITE_OK) return -1;

    rc = sqlite3_step(st);
    return (rc == SQLITE_DONE) ? 0 : -1;
}

int aura_project_binaries_list(AuraProjectBinaries     *pb,
                               AuraProjectBinaryRecord *out,
                               int                      capacity) {
    if (!pb || !out || capacity <= 0) return -1;
    sqlite3_stmt *st = pb->list_stmt;
    sqlite3_reset(st);

    int n = 0;
    while (n < capacity) {
        int rc = sqlite3_step(st);
        if (rc == SQLITE_DONE) break;
        if (rc != SQLITE_ROW) return -1;

        AuraProjectBinaryRecord *r = &out[n];
        memset(r, 0, sizeof(*r));

        const unsigned char *path = sqlite3_column_text(st, 0);
        const unsigned char *fp   = sqlite3_column_text(st, 1);
        if (path) {
            strncpy(r->path, (const char *)path, AURA_PROJECT_BINARY_PATH_CAP - 1);
        }
        if (fp) {
            strncpy(r->fingerprint, (const char *)fp,
                    AURA_PROJECT_BINARY_FINGERPRINT_LEN);
        }
        r->size             = (int64_t)sqlite3_column_int64(st, 2);
        r->added_at         = (int64_t)sqlite3_column_int64(st, 3);
        r->last_analyzed_at = (int64_t)sqlite3_column_int64(st, 4);
        n++;
    }
    return n;
}

int aura_project_binaries_count(AuraProjectBinaries *pb) {
    if (!pb) return -1;
    sqlite3_stmt *st = pb->count_stmt;
    sqlite3_reset(st);
    if (sqlite3_step(st) != SQLITE_ROW) return -1;
    return sqlite3_column_int(st, 0);
}

int aura_project_binaries_mark_analyzed(AuraProjectBinaries *pb,
                                        const char          *fp_hex,
                                        int64_t              when_unix) {
    if (!pb || !fp_hex) return -1;
    sqlite3_stmt *st = pb->mark_stmt;
    sqlite3_reset(st);
    if (sqlite3_bind_text (st, 1, fp_hex, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_bind_int64(st, 2, (sqlite3_int64)when_unix)     != SQLITE_OK) return -1;
    if (sqlite3_step(st) != SQLITE_DONE) return -1;
    return (sqlite3_changes(pb->db) > 0) ? 0 : 1;
}

int aura_project_binaries_remove(AuraProjectBinaries *pb,
                                 const char          *fp_hex) {
    if (!pb || !fp_hex) return -1;
    sqlite3_stmt *st = pb->remove_stmt;
    sqlite3_reset(st);
    if (sqlite3_bind_text(st, 1, fp_hex, -1, SQLITE_TRANSIENT) != SQLITE_OK) return -1;
    if (sqlite3_step(st) != SQLITE_DONE) return -1;
    return (sqlite3_changes(pb->db) > 0) ? 0 : 1;
}
