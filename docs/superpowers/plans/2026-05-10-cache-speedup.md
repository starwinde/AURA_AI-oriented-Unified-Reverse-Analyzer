# Cache Speedup Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a project-local persistent artifact cache so AURA reuses decompile, function disassembly, and full-disassembly window results instead of repeatedly calling Rizin for the same binary/function/window.

**Architecture:** Add a small SQLite-backed `AuraArtifactCache` to `aura_core`, keyed by binary fingerprint, engine identity, request type, artifact kind, schema version, and address/window options. `MainWindow` keeps the current in-memory pane caches, but checks the project DB before dispatching Rizin and stores successful engine outputs after a miss.

**Tech Stack:** C/C++17, SQLite via bundled `sqlite3`, cJSON, Qt6 GUI, doctest, CMake/MSVC, existing `aura_core` and `gui_smoke` targets.

---

## Scope

This plan implements a read-through artifact cache for GUI speed. It does not add persistent Rizin sessions, r2pipe, whole-analysis body caching, MCP raw access, or LLM response caching.

## File Structure

- Create `include/artifact_cache.h`
  - Public C API for opening the project DB artifact cache, building keys, and putting/getting JSON payloads.
- Create `src/core/artifact_cache.c`
  - SQLite schema, prepared statements, key validation, and payload copy ownership.
- Modify `CMakeLists.txt`
  - Add `src/core/artifact_cache.c` to `AURA_CORE_SOURCES`.
  - Add `tests/unit/artifact_cache` to the test tree.
- Create `tests/unit/artifact_cache/CMakeLists.txt`
  - Build `artifact_cache_unit` against `aura_core`, `sqlite3`, `cjson`, and doctest.
- Create `tests/unit/artifact_cache/artifact_cache_unit.cpp`
  - Unit tests for schema creation, exact key hit/miss behavior, replacement, and timestamp preservation.
- Modify `src/gui/main_window.h`
  - Add an `AuraArtifactCache*` member and small helpers for cache keys/payload conversion.
- Modify `src/gui/main_window.cpp`
  - Open/close artifact cache with the project DB.
  - Add read-through cache for `runDecompile()`, batch decompile, `runDisasm()`, and `runFullDisasmWindow()`.
- Modify `tests/integration/gui_smoke/gui_smoke.cpp`
  - Add reopen/reuse tests for decompile, function disassembly, and full-disassembly window cache.

---

### Task 1: Add Artifact Cache Core API

**Files:**
- Create: `include/artifact_cache.h`
- Create: `src/core/artifact_cache.c`
- Modify: `CMakeLists.txt`
- Test: `tests/unit/artifact_cache/artifact_cache_unit.cpp`
- Test: `tests/unit/artifact_cache/CMakeLists.txt`

- [ ] **Step 1: Write the failing unit test**

Create `tests/unit/artifact_cache/artifact_cache_unit.cpp`:

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "artifact_cache.h"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>

namespace {

std::filesystem::path tempDbPath(const char* name) {
    const auto root = std::filesystem::temp_directory_path() /
        (std::string(name) + "_" + std::to_string(std::rand()));
    std::filesystem::remove(root);
    return root;
}

AuraArtifactCacheKey baseKey() {
    AuraArtifactCacheKey key{};
    std::snprintf(key.binary_fingerprint, sizeof(key.binary_fingerprint),
                  "%064d", 1);
    std::snprintf(key.engine_id, sizeof(key.engine_id), "rizin");
    std::snprintf(key.engine_version, sizeof(key.engine_version), "0.8.0");
    key.request_type = 2;  // AURA_ENGINE_REQ_DECOMPILE, kept numeric to avoid header coupling.
    std::snprintf(key.artifact_kind, sizeof(key.artifact_kind),
                  "decompile.function");
    std::snprintf(key.backend, sizeof(key.backend), "rizin/pdgj");
    key.schema_version = 1;
    key.function_addr = 0x401000;
    key.window_addr = 0;
    key.window_count = 0;
    std::snprintf(key.options_hash, sizeof(key.options_hash), "default");
    return key;
}

}  // namespace

TEST_CASE("artifact cache stores and retrieves exact key payload") {
    const auto db = tempDbPath("aura_artifact_cache_exact");
    AuraArtifactCache* cache = aura_artifact_cache_open(db.string().c_str());
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    REQUIRE(aura_artifact_cache_put(cache, &key,
                                    "{\"text\":\"int main(){}\"}") == 0);

    char* payload = nullptr;
    REQUIRE(aura_artifact_cache_get(cache, &key, &payload) == 1);
    REQUIRE(payload != nullptr);
    CHECK(std::string(payload) == "{\"text\":\"int main(){}\"}");
    aura_artifact_cache_free_payload(payload);
    aura_artifact_cache_close(cache);
    std::filesystem::remove(db);
}

TEST_CASE("artifact cache misses on engine version and schema version drift") {
    const auto db = tempDbPath("aura_artifact_cache_miss");
    AuraArtifactCache* cache = aura_artifact_cache_open(db.string().c_str());
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"ok\":true}") == 0);

    AuraArtifactCacheKey changedEngine = key;
    std::snprintf(changedEngine.engine_version,
                  sizeof(changedEngine.engine_version), "0.9.0");
    char* payload = nullptr;
    CHECK(aura_artifact_cache_get(cache, &changedEngine, &payload) == 0);
    CHECK(payload == nullptr);

    AuraArtifactCacheKey changedSchema = key;
    changedSchema.schema_version = 2;
    CHECK(aura_artifact_cache_get(cache, &changedSchema, &payload) == 0);
    CHECK(payload == nullptr);

    aura_artifact_cache_close(cache);
    std::filesystem::remove(db);
}

TEST_CASE("artifact cache replace keeps one latest payload") {
    const auto db = tempDbPath("aura_artifact_cache_replace");
    AuraArtifactCache* cache = aura_artifact_cache_open(db.string().c_str());
    REQUIRE(cache != nullptr);

    AuraArtifactCacheKey key = baseKey();
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"rev\":1}") == 0);
    REQUIRE(aura_artifact_cache_put(cache, &key, "{\"rev\":2}") == 0);

    char* payload = nullptr;
    REQUIRE(aura_artifact_cache_get(cache, &key, &payload) == 1);
    REQUIRE(payload != nullptr);
    CHECK(std::string(payload) == "{\"rev\":2}");
    aura_artifact_cache_free_payload(payload);

    aura_artifact_cache_close(cache);
    std::filesystem::remove(db);
}

TEST_CASE("artifact cache rejects incomplete keys") {
    AuraArtifactCacheKey key = baseKey();
    key.binary_fingerprint[0] = '\0';

    AuraArtifactCache* cache = aura_artifact_cache_open(":memory:");
    REQUIRE(cache != nullptr);
    CHECK(aura_artifact_cache_put(cache, &key, "{\"bad\":true}") == -1);

    char* payload = nullptr;
    CHECK(aura_artifact_cache_get(cache, &key, &payload) == -1);
    CHECK(payload == nullptr);
    aura_artifact_cache_close(cache);
}
```

- [ ] **Step 2: Add the test CMake file**

Create `tests/unit/artifact_cache/CMakeLists.txt`:

```cmake
add_executable(artifact_cache_unit artifact_cache_unit.cpp)
target_include_directories(artifact_cache_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(artifact_cache_unit PRIVATE aura_core sqlite3)
target_compile_features(artifact_cache_unit PRIVATE cxx_std_17)

add_test(NAME artifact_cache_unit COMMAND artifact_cache_unit)
set_tests_properties(artifact_cache_unit PROPERTIES
    LABELS "unit;cache"
    TIMEOUT 30
)
```

- [ ] **Step 3: Wire the test into root CMake**

Modify the `if(AURA_BUILD_TESTS)` block in `CMakeLists.txt` by adding this line after `add_subdirectory(tests/unit/mcp)`:

```cmake
    add_subdirectory(tests/unit/artifact_cache)
```

- [ ] **Step 4: Run the new test and verify it fails to compile**

Run:

```powershell
cmake --build build-trim-gui --config Release --target artifact_cache_unit
```

Expected: build fails because `artifact_cache.h` and `src/core/artifact_cache.c` do not exist yet.

- [ ] **Step 5: Add the public header**

Create `include/artifact_cache.h`:

```c
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#ifndef AURA_ARTIFACT_CACHE_H
#define AURA_ARTIFACT_CACHE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AURA_ARTIFACT_CACHE_FINGERPRINT_CAP 65
#define AURA_ARTIFACT_CACHE_ENGINE_ID_CAP 32
#define AURA_ARTIFACT_CACHE_ENGINE_VERSION_CAP 64
#define AURA_ARTIFACT_CACHE_KIND_CAP 64
#define AURA_ARTIFACT_CACHE_BACKEND_CAP 64
#define AURA_ARTIFACT_CACHE_OPTIONS_HASH_CAP 65

typedef struct AuraArtifactCache AuraArtifactCache;

typedef struct AuraArtifactCacheKey {
    char     binary_fingerprint[AURA_ARTIFACT_CACHE_FINGERPRINT_CAP];
    char     engine_id[AURA_ARTIFACT_CACHE_ENGINE_ID_CAP];
    char     engine_version[AURA_ARTIFACT_CACHE_ENGINE_VERSION_CAP];
    int      request_type;
    char     artifact_kind[AURA_ARTIFACT_CACHE_KIND_CAP];
    char     backend[AURA_ARTIFACT_CACHE_BACKEND_CAP];
    int      schema_version;
    uint64_t function_addr;
    uint64_t window_addr;
    int      window_count;
    char     options_hash[AURA_ARTIFACT_CACHE_OPTIONS_HASH_CAP];
} AuraArtifactCacheKey;

AuraArtifactCache* aura_artifact_cache_open(const char* db_path);
void aura_artifact_cache_close(AuraArtifactCache* cache);

int aura_artifact_cache_put(AuraArtifactCache* cache,
                            const AuraArtifactCacheKey* key,
                            const char* payload_json);

/* Returns 1 for hit, 0 for miss, -1 for error.
 * On hit, *out_payload_json is heap-allocated and must be freed with
 * aura_artifact_cache_free_payload().
 */
int aura_artifact_cache_get(AuraArtifactCache* cache,
                            const AuraArtifactCacheKey* key,
                            char** out_payload_json);

void aura_artifact_cache_free_payload(char* payload_json);

#ifdef __cplusplus
}
#endif

#endif /* AURA_ARTIFACT_CACHE_H */
```

- [ ] **Step 6: Add the SQLite implementation**

Create `src/core/artifact_cache.c`:

```c
// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

#include "artifact_cache.h"

#include <stdlib.h>
#include <string.h>

#include "sqlite3.h"

static const char* kSchema =
    "CREATE TABLE IF NOT EXISTS analysis_artifacts ("
    "  binary_fingerprint TEXT NOT NULL,"
    "  engine_id TEXT NOT NULL,"
    "  engine_version TEXT NOT NULL DEFAULT '',"
    "  request_type INTEGER NOT NULL,"
    "  artifact_kind TEXT NOT NULL,"
    "  backend TEXT NOT NULL DEFAULT '',"
    "  schema_version INTEGER NOT NULL,"
    "  function_addr INTEGER NOT NULL DEFAULT 0,"
    "  window_addr INTEGER NOT NULL DEFAULT 0,"
    "  window_count INTEGER NOT NULL DEFAULT 0,"
    "  options_hash TEXT NOT NULL DEFAULT '',"
    "  payload_json TEXT NOT NULL,"
    "  created_at TEXT NOT NULL DEFAULT (datetime('now')),"
    "  updated_at TEXT NOT NULL DEFAULT (datetime('now')),"
    "  PRIMARY KEY ("
    "    binary_fingerprint, engine_id, engine_version, request_type,"
    "    artifact_kind, backend, schema_version, function_addr,"
    "    window_addr, window_count, options_hash"
    "  )"
    ");";

static const char* kPutSql =
    "INSERT OR REPLACE INTO analysis_artifacts ("
    "  binary_fingerprint, engine_id, engine_version, request_type,"
    "  artifact_kind, backend, schema_version, function_addr,"
    "  window_addr, window_count, options_hash, payload_json,"
    "  created_at, updated_at"
    ") VALUES ("
    "  ?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11, ?12,"
    "  COALESCE(("
    "    SELECT created_at FROM analysis_artifacts"
    "     WHERE binary_fingerprint = ?1"
    "       AND engine_id = ?2"
    "       AND engine_version = ?3"
    "       AND request_type = ?4"
    "       AND artifact_kind = ?5"
    "       AND backend = ?6"
    "       AND schema_version = ?7"
    "       AND function_addr = ?8"
    "       AND window_addr = ?9"
    "       AND window_count = ?10"
    "       AND options_hash = ?11"
    "  ), datetime('now')),"
    "  datetime('now')"
    ");";

static const char* kGetSql =
    "SELECT payload_json FROM analysis_artifacts"
    " WHERE binary_fingerprint = ?1"
    "   AND engine_id = ?2"
    "   AND engine_version = ?3"
    "   AND request_type = ?4"
    "   AND artifact_kind = ?5"
    "   AND backend = ?6"
    "   AND schema_version = ?7"
    "   AND function_addr = ?8"
    "   AND window_addr = ?9"
    "   AND window_count = ?10"
    "   AND options_hash = ?11;";

struct AuraArtifactCache {
    sqlite3* db;
    sqlite3_stmt* put_stmt;
    sqlite3_stmt* get_stmt;
};

static int has_text(const char* s) {
    return s != NULL && s[0] != '\0';
}

static int key_valid(const AuraArtifactCacheKey* key) {
    return key != NULL &&
           has_text(key->binary_fingerprint) &&
           has_text(key->engine_id) &&
           has_text(key->artifact_kind) &&
           key->request_type >= 0 &&
           key->schema_version > 0;
}

static int bind_key(sqlite3_stmt* st, const AuraArtifactCacheKey* key) {
    int rc = SQLITE_OK;
    rc = sqlite3_bind_text(st, 1, key->binary_fingerprint, -1,
                           SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 2, key->engine_id, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 3, key->engine_version, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int(st, 4, key->request_type);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 5, key->artifact_kind, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 6, key->backend, -1, SQLITE_TRANSIENT);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int(st, 7, key->schema_version);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 8, (sqlite3_int64)key->function_addr);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int64(st, 9, (sqlite3_int64)key->window_addr);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_int(st, 10, key->window_count);
    if (rc != SQLITE_OK) return -1;
    rc = sqlite3_bind_text(st, 11, key->options_hash, -1, SQLITE_TRANSIENT);
    return rc == SQLITE_OK ? 0 : -1;
}

AuraArtifactCache* aura_artifact_cache_open(const char* db_path) {
    if (!db_path) return NULL;

    AuraArtifactCache* cache =
        (AuraArtifactCache*)calloc(1, sizeof(*cache));
    if (!cache) return NULL;

    if (sqlite3_open(db_path, &cache->db) != SQLITE_OK) {
        aura_artifact_cache_close(cache);
        return NULL;
    }

    sqlite3_exec(cache->db, "PRAGMA journal_mode=WAL;", NULL, NULL, NULL);
    sqlite3_busy_timeout(cache->db, 5000);

    if (sqlite3_exec(cache->db, kSchema, NULL, NULL, NULL) != SQLITE_OK)
        goto fail;
    if (sqlite3_prepare_v2(cache->db, kPutSql, -1, &cache->put_stmt, NULL) !=
        SQLITE_OK)
        goto fail;
    if (sqlite3_prepare_v2(cache->db, kGetSql, -1, &cache->get_stmt, NULL) !=
        SQLITE_OK)
        goto fail;

    return cache;

fail:
    aura_artifact_cache_close(cache);
    return NULL;
}

void aura_artifact_cache_close(AuraArtifactCache* cache) {
    if (!cache) return;
    if (cache->put_stmt) sqlite3_finalize(cache->put_stmt);
    if (cache->get_stmt) sqlite3_finalize(cache->get_stmt);
    if (cache->db) sqlite3_close(cache->db);
    free(cache);
}

int aura_artifact_cache_put(AuraArtifactCache* cache,
                            const AuraArtifactCacheKey* key,
                            const char* payload_json) {
    if (!cache || !key_valid(key) || !has_text(payload_json)) return -1;

    sqlite3_stmt* st = cache->put_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_key(st, key) != 0) return -1;
    if (sqlite3_bind_text(st, 12, payload_json, -1, SQLITE_TRANSIENT) !=
        SQLITE_OK)
        return -1;

    return sqlite3_step(st) == SQLITE_DONE ? 0 : -1;
}

int aura_artifact_cache_get(AuraArtifactCache* cache,
                            const AuraArtifactCacheKey* key,
                            char** out_payload_json) {
    if (out_payload_json) *out_payload_json = NULL;
    if (!cache || !key_valid(key) || !out_payload_json) return -1;

    sqlite3_stmt* st = cache->get_stmt;
    sqlite3_reset(st);
    sqlite3_clear_bindings(st);

    if (bind_key(st, key) != 0) return -1;

    const int rc = sqlite3_step(st);
    if (rc == SQLITE_DONE) return 0;
    if (rc != SQLITE_ROW) return -1;

    const unsigned char* text = sqlite3_column_text(st, 0);
    if (!text) return -1;
    const size_t len = strlen((const char*)text);
    char* copy = (char*)malloc(len + 1u);
    if (!copy) return -1;
    memcpy(copy, text, len + 1u);
    *out_payload_json = copy;
    return 1;
}

void aura_artifact_cache_free_payload(char* payload_json) {
    free(payload_json);
}
```

- [ ] **Step 7: Add the implementation to `aura_core`**

Modify `CMakeLists.txt` inside `set(AURA_CORE_SOURCES ...)`, after `src/core/project_binaries.c`:

```cmake
    src/core/artifact_cache.c
```

- [ ] **Step 8: Run the unit test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target artifact_cache_unit
ctest --test-dir build-trim-gui -C Release -R artifact_cache_unit --output-on-failure
```

Expected: `artifact_cache_unit` passes.

- [ ] **Step 9: Commit Task 1**

Run:

```powershell
git add include/artifact_cache.h src/core/artifact_cache.c CMakeLists.txt tests/unit/artifact_cache
git commit -m "feat: add project artifact cache"
```

Expected: commit succeeds with only artifact-cache core and tests.

---

### Task 2: Add JSON Conversion Helpers for GUI Artifacts

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write failing GUI helper tests**

Add this subcase near the pure helper tests in `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
SUBCASE("artifact payload helpers round-trip disasm and decompile JSON") {
    using aura::gui::GuiInstructionRecord;
    using aura::gui::MainWindow;
    using aura::gui::DecompileLineAddrMap;

    QVector<GuiInstructionRecord> ins;
    GuiInstructionRecord r;
    r.addr = 0x401000;
    r.size = 5;
    r.bytes = QStringLiteral("554889e5");
    r.mnemonic = QStringLiteral("push");
    r.opStr = QStringLiteral("rbp");
    r.type = QStringLiteral("push");
    r.jump = 0;
    r.fail = 0;
    r.source = QStringLiteral("rizin");
    ins.push_back(r);

    const QString disasmJson =
        MainWindow::artifactPayloadForDisasm(ins, QStringLiteral("arrow text"));
    QVector<GuiInstructionRecord> decodedIns;
    QString decodedText;
    REQUIRE(MainWindow::parseDisasmArtifactPayload(disasmJson, &decodedIns,
                                                   &decodedText));
    REQUIRE(decodedIns.size() == 1);
    CHECK(decodedIns[0].addr == 0x401000);
    CHECK(decodedIns[0].bytes == QStringLiteral("554889e5"));
    CHECK(decodedText == QStringLiteral("arrow text"));

    DecompileLineAddrMap lm;
    lm.insert(1, 0x401000);
    const QString decompJson =
        MainWindow::artifactPayloadForDecompile(QStringLiteral("body"), lm);
    QString body;
    DecompileLineAddrMap decodedMap;
    REQUIRE(MainWindow::parseDecompileArtifactPayload(decompJson, &body,
                                                      &decodedMap));
    CHECK(body == QStringLiteral("body"));
    CHECK(decodedMap.value(1) == 0x401000);
}
```

- [ ] **Step 2: Run the failing GUI smoke build**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
```

Expected: build fails because the four `MainWindow` static helper methods do not exist.

- [ ] **Step 3: Declare helper methods**

Add these public static declarations to `src/gui/main_window.h` near `formatArrayCandidateRow`:

```cpp
    static QString artifactPayloadForDecompile(
        const QString& text,
        const DecompileLineAddrMap& lineMap);
    static bool parseDecompileArtifactPayload(
        const QString& payload,
        QString* text,
        DecompileLineAddrMap* lineMap);
    static QString artifactPayloadForDisasm(
        const QVector<GuiInstructionRecord>& instructions,
        const QString& text);
    static bool parseDisasmArtifactPayload(
        const QString& payload,
        QVector<GuiInstructionRecord>* instructions,
        QString* text);
```

- [ ] **Step 4: Implement decompile JSON helpers**

Add these includes to `src/gui/main_window.cpp` if they are missing:

```cpp
#include "cJSON.h"
```

Add this implementation near other static helper implementations:

```cpp
QString MainWindow::artifactPayloadForDecompile(
    const QString& text,
    const DecompileLineAddrMap& lineMap) {
    cJSON* root = cJSON_CreateObject();
    cJSON* lines = cJSON_CreateArray();
    if (!root || !lines) {
        cJSON_Delete(root);
        cJSON_Delete(lines);
        return QString();
    }
    cJSON_AddStringToObject(root, "text", text.toUtf8().constData());
    for (auto it = lineMap.constBegin(); it != lineMap.constEnd(); ++it) {
        cJSON* item = cJSON_CreateObject();
        if (!item) continue;
        cJSON_AddNumberToObject(item, "line", it.key());
        cJSON_AddNumberToObject(item, "addr",
                                static_cast<double>(it.value()));
        cJSON_AddItemToArray(lines, item);
    }
    cJSON_AddItemToObject(root, "line_map", lines);
    char* printed = cJSON_PrintUnformatted(root);
    const QString out = printed ? QString::fromUtf8(printed) : QString();
    if (printed) cJSON_free(printed);
    cJSON_Delete(root);
    return out;
}

bool MainWindow::parseDecompileArtifactPayload(
    const QString& payload,
    QString* text,
    DecompileLineAddrMap* lineMap) {
    if (!text || !lineMap) return false;
    cJSON* root = cJSON_Parse(payload.toUtf8().constData());
    if (!root) return false;
    const cJSON* textItem = cJSON_GetObjectItemCaseSensitive(root, "text");
    const cJSON* map = cJSON_GetObjectItemCaseSensitive(root, "line_map");
    if (!cJSON_IsString(textItem) || !cJSON_IsArray(map)) {
        cJSON_Delete(root);
        return false;
    }
    DecompileLineAddrMap decoded;
    const cJSON* item = nullptr;
    cJSON_ArrayForEach(item, map) {
        const cJSON* line = cJSON_GetObjectItemCaseSensitive(item, "line");
        const cJSON* addr = cJSON_GetObjectItemCaseSensitive(item, "addr");
        if (cJSON_IsNumber(line) && cJSON_IsNumber(addr)) {
            decoded.insert(line->valueint,
                           static_cast<quint64>(addr->valuedouble));
        }
    }
    *text = QString::fromUtf8(textItem->valuestring);
    *lineMap = decoded;
    cJSON_Delete(root);
    return true;
}
```

- [ ] **Step 5: Implement disasm JSON helpers**

Add this implementation after the decompile helpers:

```cpp
QString MainWindow::artifactPayloadForDisasm(
    const QVector<GuiInstructionRecord>& instructions,
    const QString& text) {
    cJSON* root = cJSON_CreateObject();
    cJSON* arr = cJSON_CreateArray();
    if (!root || !arr) {
        cJSON_Delete(root);
        cJSON_Delete(arr);
        return QString();
    }
    cJSON_AddStringToObject(root, "text", text.toUtf8().constData());
    for (const auto& r : instructions) {
        cJSON* item = cJSON_CreateObject();
        if (!item) continue;
        cJSON_AddNumberToObject(item, "addr", static_cast<double>(r.addr));
        cJSON_AddNumberToObject(item, "size", static_cast<double>(r.size));
        cJSON_AddStringToObject(item, "bytes", r.bytes.toUtf8().constData());
        cJSON_AddStringToObject(item, "mnemonic",
                                r.mnemonic.toUtf8().constData());
        cJSON_AddStringToObject(item, "op_str", r.opStr.toUtf8().constData());
        cJSON_AddStringToObject(item, "type", r.type.toUtf8().constData());
        cJSON_AddNumberToObject(item, "jump", static_cast<double>(r.jump));
        cJSON_AddNumberToObject(item, "fail", static_cast<double>(r.fail));
        cJSON_AddStringToObject(item, "source",
                                r.source.toUtf8().constData());
        cJSON_AddItemToArray(arr, item);
    }
    cJSON_AddItemToObject(root, "instructions", arr);
    char* printed = cJSON_PrintUnformatted(root);
    const QString out = printed ? QString::fromUtf8(printed) : QString();
    if (printed) cJSON_free(printed);
    cJSON_Delete(root);
    return out;
}

bool MainWindow::parseDisasmArtifactPayload(
    const QString& payload,
    QVector<GuiInstructionRecord>* instructions,
    QString* text) {
    if (!instructions || !text) return false;
    cJSON* root = cJSON_Parse(payload.toUtf8().constData());
    if (!root) return false;
    const cJSON* textItem = cJSON_GetObjectItemCaseSensitive(root, "text");
    const cJSON* arr = cJSON_GetObjectItemCaseSensitive(root, "instructions");
    if (!cJSON_IsString(textItem) || !cJSON_IsArray(arr)) {
        cJSON_Delete(root);
        return false;
    }
    QVector<GuiInstructionRecord> decoded;
    const cJSON* item = nullptr;
    cJSON_ArrayForEach(item, arr) {
        GuiInstructionRecord r;
        const cJSON* addr = cJSON_GetObjectItemCaseSensitive(item, "addr");
        const cJSON* size = cJSON_GetObjectItemCaseSensitive(item, "size");
        const cJSON* bytes = cJSON_GetObjectItemCaseSensitive(item, "bytes");
        const cJSON* mnemonic =
            cJSON_GetObjectItemCaseSensitive(item, "mnemonic");
        const cJSON* opStr = cJSON_GetObjectItemCaseSensitive(item, "op_str");
        const cJSON* type = cJSON_GetObjectItemCaseSensitive(item, "type");
        const cJSON* jump = cJSON_GetObjectItemCaseSensitive(item, "jump");
        const cJSON* fail = cJSON_GetObjectItemCaseSensitive(item, "fail");
        const cJSON* source = cJSON_GetObjectItemCaseSensitive(item, "source");
        if (!cJSON_IsNumber(addr) || !cJSON_IsNumber(size)) {
            cJSON_Delete(root);
            return false;
        }
        r.addr = static_cast<quint64>(addr->valuedouble);
        r.size = static_cast<quint32>(size->valuedouble);
        r.bytes = cJSON_IsString(bytes) ? QString::fromUtf8(bytes->valuestring)
                                        : QString();
        r.mnemonic = cJSON_IsString(mnemonic)
            ? QString::fromUtf8(mnemonic->valuestring)
            : QString();
        r.opStr = cJSON_IsString(opStr) ? QString::fromUtf8(opStr->valuestring)
                                        : QString();
        r.type = cJSON_IsString(type) ? QString::fromUtf8(type->valuestring)
                                      : QString();
        r.jump = cJSON_IsNumber(jump) ? static_cast<quint64>(jump->valuedouble)
                                      : 0;
        r.fail = cJSON_IsNumber(fail) ? static_cast<quint64>(fail->valuedouble)
                                      : 0;
        r.source = cJSON_IsString(source)
            ? QString::fromUtf8(source->valuestring)
            : QString();
        decoded.push_back(r);
    }
    *text = QString::fromUtf8(textItem->valuestring);
    *instructions = decoded;
    cJSON_Delete(root);
    return true;
}
```

- [ ] **Step 6: Run the helper test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes.

- [ ] **Step 7: Commit Task 2**

Run:

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "test: cover artifact payload round trips"
```

Expected: commit succeeds with helper methods and round-trip coverage.

---

### Task 3: Open the Artifact Cache with Projects

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Write a failing project lifecycle smoke test**

Add this subcase to `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
SUBCASE("project opens artifact cache schema") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));

    sqlite3* db = nullptr;
    REQUIRE(sqlite3_open(dbPath.toUtf8().constData(), &db) == SQLITE_OK);
    sqlite3_stmt* st = nullptr;
    REQUIRE(sqlite3_prepare_v2(
        db,
        "SELECT name FROM sqlite_master WHERE type='table' "
        "AND name='analysis_artifacts';",
        -1, &st, nullptr) == SQLITE_OK);
    CHECK(sqlite3_step(st) == SQLITE_ROW);
    sqlite3_finalize(st);
    sqlite3_close(db);
}
```

If `gui_smoke.cpp` does not include SQLite yet, add:

```cpp
extern "C" {
#include "sqlite3.h"
}
```

- [ ] **Step 2: Run the failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: test fails because `analysis_artifacts` is not created by project open.

- [ ] **Step 3: Add artifact cache ownership to `MainWindow`**

Add this include to `src/gui/main_window.h`:

```cpp
#include "artifact_cache.h"
```

Add this private member next to `m_projectDb` and `m_overrideStore`:

```cpp
    AuraArtifactCache*    m_artifactCache  = nullptr;
```

- [ ] **Step 4: Open and close the cache with projects**

In `MainWindow::closeProject()` in `src/gui/main_window.cpp`, close the cache before closing `m_projectDb`:

```cpp
    if (m_artifactCache) {
        aura_artifact_cache_close(m_artifactCache);
        m_artifactCache = nullptr;
    }
```

In `MainWindow::openProject(const QString& path)`, after opening `pb` and `os`, open the cache:

```cpp
    AuraArtifactCache* ac = aura_artifact_cache_open(pathUtf8.constData());
    if (!ac) {
        aura_override_store_close(os);
        aura_project_binaries_close(pb);
        QMessageBox::critical(this, QStringLiteral("Open Project"),
                              QStringLiteral("artifact cache 열기 실패:\n%1")
                                  .arg(path));
        return false;
    }
```

Then assign it with the other handles:

```cpp
    m_artifactCache = ac;
```

- [ ] **Step 5: Run the lifecycle test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes and the project DB contains `analysis_artifacts`.

- [ ] **Step 6: Commit Task 3**

Run:

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat: open artifact cache with GUI projects"
```

Expected: commit succeeds.

---

### Task 4: Add Decompile Read-Through Cache

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a reopen cache test for decompile**

Add this subcase to `tests/integration/gui_smoke/gui_smoke.cpp`:

```cpp
SUBCASE("decompile artifact survives project reopen") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(window.functionCount() >= 1);

    const bool firstOk = window.decompileFunctionAt(0);
    const QString firstText = window.currentDecompileText();
    REQUIRE_FALSE(firstText.isEmpty());

    aura::gui::MainWindow reopened;
    REQUIRE(reopened.openProject(dbPath));
    REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(reopened.functionCount() >= 1);
    const bool secondOk = reopened.decompileFunctionAt(0);
    const QString secondText = reopened.currentDecompileText();

    CHECK(secondOk == firstOk);
    CHECK(secondText == firstText);
}
```

- [ ] **Step 2: Run the failing reopen test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: test may pass text equality by re-calling Rizin, but no DB row is written. Continue with Step 3 and add a row-count assertion after storage is wired.

- [ ] **Step 3: Add decompile artifact key helper declarations**

Add these private methods to `src/gui/main_window.h`:

```cpp
    AuraArtifactCacheKey decompileArtifactKey(
        quint64 funcAddr,
        const QString& backend) const;
    bool loadDecompileArtifact(quint64 funcAddr,
                               const QString& backend,
                               QString* text,
                               DecompileLineAddrMap* lineMap) const;
    void storeDecompileArtifact(quint64 funcAddr,
                                const QString& backend,
                                const QString& text,
                                const DecompileLineAddrMap& lineMap) const;
```

- [ ] **Step 4: Implement decompile key and load/store helpers**

Add this implementation to `src/gui/main_window.cpp` near `runDecompile()`:

```cpp
AuraArtifactCacheKey MainWindow::decompileArtifactKey(
    quint64 funcAddr,
    const QString& backend) const {
    AuraArtifactCacheKey key{};
    copyUtf8(key.binary_fingerprint, sizeof(key.binary_fingerprint),
             currentFingerprintHex(m_currentSha256));
    copyUtf8(key.engine_id, sizeof(key.engine_id), QStringLiteral("rizin"));
    copyUtf8(key.engine_version, sizeof(key.engine_version),
             QStringLiteral("0.8.0"));
    key.request_type = AURA_ENGINE_REQ_DECOMPILE;
    copyUtf8(key.artifact_kind, sizeof(key.artifact_kind),
             QStringLiteral("decompile.function"));
    copyUtf8(key.backend, sizeof(key.backend), backend);
    key.schema_version = 1;
    key.function_addr = funcAddr;
    key.window_addr = 0;
    key.window_count = 0;
    copyUtf8(key.options_hash, sizeof(key.options_hash),
             QStringLiteral("default"));
    return key;
}

bool MainWindow::loadDecompileArtifact(
    quint64 funcAddr,
    const QString& backend,
    QString* text,
    DecompileLineAddrMap* lineMap) const {
    if (!m_artifactCache || !text || !lineMap) return false;
    AuraArtifactCacheKey key = decompileArtifactKey(funcAddr, backend);
    char* payload = nullptr;
    const int hit = aura_artifact_cache_get(m_artifactCache, &key, &payload);
    if (hit != 1 || !payload) return false;
    const QString json = QString::fromUtf8(payload);
    aura_artifact_cache_free_payload(payload);
    return parseDecompileArtifactPayload(json, text, lineMap);
}

void MainWindow::storeDecompileArtifact(
    quint64 funcAddr,
    const QString& backend,
    const QString& text,
    const DecompileLineAddrMap& lineMap) const {
    if (!m_artifactCache || text.isEmpty()) return;
    AuraArtifactCacheKey key = decompileArtifactKey(funcAddr, backend);
    const QString payload = artifactPayloadForDecompile(text, lineMap);
    if (payload.isEmpty()) return;
    aura_artifact_cache_put(m_artifactCache, &key,
                            payload.toUtf8().constData());
}
```

- [ ] **Step 5: Use the DB cache in `runDecompile()`**

In `runDecompile()`, after the memory cache check and before showing `"// 디컴파일 중..."`, add:

```cpp
    const QString preferredBackend =
        QStringLiteral("rizin/pdgj (rz-ghidra)");
    QString cachedText;
    DecompileLineAddrMap cachedLineMap;
    if (loadDecompileArtifact(funcAddr, preferredBackend, &cachedText,
                              &cachedLineMap)) {
        m_decompilePane->cache(funcAddr, preferredBackend, cachedText,
                               cachedLineMap);
        m_decompilePane->showDecompile(funcAddr, preferredBackend,
                                       cachedText);
        statusBar()->showMessage(
            QStringLiteral("Decompile cache hit: 0x%1")
                .arg(funcAddr, 0, 16));
        return true;
    }
```

After successful Rizin decompile, immediately after `m_decompilePane->cache(funcAddr, backend, text, lineMap);`, add:

```cpp
    storeDecompileArtifact(funcAddr, backend, text, lineMap);
```

- [ ] **Step 6: Store batch decompile results**

In the batch decompile loop in `runAnalyze()`, after `m_decompilePane->cache(addrs[i], label, ..., lineMap);`, add:

```cpp
                const QString bodyText = QString::fromUtf8(btext ? btext : "");
                storeDecompileArtifact(addrs[i], label, bodyText, lineMap);
```

Then change the cache call to reuse `bodyText`:

```cpp
                m_decompilePane->cache(addrs[i], label, bodyText, lineMap);
```

- [ ] **Step 7: Assert DB row exists after decompile**

Extend the decompile reopen subcase with this assertion after the first decompile:

```cpp
    sqlite3* db = nullptr;
    REQUIRE(sqlite3_open(dbPath.toUtf8().constData(), &db) == SQLITE_OK);
    sqlite3_stmt* st = nullptr;
    REQUIRE(sqlite3_prepare_v2(
        db,
        "SELECT COUNT(*) FROM analysis_artifacts "
        "WHERE artifact_kind='decompile.function';",
        -1, &st, nullptr) == SQLITE_OK);
    REQUIRE(sqlite3_step(st) == SQLITE_ROW);
    CHECK(sqlite3_column_int(st, 0) >= 1);
    sqlite3_finalize(st);
    sqlite3_close(db);
```

- [ ] **Step 8: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes and decompile artifacts are persisted.

- [ ] **Step 9: Commit Task 4**

Run:

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "feat: persist decompile artifacts"
```

Expected: commit succeeds.

---

### Task 5: Filter Batch Decompile to Cache Misses

**Files:**
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a cache-hit count assertion**

Add this helper inside `gui_smoke.cpp` test utilities:

```cpp
static int artifactCount(const QString& dbPath, const char* kind) {
    sqlite3* db = nullptr;
    if (sqlite3_open(dbPath.toUtf8().constData(), &db) != SQLITE_OK) return -1;
    sqlite3_stmt* st = nullptr;
    const char* sql =
        "SELECT COUNT(*) FROM analysis_artifacts WHERE artifact_kind=?1;";
    if (sqlite3_prepare_v2(db, sql, -1, &st, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return -1;
    }
    sqlite3_bind_text(st, 1, kind, -1, SQLITE_TRANSIENT);
    int out = -1;
    if (sqlite3_step(st) == SQLITE_ROW) out = sqlite3_column_int(st, 0);
    sqlite3_finalize(st);
    sqlite3_close(db);
    return out;
}
```

In the decompile reopen subcase, after the second analyze, assert the count did not grow:

```cpp
    const int beforeReopenCount =
        artifactCount(dbPath, "decompile.function");
    REQUIRE(beforeReopenCount >= 1);

    aura::gui::MainWindow reopened;
    REQUIRE(reopened.openProject(dbPath));
    REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));

    const int afterReopenCount =
        artifactCount(dbPath, "decompile.function");
    CHECK(afterReopenCount == beforeReopenCount);
```

- [ ] **Step 2: Run the test and observe current behavior**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: the count may stay equal because `INSERT OR REPLACE` overwrites existing keys. The test still protects against duplicate-row growth. The next step removes the duplicate subprocess work.

- [ ] **Step 3: Split batch decompile into hits and misses**

In `runAnalyze()`, replace the `addrs` construction before `aura_rizin_decompile_batch_run` with:

```cpp
        QVector<quint64> addrs;
        addrs.reserve(N);
        const QString preferredBackend =
            QStringLiteral("rizin/pdgj (rz-ghidra)");
        int cacheHits = 0;
        for (const auto& fn : m_functions) {
            QString cachedText;
            DecompileLineAddrMap cachedLineMap;
            if (loadDecompileArtifact(fn.entry, preferredBackend,
                                      &cachedText, &cachedLineMap)) {
                m_decompilePane->cache(fn.entry, preferredBackend,
                                       cachedText, cachedLineMap);
                ++cacheHits;
            } else {
                addrs.push_back(fn.entry);
            }
        }
```

Immediately after this block, add:

```cpp
        if (addrs.isEmpty()) {
            statusBar()->showMessage(
                QStringLiteral("분석 완료: 함수 %1개 (decompile cache hit: %2/%1)")
                    .arg(N).arg(cacheHits));
            m_decompilePane->showPlaceholder(
                QStringLiteral("// 좌측 함수 목록에서 함수를 선택하세요."));
        } else {
```

Wrap the existing batch call block in that `else { ... }`, and close it before `m_decompilePane->showPlaceholder(...)`. Change the final status to:

```cpp
            statusBar()->showMessage(
                QStringLiteral("분석 완료: 함수 %1개 (decompile cache: %2/%1)")
                    .arg(N).arg(filled + cacheHits));
            m_decompilePane->showPlaceholder(
                QStringLiteral("// 좌측 함수 목록에서 함수를 선택하세요."));
        }
```

- [ ] **Step 4: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes.

- [ ] **Step 5: Commit Task 5**

Run:

```powershell
git add src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "perf: skip cached batch decompile work"
```

Expected: commit succeeds.

---

### Task 6: Add Function Disassembly Read-Through Cache

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a disassembly persistence smoke test**

Add this subcase to `gui_smoke.cpp`:

```cpp
SUBCASE("function disassembly artifact survives project reopen") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(window.functionCount() >= 1);
    REQUIRE(window.disassembleFunctionAt(0));

    const int before = artifactCount(dbPath, "disasm.function");
    CHECK(before >= 1);

    aura::gui::MainWindow reopened;
    REQUIRE(reopened.openProject(dbPath));
    REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(reopened.functionCount() >= 1);
    REQUIRE(reopened.disassembleFunctionAt(0));
    CHECK(artifactCount(dbPath, "disasm.function") == before);
}
```

- [ ] **Step 2: Run the failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: fails because no `disasm.function` artifact rows are stored.

- [ ] **Step 3: Add disasm helper declarations**

Add these private methods to `src/gui/main_window.h`:

```cpp
    AuraArtifactCacheKey disasmArtifactKey(
        quint64 funcAddr,
        const QString& artifactKind,
        int windowCount) const;
    bool loadDisasmArtifact(quint64 funcAddr,
                            QVector<GuiInstructionRecord>* instructions,
                            QString* text) const;
    void storeDisasmArtifact(quint64 funcAddr,
                             const QVector<GuiInstructionRecord>& instructions,
                             const QString& text) const;
```

- [ ] **Step 4: Implement disasm key and load/store helpers**

Add this implementation to `src/gui/main_window.cpp` near `runDisasm()`:

```cpp
AuraArtifactCacheKey MainWindow::disasmArtifactKey(
    quint64 funcAddr,
    const QString& artifactKind,
    int windowCount) const {
    AuraArtifactCacheKey key{};
    copyUtf8(key.binary_fingerprint, sizeof(key.binary_fingerprint),
             currentFingerprintHex(m_currentSha256));
    copyUtf8(key.engine_id, sizeof(key.engine_id), QStringLiteral("rizin"));
    copyUtf8(key.engine_version, sizeof(key.engine_version),
             QStringLiteral("0.8.0"));
    key.request_type = AURA_ENGINE_REQ_DISASM;
    copyUtf8(key.artifact_kind, sizeof(key.artifact_kind), artifactKind);
    copyUtf8(key.backend, sizeof(key.backend), QStringLiteral("rizin/pdj"));
    key.schema_version = 1;
    key.function_addr = artifactKind == QStringLiteral("disasm.function")
        ? funcAddr
        : 0;
    key.window_addr = artifactKind == QStringLiteral("disasm.window")
        ? funcAddr
        : 0;
    key.window_count = windowCount;
    copyUtf8(key.options_hash, sizeof(key.options_hash),
             QStringLiteral("default"));
    return key;
}

bool MainWindow::loadDisasmArtifact(
    quint64 funcAddr,
    QVector<GuiInstructionRecord>* instructions,
    QString* text) const {
    if (!m_artifactCache || !instructions || !text) return false;
    AuraArtifactCacheKey key =
        disasmArtifactKey(funcAddr, QStringLiteral("disasm.function"), 0);
    char* payload = nullptr;
    const int hit = aura_artifact_cache_get(m_artifactCache, &key, &payload);
    if (hit != 1 || !payload) return false;
    const QString json = QString::fromUtf8(payload);
    aura_artifact_cache_free_payload(payload);
    return parseDisasmArtifactPayload(json, instructions, text);
}

void MainWindow::storeDisasmArtifact(
    quint64 funcAddr,
    const QVector<GuiInstructionRecord>& instructions,
    const QString& text) const {
    if (!m_artifactCache || instructions.isEmpty()) return;
    AuraArtifactCacheKey key =
        disasmArtifactKey(funcAddr, QStringLiteral("disasm.function"), 0);
    const QString payload = artifactPayloadForDisasm(instructions, text);
    if (payload.isEmpty()) return;
    aura_artifact_cache_put(m_artifactCache, &key,
                            payload.toUtf8().constData());
}
```

- [ ] **Step 5: Use the DB cache in `runDisasm()`**

In `runDisasm()`, after the memory cache check and before creating the orchestrator, add:

```cpp
    QVector<GuiInstructionRecord> cachedIns;
    QString cachedText;
    if (loadDisasmArtifact(funcAddr, &cachedIns, &cachedText)) {
        m_disasmPane->cache(funcAddr, cachedIns);
        m_disasmPane->showDisasm(funcAddr, cachedIns);
        m_disasmPane->setArrowText(funcAddr, cachedText);
        return true;
    }
```

After the existing `m_disasmPane->setArrowText(funcAddr, arrowText);`, add:

```cpp
    storeDisasmArtifact(funcAddr, ins, arrowText);
```

- [ ] **Step 6: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes and `disasm.function` rows exist.

- [ ] **Step 7: Commit Task 6**

Run:

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "perf: persist function disassembly artifacts"
```

Expected: commit succeeds.

---

### Task 7: Add Full Disassembly Window Cache

**Files:**
- Modify: `src/gui/main_window.h`
- Modify: `src/gui/main_window.cpp`
- Test: `tests/integration/gui_smoke/gui_smoke.cpp`

- [ ] **Step 1: Add a full-disassembly window persistence test**

Add this subcase to `gui_smoke.cpp`:

```cpp
SUBCASE("full disassembly window artifact survives project reopen") {
    REQUIRE(window.openProject(dbPath));
    REQUIRE(window.addBinary(fixture));
    REQUIRE(window.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(window.functionCount() >= 1);

    QTreeView* ft = functionTree(window);
    REQUIRE(ft != nullptr);
    QModelIndex entryIdx = ft->model()->index(0, 1);
    bool ok = false;
    quint64 entry = ft->model()->data(entryIdx).toString().toULongLong(&ok, 16);
    REQUIRE(ok);

    REQUIRE(window.runFullDisasmWindow(entry, 128));
    const int before = artifactCount(dbPath, "disasm.window");
    CHECK(before >= 1);

    aura::gui::MainWindow reopened;
    REQUIRE(reopened.openProject(dbPath));
    REQUIRE(reopened.analyzeBinaryAt(0, AURA_ANALYSIS_LEVEL_FULL));
    REQUIRE(reopened.runFullDisasmWindow(entry, 128));
    CHECK(artifactCount(dbPath, "disasm.window") == before);
}
```

- [ ] **Step 2: Run the failing test**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: fails because no `disasm.window` artifacts are stored.

- [ ] **Step 3: Add full-window helper declarations**

Add these private methods to `src/gui/main_window.h`:

```cpp
    bool loadFullDisasmWindowArtifact(
        quint64 addr,
        int count,
        QVector<GuiInstructionRecord>* instructions,
        QString* text) const;
    void storeFullDisasmWindowArtifact(
        quint64 addr,
        int count,
        const QVector<GuiInstructionRecord>& instructions,
        const QString& text) const;
```

- [ ] **Step 4: Implement full-window load/store**

Add this implementation to `src/gui/main_window.cpp` near `runFullDisasmWindow()`:

```cpp
bool MainWindow::loadFullDisasmWindowArtifact(
    quint64 addr,
    int count,
    QVector<GuiInstructionRecord>* instructions,
    QString* text) const {
    if (!m_artifactCache || !instructions || !text) return false;
    AuraArtifactCacheKey key =
        disasmArtifactKey(addr, QStringLiteral("disasm.window"), count);
    char* payload = nullptr;
    const int hit = aura_artifact_cache_get(m_artifactCache, &key, &payload);
    if (hit != 1 || !payload) return false;
    const QString json = QString::fromUtf8(payload);
    aura_artifact_cache_free_payload(payload);
    return parseDisasmArtifactPayload(json, instructions, text);
}

void MainWindow::storeFullDisasmWindowArtifact(
    quint64 addr,
    int count,
    const QVector<GuiInstructionRecord>& instructions,
    const QString& text) const {
    if (!m_artifactCache || instructions.isEmpty()) return;
    AuraArtifactCacheKey key =
        disasmArtifactKey(addr, QStringLiteral("disasm.window"), count);
    const QString payload = artifactPayloadForDisasm(instructions, text);
    if (payload.isEmpty()) return;
    aura_artifact_cache_put(m_artifactCache, &key,
                            payload.toUtf8().constData());
}
```

- [ ] **Step 5: Use the cache in `runFullDisasmWindow()`**

In `runFullDisasmWindow()`, after count normalization and before the loading status message, add:

```cpp
    QVector<GuiInstructionRecord> cachedIns;
    QString cachedText;
    if (loadFullDisasmWindowArtifact(addr, count, &cachedIns, &cachedText)) {
        if (cachedText.isEmpty()) {
            m_fullDisasmPane->showInstructions(addr, count, cachedIns);
        } else {
            m_fullDisasmPane->showMixedListing(addr, count, cachedText,
                                               cachedIns);
        }
        m_fullDisasmPane->setArrowText(addr, cachedText);
        statusBar()->showMessage(
            QStringLiteral("전체 디스어셈블리 cache hit: 0x%1")
                .arg(addr, 0, 16));
        return true;
    }
```

After `m_fullDisasmPane->setArrowText(addr, arrowText);`, add:

```cpp
    storeFullDisasmWindowArtifact(addr, count, ins, arrowText);
```

- [ ] **Step 6: Run GUI smoke**

Run:

```powershell
cmake --build build-trim-gui --config Release --target gui_smoke
ctest --test-dir build-trim-gui -C Release -R gui_smoke --output-on-failure
```

Expected: `gui_smoke` passes and `disasm.window` rows exist.

- [ ] **Step 7: Commit Task 7**

Run:

```powershell
git add src/gui/main_window.h src/gui/main_window.cpp tests/integration/gui_smoke/gui_smoke.cpp
git commit -m "perf: persist full disassembly windows"
```

Expected: commit succeeds.

---

### Task 8: Final Verification

**Files:**
- No new files expected beyond previous tasks.

- [ ] **Step 1: Build the full GUI tree**

Run:

```powershell
cmake --build build-trim-gui --config Release
```

Expected: full build succeeds, including `aura.exe`, `aura-gui.exe`, `aura-mcp.exe`, `artifact_cache_unit.exe`, and `gui_smoke.exe`.

- [ ] **Step 2: Run targeted tests**

Run:

```powershell
ctest --test-dir build-trim-gui -C Release -R "artifact_cache_unit|gui_smoke" --output-on-failure
```

Expected: both tests pass.

- [ ] **Step 3: Run the release gate**

Run:

```powershell
powershell -ExecutionPolicy Bypass -File scripts\verify_release_gate.ps1 -BuildDir build-trim-gui -Config Release
```

Expected: all configured tests pass.

- [ ] **Step 4: Inspect git diff**

Run:

```powershell
git status --short
git diff --stat HEAD
```

Expected: only artifact cache, GUI cache wiring, tests, and this plan are changed.

- [ ] **Step 5: Commit the plan if it is not already committed**

Run:

```powershell
git add docs/superpowers/plans/2026-05-10-cache-speedup.md .scratch/cache-speedup/PLAN.md
git commit -m "docs: plan cache speedup work"
```

Expected: documentation commit succeeds if plan files remain uncommitted.

---

## Self-Review

**Spec coverage:** The plan covers persistent storage for decompile, function disassembly, full-disassembly window reuse, duplicate batch decompile reduction, and cache invalidation by fingerprint/version/schema key.

**Placeholder scan:** The plan avoids open-ended implementation steps. Every code-facing step names exact files, code blocks, commands, and expected outcomes.

**Type consistency:** `AuraArtifactCacheKey`, `AuraArtifactCache`, `DecompileLineAddrMap`, `GuiInstructionRecord`, and `MainWindow` helper names are consistent across tasks.

**Known risk:** The plan uses a fixed `"0.8.0"` engine version key for the first implementation because the current GUI path resolves a vendored Rizin baseline. A later slice should replace this with a probed version string from the engine probe result.
