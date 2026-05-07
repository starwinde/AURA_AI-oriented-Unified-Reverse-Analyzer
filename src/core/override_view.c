// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * override_view.c — Phase 4C.1 display-layer view implementation.
 *
 * Snapshot index of ACTIVE override rows for a (fingerprint, engine)
 * pair. Rows are pulled from the store via the internal iterator
 * exposed by override_store.c.
 *
 * Lookup is linear; for the row counts expected per binary (tens to a
 * few hundred per engine) this is faster than a hashmap once cache
 * effects are accounted for. If profile data later disagrees, swap
 * to a hash table without touching the public API.
 */

#include "override_view.h"
#include "override_store_internal.h"

#include <stdlib.h>
#include <string.h>

struct AuraOverrideView {
    AuraOverrideStoreActiveRow *entries;
    size_t                      count;
    size_t                      cap;
};

static int append_cb(const AuraOverrideStoreActiveRow *row, void *user)
{
    AuraOverrideView *v = (AuraOverrideView *)user;
    if (v->count == v->cap) {
        size_t new_cap = v->cap ? v->cap * 2 : 8;
        AuraOverrideStoreActiveRow *resized =
            realloc(v->entries, new_cap * sizeof(AuraOverrideStoreActiveRow));
        if (!resized) return -1; /* abort iteration */
        v->entries = resized;
        v->cap     = new_cap;
    }
    v->entries[v->count++] = *row;
    return 0;
}

AuraOverrideView *aura_override_view_build(
    AuraOverrideStore                   *store,
    const AuraOverrideBinaryFingerprint *fp,
    const char                          *engine_id)
{
    if (!store || !fp || !engine_id) return NULL;

    AuraOverrideView *v = calloc(1, sizeof(*v));
    if (!v) return NULL;

    if (aura__override_store_iter_active(store, fp, engine_id,
                                         append_cb, v) != 0) {
        aura_override_view_destroy(v);
        return NULL;
    }
    return v;
}

size_t aura_override_view_count(const AuraOverrideView *view)
{
    return view ? view->count : 0u;
}

int aura_override_view_lookup(const AuraOverrideView *view,
                              uint64_t                function_stable_id,
                              AuraOverrideTargetKind  target_kind,
                              uint64_t                target_stable_id,
                              AuraOverridePayload    *out)
{
    if (!view || !out) return -1;

    for (size_t i = 0; i < view->count; i++) {
        const AuraOverrideStoreActiveRow *e = &view->entries[i];
        if (e->function_stable_id == function_stable_id
            && e->target_kind     == target_kind
            && e->target_stable_id == target_stable_id) {
            *out = e->payload;
            return 0;
        }
    }
    return 1;
}

void aura_override_view_destroy(AuraOverrideView *view)
{
    if (!view) return;
    free(view->entries);
    free(view);
}
