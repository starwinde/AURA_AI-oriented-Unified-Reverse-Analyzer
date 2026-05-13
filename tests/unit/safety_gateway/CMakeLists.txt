add_executable(safety_gateway_unit safety_gateway_unit.cpp)
target_include_directories(safety_gateway_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/src/safety_gateway
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(safety_gateway_unit PRIVATE aura_safety_gateway_core cjson sqlite3)
target_compile_features(safety_gateway_unit PRIVATE cxx_std_17)

add_test(NAME safety_gateway_unit COMMAND safety_gateway_unit)
set_tests_properties(safety_gateway_unit PROPERTIES
    LABELS "unit;safety_gateway"
    TIMEOUT 30
)
