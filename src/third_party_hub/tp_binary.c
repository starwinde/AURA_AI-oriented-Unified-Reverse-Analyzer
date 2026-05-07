/*
 * tp_binary.c — AURA Third-Party I/O Hub: opaque binary handle.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * Thin wrapper over MappedFile (mapped_file.h). The hub does not
 * introduce new mmap logic — it only owns the lifetime façade so
 * adapters receive a single, source-neutral handle.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "third_party_hub/tp_binary.h"

#include "mapped_file.h"

#include <stdlib.h>

struct aura_tp_binary {
    MappedFile *mf;
};

aura_tp_binary_t *aura_tp_binary_open(const char *path)
{
    if (!path) return NULL;

    aura_tp_binary_t *bin = calloc(1, sizeof(*bin));
    if (!bin) return NULL;

    bin->mf = mapped_file_open(path);
    if (!bin->mf) {
        free(bin);
        return NULL;
    }
    return bin;
}

void aura_tp_binary_close(aura_tp_binary_t *bin)
{
    if (!bin) return;
    mapped_file_destroy(bin->mf);
    free(bin);
}

const uint8_t *aura_tp_binary_bytes(const aura_tp_binary_t *bin)
{
    return (bin && bin->mf) ? bin->mf->map : NULL;
}

size_t aura_tp_binary_size(const aura_tp_binary_t *bin)
{
    return (bin && bin->mf) ? bin->mf->size : 0;
}

const char *aura_tp_binary_path(const aura_tp_binary_t *bin)
{
    return (bin && bin->mf) ? bin->mf->path : NULL;
}
