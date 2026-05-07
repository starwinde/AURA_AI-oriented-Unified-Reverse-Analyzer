# tests/unit/probe — Phase 2.5
# Engine-agnostic probe unit tests. Built unconditionally (no
# AURA_ENABLE_RIZIN gate) so the contract is exercised on hosts that
# have no RE engines installed.

add_executable(probe_unit probe_unit.cpp)
target_include_directories(probe_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(probe_unit PRIVATE aura_engine_probe)
target_compile_features(probe_unit PRIVATE cxx_std_17)

add_test(NAME probe_unit COMMAND probe_unit)
set_tests_properties(probe_unit PROPERTIES
    LABELS  "unit;probe"
    TIMEOUT 30
)

# Phase 2.5.1 Slice X.3 — real subprocess runner.
# Drives the production AuraCommandRunner against portable shell
# builtins (cmd /c on Windows, /bin/sh on POSIX). No engine binaries.
add_executable(subprocess_runner_unit subprocess_runner_unit.cpp)
target_include_directories(subprocess_runner_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(subprocess_runner_unit PRIVATE aura_engine_probe)
target_compile_features(subprocess_runner_unit PRIVATE cxx_std_17)

add_test(NAME subprocess_runner_unit COMMAND subprocess_runner_unit)
set_tests_properties(subprocess_runner_unit PROPERTIES
    LABELS  "unit;probe"
    TIMEOUT 30
)
