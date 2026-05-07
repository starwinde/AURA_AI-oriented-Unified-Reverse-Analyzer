/*
 * rizin_decompile_caps.h — runtime detection of Rizin decompile backends.
 *
 * Phase 2B.1: AURA depends on optional Rizin plugins for decompilation —
 * rz-ghidra (registers as `ghidra` core plugin → exposes `pdg`/`pdgj`)
 * and jsdec (registers as `jsdec` core plugin → exposes `pdd`/`pddj`).
 * Neither is part of base Rizin. The adapter must detect what is
 * actually loadable in the current `rizin` install at startup, not at
 * compile time.
 *
 * This header exposes:
 *   1. AuraRizinDecompileCaps — flags for each backend variant.
 *   2. AuraRizinDecompileBackend — selector enum, ordered by quality.
 *   3. aura_rizin_parse_decompile_caps — pure parser of `Lc` stdout.
 *      Testable with mocked input; no I/O.
 *   4. aura_rizin_decompile_select_backend — picks the best available
 *      backend per priority pdgj > pddj > pdd > NONE.
 *
 * Backend priority rationale (D-28 fan-out):
 *   - pdgj  : rz-ghidra JSON. Highest quality (Ghidra Sleigh decompiler),
 *             explicit line↔addr annotations.
 *   - pddj  : jsdec JSON. Moderate quality, partial line map.
 *   - pdd   : jsdec text-only fallback. Body text only, no line map.
 *
 * The actual subprocess invocation that produces `Lc` stdout lives
 * outside this file — it is wired into the adapter init path. See the
 * `aura_rizin_detect_decompile_caps` symbol declared at the bottom.
 *
 * Internal to src/adapter/rizin/. Do NOT include from core / gui.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_DECOMPILE_CAPS_H
#define AURA_RIZIN_DECOMPILE_CAPS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── Capability flags (parser output) ────────────────────────────────── */

typedef struct AuraRizinDecompileCaps {
    int has_pdgj;  /* rz-ghidra core plugin loaded → `pdg`/`pdgj` available */
    int has_pddj;  /* jsdec core plugin loaded → `pddj` available           */
    int has_pdd;   /* jsdec core plugin loaded → `pdd` text fallback        */
} AuraRizinDecompileCaps;

/* ── Backend selector (priority-ordered) ─────────────────────────────── */

typedef enum AuraRizinDecompileBackend {
    AURA_RIZIN_DEC_NONE = 0, /* sentinel — should never be returned by
                              * select_backend after PDF fallback added    */
    AURA_RIZIN_DEC_PDGJ,     /* rz-ghidra JSON  — preferred                */
    AURA_RIZIN_DEC_PDDJ,     /* jsdec JSON      — secondary                */
    AURA_RIZIN_DEC_PDD,      /* jsdec text-only — text fallback            */
    AURA_RIZIN_DEC_PDF,      /* base Rizin `pdf` disassembly — always
                              * available, used when no decompile plugin
                              * is installed (Phase 11.3.1.1 fallback,
                              * ADR-0036). Output is annotated assembly,
                              * not pseudo-C — signaled to UI via the
                              * backend stamp in the response body. */
} AuraRizinDecompileBackend;

/* ── Pure parser ─────────────────────────────────────────────────────── */

/* Parse the stdout of `rizin -q -c "Lc" -- <fixture>` into the caps
 * struct. The input is the full plugin-listing text; lines look like
 *   "ghidra: Suite of ... (Made by ..., Apache-2.0)"
 *   "jsdec: jsdec pseudo-decompiler ... (..., MIT)"
 * We detect a backend by finding a line whose name token (the leading
 * identifier before the first ':') equals "ghidra" or "jsdec", with
 * optional leading whitespace. Trailing tokens / descriptions are
 * ignored. Names are matched case-sensitively (Rizin's plugin names are
 * lowercase by convention).
 *
 * Returns 0 on success, non-zero if `out` is NULL. `plugin_list_stdout`
 * may be NULL or empty — both are treated as "no plugins detected"
 * (caps zeroed) and return 0. */
int aura_rizin_parse_decompile_caps(const char *plugin_list_stdout,
                                    AuraRizinDecompileCaps *out);

/* Pick the best available backend per the priority chain
 * pdgj → pddj → pdd → NONE. Returns AURA_RIZIN_DEC_NONE if `caps` is
 * NULL or all flags are 0. */
AuraRizinDecompileBackend aura_rizin_decompile_select_backend(
    const AuraRizinDecompileCaps *caps);

/* ── Subprocess-driven detection (full integration) ──────────────────── */

/* Run `rizin -q -c "Lc" -- <empty_fixture_path>` via the engine
 * subprocess primitive, then parse the stdout into `out`.
 *
 *   exec_path           : path to rizin executable (NULL → PATH lookup)
 *   empty_fixture_path  : path to a portable empty/minimal binary
 *                         (`tests/fixtures/empty.bin` is the project
 *                         convention — must be Windows/Linux portable;
 *                         /dev/null is forbidden).
 *
 * Returns 0 on success (caps populated; all-zero is a valid result if
 * no plugins are present). Non-zero on subprocess spawn / timeout
 * failure or NULL output buffer. */
int aura_rizin_detect_decompile_caps(const char *exec_path,
                                     const char *empty_fixture_path,
                                     AuraRizinDecompileCaps *out);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_DECOMPILE_CAPS_H */
