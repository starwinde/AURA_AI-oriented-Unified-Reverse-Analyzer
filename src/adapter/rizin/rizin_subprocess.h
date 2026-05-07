/*
 * rizin_subprocess.h — argv composition + exec-path resolution for the
 * Rizin engine adapter (Phase 2A). Internal to src/adapter/rizin/.
 *
 * Per the pivot policy:
 *   - librz linking forbidden (R-2 / D-27).
 *   - Rizin headers (`rz_core.h` etc.) MUST NOT be included anywhere.
 *   - All Rizin invocations go through this stateless subprocess
 *     primitive layered on top of include/engine_subprocess.h.
 *
 * Exec path resolution priority (Phase 2A decision, 2026-04-30):
 *   1. caller-supplied `exec_path_override` (typically from manifest)
 *   2. environment variable `AURA_RIZIN_PATH`
 *   3. PATH lookup of "rizin" (with ".exe" suffix on Windows)
 *
 * Missing rizin → AURA_RIZIN_SUB_ERR_NOT_FOUND (NOT a crash).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_SUBPROCESS_H
#define AURA_RIZIN_SUBPROCESS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Adapter-side outcome codes. Map onto AuraEngineStatus in
 * rizin_adapter.c — kept separate so this file does not depend on
 * engine_request.h. */
typedef enum AuraRizinSubStatus {
    AURA_RIZIN_SUB_OK         = 0,
    AURA_RIZIN_SUB_ERR_INVALID  = 1,
    AURA_RIZIN_SUB_ERR_NOT_FOUND = 2, /* rizin executable not located    */
    AURA_RIZIN_SUB_ERR_SPAWN  = 3,
    AURA_RIZIN_SUB_ERR_TIMEOUT = 4,
    AURA_RIZIN_SUB_ERR_CRASH  = 5,
    AURA_RIZIN_SUB_ERR_INTERNAL = 6,
} AuraRizinSubStatus;

/* One run input. `commands` is the bulk command string passed via
 * `-c`; the wrapper appends a trailing `q!!` to force exit even if a
 * command faults. timeout_s ≤0 disables the wall-clock timeout. */
typedef struct AuraRizinSubRequest {
    const char *exec_path_override; /* NULL = fall through to env/PATH    */
    const char *binary_path;        /* required                            */
    const char *commands;           /* required; semicolon-separated       */
    int         timeout_s;          /* 0 = adapter default (30s)           */
} AuraRizinSubRequest;

/* Output. stdout_buf / stderr_buf heap-owned, NUL-terminated; freed by
 * aura_rizin_sub_result_free(). */
typedef struct AuraRizinSubResult {
    AuraRizinSubStatus status;
    int    exit_code;
    int    term_signal;
    char  *stdout_buf;
    size_t stdout_len;
    char  *stderr_buf;
    size_t stderr_len;
    char  *resolved_exec; /* heap; NULL if status == ERR_NOT_FOUND/INVALID */
} AuraRizinSubResult;

void aura_rizin_sub_result_free(AuraRizinSubResult *r);

/* Resolve the rizin executable path using the documented priority.
 * Returns a heap-allocated string on success (caller frees with free()),
 * or NULL if no candidate is found. `override` may be NULL. This is
 * exposed for tests; aura_rizin_sub_run calls it internally. */
char *aura_rizin_sub_resolve_exec(const char *override);

/* Fire-and-wait one rizin run. Always populates `result`; safe to call
 * aura_rizin_sub_result_free() regardless of the return value. */
AuraRizinSubStatus aura_rizin_sub_run(const AuraRizinSubRequest *req,
                                      AuraRizinSubResult        *result);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_SUBPROCESS_H */
