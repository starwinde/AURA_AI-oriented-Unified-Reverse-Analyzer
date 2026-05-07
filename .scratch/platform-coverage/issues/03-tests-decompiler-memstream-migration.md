# 03a — `tests/decompiler/*` ir/hir_emit_pseudoc 콜사이트 마이그레이션

**Status**: closed (2026-05-03)
**Depends on**: 01
**Closing commit**: `585be690`
**Spawned**: issue 03b (dwarf/pdb/exc/sr 마이그레이션)

## 재명세 (실제 진행 내용)

PRD 추정 28건은 모든 tests/ 합계, 본 이슈는 tests/decompiler/ 한정. 실측 27 callsite / 8 emit API. 이번 03a 는 그중 ir_emit_pseudoc / hir_emit_pseudoc 13 callsite 만 처리:

| 분류 | 카운트 | 처리 |
|---|---|---|
| `ir_emit_pseudoc` + `open_memstream` | 10 | `ir_emit_pseudoc_with_strbuf` 신규 |
| `ir_emit_pseudoc` + `fmemopen` | 2 | 동상 |
| `hir_emit_pseudoc` + `open_memstream` | 2 | `hir_emit_pseudoc_with_positions` 직행 |
| **합계 (03a)** | **14** | (1 callsite 중복 매치 보정 후 13 실제 치환) |

> **참고**: 명세 시점 통계(15)는 grep 가산 그대로. 실제 `open_memstream(/fmemopen(` 호출 13건.

## DoD (03a)

- [x] 9 파일 (test_arm64_decompile / test_const_prop / test_dead_code / test_eh_flow_consumer / test_mmx_types / test_multi_arch / test_struct_array_emit / test_type_inference / test_vector_types) 의 open_memstream/fmemopen 0건
- [x] `ir_emit_pseudoc_with_strbuf(IrFunc*, AuraStrBuf*)` 신규 (codegen.c, decompiler.h)
- [x] 기존 `ir_emit_pseudoc(FILE*)` 본체/동작 무수정
- [x] Linux ctest: 22 03a-related test GREEN
- [x] MSVC build-rel: 11/12 03a-target 빌드 성공 (1 실패는 pre-existing issue 05 weak-symbol)

## 03b 스폰 — 잔여 14 callsite / 4 파일 / 4 emit API

| 파일 | callsites | emit API |
|---|---|---|
| test_dwarf_types.c | 4 | `dwarf_emit_types`, `dwarf_emit_enriched` |
| test_pdb_types.c | 4 | `pdb_emit_types`, `pdb_emit_enriched` |
| test_exception_flow.c | 3 | `exc_flow_emit` |
| test_struct_recovery.c | 1 | `sr_emit_typedefs` |

각 emit API 마다 `_with_strbuf` thin adapter 추가 + callsite 치환 필요. 별도 issue 03b 진행.

## 비고

`ir_emit_pseudoc_with_strbuf` 의 내부 구현은 `tmpfile() + fread + aura_strbuf_append`. issue 01 의 "memstream 호환 래퍼 X" 결정은 production emit core (hir_emit) 의 추상에 적용되며, FILE*-only API 를 AuraStrBuf 로 감싸는 test-friendly 어댑터에는 적용되지 않음. tmpfile() 은 C89 portable.

## 영향 파일 + callsite 수

| 파일 | callsites |
|---|---|
| tests/decompiler/test_arm64_decompile.c | 1 |
| tests/decompiler/test_eh_flow_consumer.c | 1 |
| tests/decompiler/test_mmx_types.c | 1 |
| tests/decompiler/test_multi_arch.c | 3 |
| tests/decompiler/test_struct_array_emit.c | 1 |
| tests/decompiler/test_type_inference.c | 6 |
| tests/decompiler/test_vector_types.c | 2 |
| **합계** | **15** (실측 — `grep -rn "open_memstream" tests/decompiler/` 결과 기준) |

> 주의: PRD 추정치(28)는 모든 tests/ 합계. 이 issue는 tests/decompiler/ 만. 잔여 callsite는 `grep`으로 재집계 필요.

## DoD

- [ ] 위 파일들의 모든 `open_memstream(&buf, &len)` 호출을 `aura_io_memstream_open(&buf, &len)` 으로 교체
- [ ] 각 파일의 대응 `fclose(mem)` → `aura_io_memstream_close(mem, &buf, &len)` 교체
- [ ] `#include "aura/aura_io.h"` 추가
- [ ] Linux ctest 회귀 0 (해당 테스트들 모두 GREEN 유지)
- [ ] MSVC 빌드 시 해당 vcxproj 들 모두 LNK 에러 0

## 검증 방법

```
grep -rn "open_memstream" tests/decompiler/ | wc -l   # 0이어야 함 (모두 마이그레이션 완료)
```

## 비고

순수 mechanical 변환. 의미론 차이 (tmpfile vs memstream) 가 어떤 테스트의 fflush+buf 검사 패턴에 영향을 주는지 별도 점검 필요. 발견 시 새 issue 로 spawn.
