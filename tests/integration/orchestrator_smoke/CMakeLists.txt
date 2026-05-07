# tests/integration/orchestrator_smoke — reference engine invariant gate.
# Built only when AURA_ENABLE_RIZIN is ON (Rizin adapter linked into
# aura_core). See ADR-0031 / ADR-0032 for the policy.

add_executable(orchestrator_smoke orchestrator_smoke.cpp)
target_include_directories(orchestrator_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/aura
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(orchestrator_smoke PRIVATE aura_core cjson)
target_compile_features(orchestrator_smoke PRIVATE cxx_std_17)

add_test(NAME orchestrator_smoke COMMAND orchestrator_smoke)
set_tests_properties(orchestrator_smoke PROPERTIES
    LABELS "integration;reference_engine"
    TIMEOUT 60
    ENVIRONMENT "AURA_REPO_ROOT=${CMAKE_SOURCE_DIR}"
)
