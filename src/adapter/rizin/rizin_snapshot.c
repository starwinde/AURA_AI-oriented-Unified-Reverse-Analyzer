/*
 * rizin_snapshot.c — framing + cJSON + canonical builder.
 *
 * Phase 2A:
 *   - aflj  → canonical.functions[]
 *   - isj   → canonical.symbols[]
 *   - other recognised commands keep their cJSON tree but populate no
 *     canonical fields (Phase 2B will widen).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_snapshot.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "rizin_framing.h" /* AuraRizinCmdIdParts, aura_rizin_command_id_parse */

/* ── helpers ─────────────────────────────────────────────────────────── */

static int json_get_u64(const cJSON *obj, const char *key, uint64_t *out)
{
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (!v || !cJSON_IsNumber(v)) return 0;
    /* cJSON stores numbers as double; cast guards against negative noise. */
    double d = v->valuedouble;
    if (d < 0.0) { *out = 0; return 0; }
    *out = (uint64_t)d;
    return 1;
}

static int json_get_int(const cJSON *obj, const char *key, int *out)
{
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (!v || !cJSON_IsNumber(v)) return 0;
    *out = (int)v->valuedouble;
    return 1;
}

static int json_get_string(const cJSON *obj, const char *key,
                           const char **out, size_t *out_len)
{
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (!v || !cJSON_IsString(v) || !v->valuestring) return 0;
    *out     = v->valuestring;
    *out_len = strlen(v->valuestring);
    return 1;
}

static int json_get_bool(const cJSON *obj, const char *key, int *out)
{
    const cJSON *v = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (!v) return 0;
    if (cJSON_IsTrue(v))  { *out = 1; return 1; }
    if (cJSON_IsFalse(v)) { *out = 0; return 1; }
    return 0;
}

/* ── growable pointer arrays ─────────────────────────────────────────── */

typedef struct {
    void  **data;
    size_t  count;
    size_t  cap;
} PtrVec;

static int ptrvec_push(PtrVec *v, void *p)
{
    if (v->count >= v->cap) {
        size_t nc = v->cap ? v->cap * 2u : 8u;
        void **np = (void **)realloc(v->data, nc * sizeof(void *));
        if (!np) return -1;
        v->data = np;
        v->cap  = nc;
    }
    v->data[v->count++] = p;
    return 0;
}

/* Typed growable array — stores flat structs by value (byte-copies). */
typedef struct {
    char  *data;
    size_t count;
    size_t cap;
    size_t item_size;
} FlatVec;

static int flatvec_init(FlatVec *v, size_t item_size)
{
    memset(v, 0, sizeof(*v));
    v->item_size = item_size;
    return 0;
}

static int flatvec_push(FlatVec *v, const void *item)
{
    if (v->count >= v->cap) {
        size_t nc = v->cap ? v->cap * 2u : 8u;
        char *np = (char *)realloc(v->data, nc * v->item_size);
        if (!np) return -1;
        v->data = np;
        v->cap  = nc;
    }
    memcpy(v->data + v->count * v->item_size, item, v->item_size);
    ++v->count;
    return 0;
}

/* ── canonical population ────────────────────────────────────────────── */

static int populate_functions(const cJSON *root, AuraRizinCanonical *c)
{
    if (!cJSON_IsArray(root)) return 0; /* tolerate empty */
    int n = cJSON_GetArraySize(root);
    if (n <= 0) return 0;

    AuraRizinCanonFunction *arr =
        (AuraRizinCanonFunction *)calloc((size_t)n, sizeof(*arr));
    if (!arr) return -1;

    size_t kept = 0;
    const cJSON *e;
    cJSON_ArrayForEach(e, root) {
        if (!cJSON_IsObject(e)) continue;
        AuraRizinCanonFunction f;
        memset(&f, 0, sizeof(f));
        if (!json_get_u64(e, "offset", &f.offset)) continue;
        json_get_u64(e, "size",   &f.size);
        json_get_int(e, "nbbs",   &f.nbbs);
        json_get_string(e, "name", &f.name, &f.name_len);
        json_get_string(e, "type", &f.type, &f.type_len);
        arr[kept++] = f;
    }
    c->functions       = arr;
    c->functions_count = kept;
    return 0;
}

static int populate_symbols(const cJSON *root, AuraRizinCanonical *c)
{
    if (!cJSON_IsArray(root)) return 0;
    int n = cJSON_GetArraySize(root);
    if (n <= 0) return 0;

    AuraRizinCanonSymbol *arr =
        (AuraRizinCanonSymbol *)calloc((size_t)n, sizeof(*arr));
    if (!arr) return -1;

    size_t kept = 0;
    const cJSON *e;
    cJSON_ArrayForEach(e, root) {
        if (!cJSON_IsObject(e)) continue;
        AuraRizinCanonSymbol s;
        memset(&s, 0, sizeof(s));
        json_get_u64(e, "vaddr", &s.vaddr);
        json_get_u64(e, "paddr", &s.paddr);
        json_get_u64(e, "size",  &s.size);
        json_get_string(e, "name", &s.name, &s.name_len);
        json_get_string(e, "type", &s.type, &s.type_len);
        json_get_string(e, "bind", &s.bind, &s.bind_len);
        json_get_bool  (e, "is_imported", &s.is_imported);
        arr[kept++] = s;
    }
    c->symbols       = arr;
    c->symbols_count = kept;
    return 0;
}

/* ── per-function canonical population ───────────────────────────────── */

/* CFG block parser. Two input shapes are supported, both decided by
 * the JSON root type — no inference, just direct mapping:
 *
 *   1. v0.8.2 stable `agf json @ <addr>`:
 *        { "nodes": [ { "id": N, "offset": N, "out_nodes": [N,...],
 *                        "title": "0xN", "body": "..." }, ... ] }
 *      Two passes. Pass 1 builds id→offset. Pass 2 emits one
 *      AuraRizinCanonBlock per node — addr from `offset`; size left
 *      0 (v0.8.2 does not report a per-block size in this shape and
 *      we do not derive it from the body); jump/fail from out_nodes
 *      positionally (out_nodes[0]→jump, out_nodes[1]→fail). Extra
 *      out-edges beyond the second are not representable in the
 *      current canonical schema and are dropped — visibility for
 *      that loss is the diagnostic stream's job (Phase 3E), not
 *      this layer's.
 *
 *   2. legacy array-of-blocks: either `[{"name":..., "blocks":[...]}]`
 *      or a flat array of `{"addr"|"offset", "size", "jump", "fail"}`.
 *      Used by synthetic test fixtures and pre-v0.8.2 rizin.
 */
static int populate_cfg(const cJSON *root, uint64_t function_addr,
                        FlatVec *cfgs_vec)
{
    if (!root) return 0;

    /* ── v0.8.2 shape: object with "nodes" array ───────────────────── */
    if (cJSON_IsObject(root)) {
        const cJSON *nodes =
            cJSON_GetObjectItemCaseSensitive(root, "nodes");
        if (!nodes || !cJSON_IsArray(nodes)) return 0;

        int n = cJSON_GetArraySize(nodes);
        if (n <= 0) return 0;

        AuraRizinCanonBlock *blocks =
            (AuraRizinCanonBlock *)calloc((size_t)n, sizeof(*blocks));
        if (!blocks) return -1;

        /* Pass 1: id → offset map (parallel arrays). */
        int    *ids     = (int *)calloc((size_t)n, sizeof(int));
        uint64_t *offs  = (uint64_t *)calloc((size_t)n, sizeof(uint64_t));
        if (!ids || !offs) { free(ids); free(offs); free(blocks); return -1; }

        int idx = 0;
        const cJSON *nd;
        cJSON_ArrayForEach(nd, nodes) {
            if (!cJSON_IsObject(nd)) continue;
            int      nid = -1;
            uint64_t off = 0;
            json_get_int(nd, "id", &nid);
            if (!json_get_u64(nd, "offset", &off)) continue;
            ids[idx]  = nid;
            offs[idx] = off;
            idx++;
        }
        const int known = idx;

        /* Pass 2: emit one block per node; resolve out_nodes[0..1]. */
        size_t kept = 0;
        cJSON_ArrayForEach(nd, nodes) {
            if (!cJSON_IsObject(nd)) continue;
            uint64_t off = 0;
            if (!json_get_u64(nd, "offset", &off)) continue;

            AuraRizinCanonBlock blk;
            memset(&blk, 0, sizeof(blk));
            blk.addr = off;
            /* size: v0.8.2 does not report it on this shape. Leave 0. */

            const cJSON *outs =
                cJSON_GetObjectItemCaseSensitive(nd, "out_nodes");
            if (outs && cJSON_IsArray(outs)) {
                int oi = 0;
                const cJSON *oe;
                cJSON_ArrayForEach(oe, outs) {
                    if (!cJSON_IsNumber(oe)) continue;
                    int target_id = (int)cJSON_GetNumberValue(oe);
                    uint64_t target_off = 0;
                    for (int k = 0; k < known; ++k) {
                        if (ids[k] == target_id) {
                            target_off = offs[k];
                            break;
                        }
                    }
                    if (target_off == 0) { oi++; continue; }
                    if      (oi == 0) blk.jump = target_off;
                    else if (oi == 1) blk.fail = target_off;
                    /* oi >= 2: not representable here; dropped. */
                    oi++;
                }
            }
            blocks[kept++] = blk;
        }
        free(ids);
        free(offs);

        AuraRizinCanonCfg cfg;
        memset(&cfg, 0, sizeof(cfg));
        cfg.function_addr = function_addr;
        cfg.blocks        = blocks;
        cfg.blocks_count  = kept;

        if (flatvec_push(cfgs_vec, &cfg) != 0) {
            free(blocks);
            return -1;
        }
        return 0;
    }

    /* ── Legacy array-of-blocks shape ─────────────────────────────── */
    if (!cJSON_IsArray(root)) return 0;
    int n = cJSON_GetArraySize(root);
    if (n <= 0) return 0;

    const cJSON *fn_obj = cJSON_GetArrayItem(root, 0);
    const cJSON *blk_array =
        fn_obj ? cJSON_GetObjectItemCaseSensitive(fn_obj, "blocks") : NULL;
    if (!blk_array || !cJSON_IsArray(blk_array)) {
        blk_array = root; /* flat array fallback */
    }

    int bcount = cJSON_GetArraySize(blk_array);
    if (bcount <= 0) return 0;

    AuraRizinCanonBlock *blocks =
        (AuraRizinCanonBlock *)calloc((size_t)bcount, sizeof(*blocks));
    if (!blocks) return -1;

    size_t kept = 0;
    const cJSON *be;
    cJSON_ArrayForEach(be, blk_array) {
        if (!cJSON_IsObject(be)) continue;
        AuraRizinCanonBlock blk;
        memset(&blk, 0, sizeof(blk));
        if (!json_get_u64(be, "offset", &blk.addr) &&
            !json_get_u64(be, "addr",   &blk.addr)) continue;
        json_get_u64(be, "size", &blk.size);
        json_get_u64(be, "jump", &blk.jump);
        json_get_u64(be, "fail", &blk.fail);
        blocks[kept++] = blk;
    }

    AuraRizinCanonCfg cfg;
    memset(&cfg, 0, sizeof(cfg));
    cfg.function_addr  = function_addr;
    cfg.blocks         = blocks;
    cfg.blocks_count   = kept;

    if (flatvec_push(cfgs_vec, &cfg) != 0) { free(blocks); return -1; }
    return 0;
}

/* axtj: parse xrefs to a function address. */
static int populate_xrefs(const cJSON *root, FlatVec *xrefs_vec)
{
    if (!cJSON_IsArray(root)) return 0;
    const cJSON *e;
    cJSON_ArrayForEach(e, root) {
        if (!cJSON_IsObject(e)) continue;
        AuraRizinCanonXref xr;
        memset(&xr, 0, sizeof(xr));
        if (!json_get_u64(e, "from", &xr.from)) continue;
        json_get_u64(e, "addr", &xr.to); /* 'addr' = query target in axtj */
        json_get_string(e, "type", &xr.type, &xr.type_len);
        if (flatvec_push(xrefs_vec, &xr) != 0) return -1;
    }
    return 0;
}

/* izj: parse literal strings table (Phase 11.3.6). Field shape:
 *   { "vaddr": <int>, "paddr": <int>, "ordinal": <int>, "size": <int>,
 *     "length": <int>, "section": <str>, "type": <str>, "string": <str> }
 * `string` content is engine-reported text; `type` carries the encoding
 * label ("ascii"/"utf8"/"utf16le"/"utf16be"/"wide"). */
static int populate_strings(const cJSON *root, FlatVec *strings_vec)
{
    if (!cJSON_IsArray(root)) return 0;
    const cJSON *e;
    cJSON_ArrayForEach(e, root) {
        if (!cJSON_IsObject(e)) continue;
        AuraRizinCanonString st;
        memset(&st, 0, sizeof(st));
        if (!json_get_u64(e, "vaddr", &st.vaddr)) continue;
        json_get_u64(e, "paddr",  &st.paddr);
        json_get_u64(e, "length", &st.length);
        json_get_u64(e, "size",   &st.size);
        json_get_string(e, "type",    &st.type,    &st.type_len);
        json_get_string(e, "section", &st.section, &st.section_len);
        json_get_string(e, "string",  &st.string,  &st.string_len);
        if (flatvec_push(strings_vec, &st) != 0) return -1;
    }
    return 0;
}

/* Per-variable parser. Two element shapes are recognised, both by
 * direct field reads (no inference):
 *
 *   v0.8.2 stable `afvlj`:
 *     { "name", "type", "arg": bool,
 *       "storage": { "type": "stack"|"reg", "stack": int, "reg": str } }
 *
 *   legacy `afvj`:
 *     { "name", "kind", "type", "isarg": bool,
 *       "ref": { "offset": int } }
 *
 * `kind_default` is the category key when the caller is iterating
 * `{"stack":[...], "reg":[...]}` — used as the variable's `kind` when
 * the element itself doesn't carry one. */
static int populate_variables_from_array(const cJSON *arr, uint64_t function_addr,
                                         const char *kind_default,
                                         FlatVec *vars_vec, FlatVec *addrs_vec)
{
    const cJSON *e;
    cJSON_ArrayForEach(e, arr) {
        if (!cJSON_IsObject(e)) continue;
        AuraRizinCanonVariable v;
        memset(&v, 0, sizeof(v));
        json_get_string(e, "name", &v.name, &v.name_len);
        json_get_string(e, "type", &v.type, &v.type_len);

        /* kind: prefer element field, then storage.type, then category key. */
        if (!json_get_string(e, "kind", &v.kind, &v.kind_len)) {
            const cJSON *st = cJSON_GetObjectItemCaseSensitive(e, "storage");
            if (st && cJSON_IsObject(st)) {
                json_get_string(st, "type", &v.kind, &v.kind_len);
            }
            if (!v.kind && kind_default) {
                v.kind     = kind_default;
                v.kind_len = strlen(kind_default);
            }
        }

        /* stack offset:
         *   v0.8.2 → element.storage.stack (int)
         *   legacy → element.ref.offset (int) */
        v.stack_offset = 0;
        const cJSON *st = cJSON_GetObjectItemCaseSensitive(e, "storage");
        if (st && cJSON_IsObject(st)) {
            int s = 0;
            if (json_get_int(st, "stack", &s)) v.stack_offset = (int64_t)s;
        }
        if (v.stack_offset == 0) {
            const cJSON *ref = cJSON_GetObjectItemCaseSensitive(e, "ref");
            if (ref && cJSON_IsObject(ref)) {
                int off = 0;
                if (json_get_int(ref, "offset", &off))
                    v.stack_offset = (int64_t)off;
            }
        }

        /* arg flag: prefer v0.8.2 "arg", fall back to legacy "isarg". */
        int is_arg = 0;
        if (!json_get_bool(e, "arg", &is_arg)) {
            json_get_bool(e, "isarg", &is_arg);
        }
        v.is_arg = is_arg;

        if (flatvec_push(vars_vec, &v) != 0) return -1;
        if (flatvec_push(addrs_vec, &function_addr) != 0) return -1;
    }
    return 0;
}

static int populate_variables(const cJSON *root, uint64_t function_addr,
                              FlatVec *vars_vec, FlatVec *addrs_vec)
{
    if (!root) return 0;
    if (cJSON_IsArray(root)) {
        return populate_variables_from_array(root, function_addr,
                                             NULL,
                                             vars_vec, addrs_vec);
    }
    if (cJSON_IsObject(root)) {
        /* Category-object form: iterate child arrays by key. The key
         * (stack/reg/bp/sp) becomes the variable's `kind` default. */
        const cJSON *cat;
        cJSON_ArrayForEach(cat, root) {
            if (!cJSON_IsArray(cat)) continue;
            const char *cat_key = cat->string;
            if (populate_variables_from_array(cat, function_addr,
                                              cat_key,
                                              vars_vec, addrs_vec) != 0)
                return -1;
        }
    }
    return 0;
}

/* ── lifecycle ───────────────────────────────────────────────────────── */

void aura_rizin_full_snapshot_free(AuraRizinFullSnapshot *s)
{
    if (!s) return;

    /* Free cJSON trees. */
    if (s->_json_trees) {
        for (size_t i = 0; i < s->raw.frame_count; ++i) {
            cJSON *t = (cJSON *)s->_json_trees[i];
            if (t) cJSON_Delete(t);
        }
        free(s->_json_trees);
        s->_json_trees = NULL;
    }

    /* Free canonical heap arrays (string views are NOT owned). */
    free(s->canonical.functions);
    free(s->canonical.symbols);
    /* Each cfg owns its blocks[] array. */
    for (size_t i = 0; i < s->canonical.cfgs_count; ++i) {
        free(s->canonical.cfgs[i].blocks);
    }
    free(s->canonical.cfgs);
    free(s->canonical.xrefs);
    free(s->canonical.variables);
    free(s->canonical.variables_function_addr);
    free(s->canonical.strings);
    memset(&s->canonical, 0, sizeof(s->canonical));

    /* Free framing layer (raw_buffer + frames). */
    aura_rizin_snapshot_free(&s->raw);

    s->framing_status = AURA_RIZIN_FRAME_OK;
}

/* ── main parse ──────────────────────────────────────────────────────── */

AuraRizinSnapshotStatus aura_rizin_snapshot_parse(
    const char            *buf,
    size_t                 len,
    AuraRizinFullSnapshot *out)
{
    if (!out) return AURA_RIZIN_SNAPSHOT_ERR_INVALID;
    memset(out, 0, sizeof(*out));

    AuraRizinFrameStatus fs = aura_rizin_frame_parse(buf, len, &out->raw);
    out->framing_status = fs;
    if (fs != AURA_RIZIN_FRAME_OK) {
        return AURA_RIZIN_SNAPSHOT_ERR_FRAMING;
    }

    if (out->raw.frame_count > 0) {
        out->_json_trees =
            (void **)calloc(out->raw.frame_count, sizeof(void *));
        if (!out->_json_trees) {
            aura_rizin_full_snapshot_free(out);
            return AURA_RIZIN_SNAPSHOT_ERR_OOM;
        }
    }

    /* Accumulate per-function data in growable flat vectors; commit to
     * canonical arrays at the end. */
    FlatVec cfgs_vec, xrefs_vec, vars_vec, addrs_vec, strings_vec;
    flatvec_init(&cfgs_vec,    sizeof(AuraRizinCanonCfg));
    flatvec_init(&xrefs_vec,   sizeof(AuraRizinCanonXref));
    flatvec_init(&vars_vec,    sizeof(AuraRizinCanonVariable));
    flatvec_init(&addrs_vec,   sizeof(uint64_t));
    flatvec_init(&strings_vec, sizeof(AuraRizinCanonString));

    int ok = 1;

    for (size_t i = 0; i < out->raw.frame_count; ++i) {
        const AuraRizinFrame *fr = &out->raw.frames[i];

        /* Empty body is allowed (e.g. aaa). Skip cJSON parse. */
        if (fr->raw_json_len == 0) continue;

        cJSON *tree = cJSON_ParseWithLength(fr->raw_json, fr->raw_json_len);
        if (!tree) {
            ok = 0; break;
        }
        out->_json_trees[i] = tree;

        AuraRizinCmdIdParts parts;
        if (!aura_rizin_command_id_parse(fr->command_id, &parts)) continue;

        if (strcmp(parts.base, "aflj") == 0) {
            if (populate_functions(tree, &out->canonical) != 0) { ok = 0; break; }
        } else if (strcmp(parts.base, "isj") == 0) {
            if (populate_symbols(tree, &out->canonical) != 0) { ok = 0; break; }
        } else if (strcmp(parts.base, "agfj") == 0 && parts.has_addr) {
            if (populate_cfg(tree, parts.addr, &cfgs_vec) != 0) { ok = 0; break; }
        } else if (strcmp(parts.base, "axtj") == 0 && parts.has_addr) {
            /* axtj results each have an implicit `to == parts.addr`. Fill it. */
            size_t before = xrefs_vec.count;
            if (populate_xrefs(tree, &xrefs_vec) != 0) { ok = 0; break; }
            /* Patch `to` field for all newly added xrefs. */
            for (size_t k = before; k < xrefs_vec.count; ++k) {
                AuraRizinCanonXref *xr =
                    (AuraRizinCanonXref *)(xrefs_vec.data + k * sizeof(*xr));
                xr->to = parts.addr;
            }
        } else if (strcmp(parts.base, "afvj") == 0 && parts.has_addr) {
            if (populate_variables(tree, parts.addr,
                                   &vars_vec, &addrs_vec) != 0) { ok = 0; break; }
        } else if (strcmp(parts.base, "izj") == 0) {
            if (populate_strings(tree, &strings_vec) != 0) { ok = 0; break; }
        }
        /* aftj and others: tree retained, no canonical population in Phase 2A */
    }

    if (!ok) {
        /* cfgs_vec contains AuraRizinCanonCfg with heap blocks[] inside;
         * free each before releasing the vec. */
        for (size_t k = 0; k < cfgs_vec.count; ++k) {
            AuraRizinCanonCfg *cfg =
                (AuraRizinCanonCfg *)(cfgs_vec.data + k * sizeof(*cfg));
            free(cfg->blocks);
        }
        free(cfgs_vec.data);
        free(xrefs_vec.data);
        free(vars_vec.data);
        free(addrs_vec.data);
        free(strings_vec.data);
        aura_rizin_full_snapshot_free(out);
        return AURA_RIZIN_SNAPSHOT_ERR_JSON;
    }

    /* Commit accumulated per-function vectors to canonical. */
    if (cfgs_vec.count > 0) {
        out->canonical.cfgs       = (AuraRizinCanonCfg *)cfgs_vec.data;
        out->canonical.cfgs_count = cfgs_vec.count;
    } else {
        free(cfgs_vec.data);
    }
    if (xrefs_vec.count > 0) {
        out->canonical.xrefs       = (AuraRizinCanonXref *)xrefs_vec.data;
        out->canonical.xrefs_count = xrefs_vec.count;
    } else {
        free(xrefs_vec.data);
    }
    if (vars_vec.count > 0) {
        out->canonical.variables              = (AuraRizinCanonVariable *)vars_vec.data;
        out->canonical.variables_count        = vars_vec.count;
        out->canonical.variables_function_addr = (uint64_t *)addrs_vec.data;
    } else {
        free(vars_vec.data);
        free(addrs_vec.data);
    }
    if (strings_vec.count > 0) {
        out->canonical.strings       = (AuraRizinCanonString *)strings_vec.data;
        out->canonical.strings_count = strings_vec.count;
    } else {
        free(strings_vec.data);
    }

    return AURA_RIZIN_SNAPSHOT_OK;
}
