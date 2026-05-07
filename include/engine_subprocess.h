/*
 * engine_subprocess.h — Engine-agnostic subprocess primitive (Phase 1.1).
 *
 * AURA delegates every disasm / analyze / decompile request to an external
 * engine binary (Ghidra primary, Rizin / RetDec / Capstone optional). All
 * adapters need the same low-level lifecycle: spawn(argv, envp_extra) →
 * drain(stdout + stderr, with timeout) → wait → optionally kill on timeout.
 *
 * This header defines that lifecycle as a single function (and a small
 * config / result pair) so each adapter under src/adapter/<engine>/ can
 * focus on engine-specific argv composition and exit-code interpretation
 * without re-implementing the POSIX subprocess plumbing.
 *
 * Scope (deliberately narrow per Phase 1):
 *   - Spawn one process, capture stdout + stderr to malloc'd buffers,
 *     enforce a wall-clock timeout (SIGTERM → 1 s grace → SIGKILL),
 *     return waitpid status + termination signal (if any).
 *   - stdin is bound to /dev/null (no engine in scope reads stdin in
 *     one-shot mode). Streaming-mode subprocess support is not in
 *     Phase 1 and would require additional primitives.
 *
 * The primitive is engine-neutral: it never touches XML, JSON, or any
 * engine-specific exit-code semantics. Adapters layer those concerns on
 * top via their own status mapping.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_ENGINE_SUBPROCESS_H
#define AURA_ENGINE_SUBPROCESS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Outcome of one subprocess run. The four success-side / failure-side
 * codes are AURA-side observations of the lifecycle; the child's own
 * exit-code semantics are surfaced via `exit_code` (when EXITED) and
 * `term_signal` (when SIGNALED), which adapters interpret. */
typedef enum AuraEngineSubprocStatus {
    AURA_ENGINE_SUBPROC_OK          = 0, /* spawn + wait succeeded; child EXITED with some code */
    AURA_ENGINE_SUBPROC_ERR_SPAWN   = 1, /* posix_spawn / pipe / fd setup failure */
    AURA_ENGINE_SUBPROC_ERR_TIMEOUT = 2, /* deadline exceeded; child SIGTERM/SIGKILL'd */
    AURA_ENGINE_SUBPROC_ERR_KILLED  = 3, /* child died from a signal not initiated by us */
    AURA_ENGINE_SUBPROC_ERR_INTERNAL = 4 /* OOM / waitpid / unexpected wait_status */
} AuraEngineSubprocStatus;

/* Inputs to one run. argv[0] = absolute path to the engine binary. argv
 * is NULL-terminated and must have at least 1 entry. envp_extra is a
 * NULL-terminated array of "KEY=VALUE" strings appended to the inherited
 * environ; pass NULL to inherit environ verbatim. timeout_s ≤ 0 disables
 * the wall-clock timeout (the call still waits for child exit). */
typedef struct AuraEngineSubprocConfig {
    const char *const *argv;          /**< NULL-terminated; argv[0] = binary path  */
    const char *const *envp_extra;    /**< NULL-terminated; appended to environ    */
    int                timeout_s;     /**< 0 = use default (30s); <0 = no timeout  */
    int                default_timeout_s; /**< treated as the timeout when timeout_s == 0; 0 ⇒ 30 */
} AuraEngineSubprocConfig;

/* Outputs of one run. stdout_buf / stderr_buf are heap-owned, NUL-terminated,
 * and may be NULL if the child produced no bytes on that stream. lengths
 * exclude the trailing NUL. wait_status mirrors waitpid's int status (raw,
 * for diagnostics). exit_code is meaningful iff WIFEXITED(wait_status) and
 * status == AURA_ENGINE_SUBPROC_OK. term_signal is set iff the child died
 * from a signal (either ours-on-timeout or otherwise).
 *
 * Caller must always pass a zero-initialized struct in and call
 * aura_engine_subproc_result_free() on the way out (no-op safe).
 */
typedef struct AuraEngineSubprocResult {
    AuraEngineSubprocStatus status;
    int   wait_status;
    int   exit_code;     /**< 0..255 when EXITED                         */
    int   term_signal;   /**< signal number when SIGNALED; 0 otherwise   */
    char *stdout_buf;    /**< malloc'd, NUL-terminated; NULL if empty    */
    size_t stdout_len;
    char *stderr_buf;    /**< malloc'd, NUL-terminated; NULL if empty    */
    size_t stderr_len;
} AuraEngineSubprocResult;

void aura_engine_subproc_result_free(AuraEngineSubprocResult *result);

/* Run the child. Returns the same value written to result->status.
 * On any failure, result is still populated (stderr_buf may be non-NULL
 * even when status != OK so adapters can surface diagnostics). */
AuraEngineSubprocStatus aura_engine_subproc_run(
    const AuraEngineSubprocConfig *cfg,
    AuraEngineSubprocResult       *result);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_ENGINE_SUBPROCESS_H */
