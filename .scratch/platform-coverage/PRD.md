# Platform Coverage — PRD

**작성일**: 2026-05-03
**Owner**: 사용자 결정 (2026-05-03)
**관련 결정**: ADR-0030 (Tier Platform Policy)

---

## 배경 (Why)

Phase 1~4 재점검 (`.scratch/phase-1-4-audit/summary.md`) 에서 다음이 드러남:

1. **Phase 1~4 구현 자체는 견고** — Tasks.md의 75개 sub-step claim 모두 코드/테스트/명세 일치 (Linux WSL 환경 가정).
2. **Windows MSVC 빌드는 RED**:
   - `open_memstream` 부재 → 30 callsite 미마이그레이션 (audit issue 02)
   - `__attribute__((weak))` MSVC 미지원 → `bench_pipeline.vcxproj` 등 빌드 fail (audit issue 03)
   - `MappedFile.fd` 처리에 두 모순 접근 공존 (audit issue 06)
3. **알려진 부채가 추적 시스템에 등재되지 않음** — Tasks.md Phase 2A.11/Phase 2 재점검 로그에 "별도 작업으로 분리"라 기록됐으나 이후 트래킹 누락 (audit issue 05).
4. **macOS는 Mac 하드웨어/CI 부재로 검증 불가** — Linux 호환성 80~90%이나 Mach-O 파서, 16KB page size, case-insensitive FS 등 Mac-specific 위험 다수.

## 목표 (What)

**3-Tier 플랫폼 정책을 명문화하고, Tier 1 양대 환경(Linux WSL + Windows MSVC) 모두 매 PR GREEN을 강제**한다.

| Tier | OS | 정의 | 매 PR 요구 |
|------|-----|------|-------------|
| 1 | Linux WSL (Ubuntu 24.04) | Verified — 매 PR ctest GREEN 강제 | 빌드 + ctest GREEN |
| 1 | Windows MSVC | Verified — 매 PR ctest GREEN 강제 | 빌드 + ctest GREEN |
| 3 | macOS | Best-effort, unverified — 코드는 portable 작성, 검증은 Mac 확보 후 | 없음 (코드 portability만) |

> Tier 2 (CI-verified, e2e exempt) 등급은 도입 시점에 재정의 가능하도록 예약. 현재는 1·3만 사용.

---

## DoD (Definition of Done)

### Tier 1 Windows MSVC GREEN 도달

- [ ] `open_memstream` 30+ callsite 모두 공유 헬퍼 (`include/aura_compat.h` 또는 신규 `aura_io.h`) 로 마이그레이션
- [ ] `__attribute__((weak))` 사용처가 MSVC 분기에서 컴파일 가능 (WEAK_STUB 매크로 또는 strong + #ifdef)
- [ ] `MappedFile.fd` 처리 단일 표준 채택 (G6 또는 G7, 한쪽 폐기)
- [ ] `cmake --build build-rel --config Release` 0 error, 0 warning-as-error
- [ ] `ctest --test-dir build-rel` 전체 GREEN (rizin/ghidra capability-gated SKIP은 허용)

### CI 인프라

- [ ] Windows MSVC runner 도입 (GitHub Actions windows-latest 또는 self-hosted)
- [ ] Linux WSL runner 매 PR 실행 보장
- [ ] PR 머지 게이트: 양 Tier 1 환경 모두 GREEN 강제

### 문서/추적

- [ ] ADR-0030 `Tier Platform Policy` 작성 (이 PRD의 결정 근거)
- [ ] `CLAUDE.md` §지원 플랫폼 추가
- [ ] `PRD.md` D-30 entry (ADR 포인터)
- [ ] `rules.md` §1 Tier 1 enforcement 명문화
- [ ] `Tasks.md` Phase 9 등재
- [ ] 본 PRD의 issues/* 모두 close (resolved 또는 wontfix)

---

## 비범위 (Out of Scope)

- **macOS 검증** — Mac 하드웨어/CI 확보 시점에 별도 PRD
- **신규 기능** — 기존 동작 유지 + 플랫폼 호환성만
- **3rd-party 의존성 변경** — `third_party/` 미접촉. SQLite/Capstone/Rizin/cJSON 등 그대로
- **성능 최적화** — Phase 8 영역
- **GUI Qt6 macOS 빌드** — Phase 5 영역

## 위험

| 위험 | 완화 |
|---|---|
| `tmpfile()` 의 디스크 백킹이 `open_memstream` 메모리 백킹과 의미론 차이 | 각 callsite에서 `fflush` + buf 검사 패턴 점검 |
| MSVC 16KB page size 가정 (Apple Silicon 대비) | 본 PRD에서는 무관 (Tier 3) |
| Windows CI runner 비용 | GitHub Actions windows-latest = 무료 quota 활용 |

## 참조

- `.scratch/phase-1-4-audit/summary.md` (선행 점검)
- `.scratch/phase-1-4-audit/issues/02-msvc-open-memstream-incomplete.md`
- `.scratch/phase-1-4-audit/issues/03-msvc-attribute-weak-unsupported.md`
- `.scratch/phase-1-4-audit/issues/05-known-msvc-debt-not-tracked.md`
- `.scratch/phase-1-4-audit/issues/06-mapped-file-fd-contradiction.md`
- Tasks.md Phase 2A.11 (L84~92), Phase 2 재점검 로그 (L207)

---

## Issue 분해

본 PRD는 `issues/` 하위 N개 vertical slice로 분해된다. 각 issue는 독립적으로 grab 가능 (tracer-bullet TDD).

| # | 제목 | depends-on |
|---|------|------------|
| 01 | aura_io 헬퍼 헤더 추출 (open_memstream shim) | — |
| 02 | hir_emit.c 마이그레이션을 신규 헤더로 정렬 | 01 |
| 03 | tests/decompiler/* open_memstream callsite 마이그레이션 (28 callsite) | 01 |
| 04 | src/gui/* open_memstream callsite 마이그레이션 (2 callsite) | 01 |
| 05 | aura_compat.h 에 WEAK_STUB 매크로 분기 | — |
| 06 | tests/stubs/analyzer_init_stubs.c MSVC 호환 | 05 |
| 07 | MappedFile.fd 단일화 (G6 채택, G7 폐기) | — |
| 08 | aura_compat 잔여 부채 정리 (Phase 2A.11 식별 사항) | — |
| 09 | Windows MSVC CI runner 도입 | 02·03·04·06·07 통과 |
| 10 | Tier 1 enforcement gate (양쪽 GREEN 필수) | 09 |
