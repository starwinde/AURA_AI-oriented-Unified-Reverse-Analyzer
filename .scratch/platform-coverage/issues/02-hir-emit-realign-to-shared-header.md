# 02 — `hir_emit.c` 마이그레이션 → AuraStrBuf

**Status**: closed (2026-05-03)
**Depends on**: 01
**PRD**: `.scratch/platform-coverage/PRD.md`
**Closing commits**: `fcf647a2` (RED locks) · `5ca982ed` (migration)

## 목표 (재명세)

issue 01 의 `aura_io_memstream_*` (FILE*-returning) 전제는 폐기. issue 01 design grilling 결과 `AuraStrBuf` (append-only struct, sticky-err, FILE* 단절) 가 정식 추상으로 채택되었으므로, 본 이슈는 `src/decompiler/hir_emit.c` 의 emit 경로를 그 추상으로 전환한다.

## 실제 surgery

`hir_emit.c` 의 FILE* 의존이 3 callsite 를 넘어 emit_* call graph 전체에 분포 (104 `fprintf(out,)`, 2 `fwrite(...,out)`, 3 `ftell(out)`). 따라서 다음 6 함수의 시그니처를 `FILE*` → `AuraStrBuf*` 로 전환:

- `emit_indent`, `emit_int_literal`, `try_emit_stack_var`, `emit_expr`, `emit_stmt`, `emit_local_decls`

공개 API 는 외부 contract 유지:

- `hir_emit_pseudoc(FILE *out)` — 내부 AuraStrBuf 모은 후 `fwrite(sb.data, 1, sb.len, out)` 로 어댑터 처리. fwrite 실패 → `AURA_ERR_IO`.
- `hir_emit_pseudoc_with_positions(char **out_buf)` — 내부 AuraStrBuf → `aura_strbuf_detach()` 로 caller-owned malloc'd char* 인계.

양 공개 API 는 신설 `emit_pseudoc_into(AuraStrBuf *)` helper 를 통해 단일 emit 경로로 합류. `ftell(out)` → `(long)out->len` 치환은 append-only 스트림에서 byte-exact 동등.

## DoD

- [x] `static aura_emit_memstream_open/close` 정의 삭제 (구 L31~85)
- [x] memstream open/close 콜사이트 (3 open / 1 close) 모두 제거 — emit_pseudoc_into 가 단일 AuraStrBuf 로 흡수
- [x] `#include "aura/aura_io.h"` 추가
- [x] Linux ctest 회귀 0 — hir_emit 관련 16 테스트 + decompiler 라벨 9 테스트 전부 GREEN
- [x] Slice 1 RED-lock (`test_hir_emit_strbuf_migration`) GREEN
- [x] Slice 2 RED-lock (`test_hir_emit_positions_strbuf_migration`) GREEN
- [ ] MSVC 빌드 시 hir_emit.obj 컴파일 GREEN — issue 09 (Windows MSVC CI runner) 로 이연

## 회귀 net

| 분류 | 결과 |
|---|---|
| Slice 1 byte-equiv lock (3 fixture + cross-API consistency) | GREEN |
| Slice 2 positions lock (pinned offsets + splice rebase invariant) | GREEN |
| `test_hir_emit*`, `test_hir_emission_stats`, `test_eh_flow_*`, `test_struct_array_emit`, `test_roundtrip`, `test_hir_no_*`, `test_hir_struct_typedef`, `test_hir_stack_*`, `test_aura_io` | 16/16 GREEN |
| `ctest -L decompiler` | 9/9 GREEN |
| `ctest` 전체 | 1 환경 실패 (`test_decompile_all_sh`: jq 미설치 — pre-existing, 마이그레이션 무관) |
| `test_real_binary_smoke.sh` | skip — `build-rel/aura` (MSVC) 하드코드, issue 09 영역 |

## 비고

미커밋 G4 DIFF (tmpfile() 기반 MSVC fallback) 는 본 마이그레이션이 흡수 후 삭제. 별도 보존 commit 미작성 — issue 01 의 "FILE* 단절" 정책과 정합.

CMake side: 6개 hand-rolled test target (test_pipeline / bench_pipeline / test_4T_symbolic / test_struct_array_emit / test_hir_emit / 또 1) 이 hir_emit.c 를 standalone 으로 컴파일하면서 aura_core 를 링크하지 않으므로, 각 SOURCES 목록에 `src/core/aura_io.c` 동봉.
