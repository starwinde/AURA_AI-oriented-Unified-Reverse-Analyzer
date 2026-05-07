// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_resolve.h — Phase 4C.2 auto-apply gate.
 *
 * Pure function that compares a stored AuraOverrideKey (persisted by
 * Phase 4B store) against a fresh key derived from a re-analysis run,
 * and decides whether the override may be auto-applied, must be
 * promoted to a conflict, or has been orphaned.
 *
 * The decision is purely structural — no new analysis is performed
 * (R-9). The fresh key must already have been built via
 * aura_override_key_from_function_record / _from_variable_record.
 *
 * Outcome semantics (Phase 4E decision, 2026-05-02 — conservative):
 *   APPLY    — fingerprint matches AND keys identify the same target
 *              AND both stored and fresh confidence >= STRONG.
 *   CONFLICT — fingerprint matches but the target identity shifted, OR
 *              fresh confidence dropped below STRONG, OR fingerprint
 *              differs (binary changed; user must re-apply explicitly).
 *              Never auto-applied (silent-misapply policy).
 *   ORPHAN   — fresh key is NULL OR fresh confidence is MISSING.
 *              Target absent from the re-analyzed records.
 *
 * Maps cleanly onto AuraOverrideStatus:
 *   APPLY    → AURA_OVERRIDE_STATUS_ACTIVE
 *   CONFLICT → AURA_OVERRIDE_STATUS_CONFLICT
 *   ORPHAN   → AURA_OVERRIDE_STATUS_ORPHAN
 */

#ifndef AURA_OVERRIDE_RESOLVE_H
#define AURA_OVERRIDE_RESOLVE_H

#include "override_identity.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AuraOverrideResolveOutcome {
    AURA_OVERRIDE_RESOLVE_APPLY    = 0,
    AURA_OVERRIDE_RESOLVE_CONFLICT = 1,
    AURA_OVERRIDE_RESOLVE_ORPHAN   = 2,
} AuraOverrideResolveOutcome;

/*
 * Compare a stored override key against a fresh key from re-analysis.
 *
 * `fresh` may be NULL to signal "target no longer derivable from fresh
 * records" — this is treated as ORPHAN.
 *
 * On any NULL `stored` the function returns ORPHAN (fail-safe: never
 * auto-apply against an unknown stored target).
 */
AuraOverrideResolveOutcome aura_override_resolve(
    const AuraOverrideKey *stored,
    const AuraOverrideKey *fresh);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_OVERRIDE_RESOLVE_H */
