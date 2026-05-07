# tests/integration/cli_smoke — Phase 11.1 CLI v1 invariant gate.
# Built only when AURA_ENABLE_RIZIN is ON (the `aura` binary requires it).

add_executable(cli_smoke cli_smoke.cpp)
add_dependencies(cli_smoke aura)
target_include_directories(cli_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(cli_smoke PRIVATE cjson)
target_compile_features(cli_smoke PRIVATE cxx_std_17)

add_test(NAME cli_smoke COMMAND cli_smoke)
if(WIN32)
    set(_aura_rizin_bin_default "${CMAKE_SOURCE_DIR}/third_party/rizin/0.8.2/bin/rizin.exe")
else()
    set(_aura_rizin_bin_default "${CMAKE_SOURCE_DIR}/third_party/rizin/0.8.2/bin/rizin")
endif()
set_tests_properties(cli_smoke PROPERTIES
    LABELS "integration;cli"
    TIMEOUT 120
    ENVIRONMENT "AURA_REPO_ROOT=${CMAKE_SOURCE_DIR};AURA_BIN=$<TARGET_FILE:aura>;AURA_RIZIN_BIN=${_aura_rizin_bin_default}"
)

# Phase 2.5.1 Slice X.5 — `aura --probe-engines` envelope contract.
# Independent from cli_smoke; does not require a real binary input or a
# real Rizin install (probe is engine-agnostic). Still gated by
# AURA_ENABLE_RIZIN because it links against the `aura` binary which
# itself depends on aura_core (built only with RIZIN=ON).
add_executable(probe_engines_smoke probe_engines_smoke.cpp)
add_dependencies(probe_engines_smoke aura)
target_include_directories(probe_engines_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(probe_engines_smoke PRIVATE cjson)
target_compile_features(probe_engines_smoke PRIVATE cxx_std_17)

add_test(NAME probe_engines_smoke COMMAND probe_engines_smoke)
set_tests_properties(probe_engines_smoke PROPERTIES
    LABELS "integration;cli;probe"
    TIMEOUT 60
    ENVIRONMENT "AURA_BIN=$<TARGET_FILE:aura>"
)
