# tests/unit/consent — Phase 2.5 §1.5
# Engine-agnostic consent gate unit tests.

add_executable(consent_unit consent_unit.cpp)
target_include_directories(consent_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(consent_unit PRIVATE aura_engine_consent)
target_compile_features(consent_unit PRIVATE cxx_std_17)

add_test(NAME consent_unit COMMAND consent_unit)
set_tests_properties(consent_unit PROPERTIES
    LABELS  "unit;consent"
    TIMEOUT 30
)
