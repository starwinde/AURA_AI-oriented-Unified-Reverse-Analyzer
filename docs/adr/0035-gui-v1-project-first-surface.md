# ADR-0035 — GUI v1 Project-First Surface (Phase 11.3, supersedes ADR-0034)

**Status**: Accepted
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: ADR-0030 (Tier 정책), ADR-0033 (Frontend topology),
ADR-0034 (initial v1 surface, superseded), PRD §7 D-6 (Qt6 확정),
Phase 11.4 (override CLI, `--project foo.db` 단일파일 모델)

---

## Context

ADR-0034 는 GUI v1 을 "단일 MainWindow + central QTableView = 함수
list view" 로 좁혔다. 사용자 검토 결과 RE 도구 컨벤션 (Ghidra Project
Manager, Cutter Load Options dialog) 과 정합성이 부족함이 드러나, 13
개 grilling 라운드를 거쳐 v1 표면을 **project-first 흐름** 으로 재정의.

핵심 동기:
- Phase 11.4 의 `--project foo.db` 단일 파일 모델이 multi-binary 를
  이미 지원 (override 가 `(fingerprint, stable_id)` keyed). GUI 가 이
  모델을 노출하지 않으면 CLI ↔ GUI co-equal contract (ADR-0033) 가
  실질적으로 깨진다.
- Ghidra 의 Project Manager 첫 화면은 신규 RE 사용자 / 기존 사용자
  모두에게 친숙. AURA 가 "Open Binary → 즉시 함수 list" 식 단순화는
  multi-binary workflow 를 차단.
- ADR-0034 의 좁힘 원칙 (Phase 5 함정 회피) 은 유지하되, 단위 = "한
  view, 한 인터랙션" 에서 "한 project, 한 binary 분석 흐름" 으로 확장.

## Decision

GUI v1 = **project-first 함수 list 흐름** — 사용자가 `.aura.db`
project 를 새로 만들거나 열고, binary 를 추가하고, 분석 옵션을
선택해 분석을 시작하면 함수 list 가 표시된다. 모든 다른 인터랙션
(decompile pane, override editor, LLM rename, multi-pane) 은 v2+.

### v1 표면 (확정)

| 영역 | 결정 |
|------|------|
| Project 단위 | 단일 `.aura.db` SQLite 파일 (Phase 11.4 와 동일 모델) |
| 첫 화면 | 빈 MainWindow + `File → New Project / Open Project` 메뉴 + status bar `"프로젝트를 열거나 새로 만드세요"` |
| Window 구조 | Single `QMainWindow` + `QStackedWidget` central widget (page 0 = Project view, page 1 = Function list view) + menu bar + status bar |
| 흐름 | launch → New/Open Project → Project view (binary list) → File→Add Binary → 행 선택 → Analyze 버튼 OR 더블클릭 → Analysis Options dialog (Quick/Full) → 확인 → ANALYZE dispatch → Function list view 전환 |
| Project view 컬럼 | Path / SHA-256 (앞 8자) / Size / Last Analyzed — 4 컬럼 |
| Function list 컬럼 | Name / Entry (hex) / Size / Source — 4 컬럼 |
| 데이터 모델 | `ProjectBinaryModel` + `FunctionTableModel` 모두 `QAbstractTableModel` 커스텀 |
| Analysis Options dialog | 경로 표시 (read-only) + Quick (`aa`) / Full (`aaa`) 2단계 슬라이더 + 확인/취소. v1 추가 옵션 없음 (v2 확장 여지) |
| 분석 중 UI | status bar progress message + Analyze 버튼 disable (modal dialog 회피) |
| Project DB schema 추가 | `CREATE TABLE IF NOT EXISTS project_binaries(path TEXT, fingerprint TEXT PRIMARY KEY, size INTEGER, added_at INTEGER, last_analyzed_at INTEGER NULL)` — backward-compat (CLI 는 이 테이블 무시) |
| View 복귀 | `View → Back to Project` 메뉴 + `Esc` 단축키 |
| Close 정책 | Confirm 없음 — override 즉시 commit (Phase 11.4 정책 유지) → dirty 상태 부재 |
| Recent projects | 없음 (v2) |
| Drag-drop binary 추가 | 없음 (v2 — 메뉴만) |
| Branding | Window title = "AURA" + (project loaded 시 `" — <basename>.aura.db"`), About dialog, version stamp = CLI 와 일관 |
| Source layout | `src/gui/`, target = `aura-gui` |
| Qt6 의존성 수급 | System install — `find_package(Qt6 COMPONENTS Widgets)` |
| License | Qt6 동적 링크 (PRD D-6 LGPL 준수) |
| Test | Qt offscreen platform 플러그인 + ctest (orchestrator_smoke 패턴) — gui_smoke 시나리오 = New Project → Add Binary → Analyze (Quick) → Function list 행 ≥ 1 검증 |
| CI | ADR-0030 Tier 1 양 환경 GREEN 강제 — Linux `apt qt6-base-dev`, Windows MSVC + Qt installer |

### Orchestrator API 변경 (작은 확장)

ANALYZE request 에 `analysis_level` enum 추가:
```c
typedef enum {
    AURA_ANALYSIS_LEVEL_QUICK = 0,  // Rizin: aa
    AURA_ANALYSIS_LEVEL_FULL  = 1,  // Rizin: aaa (현행 default)
} AuraAnalysisLevel;
```
Default = `FULL` → Phase 11.4 / 11.1 / 10 의 기존 ctest 영향 0
(backward-compat). Rizin adapter 1줄 분기. Ghidra adapter 는 v1 미사용
(optional engine) 이므로 매핑 작업 v2.

### v2+ 로 분리 (의도적 누락)

- 함수 클릭 시 detail 패널 (decompile / caller-callee 시각화)
- Override editor UI (rename / type / annotation)
- LLM rename 버튼
- Multi-pane docking
- Recent projects 메뉴
- Drag-drop binary 추가
- Stale binary path 자동 감지 + relocate dialog
- 분석 진행률 % (현재는 indeterminate spinner 또는 text)
- 분석 취소 버튼
- 다중 binary 동시 분석
- Hex view / disasm pane
- Cutter 식 추가 옵션 (쓰기모드 / VA / demangle 등)
- Analysis level 4단계 + 옵션 체크박스

## Rationale

### Project-first 로 변경한 근거

1. **CLI co-equal contract 보존** (ADR-0033 핵심) — Phase 11.4 가
   `--project foo.db` 단일파일 모델로 GREEN. GUI 가 동일 단위를
   노출해야 두 frontend 가 같은 데이터 모델을 공유.
2. **Multi-binary workflow 의 first-class 노출** — override DB 가
   이미 multi-binary keyed. GUI 에서 single-binary-only 로 보이는 것은
   기능 축소 + 사용자 혼란.
3. **RE 도구 사용자 친숙성** — Ghidra/Cutter/IDA 모두 project /
   workspace 개념 표준. 신규 사용자도 이 멘탈 모델 보유.
4. **ADR-0034 의 좁힘 원칙 보존** — single MainWindow 유지 (`QStacked
   Widget` 으로 view 전환), 함수 list 는 v1 의 핵심 데모 가치 그대로,
   v2 확장 영역만 명시적 누락.

### Project = 단일 `.aura.db` 파일 (디렉토리 X)

- Ghidra 의 디렉토리 기반 (`.gpr` + `.rep/`) 은 multi-tool ecosystem
  (CodeBrowser / Version Tracker / etc) 때문. AURA single-tool 에는
  과잉.
- Phase 11.4 가 이미 단일파일 모델로 검증 → CLI/GUI 단위 통일.
- 디렉토리 모델은 binary 사본 정책 (복사? 링크? 원본만?) + 마이그레이션
  + 파일 권한 등 결정 폭증 → v1 scope 폭발 위험.

### Single MainWindow + QStackedWidget (Ghidra 의 별도 window 패턴 거부)

- 별도 top-level window 2개 = close 정책 / focus / Z-order / multi-
  binary 동시 열기 등 결정 폭증. Phase 5 함정 재현 위험.
- `QStackedWidget` page 전환 = Qt 표준, ADR-0034 의 single MainWindow
  결정 보존, view 추가 시 page 추가만 하면 됨.

### Analysis Options dialog = Quick/Full 2단계만

- Cutter 완전 재현 (level 4단계 + 4 checkbox) = orchestrator API +
  rizin adapter + (향후) ghidra adapter 모두 옵션별 매핑 결정 N개.
  v1 scope 폭발 + Phase 11.4 호환성 검증 비용 ↑.
- Confirm-only dialog (옵션 0) = 사용자가 "분석 방법 선택" 명시했음
  에도 선택지 부재 → 요청 핵심 약화.
- Quick/Full 2단계 = 단일 enum (`analysis_level`) 추가 = backward-
  compat 보장 (default = Full). 실재 트레이드오프 (속도 vs 깊이) 노출
  → dialog 가 정직한 가치를 가짐. v2 에서 자연 확장.

### `project_binaries` 테이블을 신규 추가 (override 의 DISTINCT fingerprint derive 거부)

- Derive 방식은 분석 전 binary (override 0개) 가 list 에 등장 못함 →
  broken UX (Add Binary 후 Analyze 전 단계가 비어있어 보임).
- 신규 테이블 = `CREATE TABLE IF NOT EXISTS` 로 idempotent. CLI 는
  이 테이블 미참조 → backward-compat 자동.
- migration script 없이 첫 GUI 열기 시 자동 생성.

### 분석 진행 = status bar progress (modal dialog 거부)

- Modal progress dialog 는 UI freeze 인상 + 실제로 dialog open 상태에서
  app 의 다른 영역 인터랙션 차단 → ADR-0034 의 "비동기 dispatch 로 UI
  살아있음" 원칙 위배.
- Status bar message + Analyze button disable = 비차단 + 명확. cancel
  지원 시 status bar 옆 X 버튼만 추가하면 됨 (v2).

## Consequences

### Positive

- CLI ↔ GUI 가 같은 project 단위 (`.aura.db`) 를 공유 → ADR-0033 co-
  equal contract 의 현실적 보장.
- Ghidra/Cutter 사용자 onboarding 비용 ↓ (멘탈 모델 일치).
- Multi-binary workflow 가 v1 부터 first-class.
- Analysis level 옵션이 실재 가치 있는 토글로 노출 (v2 확장 자연).

### Negative

- ADR-0034 대비 v1 scope 증가 — Project view + Function list view +
  Analysis dialog 3개 surface 필요. Slice 수 6 → 8 로 증가.
- `project_binaries` schema 추가 = Phase 11.4 GREEN 이후 첫 schema
  변경. backward-compat 검증 필요 (CLI 가 GUI 가 만든 DB 를 읽고 / GUI
  가 CLI 가 만든 DB 를 열어도 정상 동작).
- ANALYZE request 에 `analysis_level` 추가 = orchestrator 공개 API
  소폭 변경. Phase 11.4 cli_smoke 가 default (FULL) 로 동작 보존
  검증해야 함.

### Neutral

- v2 의 detail pane / override editor 는 Function list view page 에
  추가 dock widget 로 자연 확장.
- Recent projects / drag-drop / 분석 취소 등 익숙한 UX 가 빠진 v1 은
  v1.x patch 로 빠르게 추가 가능 (architecture 변경 없음).

## Alternatives Considered

### v1 = ADR-0034 그대로 (함수 list view only, project 미노출)

거부. CLI co-equal contract 의 현실적 의미 약화 (CLI 의 `--project`
모델이 GUI 에서 보이지 않으면 두 frontend 가 같은 데이터를 공유한다는
주장이 표면적). Multi-binary 사용자 워크플로우 차단.

### v1 = Ghidra 식 별도 top-level window (Project Manager + CodeBrowser)

거부. Top-level window 2개 관리 비용 (close / focus / Z-order /
multi-binary 동시 열기 정책) 폭증. Phase 5 함정 재현 위험. Single
MainWindow + QStackedWidget 으로 동일 UX 가치 달성 가능.

### Project = 디렉토리 (Ghidra `.gpr` + `.rep/` 구조)

거부. Phase 11.4 단일파일 모델과 불일치 → CLI/GUI 단위 분리 = co-
equal contract 본질 훼손. 디렉토리 구조 결정 (binary 사본 / 메타파일
/ 권한) 폭증.

### Analysis dialog = Cutter 완전 재현

거부. 옵션 4단계 × 4 체크박스 모두 wire-in = orchestrator + 모든
adapter 변경 폭증. v1 scope 폭발. v2 자연 확장 경로 보유.

### Analysis dialog 없음 (Analyze 버튼 즉시 dispatch)

거부. 사용자가 "분석 방법 선택" 명시. dialog 없이는 옵션 노출 경로
부재 + Cutter/Ghidra 컨벤션과 거리.

## Implementation

Slice 단위 (ADR-0034 의 6 → 8 slice 로 재구성):

- **A** — ADR-0035 작성 + ADR-0034 superseded 표기 + ROADMAP/CONTEXT
  갱신 (코드 변경 0)
- **B** — `src/gui/` scaffold + MainWindow + 빈 menu bar + CMake
  (`find_package(Qt6 COMPONENTS Widgets)`, target `aura-gui`)
- **C** — Project DB schema migration (`project_binaries` 테이블 +
  store API 확장)
- **D** — Project view (`ProjectBinaryModel` + TableView) + New /
  Open / Add Binary 메뉴
- **E** — Analysis Options dialog (Quick/Full) + orchestrator
  ANALYZE 의 `analysis_level` enum 추가 + Rizin adapter 분기
- **F** — Function list view (`FunctionTableModel` + TableView,
  QStackedWidget page 1) + view 전환 + Esc/Back 메뉴
- **G** — gui_smoke ctest (offscreen, New Project → Add Binary →
  Analyze → 함수 list 행 ≥ 1)
- **H** — CI workflow (양 환경 Qt6 install + gui_smoke run)

Phase 11.3.1 / 11.3.2 / ... 후속 v2 작업 (decompile pane, override
editor, recent projects, drag-drop, 취소, 4단계 옵션) 은 별도 slice +
별도 ADR (필요 시) 로 분리.

## References

- ADR-0030 — Tier 1 platform policy
- ADR-0033 — Frontend topology
- ADR-0034 — Initial v1 surface (superseded by 본 ADR)
- Phase 11.4 — `--project foo.db` 단일파일 override 모델
- PRD §7 D-6 — Qt6 LGPL/Commercial 결정
- Ghidra Project Manager UX (visual reference)
- Cutter Load Options dialog UX (visual reference)
