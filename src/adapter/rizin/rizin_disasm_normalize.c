/*
 * rizin_disasm_normalize.c — pdfj cJSON → AuraRizinDisasmBody.
 *
 * Phase 11.3.7 (P2.F2 C2). Mirrors the decompile_normalize structure:
 * single-pass count-then-fill, one malloc for header + InstructionRecord
 * array. All InstructionRecord fields are direct reads from pdfj (R-9).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_disasm_normalize.h"

#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "aura/normalized_records.h"

/* Provenance defaults for the disasm path. pdfj is rizin's authoritative
 * instruction stream once `aaa` has run; confidence/completeness mirror
 * the decompile body PDGJ tier. */
#define AURA_RIZIN_INSTR_CONFIDENCE   0.95f
#define AURA_RIZIN_INSTR_COMPLETENESS 1.00f

static void copy_str(char *dst, size_t cap, const char *src)
{
    if (cap == 0) return;
    if (!src) { dst[0] = '\0'; return; }
    size_t n = strlen(src);
    if (n >= cap) n = cap - 1;
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static uint64_t read_u64(const cJSON *obj, const char *key)
{
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (!v) return 0;
    if (cJSON_IsNumber(v)) return (uint64_t)v->valuedouble;
    return 0;
}

static const char *read_str(const cJSON *obj, const char *key)
{
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (v && cJSON_IsString(v) && v->valuestring) return v->valuestring;
    return NULL;
}

/* Split pdfj.opcode (e.g. "mov rbp, rsp") into mnemonic + op_str. The
 * opcode is engine-emitted text; we only split at the first whitespace
 * to keep mnemonic and operand columns separate. This is purely a
 * string slice — no semantic interpretation (R-9 honoured). */
static void split_opcode(const char *opcode,
                         char *mnemonic, size_t mn_cap,
                         char *op_str,   size_t op_cap)
{
    if (mn_cap) mnemonic[0] = '\0';
    if (op_cap) op_str[0]   = '\0';
    if (!opcode) return;
    const char *sp = opcode;
    while (*sp && *sp != ' ' && *sp != '\t') ++sp;
    size_t mn_len = (size_t)(sp - opcode);
    if (mn_cap) {
        if (mn_len >= mn_cap) mn_len = mn_cap - 1;
        memcpy(mnemonic, opcode, mn_len);
        mnemonic[mn_len] = '\0';
    }
    while (*sp == ' ' || *sp == '\t') ++sp;
    if (op_cap) copy_str(op_str, op_cap, sp);
}

AuraRizinDisasmNormStatus aura_rizin_disasm_normalize(
    uint64_t                  function_addr,
    const void               *pdfj_root_v,
    const char               *pdf_text,
    size_t                    pdf_text_len,
    AuraRizinDisasmBody     **out_body)
{
    if (!pdfj_root_v || !out_body) return AURA_RIZIN_DISASM_NORM_ERR_NULL;
    const cJSON *root = (const cJSON *)pdfj_root_v;
    *out_body = NULL;

    /* pdfj root is an object with `ops` array. Some rizin variants emit
     * a top-level array of function objects; defensively accept either. */
    const cJSON *ops = NULL;
    if (cJSON_IsObject(root)) {
        ops = cJSON_GetObjectItemCaseSensitive(root, "ops");
    } else if (cJSON_IsArray(root) && cJSON_GetArraySize(root) > 0) {
        const cJSON *first = cJSON_GetArrayItem(root, 0);
        if (first && cJSON_IsObject(first)) {
            ops = cJSON_GetObjectItemCaseSensitive(first, "ops");
        }
        if (!ops) {
            ops = root; /* `pdj <count>` emits a raw instruction array. */
        }
    }
    if (!ops || !cJSON_IsArray(ops)) {
        return AURA_RIZIN_DISASM_NORM_ERR_SHAPE;
    }

    size_t n = (size_t)cJSON_GetArraySize(ops);

    /* Phase 11.6 T1: text blob is appended after the instruction array.
     * text_size INCLUDES the trailing NUL we write. text_size == 0 when
     * the caller didn't supply pdf_text. */
    size_t text_alloc = 0;          /* bytes reserved in body         */
    if (pdf_text && pdf_text_len > 0) {
        text_alloc = pdf_text_len + 1u;  /* +1 for trailing NUL       */
    }

    /* Single-allocation: header + n * InstructionRecord + text[text_alloc]. */
    size_t total = sizeof(AuraRizinDisasmBody)
                 + n * sizeof(AuraInstructionRecord)
                 + text_alloc;
    AuraRizinDisasmBody *body =
        (AuraRizinDisasmBody *)calloc(1, total);
    if (!body) return AURA_RIZIN_DISASM_NORM_ERR_OOM;

    body->magic              = AURA_RIZIN_DISASM_BODY_MAGIC;
    body->version            = AURA_RIZIN_DISASM_BODY_VERSION;
    body->function_addr      = function_addr;
    body->instructions_count = n;
    body->text_size          = text_alloc;

    AuraInstructionRecord *dst =
        (AuraInstructionRecord *)((char *)body + sizeof(*body));

    /* Copy the text blob (if any) right after the instruction array. */
    if (text_alloc > 0) {
        char *text_dst = (char *)dst + n * sizeof(AuraInstructionRecord);
        memcpy(text_dst, pdf_text, pdf_text_len);
        text_dst[pdf_text_len] = '\0';
    }

    for (size_t i = 0; i < n; ++i) {
        const cJSON *op = cJSON_GetArrayItem(ops, (int)i);
        if (!op || !cJSON_IsObject(op)) continue;

        AuraInstructionRecord *r = &dst[i];

        /* R-11: provenance. */
        copy_str(r->provenance.source, sizeof(r->provenance.source),
                 "rizin");
        r->provenance.confidence  = AURA_RIZIN_INSTR_CONFIDENCE;
        r->provenance.completeness = AURA_RIZIN_INSTR_COMPLETENESS;

        r->function_id = AURA_NULL_ID; /* not joined to function table here */
        r->addr = read_u64(op, "offset");
        r->size = (uint32_t)read_u64(op, "size");

        const char *bytes = read_str(op, "bytes");
        copy_str(r->bytes, sizeof(r->bytes), bytes);

        const char *opcode = read_str(op, "opcode");
        split_opcode(opcode,
                     r->mnemonic, sizeof(r->mnemonic),
                     r->op_str,   sizeof(r->op_str));

        const char *type = read_str(op, "type");
        copy_str(r->type, sizeof(r->type), type);

        r->jump = read_u64(op, "jump");
        r->fail = read_u64(op, "fail");
    }

    *out_body = body;
    return AURA_RIZIN_DISASM_NORM_OK;
}
