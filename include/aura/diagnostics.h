/*
 * diagnostics.h — Phase 3E sidecar diagnostic stream contract.
 *
 * AuraEngineResponse.diagnostics carries an optional, body-isolated stream
 * of mapping-loss visibility entries. Per Tasks.md Phase 3E and rules.md
 * R-9:
 *
 *   - Visibility ONLY. AURA does not use diagnostics to fix, merge,
 *     correct, or infer engine output.
 *   - body / pseudo-C / record fields and the diagnostic stream are
 *     completely isolated. NEVER inline a diagnostic warning into
 *     pseudo-C text or any record field.
 *   - reason_key is a stable string drawn from the AURA_DIAG_REASON_*
 *     dictionary below. Adding a new key requires confirming that the
 *     drop being surfaced is not itself a fix (R-9).
 *
 * Wire layout (AuraEngineResponse.diagnostics blob):
 *
 *   AuraDiagnosticsHeader          (16 bytes, magic / version / count)
 *   AuraDiagnosticEntry [count]    (fixed-size entries, no string pool)
 *
 * The blob is owned by the response and freed by
 * aura_engine_response_dispose() (orchestrator.c:61).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_DIAGNOSTICS_H
#define AURA_DIAGNOSTICS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Severity (Phase 3E: only `critical` is enforced) ────────────────── */

typedef enum AuraDiagnosticSeverity {
    AURA_DIAG_SEV_INFO     = 0,
    AURA_DIAG_SEV_WARNING  = 1,
    AURA_DIAG_SEV_CRITICAL = 2,
} AuraDiagnosticSeverity;

/* ── Reference kind (what `ref_id` points at) ────────────────────────── */

typedef enum AuraDiagnosticRefKind {
    AURA_DIAG_REF_NONE    = 0,
    AURA_DIAG_REF_REQUEST = 1, /* the originating AuraEngineRequest        */
    AURA_DIAG_REF_ADDR    = 2, /* a code address (ref_id = address)        */
    AURA_DIAG_REF_RECORD  = 3, /* an analyze record id                     */
} AuraDiagnosticRefKind;

/* ── Reason-key dictionary (stable strings, R-9 enforced) ────────────── */

/* Phase 3C re-definition: vendored aura-decompile emits Ghidra IR/SSA
 * XML, not PrettyPrint pseudo-C. The Ghidra adapter cannot fill the
 * decompile body view without violating R-9. This key surfaces that
 * mapping loss without synthesising one. */
#define AURA_DIAG_REASON_GHIDRA_PSEUDO_C_UNAVAILABLE \
    "ghidra_pseudo_c_unavailable"

/* Phase 3E.2 reason keys reserved for future Ghidra IR-loss surfaces.
 * Values defined here for stability — emission added when the underlying
 * IR mapper exists (3C2 / Phase 4+). */
#define AURA_DIAG_REASON_ADDRESS_SPACE_DROPPED "address_space_dropped"
#define AURA_DIAG_REASON_INDIRECT_OP           "indirect_op"
#define AURA_DIAG_REASON_PARAM_TRUNCATED       "param_truncated"
#define AURA_DIAG_REASON_JUMPTABLE_DROPPED     "jumptable_dropped"
#define AURA_DIAG_REASON_SEQNUM_COLLISION      "seqnum_collision"

/* ── Wire layout ─────────────────────────────────────────────────────── */

#define AURA_DIAG_BLOB_MAGIC   0xAFAA3E01u
#define AURA_DIAG_BLOB_VERSION 1u

#define AURA_DIAG_REASON_KEY_MAX 64u /* incl. trailing NUL */

typedef struct AuraDiagnosticsHeader {
    uint32_t magic;     /* AURA_DIAG_BLOB_MAGIC                         */
    uint32_t version;   /* AURA_DIAG_BLOB_VERSION                       */
    uint32_t count;     /* number of trailing AuraDiagnosticEntry      */
    uint32_t reserved;  /* must be 0                                   */
} AuraDiagnosticsHeader;

typedef struct AuraDiagnosticEntry {
    char     reason_key[AURA_DIAG_REASON_KEY_MAX]; /* NUL-terminated  */
    uint32_t severity;  /* AuraDiagnosticSeverity                       */
    uint32_t ref_kind;  /* AuraDiagnosticRefKind                        */
    uint64_t ref_id;    /* depends on ref_kind                          */
} AuraDiagnosticEntry;

/* ── View helpers (read-side; allocate-side is in src/core/diagnostics.c) */

/* Returns 0 on success and fills `out_header` / `out_entries` as aliases
 * into `blob`. No copy. Returns non-zero when:
 *   - blob is NULL or blob_size < sizeof(AuraDiagnosticsHeader)
 *   - magic / version mismatch
 *   - blob_size < expected payload (header + count*sizeof(entry))
 *
 * On error all out-pointers are zeroed. */
int aura_diagnostics_view(const void                   *blob,
                          size_t                        blob_size,
                          const AuraDiagnosticsHeader **out_header,
                          const AuraDiagnosticEntry   **out_entries);

/* Allocate a single-critical-entry blob and return it via *out_blob /
 * *out_size. Caller (the orchestrator/response disposer) frees with
 * free(*out_blob). Returns 0 on success, non-zero on alloc failure or
 * invalid args (NULL reason_key, key too long, etc.). */
int aura_diagnostics_alloc_critical(const char            *reason_key,
                                    AuraDiagnosticRefKind  ref_kind,
                                    uint64_t               ref_id,
                                    void                 **out_blob,
                                    size_t                *out_size);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_DIAGNOSTICS_H */
