/*
 * rizin_command_set.c — bulk JSON command catalog implementation.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_command_set.h"
#include "rizin_framing.h" /* for AURA_RIZIN_CMD_ID_MAX + aura_rizin_command_id_valid */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BEGIN_MAGIC "===AURA-BEGIN"
#define END_MAGIC   "===AURA-END"

/* ── catalog tables ──────────────────────────────────────────────────── */

const AuraRizinCmd AURA_RIZIN_ANALYZE_GLOBAL[] = {
    { "aaa",  "aaa"  },
    { "aflj", "aflj" },
    { "isj",  "isj"  },
    { "iij",  "iij"  },
    { "izj",  "izj"  },
};
const size_t AURA_RIZIN_ANALYZE_GLOBAL_COUNT =
    sizeof(AURA_RIZIN_ANALYZE_GLOBAL) / sizeof(AURA_RIZIN_ANALYZE_GLOBAL[0]);

/* Phase 3B v0.8.2 baseline: id base column kept stable for the
 * snapshot parser; cmd column issues the rizin v0.8.2 form. `aftj`
 * removed (no JSON mode in v0.8.2). */
const AuraRizinPerFunctionCmd AURA_RIZIN_PER_FUNCTION_CMDS[] = {
    { "agfj", "agf json" }, /* basic-block CFG (JSON)        */
    { "axtj", "axtj"     }, /* xrefs to address              */
    { "afvj", "afvlj"    }, /* function variables (afvl j)   */
};
const size_t AURA_RIZIN_PER_FUNCTION_CMDS_COUNT =
    sizeof(AURA_RIZIN_PER_FUNCTION_CMDS) /
    sizeof(AURA_RIZIN_PER_FUNCTION_CMDS[0]);

/* Phase 2B decompile commands, indexed by AuraRizinDecompileBackend.
 * Index 0 (NONE) is intentionally NULL — calling code must check the
 * caps before constructing a command. */
const char *const AURA_RIZIN_DECOMPILE_CMDS[] = {
    NULL,    /* AURA_RIZIN_DEC_NONE = 0  (invalid)            */
    "pdgj",  /* AURA_RIZIN_DEC_PDGJ = 1  (rz-ghidra JSON)     */
    "pddj",  /* AURA_RIZIN_DEC_PDDJ = 2  (jsdec JSON)         */
    "pdd",   /* AURA_RIZIN_DEC_PDD  = 3  (jsdec text)         */
    "pdf",   /* AURA_RIZIN_DEC_PDF  = 4  (base disassembly)   */
};
const size_t AURA_RIZIN_DECOMPILE_CMDS_COUNT =
    sizeof(AURA_RIZIN_DECOMPILE_CMDS) /
    sizeof(AURA_RIZIN_DECOMPILE_CMDS[0]);

/* ── argument safety ─────────────────────────────────────────────────── */

int aura_rizin_cmd_arg_safe(const char *s)
{
    if (!s || !*s) return 0;
    if (strstr(s, BEGIN_MAGIC) != NULL) return 0;
    if (strstr(s, END_MAGIC)   != NULL) return 0;
    /* Reject embedded NUL is impossible via C string; reject newline /
     * carriage return so a malicious arg cannot forge a delimiter line. */
    if (strchr(s, '\n') != NULL) return 0;
    if (strchr(s, '\r') != NULL) return 0;
    return 1;
}

int aura_rizin_cmd_addr_hex_valid(const char *addr_hex)
{
    if (!addr_hex) return 0;
    if (addr_hex[0] != '0') return 0;
    if (addr_hex[1] != 'x' && addr_hex[1] != 'X') return 0;
    size_t i = 2;
    for (; addr_hex[i]; ++i) {
        char c = addr_hex[i];
        int is_hex =
            (c >= '0' && c <= '9') ||
            (c >= 'a' && c <= 'f') ||
            (c >= 'A' && c <= 'F');
        if (!is_hex) return 0;
        if (i - 2 >= 16) return 0; /* max 16 hex digits = 64-bit */
    }
    return (i > 2) ? 1 : 0;
}

/* ── dynamic string buffer ───────────────────────────────────────────── */

typedef struct {
    char  *data;
    size_t cap;
    size_t len;
} StrBuf;

static int sb_reserve(StrBuf *b, size_t need)
{
    if (b->cap >= need) return 0;
    size_t nc = b->cap ? b->cap * 2u : 256u;
    while (nc < need) nc *= 2u;
    char *p = (char *)realloc(b->data, nc);
    if (!p) return -1;
    b->data = p;
    b->cap  = nc;
    return 0;
}

static int sb_append(StrBuf *b, const char *s, size_t n)
{
    if (sb_reserve(b, b->len + n + 1u) != 0) return -1;
    memcpy(b->data + b->len, s, n);
    b->len += n;
    b->data[b->len] = '\0';
    return 0;
}

static int sb_append_cstr(StrBuf *b, const char *s)
{
    return sb_append(b, s, strlen(s));
}

/* ── builder ─────────────────────────────────────────────────────────── */

static int append_framed(StrBuf *b, const char *id, const char *cmd, int first)
{
    /* Validate id under the framing grammar (same source of truth). */
    if (!aura_rizin_command_id_valid(id, strlen(id))) return -1;
    if (!aura_rizin_cmd_arg_safe(cmd)) return -1;

    if (!first) {
        if (sb_append_cstr(b, ";") != 0) return -1;
    }
    if (sb_append_cstr(b, "echo ===AURA-BEGIN:") != 0) return -1;
    if (sb_append_cstr(b, id)                    != 0) return -1;
    if (sb_append_cstr(b, "===;")                != 0) return -1;
    if (sb_append_cstr(b, cmd)                   != 0) return -1;
    if (sb_append_cstr(b, ";echo ===AURA-END:")  != 0) return -1;
    if (sb_append_cstr(b, id)                  != 0) return -1;
    if (sb_append_cstr(b, "===")               != 0) return -1;
    return 0;
}

char *aura_rizin_cmd_build(const AuraRizinCmd *cmds, size_t n)
{
    if (!cmds || n == 0) return NULL;

    StrBuf b;
    memset(&b, 0, sizeof(b));

    for (size_t i = 0; i < n; ++i) {
        if (!cmds[i].id || !cmds[i].cmd) goto fail;
        if (append_framed(&b, cmds[i].id, cmds[i].cmd, i == 0) != 0) goto fail;
    }
    return b.data; /* caller frees */

fail:
    free(b.data);
    return NULL;
}

char *aura_rizin_cmd_build_analyze_global(void)
{
    return aura_rizin_cmd_build(AURA_RIZIN_ANALYZE_GLOBAL,
                                AURA_RIZIN_ANALYZE_GLOBAL_COUNT);
}

/* Analysis-depth variants. The id stays "aaa" so snapshot parser keys remain
 * stable regardless of the selected Rizin command. */
static const AuraRizinCmd kAuraRizinAnalyzeGlobalQuick[] = {
    { "aaa",  "aa"   },
    { "aflj", "aflj" },
    { "isj",  "isj"  },
    { "iij",  "iij"  },
    { "izj",  "izj"  },
};
static const size_t kAuraRizinAnalyzeGlobalQuickCount =
    sizeof(kAuraRizinAnalyzeGlobalQuick) /
    sizeof(kAuraRizinAnalyzeGlobalQuick[0]);

static const AuraRizinCmd kAuraRizinAnalyzeGlobalAdvanced[] = {
    { "aaa",  "aaaa" },
    { "aflj", "aflj" },
    { "isj",  "isj"  },
    { "iij",  "iij"  },
    { "izj",  "izj"  },
};
static const size_t kAuraRizinAnalyzeGlobalAdvancedCount =
    sizeof(kAuraRizinAnalyzeGlobalAdvanced) /
    sizeof(kAuraRizinAnalyzeGlobalAdvanced[0]);

char *aura_rizin_cmd_build_analyze_global_with_level(AuraAnalysisLevel level)
{
    if (level == AURA_ANALYSIS_LEVEL_QUICK) {
        return aura_rizin_cmd_build(kAuraRizinAnalyzeGlobalQuick,
                                    kAuraRizinAnalyzeGlobalQuickCount);
    }
    if (level == AURA_ANALYSIS_LEVEL_ADVANCED) {
        return aura_rizin_cmd_build(kAuraRizinAnalyzeGlobalAdvanced,
                                    kAuraRizinAnalyzeGlobalAdvancedCount);
    }
    return aura_rizin_cmd_build_analyze_global();
}

char *aura_rizin_cmd_build_per_function(const char *addr_hex)
{
    if (!aura_rizin_cmd_addr_hex_valid(addr_hex)) return NULL;

    StrBuf b;
    memset(&b, 0, sizeof(b));

    for (size_t i = 0; i < AURA_RIZIN_PER_FUNCTION_CMDS_COUNT; ++i) {
        const AuraRizinPerFunctionCmd *e = &AURA_RIZIN_PER_FUNCTION_CMDS[i];
        char id[AURA_RIZIN_CMD_ID_MAX + 1u];
        char cmd[64 + 32];

        /* id = "<id_base>_<addr_hex>" — '_' avoids rizin echo seek. */
        int idn = snprintf(id, sizeof(id), "%s_%s", e->id_base, addr_hex);
        if (idn < 0 || (size_t)idn > AURA_RIZIN_CMD_ID_MAX) goto fail;
        int cn = snprintf(cmd, sizeof(cmd), "%s @ %s", e->cmd, addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;

        if (append_framed(&b, id, cmd, i == 0) != 0) goto fail;
    }
    return b.data;

fail:
    free(b.data);
    return NULL;
}

/* Phase 11.3.7 (P2.F2 C2) → Phase 11.6 T1: disasm bulk builder.
 *
 * v1: emits `aaa; pdfj @ addr` so the pdfj frame can be JSON-parsed
 *     into AuraRizinDisasmBody.instructions[].
 *
 * v2 (Phase 11.6 T1): also emits a `pdf @ addr` text frame with
 *     asm.lines/flowlines enabled — Cutter-style ASCII flow arrows
 *     (e.g. `,=<`, `.--->`, `|`). The pdf frame is appended to the
 *     same body as a NUL-terminated text blob. Frame ids stay unique
 *     so the snapshot frame parser can find each one.
 *
 *     Single-address only (id = bare "pdfj" / "pdf_text"; rizin-0.9
 *     echo @ quirk avoided).
 */
char *aura_rizin_cmd_build_disasm(const char *addr_hex)
{
    if (!aura_rizin_cmd_addr_hex_valid(addr_hex)) return NULL;

    StrBuf b;
    memset(&b, 0, sizeof(b));
    int first = 1;

    if (append_framed(&b, "aaa", "aaa", first) != 0) goto fail;
    first = 0;

    {
        const char *id = "pdfj";
        char cmd[64];
        int cn = snprintf(cmd, sizeof(cmd), "pdfj @ %s", addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    /* Phase 11.6 T1: pdf text with flow arrows.
     *
     * Per ADR-0040 D5 + ADR-0036 amend: text output uses scr.color=0 +
     * scr.utf8=0 so the byte stream is plain ASCII (no terminal
     * escapes, no UTF-8 box-drawing) — keeps the framing parser and
     * downstream consumers strictly text. asm.lines turns on the
     * gutter arrow rendering rizin already implements (ASCII chars
     * `,`/`<`/`>`/`=`/`|`/`.`/`---` etc.).
     *
     * The configs are set inline; rizin doesn't expose a portable
     * save/restore syntax, but the subprocess is one-shot so leakage
     * doesn't matter — every invocation re-applies what it needs.
     */
    {
        /* id MUST not contain '_' — the framing parser uses '_' as the
         * base/suffix separator (rizin_framing.c:aura_rizin_command_id_parse),
         * so "pdf_text" would split to base="pdf" and clash with future
         * `pdf` IDs. "pdftext" is unique under that rule. */
        const char *id = "pdftext";
        char cmd[256];
        int cn = snprintf(cmd, sizeof(cmd),
            "e scr.color=0;e scr.utf8=0;e asm.lines=true;"
            "e asm.bytes=true;e asm.comments=true;pdf @ %s",
            addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    return b.data;

fail:
    free(b.data);
    return NULL;
}

char *aura_rizin_cmd_build_disasm_window(const char *addr_hex,
                                         unsigned    count)
{
    if (!aura_rizin_cmd_addr_hex_valid(addr_hex)) return NULL;
    if (count == 0u) return NULL;
    if (count > 8192u) count = 8192u;

    StrBuf b;
    memset(&b, 0, sizeof(b));
    int first = 1;

    if (append_framed(&b, "aaa", "aaa", first) != 0) goto fail;
    first = 0;

    {
        const char *id = "pdj";
        char cmd[96];
        int cn = snprintf(cmd, sizeof(cmd), "pdj %u @ %s", count, addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    {
        /* Cutter-style text companion for the same viewport. Keep it small:
         * Rizin 0.8.0 `pD` may timeout on PE files when the byte range grows.
         */
        const char *id = "pDtext";
        char cmd[256];
        int cn = snprintf(cmd, sizeof(cmd),
            "e scr.color=0;e scr.utf8=0;e asm.lines=true;"
            "e asm.bytes=true;e asm.comments=true;pD 4096 @ %s",
            addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    return b.data;

fail:
    free(b.data);
    return NULL;
}

char *aura_rizin_cmd_build_disasm_text_range(const char *addr_hex,
                                             unsigned    byte_count)
{
    if (!aura_rizin_cmd_addr_hex_valid(addr_hex)) return NULL;
    if (byte_count == 0u) return NULL;
    if (byte_count > 4096u) byte_count = 4096u;

    StrBuf b;
    memset(&b, 0, sizeof(b));
    int first = 1;

    if (append_framed(&b, "aaa", "aaa", first) != 0) goto fail;
    first = 0;

    {
        /* id MUST not contain '_' because frame ids use '_' as the
         * base/suffix separator. */
        const char *id = "pDtext";
        char cmd[256];
        int cn = snprintf(cmd, sizeof(cmd),
            "e scr.color=0;e scr.utf8=0;e asm.lines=true;"
            "e asm.bytes=true;e asm.comments=true;pD %u @ %s",
            byte_count, addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    return b.data;

fail:
    free(b.data);
    return NULL;
}

char *aura_rizin_cmd_build_decompile(AuraRizinDecompileBackend backend,
                                     const char *addr_hex)
{
    /* Index validation: NONE (0) and out-of-range are rejected. */
    if (backend <= AURA_RIZIN_DEC_NONE) return NULL;
    if ((size_t)backend >= AURA_RIZIN_DECOMPILE_CMDS_COUNT) return NULL;

    const char *base = AURA_RIZIN_DECOMPILE_CMDS[backend];
    if (!base) return NULL;

    if (!aura_rizin_cmd_addr_hex_valid(addr_hex)) return NULL;

    StrBuf b;
    memset(&b, 0, sizeof(b));
    int first = 1;

    /* Prefix `aaa` — Rizin subprocess is stateless; the decompiler needs
     * function boundaries from the analysis pass. */
    if (append_framed(&b, "aaa", "aaa", first) != 0) goto fail;
    first = 0;

    /* IMPORTANT: id is the bare base ("pdgj"/"pddj"/"pdd") — no @addr
     * suffix. rizin 0.9's `echo` treats `@` as the seek operator, so a
     * delimiter line like `echo ===AURA-BEGIN:pdgj@0x5bc===` is parsed
     * as `echo ===AURA-BEGIN:pdgj` followed by `@0x5bc===` (a seek with
     * an invalid offset spec) and the framing line is silently dropped.
     * Per-function analyze frames hit the same rizin-0.9 quirk; that
     * regression is tracked separately as the Phase 2A-followup. The
     * decompile bulk only ever issues ONE address per call, so a bare
     * id is unambiguous. The cmd portion still seeks to the address
     * via `pdgj @ <addr>`. */
    {
        const char *id = base;
        char cmd[64 + 32];
        int cn = snprintf(cmd, sizeof(cmd), "%s @ %s", base, addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    return b.data;

fail:
    free(b.data);
    return NULL;
}

char *aura_rizin_cmd_build_decompile_batch(
    AuraRizinDecompileBackend  backend,
    const char *const         *addr_hex_list,
    size_t                     n)
{
    if (backend <= AURA_RIZIN_DEC_NONE) return NULL;
    if ((size_t)backend >= AURA_RIZIN_DECOMPILE_CMDS_COUNT) return NULL;
    if (!addr_hex_list || n == 0) return NULL;

    const char *base = AURA_RIZIN_DECOMPILE_CMDS[backend];
    if (!base) return NULL;

    /* Validate all addresses upfront. */
    for (size_t i = 0; i < n; ++i) {
        if (!aura_rizin_cmd_addr_hex_valid(addr_hex_list[i])) return NULL;
    }

    StrBuf b;
    memset(&b, 0, sizeof(b));
    int first = 1;

    /* Prefix: framed `aaa` once. */
    if (append_framed(&b, "aaa", "aaa", first) != 0) goto fail;
    first = 0;

    for (size_t i = 0; i < n; ++i) {
        const char *addr_hex = addr_hex_list[i];
        char id[AURA_RIZIN_CMD_ID_MAX + 1u];
        char cmd[64 + 32];

        int idn = snprintf(id, sizeof(id), "%s_%s", base, addr_hex);
        if (idn < 0 || (size_t)idn > AURA_RIZIN_CMD_ID_MAX) goto fail;
        int cn = snprintf(cmd, sizeof(cmd), "%s @ %s", base, addr_hex);
        if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;
        if (append_framed(&b, id, cmd, first) != 0) goto fail;
    }

    return b.data;

fail:
    free(b.data);
    return NULL;
}

char *aura_rizin_cmd_build_per_function_batch_with_analysis(
    const char *const *addr_hex_list,
    size_t             n)
{
    if (!addr_hex_list || n == 0) return NULL;

    /* Validate all addresses upfront before allocating. */
    for (size_t i = 0; i < n; ++i) {
        if (!aura_rizin_cmd_addr_hex_valid(addr_hex_list[i])) return NULL;
    }

    StrBuf b;
    memset(&b, 0, sizeof(b));
    int first = 1;

    /* Prefix: framed `aaa` re-runs analysis in the fresh subprocess. */
    if (append_framed(&b, "aaa", "aaa", first) != 0) goto fail;
    first = 0;

    for (size_t i = 0; i < n; ++i) {
        const char *addr_hex = addr_hex_list[i];
        for (size_t j = 0; j < AURA_RIZIN_PER_FUNCTION_CMDS_COUNT; ++j) {
            const AuraRizinPerFunctionCmd *e = &AURA_RIZIN_PER_FUNCTION_CMDS[j];
            char id[AURA_RIZIN_CMD_ID_MAX + 1u];
            char cmd[64 + 32];

            int idn = snprintf(id, sizeof(id), "%s_%s", e->id_base, addr_hex);
            if (idn < 0 || (size_t)idn > AURA_RIZIN_CMD_ID_MAX) goto fail;
            int cn = snprintf(cmd, sizeof(cmd), "%s @ %s", e->cmd, addr_hex);
            if (cn < 0 || (size_t)cn >= sizeof(cmd)) goto fail;

            if (append_framed(&b, id, cmd, first) != 0) goto fail;
            first = 0;
        }
    }
    return b.data;

fail:
    free(b.data);
    return NULL;
}
