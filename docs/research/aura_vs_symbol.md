# AURA Symbol / Debug Info vs x64dbg — 비교 분석

> Task #43 (Team v2-3-0-phase-2b). 입력: `docs/research/x64dbg_analysis.md` (#33) §4 PDB/symbol server, `docs/research/x64dbg_symbol_trace.md` (#39) symbol engine 전체. AURA 측은 read-only 코드 리뷰.
>
> **Clean-room**: x64dbg GPL-3. 본 문서의 권고는 인터페이스·알고리즘 기술 수준이며 코드 직접 이식은 금지.
>
> **작성일**: 2026-04-21. **Author**: compare-3-symbol (Team v2-3-0-phase-2b).

---

## 1. AURA 현재 구현 상태

### 1.1 Phase 3.12 PDB loader (`src/parser/pdb_parser.c`, 686 LOC)

**커버 범위**:
- MSF 7.0 super block + directory stream 파싱 (`Microsoft C/C++ MSF 7.00` magic + 32B header, block size 검증 ≤ 0x10000).
- Stream 0(old dir)/1(PDB info)/2(TPI)/3(DBI)/4(IPI) 인덱스 하드코딩.
- **Full eager load**: `pdb_parse_from_buffer` → `msf_parse` 가 모든 스트림을 한번에 heap 으로 복사 (`msf_read_stream` 각 블록 `memcpy`).
- TPI: `LF_STRUCTURE / LF_CLASS / LF_UNION / LF_ENUM / LF_POINTER / LF_ARRAY / LF_PROCEDURE / LF_MODIFIER / LF_BITFIELD` 9종. `read_numeric_leaf` 로 CodeView 가변 길이 leaf 디코딩. Max 65 536 type.
- DBI: 헤더에서 `sym_record_stream` 인덱스 추출 후 `parse_symbol_records` 단일 패스 — `S_GPROC32 / S_LPROC32 / S_GDATA32 / S_LDATA32` 4종만. `S_UDT / S_CONSTANT / S_PROCREF / S_LPROCREF` 는 enum 선언만 있고 **handler 부재** (switch default 로 skip).
- Public API: `pdb_parse(path)` / `pdb_parse_from_buffer(buf, sz)` / `pdb_find_symbol(name)` 선형 탐색 / `pdb_find_line(addr)` 선형 탐색.

**명시적 제약**:
- `fsize > 512 MiB` 이면 `pdb_parse` 실패. Windows kernel PDB (800MB+) 는 로드 불가.
- `PDB_MAX_SYMBOLS = 65 536` cap.

### 1.2 Phase 3.10 DWARF parser (`src/parser/dwarf_parser.c`, 1 538 LOC)

**커버 범위**:
- DWARF v2–v5. `.debug_abbrev / .debug_info / .debug_line / .debug_str` 4 섹션 파싱. DIE 트리 재구성.
- `DW_TAG_compile_unit / subprogram / variable / base_type / structure_type / union_type / enumeration_type / pointer_type / array_type / typedef / const_type / volatile_type / subrange_type / member / enumerator / formal_parameter / subroutine_type` 전부.
- DWARF 5 `DW_AT_noreturn` 반영 (attribute 0x87).
- **Pre-1 (Session #9)**: ET_REL CALL relocation name 보존 — 재배치 가능 오브젝트의 static CALL target symbol name 을 CALL instruction 에 붙인다.

**명시적 제약**:
- `.debug_frame` 은 별도 처리 — CFI VM 미구현 (unwind 용 FDE 는 `eh_frame_parser.c` 로 일원화).

### 1.3 Phase 3.14 `.eh_frame` (`src/parser/eh_frame_parser.c`, 558 LOC + `include/eh_frame_info.h`)

**커버 범위**:
- `.eh_frame` CIE/FDE 파싱. CIE augmentation `z/R/L/P` handling, FDE encoding (`DW_EH_PE_*`) 전체.
- `.gcc_except_table` LSDA 파싱 → `EhRegion` (try/catch/cleanup, filter, type index).
- `length=0` padding tolerance: libjvm.so (689MB, 46 572 FDE) 에서 linker contribution 경계 padding 로 인한 조기 break 회피.
- Cap: `EH_MAX_FDES = 524 288`, `EH_MAX_REGIONS = 65 536`.

**Plumbing 상태** (C-5, Session #8 2026-04-19):
- `eh_frame_attach_if_enabled(fi)` — `AURA_EH_FLOW=1` env opt-in. `src/core/pipeline.c:1114` 에서 파이프라인 Step 5b 로 호출.
- Consumer 1: `src/symbolic/func_detect_ehframe.c` G1 — FDE `pc_begin` 을 function candidate 로 추가 (`CAND_SRC_FDE`). `func_detect.c:393` 주석: *"G1 .eh_frame FDE — 유일하게 유지되는 recall boost"*.
- Consumer 2 (E-2, Session #9): HIR_COMMENT 로 EH region 을 디컴파일 결과에 annotation.

**명시적 제약 (코멘트 기반)**:
- CFI VM **미구현** — FDE 가 갖고 있는 DW_CFA bytecode (프롤로그 operation reverse-encoding) 는 파싱만 하고 실행하지 않는다.
- `.rela.eh_frame` 미적용: 관계형(ET_REL) 오브젝트에서는 `pc_begin` 이 relocation 전 값이라 text 범위 밖으로 떨어지는 경우 skip.
- **CFG edge 생성 없음** — unwind/EH 흐름이 CFG 에 반영되지 않는다. Phase 3.14 문서상 "완결" 이 아닌 "plumbing + candidate + comment" 단계.

### 1.4 ELF 커스텀 파서 (`src/parser/elf_parser.c`, 525 LOC)

- `libelf` **미사용** (PRD §4.2 강제). `Elf64_Ehdr / Elf64_Shdr / Elf64_Sym / Elf64_Rela` 를 memcpy + cast 로 직접 디코드.
- `.symtab / .dynsym / .strtab / .dynstr` 전부 커버. `fi->symbols[i].demangled = aura_demangle(name)` 로 심볼 생성 시점에 demangle (eager).

### 1.5 Demangling (`src/core/demangle.cpp`, 45 LOC)

- Linux/GCC: `abi::__cxa_demangle` (GCC Runtime Exception, PRD §4.2 허용).
- MSVC path (`_MSC_VER`): `UnDecorateSymbolName` (DbgHelp, `UNDNAME_COMPLETE` flag 고정).
- **단일 flag 만 지원** — DIA 의 `get_undecoratedNameEx(flags, ...)` 세분화 부재.
- **Single-storage**: demangled 문자열이 성공하면 `sym->demangled` 에, 실패하면 NULL — **decorated + undecorated dual storage 아님**. 검색은 원본 `name` 필드에만 매칭.

### 1.6 PE parser (`src/parser/pe_parser.c`)

- Import: IMAGE_IMPORT_DESCRIPTOR 순회 시 `OriginalFirstThunk` 우선, 0 이면 `FirstThunk` fallback — x64dbg (#39 §2.3) 와 동일 우선순위.
- Export: `NumberOfNames` 반복, name-RVA → file offset 변환 후 strdup.
- **Forwarder chain 미지원**: function RVA 가 IMAGE_EXPORT_DIRECTORY 범위 내에 있는지 검사 없이 `addr = image_base + frva` 로 그대로 저장. `kernel32!CreateFileA → kernelbase!CreateFileA` 같은 forwarder 는 DLL.FuncName 문자열이 주소 필드에 기록되어도 resolve 되지 않는다.
- **Ordinal-only export 미처리**: `num_names` 만 반복하므로 이름 없는 ordinal export 는 drop. Synthetic `Ordinal#N` 합성 없음.

### 1.7 현재 한계 — Short list

| # | 항목 | 파일 | 현재 |
|---|------|------|------|
| L1 | PDB symbol server 자동 다운로드 | `pdb_parser.c` | ❌ 명시적 path 만 |
| L2 | PDB 500MB+ lazy stream 디코딩 | `pdb_parser.c:616` | ❌ 512MB cap + full eager |
| L3 | PDB async load state (`isLoading/waitUntilLoaded`) | — | ❌ sync 1-call |
| L4 | Decorated + undecorated dual-name 저장 | `elf_parser.c:487` 등 | ❌ single field |
| L5 | MSVC undecorate on Linux | `demangle.cpp` | ❌ `_MSC_VER` 전용 |
| L6 | PE forwarder chain resolve | `pe_parser.c:284-290` | ❌ 범위 체크 없음 |
| L7 | Synthetic `Ordinal#N` export name | `pe_parser.c:248-301` | ❌ drop |
| L8 | `.eh_frame` / `.pdata` → CFG unwinding edge | `func_detect_ehframe.c` + none | △ G1 candidate 만, CFG edge 없음 |
| L9 | Stripped fallback (CALL-target heuristic) | — | △ func_detect_v2 별도 경로, EH metadata 없는 케이스 proxy 부재 |
| L10 | Stack unwinding VM (DW_CFA / UNWIND_CODE 실행) | — | ❌ bytecode skip |
| L11 | MAP 파일 (Borland/VC/Watcom) | — | ❌ |
| L12 | DIA SDK (Windows msdia140) | — | ❌ custom MSF 로 대체 |
| L13 | 4-tier symbol fallback (debug → export → entry → IAT) | `extern_resolver.c` 등 | 부분적 (확인 필요) |
| L14 | CodeView S_UDT / S_CONSTANT / S_PROCREF handler | `pdb_parser.c:500` | ❌ default skip |

---

## 2. 격차 매트릭스

AURA ↔ x64dbg 교차표. ✅ = 동등, △ = 부분, ❌ = 없음, N/A = scope 외.

| 기능 축 | AURA (2026-04-21) | x64dbg (#33/#39) | Gap |
|---------|-------------------|------------------|-----|
| **PDB MSF 파싱** | ✅ 커스텀 MSF 7.0 | ✅ msdia140.dll wrapper | 동등 (AURA 장점: cross-platform) |
| PDB TPI — 9종 type leaf | ✅ | ✅ DIA 전체 | △ MSVC 전용 type (LF_VTSHAPE 등) 일부 누락 |
| PDB DBI — S_GPROC32/S_L\*32 | ✅ | ✅ | △ S_UDT/S_PROCREF/S_LPROCREF handler 부재 |
| PDB lazy partial load | ❌ | ❌ DIA 가 내부 page cache | Med — AURA 가 커스텀이기 때문에 **차별화 기회** |
| PDB symbol server DL | ❌ | ✅ msdl.microsoft.com | High — libcurl 이미 의존 |
| PDB async state API | ❌ | ✅ `isLoading/waitUntilLoaded` | Med — GUI Phase 8+ 전제 |
| Dual name storage | ❌ single | ✅ decorated + undecorated | High — 1 구조체 수정 |
| Undecorate flag 세분화 | ❌ COMPLETE 고정 | ✅ UNDNAME_* flags | Low — API 사용자 설정 여지 |
| MSVC undecorate on Linux | ❌ | N/A Windows-only | Med — llvm-Demangle 고려 |
| **PE export** | ✅ name-RVA | ✅ forwarder + Ordinal# | △ 두 케이스 누락 |
| Forwarder chain 재귀 | ❌ | ✅ depth-limited | **High** — Windows 10+ recall 직결 |
| Ordinal-only export | ❌ drop | ✅ `Ordinal#N` 합성 | Med |
| **PE import** — OriginalFirstThunk 우선 | ✅ | ✅ | 동등 |
| Import ordinal 분리 | ✅ `IMAGE_ORDINAL_FLAG` 인지 후 drop | ✅ ordinal 명시 저장 | △ AURA 는 현재 ordinal import 는 count 제외 |
| **DWARF** CIE/FDE/LSDA | ✅ 커스텀 | — (Windows only) | AURA 전용 |
| DWARF v5 `DW_AT_noreturn` | ✅ | N/A | — |
| **Unwind** x64 `.pdata`/`.xdata` RUNTIME_FUNCTION | ❌ | ✅ SafeStackWalk64 | Med — PE 32/64 에서만 필요 |
| Unwind CFI VM 실행 | ❌ | ✅ msdia/DbgHelp 내부 | Med — candidate 도입이 더 높은 ROI |
| `.eh_frame_hdr` binary search table | △ 섹션 인식만 | N/A (Windows) | AURA 전용 개선 |
| "Suspected call stack" heuristic | ❌ | ✅ stripped fallback | Low — 정적 분석 대체 heuristic 보유 (func_detect v2) |
| CFG edge for EH flow | ❌ HIR_COMMENT 만 (E-2) | N/A (런타임) | High — 정확 exception 흐름 복원 |
| **4-tier symbol fallback** | △ (extern_resolver 부분) | ✅ debug→export→entry→IAT | Med — 통합 API 통일 |
| **MAP file** | ❌ | △ (파일 위치 추정) | Low |
| **DIA SDK Windows path** | ❌ | ✅ msdia140 | Low — v1.2 Windows 이후 |

**Triangulation 주석**: Ghidra `PdbApplicator` / Rizin `bin_pdb.c` / x64dbg `PDBDiaFile` 3-way reference 중 AURA 가 x64dbg 처럼 Windows-only COM 에 묶이지 않은 것은 Ghidra 만 유일 (Java). AURA 는 커스텀 C 파서로 **cross-platform 유지**하면서 Ghidra/Rizin 은 하지 않는 native 성능 확보 — lazy load + symbol server 추가로 4-way 에서 가장 넓은 cover surface 확보 가능.

---

## 3. 단기 (1–3 세션)

### 3.1 [REC-S1] PDB partial loading — stream-on-demand

**목표**: `pdb_parser.c:616` 512MB cap 제거 + full eager → GSI/PSI lazy decode.

**변경 범위** (추정 2 세션):
- `MsfFile` 구조체에 `block_size` 외 `file_data + file_size` 는 이미 보관 중 (`pdb_parser.c:161-162`). `msf_read_stream` 을 **on-demand 호출**로 바꾸고, `msf_parse` 는 directory stream 만 eager 로드, 나머지 스트림은 `block_list` 만 보관.
- TPI/DBI 파싱 시점에 해당 스트림만 lazy read. `PdbTypeInfo` 조회 API 가 처음 touch 할 때 type 레코드 bytes 만 fetch.
- Cap 상향: 512MB → 1GB (+ `pdb_parse_from_buffer` 경로는 이미 무제한).

**검증**: `ntkrnlmp.pdb` (600MB+) open → `pdb_find_symbol("KeBugCheckEx")` 0.1s 내 응답. RSS 증가가 전체 파일 대비 20% 이내.

**비의존**: L1 (symbol server) 와 직교 — 병렬 구현 가능.

### 3.2 [REC-S2] Itanium C++ demangle — 이미 완료 + 확장

**상태**: AURA `aura_demangle` 이 `__cxa_demangle` 를 이미 래핑. x64dbg (#39 §2.6) 대비 동등.

**확장 과제**:
- `sym->decoratedName` / `sym->undecoratedName` dual field (L4). 현재 단일 `sym->name` + `sym->demangled` 구조에서 `decorated = name` / `undecorated = demangled` 의 의미 매핑은 이미 있으나, 검색 API (`pdb_find_symbol`) 가 `name` 만 검색. `pdb_find_symbol` 를 두 필드 모두 탐색하도록 수정 (~30 LOC).
- 2026-04-21 기준 `libc++` 바이너리에서 `std::__1::basic_string` 과 `_ZNSt3__112basic_stringIc...` 양쪽 검색 성공 → 검증 완료 판정.

**변경 범위**: 1 세션.

### 3.3 [REC-S3] PE forwarder chain resolve

**목표**: L6 해결. `kernel32.dll!CreateFileA` → `KERNELBASE.CreateFileA` forwarder 를 export 파싱 시점에 recognize + 재귀 resolve.

**알고리즘** (x64dbg `module.cpp` §2.3 clean-room 재구현):
1. `fill_exports` 에서 `frva` 를 취득한 후, `frva` 가 IMAGE_EXPORT_DIRECTORY 의 `[VirtualAddress, VirtualAddress+Size)` 범위 내에 있는지 검사 (AURA 는 DataDirectory[0] 의 `size` 이미 접근 가능).
2. 범위 내이면 `frva` 를 file offset 으로 변환 → null-terminated string 읽기 → `"DLL.FuncName"` 형식 파싱.
3. Symbol entry 에 `forwarder_target = strdup("DLL.FuncName")` 저장. 주소는 0 으로 marking.
4. **재귀 resolve 는 MVP 에서 제외** — forwarder target 은 런타임 loader 가 resolve 하므로 정적 분석에서는 이름만 보존하면 충분. depth-limited resolve 는 향후 선택적.

**변경 범위**: `pe_parser.c` ~60 LOC, `file_format.h` Symbol 구조체 `char *forwarder_target` 1 필드 추가. 1 세션.

**검증**: `kernel32.dll` 로드 후 `CreateFileA` export 의 `forwarder_target == "KERNELBASE.CreateFileA"` 확인.

### 3.4 [REC-S4] Ordinal-only synthetic name

**목표**: L7. `pe_parser.c:248-301 fill_exports` 는 `NumberOfNames` 만 반복하여 이름 없는 ordinal export 를 drop. AURA 에도 `Ordinal#123` 합성 적용.

**변경 범위**: `fill_exports` 를 `NumberOfFunctions` 반복 + 별도 name lookup 테이블 cross-reference 로 재작성. 미매칭 ordinal 은 `"Ordinal#%u"` 합성. 1 세션, ~40 LOC.

**선행 조건**: 없음. REC-S3 과 같은 함수를 수정하므로 같은 커밋으로 처리 권장.

---

## 4. 중기 (3–6 세션)

### 4.1 [REC-M1] Stack unwinding → CFG edge (Phase 3.14 완결)

**목표**: L8/L10. 현재 `.eh_frame` 은 function boundary candidate + HIR_COMMENT annotation 까지만 사용. CFG 에 **예외 흐름 edge** 를 명시하지 않으면 exception-aware decompile 에서 control flow 가 누락된다.

**단계 분해** (3 세션 추정):

1. **LSDA → CFG edge plumbing** (1.5 세션):
   - `EhRegion {region_start, region_length, landing_pad, action}` 각 항목에 대해, `region_start` 에 해당하는 basic block 끝에 **EH_THROW edge** 를 `landing_pad` BB 로 추가.
   - CFG 에 edge type `CFG_EDGE_EXCEPTION` 신설 (기존 fallthrough/branch/call 과 구분).
   - Decompile 출력에서 `try { ... } catch { landing_pad: ... }` 재구성 가능성 확보 (구문 재조립은 M2 로 유예).

2. **CFI VM 실행** (1 세션): DW_CFA_* bytecode 를 소형 stack machine 으로 실행하여 각 PC 에서 CFA/register 복원 규칙 산출. 정적 분석에선 "frame pointer 가 어디에 보존되었는가" 가 stack variable 타입 추론에 사용 가능 (predecessor 에서 save 된 callee-saved register 를 hazard 없이 복원).

3. **PE `.pdata`/`.xdata`** (0.5 세션): ELF `.eh_frame_hdr` 와 동치 의미의 PE 측 구조를 같은 `EhFrameInfo` 로 통합 → AURA 는 OS-independent unwind 표현 통일. x64dbg `stackinfo.cpp` §2.4 의 `UNWIND_CODE` 옵코드 5종 (`UWOP_PUSH_NONVOL`, `UWOP_ALLOC_LARGE/SMALL`, `UWOP_SET_FPREG`, `UWOP_SAVE_NONVOL`, `UWOP_PUSH_MACHFRAME`) 디코드.

**검증**:
- libjvm.so (46 572 FDE) 파싱 후 EH edge 개수가 `region_count` 와 일치.
- C++ 바이너리에서 `throw/catch` 쌍이 있는 함수 디컴파일 시 `landing_pad:` label 출력.
- Ghidra parity baseline 72/O0 → 목표 +5–8%p (x64dbg 분석 §2.4 주석: "이 한 단계만으로 +10–15 point 가 typical").

### 4.2 [REC-M2] Symbol server 자동 다운로드 (libcurl + msdl.microsoft.com)

**목표**: L1. Windows PE 바이너리에서 `RSDS` 디버그 디렉토리의 `(guid, age, pdb_name)` 를 읽고 로컬 캐시 miss 시 `https://msdl.microsoft.com/download/symbols/{pdb_name}/{guid}{age}/{pdb_name}` 경로로 GET.

**단계** (2 세션):

1. **PE RSDS 추출** (0.5 세션): `IMAGE_DEBUG_DIRECTORY` 의 `IMAGE_DEBUG_TYPE_CODEVIEW` 엔트리에서 `RSDS {signature=0x53445352, GUID, Age, PdbFileName}` 디코드. PRD 에 RSDS 파싱 언급 없음 — 신규.
2. **libcurl client** (0.5 세션): `~/.cache/aura/symbols/{pdbname}/{sig}/{pdbname}` 경로 존재 여부 확인 → miss 시 libcurl GET, 0-byte 파일 검출 및 삭제. 기본 서버는 opt-in CLI flag `--sym-server <URL>` 로 활성화 (보안 고려 — 자동 off).
3. **2-level cache 관리** (1 세션): SSL cert 검증, rate-limit, disk quota (기본 5GB). Phase 2-F v1.2 Windows 에 align.

**Why libcurl**: PRD §기술 스택 에 이미 `libcurl ≥ 7.0` 확정 (LLM HTTP 클라이언트). **추가 의존 0**.

**검증**: `notepad.exe` RSDS 추출 → `notepad.pdb` 자동 다운로드 → `pdb_parse` 성공. Cache hit 시 네트워크 호출 없음.

### 4.3 [REC-M3] 4-tier symbol fallback 통합

**목표**: L13. x64dbg `symbolinfo.cpp` §4.3 의 `debug → exports → entry → IAT` 4-tier 폴백을 AURA 단일 query API 로 통일. 현재 `extern_resolver.c` / `pdb_find_symbol` / PE import 가 분산.

**API 설계** (1 세션):
```c
typedef enum {
    AURA_SYM_SRC_DEBUG = 0,   /* PDB / DWARF */
    AURA_SYM_SRC_EXPORT,      /* PE export / ELF dynsym */
    AURA_SYM_SRC_ENTRY,       /* entrypoint pseudo "_start" */
    AURA_SYM_SRC_IAT,         /* PE import / PLT */
} AuraSymSrc;

const Symbol *aura_sym_from_address(const FileInfo *fi,
                                    uint64_t addr,
                                    AuraSymSrc *src_out);  /* OR nearest-or-below */
```

**구현 노트**: 현재 `fi->symbols[]` 단일 배열을 그대로 쓰되 `src_out` 으로 source 태깅만 확장. `x64dbg SymbolFromAddressExactOrLower` 동치 함수 추가 — stack walking 에서 사용.

---

## 5. 장기 (6+ 세션)

### 5.1 [REC-L1] DIA SDK Windows-only path (Phase 2-F v1.2)

**검토 결과 — 비권고**: #39 §2.1 에서 확인된 대로 msdia140.dll 은 Visual Studio / Windows SDK 재배포 제약, GPL-3 / MSDIA 라이선스 충돌 위험 (x64dbg 실사례). AURA Apache-2.0 라이선스에서도 동일한 재배포 이슈. **커스텀 MSF 파서 유지가 전략적 차별화**.

단, v1.2 Windows only 빌드에서 **user-provided msdia140** (VS 설치된 개발자 PC) 을 감지하면 COM 경로 **보조 활성화** 는 검토 가능 — fallback 이 아니라 secondary source 로, 커스텀 파서와 교차 검증용. 2–3 세션, Windows-only #ifdef.

### 5.2 [REC-L2] MAP file support

**검토 결과 — 낮은 ROI**: #39 §2.5 참조. Borland / VC / Watcom MAP 포맷은 PDB 가 없는 바이너리 (레거시 delphi / old MSVC) 에서만 의미. AURA user base 가 이들 바이너리를 주로 다룬다는 evidence 가 현재 없음 (project_real_binary_parity_2026_04_18.md 는 cat/ls/aura-self 모두 ELF). **deferred** — 사용자 요청 시점에 1 세션 구현.

### 5.3 [REC-L3] MSVC undecorate on Linux (llvm-Demangle)

**검토 결과 — Med ROI / High 복잡도**: `UnDecorateSymbolName` 은 Windows-only. Cross-platform 커버 시 llvm-Demangle library 정적 링크 또는 자체 파서 필요. MSVC PE 를 Linux 에서 리버싱할 때만 유용 → Windows 개발자는 이미 Windows 에서 작업. 대기.

---

## 6. 항목별 spec (REC 우선순위)

### [REC-S1] PDB partial loading spec

- 파일: `src/parser/pdb_parser.c`, `include/pdb_info.h`.
- 변경 구조체: `MsfStream` 에 `uint32_t *block_list` + `uint32_t block_count` 추가, `data` 는 lazy (초기 NULL).
- 함수 신설: `static int msf_stream_ensure(MsfFile*, uint32_t stream_idx)` — 호출 시 data 로드.
- TPI/DBI 파싱: top-level metadata (stream directory + PDB info stream) 만 즉시 decode. Type index `ti_min/ti_max` 를 `PdbInfo` 에 저장하고, 개별 type 레코드는 `pdb_get_type(info, type_index)` 호출 시 materialize.
- DoD: `fsize > 512MB` 파일도 open 성공, `pdb_find_symbol` 이 평균 미지(stream) access 비용으로 응답, 전체 파일 대비 RSS < 30%.

### [REC-S3] Forwarder resolve spec

- 파일: `src/parser/pe_parser.c` (`fill_exports`), `include/file_format.h` (`Symbol` 필드 추가).
- Symbol 구조체 필드 추가: `char *forwarder_target; /* "DLL.FuncName" or NULL */`.
- `fill_exports`:
  ```
  if (exp_rva <= frva < exp_rva + exp_size) {
      size_t fwd_off = rva_to_offset(shdr, num_sec, frva, fsz);
      sym[i].forwarder_target = read_cstring_at(map, fsz, fwd_off);
      sym[i].address = 0;
  } else {
      sym[i].address = image_base + frva;  /* 기존 로직 */
  }
  ```
- `Symbol` destroy path 에서 `free(forwarder_target)` 추가.
- DoD: `tests/parser/test_pe_forwarder.c` 신규 — `kernel32.dll` 혹은 자체 생성 test PE 로 CreateFileA → KERNELBASE.CreateFileA 매핑 검증.

### [REC-S4] Ordinal synthetic name spec

- 파일: `src/parser/pe_parser.c`.
- `fill_exports` 재작성: `NumberOfFunctions` 반복 + name→ordinal 역매핑 테이블 구성 후 미매칭 ordinal 에 `snprintf(buf, 32, "Ordinal#%u", ordBase + i)` 합성.
- `sym[i].type = AURA_SYM_EXPORT; sym[i].synthetic = 1;` (선택적 필드 — 다른 경로에서 distinguish 용).
- DoD: Ordinal-only export 가 있는 test PE 에서 `Ordinal#1` 등 이름 등장.

### [REC-M1] EH CFG edge spec

- 파일: `include/cfg.h` (edge type enum 확장), `src/core/pipeline.c` (plumbing), `src/symbolic/eh_cfg.c` (신규).
- Edge type: `CFG_EDGE_EXCEPTION` 추가. `EhRegion → CFG edge` 매핑 시 predecessor BB 의 `region_start..region_start+region_length` 에 걸쳐 있는 마지막 `call/invoke` 명령 뒤에 edge 첨가.
- DoD: libstdc++ 에 linked 된 C++ 바이너리 (ex. aura-self) 디컴파일 시 `try { ... } catch` 구조 일부 복원, CFG metric `exception_edges > 0`.

---

## 7. 의존성 그래프

```
[REC-S2] dual-name search     ──────────┐
                                          │
[REC-S3] forwarder       ─┐               │
[REC-S4] Ordinal#         ├─ PE parser   │
                          │   block 완료  │
[REC-S1] PDB partial     ──┤              │
                           │              │
[REC-M3] 4-tier sym API ◀──┴──────────────┘  (통합 API 는 S-group 이 모두 끝난 후 집결)
                           │
                           ▼
[REC-M2] Symbol server DL   (libcurl 이미 의존, 독립 진행 가능)
                           │
[REC-M1] EH CFG edge ──────┴──▶ Phase 3.14 완결 → Phase 2-F 로드맵 연결
                           │
[REC-L1] DIA SDK (Windows) ┤
[REC-L2] MAP file           │    (deferred)
[REC-L3] llvm-Demangle      ┘
```

**Critical path**: REC-S1 + REC-S3 → REC-M1 → Phase 3.14 완결. REC-S2 / REC-S4 / REC-M2 / REC-M3 은 병렬 가능.

---

## 8. Phase 2-X 로드맵 매핑

| Phase | 관련 REC | 목표 효과 |
|-------|----------|-----------|
| **Phase 2-E 잔여** (v2.3.0 현재) | REC-S2 dual-name search, REC-S4 Ordinal# | 단일 함수 수정 수준, v2.3.0 rc 에 포함 가능 |
| **Phase 2-F v1.2 Windows** | REC-M2 symbol server, REC-S3 forwarder, REC-L1 DIA 검토 | Windows PE 리버싱 recall 대폭 상승 |
| **Phase 3.12 강화** | REC-S1 PDB partial | 대형 PDB (kernel, driver) 지원 — 현재 512MB cap 제거 |
| **Phase 3.14 완결** | REC-M1 EH CFG edge, CFI VM 부분 | 디컴파일 exception flow 복원 |
| **Phase 2-Quality baseline 향상** | REC-M1 (FDE+unwind 통합 candidate) | Ghidra parity 72/O0 → +5-8%p 추정 |

**Version alignment**: feedback_aura_versioning_policy.md (Session #9 결정) 에 따라 Ghidra parity 도달 전까지 tag 금지. REC-S/M 묶음은 **PR merge 기준**으로 진행하며 rc3 이후 누적.

---

## 9. 인용

### 9.1 AURA 소스 (read-only, Session #9 기준)

- `src/parser/pdb_parser.c` — MSF/TPI/DBI 파싱 (686 LOC, Phase 3.12).
- `include/pdb_info.h` — PdbInfo/PdbSymbol/PdbTypeInfo 공개 API.
- `src/parser/dwarf_parser.c` — DWARF v2-v5, Pre-1 CALL reloc name 포함 (1 538 LOC).
- `src/parser/eh_frame_parser.c` — .eh_frame CIE/FDE + LSDA (558 LOC, Phase 3.14 partial).
- `include/eh_frame_info.h` — `eh_frame_attach_if_enabled` C-5 opt-in API.
- `src/parser/elf_parser.c:446-493` — ELF symbol + `aura_demangle` 호출 지점.
- `src/parser/pe_parser.c:248-301` — PE export 파싱 (forwarder 미지원 현재 상태 확인).
- `src/core/demangle.cpp` — __cxa_demangle / UnDecorateSymbolName wrapper (45 LOC).
- `src/symbolic/func_detect_ehframe.c` — G1 FDE candidate (C-5 consumer).
- `src/core/pipeline.c:1105-1169` — `eh_frame_attach_if_enabled` plumbing.
- `PRD.md §4.2` — libelf 금지 + `__cxa_demangle` 허용 근거.

### 9.2 입력 research docs

- `docs/research/x64dbg_analysis.md` (Task #33) §4 PDB / Symbol Server, §8 REC-x-2 symbol server client.
- `docs/research/x64dbg_symbol_trace.md` (Task #39) — 전체.
  - §2.1 DIA SDK, §2.2 partial loading, §2.3 Export/Import forwarder, §2.4 stack unwinding (.pdata/.xdata ↔ .eh_frame), §2.5 MAP, §2.6 demangling.
  - §3 trace recording — **scope 외** (AURA PRD §2 non-goal).
  - §4 AURA 적용 매트릭스, §8 REC-1..5.

### 9.3 공식 spec

- LLVM PDB docs — https://llvm.org/docs/PDB/index.html (MSF / TPI / DBI / Stream directory).
- PE/COFF spec — https://learn.microsoft.com/en-us/windows/win32/debug/pe-format (IMAGE_EXPORT_DIRECTORY, RUNTIME_FUNCTION, UNWIND_INFO/UNWIND_CODE).
- DWARF v5 spec, §6.4 (.debug_frame / .eh_frame), §6.4.1 (CIE/FDE), §6.4.2 (DW_CFA).
- LSB Core Generic §10.6 (exception handling tables, LSDA).
- Itanium C++ ABI — https://itanium-cxx-abi.github.io/cxx-abi/abi.html (name mangling, `__cxa_demangle`).
- Microsoft DIA SDK — https://docs.microsoft.com/en-us/visualstudio/debugger/debug-interface-access/ (**비권고 reference**).

### 9.4 라이선스 / Clean-room

- x64dbg **GPL-3**. 본 문서의 REC 권고는 공개 소스 관찰 + 공식 spec 기반 기술 설명이며 코드 직접 이식 금지. AURA 구현은 clean-room 재작성.
- AURA **Apache-2.0**. `__cxa_demangle` GCC Runtime Exception 정적 링크 허용 (PRD §4.2, 2026-03-26 승인).
- msdia140.dll **Microsoft 재배포 제약** — AURA 에서 직접 번들 금지. user-provided 경로만 허용.

### 9.5 Triangulation 참조

- Ghidra `PdbApplicator` — docs/research/ghidra_func_detect_analysis.md §3-4 (Java 구현, 별도 파일).
- Rizin `bin_pdb.c` — docs/research/rizin_func_detect_analysis.md §4 (C 구현, FLIRT + zignatures 동행).
- 본 문서 + 두 reference 로 **3-way 최소 triangulation** 구성, REC-S1 partial load 설계 시 병치 검증 권장.

---

## 10. Executive Summary

AURA 의 symbol/debug info 스택은 **ELF+DWARF 방향으로는 상대적으로 완결**되어 있으며 (Phase 3.10 + 3.14 plumbing), **PE+PDB 방향에 집중된 격차 7건**이 존재한다: (i) PDB symbol server 부재, (ii) 512MB cap + full eager load, (iii) PE forwarder chain 미처리, (iv) ordinal-only export drop, (v) dual-name 저장 부재, (vi) `.eh_frame` → CFG unwinding edge 없음, (vii) CFI VM 미실행. 이 중 (vi) 만이 ELF 측에 영향을 미치며 Phase 3.14 완결의 최대 blocker.

**착수 순서 제안**:
1. **즉시 (v2.3.0 Phase 2-E 잔여)**: REC-S2 dual-name search + REC-S4 Ordinal# — 단일 함수 수정 수준.
2. **Phase 2-F v1.2 Windows 합류 시**: REC-S3 forwarder + REC-M2 symbol server.
3. **Phase 3.14 완결 세션**: REC-M1 EH CFG edge. 가장 큰 단일 품질 개선으로 Ghidra parity baseline +5-8%p 예상.
4. **PDB 대형 파일 케이스 발생 시**: REC-S1 partial load.

**비권고**: REC-L1 (DIA SDK) — msdia140 재배포 이슈 + AURA 커스텀 MSF 가 전략적 차별화.
**Deferred**: REC-L2 (MAP) / REC-L3 (llvm-Demangle) — 사용자 요청 시점에 재평가.

본 분석의 단기 4 + 중기 3 권고가 구현되면 AURA 는 4-way 비교 (Ghidra / Rizin / x64dbg / AURA) 중 **cross-platform × native 성능 × lazy-capable** 의 유일 교집합 포지션을 확보하며, Windows PE recall 이 x64dbg 과 동등 수준으로 수렴한다.
