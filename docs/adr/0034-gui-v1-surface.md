# ADR-0034 — GUI v1 Surface (Phase 11.3)

**Status**: Superseded by [ADR-0035](0035-gui-v1-project-first-surface.md) (2026-05-03)
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: ADR-0030 (Tier 정책), ADR-0033 (Frontend topology), PRD §7
D-6 (Qt6 확정)

> **Superseded note**: 본 ADR 의 v1 표면은 "함수 list view 전용
> single MainWindow" 였다. 2026-05-03 사용자 grilling 라운드에서
> Ghidra/Cutter 식 **project-first** 흐름 채택이 결정되어 v1 표면이
> 구조적으로 변경됨 (project 단위 = `.aura.db` 파일, 첫 화면 = Project
> Manager view, 분석 시작 시 Quick/Full 옵션 dialog, 함수 list 는
> `QStackedWidget` 두 번째 page). 본 문서는 historical reference 로
> 보존하며 결정 권위는 ADR-0035 로 이관됨.

---

## Context

ADR-0033 의 GUI bootstrap gate 의 두 조건 (CLI v1 GREEN + LLM e2e 1건)
이 commit `2eb59952` (Phase 11.4 lands) 시점에 충족. 이제 GUI v1 의
표면 정의 + 구현 진입.

이전 Phase 5 (구) GUI Integration 은 unbounded scope 로 인해 scrap
(`legacy strip` commit `0483147f`). 그 함정 회피를 위해 v1 표면을
의식적으로 좁혀야 함.

## Decision

GUI v1 = **함수 list view** — 사용자가 binary 열고 분석 후 함수 목록을
TableView 로 보는 좁은 흐름. 다른 모든 인터랙션 (decompile pane,
override editor, LLM rename button, multi-pane docking) 은 v2+.

### v1 표면 (확정)

| 영역 | 결정 |
|------|------|
| Demonstrable outcome | 함수 list view (binary 열기 + 분석 + 행 표시) |
| Window 구조 | Single `QMainWindow` + central `QTableView` + menu bar + status bar |
| 흐름 | launch → File→Open Binary → Analyze button → 함수 list 표시 |
| 분석 정책 | Open 은 file load 만, Analyze button 별도 (시점 사용자 통제, 비동기 dispatch) |
| TableView 컬럼 | Name / Entry (hex) / Size / Source — 4 컬럼 |
| 데이터 모델 | `QAbstractTableModel` 커스텀 (Qt MVC 표준 패턴) |
| Qt6 의존성 수급 | System install — `find_package(Qt6 COMPONENTS Widgets)` |
| Test | Qt offscreen platform 플러그인 + ctest (orchestrator_smoke 패턴) |
| Source layout | `src/gui/`, target = `aura-gui` |
| CI | ADR-0030 Tier 1 양 환경 GREEN 강제 — Linux `apt qt6-base-dev`, Windows MSVC + Qt installer |
| Branding | Window title = "AURA", About dialog, version stamp = CLI 와 일관 |
| License | Qt6 동적 링크 (PRD D-6 LGPL 준수) |

### v2+ 로 분리 (의도적 누락)

- 함수 클릭 시 detail 패널 (decompile / caller-callee 시각화)
- Override editor UI (rename / type / annotation)
- LLM rename 버튼
- Multi-pane docking
- Project DB 자동 open / save
- Hex view / disasm pane

## Rationale

### v1 을 "함수 list view" 로 좁힌 근거

1. **Phase 5 (구) scrap 패턴 회피** — unbounded GUI scope 가 LLM/CI/
   adapter 진척을 차단했던 함정. 좁은 v1 = "한 view, 한 인터랙션" 으로
   demonstrable + 회복 가능 + 시간 제한.
2. **GUI-native 가치 즉시 검증** — TableView 의 sort/filter/행 선택은
   GUI 만의 인터랙션. CLI 의 stdout JSON 으로 못 함. v1 에서 그 차별점
   확인.
3. **co-equal contract 의 GUI 측 검증자** — 같은 `aura_core` orchestrator
   API (ANALYZE dispatch) 가 GUI 에서도 동작 = service contract 의 양
   client 정합.
4. **단일 RE 도구 컨벤션** — Ghidra/Cutter/IDA 모두 "함수 목록" 이 첫
   화면. 신규 사용자 친숙성 + RE 사용자 이미 알고 있음.

### Open 과 Analyze 분리 (Q4)

- 즉시 dispatch 는 Open 에 ~20s 잠금 → UI freeze.
- 자동 백그라운드 dispatch 는 사용자가 시점 통제 못 함.
- 별도 Analyze button = 시점 명확 + 진행 상태 표시 가능 + 비동기 dispatch
  로 UI 살아있음.

### Qt6 system install (Q7)

- Qt6 binary distribution 수 GB → manifest+fetch 패턴 (ADR-0032)
  비현실적.
- `find_package(Qt6)` 가 표준. CMake / Linux 패키지 매니저 / Windows
  Qt Online Installer 모두 정합.

### Tier 1 양 환경 GREEN 강제 (Q10)

- ADR-0030 의 Tier 1 정의 약화 = ADR 도미노 위험.
- CI 시간 비용 (Qt6 설치) 감수 — Linux apt 는 ~30s, Windows Qt
  Online Installer 는 수 분. cache 로 amortize.
- 첫 PR 시간 증가는 일회성 (cache hit 후 빠름).

## Consequences

### Positive

- v1 의 demonstrable outcome 명확 + scope 제한 → Phase 5 함정 회피.
- Co-equal contract 가 두 frontend 에서 모두 검증 → service API 안정성.
- Qt6 system install 패턴 정합 → 신규 contributor 의 환경 setup 표준.

### Negative

- v1 사용자가 "함수 list 만 보임" 을 작은 가치로 인식할 위험 — RE 도구
  의 핵심 (decompile read-through) 부재. v2 의 빠른 도착이 중요.
- Tier 1 Windows CI 의 Qt6 설치 시간 증가 (~수 분). 첫 cache 후 amortize.

### Neutral

- 향후 v2 의 detail pane 추가 시 단일 MainWindow 에 dock widget 추가
  자연. v1 의 좁은 표면이 v2 확장 차단 안 함.

## Alternatives Considered

### v1 = 빈 창 (Hello, Qt6)

거부. Qt 동작 검증 외 가치 0. demo 가치 없음. ADR-0033 의 "co-equal
service contract 검증" 효과 없음.

### v1 = CLI 일대일 매핑 (text area 에 JSON 표시)

거부. GUI 의 시각화 가치 활용 못 함. CLI 와 동등 → 두 frontend 의 차별
이유 약화.

### v1 = 함수 list + detail 패널 + override editor (full RE workflow)

거부. v1 scope 폭발. Phase 5 (구) scrap 패턴 재현. 데이터 모델 / event
flow / 패널 layout 결정 라운드 N개 추가.

## Implementation

Slice 단위:
- A — ADR + ROADMAP + CONTEXT (본 커밋)
- B — `src/gui/` scaffolding + MainWindow + CMake
- C — `FunctionTableModel` + TableView 연결
- D — File→Open + Analyze + dispatch
- E — gui_smoke ctest (offscreen)
- F — CI workflow 갱신 (양 환경 Qt6)

Phase 11.3.1 / 11.3.2 / ... 후속 v2 작업은 별도 slice + 별도 ADR
(필요 시) 로 분리.

## References

- ADR-0030 — Tier 1 platform policy
- ADR-0033 — Frontend topology (본 ADR 의 부모)
- PRD §7 D-6 — Qt6 LGPL/Commercial 결정
- Phase 5 (구) scrap (commit `0483147f`) — unbounded GUI scope 함정의
  실증 사례
