# tests/integration/gui_smoke — Phase 11.3 Slice G invariant gate.
# Built only when AURA_BUILD_GUI is ON (Qt6) and AURA_ENABLE_RIZIN is ON
# (analyze dispatch needs the Rizin reference engine). See ADR-0035.

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets Test REQUIRED)

add_executable(gui_smoke gui_smoke.cpp)
target_include_directories(gui_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/aura
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/gui
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(gui_smoke PRIVATE
    aura_core
    aura_engine_probe
    cjson
    Qt6::Widgets
    Qt6::Test
)

# Reuse MainWindow / models from src/gui without re-declaring them here.
target_sources(gui_smoke PRIVATE
    ${CMAKE_SOURCE_DIR}/src/gui/main_window.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/main_window.h
    ${CMAKE_SOURCE_DIR}/src/gui/project_binary_model.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/project_binary_model.h
    ${CMAKE_SOURCE_DIR}/src/gui/function_table_model.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/function_table_model.h
    ${CMAKE_SOURCE_DIR}/src/gui/xref_table_model.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/xref_table_model.h
    ${CMAKE_SOURCE_DIR}/src/gui/symbol_table_model.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/symbol_table_model.h
    ${CMAKE_SOURCE_DIR}/src/gui/string_table_model.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/string_table_model.h
    ${CMAKE_SOURCE_DIR}/src/gui/code_syntax_highlighter.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/code_syntax_highlighter.h
    ${CMAKE_SOURCE_DIR}/src/gui/analysis_options_dialog.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/analysis_options_dialog.h
    ${CMAKE_SOURCE_DIR}/src/gui/decompile_pane.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/decompile_pane.h
    ${CMAKE_SOURCE_DIR}/src/gui/disasm_pane.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/disasm_pane.h
    ${CMAKE_SOURCE_DIR}/src/gui/full_disasm_pane.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/full_disasm_pane.h
    ${CMAKE_SOURCE_DIR}/src/gui/disasm_flow_gutter.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/disasm_flow_gutter.h
    ${CMAKE_SOURCE_DIR}/src/gui/cfg_pane.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/cfg_pane.h
    ${CMAKE_SOURCE_DIR}/src/gui/hex_pane.cpp
    ${CMAKE_SOURCE_DIR}/src/gui/hex_pane.h
)

target_compile_features(gui_smoke PRIVATE cxx_std_17)

if(WIN32)
    set(_gui_rizin_bin "${CMAKE_SOURCE_DIR}/third_party/rizin/0.8.2/bin/rizin.exe")
else()
    set(_gui_rizin_bin "${CMAKE_SOURCE_DIR}/third_party/rizin/0.8.2/bin/rizin")
endif()
set(_gui_sleigh_home "${CMAKE_SOURCE_DIR}/third_party/rizin/0.8.2/lib/rizin/plugins/rz_ghidra_sleigh")

add_test(NAME gui_smoke COMMAND gui_smoke)
set_tests_properties(gui_smoke PROPERTIES
    LABELS "integration;gui;reference_engine"
    TIMEOUT 120
    ENVIRONMENT
        "AURA_REPO_ROOT=${CMAKE_SOURCE_DIR};AURA_RIZIN_BIN=${_gui_rizin_bin};SLEIGHHOME=${_gui_sleigh_home};QT_QPA_PLATFORM=offscreen"
)
