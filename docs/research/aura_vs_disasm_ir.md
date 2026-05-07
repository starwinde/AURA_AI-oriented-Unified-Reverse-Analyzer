# AURA vs Ghidra · Rizin · x64dbg — Disassembly·IR 전환 블루프린트

> **작성자**: comparison teammate (Team v2-3-0-phase-2b, Task #42)
> **작성일**: 2026-04-21
> **목적**: AURA의 disasm+IR 파이프라인을 Ghidra PCode·Rizin RzIL·x64dbg 와 정량 비교하고, Phase 2-X 로 진입할 IR 재구조화 경로(단기/중기/장기)를 명세한다.
> **입력 근거**: `docs/research/{ghidra_disasm_analysis,ghidra_disasm_decompile_bridge_analysis,rizin_disasm_analysis,rizin_il_analysis,x64dbg_analysis}.md` + AURA 소스 직접 열람.
> **라이선스 경계**: Rizin LGPL-3 / Ghidra Apache-2.0 / x64dbg GPL-3 → AURA(Apache-2) 에 **코드 편입 금지**. 알고리즘·네이밍 참조만 허용, 구현은 scratch.

---

## 0. 요약 (TL;DR)

1. AURA IR 은 `IrOpcode` **28 종** · `IrType` **14 종** · `IrVal{id,type,imm}` 의 1-slot SSA 로 이미 작고 명료하지만, **플래그·부호 확장·캐리·제로 확장·나눗셈이 CMP_* 그룹 또는 UNSUPPORTED 로 축약**돼 있다. 결과적으로 `codegen.c::last_cmp_*` 스칼라 1-slot 캐시로는 AArch64 `csel`·x86 `cmov*`·flag-조합 분기를 온전히 재구성할 수 없다.
2. Rizin RzIL 은 **Core Theory 82 opcode (pure 70 + effect 12)** + `Bitvector<N>` sort + `opbuilder` DSL 로 동일 문제를 정석적으로 해결했고, Ghidra PCode 는 **CPUI_* ~90 opcode** + `Varnode(space,offset,size)` 로 주소공간까지 일반화했다. x64dbg 는 디컴파일 IR 이 없고 런타임 분석(token/pattern) 전용이라 IR 측면 차용 여지는 제한적이다.
3. 본 문서는 AURA IR 을 **(A) 단기 48-opcode 확장 → (B) 중기 `IrSort{kind,width}` + Flag 6-slot SSA → (C) 장기 codegen/arm64_lifter 재작성** 의 3단계로 전환할 것을 권고한다. 추정 비용: Phase A 1-2 세션 / 3-4 커밋, Phase B 2-3 세션 / 4-6 커밋, Phase C 3-5 세션 / 10-15 커밋.
4. Ghidra 클린-슬레이트 포크(Option D) 가 아닌 **Option B: AURA IR 을 RzIL-형상으로 점진 확장** 을 권장한다. 기존 16-pass 최적화 체인·HIR 정제기·테스트 인프라를 유지할 수 있고, 라이선스 오염 없이 같은 의미론에 도달한다.

---

## 1. AURA 현재 구조 (disasm → IR → lift → pass chain)

### 1.1 Disassembler 층 — `src/disasm/`

**파일 배치 (`find src/disasm -name '*.c'`)**:
- `capstone_wrapper.c` (276 LOC) — 4-아키텍처(x86/x86_64/ARM/ARM64) Capstone 핸들 래퍼
- `disasm.c` / `disasm_multi.c` — 선형/다중 블록 진입점
- `indirect_resolver.c` (379 LOC) — 3-패턴 간접 분기 해석
- `function_matcher.c`, `dwarf_symbols.c`, `arch_detector.c`, `dispatcher.c` 등 보조

**핵심 제약 (`capstone_wrapper.c:60-68`)**:
```c
case AURA_ARCH_ARM:
    cs_arch_val = CS_ARCH_ARM;
    cs_mode_val = CS_MODE_ARM;   /* ← 하드코딩: Thumb 미지원, IT-블록 상태 없음 */
    break;
```
- Capstone 핸들 생성 시 `CS_MODE_ARM` 고정 → Thumb/Thumb-2 미스캔, `$a/$t/$d` mapping symbol 소비 없음
- x86 64/32-bit 공존, M68K/PPC/MIPS 등 미확장
- `DisasmContext { csh handle; AuraArch arch; cs_err last_error }` 단일 상태 — Rizin 이 `RzAsm` 에 `BigEndian`·`Bits`·`Syntax` 를 유지한 것과 대비된다(#31 §2.1).

**Recursive disasm (`src/core/recursive_disasm.c`)**:
- Queue 기반 DFS worklist. `worklist_enqueue` / `worklist_dequeue`.
- Callsite 수집은 `call imm` 직접 타겟만 — `indirect_resolver.c` 의 3-패턴을 제외하면 간접 분기는 전부 드롭.
- `noreturn` 함수 목록은 하드코딩된 이름 집합(`__stack_chk_fail`, `abort`, `exit`, …) — Ghidra 의 `decompiler_analysis.xml::noreturn` 플러그형 프로파일(#27 §4) 과 비교해 정적.

**Indirect resolver (`src/disasm/indirect_resolver.c`)** — 3 패턴 **한정**:
1. `resolve_rip_relative` — `jmp qword ptr [rip+disp]` / `call qword ptr [rip+disp]` 의 절대 주소 역계산 (x86_64).
2. `detect_vtable_pattern` — `mov reg,[rdi]; … ; call [reg+N]` 의 back-5 window 스캔 → C++ vtable 인식. `PE_ADDR_UNKNOWN`/`ELF_ADDR_UNKNOWN` symbol 힌트가 있을 때만 확정.
3. `resolve_jump_table` — `cmp reg, imm; ja default; jmp [base + reg*8]` 의 x86 back-5 스캔. **8-byte entry 하드코딩** → 32-bit index table(Rizin jmptbl.c 의 케이스) 은 놓친다.

**누락**: AArch64 `adrp x0, page; ldr x1, [x0, #off]; br x1`, ARM `tbb`/`tbh`, AArch64 PAC, ARM Thumb bx/blx 인터워킹 전부 미처리.

### 1.2 IR 층 — `include/decompiler.h`

**타입 계층 (`IrType`, 14 종)**:
```
VOID, INT8, INT16, INT32, INT64, PTR, BOOL,
FLOAT, DOUBLE, LONG_DOUBLE,
VEC128, VEC256, VEC512, MMX
```
- `INT8..INT64` 는 signedness 가 없다 — `ir_sext`/`ir_zext` 는 opcode 로 존재하지 않는다. 현재는 `IR_OP_COPY` 로 축약하고 `mnemonic[16]` 문자열을 다음 pass 가 파싱하는 구조(hack).
- `VOID` 는 `RET` · `CALL_VOID` 에만 쓰이고 sort 분리가 없음 — RzIL `Bitvector<N>` 의 폭 분리(#32 §2.2) 과 차원이 다르다.

**Opcode 집합 (`IrOpcode`, 28 종)**:
```
COPY, CONST,
ADD, SUB, MUL, DIV,            /* 4 산술 */
AND, OR, XOR, SHL, SHR,         /* 5 비트/시프트 — SAR 없음 */
CMP_EQ, CMP_NE, CMP_LT, CMP_LE, CMP_GT, CMP_GE,
CMP_ULT, CMP_ULE, CMP_UGT, CMP_UGE,   /* 10 비교 */
LOAD, STORE,                    /* 2 메모리 */
BRANCH, JUMP, CALL, RET,        /* 4 제어 */
PHI, SELECT,                    /* 2 SSA */
UNSUPPORTED                      /* 1 escape */
```
- **없는 opcode**: `SDIV`/`UDIV`/`SREM`/`UREM`, `SAR`(signed shift), `ZEXT`/`SEXT`, `ROR`/`ROL`, `POPCOUNT`/`CLZ`/`CTZ`, `FADD/FMUL/FSUB/FDIV/FCMP`, `NEG`, `NOT`, `APPEND`/`EXTRACT`(bit-slice).
- **없는 구조**: 플래그 값(`CF`/`OF`/`PF`/`AF`)에 대응하는 전용 SSA 슬롯 — codegen 은 직전 `CMP_*` 의 id 만 기억(`last_cmp_id`).
- `IrVal = {uint32_t id, IrType type, int64_t imm}` — RzIL 의 `Bitvector<N>`(폭 명시) 와 달리 **상수도 I64 로 정규화**. 8-bit 의 오버플로우·부호확장을 opcode 레벨에서 표현하지 못해 `mnemonic`/`dst_pointee_width` 같은 사이드밴드 필드(#하단 F-1-T 참조) 로 보정하는 상태.

**Instr 레이아웃** (`decompiler.h::IrInstr`):
- `dst: IrVal`, `src0: IrVal`, `src1: IrVal` — 3-operand 고정.
- Phi 를 위해 `phi_srcs[]`/`phi_pred_ids[]` 동적 배열.
- Branch 는 `true_block_id` / `false_block_id` 로 후계자 명시.
- `mnemonic[16]` — 리프터 원문 기록용 디버그 필드(overflow 시 `mnemonic_overflow` flag 세트).
- `dst_pointee_width` — F-1-T 에서 opt-in 으로 추가된 포인터 폭 힌트(struct member 너비). 원칙적으로는 `IrType` 이 운반해야 할 메타.

**Block & Func**:
- `IrBlock { id, instrs, instr_count, succs[], preds[], def_reg_mask }` — `def_reg_mask` 는 Phase F Q-3 에서 Cytron SSA placement 용으로 추가.
- `IrFunc { blocks[], vars[], eh_frame_info* /* borrow, C-5 */ }`.

### 1.3 Lifter 층

**x86 lifter — `src/decompiler/codegen.c` (2438 LOC)**:
- `LIFT_BINOP` 매크로(524-552) 로 `add/sub/imul/mul/and/or/xor/shl/shr/sar` 를 매핑. `sar` 는 `IR_OP_SHR` 로 퇴화 — 부호 정보 소실.
- **Flag state (430-432)**:
  ```c
  uint32_t last_cmp_id = IR_VAL_ID_UNDEF;
  IrVal last_cmp_src0 = {IR_VAL_ID_UNDEF, IR_TYPE_INT64, 0};
  IrVal last_cmp_src1 = {IR_VAL_ID_UNDEF, IR_TYPE_INT64, 0};
  ```
  블록 진입 시 전부 리셋. 동일 블록 내 `cmp` 뒤에 `add`/`sub` 가 끼면 plausibly invalid(보수적으로 `CMP_NE` placeholder) 로 섞이고, cross-block 은 불가.
- `opcode_name` 스위치(2320-2350)에서 `CMP_UGT/UGE/GT/GE` 가 `"???"` 로 출력 — 프린터 버그이자, HIR 단계로 부호 비교 semantics 가 새어나가지 않는다는 증상.

**AArch64 lifter — `src/decompiler/arm64_lifter.c` (1449 LOC)**:
- **라인 127 silent fallback**:
  ```c
  /* Flag-only (mi/pl/vs/vc/al/nv) — no clean C equivalent. */
  /* Emit CMP_NE as a non-EQ placeholder */
  return IR_OP_CMP_NE;
  ```
  → `b.mi`·`b.pl`·`b.vs`·`b.vc` 가 전부 `CMP_NE` 로 치환된다. 이것이 v2.3.0-rc1 real-binary `csel` 파리티 손실의 뿌리.
- `adrp+add`·`adrp+ldr` 페어 처리 없음 → 전역 변수·점프테이블 베이스 주소가 opaque 상수로 남는다.

### 1.4 Pass chain — `codegen.c::ir_optimize` (2190-2253)

16 패스 단일-fixpoint (MAX_OPT_ITERS=10 상한, PASS_MANAGER_MAX_ITERS=5 실 상한):
```
sccp → const_fold → copy_prop → copy_prop_enhanced →
expr_simplify → expr_reassoc → cse → cond_simplify →
dead_code → dce → dead_store → licm → strength_reduce →
reg_coalesce → phi_elimination → tail_call
```
- Ghidra 는 `universalAction` 의 **그룹화된 action + 150+ Rule** 구조(#28 §5)로 각 rule 에 `getOpList()` 인덱스를 걸어 O(1) 디스패치. AURA 는 각 pass 가 `walk_blocks()` 를 독립 순회 → 복잡도 O(passes · blocks · instrs).
- Rizin RzIL 은 opcode 자체가 BAP semantics 로 정의돼 있어 **validator 만으로도 pass 건전성 대부분 증명 가능**(#32 §4.2). AURA 는 validator 가 없다.

### 1.5 HIR 층 — `include/hir.h`

- 26 `HirNodeKind` (SEQ/IF/WHILE/DO_WHILE/FOR/SWITCH/GOTO/LABEL/BREAK/CONTINUE/COMMENT/ASSIGN/RETURN/CALL_STMT/… + EXPR_VAR/CONST/BINOP/UNOP/CALL/CAST/FIELD_ACCESS/ARRAY_INDEX/TERNARY).
- `HirEmissionStats { gotos_emitted, funcs_with_goto, noreturn_truncations, … }` — Phase 2-A 에서 counter 도입.
- `HIR_COMMENT` (Pre-1) · `HIR_EXPR_TERNARY` (csel/cmov 용) 존재하나, **ternary 는 flag SSA 가 없으면 생성 불가** → arm64 csel 이 거의 emit 되지 않는다.

---

## 2. 4-툴 Gap Matrix

| 측면 | AURA (현재) | Ghidra PCode | Rizin RzIL | x64dbg | 단기 차용 포인트 |
|------|-------------|--------------|------------|--------|-----------------|
| IR opcode 수 | 28 | ~90 (CPUI_*) | 82 (pure 70 + eff 12) | (no IR) | **목표 48** (A-1~A-5) |
| IR 타입 sort | `IrType` enum 14개 (INT8..64+VEC+FP+PTR+BOOL) | `Varnode{space,offset,size}` 바이트 명시 | `Bitvector<N>`·`Bool`·`Mem<K,V>`·`Float<S,E>` | — | **IrSort{kind,width}** (B-1) |
| Flag 모델 | `last_cmp_*` 3-scalar, 블록-local | Flag varnode per-op emit | 명명된 Bool SSA slot (CF/OF/ZF/SF/PF/AF/NF/VF) | — | **Flag 6-slot SSA** (B-2) |
| 부호 확장/축소 | `IR_OP_COPY` + mnemonic string | CPUI_INT_ZEXT/SEXT/TRUNC | `zext`/`sext`/`cast` | — | `ZEXT`/`SEXT` opcode (A-2) |
| 나눗셈/모듈로 | `IR_OP_DIV` 단일 (부호 미분) | CPUI_INT_SDIV/UDIV/SREM/UREM | `sdiv`/`udiv`/`smod`/`umod` | — | `UDIV`/`SDIV`/`UREM`/`SREM` (A-3) |
| 부호 시프트 | `IR_OP_SHR` (sar→shr 축약) | CPUI_INT_SRIGHT/RIGHT | `shiftr` w/ fill bit | — | `SAR` 복원 (A-4) |
| Bit-slice | 없음 | CPUI_SUBPIECE · PIECE | `append`·`extract` | — | `APPEND`/`EXTRACT` (A-5) |
| FP 연산 | `UNSUPPORTED` 투척 | CPUI_FLOAT_* 14종 | `fadd/fmul/…` 14종 | — | Phase C-5 |
| 간접 분기 | 3 패턴 (rip-rel, x86 vtable, x86 jmptbl 8byte) | JumpModel 4-class (Basic/Override/Assisted) | jmptbl.c 4-dispatch (x86 / case-tbl / ARM TBB/TBH / AArch64 adrp+ldr+br) | pattern-match only | **AArch64 adrp+ldr+br** (S-2) |
| ARM mode switching | ARM fixed | SLEIGH context bits | `$a`/`$t`/`$d` mapping symbol 소비 | ZydisDecoder mode | **Thumb detection** (S-3) |
| Pass 디스패치 | 16 pass 독립 순회 | `universalAction` 그룹 + `getOpList()` 인덱스 | opbuilder + validator | — | `getOpList()` 인덱스 (M-1) |
| 라이선스 | Apache-2 | Apache-2 | LGPL-3 | GPL-3 | Rizin/Ghidra **복붙 불가** |

---

## 2.A. 워크드 예시 — x86 `ADD eax, ebx` 리프팅 비교

### AURA 현재 출력 (`codegen.c` LIFT_BINOP + last_cmp 세터)
```
%t1 = add i64 %eax %ebx          ; dst type = INT64 (regardless of eax/ebx being 32-bit)
%cmp_last = %t1                  ; last_cmp_id = %t1 (as src0)
;; OF/CF 정보 소실 — jo/jc 가 바로 뒤에 오면 CMP_NE placeholder
```
⇒ 직후 `jo label` 은 `branch cmp_ne(%t1, 0)` 로 치환됨. OF(signed overflow) 의미와 전혀 다름.

### Rizin RzIL 출력(#32 §5.2, opbuilder 형식 — 참조용)
```
(seq6
  (set eax (add (var eax) (var ebx)))
  (set cf  (bool-to-bv (carry    (var eax) (var ebx))))
  (set of  (bool-to-bv (s-carry  (var eax) (var ebx))))
  (set sf  (msb (var eax)))
  (set zf  (is-zero (var eax)))
  (set pf  (parity (extract (var eax) 0 7))))
```
⇒ 8 bit pf 까지 명시적으로 producer-정의. `jo` 는 `branch (var of) label else next`.

### Ghidra PCode 출력(#28 §3.2)
```
eax = INT_ADD eax, ebx
CF  = INT_CARRY eax_pre, ebx
OF  = INT_SCARRY eax_pre, ebx
ZF  = INT_EQUAL eax, 0
SF  = INT_SLESS eax, 0
PF  = UNIMPL                     ; Ghidra 는 PF 를 대개 생략
```

### AURA Phase A+B 목표 출력 (본 블루프린트 2-X-B 이후)
```
%eax' = ADD  i32 %eax %ebx
flag.cf = CARRY  i32 %eax %ebx
flag.of = SCARRY i32 %eax %ebx
flag.zf = IS_ZERO i32 %eax'
flag.sf = EXTRACT i32 %eax' 31 1     ; bit 31
branch flag.of, label, fallthrough   ; for subsequent JO
```

⇒ 4-툴 모두 동일 의미론에 도달. 핵심은 **플래그 producer 를 산술 opcode 와 같은 시점에 emit** 하고, predicate 으로 명시적 사용. AURA 는 이 producer 자체가 없어서 플래그 SSA 전에 opcode 가 먼저 생겨야 한다(Phase A-1 ordering).

---

## 3. 단기 (Phase 2-X-1 ~ 2-X-7) — 1-2 세션 / 3-4 커밋

목표: **기존 IR 구조를 흔들지 않고**, rc2 real-binary 파리티 손실의 8-9할을 복구한다. Ghidra #28 R-S1·R-S3, Rizin #31 S-A/B/C, Rizin #32 Phase A 의 교집합.

### 2-X-1. `IrOpcode` 28 → 48 확장 (최우선, A-level)

추가할 opcode (20종):
```
IR_OP_ZEXT, IR_OP_SEXT, IR_OP_TRUNC,            /* 부호/폭 변환 */
IR_OP_SDIV, IR_OP_UDIV, IR_OP_SREM, IR_OP_UREM, /* 부호 분리 나눗셈 */
IR_OP_SAR,                                        /* 부호 시프트 */
IR_OP_ROL, IR_OP_ROR,                            /* 회전 */
IR_OP_NEG, IR_OP_NOT,                            /* 단항 */
IR_OP_POPCOUNT, IR_OP_CLZ, IR_OP_CTZ,           /* 비트 카운트 */
IR_OP_APPEND, IR_OP_EXTRACT,                     /* bit-slice */
IR_OP_CARRY, IR_OP_SCARRY, IR_OP_SBORROW,       /* 플래그 producer */
IR_OP_IS_ZERO                                    /* ZF producer (RzIL `is_zero`) */
```
- **파급**: `codegen.c::opcode_name`, `codegen.c::ir_optimize` 각 pass, `hir_builder.c`, `pseudo_c_printer.c` 에 case 추가. `LIFT_BINOP` 매크로는 유지, `LIFT_UNOP` 새로 정의.
- **테스트**: `tests/decompiler/test_ir_opcodes.c` 에 20 opcode 각각 MIR-style golden.
- **영향**: arm64 `csel` / `cmov*` / `setg`·`setl` 조합이 정상 HIR 로 복원 → Phase 2-B 의 `gotos` 23% 중 5-8%p 감소 예상(추정, gap matrix 정량화).

### 2-X-2. `last_cmp_*` 3-scalar → Flag 6-slot (B-lite)

정식 `IrSort` 확정 전이라도 **codegen.c 내부 구조만** 교체 가능:
```c
/* codegen.c block-local flag cache */
typedef struct {
    uint32_t cf_id;  /* set by ADD/SUB/SHL/SHR */
    uint32_t of_id;  /* set by ADD/SUB/MUL */
    uint32_t zf_id;  /* set by ANY arithmetic with IS_ZERO */
    uint32_t sf_id;  /* high-bit COPY of arithmetic result */
    uint32_t pf_id;  /* POPCOUNT %2 — optional, default UNDEF */
    uint32_t af_id;  /* adjust flag — optional */
} FlagCache;
```
- `x86_lift_add` · `x86_lift_sub` 에서 각 slot 에 `IR_OP_CARRY`·`IR_OP_SCARRY`·`IR_OP_IS_ZERO` 산출 instruction emit.
- `x86_lift_jcc` 는 `last_cmp_*` 대신 해당 slot 을 읽어 `CMP_*`(이미 SSA 화된 bool) 을 branch predicate 으로 사용.
- **블록 간 전파**: 당장은 block-local 로 유지(= RzIL `local effect` 와 동일), phi 는 Phase B-1 에서 합류.

### 2-X-3. AArch64 jump-table 인식 (S-level)

`indirect_resolver.c::resolve_jump_table` 을 dispatcher 로 분해:
```c
static bool resolve_jmptbl_x86(…);
static bool resolve_jmptbl_aarch64(…);   /* adrp x0,@L; add x0,x0,:lo12:@L; ldr x1,[x0,x2,lsl#3]; br x1 */
static bool resolve_jmptbl_arm_tbb(…);   /* .tbb + byte table */
static bool resolve_jmptbl_arm_tbh(…);   /* .tbh + halfword table */
```
- Rizin `jmptbl.c` 의 4-분기 구조(#31 §3.4) 를 알고리즘 레벨에서 참고(코드 이식 금지, 파일 최상단 주석에 "inspired by Rizin jmptbl.c, reimplemented clean-room" 명시).
- 8-byte entry 하드코딩은 `entry_size` 인자로 파라미터화.

### 2-X-4. ARM Thumb detection (S-level)

- `capstone_wrapper.c` 를 `DisasmContext` 에 `cs_mode_t cur_mode` 를 추가하고, `disasm_at(addr)` 이 ARM ELF 인 경우 **mapping symbol `$a`/`$t`/`$d` 를 사전 스캔**해 주소 범위별 모드 결정. 심볼이 없는 바이너리는 LSB(=1) 타겟만 Thumb 로 가정.
- `cs_option(h, CS_OPT_MODE, new_mode)` 로 핸들 재구성(cs 는 런타임 모드 교체 지원).

### 2-X-5. `noreturn` 프로파일 외부화

- 현재 하드코딩된 이름 리스트를 `third_party/noreturn/*.txt` 로 분리, `parser/elf.c` 가 import 된 symbol 이름을 매칭.
- Ghidra 의 `decompiler_analysis.xml`(#27 §4) 패턴을 차용하지만 파일 포맷은 AURA 자체 정의.

### 2-X-6. `opcode_name` 프린터 수정

`codegen.c:2320-2350` 의 `CMP_UGT/UGE/GT/GE → "???"` 케이스를 정상 매핑. 단순 버그 수정이지만 HIR debug dump 품질이 즉시 개선.

### 2-X-7. IR validator (경량)

- 새 파일 `src/decompiler/ir_validator.c` 에 3 규칙:
  1. **Type compatibility**: `ADD/SUB` 는 `IrType(src0)==IrType(src1)`, `CMP_*` 결과는 `BOOL`.
  2. **SSA**: 각 `IrVal.id` 는 단 하나의 defining instr 을 가진다(phi 제외).
  3. **Reachability**: 모든 non-entry block 은 최소 1 predecessor.
- `ctest` 단계에 inject → 회귀 조기 발견. RzIL validator(#32 §4.2) 의 축소판.

**Phase A (2-X-1~7) 커밋 추정**: 3-4 커밋 (opcode-expand / flag-6slot / jmptbl-dispatch / validator-or-thumb 번들).

---

### 3.8. 워크드 예시 — AArch64 `csel x0, x1, x2, lt`

**현재 AURA (`arm64_lifter.c:127` fallback)**:
```
;; b.lt / csel lt 코드는 last_cmp_src0 < last_cmp_src1 로 복원, 
;; 그러나 b.mi/pl/vs/vc 는 CMP_NE placeholder 로 축약 → 의미 완전 소실
;; csel x0, x1, x2, lt 에서 condition=lt 라도 select 의 predicate 가 
;; block 경계를 넘어가면 last_cmp_id = UNDEF → select 불가 → goto fallback
```

**Phase A-1/A-2 이후 목표**:
```
%c = CMP_LT i64 %prev_cmp_s0, %prev_cmp_s1      ; SSA-화된 bool
%x0' = SELECT i64 %c, %x1, %x2                   ; csel → IR_OP_SELECT
```
HIR 에 `HIR_EXPR_TERNARY(c, x1, x2)` 로 승격되어 `x0 = c ? x1 : x2` 로 인쇄.

**Phase C-2 이후 목표** (silent fallback 제거):
```
;; for b.mi
branch flag.sf, label_mi, fallthrough
;; for b.vs
branch flag.of, label_vs, fallthrough
```
flag SSA 가 predicate 소스 → 의미 보존.

---

## 4. 중기 (Phase 2-X-B) — 2-3 세션 / 4-6 커밋

목표: IR 의 **타입 체계와 플래그 체계** 를 RzIL 수준으로 정비해, 장기 리라이트(Phase C) 의 기반을 확보한다.

### 4.1 `IrSort{kind,width}` 도입 (B-1)

현재 `IrType` enum 을 구조체로 대체:
```c
typedef enum { IR_SORT_BV, IR_SORT_BOOL, IR_SORT_FLOAT, IR_SORT_MEM, IR_SORT_VOID } IrSortKind;
typedef struct {
    IrSortKind kind;
    uint16_t   width;    /* BV: bit-width 1..512. FLOAT: total bits (32/64/80). MEM: element bits. */
    uint16_t   align;    /* MEM only */
} IrSort;
```
- `IrVal` 을 `{ uint32_t id; IrSort sort; int64_t imm; }` 로 확장.
- 기존 `IR_TYPE_INT8..INT64` 는 `{BV, 8..64}` 로 재정의, `IR_TYPE_PTR` → `{BV, <target ptr width>}` + instruction annotation(`is_pointer`).
- **마이그레이션**: 헬퍼 `IrSort ir_sort_i(uint16_t w)`/`ir_sort_bool()` 로 기존 코드 자동 치환. 1차에는 `IR_TYPE_INT64` 의 모든 참조를 `ir_sort_i(64)` 로 sed. 실패 지점만 수동 수정.
- **이득**: `ADD i8` vs `ADD i32` 가 sort 로 구별 → `expr_simplify` / `copy_prop_enhanced` 의 폭 관련 버그(예: `(int32_t)x + (int64_t)y` 를 그대로 fold) 해소.

### 4.2 Flag Global SSA 6-slot (B-2)

- `IrFunc` 에 `FlagStream flags[6]` 추가. 각 스트림은 해당 플래그 producer/consumer SSA chain.
- `x86_lift_add` emit:
  ```
  %t = add %a %b
  flags.cf = carry(%a, %b)
  flags.of = scarry(%a, %b)
  flags.zf = is_zero %t
  flags.sf = extract %t, 63, 1
  ```
- Block 경계에서는 **flag slot 을 phi 로 합류** — 기존 변수 phi 와 동일 경로. 이것이 RzIL 의 `set CF (carry …)` + 전역 VM state 와 의미론적으로 등가(#32 §3.3).
- `x86_lift_jcc`·`aarch64_lift_b_cond` 는 predicate 로 flag slot 의 SSA id 를 읽는다. → arm64 `b.mi` 등 silent-fallback 제거.

### 4.3 opbuilder DSL (B-3)

RzIL `rz_il_opbuilder_begin.h`(#32 §5.2) 에서 영감:
```c
#include "ir_opbuilder_begin.h"   /* macro 단방향 include, #undef 일괄 */
IrVal t = SEQ3(
    SET(cf, CARRY(a, b)),
    SET(of, SCARRY(a, b)),
    ADD(a, b));
#include "ir_opbuilder_end.h"
```
- 매크로는 `ir_build_*` 헬퍼로 전개, `IrFunc *cur_fn` 은 TLS 또는 scope stack.
- 2458 LOC `codegen.c` 의 `x86_lift_*` 함수들은 매크로 치환으로 500-800 LOC 수준까지 축소 가능.

### 4.4 Validator 확장 (B-4)

Phase A-7 의 3 규칙 + 추가:
4. **Flag producer**: `BRANCH` 의 predicate 는 `IR_SORT_BOOL` 또는 flag slot id.
5. **Sort propagation**: `LOAD ptr -> dst` 는 `ptr.sort.kind==BV && dst.sort.width == load_width*8`.
6. **Phi agreement**: 모든 phi incoming 의 sort 가 동일.

### 4.5 Pass 디스패치 O(1) 인덱스 (B-5)

- 각 pass 에 `uint32_t get_op_mask()` 구현 (예: `const_fold → (1<<ADD)|(1<<SUB)|(1<<MUL)|…`).
- `walk_blocks` 대신 `IrFunc` 레벨에 per-opcode bucket 유지, pass 는 자기 opcode bucket 만 순회.
- Ghidra `universalAction::getOpList()`(#28 §5.3) 의 기법. 150+ rule 구조는 지나친 일반화라 채택 안 함, 16 pass 에서만 활용.

### 4.6 Decoder 공용화 (B-6, optional)

- Capstone 외 Zydis x86 디코더를 `src/disasm/backends/{capstone,zydis}.c` 로 분리, `disasm_backend_t` 인터페이스. Phase 5.7 어셈블러(Zydis) 와 핸들 공유로 메모리 절약.

**Phase B 커밋 추정**: 4-6 커밋 (IrSort / flag-ssa / opbuilder / validator-extended / op-mask-dispatch / [backend-split opt]).

---

### 4.A. IrSort 마이그레이션 체크리스트 (B-1 가드레일)

IrSort 전환은 단일 big-bang 이므로 사전에 다음을 정리한다:

1. **헬퍼 확정**: `ir_sort_i(w)`, `ir_sort_bool()`, `ir_sort_float(w)`, `ir_sort_ptr(w)` 먼저 추가.
2. **Enum → 구조체 매핑 표 작성**:
   - `IR_TYPE_INT8` → `{BV,8,0}`
   - `IR_TYPE_INT16` → `{BV,16,0}`
   - `IR_TYPE_INT32` → `{BV,32,0}`
   - `IR_TYPE_INT64` → `{BV,64,0}`
   - `IR_TYPE_PTR` → `{BV,64,0}` + `is_pointer=true`
   - `IR_TYPE_BOOL` → `{BOOL,1,0}`
   - `IR_TYPE_FLOAT/DOUBLE/LONG_DOUBLE` → `{FLOAT,32/64/80,0}`
   - `IR_TYPE_VEC128/256/512` → `{BV,128/256/512,align=16/32/64}`
3. **sed 치환**: `IR_TYPE_INT64` → `ir_sort_i(64)` 전역 치환. 결과를 빌드 → 컴파일 에러 전수 수정.
4. **테스트 인프라**: `tests/decompiler/test_ir_sort.c` 에 sort 비교 헬퍼.
5. **`mnemonic[16]` 필드 정리**: 현재 sort 부족 보완용 사이드밴드 문자열 중 일부 제거 가능. `dst_pointee_width` 도 `IrSort.width * 8` 로 대체 검토.
6. **CI 회귀 가드**: 기존 real-binary 테스트 (`tests/decompiler/test_real_binary.sh`, `tests/benchmark/regression_harness.sh`) 실행 — 회귀 < 5% 목표.

### 4.B. opbuilder DSL 전체 매크로 예시

```c
/* ir_opbuilder_begin.h — single include, companion end.h undef 전체 */
#define ADD(a,b)      ir_build_binop(IR_OP_ADD, (a), (b))
#define SUB(a,b)      ir_build_binop(IR_OP_SUB, (a), (b))
#define CARRY(a,b)    ir_build_binop(IR_OP_CARRY, (a), (b))
#define SCARRY(a,b)   ir_build_binop(IR_OP_SCARRY, (a), (b))
#define IS_ZERO(x)    ir_build_unop (IR_OP_IS_ZERO, (x))
#define EXTRACT(x,lo,w) ir_build_extract((x),(lo),(w))
#define SET(slot,v)   ir_build_set((slot), (v))
#define SEQ2(a,b)     ir_build_seq2((a),(b))
#define SEQ3(a,b,c)   ir_build_seq3((a),(b),(c))
#define SEQ6(a,b,c,d,e,f) ir_build_seq6((a),(b),(c),(d),(e),(f))
#define BRANCH(p,t,f) ir_build_branch((p),(t),(f))
/* ... */
```
- `ir_build_*` 헬퍼는 `current_block()` 에 instr 을 append 하고 새 SSA id 를 반환.
- `ir_opbuilder_end.h` 에서 `#undef` 로 소거해 매크로 누출 방지 (RzIL `rz_il_opbuilder_end.h` 패턴).
- 파일 단위로만 include → 함수 내부에서 `opbuilder_begin()/opbuilder_end()` 호출 강제로 scope 제어.

---

## 5. 장기 (Phase 2-X-C) — 3-5 세션 / 10-15 커밋

목표: AURA IR 을 **RzIL-급 표현력** 까지 끌어올리되 scratch 구현, Apache-2 라이선스 유지.

### 5.1 codegen.c 재작성 (C-1, ~1500 LOC)

- 현재 단일 파일 2438 LOC 의 `codegen.c` 를 `src/decompiler/x86/{lift_arith.c, lift_logic.c, lift_mem.c, lift_branch.c, lift_fp.c}` 로 분할.
- 각 모듈은 Phase B 의 `opbuilder` DSL 만 사용, `last_cmp_*` 전역 제거.
- SIMD (SSE/AVX) 는 `IR_SORT_BV{128,256,512}` 기반 opcode 로 승격.

### 5.2 arm64_lifter.c 재작성 (C-2, ~1000 LOC)

- `arm64_lifter.c:127` 의 silent CMP_NE fallback 제거.
- `b.mi/pl/vs/vc` 를 `IR_OP_BRANCH` predicate = `flags.sf` / `!flags.sf` / `flags.of` / `!flags.of` 로 직결.
- `adrp + add`·`adrp + ldr` 페어 fusing → 전역 주소 재구성.
- `csel`·`csinc`·`csinv`·`csneg` → `IR_OP_SELECT` with flag predicate.
- Thumb/Thumb-2 인터워킹은 Phase A-4 의 mapping symbol 결과를 직접 소비.

### 5.3 FP lifter (C-3, RzIL 참조)

- `IR_OP_FADD/FSUB/FMUL/FDIV/FSQRT/FCMP_*` 14종, `IR_SORT_FLOAT{32,64,80}`.
- x86 `addss/addsd/movss/…`, AArch64 `fadd/fcmp` 모두 지원.
- HIR 에 `HIR_EXPR_FP_BINOP` 추가, pseudo-C 프린터에 `(float)` / `(double)` 캐스트 규칙.

### 5.4 M68K / PPC / MIPS 리프터 (C-4, optional)

- Capstone 은 이미 디스어셈블 지원. 리프터만 추가.
- Ghidra 의 SLEIGH DSL 은 편의상 참고 가능하되 AURA 는 hand-written C 유지(핵심 원칙 §5 "커스텀 구현 우선").

### 5.5 JumpModel 4-class (C-5)

- Ghidra `JumpBasic/JumpOverride/JumpAssisted/JumpTableModel`(#28 §6.2) 에 대응해 `src/decompiler/jumpmodel.c` 에 전략 패턴.
- 인덱스 범위·guard block·default edge 를 HIR `HIR_SWITCH` 로 승격.

### 5.6 ArchInfo profile 플러거블 (C-6)

- 현재 `arch_detector.c` 의 scalar 체크를 `ArchProfile { calling_conv, endianness, ptr_width, reg_file, relocation_kinds[] }` 로 교체.
- 새 아키텍처 추가 비용 ↓.

**Phase C 커밋 추정**: 10-15 커밋 — codegen.c 분할(3) + arm64 재작성(3) + FP lifter(2) + jumpmodel(2) + archprofile(1) + 기타(1-4).

---

### 5.A. arm64_lifter.c:127 fix — 코드 sketch (구현 가이드)

**현재(원문)**:
```c
/* arm64_lifter.c:120-130 */
static IrOpcode arm64_cond_to_ir_opcode(arm64_cc cc) {
    switch (cc) {
        case ARM64_CC_EQ: return IR_OP_CMP_EQ;
        case ARM64_CC_NE: return IR_OP_CMP_NE;
        case ARM64_CC_LT: return IR_OP_CMP_LT;
        /* ... GE/GT/LE ... */
        default:
            /* Flag-only (mi/pl/vs/vc/al/nv) — no clean C equivalent. */
            /* Emit CMP_NE as a non-EQ placeholder */
            return IR_OP_CMP_NE;   /* ← silent fallback */
    }
}
```

**Phase C-2 이후 (flag SSA 사용)**:
```c
/* arm64_lifter.c::arm64_lift_b_cond (new) */
static void arm64_lift_b_cond(cs_insn *insn, IrBlock *blk) {
    arm64_cc cc = insn->detail->arm64.cc;
    uint32_t pred_id;
    switch (cc) {
        case ARM64_CC_EQ: pred_id = cur_fn->flags.zf; break;
        case ARM64_CC_NE: pred_id = emit_not(cur_fn->flags.zf); break;
        case ARM64_CC_MI: pred_id = cur_fn->flags.sf; break;
        case ARM64_CC_PL: pred_id = emit_not(cur_fn->flags.sf); break;
        case ARM64_CC_VS: pred_id = cur_fn->flags.of; break;
        case ARM64_CC_VC: pred_id = emit_not(cur_fn->flags.of); break;
        case ARM64_CC_LT: pred_id = emit_xor(cur_fn->flags.sf, cur_fn->flags.of); break;
        case ARM64_CC_GE: pred_id = emit_not(emit_xor(sf, of)); break;
        case ARM64_CC_GT: pred_id = emit_and(emit_not(zf), emit_not(emit_xor(sf, of))); break;
        case ARM64_CC_LE: pred_id = emit_or(zf, emit_xor(sf, of)); break;
        case ARM64_CC_HI: pred_id = emit_and(cf, emit_not(zf)); break;   /* unsigned >  */
        case ARM64_CC_LS: pred_id = emit_or(emit_not(cf), zf); break;     /* unsigned ≤  */
        /* CS/CC handled as HS/LO (C set/clear, direct cf use) */
        case ARM64_CC_HS: pred_id = cur_fn->flags.cf; break;
        case ARM64_CC_LO: pred_id = emit_not(cur_fn->flags.cf); break;
        case ARM64_CC_AL:
        case ARM64_CC_NV:
        default:         pred_id = ir_const_bool(true); break;
    }
    ir_emit_branch(blk, pred_id, target_block_id, fallthrough_block_id);
}
```

→ 16 condition code 전부 정의. silent placeholder 0 건.

---

## 6. 의존성 그래프 (어떤 작업이 어떤 작업을 전제로 하는가)

```
                        ┌─ A-1 opcode 28→48 ──────────────┐
                        │                                   │
                        ├─ A-2 flag 6-slot (block-local) ──┤
                        │                                   │
Phase A (1-2 세션)   A-3 jmptbl 4-disp (AArch64)          │
                        │                                   │
                        ├─ A-4 Thumb detection              │
                        │                                   │
                        ├─ A-5 noreturn profile 외부화     │
                        │                                   │
                        ├─ A-6 opcode_name printer fix     │
                        │                                   │
                        └─ A-7 validator (core 3 rules)   ──┤
                                                             │
                                                             ▼
                        ┌─ B-1 IrSort{kind,width} ──────────┐
                        │  ↑ 전제: A-1 (새 opcode 가 sort 의미론 확정 필요)
                        │                                   │
Phase B (2-3 세션)   B-2 Flag Global SSA (phi 합류)  ─────┤
                        │  ↑ 전제: A-2 (block-local cache 구조) + B-1
                        │                                   │
                        ├─ B-3 opbuilder DSL ───────────────┤
                        │  ↑ 전제: B-1 sort 체계
                        │                                   │
                        ├─ B-4 validator ext (sort/flag)   ─┤
                        │  ↑ 전제: A-7 + B-1 + B-2
                        │                                   │
                        ├─ B-5 op-mask 디스패치            │
                        │                                   │
                        └─ B-6 decoder backend split (opt) ─┤
                                                             │
                                                             ▼
                        ┌─ C-1 codegen.c 분할·재작성 ──────┐
                        │  ↑ 전제: B-2 + B-3 (opbuilder 필수)
                        │                                   │
Phase C (3-5 세션)   C-2 arm64_lifter 재작성 ──────────────┤
                        │  ↑ 전제: C-1 기법 확정 + A-4 mapping sym
                        │                                   │
                        ├─ C-3 FP lifter ───────────────────┤
                        │  ↑ 전제: B-1 IrSort Float
                        │                                   │
                        ├─ C-4 m68k/ppc/mips (opt) ────────┤
                        │                                   │
                        ├─ C-5 JumpModel 4-class           │
                        │  ↑ 전제: A-3 + HIR_SWITCH
                        │                                   │
                        └─ C-6 ArchProfile 플러거블 (opt)─┤
                                                             │
                                                             ▼
                                               Ghidra/Rizin-급 IR (scratch, Apache-2)
```

---

## 7. Phase 2-X 로드맵 매핑 (AUTOMATION_ROADMAP.md 양식)

> 현재 Live canonical 은 Phase 2-B `[x]`, Phase 2-C `[ ]` 대기. 본 블루프린트의 Phase A/B/C 를 Phase 2-X 시리즈로 승격 제안.

```
Phase 2-X — IR Recapitalization (NEW, v2.3.0 → v2.4.0 경로)
├─ 2-X-A  Opcode Expand & Flag Cache (단기, Phase A)
│  ├─ [ ] A-1  IrOpcode 28→48 추가 (ZEXT/SEXT/TRUNC/SDIV/UDIV/SREM/UREM/SAR/ROL/ROR/NEG/NOT/APPEND/EXTRACT/IS_ZERO/CARRY/SCARRY/SBORROW/POPCOUNT/CLZ/CTZ)
│  ├─ [ ] A-2  Flag cache 3→6 slot (block-local, CF/OF/ZF/SF/PF/AF)
│  ├─ [ ] A-3  Indirect resolver → 4-dispatcher (x86 / AArch64 adrp+ldr+br / ARM TBB/TBH)
│  ├─ [ ] A-4  Thumb detection (capstone mode switch via mapping symbols)
│  ├─ [ ] A-5  noreturn profile 외부화
│  ├─ [ ] A-6  opcode_name printer fix (CMP_UGT/UGE/GT/GE)
│  └─ [ ] A-7  IR validator (type/SSA/reachability)
├─ 2-X-B  IrSort & Flag SSA (중기, Phase B)
│  ├─ [ ] B-1  IrSort{kind,width} 도입
│  ├─ [ ] B-2  Flag Global SSA (6-slot phi)
│  ├─ [ ] B-3  opbuilder DSL 매크로
│  ├─ [ ] B-4  Validator 확장 (sort/flag/phi)
│  ├─ [ ] B-5  Pass op-mask 디스패치
│  └─ [ ] B-6  Decoder backend split (opt: Zydis x86)
└─ 2-X-C  Full Lifter Rewrite (장기, Phase C)
   ├─ [ ] C-1  codegen.c 분할·재작성 (~1500 LOC)
   ├─ [ ] C-2  arm64_lifter 재작성 (~1000 LOC, silent CMP_NE 제거)
   ├─ [ ] C-3  FP lifter (14 opcode, IR_SORT_FLOAT)
   ├─ [ ] C-4  m68k/ppc/mips (opt)
   ├─ [ ] C-5  JumpModel 4-class
   └─ [ ] C-6  ArchProfile 플러거블 (opt)
```

**예상 totals**: 17-19 세션 / 17-25 커밋 (Phase A 1-2s/3-4c + Phase B 2-3s/4-6c + Phase C 3-5s/10-15c; 옵션 포함 시 최대).

### 7.A. Phase A 권장 커밋 시퀀스 (실행 가이드)

**Commit 1 — opcode expand**:
- `include/decompiler.h` 에 20 opcode 추가
- `src/decompiler/codegen.c::opcode_name` 에 case 20 추가 (기존 `"???"` 버그 동시 수정)
- `src/decompiler/hir_builder.c::hir_lift_instr` 에 case 20 추가
- `tests/decompiler/test_ir_opcodes.c` 신규 — 20 opcode golden
- 메시지: `feat(ir): A-1 IrOpcode 28→48 expand (v2.3.0 Phase 2-X-A)`

**Commit 2 — flag 6-slot block-local**:
- `src/decompiler/codegen.c` 에 `FlagCache` 구조 추가 (block 진입 시 리셋)
- `x86_lift_add/sub/and/or/xor/shl/shr/sar` 에서 각 slot 에 `CARRY`/`SCARRY`/`IS_ZERO`/bit-extract emit
- `x86_lift_jcc` 에서 slot id 를 predicate 로
- 테스트: `tests/decompiler/test_flag_cache.c` 신규
- 메시지: `feat(ir): A-2 x86 flag cache 3-scalar → 6-slot (block-local)`

**Commit 3 — indirect resolver 4-dispatch + printer fix + validator core**:
- `src/disasm/indirect_resolver.c` 를 `resolve_jmptbl_{x86,aarch64,arm_tbb,arm_tbh}` 로 분해
- `src/decompiler/ir_validator.c` 신규 — 3 규칙 (type/SSA/reachability)
- `ctest` 에 validator 단계 삽입
- 테스트: `tests/disasm/test_indirect_aarch64.sh` (frozen AArch64 fixture 추가)
- 메시지: `feat(disasm): A-3+A-7 indirect 4-dispatch + IR validator core`

**Commit 4 — Thumb detection + noreturn 외부화**:
- `src/disasm/capstone_wrapper.c` 에 `cs_option(CS_OPT_MODE)` 동적 전환 + `$a/$t/$d` 스캔
- `src/core/recursive_disasm.c::noreturn_names` 를 `third_party/noreturn/libc.txt` 로 분리, 로더 추가
- 메시지: `feat(disasm): A-4+A-5 ARM Thumb mapping symbols + noreturn profile`

→ 4 커밋으로 Phase A 완주. CI 통과 후 v2.3.0 rc3 에 포함.
**정량 KPI**: rc1 대비 goto 23% → 목표 8-12%, cap_hits 93% → 75% 이하(jmptbl AArch64 복구 효과), arm64 csel 파리티 0% → 60%+ (Phase C-2 종료).

---

## 8. Option 선택 및 리스크

### 8.1 Option A — Do Nothing / patchwork
- **비용**: 0. Phase 2-C 의 opt-in 플래그 누적만. 
- **리스크**: rc2→rc3 파리티가 천장(real-binary 45-55% covered_avg)에서 정체. flag-조합 분기 신규 아키텍처 리프터마다 재발생.

### 8.2 Option B — 점진 RzIL-형상 확장 (🟢 권장)
- **비용**: Phase A+B+C = 17-25 커밋. 기존 pass chain·HIR·테스트 유지.
- **리스크**: IrSort 마이그레이션이 16 pass 전반을 동시 수정해야 함 — B-1 전환 커밋은 단일 big-bang 이 불가피, 반나절 세션 격리 필요.
- **이득**: Ghidra/Rizin 급 IR 품질, 라이선스 오염 0, 기존 CI 회귀 < 5%.

### 8.3 Option C — Ghidra PCode scratch clone
- **비용**: 30+ 커밋. CPUI_* ~90 opcode + Varnode space 모델 scratch.
- **리스크**: Varnode(space,offset,size) 는 AURA 의 IrBlock/IrVal 와 차원이 달라 HIR 연계 재설계 필수. Apache-2 호환이라 파일 레벨 참조는 가능하나 code copy 는 여전히 법무 검토.
- **이득**: 주소공간 일반화(register/ram/constant/unique/stack) 완전 확보.

### 8.4 Option D — Rizin RzIL fork (❌ 비권장)
- **비용**: LGPL-3 → AURA Apache-2 에 링크 시 **동적 링크 강제 + 재배포 시 LGPL 준수**. 정적 링크 원칙(§5) 위배.
- **리스크**: 라이선스 오염, 사용자 배포 시 분리 패키징.

→ **최종 권장**: Option B. Phase A 를 v2.3.0 rc3 직후, Phase B 를 v2.4.0-α, Phase C 를 v2.4.0-β~rc1 에 배치.

---

## 9. 인용 / 출처

### AURA 내부 (본 분석 근거)
- `include/decompiler.h` — IrOpcode 28, IrType 14, IrInstr/IrBlock/IrFunc 레이아웃
- `include/hir.h` — HirNodeKind 26, HirEmissionStats, HIR_COMMENT(Pre-1), HIR_EXPR_TERNARY
- `src/disasm/capstone_wrapper.c:60-68` — CS_MODE_ARM 하드코딩
- `src/disasm/indirect_resolver.c` — 3-패턴 한정(rip-rel/vtable/x86 jmptbl 8byte)
- `src/core/recursive_disasm.c` — worklist 기반 DFS, noreturn 하드코딩
- `src/decompiler/codegen.c:430-432, 524-552, 2190-2253, 2320-2350` — last_cmp_* / LIFT_BINOP / ir_optimize / opcode_name
- `src/decompiler/arm64_lifter.c:127` — silent CMP_NE fallback (flag-only cond)
- `AUTOMATION_ROADMAP.md` — Phase 2-A/2-B 완주 상태

### 연구 문서 (본 프로젝트 `docs/research/`)
- `ghidra_disasm_analysis.md` (#27) — SLEIGH, JumpModel 4-class, M-1 Low-IR 제안
- `ghidra_disasm_decompile_bridge_analysis.md` (#28) — PCode 90-op, Varnode, universalAction, R-S1/S2/S3
- `rizin_disasm_analysis.md` (#31) — RzAsm/ELF split, jmptbl 4-dispatch, mapping symbol, S-A/B/C/D
- `rizin_il_analysis.md` (#32) — **주 참고**: RzIL Core Theory 82 opcode, Bitvector sort, opbuilder macros, 8 단계 Phase A/B/C 전환 비용(~7500 LOC, 13-19 세션)
- `x64dbg_analysis.md` (#33) — patternfind/ZydisTokenizer 분석; IR 레이어 없음 → 본 문서에서는 참조 최소

### 외부 (알고리즘·네이밍 참조만, code copy 없음)
- Rizin `librz/il/` (LGPL-3), `librz/arch/p/analysis/jmptbl.c` — 4-dispatcher 패턴
- Ghidra `Ghidra/Features/Decompiler/src/decompile/cpp/op.cc`, `action*.cc` (Apache-2) — universalAction group
- Cytron et al., "Efficiently Computing Static Single Assignment Form" (TOPLAS '91)
- Cooper et al., "A Simple, Fast Dominance Algorithm" (2001)
- BAP Core Theory: Brumley et al., "BAP: A Binary Analysis Platform" (CAV '11)

---

_끝._
