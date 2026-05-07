/*
 * rizin_disasm_normalize.h — Phase 11.3.7 (P2.F2 C2).
 *
 * pdfj cJSON tree → AuraRizinDisasmBody single-allocation body.
 *
 * pdfj output shape (Rizin v0.8 baseline):
 *   {
 *     "name": "fcn.00400000",
 *     "size": 30,
 *     "addr": 4194304,
 *     "ops": [
 *       { "offset": 4194304, "size": 1, "bytes": "55",
 *         "opcode": "push rbp", "type": "rpush", ... },
 *       { "offset": 4194305, "size": 3, "bytes": "4889e5",
 *         "opcode": "mov rbp, rsp", "type": "mov", "jump": <addr?>, ... }
 *     ]
 *   }
 *
 * AURA does not invent fields — every InstructionRecord field is read
 * directly from pdfj (R-1/R-9 enforced by isolation in this file +
 * handle_disasm in rizin_adapter.c).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_DISASM_NORMALIZE_H
#define AURA_RIZIN_DISASM_NORMALIZE_H

#include <stddef.h>
#include <stdint.h>

#include "rizin_adapter.h" /* AuraRizinDisasmBody */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AuraRizinDisasmNormStatus {
    AURA_RIZIN_DISASM_NORM_OK         = 0,
    AURA_RIZIN_DISASM_NORM_ERR_NULL   = 1, /* NULL inputs                */
    AURA_RIZIN_DISASM_NORM_ERR_SHAPE  = 2, /* pdfj root not an object/no ops */
    AURA_RIZIN_DISASM_NORM_ERR_OOM    = 3, /* alloc failed               */
} AuraRizinDisasmNormStatus;

/* Parse a pdfj cJSON root and emit a single-allocation
 * AuraRizinDisasmBody (header + InstructionRecord array + optional
 * trailing text blob). The caller frees `*out_body` with free().
 *
 * function_addr — caller-provided request key (verbatim into header).
 * pdfj_root     — cJSON tree from rizin's framed pdfj frame.
 * pdf_text      — Phase 11.6 T1: NUL-terminated rizin `pdf` annotated
 *                 disassembly text (asm.lines flow arrows). May be
 *                 NULL or empty — body emits text_size=0 in that case.
 * pdf_text_len  — byte length of pdf_text excluding any NUL. Ignored
 *                 when pdf_text is NULL.
 * out_body      — receives malloc'd body on success; untouched on error. */
AuraRizinDisasmNormStatus aura_rizin_disasm_normalize(
    uint64_t                  function_addr,
    const void               *pdfj_root,        /* const cJSON *       */
    const char               *pdf_text,         /* may be NULL          */
    size_t                    pdf_text_len,
    AuraRizinDisasmBody     **out_body);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_DISASM_NORMALIZE_H */
