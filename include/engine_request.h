/*
 * engine_request.h — AURA Engine Adapter Contract (Phase 1).
 *
 * Engine-agnostic request / response schema for all external analysis
 * engines (Ghidra primary, Rizin / RetDec / Capstone secondary). Per
 * Tasks.md Phase 1 spec:
 *
 *   1.2 Request Types        — disasm / analyze / decompile / trace.
 *   1.3 IPC schema           — request body MUST carry a `type` field;
 *                              response keeps both normalized body AND
 *                              the engine's raw response (R-4 non-discard).
 *   1.5 Adapter interface    — single entry point with three function
 *                              pointers (init / request / shutdown).
 *
 * This header defines only the contract. Concrete adapter implementations
 * live in src/adapter/<engine>/. Subprocess primitives (Tasks.md 1.1) and
 * Ghidra-specific decoding live in their own headers and are NOT pulled
 * in here, to keep this contract engine-neutral.
 *
 * Memory ownership rule (R-4): for an AuraEngineResponse populated by an
 * adapter, the adapter mallocs `body` and `raw` (when non-NULL) and the
 * orchestrator (or any direct caller) MUST release them via
 * aura_engine_response_dispose(). The adapter never frees its own output.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_ENGINE_REQUEST_H
#define AURA_ENGINE_REQUEST_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Request types (Tasks.md 1.2) ───────────────────────────────────── */

/* The four standard request types. rules.md R-7 forbids defining,
 * aliasing, or synthesizing any additional request type. The numeric
 * values are stable: they are used as bit positions in
 * AuraEngineManifest.supported_types (1u << type). */
typedef enum AuraEngineRequestType {
    AURA_ENGINE_REQ_DISASM    = 0, /* per-instruction disassembly         */
    AURA_ENGINE_REQ_ANALYZE   = 1, /* functions / symbols / CFG / types   */
    AURA_ENGINE_REQ_DECOMPILE = 2, /* Pseudo-C output                     */
    AURA_ENGINE_REQ_TRACE     = 3, /* engine-provided def-use relations   */
} AuraEngineRequestType;

/* All known request type bits. Used by manifest validation to reject
 * supported_types bitmasks that include any non-standard bit (R-7). */
#define AURA_ENGINE_REQ_TYPE_MASK_ALL \
    ((1u << AURA_ENGINE_REQ_DISASM)    | \
     (1u << AURA_ENGINE_REQ_ANALYZE)   | \
     (1u << AURA_ENGINE_REQ_DECOMPILE) | \
     (1u << AURA_ENGINE_REQ_TRACE))

/* ── Standard adapter / orchestrator status codes (Tasks.md 1.7) ──── */

/* Engine-agnostic outcome of one request. Concrete adapters MAY map a
 * richer engine-native status onto these values; the orchestrator only
 * sees this enum so a single failure path applies to every engine. */
typedef enum AuraEngineStatus {
    AURA_ENGINE_OK              = 0,
    AURA_ENGINE_ERR_UNSUPPORTED = 1, /* request type not in manifest    */
    AURA_ENGINE_ERR_INVALID     = 2, /* malformed request / bad args    */
    AURA_ENGINE_ERR_TIMEOUT     = 3, /* engine exceeded deadline        */
    AURA_ENGINE_ERR_CRASH       = 4, /* engine subprocess crashed       */
    AURA_ENGINE_ERR_NOT_FOUND   = 5, /* no engine registered for route  */
    AURA_ENGINE_ERR_INTERNAL    = 6, /* orchestrator / adapter bug      */
} AuraEngineStatus;

/* ── Request / Response schema (Tasks.md 1.3) ──────────────────────── */

/* Phase 11.3 (ADR-0035): analysis depth toggle for ANALYZE requests.
 * Engine-neutral; each adapter maps to its own command sequence. The
 * default stays Full (Rizin `aaa`) for backward compatibility with
 * Phase 10/11.1/11.4 callers using zero-init. */
typedef enum AuraAnalysisLevel {
    AURA_ANALYSIS_LEVEL_FULL     = 0, /* default — Rizin `aaa`             */
    AURA_ANALYSIS_LEVEL_QUICK    = 1, /* faster, shallower — Rizin `aa`    */
    AURA_ANALYSIS_LEVEL_ADVANCED = 2, /* aggressive/deeper — Rizin `aaaa`  */
} AuraAnalysisLevel;

/* AuraEngineRequest carries the request type plus a small set of
 * engine-neutral inputs every analysis request needs (binary path, an
 * address, an optional architecture hint). Engine-specific fields are
 * passed via the opaque `payload` slot, which adapters interpret.
 *
 * `analysis_level` is consulted only when type == ANALYZE; ignored for
 * other request types. Default value 0 == FULL preserves prior behavior
 * for all existing zero-init callers. */
typedef struct AuraEngineRequest {
    AuraEngineRequestType type;       /* required (1.3 schema spec)     */
    const char           *binary_path;/* path to the binary on disk     */
    uint64_t              addr;       /* function / instruction address */
    const char           *arch_or_null;/* "x86_64", "AArch64", ... or NULL*/
    const void           *payload;    /* engine-specific extra args     */
    size_t                payload_size;
    AuraAnalysisLevel     analysis_level; /* ANALYZE-only, default FULL */
} AuraEngineRequest;

/* AuraEngineResponse holds two parallel views of the engine answer plus
 * an optional sidecar diagnostic stream:
 *
 *   body / body_size — type-specific normalized result. Per Phase 3A the
 *                      concrete contract is:
 *
 *                        AURA_ENGINE_REQ_ANALYZE   →
 *                            AuraRizinAnalyzeBody (single-blob, 8
 *                            first-class records — see
 *                            include/aura/normalized_records.h, R-11 /
 *                            R-12).
 *                        AURA_ENGINE_REQ_DECOMPILE →
 *                            backend-specific payload whose first 16
 *                            bytes are the AuraDecompileBodyHeader view
 *                            prefix (include/aura/decompile_body.h).
 *                            Layouts: AuraRizinDecompileBody (Rizin) +
 *                            AuraGhidraDecompileBody (Ghidra, Phase 3C).
 *                        AURA_ENGINE_REQ_DISASM, AURA_ENGINE_REQ_TRACE →
 *                            body MUST be NULL / body_size 0 (Phase 3
 *                            does not define a typed body for these).
 *
 *                      Body fields MUST originate from the engine
 *                      response. AURA does not synthesise CFGs, IRs,
 *                      types, dataflow, call graphs, or function
 *                      boundaries (R-9). Pseudo-C / line maps are taken
 *                      directly from engine output (R-4).
 *
 *   raw  / raw_size  — the engine's unmodified output (XML / JSON /
 *                      text). Preserved verbatim per R-4 (no discard,
 *                      no rewrite) so consumers can always re-derive
 *                      fields the normaliser dropped.
 *
 *   diagnostics /
 *   diagnostics_size — optional sidecar stream for mapping-loss
 *                      visibility (Phase 3E). Layout: array of
 *                      AuraDiagnosticEntry (include/aura/diagnostics.h).
 *                      MUST stay isolated from body — never inline
 *                      diagnostic warnings into Pseudo-C text or any
 *                      record field. Visibility only: AURA never uses
 *                      diagnostics to correct, merge, or infer engine
 *                      output.
 *
 * All three pointers are owned by the response and released by
 * aura_engine_response_dispose(). */
typedef struct AuraEngineResponse {
    AuraEngineRequestType type;     /* mirrors request type */
    AuraEngineStatus      status;
    void                 *body;     /* typed body — see contract above */
    size_t                body_size;
    void                 *raw;      /* engine-native bytes (R-4) */
    size_t                raw_size;
    void                 *diagnostics;     /* optional sidecar (Phase 3E) */
    size_t                diagnostics_size;
} AuraEngineResponse;

/* Free both `body` and `raw` (if non-NULL) and zero the struct. Safe to
 * call on a zero-initialized response (no-ops on NULL). */
void aura_engine_response_dispose(AuraEngineResponse *response);

/* ── Adapter vtable (Tasks.md 1.5) ─────────────────────────────────── */

/* Three-function descriptor every engine adapter exports. The
 * orchestrator calls these and nothing else; engines must not be reached
 * by any other path (rules.md R-6).
 *
 *   init      — allocate adapter context. Returns 0 on success and
 *               writes the context handle into *adapter_ctx_out. The
 *               handle is opaque to the orchestrator.
 *
 *   request   — handle one request. Adapter populates `out` (status,
 *               body, raw) per the ownership rule above. Returning
 *               anything other than AURA_ENGINE_OK MUST still leave
 *               `out` in a disposable state.
 *
 *   shutdown  — release the context. Called exactly once during
 *               aura_orchestrator_destroy(). May be NULL for adapters
 *               that hold no state.
 */
typedef struct AuraEngineAdapter {
    int               (*init)(void **adapter_ctx_out);
    AuraEngineStatus  (*request)(void                    *adapter_ctx,
                                 const AuraEngineRequest *req,
                                 AuraEngineResponse      *out);
    void              (*shutdown)(void *adapter_ctx);
} AuraEngineAdapter;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_ENGINE_REQUEST_H */
