# Ghidra 디컴파일 파이프라인 + 함수 탐지 재분석

> **Session #9 (2026-04-20), v2.3.0 Phase 2-E 병렬 연구 (Task #26)**
> 작성자: research teammate (Team `v2-3-0-phase-2b`)
> 범위: NSA Ghidra `master` 브랜치 (2026-04 기준) 소스 + 공식 API 문서
> 대상 AURA: v2.3.0-rc1.1 + Phase 2-E 진행 중

---

## 1. Executive Summary

Ghidra 의 함수 탐지는 **아키텍처별 XML 패턴 DSL + 서명 해시 DB + Pseudo 재-디스어셈블 검증** 이라는 3 층 엔진을 분석 우선순위 스케줄러 위에서 구동한다. AURA 는 동일 목표(프롤로그/콜-타겟/xref/심볼)를 C 코드로 하드-코딩한 `func_detect.c` + G1(.eh_frame) / G2(.init_array) / PLT / `flirt.c` + `func_id.c` 조합으로 달성하고 있으며, 현재 성능은 **Recall 80.5% / Precision 93.6% / F1 0.866** 수준 (AArch64 stripped 기준). 실 바이너리 3 개 측정 (cat 15.8% / ls 45.1% / aura-self 87.6%) 결과는 **covered_avg 55 에서 구조적 천장** 에 부딪친 상태다.

**Ghidra 대비 핵심 격차 (top 3, 우선순위 순)**:

1. **Pre/Post context-aware 패턴 매칭 부재** — Ghidra 는 "함수 시작 후보 X 의 바로 앞 바이트가 `ret`/`nop`/`defined` 인가?" 를 XML 제약(`<prepatterns>`, `after="defined"`)으로 검증. AURA 는 후보 지점 자체만 본다. FP 의 절반 이상이 이 검증 단계에서 차단 가능.
2. **XML-driven 외부화 불가 → 컴파일러/ABI 확장 비용 O(코드 변경)** — Ghidra 는 `x86-64gcc_patterns.xml`, `x86-64win_patterns.xml`, `AARCH64_LE_patterns.xml` 를 runtime 로드. AURA 는 새 compiler/ABI 지원 시마다 C 재컴파일 필요.
3. **두 단계 FID (short + body) signature 누락** — Ghidra FID 는 `SHORT=4 code-units` + `MEDIUM=24 code-units` + `FULL-body` 3 중 해시를 `InstructionSkipper` 로 정규화하여 매칭. AURA `func_id.c` 는 **prologue-only 단일 해시** → libc/CRT 함수 식별 신뢰도 낮음.

**최대 레버 (품질 향상 기대 Δ 순)**:
- **단기**: Pre-pattern 검증 gate → **Precision +3~5%p** (FP 의 주범 = post-ret 노이즈 + alignment pad 뒤 오검출), 구현 난이도 LOW, `func_detect.c` 내부 함수 ~60 라인 추가.
- **중기**: XML pattern DSL 로더 + Ghidra 의 `x86-64gcc/AARCH64_LE` 패턴 이식 → **Recall +2~3%p**, 구현 LOW-MED, `third_party/ghidra_patterns/` 드롭-인.
- **중기**: Medium-hash FID 확장 → libc/CRT 함수 자동 naming → **Precision 체감 개선** (분석가 관점).

---

## 2. Ghidra 디컴파일 파이프라인 전체 흐름

### 2.1 분석 우선순위 표 (검증된 순서)

[출처: `ghidra/app/services/AnalysisPriority`]

| # | 우선순위 | 주요 Analyzer | AURA 대응 |
|---|---|---|---|
| pre-0 | `FORMAT_ANALYSIS.before().before().before()` | **NoReturnFunctionAnalyzer** (exit/abort 등 알려진 no-return 심볼 마킹) | `noreturn_detect.c` (부분) |
| 0 | FORMAT_ANALYSIS | Loader (PE/ELF/Mach-O opinion) | `elf_parser.c`, `pe_parser.c`, `macho_parser.c` |
| 1 | BLOCK_ANALYSIS | Memory block/section 분류 | `file_format.c` |
| 2 | DISASSEMBLY | Shift-reduce 디스어셈블러 | `disasm.c` (Capstone wrap) |
| 3 | CODE_ANALYSIS | Constant propagation, flow | `const_prop.c`, `cfg.c` |
| 3+2 | `CODE_ANALYSIS.after().after()` | **FunctionStartAnalyzer** (BulkPatternSearcher 기반) | `func_detect.c` Phase A-D + G1/G2/PLT |
| 4 | FUNCTION_ANALYSIS | CreateFunctionCmd (body 확장) | `func_detect.c` `build_funclist` |
| 4-1 | `CODE_ANALYSIS.before().before()` | **ExternalEntryFunctionAnalyzer** (entry-point symbol → func) | (AURA 는 ELF `e_entry` 단독) |
| 5 | REFERENCE_ANALYSIS | XREF build | `xref.c` |
| 6 | DATA_ANALYSIS | String/scalar refs | `string_refs.c`, `data_refs.c` |
| 7 | FUNCTION_ID_ANALYSIS | **FID signature matching** (FNV1a64) | `flirt.c` + `func_id.c` (간단 FNV-1a) |
| 8 | DATA_TYPE_PROPOGATION | 타입 전파 | `type_inference.c`, `type_constraint.c` |
| post | **DecompilerFunctionAnalyzer** (Parameter ID) | 디컴파일러 호출 → 파라미터 복원 | `param_id.c` |

### 2.2 디컴파일 파이프라인 단계 (ASCII)

```
Ghidra                                     AURA
────────────────────────────────────────   ────────────────────────────────────────
[Loader opinion]                           file_format.c (format opinion)
  ↓                                          ↓
FORMAT_ANALYSIS                            elf_parser / pe_parser / macho_parser
  ↓                                          ↓
BLOCK_ANALYSIS                             section/symbol table build
  ↓                                          ↓
DISASSEMBLY (Sleigh)                       disasm.c (Capstone)
  ↓                                          ↓
CODE_ANALYSIS                              cfg.c + const_prop.c
  ↓ ─ FunctionStartAnalyzer                  ↓ ─ func_detect.c
  │   (BulkPatternSearcher+XML pattern)      │   (C-hardcoded prologue + G1/G2/PLT)
  ↓                                          ↓
FUNCTION_ANALYSIS (CreateFunctionCmd)      build_funclist + callgraph
  ↓                                          ↓
REFERENCE_ANALYSIS                         xref.c (call/jmp target)
  ↓                                          ↓
DATA_ANALYSIS                              string_refs / data_refs / const_refs
  ↓                                          ↓
FUNCTION_ID_ANALYSIS (FidService)          flirt.c + func_id.c (FNV-1a, 단일 tier)
  ↓                                          ↓
DATA_TYPE_PROPAGATION                      type_inference / type_constraint
  ↓                                          ↓
Decompiler (Ghidra P-Code)                 hir_builder → pass_manager → codegen
  ↓                                          ↓
DecompilerFunctionAnalyzer (param ID)      param_id.c
  ↓                                          ↓
Pseudo-C output                            emitter.c / decompile_all (E-3)
```

### 2.3 AURA 와의 아키텍처 차이 요약

| 관점 | Ghidra | AURA |
|---|---|---|
| Scheduler | `AutoAnalysisManager` + priority 기반 큐 | `pipeline.c` 단일 순차 호출 |
| 확장성 | `AbstractAnalyzer` 서브클래스, XML manifest 등록 | C 함수 직접 호출, `analyzer_registry.c` 보조 |
| 상태 저장 | ProgramDB (SQLite-like) + undo/redo | stateless in-memory + CLI 재실행 |
| 언어 | Java (JVM 기반, 가비지 컬렉션) | C/C++ (네이티브) |
| 디스어셈블러 | Sleigh (declarative DSL) | Capstone (외부 라이브러리 wrap) |
| 디컴파일러 IR | P-Code | HIR (AURA 고유) |
| 패턴 매칭 | XML decision tree | 하드코딩된 C 함수 |

---

## 3. Ghidra 함수 탐지 메커니즘 심층

### 3.1 Entry point analysis

Ghidra 는 "entry point" 를 다음 소스에서 수집한다:

| 소스 | 파일 | 설명 |
|---|---|---|
| ELF `e_entry` | Loader opinion | 바이너리 진입점 (main 이 아님, `_start`) |
| ELF `.init_array` / `.fini_array` / `.preinit_array` | Loader + ApplyDataArchiveAnalyzer | ctor/dtor 함수 포인터 |
| PE `AddressOfEntryPoint` + Export table | PE loader | Windows 바이너리 진입점 |
| Mach-O `LC_FUNCTION_STARTS` | `MachoFunctionStartsAnalyzer` | Mach-O **메타데이터에 모든 함수 시작이 저장**됨 (우선순위 낮게 실행 — switch table 오검출 방지) |
| `ExternalEntryPointIterator` | `ExternalEntryFunctionAnalyzer` | Symbol table 의 external entry points |
| DWARF / PDB `.debug_*` | `DWARFAnalyzer`, `PdbAnalyzer` | 디버그 정보 기반 함수 시작 + prototype |

### 3.2 Function boundary 결정 — BulkPatternSearcher + XML DSL

Ghidra 의 핵심 `FunctionStartAnalyzer` 는 `BulkPatternSearcher<Pattern>` 로 XML 패턴 파일을 소비한다 [출처: `Ghidra/Features/BytePatterns/src/main/java/ghidra/app/analyzers/FunctionStartAnalyzer.java`]:

```java
public FunctionStartAnalyzer(...) {
    ...
    setPriority(AnalysisPriority.CODE_ANALYSIS.after().after());
    setDefaultEnablement(true);
    ...
}
```

**패턴 파일 경로 관습**:
```
Ghidra/Processors/<Arch>/data/patterns/<arch>_<endian>_patterns.xml
Ghidra/Processors/<Arch>/data/patterns/<arch>_<compiler>_patterns.xml
                                        ^^^ e.g. x86gcc / x86win / x86-64gcc / x86-64win / x86delphi
```

아키텍처별 구성 (2026-04 기준 master):
- `x86/data/patterns/` — x86-64gcc, x86-64win, x86gcc, x86win, x86delphi, x86-16_default + `prepatterns.xml`
- `AARCH64/data/patterns/` — AARCH64_LE, AARCH64_win + `pre/postpatternconstraints.xml`
- `ARM/data/patterns/` — ARM_LE, ARM_BE, ARM_switch, prepatterns
- `MIPS/data/patterns/` — MIPS_LE/BE
- `PowerPC/`, `RISCV/`, `Hexagon/`, `Loongarch/`, `NDS32/`, `68000/`, `Atmel/` 등

**XML 구조** (실제 AArch64 예시):

```xml
<patternlist>
  <patternpairs totalbits="32" postbits="16">
    <!-- 함수 경계 직전에 올 수 있는 바이트 시퀀스 (code 종료 마커) -->
    <prepatterns>
      <data>0xc0 0x03 0x5f 0xd6</data>                      <!-- ret -->
      <data>0xc0 0x03 0x5f 0xd6  0x1f 0x20 0x03 0xd5</data> <!-- ret; nop -->
      <data>0xff 0x0f 0x5f 0xd6</data>                      <!-- retab -->
      <data>........ ........ ........ 000101..</data>      <!-- b <xxx> (tail call) -->
      <data>0x20 0x00 0x20 0xd4</data>                      <!-- brk #1 -->
    </prepatterns>
    <!-- 함수 시작 지점에서 보일 수 있는 프롤로그 패턴 -->
    <postpatterns>
      <data>0xfd 0x7b 0xbf 0xa9</data>                      <!-- stp x29, x30, [sp, #-0x10]! -->
      <data>0xfe .0001111 0x1. 0xf8</data>                  <!-- stp x30, [sp, #-0x..0]! -->
      <data>111..... .1....11 10...... 0xa9</data>          <!-- stp x, x, [sp, -0x.0]! -->
      <data>0xff ..000011 000..... 0xd1</data>              <!-- sub sp, sp, #... -->
      <data>0x7f 0x23 0x03 0xd5</data>                      <!-- pacibsp -->
      <codeboundary/>
      <possiblefuncstart/>
    </postpatterns>
  </patternpairs>

  <pattern>
    <data>111..... .1....11 10...... 0xa9</data>
    <possiblefuncstart after="defined" validcode="3" contiguous="true"/>
  </pattern>

  <pattern> <!-- solid function start (prologue pair) -->
    <data>0xfd 0x7b 0xbf 0xa9 0xfd 0x03 0x00 0x91</data> <!-- stp + mov x29,sp -->
    <codeboundary/>
    <possiblefuncstart/>
  </pattern>

  <pattern> <!-- AArch64 Thunk (PLT-like) -->
    <data>
      ...10000 ........ ........ 1..10000  <!-- adrp x16, #... -->
      00010001 ........ 01...... 0xf9     <!-- ldr  x17, xxxx -->
      0x10 ......10 00...... 0x91         <!-- add  x16, x16 -->
      0x20 0x02 0x1f 0xd6                 <!-- br   x17 -->
    </data>
    <codeboundary/>
    <funcstart validcode="function" thunk="true"/>
  </pattern>
</patternlist>
```

**DSL 특징**:
- **비트-레벨 와일드카드**: `.` = 비트 와일드카드 (한 자릿수 = 한 비트). `0xfd` = 8 비트 고정.
- **prepatterns**: 함수 경계 직전에 "허용" 되는 바이트 (ret/nop/tail-call). `<patternpairs>` 는 pre ↔ post 매칭 시 pre 가 먼저 나타나야 post 가 함수 시작으로 확정.
- **postpatterns**: 프롤로그 자체.
- **possiblefuncstart / funcstart**: 강도 구분. `funcstart` = 최종 확정, `possiblefuncstart` = 후보 (추가 검증 필요).
- **codeboundary**: 이 지점은 확실한 "코드" 임을 선언.
- **after="defined"**: 바로 앞 바이트가 이미 다른 분석 단계에서 코드/데이터로 정의되어야 한다.
- **validcode**: 숫자(1-3) 또는 `function` — 뒤따르는 N 개 명령어가 유효하게 디스어셈블되어야 한다는 요구.
- **contiguous**: 앞 패턴과 본 패턴 사이에 갭이 없어야 한다.
- **thunk="true"**: 매칭 시 thunk 플래그 부여 → CreateThunkFunctionCmd 로 위임.

**검색 메커니즘**: `BulkPatternSearcher` 는 모든 활성 패턴을 AhoCorasick-유사 결정 트리로 합쳐 메모리 블록 전체를 단일 패스로 훑는다. `ProgramDecisionTree` 가 처리.

### 3.3 Signature databases — FID / FLIRT / BSim

#### FID (Function ID) — Ghidra 고유

[출처: `Ghidra/Features/FunctionID/src/main/java/ghidra/feature/fid/service/FidService.java`]

```java
public static final byte SHORT_HASH_CODE_UNIT_LENGTH = 4;
public static final byte MEDIUM_HASH_CODE_UNIT_LENGTH = 24;
public static final float SCORE_THRESHOLD = 14.6f;
public static final float MULTINAME_SCORE_THRESHOLD = 30;

private FunctionExtentGenerator generator;    // FunctionBodyFunctionExtentGenerator
private MessageDigestFactory digestFactory;  // FNV1a64MessageDigestFactory
```

**3 중 해시**:
- **Short hash (4 code units)** — 함수 시작 4 개 명령어. 빠른 pre-filter.
- **Medium hash (24 code units)** — 함수 body 의 24 개 명령어 (FunctionBodyFunctionExtentGenerator 가 flow 추적). 정밀.
- **Full hash** — 함수 전체.

**정규화**: `InstructionSkipper` (프로세서별 구현) 가 position-dependent 필드(immediate, 상대 주소, relocation 목표)를 건너뛴다. ARM/x86/MIPS/PPC 각각 고유 skipper.

**매칭 알고리즘**: FidProgramSeeker 가 program 내 모든 함수의 3 중 해시를 계산 → FidDB 조회 → `parent name` + `domain name` (prototype) 매치 점수 합산 → `SCORE_THRESHOLD=14.6` 넘으면 label. 14.6 은 bit-level 엔트로피 기준 유의미 수준.

**DB 빌드**: `ghidra_fidb` 툴. 참조 라이브러리 (`.lib`/`.a`) 를 로드 → 각 함수 FID 해시 + name 저장. Ghidra 는 Visual Studio CRT 여러 버전, libstdc++, glibc 등의 사전 빌드 `.fidbf` 를 `Features/FunctionID/data/` 에 배포하지 않음 (라이선스 이슈 — 사용자가 직접 빌드).

#### FLIRT (IDA 개념, Ghidra 에는 없음)

AURA `flirt.c` 는 이름을 차용했으나 IDA Pro 의 `.sig` 파일 포맷과는 **호환되지 않는다**. 자체 포맷.

#### BSim (Binary Similarity)

Ghidra 3 번째 시그니처 계층. Decompiler 출력 (P-Code) 의 structural feature vector → Elasticsearch 계열 DB 에 LSH (Locality Sensitive Hashing) 로 저장 → 유사 함수 검색. FID 는 "정확한 매치", BSim 은 "유사 매치".

**AURA 활용 가능성**: AURA 의 HIR (decompiler/hir_builder.c) 가 이미 있으므로 BSim-유사 구조적 유사도는 구현 난이도가 낮다. 현재 구현 제로.

### 3.4 Pattern matching 보조 Analyzer

- **FunctionStartPreFuncAnalyzer**: `CODE_ANALYSIS.before()` 에 실행 — 함수 생성 전 "prepatterns only" 매칭.
- **FunctionStartFuncAnalyzer**: FUNCTION_ANALYSIS 이후 실행 — 함수 body 확장 이후 다시 매칭.
- **FunctionStartPostAnalyzer**: DATA_ANALYSIS 이후 — 데이터 분석이 끝난 뒤 code-vs-data 확정 영역에서 잔여 탐색.
- **FunctionStartDataPostAnalyzer**: 데이터 블록 내부에서 역으로 code 발견 시 함수화.

→ Ghidra 는 **4 라운드 반복 매칭** 으로 각 분석 단계에서 새로 밝혀진 정보를 반영. AURA 는 단일 패스.

### 3.5 Flow analysis

- **FollowFlow** (`ghidra.program.model.block.FollowFlow`): CreateFunctionCmd 에서 body 확장 시 사용. fall-through, conditional branch, indirect branch 를 추적.
- **PseudoDisassembler**: 실제 program disassembly 를 수정하지 않고 "시험 디스어셈블" — 패턴 후보 검증용. `Use PseudoDisassembler` 옵션 (default ON).
- **ConstantPropagationAnalyzer**: register 상수 추적 → indirect call target 해결 (IAT, vtable, GOT).
- **NoReturnFunctionAnalyzer** (우선순위 pre-0): `exit`, `abort`, `__stack_chk_fail` 등의 심볼을 noreturn 으로 마킹 → 뒤 바이트를 함수 끝으로 처리. **매우 일찍 실행** 되는 이유는 "noreturn 을 놓치면 함수 경계가 계속 fall-through 로 잘못 확장" 되기 때문.
- **ContextBuilder** (`RegisterContextBuilder`): ARM Thumb/ARM 모드 전환, x86 16/32/64 비트 segment 상황을 register value 로 설정 → disassembler 에 힌트.

---

## 4. AURA 현재 구현과의 비교표

| # | Ghidra 기법 | AURA 구현 상태 | 관련 파일 | Gap |
|---|---|---|---|---|
| 1 | Entry point: ELF e_entry | ✅ 동등 | `elf_parser.c` | 0 |
| 2 | Entry point: .init_array/.fini_array | ✅ G2 동등 (2026-04 enabled) | `func_detect_datascan.c` | 0 |
| 3 | Entry point: PE AddressOfEntryPoint | ✅ 동등 | `pe_parser.c` | 0 |
| 4 | Entry point: Mach-O LC_FUNCTION_STARTS | ⚠️ 부분 | `macho_parser.c` | LC_FUNCTION_STARTS 직접 파싱 미구현 (AURA 는 Mach-O 지원 비주요) |
| 5 | Entry point: DWARF subprogram | ⚠️ 부분 | `dwarf_types.c` (타입 위주) | 함수 경계 entry 소비 없음 — `fi->symbols` 경유만 |
| 6 | Entry point: external symbol table | ✅ 동등 | Phase D 심볼 | 0 |
| 7 | Prologue: x86 push rbp / mov rbp rsp | ✅ 동등 | `func_detect.c:131-146` | 0 |
| 8 | Prologue: AArch64 stp x29,x30 / sub sp | ✅ 동등 | `func_detect.c:161-181` | 0 |
| 9 | Prologue: ARM32 push{…lr} | ✅ 동등 | `func_detect.c:188-204` | 0 |
| 10 | Prologue: **pre-pattern 검증** (`after="defined"`) | ❌ **미구현** | — | **FP 주요 원인** |
| 11 | Prologue: PLT thunk (`adrp+ldr+br x17`) | ✅ 동등 (AArch64 전용) | `func_detect_plt.c` | x86-64 PLT / PE IAT stub 미구현 |
| 12 | Pattern: XML DSL runtime 로드 | ❌ **미구현** | — | 새 compiler/ABI 지원 = 코드 변경 |
| 13 | Pattern: 비트-레벨 와일드카드 | ❌ 미구현 | — | Capstone mnemonic string 기반 매칭만 |
| 14 | Pattern: Rust / Go 특화 | ❌ 미구현 | — | Ghidra 는 별도 extension |
| 15 | Call target (direct call) | ✅ 동등 | `func_detect.c` Phase B | 0 |
| 16 | Call target (xref) | ✅ 동등 | `func_detect.c` Phase C + `xref.c` | 0 |
| 17 | Call target (indirect via constprop) | ⚠️ 부분 | `const_prop.c` (HIR 단계만) | func_detect 입력으로 환류 없음 |
| 18 | FDE (.eh_frame) | ✅ G1 — **AURA 의 주력** | `func_detect_ehframe.c` | 0 (Ghidra 에 없음 — ELF 고유) |
| 19 | FID: short hash (4 code units) | ⚠️ 부분 | `func_id.c` (64 bytes, 단일 tier) | 두 번째 tier 부재 |
| 20 | FID: medium hash (24 code units, body) | ❌ 미구현 | — | Ghidra 의 매칭 정밀도 핵심 |
| 21 | FID: InstructionSkipper (정규화) | ⚠️ 부분 | `func_id.c` (mask immediate bytes) | Ghidra 는 per-processor 클래스, AURA 는 heuristic byte mask |
| 22 | FLIRT (IDA 포맷) | ❌ 호환 없음 | `flirt.c` (자체 포맷) | — |
| 23 | BSim (structural similarity) | ❌ 미구현 | — | HIR 이 이미 있어 구현 난이도 낮음 |
| 24 | NoReturn analyzer | ⚠️ 부분 | `noreturn_detect.c` | Ghidra 의 "알려진 이름 DB" 만큼 풍부하지 않음 (exit/abort 정도) |
| 25 | PseudoDisassembler (trial disasm) | ❌ 미구현 | — | Capstone 은 partial-decode 가능하나 validation pass 부재 |
| 26 | Switch table recovery | ⚠️ 부분 | `switch_recovery.c` | Ghidra `ARM_switch_patterns.xml` 수준 pattern DB 없음 |
| 27 | ContextBuilder (Thumb/CPSR) | ❌ 미구현 | — | AArch64 고정, ARM Thumb mode 자동 전환 없음 |
| 28 | 4 라운드 반복 매칭 (pre/func/post/data-post) | ❌ 미구현 | `pipeline.c` 단일 패스 | 신규 정보 환류 없음 |

**정량 요약**:
- ✅ 동등 또는 강함: **13 항목** (프롤로그·call·xref·.eh_frame 등 기본 영역)
- ⚠️ 부분: **7 항목** (FID 단일 tier, noreturn DB, dwarf subprogram 등)
- ❌ 미구현: **8 항목** (XML DSL, pre-pattern, BSim, PseudoDisassembler 등)

---

## 5. 개선 로드맵 (AURA Phase 기반)

### 5.1 단기 (1-3 세션, v2.3.0 Phase 2-F ~ v2.4.0)

| # | 제안 | 예상 Δ | 난이도 | 의존성 |
|---|------|-------|--------|--------|
| S-1 | **Pre-pattern 검증 gate** — 모든 `CAND_SRC_PROLOGUE` 후보 X 에 대해 바로 앞 바이트 4-8 개가 `ret` / `ret+nop` / `nop` / `brk` / 미정의 영역인지 확인. 아니면 confidence -30. | **Precision +3~5%p** (FP 의 post-ret 노이즈 차단) | LOW | `func_detect.c` 내부 추가 약 60 LOC |
| S-2 | **Prologue pair boost** — `stp x29,x30 + mov x29,sp` (AArch64), `push rbp + mov rbp,rsp + sub rsp` (x86_64) 등 **연속 2-3 명령어 매치** 시 confidence 를 100 → 150 으로 상향 → min_confidence=100 threshold 시 생존 | Recall 유지 + Precision +1~2%p | LOW | 기존 is_* 함수 재사용 |
| S-3 | **Ghidra x86-64gcc 패턴 static 이식** — `x86-64gcc_patterns.xml` 의 prologue/thunk 바이트 시퀀스를 C 상수 배열로 복사 → `is_x86_64_thunk()` 등 신규 함수 | Recall +1~2%p | LOW | `func_detect.c` 신규 헬퍼 |
| S-4 | **NoReturn DB 확장** — glibc (`__assert_fail`, `__stack_chk_fail`, `longjmp`, `pthread_exit`), libstdc++ (`__cxa_throw`, `__cxa_rethrow`, `_Unwind_Resume`), Windows CRT (`_invalid_parameter_noinfo_noreturn`) 등 50+ 심볼명을 `noreturn_detect.c` 내부 리스트에 추가. 심볼 발견 시 CFG edge 제거 → 뒤 바이트를 별도 함수로 취급. | Recall +1%p (놓친 인접 함수 복구), Precision +0.5%p | LOW | `noreturn_detect.c` |
| S-5 | **PLT 확장: x86-64 PLT stub + PE .idata IAT stub** | Recall on Windows PE +5%p | MED | `func_detect_plt.c` 다중 arch 분기 |
| S-6 | **Switch-table 경계 보정** — `switch_recovery.c` 결과를 `func_detect` 로 환류. switch jump table 내부 주소가 새 함수 시작으로 오검출되는 것 방지 | Precision +2%p | MED | `switch_recovery.c` ↔ `func_detect.c` 순환 의존 해결 필요 |

### 5.2 중기 (3-6 세션, v2.4.x ~ v2.5.0)

| # | 제안 | 예상 Δ | 난이도 | 의존성 |
|---|------|-------|--------|--------|
| M-1 | **XML Pattern DSL 로더** — Ghidra `*.xml` 패턴 포맷(또는 단순화된 AURA subset) 을 `third_party/ghidra_patterns/` 에서 런타임 로드. 비트-와일드카드 매칭 엔진 필요 (8 비트 mask + value 테이블). | Recall +2~3%p / 확장성 | MED | `src/symbolic/pattern_loader.c` 신규. `libxml2` 또는 `cJSON` 대체 포맷 (AURA 는 `third_party/sqlite` 이미 내장) |
| M-2 | **Ghidra 패턴 DB 이식** — x86-64gcc, x86-64win, AARCH64_LE, ARM_LE 패턴 파일 자체를 repo 에 포함 (Apache 2.0 라이선스, AURA 와 호환). M-1 로더 활용. | Recall +3~5%p | MED | M-1 선행 |
| M-3 | **Medium-hash FID 확장** — `func_id.c` 에 24-code-unit body hash 추가. `FunctionBodyExtentGenerator` 등가물 (flow 추적) 구현. | 명명 정확도 +10%p (libc/CRT 인식) | MED | `func_id.c` + disasm flow walker |
| M-4 | **Per-processor InstructionSkipper** — x86: RIP-relative disp32 mask, AArch64: adrp/adr immediate mask, ARM: pc-relative ldr mask. 현재 byte-level mask 는 너무 거칠다. | FID 매칭 안정성 +20% (동일 함수 cross-binary 매치) | MED | M-3 선행 |
| M-5 | **PseudoDisassembler 등가 validation** — 후보 X 에서 8~16 개 명령어 trial-decode → ret/jmp/직접 call 도달 확인. 도달 불가 또는 invalid opcode 면 후보 기각. | Precision +2~3%p | MED | `disasm.c` 의 bounded-decode 경로 노출 |
| M-6 | **DWARF subprogram direct consumer** — `dwarf_types.c` 가 타입만 읽고 있으나 `.debug_info` 의 `DW_TAG_subprogram` 은 함수 경계 + 이름 + prototype 을 제공. unstripped 바이너리에서 ground truth 급 signal. | Recall +5%p (unstripped 바이너리) | MED | `dwarf_types.c` 확장 |
| M-7 | **4 라운드 반복 탐지 scheduler** — `func_detect` 를 CODE / FUNCTION / DATA 3 단계 후에 호출하는 얕은 scheduler. 각 라운드는 새 정보 (data block, xref) 만 추가 처리. | Recall +1~2%p | HIGH | `pipeline.c` 구조 변경 |

### 5.3 장기 (6+ 세션, v3.x)

| # | 제안 | 예상 Δ | 난이도 | 의존성 |
|---|------|-------|--------|--------|
| L-1 | **FID DB 빌드 툴** — `aura-fidb-build` CLI 로 `.a`/`.lib` → `.aura_fdb` 생성. Ghidra 는 이 단계에서 ghidra_fidb 외부 툴 제공. | 명명 품질 돌파구 | HIGH | M-3/M-4 선행 |
| L-2 | **BSim-유사 HIR structural similarity** — HIR 함수의 AST 를 feature vector (node type histogram, loop depth, call fan-out) 로 변환 → LSH-like 인덱스. Ghidra BSim 대응. | 유사 함수 식별 (fuzzing, malware) | HIGH | HIR 안정화 선행 |
| L-3 | **ML function boundary (obfuscation 대응)** — byte-level CNN/BiLSTM 로 function-start 확률 예측. ONNX 런타임 정적 링크. **C/C++ 제약 확인 필요** (PRD §5). | obfuscated 바이너리 recall +10~20%p | HIGH | 규칙상 인터프리터 언어 금지 — ONNX 정적 링크 C API 는 OK, 모델 학습은 외부 |
| L-4 | **Sleigh 스타일 선언적 DSL** — AURA 도 프로세서 정의 DSL 도입 → Capstone 의존 완화. 대공사. | 장기 유지보수성 | VERY HIGH | 전면 재설계 |
| L-5 | **Go / Rust / Swift 전용 metadata analyzer** — Go binary 의 pclntab, Rust `__rust_*` 런타임 심볼, Swift `__swift5_*` 메타데이터 | 특정 언어 +20%p recall | HIGH | 각 언어별 별도 모듈 |
| L-6 | **MIPS / PPC / RISC-V func_detect production-grade 승격** | 아키텍처 커버리지 | MED (프롤로그 패턴만) | 각 arch 별 1-2 세션 |

---

## 6. 우선순위 top 5 상세 스펙 (구현 draft)

### 6.1 S-1: Pre-pattern 검증 gate

**대상 파일**: `src/symbolic/func_detect.c`

**데이터 구조 추가**:
```c
/* func_detect.c 내부 */
static int pre_pattern_is_code_end(const DisasmResult *prev)
{
    if (!prev) return 1; /* 섹션 시작 = OK */
    const char *mn = prev->mnemonic;
    /* x86: ret / retf / iret / ud2 / jmp (직접) / int3 / nop (pad) */
    /* AArch64: ret / retab / b (tail) / brk / nop */
    /* ARM32: bx lr / pop {pc} / b (tail) / nop */
    return (strcmp(mn, "ret") == 0 || strcmp(mn, "retab") == 0 ||
            strcmp(mn, "ud2") == 0 || strcmp(mn, "int3") == 0 ||
            strcmp(mn, "brk") == 0 || strcmp(mn, "nop") == 0 ||
            (strcmp(mn, "jmp") == 0 && /* direct jmp target 이 far */ 1) ||
            (strcmp(mn, "b") == 0 && /* tail call 판정 */ 1) ||
            (strcmp(mn, "bx") == 0 && strstr(prev->operand, "lr")) ||
            (strcmp(mn, "pop") == 0 && strstr(prev->operand, "pc")));
}
```

**적용 지점**: `collect_candidates()` Phase A 프롤로그 매칭 시 `cur` 주소의 이전 명령어(`i > 0 ? &insns[i-1] : NULL`) 에 대해 `pre_pattern_is_code_end()` 호출. `false` 면 confidence 에서 -30 (또는 candidateset_add 생략). `.eh_frame` / symbol 로 이미 강한 confidence 가 붙은 후보는 영향 없음.

**테스트**: `tests/symbolic/test_func_detect.c` 에 기존 10 개 TC 에 더해 TC-11 "prologue 가 noreturn call 뒤에 있으면 허용", TC-12 "prologue 가 random code 중간에 있으면 거부" 추가. 실 바이너리 3 개 (cat/ls/aura-self) precision Δ 측정.

**예상 LOC**: ~60 라인 + 테스트 40 라인.

### 6.2 S-4: NoReturn DB 확장

**대상 파일**: `src/core/noreturn_detect.c`

**데이터**: 정적 배열로 50+ 심볼명.
```c
static const char *kKnownNoReturn[] = {
    /* libc (GNU + musl) */
    "exit", "_exit", "abort", "__assert_fail", "__stack_chk_fail",
    "longjmp", "_longjmp", "siglongjmp", "pthread_exit", "quick_exit",
    /* libstdc++ */
    "__cxa_throw", "__cxa_rethrow", "_Unwind_Resume",
    "__cxa_bad_typeid", "__cxa_bad_cast",
    "_ZSt17__throw_bad_allocv", "_ZSt20__throw_length_errorPKc",
    /* Rust */
    "_ZN4core9panicking5panic17h",  /* 접두 매칭 */
    "rust_panic", "__rust_start_panic",
    /* Go */
    "runtime.goexit", "runtime.throw", "runtime.gopanic",
    /* Windows CRT */
    "_invalid_parameter_noinfo_noreturn", "_CxxThrowException",
    "ExitProcess", "TerminateProcess", "RaiseException",
    NULL
};
```

**환류**: 현재 `noreturn_detect.c` 결과 → HIR 단계에서만 사용. `pipeline.c` 에 훅 추가해 `func_detect` 이후 noreturn call 뒤 fall-through 지점을 **함수 끝으로 단언** + 그 다음 aligned 주소를 `CAND_CONF_NORETURN_BOUNDARY=90` 후보로 등록.

### 6.3 M-1: XML Pattern DSL 로더

**신규 파일**: `src/symbolic/pattern_loader.c` + `include/pattern.h`

**포맷 결정**:
- Option A: Ghidra XML 원형 그대로. `libxml2` 정적 링크 추가 비용.
- Option B: JSON 변환판 (cJSON 기존 사용). Ghidra 패턴을 one-time 변환 스크립트(build-time) 로 JSON 화.
- **권장**: Option B — cJSON 이미 정적 링크, build-time 변환 스크립트는 C 로 작성 (인터프리터 금지 준수).

**매칭 엔진**:
```c
typedef struct {
    uint8_t value[32];   /* 고정 비트 값 */
    uint8_t mask[32];    /* 1=고정, 0=와일드카드 */
    uint8_t  length;     /* 바이트 수 */
    uint16_t flags;      /* PAT_FUNCSTART | PAT_THUNK | PAT_CODEBOUNDARY */
    uint8_t  validcode;  /* 0=없음, 1-3=검증 깊이, 4=function */
} BytePattern;

typedef struct {
    BytePattern *prepatterns;
    size_t       pre_count;
    BytePattern *postpatterns;
    size_t       post_count;
    char        *constraint;  /* "after=defined", "contiguous" 등 */
} PatternPair;
```

**매칭 메커니즘**: per-byte `(buf[k] & mask[k]) == value[k]`. 32-byte 헤드는 SSE2/NEON 로 vectorize 가능.

**DecisionTree**: 첫 바이트의 value/mask 로 dispatch 테이블 구성 → O(1) 선별.

### 6.4 M-3: Medium-hash FID 확장

**대상 파일**: `src/symbolic/func_id.c`, `src/symbolic/func_id.h`

**변경**:
```c
typedef struct {
    uint64_t short_hash;    /* 기존 - 함수 시작 4 명령어 */
    uint64_t medium_hash;   /* 신규 - body 24 명령어 (flow 추적) */
    uint64_t full_hash;     /* 신규 - 함수 전체 */
    uint16_t code_units;
} FuncIdHashes;

FuncIdHashes func_id_hash(const FuncEntry *fe, const DisasmResult *insns, ...);
```

**Body extent 생성**: CFG 로 BFS → leaf/ret 까지 24 명령어 도달. 이미 있는 `cfg.c` 재사용 가능.

**매칭**: DB lookup 시 short-hash 로 shortlist → medium-hash 로 rank → score 누적 threshold `SCORE_THRESHOLD=14.6` 상응 (AURA 에서는 명령어 단위 가중치로 재산출).

### 6.5 M-5: PseudoDisassembler 등가 validation

**접근**: Capstone 은 이미 partial-decode 가능. `disasm.c` 에 `disasm_bounded(start, max_insns, out)` API 추가 → `func_detect` 가 후보 검증 시 호출. 실패 (`CS_ERR_`) 또는 첫 8 명령어 내 ret/jmp/call 도달 실패 시 confidence -20.

**주의**: 비용이 크다. 후보당 8 명령어 × 수만 개 후보 → ms 단위. 현재 AURA 성능 예산 확인 필요.

---

## 7. 인용 / 출처

### 7.1 Ghidra 소스 코드

- `Ghidra/Features/BytePatterns/src/main/java/ghidra/app/analyzers/FunctionStartAnalyzer.java` — 메인 함수 탐지기 (검증 완료)
- `Ghidra/Features/BytePatterns/src/main/java/ghidra/app/analyzers/FunctionStart{Pre,Func,Post,DataPost}Analyzer.java` — 4 라운드 변종
- `Ghidra/Features/FunctionID/src/main/java/ghidra/feature/fid/service/FidService.java` — FID 해시/매칭 상수 (SHORT=4, MEDIUM=24, SCORE_THRESHOLD=14.6 검증)
- `Ghidra/Features/Base/src/main/java/ghidra/app/plugin/core/analysis/NoReturnFunctionAnalyzer.java` — noreturn 우선순위 (FORMAT_ANALYSIS.before().before().before())
- `Ghidra/Features/Base/src/main/java/ghidra/app/plugin/core/analysis/MachoFunctionStartsAnalyzer.java` — Mach-O LC_FUNCTION_STARTS
- `Ghidra/Features/Base/src/main/java/ghidra/app/plugin/core/function/ExternalEntryFunctionAnalyzer.java` — ELF entry point
- `Ghidra/Features/Base/src/main/java/ghidra/app/cmd/function/CreateFunctionCmd.java` — 함수 생성 커맨드
- `Ghidra/Features/Decompiler/src/main/java/ghidra/app/plugin/core/analysis/DecompilerFunctionAnalyzer.java` — 파라미터 복원 포스트-패스

### 7.2 패턴 파일 (샘플)

- `Ghidra/Processors/AARCH64/data/patterns/AARCH64_LE_patterns.xml` — 본 문서 §3.2 예시 원본
- `Ghidra/Processors/x86/data/patterns/x86-64gcc_patterns.xml`
- `Ghidra/Processors/x86/data/patterns/x86-64win_patterns.xml`
- `Ghidra/Processors/ARM/data/patterns/ARM_switch_patterns.xml`

### 7.3 공식 API 문서

- `ghidra.re/ghidra_docs/api/ghidra/app/services/AnalysisPriority.html` — 분석 우선순위 공식 순서 확인

### 7.4 AURA 내부

- `src/symbolic/func_detect.c` — CandidateSet, G1~G5, Phase A-D
- `src/symbolic/func_detect_ehframe.c` — G1 (.eh_frame)
- `src/symbolic/func_detect_datascan.c` — G2 (.init_array)
- `src/symbolic/func_detect_plt.c` — AArch64 PLT stub
- `src/symbolic/func_id.c` / `.h` — 현재 FID 구현 (FNV-1a 단일 tier)
- `src/core/flirt.c` — FLIRT-유사 패턴 매칭 (자체 포맷)
- `src/core/noreturn_detect.c` — noreturn 판정
- `Tasks_archive/v1_1.md` V1.1-3 — G1~G5 재활성화 실험 결과

---

## 8. TODO / Open questions

1. **FID 라이선스 준수** — Ghidra 의 `x86-64gcc_patterns.xml` 은 Apache 2.0. AURA (Apache 2.0) 로 직접 이식 가능. SRC 에 `LICENSES/GHIDRA-Apache2.0` 명시 + NOTICE 파일 추가 필요.
2. **BulkPatternSearcher 정확한 트리 구조** — 본 연구에서는 ProgramDecisionTree 의 상위 레벨만 확인. 실제 매칭 복잡도 O(N + M) 증명은 추가 세션에서 `Patterns.java` + `BulkPatternSearcher.java` 정독 필요.
3. **BSim 의 HIR 적용 feasibility** — AURA HIR 구조(`hir_builder.c`, `hir.h`)가 BSim 의 "feature extraction" 에 충분한지 검증 미완. AST diff 오버레이 (`tools/ast_diff/`, Session #6 Phase G) 가 전신이 될 수 있음.
4. **Go pclntab / Swift metadata 분석기 우선순위** — 단기 로드맵에 포함해야 하는지, 아니면 v3.x 까지 미뤄도 되는지 (현재 벤치 corpus 에 해당 바이너리 부재).
5. **Ghidra 의 DecompilerParameterIdCmd 는 P-Code 의존** — AURA 는 HIR 이므로 직접 이식 불가. `param_id.c` 가 이미 독자 경로로 구현 — 격차 측정은 별도 연구 필요.
6. **obfuscated 바이너리 측정** — 현재 벤치 corpus (cat/ls/aura-self) 는 compiler-direct 바이너리. 실 분석 가치는 obfuscated target 에서 나오므로 upx-packed / mpress / vmprotect 샘플 테스트 필요.
7. **F1 0.866 → 0.90 도달 경로 수치 검증** — 본 문서의 예상 Δ 는 Ghidra 비교 + AURA 이전 실험 기반 휴리스틱. 각 제안 구현 후 실제 측정 필수.

---

**문서 종료**. 다음 세션 착수 추천 순서: **S-1 (pre-pattern gate) → S-4 (noreturn DB) → S-2 (prologue pair boost) → M-3 (medium-hash FID) → M-5 (PseudoDisassembler 등가)**. 단기 S 시리즈만 완주해도 F1 0.866 → ~0.89 도달 가능 추정.
