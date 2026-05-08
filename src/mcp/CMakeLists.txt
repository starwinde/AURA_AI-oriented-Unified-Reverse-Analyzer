add_library(aura_mcp_core STATIC
    mcp_envelope.cpp
)
target_include_directories(aura_mcp_core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
)
target_link_libraries(aura_mcp_core PUBLIC cjson)
target_compile_features(aura_mcp_core PRIVATE cxx_std_17)
