add_executable(mcp_unit
    mcp_unit.cpp
    mcp_tools_header_c.c
)
target_include_directories(mcp_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(mcp_unit PRIVATE aura_mcp_core cjson)
target_compile_features(mcp_unit PRIVATE cxx_std_17)

add_test(NAME mcp_unit COMMAND mcp_unit)
set_tests_properties(mcp_unit PROPERTIES
    LABELS "unit;mcp"
    TIMEOUT 30
)
