// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_pipeline.h — Phase 4E.1 re-analysis resolve pass.
 *
 * Walks every stored override row matching (current_fp, engine_id),
 * matches each FUNCTION target against fresh records by entry address
 * (target_addr), and updates the row's status field per the
 * conservative matching policy decided 2026-05-02:
 *
 *   - FUNCTION target with non-zero target_addr matched to exactly one
 *     fresh AuraFunctionRecord whose entry == target_addr:
 *       both stored and fresh confidence ≥ STRONG → ACTIVE.
 *       otherwise                                  → CONFLICT.
 *   - FUNCTION target with target_addr == 0, no match, or ambiguous
 *     match (multiple fresh records at the same entry):
 *       → ORPHAN.
 *   - VARIABLE / TYPE / ANNOTATION / ADDRESS / SYMBOL targets:
 *       → ORPHAN. Cross-run matching for these requires parent-function
 *         anchors that the current key contract does not carry; the
 *         extension is deferred to a future Phase 4D follow-up.
 *
 * Function name fallback is explicitly forbidden. Fingerprint mismatch
 * is handled by aura_override_resolve() at single-row granularity; the
 * pipeline only iterates rows whose fingerprint matches `current_fp`,
 * so cross-binary rows are not touched by a single pass.
 *
 * R-9 — no new analysis is performed. The pipeline only reads existing
 * AuraRecordCollection fields and existing override rows.
 */

#ifndef AURA_OVERRIDE_PIPELINE_H
#define AURA_OVERRIDE_PIPELINE_H

#include <stdint.h>

#include "aura/normalized_records.h"
#include "engine_manifest.h"
#include "override_identity.h"
#include "override_store.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AuraOverrideResolvePassStats {
    uint32_t evaluated;   /* rows visited                                 */
    uint32_t applied;     /* transitioned to ACTIVE                       */
    uint32_t conflict;    /* transitioned to CONFLICT                     */
    uint32_t orphan;      /* transitioned to ORPHAN                       */
    uint32_t unchanged;   /* status was already correct (no UPDATE issued)*/
} AuraOverrideResolvePassStats;

/*
 * Run the resolve pass. `out_stats` may be NULL.
 *
 * Returns 0 on success, -1 on argument or store iteration error.
 * Per-row resolution failures are reflected in the row's status, not
 * in the return value.
 */
int aura_override_resolve_pass(
    AuraOverrideStore                   *store,
    const AuraOverrideBinaryFingerprint *current_fp,
    const AuraEngineManifest            *manifest,
    const AuraRecordCollection          *fresh_records,
    AuraOverrideResolvePassStats        *out_stats);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_OVERRIDE_PIPELINE_H */
