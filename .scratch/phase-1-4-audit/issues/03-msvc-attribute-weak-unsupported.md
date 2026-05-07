# 03 — MSVC `__attribute__((weak))` 미지원

**Status**: needs-triage
**Severity**: CRITICAL (Windows MSVC 빌드 차단)
**Phase impact**: Phase 1+2 일부 테스트 (weak stub 의존하는 narrow symbolic tests)

## 증상

```
tests/stubs/analyzer_init_stubs.c(29,1): error C2143: 구문 오류: ')'이(가) '(' 앞에 없습니다.
... (16개 함수에 대해 동일 패턴 반복)
```

## 위치

`tests/stubs/analyzer_init_stubs.c` L27~45:

```c
#define WEAK_STUB __attribute__((weak))   // ← GCC/Clang 전용

WEAK_STUB void aarch64_plt_thunks_init(void)    {}
WEAK_STUB void addr_tables_init(void)           {}
WEAK_STUB void call_fixup_init(void)            {}
WEAK_STUB void const_refs_init(void)            {}
WEAK_STUB void elf_scalar_refs_init(void)       {}
WEAK_STUB void embedded_media_init(void)        {}
WEAK_STUB void data_archive_init(void)          {}
WEAK_STUB void entry_points_init(void)          {}
WEAK_STUB void extern_entry_refs_init(void)     {}
WEAK_STUB void extern_resolver_init(void)       {}
WEAK_STUB void func_id_init(void)               {}
WEAK_STUB void func_start_after_code_init(void) {}
WEAK_STUB void func_start_after_data_init(void) {}
WEAK_STUB void param_id_init(void)              {}
WEAK_STUB void shared_return_init(void)         {}
WEAK_STUB void subroutine_refs_init(void)       {}
```

## 영향

`bench_pipeline.vcxproj` 등 weak stub 링크 대상 vcxproj 모두 빌드 fail.

## MSVC 등가물

`__attribute__((weak))` 은 GCC/Clang 의 weak symbol 어트리뷰트. MSVC에서:

| 옵션 | 방법 | 비고 |
|---|---|---|
| A | `__declspec(selectany)` (전역 변수만) | 함수에는 부적합 |
| B | `#pragma comment(linker, "/alternatename:weak=strong")` | 컴파일러별 분기 필요 |
| C | strong stub + `#ifdef`로 production 빌드에서 제외 | 제일 직관적 |
| D | static 라이브러리 분리 + 링크 순서 제어 | 현재 구조 변경 필요 |

## Phase 2A 재점검 로그에 이미 인지

`Tasks.md` Phase 2A.11 status note (L84~92):
> Windows MSVC 인프라 결함 (Phase 2A 범위 외, 별도 작업으로 분리):
>   - 추가 발견: GCC 전용 `__attribute__((aligned(64)))` (file_format.h),
>     `unistd.h` 직접 include (decompile_metrics, decompile_all, mapped_file,
>     engine_subprocess 외 5+ 파일), `__attribute__((unused/noreturn))` 다수.

→ **이미 알려진 결함**. 그러나 처리 미진행. Phase 4 진입 후에도 누적.

## 제안 처리

`include/aura_compat.h`에 `WEAK_STUB` 매크로 정의 (`#ifdef _MSC_VER` 분기) → 현재 `aura_compat.h` 의 패턴과 일관.

**ready-for-agent** (단순 매크로 정의 + 분기).

## 관련 issue

- 02 (`open_memstream`)
- 05 (Phase 2A note에 인지된 미처리 사항)
