# x64dbg GUI 패널 전체 해체

**Task #37** — v2.3.0 Phase 2-B research. GPL-3 clean-room 분석.
**Upstream**: https://github.com/x64dbg/x64dbg — `src/gui/Src/`
**License 경계**: x64dbg는 GPL-3. 본 문서는 **아키텍처 패턴, 클래스 관계, 설계 의도**만 기록한다. 구현 코드를 AURA 저장소로 직접 복사하지 않으며, 모든 포팅은 clean-room 재작성이다.
**AURA 관점**: AURA `src/gui/`는 Qt6 기반 — x64dbg는 현존하는 Qt 디버거 GUI 중 **가장 가까운 레퍼런스**다. Qt5→Qt6 차이는 §9, §12에 명시.

---

## 1. Executive Summary

### 1.1 왜 x64dbg GUI가 최대 reference인가
- **기술 스택 일치**: Qt 기반 네이티브 C++ GUI (AURA Qt6과 동일 패러다임, 5→6 포팅 비용 미미)
- **실전 성숙도**: 10년+ 운영된 다중-패널 리버스 엔지니어링 IDE — 15개 주요 view, 40+ 다이얼로그, 100+ shortcut
- **패턴 밀도**: MVC 추상화 (`AbstractTableView`), 스레드 경계 bridge, theming registry, shortcut manager 모두 **재사용 가능한 일반화 패턴**으로 추출됨
- **비교 대상** (Task #33 Ghidra/Rizin/x64dbg pattern 문서): Ghidra는 Swing/Java (포팅 큼), Rizin은 TUI (GUI 없음). x64dbg만 Qt native GUI를 제공

### 1.2 AURA 적용 top-3 즉시 가치
1. **`AbstractTableView` 패턴** — 거의 모든 데이터 패널 (Disasm / HexDump / Threads / BP / CallStack) 이 단일 추상 베이스에서 파생. AURA가 15+ 개 view를 각각 `QTableView`로 재구현 중이라면 **이 패턴으로 통합 가능**
2. **Bridge 스레드 모델** — 백그라운드 분석 워커와 GUI 스레드 간 `Qt::QueuedConnection` + 100+ signal + `BridgeResult` 동기화. AURA `analysis_worker.cpp` / `analysis_dispatcher.cpp` 와 직접 매핑
3. **Color/Font Registry + JSON 지속화** — 모든 paint()가 `Configuration::Colors["disasm.mnemonic"]` lookup. AURA syntax highlighting을 enum/switch에서 registry로 리팩토링하면 테마 교체가 설정 파일 1건으로 수렴

### 1.3 추출된 패턴 인벤토리 (14개)
| # | 패턴 | x64dbg 위치 | AURA 적용 영역 |
|---|------|------------|--------------|
| P1 | `AbstractTableView` 공통 베이스 | `BasicView/AbstractTableView.{cpp,h}` | 모든 table-기반 view |
| P2 | `ColumnDescriptor` / `DataDescriptor` 다중-인코딩 셀 | `BasicView/HexDump.h` | HexDump view, dump view |
| P3 | `HexDump` 서브클래싱으로 Stack View 구현 | `Gui/CPUStack.h` | 스택/덤프/트레이스 메모리 |
| P4 | Bridge singleton + 100+ signal | `Bridge/Bridge.h` | analysis_dispatcher 확장 |
| P5 | `BridgeResult` blocking event (worker→GUI 동기 호출) | `Bridge/Bridge.h` | 사용자 입력 필요 worker 분기 |
| P6 | Update throttling (`mLastUpdates` / `mUpdateTimers`) | `Bridge/Bridge.h` | CFG/Callgraph 과도 refresh 방지 |
| P7 | `ZydisTokenizer::SingleToken` + `RichTextPainter` | `Disassembler/*`, `BasicView/Disassembly.h` | disasm syntax highlight |
| P8 | `MenuBuilder` 재사용 가능 context menu | `Utils/MenuBuilder` | 우클릭 메뉴 통합 |
| P9 | `Configuration` registry + 테마 JSON | `Gui/AppearanceDialog.h`, `Utils/Configuration` | 색/폰트/단축키 중앙집중 |
| P10 | `VaHistory` back/forward navigation | `Utils/VaHistory` (HexDump/Disasm 공용) | 주소 navigation 히스토리 |
| P11 | `MHTabWidget` (custom tab with close/rename/reorder) | `Gui/MHTabWidget` | CFG/Disasm 다중 함수 탭 |
| P12 | `LabeledSplitter` 접을 수 있는 dock 대체 | `BasicView/LabeledSplitter.h` | 3-column master 레이아웃 |
| P13 | Shortcut registry (`Configuration::Shortcut`) | `Gui/ShortcutsDialog.h` | 모든 action에 단축키 바인딩 |
| P14 | `StdIconTable` + `SearchListView` filtered list | `BasicView/StdIconSearchListView.h` | Symbols / Modules / Imports 목록 |

---

## 2. 전체 패널 구조 + MVC 패턴

### 2.1 디렉토리 계층 (src/gui/Src/)

```
src/gui/Src/
├── BasicView/           # 추상 공통 베이스 (P1, P2, P14)
│   ├── AbstractTableView.{cpp,h}       # 모든 table view 루트
│   ├── AbstractStdTable.{cpp,h}        # 표준 데이터 모델
│   ├── StdTable.{cpp,h}                # 구체 StdTable
│   ├── StdIconTable.{cpp,h}            # 아이콘 열 지원 (모듈 상태, 스레드 타입)
│   ├── HexDump.{cpp,h}                 # hex/ASCII dump 엔진
│   ├── Disassembly.{cpp,h}             # disasm 렌더링 (AbstractTableView 서브)
│   ├── SearchListView.{cpp,h}          # filter edit + list (심볼/모듈 공통)
│   ├── StdIconSearchListView.{cpp,h}   # icon + filter 조합
│   ├── LabeledSplitter.{cpp,h}         # dock-like collapsible splitter
│   ├── LabeledSplitterDetachedWindow   # splitter 패널을 윈도우로 분리
│   ├── ReferenceView.{cpp,h}           # xref / 검색 결과 목록
│   ├── HistoryLineEdit                 # 검색 히스토리 입력
│   ├── ShortcutEdit                    # 단축키 입력 위젯
│   └── HeaderButton.h                  # 클릭 가능 헤더
│
├── Bridge/              # 스레드 경계 + 싱글톤 (P4, P5, P6)
│   └── Bridge.{cpp,h}                  # Qt::QueuedConnection 허브
│
├── Disassembler/        # 토크나이저 + 렌더 (P7)
│   ├── ZydisTokenizer                  # 옛 명칭 CapstoneTokenizer
│   ├── RichTextPainter                 # colored segment list → paint
│   └── InstructionToken
│
├── Gui/                 # 구체 view/dialog/window (40+ files)
│   ├── MainWindow.{cpp,h}              # QMainWindow + MHTabWidget
│   ├── CPUWidget.{cpp,h}               # disasm+regs+stack+dump 복합
│   ├── CPUDisassembly.{cpp,h}          # Disassembly 서브 (context menu 확장)
│   ├── CPUSideBar.{cpp,h}              # 점프 화살/BP gutter
│   ├── CPURegistersView.{cpp,h}        # RegistersView 서브
│   ├── CPUStack.{cpp,h}                # HexDump 서브 (프레임 색상)
│   ├── CPUDump.{cpp,h} + CPUMultiDump  # 메모리 덤프 탭
│   ├── CPUInfoBox.{cpp,h}              # 하단 요약 상자
│   ├── CPUArgumentWidget.{cpp,h}       # 함수 인자 추정
│   ├── MemoryMapView.{cpp,h}           # 메모리 맵 (StdIconTable)
│   ├── ThreadView.{cpp,h}              # 스레드 목록 (StdTable)
│   ├── CallStackView.{cpp,h}           # unwind 프레임 목록
│   ├── BreakpointsView.{cpp,h}         # BP 리스트 + 그룹
│   ├── SymbolView.{cpp,h}              # 모듈 ↔ 심볼 split
│   ├── LogView.{cpp,h}                 # QTextBrowser 기반
│   ├── HandlesView.{cpp,h}             # 핸들/윈도우/TCP/privilege
│   ├── LocalVarsView.{cpp,h}           # 현재 프레임 지역변수
│   ├── DisassemblerGraphView.{cpp,h}   # CFG graph
│   ├── DisassemblyPopup.{cpp,h}        # hover tooltip disasm
│   ├── AppearanceDialog.{cpp,h,ui}     # theming
│   ├── ShortcutsDialog.{cpp,h,ui}      # 단축키
│   └── … 35+ dialogs
│
├── Tracer/              # 트레이스 녹화/재생
│   ├── TraceBrowser                    # AbstractTableView 서브
│   ├── TraceManager                    # 다중 트레이스 파일 관리
│   └── TraceFileReader
│
├── Memory/              # 페이지 히스토리, 메모리 모델
├── Utils/               # Configuration, MenuBuilder, VaHistory, …
├── QHexEdit/            # 패치용 hex editor (ThirdParty 파생)
└── Accessible/          # 스크린리더/자동화
```

### 2.2 MVC 매핑

x64dbg는 Qt `QAbstractItemModel` 기반 **표준 MVC를 사용하지 않는다**. 대신 `AbstractTableView`가 **view+controller를 통합하고 model은 가상 함수 콜백으로 위임**하는 커스텀 패턴을 채택.

```
┌─ Model layer ─────────────────────────────────────────┐
│ (서브클래스가 override)                                 │
│  virtual QString getCellContent(int row, int col)      │
│  virtual QColor  getCellColor(int row, int col)        │
│  virtual bool    isSelected(int row)                   │
│  virtual void    prepareData()      // 가시영역 사전로드 │
│  setRowCount(int), reloadData()                        │
└────────────────────────────────────────────────────────┘
             ▲                         ▲
             │ data                    │ redraw
┌─ View/Controller (AbstractTableView) ────────────────┐
│  QAbstractScrollArea 상속                              │
│  paintEvent → paintContent(painter, row0, rowCount)   │
│  mTableOffset, mNbrOfLineToPrint                       │
│  addColumnAt/setColumnHidden/Order                     │
│  mouse/keyboard → selection + context menu             │
│  signals: selectionChanged, tableOffsetChanged         │
└────────────────────────────────────────────────────────┘
```

**왜 `QAbstractItemModel` 을 안 썼나**:
- 10M+ 행 메모리/트레이스 데이터 — model/view 의 `index()`/`data()` 호출 오버헤드가 크다
- hex dump, disasm 에서 **한 행이 여러 column에 걸쳐 custom paint** (예: jump arrow가 여러 열 spanning) — item delegate로 표현이 번거롭다
- offset-기반 virtual scrolling — QAbstractItemModel의 parent/child 계층과 맞지 않음

**AURA 시사점**: CFG/Callgraph처럼 노드 수가 크고 행 단위가 아닌 view는 이 패턴이 유리. 단순 목록 (Imports 등) 은 `QTableView`+`QAbstractTableModel` 충분.

### 2.3 Common widget 계층도

```
QAbstractScrollArea
  └─ AbstractTableView ─ (paint + column + scroll offset)
       ├─ AbstractStdTable ─ (row-based data storage, sort)
       │    ├─ StdTable ─ (generic string cells)
       │    │    ├─ ThreadView
       │    │    ├─ BreakpointsView
       │    │    ├─ HandlesView.subtables
       │    │    └─ ReferenceView.internal
       │    ├─ StdIconTable ─ (icon 컬럼 추가)
       │    │    ├─ MemoryMapView
       │    │    └─ CallStackView
       │    └─ StdTableSearchList (combined with SearchListView)
       ├─ HexDump ─ (byte-oriented multi-encoding)
       │    ├─ CPUStack (프레임 annotation)
       │    ├─ CPUDump
       │    └─ TraceMemoryDump
       └─ Disassembly ─ (instruction-oriented, token painter)
            └─ CPUDisassembly (context menu + commands)
            └─ TraceBrowser (recorded instructions)
```

이 단일 계층 덕분에:
- 모든 테이블 view가 **동일한 단축키** (Ctrl+G goto, Ctrl+F find, 방향키 selection)
- 모든 view가 **공통 setupContextMenu + MenuBuilder** 사용
- 모든 view가 **Configuration 레지스트리 color/font**에 자동 반응 (signal `tokenizerConfigUpdatedSlot`, `updateColorsSlot`)

---

## 3. Disassembly view 심층 (Task #33 확장)

Task #33에서는 tokenizer + CLI 명령 처리를 다뤘다. 여기서는 **Qt UI 측면의 disasm**을 다룬다.

### 3.1 클래스 계층
`Disassembly : AbstractTableView` (BasicView/) → `CPUDisassembly : Disassembly` (Gui/) → `TraceBrowser` 는 별도 (AbstractTableView 직접 상속).

**분리 이유**:
- `BasicView/Disassembly` — 범용 disasm 렌더. reference view 나 hover popup 에서도 재사용
- `CPUDisassembly` — 라이브 디버깅 특화 컨텍스트 메뉴 ("Toggle breakpoint", "Run to selection", "Assemble")
- `TraceBrowser` — 과거 실행 기록. 레지스터/메모리 상태가 각 행마다 **동결된 스냅샷**

### 3.2 토큰 + 렌더 파이프라인
```
Capstone decode 결과 → ZydisTokenizer.tokenize(insn, &InstructionToken)
                                 ↓
           InstructionToken = list<SingleToken{type, text, value}>
                                 ↓
           Configuration::Colors[ token_type ] 매핑
                                 ↓
           RichTextPainter::List { CustomRichText_t{ text, color, background, flags } }
                                 ↓
           RichTextPainter::paintRichText(painter, x, y, width, height, xinc, list)
                                 ↓
           QPainter draw (mono font, 정렬된 column)
```

Token 타입 (대표):
- `Mnemonic`, `MnemonicNormal`, `MnemonicBranch`, `MnemonicCall`, `MnemonicRet`, `MnemonicPushPop`
- `GeneralRegister`, `FpuRegister`, `MmxRegister`, `SseRegister`, `AvxRegister`
- `MemorySize`, `MemoryBaseRegister`, `MemoryIndexRegister`, `MemoryScale`, `MemoryOperator`, `MemoryBrackets`
- `Value`, `Address`, `Space`, `Comma`
- `Prefix`, `Uncategorized`

**AURA 현재**: `src/gui/disasm_view.cpp` — switch/case 색상 고정. Token 열거 → 색상 테이블 lookup 으로 바꾸면 테마 파일 한 줄 수정으로 색 교체.

### 3.3 SideBar (점프 화살, BP gutter)
`CPUSideBar : QAbstractScrollArea` — CPUDisassembly의 scroll offset을 **수동 동기화**. 너비 고정 (약 40px).
- `drawBullets()` — BP 원형 아이콘 (active / disabled / HW)
- `drawJump()` — 가시 영역 내 분기 표적. backward/forward + 실행여부로 색 4가지
- `drawFoldingCheckbox()` — 함수 접기 ±
- `drawLabelArrows()` — 주소→레이블 가는 선

점프 아크 layout 알고리즘:
1. 가시 함수 범위에서 모든 branch instruction 수집
2. 동일 열 충돌 해결 위해 **column assignment (트랙)** — 짧은 점프 먼저, 긴 점프 뒤로
3. 각 아크를 `QPainterPath` (3개 세그먼트: from-out, vertical, in-to) 로 그림

**AURA 적용**: CFG view에서 in-out 엣지 렌더 대신 선형 disasm view에 점프 화살 렌더 — 현재 AURA는 없음. 저비용 고가치 기능.

### 3.4 Hover popup (`DisassemblyPopup`)
마우스를 주소 오퍼랜드에 올리면 **미니 Disassembly 인스턴스를 툴팁으로 띄움**. 해당 주소 기준 10-20 라인을 미리보기.
- 내부적으로 `Disassembly` 위젯을 `frameless Popup` 으로 감싸서 재사용 — P1 패턴의 실전 가치

### 3.5 Code folding (`CodeFoldingHelper`)
- 함수 / 영역 단위로 접기
- 접힌 영역은 `[+ 42 instructions]` 한 줄로 대체
- side bar ± 체크박스와 double-click 토글

---

## 4. Memory / Register / Stack views

### 4.1 HexDump 엔진

HexDump는 단순 hex 뿐 아니라 **다중 데이터 해석**을 하나의 뷰에서 스위치 가능 — 리버스 엔지니어링에서 핵심.

```
ColumnDescriptor {
    bool isData;            // raw 데이터 vs 주소/annotation 컬럼
    int itemCount;          // 행당 아이템 수 (보통 16)
    bool separator;         // 시각 구분선
    QString textCodec;      // ASCII/UTF-8/UTF-16/Shift_JIS/GBK 등
    DataDescriptor data;
}

DataDescriptor {
    Size itemSize;          // Byte / Word / Dword / Qword / Tword (10-byte FPU)
    union {
        ByteViewMode;       // HexByte / AsciiByte / SignedDec / UnsignedDec
        WordViewMode;       // HexWord / UnicodeWord / SignedDec / UnsignedDec / HalfFloat
        DwordViewMode;      // HexDword / Signed / Unsigned / FloatDword (IEEE 32)
        QwordViewMode;      // HexQword / Signed / Unsigned / DoubleQword (IEEE 64)
        TwordViewMode;      // FloatTword (x87 80-bit extended)
    };
}
```

컨텍스트 메뉴로 같은 메모리를 **byte hex → word dec → dword float → qword double** 으로 전환 — 구조체 역공학 시 필수.

**AURA 적용**: hex dump view (현재 read-only byte only). `ColumnDescriptor` 도입 → 데이터 해석 모드 5종 제공. 추가 비용: paint 함수 분기만 확장, 상태는 per-column 저장.

### 4.2 Selection / Copy
`SelectionData { firstSelectedIndex, fromIndex, toIndex }` — byte-level. Shift+click 확장. Copy 메뉴:
- Copy Selection (hex)
- Copy Selection (no spaces)
- Copy Address (절대)
- Copy RVA (모듈 상대)
- Copy File Offset (섹션 역산)

### 4.3 CPURegistersView
`RegistersView` 기반. 레지스터를 **카테고리 그룹**으로 나누고 그룹별로 접기:
- General (RAX..R15, RIP, RFLAGS 개별 플래그)
- FPU Stack (ST0..ST7, TagWord, StatusWord, ControlWord)
- SSE (XMM0..XMM15)
- AVX (YMM0..YMM15 / ZMM0..ZMM31)
- Segments (CS, DS, ES, FS, GS, SS + base/limit)
- Debug (DR0..DR7)

**Flag 바이트 레벨 편집**: RFLAGS 의 CF/PF/AF/ZF/SF/OF/DF/TF/IF 각 비트가 클릭 토글.

**Paint 접근**:
- QAbstractItemView 아니라 `QWidget::paintEvent` 에서 전체 직접 그림
- 레지스터 각 항목은 (label rect, value rect) pair 로 hit-test
- 더블클릭 → `EditFloatRegister` / `GotoDialog` 등 전용 다이얼로그

**AURA 적용**: 레지스터 뷰는 현재 없음 (AURA는 static analyzer). 그러나 **호출 규약 추정 결과 표시** (E-2 EH flow annotation 확장) 에 동일 패턴 사용 가능. "함수 X는 RDI, RSI, RDX 를 쓰고 RAX 반환" 을 이런 그룹 뷰로.

### 4.4 CPUStack (HexDump 재활용 예시)
`CPUStack : HexDump` — 베이스 HexDump 기능 + 스택 특화:

| 기능 | 구현 |
|------|------|
| User / system frame 구분 | `mUserStackFrameColor` vs `mSystemStackFrameColor` (RIP 모듈 비교) |
| Return address 하이라이트 | `mStackReturnToColor` (disasm 조회 → call 이면 표시) |
| SEH chain 표시 | `mStackSEHChainColor` (FS:[0] 체인 unwinding) |
| CSP / CBP 마커 | `gotoCspSlot` / `gotoCbpSlot` — 현재 스택/베이스 포인터로 점프 |
| 프레임 탐색 | `gotoPreviousFrameSlot` / `gotoNextFrameSlot` — CallStack과 연동 |
| "this" 포인터 | 해당 stack slot 이 class instance 로 보이면 `RTTI` 검색 후 vtable 표시 |

**재사용 가치**: HexDump에 color-overlay 훅만 노출했기 때문에 CPUStack은 300라인 내. 동일 훅으로 "heap block 시각화", "vtable 덤프 annotation" 등 추가 뷰를 경량 구현 가능.

---

## 5. Modules / Threads / CallStack / Breakpoints

### 5.1 ThreadView
`StdTable` 직접 서브. 14 컬럼. 데이터 소스는 `DbgGetThreadList()` (Bridge 경유). Context menu:
- Switch to thread (활성 스레드 변경)
- Suspend / Resume / Kill
- Set name (Windows 10+ `SetThreadDescription`)
- Go to thread entry (disasm 점프)
- Execute custom command (사용자 정의)

업데이트 트리거: `GUI_UPDATE_THREAD_VIEW` signal (Bridge 발신) → `updateThreadListSlot`.

### 5.2 CallStackView
`StdIconTable` — 아이콘은 party (User / System DLL) 구분. 7 컬럼 (Thread, Address, To, From, Size, Party, Comment).

**Unwind 소스**: `DbgFunctions()->StackCallStack` — DBGHelp `StackWalk64` 래핑. Fallback (심볼 없음): RBP chain walk.

**Suspected stack**: RBP/심볼 부재 시 heuristic — stack 을 훑어 "looks like return address" (코드 섹션 가리키고 preceding 명령이 call) 항목만 수집. AURA 의 PDA-lite mode와 유사 접근.

### 5.3 BreakpointsView
`StdTable`. BP를 **타입 그룹화**: Software(INT3) / Hardware(DR0-3) / Memory(page protect) / DLL(Load/Unload) / Exception(SEH hook).

Columns: Type, Addr, Module+Label, State, Disasm preview, Hits, Summary (condition + log + command + fast-resume 한 줄 합침).

**Conditional BP 모델** — 각 BP가 갖는:
- `breakCondition` (x64dbg expr)
- `logText` / `logCondition` (조건 만족 시 로그만 찍고 계속)
- `commandText` / `commandCondition` (커맨드 실행 후 계속)
- `fastResume` (UI update 생략)

→ Summary 열 한 줄 요약 덕에 100개 BP 도 훑어볼 수 있음.

**AURA 현재**: BP 개념이 없음 (static). 그러나 "조건부 re-analysis trigger" (이 함수가 재방문될 때마다 X 체크) 형태로 이 UX 를 재사용할 여지.

### 5.4 MemoryMapView
`StdIconTable`. 아이콘: 모듈 / 스택 / 힙 / mapped file / reserved.

컬럼: Address, Size, Party, Page info, Content (module path / "Stack (thread N)"), Allocation base, CurProtect, AllocProtect.

Context menu: BP (Access/Read/Write/Execute) 세분화 — 페이지 전체 또는 range.

---

## 6. Log / Script / Trace (텍스트 view 공통 패턴)

### 6.1 LogView
`QTextBrowser` 기반 — `QPlainTextEdit` 아닌 `QTextBrowser` 선택 이유:
- 하이퍼링크 자동 처리 (HTML `<a href=x64dbg://...>`)
- 내부 anchor navigation
- `setOpenLinks(false)` + `anchorClicked` signal → x64dbg 명령 dispatch (예: `disasm 0x401000`)

슬롯 2개:
- `addMsgToLogSlot(QString)` — 자동 escape
- `addMsgToLogHtmlSlot(QString)` — raw HTML (색상 diagnostic msg)

**Flush 전략**: BP loop 등에서 초당 수천 라인 로그 — append 마다 reflow 하면 UI freeze. 해결:
- 내부 `QStringList pendingMessages`
- `flushTimerSlot` — 50ms 간격 batch append
- `redirectLogSlot` — FILE* 파일 동시 write

**Find**: `findInLogSlot` + `findNext/Previous` — QTextBrowser built-in `find()`. 결과는 selection highlight.

**AURA 적용**: `src/gui/console_panel.cpp` 가 현재 `QPlainTextEdit`. Hyperlink 로 "decompile result 클릭 → AST view 이동" 같은 기능을 QTextBrowser + anchorClicked 로 저비용 추가 가능.

### 6.2 Script view
줄 번호 + 중단 / 실행 / 디버그 지원. 기본 `AbstractTableView` 패턴 재사용 — 행 = script instruction, 컬럼 = [ip, text, info]. IP 마커는 disasm 과 동일 RichTextPainter.

### 6.3 TraceBrowser
`AbstractTableView` 직접 상속. **CPUDisassembly와 구조적으로 거의 동일** 하지만:
- 데이터 소스 = `TraceFileReader` (디스크 파일, mmap)
- 각 행이 실행 당시 스냅샷: Index, Address, Opcode, Disassembly, Registers, Memory accesses
- 분기/루프 시각 (`drawFunctionGraphic`): 반복 블록은 "Loop start/mid/end" 기호
- 재생/역재생 — time-travel debugging 계열

**녹화 모델**: `toggleTraceRecording` — 각 명령 실행 후 Bridge 훅 → 직렬화 (컴팩트 포맷: delta encoding). 대용량 (수GB) 대비.

---

## 7. Symbol / Source views

### 7.1 SymbolView — master/detail split

```
┌─────────────────────────────────────────────────────────┐
│ Modules (StdIconSearchListView)                         │
│ ┌───────────────────────────────────────────────────┐   │
│ │ [filter edit..........................] [⟳]      │   │
│ │ 🟢 kernel32.dll   0x7FFE0000   PDB loaded        │   │
│ │ 🟡 user32.dll     0x7FFA0000   Export only       │   │
│ │ 🔴 target.exe     0x00400000   Loading...        │   │
│ └───────────────────────────────────────────────────┘   │
├─────────────────────────────────────────────────────────┤
│ Symbols in <selected module> (SearchListView)           │
│ ┌───────────────────────────────────────────────────┐   │
│ │ [filter..........................] [regex] [⟳]   │   │
│ │ CreateFileW      0x7FFE1234   Export             │   │
│ │ ReadFile         0x7FFE1340   Export             │   │
│ │ __security_init  0x7FFE2000   Local (PDB)        │   │
│ └───────────────────────────────────────────────────┘   │
└─────────────────────────────────────────────────────────┘
```

`SearchListView` 패턴:
- 상단 filter edit (회귀식 모드 토글)
- 중앙 StdTable
- 하단 status ("1,234 of 50,000 symbols")
- Filter는 **모든 컬럼 OR 검색** (기본) 또는 특정 컬럼 집중

**Symbol load 상태 색상** (`getCellColor`):
- 회색: not loaded
- 녹색: PDB loaded
- 노랑: export only
- 빨강: load failed
- 파랑: loading (async)

**AURA 적용**: AURA `src/gui/` 는 현재 symbol 검색이 단일 list. master/detail + filter 패턴으로 바꾸면 large binary (aura-self 에서 수천 함수) 에서 UX 수혜 큼.

### 7.2 Source view (source-level debug)
PDB source mapping 시 — file → lines list. `FileLines.h` 가 파일 캐시 (mmap + line offset index).

---

## 8. Dock widget layout

### 8.1 왜 MHTabWidget (QDockWidget 아님)?
x64dbg는 **QDockWidget 을 사용하지 않는다**. `MHTabWidget`이라는 커스텀 QTabWidget 서브클래스를 씀. 이유:
1. **탭 분리 → 독립 윈도우**: 탭을 드래그하면 별도 top-level 창 (`LabeledSplitterDetachedWindow` 계열 재사용)
2. **탭 재정렬 저장**: `loadTabSavedOrder`/`loadTabDefaultOrder` — JSON 지속화
3. **탭별 close 금지**: 디버깅 뷰는 닫히면 재생성 부담 — close 대신 hide + 메뉴로 복원
4. **탭 아이콘 + badge count**: Log 탭에 "new messages" 배지

### 8.2 LabeledSplitter (dock 유사)
접을 수 있는 세로/가로 splitter:
- 각 섹션에 label header (click → collapse/expand)
- drag grip으로 사이즈 조정
- `LabeledSplitterDetachedWindow` — 섹션을 별창으로 분리

**CPUWidget 레이아웃 예시**:
```
┌─ CPUWidget (QVBoxLayout) ────────────────────────────┐
│ ┌─ QSplitter Horizontal ─────────────────────────┐   │
│ │ ┌─ LabeledSplitter Vertical ────┐  ┌─ Regs ─┐ │   │
│ │ │ [SideBar][Disasm      ]       │  │ RAX..  │ │   │
│ │ │ --- (collapsible) ---         │  │ FPU    │ │   │
│ │ │ [ArgWidget]                   │  │ SSE    │ │   │
│ │ │ --- (collapsible) ---         │  └────────┘ │   │
│ │ │ [InfoBox]                     │             │   │
│ │ └───────────────────────────────┘             │   │
│ │ ┌─ LabeledSplitter Vertical ────────────────┐ │   │
│ │ │ [CPUMultiDump (tabbed dumps)]             │ │   │
│ │ │ --- (collapsible) ---                     │ │   │
│ │ │ [CPUStack]                                │ │   │
│ │ └───────────────────────────────────────────┘ │   │
│ └────────────────────────────────────────────────┘   │
└──────────────────────────────────────────────────────┘
```

Splitter state 는 `mDisasmSidebarSplitterStatus` 등 여러 QByteArray 로 저장/복원.

**AURA 시사점**: AURA 가 QDockWidget 을 안 쓴다면 (혹은 쓰다 복잡해졌다면) MHTabWidget + LabeledSplitter 조합으로 **더 예측 가능한 레이아웃** 을 얻을 수 있음. Qt6 `QDockWidget` 은 여전히 flaky (drag 도중 크래시 이슈 잔존) — 참고 가치 있음.

### 8.3 Qt6 대응 차이
| 요소 | Qt5 (x64dbg) | Qt6 (AURA) |
|------|-------------|-----------|
| `QAbstractScrollArea::setupViewport` | 동일 | 동일 |
| `QMdiArea` | 사용 가능 | 사용 가능 |
| `QFontMetrics::width` | deprecated 없음 | `horizontalAdvance` 필수 |
| `QTabBar::moveTab` | 동일 | 동일 |
| `QPainter::setRenderHint(Antialiasing)` | 동일 | 동일 |
| `QString::split` | `QString::SkipEmptyParts` | `Qt::SkipEmptyParts` |
| `QRegExp` | 기본 | `QRegularExpression` 강제 |
| High-DPI API | `QT_AUTO_SCREEN_SCALE_FACTOR` | built-in (기본 on) |
| Style Hint: dock tab 삭제 | N/A | `QTabBar::setDocumentMode` 변경 없음 |

포팅 시 x64dbg 코드 대부분은 **기계적 치환** 로 Qt6 빌드 통과. Regex + QFontMetrics 가 주요 마찰점.

---

## 9. Theming + Syntax highlighting

### 9.1 Configuration 레지스트리

`Utils/Configuration` 은 **QString → QColor / QFont / QKeySequence / QVariant** 4종 레지스트리. 모든 설정이 이 한 곳으로 흐름.

```
Configuration
├─ QMap<QString, QColor>        Colors      // "disasm.mnemonic", "hexdump.modified", ...
├─ QMap<QString, QFont>         Fonts       // "AbstractTableView", "Disassembly", "HexDump", "Stack", "Registers", "Log"
├─ QMap<QString, Shortcut>      Shortcuts   // "ActionStepOver", "ActionToggleBp", ...
└─ QMap<QString, QVariant>      Settings    // misc bool/int
```

**Signal**: `colorsUpdated()`, `fontsUpdated()`, `shortcutsUpdated()` — 모든 view가 구독 → 실시간 반영, 앱 재시작 불필요.

### 9.2 Theme JSON

x64dbg theme 파일 (사용자 배포 가능):
```json
{
  "name": "Ocean Dark",
  "author": "Somebody",
  "colors": {
    "disasm.mnemonic.default": "#DCDCDC",
    "disasm.mnemonic.call":    "#FF9F43",
    "disasm.mnemonic.ret":     "#FF5C5C",
    "disasm.mnemonic.jmp":     "#61DAFB",
    "disasm.register.general": "#FFEB7F",
    "disasm.register.fpu":     "#FFCB74",
    "disasm.memory.bracket":   "#808080",
    "disasm.value.hex":        "#CE9178",
    "hexdump.background":      "#1E1E1E",
    "hexdump.byte.00":         "#5A5A5A",
    "hexdump.byte.7F":         "#B4B4B4",
    "hexdump.byte.FF":         "#FF9F43",
    "hexdump.byte.printable":  "#61DAFB",
    "hexdump.modified":        "#FF5555",
    "stack.frame.user":        "#3C3C3C",
    "stack.frame.system":      "#2D2D2D",
    "stack.returnto":          "#FFEB7F",
    "log.warning":             "#FFCC00",
    "log.error":               "#FF5555"
  },
  "fonts": {
    "Disassembly":      {"family": "Consolas", "size": 10, "bold": false, "italic": false},
    "HexDump":          {"family": "Consolas", "size": 10},
    "Log":              {"family": "Consolas", "size": 9},
    "AbstractTableView": {"family": "Segoe UI", "size": 9}
  }
}
```

`AppearanceDialog` 구조:
- 좌측 tree: 카테고리 (Disassembly / HexDump / Stack / Registers / Log / General)
- 각 카테고리 아래 ColorInfo 목록
- `ColorInfo { propertyName, colorName, backgroundColorName, defaultBackgroundColorName, defaultFontName }`
- 우측 preview panel — 선택한 카테고리의 미니 뷰 실시간 렌더
- 하단 Save/Revert — `colorBackupMap`/`fontBackupMap` 으로 rollback

### 9.3 Syntax highlight flow (통합)

```
Data source (insn / byte / log line)
    ↓
Tokenizer (ZydisTokenizer / ByteClassifier / LogParser)
    ↓
[ (tokenType_str, text_str), ... ]
    ↓
for token in tokens:
    color = Configuration::Colors[ token.key ]     // "disasm.register.fpu"
    bg    = Configuration::Colors[ token.key + ".background" ]  // optional
    font  = Configuration::Fonts["Disassembly"]
    list.append( CustomRichText_t { text, color, bg, flags } )
    ↓
RichTextPainter::paintRichText( painter, list )
```

**AURA 적용 — 테마 시스템 부재 시 도입 순서**:
1. `src/gui/theme.{cpp,h}` — Colors/Fonts map + JSON load/save
2. 기존 `QPainter::setPen(Qt::red)` 등 하드코딩 → `theme::color("disasm.mnemonic.call")`
3. Tokenizer 가 이미 있다면 (decompile_view syntax highlight) token type → key 매핑 테이블 한 개 추가
4. AppearanceDialog 는 최후. 먼저 JSON 파일 수동 편집 지원

---

## 10. Shortcut manager

### 10.1 Registry 모델
`Configuration::Shortcut { QString Name; QKeySequence Hotkey; QKeySequence HotkeyDefault; QString Category; bool Global; }`

- `Name` — 내부 식별자 (예: "ActionStepOver")
- `Hotkey` — 현재 바인딩 (`QKeySequence::Keyboard`)
- `Category` — 메뉴 그룹 ("Debug", "View", "Memory", ...)
- `Global` — true 면 main window 레벨, false 면 특정 view 포커스 시에만 (AbstractTableView 내장 검색 단축키)

### 10.2 Action 과의 연결
`ActionHelper<T>` — mixin 으로 `AbstractTableView` 가 상속. `makeShortcutAction(QString name, void(T::*slot)())`:
- `QAction` 생성
- `Configuration::Shortcuts[name].Hotkey` 바인딩
- `shortcutsUpdated` 수신 시 자동 재바인딩
- 메뉴에 추가 시 단축키 텍스트도 자동 반영

### 10.3 ShortcutsDialog 편집 UX
- 좌측 카테고리 tree + 우측 filter edit
- 선택 시 하단 `ShortcutEdit` 위젯 — key capture 모드 (Ctrl, Shift, Alt 조합 수집)
- 충돌 감지 — 같은 `Global` scope 내 중복 시 경고
- Save/Revert — `ShortcutsBackup` 으로 rollback

**AURA 적용**: 현재 `.ui` 에 박힌 shortcut attribute → Configuration 기반으로 이전. 비용 낮음, 가치 높음 (사용자 커스터마이징).

---

## 11. Menu / Toolbar / Status bar

### 11.1 MainWindow 메뉴 구성

```
File   | Open / Attach / Detach / Recent / Exit
View   | CPU / Log / Memory Map / Call Stack / Threads / Breakpoints / Symbols / References / Handles / Trace / ...
Debug  | Run / Pause / Step Into / Step Over / Run to user / Trace ...
Plugins| <plugin-provided>
Favourites | <사용자 북마크>
Options| Preferences / Appearance / Shortcuts / Language / Topmost
Help   | About / Report Bug / Check Update / Donate
```

메뉴 런타임 수정: `MenuInfo` / `MenuEntryInfo` 구조체 + Bridge 훅. 플러그인이 메뉴 / 아이템 동적 추가/제거 — AURA 가 장래 플러그인 지원 시 참조.

### 11.2 Toolbar
`mFavouriteToolbar` — 사용자 즐겨찾기 툴/명령. 기본 toolbar (step/pause/run 등) 은 일반 `QToolBar`.

**중요**: x64dbg는 toolbar button 을 과도하게 노출하지 않음 — 대부분 기능은 컨텍스트 메뉴 + 단축키. Toolbar 는 10개 미만의 핵심 제어에 집중. UX lesson: **툴바는 희소할수록 가치 있다**.

### 11.3 StatusBar
- `DebugStatusLabel` — "Running" / "Paused" / "Terminated" 상태 + 색
- `LogStatusLabel` — 마지막 로그 라인 (탭이 닫혀있어도 주요 이벤트 놓치지 않게)
- 진행률 / 시간 / 스레드 수 등 작은 위젯 다수

**AURA 적용**: 현재 status bar가 단일 텍스트. 분석 상태 (aura "Analyzing function 42/128..."), 마지막 경고 tail 이 유용.

---

## 12. AURA 관점 관찰 + 적용 가능 패턴 Top 10

이 섹션은 **본 문서의 ROI 핵심**. AURA `src/gui/` 에 즉시 포팅 가능한 순서로.

### ① `AbstractTableView` 공통 베이스 도입 (P1) — **최상 ROI**
- 현재 AURA: `src/gui/` 의 call_graph_view, cfg_view, decompile_view, hex_dump_view 등이 각자 `QAbstractScrollArea` 또는 `QTableView` 를 개별 구현
- 포팅: `AbstractTableView` clean-room 재작성 (약 800 LOC 예상) → 위 뷰들 순차 이전
- 수혜: 단축키/컨텍스트 메뉴/color/font 반응 공통화. 새 view 추가 비용 40% 감소 예측
- 난이도: 중. **단일 PR 권장하지 않음** — 베이스 먼저, view 이전은 개별 PR

### ② Configuration registry + theme JSON (P9) — **최상 ROI**
- 현재 AURA: 색/폰트 하드코딩 (switch/case)
- 포팅: `src/gui/theme.{cpp,h}` ← JSON load + `QMap<QString, QColor/QFont>` + `themeChanged` signal
- 수혜: 테마 교체 재시작 불필요. 기여자가 JSON 으로 색 튠 가능
- 비용: 낮음 (200 LOC + call-site 치환)
- 선행 의존: ① 일부

### ③ `RichTextPainter` + Token → Color lookup (P7) — **높음**
- 현재 AURA: decompile_view 에서 문자열 수준 highlight. 토큰 경계 불명확
- 포팅: Token list 를 decompiler HIR/AST에서 생성 (이미 `hir_emit_*` 경로 존재) → RichTextPainter 계열로 paint
- 수혜: 점프 타입별 색, 레지스터/immediate 구분, 테마 연동
- 난이도: 중. Tokenizer 는 이미 있음 — 렌더만 교체

### ④ Bridge 스레드 모델 강화 (P4, P5, P6) — **높음**
- 현재 AURA: `analysis_worker` + dispatcher 존재. 그러나 signal 수가 적고 throttling 없음
- 포팅: Bridge-like hub (`aura_ui_bridge.{cpp,h}`) — analysis 결과 20+ 이벤트 signal, `QMap<EventType, QTimer>` throttling
- 수혜: 대형 바이너리 분석 중 UI lag 해소
- 비용: 중. 기존 signal 네이밍 정리 필요

### ⑤ HexDump multi-encoding ColumnDescriptor (P2) — **높음**
- 현재 AURA: hex dump byte-only
- 포팅: ColumnDescriptor 도입. Byte/Word/Dword/Qword + Float 해석 스위치
- 수혜: 구조체 역공학 UX 대폭 개선
- 비용: 낮음 (HexDump 는 이미 있음). paint 분기만 추가

### ⑥ Jump arrow side-bar (3.3 참조) — **중**
- 현재 AURA: disasm view에 선형 배치만
- 포팅: CPUSideBar clean-room 재작성. 점프 수집 → column 배치 → QPainterPath
- 수혜: 분기 구조 가시성
- 비용: 중 (300-500 LOC)

### ⑦ `LabeledSplitter` + `MHTabWidget` (P11, P12) — **중**
- 현재 AURA: QDockWidget 사용 (또는 미사용 — 확인 필요)
- 포팅: 탭을 분리 창으로 드래그 + 섹션 접기
- 수혜: multi-monitor 워크플로우, dock 안정성
- 비용: 중. 기존 레이아웃 대체 작업

### ⑧ Shortcut registry (P13) — **중**
- 현재: .ui 파일 shortcut 속성
- 포팅: Configuration::Shortcuts + ShortcutsDialog clean-room
- 수혜: 사용자 커스터마이징, 충돌 감지
- 비용: 낮음 (단, action 등록부 전수 수정)

### ⑨ Symbol master/detail + SearchListView (§7) — **중**
- 현재 AURA: 심볼 단일 list
- 포팅: 모듈 ↔ 심볼 2단. Filter edit 위젯 `SearchListView` 재사용
- 수혜: 10k+ 심볼 바이너리에서 검색성
- 비용: 낮음

### ⑩ Log view → QTextBrowser + hyperlink (§6.1) — **낮음 비용, 중 가치**
- 현재 AURA: `QPlainTextEdit`
- 포팅: QTextBrowser 로 스왑 + `x64dbg://` 유사 `aura://goto-func/0x401000` 링크 스킴
- 수혜: diagnostic → 소스 위치 ↔ disasm 점프
- 비용: 매우 낮음

### 패턴 제외 목록 (AURA 에 비적합)
- **Trace recording (TraceBrowser)** — AURA는 static. 불필요
- **CPURegistersView 원형** — AURA 는 debugger 아님. 단, 호출 규약 표시에 축소형 재사용 가능 (위 §4.3 말미)
- **BridgeResult 동기 blocking** — AURA worker 는 fire-and-forget 선호. 현재 모델 유지

---

## 13. Cross-reference (Task #33 / #36)

### 13.1 Task #33 (x64dbg pattern/symbol/CLI) 와 차이
| 영역 | #33 (surface 수준) | #37 (본 문서, 심층) |
|------|--------------------|------------------|
| Disasm | 토크나이저 타입 나열 | 전체 렌더 파이프라인, sidebar, hover popup, folding, CPUDisassembly context menu |
| Pattern 매칭 | YARA-like signature | 해당 없음 (본 문서는 GUI 전담) |
| CLI 명령 | 스크립트 `disasm addr` | 해당 없음 |
| 공통 | ZydisTokenizer 존재 사실 | 토큰→색 매핑, Configuration signal flow |

### 13.2 Task #36 (Bridge) 와 분업
- #36: GUI↔DBG Bridge C API (`_plugin_*`, `GuiAddLogMessage`, `DbgCmdExec`) — 즉 **디버거 코어 방향** 바인딩
- #37 (본 문서): Qt signal/slot + `BridgeResult` — GUI **내부** 스레드 안전 패턴
- 교집합: Bridge 싱글톤은 양쪽 경계. #36 은 Bridge의 C-facing 을, #37 은 Bridge의 Qt-facing 을 다룸

### 13.3 타 문서 triangulation 가능성
- `ghidra_disasm_analysis.md`: Ghidra 의 Swing ListingPanel vs x64dbg CPUDisassembly — 둘 다 token-based paint. AURA 용 공통 추상화 도출 가능
- `rizin_disasm_analysis.md`: TUI (ncurses) — 렌더 방법은 다르지만 **토큰 + 색 매핑 concept은 동일**
- 결론: AURA GUI의 disasm 렌더 아키텍처는 **Ghidra의 listing 구조 + x64dbg의 token/color registry + Rizin의 텍스트 variants** 삼각 참조로 설계

---

## 14. 인용

**Primary source (x64dbg GPL-3)**:
- Repository: https://github.com/x64dbg/x64dbg (development branch, HEAD as of 2026-04-21)
- `src/gui/Src/BasicView/AbstractTableView.{cpp,h}`
- `src/gui/Src/BasicView/HexDump.{cpp,h}`
- `src/gui/Src/BasicView/Disassembly.{cpp,h}`
- `src/gui/Src/Bridge/Bridge.{cpp,h}`
- `src/gui/Src/Gui/MainWindow.{cpp,h}`
- `src/gui/Src/Gui/CPUWidget.{cpp,h}`
- `src/gui/Src/Gui/CPUDisassembly.{cpp,h}`
- `src/gui/Src/Gui/CPUSideBar.{cpp,h}`
- `src/gui/Src/Gui/CPUStack.{cpp,h}`
- `src/gui/Src/Gui/CPURegistersView.{cpp,h}`
- `src/gui/Src/Gui/MemoryMapView.{cpp,h}`
- `src/gui/Src/Gui/ThreadView.{cpp,h}`
- `src/gui/Src/Gui/CallStackView.{cpp,h}`
- `src/gui/Src/Gui/BreakpointsView.{cpp,h}`
- `src/gui/Src/Gui/SymbolView.{cpp,h}`
- `src/gui/Src/Gui/LogView.{cpp,h}`
- `src/gui/Src/Gui/AppearanceDialog.{cpp,h}`
- `src/gui/Src/Gui/ShortcutsDialog.{cpp,h}`
- `src/gui/Src/Tracer/TraceBrowser.{cpp,h}`

**Related AURA docs**:
- `docs/research/x64dbg_analysis.md` (Task #33 — surface-level x64dbg analysis)
- `docs/research/ghidra_disasm_analysis.md`
- `docs/research/rizin_disasm_analysis.md`
- `docs/research/README.md` (v2 index)

**License note**: x64dbg source is GPL-3. This document records **architectural patterns, class hierarchies, and design intent** for clean-room reimplementation reference only. No x64dbg source code is copied into AURA. Any AURA adoption of the patterns described must be independently implemented.

---

**문서 끝.** Task #37 완료.
