// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_resolve.c — Phase 4C.2 auto-apply gate implementation.
 *
 * Pure structural decision over two AuraOverrideKey instances. No
 * record collection traversal, no new analysis (R-9). Caller is
 * expected to have already derived `fresh` from current engine output.
 */

#include "override_resolve.h"

AuraOverrideResolveOutcome aura_override_resolve(
    const AuraOverrideKey *stored,
    const AuraOverrideKey *fresh)
{
    /* Fail-safe: any missing stored key is ORPHAN — never auto-apply
     * against an unknown stored side. */
    if (!stored) return AURA_OVERRIDE_RESOLVE_ORPHAN;

    /* Fresh missing or fresh is MISSING confidence → ORPHAN. */
    if (!fresh) return AURA_OVERRIDE_RESOLVE_ORPHAN;
    if (fresh->confidence == AURA_OVERRIDE_CONFIDENCE_MISSING)
        return AURA_OVERRIDE_RESOLVE_ORPHAN;

    /* Fingerprint mismatch — binary changed. The stored override target
     * may still exist semantically in the new binary, but the AURA
     * silent-misapply policy forbids auto-applying across binaries.
     * Promote to CONFLICT so the user can review and re-apply
     * explicitly (Phase 4E decision, 2026-05-02). */
    if (!aura_override_fingerprint_match(&stored->binary_fingerprint,
                                         &fresh->binary_fingerprint))
        return AURA_OVERRIDE_RESOLVE_CONFLICT;

    /* Same target identity required for APPLY. If the engine identity
     * + fingerprint match but the function/target stable ids shifted,
     * the override has drifted onto a different target — CONFLICT. */
    if (!aura_override_key_same_target(stored, fresh))
        return AURA_OVERRIDE_RESOLVE_CONFLICT;

    /* Both confidences must clear the auto-apply threshold (4A.4).
     * If fresh dropped below STRONG → CONFLICT (target identified but
     * weakly). Stored side is informational; the policy is gated on
     * the re-analyzed confidence. */
    if (!aura_override_confidence_allows_auto_apply(fresh->confidence))
        return AURA_OVERRIDE_RESOLVE_CONFLICT;

    /* Stored confidence was already validated at insert time, but
     * preserve the gate here for symmetry. */
    if (!aura_override_confidence_allows_auto_apply(stored->confidence))
        return AURA_OVERRIDE_RESOLVE_CONFLICT;

    return AURA_OVERRIDE_RESOLVE_APPLY;
}
