# tests/unit/bootstrap — Phase 2.5 §1.6/§1.7

add_executable(bootstrap_unit bootstrap_unit.cpp)
target_include_directories(bootstrap_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(bootstrap_unit PRIVATE
    aura_engine_bootstrap
    aura_engine_consent
)
target_compile_features(bootstrap_unit PRIVATE cxx_std_17)

add_test(NAME bootstrap_unit COMMAND bootstrap_unit)
set_tests_properties(bootstrap_unit PROPERTIES
    LABELS  "unit;bootstrap"
    TIMEOUT 30
)
