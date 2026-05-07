// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/*
 * project_binaries.h — Phase 11.3 GUI v1 project binary registry
 *                      (ADR-0035 project-first surface).
 *
 * Per-project SQLite-backed registry of binaries the user has added to a
 * `.aura.db` project file. Coexists with the `overrides` table managed by
 * override_store (same DB file, independent connection / table).
 *
 * Schema (idempotent CREATE TABLE IF NOT EXISTS):
 *   project_binaries(
 *     path             TEXT    NOT NULL,
 *     fingerprint      TEXT    PRIMARY KEY,   -- 64-char hex SHA-256
 *     size             INTEGER NOT NULL,
 *     added_at         INTEGER NOT NULL,      -- unix seconds
 *     last_analyzed_at INTEGER NULL           -- unix seconds, NULL if none
 *   );
 *
 * Backward-compat: CLI does not consult this table. A `.aura.db` produced
 * by either frontend remains readable by the other.
 *
 * Out of scope (deferred):
 *   - Stale-path detection / relocate flow (v2).
 *   - Binary aliases / labels (v2).
 *   - Multi-project federation.
 */

#ifndef AURA_PROJECT_BINARIES_H
#define AURA_PROJECT_BINARIES_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AURA_PROJECT_BINARY_PATH_CAP        1024
#define AURA_PROJECT_BINARY_FINGERPRINT_LEN 64  // hex (32 bytes * 2)

typedef struct AuraProjectBinaryRecord {
    char    path[AURA_PROJECT_BINARY_PATH_CAP];
    char    fingerprint[AURA_PROJECT_BINARY_FINGERPRINT_LEN + 1];  // +NUL
    int64_t size;
    int64_t added_at;
    int64_t last_analyzed_at;  // 0 sentinel = never analyzed
} AuraProjectBinaryRecord;

typedef struct AuraProjectBinaries AuraProjectBinaries;

/*
 * Open or create a project binary registry on top of the given .aura.db
 * file path. Schema is created idempotently.
 *
 *   path == ":memory:"  → transient in-memory DB (used by tests).
 *   path == "<file>"    → on-disk DB, created if absent.
 *
 * Returns NULL on failure (NULL path, sqlite open fail, schema/prepare
 * failure).
 */
AuraProjectBinaries *aura_project_binaries_open(const char *path);

/*
 * Close the registry. NULL-safe.
 */
void aura_project_binaries_close(AuraProjectBinaries *pb);

/*
 * Insert or replace a row keyed by `fingerprint`. `added_at` is preserved
 * across replaces (existing row's value retained); `path`, `size`, and
 * `last_analyzed_at` are overwritten with the supplied values.
 *
 * Returns 0 on success, -1 on failure.
 */
int aura_project_binaries_put(AuraProjectBinaries           *pb,
                              const AuraProjectBinaryRecord *rec);

/*
 * Fill `out` (up to `capacity` rows) with all registered binaries,
 * ordered by added_at ASC. Returns the number of rows written, or -1
 * on error. If the table contains more rows than `capacity`, only the
 * first `capacity` rows (by added_at) are written.
 */
int aura_project_binaries_list(AuraProjectBinaries     *pb,
                               AuraProjectBinaryRecord *out,
                               int                      capacity);

/*
 * Total row count. Returns -1 on error.
 */
int aura_project_binaries_count(AuraProjectBinaries *pb);

/*
 * Update last_analyzed_at for the row keyed by hex fingerprint.
 * Returns 0 if updated, 1 if no row matched, -1 on error.
 */
int aura_project_binaries_mark_analyzed(AuraProjectBinaries *pb,
                                        const char          *fingerprint_hex,
                                        int64_t              when_unix);

/*
 * Delete row by hex fingerprint. Returns 0 if deleted, 1 if no match,
 * -1 on error.
 */
int aura_project_binaries_remove(AuraProjectBinaries *pb,
                                 const char          *fingerprint_hex);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* AURA_PROJECT_BINARIES_H */
