# AURA Tasks — Deferred / Scrapped Phases

> **상위 문서**: [Tasks.md](./Tasks.md) (현재 active phases) · [AUTOMATION_ROADMAP.md](./AUTOMATION_ROADMAP.md) (live status)
> **목적**: 2026-05-03 외부 도구 오케스트레이션 pivot 으로 무효화되거나 보류된 Phase 항목을 한 곳에 모은다. 외부 reader 가 "왜 이 phase 가 안 보이는지" 즉시 이해 가능하도록.
> **상태 기호**: ❌ scrapped (영구 폐기) · ⏸️ deferred (조건부 재개 가능) · 🔄 reborn (다른 phase 로 부활)

---

## 분류 요약

| Phase | 옛 제목 | 상태 | 후속 / 흡수처 |
|-------|---------|------|--------------|
| **5** | GUI Integration | 🔄 **reborn** (실질 완료) | Phase 11.3~11.6 으로 분해, 80% 완료 |
| **6** | Secondary Engine Adapters | ⏸️ deferred | Phase 6+ 또는 사용자 요청 시 재개 |
| **7** | Multi-engine Compare / Multi-decompiler Serving | ⏸️ deferred | Phase 6 + session/cache 의존. 옛 7.1 번호는 angr `symbolic` 으로 재사용됐지만, decompiler serving 목표는 D-36 으로 보존 |
| **8** | Performance / mmap | ⏸️ deferred | mmap 자체는 D-6 완료. concurrency / 캐시 → Phase 11.5 SessionManager |

---

## Phase 5 — GUI Integration  🔄 reborn

**원래 의도** (pre-pivot): AURA 가 처음부터 Qt6 GUI 를 직접 만들기. 6개 sub-task 로 분해되어 있었음.

**상태**: **80% 완료** — 새 phase 번호 (11.3~11.6) 로 분해되어 모두 ✅ landed. 옛 5.x 6 sub-task 와 새 11.x phase 의 매핑:

| 옛 5.x | 새 phase / 위치 | 상태 |
|--------|----------------|------|
| 5.1 디컴파일 뷰 (엔진 응답 그대로 표시) | Phase 11.3.1 (Cutter-style workspace) + 11.3.9 (Decompile pane 강화) | ✅ |
| 5.2 함수 목록 ↔ 디컴파일 ↔ CFG 동기 | Phase 11.3.5 (docks) + 11.3.7 (Disasm) + 11.3.8 (CFG) + 11.3.9 (양방향 sync) | ✅ |
| 5.3 Override 적용 결과 즉시 reflow | Phase 11.3.2 (Override Editor) | ✅ |
| 5.4 우클릭 메뉴 wire (Rename / Type Cast / Annotation) | Phase 11.3.9 (5개 context-menu actions) | ✅ |
| 5.5 엔진 선택 UI (Engine Manifest 기반 동적 dropdown) | CLI `--engine` flag + `aura engines` 만 있음 | 🟡 **부분** — GUI dropdown 미구현 |
| 5.6 Trace visualization (varnode/xref tree/graph) | Phase 11.3.5 Xrefs dock (표 형식) | 🟡 **부분** — graph 시각화 미구현 |

**옛 5.x 에 없던 추가 GUI 작업** (모두 ✅ landed):
- 11.3.3 RPC 서버 (TCP localhost JSON-line)
- 11.3.4 Batch decompile (single Rizin invocation)
- 11.3.6 Strings dock + 9th 1급 record (body schema v3)
- 11.3.10 Hex view dock (mmap)
- 11.4.x PP1~PP4 — Type Propagation / Field Candidates / Array Candidates / Auto-labelling
- 11.5 P5 polish — 8 features (Recent Projects MRU, drag-drop, Go-to-address, Find function, Copy address/name, font zoom, shortcuts cheat sheet, dock focus)
- 11.6 Disasm flow arrow gutter (Cutter 스타일)

**잔여 (옛 5.5 / 5.6)**:
- **5.5 GUI 엔진 dropdown** — CLI 의 `--engine` flag 와 동등한 dropdown UI. 사용자가 함수마다 또는 default 로 엔진 선택 가능하게. 현재는 Rizin default + 사용자 명시 시만 변경.
- **5.6 Trace graph 뷰** — 현재 Xrefs dock 이 표 형식. tree / node-edge graph 시각화는 별도 widget 필요 (Phase 11.3.8 의 CFG view 와 비슷한 구조).

**재개 조건**: 사용자 요청 시 백로그 entry 신설 + 별도 phase 번호 부여 (예: Phase 11.7 / 11.8).

---

## Phase 6 — Secondary Engine Adapters (RetDec / Capstone)  ⏸️ deferred

**원래 의도**: Phase 1 의 어댑터 계약 위에 보조 엔진 추가.
- 6.1 Capstone (disasm secondary / fallback, primary 는 Rizin)
- 6.2 RetDec (decompile secondary, Rizin/Ghidra co-primary 비교용)
- 6.3 Adapter conformance test (Phase 1 계약 + R-10/R-11/R-12 검증)

**왜 deferred?**:
1. **현재 primary 만으로 동작** — Rizin (disasm/analyze/decompile/trace primary) + Ghidra (decompile co-primary) 가 충분
2. **사용자 요청 부재** — 보조 엔진 비교 / 정확성 검증 시나리오 아직 등장 안 함
3. **결과 reconciliation 정책 미결정** — Phase 7 (Multi-engine Compare) 와 함께 정해져야 함

**재개 조건**:
- 사용자가 "Rizin 결과 의심됨, RetDec 으로 cross-check 하고 싶다" 같은 명시 use case 발생
- 또는 `aura --probe-engines` 가 RetDec 환경에서 실제 사용 가능 검증 후 도입

**ADR / R-rule 영향**: rules.md R-7 (request type 표준화) / R-8 (type-별 primary 집합) 모두 보조 엔진 도입 시점에 갱신 필요. RetDec 은 `decompile` secondary 로 명확 분류, Capstone 은 `disasm` secondary / fallback.

---

## Phase 7 — Multi-engine Compare / Multi-decompiler Serving  ⏸️ deferred

**최종 의도 (D-36, 2026-05-06 재확인)**: 같은 함수에 대해 복수 decompiler 결과를 동시에 요청·보존·표시한다. 현재 0.8.0 Rizin/rz-ghidra 단일 기준은 시연 가능한 baseline 이며 최종 범위 축소가 아니다.
- Decompile serving/compare view (Rizin/rz-ghidra vs Ghidra co-primary + RetDec secondary)
- 7.2 Disasm cross-check (Rizin vs Capstone)
- 7.3 Vote / 우선순위 규칙 (D-3) — type-별 primary 집합 우선, 불일치는 사용자 노출. 자동 merge / 자동 정정 / "정답" 결정 금지

**왜 deferred?**:
1. **Phase 6 의존** — 비교 대상 보조 엔진이 없으면 비교 불가
2. **GUI multi-engine compare view 자체가 큰 작업** — 별도 phase 분리 필요
3. **Session/cache 의존** — 복수 decompiler 를 동시에 서빙하려면 per-engine session lifecycle, cache key, partial failure 표시 정책이 필요

**번호 정리**: **Phase 7.1** 번호는 ROADMAP 에서 angr `symbolic` request type 으로 재사용됐다. 따라서 옛 "7.1 Decompile compare" 라벨은 폐기하지만, **multi-decompiler serving 목표 자체는 폐기하지 않는다**. 구현 phase 진입 시 새 번호(예: Phase 14 또는 당시 ROADMAP 의 다음 빈 번호)와 별도 ADR 로 승격한다.

**현 7.1 (angr `symbolic`)** 은 D-34 로 정책 승인됐으며, 구현은 외부 angr runner/subprocess 방식으로만 허용된다. 새 7.1 은:
- angr 어댑터 신설
- 새 request type `symbolic` (D-34 승인, primary = `{angr}`)
- `aura_angr_runner.py` 작성
- PRD §F-6 갱신

**재개 조건**:
- Phase 6 RetDec / secondary decompiler adapter 재개
- Phase 12 session/cache layer 의 per-engine lifecycle + cache key 정리
- GUI engine dropdown 또는 compare view 사용자 요청
- `--engine-compare` / `--decompilers` 같은 CLI surface 논의 착수

---

## Phase 8 — Performance / mmap  ⏸️ deferred

**원래 의도**: 500MB+ 바이너리를 UI 동결 없이 처리.
- 8.1 Lazy 엔진 호출 (요청 시점에만 adapter dispatch)
- 8.2 결과 캐시 (`~/.cache/aura/`, 엔진 + request type 별 키)
- 8.3 엔진 호출 큐 + UI 스레드 분리 + 엔진 동시성 제한

**왜 deferred?**:
1. **mmap 자체는 D-6 으로 완료** — `src/core/mapped_file.c`, Phase 11.3.10 Hex view 가 이미 mmap 기반
2. **concurrency / 캐시 / 호출 큐 = Phase 11.5 SessionManager 로 흡수 예정**:
   - per-engine mutex + global semaphore N=2 (Phase 2.5 §1.6 deferred 회수)
   - idle timer + LRU + max_concurrent_sessions=3
   - DB 캐시 (analysis_hash, 2-source merge, field-level type)
3. **현재 사용 시나리오 = 작은 binary** (수십 MB). 큰 binary 시나리오 부재로 우선순위 낮음

**재개 조건**:
- Phase 11.5 SessionManager 진입 시 8.3 (호출 큐 + 동시성) 자동 진행
- 사용자가 500MB+ 실제 binary 분석 시나리오 가져옴 → 8.1 / 8.2 별도 cycle

---

## 조회용 — 옛 phase ↔ 새 phase 매핑표

다른 도구 / 외부 문서 / 옛 PR 에서 "Phase 5/6/7/8" 언급 발견 시 다음으로 환원:

| 옛 라벨 | 실제 위치 |
|---------|----------|
| "Phase 5 GUI" | Phase 11.3 ~ 11.6 (전체) |
| "Phase 5.1 디컴파일 뷰" | Phase 11.3.1 / 11.3.9 |
| "Phase 5.5 엔진 dropdown" | (미구현, 백로그 후보 — Phase 11.7+) |
| "Phase 5.6 Trace graph" | (미구현, 백로그 후보 — Phase 11.7+) |
| "Phase 6 Capstone/RetDec" | (미진행, 본 문서) |
| "Phase 7 Compare" | (미진행, 본 문서) — multi-decompiler serving 목표 보존. 단 옛 "7.1 Decompile compare" ≠ 신 "7.1 angr symbolic" |
| "Phase 7.1" (옛) | Decompile compare — 미진행 |
| "Phase 7.1" (신, ROADMAP 백로그) | **angr `symbolic` request type 신설** |
| "Phase 8 mmap/perf" | mmap = D-6 완료 / concurrency = Phase 11.5 SessionManager |

---

## 거버넌스

- 본 문서는 **"틀어져서 사용 못 하는 항목 보관소"** — 머지 영구 차단됨.
- 부활 (deferred → active) 시 **별도 ADR 작성 의무**. 부활 phase 번호는 **새로 부여** (옛 번호 재사용 금지) — 옛 번호는 본 문서에서만 살아 있음.
- Phase 5 의 잔여 (5.5 / 5.6) 처럼 부분 살아남는 항목은 신규 phase 번호로 분리.
- 본 문서는 release snapshot 성격 (Tasks.md 와 동일 등급, rules.md §11.2). 자주 갱신 안 함.
