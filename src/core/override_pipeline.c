// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_pipeline.c — Phase 4E.1 re-analysis resolve pass.
 *
 * Conservative matching: FUNCTION target.entry exact match against
 * fresh AuraFunctionRecord.entry. No name fallback. Variable / other
 * targets are classified ORPHAN until Phase 4D extends the key
 * contract with parent-function anchors.
 */

#include "override_pipeline.h"

#include <string.h>

#include "override_store.h"
#include "override_store_internal.h"

/* Locally compute fresh confidence per the same priority used by
 * aura_override_key_from_function_record (4A.X2). Kept inline to avoid
 * recomputing the full fresh key when we only need the confidence. */
static AuraOverrideConfidence fresh_function_confidence(
    const AuraFunctionRecord *r)
{
    if (!r) return AURA_OVERRIDE_CONFIDENCE_MISSING;
    if (r->function_id != AURA_NULL_ID)
        return AURA_OVERRIDE_CONFIDENCE_EXACT;
    if (r->entry != 0 && r->size != 0
        && r->provenance.source[0] != '\0')
        return AURA_OVERRIDE_CONFIDENCE_STRONG;
    if (r->entry != 0 && r->size != 0
        && r->name[0] != '\0')
        return AURA_OVERRIDE_CONFIDENCE_WEAK;
    return AURA_OVERRIDE_CONFIDENCE_MISSING;
}

/* Find a fresh function record whose entry matches the target address.
 * Returns:
 *    0 — exactly one match; *out_match set.
 *    1 — no match.
 *    2 — ambiguous (multiple matches).
 */
static int find_function_by_entry(const AuraRecordCollection *coll,
                                  uint64_t                     entry,
                                  const AuraFunctionRecord   **out_match)
{
    *out_match = NULL;
    if (!coll || entry == 0) return 1;

    size_t n = aura_records_function_count(coll);
    const AuraFunctionRecord *first_hit = NULL;
    for (size_t i = 0; i < n; i++) {
        const AuraFunctionRecord *r = aura_records_function_at(coll, i);
        if (!r) continue;
        if (r->entry != entry) continue;
        if (first_hit) return 2; /* ambiguous */
        first_hit = r;
    }
    if (!first_hit) return 1;
    *out_match = first_hit;
    return 0;
}

typedef struct {
    AuraOverrideStore                  *store;
    const AuraRecordCollection         *fresh_records;
    AuraOverrideResolvePassStats       *stats;
    int                                 had_error;
} PassCtx;

static AuraOverrideStatus classify_function_row(
    const AuraOverrideRecord     *stored,
    const AuraRecordCollection   *fresh)
{
    if (stored->key.target_addr == 0)
        return AURA_OVERRIDE_STATUS_ORPHAN;

    const AuraFunctionRecord *match = NULL;
    int rc = find_function_by_entry(fresh, stored->key.target_addr, &match);
    if (rc != 0)
        return AURA_OVERRIDE_STATUS_ORPHAN; /* no match or ambiguous */

    /* Stored confidence must already clear the auto-apply gate. */
    if (!aura_override_confidence_allows_auto_apply(stored->key.confidence))
        return AURA_OVERRIDE_STATUS_CONFLICT;

    /* Fresh confidence must also clear the gate. */
    AuraOverrideConfidence fc = fresh_function_confidence(match);
    if (!aura_override_confidence_allows_auto_apply(fc))
        return AURA_OVERRIDE_STATUS_CONFLICT;

    return AURA_OVERRIDE_STATUS_ACTIVE;
}

static int pass_cb(const AuraOverrideRecord *stored, void *user)
{
    PassCtx *ctx = (PassCtx *)user;
    if (ctx->stats) ctx->stats->evaluated++;

    AuraOverrideStatus new_status;
    if (stored->key.target_kind == AURA_OVERRIDE_TARGET_FUNCTION) {
        new_status = classify_function_row(stored, ctx->fresh_records);
    } else {
        /* VARIABLE / TYPE / ANNOTATION / ADDRESS / SYMBOL: cross-run
         * matching deferred (Phase 4D follow-up). Conservative: ORPHAN. */
        new_status = AURA_OVERRIDE_STATUS_ORPHAN;
    }

    if (new_status == stored->status) {
        if (ctx->stats) ctx->stats->unchanged++;
    } else {
        int rc = aura_override_store_set_status(ctx->store, &stored->key, new_status);
        if (rc < 0) {
            ctx->had_error = 1;
            return -1; /* abort iteration */
        }
    }

    if (ctx->stats) {
        switch (new_status) {
        case AURA_OVERRIDE_STATUS_ACTIVE:   ctx->stats->applied++;  break;
        case AURA_OVERRIDE_STATUS_CONFLICT: ctx->stats->conflict++; break;
        case AURA_OVERRIDE_STATUS_ORPHAN:   ctx->stats->orphan++;   break;
        default: break;
        }
    }
    return 0;
}

int aura_override_resolve_pass(
    AuraOverrideStore                   *store,
    const AuraOverrideBinaryFingerprint *current_fp,
    const AuraEngineManifest            *manifest,
    const AuraRecordCollection          *fresh_records,
    AuraOverrideResolvePassStats        *out_stats)
{
    if (!store || !current_fp || !manifest || !manifest->engine_id)
        return -1;

    if (out_stats) memset(out_stats, 0, sizeof(*out_stats));

    PassCtx ctx;
    ctx.store         = store;
    ctx.fresh_records = fresh_records;
    ctx.stats         = out_stats;
    ctx.had_error     = 0;

    int rc = aura__override_store_iter_by_fp_engine(store, current_fp,
                                                    manifest->engine_id,
                                                    pass_cb, &ctx);
    if (rc != 0 || ctx.had_error) return -1;
    return 0;
}
