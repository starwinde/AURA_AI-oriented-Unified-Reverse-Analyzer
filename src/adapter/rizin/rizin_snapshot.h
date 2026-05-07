/*
 * rizin_snapshot.h — combined raw / framed / cJSON / canonical snapshot.
 *
 * Pipeline position:
 *   subprocess.stdout
 *     → rizin_framing.parse        (raw_buffer + frames[])
 *     → rizin_snapshot.parse       (cJSON tree per frame; canonical mirror)
 *     → third_party_hub/rizin_to_aura.c (canonical → normalized records)
 *
 * R-4 contract: raw_buffer holds the verbatim subprocess stdout. Nothing
 * in this layer mutates it. Canonical string fields are pointers into
 * snapshot-owned storage (the cJSON tree's own buffers); their lifetime
 * matches the AuraRizinFullSnapshot.
 *
 * Phase 2A scope: aflj (functions) and isj (symbols) populate canonical.
 * Other recognised command_ids (agfj/axtj/afvj/aftj/iij/izj/aaa) parse
 * their JSON but populate no canonical fields yet — the snapshot retains
 * their cJSON trees for downstream Phase 2B passes.
 *
 * Internal to src/adapter/rizin/. Do NOT include from core / gui.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_RIZIN_SNAPSHOT_H
#define AURA_RIZIN_SNAPSHOT_H

#include <stddef.h>

#include "rizin_framing.h"
#include "third_party_hub/rizin_canonical.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum AuraRizinSnapshotStatus {
    AURA_RIZIN_SNAPSHOT_OK            = 0,
    AURA_RIZIN_SNAPSHOT_ERR_FRAMING   = 1, /* framing parse failed       */
    AURA_RIZIN_SNAPSHOT_ERR_JSON      = 2, /* a frame body was not valid JSON
                                              and not empty (aaa)        */
    AURA_RIZIN_SNAPSHOT_ERR_OOM       = 3,
    AURA_RIZIN_SNAPSHOT_ERR_INVALID   = 4,
} AuraRizinSnapshotStatus;

/* Owns: raw.frames, raw.raw_buffer, every cJSON tree, every canonical
 * heap array (functions, symbols, cfgs, xrefs, variables, …).
 * String fields inside canonical point INTO raw.raw_buffer (do not free). */
typedef struct AuraRizinFullSnapshot {
    AuraRizinSnapshot       raw;
    AuraRizinCanonical      canonical;
    AuraRizinFrameStatus    framing_status; /* surfaced for diagnostics  */

    /* Opaque storage for the per-frame cJSON trees. Treated as an array
     * of `void *` of length raw.frame_count; freed by snapshot_free. */
    void                  **_json_trees;
} AuraRizinFullSnapshot;

/* Parse raw subprocess stdout (R-4 verbatim copied internally) into
 * frames + cJSON + canonical.
 *
 * On success: out is fully populated; caller must free with
 * aura_rizin_full_snapshot_free().
 *
 * On any error: out is left in a safe, free-able state (call _free anyway).
 *               framing_status holds the framing layer's error code. */
AuraRizinSnapshotStatus aura_rizin_snapshot_parse(
    const char            *buf,
    size_t                 len,
    AuraRizinFullSnapshot *out);

void aura_rizin_full_snapshot_free(AuraRizinFullSnapshot *s);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_RIZIN_SNAPSHOT_H */
