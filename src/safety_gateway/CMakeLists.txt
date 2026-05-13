add_library(aura_safety_gateway_core STATIC
    control_api.cpp
    gateway_config.cpp
    gateway_request.cpp
    gateway_policy.cpp
    gateway_cache.cpp
    mcp_http.cpp
    remote_access.cpp
    request_log.cpp
    session_reveal_store.cpp
    ui_assets.cpp
    upstream_forwarder.cpp
)
target_include_directories(aura_safety_gateway_core
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/sqlite
)
target_link_libraries(aura_safety_gateway_core PUBLIC aura_core cjson PRIVATE sqlite3)
target_compile_features(aura_safety_gateway_core PUBLIC cxx_std_17)

add_executable(aura-safety-gateway main.cpp)
target_include_directories(aura-safety-gateway PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/sqlite
)
target_link_libraries(aura-safety-gateway PRIVATE aura_safety_gateway_core aura_core cjson sqlite3)
target_compile_features(aura-safety-gateway PRIVATE cxx_std_17)
