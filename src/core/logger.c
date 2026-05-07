// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * logger.c -- AURA global logging implementation
 */

#include "logger.h"

#include <stdarg.h>
#include <string.h>

/* ── Global state ───────────────────────────────────────────────────────── */

static AuraLogLevel g_log_level  = AURA_LOG_INFO;
static FILE        *g_log_stream = NULL; /* NULL => stderr */

/* ── Level names ────────────────────────────────────────────────────────── */

static const char *level_tag(AuraLogLevel level)
{
    switch (level) {
    case AURA_LOG_DEBUG: return "DEBUG";
    case AURA_LOG_INFO:  return "INFO ";
    case AURA_LOG_WARN:  return "WARN ";
    case AURA_LOG_ERROR: return "ERROR";
    default:             return "?????";
    }
}

/* ── Public API ─────────────────────────────────────────────────────────── */

void aura_log_set_level(AuraLogLevel level)
{
    g_log_level = level;
}

AuraLogLevel aura_log_get_level(void)
{
    return g_log_level;
}

void aura_log_set_stream(FILE *stream)
{
    g_log_stream = stream;
}

void aura_log(AuraLogLevel level, const char *file, int line,
              const char *fmt, ...)
{
    if (level < g_log_level)
        return;

    FILE *out = g_log_stream ? g_log_stream : stderr;

    fprintf(out, "[%s] ", level_tag(level));

    /* Include file:line for DEBUG messages */
    if (file) {
        /* Strip path, show only basename */
        const char *base = strrchr(file, '/');
        if (base)
            base++;
        else
            base = file;
        fprintf(out, "%s:%d: ", base, line);
    }

    va_list ap;
    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    va_end(ap);

    fputc('\n', out);
    fflush(out);
}
