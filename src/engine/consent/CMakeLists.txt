# src/engine/consent — Phase 2.5 §1.5
# Engine-bootstrap consent decision layer. Pure logic over an injectable
# store backend; SQLite persistence layer added in a later slice.

add_library(aura_engine_consent STATIC
    consent_gate.c
    consent_store_sqlite.c
    consent_lock.c
)
target_include_directories(aura_engine_consent PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(aura_engine_consent PUBLIC sqlite3)
target_compile_features(aura_engine_consent PRIVATE c_std_11)
