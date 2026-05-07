# x64dbg Bridge 아키텍처 해체

> Task #36. Session #9 (2026-04-21). x64dbg (GPL-3, https://github.com/x64dbg/x64dbg) `src/bridge/` 단일 subsystem 심층. GPL-3 clean-room — 본 문서는 AURA 코드에 x64dbg 소스를 복사하지 않는다. 구조적 관찰만 기록한다.
> Sibling task #33 은 AURA 교차 4영역 한정, #35/#37/#38/#39 는 core/GUI/plugin/symbol 해체. 본 task 는 **bridge layer** 만.

---

## 1. Executive Summary

x64dbg 는 `x32dbg.exe` / `x64dbg.exe` 를 launcher 로 두고 **단일 프로세스** 내에서 세 DLL 이 협력한다:

- `x32bridge.dll` / `x64bridge.dll` — **Bridge**: C ABI 교환대, DLL 로더, 설정/번역 공유.
- `x32dbg.dll` / `x64dbg.dll` — **DBG**: 디버거 엔진 (Windows API, 아키텍처 종속).
- `x32gui.dll` / `x64gui.dll` — **GUI**: Qt 기반 사용자 인터페이스.

Bridge 는 **별도 프로세스가 아니다**. 공유 메모리·파이프 IPC 가 아니라 **같은 주소공간 DLL 간 함수 포인터 호출**이 기본 메커니즘이며, 여기에 (a) GUI→DBG 쪽은 직접 함수 포인터 dispatch, (b) DBG→GUI 쪽은 `GUIMSG` 정수 + void\* 파라미터 쌍을 Qt signal 로 main thread 로 thread-hop 하는 **단방향 비대칭 패턴**이 얹혀 있다. Bridge 자체는 얇고 (`bridgemain.cpp` 단일 파일 중심), API 안정성은 append-only enum + fixed-layout struct + `BRIDGE_IMPEXP` / `PLUG_IMPEXP` export 매크로에 의존한다.

**AURA 관점 핵심 3**: (i) AURA 는 단일 프로세스·단일 바이너리 구조여서 Bridge 의 "DLL 경계" 동기는 **직접 적용 불가**. (ii) 그러나 GUI↔core 경계를 "C ABI + 메시지 번호 + 불투명 void\*" 로 인위적으로 좁히는 **자기규율**은 AURA `src/gui/` ↔ `src/core/` `src/decompiler/` 경계를 규정하는 데 가치 있음. (iii) 장기 plugin 전략(PRD "MVP 이후 유보") 재도입 시 **`PLUG_SDKVERSION` + `CB_*` 이벤트 집합**이 가장 현실적 reference.

---

## 2. Bridge 진입점 및 초기화

### 2.1 DLL 경계의 물리적 형태

Bridge 는 `BUILD_BRIDGE` 매크로로 dllexport/import 를 뒤집는 전형적 Windows 동적 라이브러리 패턴:

```c
#ifdef BUILD_BRIDGE
  #define BRIDGE_IMPEXP __declspec(dllexport)
#else
  #define BRIDGE_IMPEXP __declspec(dllimport)
#endif
```

모든 공용 API (`BridgeInit`, `BridgeStart`, `DbgMemRead`, `GuiDisasmAt` …) 가 이 매크로로 export 된다. 헤더는 `extern "C"` 로 감싸 name mangling 을 차단하고, `#pragma pack(16)` (x64) / `pack(8)` (x86) 로 구조체 레이아웃을 고정해 DLL 간 binary compatibility 를 맞춘다.

### 2.2 3-단계 초기화

launcher 는 ① `InitializeUserDirectory` ② `BridgeInit` ③ `BridgeStart` 를 순차 호출한다.

1. **InitializeUserDirectory** (`bridgemain.cpp`) — working / user / INI 경로 확정. `szWorkingDirectory`, `szUserDirectory`, `szIniFile` (각 `MAX_PATH`) static 버퍼 채움. 사용자 override 가 있으면 디스크에서 설정 선로딩.
2. **BridgeInit(BRIDGE_CONFIG\*)** — `x64dbg.dll`, `x64gui.dll`, 기타 의존 DLL 을 `LoadLibrary` 로 올리고, 약 25 개 `_dbg_*` 함수 포인터 (`_dbg_memread`, `_dbg_addrinfoget`, …) 와 3 개 `_gui_*` 함수 포인터 (`_gui_guiinit`, `_gui_sendmessage`, `_gui_translate_text`) 를 `GetProcAddress` 로 해결. `InitializeCriticalSection(&csIni)`, `InitializeCriticalSection(&csTranslate)`. 실패 시 사람이 읽을 수 있는 에러 문자열 반환.
3. **BridgeStart** — `_dbg_sendmessage(DBG_INITIALIZE_LOCKS, …)` 로 DBG 측 자료구조 락 초기화 → `_gui_guiinit(argc, argv)` (GUI Qt 이벤트 루프 진입 = blocking) → 복귀 시 `BridgeSettingFlush` 로 INI persist → 정리.

즉 **프로세스 전체 라이프타임 = GUI 이벤트 루프 라이프타임**. DBG 는 GUI 가 띄운 워커 thread 들에서 돈다.

### 2.3 `bridgemain_checker.c`

별도 `.c` (C89) 파일로 bridge API 시그니처 불일치를 **compile-time** 검증한다. `_plugins.h` 포함된 plugin SDK 에 대해서도 동일 역할을 수행. 시그니처 표류 방지 장치 — API 안정성 전략의 일부.

---

## 3. GUI → DBG API

GUI 쪽은 DBG 함수 포인터를 **직접** 호출한다 (thread-hop 없음). Bridge 는 얇은 inline wrapper:

```c
BRIDGE_IMPEXP bool DbgMemRead(duint va, void* dest, duint size);
BRIDGE_IMPEXP bool DbgCmdExec(const char* cmd);
BRIDGE_IMPEXP bool DbgIsDebugging(void);
```

구현은 `return _dbg_memread(va, dest, size);` 형태. 약 25 범주:

| 범주 | 대표 함수 |
|------|-----------|
| Memory | `DbgMemRead/Write`, `DbgMemGetPageSize`, `DbgMemFindBaseAddr` |
| Execution | `DbgCmdExec`, `DbgInit`, `DbgExit`, `DbgIsDebugging` |
| AddrInfo | `DbgGetLabelAt`, `DbgSetCommentAt`, `DbgGetModuleAt` |
| Breakpoint | `DbgGetBpxTypeAt`, `DbgGetBpList` |
| Analysis | `DbgGetFunctionTypeAt`, `DbgGetLoopTypeAt`, `DbgAnalyzeFunction` |
| Symbol | `DbgSymbolEnum(CBSYMBOLENUM cb, void* user)` 콜백형 |
| Register | `DbgGetRegDumpEx(REGDUMP_AVX512*)` |
| XRef / Type | `DbgXrefAdd`, `DbgXrefGet`, `DbgTypeVisit` |

**관찰**: 동기 호출이다. GUI 스레드가 직접 DBG 함수로 들어간다. DBG 내부에서 공유 자료구조에 접근할 때는 DBG 자신의 읽기-쓰기 락으로 보호. 즉 bridge 는 락을 **소유하지 않고** DBG 가 자기 락을 관리한다.

예외: `DbgCmdExec` 은 명령어 문자열을 DBG 의 command queue 에 넣고 즉시 반환한다 — 디버거 명령어 dispatcher 는 별도 worker thread 에서 소비.

---

## 4. DBG → GUI 이벤트 (`Gui*` 함수군)

반대 방향은 **메시지 기반**. Bridge 가 제공하는 wrapper 는 내부적으로 `_gui_sendmessage` 하나로 수렴한다:

```c
__declspec(dllexport) void* _gui_sendmessage(GUIMSG type, void* param1, void* param2);
```

GUI 측 (`src/gui/Src/Bridge/Bridge.cpp`) 에서 이 심볼의 구현은 `Bridge::getBridge()->processMessage(type, p1, p2)` 로 위임되며, 내부는 **60+ case 의 거대한 switch(GUIMSG)** 다.

### 4.1 Thread-hop 패턴 3 종

| 패턴 | 용도 | 메커니즘 |
|------|------|---------|
| **Fire-and-forget Qt signal** | 대부분 view 업데이트 (`GUI_UPDATE_REGISTER_VIEW`, `GUI_ADD_MSG_TO_LOG`) | `emit xxx(...)` → `Qt::AutoConnection` 이 스레드 경계 넘을 때 자동 `QueuedConnection` 으로 승격 → Qt main thread 슬롯에서 실제 수행 |
| **Throttled signal** | 고빈도 뷰 갱신 (`GUI_UPDATE_ALL_VIEWS`) | `emit throttleUpdate(type)` → `throttleUpdateSlot` 이 rate-limit 후 `doUpdate()` |
| **Blocking bidirectional** | 반환값이 필요한 (`GUI_MENU_ADD`, 사용자 응답 다이얼로그) | `BridgeResult result(BridgeResult::MenuAdd); emit menuAddMenu(...); return (void*)result.Wait();` — 내부적으로 Windows event handle (`mResultEvents`) 에 대기. Qt slot 이 `setResult(...)` 후 SetEvent |

첫 번째 패턴 덕에 DBG worker thread 는 **절대 Qt 위젯에 직접 접근하지 않는다** (Qt 규칙). 세 번째 패턴은 deadlock 위험이 있으나 x64dbg 는 GUI→DBG 호출 내부에서 DBG→GUI blocking 을 지양하는 관례로 회피.

### 4.2 GUIMSG 카테고리 (약 70 종)

- Display: `GUI_DISASSEMBLE_AT`, `GUI_DUMP_AT`, `GUI_STACK_DUMP_AT`, `GUI_SET_DEBUG_STATE`
- Log/Status: `GUI_ADD_MSG_TO_LOG`, `GUI_ADD_STATUS_BAR_MSG`, `GUI_DISPLAY_WARNING`
- View refresh: `GUI_UPDATE_DISASSEMBLY_VIEW`, `GUI_UPDATE_REGISTER_VIEW`, `GUI_UPDATE_ALL_VIEWS`
- Script: `GUI_SCRIPT_ADD`, `GUI_SCRIPT_ERROR`, `GUI_SCRIPT_SETIP`
- Menu: `GUI_MENU_ADD`, `GUI_MENU_ADD_ENTRY`, `GUI_MENU_SET_ICON`
- Reference view: `GUI_REF_ADDCOLUMN`, `GUI_REF_SETCELLCONTENT`
- Graph/Type: `GUI_LOAD_GRAPH`, `GUI_TYPE_ADDNODE`, `GUI_TYPE_VISIT`
- User callback: `GuiExecuteOnGuiThreadEx(CBGUITHREAD cb, void* user)` — 임의 함수 GUI thread 에서 실행

---

## 5. Shared data structures

DLL 경계를 넘는 모든 데이터는 **POD struct + 고정 정렬 + 불투명 포인터** 규칙을 따른다.

### 5.1 Primitive 컨테이너: `ListInfo`

```c
typedef struct { int count; size_t size; void* data; } ListInfo;
```

가변 길이 배열을 DLL 간 전달하는 기본 수단. 호출자(=consumer)가 `BridgeFree(data)` 로 해제할 책임을 진다. `size` 는 반드시 `count * sizeof(T)` — `BridgeList<T>::ToVector()` 템플릿 래퍼가 size 불일치 시 assert.

### 5.2 핵심 POD 타입 (선별)

| 타입 | 역할 |
|------|------|
| `SELECTIONDATA { duint start, end; }` | GUI 선택 범위 |
| `SYMBOLINFO` | addr + decorated/undecorated 이름 + type + ordinal + 메모리-소유권 플래그 |
| `REGDUMP_AVX512` / `REGISTERCONTEXT_AVX512` | 전체 CPU 상태 (RAX-R15, RIP, FLAGS, x87, XMM/YMM/ZMM, MXCSR) |
| `DISASM_INSTR` | 바이트 + 타입 + operand 최대 3 (`DISASM_ARG`) |
| `FUNCTION { duint start, end, instrcount; }` | 함수 경계 |
| `LOOP { duint start, end; int depth; }` | 루프 바디 |
| `BRIDGE_ADDRINFO` | module + label + comment + bookmark + function + loop + args 통합 |
| `WATCHINFO` | 감시식 이름·조건·타입·값 |
| `TYPEVISITDATA` | 타입 tree visitor (재귀 상한 + 콜백) |

### 5.3 Control-flow graph 교환

`bridgegraph.h` 는 두 레이어를 제공한다:

- **C-ABI layer** (DLL 경계): `BridgeCFInstruction { duint va; unsigned char data[15]; }`, `BridgeCFNodeList { duint start, end, brtrue, brfalse; int instrcount; bool terminal; ListInfo exits; ListInfo instrs; }`, `BridgeCFGraphList { duint entry; ListInfo nodes; }`.
- **C++11 layer** (같은 모듈 내부 편의): `BridgeCFNode` (std::vector 로 exits/instrs), `BridgeCFGraph` (`std::unordered_map<duint, Node>` + parent map), 양방향 변환 함수 제공.

→ DLL 경계에서는 flat list, 내부에서는 STL. AURA 에 **직접적으로 이식 가치 높은 패턴** (§8 참조).

---

## 6. IPC / 동기화 모델

### 6.1 "같은 프로세스, 다중 thread"

한 번 더 강조: Bridge 는 프로세스간 IPC 가 아니다. Thread-level 동시성만 존재한다.

- **GUI Qt main thread** — 이벤트 루프, 모든 위젯/QPainter.
- **DBG debug loop thread** — `WaitForDebugEvent` / `ContinueDebugEvent`. 이 thread 가 peer 프로세스 (디버기) 이벤트를 받아 GUI 로 `GUIMSG` 를 flooding.
- **DBG command queue thread** — `DbgCmdExec` 가 넣은 명령어 소비. `src/dbg/msgqueue.cpp` 의 `MESSAGE_QUEUE { int msg; duint Param1, Param2; }` 큐 사용 (`MsgAllocQueue`, `MsgSend`, `MsgWait`, `MsgGet`).
- **Analysis worker thread** — 장시간 분석 (`DbgAnalyzeFunction`) 작업.

### 6.2 동기화 원시

Bridge 자체가 관리하는 락은 둘뿐이다:

- `csIni` (`CRITICAL_SECTION`) — `Utf8Ini settings` 보호 (`BridgeSettingGet/Set/Flush`).
- `csTranslate` — `GuiTranslateText` 번역 캐시.

그 외 공유 자료구조 (심볼 테이블, 메모리 맵, 함수 목록 …) 의 락은 **DBG 내부 소유** (`lock_memory`, `lock_modules`, `lock_threads` 등 DBG 측 락). Bridge 는 관여하지 않는다.

정적 플래그 `bDisableGUIUpdate` (unprotected, volatile 아님) + 매크로 `CHECK_GUI_UPDATE_DISABLED` — 배치 작업 중 GUI 스팸 차단. Unprotected 인 이유는 flag 가 "권고"여서 race condition 이 기능적 문제를 일으키지 않기 때문.

### 6.3 Memory ownership

`BridgeAlloc` / `BridgeFree` 를 bridge.dll 이 exports. 모든 cross-DLL 할당은 이 쌍을 사용해 "어느 DLL 의 heap 이 해제하느냐" 문제를 회피한다. 각 구조체는 인라인 fixed 배열 (`MAX_LABEL_SIZE=256`) 을 선호하며, 가변 길이는 `ListInfo` 로 통일.

---

## 7. 버전 호환성 전략

**형식적 semver 는 없다.** 대신 3 겹 방어:

1. **컴파일타임 프로토콜 버전 상수**: `DBG_VERSION = 25` 매크로. `BridgeGetDbgVersion()` 런타임 노출. GUI 기동 시 mismatch 면 거절 — 그러나 이는 "동일 zip 배포판끼리만 호환" 정책일 뿐이지 **독립 릴리스 간 호환 아님**.
2. **Append-only 규약**: `DBGMSG` / `GUIMSG` enum 값은 **끝에만 추가**, 중간 삽입·재배치 금지. `CB_*` 플러그인 이벤트 (37 종) 도 동일 규칙.
3. **ABI-친화 구조체**:
   - `#pragma pack(16)` (x64) / `pack(8)` (x86) 명시 정렬.
   - 포인터 대신 고정 buffer (`char name[256]`).
   - 확장 가능 영역은 끝에만 append.
   - 일부 타입은 `SYMBOLPTR` 처럼 **opaque 포인터 + 별도 getter** 패턴 — 내부 교체 시 헤더 재컴파일 불필요.

Plugin SDK (`_plugins.h`) 는 `PLUG_SDKVERSION = 1` 하나로 버저닝. `PLUG_INITSTRUCT { int pluginHandle; int sdkVersion; int pluginVersion; char pluginName[256]; }` 로 초기화 핸드셰이크. 이벤트 추가만 허용, 기존 콜백 시그니처 변경 금지.

**결론**: 엄격한 ABI 계약이 아니라 **규율 + append-only + same-build-required** 의 조합. 실전에서는 plugin 재컴파일 없이 디버거만 업데이트하면 깨지는 사례가 자주 보고됨.

---

## 8. AURA 관점 — GUI ↔ core 경계 재평가

AURA 는 PRD 에서 GUI ↔ core 분리를 강조하나 현재 구조는:

- `src/core/`, `src/decompiler/`, `src/parser/` 등이 정적 라이브러리 (`libaura_core.a` 또는 CMake object library) 로 번들.
- `src/gui/` 가 Qt6 앱으로 그 라이브러리를 링크.
- **프로세스 분리도 없고 DLL 경계도 없음.** 분리는 include path 와 함수 명명 규약에 의존.

### 8.1 Bridge 에서 **직접** 차용할 것 (2026-04-21 기준)

| 아이디어 | AURA 적용 형태 | 난이도 |
|---------|---------------|-------|
| `GuiExecuteOnGuiThreadEx(cb, user)` 패턴 | AURA GUI 의 decompile worker 가 `QMetaObject::invokeMethod(mainWindow, fn, Qt::QueuedConnection)` 로 결과 marshal (이미 부분 존재). bridge 의 콜백 + userdata 2-쌍 시그니처가 **void\* userdata 단일 슬롯**으로 단순. | 낮음 |
| `ListInfo { count, size, data }` flat container | AURA core→GUI 전달 시 C-ABI 수준 컨테이너 정의해 두면 추후 CLI `--decompile-all` JSON streaming (#25) 및 plugin 경계에 재사용 가능 | 낮음 |
| C-ABI 레이어 + C++11 편의 레이어 이중 정의 (bridgegraph.h) | AURA HIR / CFG 를 외부에 노출할 때 동일 패턴: `aura_cfg_t` (C POD) + `aura::Cfg` (C++ wrapper) | 중간 |
| `#pragma pack` + `MAX_*` 고정 크기 buffer | 경계 구조체 layout 고정 — ARM/x86-64 혼용 CI 에서 현 AURA 는 미보장 (`feedback_ci_hardcoded_build_rel.md` 와 별개 이슈) | 낮음 |

### 8.2 **차용하지 말 것**

- **세 DLL 분할**: AURA 는 정적 링크 원칙 (PRD 핵심 원칙 #4). Bridge 의 존재 이유 — plugin ABI 의 DLL 경계 — 가 AURA 에 없음.
- **`_gui_sendmessage` 거대 switch**: 60+ case dispatch 는 Qt signal/slot 과 중복. AURA 는 Qt signal 직접 사용이 자연스러움. `GUIMSG` 정수는 stable plugin ABI 목적일 때만 의미.
- **`BridgeResult` blocking event**: GUI 스레드에서 core 스레드로 blocking sync 호출은 deadlock 안티패턴. AURA 는 Qt `Qt::BlockingQueuedConnection` 또는 `QFutureWatcher` 로 충분.
- **`DBG_VERSION` hardcoded 상수**: AURA 가 plugin SDK 를 재도입하기 전까지 불필요.

### 8.3 v3.0.0+ plugin 재도입 시 reference 가치

PRD 는 "플러그인 시스템 MVP 이후 유보". 만약 재도입한다면:

- `PLUG_INITSTRUCT` 핸드셰이크 구조 (handle + sdkVersion + pluginVersion + name) 그대로 차용 가능.
- `CB_*` 이벤트 집합 중 AURA 에 의미 있는 것: `CB_LOADFILE` (ELF/PE open), `CB_ANALYZE` (함수 탐지 완료), `CB_ADDRINFO` (GUI addr info 요청 hook), `CB_MENUENTRY` (GUI 메뉴 확장), `CB_LOADDB/SAVEDB` (세션 영속).
- Ghidra `Plugin` Java 인터페이스 대비 x64dbg 방식이 **C ABI 로 가장 가볍다** — AURA C11/C++17 원칙과 정합.

---

## 9. Cross-reference (#33 / #35 / #37 / #38 / #39)

| 연관 task | 경계 | 본 문서와의 관계 |
|----------|------|-----------------|
| **#33** x64dbg_analysis.md | AURA 교차 4 영역 (pattern scan / PDB / CLI / Qt disasm) | Bridge 는 4 영역 외 — 별도 layer. 중복 없음. |
| **#35** x64dbg-core-engine (`src/dbg/`) | DBG 내부. `_dbg_*` 함수 포인터의 구현체, `msgqueue.cpp`, 락 구조 | 본 문서가 "DBG 내부 락은 DBG 소유" 로 넘긴 부분 = #35 심층. DBG_VERSION=25 의 의미도 #35. |
| **#37** x64dbg-gui-panels (`src/gui/Src/`) | GUI 내부. `Bridge.cpp` switch 각 case 가 emit 하는 signal 이 실제 어느 Qt widget slot 으로 가는지 | 본 문서 §4 의 "emit 이후"를 #37 이 담당. |
| **#38** x64dbg-plugin-scripting | `_plugins.h`, `CB_*` 37 이벤트, script engine | 본 문서 §7 의 plugin 얇은 요약을 #38 이 확장. |
| **#39** x64dbg-symbol-trace | Symbol engine + trace recording | `DbgSymbolEnum`, `SYMBOLINFO`, `SYMBOLPTR` opaque 포인터 실제 사용처 = #39. |

**본 task 고유 기여**: (a) Bridge 가 **프로세스 IPC 가 아니라 DLL 경계**임을 명시적으로 기록. (b) GUI→DBG 동기 직접 호출 vs DBG→GUI 비동기 메시지의 **비대칭성**. (c) `ListInfo` + C/C++ 이중 레이어 (`bridgegraph.h`) 패턴이 AURA 에 이식 가치 최상이라는 결론.

---

## 10. 인용

1. `src/bridge/bridgemain.cpp` — https://github.com/x64dbg/x64dbg/blob/development/src/bridge/bridgemain.cpp (BridgeInit, BridgeStart, Dbg\*/Gui\* wrapper 구현)
2. `src/bridge/bridgemain.h` — DBGMSG / GUIMSG enum, SELECTIONDATA / REGDUMP_AVX512 / DISASM_INSTR / BRIDGE_ADDRINFO / WATCHINFO / TYPEVISITDATA 선언
3. `src/bridge/_global.h` — `_dbg_*` / `_gui_*` 함수 포인터 extern 선언
4. `src/bridge/bridgegraph.h` — BridgeCFInstruction / BridgeCFNodeList / BridgeCFGraphList POD, BridgeCFNode / BridgeCFGraph C++ wrapper
5. `src/bridge/bridgelist.h` — ListInfo, BridgeList<T> 템플릿, BridgeAlloc/BridgeFree 규약
6. `src/gui/Src/Bridge/Bridge.cpp` — `_gui_sendmessage` switch, `BridgeResult::Wait`, Qt signal emit 패턴
7. `src/dbg/msgqueue.cpp` — MESSAGE_QUEUE, MsgAllocQueue / MsgSend / MsgWait / MsgGet
8. `src/dbg/_plugins.h` — PLUG_SDKVERSION=1, PLUG_INITSTRUCT, CB_\* 37 이벤트, \_plugin_registercallback
9. https://help.x64dbg.com/en/latest/developers/index.html — developer 가이드 (403 실패 — cache 또는 본문 우회 필요; 본 문서는 소스코드만 근거로 작성)
10. License: x64dbg 는 GPL-3. 본 문서는 **구조 관찰만 기록**하며 소스를 복사·인용하지 않는다. AURA 로의 실제 코드 이식은 clean-room 재구현 필요.

---

*작성: 2026-04-21, researcher teammate (Team v2-3-0-phase-2b, Task #36). 코드 수정 0. 커밋 없음.*
