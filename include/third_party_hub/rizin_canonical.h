/*
 * rizin_canonical.h — Rizin canonical mirror types (third-party hub layer).
 *
 * R-10 exception zone (PRD 2026-04-30 decision):
 *   This is the ONLY public header allowed to declare Rizin-shaped types
 *   for the rest of the build. It exists so that the canonical→normalized
 *   mapping in src/third_party_hub/rizin_to_aura.c can compile without
 *   leaking adapter internals upward.
 *
 *   The Rizin adapter (src/adapter/rizin/) populates these structs from
 *   parsed bulk JSON; the hub consumes them and emits AURA normalized
 *   records (include/aura/normalized_records.h). NOTHING else in the
 *   build is permitted to include this header.
 *
 * Field naming mirrors Rizin's JSON command output names verbatim where
 * practical (offset/size/jump/fail/nbbs/vaddr) so reviewers can trace a
 * field back to its rizin command (`aflj`, `agfj`, `isj`, `izj`, etc.).
 *
 * String fields are *immutable views* into the owning AuraRizinSnapshot's
 * raw_buffer — they are NOT NUL-terminated; use the paired `_len` field.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_THIRD_PARTY_HUB_RIZIN_CANONICAL_H
#define AURA_THIRD_PARTY_HUB_RIZIN_CANONICAL_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── aflj: function list ─────────────────────────────────────────────── */

typedef struct AuraRizinCanonFunction {
    uint64_t    offset;     /* entry address (aflj.offset)                */
    uint64_t    size;       /* function bytes (aflj.size; 0 if unknown)   */
    int         nbbs;       /* basic block count (aflj.nbbs; 0 if absent) */
    const char *name;       /* immutable view; not NUL-terminated         */
    size_t      name_len;
    const char *type;       /* "fcn" | "sym" | "loc" | "" (aflj.type)     */
    size_t      type_len;
} AuraRizinCanonFunction;

/* ── agfj: per-function basic-block CFG ──────────────────────────────── */

typedef struct AuraRizinCanonBlock {
    uint64_t addr;          /* block start  (agfj.blocks[].offset)        */
    uint64_t size;          /* block bytes  (agfj.blocks[].size)          */
    uint64_t jump;          /* taken target  (agfj.blocks[].jump; 0 = -)  */
    uint64_t fail;          /* not-taken     (agfj.blocks[].fail; 0 = -)  */
} AuraRizinCanonBlock;

typedef struct AuraRizinCanonCfg {
    uint64_t              function_addr; /* matches the agfj target     */
    AuraRizinCanonBlock  *blocks;
    size_t                blocks_count;
} AuraRizinCanonCfg;

/* ── isj: symbol table ───────────────────────────────────────────────── */

typedef struct AuraRizinCanonSymbol {
    uint64_t    vaddr;      /* isj.vaddr                                  */
    uint64_t    paddr;      /* isj.paddr (0 if absent)                    */
    uint64_t    size;       /* isj.size  (0 if absent)                    */
    const char *name;       /* isj.name; immutable view                   */
    size_t      name_len;
    const char *type;       /* "FUNC" | "OBJECT" | "NOTYPE" | …           */
    size_t      type_len;
    const char *bind;       /* "GLOBAL" | "LOCAL" | "WEAK"                */
    size_t      bind_len;
    int         is_imported;/* 1 if marked as imported                    */
} AuraRizinCanonSymbol;

/* ── axtj: xrefs to an address ───────────────────────────────────────── */

typedef struct AuraRizinCanonXref {
    uint64_t    from;       /* xref source address                        */
    uint64_t    to;         /* target (matches the queried function addr) */
    const char *type;       /* "CALL" | "JMP" | "DATA" | "STRING" …       */
    size_t      type_len;
} AuraRizinCanonXref;

/* ── izj: literal strings table (Phase 11.3.6) ───────────────────────── */

typedef struct AuraRizinCanonString {
    uint64_t    vaddr;       /* izj.vaddr — virtual address of literal     */
    uint64_t    paddr;       /* izj.paddr (0 if absent)                    */
    uint64_t    length;      /* izj.length — character count               */
    uint64_t    size;        /* izj.size   — byte count incl. terminator   */
    const char *type;        /* "ascii" | "utf8" | "utf16le" | "utf16be" | "wide" */
    size_t      type_len;
    const char *section;     /* izj.section — e.g. ".rodata"; "" if absent */
    size_t      section_len;
    const char *string;      /* izj.string — content view (NOT NUL-terminated) */
    size_t      string_len;
} AuraRizinCanonString;

/* ── afvj: function variables / arguments ────────────────────────────── */

typedef struct AuraRizinCanonVariable {
    const char *name;
    size_t      name_len;
    const char *kind;       /* "reg" | "stack" | "bp" | "sp"              */
    size_t      kind_len;
    const char *type;       /* C type spelling (or "" if unknown)         */
    size_t      type_len;
    int64_t     stack_offset; /* signed; only meaningful when kind=stack  */
    int         is_arg;     /* 1 if formal argument                       */
} AuraRizinCanonVariable;

/* ── aftj: function type signature (skeleton) ────────────────────────── */

typedef struct AuraRizinCanonTypeSig {
    const char *return_type;
    size_t      return_type_len;
    const char *name;       /* function name in signature (often == aflj.name) */
    size_t      name_len;
    /* Argument types are derived from afvj for Phase 2A; aftj parsing
     * stays a skeleton until Phase 2B fleshes out the type system. */
} AuraRizinCanonTypeSig;

/* ── top-level canonical bundle ──────────────────────────────────────── */

/* Lifetime: owned by the producer (rizin_snapshot.c). All variable-length
 * arrays and string buffers point either into the owning AuraRizinSnapshot
 * (immutable views) or into snapshot-allocated arrays. The hub MUST treat
 * this struct as read-only. */
typedef struct AuraRizinCanonical {
    AuraRizinCanonFunction *functions;
    size_t                  functions_count;

    AuraRizinCanonSymbol   *symbols;
    size_t                  symbols_count;

    /* Per-function ancillary data (Phase 2A: at most one populated set;
     * Phase 2B will widen). cfgs[i] / xrefs[i] / variables[i] correspond
     * by function_addr, not by position in functions[]. */
    AuraRizinCanonCfg      *cfgs;
    size_t                  cfgs_count;

    AuraRizinCanonXref     *xrefs;
    size_t                  xrefs_count;

    AuraRizinCanonVariable *variables;
    size_t                  variables_count;

    /* The variable-to-function join key. Length == variables_count; entry
     * i is the function entry address that owns variables[i]. */
    uint64_t               *variables_function_addr;

    /* Phase 11.3.6: izj literal strings (file-wide, not per-function). */
    AuraRizinCanonString   *strings;
    size_t                  strings_count;
} AuraRizinCanonical;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_THIRD_PARTY_HUB_RIZIN_CANONICAL_H */
