# 05 — `aura_compat.h` 에 WEAK_STUB 매크로 분기

**Status**: ready-for-agent
**Depends on**: —
**Audit ref**: `.scratch/phase-1-4-audit/issues/03-msvc-attribute-weak-unsupported.md`

## 목표

`__attribute__((weak))` 의 MSVC 등가물을 `aura_compat.h` 에 매크로로 정의하여 `tests/stubs/analyzer_init_stubs.c` 가 양 컴파일러에서 빌드되도록 한다.

## 인터페이스

```c
/* include/aura_compat.h */
#ifdef _MSC_VER
#  define AURA_WEAK __pragma(comment(linker, "/alternatename:_<sym>=_<strong>"))  /* per-symbol */
   /* or */
#  define AURA_WEAK   /* no-op; rely on strong stubs only */
#else
#  define AURA_WEAK __attribute__((weak))
#endif
```

## 두 후보

### A. **per-symbol /alternatename** (정확하지만 복잡)
- 각 weak symbol마다 `#pragma comment(linker, ...)` 발행
- 매크로 인자로 심볼 이름 받음

### B. **no-op + strong stub default** (단순)
- MSVC에서는 weak attribute 무시
- weak가 의도하던 "production override 가능" 의미는 별도 link order로 보장
- analyzer_init_stubs.c 의 strong override 가 link 순서 보장만 되면 작동

## 권장: B (단순). production 빌드는 stub 미링크, narrow symbolic test 만 stub 사용 → 충돌 없음.

## DoD

- [ ] `include/aura_compat.h` 에 `AURA_WEAK` 매크로 정의
- [ ] `tests/stubs/analyzer_init_stubs.c` L27 의 `#define WEAK_STUB __attribute__((weak))` → `#define WEAK_STUB AURA_WEAK`
- [ ] Linux 빌드 회귀 0 (weak 의미론 보존)
- [ ] MSVC 빌드 시 bench_pipeline.vcxproj 등 분석기 stub 의존 vcxproj 들 컴파일 GREEN
- [ ] 회귀 테스트: production 빌드에서 strong override가 weak stub을 가리는지 확인 (Linux only — MSVC는 stub 별도 작동만 검증)
