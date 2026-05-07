// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * aura_io.h — AuraStrBuf: portable memory-backed text buffer.
 *
 * Replaces POSIX `open_memstream()` for AURA's emit paths (decompiled
 * pseudocode, diagnostics, LLM streaming responses). Pure-malloc, OS-
 * independent, zero-dependency. Decided 2026-05-03 (Phase 9 issue 01,
 * design grilling Q1~Q9).
 *
 * USAGE
 * -----
 *
 *     AuraStrBuf sb = AURA_STRBUF_INIT;
 *     aura_strbuf_printf(&sb, "void %s(", name);
 *     aura_strbuf_printf(&sb, "int %s) { ... }", arg);
 *
 *     size_t len;
 *     char  *out = aura_strbuf_detach(&sb, &len);
 *     if (!out) { return -ENOMEM; }      // sticky err caught at end
 *     // out is now caller-owned; sb is reset and may be reused or freed.
 *     ...
 *     free(out);
 *     aura_strbuf_free(&sb);             // safe (no-op when reset)
 *
 * ERROR MODEL — STICKY
 * --------------------
 * If allocation fails (or NULL inputs), `err` is set to -1 and ALL
 * subsequent operations on the same instance silently no-op. Callers
 * check at the end (`detach()` returns NULL, or `aura_strbuf_status()`).
 * This keeps long emit chains free of per-call error checks.
 *
 * MEMORY GROWTH
 * -------------
 * Lazy: nothing allocated by AURA_STRBUF_INIT or aura_strbuf_init().
 * First write triggers a 256-byte malloc; subsequent growth doubles cap
 * (amortized O(1) append). aura_strbuf_init_capacity() lets callers
 * pre-size to avoid early reallocs. detach() shrinks to len+1.
 *
 * THREAD SAFETY
 * -------------
 * AuraStrBuf is NOT thread-safe at instance level. Multiple threads MUST
 * NOT operate on the same AuraStrBuf concurrently.
 *
 * SAFE multi-thread patterns:
 *   1. Per-thread instances — each thread owns its own AuraStrBuf.
 *   2. Hand-off — one thread builds, calls detach() to extract a plain
 *      char*, then transfers OWNERSHIP of that char* to another thread
 *      (Qt signal/slot, channel, etc.). The originating AuraStrBuf is
 *      reused or freed by its original thread only.
 *
 * UNSAFE patterns:
 *   - Two threads writing to the same AuraStrBuf instance.
 *   - One thread writing while another reads `sb->data` directly.
 *
 * If shared mutable buffer is required (Phase 9+ future), opt into a
 * separate AuraStrBufTs type with internal locking — not provided yet.
 *
 * RAII (C++)
 * ----------
 * `aura::StrBuf` (below) wraps the C struct with destructor-driven free,
 * deleted copy, and move semantics. Use it from C++ callsites for
 * exception safety; the C API is fine for plain C code.
 */

#pragma once

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AuraStrBuf {
    char  *data;        /* heap buffer; NULL when empty / freshly init'd */
    size_t len;         /* used bytes (excluding null terminator)        */
    size_t cap;         /* allocated capacity (>= len + 1 when data != NULL) */
    int    err;         /* 0 = ok; -1 = OOM (sticky)                     */
} AuraStrBuf;

#define AURA_STRBUF_INIT  { NULL, 0, 0, 0 }

/* Initialize to fresh/empty state. Equivalent to assigning AURA_STRBUF_INIT. */
void  aura_strbuf_init           (AuraStrBuf *sb);

/* Initialize and pre-allocate `initial_cap` bytes (excluding null terminator).
 * Useful when the expected output size is known to avoid early reallocs.
 * If allocation fails, sb->err is set; subsequent ops will no-op. */
void  aura_strbuf_init_capacity  (AuraStrBuf *sb, size_t initial_cap);

/* Append formatted text. Sticky on OOM or NULL inputs. */
void  aura_strbuf_printf         (AuraStrBuf *sb, const char *fmt, ...);

/* va_list variant of aura_strbuf_printf. */
void  aura_strbuf_vprintf        (AuraStrBuf *sb, const char *fmt, va_list ap);

/* Append `n` raw bytes (binary-safe). Sticky on OOM or NULL inputs. */
void  aura_strbuf_append         (AuraStrBuf *sb, const char *data, size_t n);

/* Transfer ownership of the buffer to caller. Returns a NUL-terminated
 * malloc'd char* (must be free()'d by caller); shrinks to exactly len+1.
 * Sets *out_len if non-NULL. Returns NULL when sb is empty or in err state.
 * After detach, sb is reset to fresh state and may be reused or freed. */
char *aura_strbuf_detach         (AuraStrBuf *sb, size_t *out_len);

/* Free internal buffer and reset to fresh state. Safe to call multiple
 * times, on a freshly-init'd sb, or after detach (all no-ops). */
void  aura_strbuf_free           (AuraStrBuf *sb);

/* Return sticky error status: 0 = ok, -1 = OOM (or other failure). */
int   aura_strbuf_status         (const AuraStrBuf *sb);

/* Emit-to-FILE callback used by aura_strbuf_capture_emit(). The thunk
 * receives the caller's opaque ctx and a writable temporary FILE*.
 * Return AURA_OK on success or any error code; non-OK aborts capture. */
typedef int (*AuraEmitFileFn)(void *ctx, FILE *out);

/* Capture the bytes a FILE*-only emit function would have written into
 * a caller-owned AuraStrBuf. Backed by tmpfile() + fread + append, so
 * portable to MSVC where open_memstream/fmemopen are unavailable.
 *
 * Used by *_with_strbuf adapters (see Phase 9 issues 03a/03b) to give
 * tests an AuraStrBuf-shaped surface without touching the FILE*-based
 * emit core.
 *
 * Returns: AURA_OK, the emit fn's error code, AURA_ERR_INVALID_ARG,
 *          AURA_ERR_IO (tmpfile / fwrite path), or AURA_ERR_NOMEM. */
int   aura_strbuf_capture_emit   (AuraEmitFileFn fn, void *ctx,
                                  AuraStrBuf *out);

#ifdef __cplusplus
}  /* extern "C" */

namespace aura {

/* RAII wrapper for AuraStrBuf — exception-safe C++ usage. */
class StrBuf {
    AuraStrBuf sb_;
public:
    StrBuf() noexcept                                : sb_{ nullptr, 0, 0, 0 } {}
    explicit StrBuf(size_t initial_cap) noexcept     : sb_{ nullptr, 0, 0, 0 } {
        aura_strbuf_init_capacity(&sb_, initial_cap);
    }
    ~StrBuf() noexcept                               { aura_strbuf_free(&sb_); }

    StrBuf(const StrBuf &)            = delete;
    StrBuf &operator=(const StrBuf &) = delete;

    StrBuf(StrBuf &&other) noexcept                  : sb_(other.sb_) {
        other.sb_ = AuraStrBuf{ nullptr, 0, 0, 0 };
    }
    StrBuf &operator=(StrBuf &&other) noexcept {
        if (this != &other) {
            aura_strbuf_free(&sb_);
            sb_ = other.sb_;
            other.sb_ = AuraStrBuf{ nullptr, 0, 0, 0 };
        }
        return *this;
    }

    void printf(const char *fmt, ...) noexcept {
        va_list ap;
        va_start(ap, fmt);
        aura_strbuf_vprintf(&sb_, fmt, ap);
        va_end(ap);
    }

    void  append(const char *d, size_t n) noexcept   { aura_strbuf_append(&sb_, d, n); }
    char *detach(size_t *out_len = nullptr) noexcept { return aura_strbuf_detach(&sb_, out_len); }
    int   status() const noexcept                    { return aura_strbuf_status(&sb_); }

    AuraStrBuf       *raw()       noexcept           { return &sb_; }
    const AuraStrBuf *raw() const noexcept           { return &sb_; }
};

}  /* namespace aura */
#endif  /* __cplusplus */
