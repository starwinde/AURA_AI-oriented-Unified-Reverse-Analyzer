# x64dbg Plugin SDK + Scripting 엔진 해체

> Session #9 (2026-04-21), Task #38. Team `v2-3-0-phase-2b`, research teammate.
> 대상: x64dbg (GPL-3, https://github.com/x64dbg/x64dbg @ `development` branch).
> Scope: `src/dbg/_plugins.h` + `_plugins.cpp` + `plugin_loader.*` + `simplescript.*` + `expressionparser.*` + `commands/cmd-*.cpp` + `variable.h`.
> Clean-room: GPL-3 소스 직접 재사용 금지. 설계 패턴/인터페이스만 참조.
> 중복 회피: Task #33 은 CLI dispatcher 개요 수준. 본 문서는 plugin + scripting 내부 전체.

---

## 1. Executive Summary

x64dbg 의 extensibility layer 는 **세 축**으로 구성된다:

1. **Plugin SDK** (`src/dbg/_plugins.h`, 378 LOC, SDK version `PLUG_SDKVERSION=1`)
   — Windows DLL ABI. 35 개 CBTYPE 이벤트, 6 개 callback 함수 포인터 typedef, `_plugin_*` export 40여 개. 플러그인이 debug event/command/menu/expression function 에 훅을 건다.
2. **Scripting 엔진** (`src/dbg/simplescript.cpp`, 953 LOC)
   — `.x64dbg.txt` 텍스트 파일. 어셈블리 mnemonic 모방 (`jmp`, `call`, `ret`, `jne`, `jae` …) 기반 label-jump 제어 흐름. 루프는 문법 구성 X → conditional jump 로 구현. `$_EZ_FLAG` / `$_BS_FLAG` 두 개 script flag 가 비교 결과 보관.
3. **ExpressionParser** (`src/dbg/expressionparser.cpp`, 1,182 LOC)
   — Shunting-yard 기반 14-레벨 C-style precedence. `[addr]` memory deref, `reg` 직접 읽기, `var` 자동 resolve, `func(args)` 플러그인 expression function 호출. 모든 CLI argument + 조건부 breakpoint + log 포맷 `{expr}` 에서 공용.

**핵심 관찰**:
- x64dbg 는 script 를 **"command 순서의 라인-맵"** 으로 취급한다 — AST/bytecode 가 아니다. 한 줄 = 한 command = 한 CLI dispatch. 플러그인이 등록한 command 도 스크립트 내부에서 그대로 호출 가능.
- Expression 은 **plugin extensible** 이다. `_plugin_registerexprfunction("my_func", argc, cb, userdata)` 로 DSL 에 함수 추가. ⇒ plugin 이 scripting 문법을 확장.
- Callback 메커니즘이 매우 평면적 (flat array `gPluginCallbackList[CB_LAST]`). 각 CBTYPE 당 여러 plugin 이 등록되면 **등록 순서대로** 직렬 호출 (`plugincbcall`).

**AURA 관점 결론**: 플러그인 MVP 유보 (PRD §4.1) 전제를 뒤집을 이유는 없다. 그러나 **ExpressionParser 구조**는 AURA CLI (`--decompile`/`--decompile-all`) 의 value-expression 확장 (예: `--filter "addr >= 0x1000 && size < 256"`) 에 장기 참조 가치가 있다. Bridge 모델 (#36) 과 함께 봐야 complete picture.

---

## 2. Plugin SDK

### 2.1 Plugin lifecycle + init/stop

x64dbg 는 런타임 시작 시 `plugins/` 디렉토리의 모든 `.dp32/.dp64` DLL 을 `pluginloadall()` 로 일괄 로딩한다. 단일 플러그인 로딩은 `pluginload(name)`.

**DLL loader 의무 export** (`plugin_loader.h`):
```c
typedef bool (*PLUGINIT)(PLUG_INITSTRUCT* initStruct);  // required
typedef bool (*PLUGSTOP)();                              // optional
typedef void (*PLUGSETUP)(PLUG_SETUPSTRUCT* setupStruct);// optional
```

`cleanupLoadingPlugin()` (plugin_loader.cpp) 의 resolve 순서:
1. `LoadLibraryW(plugpath)` — DLL 매핑.
2. `GetProcAddress(hPlugin, "pluginit")` — 없으면 로딩 실패 (FreeLibrary 후 반환).
3. `pluginit(&initStruct)` 호출. 플러그인은 initStruct 에 `pluginName`, `sdkVersion`, `pluginVersion` 쓴다.
4. SDK version 불일치 시 경고 + 로딩 중단.
5. `GetProcAddress(hPlugin, "plugstop")` / `plugsetup` — 존재하면 함수 포인터 저장.
6. `plugsetup(&setupStruct)` 호출 — GUI 창 핸들 (HWND) + 7 개 menu 핸들 전달.
7. PLUG_DATA 레코드를 전역 `pluginList` 에 추가.

**언로딩 순서** (`cleanupLoadingPlugin`):
1. `plugstop()` 호출 (있으면).
2. `plugincmdunregisterall(handle)` — command 해제.
3. `pluginexprfuncunregisterall` — expression function 해제.
4. `pluginformatfuncunregisterall` — format function 해제.
5. 모든 CBTYPE 의 등록된 callback 제거.
6. menu 엔트리 제거.
7. `FreeLibrary(hPlugin)`.

**버전 호환**:
- 유일한 gate 는 `PLUG_SDKVERSION` (현재 `1`). 증가 시 ABI 깨짐 전제.
- `pluginVersion` 은 플러그인 자체 버전으로 x64dbg 는 단순 기록만.
- 크로스 비트 불가: `.dp32` 는 x32dbg.exe 전용, `.dp64` 는 x64dbg.exe 전용 (Windows DLL 특성).

### 2.2 Callback / hook 등록

**플러그인 API export** (`_plugins.h`):
```c
void _plugin_registercallback(int pluginHandle, CBTYPE cbType, CBPLUGIN cbPlugin);
bool _plugin_unregistercallback(int pluginHandle, CBTYPE cbType);

typedef void (*CBPLUGIN)(CBTYPE cbType, void* callbackInfo);
```

**내부 storage** (`plugin_loader.h`):
```c
struct PLUG_CALLBACK {
    int pluginHandle;
    CBTYPE cbType;
    CBPLUGIN cbPlugin;
};
// gPluginCallbackList[CB_LAST] = std::vector<PLUG_CALLBACK>  (per-type bucket)
```

플러그인 1 개가 CBTYPE 당 **1 개 callback** 만 등록 가능 (동일 handle+type 재등록 시 덮어쓰기). 서로 다른 플러그인은 같은 CBTYPE 에 독립적으로 등록 가능 — `plugincbcall()` 이 벡터 순회로 전부 호출.

**CBTYPE 35 개** (`_plugins.h:274-311`) — 대분류:

| 분류 | CBTYPE | 전달 구조체 |
|------|--------|-------------|
| 세션 | `CB_INITDEBUG`, `CB_STOPDEBUG`, `CB_STOPPINGDEBUG`, `CB_PAUSEDEBUG`, `CB_RESUMEDEBUG`, `CB_STEPPED` | PLUG_CB_* (대부분 reserved) |
| 프로세스/쓰레드 | `CB_CREATEPROCESS`, `CB_EXITPROCESS`, `CB_CREATETHREAD`, `CB_EXITTHREAD`, `CB_ATTACH`, `CB_DETACH` | Win32 DEBUG_INFO 구조체 포인터 |
| 모듈 | `CB_LOADDLL`, `CB_UNLOADDLL`, `CB_SYSTEMBREAKPOINT` | LOAD_DLL_DEBUG_INFO + modInfo |
| Exception/BP | `CB_EXCEPTION`, `CB_BREAKPOINT`, `CB_OUTPUTDEBUGSTRING`, `CB_DEBUGEVENT` | EXCEPTION_DEBUG_INFO, BRIDGEBP, DEBUG_EVENT |
| GUI | `CB_MENUENTRY`, `CB_MENUPREPARE`, `CB_WINEVENT`, `CB_WINEVENTGLOBAL`, `CB_SELCHANGED` | hEntry, MSG*, duint VA |
| DB | `CB_LOADDB`, `CB_SAVEDB` | json_t* root + loadSaveType |
| 분석 | `CB_ANALYZE`, `CB_ADDRINFO`, `CB_FILTERSYMBOL` | BridgeCFGraphList, BRIDGE_ADDRINFO, 심볼명 |
| 값 변환 | `CB_VALFROMSTRING`, `CB_VALTOSTRING` | plugin 이 커스텀 값 파싱/렌더 추가 |
| Trace | `CB_TRACEEXECUTE`, `CB_STARTTRACE`, `CB_STOPTRACE` | cip+stop bool, traceFilePath |

`retval` 필드가 있는 CBTYPE (예: `PLUG_CB_FILTERSYMBOL`, `PLUG_CB_ADDRINFO`, `PLUG_CB_VALFROMSTRING`) 은 플러그인이 `true` 로 설정하면 **엔진의 default 처리를 가로챈다** — Ghidra analyzer priority 개념의 단순화 버전.

### 2.3 Command / Expression / Format 함수 등록

**Command 등록** — CLI 에서 사용자가 타이핑할 수 있는 단어 추가:
```c
typedef bool (*CBPLUGINCOMMAND)(int argc, char** argv);
bool _plugin_registercommand(int pluginHandle, const char* command,
                             CBPLUGINCOMMAND cbCommand, bool debugonly);
```

`debugonly=true` 면 세션이 attached 상태가 아닐 때 호출 거부. 내부 storage `gPluginCommandList` 는 `{handle, command-name}` 페어 벡터. 실제 디스패치는 `command.cpp::cbCommand()` 가 `cmdget()` 으로 core + plugin command 를 통합 lookup (core command 와 이름 충돌 시 core 우선).

**Expression function 등록** — ExpressionParser DSL 에 함수 주입:
```c
typedef duint (*CBPLUGINEXPRFUNCTION)(int argc, const duint* argv, void* userdata);
typedef bool (*CBPLUGINEXPRFUNCTIONEX)(ExpressionValue* result,
                                        int argc, const ExpressionValue* argv,
                                        void* userdata);

bool _plugin_registerexprfunction(int, const char*, int argc, CBPLUGINEXPRFUNCTION, void*);
bool _plugin_registerexprfunctionex(int, const char*, ValueType returnType,
                                     const ValueType* argTypes, size_t argCount,
                                     CBPLUGINEXPRFUNCTIONEX, void*);
```

`ValueType` enum: `ValueTypeNumber`, `ValueTypeString`, plus "optional" variants (Ex variant 만). "Ex" 는 타입-체크된 argument validation + string return 지원. 일반 버전은 `duint` 스칼라만.

**Format function 등록** — log 포맷 `{type:arg}` 에 커스텀 타입 추가:
```c
typedef FORMATRESULT (*CBPLUGINFORMATFUNCTION)(char* dest, size_t destCount,
                                                int argc, char* argv[],
                                                duint value, void* userdata);
bool _plugin_registerformatfunction(int, const char* type,
                                     CBPLUGINFORMATFUNCTION, void*);
```

`FORMATRESULT`: `FORMAT_ERROR`, `FORMAT_SUCCESS`, `FORMAT_ERROR_MESSAGE`, `FORMAT_BUFFER_TOO_SMALL`. 버퍼 부족 시 엔진이 더 큰 버퍼로 재시도. → **플러그인이 CLI 로그 출력 포맷을 확장**한다는 점이 AURA `--decompile-all --json` (Task #25) 의 pluggable renderer 설계 단서가 될 수 있음.

### 2.4 Event 처리 (bp / exc / module / thread)

**트리거 경로**:
1. Windows debug loop (`debugloop.cpp`) 가 `WaitForDebugEvent` 로 DEBUG_EVENT 수신.
2. Core 가 내부 핸들링 후 `plugincbcall(CB_EXCEPTION, &info)` 호출.
3. `plugincbcall` 이 해당 CBTYPE 의 콜백 벡터 순회, 각 CBPLUGIN 을 **동기 호출** (worker thread 없음 — 플러그인이 블록하면 디버거 전체 블록).
4. `CB_BREAKPOINT` 는 사용자 breakpoint hit 시 `BRIDGEBP*` 전달 (type/active/singleshoot/file 정보 포함).

**특기사항**:
- `PLUG_CB_DEBUGEVENT` 는 모든 debug event 마다 발생 — filtering 은 플러그인 책임.
- Breakpoint hit 시 순서: `CB_DEBUGEVENT` → `CB_BREAKPOINT` → `CB_PAUSEDEBUG` (pause 로 전환된 경우). 이 순서는 AURA 가 event pipeline 을 만든다면 벤치마크.

### 2.5 Plugin → GUI (Bridge 경유)

플러그인은 GUI 스레드에 직접 접근하지 않고 **Bridge API** 로 proxy 호출한다. `_plugin_logprintf`, `_plugin_logputs`, `GuiReference*` 등이 모두 Bridge 호출로 GUI 에 마샬링. 본 문서는 Task #36 scope 라 상세 skip — 참조만.

**Plugin 이 직접 받는 GUI 핸들**:
- `PLUG_SETUPSTRUCT::hwndDlg` — 메인 윈도우 HWND (대화상자 parent 로 사용).
- `hMenu`/`hMenuDisasm`/`hMenuDump`/`hMenuStack`/`hMenuGraph`/`hMenuMemmap`/`hMenuSymmod` — 7 개 pluggable menu point.

**Menu 추가**:
```c
int _plugin_menuadd(int hMenu, const char* title);                 // submenu 생성
bool _plugin_menuaddentry(int hMenu, int hEntry, const char* title); // clickable
```

클릭 시 `CB_MENUENTRY{hEntry}` 콜백 발사 → 플러그인이 `hEntry` 로 어떤 액션인지 분기. 이는 Qt signal/slot 의 C ABI 우회 — AURA 가 C core + Qt GUI 분리 원칙이 동일하므로 (PRD §5), 참조 가치 있음.

### 2.6 Plugin lifecycle 요약 다이어그램

```
LoadLibraryW
   │
   ├─ GetProcAddress("pluginit")  ← required
   │  pluginit(&initStruct)       ← plugin 이 이름/버전 작성
   │
   ├─ GetProcAddress("plugsetup") ← optional
   │  plugsetup(&setupStruct)     ← GUI HWND + menu 핸들 전달
   │
   │  === plugin alive ===
   │  _plugin_registercommand / _plugin_registercallback / _plugin_menuadd / ...
   │  runtime: CBTYPE events, command invocations, menu clicks
   │
   ├─ GetProcAddress("plugstop")  ← optional
   │  plugstop()                  ← plugin 정리
   │
   └─ cleanupLoadingPlugin:
       plugincmdunregisterall → pluginexprfuncunregisterall →
       pluginformatfuncunregisterall → menu 제거 → FreeLibrary
```

---

## 3. Scripting 엔진

### 3.1 Command dispatcher 카테고리 (`src/dbg/commands/`)

`cmd-all.h` 는 19 개 cmd-*.cpp 파일의 entry point 를 한 헤더로 묶어 `main.cpp` 에서 `cmdnew()` 일괄 등록한다. 카테고리:

| 파일 | 대표 명령 | LOC |
|------|----------|-----|
| `cmd-general-purpose.cpp` | `cmd`, `ret`, `log`, `loghtml`, `msg`, `msgyn`, `printstack`, `chd` | ~33 KB |
| `cmd-debug-control.cpp` | `init/stop/run/pause/StepIn/StepOver`, `attach`, `detach`, `erun`, `tocnd` | ~20 KB |
| `cmd-breakpoint-control.cpp` | `bp`, `bph`, `bpd/bpe`, `bpl`, `bpc`, `bpmc`, `bpgoto` | ~51 KB |
| `cmd-conditional-breakpoint-control.cpp` | `bpcond`, `bplog`, `bplogcond`, `bpname`, `bpfastresume` | ~14 KB |
| `cmd-tracing.cpp` | `TraceIntoConditional/Over`, `TraceSet*`, `starttrace`, `stoptrace` | ~7 KB |
| `cmd-thread-control.cpp` | `createthread`, `suspendthread`, `resumethread`, `killthread`, `setthreadname` | ~8 KB |
| `cmd-memory-operations.cpp` | `alloc`, `free`, `memset`, `memcopy`, `memread`, `memwrite` | ~10 KB |
| `cmd-operating-system-control.cpp` | `setpriv`, `getpriv`, `gethpid`, `gethtid` | ~4 KB |
| `cmd-watch-control.cpp` | `wa`, `wd`, `we`, `wc` | ~6 KB |
| `cmd-variables.cpp` | `var`, `vardel`, `varlist` | ~4 KB |
| `cmd-searching.cpp` | `findref`, `find`, `findall`, `findguid`, `findasm`, `modcallfind` | ~41 KB |
| `cmd-user-database.cpp` | `dbsave/dbload`, `cmt/argset/lblset`, `commentlist`, `bookmarklist` | ~20 KB |
| `cmd-analysis.cpp` | `analyze`, `anal`, `analxrefs`, `analadv`, `cfanalyze`, `exanal` | ~19 KB |
| `cmd-types.cpp` | `typeadd`, `typeclear`, `datatype`, `sizeof` | ~12 KB |
| `cmd-plugins.cpp` | `plugload`, `plugunload`, `pluglist` | ~2 KB |
| `cmd-script.cpp` | `scriptload`, `scriptrun`, `scriptcmd`, `scriptexec`, `msg`, `msgyn`, `log`, `logredirect` | ~3 KB |
| `cmd-gui.cpp` | `disasm`, `dump`, `sdump`, `tracelogshow`, `graph`, `refinit`, `refadd` | ~10 KB |
| `cmd-misc.cpp` | `cmp`, `test`, `mov`, `modsymname`, `getmodinfo` | ~33 KB |
| `cmd-undocumented.cpp` | internal testing | ~20 KB |

**Core dispatcher** (`command.h`):
```c
struct COMMAND {
    std::vector<String>* names;   // alias 지원
    CBCOMMAND cbCommand;
    bool debugonly;
    COMMAND* next;                 // 링크드 리스트 — 등록 순 유지
};

COMMAND* cmdfind(const char* name, COMMAND** link);
bool cmdnew(const char* name, CBCOMMAND cbCommand, bool debugonly);
bool cmddirectexec(const char* cmd);
void cmdsplit(const char* cmd, StringList & commands);
```

`cmdsplit` 은 `;` (세미콜론) 으로 여러 명령 한 줄 실행 지원. `cmddirectexec` 는 `cmd.cpp::cbCommand(argc,argv)` 로 argument tokenize 후 dispatch.

**Plugin command vs core command**:
- Core: `cmdnew` 로 등록, `COMMAND` 링크드 리스트에.
- Plugin: `_plugin_registercommand` → `plugincmdregister` → 궁극적으로 `cmdnew` 경유 → **동일 리스트에 합쳐짐**. 충돌 체크는 `cmdfind` 가 선-존재 확인 후 거부.

### 3.2 ExpressionParser DSL

**전체 파이프라인**:
1. `ExpressionParser(str)` 생성자가 `tokenize()` + `shuntingYard()` 호출.
2. `Calculate(result, signedcalc, allowassign, ...)` 가 RPN 리스트를 stack 평가.
3. Data token 은 `valfromstring()` 로 register / variable / module.func / symbol 해결.

**Token types** (`expressionparser.h:58-112`) — 40+ 개. 주요 그룹:
- Data / QuotedData / NumericLiteral / Function / Comma / OpenParen / CloseParen
- Unary: `-x`, `+x`, `~x` (bitwise NOT), `!x` (logical NOT), `++x`, `--x`
- Arithmetic: `*`, ` ` ` (HiMul), `/`, `%`, `+`, `-`
- Shift/rotate: `<<`, `>>`, `<<<` (rol), `>>>` (ror)
- Comparison: `<`, `<=`, `>`, `>=`, `==`, `!=`
- Bitwise: `&`, `^`, `|`
- Logical: `&&`, `||`, `->` (logical implication)
- Assignment: `=`, `*=`, `` `= ``, `/=`, `%=`, `+=`, `-=`, `<<=`, `>>=`, `<<<=`, `>>>=`, `&=`, `^=`, `|=`
- Suffix/prefix inc/dec

**Precedence** (C-style, `expressionparser.cpp:65-129`):
| Lvl | Operator |
|-----|----------|
| 1 | `x++`, `x--` (suffix) |
| 2 | unary `-`, `+`, `~`, `!`, `++x`, `--x` |
| 3 | `*`, `` ` ``, `/`, `%` |
| 4 | `+`, `-` |
| 5 | `<<`, `>>`, `<<<`, `>>>` |
| 6 | `<`, `<=`, `>`, `>=` |
| 7 | `==`, `!=` |
| 8 | `&` |
| 9 | `^` |
| 10 | `|` |
| 11 | `&&` |
| 12 | `||`, `->` |
| 14 | 모든 assignment |

**Memory deref**: `[addr]` — tokenizer 가 bracket depth 추적 (`stateMemory`). 괄호 안은 operator 재귀 파싱하지 않고 **데이터 token** 으로 전체 보존 → `valfromstring()` 이 `[addr]` 문자열 통째로 받아 memory read 수행.

**Register resolution**: `valfromstring()` 이 먼저 register 이름 비교 (eax, rax, rip, zmm0 …) — 데이터 token 중 하나로 처리. 본 파일만 봐서는 구현 노출 안 되지만 `value.cpp` 에 있음 (Task #35 scope).

**Variable resolution**: Data token 중 `$` prefix 또는 이전 `var` 로 생성된 이름이 `varget(name, &value, NULL, NULL)` 로 해결. Builtin 변수는 `$_EZ_FLAG`, `$_BS_FLAG`, `$RESULT` 등.

**Function call**: Data token 뒤에 `(` 가 오면 `Function` token 으로 분류. `_plugin_registerexprfunction` 으로 등록된 모든 이름이 candidates. 인자는 comma 로 분리, 재귀 파싱.

### 3.3 Variables (user + builtin)

**Storage model** (`variable.h`):
```c
enum VAR_TYPE    { VAR_SYSTEM=1, VAR_USER=2, VAR_READONLY=3, VAR_HIDDEN=4 };
enum VAR_VALUE_TYPE { VAR_UINT, VAR_STRING };

struct VAR {
    String name;
    String alias;
    VAR_TYPE type;
    VAR_VALUE value;  // union { duint; vector<byte>*; } + size
};
```

`varnew`, `varset`, `varget`, `vardel`, `varenum` 로 관리.

**User-defined** (`cmd-variables.cpp`):
- `var NAME [VALUE]` — 생성. `VALUE` 는 ExpressionParser 로 평가. 이미 존재하는 값이면 에러 ("Invalid variable name" — 재사용 방지).
- `vardel NAME` — 삭제 (non-system 만).
- `varlist [USER|READONLY|SYSTEM]` — GUI reference view 로 출력.

**Builtin (system) 변수**: 디버거가 `varnew(..., VAR_SYSTEM)` 로 사전 등록.
- `$_EZ_FLAG` — equal/zero flag (비교 결과 같음 / cmp 결과 0).
- `$_BS_FLAG` — bigger/signed flag (a > b).
- `$RESULT` — 마지막 명령의 결과 (e.g., `msgyn` 대화상자 답).
- `$_PID`, `$_TID`, `$hp` (heap peb), `$_BRK`, `$_EIP`/`$_RIP` 등 runtime state mirror.
- Alias 메커니즘으로 동일 값 다른 이름 가능 (`VAR::alias` 필드).

### 3.4 Conditional / Loop

**Loop 은 1 차 문법이 아니다** — x64dbg 스크립트는 label + conditional jump 로만 반복 구성. 이는 x86 어셈블리 mental model 을 빌려온 의도적 결정.

**Branch instructions** (`simplescript.cpp:138-160`, `scriptGetBranchType`):
```
jmp, goto                 → scriptjmp                (unconditional)
call                       → scriptcall               (stack push)
ret                        → (internal) stack pop
je, ife, ifeq, jz, ifz     → scriptjejz               ($_EZ_FLAG=1)
jne, ifne, ifneq, jnz, ifnz → scriptjnejnz            ($_EZ_FLAG=0)
jb, ifb, jl, ifl           → scriptjbjl               ($_BS_FLAG=0 && $_EZ_FLAG=0)
ja, ifa, jg, ifg           → scriptjajg               ($_BS_FLAG=1 && $_EZ_FLAG=0)
jbe, ifbe, ifbeq, jle, ifle, ifleq → scriptjbejle    ($_BS_FLAG=0 || $_EZ_FLAG=1)
jae, ifae, ifaeq, jge, ifge, ifgeq → scriptjaejge    ($_BS_FLAG=1 || $_EZ_FLAG=1)
```

**Label 문법**: 라인 끝에 `:` — `cur.type = linelabel`. 라벨 중복 정의 시 로드 단계에서 에러.

**분기 평가 절차** (`scriptBranchTaken`):
1. 이전 command (대개 `cmp A,B` 또는 `test`) 가 `$_EZ_FLAG` / `$_BS_FLAG` 를 설정.
2. branch instruction 이 plain string match (정규식 X, startswith 만) 로 SCRIPTBRANCHTYPE 결정.
3. Flag 읽어 분기 결정. `call` 은 stack push, `ret` 은 pop.
4. 라벨 주소 resolve 는 로드 단계 `scriptCreateLineMap` 에서 이미 `cur.branch.dest` 에 pre-compute.

**Call stack**: `std::vector<SCRIPTFRAME>` — 재귀 지원. 각 frame 에 `ip` + SCRIPTSTATE(stepping/running). `ret` 실행 시 pop.

**Loop 작성 예**:
```
// "5 회 반복" 카운터 루프
var i 0
loop_start:
    // body: print i
    log "i = {$RESULT}"
    inc i
    cmp i, 5
    jne loop_start
```

### 3.5 Script file format + 실행 모델

**File naming**: `.x64dbg.txt` (확장자 규약, hard requirement 아님 — `scriptload` 는 임의 path).

**Line types** (`simplescript.cpp:33-42`, `LINEMAPENTRY`):
- `lineempty` — 빈 줄.
- `linecomment` — `//` 또는 `;` 시작. (C++ 스타일 + 어셈블리 스타일 양쪽 허용).
- `linelabel` — `name:` 형식.
- `linebranch` — branch mnemonic (표 §3.4).
- `linecommand` — 기타 모든 것. core command + plugin command 모두 직접 호출.

**Trailing comment 제거**: 파서가 inline `"..."` 안의 `//` 는 무시 (간단 state machine — `inquote`/`inescape`). 문자열 바깥의 `//` 이후는 `line_comment` 로 분리 보관 (execution 시 주석 제거).

**Script 로드 단계** (`scriptCreateLineMap`):
1. `FileHelper::ReadAllText` 로 전체 읽기.
2. CRLF / LF 모두 지원.
3. 각 줄의 type 분류 (위).
4. 모든 라벨 수집, 중복 체크.
5. 모든 branch 의 target label 이 존재하는지 검증 → `branch.dest` 에 목표 IP 저장.
6. 마지막 줄이 `ret`/`error`/`invalid`/unconditional `jmp` 가 아니면 `ret` 자동 추가.

**실행 모델** (`scriptInternalCmd` + `scriptInternalCmdExec`):
- **AST 없음** — 각 줄이 CLI string 그대로 `cmddirectexec(cmd)` 호출.
- SCRIPTSTATE: `SCRIPT_PAUSED` / `SCRIPT_STEPPING` / `SCRIPT_RUNNING` — atomic.
- 실행 중 `dbgisrunning()` 이 true 이면 sleep 1ms 폴링 (debugger 가 일시중지 대기).
- Script 전용 internal commands (외부 플러그인이 override 불가):
  - `ret` — 스택 pop 또는 스크립트 종료.
  - `pause` — 스크립트 suspend.
  - `nop` — no-op (stepping 시 break 지점).
  - `error "msg"` — 에러 표시 후 종료.
  - `invalid` — 의도적 실패 (테스트용).
  - `log` — 로깅 활성화 flag.
- `scriptrun` / `scriptexec` 는 실행 중 재귀 호출 금지 (deadlock 방지).

**Thread model**:
- Script 는 **디버거 thread 와 별도 worker thread** 에서 실행 (`JobQueue scriptQueue`).
- `CB_BREAKPOINT` 등 debug event 는 worker thread 가 기다리다가 script 가 관찰.
- `_plugin_startscript(cbScript)` 로 플러그인이 C 함수를 script thread 에서 실행 가능 — 동기화 지점.

### 3.6 Debug event 기반 스크립트 (conditional BP → script)

x64dbg 의 **조건부 breakpoint + 스크립트 실행** 고유 기능 (`cmd-conditional-breakpoint-control.cpp` + core breakpoint manager):
- `bpcond ADDR "expression"` — BP hit 시 expression 평가, 0 이면 재개 (break 안 함).
- `bplog ADDR "format {rax}"` — hit 시 포맷 문자열 로깅.
- `bplogcond ADDR "expr"` — 로깅 조건.
- `bpcommand ADDR "cmd"` — hit 시 CLI command 실행 (스크립트 호출 가능).
- `bpcommandcond ADDR "expr"` — command 실행 조건.
- `bpfastresume ADDR [0|1]` — BP hit 시 커스텀 처리 후 자동 재개.

→ **Plugin 이 `CB_BREAKPOINT` 로 훅 하지 않고도, 사용자가 CLI 만으로 "BP → 조건 → 스크립트 실행" 자동화 가능**. 이는 plugin extensibility 의 심각한 경쟁자이며 많은 plugin 용도 (단순 trace/log) 를 대체.

---

## 4. AURA 관점

### 4.1 PRD §4.1 plugin 유보 전제 확인

AURA PRD 는 plugin 시스템을 **MVP 이후** (v3.0.0 후 재검토) 로 명시적 연기. 본 문서는 그 결정을 **뒤집지 않는다**. 오히려 x64dbg 사례가 다음 2가지 이유로 plugin 연기 정당성 강화:

1. **Plugin SDK 복잡도 ≫ MVP 가치**: 35 CBTYPE + 40 export + SDK version gate + menu/Bridge API + expression function extension. x64dbg 는 Windows 디버거 10+ 년 축적된 layer. AURA MVP (정적 RE) 는 user-extensible surface 가 훨씬 좁다.
2. **PRD §5 "커스텀 구현 우선" 과 긴장**: Plugin 허용 ⇒ 외부 플러그인이 AURA 내부에 의존 ⇒ ABI 안정성 보장 필요 ⇒ "외부 라이브러리 대신 직접 구현" 원칙이 내부 API 설계 자유도를 제약받음.

### 4.2 단기 참조 가치 (v2.3.x / Phase 2-C~E 범위 내)

- **N/A** — 본 task 의 모든 관찰은 장기 reference.

### 4.3 중기 참조 가치 (v3.0.0 CLI 확장 시)

- **ExpressionParser 설계 구조** (shunting-yard, 14-level C precedence, `[addr]` 전용 bracket depth 추적, data token fallback 으로 variable/register 해결) 가 AURA CLI filter 확장에 단서:
  - `aura --decompile-all --filter "func.size > 256 && func.addr >= 0x1000"` 류 predicate.
  - `aura --list-functions --sort "size desc"` 류 정렬 키.
  - 구현 시 **내장만** (plugin extension 불필요), ~500-800 LOC C 포팅 + unit test 로 수용 가능.
- **`[expression]` bracket pattern**: AURA HIR / 디컴파일 출력에 memory deref 표현 필요 시 x64dbg 의 간단한 bracket-depth 토큰화가 참조 가치. Ghidra 는 훨씬 복잡한 AST 사용.

### 4.4 장기 참조 가치 (v3.0.0+ plugin MVP 재검토 시)

Plugin MVP 가 재검토되는 시점에서 **반드시** 참조:

- **Flat CBTYPE enum + 콜백 벡터 per type**: 단순성 압도적. Ghidra Analyzer priority system 보다 훨씬 가벼움. 그러나 CBTYPE 확장 시 ABI 깨짐.
- **`PLUG_SDKVERSION` gate**: 단일 정수로 SDK 호환 검증. version skew 시 fail-fast.
- **Plugin command 등록 = core command 와 동일 테이블**: 충돌 체크만 있으면 통합. AURA 가 CLI 를 subcommand 기반으로 재구성 시 pattern 참조.
- **Bridge 간접 호출로 GUI/core 분리**: AURA Qt6 GUI (Phase 5.x) 와 core C 분리 원칙과 완전 일치. 구체 ABI 는 Task #36 에서 별도 분석.
- **Expression function 등록 = DSL 확장**: 만약 AURA 가 script 기능을 허용한다면, expression evaluator 확장 포인트가 가장 ROI 높은 hook.

### 4.5 명시적 반례 (AURA 가 피해야 할 x64dbg 패턴)

- **Label + conditional jump 스크립트 문법**: x86 mental model 의존. C/C++ 친화 AURA 사용자에게 역직관적. AURA 가 script 를 도입하려면 Python 호환 문법 또는 Lua 류 구조적 제어흐름 선호.
- **Plugin callback 동기 블로킹**: 플러그인 버그가 디버거 전체 hang. AURA 는 timeout + worker thread 분리 필수.
- **SDK version 단일 정수**: 세분 호환 불가. AURA 가 plugin 도입 시 semantic version + feature flag bitset 권장.

---

## 5. Cross-reference (#33/#36/#37)

| Task | 주제 | 본 문서와의 관계 |
|------|------|----------------|
| #33 (완료) | x64dbg pattern / PDB / CLI / Disasm UX | CLI dispatcher **개요** — 본 문서 §3.1 이 전체 카테고리 해체로 확장. #33 과 중복 없음 (#33 은 4 cross-cutting 영역만). |
| #36 (진행중) | Bridge API (GUI↔DBG) | 본 문서 §2.5 는 Plugin→GUI 경로만 요약. Bridge ABI 전체 구조 + BridgeList/BridgeCFGraphList 상세는 #36 산출물. |
| #37 (진행중) | Qt GUI 패널 전체 | 본 문서 §2.5 의 HWND + 7 menu handle 은 GUI 진입점. GUI 내부 MDI/dock/panel 은 #37. |
| #35 (pending) | 디버거 코어 (src/dbg/) | 본 문서는 command/script/expression layer 까지. debug loop / memory / symbol / analysis core 는 #35. |
| #39 (pending) | Symbol engine + Trace recording | `CB_STARTTRACE` / `CB_STOPTRACE` / `CB_TRACEEXECUTE` 콜백 (§2.2) 은 #39 가 심화. |

**Triangulation 가치**: Ghidra (Java plugin, OSGi-like) vs Rizin (RzCore plugin, C struct table) vs x64dbg (Win32 DLL export) 3 독립 구현 비교 → AURA 가 향후 plugin 을 도입 시 "어느 것도 완벽하지 않음" + "최소한 SDK version gate + flat callback 은 공통" 결론 가능.

---

## 6. 인용

- Repository: https://github.com/x64dbg/x64dbg (branch `development`, pushed 2026-04-20).
- License: GPL-3.0 — **clean-room 재작성**만 허용. 본 문서는 인터페이스 signature + 동작 설명만 수록, 소스 스니펫은 API surface (struct/enum/export) 에 한정.
- `src/dbg/_plugins.h` (378 LOC) — public SDK header.
- `src/dbg/_plugins.cpp` (212 LOC) — export wrapper impl.
- `src/dbg/_plugin_types.h` (36 LOC) — shared type aliases.
- `src/dbg/plugin_loader.h` / `plugin_loader.cpp` (104 + ~1,300 LOC) — DLL lifecycle.
- `src/dbg/simplescript.h` / `simplescript.cpp` (48 + 953 LOC) — scripting engine.
- `src/dbg/expressionparser.h` / `expressionparser.cpp` (199 + 1,182 LOC) — DSL 파서.
- `src/dbg/command.h` (37 LOC) + `commandparser.h` (31 LOC) — core command dispatch.
- `src/dbg/variable.h` (56 LOC) — variable storage model.
- `src/dbg/commands/cmd-*.cpp` (19 파일, 총 ~270 KB) — command implementations.
- 공식 문서: https://help.x64dbg.com/en/latest/introduction/scripting.html (403 — Cloudflare gate, 본 분석은 소스 우선).
- 공식 문서: https://help.x64dbg.com/en/latest/developers/plugins/index.html (403 — 동일).

> 공식 docs 접근 실패 (WebFetch 403) → 본 분석은 전적으로 소스 코드 읽기 기반. AURA PRD §4.1 plugin 유보 결정을 재검토할 이유가 현 시점 **없음**.
