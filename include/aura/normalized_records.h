/*
 * normalized_records.h — AURA 1급 normalized records (Phase 2A).
 *
 * Engine-agnostic record types produced by third_party_hub adapters
 * (Rizin, Ghidra, ...). Per rules.md:
 *
 *   R-11 — every record carries an AuraProvenance (source / confidence
 *          / completeness). Records with empty provenance MUST be
 *          rejected at collection insert time.
 *
 *   R-12 — function / block / edge / variable / type-fact / call-edge
 *          / symbol / xref are independent records. FunctionRecord
 *          MUST NOT embed variables / types / calls as nested arrays.
 *          Cross-record references go through stable IDs only
 *          (function_id / block_id / var_id).
 *
 * The 8 records form the schema; this header is the single source of
 * truth for their layout. Adapters fill them; consumers read them.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_NORMALIZED_RECORDS_H
#define AURA_NORMALIZED_RECORDS_H

#include <stddef.h>
#include <stdint.h>

/* C++ doesn't recognize C11's _Static_assert keyword; map it to the C++
 * equivalent so this header is includable from C++ TU's (e.g. the
 * orchestrator_smoke gate, doctest-based). */
#if defined(__cplusplus) && !defined(_Static_assert)
#define _Static_assert static_assert
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ── Provenance (R-11) ─────────────────────────────────────────────── */

/* source     — engine_id of the producer ("rizin", "ghidra", ...).
 *              Empty string = invalid; insert MUST reject.
 * confidence — [0.0, 1.0]. <0 invalid.
 * completeness — [0.0, 1.0]. <0 invalid. 1.0 = engine reported full
 *                data for this record's domain (e.g. all CFG edges
 *                seen); <1.0 = adapter knows it dropped or could not
 *                reconstruct fields.
 *
 * Adapters MUST populate before insert. The collection layer enforces
 * non-empty source and non-negative confidence/completeness. */
typedef struct AuraProvenance {
    char  source[16];
    float confidence;
    float completeness;
} AuraProvenance;

/* Convenience: zero-init helper. */
static inline void aura_provenance_clear(AuraProvenance *p)
{
    if (!p) return;
    p->source[0]   = '\0';
    p->confidence  = 0.0f;
    p->completeness = 0.0f;
}

/* ── Stable IDs ────────────────────────────────────────────────────── */

/* 0 is the "null" sentinel (no such record). Real IDs start at 1. */
typedef uint32_t AuraFunctionId;
typedef uint32_t AuraBlockId;
typedef uint32_t AuraVariableId;
typedef uint32_t AuraSymbolId;
typedef uint32_t AuraStringId;

#define AURA_NULL_ID 0u

/* ── 8 first-class records (R-12) ──────────────────────────────────── */

/* FunctionRecord — function-level facts ONLY.
 *
 * R-12 invariants (enforced by tests/adapter/rizin/test_rizin_record_shape.c):
 *   - First field MUST be `provenance`.
 *   - MUST NOT contain variables[], types[], calls[], xrefs[] arrays
 *     or pointers. Such facts live in their own records and reference
 *     this function via function_id.
 */
typedef struct AuraFunctionRecord {
    AuraProvenance provenance; /* R-11/R-12: first field, mandatory     */
    AuraFunctionId function_id;
    uint64_t       entry;      /* engine-reported entry address          */
    uint64_t       size;       /* engine-reported byte size; 0 = unknown */
    char           name[128];  /* engine-reported symbol; "" = unnamed   */
} AuraFunctionRecord;

typedef struct AuraBlockRecord {
    AuraProvenance provenance;
    AuraBlockId    block_id;
    AuraFunctionId function_id; /* owning function                       */
    uint64_t       start_addr;
    uint64_t       end_addr;    /* exclusive                              */
} AuraBlockRecord;

typedef enum AuraEdgeKind {
    AURA_EDGE_UNKNOWN     = 0,
    AURA_EDGE_FALLTHROUGH = 1,
    AURA_EDGE_JUMP        = 2,
    AURA_EDGE_BRANCH_TRUE = 3,
    AURA_EDGE_BRANCH_FALSE = 4,
    AURA_EDGE_CALL        = 5,
    AURA_EDGE_RETURN      = 6,
} AuraEdgeKind;

typedef struct AuraEdgeRecord {
    AuraProvenance provenance;
    AuraBlockId    src_block;
    AuraBlockId    dst_block;
    AuraEdgeKind   kind;
} AuraEdgeRecord;

typedef struct AuraVariableRecord {
    AuraProvenance provenance;
    AuraVariableId var_id;
    AuraFunctionId function_id; /* owner                                  */
    char           name[64];
    int32_t        stack_offset; /* INT32_MIN = N/A (register var, etc.)  */
    char           kind[8];     /* "stack"/"reg"/"arg" — engine-reported  */
} AuraVariableRecord;

/* TypeFactRecord — one engine-reported type assignment.
 *
 * Decoupled from VariableRecord per R-12 so multi-source type
 * propagation can layer evidence without touching variable identity. */
typedef struct AuraTypeFactRecord {
    AuraProvenance provenance;
    AuraVariableId var_id;     /* subject; AURA_NULL_ID = function-return */
    AuraFunctionId function_id;
    char           type_str[64]; /* engine-reported type literal           */
} AuraTypeFactRecord;

typedef struct AuraCallEdgeRecord {
    AuraProvenance provenance;
    AuraFunctionId caller_id;
    AuraFunctionId callee_id;   /* AURA_NULL_ID if unresolved (indirect)   */
    uint64_t       site_addr;   /* call instruction address                */
} AuraCallEdgeRecord;

typedef enum AuraSymbolKind {
    AURA_SYMBOL_UNKNOWN  = 0,
    AURA_SYMBOL_FUNCTION = 1,
    AURA_SYMBOL_OBJECT   = 2,
    AURA_SYMBOL_SECTION  = 3,
    AURA_SYMBOL_IMPORT   = 4,
} AuraSymbolKind;

typedef struct AuraSymbolRecord {
    AuraProvenance provenance;
    AuraSymbolId   symbol_id;
    uint64_t       addr;
    AuraSymbolKind kind;
    char           name[128];
} AuraSymbolRecord;

typedef enum AuraXrefKind {
    AURA_XREF_UNKNOWN = 0,
    AURA_XREF_DATA    = 1,
    AURA_XREF_CODE    = 2,
    AURA_XREF_CALL    = 3,
} AuraXrefKind;

typedef struct AuraXrefRecord {
    AuraProvenance provenance;
    uint64_t       from_addr;
    uint64_t       to_addr;
    AuraXrefKind   kind;
} AuraXrefRecord;

/* InstructionRecord — engine-reported single instruction within a function.
 *
 * Phase 11.3.7 (P2.F2): per ADR-0040, this is a 10th 1급 record carrying
 * the structured fields rizin `pdfj` already exposes (mnemonic / op_str /
 * bytes / type / jump / fail). Storing as one blob would force re-parsing
 * downstream (R-9 violation); structured fields let label-suggestion (PP4),
 * search-by-mnemonic, and CFG edge resolution read what they need.
 *
 * `bytes[]` is the engine's contiguous hex string ("4889e5"); display layer
 * pretty-prints spacing ("48 89 e5"). `addr` is unique within the owning
 * function — there is no separate instruction_id (addr serves as key).
 */
typedef struct AuraInstructionRecord {
    AuraProvenance provenance;     /* R-11/R-12 first field, mandatory     */
    AuraFunctionId function_id;    /* owning function (AURA_NULL_ID = ?)   */
    uint64_t       addr;
    uint32_t       size;           /* instruction byte length              */
    uint32_t       _pad;           /* explicit padding for stable layout   */
    char           bytes[24];      /* hex string e.g. "4889e5"             */
    char           mnemonic[16];   /* "mov", "call", "jmp", ...            */
    char           op_str[96];     /* "rbp, rsp"                            */
    char           type[16];       /* pdj.type: "mov"|"jmp"|"call"|...     */
    uint64_t       jump;           /* taken target (0 if N/A)              */
    uint64_t       fail;           /* not-taken (0 if N/A)                 */
} AuraInstructionRecord;

/* StringRecord — engine-reported literal in the binary's data sections.
 *
 * Phase 11.3.6: surfaces rizin `izj` output as a 1급 record so the GUI
 * Strings dock, label-suggestion (PP4), and LLM context payloads share
 * one source of truth. Per R-1/R-9: AURA does NOT scan binaries for
 * strings on its own — every record here originates from an external
 * engine's bulk JSON (rizin `izj` for now).
 *
 * `content[]` carries an engine-reported text snippet (NUL-terminated,
 * truncated to 127 bytes — long literals are presented up to that
 * limit; the engine raw layer retains the full bytes if needed).
 */
typedef enum AuraStringEncoding {
    AURA_STRING_ENC_UNKNOWN = 0,
    AURA_STRING_ENC_ASCII   = 1,
    AURA_STRING_ENC_UTF8    = 2,
    AURA_STRING_ENC_UTF16LE = 3,
    AURA_STRING_ENC_UTF16BE = 4,
    AURA_STRING_ENC_WIDE    = 5, /* engine-reported "wide" w/o LE/BE qual. */
} AuraStringEncoding;

typedef struct AuraStringRecord {
    AuraProvenance     provenance;  /* R-11/R-12: first field, mandatory  */
    AuraStringId       string_id;
    uint64_t           addr;        /* engine-reported VA of the literal  */
    uint64_t           length;      /* engine-reported byte length        */
    AuraStringEncoding encoding;
    char               section[16]; /* engine-reported section name; ""=N/A */
    char               content[128]; /* NUL-terminated; trailing 127 bytes */
} AuraStringRecord;

/* ── Compile-time R-11/R-12 enforcement ────────────────────────────── */

/* "provenance must be the first field" — testable, future-proof against
 * accidental field reorder. */
_Static_assert(offsetof(AuraFunctionRecord,  provenance) == 0,
               "R-11/R-12: AuraFunctionRecord.provenance must be first");
_Static_assert(offsetof(AuraBlockRecord,     provenance) == 0,
               "R-11/R-12: AuraBlockRecord.provenance must be first");
_Static_assert(offsetof(AuraEdgeRecord,      provenance) == 0,
               "R-11/R-12: AuraEdgeRecord.provenance must be first");
_Static_assert(offsetof(AuraVariableRecord,  provenance) == 0,
               "R-11/R-12: AuraVariableRecord.provenance must be first");
_Static_assert(offsetof(AuraTypeFactRecord,  provenance) == 0,
               "R-11/R-12: AuraTypeFactRecord.provenance must be first");
_Static_assert(offsetof(AuraCallEdgeRecord,  provenance) == 0,
               "R-11/R-12: AuraCallEdgeRecord.provenance must be first");
_Static_assert(offsetof(AuraSymbolRecord,    provenance) == 0,
               "R-11/R-12: AuraSymbolRecord.provenance must be first");
_Static_assert(offsetof(AuraXrefRecord,      provenance) == 0,
               "R-11/R-12: AuraXrefRecord.provenance must be first");
_Static_assert(offsetof(AuraStringRecord,    provenance) == 0,
               "R-11/R-12: AuraStringRecord.provenance must be first");
_Static_assert(offsetof(AuraInstructionRecord, provenance) == 0,
               "R-11/R-12: AuraInstructionRecord.provenance must be first");

/* ── Collection container ──────────────────────────────────────────── */

/* Engine-agnostic in-memory bag of records. Adapters fill it; the hub
 * mapping layer is the only writer. Consumers read via the count/at
 * accessors below.
 *
 * This is intentionally not a polyglot heterogeneous container: each
 * record kind has its own dynamic array, which keeps R-12 honest
 * (you cannot accidentally stuff a variable into a function slot). */
typedef struct AuraRecordCollection AuraRecordCollection;

AuraRecordCollection *aura_records_create(void);
void                  aura_records_destroy(AuraRecordCollection *c);

/* ID issuers. Return AURA_NULL_ID iff `c == NULL`. IDs are unique
 * within a collection but not across collections. */
AuraFunctionId aura_records_alloc_function_id(AuraRecordCollection *c);
AuraBlockId    aura_records_alloc_block_id   (AuraRecordCollection *c);
AuraVariableId aura_records_alloc_variable_id(AuraRecordCollection *c);
AuraSymbolId   aura_records_alloc_symbol_id  (AuraRecordCollection *c);
AuraStringId   aura_records_alloc_string_id  (AuraRecordCollection *c);

/* Insert APIs. Each validates `provenance` per R-11:
 *   - source[0] != '\0'
 *   - confidence in [0.0, 1.0]
 *   - completeness in [0.0, 1.0]
 * On failure → returns -1 and the record is NOT stored.
 * On success → returns 0 and the record is copied into the collection. */
int aura_records_add_function (AuraRecordCollection *c, const AuraFunctionRecord *r);
int aura_records_add_block    (AuraRecordCollection *c, const AuraBlockRecord    *r);
int aura_records_add_edge     (AuraRecordCollection *c, const AuraEdgeRecord     *r);
int aura_records_add_variable (AuraRecordCollection *c, const AuraVariableRecord *r);
int aura_records_add_type_fact(AuraRecordCollection *c, const AuraTypeFactRecord *r);
int aura_records_add_call_edge(AuraRecordCollection *c, const AuraCallEdgeRecord *r);
int aura_records_add_symbol   (AuraRecordCollection *c, const AuraSymbolRecord   *r);
int aura_records_add_xref     (AuraRecordCollection *c, const AuraXrefRecord     *r);
int aura_records_add_string   (AuraRecordCollection *c, const AuraStringRecord   *r);
int aura_records_add_instruction(AuraRecordCollection *c, const AuraInstructionRecord *r);

/* Read accessors. Return record count / pointer to internal storage.
 * Pointers remain valid until the next insert into the same array or
 * collection destroy. Callers MUST NOT mutate. */
size_t                       aura_records_function_count (const AuraRecordCollection *c);
const AuraFunctionRecord    *aura_records_function_at    (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_block_count    (const AuraRecordCollection *c);
const AuraBlockRecord       *aura_records_block_at       (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_edge_count     (const AuraRecordCollection *c);
const AuraEdgeRecord        *aura_records_edge_at        (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_variable_count (const AuraRecordCollection *c);
const AuraVariableRecord    *aura_records_variable_at    (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_type_fact_count(const AuraRecordCollection *c);
const AuraTypeFactRecord    *aura_records_type_fact_at   (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_call_edge_count(const AuraRecordCollection *c);
const AuraCallEdgeRecord    *aura_records_call_edge_at   (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_symbol_count   (const AuraRecordCollection *c);
const AuraSymbolRecord      *aura_records_symbol_at      (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_xref_count     (const AuraRecordCollection *c);
const AuraXrefRecord        *aura_records_xref_at        (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_string_count   (const AuraRecordCollection *c);
const AuraStringRecord      *aura_records_string_at      (const AuraRecordCollection *c, size_t i);
size_t                       aura_records_instruction_count(const AuraRecordCollection *c);
const AuraInstructionRecord *aura_records_instruction_at  (const AuraRecordCollection *c, size_t i);

/* Validation helper exposed for tests. Returns 1 iff `p` satisfies R-11. */
int aura_provenance_is_valid(const AuraProvenance *p);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_NORMALIZED_RECORDS_H */
