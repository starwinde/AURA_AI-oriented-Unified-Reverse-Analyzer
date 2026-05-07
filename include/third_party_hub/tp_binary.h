/*
 * tp_binary.h — AURA Third-Party I/O Hub: opaque binary handle.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * `aura_tp_binary_t` mirrors `RzCore *` shape: an opaque handle that
 * owns the mmap'd bytes and identifying metadata (path, size). It is
 * the single input handle every adapter receives. Backed by AURA's
 * existing `MappedFile` (mapped_file.h) — the hub does not introduce
 * new mmap logic, only a shared façade type.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_TP_BINARY_H
#define AURA_TP_BINARY_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Opaque. Definition lives in src/third_party_hub/tp_binary.c. */
typedef struct aura_tp_binary aura_tp_binary_t;

/* Open a file for hub consumption. Reuses MappedFile internally.
 * Returns NULL on failure (path NULL / open fails / OOM). */
aura_tp_binary_t *aura_tp_binary_open (const char *path);
void              aura_tp_binary_close(aura_tp_binary_t *bin);

/* Read-only accessors. NULL-safe (return NULL / 0). */
const uint8_t    *aura_tp_binary_bytes(const aura_tp_binary_t *bin);
size_t            aura_tp_binary_size (const aura_tp_binary_t *bin);
const char       *aura_tp_binary_path (const aura_tp_binary_t *bin);

#ifdef __cplusplus
}
#endif

#endif /* AURA_TP_BINARY_H */
