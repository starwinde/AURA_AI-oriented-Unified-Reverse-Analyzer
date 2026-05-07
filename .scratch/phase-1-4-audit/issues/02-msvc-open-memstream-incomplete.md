# 02 — MSVC `open_memstream` 마이그레이션 미완성

**Status**: needs-triage
**Severity**: CRITICAL (Windows MSVC 빌드 차단)
**Phase impact**: 직접: Phase 4 GREEN baseline 무효화. 간접: Phase 1~3 MSVC 빌드 미검증.

## 증상

미커밋 DIFF의 `src/decompiler/hir_emit.c`가 `open_memstream` → `aura_emit_memstream_open` 래퍼로 마이그레이션 시작했으나 미완성:

```
test_vector_types.obj : error LNK2019: open_memstream
... 확인할 수 없는 외부 기호
test_vector_types.exe : fatal error LNK1120: 1개의 확인할 수 없는 외부 참조입니다.
```

## 범위 (실측)

```
$ grep -rn "open_memstream" tests/ src/
```

| 위치 | callsites | 마이그레이션? |
|---|---|---|
| `src/decompiler/hir_emit.c` | 3 | ✅ 완료 (DIFF) |
| `src/gui/main_window.cpp` | 1 | ❌ 미마이그레이션 |
| `src/gui/file_loader.cpp` | 1 | ❌ 미마이그레이션 |
| `tests/decompiler/test_arm64_decompile.c` | 1 | ❌ |
| `tests/decompiler/test_eh_flow_consumer.c` | 1 | ❌ |
| `tests/decompiler/test_mmx_types.c` | 1 | ❌ |
| `tests/decompiler/test_multi_arch.c` | 3 | ❌ |
| `tests/decompiler/test_struct_array_emit.c` | 1 | ❌ |
| `tests/decompiler/test_type_inference.c` | 6 | ❌ |
| `tests/decompiler/test_vector_types.c` | 2 | ❌ (← 빌드 fail 직접 원인) |
| **합계** | **20** | 3 / 20 |

## 구조적 결함

`aura_emit_memstream_open` / `aura_emit_memstream_close` 가 `hir_emit.c` 내부 `static` 함수로 정의됨 → **다른 모듈 사용 불가**. 공유 헤더(`include/aura_compat.h` 또는 신규 `include/aura_io.h`)로 추출하지 않음.

## 의미론 위험

MSVC 분기는 `tmpfile()` 사용:
- `open_memstream`: 메모리 백킹, `fflush` 후 buffer 즉시 갱신
- `tmpfile()`: 디스크 백킹, `fclose` 시 별도 read 필요

→ 링크 에러는 해소돼도 **runtime 의미론 차이**로 테스트 실패 가능.

## 제안 처리

| 단계 | 내용 |
|---|---|
| 1 | 헬퍼를 `include/aura_compat.h` (또는 신규 `aura_io.h`)로 추출 — 공유 가능 |
| 2 | `tests/CMakeLists.txt`의 `/FI"aura_compat.h"` 경로로 매크로 치환 또는 명시적 호출 마이그레이션 |
| 3 | GUI 파일 2개 별도 처리 (Qt6 빌드 컨텍스트) |
| 4 | tmpfile 의미론 검증 — 모든 callsite의 `fflush` + buf 검사 패턴 확인 |

이 작업은 **별도 작업 단위**로 분리해야 함 (B+X의 X 트리거는 아니지만 점검 baseline 외 대규모 변경). **ready-for-agent** (TDD 가능, 명세 명확).

## 관련 issue

- 03 (`__attribute__((weak))` MSVC 미지원)
- 04 (DIFF WIP 상태)
