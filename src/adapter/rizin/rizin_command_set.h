/*
 * rizin_command_set.h — bulk JSON command catalog for the Rizin adapter.
 *
 * Each catalog entry pairs:
 *   id  — stable identifier emitted in BEGIN/END delimiters (matches the
 *         framing layer's command_id grammar [A-Za-z0-9_\-@.:], len 1..31)
 *   cmd — verbatim Rizin command string (e.g. "aflj", "agfj @ 0x401000")
 *
 * The build helpers produce a single bulk command string suitable for
 * passing to rizin via `-c`. Each entry is wrapped with rizin's `?e`
 * (echo) so the framing layer can split bulk stdout cleanly:
 *
 *   ?e ===AURA-BEGIN:<id>===;<cmd>;?e ===AURA-END:<id>===
 *
 * `aura_rizin_cmd_arg_safe` rejects any user-supplied argument that
 * contains the framing magic — preventing delimiter injection from a
 * crafted binary path or address string.
 *
 * Internal to src/adapter/rizin/. Do NOT include from core / gui.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_COMMAND_SET_H
#define AURA_RIZIN_COMMAND_SET_H

#include <stddef.h>

#include "engine_request.h"       /* AuraAnalysisLevel */
#include "rizin_decompile_caps.h" /* AuraRizinDecompileBackend */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AuraRizinCmd {
    const char *id;   /* command_id used in the BEGIN/END delimiter      */
    const char *cmd;  /* raw rizin command string                         */
} AuraRizinCmd;

/* Phase 2A analyze: global commands (no per-function args).
 *   aaa  — analyze all (no body)
 *   aflj — function list (JSON)
 *   isj  — symbols (JSON)
 *   iij  — imports (JSON)
 *   izj  — strings (JSON)
 */
extern const AuraRizinCmd  AURA_RIZIN_ANALYZE_GLOBAL[];
extern const size_t        AURA_RIZIN_ANALYZE_GLOBAL_COUNT;

/* Per-function command templates. Targets the official stable Rizin
 * release (verified against v0.8.2). The catalog pairs:
 *
 *   id base    rizin v0.8.2 cmd     notes
 *   "agfj"  →  "agf json"           basic-block CFG (JSON)
 *   "axtj"  →  "axtj"               xrefs to address
 *   "afvj"  →  "afvlj"              function variables (afvl with j)
 *
 * Phase 3B baseline correction (verified 2026-05-01 against
 * /home/str/rizin-stable-0.8.2/, built from rizin-src-v0.8.2.tar.xz):
 * v0.8.2 has neither legacy `agfj`/`afvj` nor `aftj`. Issuing any of
 * those raises a soft error that halts the entire `rizin -c` script
 * and breaks framing for everything after it. The id base column
 * stays stable so the snapshot parser keys (which key on base) remain
 * unchanged.
 *
 * `aftj` was previously in the catalog (function type signature JSON)
 * but stable v0.8.2 has no JSON mode for `aft` (only the plain text
 * form). It is removed rather than synthesised — issuing `aft` would
 * either error out (halting the script) or produce non-JSON text the
 * snapshot parser cannot consume. Function-type ingestion is left
 * unsupported under this catalog.
 *
 * The builder composes per-function ids as "<id_base>_<addr_hex>"
 * (Phase 3B: '_' separator avoids the rizin `echo` seek quirk that
 * would silently drop a delimiter line containing "@<addr>"). */
typedef struct AuraRizinPerFunctionCmd {
    const char *id_base; /* stable base used by the snapshot parser   */
    const char *cmd;     /* actual rizin command to issue (no @addr)  */
} AuraRizinPerFunctionCmd;

extern const AuraRizinPerFunctionCmd AURA_RIZIN_PER_FUNCTION_CMDS[];
extern const size_t                  AURA_RIZIN_PER_FUNCTION_CMDS_COUNT;

/* ── argument safety ─────────────────────────────────────────────────── */

/* Returns 1 if `s` is non-NULL and contains neither the BEGIN nor the
 * END framing magic substring; 0 otherwise. NULL or empty string returns
 * 0 — argument injection is rejected before it reaches rizin. */
int aura_rizin_cmd_arg_safe(const char *s);

/* Returns 1 iff `addr_hex` is a valid hex address literal acceptable to
 * rizin (e.g. "0x401000"). Form: "0x" prefix + 1..16 hex digits.
 * Used to gate per-function command construction. */
int aura_rizin_cmd_addr_hex_valid(const char *addr_hex);

/* ── bulk command builder ────────────────────────────────────────────── */

/* Build a bulk command string from `n` catalog entries.
 *
 * Output (heap, NUL-terminated, caller frees with free()):
 *   ?e ===AURA-BEGIN:<id0>===;<cmd0>;?e ===AURA-END:<id0>===;
 *   ?e ===AURA-BEGIN:<id1>===;<cmd1>;?e ===AURA-END:<id1>===;
 *   ...
 *
 * Returns NULL on:
 *   - cmds == NULL or n == 0
 *   - any entry's id fails command_id validation (framing rules)
 *   - any entry's cmd is NULL or contains framing magic
 *   - allocation failure
 */
char *aura_rizin_cmd_build(const AuraRizinCmd *cmds, size_t n);

/* Build the global analyze bulk = `aura_rizin_cmd_build(AURA_RIZIN_ANALYZE_GLOBAL, ...)`. */
char *aura_rizin_cmd_build_analyze_global(void);

/* Phase 11.3.4: build a bulk decompile command for many addresses in a
 * single Rizin invocation. Output:
 *
 *   ?e ===AURA-BEGIN:aaa===;aaa;?e ===AURA-END:aaa===;
 *   ?e ===AURA-BEGIN:<base>_<addr0>===;<base> @ <addr0>;?e ===AURA-END:...;
 *   ?e ===AURA-BEGIN:<base>_<addr1>===;<base> @ <addr1>;?e ===AURA-END:...;
 *   ...
 *
 * Where <base> is the per-backend command (pdgj/pddj/pdd/pdf). Frame ids
 * are `<base>_<addr_hex>` so the snapshot parser can locate each result.
 *
 * Returns NULL on backend out-of-range, any invalid address, or alloc
 * failure. Caller frees with free(). */
char *aura_rizin_cmd_build_decompile_batch(
    AuraRizinDecompileBackend  backend,
    const char *const         *addr_hex_list,
    size_t                     n);

/* Build the global analyze bulk with the user-selected analysis depth:
 * Quick=`aa`, Full=`aaa`, Advanced=`aaaa`. Full is identical to
 * aura_rizin_cmd_build_analyze_global(). All trailing JSON fan-out commands
 * (aflj/isj/iij/izj) remain identical regardless of depth. */
char *aura_rizin_cmd_build_analyze_global_with_level(AuraAnalysisLevel level);

/* Build the per-function bulk for one address. Produces 3 framed
 * entries (agfj/axtj/afvj), with id "<id_base>_<addr_hex>" and
 * command "<rizin08_cmd> @ <addr_hex>". Returns NULL if addr_hex is
 * invalid.
 *
 * The underscore in the framing id is intentional (Phase 3B): rizin
 * `echo` parses `@<addr>` inside its argument as a seek operator and
 * would silently drop the whole delimiter line. */
char *aura_rizin_cmd_build_per_function(const char *addr_hex);

/* ── Phase 2B decompile commands ─────────────────────────────────────── */

/* Decompile command per backend.
 *
 *   Index AURA_RIZIN_DEC_NONE (0) = NULL  (unused — invalid backend).
 *   Index AURA_RIZIN_DEC_PDGJ      = "pdgj" — rz-ghidra JSON
 *   Index AURA_RIZIN_DEC_PDDJ      = "pddj" — jsdec JSON
 *   Index AURA_RIZIN_DEC_PDD       = "pdd"  — jsdec text fallback
 *
 * Indexable by AuraRizinDecompileBackend value. NULL at index 0 keeps the
 * mapping total without introducing a sentinel "unknown" string.
 */
extern const char *const AURA_RIZIN_DECOMPILE_CMDS[];
extern const size_t      AURA_RIZIN_DECOMPILE_CMDS_COUNT;

/* Build a single-function decompile bulk for `backend` at `addr_hex`.
 *
 * Output (heap, NUL-terminated, caller frees with free()):
 *   echo ===AURA-BEGIN:aaa===;aaa;echo ===AURA-END:aaa===;
 *   echo ===AURA-BEGIN:<cmd>@<addr_hex>===;<cmd> @ <addr_hex>;
 *   echo ===AURA-END:<cmd>@<addr_hex>===
 *
 * `aaa` is prefixed because each Rizin subprocess is stateless — without
 * a re-analysis pass the decompiler has no function boundary information.
 * (Same justification as `aura_rizin_cmd_build_per_function_batch_with_analysis`.)
 *
 * Returns NULL on:
 *   - backend == AURA_RIZIN_DEC_NONE or out-of-range
 *   - addr_hex fails aura_rizin_cmd_addr_hex_valid()
 *   - allocation failure
 */
char *aura_rizin_cmd_build_decompile(AuraRizinDecompileBackend backend,
                                     const char *addr_hex);

/* Phase 11.3.7 (P2.F2 C2): build framed bulk command for instruction-level
 * disassembly via rizin's `pdfj`. Produces:
 *   echo ===AURA-BEGIN:aaa===; aaa; echo ===AURA-END:aaa===
 *   echo ===AURA-BEGIN:pdfj===; pdfj @ <addr_hex>; echo ===AURA-END:pdfj===
 * Single-allocation NUL-terminated string; caller frees. NULL on invalid
 * addr_hex or allocation failure. The `pdfj` id is bare (no @addr suffix)
 * to avoid the rizin-0.9 `echo @` seek-operator quirk (cf. build_decompile). */
char *aura_rizin_cmd_build_disasm(const char *addr_hex);

/* Build a bounded continuous disassembly stream using `pdj` plus a bounded
 * `pD` text companion for the GUI's With arrows tab.
 * Produces `aaa`, `pdj <count> @ <addr_hex>`, and `pD 4096 @ <addr_hex>`.
 * count is clamped by the caller and must be > 0. */
char *aura_rizin_cmd_build_disasm_window(const char *addr_hex,
                                         unsigned    count);

/* Build a Cutter-style continuous text disassembly stream using `pD`.
 * Produces `aaa` plus `pD <byte_count> @ <addr_hex>` with terminal color
 * disabled and ASCII flow/line rendering enabled. byte_count is clamped by
 * the caller and must be > 0. */
char *aura_rizin_cmd_build_disasm_text_range(const char *addr_hex,
                                             unsigned    byte_count);

/* Build a per-function batch that prefixes `aaa` (re-analysis required because
 * each Rizin subprocess is stateless — Phase 1 subprocess is process-local).
 *
 * Produces: framed aaa; then for each address in addr_hex_list[], the 4 per-
 * function framed entries (agfj/axtj/afvj/aftj). aftj is included as a
 * skeleton frame (body may be empty). Returns NULL on any error (invalid
 * address, allocation failure, etc.). Caller frees with free(). */
char *aura_rizin_cmd_build_per_function_batch_with_analysis(
    const char *const *addr_hex_list,
    size_t             n);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_COMMAND_SET_H */
