# ADR-0042 — Phase 11.3.9 (P2.F4) Decompile pane 강화 (양방향 sync + context menu + nav history)

- **Status**: Accepted (planning)
- **Date**: 2026-05-04
- **Related**: ADR-0040 (F2 Disasm view + line_map 단방향), ADR-0041
  (F3 CFG view + cross-pane sync), ADR-0037 (Override editor —
  Rename/Reset 기존), Phase 4B override_store
  (`AURA_OVERRIDE_PAYLOAD_RENAME` / `_ANNOTATION` 이미 존재).

## Context

P2 의 3개 sub-feature 중 F2/F3 closed. F4 는 (a) line_map 양방향
완성 — F2 의 deferred 항목, (b) 우클릭 컨텍스트 메뉴 base — PP1~PP4
페인 포인트 작업의 hook 자리, (c) 함수 nav history. 세 축.

선결 자산:
- `override_store.h` 에 `AURA_OVERRIDE_PAYLOAD_ANNOTATION` 이 이미
  등재됨 (Phase 4B 가 미리 깔아 둔 것) — comment 추가에 **schema bump
  불필요**.
- `DecompilePane::lineSelected(addr)` signal + `DisasmPane::selectInstruction(addr)`
  slot 으로 단방향 sync 동작 중 (F2 cycle-9).
- `m_addrToLine` (DisasmPane) 와 `m_currentLineMap` (DecompilePane)
  — 양방향 매핑 기반 자료 이미 보유.

## Decisions

### D1 — Bidirectional line_map sync: **A (DisasmPane signal → main_window 라우팅)**

- DisasmPane: `instructionSelected(quint64 addr)` signal 추가;
  cursorPositionChanged 시 `m_addrToLine` 의 역방향 (vector index
  로 addr 보관) 으로 cursor line → addr 해상.
- DecompilePane: `selectLine(quint64 addr)` 신규 slot — addr → line
  역인덱스 lookup (m_currentLineMap 을 line→addr 에서 addr→line 으로
  뒤집은 hash) → setTextCursor.
- main_window: `connect(disasm.instructionSelected → decomp.selectLine)`.
- **Re-entrancy guard**: 양 페인 cursor change 가 서로를 trigger 하지
  않도록 `QSignalBlocker` (또는 bool flag) 로 양 방향 모두 가드. F2
  의 단방향 케이스에는 echo 위험 없었지만 F4 의 mutual sync 에는 필수.

**Reason**: F2 의 mirror — 동일 mediator 패턴 (signal → main_window
connect → slot). DisasmPane 이 ExtraSelection 을 직접 DecompilePane
에 적용하지 않고 main_window 가 단일 mediator (ADR-0041 의 CFG cross-pane
패턴과 동형).

**Alternative B (자동 mirror — ExtraSelection 변경 시 양쪽 자동 sync)**:
echo loop 위험으로 거부.

### D2 — Context menu v1: **5개 항목 (Jump / Rename / Reset / Xrefs / Comment)**

- DecompilePane 의 `setContextMenuPolicy(Qt::CustomContextMenu)` +
  `customContextMenuRequested` signal → 현재 cursor line 의 line_map
  addr 해상 후 QMenu 표시. addr == 0 이면 모든 액션 disable.
- 액션:
  1. Jump to disasm — DisasmPane.selectInstruction(addr)
  2. Rename — InputDialog → override_store_put (RENAME)
  3. Reset name — override_store_delete (RENAME)
  4. Find xrefs — xrefs dock 포커스 + 해당 addr 필터 (XrefTableModel
     에 setFilterAddr 같은 helper 추가)
  5. **Add comment** — InputDialog → override_store_put (ANNOTATION
     payload)
- **Add comment v1 포함 — schema 확장 0**: `AURA_OVERRIDE_PAYLOAD_ANNOTATION`
  이 이미 정의됨. 256B 텍스트 cap 충분.
- **DisasmPane 우클릭 미러는 deferred (F4 v2 / F5)**: 같은 액션이지만
  위치만 달라 v1 가치 적음, 테스트 매트릭스만 2배.

### D3 — Navigation history: **A 단순화 (함수 entry 만 push, cursor pos 는 v2)**

- `MainWindow` 에 `QStack<quint64> m_navBack / m_navForward`. 함수
  진입 시 currentFunc 를 back 에 push, forward stack clear (browser
  표준 — non-linear nav 는 forward 무효화).
- `goBack()` / `goForward()` slot — pop / push 짝, 활성 함수 전환.
  flag 로 nav 액션 자체는 push 하지 않음 (re-entrancy 차단).
- cursor 위치 보존은 vector<pair<addr, int>> 로 자료구조만 바꾸면
  v2 에서 추가 가능 (additive).

**Reason**: "방금 그 함수로" 빈도가 cursor 위치 보존보다 큼 (cycle
테스트 비용 정당화). browser 표준 forward stack 동작 — 익숙함.

**Alternative B (back only, forward 없음)**: forward 결손 시 "잘못
돌아가서 다시 앞으로" 흐름 끊김 — UX 후퇴, 거부.

### D4 — UI affordance: **단축키 + View 메뉴, toolbar 신설 X**

- `Alt+Left` / `Alt+Right` 키 (browser 표준) + View 메뉴 아래 "Back"
  / "Forward" QAction. 별도 toolbar 신설 X.

**Reason**: ADR-0036 Cutter-style workspace 가 toolbar 신설을 minimize
하는 방향. 4개 dock 토글 사이에 nav 버튼이 끼면 의미축이 섞임. 단축키
+ 메뉴 조합 = discoverability + speed 양립.

**Alternative A (toolbar)**: 시각 노이즈 경합 — 거부.

### D5 — Cycle 분해 (4 cycle)

| Cycle | Focus | Files | Test |
|------|------|-------|------|
| C1 (cycle-14) | ADR (이번) + bidirectional sync (D1) | `disasm_pane.{h,cpp}`, `decompile_pane.{h,cpp}`, `main_window.{h,cpp}` | gui_smoke TC: disasm cursor → decomp line 동기 (F2 mirror) |
| C2 (cycle-15) | Context menu (D2 — 5 actions) | `decompile_pane.{h,cpp}`, `main_window.{h,cpp}`, optional XrefTableModel filter helper | gui_smoke TC: 우클릭 5 항목 표시 + Rename → store row, ANNOTATION → store row |
| C3 (cycle-16) | Nav history (D3 + D4) | `main_window.{h,cpp}` (QStack + slots + QAction), View 메뉴 추가 | gui_smoke TC: A→B→A 후 Back → A, Forward → B |
| C4 (cycle-17, 선택) | Polish + R-5 가드 회귀 | gui_smoke timing 안정화, override_store integration TC 재실행 | regression: 전체 GREEN |

## R-1 / R-5 / R-9 / R-10 guards

- **R-5 (override 불변성)**: 컨텍스트 메뉴의 Rename / Add comment 는
  `override_store_put` 으로 SQLite 누적. `AuraEngineResponse` mutate
  X. 표시는 GUI 가 store + engine join 으로 합성.
- **R-9 (no new analysis)**: line_map 역인덱스 / nav history 모두 GUI
  표시 보조이지 분석 산출 X. addr → line 매핑은 engine 이 이미 emit
  한 line_map 의 역방향만 build.
- **R-1 (engine 단일출처)**: 모든 함수/주소 정보는 분석 시 fetch 된
  record 를 재사용. F4 가 신규 rizin 호출 추가 X.
- **R-10 (no smart logic)**: nav history 는 stack 두 개의 단순 push/pop.
  "최근 본 함수 추천" 같은 추론 X.

## Alternatives considered (요약)

- **D1 ExtraSelection 자동 mirror**: echo loop 위험, 거부.
- **D2 Add comment defer**: schema 가 이미 있어 deferral 비용 = 가치,
  거부 (포함이 우세).
- **D2 DisasmPane 우클릭 v1 포함**: 테스트 비용 2x vs 가치 미미,
  v2 / F5 묶음으로 deferred.
- **D3 cursor 위치 보존**: additive — v2 deferred.
- **D3 back only**: 거부, UX 후퇴.
- **D4 신규 toolbar**: 거부, 시각 노이즈.
