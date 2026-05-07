// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "override_identity.h"

#include <string.h>

/* ─────────────────────────────────────────────────────────────────────
 * Internal helpers
 * ───────────────────────────────────────────────────────────────────── */

static AuraOverrideKey make_zero_key(void)
{
    AuraOverrideKey k;
    memset(&k, 0, sizeof(k));
    k.confidence = AURA_OVERRIDE_CONFIDENCE_MISSING;
    return k;
}

static void fill_engine_fields(AuraOverrideKey *k,
                               const AuraEngineManifest *manifest)
{
    if (!manifest) return;
    if (manifest->engine_id)
        strncpy(k->engine_id, manifest->engine_id, sizeof(k->engine_id) - 1);
    if (manifest->version)
        strncpy(k->engine_version, manifest->version, sizeof(k->engine_version) - 1);
}

/* ─────────────────────────────────────────────────────────────────────
 * Public API
 * ───────────────────────────────────────────────────────────────────── */

AuraOverrideKey aura_override_key_from_function_record(
    const AuraFunctionRecord            *record,
    const AuraEngineManifest            *manifest,
    const AuraOverrideBinaryFingerprint *fingerprint)
{
    if (!record || !manifest || !fingerprint)
        return make_zero_key();

    AuraOverrideKey k;
    memset(&k, 0, sizeof(k));

    fill_engine_fields(&k, manifest);
    k.binary_fingerprint = *fingerprint;
    k.target_kind        = AURA_OVERRIDE_TARGET_FUNCTION;

    /* 4A.X2 priority: determine function_stable_id and confidence */
    if (record->function_id != AURA_NULL_ID) {
        k.function_stable_id = (uint64_t)record->function_id;
        k.target_stable_id   = (uint64_t)record->function_id;
        k.confidence         = AURA_OVERRIDE_CONFIDENCE_EXACT;
    } else if (record->entry != 0 && record->size != 0
               && record->provenance.source[0] != '\0') {
        k.function_stable_id = record->entry;
        k.target_stable_id   = record->entry;
        k.confidence         = AURA_OVERRIDE_CONFIDENCE_STRONG;
    } else if (record->entry != 0 && record->size != 0
               && record->name[0] != '\0') {
        k.function_stable_id = record->entry;
        k.target_stable_id   = record->entry;
        k.confidence         = AURA_OVERRIDE_CONFIDENCE_WEAK;
    } else {
        k.function_stable_id = 0;
        k.target_stable_id   = 0;
        k.confidence         = AURA_OVERRIDE_CONFIDENCE_MISSING;
    }

    /* Always populate target_addr from record->entry when available.
     * Phase 4E re-analysis matching requires the entry address as the
     * stable cross-run anchor (engine-assigned function_id is NOT
     * guaranteed stable across re-analysis). 2026-05-02. */
    if (record->entry != 0)
        k.target_addr = record->entry;

    return k;
}

AuraOverrideKey aura_override_key_from_variable_record(
    const AuraVariableRecord            *record,
    const AuraEngineManifest            *manifest,
    const AuraOverrideBinaryFingerprint *fingerprint)
{
    if (!record || !manifest || !fingerprint)
        return make_zero_key();

    AuraOverrideKey k;
    memset(&k, 0, sizeof(k));

    fill_engine_fields(&k, manifest);
    k.binary_fingerprint = *fingerprint;
    k.target_kind        = AURA_OVERRIDE_TARGET_VARIABLE;

    /* Function anchor inherits from the owning function_id if available */
    if (record->function_id != AURA_NULL_ID)
        k.function_stable_id = (uint64_t)record->function_id;

    /* Variable stable id */
    if (record->var_id != AURA_NULL_ID) {
        k.target_stable_id = (uint64_t)record->var_id;
        /* Confidence follows function anchor strength, capped at STRONG
         * since var_id alone cannot guarantee EXACT without a function
         * engine stable id. Use EXACT only if both function_id and var_id
         * are provided by the engine. */
        if (record->function_id != AURA_NULL_ID)
            k.confidence = AURA_OVERRIDE_CONFIDENCE_EXACT;
        else
            k.confidence = AURA_OVERRIDE_CONFIDENCE_STRONG;
    } else if (record->name[0] != '\0') {
        k.target_stable_id = 0;
        k.confidence       = AURA_OVERRIDE_CONFIDENCE_WEAK;
    } else {
        k.confidence = AURA_OVERRIDE_CONFIDENCE_MISSING;
    }

    return k;
}

bool aura_override_fingerprint_match(
    const AuraOverrideBinaryFingerprint *a,
    const AuraOverrideBinaryFingerprint *b)
{
    if (!a || !b) return false;

    if (a->file_size != b->file_size) return false;
    if (memcmp(a->sha256, b->sha256, sizeof(a->sha256)) != 0) return false;
    if (strncmp(a->format_kind, b->format_kind, sizeof(a->format_kind)) != 0) return false;

    /* image_base: compare only if both are non-zero */
    if (a->image_base != 0 && b->image_base != 0
        && a->image_base != b->image_base)
        return false;

    /* text_section_hash: compare only if both are non-zero */
    static const uint8_t zero32[32] = {0};
    bool a_has_tsh = (memcmp(a->text_section_hash, zero32, 32) != 0);
    bool b_has_tsh = (memcmp(b->text_section_hash, zero32, 32) != 0);
    if (a_has_tsh && b_has_tsh
        && memcmp(a->text_section_hash, b->text_section_hash, 32) != 0)
        return false;

    return true;
}

bool aura_override_confidence_allows_auto_apply(AuraOverrideConfidence confidence)
{
    return confidence == AURA_OVERRIDE_CONFIDENCE_EXACT
        || confidence == AURA_OVERRIDE_CONFIDENCE_STRONG;
}

bool aura_override_key_same_target(
    const AuraOverrideKey *a,
    const AuraOverrideKey *b)
{
    if (!a || !b) return false;

    if (strncmp(a->engine_id, b->engine_id, sizeof(a->engine_id)) != 0) return false;
    if (!aura_override_fingerprint_match(&a->binary_fingerprint,
                                         &b->binary_fingerprint)) return false;
    if (a->request_type       != b->request_type)       return false;
    if (a->function_stable_id != b->function_stable_id) return false;
    if (a->target_kind        != b->target_kind)        return false;
    if (a->target_stable_id   != b->target_stable_id)   return false;

    return true;
}
