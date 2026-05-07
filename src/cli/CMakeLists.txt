# src/cli/CMakeLists.txt — `aura` CLI binary (Phase 11.1).
# Frontend topology: ADR-0033. Built when AURA_ENABLE_RIZIN is ON
# (Rizin adapter linked into aura_core).

add_executable(aura main.cpp)
target_include_directories(aura PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/aura
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/CLI11
)
target_link_libraries(aura PRIVATE aura_core cjson aura_engine_probe)
if(WIN32)
    target_link_libraries(aura PRIVATE ws2_32)
endif()
target_compile_features(aura PRIVATE cxx_std_17)

install(TARGETS aura RUNTIME DESTINATION bin)
