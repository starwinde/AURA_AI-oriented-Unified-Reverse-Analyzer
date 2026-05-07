// src/engine/consent/consent_store_sqlite.h — Phase 2.5 §1.5
//
// SQLite-backed AuraConsentStore. The decision logic in consent_gate.c
// reads through the AuraConsentStore vtable; this header exposes the
// concrete production implementation that opens a database file
// (typically ~/.aura/global_consent.db) and persists upserts.
//
// The schema mirrors plan §1.5:
//   engine_consent(
//     engine_id TEXT PRIMARY KEY,
//     decision  TEXT, decided_at INTEGER,
//     bootstrap_state TEXT,
//     last_attempt_at INTEGER, retry_after INTEGER,
//     failure_count INTEGER, last_error TEXT)

#ifndef AURA_ENGINE_CONSENT_STORE_SQLITE_H
#define AURA_ENGINE_CONSENT_STORE_SQLITE_H

#include "consent_gate.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AuraConsentStoreSqlite AuraConsentStoreSqlite;

/* Open (and create if missing) a consent DB at `path`. ":memory:" is a
 * valid path and is used by the unit tests so we never touch the real
 * ~/.aura tree. Returns NULL on error. */
AuraConsentStoreSqlite *aura_consent_store_sqlite_open(const char *path);

/* Free the handle. Safe on NULL. */
void aura_consent_store_sqlite_close(AuraConsentStoreSqlite *s);

/* Adapter so the SQLite store plugs into the generic AuraConsentStore
 * vtable consumed by `aura_consent_check`. The returned pointer is
 * owned by `s` — do not free. */
AuraConsentStore *aura_consent_store_sqlite_as_store(
    AuraConsentStoreSqlite *s);

/* Insert-or-replace a record for `engine_id`. Returns 0 on success,
 * negative on SQLite error. */
int aura_consent_store_sqlite_upsert(
    AuraConsentStoreSqlite  *s,
    const char              *engine_id,
    const AuraConsentRecord *rec);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_CONSENT_STORE_SQLITE_H */
