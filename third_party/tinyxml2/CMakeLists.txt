# tinyxml2 11.0.0 (zlib/libpng license) — vendored for AURA D-27 Ghidra XML protocol parsing
cmake_minimum_required(VERSION 3.16)

add_library(tinyxml2_static STATIC ${CMAKE_CURRENT_SOURCE_DIR}/tinyxml2.cpp)

target_include_directories(tinyxml2_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(tinyxml2_static PUBLIC cxx_std_11)
target_compile_options(tinyxml2_static PRIVATE -w)
set_target_properties(tinyxml2_static PROPERTIES POSITION_INDEPENDENT_CODE ON)
