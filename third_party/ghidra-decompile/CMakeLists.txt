# Ghidra 12.0.4 decompile/cpp vendor (Apache 2.0) — AURA D-27 Phase 0
#
# Targets:
#   ghidra_zlib            — vendored zlib static lib (Ghidra ships this in decompile/zlib/)
#   aura-sleigh-compile    — slgh_compile main, generates .sla from .slaspec
#   aura-decompile         — ghidra_process main, production XML subprocess
#
# Phase 0 scope: build/run verification only. AURA HIR integration deferred.
# Source partitioning derived from cpp/Makefile (CORE + DECCORE + SLEIGH + GHIDRA + SLACOMP).
# libbfd-dependent files (analyzesigs, codedata, sleighexample, loadimage_bfd, bfd_arch) excluded
# — only used by decomp_dbg target which is not built (avoids GPL contamination).

cmake_minimum_required(VERSION 3.16)

find_program(BISON_EXECUTABLE bison)
find_program(FLEX_EXECUTABLE flex)

set(GHIDRA_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cpp)
set(GHIDRA_PREBUILT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/prebuilt_gen)
set(GHIDRA_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${GHIDRA_GEN_DIR})

# ── bison/flex generated files ──────────────────────────────────────────────
# bison/flex 없을 때 prebuilt_gen/ 의 사전 생성 파일을 복사해 사용한다.
if(BISON_EXECUTABLE AND FLEX_EXECUTABLE)
    add_custom_command(
        OUTPUT ${GHIDRA_GEN_DIR}/xml.cc
        COMMAND ${BISON_EXECUTABLE} -l -o ${GHIDRA_GEN_DIR}/xml.cc ${GHIDRA_CPP_DIR}/xml.y
        DEPENDS ${GHIDRA_CPP_DIR}/xml.y
        COMMENT "[ghidra] bison xml.y"
        VERBATIM
    )
    add_custom_command(
        OUTPUT ${GHIDRA_GEN_DIR}/grammar.cc
        COMMAND ${BISON_EXECUTABLE} -l -o ${GHIDRA_GEN_DIR}/grammar.cc ${GHIDRA_CPP_DIR}/grammar.y
        DEPENDS ${GHIDRA_CPP_DIR}/grammar.y
        COMMENT "[ghidra] bison grammar.y"
        VERBATIM
    )
    add_custom_command(
        OUTPUT ${GHIDRA_GEN_DIR}/pcodeparse.cc
        COMMAND ${BISON_EXECUTABLE} -l -o ${GHIDRA_GEN_DIR}/pcodeparse.cc ${GHIDRA_CPP_DIR}/pcodeparse.y
        DEPENDS ${GHIDRA_CPP_DIR}/pcodeparse.y
        COMMENT "[ghidra] bison pcodeparse.y"
        VERBATIM
    )
    add_custom_command(
        OUTPUT ${GHIDRA_GEN_DIR}/slghparse.cc ${GHIDRA_GEN_DIR}/slghparse.hh
        COMMAND ${BISON_EXECUTABLE} -l -d -o ${GHIDRA_GEN_DIR}/slghparse.cc ${GHIDRA_CPP_DIR}/slghparse.y
        DEPENDS ${GHIDRA_CPP_DIR}/slghparse.y
        COMMENT "[ghidra] bison slghparse.y"
        VERBATIM
    )
    add_custom_command(
        OUTPUT ${GHIDRA_GEN_DIR}/slghscan.cc
        COMMAND ${FLEX_EXECUTABLE} -L -o${GHIDRA_GEN_DIR}/slghscan.cc ${GHIDRA_CPP_DIR}/slghscan.l
        DEPENDS ${GHIDRA_CPP_DIR}/slghscan.l ${GHIDRA_GEN_DIR}/slghparse.hh
        COMMENT "[ghidra] flex slghscan.l"
        VERBATIM
    )
else()
    message(STATUS "[ghidra] bison/flex not found — using prebuilt_gen sources")
    foreach(_f xml.cc grammar.cc pcodeparse.cc slghparse.cc slghparse.hh slghscan.cc)
        configure_file(${GHIDRA_PREBUILT_DIR}/${_f} ${GHIDRA_GEN_DIR}/${_f} COPYONLY)
    endforeach()
endif()

# ── Source partitions (mirrors cpp/Makefile) ────────────────────────────────
set(_GEN_NAMES xml grammar pcodeparse slghparse slghscan)

# Resolves a list of bare names ("xml" "address") to absolute .cc paths,
# routing generated files to GHIDRA_GEN_DIR.
function(ghidra_resolve_srcs out_var)
    set(_paths "")
    foreach(name IN LISTS ARGN)
        list(FIND _GEN_NAMES ${name} _is_gen)
        if(_is_gen GREATER -1)
            list(APPEND _paths ${GHIDRA_GEN_DIR}/${name}.cc)
        else()
            list(APPEND _paths ${GHIDRA_CPP_DIR}/${name}.cc)
        endif()
    endforeach()
    set(${out_var} ${_paths} PARENT_SCOPE)
endfunction()

ghidra_resolve_srcs(_core_paths
    xml marshal space float address pcoderaw translate opcodes globalcontext
)
ghidra_resolve_srcs(_deccore_paths
    capability architecture options graph cover block cast typeop database cpool
    comment stringmanage modelrules fspec action loadimage grammar varnode op type
    variable varmap jumptable emulate emulateutil flow userop expression multiprecision
    funcdata funcdata_block funcdata_op funcdata_varnode unionresolve pcodeinject
    heritage prefersplit rangeutil ruleaction subflow blockaction merge double
    transform constseq coreaction condexe override dynamic crc32 prettyprint
    printlanguage printc printjava memstate opbehavior paramid signature
)
ghidra_resolve_srcs(_sleigh_paths
    sleigh pcodeparse pcodecompile sleighbase slghsymbol
    slghpatexpress slghpattern semantics context slaformat compression filemanage
)
ghidra_resolve_srcs(_ghidra_paths
    ghidra_arch inject_ghidra ghidra_translate loadimage_ghidra
    typegrp_ghidra database_ghidra ghidra_context cpool_ghidra
    ghidra_process comment_ghidra string_ghidra signature_ghidra
)

# D-29A argv-mode addition: RawBinaryArchitecture + SleighArchitecture base
# + libdecomp startup helpers + AURA argv-mode entry. RawBinaryArchitecture
# uses RawLoadImage (already in _core_paths) and inherits from
# SleighArchitecture (sleigh_arch.cc — not pulled in by the legacy
# subprocess-mode path because ArchitectureGhidra inherits from Architecture
# directly, bypassing Sleigh*). libdecomp.cc provides startDecompilerLibrary.
# See plan §"argv 인자 사양 Fixation Amendment".
ghidra_resolve_srcs(_aura_argv_paths
    raw_arch sleigh_arch libdecomp inject_sleigh aura_argv_mode
)
ghidra_resolve_srcs(_slacomp_paths slgh_compile slghparse slghscan)

# Note on zlib: Ghidra vendors a subset of zlib in decompile/zlib/ but their Makefile
# also uses `-lz` (system zlib) — vendored subset omits crc32.c etc. We follow Ghidra's
# upstream pattern: link system libz, keep vendored headers (compression.cc references
# `../zlib/zlib.h` relative to cpp/ — resolves via filesystem to vendored header).

# ── aura-sleigh-compile (slgh_compile main, builds .sla from .slaspec) ──────
add_executable(aura-sleigh-compile
    ${_core_paths}
    ${_sleigh_paths}
    ${_slacomp_paths}
)
target_include_directories(aura-sleigh-compile PRIVATE ${GHIDRA_CPP_DIR} ${GHIDRA_GEN_DIR})
target_link_libraries(aura-sleigh-compile PRIVATE z)
target_compile_features(aura-sleigh-compile PRIVATE cxx_std_11)
target_compile_options(aura-sleigh-compile PRIVATE -w)

# ── aura-decompile (ghidra_process main, production XML subprocess) ─────────
add_executable(aura-decompile
    ${_core_paths}
    ${_deccore_paths}
    ${_sleigh_paths}
    ${_ghidra_paths}
    ${_aura_argv_paths}
)
target_include_directories(aura-decompile PRIVATE ${GHIDRA_CPP_DIR} ${GHIDRA_GEN_DIR})
target_link_libraries(aura-decompile PRIVATE z)
target_compile_features(aura-decompile PRIVATE cxx_std_11)
target_compile_options(aura-decompile PRIVATE -w)
# D-29A Step 0.1: select XmlEncode (tinyxml2-friendly) over PackedEncode
# for stdout encoding. The two encoder sites in ghidra_process.cc are
# guarded by `#ifdef AURA_USE_XML_OUT`; toggling this define is the
# only entry point for the swap. zero-conflict with upstream merges.
target_compile_definitions(aura-decompile PRIVATE AURA_USE_XML_OUT=1)
# D-29A implementation turn #2: enable argv one-shot mode in main(). When
# argv contains --decompile / --help / --version, dispatch to
# aura_argv_mode_entry instead of the legacy subprocess loop. Legacy path
# preserved for Ghidra Java client compatibility. Toggling this define
# is the only entry point for the swap. Zero-conflict with upstream.
target_compile_definitions(aura-decompile PRIVATE AURA_ARGV_MODE=1)

# ── .sla generation: x86-64 (Phase 0 minimum) ───────────────────────────────
set(GHIDRA_PROC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/processors)
set(GHIDRA_SLA_DIR ${CMAKE_CURRENT_BINARY_DIR}/sla)
file(MAKE_DIRECTORY ${GHIDRA_SLA_DIR})

# slgh_compile invocation: <slaspec_input> <sla_output>
add_custom_command(
    OUTPUT ${GHIDRA_SLA_DIR}/x86-64.sla
    COMMAND $<TARGET_FILE:aura-sleigh-compile>
            ${GHIDRA_PROC_DIR}/x86/languages/x86-64.slaspec
            ${GHIDRA_SLA_DIR}/x86-64.sla
    DEPENDS aura-sleigh-compile
            ${GHIDRA_PROC_DIR}/x86/languages/x86-64.slaspec
    COMMENT "[ghidra] sleigh-compile x86-64.sla"
    VERBATIM
)

# D-29A: AARCH64.sla added to enable argv-mode smoke on aarch64 host
# (D-27 baseline only built x86-64). Cross-arch decompile via --arch
# override remains supported for x86-64 targets.
add_custom_command(
    OUTPUT ${GHIDRA_SLA_DIR}/AARCH64.sla
    COMMAND $<TARGET_FILE:aura-sleigh-compile>
            ${GHIDRA_PROC_DIR}/AARCH64/languages/AARCH64.slaspec
            ${GHIDRA_SLA_DIR}/AARCH64.sla
    DEPENDS aura-sleigh-compile
            ${GHIDRA_PROC_DIR}/AARCH64/languages/AARCH64.slaspec
    COMMENT "[ghidra] sleigh-compile AARCH64.sla"
    VERBATIM
)

add_custom_target(aura_sla_files ALL
    DEPENDS ${GHIDRA_SLA_DIR}/x86-64.sla
            ${GHIDRA_SLA_DIR}/AARCH64.sla
)

# Expose .sla output dir for downstream tests
set_property(TARGET aura-decompile PROPERTY AURA_SLA_DIR ${GHIDRA_SLA_DIR})
