/*
 * rizin_decompile_normalize.c — pdgj/pddj/pdd → AuraRizinDecompileBody.
 *
 * See rizin_decompile_normalize.h for design rationale and contract.
 *
 * pdgj real schema (rz-ghidra HEAD on rizin 0.9.0, captured 2026-05-01
 * against tests/fixtures/stripped_nucleus.elf @ 0x5bc):
 *
 *   {
 *     "code": "<single-string pseudo-C; embedded \\n>",
 *     "annotations": [
 *       {"start": <byte_offset>, "end": <byte_offset>,
 *        "type": "offset", "offset": <addr_decimal>},
 *       {"start": ..., "end": ..., "type": "syntax_highlight", ...},
 *       ...
 *     ]
 *   }
 *
 * Only annotations of type "offset" carry an addr; we map their
 * `start` byte position back to a 1-based line number in `code` and
 * emit (line, addr) pairs, deduplicating consecutive identical pairs
 * so that one annotation per token doesn't blow up line_map_count.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_decompile_normalize.h"

#include <stdlib.h>
#include <string.h>

#define DEC_ALIGN8(n) (((n) + 7u) & ~(size_t)7u)

/* ── shared body allocator ───────────────────────────────────────────── */

/* Build an unpopulated body of the requested shape. body_text is copied
 * from `text_src` (text_src may be NULL if text_len == 0). line_map
 * entries are zeroed; caller fills them.
 *
 * Returns NULL on OOM. */
static AuraRizinDecompileBody *
alloc_body(uint32_t backend,
           uint64_t function_addr,
           const char *text_src,
           size_t  text_len,
           size_t  line_map_count,
           float   confidence,
           float   completeness,
           AuraRizinDecompileLineMap **out_line_map_writable)
{
    size_t header_off = 0;
    size_t text_off   = sizeof(AuraRizinDecompileBody);
    size_t line_off   = DEC_ALIGN8(text_off + text_len + 1u);
    size_t total      = line_off + line_map_count
                                   * sizeof(AuraRizinDecompileLineMap);
    (void)header_off;

    AuraRizinDecompileBody *body =
        (AuraRizinDecompileBody *)malloc(total);
    if (!body) return NULL;
    memset(body, 0, total);

    body->magic          = AURA_RIZIN_DECOMPILE_BODY_MAGIC;
    body->version        = AURA_RIZIN_DECOMPILE_BODY_VERSION;
    body->backend        = backend;
    body->reserved       = 0;
    body->function_addr  = function_addr;
    body->body_text_len  = text_len;
    body->line_map_count = line_map_count;
    body->confidence     = confidence;
    body->completeness   = completeness;

    char *text_dst = (char *)body + text_off;
    if (text_len > 0 && text_src != NULL) {
        memcpy(text_dst, text_src, text_len);
    }
    text_dst[text_len] = '\0';

    if (out_line_map_writable) {
        *out_line_map_writable = (line_map_count == 0)
            ? NULL
            : (AuraRizinDecompileLineMap *)((char *)body + line_off);
    }
    return body;
}

/* ── pdgj-specific: byte-offset → line number ───────────────────────── */

/* Build a sorted array of byte offsets where each line begins.
 * `line_starts[0] == 0`. line N starts at line_starts[N-1].
 * Returns line count (≥ 1) and *out_line_starts (heap, caller frees). */
static size_t build_line_starts(const char *code,
                                size_t      code_len,
                                size_t    **out_line_starts)
{
    *out_line_starts = NULL;
    /* Worst case: one line per byte. Use a growing buffer. */
    size_t  cap   = 32;
    size_t  count = 0;
    size_t *arr   = (size_t *)malloc(cap * sizeof(size_t));
    if (!arr) return 0;
    arr[count++] = 0;
    for (size_t i = 0; i < code_len; ++i) {
        if (code[i] == '\n') {
            if (count + 1 > cap) {
                size_t  ncap = cap * 2u;
                size_t *narr = (size_t *)realloc(arr, ncap * sizeof(size_t));
                if (!narr) { free(arr); return 0; }
                arr = narr; cap = ncap;
            }
            arr[count++] = i + 1u;
        }
    }
    *out_line_starts = arr;
    return count;
}

/* Binary-search byte_off in line_starts; returns 1-based line number. */
static uint32_t lookup_line(const size_t *line_starts,
                            size_t        line_count,
                            size_t        byte_off)
{
    if (line_count == 0) return 1u;
    /* Find the largest i such that line_starts[i] <= byte_off. */
    size_t lo = 0, hi = line_count - 1u;
    while (lo < hi) {
        size_t mid = lo + (hi - lo + 1u) / 2u;
        if (line_starts[mid] <= byte_off) lo = mid;
        else                              hi = mid - 1u;
    }
    return (uint32_t)(lo + 1u); /* 1-based */
}

/* ── pdgj normalize ──────────────────────────────────────────────────── */

AuraRizinDecompileNormStatus aura_rizin_normalize_decompile_pdgj(
    const cJSON                 *pdgj_root,
    uint64_t                     function_addr,
    AuraRizinDecompileBody     **out_body)
{
    if (!out_body) return AURA_RIZIN_DEC_NORM_ERR_INVALID;
    *out_body = NULL;

    if (!pdgj_root) return AURA_RIZIN_DEC_NORM_ERR_INVALID;
    if (!cJSON_IsObject(pdgj_root)) return AURA_RIZIN_DEC_NORM_ERR_PARSE;

    const cJSON *code_node = cJSON_GetObjectItemCaseSensitive(pdgj_root, "code");
    if (!cJSON_IsString(code_node) || !code_node->valuestring) {
        return AURA_RIZIN_DEC_NORM_ERR_PARSE;
    }
    const char *code = code_node->valuestring;
    size_t      code_len = strlen(code);

    const cJSON *annot = cJSON_GetObjectItemCaseSensitive(pdgj_root, "annotations");
    /* annotations is optional — if absent or non-array, line_map = 0. */
    int has_annot = (annot && cJSON_IsArray(annot));

    /* Pass 1: walk annotations to count "offset" entries (upper bound on
     * line_map_count, before dedup). */
    size_t pre_count = 0;
    if (has_annot) {
        const cJSON *it = NULL;
        cJSON_ArrayForEach(it, annot) {
            if (!cJSON_IsObject(it)) continue;
            const cJSON *t = cJSON_GetObjectItemCaseSensitive(it, "type");
            if (!cJSON_IsString(t) || !t->valuestring) continue;
            if (strcmp(t->valuestring, "offset") != 0) continue;
            ++pre_count;
        }
    }

    /* Build line_starts now so we can compute line numbers. */
    size_t *line_starts = NULL;
    size_t  line_count  = 0;
    if (code_len > 0 || pre_count > 0) {
        line_count = build_line_starts(code, code_len, &line_starts);
        if (line_count == 0) return AURA_RIZIN_DEC_NORM_ERR_OOM;
    }

    /* Pass 2: collect (line, addr) pairs; dedupe consecutive duplicates.
     * Worst case allocates pre_count entries; we'll truncate count. */
    AuraRizinDecompileLineMap *staging = NULL;
    if (pre_count > 0) {
        staging = (AuraRizinDecompileLineMap *)
            calloc(pre_count, sizeof(AuraRizinDecompileLineMap));
        if (!staging) {
            free(line_starts);
            return AURA_RIZIN_DEC_NORM_ERR_OOM;
        }
    }

    size_t map_count = 0;
    if (has_annot) {
        const cJSON *it = NULL;
        cJSON_ArrayForEach(it, annot) {
            if (!cJSON_IsObject(it)) continue;
            const cJSON *t = cJSON_GetObjectItemCaseSensitive(it, "type");
            if (!cJSON_IsString(t) || !t->valuestring) continue;
            if (strcmp(t->valuestring, "offset") != 0) continue;

            const cJSON *s = cJSON_GetObjectItemCaseSensitive(it, "start");
            const cJSON *o = cJSON_GetObjectItemCaseSensitive(it, "offset");
            if (!cJSON_IsNumber(s) || !cJSON_IsNumber(o)) continue;
            double sd = s->valuedouble;
            double od = o->valuedouble;
            if (sd < 0.0 || od < 0.0) continue;
            size_t   byte_off = (size_t)sd;
            uint64_t addr     = (uint64_t)od;
            if (byte_off > code_len) byte_off = code_len;

            uint32_t line = lookup_line(line_starts, line_count, byte_off);

            /* Dedup against previous entry (same line + same addr). */
            if (map_count > 0
                && staging[map_count - 1u].line == line
                && staging[map_count - 1u].addr == addr) {
                continue;
            }
            staging[map_count].line = line;
            staging[map_count].pad  = 0;
            staging[map_count].addr = addr;
            ++map_count;
        }
    }

    /* Completeness: fraction of total lines that have a mapping. */
    float completeness = 0.0f;
    if (line_count > 0) {
        /* Count distinct mapped lines (linear scan since sorted by emit
         * order, not line; but consecutive dedup catches most). */
        size_t distinct = 0;
        uint32_t last = 0;
        for (size_t i = 0; i < map_count; ++i) {
            if (staging[i].line != last) { ++distinct; last = staging[i].line; }
        }
        if (distinct > line_count) distinct = line_count;
        completeness = (float)distinct / (float)line_count;
    }

    AuraRizinDecompileLineMap *line_map_out = NULL;
    AuraRizinDecompileBody *body = alloc_body(
        AURA_RIZIN_DEC_BACKEND_PDGJ, function_addr,
        code, code_len, map_count,
        AURA_RIZIN_DEC_PDGJ_CONFIDENCE, completeness,
        &line_map_out);

    free(line_starts);

    if (!body) {
        free(staging);
        return AURA_RIZIN_DEC_NORM_ERR_OOM;
    }

    if (map_count > 0 && line_map_out) {
        memcpy(line_map_out, staging,
               map_count * sizeof(AuraRizinDecompileLineMap));
    }
    free(staging);

    *out_body = body;
    return AURA_RIZIN_DEC_NORM_OK;
}

/* ── pdd (text fallback) normalize ───────────────────────────────────── */

AuraRizinDecompileNormStatus aura_rizin_normalize_decompile_pdd(
    const char                  *raw_text,
    size_t                       raw_text_len,
    uint64_t                     function_addr,
    AuraRizinDecompileBody     **out_body)
{
    if (!out_body) return AURA_RIZIN_DEC_NORM_ERR_INVALID;
    *out_body = NULL;

    /* raw_text NULL with len=0 is OK (empty body). */
    if (raw_text_len > 0 && !raw_text) {
        return AURA_RIZIN_DEC_NORM_ERR_INVALID;
    }

    /* completeness for text-only: body present but no line map → 0.0 */
    float completeness = 0.0f;

    AuraRizinDecompileLineMap *unused = NULL;
    AuraRizinDecompileBody *body = alloc_body(
        AURA_RIZIN_DEC_BACKEND_PDD, function_addr,
        raw_text, raw_text_len, 0,
        AURA_RIZIN_DEC_PDD_CONFIDENCE, completeness,
        &unused);
    if (!body) return AURA_RIZIN_DEC_NORM_ERR_OOM;
    *out_body = body;
    return AURA_RIZIN_DEC_NORM_OK;
}

/* ── dispatcher ──────────────────────────────────────────────────────── */

AuraRizinDecompileNormStatus aura_rizin_normalize_decompile_pdf(
    const char                  *raw_text,
    size_t                       raw_text_len,
    uint64_t                     function_addr,
    AuraRizinDecompileBody     **out_body)
{
    if (!out_body) return AURA_RIZIN_DEC_NORM_ERR_INVALID;
    *out_body = NULL;
    if (raw_text_len > 0 && !raw_text)
        return AURA_RIZIN_DEC_NORM_ERR_INVALID;

    AuraRizinDecompileLineMap *unused = NULL;
    AuraRizinDecompileBody *body = alloc_body(
        AURA_RIZIN_DEC_BACKEND_PDF, function_addr,
        raw_text, raw_text_len, 0,
        AURA_RIZIN_DEC_PDF_CONFIDENCE, 0.0f, &unused);
    if (!body) return AURA_RIZIN_DEC_NORM_ERR_OOM;
    *out_body = body;
    return AURA_RIZIN_DEC_NORM_OK;
}

AuraRizinDecompileNormStatus aura_rizin_decompile_normalize(
    AuraRizinDecompileBackend    backend,
    uint64_t                     function_addr,
    const cJSON                 *json_root_or_null,
    const char                  *raw_text_or_null,
    size_t                       raw_text_len,
    AuraRizinDecompileBody     **out_body)
{
    if (!out_body) return AURA_RIZIN_DEC_NORM_ERR_INVALID;
    *out_body = NULL;

    switch (backend) {
    case AURA_RIZIN_DEC_PDGJ:
        return aura_rizin_normalize_decompile_pdgj(
            json_root_or_null, function_addr, out_body);

    case AURA_RIZIN_DEC_PDD:
        return aura_rizin_normalize_decompile_pdd(
            raw_text_or_null, raw_text_len, function_addr, out_body);

    case AURA_RIZIN_DEC_PDF:
        return aura_rizin_normalize_decompile_pdf(
            raw_text_or_null, raw_text_len, function_addr, out_body);

    case AURA_RIZIN_DEC_PDDJ:
        /* jsdec JSON schema not verified in this environment — refuse
         * rather than emit fabricated output. */
        return AURA_RIZIN_DEC_NORM_ERR_BAD_BACKEND;

    case AURA_RIZIN_DEC_NONE:
    default:
        return AURA_RIZIN_DEC_NORM_ERR_BAD_BACKEND;
    }
}
