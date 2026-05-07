/*
 * rizin_decompile_caps.c — runtime detection of Rizin decompile backends.
 *
 * See rizin_decompile_caps.h for design rationale and contract.
 *
 * The pure parser scans `rizin -q -c "Lc"` stdout for plugin lines whose
 * leading identifier (before the first ':') equals one of:
 *
 *   "ghidra"  → rz-ghidra installed → has_pdgj
 *   "jsdec"   → jsdec installed     → has_pddj + has_pdd (same plugin
 *                                     exposes both JSON and text mode)
 *
 * Match is anchored: leading whitespace is allowed, but the name token
 * must end at ':'. This avoids false positives from descriptions that
 * mention "ghidra" or "jsdec" inside another plugin's text.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_decompile_caps.h"

#include <ctype.h>
#include <stddef.h>
#include <string.h>

/* ── pure parser ─────────────────────────────────────────────────────── */

/* Skip leading horizontal whitespace; returns pointer to first non-WS. */
static const char *skip_hws(const char *s)
{
    while (*s == ' ' || *s == '\t') ++s;
    return s;
}

/* True iff the line, with optional leading whitespace, starts with the
 * exact identifier `name` followed immediately by ':'. */
static int line_name_eq(const char *line, const char *name)
{
    const char *p = skip_hws(line);
    size_t      n = strlen(name);
    if (strncmp(p, name, n) != 0) return 0;
    return p[n] == ':';
}

int aura_rizin_parse_decompile_caps(const char *plugin_list_stdout,
                                    AuraRizinDecompileCaps *out)
{
    if (!out) return -1;
    out->has_pdgj = 0;
    out->has_pddj = 0;
    out->has_pdd  = 0;

    if (!plugin_list_stdout || !*plugin_list_stdout) return 0;

    const char *p = plugin_list_stdout;
    while (*p) {
        /* find end of current line */
        const char *eol = p;
        while (*eol && *eol != '\n' && *eol != '\r') ++eol;

        /* match against a temporary copy is not necessary — line_name_eq
         * stops at ':' which always appears before EOL in plugin entries.
         * For lines without ':' the helper returns 0 cheaply. */
        if (line_name_eq(p, "ghidra")) {
            out->has_pdgj = 1;
        } else if (line_name_eq(p, "jsdec")) {
            out->has_pddj = 1;
            out->has_pdd  = 1;
        }

        /* advance past the line terminator(s) */
        p = eol;
        while (*p == '\n' || *p == '\r') ++p;
    }

    return 0;
}

AuraRizinDecompileBackend aura_rizin_decompile_select_backend(
    const AuraRizinDecompileCaps *caps)
{
    if (!caps) return AURA_RIZIN_DEC_PDF;  /* base Rizin always available */
    if (caps->has_pdgj) return AURA_RIZIN_DEC_PDGJ;
    if (caps->has_pddj) return AURA_RIZIN_DEC_PDDJ;
    if (caps->has_pdd)  return AURA_RIZIN_DEC_PDD;
    /* Phase 11.3.1.1 ADR-0036: when no decompile plugin is loaded, fall
     * back to base Rizin's `pdf` (annotated disassembly). Always available
     * → never returns NONE. UI distinguishes via the backend stamp. */
    return AURA_RIZIN_DEC_PDF;
}

/* ── subprocess-driven detection ─────────────────────────────────────── */

/* The subprocess wrapper lives in rizin_subprocess.h, which already
 * encapsulates rizin invocation with exit-code mapping. We reuse it to
 * run a `Lc`-only command on the empty fixture. */
#include "rizin_subprocess.h"

#include <stdlib.h>

int aura_rizin_detect_decompile_caps(const char *exec_path,
                                     const char *empty_fixture_path,
                                     AuraRizinDecompileCaps *out)
{
    if (!out) return -1;
    out->has_pdgj = 0;
    out->has_pddj = 0;
    out->has_pdd  = 0;

    if (!empty_fixture_path) return -2;

    AuraRizinSubRequest req = {0};
    req.exec_path_override = exec_path;       /* may be NULL → PATH lookup  */
    req.binary_path        = empty_fixture_path;
    req.commands           = "Lc";
    req.timeout_s          = 10;              /* 10s plenty for plugin enum */

    AuraRizinSubResult res = {0};
    AuraRizinSubStatus st  = aura_rizin_sub_run(&req, &res);
    if (st != AURA_RIZIN_SUB_OK) {
        aura_rizin_sub_result_free(&res);
        return (int)st;
    }

    /* Parse stdout; the parser is total — empty / NULL is valid. */
    int prc = aura_rizin_parse_decompile_caps(res.stdout_buf, out);

    aura_rizin_sub_result_free(&res);
    return prc;
}
