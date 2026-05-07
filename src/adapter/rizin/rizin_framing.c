/*
 * rizin_framing.c — BEGIN/END delimiter framing for bulk Rizin stdout.
 *
 * Recognized delimiter lines (after CRLF/LF stripping):
 *   ===AURA-BEGIN:<id>===
 *   ===AURA-END:<id>===
 *
 * Frame raw_json fields are immutable views into AuraRizinSnapshot.raw_buffer;
 * no second JSON allocation is made here.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "rizin_framing.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BEGIN_PREFIX  "===AURA-BEGIN:"
#define END_PREFIX    "===AURA-END:"
#define DELIM_SUFFIX  "==="

#define BEGIN_PREFIX_LEN  (sizeof(BEGIN_PREFIX)  - 1u)
#define END_PREFIX_LEN    (sizeof(END_PREFIX)    - 1u)
#define DELIM_SUFFIX_LEN  (sizeof(DELIM_SUFFIX)  - 1u)

/* ── command_id validation and parsing ───────────────────────────────── */

int aura_rizin_command_id_valid(const char *id, size_t len)
{
    size_t i;
    if (!id || len == 0 || len > AURA_RIZIN_CMD_ID_MAX) return 0;
    for (i = 0; i < len; ++i) {
        unsigned char ch = (unsigned char)id[i];
        if ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9') ||
            ch == '_' || ch == '-' || ch == '@' || ch == '.' || ch == ':') {
            continue;
        }
        return 0;
    }
    return 1;
}

int aura_rizin_command_id_parse(const char *id, AuraRizinCmdIdParts *out)
{
    if (!id || !out) return 0;
    memset(out, 0, sizeof(*out));

    /* Phase 3B: separator is '_'. Earlier versions used '@', but rizin
     * 0.9 echo treats '@' inside an argument as a seek operator and
     * would silently drop a delimiter line that contained "@<addr>". */
    const char *sep = strchr(id, '_');
    size_t base_len = sep ? (size_t)(sep - id) : strlen(id);
    if (base_len == 0 || base_len > AURA_RIZIN_CMD_ID_MAX) return 0;
    memcpy(out->base, id, base_len);
    out->base[base_len] = '\0';

    if (!sep) return 1; /* no suffix, done */

    /* Try to parse "_0x<hex>" suffix. */
    const char *suffix = sep + 1;
    if (suffix[0] == '0' && (suffix[1] == 'x' || suffix[1] == 'X')) {
        uint64_t val = 0;
        size_t i = 2;
        for (; suffix[i]; ++i) {
            char c = suffix[i];
            int d;
            if      (c >= '0' && c <= '9') d = c - '0';
            else if (c >= 'a' && c <= 'f') d = c - 'a' + 10;
            else if (c >= 'A' && c <= 'F') d = c - 'A' + 10;
            else { i = 2; break; } /* malformed */
            if (i - 2 >= 16) { i = 2; break; } /* overflow guard */
            val = (val << 4) | (uint64_t)d;
        }
        if (i > 2) {
            out->has_addr = 1;
            out->addr     = val;
        }
    }
    return 1; /* base always valid even if suffix malformed */
}

/* ── lifecycle ───────────────────────────────────────────────────────── */

void aura_rizin_snapshot_free(AuraRizinSnapshot *s)
{
    if (!s) return;
    free(s->raw_buffer);
    free(s->frames);
    s->raw_buffer     = NULL;
    s->raw_buffer_len = 0;
    s->frames         = NULL;
    s->frame_count    = 0;
}

/* ── frame array ─────────────────────────────────────────────────────── */

typedef struct {
    AuraRizinFrame *data;
    size_t          count;
    size_t          cap;
} FrameVec;

static int framevec_push(FrameVec *v, const AuraRizinFrame *f)
{
    if (v->count >= v->cap) {
        size_t new_cap = v->cap ? v->cap * 2u : 8u;
        AuraRizinFrame *p = (AuraRizinFrame *)realloc(
            v->data, new_cap * sizeof(AuraRizinFrame));
        if (!p) return -1;
        v->data = p;
        v->cap  = new_cap;
    }
    v->data[v->count++] = *f;
    return 0;
}

/* ── line iterator ───────────────────────────────────────────────────── */

/* Returns pointer to start of next line, or NULL if at end.
 * *line_start / *line_len describe the current line WITHOUT the newline
 * sequence. Handles both LF and CRLF. */
static const char *next_line(const char *p, const char *end,
                             const char **line_start, size_t *line_len)
{
    const char *nl;
    if (p >= end) return NULL;
    *line_start = p;
    nl = (const char *)memchr(p, '\n', (size_t)(end - p));
    if (nl) {
        *line_len = (size_t)(nl - p);
        if (*line_len > 0 && p[*line_len - 1u] == '\r') --(*line_len);
        return nl + 1;
    }
    /* no newline — last line without terminator */
    *line_len = (size_t)(end - p);
    return end;
}

/* ── delimiter recognition ───────────────────────────────────────────── */

/* Try to parse "===AURA-BEGIN:<id>===" or "===AURA-END:<id>===".
 * On match: copies id into id_out (NUL-terminated), returns 1.
 * On invalid id chars/length: returns -1 (INVALID_ID).
 * On no match: returns 0. */
static int parse_delim(const char *line, size_t len,
                        const char *prefix, size_t prefix_len,
                        char *id_out)
{
    size_t id_len;
    if (len < prefix_len + DELIM_SUFFIX_LEN) return 0;
    if (memcmp(line, prefix, prefix_len) != 0) return 0;
    if (memcmp(line + len - DELIM_SUFFIX_LEN,
               DELIM_SUFFIX, DELIM_SUFFIX_LEN) != 0) return 0;

    id_len = len - prefix_len - DELIM_SUFFIX_LEN;
    if (!aura_rizin_command_id_valid(line + prefix_len, id_len)) return -1;
    memcpy(id_out, line + prefix_len, id_len);
    id_out[id_len] = '\0';
    return 1;
}

/* ── main parse ──────────────────────────────────────────────────────── */

AuraRizinFrameStatus aura_rizin_frame_parse(const char        *buf,
                                             size_t             len,
                                             AuraRizinSnapshot *out)
{
    FrameVec fv;
    const char *p, *end;
    int         in_frame = 0;
    char        cur_id[AURA_RIZIN_CMD_ID_MAX + 1u];
    char        del_id[AURA_RIZIN_CMD_ID_MAX + 1u];
    const char *json_start = NULL; /* points into raw_buffer */
    AuraRizinFrameStatus err;

    if (!out) return AURA_RIZIN_FRAME_ERR_OOM;
    memset(out, 0, sizeof(*out));
    memset(&fv, 0, sizeof(fv));

    /* NULL buf with len==0 is an empty-buffer case → treated as no frames. */
    if (!buf && len != 0) return AURA_RIZIN_FRAME_ERR_NO_FRAMES;

    /* Copy stdout verbatim; NUL-terminate for safety. */
    out->raw_buffer = (char *)malloc(len + 1u);
    if (!out->raw_buffer) return AURA_RIZIN_FRAME_ERR_OOM;
    if (len) memcpy(out->raw_buffer, buf, len);
    out->raw_buffer[len] = '\0';
    out->raw_buffer_len  = len;

    p   = out->raw_buffer;
    end = out->raw_buffer + len;

    while (p < end) {
        const char *line;
        size_t      line_len;
        const char *next = next_line(p, end, &line, &line_len);
        int bm, em;

        bm = parse_delim(line, line_len, BEGIN_PREFIX, BEGIN_PREFIX_LEN, del_id);
        if (bm < 0) { err = AURA_RIZIN_FRAME_ERR_INVALID_ID; goto fail; }
        if (bm > 0) {
            if (in_frame) { err = AURA_RIZIN_FRAME_ERR_NESTED; goto fail; }
            memcpy(cur_id, del_id, sizeof(del_id));
            json_start = next; /* body starts at next line */
            in_frame = 1;
            p = next;
            continue;
        }

        em = parse_delim(line, line_len, END_PREFIX, END_PREFIX_LEN, del_id);
        if (em < 0) { err = AURA_RIZIN_FRAME_ERR_INVALID_ID; goto fail; }
        if (em > 0) {
            const char *json_end;
            AuraRizinFrame fr;
            if (!in_frame) { err = AURA_RIZIN_FRAME_ERR_NO_BEGIN; goto fail; }
            if (strcmp(cur_id, del_id) != 0) {
                err = AURA_RIZIN_FRAME_ERR_ID_MISMATCH; goto fail;
            }
            /* Body = everything from json_start up to the line preceding END.
             * Strip the trailing newline (LF / CRLF) if present. */
            json_end = line; /* start of "===AURA-END:..." line */
            if (json_end > json_start && json_end[-1] == '\n') --json_end;
            if (json_end > json_start && json_end[-1] == '\r') --json_end;

            memset(&fr, 0, sizeof(fr));
            memcpy(fr.command_id, cur_id, strlen(cur_id) + 1u);
            fr.raw_json     = json_start;
            fr.raw_json_len = (json_end >= json_start)
                              ? (size_t)(json_end - json_start) : 0u;

            if (framevec_push(&fv, &fr) != 0) {
                err = AURA_RIZIN_FRAME_ERR_OOM; goto fail;
            }
            in_frame   = 0;
            json_start = NULL;
            cur_id[0]  = '\0';
        }
        p = next;
    }

    if (in_frame) { err = AURA_RIZIN_FRAME_ERR_NO_END; goto fail; }
    if (fv.count == 0) { err = AURA_RIZIN_FRAME_ERR_NO_FRAMES; goto fail; }

    out->frames      = fv.data;
    out->frame_count = fv.count;
    return AURA_RIZIN_FRAME_OK;

fail:
    free(fv.data);
    aura_rizin_snapshot_free(out);
    return err;
}
