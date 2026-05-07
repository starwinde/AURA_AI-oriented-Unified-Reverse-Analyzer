// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_view.h — Phase 4C.1 display-layer view.
 *
 * AuraOverrideView is a read-only, in-memory index of ACTIVE overrides
 * for a specific (binary fingerprint, engine_id) pair. The view does
 * NOT mutate AuraEngineResponse.raw or .body (R-5); it sits on top of
 * the engine output as a lookup overlay used by the rendering layer.
 *
 * Construction snapshots the store's ACTIVE rows at build time. The
 * view does not observe later store mutations — callers rebuild the
 * view after store changes. This matches the typical render pipeline
 * (build view per frame / per pseudo-C re-emit).
 *
 * Out of scope (Phase 4D+):
 *   - Rename propagation across use-sites.
 *   - Type cast cascade.
 *   - Live observation of store mutations.
 */

#ifndef AURA_OVERRIDE_VIEW_H
#define AURA_OVERRIDE_VIEW_H

#include <stdint.h>

#include "override_identity.h"
#include "override_store.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AuraOverrideView AuraOverrideView;

/*
 * Build an in-memory view from the ACTIVE rows in `store` matching the
 * given fingerprint + engine_id. Returns NULL on argument or
 * allocation failure.
 *
 * The view holds copies; the caller may mutate `store` afterwards
 * without invalidating the view (subject to "rebuild to see changes").
 */
AuraOverrideView *aura_override_view_build(
    AuraOverrideStore                   *store,
    const AuraOverrideBinaryFingerprint *fp,
    const char                          *engine_id);

/*
 * Number of active overrides indexed in the view.
 */
size_t aura_override_view_count(const AuraOverrideView *view);

/*
 * Look up an applied override by (function_stable_id, target_kind,
 * target_stable_id).
 *
 * Returns:
 *    0 — found, *out filled.
 *    1 — not found.
 *   -1 — error (NULL args).
 */
int aura_override_view_lookup(const AuraOverrideView *view,
                              uint64_t                function_stable_id,
                              AuraOverrideTargetKind  target_kind,
                              uint64_t                target_stable_id,
                              AuraOverridePayload    *out);

/*
 * Free the view and all internal storage. NULL-safe.
 */
void aura_override_view_destroy(AuraOverrideView *view);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_OVERRIDE_VIEW_H */
