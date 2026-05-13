add_executable(malware_risk_unit malware_risk_unit.cpp)
target_include_directories(malware_risk_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(malware_risk_unit PRIVATE aura_core)
target_compile_features(malware_risk_unit PRIVATE cxx_std_17)

add_test(NAME malware_risk_unit COMMAND malware_risk_unit)
set_tests_properties(malware_risk_unit PROPERTIES LABELS "unit;security")
