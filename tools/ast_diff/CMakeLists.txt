cmake_minimum_required(VERSION 3.16)
project(ast_diff CXX)

# AURA Phase G — Hybrid scorer ast_diff binary.
# Standalone CMake project. NOT included from root CMakeLists.txt.
# Build: cmake -S tools/ast_diff -B tools/ast_diff/build
#        cmake --build tools/ast_diff/build
# Requires: libclang-18-dev (Debian/Ubuntu apt package)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

# libclang-18 (Debian/Ubuntu): headers under /usr/lib/llvm-18/include,
# .so under /usr/lib/llvm-18/lib + symlinks at /usr/lib/aarch64-linux-gnu/.
# Allow override via -DLLVM_PREFIX=/path/to/llvm.
if(NOT DEFINED LLVM_PREFIX)
    set(LLVM_PREFIX "/usr/lib/llvm-18")
endif()

find_path(LIBCLANG_INCLUDE_DIR clang-c/Index.h
    PATHS ${LLVM_PREFIX}/include /usr/include
    NO_DEFAULT_PATH)
if(NOT LIBCLANG_INCLUDE_DIR)
    message(FATAL_ERROR
        "clang-c/Index.h not found. Install libclang-18-dev:\n"
        "  sudo apt install libclang-18-dev")
endif()

find_library(LIBCLANG_LIB NAMES clang clang-18
    PATHS ${LLVM_PREFIX}/lib /usr/lib/aarch64-linux-gnu /usr/lib/x86_64-linux-gnu
    NO_DEFAULT_PATH)
if(NOT LIBCLANG_LIB)
    message(FATAL_ERROR
        "libclang.so not found. Install libclang-18-dev:\n"
        "  sudo apt install libclang-18-dev")
endif()

message(STATUS "libclang headers: ${LIBCLANG_INCLUDE_DIR}")
message(STATUS "libclang lib:     ${LIBCLANG_LIB}")

add_executable(ast_diff ast_diff.cpp)
target_include_directories(ast_diff PRIVATE ${LIBCLANG_INCLUDE_DIR})
target_link_libraries(ast_diff PRIVATE ${LIBCLANG_LIB})
target_compile_options(ast_diff PRIVATE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
    -fno-exceptions)

enable_testing()
add_executable(test_ast_diff test_ast_diff.cpp)
target_include_directories(test_ast_diff PRIVATE ${LIBCLANG_INCLUDE_DIR})
target_link_libraries(test_ast_diff PRIVATE ${LIBCLANG_LIB})
target_compile_options(test_ast_diff PRIVATE
    -Wall -Wextra -fno-exceptions)
add_test(NAME ast_diff_unit COMMAND test_ast_diff)
