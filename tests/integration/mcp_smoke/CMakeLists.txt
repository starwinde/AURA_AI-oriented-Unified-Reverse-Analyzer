add_executable(mcp_smoke mcp_smoke.cpp)
add_dependencies(mcp_smoke aura-mcp)
target_include_directories(mcp_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(mcp_smoke PRIVATE cjson)
target_compile_features(mcp_smoke PRIVATE cxx_std_17)

add_test(NAME mcp_smoke COMMAND mcp_smoke)
set_tests_properties(mcp_smoke PROPERTIES
    LABELS "integration;mcp"
    TIMEOUT 30
    ENVIRONMENT "AURA_MCP_BIN=$<TARGET_FILE:aura-mcp>"
)
