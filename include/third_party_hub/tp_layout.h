/*
 * tp_layout.h — AURA Third-Party I/O Hub: section / function mirrors.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * `aura_tp_section_t` mirrors `RzBinSection`; `aura_tp_function_t`
 * mirrors `RzAnalysisFunction`. Both are POD with borrowed string
 * pointers (adapter context owns the backing storage).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_TP_LAYOUT_H
#define AURA_TP_LAYOUT_H

#include <stddef.h>
#include <stdint.h>

#include "tp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct aura_tp_section_t {
    aura_tp_addr_t   vaddr;    /* virtual base address                  */
    aura_tp_addr_t   paddr;    /* file offset (0 if BSS-like)           */
    uint64_t         vsize;    /* in-memory size                        */
    uint64_t         psize;    /* on-disk size                          */
    uint32_t         perm;     /* R/W/X bitmask (engine-defined)        */
    aura_tp_source_t source;
    const char      *name;     /* borrowed (adapter-owned)              */
} aura_tp_section_t;

typedef struct aura_tp_function_t {
    aura_tp_addr_t   entry;    /* function entry VA                     */
    uint64_t         size;     /* total span in bytes (0 if unknown)    */
    aura_tp_source_t source;
    const char      *name;     /* borrowed (adapter-owned)              */
} aura_tp_function_t;

#ifdef __cplusplus
}
#endif

#endif /* AURA_TP_LAYOUT_H */
