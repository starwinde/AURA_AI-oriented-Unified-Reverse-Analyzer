# x64dbg Core Engine 해체 분석

> Session #9 (2026-04-21), Task #35. GPL-3 clean-room scope.
> 대상: `src/dbg/` (breakpoint / memory / thread / exception / stepping).
> 본 문서는 **동적 debugger 의 runtime core** 를 해체한다. Task #33 `x64dbg_analysis.md` 가 다룬 4 교차 scope (pattern / PDB / CLI / disasm UX) 와 **중복 없음**.
> 형제 Task scope 경계: #36 (bridge), #37 (GUI), #38 (plugin+scripting), #39 (symbol+trace) 는 별도.

---

## 1. Executive Summary

x64dbg 의 core engine 은 5 개 subsystem 으로 명확히 분리된다: **Breakpoint Manager** (`breakpoint.cpp/h`), **Memory subsystem** (`memory.cpp/h`), **Thread registry** (`thread.cpp/h`), **Exception dispatch** (`exception.cpp/h`), **Stepping engine** (`debugger.cpp/h`). 모두 Windows user-mode Debug API (`DEBUG_EVENT` 루프 + `GetThreadContext` + `VirtualQueryEx` + DR0-3) 에 강결합되어 있으며, 저수준 기계 조작은 대부분 **TitanEngine** wrapper (SetBPX / SetMemoryBPXEx / StepInto / StepOver / GetContextDataEx) 에 위임한다. x64dbg 고유의 가치는 (a) BP 5 타입 (BPNORMAL/BPHARDWARE/BPMEMORY/BPDLL/BPEXCEPTION) 통합 레지스트리, (b) `Range → MEMPAGE` 캐시 + VirtualQueryEx/VAD/PE-section/TEB/PEB 3-phase enumeration, (c) 예외 코드/NtStatus/Win32 3 DB 병렬 lookup, (d) StepOver 의 "call 다음 주소에 임시 BP" 패턴 + RET opcode (C3/C2) 기반 step-out 휴리스틱에 집중된다.

AURA 는 **정적 RE** 이므로 runtime BP/stepping 은 전면 scope out 이다. 단 하나의 간접 연결: x64dbg 의 exception dispatch 가 `.pdata`/`.eh_frame` 파싱 결과를 활용하지는 않으나, AURA `src/parser/eh_frame_parser.c` + `src/parser/seh_parser.c` + `src/decompiler/exception_flow.c` (2ebe264 E-2) 는 동일한 예외 정보 테이블을 **정적 관점**에서 본다 — x64dbg 의 exception taxonomy (MS_VC_EXCEPTION, SetThreadName, C++ EH) 가 AURA HIR_COMMENT annotation 품질 비교의 참조로 의미 있을 수 있다. 그 외 본 문서의 내용은 **AURA 에 이식 제안 대상이 아니며 구조적 해체가 유일한 산출 목적**이다.

---

## 2. Breakpoint Manager 해체

### 2.1 타입 분류와 통합 레지스트리

`breakpoint.h` 가 정의하는 BP 타입:

```cpp
enum BP_TYPE {
    BPNORMAL    = 0,  // SW BP (int3 / 0xCC)
    BPHARDWARE  = 1,  // HW BP (DR0-3)
    BPMEMORY    = 2,  // 페이지 보호 기반
    BPDLL       = 3,  // LOAD_DLL_DEBUG_EVENT 후킹
    BPEXCEPTION = 4,  // 특정 exception code 브레이크
};
```

단일 전역 맵이 모든 타입을 수용한다:

```cpp
// breakpoint.cpp 의 핵심 상태 (추정)
std::map<BreakpointKey, BREAKPOINT> breakpoints;
// BreakpointKey = (BP_TYPE, ModHash, module-relative addr)
// BPEXCEPTION 만 addr 자체를 key 로 씀 (모듈 무관)
```

`BpNew()` 는 (1) 주소 검증 → (2) `ModBaseFromAddr` 로 모듈 상대 주소 계산 (`bp.addr = Address - moduleBase`) → (3) `breakpoints.emplace(key, bp).second` 반환. 모듈 상대 저장 덕분에 ASLR rebase 후에도 BP 가 추적된다.

### 2.2 BREAKPOINT 필드 (핵심만)

- 식별/상태: `duint addr`, `bool enabled`, `bool active`, `bool silent`, `bool singleshoot`, `bool fastResume`
- SW 복원: `unsigned short oldbytes` (최대 2 바이트 — int3 1 바이트 + long int3 `0xCD 0x03` 대응)
- HW 인코딩: `DWORD titantype` — 상/하위 니블에 DR-slot, access-type, size 팩킹
- 메타: `std::string name`, `std::string module`, `uint32 hitcount`
- 조건부 실행: `breakCondition`, `commandCondition`, `commandText` (expression evaluator)
- 로깅 BP: `logText`, `logCondition`, `logFile`

### 2.3 SW BP 삽입/해제 (int3)

실제 메모리 writing 은 TitanEngine 위임:

```cpp
// 주소의 현재 바이트 저장 후 int3 쓰기
if(!MemRead(Address, &bpInfo->oldbytes, sizeof(bpInfo->oldbytes)))
    return false;
SetBPX(Address, bpInfo->titantype, cbUserBreakpoint);
// 삭제 시:
DeleteBPX(Address);  // oldbytes 자동 복원
```

포인트: `oldbytes` 를 `unsigned short` 로 저장하는 이유는 Windows 디버거 호환 "long int3" (`CD 03`) 대응.

### 2.4 HW BP (DR0-3)

`titantype` 이 DR 레지스터 설정의 모든 정보를 담는다:

```cpp
TITANGETDRX(titantype)   // UE_DR0..UE_DR3
TITANGETTYPE(titantype)  // execute / write / read-write
TITANGETSIZE(titantype)  // 1 / 2 / 4 / 8 bytes
```

TitanEngine 의 `SetHardwareBreakPoint` 가 DR7 bits 를 조작하여 4 개 slot 중 하나를 할당. slot 고갈 시 에러 반환 (x64dbg 가 retry 로직 없음 — 사용자가 해제).

센티넬 `TITANSETDRX(titantype, UE_DR7)` 는 "아직 활성화 안 됨" 표식 — 프로세스 로드 중 잘못된 삭제 방지.

### 2.5 Memory BP (페이지 보호)

`memsize` 필드가 감시 영역 바이트 수. TitanEngine 의 `SetMemoryBPXEx` 가 페이지 보호를 `PAGE_GUARD` 또는 `PAGE_NOACCESS` 로 바꾸어 접근 시 `EXCEPTION_GUARD_PAGE`/`EXCEPTION_ACCESS_VIOLATION` 유발, 핸들러에서 원 보호로 복원 + single-step 한 후 재설정. singleshoot 이면 재설정 생략.

### 2.6 Conditional / Logging BP

`BpCheckHit()` (exception handler 경유 호출) 가 순서대로:
1. `breakCondition` 평가 (expression) — false 면 조용히 continue
2. `logCondition` 평가 → true 면 `logText` 포맷 후 `logFile` 에 append
3. `commandCondition` → true 면 `commandText` 를 `cmddirectexec` 로 실행 (`CommandCondition` 으로 script 분기)
4. 실제 break 여부는 `breakCondition` 만 결정

`fastResume` 플래그는 "로그만 쓰고 UI 갱신 skip" — 성능 모드.

---

## 3. Memory Subsystem

### 3.1 Read/Write wrapper 계층

| 함수 | 의미 | 용도 |
|------|------|------|
| `MemReadDumb` | 단순 `ReadProcessMemory` | 내부 저수준 |
| `MemReadUnsafe` | 캐시 bypass + 에러 무시 | 빠른 경로 |
| `MemReadSafePage` | guard-page 감지 + zero-fill | 디스어셈블 read 경로 |
| `MemRead` | 페이지 단위 loop + `ERROR_PARTIAL_COPY` 허용 | 일반 API |
| `MemWrite` / `MemPatch` | `WriteProcessMemory` + patch map 기록 | editor 경로 |

### 3.2 Guard-page 처리 (`IgnoreThisRead`)

`QueryWorkingSetEx` 로 페이지가 **주소 공간에 존재하나 working set 에서 invalid** 인지 확인. 그런 경우 `ReadProcessMemory` 를 호출하면 page fault → 프로세스 일시정지가 아니라 디버거 실패. 그래서:

```cpp
if(IgnoreThisRead(addr)) {
    memset(out, 0, size);
    if(bytesRead) *bytesRead = size;
    return true;  // 성공처럼 반환
}
```

사용자 UX 관점: 페이지가 읽히지 않을 때 "???" 대신 `00 00 ..` 로 채워 디스어셈블 연속성을 유지. AURA 는 정적 파일을 다루므로 이 문제 없음 (page가 전부 존재).

### 3.3 Memory Map 캐시 (`MemUpdateMap`)

3-phase pipeline:

1. **QueryMemPages**: `VirtualQueryEx` 를 `lpMinimumApplicationAddress` 부터 순회. `MEMORY_BASIC_INFORMATION` 의 `AllocationBase` 가 동일한 연속 region 을 하나의 entry 로 병합 → `std::map<Range, MEMPAGE>`.
2. **ProcessFileSections**: 각 module 의 PE header 를 읽어 section table 을 얻고, 위 coarse region 을 section 단위로 분할 (code `.text` / data `.rdata` / `.data` / `.rsrc` 등). Windows 11 24H2+ 의 hotpatch page 도 별도 label.
3. **ProcessSystemPages**: Thread list 순회 → 각 TEB 의 `NT_TIB.StackBase/Limit` 추출 → "Stack (TID)" label. PEB 의 heap list → "Heap (ID)" label.

결과는 `std::map<Range, MEMPAGE, RangeCompare>`, `RangeCompare` 가 address → containing range 를 O(log n) 으로 찾게 함. `MemFindBaseAddr` 는 이 캐시 lookup 만 수행 (refresh 파라미터 true 일 때만 `MemUpdateMap` 재실행).

### 3.4 Lazy invalidation

자동 TTL 없음. 모든 query 함수가 `bool Refresh` 옵션을 받아 명시적 갱신. debugger 가 `LOAD_DLL_DEBUG_EVENT` / `UNLOAD_DLL_DEBUG_EVENT` / `CREATE_THREAD_DEBUG_EVENT` 를 처리할 때마다 `MemUpdateMapAsync` 로 비동기 refresh 요청 (`memMapThreadCounter` 카운터 기반 dedup).

### 3.5 Pattern search 연계

`MemFindInPage` / `MemFindInMap` 이 Task #33 에서 분석된 `patternfind` 를 래핑. `MemFindInMap` 은 메모리 맵을 순회하며 각 readable region 에 대해 `MemRead` + `patternfind` 호출 + progress callback.

---

## 4. Thread Context

### 4.1 THREADINFO 필드

```cpp
struct THREADINFO {
    DWORD  ThreadId;
    HANDLE Handle;
    int    ThreadNumber;           // 1,2,3... 사람 친화적 index
    duint  ThreadStartAddress;
    duint  ThreadLocalBase;        // = TEB base
    char   threadName[...];        // SetThreadDescription / MS_VC_EXCEPTION
};
```

레지스트리: `std::unordered_map<DWORD, THREADINFO> threadList`, `LockThreads` (shared_mutex) 보호. 읽기는 `SHARED_ACQUIRE`, 쓰기는 `EXCLUSIVE_ACQUIRE` — `CREATE_THREAD_DEBUG_EVENT` / `EXIT_THREAD_DEBUG_EVENT` 경로만 exclusive.

### 4.2 TEB / TIB 접근

- `ThreadGetLocalBase(tid)`: 레지스트리 조회, miss 시 `NtQueryInformationThread(ThreadBasicInformation)` 으로 `TEB` 주소 얻기.
- `ThreadGetTeb(tebBase, &teb)`: `MemReadUnsafe` 로 TEB 구조체 전체 read.
- `ThreadGetLastErrorTEB(tid)`: `ThreadLocalBase + offsetof(TEB, LastErrorValue)` 에서 DWORD read — per-thread last error 추적.

TEB 읽기가 `MemReadUnsafe` 기반이므로 위 guard-page 완화 경로를 타지 않음 (TEB 는 항상 valid 가정).

### 4.3 Context 조작

x64dbg 는 `GetThreadContext`/`SetThreadContext` 를 직접 부르지 않고 TitanEngine macro 사용:

```cpp
duint rip = GetContextDataEx(hThread, UE_CIP);   // RIP on x64, EIP on x86
duint rsp = GetContextDataEx(hThread, UE_CSP);   // RSP or ESP
duint rflags = GetContextDataEx(hThread, UE_EFLAGS);
SetContextDataEx(hThread, UE_CIP, newRip);
```

`UE_CIP`/`UE_CSP` 매크로가 빌드 타겟에 따라 RIP/EIP, RSP/ESP 로 분기 — 아키텍처 독립 호출 가능. x87 / XMM / AVX 도 `UE_X87_R0` .. 로 래핑.

### 4.4 Suspend/Resume all

```cpp
int ThreadSuspendAll() {
    SHARED_ACQUIRE(LockThreads);
    int count = 0;
    for(auto& e : threadList)
        if(SuspendThread(e.second.Handle) != (DWORD)-1)
            count++;
    return count;
}
```

단순 range-for. 주의: Windows `SuspendThread` 는 카운터 기반이므로 중복 호출 시 카운터가 누적 → `ResumeAll` 이 대응 횟수 만큼 `ResumeThread` 필요.

---

## 5. Exception Dispatch

### 5.1 예외 코드 DB (3 병렬)

- `exceptiondb.txt` → `ExceptionNames: unordered_map<uint32, string>` (base-16 parsing)
- `ntstatus.txt` → `NtStatusNames` (base-16)
- `errorcodes.txt` → `ErrorNames` (base-10, Win32 `GetLastError`)

모두 공통 파서 `UniversalCodeInit(file, map, radix)` 가 로드. `ExceptionCodeToName(code)` 는 2-level lookup: `ExceptionNames` miss 시 `NtStatusNames` fallback → 의사 merge.

Hardcoded 상수 하나: `MS_VC_EXCEPTION = 0x406D1388` (SetThreadName).

### 5.2 `cbException` 핸들러

`DEBUG_EVENT` 루프가 `EXCEPTION_DEBUG_EVENT` 수신 시 호출:

```cpp
static void cbException(EXCEPTION_DEBUG_INFO* ExceptionData) {
    // 1. code + flags 추출
    //    ExceptionData->ExceptionRecord.ExceptionCode/ExceptionFlags
    // 2. first-chance vs second-chance 구분
    //    first-chance = ExceptionFlags & EXCEPTION_NONCONTINUABLE 없음
    // 3. exception filter lookup
    auto flt = dbggetexceptionfilter(code);
    //    filter = (break? log? ignore?) × (first_chance | second_chance)
    // 4. 특수 예외 intercept
    //    - MS_VC_EXCEPTION → ThreadName 설정 후 continue
    //    - EXCEPTION_BREAKPOINT (0x80000003) → BP 조회 / single-shot 판단
    //    - EXCEPTION_SINGLE_STEP (0x80000004) → HW BP or stepping
    //    - EXCEPTION_GUARD_PAGE → memory BP
    // 5. continueStatus 결정
    dbgsetcontinuestatus(filter.swallow
        ? DBG_EXCEPTION_HANDLED
        : DBG_EXCEPTION_NOT_HANDLED);
    // 6. filter.break == true 면 GUI 에 알림 후 DebugLoop wait
}
```

### 5.3 SEH / VEH / Vectored chain 과의 관계

x64dbg 자체는 **디버기의 SEH/VEH chain 을 구현하지 않고 관찰만 한다**. Windows debug port 가 예외를 받으면 다음 순서:

1. **first-chance** → 디버거 (x64dbg) 통지 → `DBG_EXCEPTION_NOT_HANDLED` 반환 시 OS 가 디버기 VEH 체인 → SEH 체인 → `UnhandledExceptionFilter` 경로 진행.
2. 디버기가 예외를 처리 못하면 → **second-chance** 로 다시 디버거에 통지 → 보통 break (치명적).

filter 설정 (`dbggetexceptionfilter`) 이 "first-chance break vs continue" 를 제어. UI 의 Exception View 가 이 테이블을 편집. x64dbg 는 VEH/SEH 체인 내용 자체를 dump 할 때 TEB + PE `.pdata` 읽기를 통해 표시하나, 이는 read-only.

### 5.4 BP 히트 판별

`EXCEPTION_BREAKPOINT` 의 경우 `ExceptionAddress` 로 `breakpoints` 맵 조회. BPNORMAL 히트면 `cbUserBreakpoint` → `BpCheckHit` → 조건 평가 → `oldbytes` 복원 + RIP 를 해당 주소로 되돌림 + single-step + 재삽입 (singleshoot 아닌 경우).

---

## 6. Stepping Engine

### 6.1 API 표면

`debugger.h` 의 공개 함수:

```cpp
void cbStep();                               // generic step 재진입
void cbRtrStep();                            // return-to (step-out)
void StepIntoWow64(TITANCBSTEP cb);          // x64 vs WoW64 분기
void StepOverWrapper(TITANCBSTEP cb);        // call 스킵
void StepIntoUser(...), StepIntoSystem(...);
void StepOverUser(...), StepOverSystem(...); // user/system code filter
void dbgsetsteprepeat(bool steppingIn, duint repeat);
bool dbgstepactive();
```

Trace 계열 (조건부 stepping, trace record 연동):

```cpp
void cbTraceIntoConditionalStep();
void cbTraceOverConditionalStep();
void cbTraceXConditionalStep(STEPFUNCTION, TITANCBSTEP cb);
void cbTraceIntoBeyondTraceRecordStep();
void cbTraceOverBeyondTraceRecordStep();
```

(Trace recording 자체는 Task #39 scope)

### 6.2 Step-Into (trap flag)

`StepIntoWow64(cb)` 는 TitanEngine `StepInto` 호출 → context 에 `EFLAGS.TF = 1` 설정 → `ContinueDebugEvent` → 다음 명령 실행 후 `EXCEPTION_SINGLE_STEP` → `cb = cbStep` 호출.

```cpp
void cbStep() {
    hActiveThread = ThreadGetHandle(GetDebugData()->dwThreadId);
    duint CIP = GetContextDataEx(hActiveThread, UE_CIP);
    if(bAbortStepping || !stepRepeat || !--stepRepeat) {
        // step 완료 → GUI pause
    } else {
        dbgtraceexecute(CIP);  // trace record
        (bRepeatIn ? StepIntoWow64 : StepOverWrapper)(cbStep);
    }
}
```

`stepRepeat` 카운터로 "N-step at once" 지원.

### 6.3 Step-Over (call frame 스킵)

`StepOverWrapper(cb)`:
1. 현재 CIP 의 명령 디스어셈블 → CALL opcode 인가?
2. CALL 아니면 `StepInto` 로 fallback.
3. CALL 이면 `CIP + instructionLength` 주소에 **singleshoot SW BP** 삽입 → `ContinueDebugEvent` with `DBG_CONTINUE` → CALL 실행 → return 시 BP 히트 → `cb` 호출.

즉 "step-over = call 다음 주소에 임시 BP". 재귀/long call 에 안전.

### 6.4 Step-Out (run-to-return)

```cpp
void cbRtrStep() {
    duint csp = GetContextDataEx(hActiveThread, UE_CSP);
    unsigned char b1, b2;
    MemRead(cip, &b1, 1);
    // RET 검출: 0xC3 (near ret), 0xC2 (ret imm16), 0xCA/0xCB (far ret)
    bool reachedReturn = (b1 == 0xC3 || b1 == 0xC2 /* 등 */)
                      && csp >= gRtrPreviousCSP;  // stack unwound
    if(reachedReturn || bAbortStepping)
        cbRtrFinalStep(true);
    else
        StepOverWrapper(cbRtrStep);  // 루프
}
```

**두 조건 AND**: (1) 현재 명령이 RET opcode, (2) CSP 가 시작 시점 이상으로 증가 (재귀 호출의 중간 RET 제외). `StepOverWrapper` 로 반복 — 즉 call 은 통째로 skip, 기타 명령은 1 step.

### 6.5 Run-to-Cursor

```cpp
static std::vector<std::pair<duint, duint>> RunToUserCodeBreakpoints;

void cbRunToUserCodeBreakpoint(const void* ExceptionAddress) {
    dbgClearRtuBreakpoints();  // 모든 임시 BP 제거
    // pause
}

static void dbgClearRtuBreakpoints() {
    for(auto& i : RunToUserCodeBreakpoints) {
        BREAKPOINT bp;
        if(!BpGet(i.first, BPMEMORY, nullptr, &bp))
            RemoveMemoryBPX(i.first, i.second);
    }
    RunToUserCodeBreakpoints.clear();
}
```

"Run to user code" 는 모든 non-system 모듈의 `.text` 섹션에 memory BP 를 깔고 첫 히트 후 즉시 제거. 일반 run-to-cursor 는 cursor 주소 1 개에 singleshoot SW BP.

### 6.6 StepIntoUser/System 분기

`StepIntoUser` 는 "system module (kernel32, ntdll 등) 진입 시 자동 step-out" 로직. `SymGetModuleInfo` 로 현재 CIP 의 모듈이 user 인지 system 인지 판별 후 system 이면 다시 step-out 체인 진입. UX 상 "system code 건너뛰기" 옵션.

---

## 7. AURA 관점 관찰

| 영역 | AURA 적용 가능성 | 근거 |
|------|-----------------|------|
| SW/HW BP 삽입 | **scope out** | AURA 는 프로세스를 실행하지 않음 |
| Memory page cache | **scope out** | 정적 파일은 mmap 으로 전체 접근 |
| Thread context | **scope out** | 스레드 개념 없음 |
| Exception dispatch runtime | **scope out** | 동적 이벤트 없음 |
| Stepping engine | **scope out** | 정적 분석 |

**AURA 와 유일한 간접 접점**: x64dbg 의 예외 코드 taxonomy (`exceptiondb.txt`, `MS_VC_EXCEPTION`) 는 **정적 관점에서도 유용**하다. AURA 의 `src/parser/eh_frame_parser.c` (DWARF CIE/FDE) + `src/parser/seh_parser.c` (PE `.pdata` + SCOPE_TABLE) + `src/decompiler/exception_flow.c` (E-2 HIR_COMMENT annotation) 가 bin 에서 exception handler 주소를 추출할 때, handler 본체의 `__CxxFrameHandler3` / `__GSHandlerCheck` / `__C_specific_handler` 같은 RVA 에서 x64dbg 스타일의 **handler-type label** 을 붙이면 HIR_COMMENT 품질이 향상될 수 있다. 이는 Task #33 의 PDB symbol server 경로 (msdl.microsoft.com) 로 이름을 얻은 후 → 본 문서의 exception taxonomy 와 매칭하는 **교차 가치**. **구조적 관찰일 뿐 이식 제안 아님** (E-2 의 cache 는 이미 완료, 추가 annotation 품질 개선은 별도 Task 필요 시 사용자 결정).

그 외 본 문서의 core engine 전체는 AURA scope 외. **런타임 엔진을 정적 분석기에 이식하는 것은 범위 혼돈을 초래**하므로 명시적으로 배제한다 (feedback_aura_option_scope_discipline 참조).

---

## 8. Cross-reference

- **#33 (x64dbg 교차 scope)**: Pattern scan (`patternfind`) / PDB symbol server / CLI dispatcher / ZydisTokenizer. 본 문서와 disjoint.
- **#36 (bridge)**: GUI ↔ DBG 통신. BP 상태 / thread context / memory map 을 GUI 에 pump 하는 파이프가 bridge 층. 본 문서가 정의한 데이터 생산자이고 #36 이 소비자.
- **#37 (GUI)**: Memory Map / Threads / Breakpoints / CPU / Stack 패널이 본 문서 subsystem 의 직접 view. Qt 표현층은 #37 에서.
- **#38 (plugin+scripting)**: Plugin SDK 가 `BpSetCallback`, `RegisterCallback(CB_CREATEPROCESS)`, `DbgEval` 등을 노출 — 본 문서 core 를 외부 재사용 가능하게 함. 본 문서가 internals, #38 이 external SDK surface.
- **#39 (symbol + trace)**: Trace record 가 `cbStep` 계열의 `dbgtraceexecute(CIP)` 호출에서 feed. Symbol engine 은 `ThreadGetStartAddress` / `MemFindBaseAddr` 를 통해 모듈 경계를 얻음. Trace 는 stepping 의 결과, symbol 은 memory map 의 결과.

---

## 9. 인용

GPL-3 소스 경로 (상용 상호운용 금지, 구조적 분석만):

- `src/dbg/breakpoint.h` — BP_TYPE, BREAKPOINT struct, API 선언
- `src/dbg/breakpoint.cpp` — BpNew / SW BP (int3 + SetBPX) / HW BP (TITANGETDRX) / Memory BP (SetMemoryBPXEx)
- `src/dbg/memory.h` — MemRead/Write/Protect/Update API
- `src/dbg/memory.cpp` — MemUpdateMap 3-phase (QueryMemPages + ProcessFileSections + ProcessSystemPages), IgnoreThisRead (QueryWorkingSetEx)
- `src/dbg/thread.h` / `thread.cpp` — THREADINFO, threadList map, ThreadGetTeb (NtQueryInformationThread)
- `src/dbg/exception.h` / `exception.cpp` — ExceptionCodeInit, UniversalCodeInit, 3 parallel DB
- `src/dbg/debugger.h` / `debugger.cpp` — cbException, cbStep, cbRtrStep, StepIntoWow64, StepOverWrapper, cbRunToUserCodeBreakpoint
- https://help.x64dbg.com/ — 공식 docs (exception view, BP types 설명)

AURA 내부 연관 파일 (관찰만, 수정 없음):
- `src/parser/eh_frame_parser.c` — DWARF CIE/FDE
- `src/parser/seh_parser.c` — PE `.pdata` + RUNTIME_FUNCTION + UNWIND_INFO + SCOPE_TABLE
- `src/decompiler/exception_flow.c` — E-2 HIR_COMMENT annotation consumer
- `src/symbolic/func_detect_ehframe.c` — 예외 정보 기반 함수 탐지
