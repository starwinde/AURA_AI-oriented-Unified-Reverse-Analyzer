# YARA library (BSD 3-Clause) — CMake build for AURA integration
# Minimal build: core + default modules (no libcrypto, no cuckoo, etc.)

cmake_minimum_required(VERSION 3.16)

set(YARA_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libyara)

set(YARA_SOURCES
    ${YARA_SRC_DIR}/ahocorasick.c
    ${YARA_SRC_DIR}/arena.c
    ${YARA_SRC_DIR}/atoms.c
    ${YARA_SRC_DIR}/base64.c
    ${YARA_SRC_DIR}/bitmask.c
    ${YARA_SRC_DIR}/compiler.c
    ${YARA_SRC_DIR}/endian.c
    ${YARA_SRC_DIR}/exec.c
    ${YARA_SRC_DIR}/exefiles.c
    ${YARA_SRC_DIR}/filemap.c
    ${YARA_SRC_DIR}/grammar.c
    ${YARA_SRC_DIR}/hash.c
    ${YARA_SRC_DIR}/hex_grammar.c
    ${YARA_SRC_DIR}/hex_lexer.c
    ${YARA_SRC_DIR}/lexer.c
    ${YARA_SRC_DIR}/libyara.c
    ${YARA_SRC_DIR}/mem.c
    ${YARA_SRC_DIR}/modules.c
    ${YARA_SRC_DIR}/notebook.c
    ${YARA_SRC_DIR}/object.c
    ${YARA_SRC_DIR}/parser.c
    ${YARA_SRC_DIR}/proc.c
    ${YARA_SRC_DIR}/re.c
    ${YARA_SRC_DIR}/re_grammar.c
    ${YARA_SRC_DIR}/re_lexer.c
    ${YARA_SRC_DIR}/rules.c
    ${YARA_SRC_DIR}/scan.c
    ${YARA_SRC_DIR}/scanner.c
    ${YARA_SRC_DIR}/simple_str.c
    ${YARA_SRC_DIR}/sizedstr.c
    ${YARA_SRC_DIR}/stack.c
    ${YARA_SRC_DIR}/stopwatch.c
    ${YARA_SRC_DIR}/stream.c
    ${YARA_SRC_DIR}/strutils.c
    ${YARA_SRC_DIR}/threading.c
    # Default modules (from module_list without #ifdef guards)
    ${YARA_SRC_DIR}/modules/tests/tests.c
    ${YARA_SRC_DIR}/modules/pe/pe.c
    ${YARA_SRC_DIR}/modules/pe/pe_utils.c
    ${YARA_SRC_DIR}/modules/elf/elf.c
    ${YARA_SRC_DIR}/modules/math/math.c
    ${YARA_SRC_DIR}/modules/time/time.c
    ${YARA_SRC_DIR}/modules/console/console.c
    ${YARA_SRC_DIR}/modules/string/string.c
    # Linux proc
    ${YARA_SRC_DIR}/proc/linux.c
    # TLSH (bundled)
    ${YARA_SRC_DIR}/tlshc/tlsh.c
    ${YARA_SRC_DIR}/tlshc/tlsh_impl.c
    ${YARA_SRC_DIR}/tlshc/tlsh_util.c
)

add_library(yara_static STATIC ${YARA_SOURCES})

target_include_directories(yara_static PUBLIC
    ${YARA_SRC_DIR}/include
)

target_include_directories(yara_static PRIVATE
    ${YARA_SRC_DIR}
    ${YARA_SRC_DIR}/modules
    ${YARA_SRC_DIR}/tlshc
    ${YARA_SRC_DIR}/include/tlshc
)

target_compile_definitions(yara_static PRIVATE
    HAVE_STDBOOL_H=1
    HAVE_CLOCK_GETTIME=1
    USE_LINUX_PROC
    _GNU_SOURCE
    BUCKETS_128
)

# Suppress warnings from third-party code
target_compile_options(yara_static PRIVATE -w)

target_link_libraries(yara_static PRIVATE pthread m)
