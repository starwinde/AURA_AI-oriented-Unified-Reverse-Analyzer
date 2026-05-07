// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_identity.h — Phase 4A Stable Identity Contract
 *
 * Defines the stable key used to identify an override target across
 * re-analysis runs. All fields are derived from existing engine record
 * fields — no new analysis is performed here (R-9).
 *
 * Confidence policy (4A.3 / 4A.4):
 *   EXACT   — engine-provided stable id + binary fingerprint match.
 *             Auto-apply on re-analysis: YES.
 *   STRONG  — binary_fingerprint + engine_id + function address/range +
 *             target address/storage + provenance source match.
 *             Auto-apply on re-analysis: YES.
 *   WEAK    — name / index / estimated position only.
 *             Auto-apply: NO. Must be promoted to conflict for UI review.
 *   MISSING — target not found after re-analysis.
 *             Auto-apply: NO. Preserved as orphan.
 *
 * Silent misapply is forbidden: if confidence < STRONG, the override
 * must NOT be applied automatically and MUST be preserved in a
 * conflict/orphan state for explicit user resolution.
 *
 * Overlay boundary (4A.X4):
 *   AuraEngineResponse.raw and .body are immutable from AURA's
 *   perspective. Override application produces a separate display-layer
 *   view (AuraOverrideView, Phase 4C). No mutation of engine output here.
 */

#ifndef AURA_OVERRIDE_IDENTITY_H
#define AURA_OVERRIDE_IDENTITY_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "aura/normalized_records.h"  /* AuraFunctionRecord, AuraVariableRecord,
                                         AuraFunctionId, AuraVariableId,
                                         AuraProvenance, AURA_NULL_ID */
#include "engine_request.h"           /* AuraEngineRequestType */
#include "engine_manifest.h"          /* AuraEngineManifest */

#ifdef __cplusplus
extern "C" {
#endif

/* ─────────────────────────────────────────────────────────────────────
 * 4A.X1 — Binary Fingerprint
 *
 * Outermost guard for auto-apply. If binary_fingerprint differs from
 * the stored key's fingerprint, auto-apply is forbidden regardless of
 * any other field match.
 *
 * fingerprint is an identifier, not an analysis result (R-9).
 * ───────────────────────────────────────────────────────────────────── */

typedef struct AuraOverrideBinaryFingerprint {
    uint64_t file_size;
    uint8_t  sha256[32];
    char     format_kind[8];           /* "elf" / "pe" / "mach-o" / "unknown" */
    uint64_t image_base;               /* 0 = unknown / not applicable */
    uint8_t  text_section_hash[32];    /* all-zero = not computed */
} AuraOverrideBinaryFingerprint;

/* ─────────────────────────────────────────────────────────────────────
 * 4A.1 — Override Target Kind
 * ───────────────────────────────────────────────────────────────────── */

typedef enum AuraOverrideTargetKind {
    AURA_OVERRIDE_TARGET_FUNCTION   = 0,
    AURA_OVERRIDE_TARGET_VARIABLE   = 1,
    AURA_OVERRIDE_TARGET_TYPE       = 2,
    AURA_OVERRIDE_TARGET_ANNOTATION = 3,
    AURA_OVERRIDE_TARGET_ADDRESS    = 4,
    AURA_OVERRIDE_TARGET_SYMBOL     = 5,
} AuraOverrideTargetKind;

/* ─────────────────────────────────────────────────────────────────────
 * 4A.3 — Confidence
 * ───────────────────────────────────────────────────────────────────── */

typedef enum AuraOverrideConfidence {
    AURA_OVERRIDE_CONFIDENCE_EXACT   = 0,
    AURA_OVERRIDE_CONFIDENCE_STRONG  = 1,
    AURA_OVERRIDE_CONFIDENCE_WEAK    = 2,
    AURA_OVERRIDE_CONFIDENCE_MISSING = 3,
} AuraOverrideConfidence;

/* ─────────────────────────────────────────────────────────────────────
 * 4A.2 + 4A.X3 — Stable Key
 *
 * All char[] fields are null-terminated; strncpy is used during
 * construction to ensure no overflow and guaranteed termination.
 *
 * function_stable_id priority (4A.X2):
 *   1. record->function_id != AURA_NULL_ID  → EXACT
 *   2. entry + size + provenance.source     → STRONG
 *   3. entry + size + name                  → WEAK
 *   4. none of the above                    → MISSING, id = 0
 *
 * target_addr and engine_record_source_id are optional (0 = absent).
 * ───────────────────────────────────────────────────────────────────── */

typedef struct AuraOverrideKey {
    /* Engine identity (4A.X3) */
    char                          engine_id[32];
    char                          engine_version[32];
    uint32_t                      body_schema_version;
    uint32_t                      normalized_record_schema_version;

    /* Request context */
    AuraEngineRequestType         request_type;

    /* Binary anchor (4A.X1) */
    AuraOverrideBinaryFingerprint binary_fingerprint;

    /* Function anchor (4A.X2) */
    uint64_t                      function_stable_id;

    /* Target */
    AuraOverrideTargetKind        target_kind;
    uint64_t                      target_stable_id;
    uint64_t                      target_addr;              /* 0 = absent */

    /* Engine record linkage */
    uint64_t                      engine_record_source_id;  /* 0 = absent */

    /* Match quality */
    AuraOverrideConfidence        confidence;
} AuraOverrideKey;

/* ─────────────────────────────────────────────────────────────────────
 * Helper API
 *
 * All functions are pure data assembly from existing record fields.
 * No new analysis, no CFG, no type inference (R-9).
 * ───────────────────────────────────────────────────────────────────── */

/*
 * Build a stable key for a function-level override target.
 * confidence is derived automatically from 4A.X2 priority.
 * Returns a zero-initialized key with confidence=MISSING if any of
 * record, manifest, or fingerprint is NULL.
 */
AuraOverrideKey aura_override_key_from_function_record(
    const AuraFunctionRecord            *record,
    const AuraEngineManifest            *manifest,
    const AuraOverrideBinaryFingerprint *fingerprint);

/*
 * Build a stable key for a variable-level override target.
 * target_kind is set to AURA_OVERRIDE_TARGET_VARIABLE.
 * confidence is derived from the variable's function anchor first,
 * then var_id availability.
 * Returns zero key with confidence=MISSING on NULL input.
 */
AuraOverrideKey aura_override_key_from_variable_record(
    const AuraVariableRecord            *record,
    const AuraEngineManifest            *manifest,
    const AuraOverrideBinaryFingerprint *fingerprint);

/*
 * Exact binary comparison of two fingerprints.
 * Compares file_size, sha256[32], and format_kind.
 * text_section_hash and image_base are included only if both are
 * non-zero / non-empty respectively.
 */
bool aura_override_fingerprint_match(
    const AuraOverrideBinaryFingerprint *a,
    const AuraOverrideBinaryFingerprint *b);

/*
 * Returns true only for EXACT and STRONG.
 * WEAK and MISSING must never be auto-applied (4A.4).
 */
bool aura_override_confidence_allows_auto_apply(AuraOverrideConfidence confidence);

/*
 * Returns true if two keys refer to the same override target.
 * Compares: engine_id, binary_fingerprint (via fingerprint_match),
 * request_type, function_stable_id, target_kind, target_stable_id.
 * confidence is intentionally excluded — the same target may have
 * different confidence after re-analysis.
 */
bool aura_override_key_same_target(
    const AuraOverrideKey *a,
    const AuraOverrideKey *b);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_OVERRIDE_IDENTITY_H */
