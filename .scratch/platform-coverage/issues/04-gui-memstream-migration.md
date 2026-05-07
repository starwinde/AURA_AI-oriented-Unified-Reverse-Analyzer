# 04 — `src/gui/*` open_memstream callsite 마이그레이션 (2 callsites)

**Status**: ready-for-agent
**Depends on**: 01

## 영향

| 파일 | callsite 라인 |
|---|---|
| src/gui/main_window.cpp | 1583 |
| src/gui/file_loader.cpp | 392 |

## DoD

- [ ] 두 callsite 모두 `aura_io_memstream_open` / `aura_io_memstream_close` 로 교체
- [ ] `#include "aura/aura_io.h"` (C++에서 `extern "C"` 처리 확인)
- [ ] Qt6 빌드 GREEN (Linux + MSVC 양쪽)

## 비고

`aura_io.h` 가 C 헤더라면 `#ifdef __cplusplus extern "C" { ... }` 보호 필요. issue 01 헤더에서 미리 처리.

GUI 빌드는 `AURA_BUILD_GUI` 옵션 의존. 옵션 OFF 시 본 issue skip 가능.
