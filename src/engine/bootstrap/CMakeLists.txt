# src/engine/bootstrap — Phase 2.5 §1.6/§1.7
# Engine bootstrap orchestration. The classify layer is pure logic
# (no fetch, no filesystem) so it links into both the Bootstrap
# Manager and the Consent gate without dragging network deps.

add_library(aura_engine_bootstrap STATIC
    bootstrap_classify.c
    bootstrap_manager.c
)
target_include_directories(aura_engine_bootstrap PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(aura_engine_bootstrap PUBLIC aura_engine_consent)
target_compile_features(aura_engine_bootstrap PRIVATE c_std_11)
