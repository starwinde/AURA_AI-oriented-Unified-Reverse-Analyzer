add_library(aura_mcp_core STATIC
    mcp_cli_bridge.cpp
    mcp_envelope.cpp
    mcp_path_policy.cpp
    mcp_tools.cpp
)
target_include_directories(aura_mcp_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)
target_link_libraries(aura_mcp_core PUBLIC aura_core cjson)
target_compile_features(aura_mcp_core PUBLIC cxx_std_17)

add_executable(aura-mcp mcp_server.cpp)
target_include_directories(aura-mcp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)
target_link_libraries(aura-mcp PRIVATE aura_mcp_core cjson)
target_compile_features(aura-mcp PRIVATE cxx_std_17)
