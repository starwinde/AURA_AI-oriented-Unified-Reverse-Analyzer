// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_store.h — Phase 4B SQLite-backed Override Store
 *
 * Row-oriented persistence for user overrides keyed by AuraOverrideKey
 * (Phase 4A stable identity contract). One row per (binary fingerprint,
 * engine identity, request type, function anchor, target identity) tuple.
 *
 * Scope (Phase 4B):
 *   - Schema definition + idempotent CREATE TABLE on open.
 *   - CRUD: put / get / delete / count.
 *   - Round-trip preservation of every AuraOverrideKey field.
 *
 * Out of scope (deferred to Phase 4C+):
 *   - Conflict / orphan persistence and resolution flow.
 *   - Auto-apply gate against fresh engine records (4C.2).
 *   - Multi-row transactional re-application pipeline (4E).
 *
 * Rules:
 *   R-5 — engine output is immutable. The store holds AURA-side override
 *         data only; it does NOT mutate AuraEngineResponse.
 *   R-9 — no new analysis. The store persists existing key fields and
 *         user-provided payload only.
 */

#ifndef AURA_OVERRIDE_STORE_H
#define AURA_OVERRIDE_STORE_H

#include <stdint.h>

#include "override_identity.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ─────────────────────────────────────────────────────────────────────
 * Payload
 *
 * Phase 4B carries user override data as a discriminated text blob.
 * Phase 4D will extend with structured cascades (rename propagation,
 * type cast cascade); for 4B the schema is intentionally minimal so
 * round-trip semantics can be validated independently.
 * ───────────────────────────────────────────────────────────────────── */

typedef enum AuraOverridePayloadKind {
    AURA_OVERRIDE_PAYLOAD_RENAME     = 0,
    AURA_OVERRIDE_PAYLOAD_TYPE       = 1,
    AURA_OVERRIDE_PAYLOAD_ANNOTATION = 2,
} AuraOverridePayloadKind;

#define AURA_OVERRIDE_PAYLOAD_TEXT_CAP 256

typedef struct AuraOverridePayload {
    AuraOverridePayloadKind kind;
    char                    text[AURA_OVERRIDE_PAYLOAD_TEXT_CAP];
} AuraOverridePayload;

/* ─────────────────────────────────────────────────────────────────────
 * Status (Phase 4C.3)
 *
 * Each row carries a status reflecting the latest resolve outcome:
 *   PENDING  — newly stored, not yet evaluated against fresh records.
 *   ACTIVE   — applied successfully (resolve outcome = APPLY).
 *   CONFLICT — fingerprint matches but target shifted or confidence
 *              dropped below STRONG; user review required.
 *   ORPHAN   — fingerprint differs or target absent in fresh records.
 *
 * Newly inserted rows default to PENDING. The resolve pipeline (Phase
 * 4E) is responsible for transitioning rows to ACTIVE/CONFLICT/ORPHAN.
 * ───────────────────────────────────────────────────────────────────── */

typedef enum AuraOverrideStatus {
    AURA_OVERRIDE_STATUS_PENDING  = 0,
    AURA_OVERRIDE_STATUS_ACTIVE   = 1,
    AURA_OVERRIDE_STATUS_CONFLICT = 2,
    AURA_OVERRIDE_STATUS_ORPHAN   = 3,
} AuraOverrideStatus;

typedef struct AuraOverrideRecord {
    AuraOverrideKey     key;
    AuraOverridePayload payload;
    AuraOverrideStatus  status;
} AuraOverrideRecord;

/* ─────────────────────────────────────────────────────────────────────
 * Store handle (opaque)
 * ───────────────────────────────────────────────────────────────────── */

typedef struct AuraOverrideStore AuraOverrideStore;

/*
 * Open or create a SQLite-backed store at `path`.
 *   path == ":memory:"  → transient in-memory DB (used by tests).
 *   path == "<file>"    → on-disk DB, created if absent.
 *
 * On success the schema is created idempotently and prepared statements
 * are bound. Returns NULL on any failure (path NULL, sqlite open fail,
 * schema creation fail, statement preparation fail).
 */
AuraOverrideStore *aura_override_store_open(const char *path);

/*
 * Close the store, finalizing all prepared statements and closing the
 * underlying SQLite handle. NULL-safe.
 */
void aura_override_store_close(AuraOverrideStore *store);

/*
 * Insert or replace a record. Natural primary key:
 *   (bf_sha256, engine_id, request_type, function_stable_id,
 *    target_kind, target_stable_id)
 *
 * `created_at` is preserved across replaces; `updated_at` is refreshed.
 * Returns 0 on success, -1 on failure (NULL args, bind/step error).
 */
int aura_override_store_put(AuraOverrideStore         *store,
                            const AuraOverrideRecord  *rec);

/*
 * Read a record by key. The lookup matches on the same primary-key tuple
 * used by put().
 *
 * Returns:
 *    0 — found, *out filled.
 *    1 — not found, *out untouched.
 *   -1 — error (NULL args, prepare/step failure).
 */
int aura_override_store_get(AuraOverrideStore       *store,
                            const AuraOverrideKey   *key,
                            AuraOverrideRecord      *out);

/*
 * Delete a record by key.
 *
 * Returns:
 *    0 — deleted (1 row).
 *    1 — not found (0 rows).
 *   -1 — error.
 */
int aura_override_store_delete(AuraOverrideStore     *store,
                               const AuraOverrideKey *key);

/*
 * Total row count. Returns -1 on error.
 */
int aura_override_store_count(AuraOverrideStore *store);

/*
 * Update the status field of an existing row. Returns 0 if updated,
 * 1 if no row matched the key, -1 on error.
 */
int aura_override_store_set_status(AuraOverrideStore     *store,
                                   const AuraOverrideKey *key,
                                   AuraOverrideStatus     status);

/*
 * Count rows with the given status. Returns -1 on error.
 */
int aura_override_store_count_by_status(AuraOverrideStore *store,
                                        AuraOverrideStatus status);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_OVERRIDE_STORE_H */
