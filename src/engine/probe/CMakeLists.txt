# src/engine/probe — Phase 2.5
# Engine-agnostic probe library. No dependency on Rizin / Ghidra / angr /
# retdec adapters; deliberately built outside AURA_ENABLE_RIZIN so the
# probe contract can be exercised on hosts that have no RE engines at all.

add_library(aura_engine_probe STATIC
    engine_probe.c
    probe_registry.c
    probe_cache.c
    command_runner_subprocess.c
)
target_include_directories(aura_engine_probe PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(aura_engine_probe PUBLIC cjson)
target_compile_features(aura_engine_probe PRIVATE c_std_11)
