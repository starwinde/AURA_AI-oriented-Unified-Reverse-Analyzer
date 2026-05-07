add_executable(safety_unit safety_unit.cpp)
target_include_directories(safety_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/cjson
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(safety_unit PRIVATE aura_core cjson)
target_compile_features(safety_unit PRIVATE cxx_std_17)

add_test(NAME safety_unit COMMAND safety_unit)
set_tests_properties(safety_unit PROPERTIES LABELS "unit;safety")

find_package(Python3 COMPONENTS Interpreter QUIET)
if(Python3_FOUND)
    add_test(
        NAME pii_runner_protocol
        COMMAND ${Python3_EXECUTABLE}
                ${CMAKE_SOURCE_DIR}/tests/unit/safety/test_pii_runner_protocol.py
                ${CMAKE_SOURCE_DIR}/tools/pii-runner/aura_pii_runner.py
    )
    set_tests_properties(pii_runner_protocol PROPERTIES
        LABELS "unit;safety;pii-runner"
        TIMEOUT 10
    )
endif()
