# 01 — `AuraStrBuf` text buffer 도입

**Status**: closed (2026-05-03)
**Depends on**: —
**PRD**: `.scratch/platform-coverage/PRD.md`
**Audit ref**: `.scratch/phase-1-4-audit/issues/02-msvc-open-memstream-incomplete.md`
**Design grilling**: 2026-05-03 세션, 9 결정 합의 (Q1~Q9)
**Closing commits**: `87b1e232` (TC-1) · `59287353` (TC-2/3/5) · `8bcc56fe` (TC-4/6/7/10/11) · `7e5b1ca0` (TC-8/9)

## 배경

선행 점검에서 `open_memstream` 의 MSVC 부재가 Phase 4 GREEN baseline 무효화의 직접 원인으로 식별. 단순 호환 래퍼(`tmpfile()` 백킹) 대신, **AURA 의 외부 엔진 오케스트레이션 정체성에 부합하는 자체 메모리 버퍼**로 추상 갈아치움.

대안 검토 끝에 결정: **memstream 호환 래퍼 X / 자체 `AuraStrBuf` 자료구조 채택**. OS 의존 0, R-9 정합, macOS Tier 3 미래 안전, LLM streaming 응답 그릇 재사용 가능.

## 설계 합의 (9결정)

| # | 결정 사안 | 채택안 |
|---|---|---|
| Q1 | 추상 형태 | 자체 `AuraStrBuf` 자료구조 |
| Q2 | 메모리 모델 | 스택 할당 + transparent struct |
| Q3 | 에러 처리 | Sticky error flag (OOM 후 silently no-op, 끝에서 1회 체크) |
| Q4 | 성장 정책 | lazy init 256 byte → ×2 + `init_capacity` 옵션 |
| Q5 | detach 시맨틱 | zero state 리셋 + 재사용 가능 |
| Q6 | C/C++ 호환 | 단일 헤더 + inline RAII class (`aura::StrBuf`) |
| Q7 | Thread safety | 보장 안 함. **per-thread instance + detach hand-off 패턴만 공식 지원**. shared mutable 필요 시 future `AuraStrBufTs` opt-in (현재 미도입, YAGNI) |
| Q8 | 헤더 경로 | `include/aura/aura_io.h` (Phase 3+ 컨벤션) |
| Q9 | 첫 RED | TC-1 minimal lifecycle smoke |

## 인터페이스

```c
/* include/aura/aura_io.h */
typedef struct {
    char  *data;
    size_t len;
    size_t cap;
    int    err;          /* 0 = ok, -1 = OOM (sticky) */
} AuraStrBuf;

#define AURA_STRBUF_INIT  {NULL, 0, 0, 0}

/* C API */
void  aura_strbuf_init          (AuraStrBuf *sb);
void  aura_strbuf_init_capacity (AuraStrBuf *sb, size_t initial_cap);
void  aura_strbuf_printf        (AuraStrBuf *sb, const char *fmt, ...);
void  aura_strbuf_vprintf       (AuraStrBuf *sb, const char *fmt, va_list ap);
void  aura_strbuf_append        (AuraStrBuf *sb, const char *data, size_t n);
char *aura_strbuf_detach        (AuraStrBuf *sb, size_t *out_len);
void  aura_strbuf_free          (AuraStrBuf *sb);
int   aura_strbuf_status        (const AuraStrBuf *sb);

/* C++ RAII wrapper — same header, #ifdef __cplusplus 영역 */
namespace aura { class StrBuf { /* ~30 lines inline forwarding + dtor */ }; }
```

## DoD

- [x] `include/aura/aura_io.h` 신규 (C API + inline C++ RAII wrapper) — 145 LOC
- [x] `src/core/aura_io.c` 신규 (구현) — 145 LOC
- [x] `tests/core/test_aura_io.c` 신규 (TC-1~11) — 11/11 GREEN
- [x] CMake 등록 (`AURA_CORE_SOURCES` + `add_executable test_aura_io` label `core;phase9`)
- [x] MSVC 빌드 시 test_aura_io 단독 컴파일·링크 GREEN (실측: 본 호스트 Windows MSVC 11/11)
- [ ] Linux ctest GREEN — 후속 (코드 경로 동일, Tier 1 Linux runner 도입 후 정식 검증)
- [x] doc-comment 에 thread safety 정책 명문화 (per-thread + hand-off 패턴)
- [ ] TC-12 OOM sticky err — alloc fault inject 인프라 별도 작업으로 분리
- [ ] TC-13/14 C++ RAII destructor + move — issue 04 (GUI 마이그레이션) 진행 시 함께 검증

## TDD 사이클 (TC 순서)

| # | 테스트 | 검증 결정 |
|---|---|---|
| TC-1 | basic_lifecycle | Q1·Q2·Q3·Q4·Q5 (tracer bullet) |
| TC-2 | empty_detach (no printf) | edge case |
| TC-3 | multiple_printf_accumulates | Q4 cap growth |
| TC-4 | growth_across_256_boundary | Q4 first realloc |
| TC-5 | detach_reset_then_reuse | Q5 reusable |
| TC-6 | free_idempotent | safety |
| TC-7 | null_sb_safety (cJSON-style) | Q3 sticky no-op |
| TC-8 | long_string_multi_realloc | Q4 amortized growth |
| TC-9 | vprintf_forwarding | Q6 va_list |
| TC-10 | status_getter | Q3 |
| TC-11 | init_capacity_avoids_first_realloc | Q4 옵션 |
| TC-12 | oom_sets_sticky_err (alloc fault inject) | Q3 (별도 빌드 plumbing) |
| TC-13 | cpp_raii_destructor | Q6 |
| TC-14 | cpp_raii_move_semantics | Q6 |

각 TC 는 vertical slice. RED → 최소 구현 → GREEN → 다음 TC.

## 제약 / 비-목표

- `open_memstream` 호환 인터페이스 (`FILE *` 반환) **미제공** — 의도된 단절
- Thread-safe variant **미제공** — 시나리오 1 (per-thread + hand-off) 만 공식 지원
- arena/pool allocator 통합 **미제공** — pure malloc/realloc/free
- shrink_to_fit 정책: detach 시 자동 shrink (정확히 `len+1`), 그 외 시점에는 자동 안 함

## 후속 issue 영향

- **02** (hir_emit.c 마이그레이션): `aura_emit_memstream_*` static 함수 삭제 → `aura_strbuf_*` 호출로 교체. 3 callsite.
- **03** (tests/decompiler/* 마이그레이션): 15 callsite 의 `open_memstream` → `aura_strbuf_*`. 호출 형태 변경 (FILE* → AuraStrBuf*).
- **04** (GUI 마이그레이션): 2 callsite (file_loader.cpp, main_window.cpp) — `aura::StrBuf` RAII wrapper 사용 권장.
