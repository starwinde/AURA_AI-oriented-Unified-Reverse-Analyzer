/*
 * tp_vec.c — AURA Third-Party I/O Hub: type-erased vector container.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * Minimal contiguous vector. No element destructors — POD only.
 * Growth policy: cap doubles, with a 4-element minimum on first push.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "third_party_hub/tp_types.h"

#include <stdlib.h>
#include <string.h>

int aura_tp_vec_init(aura_tp_vec_t *v, size_t elem_size)
{
    if (!v || elem_size == 0) return AURA_TP_E_INVAL;
    v->data      = NULL;
    v->elem_size = elem_size;
    v->len       = 0;
    v->cap       = 0;
    return AURA_TP_OK;
}

int aura_tp_vec_reserve(aura_tp_vec_t *v, size_t want_cap)
{
    if (!v || v->elem_size == 0) return AURA_TP_E_INVAL;
    if (want_cap <= v->cap) return AURA_TP_OK;

    /* overflow guard on byte size */
    if (want_cap > (SIZE_MAX / v->elem_size)) return AURA_TP_E_NOMEM;

    void *p = realloc(v->data, want_cap * v->elem_size);
    if (!p) return AURA_TP_E_NOMEM;
    v->data = p;
    v->cap  = want_cap;
    return AURA_TP_OK;
}

int aura_tp_vec_push(aura_tp_vec_t *v, const void *elem)
{
    if (!v || !elem || v->elem_size == 0) return AURA_TP_E_INVAL;

    if (v->len == v->cap) {
        size_t new_cap = v->cap ? v->cap * 2 : 4;
        int rc = aura_tp_vec_reserve(v, new_cap);
        if (rc != AURA_TP_OK) return rc;
    }

    memcpy((char *)v->data + v->len * v->elem_size, elem, v->elem_size);
    v->len++;
    return AURA_TP_OK;
}

void *aura_tp_vec_at(const aura_tp_vec_t *v, size_t idx)
{
    if (!v || !v->data || idx >= v->len) return NULL;
    return (char *)v->data + idx * v->elem_size;
}

void aura_tp_vec_free(aura_tp_vec_t *v)
{
    if (!v) return;
    free(v->data);
    v->data = NULL;
    v->len  = 0;
    v->cap  = 0;
}
