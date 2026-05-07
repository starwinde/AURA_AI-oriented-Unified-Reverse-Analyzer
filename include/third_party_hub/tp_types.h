/*
 * tp_types.h — AURA Third-Party I/O Hub: shared scalar / container types.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * This header defines the foundational mirror types used by every
 * adapter contract in the hub: addresses, source provenance tags,
 * error codes, and the type-erased vector container that mirrors
 * `RzList` / `RzVector` shape without depending on Rizin headers.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_TP_TYPES_H
#define AURA_TP_TYPES_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Mirror of Rizin `ut64`. All addresses in the hub are virtual. */
typedef uint64_t aura_tp_addr_t;

/* Provenance tag: which adapter populated a payload. Stable values —
 * referenced by registry lookup and AUTO dispatch order. */
typedef enum aura_tp_source_t {
    AURA_TP_SOURCE_UNKNOWN     = 0,
    AURA_TP_SOURCE_AURA_NATIVE = 1,
    AURA_TP_SOURCE_RIZIN       = 2,
    AURA_TP_SOURCE_CAPSTONE    = 3,
    AURA_TP_SOURCE_ZYDIS       = 4,
    AURA_TP_SOURCE_GHIDRA      = 5,
    AURA_TP_SOURCE_YARA        = 6,
    AURA_TP_SOURCE__COUNT      = 7  /* keep last */
} aura_tp_source_t;

/* Capability flags. Adapters declare which fn-ptrs they implement. */
typedef enum aura_tp_caps_t {
    AURA_TP_CAP_NONE          = 0u,
    AURA_TP_CAP_DISASM_RANGE  = 1u << 0,
    AURA_TP_CAP_LIST_FUNCS    = 1u << 1,
    AURA_TP_CAP_LIST_SECTIONS = 1u << 2
} aura_tp_caps_t;

/* Error codes. Negative = error; 0 = OK; positive = partial-success
 * count (e.g. ops emitted before short-circuit). */
#define AURA_TP_OK            0
#define AURA_TP_E_INVAL      -1   /* NULL input or malformed args        */
#define AURA_TP_E_NOMEM      -2   /* allocation failure                  */
#define AURA_TP_E_NOTSUP     -3   /* adapter / capability not registered */
#define AURA_TP_E_DUP        -4   /* duplicate adapter source            */
#define AURA_TP_E_FULL       -5   /* registry full                       */
#define AURA_TP_E_RANGE      -6   /* address / length out of bounds      */

/* Type-erased contiguous vector — mirrors `RzVector` shape.
 *
 * Layout is POD. Caller owns the storage lifecycle:
 *   aura_tp_vec_init(v, sizeof(T));
 *   aura_tp_vec_push(v, &elem);
 *   aura_tp_vec_free(v);
 *
 * `data` holds `len` consecutively-packed elements of `elem_size`
 * bytes each; capacity is in elements. Adapters allocate elements
 * directly into the vector to avoid a copy round-trip. */
typedef struct aura_tp_vec_t {
    void   *data;
    size_t  elem_size;
    size_t  len;
    size_t  cap;
} aura_tp_vec_t;

int    aura_tp_vec_init   (aura_tp_vec_t *v, size_t elem_size);
int    aura_tp_vec_reserve(aura_tp_vec_t *v, size_t want_cap);
int    aura_tp_vec_push   (aura_tp_vec_t *v, const void *elem);
void  *aura_tp_vec_at     (const aura_tp_vec_t *v, size_t idx);
void   aura_tp_vec_free   (aura_tp_vec_t *v);

#ifdef __cplusplus
}
#endif

#endif /* AURA_TP_TYPES_H */
