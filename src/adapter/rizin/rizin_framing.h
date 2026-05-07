/*
 * rizin_framing.h — stdout delimiter framing parser for the Rizin adapter.
 *
 * Each Rizin command's output is wrapped by echo lines injected by
 * rizin_command_set:
 *
 *   ===AURA-BEGIN:<id>===
 *   <raw JSON body — zero or more lines>
 *   ===AURA-END:<id>===
 *
 * This layer:
 *   1. Copies the full stdout verbatim into AuraRizinSnapshot.raw_buffer
 *      (R-4 output non-discard).
 *   2. Builds AuraRizinFrame immutable views (pointers into raw_buffer —
 *      no extra JSON copy) for each command's body.
 *   3. Returns distinct status codes for every malformed condition so
 *      callers can log precise diagnostics.
 *
 * Internal to src/adapter/rizin/. Do NOT include from core / gui.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_FRAMING_H
#define AURA_RIZIN_FRAMING_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Maximum command_id length, excluding NUL.
 * Allowed chars: [A-Za-z0-9_\-@.:], length 1..AURA_RIZIN_CMD_ID_MAX. */
#define AURA_RIZIN_CMD_ID_MAX 31u

/* ── Outcome codes ───────────────────────────────────────────────────── */

typedef enum AuraRizinFrameStatus {
    AURA_RIZIN_FRAME_OK              = 0,
    AURA_RIZIN_FRAME_ERR_NO_FRAMES   = 1, /* no BEGIN/END pairs found         */
    AURA_RIZIN_FRAME_ERR_NO_END      = 2, /* BEGIN without matching END        */
    AURA_RIZIN_FRAME_ERR_NO_BEGIN    = 3, /* END without preceding BEGIN       */
    AURA_RIZIN_FRAME_ERR_NESTED      = 4, /* BEGIN encountered inside frame    */
    AURA_RIZIN_FRAME_ERR_ID_MISMATCH = 5, /* BEGIN id != END id               */
    AURA_RIZIN_FRAME_ERR_INVALID_ID  = 6, /* id contains illegal chars/length  */
    AURA_RIZIN_FRAME_ERR_OOM         = 7, /* malloc / realloc failure          */
} AuraRizinFrameStatus;

/* ── Per-command frame ───────────────────────────────────────────────── */

/* raw_json is an immutable view into AuraRizinSnapshot.raw_buffer.
 * Lifetime is bounded by the owning AuraRizinSnapshot.
 * raw_json_len may be 0 for commands that produce no output (e.g. "aaa"). */
typedef struct AuraRizinFrame {
    char        command_id[AURA_RIZIN_CMD_ID_MAX + 1u];
    const char *raw_json;      /* pointer into raw_buffer; NOT NUL-terminated */
    size_t      raw_json_len;
} AuraRizinFrame;

/* ── Full snapshot ───────────────────────────────────────────────────── */

/* AuraRizinSnapshot owns raw_buffer and frames[].
 * Frames are ordered by appearance in stdout. */
typedef struct AuraRizinSnapshot {
    /* R-4: verbatim copy of subprocess stdout (heap-owned, NUL-terminated). */
    char  *raw_buffer;
    size_t raw_buffer_len;

    AuraRizinFrame *frames;
    size_t          frame_count;
} AuraRizinSnapshot;

/* ── API ─────────────────────────────────────────────────────────────── */

/* Parse `buf` (len bytes, need not be NUL-terminated) into `out`.
 *
 * On success: out->raw_buffer is a heap copy of buf; frames[] are views
 * into it.  Call aura_rizin_snapshot_free(out) when done.
 *
 * On any error: out is left in a safe, freeable state; call _free anyway.
 * buf and len are not modified. */
AuraRizinFrameStatus aura_rizin_frame_parse(const char        *buf,
                                             size_t             len,
                                             AuraRizinSnapshot *out);

/* Release all heap memory in *s.  NULL-safe.  Does NOT free s itself. */
void aura_rizin_snapshot_free(AuraRizinSnapshot *s);

/* Validate a command_id string of `len` bytes (need not be NUL-terminated).
 * Returns 1 if valid (length 1..AURA_RIZIN_CMD_ID_MAX, chars [A-Za-z0-9_\-@.:]).
 * Returns 0 otherwise. */
int aura_rizin_command_id_valid(const char *id, size_t len);

/* ── Command-id suffix parser ────────────────────────────────────────── */

/* Split a command_id of the form "<base>[_<addr_hex>]" into parts.
 *
 * base is always populated (NUL-terminated). has_addr is set to 1 iff
 * the id contains "_" followed by a valid hex address ("0x..."). addr
 * is set to the parsed address value when has_addr == 1.
 *
 * Phase 3B: separator changed from '@' to '_' because rizin 0.9 `echo`
 * treats '@' inside its argument as a seek operator and would silently
 * drop the framing line.
 *
 * Returns 1 on success (base could be extracted).
 * Returns 0 if id is NULL or base would overflow AURA_RIZIN_CMD_ID_MAX. */
typedef struct AuraRizinCmdIdParts {
    char     base[AURA_RIZIN_CMD_ID_MAX + 1u];
    int      has_addr;
    uint64_t addr;
} AuraRizinCmdIdParts;

int aura_rizin_command_id_parse(const char *id, AuraRizinCmdIdParts *out);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_FRAMING_H */
