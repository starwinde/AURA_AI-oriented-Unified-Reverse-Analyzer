// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * aura_io.c — AuraStrBuf implementation. See include/aura/aura_io.h.
 *
 * Implementation notes (Phase 9 issue 01, 2026-05-03):
 *   - Pure malloc/realloc/free; no OS-specific calls.
 *   - Lazy first-allocation: 256 bytes on first write.
 *   - Geometric growth ×2 to amortize append cost.
 *   - Sticky err: once set, all ops silently no-op until reset by detach
 *     or free. Callers check at the end via detach() return or status().
 *   - data[len] = '\0' is maintained whenever data != NULL, so callers
 *     may treat it as a C string between ops (read-only).
 */

#include "aura/aura_io.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AURA_STRBUF_INITIAL_CAP  ((size_t)256)

/* Ensure sb has room for `additional` more bytes plus the null terminator.
 * Returns 0 on success, -1 on OOM (and sets sb->err). */
static int aura_strbuf_reserve(AuraStrBuf *sb, size_t additional)
{
    size_t need = sb->len + additional + 1;   /* +1 for NUL */
    if (need <= sb->cap) return 0;

    size_t new_cap = (sb->cap == 0) ? AURA_STRBUF_INITIAL_CAP : sb->cap;
    while (new_cap < need) {
        size_t doubled = new_cap * 2;
        if (doubled < new_cap) {              /* size_t overflow */
            sb->err = -1;
            return -1;
        }
        new_cap = doubled;
    }

    char *new_data = (char *)realloc(sb->data, new_cap);
    if (!new_data) {
        sb->err = -1;
        return -1;
    }
    sb->data = new_data;
    sb->cap  = new_cap;
    return 0;
}

/* ===================================================================
 * Public API
 * =================================================================== */

void aura_strbuf_init(AuraStrBuf *sb)
{
    if (!sb) return;
    sb->data = NULL;
    sb->len  = 0;
    sb->cap  = 0;
    sb->err  = 0;
}

void aura_strbuf_init_capacity(AuraStrBuf *sb, size_t initial_cap)
{
    if (!sb) return;
    aura_strbuf_init(sb);
    if (initial_cap == 0) return;

    char *buf = (char *)malloc(initial_cap);
    if (!buf) {
        sb->err = -1;
        return;
    }
    buf[0]   = '\0';
    sb->data = buf;
    sb->cap  = initial_cap;
}

void aura_strbuf_vprintf(AuraStrBuf *sb, const char *fmt, va_list ap)
{
    if (!sb || sb->err) return;
    if (!fmt) { sb->err = -1; return; }

    /* First attempt: probe required size with a copy of ap. */
    va_list ap_copy;
    va_copy(ap_copy, ap);

    /* If there's already room, write directly; otherwise vsnprintf-probe
     * with len=0 to learn the required size, then grow. */
    size_t avail = (sb->cap > sb->len) ? (sb->cap - sb->len) : 0;
    int needed = vsnprintf(sb->data ? sb->data + sb->len : NULL,
                           avail, fmt, ap_copy);
    va_end(ap_copy);

    if (needed < 0) { sb->err = -1; return; }

    if ((size_t)needed >= avail) {
        /* Not enough room (or no buffer at all) — grow and retry. */
        if (aura_strbuf_reserve(sb, (size_t)needed) != 0) return;
        avail = sb->cap - sb->len;
        int written = vsnprintf(sb->data + sb->len, avail, fmt, ap);
        if (written < 0 || (size_t)written != (size_t)needed) {
            sb->err = -1;
            return;
        }
    }

    sb->len += (size_t)needed;
    /* vsnprintf already wrote NUL, but ensure invariant if data was empty. */
    if (sb->data) sb->data[sb->len] = '\0';
}

void aura_strbuf_printf(AuraStrBuf *sb, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    aura_strbuf_vprintf(sb, fmt, ap);
    va_end(ap);
}

void aura_strbuf_append(AuraStrBuf *sb, const char *data, size_t n)
{
    if (!sb || sb->err) return;
    if (n == 0) return;
    if (!data) { sb->err = -1; return; }

    if (aura_strbuf_reserve(sb, n) != 0) return;
    memcpy(sb->data + sb->len, data, n);
    sb->len += n;
    sb->data[sb->len] = '\0';
}

char *aura_strbuf_detach(AuraStrBuf *sb, size_t *out_len)
{
    if (!sb || sb->err || !sb->data) return NULL;

    /* Shrink to exactly len + 1 (caller pays only for what was written). */
    char *result = (char *)realloc(sb->data, sb->len + 1);
    if (!result) result = sb->data;   /* shrink failure: keep original */
    result[sb->len] = '\0';

    if (out_len) *out_len = sb->len;

    /* Reset to fresh state — sb is reusable or safe to free. */
    sb->data = NULL;
    sb->len  = 0;
    sb->cap  = 0;
    sb->err  = 0;

    return result;
}

void aura_strbuf_free(AuraStrBuf *sb)
{
    if (!sb) return;
    free(sb->data);
    sb->data = NULL;
    sb->len  = 0;
    sb->cap  = 0;
    sb->err  = 0;
}

int aura_strbuf_status(const AuraStrBuf *sb)
{
    return sb ? sb->err : -1;
}

/* Phase 9 issue 03b — shared tmpfile→strbuf bridge for FILE*-only emit
 * APIs. Returns the inner emit fn's status (or AURA_ERR_IO on tmpfile/
 * read/seek failures). Defined here so each *_with_strbuf wrapper stays
 * a thin 1-call function. AURA_OK / AURA_ERR_* are pulled in via
 * <stdio.h> + the existing AuraError chain at link time; the prototype
 * uses plain int for the callback to avoid circular includes. */
int aura_strbuf_capture_emit(AuraEmitFileFn fn, void *ctx, AuraStrBuf *out)
{
    /* AURA_OK = 0, AURA_ERR_INVALID_ARG = -4, AURA_ERR_IO = -3,
     * AURA_ERR_NOMEM = -2 — match aura.h. We use literal ints here
     * because aura_io is meant to be the lowest-level dependency. */
    if (!fn || !out) return -4;     /* AURA_ERR_INVALID_ARG */

    FILE *tmp = tmpfile();
    if (!tmp) return -3;            /* AURA_ERR_IO */

    int rc = fn(ctx, tmp);
    if (rc != 0) {
        fclose(tmp);
        return rc;
    }

    if (fflush(tmp) != 0 || fseek(tmp, 0, SEEK_END) != 0) {
        fclose(tmp);
        return -3;
    }
    long sz = ftell(tmp);
    if (sz < 0) {
        fclose(tmp);
        return -3;
    }
    rewind(tmp);

    if (sz > 0) {
        char *scratch = (char *)malloc((size_t)sz);
        if (!scratch) {
            fclose(tmp);
            return -2;              /* AURA_ERR_NOMEM */
        }
        if (fread(scratch, 1, (size_t)sz, tmp) != (size_t)sz) {
            free(scratch);
            fclose(tmp);
            return -3;
        }
        aura_strbuf_append(out, scratch, (size_t)sz);
        free(scratch);
    }
    fclose(tmp);

    if (aura_strbuf_status(out) != 0) return -2;
    return 0;
}
