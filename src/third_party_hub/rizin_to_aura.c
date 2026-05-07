/*
 * rizin_to_aura.c — canonical → normalized records.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_to_aura.h"

#include <string.h>

/* ── helpers ─────────────────────────────────────────────────────────── */

static void copy_view(char *dst, size_t cap,
                      const char *src, size_t src_len)
{
    if (!dst || cap == 0) return;
    if (!src || src_len == 0) { dst[0] = '\0'; return; }
    size_t n = (src_len < cap - 1) ? src_len : cap - 1;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void fill_provenance(AuraProvenance *p,
                            float confidence, float completeness)
{
    memset(p->source, 0, sizeof(p->source));
    /* Length-bounded; "rizin" is 5 chars + NUL. */
    memcpy(p->source, "rizin", 5);
    p->confidence   = confidence;
    p->completeness = completeness;
}

static AuraSymbolKind map_symbol_kind(const char *type, size_t type_len,
                                       int is_imported)
{
    if (is_imported) return AURA_SYMBOL_IMPORT;
    if (!type || type_len == 0) return AURA_SYMBOL_UNKNOWN;
    if (type_len == 4 && memcmp(type, "FUNC", 4) == 0)
        return AURA_SYMBOL_FUNCTION;
    if (type_len == 6 && memcmp(type, "OBJECT", 6) == 0)
        return AURA_SYMBOL_OBJECT;
    if (type_len == 7 && memcmp(type, "SECTION", 7) == 0)
        return AURA_SYMBOL_SECTION;
    return AURA_SYMBOL_UNKNOWN;
}

/* ── stable ID lookup helpers ────────────────────────────────────────── */

static AuraFunctionId find_function_id_by_addr(
    const AuraRecordCollection *col, uint64_t addr)
{
    size_t n = aura_records_function_count(col);
    for (size_t i = 0; i < n; ++i) {
        const AuraFunctionRecord *r = aura_records_function_at(col, i);
        if (r && r->entry == addr) return r->function_id;
    }
    return AURA_NULL_ID;
}

static AuraBlockId find_block_id_by_addr(
    const AuraRecordCollection *col, AuraFunctionId fn_id, uint64_t addr)
{
    size_t n = aura_records_block_count(col);
    for (size_t i = 0; i < n; ++i) {
        const AuraBlockRecord *r = aura_records_block_at(col, i);
        if (r && r->function_id == fn_id && r->start_addr == addr)
            return r->block_id;
    }
    return AURA_NULL_ID;
}

/* Find the function whose range [entry, entry+size) contains addr.
 * Used for call xref caller lookup. Falls back to entry match when size==0. */
static AuraFunctionId find_function_containing(
    const AuraRecordCollection *col, uint64_t addr)
{
    size_t n = aura_records_function_count(col);
    for (size_t i = 0; i < n; ++i) {
        const AuraFunctionRecord *r = aura_records_function_at(col, i);
        if (!r) continue;
        if (r->size > 0) {
            if (addr >= r->entry && addr < r->entry + r->size)
                return r->function_id;
        } else {
            if (addr == r->entry) return r->function_id;
        }
    }
    return AURA_NULL_ID;
}

/* ── per-domain mappers ─────────────────────────────────────────────── */

static int emit_functions(const AuraRizinCanonical *c,
                          AuraRecordCollection     *out)
{
    for (size_t i = 0; i < c->functions_count; ++i) {
        const AuraRizinCanonFunction *f = &c->functions[i];
        AuraFunctionRecord r;
        memset(&r, 0, sizeof(r));
        fill_provenance(&r.provenance,
                        AURA_RIZIN_HUB_FN_CONFIDENCE,
                        AURA_RIZIN_HUB_FN_COMPLETENESS);
        r.function_id = aura_records_alloc_function_id(out);
        r.entry       = f->offset;
        r.size        = f->size;
        copy_view(r.name, sizeof(r.name), f->name, f->name_len);

        if (aura_records_add_function(out, &r) != 0) return -1;
    }
    return 0;
}

static int emit_symbols(const AuraRizinCanonical *c,
                        AuraRecordCollection     *out)
{
    for (size_t i = 0; i < c->symbols_count; ++i) {
        const AuraRizinCanonSymbol *s = &c->symbols[i];
        AuraSymbolRecord r;
        memset(&r, 0, sizeof(r));
        fill_provenance(&r.provenance,
                        AURA_RIZIN_HUB_SYM_CONFIDENCE,
                        AURA_RIZIN_HUB_SYM_COMPLETENESS);
        r.symbol_id = aura_records_alloc_symbol_id(out);
        r.addr      = s->vaddr;
        r.kind      = map_symbol_kind(s->type, s->type_len, s->is_imported);
        copy_view(r.name, sizeof(r.name), s->name, s->name_len);

        if (aura_records_add_symbol(out, &r) != 0) return -1;
    }
    return 0;
}

static int emit_blocks_and_edges(const AuraRizinCanonical *c,
                                  AuraRecordCollection     *out)
{
    for (size_t ci = 0; ci < c->cfgs_count; ++ci) {
        const AuraRizinCanonCfg *cfg = &c->cfgs[ci];
        AuraFunctionId fn_id = find_function_id_by_addr(out, cfg->function_addr);
        if (fn_id == AURA_NULL_ID) continue; /* orphan cfg — skip conservatively */

        for (size_t bi = 0; bi < cfg->blocks_count; ++bi) {
            const AuraRizinCanonBlock *blk = &cfg->blocks[bi];
            AuraBlockRecord br;
            memset(&br, 0, sizeof(br));
            fill_provenance(&br.provenance,
                            AURA_RIZIN_HUB_BLOCK_CONFIDENCE,
                            AURA_RIZIN_HUB_BLOCK_COMPLETENESS);
            br.block_id    = aura_records_alloc_block_id(out);
            br.function_id = fn_id;
            br.start_addr  = blk->addr;
            br.end_addr    = blk->addr + blk->size;
            if (aura_records_add_block(out, &br) != 0) return -1;

            /* Emit edges: jump (taken) and fail (not-taken). */
            if (blk->jump != 0) {
                AuraEdgeRecord er;
                memset(&er, 0, sizeof(er));
                fill_provenance(&er.provenance,
                                AURA_RIZIN_HUB_EDGE_CONFIDENCE,
                                AURA_RIZIN_HUB_EDGE_COMPLETENESS);
                er.src_block = br.block_id;
                er.dst_block = find_block_id_by_addr(out, fn_id, blk->jump);
                er.kind = AURA_EDGE_JUMP;
                /* dst_block may be AURA_NULL_ID if target outside this function. */
                if (aura_records_add_edge(out, &er) != 0) return -1;
            }
            if (blk->fail != 0) {
                AuraEdgeRecord er;
                memset(&er, 0, sizeof(er));
                fill_provenance(&er.provenance,
                                AURA_RIZIN_HUB_EDGE_CONFIDENCE,
                                AURA_RIZIN_HUB_EDGE_COMPLETENESS);
                er.src_block = br.block_id;
                er.dst_block = find_block_id_by_addr(out, fn_id, blk->fail);
                er.kind = AURA_EDGE_FALLTHROUGH;
                if (aura_records_add_edge(out, &er) != 0) return -1;
            }
        }
    }
    return 0;
}

static int emit_variables_and_type_facts(const AuraRizinCanonical *c,
                                          AuraRecordCollection     *out)
{
    for (size_t i = 0; i < c->variables_count; ++i) {
        const AuraRizinCanonVariable *v = &c->variables[i];
        uint64_t fn_addr = c->variables_function_addr
                           ? c->variables_function_addr[i] : 0;
        AuraFunctionId fn_id = fn_addr
                               ? find_function_id_by_addr(out, fn_addr)
                               : AURA_NULL_ID;
        /* Skip variables with no owning function. */
        if (fn_id == AURA_NULL_ID) continue;

        AuraVariableRecord vr;
        memset(&vr, 0, sizeof(vr));
        fill_provenance(&vr.provenance,
                        AURA_RIZIN_HUB_VAR_CONFIDENCE,
                        AURA_RIZIN_HUB_VAR_COMPLETENESS);
        vr.var_id      = aura_records_alloc_variable_id(out);
        vr.function_id = fn_id;
        copy_view(vr.name, sizeof(vr.name), v->name, v->name_len);
        copy_view(vr.kind, sizeof(vr.kind), v->kind, v->kind_len);
        vr.stack_offset = (int32_t)v->stack_offset;
        if (aura_records_add_variable(out, &vr) != 0) return -1;

        /* TypeFact from variable's type field (C-2 scope). */
        if (v->type && v->type_len > 0) {
            AuraTypeFactRecord tf;
            memset(&tf, 0, sizeof(tf));
            fill_provenance(&tf.provenance,
                            AURA_RIZIN_HUB_TFACT_CONFIDENCE,
                            AURA_RIZIN_HUB_TFACT_COMPLETENESS);
            tf.var_id      = vr.var_id;
            tf.function_id = fn_id;
            copy_view(tf.type_str, sizeof(tf.type_str), v->type, v->type_len);
            if (aura_records_add_type_fact(out, &tf) != 0) return -1;
        }
    }
    return 0;
}

static int emit_xrefs_and_call_edges(const AuraRizinCanonical *c,
                                      AuraRecordCollection     *out)
{
    for (size_t i = 0; i < c->xrefs_count; ++i) {
        const AuraRizinCanonXref *x = &c->xrefs[i];

        AuraXrefRecord xr;
        memset(&xr, 0, sizeof(xr));
        fill_provenance(&xr.provenance,
                        AURA_RIZIN_HUB_XREF_CONFIDENCE,
                        AURA_RIZIN_HUB_XREF_COMPLETENESS);
        xr.from_addr = x->from;
        xr.to_addr   = x->to;
        /* Map rizin type string to AuraXrefKind. */
        if (x->type && x->type_len == 4 && memcmp(x->type, "CALL", 4) == 0)
            xr.kind = AURA_XREF_CALL;
        else if (x->type && x->type_len >= 3 && memcmp(x->type, "JMP", 3) == 0)
            xr.kind = AURA_XREF_CODE;
        else if (x->type && x->type_len >= 4 && memcmp(x->type, "DATA", 4) == 0)
            xr.kind = AURA_XREF_DATA;
        else
            xr.kind = AURA_XREF_UNKNOWN;
        if (aura_records_add_xref(out, &xr) != 0) return -1;

        /* Emit CallEdge for CALL xrefs. */
        if (xr.kind == AURA_XREF_CALL) {
            AuraCallEdgeRecord ce;
            memset(&ce, 0, sizeof(ce));
            fill_provenance(&ce.provenance,
                            AURA_RIZIN_HUB_CALL_CONFIDENCE,
                            AURA_RIZIN_HUB_CALL_COMPLETENESS);
            ce.caller_id = find_function_containing(out, x->from);
            ce.callee_id = find_function_id_by_addr(out, x->to);
            ce.site_addr = x->from;
            if (aura_records_add_call_edge(out, &ce) != 0) return -1;
        }
    }
    return 0;
}

/* Phase 11.3.6: izj literal strings → AuraStringRecord. */
static int emit_strings(const AuraRizinCanonical *c,
                        AuraRecordCollection     *out)
{
    for (size_t i = 0; i < c->strings_count; ++i) {
        const AuraRizinCanonString *s = &c->strings[i];

        AuraStringRecord sr;
        memset(&sr, 0, sizeof(sr));
        fill_provenance(&sr.provenance,
                        AURA_RIZIN_HUB_STRING_CONFIDENCE,
                        AURA_RIZIN_HUB_STRING_COMPLETENESS);
        sr.string_id = aura_records_alloc_string_id(out);
        sr.addr      = s->vaddr;
        sr.length    = s->length;

        /* Map rizin type string → AuraStringEncoding. */
        if (s->type && s->type_len == 5 && memcmp(s->type, "ascii", 5) == 0)
            sr.encoding = AURA_STRING_ENC_ASCII;
        else if (s->type && s->type_len == 4 && memcmp(s->type, "utf8", 4) == 0)
            sr.encoding = AURA_STRING_ENC_UTF8;
        else if (s->type && s->type_len == 7 && memcmp(s->type, "utf16le", 7) == 0)
            sr.encoding = AURA_STRING_ENC_UTF16LE;
        else if (s->type && s->type_len == 7 && memcmp(s->type, "utf16be", 7) == 0)
            sr.encoding = AURA_STRING_ENC_UTF16BE;
        else if (s->type && s->type_len == 4 && memcmp(s->type, "wide", 4) == 0)
            sr.encoding = AURA_STRING_ENC_WIDE;
        else
            sr.encoding = AURA_STRING_ENC_UNKNOWN;

        copy_view(sr.section, sizeof(sr.section), s->section, s->section_len);
        copy_view(sr.content, sizeof(sr.content), s->string,  s->string_len);

        if (aura_records_add_string(out, &sr) != 0) return -1;
    }
    return 0;
}

/* ── entry ───────────────────────────────────────────────────────────── */

AuraRizinHubStatus aura_rizin_to_aura_normalize(
    const AuraRizinCanonical *canonical,
    AuraRecordCollection     *out)
{
    if (!canonical || !out) return AURA_RIZIN_HUB_ERR_INVALID;

    /* Insertion order: functions/symbols first (needed for ID lookups below). */
    if (emit_functions(canonical, out) != 0) return AURA_RIZIN_HUB_ERR_INSERT;
    if (emit_symbols  (canonical, out) != 0) return AURA_RIZIN_HUB_ERR_INSERT;

    /* Blocks (depends on function IDs). */
    if (emit_blocks_and_edges(canonical, out) != 0) return AURA_RIZIN_HUB_ERR_INSERT;

    /* Variables + type facts (depends on function IDs). */
    if (emit_variables_and_type_facts(canonical, out) != 0)
        return AURA_RIZIN_HUB_ERR_INSERT;

    /* Xrefs + call edges (depends on function + block IDs). */
    if (emit_xrefs_and_call_edges(canonical, out) != 0)
        return AURA_RIZIN_HUB_ERR_INSERT;

    /* Phase 11.3.6: literal strings (file-wide; no ID dependency). */
    if (emit_strings(canonical, out) != 0)
        return AURA_RIZIN_HUB_ERR_INSERT;

    return AURA_RIZIN_HUB_OK;
}
