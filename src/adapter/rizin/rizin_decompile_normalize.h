/*
 * rizin_decompile_normalize.h — pdgj/pddj/pdd → AuraRizinDecompileBody.
 *
 * Phase 2B.3: produces the single-allocation decompile body from the raw
 * engine output. Each backend has its own input shape:
 *
 *   PDGJ : cJSON object {"code": "<source>", "annotations": [...]}.
 *          Real schema captured from rz-ghidra HEAD on rizin 0.9.0
 *          (WSL Ubuntu, 2026-05-01) — see test fixture comments.
 *
 *   PDD  : raw text (no JSON). Body text is a verbatim copy of the raw
 *          stdout slice; line_map is empty (count=0). This is the
 *          documented text fallback for jsdec.
 *
 *   PDDJ : not supported in this implementation. jsdec is not installed
 *          in the verification environment, so its JSON schema has not
 *          been captured. Returning ERR_BAD_BACKEND keeps us honest —
 *          no fake parser. Wire-up lands when jsdec is verified.
 *
 * Internal to src/adapter/rizin/. Do NOT include from core / gui.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_DECOMPILE_NORMALIZE_H
#define AURA_RIZIN_DECOMPILE_NORMALIZE_H

#include <stddef.h>
#include <stdint.h>

#include "cJSON.h"
#include "rizin_adapter.h"          /* AuraRizinDecompileBody, magic   */
#include "rizin_decompile_caps.h"   /* AuraRizinDecompileBackend       */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AuraRizinDecompileNormStatus {
    AURA_RIZIN_DEC_NORM_OK             = 0,
    AURA_RIZIN_DEC_NORM_ERR_INVALID    = 1, /* NULL inputs / inconsistent  */
    AURA_RIZIN_DEC_NORM_ERR_BAD_BACKEND = 2, /* backend not implemented    */
    AURA_RIZIN_DEC_NORM_ERR_PARSE      = 3, /* JSON missing required keys  */
    AURA_RIZIN_DEC_NORM_ERR_OOM        = 4,
} AuraRizinDecompileNormStatus;

/* Confidence/completeness defaults per backend (R-11 provenance).
 * Documented here so the test can assert exact values. */
#define AURA_RIZIN_DEC_PDGJ_CONFIDENCE 0.90f
#define AURA_RIZIN_DEC_PDDJ_CONFIDENCE 0.70f
#define AURA_RIZIN_DEC_PDD_CONFIDENCE  0.50f
#define AURA_RIZIN_DEC_PDF_CONFIDENCE  0.30f  /* disasm, not pseudo-C */

/* Build a body from rz-ghidra's pdgj JSON.
 *
 *   pdgj_root      : a cJSON object with "code" (string) and
 *                    "annotations" (array). Caller retains ownership;
 *                    we read but do not free.
 *   function_addr  : verbatim from the request (echoed into body).
 *   out_body       : on OK, *out_body is a heap allocation; caller frees
 *                    with free(*out_body). On error, *out_body is NULL.
 */
AuraRizinDecompileNormStatus aura_rizin_normalize_decompile_pdgj(
    const cJSON                 *pdgj_root,
    uint64_t                     function_addr,
    AuraRizinDecompileBody     **out_body);

/* Build a body from jsdec's plain-text pdd output.
 *
 *   raw_text       : pseudo-C body as emitted by `pdd`. May contain any
 *                    non-NUL bytes; we copy raw_text_len chars verbatim.
 *   raw_text_len   : strlen-style; 0 is valid (produces empty body).
 *   line_map_count is always 0 for this backend.
 */
AuraRizinDecompileNormStatus aura_rizin_normalize_decompile_pdd(
    const char                  *raw_text,
    size_t                       raw_text_len,
    uint64_t                     function_addr,
    AuraRizinDecompileBody     **out_body);

/* Phase 11.3.1.1 (ADR-0036): PDF disasm fallback. Same passthrough
 * shape as PDD (raw text body, empty line map) but body backend stamp
 * is AURA_RIZIN_DEC_BACKEND_PDF and confidence is AURA_RIZIN_DEC_PDF_
 * CONFIDENCE so the UI can label it as disassembly, not pseudo-C. */
AuraRizinDecompileNormStatus aura_rizin_normalize_decompile_pdf(
    const char                  *raw_text,
    size_t                       raw_text_len,
    uint64_t                     function_addr,
    AuraRizinDecompileBody     **out_body);

/* Polymorphic dispatcher — routes to the per-backend impl based on
 * `backend`. Inputs not relevant to the chosen backend are ignored.
 *
 *   PDGJ → uses json_root_or_null
 *   PDDJ → returns ERR_BAD_BACKEND
 *   PDD  → uses raw_text + raw_text_len
 *   any other value (incl. NONE) → ERR_BAD_BACKEND
 */
AuraRizinDecompileNormStatus aura_rizin_decompile_normalize(
    AuraRizinDecompileBackend    backend,
    uint64_t                     function_addr,
    const cJSON                 *json_root_or_null,
    const char                  *raw_text_or_null,
    size_t                       raw_text_len,
    AuraRizinDecompileBody     **out_body);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_DECOMPILE_NORMALIZE_H */
