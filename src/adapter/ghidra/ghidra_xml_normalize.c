/*
 * ghidra_xml_normalize.c — D-29A turn #6 byte-level XML normalize layer.
 *
 * Pure transformations (no XML parse, no semantic interpretation):
 *   1) BOM strip               — drop EF BB BF if present at offset 0
 *   2) Line-ending normalize   — \r\n → \n, lone \r → \n
 *   3) Empty / whitespace-only — reject as AURA_XMLN_ERR_EMPTY
 *   4) Known-bad prefix gate   — first non-ws char must be '<'; reject
 *                                <!DOCTYPE html, <html, <!--<html-->, JSON {/[
 *   5) Prolog prepend          — if body does NOT start with "<?xml",
 *                                prepend the canonical 5-byte UTF-8 prolog
 *
 * Frozen scope (per plan §"Schema Reality + Verification Scope Amendment",
 * Amendment 2 OUT-list — strictly enforced):
 *   - NO element rename            (no <basicblock>↔<block>)
 *   - NO structure flatten         (no <ast>/<varnodes> reorder)
 *   - NO op-code translation       (no CPUI_xxx → AURA IrOpcode)
 *   - NO schema validation         (well-formed parse belongs downstream)
 *   - NO semantic correctness      (defer to D-29B+)
 *
 * Idempotent: aura_ghidra_xml_normalize(out) == out (byte-exact fixed
 * point for any AURA_XMLN_OK output).
 *
 * Copyright 2026 AURA Project Contributors
 * SPDX-License-Identifier: Apache-2.0
 */
#include "ghidra_xml_normalize.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define AURA_XML_PROLOG     "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
#define AURA_XML_PROLOG_LEN (sizeof AURA_XML_PROLOG - 1)

/* Skip leading ASCII whitespace (space / tab / LF / CR). Returns the
 * offset to the first non-whitespace byte, or `len` if none. */
static size_t skip_ws(const char *s, size_t len)
{
    size_t i = 0;
    while (i < len) {
        char c = s[i];
        if (c != ' ' && c != '\t' && c != '\n' && c != '\r') break;
        ++i;
    }
    return i;
}

/* Case-insensitive ASCII prefix match. */
static int starts_with_ci(const char *s, size_t s_len, const char *needle)
{
    size_t n = strlen(needle);
    if (s_len < n) return 0;
    for (size_t i = 0; i < n; ++i) {
        char a = s[i];
        char b = needle[i];
        if (a >= 'A' && a <= 'Z') a = (char)(a - 'A' + 'a');
        if (b >= 'A' && b <= 'Z') b = (char)(b - 'A' + 'a');
        if (a != b) return 0;
    }
    return 1;
}

/* Determine if the head (first non-ws region) is a known-bad shape. */
static int is_known_bad(const char *body, size_t body_len)
{
    /* Must start with '<' to be XML at all. */
    if (body_len == 0 || body[0] != '<') return 1;

    /* Reject HTML doctype / html root. We do NOT reject <?xml because the
     * prolog itself is valid and is handled by the caller. */
    if (starts_with_ci(body, body_len, "<!doctype html")) return 1;
    if (starts_with_ci(body, body_len, "<html"))           return 1;
    return 0;
}

void aura_ghidra_xml_normalize_result_free(AuraXmlNormalizeResult *result)
{
    if (!result) return;
    free(result->xml);
    result->xml = NULL;
    result->xml_len = 0;
}

AuraXmlNormalizeStatus aura_ghidra_xml_normalize(
    const char *raw,
    size_t raw_len,
    AuraXmlNormalizeResult *result)
{
    if (!result) return AURA_XMLN_ERR_OOM;
    memset(result, 0, sizeof *result);

    if (!raw || raw_len == 0) {
        result->status = AURA_XMLN_ERR_EMPTY;
        return AURA_XMLN_ERR_EMPTY;
    }

    /* (1) BOM strip. */
    size_t off = 0;
    if (raw_len >= 3 &&
        (unsigned char)raw[0] == 0xEF &&
        (unsigned char)raw[1] == 0xBB &&
        (unsigned char)raw[2] == 0xBF) {
        off = 3;
    }

    const char *src = raw + off;
    size_t      src_len = raw_len - off;

    /* (3) Empty / whitespace-only check (after BOM strip). */
    size_t ws = skip_ws(src, src_len);
    if (ws == src_len) {
        result->status = AURA_XMLN_ERR_EMPTY;
        return AURA_XMLN_ERR_EMPTY;
    }

    /* (4) Known-bad prefix gate. */
    if (is_known_bad(src + ws, src_len - ws)) {
        result->status = AURA_XMLN_ERR_BAD;
        return AURA_XMLN_ERR_BAD;
    }

    /* (5) Decide whether to prepend a prolog. We look at the first non-ws
     * region (so leading whitespace / blank lines do not hide an existing
     * "<?xml" prolog). */
    int has_prolog = 0;
    if (src_len - ws >= 5 && memcmp(src + ws, "<?xml", 5) == 0) {
        has_prolog = 1;
    }

    /* (2) Line-ending normalize: pre-allocate a buffer of (prolog? +
     * src_len + 1). CRLF→LF only shrinks; lone \r→\n is in-place. */
    size_t cap = src_len + 1 + (has_prolog ? 0 : AURA_XML_PROLOG_LEN);
    char *out = (char *)malloc(cap);
    if (!out) {
        result->status = AURA_XMLN_ERR_OOM;
        return AURA_XMLN_ERR_OOM;
    }

    size_t w = 0;
    if (!has_prolog) {
        memcpy(out + w, AURA_XML_PROLOG, AURA_XML_PROLOG_LEN);
        w += AURA_XML_PROLOG_LEN;
    }

    for (size_t i = 0; i < src_len; ++i) {
        char c = src[i];
        if (c == '\r') {
            /* \r\n → \n (consume the \n on next iteration); lone \r → \n. */
            out[w++] = '\n';
            if (i + 1 < src_len && src[i + 1] == '\n') ++i;
        } else {
            out[w++] = c;
        }
    }
    out[w] = '\0';

    result->status  = AURA_XMLN_OK;
    result->xml     = out;
    result->xml_len = w;
    return AURA_XMLN_OK;
}
