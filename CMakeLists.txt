cmake_minimum_required(VERSION 3.16)
project(aura
    VERSION 3.0.0
    DESCRIPTION "AURA — RE-tool orchestrator + LLM context provider"
    LANGUAGES C CXX
)

# ── 표준 설정 ───────────────────────────────────────────────────────────────
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ── 컴파일 경고 플래그 ──────────────────────────────────────────────────────
if(MSVC)
    add_compile_options(/W4 /utf-8)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DNOMINMAX -DWIN32_LEAN_AND_MEAN)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)
endif()

# ── SQLite (amalgamation, Public Domain) — project DB ──────────────────────
add_library(sqlite3 STATIC third_party/sqlite/sqlite3.c)
target_include_directories(sqlite3 PUBLIC third_party/sqlite)
target_compile_definitions(sqlite3 PRIVATE
    SQLITE_THREADSAFE=1
    SQLITE_OMIT_LOAD_EXTENSION
)
if(MSVC)
    target_compile_options(sqlite3 PRIVATE /w)
else()
    target_compile_options(sqlite3 PRIVATE -w)
endif()

# ── cJSON (단일 파일, 정적 링크) — IPC payload + LLM JSON ───────────────────
add_library(cjson STATIC third_party/cjson/cJSON.c)
target_include_directories(cjson PUBLIC third_party/cjson)
if(MSVC)
    target_compile_options(cjson PRIVATE /w)
else()
    target_compile_options(cjson PRIVATE -w)
endif()

# ── libcurl (LLM HTTP 클라이언트) ────────────────────────────────────────────
find_package(CURL QUIET)
if(NOT CURL_FOUND)
    find_path(CURL_INCLUDE_DIR curl/curl.h
        HINTS
            ${CMAKE_SOURCE_DIR}/third_party/curl/include
            /usr/include
            /usr/include/${CMAKE_LIBRARY_ARCHITECTURE}
    )
    find_library(CURL_LIBRARY NAMES curl
        HINTS /usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} /usr/lib
    )
    if(CURL_INCLUDE_DIR AND CURL_LIBRARY)
        set(CURL_FOUND TRUE)
        add_library(CURL::libcurl UNKNOWN IMPORTED)
        set_target_properties(CURL::libcurl PROPERTIES
            IMPORTED_LOCATION "${CURL_LIBRARY}"
            INTERFACE_INCLUDE_DIRECTORIES "${CURL_INCLUDE_DIR}"
        )
        message(STATUS "libcurl found manually: ${CURL_LIBRARY}")
    endif()
endif()
option(AURA_BUILD_LLM "Build LLM integration module" ${CURL_FOUND})

# ── External RE-tool adapters (Phase 1~3 contract) ─────────────────────────
# Rizin / Ghidra adapters speak to external processes; no in-tree RE engine.
option(AURA_ENABLE_RIZIN "Build Rizin engine adapter (subprocess)" OFF)

set(_AURA_RIZIN_HUB_DEFAULT OFF)
if(AURA_ENABLE_RIZIN)
    set(_AURA_RIZIN_HUB_DEFAULT ON)
endif()
option(AURA_ENABLE_RIZIN_HUB
       "Build third_party_hub skeleton (Rizin-style I/O hub)"
       ${_AURA_RIZIN_HUB_DEFAULT})
unset(_AURA_RIZIN_HUB_DEFAULT)
if(AURA_ENABLE_RIZIN_HUB)
    message(STATUS "AURA third_party_hub: enabled (skeleton)")
endif()

if(AURA_ENABLE_RIZIN)
    message(STATUS "AURA Rizin adapter: enabled (subprocess-only)")
    include_directories(${CMAKE_SOURCE_DIR}/src/adapter/rizin)
    include_directories(${CMAKE_SOURCE_DIR}/src/third_party_hub)
    add_compile_definitions(AURA_ENABLE_RIZIN=1)
endif()

# ── 헤더 경로 ───────────────────────────────────────────────────────────────
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)

# ── aura_core: orchestrator / IPC / override pipeline ───────────────────────
# In-house disassembler / parser / decompiler / symbolic engine were removed
# in commit 463c7967 (branch feat/strip-legacy-engines). All RE work happens
# in external tools accessed via the adapter contract.
set(AURA_CORE_SOURCES
    src/core/orchestrator.c
    src/core/sha256.c
    src/core/engine_manifest.c
    src/core/engine_subprocess.c
    src/core/diagnostics.c
    src/core/aura_compat.c
    src/core/aura_io.c
    src/core/logger.c
    src/core/demangle.cpp
    src/core/mapped_file.c
    src/core/normalized_records.c
    src/core/type_propagation.cpp
    src/core/override_identity.c
    src/core/override_store.c
    src/core/override_resolve.c
    src/core/override_view.c
    src/core/override_pipeline.c
    src/core/project_binaries.c
    src/core/string_protection_store.c
    src/core/safety/string_safety.cpp
    src/adapter/ghidra/ghidra_adapter.c
    src/adapter/ghidra/ghidra_subprocess.c
    src/adapter/ghidra/ghidra_xml_normalize.c
)

if(AURA_ENABLE_RIZIN_HUB)
    list(APPEND AURA_CORE_SOURCES
        src/third_party_hub/tp_vec.c
        src/third_party_hub/tp_binary.c
        src/third_party_hub/tp_registry.c
        src/third_party_hub/tp_hub.c
    )
endif()

if(AURA_ENABLE_RIZIN)
    list(APPEND AURA_CORE_SOURCES
        src/adapter/rizin/rizin_subprocess.c
        src/adapter/rizin/rizin_framing.c
        src/adapter/rizin/rizin_command_set.c
        src/adapter/rizin/rizin_snapshot.c
        src/adapter/rizin/rizin_decompile_caps.c
        src/adapter/rizin/rizin_decompile_normalize.c
        src/adapter/rizin/rizin_disasm_normalize.c
        src/adapter/rizin/rizin_adapter.c
        src/third_party_hub/rizin_to_aura.c
    )
endif()

add_library(aura_core STATIC ${AURA_CORE_SOURCES})
target_compile_definitions(aura_core PRIVATE AURA_NO_MAIN)
if(MSVC)
    # /FI force-include for AURA_WEAK / AURA_UNUSED macros. Use the
    # bare header name (not an absolute CMAKE_SOURCE_DIR path) so MSVC
    # resolves it through the existing include_directories() search
    # paths. Absolute paths fail to parse when CMAKE_SOURCE_DIR contains
    # non-ASCII characters (e.g. Korean) — the /FI argument is wrapped in
    # backslash-escaped double quotes that MSVC cannot decode under
    # those locales. Bare-name lookup is locale-independent.
    target_compile_options(aura_core PRIVATE /FIaura_compat.h)
endif()
set(AURA_CORE_LINK_LIBS)
if(WIN32)
    list(APPEND AURA_CORE_LINK_LIBS ws2_32 dbghelp)
else()
    list(APPEND AURA_CORE_LINK_LIBS m dl)
endif()
if(AURA_ENABLE_RIZIN_HUB)
    target_compile_definitions(aura_core PRIVATE AURA_HAS_TP_HUB=1)
endif()
target_link_libraries(aura_core PUBLIC ${AURA_CORE_LINK_LIBS} cjson)
target_link_libraries(aura_core PRIVATE sqlite3)

# ── aura_llm: libcurl + cJSON ──────────────────────────────────────────────
if(AURA_BUILD_LLM)
    set(AURA_LLM_SOURCES
        src/llm/llm_client.c
        src/llm/llm_http.c
        src/llm/lmstudio_client.c
        src/llm/llamacpp_client.c
        src/llm/openai_client.c
        src/llm/groq_client.c
        src/llm/llm_config.c
        src/llm/llm_cache.c
        src/llm/prompt_templates.c
    )

    add_library(aura_llm STATIC ${AURA_LLM_SOURCES})
    target_include_directories(aura_llm PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src/core
        ${CMAKE_SOURCE_DIR}/src/llm
    )
    target_link_libraries(aura_llm PUBLIC cjson CURL::libcurl)
    target_compile_definitions(aura_llm PRIVATE AURA_NO_MAIN)
    message(STATUS "AURA LLM: enabled (libcurl ${CURL_VERSION_STRING})")
else()
    message(WARNING "libcurl not found — LLM module disabled. Install libcurl4-openssl-dev to enable.")
endif()

# ── 헤더 설치 ──────────────────────────────────────────────────────────────
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include/aura
    FILES_MATCHING PATTERN "*.h"
)

# ── 문서 설치 ──────────────────────────────────────────────────────────────
install(FILES
    ${CMAKE_SOURCE_DIR}/README.md
    ${CMAKE_SOURCE_DIR}/LICENSE
    DESTINATION share/doc/aura
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets/safety/
    DESTINATION share/aura/safety
)

# ── Engine-agnostic probe library (Phase 2.5) ─────────────────────────────
# Built unconditionally — the whole point is to surface a usable probe
# contract on hosts that have no RE engines installed at all. Must NOT
# depend on AURA_ENABLE_RIZIN.
add_subdirectory(src/engine/probe)

# ── Engine-bootstrap consent gate (Phase 2.5 §1.5) ────────────────────────
# Pure decision layer over an injectable store. Built unconditionally —
# same rationale as the probe library.
add_subdirectory(src/engine/consent)

# ── Engine bootstrap orchestration (Phase 2.5 §1.6/§1.7) ──────────────────
# Pure classification + (later) dispatch layer. No fetch / venv code; the
# real fetcher is injected by the caller so tests stay hermetic.
add_subdirectory(src/engine/bootstrap)

# ── Tests ──────────────────────────────────────────────────────────────────
# Integration gates introduced in Phase 10 (ADR-0031 reference engine policy
# + ADR-0032 external tool acquisition). Default ON; gated per-suite by
# additional options (e.g. AURA_ENABLE_RIZIN for orchestrator_smoke).
option(AURA_BUILD_TESTS "Build AURA test suite" ON)
if(AURA_BUILD_TESTS)
    enable_testing()

    # Phase 2.5 — engine-agnostic probe unit tests, no engine dep.
    add_subdirectory(tests/unit/probe)
    # Phase 2.5 §1.5 — consent gate unit tests, no engine dep.
    add_subdirectory(tests/unit/consent)
    # Phase 2.5 §1.6/§1.7 — bootstrap classify/dispatch unit tests.
    add_subdirectory(tests/unit/bootstrap)
    add_subdirectory(tests/unit/safety)

    if(AURA_ENABLE_RIZIN)
        add_subdirectory(tests/integration/orchestrator_smoke)
    endif()
endif()

# ── Frontend: CLI (Phase 11.1, ADR-0033) ───────────────────────────────────
# `aura` binary. Built when AURA_ENABLE_RIZIN is ON (the Rizin reference
# engine is linked into aura_core in that mode).
if(AURA_ENABLE_RIZIN)
    add_subdirectory(src/cli)
    if(AURA_BUILD_TESTS)
        add_subdirectory(tests/integration/cli_smoke)
    endif()
endif()

# ── Frontend: GUI (Phase 11.3, ADR-0035) ───────────────────────────────────
# `aura-gui` Qt6 binary. Opt-in (default OFF) until CI runners install Qt6.
# Requires Qt6::Widgets — set Qt6_DIR or CMAKE_PREFIX_PATH if non-standard.
option(AURA_BUILD_GUI "Build aura-gui Qt6 frontend" OFF)
if(AURA_BUILD_GUI)
    add_subdirectory(src/gui)
    if(AURA_BUILD_TESTS AND AURA_ENABLE_RIZIN)
        add_subdirectory(tests/integration/gui_smoke)
    endif()
endif()
