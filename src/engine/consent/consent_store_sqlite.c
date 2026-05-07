// src/engine/consent/consent_store_sqlite.c — Phase 2.5 §1.5

#include "consent_store_sqlite.h"

#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

struct AuraConsentStoreSqlite {
    sqlite3          *db;
    AuraConsentStore  vtbl;
};

static const char *kSchemaSql =
    "CREATE TABLE IF NOT EXISTS engine_consent ("
    "  engine_id        TEXT PRIMARY KEY,"
    "  decision         TEXT,"
    "  decided_at       INTEGER,"
    "  bootstrap_state  TEXT,"
    "  last_attempt_at  INTEGER,"
    "  retry_after      INTEGER,"
    "  failure_count    INTEGER,"
    "  last_error       TEXT"
    ");";

static void copy_text(char *dst, size_t cap, const unsigned char *src) {
    if (cap == 0) return;
    if (!src) { dst[0] = '\0'; return; }
    size_t n = strlen((const char *)src);
    if (n >= cap) n = cap - 1;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static int sqlite_load(AuraConsentStore  *self,
                       const char        *engine_id,
                       AuraConsentRecord *out) {
    AuraConsentStoreSqlite *s = (AuraConsentStoreSqlite *)self->state;
    if (!s || !s->db || !engine_id || !out) return -1;

    static const char *q =
        "SELECT decision, decided_at, bootstrap_state, last_attempt_at,"
        "       retry_after, failure_count"
        "  FROM engine_consent WHERE engine_id = ?1;";
    sqlite3_stmt *st = NULL;
    if (sqlite3_prepare_v2(s->db, q, -1, &st, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text(st, 1, engine_id, -1, SQLITE_TRANSIENT);

    int rc = sqlite3_step(st);
    int found = 0;
    if (rc == SQLITE_ROW) {
        memset(out, 0, sizeof(*out));
        copy_text(out->decision,        sizeof(out->decision),
                  sqlite3_column_text(st, 0));
        out->decided_at_ms = sqlite3_column_int64(st, 1);
        copy_text(out->bootstrap_state, sizeof(out->bootstrap_state),
                  sqlite3_column_text(st, 2));
        out->last_attempt_at_ms = sqlite3_column_int64(st, 3);
        out->retry_after_ms     = sqlite3_column_int64(st, 4);
        out->failure_count      = sqlite3_column_int(st, 5);
        found = 1;
    }
    sqlite3_finalize(st);
    return found;
}

AuraConsentStoreSqlite *aura_consent_store_sqlite_open(const char *path) {
    if (!path) return NULL;
    AuraConsentStoreSqlite *s = calloc(1, sizeof(*s));
    if (!s) return NULL;
    if (sqlite3_open(path, &s->db) != SQLITE_OK) {
        if (s->db) sqlite3_close(s->db);
        free(s);
        return NULL;
    }
    char *err = NULL;
    if (sqlite3_exec(s->db, kSchemaSql, NULL, NULL, &err) != SQLITE_OK) {
        if (err) sqlite3_free(err);
        sqlite3_close(s->db);
        free(s);
        return NULL;
    }
    s->vtbl.load  = &sqlite_load;
    s->vtbl.state = s;
    return s;
}

void aura_consent_store_sqlite_close(AuraConsentStoreSqlite *s) {
    if (!s) return;
    if (s->db) sqlite3_close(s->db);
    free(s);
}

AuraConsentStore *aura_consent_store_sqlite_as_store(
    AuraConsentStoreSqlite *s) {
    return s ? &s->vtbl : NULL;
}

int aura_consent_store_sqlite_upsert(
    AuraConsentStoreSqlite  *s,
    const char              *engine_id,
    const AuraConsentRecord *rec) {
    if (!s || !s->db || !engine_id || !rec) return -1;
    static const char *q =
        "INSERT INTO engine_consent("
        "  engine_id, decision, decided_at, bootstrap_state,"
        "  last_attempt_at, retry_after, failure_count, last_error)"
        " VALUES(?1, ?2, ?3, ?4, ?5, ?6, ?7, '')"
        " ON CONFLICT(engine_id) DO UPDATE SET"
        "  decision=excluded.decision,"
        "  decided_at=excluded.decided_at,"
        "  bootstrap_state=excluded.bootstrap_state,"
        "  last_attempt_at=excluded.last_attempt_at,"
        "  retry_after=excluded.retry_after,"
        "  failure_count=excluded.failure_count;";
    sqlite3_stmt *st = NULL;
    if (sqlite3_prepare_v2(s->db, q, -1, &st, NULL) != SQLITE_OK) return -1;
    sqlite3_bind_text (st, 1, engine_id,         -1, SQLITE_TRANSIENT);
    sqlite3_bind_text (st, 2, rec->decision,     -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(st, 3, rec->decided_at_ms);
    sqlite3_bind_text (st, 4, rec->bootstrap_state, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int64(st, 5, rec->last_attempt_at_ms);
    sqlite3_bind_int64(st, 6, rec->retry_after_ms);
    sqlite3_bind_int  (st, 7, rec->failure_count);
    int rc = sqlite3_step(st);
    sqlite3_finalize(st);
    return rc == SQLITE_DONE ? 0 : -1;
}
