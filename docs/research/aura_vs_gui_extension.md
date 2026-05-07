# AURA GUI + CLI + Extension vs x64dbg — 비교 분석

**Task #44** — v2.3.0 Phase 2-B compare. Session #9 (2026-04-21). Team `v2-3-0-phase-2b`, comparison teammate.
**입력**: `docs/research/x64dbg_analysis.md` (#33 — CLI dispatcher + disasm UX), `docs/research/x64dbg_bridge_api.md` (#36 — GUI↔DBG Bridge 아키텍처), `docs/research/x64dbg_gui_panels.md` (#37 — Qt GUI 14 패턴, 최고 ROI 754 LOC), `docs/research/x64dbg_plugin_scripting.md` (#38 — Plugin SDK + ExpressionParser).
**Scope**: AURA `src/gui/` (Qt6, `aura-gui` 24 MB) + `src/cli/` + `src/core/aura.c` argv dispatch + PRD §4.1 plugin 유보 + rules.md §2 C/C++ 전용.
**License 경계**: x64dbg GPL-3. 본 문서는 **API-level pattern** 만 참조. AURA 저장소 수정/커밋 없음.
**Compare-1/2/3 와의 관계**: #41 (func_detect), #42 (disasm+IR), #43 (symbol) 과 독립. 본 task 는 **GUI + CLI UX + extension** 축 전용.

---

## 1. AURA 현재 구현 snapshot

### 1.1 GUI (`src/gui/`, Qt6, `aura-gui` 24 MB)

실존 파일 (39 `.cpp/.h` 쌍):

| 그룹 | 파일 | 대략 역할 |
|------|------|----------|
| 메인 shell | `main_window.{cpp,h}`, `main_gui.cpp`, `sidebar.{cpp,h}`, `panels.{cpp,h}` | QMainWindow + `QDockWidget` + `QSplitter` + `QTabWidget` |
| 분석 파이프라인 UI | `analysis_dispatcher.{cpp,h}`, `analysis_worker.{cpp,h}`, `analyzer_select_dialog.{cpp,h}` | `AnalysisStage` enum(8) + DAG dep + `StageRequest` queue |
| 디스어셈블 / Hex | `disasm_column_config.{cpp,h}`, `command_palette.{cpp,h}` | 열 구성 + command palette (Ctrl-P 추정) |
| 그래프 뷰 | `cfg_view.{cpp,h}`, `callgraph_view.{cpp,h}`, `stack_layout_view.{cpp,h}` | 개별 `QAbstractScrollArea` 기반 |
| 디컴파일 뷰 | `pseudoc_highlighter.{cpp,h}` | `QSyntaxHighlighter` + `QRegularExpression` + `QTextCharFormat` 6종 규칙 |
| 프로젝트 / 세션 | `project.{cpp,h}`, `project_manager_window.{cpp,h}`, `session_manager.{cpp,h}`, `file_loader.{cpp,h}` | SQLite (D-13) 기반 persist |
| 편집 / 패치 | `edit_handlers.{cpp,h}`, `patch_editor.{cpp,h}`, `type_editor.{cpp,h}`, `undo_manager.{cpp,h}` | Zydis re-assemble path |
| 다이얼로그 | `export_dialog.{cpp,h}`, `search_dialog.{cpp,h}`, `settings_dialog.{cpp,h}` | 정적 Qt Designer `.ui` 추정 |
| LLM / 협업 | `llm_panel.{cpp,h}`, `collab_panel.{cpp,h}`, `console_panel.{cpp,h}`, `debugger_panel.{cpp,h}` | libcurl LM Studio 연동 |
| 공용 | `theme_manager.{cpp,h}`, `shortcut_manager.{cpp,h}`, `nav_history.{cpp,h}` | 테마 Dark/Light 2종 enum, shortcut 관리자 존재 (내용 추후 확인) |

**주요 관찰**:
- `main_window.h` line 10: `#include <QDockWidget>` → AURA 는 **x64dbg 와 반대로 `QDockWidget` 을 사용**. `MHTabWidget` / `LabeledSplitter` 패턴은 미채택.
- `theme_manager.h`: `enum Theme { Light, Dark }` + `applyTheme` + `darkStyleSheet()` static — **Qt stylesheet 기반 단일 파일 단일 모드**. registry/JSON/per-token 없음.
- `pseudoc_highlighter.h`: **6개 정적 규칙** (keyword / type / comment / number / 함수호출) — 토큰 타입 enum 또는 색상 키 없음. `switch`/`case` 를 `QVector<HighlightRule>` 로 캡슐화했지만 **themeable 아님** (색이 파일 내 하드코딩).
- `analysis_dispatcher.h`: `AnalysisStage` enum (Parse/Disasm/FuncDetect/Cfg/Dfg/Hir/Decompile/ExtraAnalyzers), `StageRequest { stage, funcAddr, seqId }`, DAG 의존성 자동 해소, per-stage cancel, `AURA_GUI_SYNC` escape hatch. **x64dbg Bridge `GUIMSG` 60+ case 의 단순화판이 이미 부분 존재**.

### 1.2 CLI (`src/core/aura.c` argv + `src/cli/`)

`src/core/aura.c` 는 **if-else `strcmp(argv[i], "--flag")` 체인** 으로 dispatch. 현재 옵션:
- `--version` / `--verbose`
- `--disasm <file>` / `--info <file> [--json]`
- `--patch <file> --addr <addr> --asm "..."` (Zydis 기반)
- `--recursive <file>` / `--strings <file>` / `--xref <file> --addr <addr>`
- `--callgraph <file> [--dot]` / `--functions <file>`
- `--cfg <file> --func <addr> [--dot]` / `--dfg <file> --func <addr> [--json]`
- `--decompile-metrics <file> --func <addr>` (A-5)
- `--decompile-all <file>` (E-3, `src/cli/decompile_all.{c,h}` 진행 중)
- `--decompile <file> --func <addr>` (Phase 5.42 HIR)

**한계 관찰**:
- 옵션 간 조합 폭발 — 각 분기가 hand-rolled. x64dbg `cmdnew(name, cb, debugonly)` 의 **registry** 패턴 미채택.
- **value expression 없음** — `--func 0x401000` 같이 리터럴 주소만 허용. `--func "main+0x10"` 또는 `--filter "size > 256"` 불가.
- `--decompile-all` 은 전체 함수 일괄 — 선별 기능 없음 (filter / sort / offset 모두 부재).
- JSON 출력이 옵션별 ad-hoc — 통일된 streaming schema 없음.

### 1.3 Plugin 정책 (PRD §4.1 유보)

PRD 핵심 원칙 #3: "**플러그인 시스템, 스크립트 인터페이스는 MVP 이후로 유보**". rules.md §2: "**C/C++ 전용, Python/Java 등 인터프리터 언어 사용 금지**".

현재 AURA 의 외부 확장 표면:
- `--decompile-all --json` → 외부 tool 이 stdout 파이프로 소비 (E-3 완료 시).
- LLM panel — HTTP API, 외부 모델이 결과 수정은 가능하나 AURA 내부는 수정 불가.
- 설정 파일 (SQLite D-13 프로젝트 DB) — schema 는 있으나 플러그인이 schema 확장 불가.

### 1.4 gui ↔ core 경계

현 구조 (추정):
- `src/core/libaura_core.a` (또는 object library) — parser, decompiler, disasm, analysis.
- `src/gui/aura-gui` — 위 static lib 를 **직접 링크**. 헤더 경로 `#include "aura.h"` 등으로 C ABI 호출.
- Qt worker 패턴: `AnalysisWorker` (QObject/QThread) → core 함수 호출 → `emit resultReady(...)` → `AnalysisDispatcher` slot.

**분리 원칙 (PRD 핵심 원칙 #4 정적 링크 우선)**: DLL / 프로세스 분리 없음. 경계는 **컴파일 단위 + include path + 함수 prefix** 관습에 의존.

---

## 2. x64dbg top-10 GUI 패턴 AURA 적용성

`docs/research/x64dbg_gui_panels.md` §12 의 10 항목을 각각 **포팅 여부 / Qt5→Qt6 마찰 / 예상 세션 / ROI** 로 평가.

### ① AbstractTableView 공통 베이스 (P1)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **조건부 채택**. 기존 `cfg_view / callgraph_view / stack_layout_view` 가 이미 각자 구현. 신규 view (symbol list, xref list) 부터 적용. |
| Qt5→Qt6 마찰 | `QFontMetrics::width` → `horizontalAdvance` (검색 교체 2 분). `QRegExp` → `QRegularExpression` (x64dbg 내부 5 군데). |
| 예상 세션 | 1.5–2 (clean-room 재작성 ~800 LOC + 신규 view 1 건 포팅) |
| ROI | **중** — `decompile_all` 결과 테이블 뷰 (수천 함수) 에서 virtual scroll 이 필요할 때 즉시 가치. 기존 3 view 재작성 비용 ≥ 이득 → **신규 한정**. |

### ② Configuration theme registry + JSON (P9)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **강력 권장 채택**. `theme_manager` 가 이미 존재하지만 Dark/Light enum + stylesheet 방식 → registry 방식으로 확장. |
| Qt5→Qt6 마찰 | 없음 (`QMap<QString, QColor>` 은 Qt5/6 공통). |
| 예상 세션 | 1 (registry 구조체 ~150 LOC + `theme.json` 로더 + 기존 stylesheet 치환 ~200 LOC). |
| ROI | **최상** — `pseudoc_highlighter` 의 하드코딩 색상을 `theme::color("pseudoc.keyword")` 로 이전하면 LLM / collab 패널 스타일 통일. 사용자 테마 외부화 가능. |

### ③ RichTextPainter 토큰 → color lookup (P7)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **조건부 채택** — 토큰 생성은 이미 decompiler HIR 에서 나오고 있음. 렌더만 QSyntaxHighlighter 대신 토큰 리스트 직접 paint 로 전환. |
| Qt5→Qt6 마찰 | x64dbg 는 자체 RichTextPainter (QTextEdit 대비 최적화). AURA 는 `QSyntaxHighlighter` + `QTextCharFormat` 으로 충분 — **full port 불필요**. 토큰-색상 매핑 테이블만 채택. |
| 예상 세션 | 0.5 (매핑 테이블 + 기존 regex rule 6 → 토큰 키 N 개로 확장) |
| ROI | **높음** — ② 를 전제. decompile view 가독성 향상. |

### ④ Bridge 스레드 모델 (P4/P5/P6)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **부분 채택**. `analysis_dispatcher` 가 이미 `AnalysisStage` enum + queue + dedup + cancel 을 구현 → Bridge 의 핵심 기능 중복. **`GUIMSG` 60+ 정수 dispatch 는 불필요** (Qt signal/slot 로 충분, #36 §8.2 "차용하지 말 것"과 일치). |
| 채택할 것 | (a) Throttling `QTimer` per-event-type (§3 `GUI_UPDATE_*` rate limit) — 대형 바이너리 분석 시 UI lag 해소. (b) `BridgeAlloc/BridgeFree` 류 owner 규약 (현 AURA 는 묵시적). |
| Qt5→Qt6 마찰 | `Qt::AutoConnection` 동작 동일. `QMetaObject::invokeMethod` 시그니처 Qt6 에서 template 변경 (functional 지원 강화) — 긍정. |
| 예상 세션 | 0.5–1 (throttling 도입만) |
| ROI | **중** — 대형 바이너리에서 "Analyzing 42/2000..." 진행률이 초당 수천 번 fire 되는 상황 방지. |

### ⑤ HexDump multi-encoding ColumnDescriptor (P2)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **보류**. AURA 현 hex view 는 `disasm_column_config` 수준. 구조체 역공학 필요 시점 (Phase 8 이후 type-editor 강화) 에 재평가. |
| Qt5→Qt6 마찰 | 없음. |
| 예상 세션 | 1–2 (ColumnDescriptor + 5 해석 모드 paint 분기) |
| ROI | **중** — `type_editor.{cpp,h}` 가 이미 존재 → 시너지 가능. 그러나 긴급성 낮음. |

### ⑥ Jump arrow side-bar (§3.3)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **채택 권장** — AURA disasm view 에 현재 선형 배치만. `cfg_view` 는 별도 뷰. 선형 disasm 에 점프 화살은 **즉시 가시성 개선**. |
| Qt5→Qt6 마찰 | `QPainterPath` API 동일. |
| 예상 세션 | 1 (300–500 LOC clean-room) |
| ROI | **중-높음** — 정성적 UX 큰 차이. |

### ⑦ LabeledSplitter + MHTabWidget (P11/P12)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **보류**. AURA 가 `QDockWidget` 사용 (main_window.h:10) → x64dbg 가 피한 API. Qt6 `QDockWidget` 이 여전히 드래그 중 크래시 이슈 있는지 측정 후 결정. |
| 현시점 조건 | 사용자가 "탭 분리 창" / "섹션 접기" 요청할 때 재검토. |
| Qt5→Qt6 마찰 | `QTabBar::moveTab` 동일. 드래그 detach 는 `QDrag` + `QWindow::fromWinId` 로 Qt6 에서 더 안정. |
| 예상 세션 | 2–3 (MHTabWidget ~500 LOC + LabeledSplitter ~300 LOC + 레이아웃 마이그레이션) |
| ROI | **낮음-중** — 현재 dock 경험이 문제가 아니라면 우선 순위 하위. |

### ⑧ Shortcut registry (P13)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **채택**. `shortcut_manager.{cpp,h}` 가 이미 있음 → x64dbg 의 `Configuration::Shortcut { Name, Hotkey, Category, Global }` 구조로 확장 + ShortcutsDialog clean-room. |
| Qt5→Qt6 마찰 | `QKeySequence` 동일. `QShortcut` 소유권 규칙 Qt6 에서 동일. |
| 예상 세션 | 1 (기존 구조 확장 + 충돌 감지 + dialog). |
| ROI | **중-높음** — 사용자 커스터마이징. ② 와 묶어 "Preferences" 페이지 탄생. |

### ⑨ Symbol master/detail + SearchListView (§7)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **채택**. AURA 가 대형 binary (aura-self: 수천 함수) 에서 단일 list 검색 성능이 bottleneck. master (module) / detail (symbol) 2-pane + filter edit. |
| Qt5→Qt6 마찰 | `QSortFilterProxyModel` 동일. |
| 예상 세션 | 1 (기존 심볼 뷰 → 2-pane 재구성). |
| ROI | **높음** — #43 (symbol compare) 와 시너지. 사용자 체감 큰 변화. |

### ⑩ Log view → QTextBrowser + hyperlink (§6.1)

| 축 | 평가 |
|----|------|
| 포팅 여부 | **채택 — 저비용 고가치**. 현 `console_panel` 이 `QPlainTextEdit` 추정 → `QTextBrowser` 로 스왑 + `aura://goto-func/0x401000` URL 스킴 → anchorClicked signal → `navigateToAddress` (main_window 이미 존재). |
| Qt5→Qt6 마찰 | `setOpenLinks(false)` + `anchorClicked(QUrl)` signal 동일. |
| 예상 세션 | 0.3–0.5 (위젯 교체 + URL 스킴 파서). |
| ROI | **중** — decompile 결과 / LLM 제안에서 함수 이름 클릭 → 점프 UX 구현. |

### 패턴 제외 (AURA 비적합 — §12 원문 따름)

- **Trace recording (TraceBrowser)** — 정적 분석. 불필요.
- **CPURegistersView 원형** — debugger 아님. 호출 규약 표시용 축소는 Phase 2-E E-2 EH flow 와 시너지 가능 (향후).
- **BridgeResult blocking event** — deadlock 안티패턴. Qt `Qt::BlockingQueuedConnection` + `QFutureWatcher` 로 충분 (#36 §8.2).

### Top-10 요약 ROI 매트릭스

| 번호 | 패턴 | ROI | 세션 | 의존 |
|------|------|-----|------|------|
| ② | Theme registry + JSON | **최상** | 1 | 없음 |
| ③ | Token → color lookup | **높음** | 0.5 | ② |
| ⑨ | Symbol master/detail | **높음** | 1 | 없음 |
| ⑩ | Log → QTextBrowser + hyperlink | **중** | 0.5 | 없음 |
| ⑥ | Jump arrow side-bar | **중-높음** | 1 | 없음 |
| ⑧ | Shortcut registry | **중-높음** | 1 | 기존 shortcut_manager |
| ④ | Bridge throttling | **중** | 0.5–1 | 기존 dispatcher |
| ① | AbstractTableView (신규 한정) | **중** | 1.5–2 | 없음 |
| ⑤ | HexDump multi-encoding | **중** | 1–2 | type_editor 시너지 |
| ⑦ | LabeledSplitter/MHTab | **낮음-중** | 2–3 | QDockWidget 문제 발생 전제 |

**권장 순서**: ② → ③ → ⑩ → ⑨ → ⑧ → ⑥ → ④ → ① → ⑤ → ⑦.

---

## 3. CLI ExpressionParser 확장 (shunting-yard)

### 3.1 x64dbg 의 구조 (#38 §3.2)

- Shunting-yard, 14-level C-style precedence.
- Token 40+ (Data / Unary / Arith / Shift / Cmp / Bitwise / Logical / Assignment / Function / `[addr]` memory deref).
- `valfromstring()` — register / variable / `$RESULT` / `module.func` / symbol 자동 resolve.
- **Plugin extension**: `_plugin_registerexprfunction(name, argc, cb, userdata)` 로 DSL 에 함수 주입 (#38 §2.3).

### 3.2 현재 AURA CLI 한계 (§1.2 복사)

- 리터럴만 허용 (`--func 0x401000`).
- 조합 없음 (`--filter ...`, `--sort ...` 모두 부재).
- 옵션 dispatch 가 `strcmp` 체인 — 30+ 로 확장 시 선형 유지보수 비용.

### 3.3 AURA 에 적용 가능한 DSL subset

**초기 scope 제안** (plugin 확장 제외, 내장만 — rules.md §2 인터프리터 금지 준수):

| 카테고리 | x64dbg 전체 | AURA subset (초기) | AURA subset (중기) |
|---------|-------------|--------------------|--------------------|
| 리터럴 | 10/16/2진수 | 10/16진 | + 문자열 `"..."` |
| 식별자 | register / variable / symbol | **symbol** (`main`, `puts`, `func_401000`) | + `$` prefix 사용자 변수 (1 세션 계산용) |
| 산술 | +, -, *, /, %, HiMul, shift/rotate | `+`, `-`, `*`, `/`, `%` (stage 1) | + 비트 연산 `&`, `|`, `^`, `~`, `<<`, `>>` |
| 비교 | all | `<`, `<=`, `>`, `>=`, `==`, `!=` | 동일 |
| 논리 | `&&`, `\|\|`, `->` | `&&`, `\|\|`, `!` | 동일 |
| 할당 | all | **금지** (CLI 는 read-only 선호) | 동일 |
| Memory deref | `[addr]` | **금지** (static RE) | **금지** |
| Function call | plugin 확장 | 내장 `size(func)`, `addr(func)`, `name(func)` | + `xref(addr, "call")`, `section(addr)` |

**구현 비용** (#38 §3.2 1,182 LOC 기준으로 subset 추정): ~500–800 LOC C, 1.5–2 세션 + unit test 세트.

### 3.4 Filter / Sort 사용 예

```bash
# 함수 크기 256 바이트 초과만 decompile
aura --decompile-all binary --filter "size > 256"

# .text 섹션의 함수만, 주소 오름차순, 상위 100
aura --decompile-all binary \
     --filter "section == \"text\" && size >= 16" \
     --sort "addr asc" --limit 100

# 이름 prefix 매칭 + 디스어셈블
aura --disasm binary --filter "name starts \"aura_\""
```

**장점**:
- `--decompile-all` 의 N × decompile 시간이 사용자 scope 로 축소.
- Future GUI "Filter bar" (§2 ⑨ master/detail 와 연계) 와 **동일 DSL** 공유 — UX 일관성.

**Scope 제한 (PRD §4.1 + rules.md §2)**:
- ExpressionParser **내장만**. plugin-registered function 허용하지 않음 (rules.md §2 인터프리터 언어 금지의 연장 해석).
- 할당 연산 / memory deref / register 읽기 **전부 제외** — runtime debugger 가 아님.
- Stage 1 (산술 + 비교 + 논리 + 내장 함수 3) → stage 2 (비트 + 문자열) 분리.

### 3.5 Dispatcher 패턴 재구성 (v3.0.0+ reference)

`strcmp` 체인 → #38 §3.1 의 `cmdnew(name, cb, debugonly)` registry 이식:

```c
typedef int (*aura_cli_cb)(int argc, const char **argv, FILE *out);

typedef struct {
    const char *name;         /* e.g. "decompile-all" */
    aura_cli_cb cb;
    const char *help;
    bool requires_binary;
} aura_cli_command;

int aura_cli_register(const aura_cli_command *cmd);
int aura_cli_dispatch(int argc, const char **argv);
```

- 카테고리별 파일 분리 (#33 §5.1 `cmd-searching.cpp`, `cmd-analysis.cpp` 패턴):
  - `src/cli/cmd_disasm.c`, `src/cli/cmd_decompile.c`, `src/cli/cmd_analysis.c`, `src/cli/cmd_patch.c`.
- 현재는 Phase 11.4 이후 (PRD 제약) — **지금 리팩터 금지**.

---

## 4. Plugin system 재검토 (v3.0.0 이후)

### 4.1 PRD §4.1 유보 결정 재확인

PRD §4.1 원문: **"플러그인 시스템, 스크립트 인터페이스는 MVP 이후로 유보"**. rules.md §2: **"C/C++ 전용, 인터프리터 언어 금지"**.

#38 §4.1 의 2 가지 유보 정당성:
1. Plugin SDK 복잡도 ≫ MVP 가치 (x64dbg 35 CBTYPE + 40 export + SDK version gate).
2. PRD §5 "커스텀 구현 우선" 과 긴장 — plugin 허용 ⇒ 외부 ABI 안정성 요구 ⇒ 내부 리팩터 자유도 감소.

**결론 — 본 문서 입장**: PRD §4.1 유보 유지. v3.0.0 (정적 MVP 완주) 이전 재검토 금지.

### 4.2 v3.0.0 이후 채택 시의 설계 단서

채택이 결정되면 x64dbg 의 다음 패턴이 가장 적은 이식 비용:

| x64dbg 원본 | AURA 재구현 형태 | 비용 |
|-------------|------------------|------|
| `PLUG_INITSTRUCT { handle, sdkVersion, pluginVersion, name[256] }` | `aura_plugin_init_t` 동일 struct | 낮음 |
| `PLUG_SDKVERSION=1` 단일 정수 gate | **semver + feature flag bitset** (#38 §4.5 반례 채택) | 중 |
| `CBTYPE` flat enum + per-type vector | `aura_cb_type_t` enum — 정적 분석용 6 종 재구성 (아래 §4.3) | 낮음 |
| `_plugin_registercommand` → core table 통합 | §3.5 의 `aura_cli_register` 경로 그대로 재사용 | 낮음 |
| `_plugin_registerexprfunction` DSL 확장 | §3 의 ExpressionParser 확장 포인트 | 중 |
| Menu handle 7종 + `CB_MENUENTRY` | Qt6 `QMenu::addAction` + signal 로 직접 가능 — C ABI 우회 불필요 | 매우 낮음 |

### 4.3 AURA 에 의미 있는 CBTYPE subset

x64dbg 35개 → **6개** (정적 분석 범위):

- `AURA_CB_LOAD_FILE` — ELF/PE/Mach-O open 직후 (플러그인이 파서 hook).
- `AURA_CB_FUNCS_DETECTED` — func_detect 완료 (플러그인이 이름/범위 override).
- `AURA_CB_CFG_BUILT` — BridgeCFGraphList 유사 전달 (플러그인이 추가 분석).
- `AURA_CB_HIR_EMITTED` — decompile 직전 (플러그인이 HIR 수정).
- `AURA_CB_DECOMPILE_DONE` — pseudo-C 생성 후 (플러그인이 annotation 추가).
- `AURA_CB_SAVE_PROJECT` — SQLite persist (플러그인 자체 데이터 직렬화).

Runtime debugger callback (BP/TRACE/EXCEPTION/THREAD) **전부 제외** — AURA scope 밖.

### 4.4 피해야 할 반례 (#38 §4.5 요약)

1. **동기 블로킹 callback**: 플러그인 버그가 AURA 전체 hang. AURA 는 timeout + worker thread 분리 필수.
2. **Label + conditional jump 스크립트**: x86 mental model 의존. AURA 는 구조적 제어 흐름만 (if 재도입 시 Lua 가 Python 대비 compliant — 그러나 **현 PRD §4.1 하에서는 금지**).
3. **단일 정수 SDK version**: semver + feature flag 권장 (§4.2 위).

---

## 5. Bridge 패턴 (GUI ↔ core 경계 재평가)

### 5.1 채택 불가 — x64dbg 3 DLL 분리

`x32bridge.dll` + `x32dbg.dll` + `x32gui.dll` 구조는 **AURA PRD 핵심 원칙 #4 "정적 링크 우선"** 과 정면 충돌. AURA 는 단일 프로세스 단일 바이너리.

결과:
- `BRIDGE_IMPEXP` 매크로 (#36 §2.1) — 불필요.
- `BridgeInit/BridgeStart` 3단계 초기화 — 불필요 (`main.cpp` 직접 `QApplication` + `MainWindow`).
- `_dbg_*` / `_gui_*` 함수 포인터 resolve — 불필요 (직접 링크).

### 5.2 차용 가능 — ABI-식 내부 경계 **자기규율**

#36 §8.1 "Bridge 에서 직접 차용할 것" 4 항목을 AURA 에 매핑:

| Bridge 아이디어 | AURA 적용 |
|----------------|-----------|
| `GuiExecuteOnGuiThreadEx(cb, user)` | AURA decompile worker 이 이미 `QMetaObject::invokeMethod(mainWindow, fn, Qt::QueuedConnection)` 사용 (analysis_dispatcher.h) — **부분 존재**. Bridge 의 **callback + void\* userdata 2-쌍 C ABI** 는 core→GUI 마샬링용 single-slot 으로 단순화 이식. |
| `ListInfo { count, size, data }` flat container | **채택 권장**. `--decompile-all` JSON streaming 과 plugin 경계 (v3.0.0 후) 에 재사용. `aura_list_t` C struct 신규. |
| `bridgegraph.h` C-ABI + C++11 이중 레이어 | **채택 권장** — AURA HIR/CFG 를 외부 (CLI JSON / plugin) 에 노출할 때: `aura_cfg_t` POD (C) + `aura::Cfg` wrapper (C++). #36 §8.1 원문 "난이도 중간". |
| `#pragma pack` + `MAX_*` 고정 크기 buffer | **부분 채택**. cross-arch CI (ARM/x86-64 혼용) 안정성에 기여. rules.md `feedback_ci_hardcoded_build_rel.md` 와 별개 이슈지만 동일 결에서 묶어볼 가치. |

### 5.3 적용 예 — `aura_cfg_t` 공개 ABI

현재 CFG 는 GUI 내부 C++ 구조로 존재 추정. `cli_decompile_all` 이 JSON 으로 변환하는 path 에 ABI 레이어 삽입:

```c
typedef struct {
    uint64_t va;
    uint8_t  bytes[15];
    uint8_t  len;
} aura_cfg_instr_t;

typedef struct {
    uint64_t start, end, brtrue, brfalse;
    int      instr_count;
    bool     terminal;
    aura_list_t exits;   /* of uint64_t */
    aura_list_t instrs;  /* of aura_cfg_instr_t */
} aura_cfg_node_t;

typedef struct {
    uint64_t entry;
    aura_list_t nodes;   /* of aura_cfg_node_t */
} aura_cfg_t;

int aura_cfg_build(const char *binary, uint64_t func_addr, aura_cfg_t *out);
void aura_cfg_free(aura_cfg_t *cfg);
```

GUI 측 `cfg_view.cpp` 는 `aura_cfg_t` 를 `std::unordered_map<uint64_t, Node>` 로 변환해 소비. CLI 측 `--decompile-all` JSON 에도 동일 struct 직렬화 → **CLI 와 GUI 가 같은 구조 공유**.

비용: 기존 cfg 내부 → ABI 경계 마이그레이션 ~300–500 LOC. 단일 세션 가능. v2.3.0 scope 로 적합.

---

## 6. 항목별 spec (구현 단위)

**채택 권장 항목만 상세 spec 작성**. 각 항목은 **독립 PR** 단위 (rules.md §8 스코프 통제).

### S-gui-2 — Theme registry + JSON (②)

- **파일 신규**: `src/gui/theme_registry.{cpp,h}` (150 LOC 예상).
- **파일 수정**: `src/gui/theme_manager.{cpp,h}` — enum → registry 위임, backward-compat Dark/Light preset 유지.
- **API**:
  ```cpp
  class ThemeRegistry {
  public:
      static QColor color(const QString &key, const QColor &fallback = Qt::black);
      static QFont  font (const QString &key, const QFont  &fallback);
      static bool   loadJson(const QString &path);
      static void   saveJson(const QString &path);
      Q_SIGNAL void colorsUpdated();
  };
  ```
- **의존**: 없음. `QMap` + `QJsonDocument` Qt 내장.
- **테스트**: `tests/gui/test_theme_registry.cpp` (JSON roundtrip + fallback).
- **DoD**: Dark/Light 두 기본 테마가 JSON 으로 외부화. `pseudoc_highlighter` 색상 key 5개 lookup 치환.
- **예상 세션**: 1.

### S-gui-3 — Token → color lookup (③)

- **파일 수정**: `src/gui/pseudoc_highlighter.{cpp,h}`.
- **변경**: `HighlightRule` → `{ QRegularExpression pattern; QString colorKey; }`. `highlightBlock` 이 `ThemeRegistry::color(rule.colorKey)` 호출.
- **의존**: S-gui-2.
- **DoD**: 6 규칙 → 6 color key. LLM / decompile view 가 테마 교체 즉시 반영.
- **예상 세션**: 0.3.

### S-gui-9 — Symbol master/detail view (⑨)

- **파일 신규**: `src/gui/symbol_browser.{cpp,h}` (Module list + Symbol list + Filter edit).
- **의존**: 없음. `QSortFilterProxyModel` 내장.
- **DoD**: `aura --functions` + `aura --decompile-all` 결과를 GUI 에서 `QLineEdit` filter 로 실시간 검색 (1만 함수 binary 에서 30ms 이하 응답).
- **예상 세션**: 1.

### S-gui-10 — Log hyperlink (⑩)

- **파일 수정**: `src/gui/console_panel.{cpp,h}` — `QPlainTextEdit` → `QTextBrowser` + `setOpenLinks(false)` + `anchorClicked(QUrl)` → `MainWindow::navigateToAddress`.
- **URL 스킴**: `aura://goto-func/0x401000`, `aura://goto-addr/0x12345`, `aura://open-cfg/0x401000`.
- **의존**: 없음.
- **DoD**: decompile 결과 + LLM 응답의 함수 이름이 링크로 렌더. 클릭 → disasm 점프.
- **예상 세션**: 0.5.

### S-gui-8 — Shortcut registry 확장 (⑧)

- **파일 수정**: `src/gui/shortcut_manager.{cpp,h}` — 기존 구조 확장. Category/Global 플래그 + 충돌 감지.
- **파일 신규**: `src/gui/shortcuts_dialog.{cpp,h}`.
- **의존**: S-gui-2 (theme 과 함께 Preferences 창 탄생).
- **DoD**: 단축키 표 + filter + capture widget + Save/Revert. JSON 지속화.
- **예상 세션**: 1.

### S-gui-6 — Jump arrow side-bar (⑥)

- **파일 신규**: `src/gui/disasm_sidebar.{cpp,h}` (`CPUSideBar` clean-room, ~400 LOC).
- **의존**: 없음.
- **DoD**: 선형 disasm 뷰 좌측 40px column. 가시영역 분기 수집 → track 배치 → `QPainterPath`. 전진/후진 4색.
- **예상 세션**: 1.

### S-gui-4 — Dispatcher throttling (④)

- **파일 수정**: `src/gui/analysis_dispatcher.{cpp,h}` — event-type 별 `QMap<AnalysisStage, QTimer>` + 100ms rate limit.
- **의존**: 기존 dispatcher (이미 존재).
- **DoD**: 대형 바이너리 (1000+ 함수) 진행률 갱신이 UI thread 점유 < 20%.
- **예상 세션**: 0.5.

### S-cli-1 — ExpressionParser subset (stage 1)

- **파일 신규**: `src/cli/expr_parser.{c,h}` (shunting-yard ~500–800 LOC).
- **파일 수정**: `src/cli/decompile_all.c` — `--filter` / `--sort` / `--limit` 옵션 수용.
- **의존**: 없음.
- **Scope**: §3.3 Stage 1 subset (산술 + 비교 + 논리 + 내장 함수 3: `size(f)`, `addr(f)`, `name(f)`).
- **DoD**: 모든 `--decompile-all --filter` 표현식이 AST → predicate 로 평가. 100 unit test.
- **예상 세션**: 1.5–2.

### M-abi-1 — `aura_cfg_t` C-ABI 경계

- §5.3 참조.
- **파일 신규**: `include/aura/cfg_public.h` + `src/core/cfg_public.c`.
- **의존**: 없음.
- **DoD**: CLI `--cfg --json` 과 GUI `cfg_view` 가 동일 struct 소비. Cross-arch CI 통과.
- **예상 세션**: 1–1.5.

---

## 7. Phase 2-X 로드맵 매핑

v2.3.0 Phase 2-B (research) 결과물을 **v2.3.0 Phase 2-X (옵션) 또는 v2.4.0** 으로 편성:

| Phase 2-X ID | 작업 묶음 | 포함 | 세션 누계 |
|--------------|-----------|------|-----------|
| **2-X-10 GUI pack** | ② + ③ + ⑩ + ⑨ + ⑧ + ④ (theme 중심) | S-gui-2, S-gui-3, S-gui-10, S-gui-9, S-gui-8, S-gui-4 | ~4.8 |
| **2-X-11 CLI DSL** | ExpressionParser subset | S-cli-1 | ~2 |
| **2-X-12 ABI 경계** | `aura_cfg_t` + `aura_list_t` | M-abi-1 | ~1.5 |
| **2-X-13 GUI stretch** | ⑥ + ① (신규 view 한정) | S-gui-6, (신규 view 한정 AbstractTableView) | ~3 |

**총**: ~11.3 세션. 분산 착수 가능 (의존성 낮음).

**권장 착수 순서**:
1. 2-X-12 ABI 경계 (다른 작업의 하위 인프라).
2. 2-X-10 GUI pack (사용자 체감 큰 차이).
3. 2-X-11 CLI DSL (power user).
4. 2-X-13 GUI stretch.

**PRD §4.1 plugin 유보 유지** — Phase 2-X 에서 plugin 도입 **절대 금지**. v3.0.0 후 별도 검토 (#38 §4.1 지지).

---

## 8. 인용

### 8.1 입력 research docs

- `docs/research/x64dbg_analysis.md` (#33) — CLI dispatcher + disasm UX + PDB + pattern 4-영역.
- `docs/research/x64dbg_bridge_api.md` (#36) — Bridge 아키텍처 (3 DLL, GUIMSG, BridgeResult, ListInfo, bridgegraph.h).
- `docs/research/x64dbg_gui_panels.md` (#37) — Qt GUI 14 패턴 (P1–P14) + top-10 ROI (§12) + Qt5→Qt6 차이 (§8.3).
- `docs/research/x64dbg_plugin_scripting.md` (#38) — Plugin SDK (35 CBTYPE, PLUG_SDKVERSION) + simplescript + ExpressionParser (shunting-yard, 14-level precedence).

### 8.2 AURA 코드 참조점

- `src/gui/main_window.{cpp,h}` — QMainWindow + `QDockWidget` + `QSplitter` + `QTabWidget`.
- `src/gui/theme_manager.{cpp,h}` — `enum { Light, Dark }`, stylesheet 기반. **registry 아님**.
- `src/gui/pseudoc_highlighter.{cpp,h}` — `QSyntaxHighlighter` + 6 regex rule, 색상 하드코딩.
- `src/gui/analysis_dispatcher.{cpp,h}` — `AnalysisStage` enum(8) + DAG dep + queue + cancel + `AURA_GUI_SYNC`.
- `src/gui/shortcut_manager.{cpp,h}` — 기존 shortcut layer (확장 여지).
- `src/gui/cfg_view.{cpp,h}`, `callgraph_view.{cpp,h}`, `stack_layout_view.{cpp,h}` — 각자 구현 (AbstractTableView 미채택).
- `src/gui/console_panel.{cpp,h}` — 현 `QPlainTextEdit` 추정 (⑩ 대상).
- `src/core/aura.c` line 80–260 — `strcmp(argv[i], "--flag")` 체인 dispatch 11종.
- `src/cli/decompile_metrics.{c,h}`, `src/cli/decompile_all.{c,h}` — A-5 + E-3 신규 CLI entries.

### 8.3 PRD / rules 참조점

- **PRD §4.1** — 플러그인 시스템 MVP 이후 유보 (§4 본 문서 §4.1 지지).
- **PRD 핵심 원칙 #3** — 플러그인 시스템 MVP 이후.
- **PRD 핵심 원칙 #4** — 정적 링크 우선 (§5.1 3 DLL 채택 불가 근거).
- **PRD 핵심 원칙 #5** — 커스텀 구현 우선 (§4.1 plugin 유보 정당성 강화).
- **rules.md §2** — C/C++ 전용, Python/Java 금지 (§3 DSL stage 1 내장 한정).
- **rules.md §8** — 스코프 통제 (§6 독립 PR 단위).

### 8.4 License 경계

x64dbg 는 GPL-3. 본 문서는 **아키텍처 패턴 + API surface + 설계 의도**만 기록한다. AURA 로의 실제 이식은 **clean-room 재구현** 원칙 준수. 입력 #33/#36/#37/#38 문서 자체도 동일 원칙 따라 작성되어 있음 (각 문서 License note 참조).

---

**문서 끝.** Task #44 완료. 예상 LOC ≈ 700 (요구 600–800 범위 중앙).
