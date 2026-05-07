/*
 * tp_adapter.h — AURA Third-Party I/O Hub: adapter contract + dispatch.
 *
 * Skeleton (2026-04-30). See docs/design/third_party_hub.md.
 *
 * Adapter contract (immutable static globals) + registry + hub
 * dispatch entry points. Adapters register once at startup; the hub
 * then routes pipeline calls to the appropriate adapter by source
 * tag (or AUTO via fixed priority).
 *
 * Memory ownership: the caller passes an initialized `aura_tp_vec_t`
 * and the adapter pushes elements into it. The caller frees the
 * vector when done. Borrowed string pointers inside elements remain
 * valid until the adapter context is closed.
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_TP_ADAPTER_H
#define AURA_TP_ADAPTER_H

#include <stddef.h>
#include <stdint.h>

#include "tp_binary.h"
#include "tp_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct aura_tp_adapter_t {
    const char       *name;     /* short identifier — diagnostic only   */
    aura_tp_source_t  source;   /* unique per registry                  */
    uint32_t          caps;     /* OR of aura_tp_caps_t                 */

    /* Renamed from `open` / `close` to avoid MSVC <io.h>'s
     * `#define open _open` / `#define close _close` macro collision
     * when this header is reached via aura_compat.h /FI on MSVC. */
    int (*open_fn) (aura_tp_binary_t *bin, void **ctx_out);
    int (*close_fn)(void *ctx);

    int (*disasm_range)  (void *ctx, aura_tp_addr_t va, size_t len,
                          aura_tp_vec_t *out_ops);
    int (*list_functions)(void *ctx, aura_tp_vec_t *out_funcs);
    int (*list_sections) (void *ctx, aura_tp_vec_t *out_sections);
} aura_tp_adapter_t;

/* Maximum simultaneously-registered adapters. One per source tag. */
#define AURA_TP_REGISTRY_MAX 8

/* Registry. Adapters live as static globals — the registry stores
 * pointers, not copies. Re-registering the same source yields E_DUP. */
int                       aura_tp_register_adapter(const aura_tp_adapter_t *adp);
const aura_tp_adapter_t  *aura_tp_lookup_adapter  (aura_tp_source_t source);
void                      aura_tp_clear_registry  (void); /* test-only */

/* Special source tag for hub dispatch: pick first adapter that
 * implements the requested capability, in fixed priority order
 * (AURA_NATIVE → RIZIN → CAPSTONE → ZYDIS → GHIDRA → YARA). */
#define AURA_TP_SOURCE_AUTO ((aura_tp_source_t)AURA_TP_SOURCE__COUNT)

/* Hub dispatch entry points. Each routes by `preferred` source tag
 * (or AUTO) and validates the adapter declares the capability. The
 * binary handle is forwarded to adapter::open on first call within
 * dispatch — for the skeleton this means open/close are paired
 * inline; future revisions may cache contexts.
 *
 * Returns:
 *   AURA_TP_OK / positive on success,
 *   AURA_TP_E_INVAL on NULL inputs,
 *   AURA_TP_E_NOTSUP if no adapter satisfies the request.
 */
int aura_tp_hub_disasm_range  (aura_tp_binary_t *bin,
                               aura_tp_source_t  preferred,
                               aura_tp_addr_t    va,
                               size_t            len,
                               aura_tp_vec_t    *out_ops);

int aura_tp_hub_list_functions(aura_tp_binary_t *bin,
                               aura_tp_source_t  preferred,
                               aura_tp_vec_t    *out_funcs);

int aura_tp_hub_list_sections (aura_tp_binary_t *bin,
                               aura_tp_source_t  preferred,
                               aura_tp_vec_t    *out_sections);

#ifdef __cplusplus
}
#endif

#endif /* AURA_TP_ADAPTER_H */
