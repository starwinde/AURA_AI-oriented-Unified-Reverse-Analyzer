# src/gui/CMakeLists.txt — `aura-gui` Qt6 binary (Phase 11.3, ADR-0035).
#
# Built when AURA_BUILD_GUI is ON (default OFF — opt-in until CI runners
# install Qt6). Requires Qt6::Widgets via `find_package`.

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

set(AURA_GUI_SOURCES
    main.cpp
    main_window.cpp
    project_binary_model.cpp
    analysis_options_dialog.cpp
    function_table_model.cpp
    xref_table_model.cpp
    symbol_table_model.cpp
    string_table_model.cpp
    safety_settings_dialog.cpp
    code_syntax_highlighter.cpp
    demo_mode_pane.cpp
    gateway_pane.cpp
    decompile_pane.cpp
    disasm_pane.cpp
    full_disasm_pane.cpp
    disasm_flow_gutter.cpp
    cfg_pane.cpp
    hex_pane.cpp
    rpc_server.cpp
)

set(AURA_GUI_HEADERS
    main_window.h
    project_binary_model.h
    analysis_options_dialog.h
    function_table_model.h
    xref_table_model.h
    symbol_table_model.h
    string_table_model.h
    safety_settings_dialog.h
    code_syntax_highlighter.h
    demo_mode_pane.h
    gateway_pane.h
    decompile_pane.h
    disasm_pane.h
    full_disasm_pane.h
    disasm_flow_gutter.h
    cfg_pane.h
    hex_pane.h
    rpc_server.h
)

add_executable(aura-gui
    ${AURA_GUI_SOURCES}
    ${AURA_GUI_HEADERS}
)

target_include_directories(aura-gui PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/aura
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(aura-gui PRIVATE
    Qt6::Widgets
    Qt6::Network
    aura_core
    aura_engine_probe
    cjson
)

target_compile_features(aura-gui PRIVATE cxx_std_17)

install(TARGETS aura-gui RUNTIME DESTINATION bin)
