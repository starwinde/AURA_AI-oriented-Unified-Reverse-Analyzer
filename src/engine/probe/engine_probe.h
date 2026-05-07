// src/engine/probe/engine_probe.h — Phase 2.5
//
// Public probe entry points. Each engine has its own probe function so
// the registry / dispatcher above can compose them with whatever timeout
// or caching policy applies. Phase 2.5 starts with rizin only; later
// slices add ghidra-decomp, ghidra-full, angr, retdec.

#ifndef AURA_ENGINE_PROBE_H
#define AURA_ENGINE_PROBE_H

#include "command_runner.h"
#include "probe_result.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Resolve the spawn name for an engine binary.
 *
 * Lookup priority (rules.md §1 self-consistency, Phase 2.5.2):
 *   1. env var override (e.g. AURA_RIZIN_BIN) — wins if set + non-empty
 *   2. vendored repo path (third_party/<engine>/...) — used when
 *      AURA_REPO_ROOT env points at the repo root AND the file exists
 *   3. default name on PATH — final fallback (single name, no fallback list)
 *
 * Writes the resolved spawn name (env value, absolute vendored path, or
 * default name) into `out_buf` (NUL-terminated, truncated if too small).
 * Returns:
 *   1 = env override used
 *   2 = vendored path used
 *   3 = PATH default used
 *
 * `env_var`      may be NULL → skip step 1.
 * `vendored_rel` may be NULL or "" → skip step 2.
 * `default_name` MUST be non-NULL — it is the final fallback.
 *
 * The caller spawns whatever is in `out_buf`. Spawn failures still map
 * to ENGINE_MISSING on the result (lookup outcome is informational only;
 * the runner is the source of truth). */
int aura_probe_resolve_binary(const char *env_var,
                              const char *vendored_rel,
                              const char *default_name,
                              char       *out_buf,
                              size_t      out_cap);

/* Probe the Rizin engine via `rizin -v`.
 *
 * Returns 0 on success (caller inspects `out->status`), or a negative
 * value when the probe itself could not be performed (NULL args, etc.).
 * Spawn failures are NOT errors here — they map to ENGINE_MISSING on
 * the result. */
int aura_probe_rizin(AuraCommandRunner *runner, AuraProbeResult *out);

/* Probe the vendored ghidra-decomp binary via `ghidra-decomp --version`.
 * Same return contract as aura_probe_rizin. ENGINE_MISSING populates
 * out->install_hint with a vendor/path hint so downstream UIs can guide
 * the user to the third_party/ghidra-decomp tree. */
int aura_probe_ghidra_decomp(AuraCommandRunner *runner, AuraProbeResult *out);

/* Probe ghidra-full via two commands:
 *   1. `java -version`            → required runtime check (>= 17)
 *   2. `analyzeHeadless -help`    → engine binary check (exit 0)
 *
 * Status mapping:
 *   - Java spawn fails OR major < 17  → RUNTIME_MISSING (required_runtime
 *                                       set, install_hint OS-keyed)
 *   - Java OK, analyzeHeadless spawn fails → ENGINE_MISSING (install_hint
 *                                            points at third_party tree)
 *   - Both succeed → AVAILABLE (detected_version = analyzeHeadless banner
 *                               or "ghidra-full" sentinel) */
int aura_probe_ghidra_full(AuraCommandRunner *runner, AuraProbeResult *out);

/* Probe angr via `python3 -c "import angr; print(angr.__version__)"`.
 *   - python3 spawn fails              → RUNTIME_MISSING (Python 3 hint)
 *   - python3 OK, import fails (rc!=0) → ENGINE_MISSING (pip install angr
 *                                        inside third_party/angr/venv)
 *   - python3 OK, version on stdout    → AVAILABLE */
int aura_probe_angr(AuraCommandRunner *runner, AuraProbeResult *out);

/* Probe retdec via `retdec-decompiler --version`.
 * Same shape as ghidra-decomp: spawn fail → ENGINE_MISSING with hint,
 * exit 0 + version token → AVAILABLE. */
int aura_probe_retdec(AuraCommandRunner *runner, AuraProbeResult *out);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ENGINE_PROBE_H */
