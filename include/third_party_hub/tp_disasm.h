/*
 * tp_disasm.h — AURA Third-Party I/O Hub: disasm op mirror type.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * `aura_tp_op_t` mirrors `RzAnalysisOp` shape — one decoded
 * instruction. POD layout, no embedded pointers that the hub itself
 * owns; if an adapter needs to expose mnemonic / operand strings, it
 * keeps them in adapter-local storage and the op holds a borrowed
 * pointer (lifetime tied to the adapter context).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_TP_DISASM_H
#define AURA_TP_DISASM_H

#include <stddef.h>
#include <stdint.h>

#include "tp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct aura_tp_op_t {
    aura_tp_addr_t   va;        /* virtual address of this op            */
    uint8_t          size;      /* encoded length in bytes (≤15 x86)     */
    uint8_t          _pad[3];
    uint32_t         id;        /* engine-internal opcode id (cs_insn.id)*/
    aura_tp_source_t source;    /* who produced this op                  */
    const char      *mnemonic;  /* borrowed (adapter-owned)              */
    const char      *op_str;    /* borrowed (adapter-owned)              */
} aura_tp_op_t;

#ifdef __cplusplus
}
#endif

#endif /* AURA_TP_DISASM_H */
