// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0
//
// make_sig.c — one-shot generator for x86_64_libc_common.sig.
//
// Reads `third_party/sigdb/x86_64_libc_common.pat` and emits the binary
// AURA-flat-v10 blob at `third_party/sigdb/x86_64_libc_common.sig` using
// the schema documented in src/core/flirt_ida.c.
//
// To regenerate:
//   cc third_party/sigdb/make_sig.c -o /tmp/make_sig && \
//   cd /path/to/repo && /tmp/make_sig
//
// This tool is committed for reproducibility but is NOT part of the
// main build — tests read the already-serialised `.sig` blob.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PAT_BYTES 32
#define MAX_NAME  128

typedef struct {
    uint8_t  pattern[PAT_BYTES];
    uint8_t  mask[PAT_BYTES];
    uint16_t crc_len;
    uint16_t crc16;
    uint16_t func_len;
    char     name[MAX_NAME];
    uint16_t name_len;
} Sig;

static int hex_nibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int parse_hex_u16(const char *s, int width, uint16_t *out) {
    uint32_t v = 0;
    for (int i = 0; i < width; i++) {
        int n = hex_nibble(s[i]);
        if (n < 0) return 0;
        v = (v << 4) | (uint32_t)n;
    }
    *out = (uint16_t)v;
    return 1;
}

static int parse_line(const char *line, Sig *s) {
    memset(s, 0, sizeof(*s));
    if (strlen(line) < 64 + 14) return 0;

    for (int i = 0; i < PAT_BYTES; i++) {
        char h = line[2*i], l = line[2*i+1];
        if (h == '.' || l == '.') { s->pattern[i] = 0; s->mask[i] = 1; continue; }
        int hi = hex_nibble(h), lo = hex_nibble(l);
        if (hi < 0 || lo < 0) return 0;
        s->pattern[i] = (uint8_t)((hi << 4) | lo);
        s->mask[i] = 0;
    }
    const char *c = line + 64;
    if (*c++ != ' ') return 0;
    if (!parse_hex_u16(c, 2, &s->crc_len))  return 0; c += 2;
    if (*c++ != ' ') return 0;
    if (!parse_hex_u16(c, 4, &s->crc16))    return 0; c += 4;
    if (*c++ != ' ') return 0;
    if (!parse_hex_u16(c, 4, &s->func_len)) return 0; c += 4;
    if (*c++ != ' ') return 0;
    if (*c++ != ':') return 0;
    uint16_t off;
    if (!parse_hex_u16(c, 4, &off)) return 0; c += 4;
    if (*c++ != ' ') return 0;

    int ni = 0;
    while (*c && *c != ' ' && *c != '\n' && *c != '\r' && ni + 1 < MAX_NAME) {
        s->name[ni++] = *c++;
    }
    s->name[ni] = '\0';
    s->name_len = (uint16_t)ni;
    return (ni > 0);
}

static void put_u16(FILE *f, uint16_t v) {
    uint8_t b[2] = { (uint8_t)(v & 0xFF), (uint8_t)((v >> 8) & 0xFF) };
    fwrite(b, 1, 2, f);
}
static void put_u32(FILE *f, uint32_t v) {
    uint8_t b[4] = { (uint8_t)(v & 0xFF), (uint8_t)((v >> 8) & 0xFF),
                     (uint8_t)((v >> 16) & 0xFF), (uint8_t)((v >> 24) & 0xFF) };
    fwrite(b, 1, 4, f);
}

int main(void) {
    const char *in  = "third_party/sigdb/x86_64_libc_common.pat";
    const char *out = "third_party/sigdb/x86_64_libc_common.sig";

    FILE *fp = fopen(in, "r");
    if (!fp) { perror(in); return 1; }

    Sig sigs[256];
    uint32_t n = 0;
    char line[4096];
    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '-' && line[1] == '-' && line[2] == '-') break;
        if (line[0] == '\0' || line[0] == '\n' || line[0] == ';' || line[0] == '#') continue;
        if (parse_line(line, &sigs[n])) n++;
    }
    fclose(fp);

    FILE *w = fopen(out, "wb");
    if (!w) { perror(out); return 1; }
    fwrite("IDASGN10", 1, 8, w);
    put_u32(w, 10);
    put_u32(w, n);
    for (uint32_t i = 0; i < n; i++) {
        fwrite(sigs[i].pattern, 1, PAT_BYTES, w);
        fwrite(sigs[i].mask,    1, PAT_BYTES, w);
        put_u16(w, sigs[i].crc_len);
        put_u16(w, sigs[i].crc16);
        put_u16(w, sigs[i].func_len);
        put_u16(w, sigs[i].name_len);
        fwrite(sigs[i].name, 1, sigs[i].name_len, w);
    }
    fclose(w);

    printf("wrote %u sigs to %s\n", n, out);
    return 0;
}
