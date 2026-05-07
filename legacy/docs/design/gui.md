# AURA GUI 설계 문서

> Phase 8.1 산출물. 작성일: 2026-04-03
> 사용자와의 설계 논의를 거쳐 확정된 GUI 아키텍처 및 기능 명세.

---

## 1. 개요

| 항목 | 결정 |
|------|------|
| GUI 프레임워크 | Qt6 (PRD D-1, 2026-03-25 확정) |
| GUI 언어 | C++17 (CLAUDE.md "신규 모듈은 C++17 권장" 준수) |
| DB 엔진 | SQLite (amalgamation, `third_party/sqlite/`, Public Domain) |
| DB 단위 | 프로젝트별 `.aura.db` |
| 프로젝트 구조 | Ghidra식 별도 경로 (`.aura/` 디렉토리) |
| 최근 프로젝트 | `~/.config/aura/config.json`에 최근 10개 경로 저장 |
| 엔진-UI 분리 | 단일 스레드 코어 + QThread/Signal-Slot (PRD D-9) |
| 백엔드 연동 | `extern "C"`로 기존 C API 호출 — 기존 코드 수정 없음 |
| UI 응답 목표 | ≤ 100ms (PRD §5) |
| 단축키 | MVP 미구현, 기능 확정 후 일괄 배정 |

### 설계 원칙

1. **분석 엔진 ↔ UI 스레드 완전 분리** — 분석 중 UI 동결 방지 (PRD §4.4)
2. **기존 C 백엔드 무수정** — GUI 모듈(`src/gui/`)만 C++17, 나머지 C11 유지
3. **MVP 우선** — 핵심 기능으로 동작 확보 후 확장

---

## 2. 프로젝트 저장 구조

```
사용자 지정 경로/
├── MyProject.aura/              ← 프로젝트 디렉토리
│   ├── project.json             ← 프로젝트 메타 (이름, 생성일, 바이너리 목록)
│   ├── binaries/
│   │   ├── target1.elf.aura.db  ← 바이너리별 분석 DB (SQLite)
│   │   └── target2.elf.aura.db
│   └── exports/                 ← 내보내기 결과물
```

- DB 스키마에 변경 이력 컬럼 (who/when/what) 포함 — Phase 8 협업 서버 (8.53~8.55) 확장 대비
- 하나의 프로젝트에 여러 바이너리 포함 가능 (Ghidra와 동일)
- 프로젝트 디렉토리 복사만으로 이동/공유 가능

### 바이너리 로드 방식 (혼합)

| 방식 | 동작 | 용도 |
|------|------|------|
| **File > Open** | mmap 직접 참조 — 빠름, 원본 필요 | 로컬 바이너리 분석 |
| **File > Import** | 프로젝트에 복사 후 mmap — 이동성 확보, 원본 불필요 | 프로젝트 공유/이동 |

---

## 3. 레이아웃

```
┌───┬──────────────┬──────────────────┬────────────────┐
│   │              │                  │  디컴파일 뷰    │
│ 아│  선택된 패널  │  중앙             │  (Pseudo-C)    │
│ 이│  (토글 전환)  │  디스어셈블리      ├────────────────┤
│ 콘│              │  Hex (탭)        │  LLM 패널      │
│ 바│              │                  │  (분석/질의)    │
│   │              │                  │                │
├───┴──────────────┴──────────────────┴────────────────┤
│ 상태바                                                │
└──────────────────────────────────────────────────────┘
```

### 3.1 좌측 패널

Binary Ninja식 **아이콘 사이드바 + 패널 토글 전환**. 한 번에 하나만 표시. 같은 아이콘 재클릭 시 닫힘.

| # | 패널 | MVP | 내용 |
|---|------|:---:|------|
| 1 | 심볼 목록 | O | 함수/변수/import/export. 타입별 필터, 검색, 정렬. 더블클릭→뷰 이동 |
| 2 | 문자열 목록 | O | 바이너리 내 추출 문자열 + 참조 주소. 최소 길이 필터 |
| 3 | 데이터 타입 | O | Level 1: 읽기 전용 (추론 결과 표시). Level 2~3은 이후 확장 |
| 4 | 섹션/세그먼트 | O | 섹션 트리, 주소/크기/권한 |
| 5 | 북마크 | O | 사용자 마커. 카테고리/설명/주소. DB 저장 |

### 3.2 중앙 뷰

| # | 뷰 | MVP | 내용 |
|---|-----|:---:|------|
| 1 | 디스어셈블리 | O | 주소·바이트·니모닉·오퍼랜드 테이블. 컨텍스트 메뉴, 클립보드, 호버 툴팁, 컬럼 커스터마이징 |
| 2 | Hex | O | 원시 바이트 + ASCII. 컨텍스트 메뉴, 클립보드 |
| 3 | CFG 그래프 | 이후 | DOT 렌더링. 백엔드 `cfg_print_dot()` 이미 구현 |
| 4 | Call Graph | 이후 | `aura_callgraph_file()` 이미 구현 |
| 5 | 패치 편집기 | 이후 | `patch_apply()` 이미 구현 |
| 6 | Stack Layout | 이후 | 백엔드 구현 필요 |

### 3.3 우측 상단 — 디컴파일 뷰

- Pseudo-C 출력, QSyntaxHighlighter 기반 문법 하이라이팅
- 분석 완료 시 **자동 표시** (Ghidra식)
- 컨텍스트 메뉴, 클립보드, 호버 툴팁

### 3.4 우측 하단 — LLM 패널

| # | 기능 | MVP | 이후 |
|---|------|:---:|:---:|
| 1 | 함수 요약 | O | — |
| 2 | 함수명 제안 | O | — |
| 3 | 취약점 분석 | — | O |
| 4 | 대화형 질의 | — | O |
| 5 | 분석 히스토리 | — | O |

### 3.5 상태바

| 영역 | 표시 내용 | MVP |
|------|----------|:---:|
| 현재 주소 | hex 표시 | O |
| 파일 오프셋 | 가상주소 ↔ 파일 오프셋 매핑 | O |
| 심볼릭 위치 | `main+0x1A` 형태 | O |
| 바이트 값 | 현재 주소의 원시 바이트 | O |
| 파일 정보 | 포맷 + 아키텍처 | O |
| 분석 진행률 | 프로그레스바 + 취소 버튼 | O |
| 오류/경고 | 분석 중 문제 표시 | O |
| 증분 검색 | 타이핑 중 실시간 표시 | O |

### 3.6 툴바

| 그룹 | 버튼 |
|------|------|
| 파일 | Open, Save |
| 편집 | Undo, Redo |
| 탐색 | Back, Forward, 주소 입력창 |
| 검색 | Search |
| 분석 | Run Analysis |
| 뷰 | Function Graph, Decompiler |
| 기타 | LLM Analyze, 북마크 추가 |

---

## 4. 메뉴 구조

### File
Open, Import, Recent Projects (10개), Save Project, Export (ASM/JSON/C bytes/Hex dump), Close, Exit

### Edit
Undo (Ctrl+Z), Redo (Ctrl+Shift+Z), Program Options, Tool Options

### Navigation
Go to Address (Ctrl+G), Go to Function, Back (Alt+←), Forward (Alt+→), Next/Previous Function

### Search
Memory (바이트 시퀀스), Program Text, Strings, Instructions, Direct References, Indirect References, Scalars, YARA Rules

### Select (메뉴 존재, 기능 이후 구현)
All, None, All Instructions, All Data, All Undefined, Current Function, Forward/Back References, Dead Subroutines

### Analyze
Auto Analysis (ON/OFF), Functions, CFG, Call Graph, DFG, Current Analysis Options

### Window
Disassembly, Decompiler, Hex View, LLM Panel, Function Graph, Function Call Tree, Memory Map, Console/Messages

### LLM
Summarize Function, Suggest Name, Settings

### Tools (메뉴 존재, 기능 이후 구현)
Script Manager, REPL, Patch Editor

### Help
About, Documentation, Shortcuts

---

## 5. 이벤트 흐름

### 5.1 앱 시작

```
앱 실행 → Project Manager 창 표시
  ├─ 최근 프로젝트 목록 (config.json에서 로드, 존재 확인 후 정리)
  ├─ New Project → 이름 + 경로 선택 → .aura/ 디렉토리 생성
  ├─ Open Project → 기존 .aura/ 선택
  └─ 프로젝트 선택 → MainWindow (분석 창) 열림
```

### 5.2 파일 로드

```
File > Open  → 파일 선택 → mmap 직접 참조
File > Import → 파일 선택 → .aura/binaries/에 복사 → mmap
  ↓
첫 실행: 로드 옵션 다이얼로그 (포맷/아키텍처 확인)
이후: 자동 로드 (DB 설정 사용). 메뉴에서 Program Options로 접근 가능
```

### 5.3 자동 분석

```
설정: Auto Analysis [ON/OFF] 토글

ON (기본값): 로드 완료 → 기본 분석기 전체 즉시 시작 (백그라운드 QThread)
OFF: 로드 완료 → 분석기 선택 다이얼로그 표시 → 확인 후 시작

공통:
  - 상태바에 진행률 바 + 취소 버튼
  - Analyze > Current Analysis Options에서 분석기 상태 확인/변경
  - UI는 분석 중에도 반응 (비블로킹)
```

### 5.4 분석 완료 후

```
커서 초기 위치: main() 우선 (기본값), entry point 모드로 전환 가능
  - main 심볼 있음 → main()으로 이동
  - main 심볼 없음 → entry point로 fallback

디컴파일 뷰: 자동 표시 (우측 상단)
```

### 5.5 뷰 동기화

```
동기화 ON (기본값): 디스어셈블리 클릭 ↔ 디컴파일 자동 따라감 (양방향)
동기화 OFF: 각 뷰 독립, Tab 키로 수동 전환
```

### 5.6 저장/종료

```
자동 저장: 기본 OFF, Tool Options에서 ON 가능 (ON 시 일정 간격 자동 저장)
종료 시: 저장 확인 다이얼로그

상태 복원 범위 (전체):
  - 커서 위치
  - 열린 뷰 목록
  - 창 크기/위치
  - 패널 레이아웃
  - Navigation 히스토리
  - 북마크
```

---

## 6. 검색 기능

| # | 기능 | MVP | 이후 |
|---|------|:---:|:---:|
| 1 | Go to Address | O | — |
| 2 | 심볼 이름 검색/이동 | O | — |
| 3 | 문자열 검색 | O | — |
| 4 | 바이트 패턴 검색 (Hex) | — | O |
| 5 | 와일드카드 패턴 (`90 ?? CC`) | — | O |
| 6 | Xref To/From | — | O |
| 7 | 디스어셈블리/디컴파일 텍스트 검색 | — | O |
| 8 | 정규식 검색 | — | O |
| 9 | 상수값 검색 (immediate) | — | O |
| 10 | YARA 규칙 검색 (기본 내장) | — | O |
| 11 | 스크립트 기반 검색 | — | O |

---

## 7. 백엔드 API 연동

GUI는 기존 C API를 `extern "C"`로 호출. 주요 API:

| 계층 | 헤더 | 주요 함수 |
|------|------|----------|
| 고수준 파이프라인 | `pipeline.h` | `aura_disasm_file()`, `aura_info_file()`, `aura_cfg_func()`, `aura_dfg_func()`, `aura_callgraph_file()` |
| 파일 파싱 | `file_format.h` | `file_info_create()`, `file_info_destroy()` |
| 디스어셈블 | `disasm.h` | `disasm_init()`, `disasm_run()`, `disasm_destroy()` |
| 디컴파일 | `decompiler.h` | `ir_lift()`, `ir_build_ssa()`, `ir_optimize()`, `ir_emit_pseudoc()` |
| 패치 | `patch.h` | `patch_encode()`, `patch_apply()` |
| 함수 탐지 | `func_detect.h` | `func_detect()`, `func_detect_print()` |
| CFG | `cfg.h` | `cfg_build()`, `cfg_print_dot()` |

---

## 8. AURA 차별화 포인트

| 항목 | IDA Pro | Ghidra | Binary Ninja | AURA |
|------|---------|--------|-------------|------|
| LLM 기본 내장 | 플러그인 | 플러그인 | Sidekick(유료) | **기본 제공** |
| 로컬 LLM | X | X | X | **기본 제공** |
| YARA 기본 내장 | 플러그인 | 플러그인 | 플러그인 | **기본 제공 (목표)** |
| 디컴파일러 포함 | 별도 구매 | 기본 | 기본 | **기본** |
| 가격 | $2,000+ | 무료 | $300+ | **무료** |
| 네이티브 성능 | O | X (Java) | O | **O (C/C++)** |
| 실시간 협업 | Team Server(유료) | Ghidra Server | Enterprise(유료) | **목표 (Phase 8)** |
