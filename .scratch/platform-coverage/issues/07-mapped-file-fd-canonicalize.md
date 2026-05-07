# 07 — `MappedFile.fd` 단일화 (G6 채택, G7 폐기)

**Status**: ready-for-agent
**Depends on**: —
**Audit ref**: `.scratch/phase-1-4-audit/issues/06-mapped-file-fd-contradiction.md`

## 목표

미커밋 DIFF에 공존하는 두 모순 접근 중 하나(**G6: 헤더 단일화**)만 채택, 나머지(**G7: 테스트 #ifndef 가드**) 폐기.

## 결정

**G6 채택 근거**:
- 헤더가 truth → 호출자 코드 간결
- `mapped_file.c` G8 (Windows에서 `mf->fd = -1` 초기화) 가 G6와 일관 → 작성자 의도가 G6 쪽
- 새 테스트 작성 시 #ifndef 가드 누락으로 인한 회귀 위험 0

## DoD

- [ ] `include/mapped_file.h` Windows 분기에 `int fd` 보존 (현 미커밋 DIFF 그대로)
- [ ] `tests/core/test_data_refs.c` L47 의 `#ifndef _WIN32 ... mf->fd = -1; ... #endif` 가드 제거
- [ ] `tests/parser/test_format_support.c` 5개 위치 (L143, L156, L175, L191, L201) `#ifndef _WIN32` 가드 모두 제거
- [ ] Linux + MSVC 양쪽 ctest 회귀 0 (특히 test_data_refs / test_format_support)
- [ ] `mapped_file.c` G8 fd=-1 초기화 보존
