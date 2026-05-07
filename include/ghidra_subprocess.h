/*
 * ghidra_subprocess.h — D-29A turn #5 wrapper for vendored aura-decompile.
 *
 * Provides a clean C API over the argv one-shot mode shipped by
 * `third_party/ghidra-decompile/cpp/aura_argv_mode.cc` (turn #2).
 * The wrapper composes argv, manages the subprocess lifecycle (spawn /
 * stdout-stderr drain / timeout / waitpid), and maps the frozen exit-code
 * contract (0/1/2/3/4/5/6/+128+signal) into a typed AURA enum.
 *
 * Strict contract scope (per plan §"Schema Reality + Verification Scope
 * Amendment"):
 *   - This wrapper does NOT parse XML.
 *   - This wrapper does NOT strip envelopes (argv mode emits no envelope).
 *   - This wrapper does NOT translate op codes / element names.
 * Those are the responsibility of `ghidra_xml_normalize.c` (turn #6) and
 * `ghidra_xml_to_hir.c` (turn #7), respectively.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_GHIDRA_SUBPROCESS_H
#define AURA_GHIDRA_SUBPROCESS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Status / exit-code enum.
 *
 * 0..6 mirror the aura-decompile argv-mode exit-code contract verbatim
 * (plan §"argv 인자 사양 Fixation Amendment"). 100..103 cover AURA-side
 * spawn / waitpid / timeout / signal failures the child binary cannot
 * report. */
typedef enum {
    AURA_GHIDRA_OK              = 0,
    AURA_GHIDRA_ERR_ARGV        = 1,
    AURA_GHIDRA_ERR_LOAD        = 2,
    AURA_GHIDRA_ERR_ADDR        = 3,
    AURA_GHIDRA_ERR_ARCH        = 4,
    AURA_GHIDRA_ERR_DECOMPILE   = 5,
    AURA_GHIDRA_ERR_IO          = 6,
    AURA_GHIDRA_ERR_SPAWN       = 100,  /**< posix_spawn / pipe / fd setup failure */
    AURA_GHIDRA_ERR_TIMEOUT     = 101,  /**< exceeded configured timeout */
    AURA_GHIDRA_ERR_KILLED      = 102,  /**< child killed by signal (e.g., SIGSEGV) */
    AURA_GHIDRA_ERR_INTERNAL    = 103,  /**< malloc / waitpid / unexpected */
} AuraGhidraStatus;

/* Caller-provided configuration. All paths must outlive any pending call. */
typedef struct {
    const char *decompile_bin;       /**< absolute path to aura-decompile (required) */
    const char *processors_dir;      /**< vendored processors/ dir (forwarded as $AURA_GHIDRA_PROCESSORS_DIR if non-NULL) */
    const char *sla_dir;             /**< .sla output dir (forwarded as $AURA_GHIDRA_SLA_DIR if non-NULL) */
    int timeout_s;                   /**< 0 = use built-in default 30s; negative = no timeout */
} AuraGhidraSubprocessConfig;

/* Result struct. Caller must call aura_ghidra_decompile_result_free()
 * to release xml + stderr_log buffers. Safe to call on a zero-initialized
 * struct (no-op if nothing was allocated). */
typedef struct {
    AuraGhidraStatus status;
    int wait_status;                 /**< raw waitpid status (for diagnostics) */
    int term_signal;                 /**< signal number if killed; 0 otherwise */
    char *xml;                       /**< malloc'd, NUL-terminated; NULL on failure or empty */
    size_t xml_len;                  /**< byte length of xml (excluding the trailing NUL) */
    char *stderr_log;                /**< malloc'd, NUL-terminated; NULL if stderr was empty */
    size_t stderr_len;               /**< byte length of stderr_log (excluding NUL) */
} AuraGhidraDecompileResult;

void aura_ghidra_decompile_result_free(AuraGhidraDecompileResult *result);

/* Spawn aura-decompile in argv mode for the given binary + addr.
 *
 * Composes argv =
 *   {decompile_bin, "--decompile", binary_path, "--addr", <hex>,
 *    [optional "--arch", <arch>]}
 *
 * Forwards $AURA_GHIDRA_PROCESSORS_DIR and $AURA_GHIDRA_SLA_DIR from the
 * config into the child environment (when non-NULL). stdin is bound to
 * /dev/null (argv mode never reads stdin). stdout / stderr captured into
 * result->xml / result->stderr_log respectively.
 *
 * On any error, result->xml is NULL (frozen contract: stdout is not
 * trusted on non-zero exit). result->stderr_log retains diagnostic
 * output (5-stage log + Ghidra error messages) regardless of status.
 *
 * Return value mirrors result->status. */
AuraGhidraStatus aura_ghidra_decompile_at(
    const AuraGhidraSubprocessConfig *cfg,
    const char *binary_path,
    uint64_t addr,
    const char *arch_override_or_null,
    AuraGhidraDecompileResult *result);

#ifdef __cplusplus
}
#endif

#endif /* AURA_GHIDRA_SUBPROCESS_H */
