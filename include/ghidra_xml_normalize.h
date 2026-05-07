/*
 * ghidra_xml_normalize.h — D-29A turn #6 byte-level XML normalize layer.
 *
 * Sits between aura_ghidra_decompile_at() (turn #5 wrapper) and any future
 * XML→HIR mapper (turn #7+). Receives raw stdout bytes from the vendored
 * aura-decompile argv mode and returns a clean UTF-8 XML buffer fit for
 * a strict parser.
 *
 * Frozen scope (per plan §"Schema Reality + Verification Scope Amendment",
 * Amendment 2 IN-list — verbatim):
 *   - UTF-8 BOM strip (EF BB BF at offset 0)
 *   - CRLF / lone CR → LF normalization
 *   - <?xml version="1.0" encoding="UTF-8"?> prolog prepend if missing
 *   - empty / whitespace-only input → AURA_XMLN_ERR_EMPTY
 *   - known-bad XML prefix (not '<' as first non-whitespace, or DOCTYPE)
 *     → AURA_XMLN_ERR_BAD
 *
 * Frozen OUT-list (these are NOT this layer's responsibility):
 *   - element rename (no <basicblock>↔<block>, no <pcode>↔<op>)
 *   - structure flatten (no <ast>/<varnodes>/<highlist> reordering)
 *   - op-code translation (no CPUI_xxx → AURA IrOpcode)
 *   - schema validation (no DTD / RNG check; tinyxml2 well-formed parse
 *     happens downstream)
 *   - semantic correctness (no function-boundary / CFG / call-target check)
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef AURA_GHIDRA_XML_NORMALIZE_H
#define AURA_GHIDRA_XML_NORMALIZE_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    AURA_XMLN_OK         = 0,
    AURA_XMLN_ERR_EMPTY  = 1,  /**< input NULL / 0-length / whitespace only */
    AURA_XMLN_ERR_BAD    = 2,  /**< known-bad prefix (HTML / JSON / binary) */
    AURA_XMLN_ERR_OOM    = 3,  /**< malloc failure */
} AuraXmlNormalizeStatus;

typedef struct {
    AuraXmlNormalizeStatus status;
    char  *xml;        /**< malloc'd, NUL-terminated; NULL on failure */
    size_t xml_len;    /**< byte length excluding the trailing NUL */
} AuraXmlNormalizeResult;

void aura_ghidra_xml_normalize_result_free(AuraXmlNormalizeResult *result);

/* Normalize raw stdout bytes from aura-decompile.
 *
 * Allocates a fresh buffer in result->xml. Caller owns it (free via
 * aura_ghidra_xml_normalize_result_free). Safe to call on a zero-init
 * result; the function fully overwrites it.
 *
 * Idempotent: applying normalize to its own output is a byte-exact
 * fixed point.
 *
 * Return value mirrors result->status. */
AuraXmlNormalizeStatus aura_ghidra_xml_normalize(
    const char *raw,
    size_t raw_len,
    AuraXmlNormalizeResult *result);

#ifdef __cplusplus
}
#endif

#endif /* AURA_GHIDRA_XML_NORMALIZE_H */
