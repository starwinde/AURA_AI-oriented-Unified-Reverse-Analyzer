// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * logger.h -- AURA global logging facility
 *
 * Four severity levels: DEBUG, INFO, WARN, ERROR.
 * DEBUG output is suppressed by default; enable with aura_log_set_level(AURA_LOG_DEBUG)
 * or the --verbose CLI flag.
 *
 * Usage:
 *   AURA_LOG_D("loaded %d instructions", count);
 *   AURA_LOG_I("parsing %s", path);
 *   AURA_LOG_W("section .text not found, falling back");
 *   AURA_LOG_E("elf_parser_load failed: %s", aura_error_str(err));
 */

#ifndef AURA_LOGGER_H
#define AURA_LOGGER_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AuraLogLevel {
    AURA_LOG_DEBUG = 0,
    AURA_LOG_INFO  = 1,
    AURA_LOG_WARN  = 2,
    AURA_LOG_ERROR = 3,
    AURA_LOG_NONE  = 4,
} AuraLogLevel;

/**
 * Set the minimum log level. Messages below this level are suppressed.
 * Default: AURA_LOG_INFO (DEBUG suppressed).
 */
void aura_log_set_level(AuraLogLevel level);

/** Get the current minimum log level. */
AuraLogLevel aura_log_get_level(void);

/**
 * Set the log output stream. Default: stderr.
 * Pass NULL to reset to stderr.
 */
void aura_log_set_stream(FILE *stream);

/**
 * Core log function. Prefer the macros below.
 */
void aura_log(AuraLogLevel level, const char *file, int line,
              const char *fmt, ...)
#ifdef __GNUC__
    __attribute__((format(printf, 4, 5)))
#endif
;

/* Convenience macros with file/line for DEBUG, source-free for others */
#define AURA_LOG_D(fmt, ...) \
    aura_log(AURA_LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define AURA_LOG_I(fmt, ...) \
    aura_log(AURA_LOG_INFO, NULL, 0, fmt, ##__VA_ARGS__)
#define AURA_LOG_W(fmt, ...) \
    aura_log(AURA_LOG_WARN, NULL, 0, fmt, ##__VA_ARGS__)
#define AURA_LOG_E(fmt, ...) \
    aura_log(AURA_LOG_ERROR, NULL, 0, fmt, ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif /* AURA_LOGGER_H */
