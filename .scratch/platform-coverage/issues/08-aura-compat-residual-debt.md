# 08 — aura_compat 잔여 부채 정리 (Phase 2A.11 식별 사항)

**Status**: needs-triage
**Depends on**: —
**Audit ref**: `.scratch/phase-1-4-audit/issues/05-known-msvc-debt-not-tracked.md`

## 배경

Tasks.md Phase 2A.11 status note (L84~92) + Phase 2 재점검 로그 (L207) 가 명시한 알려진 MSVC 부채:

- `__attribute__((aligned(64)))` (`file_format.h`) — 부분 fix 보존 (`AURA_FILEINFO_ALIGN` shim)
- `unistd.h` 직접 include — `decompile_metrics`, `decompile_all`, `mapped_file`, `engine_subprocess` 외 5+ 파일
- `__attribute__((unused/noreturn))` 다수
- YARA `sys/mman.h` (현재 `AURA_BUILD_YARA` 디폴트 OFF로 우회)
- `src/third_party_hub` include path 누락 (`rizin_to_aura.h`)

## DoD

- [ ] 각 항목 별로 해결 / wontfix 결정 (sub-issue 으로 spawn 가능)
- [ ] `__attribute__((unused))` → `AURA_UNUSED` 매크로 (`aura_compat.h`)
- [ ] `__attribute__((noreturn))` → `AURA_NORETURN` 매크로
- [ ] `__attribute__((aligned(N)))` → `AURA_ALIGNED(N)` 매크로 (file_format.h shim 일반화)
- [ ] `unistd.h` 직접 include 0건 (모두 `aura_compat.h` 또는 `aura_compat` 내부 분기)
- [ ] YARA: 별도 issue (Tier 1 정책 영향 평가 후)

## 비고

본 issue는 **scope creep 경향**이 있음. 5+ 파일을 한 번에 잡으려 하지 말고, 각 매크로 도입을 별도 sub-issue 로 분해.

triage 단계 — 우선순위 결정 필요.
