/*
 * rizin_adapter.h — Rizin engine adapter (Phase 2A).
 *
 * Public surface: manifest, vtable, registration helper, and the
 * normalized analyze-response body. NO Rizin canonical types or rizin
 * subprocess details cross this boundary (R-10).
 *
 * Phase 2A request scope:
 *   AURA_ENGINE_REQ_ANALYZE — bulk JSON analyze (aaa+aflj+isj+iij+izj),
 *                             returns flat function + symbol records.
 *   Other request types     → AURA_ENGINE_ERR_UNSUPPORTED.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_ADAPTER_H
#define AURA_RIZIN_ADAPTER_H

#include <stddef.h>
#include <stdint.h>

#include "aura/normalized_records.h"
#include "engine_manifest.h"
#include "engine_request.h"
#include "orchestrator.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Optional adapter configuration. Pass NULL to use environment / PATH. */
typedef struct AuraRizinAdapterConfig {
    const char *exec_path; /* override for the rizin binary               */
    int         timeout_s; /* per-request wall-clock; 0 = adapter default */
} AuraRizinAdapterConfig;

/* Analyze response body — single contiguous malloc so the orchestrator's
 * default `free(body)` disposer reclaims everything. Arrays follow the
 * header in memory; access via the helpers below.
 *
 * Layout (v2, all in one allocation):
 *   [AuraRizinAnalyzeBody header]
 *   [AuraFunctionRecord  functions [functions_count ]]
 *   [AuraSymbolRecord    symbols   [symbols_count   ]]
 *   [AuraBlockRecord     blocks    [blocks_count    ]]
 *   [AuraEdgeRecord      edges     [edges_count     ]]
 *   [AuraVariableRecord  variables [variables_count ]]
 *   [AuraTypeFactRecord  type_facts[type_facts_count]]
 *   [AuraCallEdgeRecord  call_edges[call_edges_count]]
 *   [AuraXrefRecord      xrefs     [xrefs_count     ]]
 *   [AuraStringRecord    strings   [strings_count   ]]   (v3+)
 *
 * Schema versioning:
 *   v2 — initial 8-record body (Phase 2A).
 *   v3 — Phase 11.3.6: appended `strings[]` (rizin `izj`). Older
 *        consumers reading a v3 body remain valid for the v2 prefix;
 *        new consumers MUST guard `strings_count` access on
 *        `version >= 3` before dereferencing.
 */
#define AURA_RIZIN_ANALYZE_BODY_MAGIC   0xAFAA2A01u
#define AURA_RIZIN_ANALYZE_BODY_VERSION 3u

typedef struct AuraRizinAnalyzeBody {
    uint32_t magic;            /* AURA_RIZIN_ANALYZE_BODY_MAGIC          */
    uint32_t version;          /* AURA_RIZIN_ANALYZE_BODY_VERSION        */
    size_t   functions_count;
    size_t   symbols_count;
    size_t   blocks_count;
    size_t   edges_count;
    size_t   variables_count;
    size_t   type_facts_count;
    size_t   call_edges_count;
    size_t   xrefs_count;
    size_t   strings_count;    /* v3+: rizin izj literal count           */
} AuraRizinAnalyzeBody;

const AuraFunctionRecord *
aura_rizin_analyze_body_functions(const AuraRizinAnalyzeBody *b);

const AuraSymbolRecord *
aura_rizin_analyze_body_symbols(const AuraRizinAnalyzeBody *b);

const AuraBlockRecord *
aura_rizin_analyze_body_blocks(const AuraRizinAnalyzeBody *b);

const AuraEdgeRecord *
aura_rizin_analyze_body_edges(const AuraRizinAnalyzeBody *b);

const AuraVariableRecord *
aura_rizin_analyze_body_variables(const AuraRizinAnalyzeBody *b);

const AuraTypeFactRecord *
aura_rizin_analyze_body_type_facts(const AuraRizinAnalyzeBody *b);

const AuraCallEdgeRecord *
aura_rizin_analyze_body_call_edges(const AuraRizinAnalyzeBody *b);

const AuraXrefRecord *
aura_rizin_analyze_body_xrefs(const AuraRizinAnalyzeBody *b);

/* v3+: returns NULL when version < 3 or strings_count == 0. */
const AuraStringRecord *
aura_rizin_analyze_body_strings(const AuraRizinAnalyzeBody *b);

/* ── Phase 2B decompile response body ────────────────────────────────── */

/* Backend stamp in the body — values mirror AuraRizinDecompileBackend
 * defined in src/adapter/rizin/rizin_decompile_caps.h (kept internal so
 * R-10 isolation holds). The numeric values are part of the public body
 * contract: clients can read body->backend without including any
 * adapter-internal header.
 *
 *   0 = NONE  (invalid — should never appear in a well-formed body)
 *   1 = PDGJ  (rz-ghidra JSON     → source = "rizin/pdgj")
 *   2 = PDDJ  (jsdec JSON         → source = "rizin/pddj")
 *   3 = PDD   (jsdec text fallback → source = "rizin/pdd")
 */
#define AURA_RIZIN_DEC_BACKEND_NONE 0u
#define AURA_RIZIN_DEC_BACKEND_PDGJ 1u
#define AURA_RIZIN_DEC_BACKEND_PDDJ 2u
#define AURA_RIZIN_DEC_BACKEND_PDD  3u
#define AURA_RIZIN_DEC_BACKEND_PDF  4u  /* Phase 11.3.1.1 disasm fallback */

typedef struct AuraRizinDecompileLineMap {
    uint32_t line; /* 1-based line number within body_text                */
    uint32_t pad;  /* explicit padding for stable layout / alignment      */
    uint64_t addr; /* engine-reported address mapped to this line         */
} AuraRizinDecompileLineMap;

/* Single-allocation layout (caller frees with free(body)):
 *   [AuraRizinDecompileBody header]
 *   [char body_text[body_text_len + 1]  — NUL-terminated]
 *   [<padding to align(8)>]
 *   [AuraRizinDecompileLineMap line_map[line_map_count]]
 *
 * Use the accessor helpers to obtain the embedded buffers. The
 * `body_text_len` excludes the trailing NUL (strlen-style). */
#define AURA_RIZIN_DECOMPILE_BODY_MAGIC   0xAFAA2B01u
#define AURA_RIZIN_DECOMPILE_BODY_VERSION 1u

typedef struct AuraRizinDecompileBody {
    uint32_t magic;          /* AURA_RIZIN_DECOMPILE_BODY_MAGIC           */
    uint32_t version;        /* AURA_RIZIN_DECOMPILE_BODY_VERSION         */
    uint32_t backend;        /* AURA_RIZIN_DEC_BACKEND_*                  */
    uint32_t reserved;       /* explicit alignment slot                   */
    uint64_t function_addr;  /* request address (verbatim from CLI/req)   */
    size_t   body_text_len;  /* strlen(body_text), no NUL                 */
    size_t   line_map_count; /* may be 0 (esp. for PDD text fallback)     */
    float    confidence;     /* per-backend default (R-11)                */
    float    completeness;   /* fraction of code with addr mapping        */
} AuraRizinDecompileBody;

/* Returns NUL-terminated pseudo-C body text, or "" if magic invalid. */
const char *aura_rizin_decompile_body_text(const AuraRizinDecompileBody *b);

/* Returns the line map array (line_map_count entries). May be NULL when
 * line_map_count == 0 (e.g. PDD text fallback). */
const AuraRizinDecompileLineMap *
aura_rizin_decompile_body_line_map(const AuraRizinDecompileBody *b);

/* Stable provenance source string per backend. Returns "" for NONE/unknown.
 *   PDGJ → "rizin/pdgj"
 *   PDDJ → "rizin/pddj"
 *   PDD  → "rizin/pdd"
 */
const char *aura_rizin_decompile_backend_source(uint32_t backend);

/* ── Phase 11.3.7 (P2.F2) disassembly response body ────────────────────
 *
 * Per ADR-0040: separate body (NOT an analyze-body bump) so analyze
 * latency stays bounded; instructions are fetched on-demand per
 * function. Single-allocation layout (caller frees with free(body)):
 *
 *   v1: [AuraRizinDisasmBody header]
 *       [AuraInstructionRecord instructions[instructions_count]]
 *
 *   v2 (Phase 11.6 T1): same layout + a NUL-terminated text blob
 *       appended after the instructions[] array. The blob is rizin's
 *       `pdf` annotated disassembly with `asm.lines=true` (the gutter
 *       flow arrows you'd see in Cutter or `rizin -c pdf`).
 *
 *       [AuraRizinDisasmBody header]
 *       [AuraInstructionRecord instructions[instructions_count]]
 *       [char text[text_size]]                  // includes trailing \0
 *
 *       text_size INCLUDES the trailing NUL. text_size == 0 means the
 *       text blob is absent (parse failure or older adapter).
 *
 * Accessor returns NULL for invalid magic or empty body.
 */
#define AURA_RIZIN_DISASM_BODY_MAGIC   0xAFAA2C01u
#define AURA_RIZIN_DISASM_BODY_VERSION 2u

typedef struct AuraRizinDisasmBody {
    uint32_t magic;             /* AURA_RIZIN_DISASM_BODY_MAGIC          */
    uint32_t version;           /* AURA_RIZIN_DISASM_BODY_VERSION        */
    uint64_t function_addr;     /* request key (verbatim from CLI/RPC)   */
    size_t   instructions_count;
    size_t   text_size;         /* v2+: bytes incl. trailing \0; 0 = N/A */
} AuraRizinDisasmBody;

typedef enum AuraRizinDisasmMode {
    AURA_RIZIN_DISASM_MODE_FUNCTION = 0, /* default: pdfj/pdf at function */
    AURA_RIZIN_DISASM_MODE_WINDOW   = 1, /* pdj count at arbitrary addr   */
    AURA_RIZIN_DISASM_MODE_TEXT_RANGE = 2, /* pD byte range at arbitrary addr */
} AuraRizinDisasmMode;

typedef struct AuraRizinDisasmOptions {
    AuraRizinDisasmMode mode;
    uint32_t            instruction_count; /* WINDOW only */
    uint32_t            byte_count;        /* TEXT_RANGE only */
} AuraRizinDisasmOptions;

const AuraInstructionRecord *
aura_rizin_disasm_body_instructions(const AuraRizinDisasmBody *b);

/* v2+: returns a pointer into the body's appended text blob (NUL-
 * terminated rizin `pdf` annotated disassembly with flow arrows).
 * Returns NULL when version < 2, text_size == 0, or magic mismatch. */
const char *
aura_rizin_disasm_body_text(const AuraRizinDisasmBody *b);

/* Phase 11.3.4 batch decompile — single Rizin subprocess invocation that
 * decompiles many functions at once, populating an array of bodies.
 *
 *   exec_path      : path to rizin executable (NULL → PATH lookup)
 *   binary_path    : binary to analyze
 *   addr_list      : array of `n` function entry addresses (uint64)
 *   n              : number of addresses (must be > 0)
 *   timeout_s      : per-subprocess wall clock; 0 = adapter default 60s
 *   out_bodies     : caller-provided array of length `n`; on success each
 *                    slot points at a heap AuraRizinDecompileBody*
 *                    (caller frees with free()). Slots for which the
 *                    decompile produced no usable body are set to NULL.
 *   out_backend    : on success, the chosen backend (PDGJ/PDDJ/PDD/PDF)
 *
 * Returns:
 *    0  on overall success (subprocess + framing OK; per-frame body
 *        allocation may have failed individually — those slots are NULL).
 *   -1  on argument / subprocess / framing failure (no slots populated).
 *
 * Backend selection follows aura_rizin_decompile_select_backend() —
 * caps detection runs once on the first call (cached subsequently). */
int aura_rizin_decompile_batch_run(
    const char            *exec_path,
    const char            *binary_path,
    const uint64_t        *addr_list,
    size_t                 n,
    int                    timeout_s,
    struct AuraRizinDecompileBody **out_bodies,
    uint32_t              *out_backend);

/* Adapter manifest + vtable (static storage, lifetime = process). */
const AuraEngineManifest *aura_rizin_adapter_manifest(void);
const AuraEngineAdapter  *aura_rizin_adapter_vtable(void);

/* Register the rizin adapter with `orch`. Stashes `cfg` (shallow-copied)
 * into a static slot consulted by init(); pass NULL for defaults.
 *
 * Returns 0 on success, negative on failure (mirrors
 * aura_orchestrator_register). */
int aura_orchestrator_register_rizin(
    AuraOrchestrator             *orch,
    const AuraRizinAdapterConfig *cfg_or_null);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_ADAPTER_H */
