# ADR-0041 — Phase 11.3.8 (P2.F3) CFG view (control flow graph 시각화)

- **Status**: Accepted (planning)
- **Date**: 2026-05-04
- **Supersedes**: —
- **Related**: ADR-0040 (P2.F2 Disasm view), ADR-0036 (Cutter-style workspace),
  ADR-0033 (Frontend topology), ADR-0038 (RPC TCP/JSON-line). Phase 2A
  (BlockRecord/EdgeRecord 1급 분해).

## Context

P2.F2 (Disasm view) closed end-to-end (Phase 11.3.7, 4 cycles). F3 is the
next P2 item per the 8-hour autonomous loop plan. Pre-existing assets:

- `AuraBlockRecord` + `AuraEdgeRecord` 가 이미 R-12 1급 record 로 분해됨
  (`include/aura/normalized_records.h:96, 114`). `AuraEdgeKind` enum 은
  UNKNOWN / FALLTHROUGH / JUMP / BRANCH_TRUE / BRANCH_FALSE / CALL / RETURN.
- `src/third_party_hub/rizin_to_aura.c::emit_blocks_and_edges` 가 canonical
  CFG (rizin agfj) → records 로 변환. analyze 시점에 채워진다.
- analyze body (`AuraRizinAnalyzeBody` v3) 에 `blocks[blocks_count]` +
  `edges[edges_count]` 가 이미 있고 GUI 접근자 `aura_rizin_analyze_body_blocks/edges`
  도 노출되어 있음 (`include/rizin_adapter.h:84/87`).
- DisasmPane 패턴 (Cutter-style tabified dock, cache, RPC 1:1, gui_smoke
  TC) 답습 가능.

**핵심 차이점 (vs F2)**: F2 는 데이터를 새로 fetch (rizin pdfj) 했지만
F3 의 데이터는 이미 analyze body 에 들어 있다 — 재호출은 R-12 single-source-
of-truth 정신 위반. Body type 신설은 필요 없다.

## Decisions

### D1 — Data fetch path: **on-demand RPC, 데이터 ownership 은 analyze body**

`cfg_function(func_addr)` RPC 신설. 서버 측은 **이미 fetch 된 analyze body
의 blocks[]/edges[] 를 function_id 로 필터**하여 응답한다. rizin agfj
재호출 없음. 새 body type 없음. GUI 는 응답을 per-function cache (DisasmPane
패턴 답습).

- **Reason**: BlockRecord/EdgeRecord 가 이미 Phase 2A 산출물로 analyze body
  에 있다. agfj 재호출은 R-1 (외부 도구 비용 중복) + R-12 (single source
  of truth) 두 룰을 동시에 위반한다. 한편 GUI 가 1k 함수의 모든 QGraphicsItem
  을 사전 생성하는 것은 메모리 폭발 — on-demand RPC 가 cache 단위와 lazy
  view 단위를 일치시킨다.
- **Alternative A (즉시 fill at analyze)**: pure read, no-RPC. Tradeoff —
  GUI 가 모든 함수의 QGraphicsItem 을 미리 만들어야 하고 dock 미사용 시
  메모리 낭비. 거부.
- **Alternative B' (별도 body + agfj 재호출)**: ADR-0040 의 DisasmBody
  패턴 곧이곧대로 답습. Tradeoff — 같은 데이터 두 번 fetch, R-12 위반. 거부.

### D2 — CLI scope: **`aura cfg --func <addr>` JSON `{blocks[], edges[]}`**

DisasmCLI 답습. body 신설 없이 직접 직렬화 (analyze body 의 blocks/edges
를 function_id 로 필터해서 두 배열만).

- **Reason**: cli ↔ rpc 대칭성 + headless DX (jq 필터 부담 회피). ADR-0040
  D2 와 동일 mental model.
- **Alternative**: `aura analyze` 의 blocks[]/edges[] 만 사용 (별도 CLI 없음).
  Tradeoff — 함수별 추출은 caller 가 jq 로 매번 필터, 자동화 친화도 떨어짐.
  거부.

### D3 — GUI rendering: **QGraphicsScene + QGraphicsView + custom QGraphicsItem**

`CfgPane` widget = `QGraphicsView`. Scene 에 `BasicBlockNode : QGraphicsItem`
(블록당 1개, 안쪽에 monospace QGraphicsTextItem 으로 mnemonic 미리보기) +
`EdgeArrow : QGraphicsPathItem` (블록간 화살표).

- **Reason**: Qt native, viewport transform 으로 zoom/pan 무료, item-level
  hit-testing 으로 double-click jump 자연스럽다. Cutter graph view 도 동일
  접근.
- **Alternative B (QWidget + QPainter)**: 단순하나 zoom/pan/hit-test 직접
  구현 → DisasmPane 단순성 이득이 사라진다. 거부.
- **Alternative C (graphviz subprocess)**: rules.md §5 "새 외부 의존성 도입
  시도" STOP signal. 게이트 통과 비용 (PRD §5 표 갱신 + D 결정 등재) > F3
  v1 가치. R-1 자체는 무관 (layout 은 분석 아님) 하지만 의존성 게이트가
  막는다. F3 v2 에서 재검토 가능.

### D4 — Auto layout: **BFS topological + 동일 depth 가로 배치 (Sugiyama 의 단순화)**

엔트리 블록을 root, 각 블록의 BFS depth → y 좌표 (`depth × VERT_SPACING`).
같은 depth 의 블록은 좌→우 순서로 x 배치 (`HORIZ_SPACING`). Loop back-edge
는 단순 곡선 (위로 우회).

- **R-9 가드 명시 확인**: layout = GUI 표시이지 "분석 정보 생성" 이 아니다.
  graph topology 자체는 EdgeRecord 가 이미 갖고 있고 layout 은 그 표시
  좌표만. R-9 위반 X.
- **Reason**: Sugiyama 정식 구현 (dummy node + crossing minimization +
  coordinate assignment) 은 ~수백 줄, F3 v1 cost 과대. BFS+동일 depth 가로
  배치는 "linear control flow + 작은 분기" 케이스 (대부분의 실 함수) 에서
  가독성 충분.
- **Alternative A (vertical 1열)**: 쉽지만 if/else 한 줄 → 가독성 X. 거부.
- **Alternative B (Sugiyama 정식)**: IDA/Cutter 표준 품질. Tradeoff — ~500
  LoC + 테스트. F3 v2 cycle (C5) 으로 deferred.
- **Alternative C (graphviz)**: D3 와 동일 사유 거부.

### D5 — Edge styling + interaction: **모두 v1 포함, edge routing 은 straight line**

- Edge color 매핑: BRANCH_TRUE=green / BRANCH_FALSE=red / CALL=blue /
  FALLTHROUGH=gray / JUMP=black / RETURN=purple / UNKNOWN=gray. EdgeKind
  enum 직매핑.
- Edge routing: **straight line (v1)**. Manhattan/bezier 는 layout 정식화
  (D4 v2) 와 한 묶음으로 deferred — straight + 동일 depth 가로 배치 조합
  이면 v1 시각적 충돌 적음.
- Pan: `setDragMode(ScrollHandDrag)` (좌클릭 빈 공간 drag). Zoom: wheel +
  Ctrl 수정자 (실수 스크롤 방지).
- Double-click block → `DisasmPane::selectInstruction(block.start_addr)`
  (ADR-0040 의 기존 slot 재활용) — cross-pane sync 자연스러움.
- **Deferred to v2**: edge orthogonal routing, hover tooltip (mnemonic
  전체), block 내 인라인 disasm 풀림.

## Consequences

**F3 cycle plan (4 cycles + optional 5th)**:

| Cycle | Focus | Files | Test |
|------|------|-------|------|
| C1 (cycle-10) | ADR + 데이터 모델 재활용 확인 (신규 record/body 0) | `docs/adr/0041-cfg-view.md`; rizin_adapter.h 의 blocks/edges accessor 재사용 확인 only | regression: existing block/edge provenance |
| C2 (cycle-11) | CLI + RPC + GUI 스켈레톤 | `src/cli/main.cpp` (`cmd_cfg`), `src/gui/rpc_server.cpp` (`cfg_function` analyze body 필터), `src/gui/cfg_pane.{h,cpp}` (QGraphicsView 빈 scene), `src/gui/main_window.{h,cpp}` (cfgDock + tabify with disasmDock), `src/gui/CMakeLists.txt` | cli_smoke TC: `aura cfg --func` JSON shape (blocks/edges count > 0) |
| C3 (cycle-12) | BasicBlockNode + EdgeArrow + BFS layout | `cfg_pane.{h,cpp}` (BasicBlockNode QGraphicsItem, EdgeArrow QGraphicsPathItem, layoutBfs() 함수, color map) | gui_smoke TC: cfgDock objectName + scene items count == blocks + edges |
| C4 (cycle-13) | pan/zoom + double-click jump + gui_smoke 강화 | `cfg_pane.{h,cpp}` (wheelEvent, ScrollHandDrag, mouseDoubleClickEvent → emit blockActivated(addr)), `main_window.cpp` (connect → DisasmPane::selectInstruction) | gui_smoke TC: simulate double-click → assert disasm cursor at block.start_addr |
| C5 *(deferred to F3 v2)* | Sugiyama hierarchical 정식 또는 edge orthogonal routing | `src/gui/cfg_layout.{h,cpp}` (신규) | gui_smoke TC: 분기 함수에서 edge 교차 0 |

**R-1 / R-9 / R-10 guards**:
- AURA 가 CFG 를 새로 만들지 않는다 — 모든 block/edge 는 rizin agfj → hub
  canonical → BlockRecord/EdgeRecord 를 거친다 (Phase 2A 기존 경로).
- Layout 알고리즘 자체 구현은 분석이 아닌 GUI 표시이므로 R-9 무관 — ADR
  본문에 명시.
- graphviz 등 외부 도구 도입은 rules.md §5 STOP — F3 v1 차단, F3 v2
  재검토 시 PRD §5/§9 게이트 거침.

## Alternatives considered (요약)

- **D1 즉시 fill / 별도 body + agfj 재호출**: 둘 다 single-source-of-truth
  + lazy view 비용으로 거부.
- **D2 CLI 생략 (analyze 의존)**: Disasm 와 비대칭, headless DX 저하 — 거부.
- **D3 QPainter / graphviz**: 각각 zoom/pan 비용, 의존성 게이트 비용으로
  거부.
- **D4 Sugiyama 정식 / vertical 1열 / graphviz**: v1 cost 또는 가독성 trade —
  D 채택, Sugiyama 는 v2 deferred.
- **D5 orthogonal routing v1 포함**: layout 정식화 (D4) 와 묶어서 v2 deferred.
