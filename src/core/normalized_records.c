/*
 * normalized_records.c — collection container for AURA 1급 records.
 *
 * Eight independent dynamic arrays (one per record kind, R-12) plus
 * monotonic ID counters. Insert path validates AuraProvenance per R-11
 * before the record is copied in.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "aura/normalized_records.h"

#include <stdlib.h>
#include <string.h>

/* Generic dynamic array of fixed-size records. */
typedef struct AuraRecVec {
    void  *data;
    size_t count;
    size_t cap;
    size_t elem_size;
} AuraRecVec;

static int recvec_reserve(AuraRecVec *v, size_t need)
{
    if (v->cap >= need) return 0;
    size_t new_cap = v->cap ? v->cap : 8u;
    while (new_cap < need) new_cap *= 2u;
    void *p = realloc(v->data, new_cap * v->elem_size);
    if (!p) return -1;
    v->data = p;
    v->cap  = new_cap;
    return 0;
}

static int recvec_push(AuraRecVec *v, const void *src)
{
    if (recvec_reserve(v, v->count + 1) != 0) return -1;
    memcpy((char *)v->data + v->count * v->elem_size, src, v->elem_size);
    v->count += 1;
    return 0;
}

static const void *recvec_at(const AuraRecVec *v, size_t i)
{
    if (!v || i >= v->count) return NULL;
    return (const char *)v->data + i * v->elem_size;
}

static void recvec_free(AuraRecVec *v)
{
    free(v->data);
    v->data = NULL;
    v->count = 0;
    v->cap = 0;
}

struct AuraRecordCollection {
    AuraRecVec functions;
    AuraRecVec blocks;
    AuraRecVec edges;
    AuraRecVec variables;
    AuraRecVec type_facts;
    AuraRecVec call_edges;
    AuraRecVec symbols;
    AuraRecVec xrefs;
    AuraRecVec strings;
    AuraRecVec instructions;

    AuraFunctionId next_function_id;
    AuraBlockId    next_block_id;
    AuraVariableId next_variable_id;
    AuraSymbolId   next_symbol_id;
    AuraStringId   next_string_id;
};

/* ── Provenance validation (R-11) ─────────────────────────────────── */

int aura_provenance_is_valid(const AuraProvenance *p)
{
    if (!p) return 0;
    if (p->source[0] == '\0') return 0;
    if (p->confidence  < 0.0f || p->confidence  > 1.0f) return 0;
    if (p->completeness < 0.0f || p->completeness > 1.0f) return 0;
    return 1;
}

/* ── Lifecycle ───────────────────────────────────────────────────── */

AuraRecordCollection *aura_records_create(void)
{
    AuraRecordCollection *c = (AuraRecordCollection *)calloc(1, sizeof(*c));
    if (!c) return NULL;
    c->functions.elem_size  = sizeof(AuraFunctionRecord);
    c->blocks.elem_size     = sizeof(AuraBlockRecord);
    c->edges.elem_size      = sizeof(AuraEdgeRecord);
    c->variables.elem_size  = sizeof(AuraVariableRecord);
    c->type_facts.elem_size = sizeof(AuraTypeFactRecord);
    c->call_edges.elem_size = sizeof(AuraCallEdgeRecord);
    c->symbols.elem_size    = sizeof(AuraSymbolRecord);
    c->xrefs.elem_size      = sizeof(AuraXrefRecord);
    c->strings.elem_size    = sizeof(AuraStringRecord);
    c->instructions.elem_size = sizeof(AuraInstructionRecord);
    /* IDs start at 1; AURA_NULL_ID (0) is the null sentinel. */
    c->next_function_id = 1;
    c->next_block_id    = 1;
    c->next_variable_id = 1;
    c->next_symbol_id   = 1;
    c->next_string_id   = 1;
    return c;
}

void aura_records_destroy(AuraRecordCollection *c)
{
    if (!c) return;
    recvec_free(&c->functions);
    recvec_free(&c->blocks);
    recvec_free(&c->edges);
    recvec_free(&c->variables);
    recvec_free(&c->type_facts);
    recvec_free(&c->call_edges);
    recvec_free(&c->symbols);
    recvec_free(&c->xrefs);
    recvec_free(&c->strings);
    recvec_free(&c->instructions);
    free(c);
}

/* ── ID issuers ──────────────────────────────────────────────────── */

AuraFunctionId aura_records_alloc_function_id(AuraRecordCollection *c)
{ return c ? c->next_function_id++ : AURA_NULL_ID; }
AuraBlockId aura_records_alloc_block_id(AuraRecordCollection *c)
{ return c ? c->next_block_id++ : AURA_NULL_ID; }
AuraVariableId aura_records_alloc_variable_id(AuraRecordCollection *c)
{ return c ? c->next_variable_id++ : AURA_NULL_ID; }
AuraSymbolId aura_records_alloc_symbol_id(AuraRecordCollection *c)
{ return c ? c->next_symbol_id++ : AURA_NULL_ID; }
AuraStringId aura_records_alloc_string_id(AuraRecordCollection *c)
{ return c ? c->next_string_id++ : AURA_NULL_ID; }

/* ── Insert ──────────────────────────────────────────────────────── */

#define DEFINE_ADD(suffix, type, vec) \
int aura_records_add_##suffix(AuraRecordCollection *c, const type *r) { \
    if (!c || !r) return -1; \
    if (!aura_provenance_is_valid(&r->provenance)) return -1; \
    return recvec_push(&c->vec, r); \
}

DEFINE_ADD(function,  AuraFunctionRecord,  functions)
DEFINE_ADD(block,     AuraBlockRecord,     blocks)
DEFINE_ADD(edge,      AuraEdgeRecord,      edges)
DEFINE_ADD(variable,  AuraVariableRecord,  variables)
DEFINE_ADD(type_fact, AuraTypeFactRecord,  type_facts)
DEFINE_ADD(call_edge, AuraCallEdgeRecord,  call_edges)
DEFINE_ADD(symbol,    AuraSymbolRecord,    symbols)
DEFINE_ADD(xref,      AuraXrefRecord,      xrefs)
DEFINE_ADD(string,    AuraStringRecord,    strings)
DEFINE_ADD(instruction, AuraInstructionRecord, instructions)

#undef DEFINE_ADD

/* ── Read ────────────────────────────────────────────────────────── */

#define DEFINE_COUNT_AT(suffix, type, vec) \
size_t aura_records_##suffix##_count(const AuraRecordCollection *c) \
{ return c ? c->vec.count : 0u; } \
const type *aura_records_##suffix##_at(const AuraRecordCollection *c, size_t i) \
{ return c ? (const type *)recvec_at(&c->vec, i) : NULL; }

DEFINE_COUNT_AT(function,  AuraFunctionRecord,  functions)
DEFINE_COUNT_AT(block,     AuraBlockRecord,     blocks)
DEFINE_COUNT_AT(edge,      AuraEdgeRecord,      edges)
DEFINE_COUNT_AT(variable,  AuraVariableRecord,  variables)
DEFINE_COUNT_AT(type_fact, AuraTypeFactRecord,  type_facts)
DEFINE_COUNT_AT(call_edge, AuraCallEdgeRecord,  call_edges)
DEFINE_COUNT_AT(symbol,    AuraSymbolRecord,    symbols)
DEFINE_COUNT_AT(xref,      AuraXrefRecord,      xrefs)
DEFINE_COUNT_AT(string,    AuraStringRecord,    strings)
DEFINE_COUNT_AT(instruction, AuraInstructionRecord, instructions)

#undef DEFINE_COUNT_AT
