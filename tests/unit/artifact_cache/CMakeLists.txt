add_executable(artifact_cache_unit artifact_cache_unit.cpp)
target_include_directories(artifact_cache_unit PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/third_party/doctest
)
target_link_libraries(artifact_cache_unit PRIVATE aura_core sqlite3)
target_compile_features(artifact_cache_unit PRIVATE cxx_std_17)

add_test(NAME artifact_cache_unit COMMAND artifact_cache_unit)
set_tests_properties(artifact_cache_unit PROPERTIES
    LABELS "unit;cache"
    TIMEOUT 30
)
