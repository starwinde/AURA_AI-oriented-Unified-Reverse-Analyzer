add_executable(safety_gateway_smoke safety_gateway_smoke.cpp)
add_dependencies(safety_gateway_smoke aura-safety-gateway)
target_include_directories(safety_gateway_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_compile_features(safety_gateway_smoke PRIVATE cxx_std_17)
if(WIN32)
    target_link_libraries(safety_gateway_smoke PRIVATE ws2_32)
endif()

add_test(NAME safety_gateway_smoke COMMAND safety_gateway_smoke)
set_tests_properties(safety_gateway_smoke PROPERTIES
    LABELS "integration;safety_gateway"
    TIMEOUT 30
    ENVIRONMENT "AURA_SAFETY_GATEWAY_BIN=$<TARGET_FILE:aura-safety-gateway>"
)
