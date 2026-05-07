# Ghidra 디스어셈블러 파이프라인 재분석

**Session #9, 2026-04-20** — Phase 2-E 병렬 연구 (ghidra-analyst Task #26 과 쌍, Task #27)

> Scope: 디스어셈블 레이어 (machine bytes → decoded instructions → PCode → analyzer-ready CFG). 함수 탐지는 Task #26 sibling, lifting(disasm↔decompiler 브리지)은 Task #28 sibling. 본 문서는 **decoding + target-resolution + switch recovery** 에 집중한다.

---

## 1. Executive Summary

AURA 의 disasm 레이어는 **Capstone 5.x 핸드롤 디코더** 위에 얇은 C 래퍼(`src/disasm/capstone_wrapper.c`, 276 LOC) 와 자체 **recursive descent**(`src/core/recursive_disasm.c`, 654 LOC) + **indirect resolver**(`src/disasm/indirect_resolver.c`, 379 LOC) + **pattern-based switch recovery**(`src/decompiler/switch_recovery.c`, 294 LOC) 로 구성된다. 반면 Ghidra 는 **SLEIGH** (processor specification language) → **PCode** (retargetable IR) 로 **decoding 자체를 데이터-구동**하고, disassembler / analyzer / decompiler 전 계층이 PCode 위에서 동작한다.

구조적 격차 **top 3**:

1. **decoding 모델**: Capstone = per-arch hand-written C, Ghidra = SLEIGH `.slaspec` pattern DSL. 새 아키텍처 추가 비용 N배 (Ghidra 50+ vs AURA 4). 정확도는 양방향 trade-off (Capstone 은 production, SLEIGH 는 자동 semantic 생성).
2. **target resolution 깊이**: AURA 는 **mnemonic/operand 문자열 파싱** 기반 (`strcmp`/`strtoull`), Ghidra 는 **PCode emulation + flow analysis** 기반. AURA 의 `indirect_resolver.c` 는 rip-relative + vtable + jump-table 3 패턴만 cover — Ghidra 의 `JumpBasic`/`JumpBasicOverride`/`JumpAssisted` 4-class 계층 대비 표현력 빈약.
3. **IR 추상화 level**: AURA IR (`include/decompiler.h` `IR_OP_*`) 는 ~25 opcode — high-level (ADD/SUB/CMP/BRANCH/PHI/CALL). Ghidra PCode 는 ~80 `CPUI_*` opcode — **low-level semantic 완전 표현** (flag effects, MULTIEQUAL, INDIRECT, PIECE/SUBPIECE). AURA 는 이 저수준 표현을 못 하므로 condition code / side effect / aliasing 을 architecture 별로 핸들링해야 한다 (RC-2 condition-code lowering 이 바로 이 gap).

**AURA 가 최대 레버를 얻을 단일 변경**은 Capstone → SLEIGH 교체가 아니라, **PCode-like low-IR 도입** (Capstone 출력 → low-IR → current AURA IR). 본 문서 §7.2 참조.

---

## 2. Ghidra 디스어셈블러 전체 파이프라인

```
┌─────────────────┐
│ Loader (ELF/PE) │  binary format parse, symbol/section layout
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ SLEIGH Language │  .slaspec (endian/space/token/constructor/pcode)
│ Compiler        │  → compiled .sla (pattern tables)
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Disassembler    │  recursive descent: known entries → follow flow
│ (bytes → PCode) │  bit-pattern match in .sla → constructor → PCode emit
└────────┬────────┘
         │ low PCode stream per function
         ▼
┌─────────────────┐
│ Auto-Analyzer   │  symbol recovery, xref, type hints, calling conv,
│ (pipeline of N) │  function-start detection, JumpTable analyzer
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│ Decompiler      │  SSA (MULTIEQUAL insertion), data-flow, type prop,
│ (PCode → C)     │  structuring (BlockGraph), PrintC emit
└─────────────────┘
```

**각 단계 책임 비교:**

| 단계 | Ghidra 코드 위치 | AURA 대응 | AURA 코드 위치 |
|------|-----------------|----------|---------------|
| Loader | `Ghidra/Features/Base/.../loader/` | ELF/PE/Mach-O 커스텀 파서 | `src/parser/` |
| SLEIGH compile | `Ghidra/Features/SleighDevTools/` | — (Capstone 내장 decoders) | `third_party/capstone/` |
| Disassembler | `Ghidra/Features/Base/.../plugin/core/disassembler/` + decomp `cpp/` | `capstone_wrapper.c` + `recursive_disasm.c` | `src/disasm/`, `src/core/` |
| Analyzer | `Ghidra/Features/Base/.../plugin/core/analysis/` | `func_detect.c`, `xref.c`, `entry_points.c` | `src/symbolic/`, `src/disasm/` |
| Decompiler | `Ghidra/Features/Decompiler/src/decompile/cpp/` | `decompiler/`, `hir.c`, `structural_analysis.c` | `src/decompiler/` |

---

## 3. SLEIGH 심층

### 3.1 `.slaspec` 파일 구조

단일 processor 당 하나의 `.slaspec` 이 아래 섹션을 순서대로 포함한다:

1. **Basic definitions** — endianness (`big`/`little`), default alignment, address spaces (`ram`, `register`, `unique`)
2. **Tokens and fields** — 명령어 bit layout, 서브필드 (opcode, reg id, imm)
3. **Registers** — register varnode 선언 (`define register offset=0 size=8 [ x0 x1 ... ]`)
4. **Macros** — 재사용 가능한 semantic 파편
5. **Constructors** — pattern + display + semantic 의 3-part block. 대부분의 `.slaspec` 라인은 constructor.
6. **P-code semantics** — constructor 당 PCode 출력 블록

하나의 AArch64 `.slaspec` 는 **수만 라인**. SLEIGH 는 `pspec` (processor spec, XML), `ldefs` (language defs), 컴파일된 `.sla` 의 3-tier 디렉토리 레이아웃으로 운영된다.

### 3.2 Pattern-based instruction decoding

Constructor 는 bit pattern 섹션으로 식별된다:

```
:add Rd, Rn, Rm    is op=0b001 & Rd & Rn & Rm
    { Rd = Rn + Rm; }
```

- `op=0b001 & Rd & Rn & Rm` 가 **pattern**. Token 필드의 bit 값 제약.
- 여러 constructor 가 한 token 을 공유. **SLEIGH 제약**: 두 constructor 의 pattern set 은 **disjoint 이거나 한쪽이 다른 쪽의 subset** 이어야 한다 (subset 일 경우 더 specific 한 쪽이 우선).
- SLEIGH 컴파일러는 tree-based 디코딩 테이블로 변환 → runtime matching O(log N).
- 가변 길이 (x86) 는 multi-token 확장으로 해결.

**Capstone 대비**: Capstone 은 per-arch `arm64_insn.inc` / `X86DisassemblerDecoder.c` 같은 hand-written C. 디코딩 속도는 Capstone 가 빠르다 (LLVM TableGen 기반). 반면 **새 ISA extension 추가** (ARM v9 SVE2, AArch64 MTE, AMX 등) 는 SLEIGH 가 데이터만 추가하면 됨 → 커뮤니티 기여 속도에서 Ghidra 우위.

### 3.3 PCode 생성 (semantic section)

Constructor 의 `{ ... }` 블록이 PCode semantics. 위 예제 `Rd = Rn + Rm;` 은 다음 PCode 로 풀린다:

```
tmp:8  = INT_ADD Rn, Rm
Rd     = COPY tmp
```

- **모든 side effect 는 명시적**. Flag 도 별도 varnode 에 COPY (`NF`, `ZF`, `CF`, `VF`).
- **"No indirect effects" rule** — 모든 변경은 출력 varnode 로 표출.
- 단일 machine 명령은 보통 1~20 PCode op 로 expand. 이로써 decompiler 는 **processor-agnostic** 하게 모든 분석을 수행.

### 3.4 Capstone 대비 장단점

| 관점 | SLEIGH | Capstone |
|------|--------|----------|
| 새 ISA 추가 | `.slaspec` 작성 (수천 라인 DSL) | C decoder 이식 (LLVM TableGen 또는 수작업) |
| Decoding 속도 | pattern tree traversal (Java VM) | hand-tuned C tables |
| Semantic 정밀도 | **자동** (PCode 생성) | — (mnemonic/operand 문자열만) |
| 플래그/사이드이펙트 | **명시적** | 별도 구현 필요 |
| 에코시스템 | 20+ 아키텍처, 커뮤니티 기여 활발 | 20+ 아키텍처, production-grade |
| AArch64 완성도 | SVE/NEON 포함 | 전체 지원 |
| 라이센스 | Apache 2.0 | BSD |

---

## 4. PCode IR vs AURA custom IR

### 4.1 추상화 수준

| 측면 | AURA IR (`IR_OP_*`) | Ghidra PCode (`CPUI_*`) |
|------|---------------------|-------------------------|
| Opcode 수 | ~25 | ~80 |
| 레벨 | high (ADD, SUB, CMP_EQ, CMP_UGT) | low (INT_ADD, INT_SUB, INT_EQUAL, INT_LESS) |
| SSA | PHI (`IR_OP_PHI`) | MULTIEQUAL (동일 개념) |
| 사이드이펙트 | — (per-arch handler 필요) | INDIRECT opcode 로 표현 |
| 바이트-level 연산 | 없음 | PIECE, SUBPIECE, INT_ZEXT, INT_SEXT |
| Flag 모델링 | — (RC-2 lowering 에서 추가 중) | 명시적 NZCV varnode |
| 메모리 모델 | LOAD/STORE | LOAD/STORE with address space id |
| 호출 | CALL | CALL, CALLIND, CALLOTHER |

AURA IR 은 **`IR_OP_UNSUPPORTED`** enum 을 두어 미지원 명령어를 통으로 넘기는데, 이는 bitwise-precise 분석 (condition code 전파, partial register aliasing) 을 구조적으로 불가능하게 한다.

### 4.2 최적화 pass 체인 비교

| Ghidra 패스 | AURA 대응 | 상태 |
|------------|----------|------|
| Heritage (SSA construction) | `decompiler/` SSA | ✅ 구현 |
| Rule-based simplification (RuleCollectTerms, RuleSelectCse) | 현행 peephole 수준 | 부분 |
| SubvariableFlow (varnode split/merge) | — | **없음** |
| Type propagation (sub_metatype ordering) | `type_constraint` (Pre-2) | 초보 |
| BlockGraph structuring | `structural_analysis.c` | ✅ 구현 |
| PrintC | `hir.c` + emit | ✅ 구현 |

### 4.3 Transition 가능성

**PCode-like low-IR 를 Capstone 과 current AURA IR 사이에 삽입**하는 것이 현실적. Capstone detail mode (`CS_OPT_DETAIL=ON`) 를 활용하면 operand breakdown 을 얻을 수 있어 per-opcode → low-IR lowering table 을 C 로 유지보수 가능하다. 단, ISA 당 lowering table = 수백~수천 라인 → **AArch64 + x86_64 두 개만 우선 타깃**.

---

## 5. 디스어셈블러 정확도 기법

### 5.1 Recursive descent + linear sweep fallback

Ghidra 입장: **"We don't generally do linear sweep because it isn't generally good on all processors when you might have data embedded in the code for processor such as ARM."** (NSA maintainer 공식 코멘트). Linear sweep 은 analyzer 로 **opt-in** 제공 — 기본 disable.

**AURA 상태**: `recursive_disasm.c:485` `recdis_run_multi_ex()` 가 recursive descent. Linear sweep 은 `src/symbolic/func_detect.c` 에서 엔트리 후보 수집용으로만 쓰임. Ghidra 와 철학 일치 — 이 부분은 gap 없음.

### 5.2 Mixed-mode (ARM/Thumb, x86 16/32/64)

**Ghidra**: `TMode` register 를 context variable 로 두고 `.slaspec` 의 `globalset` / `instructionLength` 전환으로 per-address mode decoding. BL/BLX 같은 interworking 명령이 TMode 를 자동 플립.

**AURA**: `capstone_wrapper.c:60-68` — `AURA_ARCH_ARM` 은 항상 `CS_MODE_ARM`, `AURA_ARCH_ARM64` 도 고정. **Thumb 디코딩 경로 없음**. `src/symbolic/func_detect.c:478` 의 ARM ELF mapping symbol `$x/$d/$t` 는 boundary detection 에만 쓰임, disasm context 를 전환하지 않는다. → **실질적 gap**.

### 5.3 Data vs code 분류

**Ghidra**: 5-계층 hierarchy (① debug symbols / entry points, ② known function signatures, ③ symbolic emulation, ④ pattern heuristics, ⑤ 마지막으로 speculative). 분기로 **reach 되지 않는 byte 는 절대 disassemble 하지 않는다**.

**AURA**: `entry_points.c:491` 이 여러 후보 소스 (.init_array, DT_INIT, symbol table, ELF header e_entry, function prologue signature) 를 머지하지만, symbolic emulation 단계가 없어 **간접 호출 타겟**은 `indirect_resolver.c` 에서 제한된 패턴만 cover. "walk back from cmp" 식 heuristic 이 대부분.

### 5.4 Switch / jump table recovery

**Ghidra JumpModel 계층** (`decompile/cpp/jumptable.cc`):
- `JumpModelTrivial` — 직접 분기만
- `JumpBasic` — 표준 switch/case (normalized switch variable + guard analysis)
- `JumpBasicOverride` — 사용자 hint override
- `JumpAssisted` — PCode emulation 으로 변수 값 enumerate → 각 table entry 주소 계산

**AURA**:
- `recursive_disasm.c:252` `detect_jump_table()` — cmp+jmp `[base+reg*8]` 정확 패턴만
- `indirect_resolver.c:152` `resolve_jump_table()` — 동일 패턴 사후 스캔
- `switch_recovery.c:105` `follow_chain()` — **if-else-if chain** (IR 레벨) 을 switch 로 승격. Pattern B 언급된 jump-table-as-succ 경로는 placeholder.

**Gap**: 
1. 8-byte entry 만 가정 (AArch64 adrp+add 기반 table 는 4-byte offset → 미지원)
2. guard (`cmp reg, N; ja default`) 가 jmp 직전 5 insn 안에 있어야 인식. Ghidra 는 dataflow 로 임의 거리 추적
3. PCode emulation 이 없어 **복잡한 index 변환** (shift, xor, lookup-in-lookup) 전혀 cover 안됨

### 5.5 Thunk / indirect / indirect-call resolution

**Ghidra**: thunk analyzer 가 별도 pass — PLT, GOT, import stub, language-specific thunks (Go, Rust closure dispatcher) 를 패턴 + symbol 결합으로 탐지. "single jmp-to-external" 은 thunk 로 mark.

**AURA**: `aarch64_plt_thunks.c` (213 LOC) 가 AArch64 PLT 만 cover. x86_64 PLT 는 별도 경로. Go/Rust 고유 thunk 패턴 미구현.

**Indirect call**:
- Ghidra: flow analysis 로 `CALLIND` 의 함수 포인터 origin 을 chain back → 상수/글로벌 table/vtable 로 해결
- AURA `indirect_resolver.c`: rip-relative immediate pointer, vtable pattern (`mov reg,[rdi]; call [reg+N]`), jump table. **register-based vtable** (calling convention 에서 thisptr 이 rcx/rdi 가 아닌 경우) 은 놓침.

---

## 6. AURA 비교표

| Ghidra 기법 | AURA 구현 상태 | Gap 심각도 | AURA 파일 |
|-------------|---------------|----------|-----------|
| SLEIGH pattern decoding | Capstone hand-written | low (정확도 동등) | `third_party/capstone/` |
| PCode low-IR | **미구현** | **critical** | — |
| MULTIEQUAL/PHI SSA | `IR_OP_PHI` | 동등 | `src/decompiler/` |
| Recursive descent | 구현 | 동등 | `recursive_disasm.c:485` |
| Linear sweep opt-in | func_detect 부분 | medium | `func_detect.c` |
| Mixed-mode ARM/Thumb | **없음** | **high** | `capstone_wrapper.c:60` |
| Mixed-mode x86 16/32/64 | arch 고정 | medium | 동상 |
| Data/code 5-tier hierarchy | 엔트리 머지만 | medium | `entry_points.c` |
| JumpModel 4-class | 2 패턴만 (indirect_resolver + switch_recovery) | **high** | `indirect_resolver.c`, `switch_recovery.c` |
| Thunk analyzer (N-language) | AArch64 PLT only | medium | `aarch64_plt_thunks.c` |
| Symbolic emulation | **없음** | **high** | — |
| Type propagation | 초보 (type_constraint) | medium | `src/decompiler/` |
| SubvariableFlow | **없음** | medium | — |
| Flag modeling | RC-2 부분 진행 중 | medium | condition-code lowering |
| Rule-based simplification | peephole 수준 | low | — |
| Architecture 수 | 4 production | 50+ | 정책상 MVP 제한 |

---

## 7. 개선 로드맵

### 7.1 단기 (1-3 세션) — Capstone 위에 추가 기법 layer

**S-1. ARM/Thumb dual-context disassembly** (1 세션)
- `capstone_wrapper.c` 에 `DisasmContext` 당 두 csh (ARM + THUMB) 유지, address → mode map 운영
- ELF mapping symbol `$t` / interworking branch (`bx`, `blx`) 에서 mode flip
- 예상 효과: ARM 바이너리 recall **+5~10%**
- 구현 난이도: **low-medium** (Capstone API 는 준비됨)

**S-2. JumpBasic-lite: dataflow-aware guard detection** (2 세션)
- `indirect_resolver.c` 의 `cmp within 5 insn` 제약을 제거하고 CFG 상 predecessor chain 에서 `cmp reg, N` 를 찾는다
- normalized switch variable 식별 (reg rename 추적)
- 예상 효과: switch recovery precision 유지, recall **+10~15%**
- 구현 난이도: **medium** (새 CFG walker 필요)

**S-3. AArch64 4-byte jump table + adrp/add table base resolution** (1 세션)
- 현재 8-byte entry 고정 → entry size enum (4/8) + adrp+add lowering 패턴 추가
- 예상 효과: AArch64 stripped 바이너리 switch recall **+20%**
- 구현 난이도: **medium**

### 7.2 중기 (3-6 세션) — 핵심 알고리즘 신규 구현

**M-1. Low-IR 도입 (PCode-like)** — 최대 레버
- Capstone detail 출력 → `low_ir` module → current AURA IR 2-stage lowering
- AArch64 + x86_64 lowering table 우선 (~3k LOC 예상)
- 조건부 플래그 (NZCV) 를 first-class varnode 로 모델링
- 이후 condition-code/partial register aliasing 이 processor-agnostic 하게 처리 → decompile 품질 structural jump
- 예상 효과: decomp precision **+5%**, recall **+2~3%**, 향후 새 arch 추가 비용 1/3
- 구현 난이도: **high** (core module 신설)

**M-2. Thunk analyzer 통합 pass**
- PLT/GOT + Go/Rust/Swift compiler-emitted thunk 패턴 DB
- `aarch64_plt_thunks.c` + x86_64 equivalent 를 하나의 `thunk_analyzer.c` 로 통합
- 예상 효과: indirect 호출 타겟 해결률 **+10%**
- 구현 난이도: **medium**

**M-3. Symbolic emulation (mini interpreter)**
- Low-IR 위에서 constant propagation + bounded register state emulation
- switch table index, indirect call target, string reference 추론에 공용 사용
- 예상 효과: JumpAssisted 급 해결 가능
- 구현 난이도: **high**

### 7.3 장기 (6+ 세션) — 구조적 변경

**L-1. SLEIGH 라이트 채택 검토** (조사만, 구현 보류)
- `.slaspec` 의 일부 (pattern table DSL) 만 import 하여 ISA extension 추가 비용 감축
- Capstone 유지 + SLEIGH 는 decoder 보조
- 위험: 유지보수 부담 증가, Java→C 바인딩 고민

**L-2. RISC-V / WebAssembly 지원**
- Capstone 이 두 ISA 모두 지원하므로 disasm 레이어는 배선만
- func_detect / calling_conv / stack_analysis 가 arch 별 분기 필요
- 소요: arch 당 ~2 세션

**L-3. Plugin-style processor module**
- Ghidra 처럼 per-arch code 를 동적 로드. 단 정적 링크 정책 (PRD §4.2) 과 충돌 → 현시점 **보류**.

---

## 8. 핵심 제안 top 5 상세 스펙

### 제안 1. Low-IR (M-1) — 최대 ROI

- **File**: `src/ir_low/` 신설 (`low_ir.h/c`, `lower_aarch64.c`, `lower_x86_64.c`)
- **API**:
  ```c
  typedef struct LowIrOp { LowIrOpcode op; LowIrVarnode srcs[3]; LowIrVarnode dst; uint32_t src_count; } LowIrOp;
  int low_ir_lower_insn(const DisasmResult *insn, AuraArch arch, LowIrOp *out, size_t *out_count, size_t max);
  ```
- **Test**: `tests/ir_low/test_lower_aarch64_add.c` (ADD → INT_ADD + flag NZCV updates), `test_lower_x86_64_lea.c`, `test_lower_condition_codes.c`
- **Integration**: `decompiler.c` 에서 current `ir_build_from_disasm()` 을 2-stage (disasm → low_ir → ir) 로 변경
- **Risk**: 전환 기간 동안 ISA 커버리지 gap 발생 → feature flag `AURA_LOWIR=1`

### 제안 2. JumpBasic-lite (S-2)

- **File**: `src/disasm/jump_model.c` 신설 (기존 `indirect_resolver.c` 의 jump table 부분 이관)
- **API**:
  ```c
  typedef enum { JUMP_TRIVIAL, JUMP_BASIC, JUMP_OVERRIDE } JumpModelKind;
  int jump_model_recover(const CFG *cfg, uint32_t blk_id, JumpTable *out);
  ```
- **Test**: `tests/disasm/test_jump_model_long_guard.c` (guard 20 insn 떨어진 경우), `test_jump_model_register_rename.c`
- **Migration**: `switch_recovery.c` Pattern B 를 신 모듈로 재구현

### 제안 3. ARM/Thumb dual-context (S-1)

- **File**: `src/disasm/capstone_wrapper.c` 확장 (`DisasmContext` 에 `csh thumb_handle` 추가) + `src/disasm/arm_mode_map.c` 신설
- **API**:
  ```c
  int disasm_run_mixed(DisasmContext *, const uint8_t *, size_t, AuraAddr, const ArmModeMap *, DisasmResult *, size_t);
  ```
- **Test**: `tests/disasm/test_arm_thumb_interwork.c` (ARM→Thumb BL, Thumb→ARM BX)
- **Integration**: `recursive_disasm.c:disasm_one_func()` 에서 mixed-mode 지원 시 BL/BX 후에 mode flip

### 제안 4. AArch64 4-byte jump table (S-3)

- **File**: `src/disasm/jump_table_aarch64.c` 신설 (또는 `jump_model.c` 내부 variant)
- **API**: entry size + base resolution 분기, adrp+add + ldrsw 패턴 인식
- **Test**: `tests/disasm/test_aarch64_switch_adrp.c` (production binaries 에서 추출한 switch blob)

### 제안 5. Thunk analyzer 통합 (M-2)

- **File**: `src/disasm/thunk_analyzer.c` 신설 (+ `aarch64_plt_thunks.c` 를 흡수)
- **API**:
  ```c
  typedef enum { THUNK_PLT, THUNK_GO_CLOSURE, THUNK_RUST_DISPATCH, THUNK_SWIFT_TAIL } ThunkKind;
  int thunk_detect(const RecDisasmResult *, ThunkTable *out);
  ```
- **Test**: `tests/disasm/test_thunk_plt_x86_64.c`, `test_thunk_go_closure.c`
- **Registry**: 각 kind 에 언어별 pattern DB (별도 `thunk_patterns.inc`)

---

## 9. Open Questions

1. **Capstone → SLEIGH 전환 비용/편익**
   - SLEIGH 컴파일러를 C 로 재이식하는 비용은 추정상 **연 단위**. 유지되는 Capstone decoder 의 production 완성도 대비 얻는 이득은 "ISA extension 기여 속도" 한 항목. 본 문서 결론: **전환 NO, Low-IR (M-1) 이 대안**.

2. **PCode-like IR 도입 vs 현행 유지**
   - 현행 IR 은 high-level 이라 condition-code / partial-register / flag-tracking 이 arch 별 패치로 누적 중 (RC-2). Low-IR 를 인터포즈하면 이 분기들이 한 곳으로 집중 → 유지보수 경감. **제안**: M-1 을 v2.4.0 목표로.

3. **새 아키텍처 추가 방식**
   - 옵션 A: Capstone 위에 per-arch C module (현행)
   - 옵션 B: SLEIGH 부분 import
   - 옵션 C: ML-based decoder (학술 연구 단계, production 위험)
   - 현실적 결론: A 유지 + Low-IR 도입으로 arch-specific 코드를 lowering table 로 표준화.

4. **JumpAssisted 수준 (symbolic emulation) 의 implementation 비용**
   - 완전한 emulator 는 수천 라인 + 테스트. Phase F/G 이후 별도 track 으로 분리.

5. **성능 회귀 우려**
   - Low-IR 추가 시 per-function 분석 latency +10~20% 예상 (decomp 전체의 <5%). 벤치 harness 로 확인 필요.

---

## 10. 인용

### Ghidra 공식 문서
- [SLEIGH Language Specification](https://ghidra.re/ghidra_docs/languages/html/sleigh.html) — NSA, Ghidra docs
- [Ghidra Decompiler Concepts](https://www.ghidradocs.com/11.0.1_PUBLIC/help/Decompiler/help/topics/DecompilePlugin/DecompilerConcepts.html)
- [SLEIGH Constructors chapter](https://ghidra-decompiler-docs.netlify.app/sleigh_constructors)

### Ghidra 소스
- `Ghidra/Features/Decompiler/src/decompile/cpp/jumptable.cc` — JumpModel 계층 ([mirror](https://github.com/NationalSecurityAgency/ghidra/blob/master/Ghidra/Features/Decompiler/src/decompile/cpp/jumptable.cc))
- `Ghidra/Features/Base/src/main/java/ghidra/app/plugin/core/disassembler/` — disassembler plugin
- `Ghidra/Processors/` — architecture specs

### Third-party 분석
- [Ghidra Discussion #2994 — "What kind of disassembling technique does Ghidra use?"](https://github.com/NationalSecurityAgency/ghidra/discussions/2994) — NSA maintainer 공식 답변
- [DeepWiki — Ghidra Decompiler System](https://deepwiki.com/NationalSecurityAgency/ghidra/2-decompiler-system)
- [DeepWiki — ARM/AArch64 Architecture Support](https://deepwiki.com/NationalSecurityAgency/ghidra/3.3-armaarch64-architecture-support)
- [PT SWARM — Guide to P-code Injection](https://swarm.ptsecurity.com/guide-to-p-code-injection/)
- [PT SWARM — Creating a Ghidra processor module](https://swarm.ptsecurity.com/creating-a-ghidra-processor-module-in-sleigh-using-v8-bytecode-as-an-example/)
- [NCC Group — Exploring Ghidra's decompiler internals](https://www.nccgroup.com/research/earlyremoval-in-the-conservatory-with-the-wrench-exploring-ghidra-s-decompiler-internals-to-make-automatic-p-code-analysis-scripts/)

### 학술
- "A Formal Semantics for P-Code", Springer 2023 — https://link.springer.com/chapter/10.1007/978-3-031-25803-9_7
- "SoK: All You Ever Wanted to Know About x86/x64 Binary Disassembly" — Pang et al., arxiv 2007.14266

### AURA 참조 (read-only)
- `src/disasm/capstone_wrapper.c` (276 LOC) — Capstone 래퍼
- `src/core/recursive_disasm.c` (654 LOC) — recursive descent + 기본 jump table
- `src/disasm/indirect_resolver.c` (379 LOC) — indirect call/jmp + vtable + jump table
- `src/decompiler/switch_recovery.c` (294 LOC) — if-else-if chain → switch 승격
- `include/decompiler.h` — IR_OP_* enum (~25 opcodes)
- `src/disasm/aarch64_plt_thunks.c` (213 LOC) — AArch64 PLT thunk

### Sibling tasks
- Task #26 (ghidra-analyst): 함수 탐지 pipeline — function start heuristic, signature matching
- Task #28: disasm ↔ decompiler lifting (PCode→high-IR bridge) 재분석
