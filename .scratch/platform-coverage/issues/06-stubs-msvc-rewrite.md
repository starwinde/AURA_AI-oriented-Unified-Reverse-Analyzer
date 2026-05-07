# 06 — `tests/stubs/analyzer_init_stubs.c` MSVC 호환

**Status**: ready-for-agent
**Depends on**: 05

## DoD

- [ ] `WEAK_STUB` 매크로 정의를 `AURA_WEAK` (issue 05) 로 통일
- [ ] 16개 stub 함수 컴파일 GREEN (Linux + MSVC)
- [ ] 본 stub을 사용하는 vcxproj (bench_pipeline 등) 빌드 GREEN
- [ ] strong override 주입 시 stub이 가려지는지 회귀 테스트 (Linux)
