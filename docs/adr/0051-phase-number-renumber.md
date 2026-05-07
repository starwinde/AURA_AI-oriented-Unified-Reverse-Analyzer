# ADR-0051 — Phase number renumber: plan 11.5–12 → 12.1–13

- **Status**: Accepted
- **Date**: 2026-05-05
- **Related**: ADR-0048 (Phase 11.6 Disasm flow gutter — 옛 마지막 11.x phase),
  ADR-0049/0050 (Phase 2.5.1/2.5.2).
  Plan: [`~/.claude/plans/c-q12-refactored-key.md`](file:~/.claude/plans/c-q12-refactored-key.md).
  영향 문서: `Tasks.md`, `AUTOMATION_ROADMAP.md`, plan 본문.

## Context

Phase 2.5 closeout 단계에서 plan 문서 (`c-q12-refactored-key.md`) 의 phase
번호 표를 Tasks.md / ROADMAP 에 반영 시도 중 **번호 충돌** 발견.

### 충돌 매트릭스

| 번호 | 코드베이스 / Tasks.md | Plan 문서 |
|------|---------------------|----------|
| 11.5 | P5 polish suite (8 features) — ✅ landed | SessionManager |
| 11.6 | Disasm flow arrow gutter (Cutter-style) — ✅ landed | Rizin r2pipe persistent session |
| 11.7 | (없음) | Ghidra full + AuraDaemon.java |
| 11.8 | (없음) | DB 캐시 + invalidation |
| 11.9 | (없음) | dependents() + pruning |
| 11.10 | (없음) | integrity + crash recovery |
| 12 | (없음) | LLM context (Internal 1B verifier) |

코드베이스 의 11.5/11.6 은 이미 머지·종료된 상태이므로 변경 불가. Plan 의
미반영 phase 들에 새 번호 부여가 필요.

## Decisions

### D1 — Plan 의 옛 11.5~11.10 → 새 Phase 12 묶음 (12.1~12.6)

옛 plan 11.5~11.10 은 모두 **"외부 도구 daemon / persistent session / cache
/ dependents / integrity"** 한 도메인. 한 phase 묶음 (Phase 12 — "External
Engine Session & Cache Layer") 으로 모아 sub-numbering.

| 옛 plan 번호 | 새 번호 | 내용 |
|-------------|---------|------|
| 11.5 | **12.1** | SessionManager (RAII + idle + LRU + 동시성 primitives) |
| 11.6 | **12.2** | Rizin r2pipe persistent session adapter |
| 11.7 | **12.3** | Ghidra full + AuraDaemon.java + progressive readiness |
| 11.8 | **12.4** | DB 캐시 (analysis_hash + 2-source merge + field-level type) + invalidation |
| 11.9 | **12.5** | dependents() with confidence pruning + expansion cap |
| 11.10 | **12.6** | integrity check + crash recovery |

의존 순서 명확: 12.1 → 12.2/12.3 → 12.4 → 12.5/12.6.

### D2 — Plan 의 옛 12 → 새 Phase 13

옛 plan 12 = "LLM Context Provider (Internal 1B verifier + external MCP/IPC)"
= Phase 12 묶음과 다른 도메인 (LLM pipeline). **Phase 13** 으로 분리.

사용자 메모리 (`llm_pipeline_direction.md`) 에 "별도 긴 대화에서 진행" 명시 —
독립 phase 단위 처리가 자연.

### D3 — Phase 2D / 7.1 그대로

옛 plan 2D (ghidra-full opt-in vendoring) / 7.1 (angr `symbolic` request type)
은 **단일 작업 단위** — sub-numbering 불요. 원 번호 유지.

7.1 은 옛 Tasks.md Phase 7 의 "7.1 Decompile compare" 와 번호 충돌하지만,
옛 Phase 7 자체가 ⏸️ deferred 로 Tasks_deferred.md 에 격리됨 → 실 사용 충돌
없음. Tasks_deferred.md 의 매핑표가 "옛 7.1 ≠ 신 7.1" 명시.

### D4 — 옛 phase 번호 재사용 금지 (영구)

부활 (deferred → active) 시 **새 번호 부여** 의무 — 옛 번호 재사용 금지.
옛 번호는 Tasks_deferred.md / 본 ADR / git history 에서만 살아있음.

본 ADR 이전에 머지된 코드/문서 의 phase 번호 인용은 변경하지 않음 (역사
보존). 본 ADR 이후 새로 작성하는 모든 문서 / plan / commit / ROADMAP entry 는
새 번호 체계 사용.

### D5 — 갱신 범위

본 ADR commit 과 함께 다음 문서 일괄 갱신:

1. **Plan 문서** (`~/.claude/plans/c-q12-refactored-key.md`):
   - "Phase 분할 요약" 표 (L20-29) → 새 번호로 대체
   - 본문 §3 헤더 "(Phase 11.5)" → "(Phase 12.1, 옛 Plan 11.5)"
   - 본문 §4 헤더 "(Phase 11.8-11.10)" → "(Phase 12.4-12.6, 옛 Plan 11.8-11.10)"
   - 본문 §6 헤더 "(Phase 12)" → "(Phase 13, 옛 Plan 12)"
   - 표 하단에 "Phase 번호 재배정 주의" 박스 (본 ADR 참조)

2. **Tasks.md** (active phase 표):
   - 신규 phase 행 8개 추가: 2D / 7.1 / 12 묶음 / 12.1~12.6 / 13
   - 모두 `[ ]` planned 상태

3. **AUTOMATION_ROADMAP.md** (다음 세션 백로그):
   - 중기 phase 표 — 옛 번호 (11.5~12) 인용 → 새 번호 (12.1~13)
   - 진입 권장 순서 — `Phase 11.5 SessionManager` → `Phase 12.1 SessionManager`
   - Phase 2.5 행의 "§1.6 ... Phase 11.5" → "Phase 12.1"

## Out of scope

1. **옛 git history 내 commit message / closed ADR (0001~0050) 의 phase
   번호** — 변경 안 함. 역사 보존.
2. **Phase 11.x 의 `.x` 추가 가능성** — 미래 Phase 11.7+ 가 P5 polish/gutter 와
   같은 GUI 영역에서 등장하면 그때 결정. 본 ADR 은 plan 의 미반영 phase 만
   처리.
3. **Tasks_deferred.md 의 "옛 7.1" 처리** — 이미 매핑표에 명시됨. 본 ADR 은
   active 쪽 번호만 다룸.

## Verification

본 ADR commit 직후:

- `grep -nE "Phase 11\.[5-9]|Phase 11\.10|Phase 12\)" ~/.claude/plans/c-q12-refactored-key.md`
  → 옛 plan 의 11.5~12 인용 0건 (재배정 매핑 주석 외)
- `grep -nE "Phase 11\.5|Phase 12 " AUTOMATION_ROADMAP.md`
  → Phase 11.5 (P5 polish ✅ landed 행) 만 살아있음. 백로그 의 SessionManager
  인용은 모두 12.1 사용.
- Tasks.md 진행 표 — Phase 12 묶음 + 13 행 신규 등장.

미래 작업자가 plan 의 phase 번호 인용 시 본 ADR 참조하여 옛/신 매핑 확인.
