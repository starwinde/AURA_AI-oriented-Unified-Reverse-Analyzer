// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_store_internal.h — Phase 4C internal shared interface
 * between override_store.c and override_view.c.
 *
 * Not part of the public surface (not included from any public header).
 * Defines the iterator callback used by AuraOverrideView to materialize
 * an in-memory snapshot of ACTIVE override rows.
 */

#ifndef AURA_OVERRIDE_STORE_INTERNAL_H
#define AURA_OVERRIDE_STORE_INTERNAL_H

#include <stdint.h>

#include "override_identity.h"
#include "override_store.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AuraOverrideStoreActiveRow {
    uint64_t                function_stable_id;
    AuraOverrideTargetKind  target_kind;
    uint64_t                target_stable_id;
    AuraOverridePayload     payload;
} AuraOverrideStoreActiveRow;

typedef int (*aura_override_store_active_cb)(
    const AuraOverrideStoreActiveRow *row, void *user);

/* Iterate ACTIVE rows for (fp, engine_id). cb returning non-zero stops
 * iteration. Returns 0 on success, -1 on error. */
int aura__override_store_iter_active(
    AuraOverrideStore                   *s,
    const AuraOverrideBinaryFingerprint *fp,
    const char                          *engine_id,
    aura_override_store_active_cb        cb,
    void                                *user);

/* Iterate ALL rows (any status) for (fp, engine_id) returning a full
 * AuraOverrideRecord per row. Used by Phase 4E.1 resolve pass.
 * cb returning non-zero stops iteration. Returns 0 on success, -1 on
 * error. */
typedef int (*aura_override_store_record_cb)(
    const AuraOverrideRecord *rec, void *user);

int aura__override_store_iter_by_fp_engine(
    AuraOverrideStore                   *s,
    const AuraOverrideBinaryFingerprint *fp,
    const char                          *engine_id,
    aura_override_store_record_cb        cb,
    void                                *user);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_OVERRIDE_STORE_INTERNAL_H */
