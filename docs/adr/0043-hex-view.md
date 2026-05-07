# ADR-0043 — Phase 11.3.10 (P2.F5) Hex view dock (raw bytes 표시)

- **Status**: Accepted (planning)
- **Date**: 2026-05-04
- **Related**: ADR-0040 (F2 Disasm), ADR-0041 (F3 CFG), ADR-0042
  (F4 Decomp 강화), ADR-0036 (Cutter-style workspace),
  `include/mapped_file.h` + `src/core/mapped_file.c` (Phase D-10
  2-layer mmap I/O).

## Context

P2 의 F2/F3/F4 closed. F5 = hex view dock — Cutter/IDA/Ghidra style
의 address column + 16-byte hex 행 + ASCII column. **데이터는 raw
bytes 만; 분석 산출물 X.** 선결 자산: `MappedFile` (Win MapViewOfFile
/ POSIX mmap), `m_currentBinaryPath` (MainWindow), DisasmPane/CfgPane
mediator 패턴.

**핵심 차이점 (vs F2/F3/F4)**: hex 데이터는 "분석"이 아니다 — pdfj /
agfj 처럼 rizin 의 해석을 거치지 않는다. mmap 으로 binary 파일을
바이트 그대로 읽는 일은 R-9 의 "파생 분석" 정의 (CFG / IR / Type /
call graph / 함수 경계 자체 생성) 의 어느 항에도 해당하지 않는다.
F2/F3 의 "rizin 거쳐야 한다" 제약이 자연 완화된다.

## Decisions

### D1 — Data source: **mmap 직접 read (display-only path)**

`HexPane` 가 `MappedFile *` 핸들을 직접 보유. `mapped_file_open(path)`
로 바인딩, 페인 close 시 `mapped_file_destroy`. addr → file offset
매핑은 v1 에서 단순 동일시 (raw file offset = 표시 addr). 가상주소 ↔
file offset 변환은 v2 deferred.

**Reason**: (a) hex view 는 1 byte 단위 access — rizin RPC + JSON
라운드트립은 16 byte 행마다 호출이라 latency / 파싱비 모두 압도적
손해. mmap 은 OS page cache 위에서 page-size 단위 lazy load 라
100MB+ binary 도 free. (b) raw bytes 는 분석 산출 X —
`AuraEngineResponse` / record collection 에 들어가지 않으므로
R-12 single-source-of-truth 무관, R-9 무관. (c) 인프라 이미 존재
(`MappedFile`), 신규 의존성 0.

**Alternative A (rizin pxj)**: R-1/R-12 일관성은 강하지만 큰 binary
의 행마다 JSON 비용 + 분석 채널 오용. 거부.

**Alternative C (둘 다)**: 분기 매트릭스 2배. 거부.

### D2 — CLI scope: **CLI 추가 X (GUI-only)**

F2/F3 의 `aura disasm` / `aura cfg` 는 분석 산출 (instruction / CFG
record) 직렬화라서 headless 가치가 명확. Hex view 는 그저 raw
bytes — `xxd <bin>` / `od -An -tx1 <bin>` 가 이미 한 줄.

**Reason**: F2/F3 와의 비대칭은 "분석 vs 분석 아님" 의 자연스러운
결과. CLI 일관성은 분석 산출물 한정.

### D3 — GUI rendering: **QPlainTextEdit monospace (DisasmPane 패턴)**

`HexPane` = QPlainTextEdit (read-only, monospace). 행 format:
`"<addr16hex>  <16 byte 의 XX XX ...>  <ASCII non-printable=.>"`.
DisasmPane 의 mental model 답습.

**Reason**: 학습/테스트 비용 최소. cursorPositionChanged 로 addr
역계산 (line × 16 + col) 이 cross-pane sync 에 자연.

**Alternative B (QTableView 3 cols)**: column 폭 정렬 vs 가독성
trade-off, stylesheet 비용. 거부.

**Alternative C (custom paintEvent)**: IDA 레벨 컨트롤이지만 cost
수백 LoC. v2 deferred.

### D4 — Scrolling/paging: **mmap 전체 + viewport-driven lazy 행 생성**

mmap 자체는 lazy (OS page cache). 그러나 QPlainTextEdit 에 100MB
hex 텍스트 (16 byte/행 → 약 360MB ASCII) 일괄 push 는 죽는다. →
`HexPane` 가 viewport 변화를 받아 **보이는 행 ± buffer (e.g. ±200
rows) 만 lazy 생성**하여 textView 에 갈아끼움. mmap 영역 자체는
한 번에 전체 매핑 (cost 0 — virtual address space 만 잡음).

**Reason**: mmap 의 lazy page-fault + viewport-only 텍스트 생성 →
100MB+ binary 도 즉시 응답. PRD §1 의 "Cutter/IDA 레벨" 약속 일관성.

**Alternative C (v1 = ≤1MB 만)**: PRD 약속과 충돌. 거부.

### D5 — Cross-pane sync (v1): **단방향 in (다른 페인 → hex)**

v1 connection 2개:
1. `DisasmPane::instructionSelected(addr)` → `HexPane::scrollToAddr(addr)`
2. `CfgPane::blockActivated(addr)` → `HexPane::scrollToAddr(addr)`

**Reverse (hex 클릭 → DisasmPane)**: deferred. addr 가 instruction
boundary 가 아닐 수 있어 nearest-instruction snap 필요 + cache miss
edge case. F5 v2 또는 PP1 (data type cast) 에서 자연 등장.

**Reason**: F4 mediator 답습 (signal → main_window connect → slot).
"지금 보고 있는 instruction/block 의 raw bytes 도 같이 본다" 가 95%
user value — in 방향만으로 충족.

## Cycle plan (3 cycles + ADR)

| Cycle | Focus | Files |
|------|------|-------|
| C1 (cycle-18, this) | ADR + Phase 11.3.9 close 표기 | `docs/adr/0043-hex-view.md`, `AUTOMATION_ROADMAP.md` |
| C2 (cycle-19) | HexPane skeleton + MappedFile 바인딩 + 기본 렌더 (≤16KB) + gui_smoke 첫 행 검증 | `src/gui/hex_pane.{h,cpp}` (신규), `main_window.{h,cpp}`, `CMakeLists.txt`, `tests/integration/gui_smoke/{CMakeLists.txt, gui_smoke.cpp}` |
| C3 (cycle-20) | Viewport-driven lazy 행 생성 + scrollToAddr slot | `hex_pane.{h,cpp}` (resizeEvent / scrollContentsBy hook + fillRange) |
| C4 (cycle-21) | Cross-pane sync in (D5) + gui_smoke 강화 | `main_window.cpp` connect 2 lines |

## R-1 / R-9 / R-10 / R-12 guards (명시)

- **R-1**: hex view = raw bytes 표시. disassemble/analyze 아님. mmap
  = OS file I/O, "엔진" 의미 X.
- **R-9 (핵심)**: ADR 정의 — CFG/IR/Type/call graph/함수 경계 자체
  생성 금지. raw byte 표시는 그 어느 항에도 해당 X.
- **R-10**: rizin 헤더 / `RzCore *` / librz 링크 미사용. mmap 은
  plain `<sys/mman.h>` / `<windows.h>`.
- **R-12 (핵심)**: hex bytes 는 record 가 아니다 —
  `AuraInstructionRecord.bytes` 와 동일 데이터가 노출되더라도 hex
  pane 은 record 를 거치지 X **직접 mmap read**. Display-only path:
  `AuraEngineResponse.body` 에 새 type 추가 X, normalized records
  ingestion 도 거치지 X.

## Alternatives considered (요약)

- D1 rizin pxj: 분석 채널 오용. 거부.
- D1 둘 다: 매트릭스 2배. 거부.
- D2 CLI 추가: xxd 동치. 거부.
- D3 QTableView: 정렬 비용. 거부.
- D3 custom paint: 과대. v2.
- D4 페이지 단위 fetch: D1=mmap 와 중복. 폐기.
- D4 v1 작은 binary 만: PRD 약속 충돌. 거부.
- D5 양방향 v1: cache miss edge case. v2.
