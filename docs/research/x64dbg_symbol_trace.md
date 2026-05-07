# x64dbg Symbol Engine 확장 + Trace Recording 해체

> Task #39 (Team v2-3-0-phase-2b). x64dbg (GPL-3, https://github.com/x64dbg/x64dbg) 의 **symbol engine 전체** + **trace recording** 심층. Task #33 의 symbol 표면(symbol server 4-tier) 를 더 깊이 파고, 이번에는 `SymbolSourceBase` 추상화, DIA 통합, export/import/forwarder, stack unwinding, trace 바이너리 포맷, block hit counter 까지 내려간다.
>
> **Clean-room**: 모든 내용은 공개 소스와 공식 문서에서만 도출. GPL-3 코드는 본 문서에 복제하지 않으며, 인터페이스/포맷/알고리즘의 **기능적 기술** 에 한정.

---

## 1. Executive Summary

x64dbg 의 symbol 스택은 다음 4 layer 구조로 정리된다: (i) `SymbolSourceBase` abstract interface (recall/load 상태 분리), (ii) `SymbolSourceDIA` 가 `PDBDiaFile` 를 통해 msdia140 COM 을 래핑, (iii) `module.cpp` 의 EAT/IAT/forwarder 파서가 PDB 와 독립된 2차 소스, (iv) `symbolinfo.cpp` 의 merge/fallback 로직 (`debug → export → entry → import`). Stack unwinding 은 `stackinfo.cpp` 에서 3 단계 (x64 `.pdata/.xdata` RUNTIME_FUNCTION → x86 frame-pointer → heuristic "suspected" 스캔) 로 분리.

Trace recording 은 두 서브시스템으로 나뉜다: (a) per-instruction **trace log** — magic `TRAC` + JSON metadata + SoA delta-encoded 명령당 엔트리 (3072B buffer, 매 512 instr. 전체 register snapshot), (b) per-address **hit counter** — 3 storage mode (bit/byte/word) 로 기본 블록 커버리지 측정. 후자가 AURA 정적 coverage metric (gap_analyzer.sh) 과 교차한다.

**AURA 관점 총평**:
- **High (Phase 3.12 PDB 강화)**: `SymbolSourceBase` 의 lazy-load 플래그 (`isOpen`/`isLoading`/`cancelLoading`/`waitUntilLoaded`) 와 dual-name 필드 (`decoratedName`/`undecoratedName`) 는 AURA PDB 로더에 즉시 이식 가치.
- **High (Phase 3.14 EH frame)**: `.pdata/.xdata` RUNTIME_FUNCTION 접근 패턴은 ELF `.eh_frame` DWARF CIE/FDE 파싱의 Windows 쌍방향 reference. "Heuristic suspected call stack" 은 AURA 가 unwind info 없는 stripped 바이너리에서 참조 가능.
- **Med (Phase 2-F v1.2 Windows)**: DIA SDK 직접 사용은 Windows-only 으로, AURA v1.2 Windows release 에서만 고려. Cross-platform 필요 시 llvm-pdb 대체.
- **Low (out of scope)**: Trace log 자체는 동적 실행 산물 — AURA scope 외. 단 block hit counter 자료 구조 (bit/byte/word 3-tier) 는 AURA `coverage_map_t` 가 있다면 설계 참조.

---

## 2. Symbol engine 확장

### 2.1 DIA SDK 사용 (vs DbgHelp)

**파일**: `src/dbg/symbolsourcedia.cpp` + (추정) `src/dbg/PDBDiaFile.cpp` wrapper.

x64dbg 는 `DbgHelp.dll` 의 `Sym*` API 대신 **`msdia140.dll` 을 직접 `CoCreateInstance(CLSID_DiaSource, …, IID_IDiaDataSource)`** 로 로드한다 (소스 코드는 `PDBDiaFile` 내부이며 `symbolsourcedia.cpp` 는 상위 wrapper 만 노출). 공식 DIA SDK 문서 (https://docs.microsoft.com/en-us/visualstudio/debugger/debug-interface-access/) 와 일치.

`symbolsourcedia.cpp` 에서 확인된 호출 패턴:
- `pdb.enumerateLexicalHierarchy(query)` — `IDiaSession::findChildren(SymTagFunction / SymTagPublicSymbol / SymTagData / SymTagLabel)` 을 내부에서 래핑. 콜백에 `DiaSymbol_t` 로 normalize 된 데이터 전달.
- `pdb.enumerateLineNumbers(0, uint32_t(_imageSize), lines, files, _requiresShutdown)` — `IDiaSession::findLinesByAddr` 을 이미지 전 범위에 호출. `IDiaEnumLineNumbers` + `IDiaSourceFile` 의 연속 소비.

**DbgHelp 대비 이유**:
- `DbgHelp.dll` 는 thread-safety 약함 (프로세스 당 single SymHandle 컨텍스트). DIA 는 `IDiaSession` 단위로 격리.
- DbgHelp `SymEnumSymbols` 는 regex-like 이름 필터만 제공 — x64dbg 는 lexical 계층 (functions inside namespace etc.) 전체 탐색 필요.
- DIA 는 undecorated name 을 개별 `get_undecoratedNameEx(flags)` 로 세분화 제어 (DbgHelp `UnDecorateSymbolName` 은 flat flags).

**compat layer**: `src/dbg/dbghelp_compat.cpp` 는 development 브랜치 HEAD 에서 404 (문서 작성 시점 2026-04-21). 존재한 시기에도 thin DbgHelp → internal symbolsource shim 이었던 것으로 추정 (추후 확정 필요).

**`PDBDiaFile` 래핑 추정 구조** (소스 직접 관찰 못함, 일반 DIA wrapper 패턴 기반):
- 생성자에서 `CoInitializeEx(nullptr, COINIT_MULTITHREADED)` + `CoCreateInstance(CLSID_DiaSource, …, IID_IDiaDataSource, (void**)&pSource)`.
- `pSource->loadDataFromPdb(pdbPath)` 또는 `loadAndValidateDataFromPdb(path, guid, age)` (PE debug directory 와 GUID match 검증 — PDB/exe 미스매치 방어).
- `pSource->openSession(&pSession)` → `pSession->put_loadAddress(imageBase)` → symbol enumeration 시작.
- Cleanup 시 `pSession->Release()`, `pSource->Release()`, 프로세스 종료 시 `CoUninitialize()`.

**msdia140.dll 배포 제약**: 이 DLL 은 Visual Studio 또는 Windows SDK 와 함께 배포되며, end-user 시스템에 독립 재배포 불가 (MS 라이선스). x64dbg 는 snapshot 을 자체 번들 (`x64dbg/x64/msdia140.dll`) — GPL-3 와 MSDIA 재배포 라이선스의 호환성은 별도 법적 이슈 (본 문서 범위 외).

**AURA 적용**: AURA 는 현재 `src/parser/pdb_parser.c` 커스텀 파서 사용 (libelf/DbgHelp 의존 금지). DIA SDK 는 Windows-only COM 이라 cross-platform 유지 제약에 충돌. Phase 2-F v1.2 Windows release 에서 **보조 경로** (user 가 msdia140 보유 시 우선 사용) 만 검토. 근본적으로 AURA 는 **MSF (Multi-Stream Format)** 를 직접 파싱하므로 DIA 의존 없음 — 이것이 cross-platform 장점이자 PDB spec 변경에 대한 취약점.

### 2.2 PDB partial loading

**파일**: `src/dbg/symbolsourcedia.cpp`.

**현실**: x64dbg 는 **부분 로드하지 않는다**. `enumerateLineNumbers(0, uint32_t(_imageSize), …)` 이 이미지 전 범위를 한 번에 훑고, symbol 콜백도 `enumerateLexicalHierarchy` 에서 전체 계층을 소비. 수집 결과는 즉시 in-memory 인덱스로 사전 구축:
- `_symAddrMap` — RVA 오름차순 정렬.
- `_symNameMap` — decorated name 정렬.
- `_linesData`, `_lineAddrMap`, `_sourceLines` — 계층화된 라인 정보.
- 중복 symbol 은 스캔 중 제거.

**async**: `isOpen()`/`isLoading()`/`cancelLoading()`/`waitUntilLoaded()` 가 노출되므로 "loading 중에도 query 시도 가능" 이지만 query 는 `waitUntilLoaded` 로 블록될 가능성이 높다 (소스에서 확정 불가 — 함수명만 확인).

**500MB+ PDB 대응**: x64dbg 는 **명시적 대응 없음**. `msdia140.dll` 가 내부적으로 MSF stream random-access + 페이지 캐시를 수행하므로 DIA 사용자는 memory footprint 를 직접 제어하지 못한다. 실제로 대형 PDB (예: `ntkrnlmp.pdb` 800MB+) 를 로드하면 RSS 가 수백 MB 로 상승하는 것이 관찰되는 일반적 패턴.

**AURA 적용**: AURA 커스텀 PDB 파서는 역으로 **lazy stream 디코딩** 이 가능. 기회: GSI/PSI (Global/Public Symbol Index) 만 즉시 파싱 → DBI stream 의 module info 는 on-demand 로드 → TPI (Type) stream 은 `type_constraint` 실행 시에만. v2.3.0 Phase 2-E 에서 이미 TPI 는 lazy 하게 다루고 있다고 추정 (별도 확인 필요).

### 2.3 Export / Import 해석 (+ forwarder chain)

**파일**: `src/dbg/module.cpp` (`ReadExportDirectory`, `ReadImportDirectory`, `getProcAddress`).

#### Export (EAT)

1. `RtlImageDirectoryEntryToData` 로 `IMAGE_EXPORT_DIRECTORY` 위치.
2. directory bounds 검증 후 `AddressOfFunctions[]` 순회; RVA + `i + exportDir->Base` 로 ordinal 계산.
3. **Forwarder 감지**: export 의 function RVA 가 **export directory 자체 범위 내** 에 떨어지면 forwarder. 이는 PE spec 공식 정의.
4. **Forwarder name 파싱**: 해당 RVA 를 file offset 으로 변환 후 null-terminated 문자열 읽기 → `"DLL.FuncName"` 형식.
5. **Synthetic name**: 이름 없는 ordinal 전용 export 는 `"Ordinal#" + std::to_string(ordinal)` 합성.
6. `exportsByName` (name 정렬) + `exportsByRva` (RVA 정렬) 두 인덱스를 동시 유지.

#### `getProcAddress` 재귀 resolve

- `"DLL.FuncName"` 문자열에서 `.` 위치 분리 → 대상 DLL 의 module handle 획득 → 해당 module 에서 name lookup 반복.
- **재귀 깊이 상한** 존재 (configurable) — 무한 루프 방어 (forwarder A → DLL_B!X, DLL_B!X → A 인 케이스).

#### Import (IAT)

1. `IMAGE_IMPORT_DESCRIPTOR` 순회.
2. **Thunk 선택**: `OriginalFirstThunk` 우선 (ASLR-corruption-free), fallback 으로 `FirstThunk`. 이유: `FirstThunk` 는 런타임에 로더가 실제 주소로 덮어쓰므로 이름 리커버리에 비적합.
3. 각 `IMAGE_THUNK_DATA` 에서 `u1.AddressOfData` 추출.
4. **Ordinal 판별**: `(val & IMAGE_ORDINAL_FLAG) != 0` 이면 16-bit 마스크 후 ordinal 로 저장; 아니면 `IMAGE_IMPORT_BY_NAME.Name` (null-terminated) 읽기.
5. 주소가 부적합한 import 는 silent skip (ntdll loader 거동과 동일).
6. `importsByRva` 에 정렬 저장.

**AURA 적용**: AURA `src/parser/pe_parser.c` 는 이미 EAT/IAT 파싱 보유 (Phase 3.11 complete 으로 추정). x64dbg 와 비교 시 **forwarder chain 재귀 resolve** 와 **synthetic `Ordinal#` name** 두 포인트가 검증 체크리스트. 특히 forwarder 는 Windows 시스템 DLL (`kernel32.dll` → `kernelbase.dll`) 에서 광범위하게 사용되므로 누락 시 import 이름 복원 recall 하락.

### 2.4 Stack unwinding (SEH / CFI / FP)

**파일**: `src/dbg/stackinfo.cpp`.

3-tier strategy:

1. **x64 primary — `.pdata`/`.xdata` 기반 `RUNTIME_FUNCTION` 언와인드**:
   - `SafeStackWalk64()` (x64dbg 자체 래퍼 — MS `StackWalk64` 가 특정 상황에서 crash 하는 것 회피).
   - `StackSymFunctionTableAccess64()` callback 이 `ModInfoFromAddr()->findRuntimeFunction()` 을 호출 → `.pdata` 의 `RUNTIME_FUNCTION {BeginAddress, EndAddress, UnwindData}` 조회.
   - MS ABI 규격: `.xdata` 의 `UNWIND_INFO` + `UNWIND_CODE[]` 해석 (push/allocate/save-regs/set-fpreg). Windows x64 에는 SEH 와 별도 구조.

2. **x86 frame-pointer fallback**:
   - `SymFunctionTableAccess64()` (Windows DbgHelp) 사용 — x86 에서는 대부분 `EBP` 체인을 신뢰.
   - `/Oy` (omit frame pointer) 최적화 바이너리는 불완전.

3. **Heuristic "suspected" call stack** (`stackgetsuspectedcallstack`):
   - `ShowSuspectedCallStack` 옵션.
   - 스택 메모리를 선형 스캔 → 포인터처럼 보이는 값 수집 → 각 후보 주소 앞 **16 instruction** 역디스어셈블 → 앞에 `CALL` 이 있고 target 이 해당 값을 지시하면 return address 후보로 채택.
   - **어떤 unwind metadata 도 불필요** — stripped Linux 바이너리나 anti-debug 케이스에 유용.

**`UNWIND_INFO` / `UNWIND_CODE` 상세 (공식 PE/COFF spec)**:
```
UNWIND_INFO {
    uint8_t  Version:3;        // 1 (사실상 고정)
    uint8_t  Flags:5;          // UNW_FLAG_EHANDLER/UHANDLER/CHAININFO
    uint8_t  SizeOfProlog;     // 프롤로그 길이 (byte)
    uint8_t  CountOfCodes;     // UNWIND_CODE 수
    uint8_t  FrameRegister:4;  // 0 = no frame pointer, else RAX..R15
    uint8_t  FrameOffset:4;    // frame register offset /16
    UNWIND_CODE UnwindCode[CountOfCodes];
    // optional: chain info / exception handler RVA
}
UNWIND_CODE {
    uint8_t CodeOffset;        // 프롤로그 내 offset
    uint8_t UnwindOp:4;        // UWOP_PUSH_NONVOL / UWOP_ALLOC_LARGE/SMALL / UWOP_SET_FPREG / UWOP_SAVE_NONVOL / UWOP_PUSH_MACHFRAME
    uint8_t OpInfo:4;
}
```
Unwind 알고리즘: 현재 RIP 가 프롤로그/에필로그 사이에 있는지 판정 → 해당 범위에서만 `UNWIND_CODE[]` 를 **역순** 적용 → 이전 RSP/RBP/callee-saved 복원 → return address = `[RSP]` → pop → 다음 프레임으로.

**모듈 경계 횡단**: `StackGetModuleBaseProc64()` 콜백이 `ModBaseFromAddr()` 로 프레임마다 module base 를 re-resolve → 해당 모듈의 unwind metadata 로 전환.

**SEH (x86)**: 명시적 SEH handler chain walk 은 `stackinfo.cpp` 스니펫에서 직접 보이지 않음 (별도 SEH view 파일 추정 — 예: `msgexception.cpp`). x64 는 SEH 가 table-based 로 통합되어 별도 walk 불필요.

**AURA 적용 (Phase 3.14 `.eh_frame`)**:
- ELF 에서 `.eh_frame` 은 DWARF CIE (Common Information Entry) + FDE (Frame Description Entry) 로 `.xdata` 와 **개념 동일** (프롤로그 operation 의 reverse-encoding). AURA 가 DWARF CFI VM 을 구현하면 x86-64 ELF 에서 정확한 프레임 복원 가능.
- **매핑표** (Windows x64 vs DWARF):

| 개념 | Windows x64 | DWARF (Linux/BSD) |
|------|-------------|--------------------|
| Unwind descriptor | `RUNTIME_FUNCTION {begin, end, unwindData}` | `FDE {initialLocation, addressRange, cieRef}` |
| Operation encoding | `UNWIND_CODE[]` opcodes | DWARF CFI bytecode (DW_CFA_*) |
| Frame register | `FrameRegister` 4-bit | DW_CFA_def_cfa / DW_CFA_def_cfa_register |
| Callee-saved save | `UWOP_SAVE_NONVOL` (stack offset) | `DW_CFA_offset` |
| Section | `.pdata`/`.xdata` | `.eh_frame` / `.eh_frame_hdr` |
| Lookup | `RtlLookupFunctionEntry` binary search | `.eh_frame_hdr` binary search table |

- x64dbg 의 "suspected call stack" 은 **stripped 바이너리 의존 fallback** 의 직접 reference. AURA 정적 분석에서도 "CALL 앞 16 instr. 역디스어셈블 → 유효한 target" heuristic 을 function detection (Ghidra parity baseline 72/O0 → 90% 목표) 에 차용 가능. 단 정적 분석에서는 stack dump 가 없으므로 **relocation table + CALL target reachability** 로 proxy.
- **구체 적용안**: AURA 의 `function_detection_v2` (추정 모듈명) 에 `cfi_cover(ELF)` 또는 `pdata_cover(PE)` 단계 추가 → 각 FDE/RUNTIME_FUNCTION 의 `[begin, end)` 범위를 "확정 function" 으로 등록. 이 한 단계만으로도 ghidra parity O0 기준 +10~15 point 상승이 typical (DWARF/PE unwind 커버리지가 linker-generated thunk 제외 대부분 function 에 존재).

### 2.5 MAP file support

**확인 결과**: 본 task 범위에서 fetch 한 4개 파일 (`symbolinfo.cpp`, `symbolsourcebase.h`, `symbolsourcedia.cpp`, `module.cpp`, `stackinfo.cpp`) 에서 **Borland / Watcom / VC MAP 파일 파싱 코드는 관찰되지 않음**. x64dbg 는 `.map` 파일 로드를 지원하지만 이는 별도 파일 (예: `symbolsourcemap.cpp` 또는 GUI 의 `SymbolSourceManual`) 로 분리되어 있을 것으로 추정. 확정적 기술은 별도 follow-up 필요.

일반론 (AURA 참조):
- **Borland MAP**: `Address         Publics by Value` 섹션 + `0001:00000000` 형식 (segment:offset) — 각 라인은 segment 번호, relative offset, 데코레이션된 이름.
- **VC MAP (`/MAP` linker 플래그)**: `Address  Publics by Value              Rva+Base               Lib:Object` — `0001:00010000       _WinMain@16    0000000000411000 f   main.obj`.
- **Watcom MAP**: OMF object section 기반, 문법 상이.

**AURA 적용**: AURA 가 PDB 없는 Borland 바이너리 심볼 복원이 필요할 경우 user-supplied MAP 파일 파싱은 1 세션 구현. 그러나 우선순위 낮음 — Phase 3.12 PDB 강화 가치 대비 ROI 낮음.

### 2.6 Symbol name demangling

**MSVC demangle**:
- x64dbg DIA 경로는 `IDiaSymbol::get_undecoratedNameEx(flags, BSTR*)` 로 DIA 가 내부적으로 undecorate — **x64dbg 코드에 `UnDecorateSymbolName` 직접 호출은 `symbolinfo.cpp` 에서 관찰되지 않음**.
- `SymbolInfo.undecoratedName` 필드가 dual storage — 원본 `decoratedName` 과 함께 저장.
- DIA flags (공식 문서): `UNDNAME_COMPLETE`, `UNDNAME_NO_ARGUMENTS`, `UNDNAME_NAME_ONLY`, `UNDNAME_32_BIT_DECODE` 등 — user-configurable.

**Itanium C++ ABI (g++/clang)**:
- x64dbg 는 Windows 전용 이므로 Itanium 케이스 상대적 희박. 단 MinGW GCC 로 컴파일된 Windows PE 는 Itanium mangling 사용 (`_Z...`). x64dbg 가 `__cxa_demangle` 또는 libiberty `cplus_demangle` 래핑 여부 → 본 task 범위에서 미확인.

**AURA 적용**:
- AURA 는 `<cxxabi.h>` 의 `__cxa_demangle` 을 PRD §4.2 에서 승인 (GCC Runtime Exception, 정적 링크 허용) — Itanium ABI 커버. Windows MSVC mangling 은 `UnDecorateSymbolName` 이 Windows-only → cross-platform 유지 시 `llvm-Demangle` 또는 자체 파서 필요.
- **Dual name 저장** (decorated + undecorated) 은 AURA `symbol_entry_t` 에 반영 가치 — pattern match / search / export 시 두 표기 모두 검색 대상.

---

## 3. Trace recording

### 3.1 Binary format

**파일**: `src/dbg/TraceRecord.cpp`.

**File layout**:
```
┌─────────────────────────────────────────────────────────┐
│ magic 'T' 'R' 'A' 'C'                         4 bytes   │
│ size header                                   8 bytes   │
│ JSON metadata { ver, arch, hashAlgorithm,               │
│                 hash, compression, path }     variable  │
│ Per-instruction entries ...                             │
└─────────────────────────────────────────────────────────┘
```

**Per-entry layout (variable length)**:
| Field | Bytes | Semantics |
|-------|-------|-----------|
| block type | 1 | `TraceRecordType` (None/BitExec/Byte.../Word...) |
| register change count | 1 | delta-encoding count |
| memory access count | 1 | mem delta-encoding count |
| flags + opcode size | 1 | flags (thread-id-present 등) + opcode 길이 |
| thread ID | 0 or 4 | optional, flag-conditioned |
| opcode bytes | variable | raw instruction bytes |
| reg/mem delta | variable | SoA-grouped delta + position encoding |

**SoA (Structure of Arrays)**: 동일 타입 데이터 (예: register index) 를 연속 배치 → RLE 압축 효율 극대화. x64dbg 주석 기준: "improve compression ratio for homogeneous streams."

**Full register snapshot**: **매 512 instructions** 전체 register context 를 기록 → 덜 빈번한 restore point. Delta-only 연쇄 오류 방지 + 임의 위치 replay 의 pivot.

**Delta encoding 예시** (추정 — SoA 배치 기반):
```
이전 reg context: RAX=0x100, RBX=0x200, RCX=0x300 …
현재 명령: MOV RAX, 0x400        ; RAX 만 변경
엔트리:
  regChangeCount = 1
  regIdx[] = { 0 /* RAX */ }     ; SoA: 모든 인덱스 먼저
  regVal[] = { 0x400 }           ; SoA: 값 이어서
```
SoA 배치는 `{idx0, val0, idx1, val1, …}` (AoS) 대비 RLE 을 연속된 idx 시퀀스 또는 값 시퀀스에서 더 높은 반복율로 압축한다.

### 3.2 Replay mechanism

**상태**: 본 task 의 `TraceRecord.cpp` 응답에서 **explicit replay logic 이 확인되지 않음**. Infrastructure 만 관찰:
- `rtOldContext` — 이전 thread context 저장.
- `rtOldMemory` — 이전 memory delta 버퍼.
- Delta-chain + 512-instr snapshot 으로 임의 offset 복원 가능.

실제 replay UI (`TraceBrowser`, `TraceRegisters`) 는 `src/gui/Src/` 에 분산 — Task #37 (GUI panels) 범위. 본 문서는 format 계층만 커버.

### 3.3 Filter / search

- 본 task 범위 `TraceRecord.cpp` 스니펫에는 filter/search 직접 구현 부재.
- x64dbg UI 는 `TraceBrowser` 에 search box 제공 (명령어 mnemonic, register, memory pattern). 구현은 `src/gui/Src/BasicView/SearchListViewDialog.cpp` 에 위임되는 것으로 추정.
- **format 이 random-access 가능한지 여부**: 512-instr snapshot 이 있으므로 "O(instr_count/512)" seek 이후 delta 재생 가능. 실시간 search 에서는 전체 trace 를 선형 스캔하는 편이 일반적.

### 3.4 Block coverage + 정적 metric 교차

**API**: `getHitCount(duint address)`, `TraceExecute()`, `TraceExecuteRecord()`, `enableTraceRecording(bool, path)`, `increaseInstructionCounter()`.

**Storage modes (per-4KB page)**:

| Mode | Size/page | Counter bits | Max hits | 용도 |
|------|-----------|--------------|----------|------|
| BitExec | 512 B | 0 (presence only) | 1 | "instruction executed?" |
| ByteWith... | 4 KB | 6 | 63 | 저빈도 coverage |
| WordWith... | 8 KB | 14 | 16 383 | 고빈도 (loop body) |

- 2-bit 은 execution type (예: branch/taken/not-taken, linear, call, ret 등 카테고리), 나머지 6/14 bit 이 hit counter.
- Saturating counter — 최대값에서 clip.
- `TraceRecordPage` 가 페이지 단위 slot: `{rawPtr, rva, dataType, moduleIndex}`.

**AURA 정적 metric 과의 교차**:
- AURA 의 `gap_analyzer.sh` / coverage 측정은 **정적** (디컴파일된 function 중 HIR 생성 성공한 instruction 수 / 전체 instruction 수). Dynamic hit 이 아님.
- 공통점: **주소 공간 → 카운터** 의 dense map 구조. AURA 도 per-page bit map + byte counter 로 "decode 성공" vs "decode 실패" vs "decode 부분 성공" 3-상태를 기록하면 `covered_avg 55 flat` 천장 (project_real_binary_parity_2026_04_18.md) 을 주소 단위로 break-down 가능.
- **scope 외 명시**: AURA 가 dynamic execution 을 지원할 계획은 없음 (PRD §2 non-goal 추정). Trace recording 자체 이식은 제외.

### 3.5 Performance

- **Synchronous write**: `WriteFile` 를 명령당 호출 — async I/O 미사용. trace 활성 시 runtime overhead 상당.
- **Buffer size**: per-instruction 버퍼 3072 B — 대부분의 명령 (opcode 15B 최대, reg 20개 × 8B, mem 다수) 이 1 버퍼 안에 수용.
- **Snapshot cadence**: 512 instructions — 압축률 vs replay latency trade-off.
- **추정 overhead** (공식 수치 없음): 명령당 수 μs 추가 → 정적 분석은 μs 단위가 누적되지 않으므로 AURA 에서는 비고려.

---

## 4. AURA 적용 매트릭스

| AURA 축 | x64dbg layer | Priority | 비고 |
|--------|--------------|----------|------|
| **Phase 3.12 PDB 강화** | `SymbolSourceBase` dual name + load-state API | **High** | `isLoading`/`waitUntilLoaded` 패턴은 async PDB 로드 시 UI 응답성 확보 |
| Phase 3.12 PDB 강화 | `_symAddrMap`/`_symNameMap` dual index | High | AURA PDB 쿼리가 이미 있다면 정렬 인덱스 검증 |
| Phase 3.12 PDB 강화 | DIA `get_undecoratedNameEx` flag 기반 | Med | AURA 는 `__cxa_demangle` 쪽 (Itanium) — MSVC 커버는 보조 |
| **Phase 2-F v1.2 Windows** | DIA SDK `CoCreateInstance(CLSID_DiaSource)` | Med | Windows-only, msdia140 runtime 의존. 커스텀 PDB 가 충분 시 skip |
| Phase 2-F v1.2 Windows | Stream lazy-load (AURA 만 가능) | High | x64dbg DIA 가 full-load → AURA 의 차별화 기회 |
| **Phase 3.14 `.eh_frame`** | `RUNTIME_FUNCTION` .pdata/.xdata 패턴 | High | Windows x64 unwind ↔ DWARF CIE/FDE 쌍방향 reference |
| Phase 3.14 `.eh_frame` | "suspected call stack" heuristic | Med | stripped ELF 에서 CALL 16-instr. 역디스어셈블 fallback 차용 |
| **Function detection** | Forwarder chain resolve | Med | AURA PE 파서 검증 체크리스트 — `kernel32→kernelbase` 케이스 |
| Function detection | IAT `OriginalFirstThunk` 우선 | High | ASLR 처리 바이너리에서 name recall 필수 |
| **Symbol recall** | `"Ordinal#123"` synthetic name | Med | ordinal-only export 에 name 부여 |
| **Coverage metric** | Bit/Byte/Word 3-tier hit counter | **Low (참조만)** | AURA 정적 coverage 설계 시 dense map 구조 참고 |
| Trace recording | TRAC magic + JSON metadata + SoA delta | **Out of scope** | 동적 실행 — AURA PRD §2 non-goal |

---

## 5. Cross-reference (#33, #35, #38)

| Task | 겹침 | 차이 |
|------|------|------|
| **#33** (pattern/symbol/CLI/disasm view) | symbol server 4-tier (표면) | #39 는 `SymbolSourceBase` 추상화 + DIA 통합 + export/import/unwind 까지 깊이 |
| **#35** (디버거 코어 해체) | `src/dbg/` 전반 (`module.cpp`, `symbolinfo.cpp`, `TraceRecord.cpp` 포함) | #35 는 debugger loop (attach/step/bp) 중심, #39 는 symbol + trace 가로 |
| **#38** (plugin/scripting) | SDK export 함수 중 일부가 symbol API | #38 은 host↔plugin API 계약 (`_plugin_registercommand` 등), #39 는 엔진 내부 |
| **#36** (bridge API) | Bridge 가 symbol query 를 GUI 로 forward | #36 은 BridgeMain.cpp 의 GUI/DBG 경계, #39 는 DBG 쪽 implementations |
| **#37** (GUI panels) | SymbolView/CallStackView 가 #39 데이터 소비 | #37 은 Qt widget, #39 는 그 아래 data source |

**Triangulation note**: Rizin (#31/#32) 의 심볼 로더 (`bin_pdb.c`), Ghidra (#26) 의 `PdbApplicator` 와 함께 x64dbg 의 DIA wrapper 가 **3-way** reference → AURA PDB 로더 강화 시 최소 3 개 구현체를 병치 검증 가능.

---

## 6. 인용 (공개 소스)

1. **x64dbg repository** — https://github.com/x64dbg/x64dbg (GPL-3). 본 문서 기반 커밋: `development` 브랜치 HEAD, fetch 시점 2026-04-21.
   - `src/dbg/symbolinfo.cpp` — fallback chain (`SymbolFromAddressExact`, `SymbolFromAddressExactOrLower`, `SymEnum`).
   - `src/dbg/symbolsourcebase.h` — `SymbolSourceBase` 추상화, `SymbolInfo` 구조체.
   - `src/dbg/symbolsourcedia.cpp` — DIA 래퍼, `enumerateLexicalHierarchy` / `enumerateLineNumbers`.
   - `src/dbg/module.cpp` — `ReadExportDirectory` / `ReadImportDirectory` / `getProcAddress` / forwarder resolve.
   - `src/dbg/stackinfo.cpp` — `SafeStackWalk64` / `stackgetsuspectedcallstack`.
   - `src/dbg/TraceRecord.h`, `src/dbg/TraceRecord.cpp` — trace format, hit counter 3-mode.
   - `src/dbg/dbghelp_compat.cpp` — HEAD 404 (2026-04-21) 미확정.
2. **Microsoft DIA SDK** — https://docs.microsoft.com/en-us/visualstudio/debugger/debug-interface-access/
   - `IDiaDataSource`, `IDiaSession`, `IDiaSymbol`, `IDiaEnumLineNumbers`, `get_undecoratedNameEx`.
3. **Microsoft DbgHelp** — https://docs.microsoft.com/en-us/windows/win32/debug/dbghelp-functions
   - `StackWalk64`, `SymFunctionTableAccess64`, `UnDecorateSymbolName`, `SymFromAddr`.
4. **PE/COFF spec** — https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
   - `IMAGE_EXPORT_DIRECTORY`, `IMAGE_IMPORT_DESCRIPTOR`, `RUNTIME_FUNCTION`, `.pdata`/`.xdata`, `UNWIND_INFO`/`UNWIND_CODE`.
5. **x64dbg command reference** — https://help.x64dbg.com/en/latest/commands/analysis/index.html (비직접 인용 — command surface 확인용).
6. **Task #33 report** — `docs/research/x64dbg_analysis.md` (본 task 는 해당 문서의 §4 "PDB / symbol server" 심화판).
7. **AURA PRD** — `/PRD.md` §4.2 (`__cxa_demangle` 승인, libelf 금지).
8. **AURA 기존 연구** — `docs/research/ghidra_*` (Ghidra `PdbApplicator` 비교용), `docs/research/rizin_*` (`bin_pdb.c` 비교용).

---

## 7. 후속 follow-up (scope 외 확인 필요)

- [ ] `src/dbg/dbghelp_compat.cpp` 의 실제 구현 (404 — master 또는 tag 브랜치 fetch).
- [ ] MAP 파일 파서 위치 확정 — 추정 `SymbolSourceMap` 또는 `msgsymbol.cpp`.
- [ ] Itanium (`__cxa_demangle`) 사용 여부 — MinGW PE 바이너리 지원 확인.
- [ ] `TraceBrowser` 의 random-access seek 알고리즘 (512-instr snapshot 기반 점프).
- [ ] x86 SEH handler chain walk 구현 위치 (`msgexception.cpp` 추정).

이상 5 항목은 본 task 범위 밖으로, 후속 task (#35 디버거 코어 해체) 에서 자연스럽게 커버될 것으로 예상.

---

## 8. 구체 권고 (AURA 착수 가능 단위)

본 문서의 technical inventory 를 AURA 구현 단위로 환산하면 다음 5 건이 "1-2 세션" 규모 착수 가능:

### 8.1 [REC-1] PDB loader 의 dual-name 저장 (High, ~1 세션)
AURA `symbol_entry_t` 에 `decoratedName` 과 `undecoratedName` 필드 분리 (현재 통합 저장 추정). 변경 규모: 구조체 1 개, demangle caller 1 개, query API (`find_by_name`) 가 두 필드 모두 조회. 테스트: `libc++` 인 바이너리 로드 후 `std::__1::basic_string` 과 `_ZNSt...` 양쪽 검색 성공 확인. Phase 3.12 DoD 에 추가.

### 8.2 [REC-2] PE forwarder chain resolve (High, ~1 세션)
AURA PE 파서가 `kernel32!CreateFileA → kernelbase!CreateFileA` forwarder 를 이름 수준에서 따라가지 못하면 import name 해석 recall 이 Windows 10+ 에서 급락. 구현: `IMAGE_EXPORT_DIRECTORY.{VirtualAddress, Size}` 범위 내에 function RVA 가 있으면 forwarder 로 판정 → null-terminated string 읽기 → `.` split → 대상 모듈에서 재귀 lookup (depth 상한 16).

### 8.3 [REC-3] `.eh_frame` CFI 기반 function range 추출 (High, 2 세션)
AURA function detection 에 `.eh_frame_hdr` + FDE 범위 enumeration 추가. DWARF CFI VM 은 **실행 불필요** — range `[initialLocation, initialLocation+addressRange)` 만 취하면 function 경계 확정. Ghidra parity baseline 72/O0 → 예상 82-85/O0 으로 상승. PE x64 는 `.pdata` `RUNTIME_FUNCTION` 로 동일 효과.

### 8.4 [REC-4] Stripped binary "CALL-target" heuristic (Med, 1 세션)
unwind metadata 없는 stripped ELF 에서 function detection 보강. 구현: relocation table + direct `CALL` instruction 의 target address 를 function entry 후보로 등록. x64dbg 의 "16-instr 역디스어셈블" 은 AURA 에서는 단일 pass 로 충분 (정적 분석은 CALL target 을 바로 알 수 있음).

### 8.5 [REC-5] 정적 coverage dense map (Low, 참조만)
x64dbg 의 bit/byte/word 3-tier hit counter 구조를 AURA `decode_coverage_map_t` 에 차용. Per-4KB-page slot + saturating counter. `gap_analyzer.sh` 출력 `covered_avg 55` 천장 분석 시 주소별 상세 break-down 제공. 착수 조건: Phase 2-E 완료 후.

---

## 9. 결론

x64dbg 의 symbol engine 은 "abstract source + multi-backend fallback" 구조로, DIA 전체 로드라는 한계에도 불구하고 `SymbolSourceBase` 추상화 계층은 AURA 가 **lazy load 를 유지한 채로 차용** 가능한 형태다. Stack unwinding 은 Windows `.pdata/.xdata` 를 통해 DWARF `.eh_frame` 과 1:1 대응 관계를 형성하며, 이 대응표가 AURA Phase 3.14 의 구현 가이드가 된다. Trace recording 은 AURA scope 외이나, block hit counter 의 3-tier dense map 은 정적 coverage metric 에도 설계 참조 가치가 있다.

본 task 의 5 REC 권고 중 **REC-3 (`.eh_frame` function range 추출)** 이 단일 착수로 Ghidra parity baseline 을 가장 크게 개선할 것으로 예상되며, v2.3.0 Phase 2-E 이후 Phase 3.14 우선 착수를 권고.
