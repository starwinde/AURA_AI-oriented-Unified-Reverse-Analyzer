# Ghidra 디스어셈블러 ↔ 디컴파일러 브리지 (lifting + PCode) 재분석

Session #9 (2026-04-20), Phase 2-E 병렬 연구 — Task #28 (bridge-analyst).
자매 task: #26 ghidra-analyst (func detect / pipeline), #27 disasm-analyst (SLEIGH / sweep).

---

## 1. Executive Summary

AURA 디컴파일 품질의 근본적 상한은 "asm → IR" 브리지 레이어에서 결정된다. Ghidra 는 이 레이어를 **SLEIGH 명령 스펙 → 대략 90개의 PCode operation → Funcdata 위의 universalAction 파이프라인** 으로 3 계층 분리해 운영하며, 각 계층이 독립적으로 진화하게 설계되어 있다. AURA 는 **Capstone 의 mnemonic + operand string → C 서브셋 IrOpcode (약 30개) → 단일 fixpoint PassManager** 로 압축해 구현했다. 그 결과 lifting 코드는 간결하지만 (codegen.c 2438 LOC + arm64_lifter.c 1449 LOC), 고급 디컴파일 기법이 들러붙을 표면적이 구조적으로 좁다.

본 재분석에서 파악한 브리지 레이어의 **핵심 격차** 3–5:

1. **IR 자체의 semantic 해상도**: AURA IrOpcode 에는 signed vs unsigned 산술 구분 (INT_SDIV/INT_SREM), zero/sign 확장 (INT_ZEXT/INT_SEXT), carry/borrow (INT_CARRY/SCARRY/SBORROW), bit-extract (SUBPIECE/PIECE), 그리고 float-family 전체가 **독립 opcode 로 존재하지 않는다**. FLOAT*는 IrType 에만 흔적이 있고 IR_OP_ADD 등 정수 opcode 를 공유하므로, 상수 폴딩/type propagation 규칙이 혼동한다.
2. **Flag / condition-code 추상화 부재**: Ghidra 는 EFLAGS/NZCV 를 1-bit register varnode 로 lift 한 뒤 optimization 이 소멸시키는 **explicit lazy flag** 모델을 채택. AURA 는 `last_cmp_src0/src1/id` 스칼라 3 개 (codegen.c:430–432) 로 직전 cmp/test 만 기억하는 **eager-but-single-slot** 모델이라, 두 비교 사이에 비교 흔적을 잃는 코드 (e.g. `cmp; <비플래그 명령>; cmp; cmov`) 에서 의미 손실 발생. RC-2 S2–S6 이 이 구멍을 메우려는 일련의 시도이다.
3. **Address space 개념 실종**: Ghidra Varnode 는 `(space, offset, size)` 3-tuple 로 register / ram / constant / unique / stack 을 동등하게 다룬다. AURA IrVal 은 `(id, type, imm)` 뿐이며, 메모리 참조는 `IR_OP_LOAD/STORE` 의 피연산자가 `IR_TYPE_PTR` 이라는 약한 타입 힌트만으로 구분된다. 결과적으로 alias analysis / stack analysis 가 별도 파일 (alias_analysis.c, stack_analysis.c) 에서 IR 바깥의 보조 정보로 존재하며, IR 변환과 함께 refine 되지 않는다.
4. **Pass chain 깊이**: Ghidra 의 universalAction 은 수십 개 Action + 수백 개 Rule 로 구성되어 있고 그룹화된 순서로 여러 차례 반복된다. AURA 의 PassManager 는 **단일 fixpoint (최대 5 반복)** + 하드코딩된 10 여개 pass (codegen.c:2209–2232), 그 뒤에 out-of-SSA (reg coalesce, phi elim) 와 tail-call 이 one-shot 으로 붙는다.
5. **HIR 구조화의 의존성**: Ghidra 는 PCode 위에서 직접 block-structuring 을 수행. AURA 는 IrFunc → HirFunc 의 2-IR 모델로, HIR build 가 post-dominator 에 강하게 의존 (hir_builder.c emit_region) 하여 post-dom 이 비정상이면 goto fallback 으로 즉시 떨어진다 (HirEmissionStats.gotos_emitted 계측).

**가장 큰 parity 레버 3**:
- **L1 — IrOpcode 확장** (unsigned 산술 + zext/sext + signed compare 유지 + carry family). 예상 +Δ: 디컴파일 정확도 +8~12% (IR 해상도 자체가 하류 전부에 영향, B-2 type propagation 로그가 이미 타입 혼동의 증거). 난이도: **중**.
- **L2 — Flag-as-varnode 모델로의 리팩터** (또는 최소한 `last_cmp_*` 를 퍼-블록 stack 으로 확장). 예상 +Δ: cmov/setcc/csel 정확도 +15~20%, 현재 silent CMP_NE fallback (arm64_lifter.c:127) 이 주된 false branch 원천. 난이도: **중-상**.
- **L3 — Pass chain 을 "그룹 기반 반복" 으로 재설계** (stackflow → base → blockrecovery → typerecovery → cleanup → merge 의 Ghidra 스타일). 예상 +Δ: covered_avg plateau 55 (real_binary_parity_2026_04_18) 를 구조적으로 상향, +5~8%. 난이도: **상**.

---

## 2. Ghidra PCode 심층

### 2.1 PCode operation set

Ghidra `PcodeOp` 클래스는 **약 90개** 의 opcode 상수를 정의한다 (v11.x 기준). 기능별 분류:

| 그룹 | opcode (mnemonic) | 공통 semantic |
|------|-------------------|----------------|
| Copy/Move | `COPY`, `LOAD`, `STORE` | varnode 복사 및 메모리 I/O. LOAD/STORE 는 첫 인자가 address-space id |
| Control flow | `BRANCH`, `CBRANCH`, `BRANCHIND`, `CALL`, `CALLIND`, `RETURN`, `CALLOTHER` | BRANCH 는 직접/조건/간접 구분. CALLOTHER 는 `pcodeop`(user-defined) 훅 |
| Int arith | `INT_ADD`, `INT_SUB`, `INT_MULT`, `INT_DIV`, `INT_SDIV`, `INT_REM`, `INT_SREM`, `INT_NEGATE`, `INT_2COMP` | unsigned vs signed 분리 |
| Int compare | `INT_EQUAL`, `INT_NOTEQUAL`, `INT_LESS`, `INT_LESSEQUAL`, `INT_SLESS`, `INT_SLESSEQUAL` | unsigned 기본, `S` prefix = signed |
| Bitwise | `INT_AND`, `INT_OR`, `INT_XOR`, `INT_LEFT`, `INT_RIGHT`, `INT_SRIGHT` | SRIGHT = arithmetic shift right |
| Size change | `INT_ZEXT`, `INT_SEXT`, `PIECE`, `SUBPIECE` | zero/sign extend + 연결/절단. Ghidra 는 크기 변환을 **opcode 수준** 에서 분리 |
| Carry/overflow | `INT_CARRY`, `INT_SCARRY`, `INT_SBORROW` | 플래그 recovery 전용 |
| Boolean | `BOOL_AND`, `BOOL_OR`, `BOOL_XOR`, `BOOL_NEGATE` | 1-bit varnode 전용 (flag merge) |
| Float | `FLOAT_ADD/SUB/MULT/DIV/NEG/ABS/SQRT`, `FLOAT_EQUAL/NOTEQUAL/LESS/LESSEQUAL/NAN`, `FLOAT_INT2FLOAT`, `FLOAT_FLOAT2FLOAT`, `FLOAT_TRUNC`, `FLOAT_CEIL`, `FLOAT_FLOOR`, `FLOAT_ROUND` | 17 개 |
| Specialized | `POPCOUNT`, `LZCOUNT`, `NEW`, `CPOOLREF`, `SEGMENTOP`, `UNIMPLEMENTED` | `NEW`/`CPOOLREF` 는 JVM 류 bytecode |
| High (post-SSA) | `MULTIEQUAL`, `INDIRECT`, `PTRADD`, `PTRSUB`, `CAST`, `EXTRACT`, `INSERT` | MULTIEQUAL = φ. INDIRECT = call side-effect placeholder. PTRADD/PTRSUB = typed 포인터 연산 (high PCode 전용) |

참고 자료:
- `PcodeOp` javadoc (ghidra.re ghidra_docs/api/ghidra/program/model/pcode/PcodeOp.html)
- P-Code Reference Manual (spinsel.dev 미러)
- 소스: `Ghidra/Features/Decompiler/src/decompile/cpp/op.hh`, `opcodes.hh`, `typeop.hh`

### 2.2 Varnode 및 AddressSpace

Varnode = `(AddressSpace, offset, size)` 의 immutable 3-tuple. Decompiler 내부에서는 `Varnode *` 가 SSA value 역할 (`defOp()`, `descendList` 로 def-use 쌍방 탐색).

**AddressSpace 타입**:
- `register` — 아키텍처 register file. x86_64 의 `RAX` 는 `register:0:8` 같은 offset 으로 표현.
- `ram` — 주 메모리. `LOAD (ram_id, addr)` 로 실제 메모리 로드.
- `constant` — 상수 리터럴. 모든 immediate 는 `(constant, value, size)` varnode.
- `unique` — SLEIGH 내부 temporary. 한 명령어 내부에서만 살아있고 lifter 가 자유롭게 발급.
- `stack` — 스택 프레임 전용 (`ActionStackPtrFlow` 후 승격). 원래는 `ram` 으로 들어온 것을 분석이 분리.

이 모델의 장점은 **alias 관계가 address space 로 먼저 분할되므로** alias analysis 가 자연스레 space 별로 수행된다는 점이다. AURA 에는 이 구분이 없다 (§4.2 참조).

### 2.3 SLEIGH → PCode 변환

SLEIGH 는 Ghidra 의 instruction-spec DSL. 각 프로세서의 `*.slaspec` 이 컴파일되어 `.sla` 가 되고, 실행 시 `Emulate` / `Sleigh` 객체가 **instruction → PCode sequence** 로 expand 한다.

```
  ADD EAX, EBX
  ↓ (SLEIGH pattern match)
  tmp = INT_ADD EAX, EBX          // 32-bit
  CF  = INT_CARRY EAX, EBX        // flag recovery
  OF  = INT_SCARRY EAX, EBX
  ZF  = INT_EQUAL tmp, 0
  SF  = INT_SLESS tmp, 0
  EAX = COPY tmp
```

한 명령이 평균 4~8 PCode op 로 unfold. "flag 계산을 먼저 전부 emit 하고 나중에 소멸시키는" 전략의 기반.

### 2.4 PCode injection / custom op

Ghidra 는 다음 두 가지 확장 점을 제공:
- **pcodeop (`CALLOTHER`)**: SLEIGH 에서 `pcodeop rdtsc;` 같이 선언 → CALLOTHER opcode 로 escape. 추후 `pcode-injection` XML 로 대체 구현 주입.
- **Custom action / rule**: 디컴파일러 C++ 에 사용자가 Action 을 addAction() 으로 끼워넣을 수 있음 (processor-specific 룰이 `*_rules.xml` 로 선언).

이는 decompilePlugin 의 "custom processor" 확장 경로이며 AURA 에는 대응 개념이 없다 (PRD §4.1 플러그인 유보).

---

## 3. Ghidra 디컴파일러의 PCode consumer

### 3.1 Pass chain 전체

Ghidra decompiler 의 파이프라인은 `Funcdata` 객체를 중심으로 `ActionDatabase::universalAction()` (coreaction.cc) 이 구성한 Action 시퀀스를 반복 실행한다. 공개 문서로 확정 가능한 **대분류 그룹 순서** (deepwiki + action.hh):

1. **universal/base** — SSA 준비 (ActionStart, ActionRestrictLocal, ActionNormalize, ActionDeindirect)
2. **stackvars** — ActionStackPtrFlow (스택 포인터 변화 해결 → stack space 승격)
3. **blockrecovery** — 블록 병합, 반복되지 않는 edge 처리
4. **typerecovery** — ActionInferTypes (DataType propagation, 반복적)
5. **forcegoto** — irreducible edge 를 goto 로 격하
6. **control-structure** — if/while/for/switch 복원 (StructureBlock)
7. **cleanup** — RuleEarlyRemoval, RuleSelectCse, RuleCollectTerms 등 Rule 기반
8. **merge** — HighVariable consolidation (여러 Varnode 를 하나의 "C 변수" 로 통합)
9. **dynamic** — 최종 출력 준비

각 그룹 내부에는 수십 개의 Rule (pattern-match 기반 rewrite) 이 ActionPool 에 수집되어 fixpoint 로 반복 적용된다. 총 Rule 개수는 `Ghidra/Features/Decompiler/src/decompile/cpp/ruleaction.cc` 하나에만 **약 150+** 있음 (파일 scan 기준).

### 3.2 Type inference / DataType propagation

`ActionInferTypes` 의 알고리즘은 반복적 meet-based lattice propagation:
- 각 Varnode 에 `Datatype *` 초기 값 부여 (레지스터 기본 → int\<N\>)
- SLEIGH 가 hint 한 타입, 호출 규약의 파라미터 타입, 구조체 필드 등을 **seed** 로 배치
- INT_ADD dst 의 타입 = lattice_meet(src0.type, src1.type)
- PTR arithmetic 은 `PTRSUB`/`PTRADD` high-opcode 로 변환되며 이는 타입 추론을 피드백한다
- 반복 수렴 (수십 iter 가능)

AURA `type_inference.c` (513 LOC) 는 유사한 철학 (type_wider meet) 이지만 PTR 전파와 int-width 전파를 Pass 2 로 분리한 **경량** 버전. `type_constraint.c` (884 LOC) 는 B-2 에서 array-stride hint 같은 추가 seed 를 얹은 구조이며, B-2 INFO 로그가 가시화한 바로는 여전히 "가장 넓은 타입 승" 휴리스틱 수준.

### 3.3 Structural analysis

Ghidra 는 `BlockGraph` 위에 if/while/switch/goto 를 복원. 특징:
- Post-dominator tree 기반 (sa_compute_postdom 과 동일 방향)
- Irreducible 영역은 `forcegoto` 그룹에서 label+goto 로 emit
- Loop analysis 는 dominator + natural-loop 로 초기 탐지 후 **Tarjan SCC** 로 irreducible loop 포착 (AURA loop_detect.c 도 유사하나 단순화됨)

### 3.4 Variable naming

Ghidra 는 다음 순서로 변수명을 결정:
1. HighSymbol (PDB/DWARF 등 외부 symbol)
2. StackFrame offset → `local_XX` / `param_X`
3. Register-bound high variable → `iVar1`, `uVar2` prefix + 타입 약어
4. 사용자 rename (DB 저장)

AURA 는 hir_builder/hir_emit 가 직접 `a0`, `v123`, `var_N` 로 명명 (hir_emit_set_stack_frame 가 stack frame 기반 이름에 기여).

---

## 4. AURA 브리지 레이어 심층

### 4.1 IrOpcode coverage

`include/decompiler.h:79-132` 기준, AURA 의 IrOpcode **총 28개** (IR_OP_UNSUPPORTED 포함):

```
COPY, CONST, ADD, SUB, MUL, DIV,
AND, OR, XOR, SHL, SHR,
CMP_EQ, CMP_NE, CMP_LT, CMP_LE, CMP_ULT, CMP_ULE,
CMP_GT, CMP_GE, CMP_UGT, CMP_UGE,        (RC-2 S3 로 추가)
LOAD, STORE,
BRANCH, JUMP, CALL, RET,
PHI, SELECT,                             (A-8 로 SELECT 추가)
UNSUPPORTED                              (RC-1 silent drop 방지 sentinel)
```

Lifter 파일:
- **x86/x86_64**: `src/decompiler/codegen.c:369` (ir_lift) — mnemonic 문자열 비교 + LIFT_BINOP 매크로 (add/sub/imul/and/or/xor/shl/shr/sar), mov 류, setcc family (cond 접미사 → CMP opcode, setcc re-emit), cmovcc → SELECT + fresh CMP, bit manipulation (bswap/bsf/bsr/popcnt/lzcnt/tzcnt) 는 **COPY 로 fallback** (2438 LOC). MMX/SSE/AVX/AVX-512 탐지는 IrType 층만 (VEC128/256/512) — 실제 semantic 은 COPY.
- **AArch64**: `src/decompiler/arm64_lifter.c:1` — mov/movz/movk, add/sub/mul, ldr/str/ldp/stp, bl/blr/b/ret, cmp/cbz/cbnz, b.cond, csel/csinc (1449 LOC). flag-only suffix (mi/pl/vs/vc/al/nv) 는 CMP_NE fallback (silent, L2 의 근본 원인).
- **MIPS / PowerPC / RISC-V / Dalvik**: mips_lifter.c / ppc_lifter.c / riscv_lifter.c / dalvik_lifter.c — 각각 최소 집합 (mov, arith, mem, branch).

### 4.2 IrVal / IrType / IrBlock 설계

```c
typedef struct { uint32_t id; IrType type; int64_t imm; } IrVal;
```

- **id**: 함수 전역 유일한 SSA value ID. 단일 def 원칙.
- **type**: 14 enum (VOID/INT8/16/32/64/PTR/BOOL/FLOAT/DOUBLE/LONG_DOUBLE/VEC128/256/512/MMX).
- **imm**: op == IR_OP_CONST 일 때만 유효한 out-of-band 상수.
- **address space 필드 없음** — LOAD/STORE 에서 src0 의 `type == IR_TYPE_PTR` 로 "메모리 주소" 임을 암시.

IrBlock 에는 Ghidra 에 없는 AURA 전용 필드 `def_reg_mask` (decompiler.h:261) 가 있어 Phase F Q-3 에서 레지스터 단위 Cytron phi 배치를 뒷받침한다.

### 4.3 AURA 최적화 pass 목록

`src/decompiler/codegen.c:2190` (ir_optimize) 에서 PassManager 에 등록되는 순서:

| # | 패스 이름 | 파일 | 역할 |
|---|-----------|------|------|
| 1 | sccp (const_propagate) | const_prop.c | 상수 전파 |
| 2 | const_fold | codegen.c:2001 | 상수 접기 (CONST op CONST → CONST) |
| 3 | copy_prop (기본) | codegen.c:2036 | 단순 COPY use 치환 |
| 4 | copy_prop_enhanced | copy_prop.c | SSA-aware 강화판 |
| 5 | expr_simplify | expr_simplify.c | x + 0, x - x, x * 1 등 |
| 6 | expr_reassoc | expr_reassoc.c | 결합법칙 기반 재배열 |
| 7 | cse | cse.c | 공통 부분식 제거 |
| 8 | cond_simplify | cond_simplify.c | 조건식 정리 |
| 9 | dead_code | dead_code.c | 코어 DCE |
| 10 | dce | codegen.c:2065 | 보조 DCE (SSA def-use) |
| 11 | dead_store | dead_store.c | unused STORE 제거 |
| 12 | licm | licm.c | Loop Invariant Code Motion |
| 13 | strength_reduce | strength_reduce.c | x*2 → x<<1 등 |

PassManager fixpoint 최대 5회 반복 (pass_manager.c:24, PASS_MANAGER_MAX_ITERS).

One-shot 후처리 (fixpoint 이후 1회):
14. `reg_coalesce` — 레지스터 합침
15. `phi_elimination` — SSA 해제
16. `tail_call` — CALL+RET 패턴 변환

**합산: 16 pass**. Ghidra 의 ~100+ pass 대비 약 1/6. PRD에 "미래에 확장" 의도로 PassManager 만 프레임화된 상태.

### 4.4 control_flow.c → IrFunc 생성 보조

`control_flow.c:44` (844 LOC) 는 IrFunc 가 이미 존재한다고 가정하고 **pseudo-C 직출력** 을 담당. pattern matching (if / if-else / while / do-while / switch / for) + DFS 기반 loop header 감지. Ghidra 의 `BlockGraph` 에 해당하지만 훨씬 가벼운 "print 시점 구조화" 방식이다. HIR 모델로 이관된 후에도 control_flow.c 는 legacy emit 경로로 여전히 사용된다.

---

## 5. Layer-by-layer 비교표

| Ghidra | AURA | Gap | 파일 |
|--------|------|-----|------|
| SLEIGH `*.slaspec` / `.sla` | Capstone mnemonic+operand string | AURA 는 SLEIGH-free; lifter 가 mnemonic 문자열 비교로 직접 case-by-case 분기 | third_party/capstone/, codegen.c:458+ |
| `Emulate` / `Sleigh` (PCode emitter) | `ir_lift` / `ir_lift_arm64` / `ir_lift_*` | 명령 → 4~8 opcode vs 명령 → 1~2 opcode. flag unfold 없음 | codegen.c:369, arm64_lifter.c 전체 |
| `PcodeOp` (90+ opcode) | `IrOpcode` (28) | INT_SDIV/SREM, ZEXT/SEXT, PIECE/SUBPIECE, CARRY*, FLOAT_*, BOOL_*, MULTIEQUAL (=PHI) 만 대응, 나머지 격차 | include/decompiler.h:79-132 |
| `Varnode (space, offset, size)` | `IrVal (id, type, imm)` | address space 개념 실종 (§4.2) | include/decompiler.h:149-153 |
| `AddressSpace` (register/ram/constant/unique/stack) | LOAD/STORE 의 `IR_TYPE_PTR` 힌트만 | AURA 는 alias/stack/register 를 type 1개로 flatten. alias_analysis.c 가 외부 정보로 존재 | src/decompiler/alias_analysis.c |
| `Funcdata` (모든 상태 중앙 허브) | `IrFunc` + `HirFunc` (2-IR) + 다수 분산 struct | AURA 는 분석 결과 (ParamId, StructRecovery, EhFrame, StackFrame) 를 각 pass 가 개별 인자로 전달 | hir_builder.c 인자 목록 |
| `ActionInferTypes` | `ir_infer_types` + `type_constraint.c` | AURA 는 2-pass meet, seed 범위 좁음 | type_inference.c, type_constraint.c |
| `ActionStackPtrFlow` | `stack_analysis.c` (C-3) | AURA 는 post-hoc, IR 외부. Ghidra 는 IR 내부에서 space 승격 | src/decompiler/stack_analysis.c |
| `BlockGraph` structuring | `structural_analysis.c` + `hir_builder.c` | 알고리즘 동등 (Cooper post-dom) 이나 irreducible 처리 범위 좁음 | structural_analysis.c, goto_elimination.c |
| `HighVariable` / `HighSymbol` | `HirLocal` / `HirParam` + hir_var.name | consolidation 로직 얕음, 사용자 rename DB 없음 | hir.h:253-273 |
| Rule-based rewrite (150+) | expr_simplify + expr_reassoc + strength_reduce + cond_simplify | Rule 수가 1-2 자릿수 | expr_simplify.c, expr_reassoc.c, strength_reduce.c, cond_simplify.c |
| Action group 반복 (여러 차례) | PassManager 단일 fixpoint (max 5) | 그룹 단위 반복 없음 | pass_manager.c:24,74 |
| `PTRADD`/`PTRSUB` (typed 포인터 연산) | 일반 ADD/SUB + dst_pointee_width (F-1-T) | pointee width 만 opt-in 추적, opcode 분리 없음 | decompiler.h:200-213 |
| `MULTIEQUAL` (high phi) / `INDIRECT` | `IR_OP_PHI` / (없음) | INDIRECT 대응 없음 → CALL side-effect 명시화 부족 | include/decompiler.h:121 |
| `CAST` | HirCast node (HIR only) | IR 레벨 cast 없음 → type coercion 이 암시적 | hir.h:66 |
| `pcodeop` / CALLOTHER | (없음) | 사용자 정의 intrinsic 확장점 없음 | — |

---

## 6. 기법별 심층 비교

### 6.1 Instruction semantic coverage

**x86/x86_64**:
- AURA: mov/movzx/movsx/movsxd/lea, add/sub/imul/and/or/xor/shl/shr/sar, neg/not/inc/dec, setcc/cmovcc (modern RC-2 처리), bswap/bsf/bsr/popcnt/lzcnt/tzcnt (all **COPY fallback** — 의미 소실), cmp/test, jcc, call, ret, push/pop.
- 누락: **x87 stack ops** (fld/fst/fadd/fmul/fdiv), **AVX/AVX-512 연산** (vaddps, vmulpd 등 packed FP), **SIMD 정수 연산** (paddb/pmullw/pcmpeqb), **atomic/lock-prefixed ops**, **string ops** (rep movsb/stosb/scasb, cld/std), **system ops** (syscall, sysenter, cpuid, rdtsc), **cmpxchg/xadd**, **bound/enter/leave**, **bit field** (bt/bts/btr/btc), **rotate** (rol/ror/rcl/rcr).
- Ghidra 는 위 전부를 PCode 로 lift (일부는 CALLOTHER 로).

**AArch64**:
- AURA: mov/movz/movk, add/sub/mul, ldr/str/ldp/stp, b/bl/blr/ret, cmp/cbz/cbnz, b.cond, csel/csinc, prologue (PAC/BTI 인식하여 주석화), ABI 인자 seeding (x0-x7 → SSA id 0-7).
- 누락: **NEON SIMD** (add/mul/mla, ld1/st1), **FP/HP scalar** (fadd/fmul/fcvt), **atomic/LSE** (ldadd, swp, cas), **exclusive** (ldxr/stxr), **crypto** (aese/aesd), **system reg** (mrs/msr), **pointer auth full semantic** (현재는 주석만).

**공통**:
- Carry/overflow flag 는 어느 ISA 에서도 recovery 안 됨 (INT_CARRY 류 부재).
- ZEXT/SEXT 가 independent opcode 가 아니라 mov-family 에 숨어있음 → type propagation 이 width 변화 추론 어려움.

### 6.2 Flag tracking

**Ghidra**: flag 를 1-bit register varnode 로 SLEIGH 가 lift → BOOL_AND/OR/XOR/NEGATE 로 합성/소멸 → 미사용 flag 는 DCE 가 제거. 그 결과 "3 단계 이전의 CMP" 도 명시적 def-use chain 으로 남아 `cmov` 가 정확히 그 CMP 를 참조.

**AURA**: codegen.c:430-432 의 3 스칼라 `last_cmp_id`, `last_cmp_src0`, `last_cmp_src1` 만 기억. 각 블록 시작 시 reset. cmp/test 이후에 비비교 명령이 낀 뒤 다시 cmp 가 오면 이전 값은 **overwrite**. setcc/cmovcc 는 "직전 cmp" 를 가정한 re-emit (L2 에서 근본 원인).

**정량**: 실 바이너리에서 "cmp; <intervening>; setcc/cmovcc" 패턴 빈도 추정 10–20% → 해당 비율만큼 false branch 가능.

### 6.3 Type inference 깊이

- Ghidra: lattice meet + PTRADD/PTRSUB + seed (param type / struct field / string ref / symbol type), 수십 iter.
- AURA: 2-pass meet (width 전파, PTR 전파), seed 는 레지스터 크기 + LEA pattern 뿐. type_constraint.c (B-2) 가 array-stride hint seed 를 추가한 상태.

Ghidra 대비 AURA type 파이프라인의 **missing seed 종류**:
- LLM / signature DB 가 제공하는 함수 prototype (FLIRT 유사) → AURA 는 func_detect 의 심볼명만 씀
- struct field 타입의 역전파 (field access → base 타입 refine)
- libc/POSIX 함수 인자 타입 (printf family 가 특히 강력)
- DWARF 타입의 IR level injection (현재 AURA 는 pseudo-C 출력 시만 활용)

### 6.4 Pass chain 완성도

표 §4.3 기준 **16 pass, 단일 fixpoint**. Ghidra 대비 결락 차원:

| Ghidra 그룹 | AURA 대응 | 상태 |
|-------------|-----------|------|
| universal/base | sccp + const_fold + copy_prop | ✓ (단순화) |
| stackvars | stack_analysis.c (IR 외부) | △ IR 내부 승격 없음 |
| blockrecovery | CFG reconstruction (cfg.c) | ✓ 다만 B-2 에서 밝혀진 quality bug 있음 (project_quality_bugs_session8) |
| typerecovery | ir_infer_types + type_constraint | △ seed 좁음, 1회성 |
| forcegoto | goto_elimination.c | ✓ |
| control-structure | structural_analysis.c + hir_builder.c | ✓ 다만 post-dom 실패 시 즉시 goto fallback |
| cleanup | expr_simplify/reassoc, strength_reduce, cond_simplify | △ Rule 수 적음 |
| merge | (얕은 HighVariable) | △ |
| dynamic | hir_emit_pseudoc | ✓ |

### 6.5 외부 확장성

- Ghidra: processor-specific rules XML (ARM_rules.xml 등), pcodeop injection XML, Action addAction API, Java plugin (FID, Reversing GLue 등).
- AURA: 플러그인 유보 (PRD §4.1). 확장 경로는 IrPass 추가 커밋 외에 없음. 단 pass_manager_add() API 는 heap 등록이라 dlsym/외부 모듈화 기반이 이미 있음 (향후 활용).

---

## 7. 개선 로드맵

각 제안마다 **예상 +Δ parity score / 난이도 / 의존성 / 근거** 기록. Δ 추정 근거는 "real binary covered_avg 55 flat (project_real_binary_parity_2026_04_18)" 을 기준선으로 하여, 해당 기법이 해소하는 구체적 증상 빈도에서 역산.

### 7.1 단기 (1–3 세션)

**R-S1. IrOpcode 확장: unsigned 산술 + zext/sext 분리**
- 추가 opcode: `IR_OP_UDIV`, `IR_OP_SDIV`, `IR_OP_UREM`, `IR_OP_SREM`, `IR_OP_ZEXT`, `IR_OP_SEXT`, `IR_OP_SAR` (기존 SHR 에서 signed 분리).
- 수정 파일: decompiler.h (enum), codegen.c (lifter + const_fold), arm64_lifter.c, 각 pass (expr_simplify 등 에서 opcode handling).
- 예상 Δ: **+4~6%** (div/rem 오판 제거 + sign-extend 구분으로 INT32 → INT64 승격 시 값 왜곡 방지).
- 난이도: **중** — enum 확장은 쉽지만 모든 pass 를 touch.
- 의존성: 없음 (B-2 이후 가능).
- 근거: 현재 codegen.c `imul`/`mul` 이 같은 IR_OP_MUL 로 축약됨. div 도 unsigned/signed 구분 없음 → 상수 접기 결과가 signed-wrap 을 잘못 처리.

**R-S2. Flag-aware `last_cmp_*` 를 per-block stack 으로 확장**
- 변경: codegen.c:430 의 3 스칼라 → 블록별 stack (depth 4), 비교 결과를 **BOOL typed IrVal id 로 live 관리**. setcc/cmovcc 는 stack top 을 참조하되 fresh CMP re-emit 대신 **기존 CMP 의 SSA id 공유**.
- 수정 파일: codegen.c (lifter + 전체 cmov/setcc 경로), arm64_lifter.c (csel/b.cond), test suite 업데이트.
- 예상 Δ: **+6~10%** (cmov 뒤 false branch 는 decompile 전체 구조를 왜곡).
- 난이도: **중** — 구조 변경 범위 제한적.
- 의존성: 없음.
- 근거: arm64_lifter.c:125-127 "flag-only suffix → CMP_NE placeholder" 주석이 손실 위치를 명시.

**R-S3. PCode-style high opcode 도입: PTRADD / PTRSUB**
- 추가 opcode: `IR_OP_PTRADD (base, idx, stride)`, `IR_OP_PTRSUB (base, off)`.
- 수정 파일: decompiler.h, type_inference.c (pointee propagation 공식화), struct_recovery.c (PTRSUB 기반 field access 탐지), hir_emit (ARRAY_INDEX/FIELD_ACCESS 생성 쉬워짐).
- 예상 Δ: **+3~5%** (struct/array access 에서 HIR_ARRAY_INDEX 생성 정확도 상승, F-1-T dst_pointee_width 의 상위 호환).
- 난이도: **중-상** — type_inference / struct_recovery 의 feedback loop 손봐야.
- 의존성: R-S1 (sext 구분) 이 있으면 정확도 추가 상승.
- 근거: F-1-T dst_pointee_width 가 이미 opt-in 필드로 도입. PTRADD/PTRSUB 는 이를 opcode-level 로 승격한 것.

### 7.2 중기 (3–6 세션)

**R-M1. Address space 개념 도입 (IrVal.space 필드)**
- 추가 enum: `IR_SPACE_REG / RAM / STACK / CONST / UNIQUE`. IrVal 에 1-byte `space` 추가 (구조체 패킹 확인).
- lifter 가 레지스터 참조는 `REG`, 메모리는 `RAM`, LEA rsp+off 는 `STACK` 으로 분류.
- alias_analysis.c 가 space 별로 분리 수행.
- 예상 Δ: **+5~8%** (alias precision 상승 → DCE 공격성 증가).
- 난이도: **상** — IrVal 이진 크기 변경, 전체 파이프라인 재빌드 필요.
- 의존성: R-S1, R-S3 완료 후 권장.

**R-M2. Pass chain 그룹 기반 반복**
- PassManager 에 "group" 개념 추가: 여러 IrPass 를 그룹으로 묶고, 그룹 단위로 fixpoint. 바깥 루프는 그룹 순차 실행.
- 그룹: {base} → {stackvars} → {blockrecovery} → {typerecovery} → {cleanup} → {merge}. Ghidra universalAction 구조 모방.
- 예상 Δ: **+3~5%** (수렴 품질. 현재 fixpoint 5 회는 단일 group 이므로 interaction 제한).
- 난이도: **중** — pass_manager.c 확장만으로 대응 가능.
- 의존성: R-S1/S2/S3 의 pass 들이 늘어난 뒤에 가치가 커짐.

**R-M3. Carry/overflow/zero/sign flag recovery opcode**
- 추가 opcode: `IR_OP_CARRY`, `IR_OP_SCARRY`, `IR_OP_SBORROW`.
- add/sub lifter 가 (dst, cf, of) 3-output 형태로 emit (IrInstr 의 dst 를 single 로 유지하려면 별도 def instruction 추가).
- 예상 Δ: **+2~4%** (multi-word arith, adc/sbb, jc/jo 가 정확해짐).
- 난이도: **상** — IrInstr 는 단일 dst 가정, 다출력 표현 설계 필요.
- 의존성: R-S2 완료 (flag stack 이 bool opcode 의 수요자).

### 7.3 장기 (6+ 세션)

**R-L1. AURA IR 을 PCode-like 형식으로 진화 vs 현행 유지 — 결정점**
- 선택 A: **유지** — IrOpcode 를 점진 확장 (S1/M3 라인), Ghidra opcode 와 1:1 근접하지만 C-like naming 유지.
- 선택 B: **채택** — IrOpcode 를 Ghidra PCode 네이밍/세트로 교체, Varnode-style `(space, offset, size)` 로 전환. 프리젠테이션 레이어 (pseudo-C) 는 변경 없음.
- 비용 (B안): lifter 전면 rewrite (~3000 LOC churn), 모든 pass update, test fixture 재작성. 약 10 세션.
- 편익: 학계/업계 공용어 습득, 향후 Ghidra plugin ecosystem 과의 bridging 기반.
- 권장: **A안** (단기/중기 달성 후 재평가).

**R-L2. SLEIGH-style instruction spec DSL 도입**
- 현재: codegen.c / arm64_lifter.c 의 mnemonic 분기가 수동 작성.
- 대안: AURA 전용 spec DSL (혹은 SLEIGH `.sla` 파일을 읽는 interpreter) → 자동 opcode generation.
- 예상 Δ: **유지보수 품질 +크게, parity Δ 간접** (opcode 누락 속도가 느려짐).
- 난이도: **최상** — 새로운 툴체인.
- 의존성: R-S1/M3 까지의 opcode 확장이 "규모의 한계" 에 닿았다고 확인된 후 (lifter 유지보수 고통이 커진 뒤).

**R-L3. LLM-driven Rule 자동 합성 (실험적)**
- Ghidra 의 150+ Rule 은 전부 손으로 작성됨. AURA 는 Phase 6 LLM 파이프라인을 이미 설계 중 → "decompile 실패 증상 → 규칙 패치" 를 LLM 이 제안하는 실험 가능.
- 난이도: 실험적 (safety / correctness 검증 레이어 필요).

---

## 8. 핵심 제안 top 5 상세 스펙

### 제안 #1 — IrOpcode 확장 (unsigned 산술 + zext/sext + SAR 분리)

**수정 파일**:
- `include/decompiler.h` — IrOpcode enum 에 UDIV/SDIV/UREM/SREM/ZEXT/SEXT/SAR 추가.
- `src/decompiler/codegen.c` — LIFT_BINOP 에 div/idiv/sar 분기 분리, sub-family `movzx`/`movsx`/`movsxd` 를 ZEXT/SEXT opcode 로 교체.
- `src/decompiler/arm64_lifter.c` — `udiv`/`sdiv`/`asr`/`uxtb`/`sxtb` 등 해당 매핑.
- `src/decompiler/const_prop.c` — 접기 규칙 추가 (signed vs unsigned overflow 처리).
- `src/decompiler/expr_simplify.c` — 새 opcode 대응.
- `src/decompiler/type_inference.c` — ZEXT/SEXT 의 dst width 상승 명시화.
- `src/decompiler/hir_emit.c` — 새 opcode → C 연산자 문자열.
- 테스트: `tests/decompiler/` 내 새 opcode 커버리지 + 기존 회귀 확인.

**신규 자료구조**: 없음 (enum 확장).

**API**: 없음 (공개 API 변화 없음).

**테스트 전략**:
1. unit: 각 lifter 마다 새 opcode 가 정확히 emit 되는지.
2. integration: cat/ls 실측 기준 covered_avg 상승 확인.
3. 회귀: 기존 benchmark (regression_harness.sh) 통과.

**예상 commits**: 3–4 (enum + lifter / 접기+simplify / type_inference+emit / 테스트).

### 제안 #2 — Flag stack (cmp history per-block)

**수정 파일**:
- `src/decompiler/codegen.c` — line 430 `last_cmp_*` 3 스칼라 삭제, 대신 per-block `CmpStack cmp_stack` (depth 4, ring buffer). 각 cmp/test 마다 push, cmovcc/setcc 가 top 참조.
- `src/decompiler/arm64_lifter.c` — 동일 패턴.
- `include/decompiler.h` — 필요 시 `CmpRecord` 공개 (대개 static 유지).

**신규 자료구조**:
```c
typedef struct {
    uint32_t cmp_id;     /* CMP instr 결과 SSA id (BOOL type) */
    IrVal    src0, src1; /* cmp 의 원본 피연산자 */
    IrOpcode cmp_op;     /* CMP_EQ/NE/LT/... */
} CmpRecord;
#define CMP_STACK_DEPTH 4
```

**API**: 내부적.

**테스트 전략**:
1. fixture: "cmp; xor rax,rax; setcc" (intervening non-flag 명령) — 현재 false, 제안 후 true.
2. real binary: cat / ls 에서 cmov 빈도 계측, 변환 오류율 측정.

**예상 commits**: 2–3 (x86 경로 / arm64 경로 / 회귀).

### 제안 #3 — PTRADD / PTRSUB high opcode

**수정 파일**:
- `include/decompiler.h` — 2 개 opcode 추가 + dst_pointee_width 와의 관계 명시.
- `src/decompiler/codegen.c` — lifter 에서 `lea` 와 `add rN, rM` (rN 이 PTR) 을 PTRADD 로 emit.
- `src/decompiler/arm64_lifter.c` — `add xN, xM, xK, lsl #N` 패턴 (array index) 을 PTRADD 로.
- `src/decompiler/type_inference.c` — PTRADD dst.type 은 PTR 강제, pointee propagation.
- `src/decompiler/struct_recovery.c` — PTRSUB (base - const) 를 field access 후보로 직접 소비.
- `src/decompiler/hir_emit.c` — PTRADD/PTRSUB 를 HIR_ARRAY_INDEX / HIR_FIELD_ACCESS 로 매핑.

**신규 자료구조**: 없음.

**API**: 없음.

**테스트 전략**:
1. struct fixture: 기존 B-2 array/struct recovery 테스트의 정확도 향상 확인.
2. pointer-heavy real binary (e.g. strace / ls).

**예상 commits**: 4–5 (opcode / lifter / type_inference / struct_recovery + hir_emit / 회귀).

### 제안 #4 — Pass group 기반 PassManager 확장

**수정 파일**:
- `include/pass_manager.h` — `pass_manager_begin_group` / `end_group` API 추가 (또는 `pass_manager_add_group(passes[], count)`).
- `src/decompiler/pass_manager.c` — 내부에 `Group` 배열, 바깥 루프가 그룹 순차 실행, 각 그룹이 자신의 max_iters 가짐.
- `src/decompiler/codegen.c:2190 ir_optimize` — 그룹 선언.

**신규 자료구조**:
```c
typedef struct {
    IrPass  *passes;
    uint32_t count;
    int      max_iters;
    const char *name;   /* "base" / "cleanup" / ... */
} PmGroup;
```

**API 변경**: 하위 호환 유지 — 기존 `pass_manager_add` 는 "default group" 에 추가.

**테스트 전략**:
1. unit: 그룹 순서가 실행 순서를 결정하는지.
2. 품질 지표: covered_avg 변화.

**예상 commits**: 2 (API / ir_optimize 적용 + 회귀).

### 제안 #5 — Flag/carry opcode + multi-output IrInstr 설계

**수정 파일**:
- `include/decompiler.h` — IR_OP_CARRY / SCARRY / SBORROW 추가, 필요 시 IrInstr 에 `extra_dst[2]` 혹은 별도 "flag def" 경량 표현 (2 가지 설계 대안 존재).
- `src/decompiler/codegen.c` — add/sub/adc/sbb/mul/imul 에서 flag def 병발.
- `src/decompiler/arm64_lifter.c` — `adds`/`subs`/`adcs` 처리.
- DCE/copy_prop — extra_dst 인식.

**신규 자료구조 (대안 A)**: IrInstr 의 dst 를 `IrVal dst; IrVal extra_dsts[2];` 로 확장. **대안 B**: carry def 를 별도 `IR_OP_CARRY` instruction 으로 분리 (Ghidra 방식에 더 근접).

**테스트 전략**:
1. multi-word arith fixture (64-bit × 64-bit = 128-bit) — 현재 결과 왜곡 여부 확인.
2. jc/jo 가 의미론적으로 추적되는지.

**예상 commits**: 5–7 (설계 + opcode + lifter × 2 + DCE/prop + 회귀).

---

## 9. Cross-reference

### Task #26 (ghidra-analyst: func detect / pipeline) 와의 overlap 지점

- 본 문서 §3.1 pass chain 그룹 vs #26 의 function boundary / entry-point → **#26 이 universal/base 그룹을 상세, 본 #28 은 typerecovery/cleanup/merge 를 상세**.
- FID / FLIRT signature → #26. 본 문서는 "symbol seed 가 type inference 에 주는 효과" 만 §6.3 에서 인용.
- project_quality_bugs_session8 (function-detection + CFG + hir_builder.c term=NULL bail 3요인 복합) 은 #26 범위. 본 문서는 **그 중 hir_builder term=NULL 을 pass chain 관점에서 참조만**.

### Task #27 (disasm-analyst: SLEIGH / sweep / switch table) 와의 overlap 지점

- SLEIGH 상세 (`.slaspec` 문법, pattern matching) → #27. 본 문서 §2.3 에서는 "SLEIGH → PCode" 1단계만 요약.
- Recursive / linear sweep, switch table recovery → #27. 본 문서는 **lifting 이후의 IR 소비자 경로만**.
- Mixed-mode (ARM/Thumb, x86 16/32/64) → #27. 본 문서 §6.1 instruction coverage 는 단일 mode 전제.

### 3 doc 통합 가이드

- **공통 headline (exec summary)**: 각 문서가 자신의 top 3 격차를 제시 → 통합 시 "lifting 품질의 구조적 상한" 마스터 테이블을 만든다.
- **중복 회피**: PCode / Varnode 정의는 #28 마스터, 심볼/함수 탐지는 #26 마스터, 디스어셈블러 정확도는 #27 마스터.
- **상호참조 포맷**: `§X.Y (Task #NN)` 으로 1차 위치 + 재인용.

---

## 10. Open Questions

- **AURA IR 을 PCode 로 migration 하는 비용/가치**: Phase F~G 동안의 옵션 실험이 필요. 대조실험: 소규모 블록을 PCode 스타일로 재작성 후 품질 Δ 측정.
- **Ghidra 150+ Rule 이식 가능성**: Rule 들 사이의 의존성이 얼마나 강한가? subset 이식이 유의미한 Δ 를 주는가? Phase 2 이후 prototype 세션 1회로 top 20 Rule pick 결과 시험.
- **Address space 도입 시 IrVal 크기 부담**: 현재 12 bytes → 13 bytes (미정렬) 또는 16 bytes (정렬). cache 영향 벤치 필요.
- **SLEIGH 기반 자동 lifter 생성** 이 AURA 의 언어 제약 (C11/C++17) 과 양립 가능한가? — SLEIGH 파서를 C++17 로 작성 가능하지만 spec 생태계 유지가 부담.
- **LLM 이 제안하는 Rule 의 검증 프로토콜** (Phase 6 연동): 어떤 cost model 로 accept/reject?

---

## 11. 인용

### AURA 소스 (핵심)
- `include/decompiler.h` — IrType/IrOpcode/IrVal/IrInstr/IrBlock/IrFunc.
- `include/hir.h` — HirNodeKind/HirNode/HirFunc + HirEmissionStats.
- `include/pass_manager.h` / `src/decompiler/pass_manager.c` — PassManager API + fixpoint 구현.
- `src/decompiler/codegen.c:369 ir_lift` — x86/x86_64 lifter.
- `src/decompiler/codegen.c:2190 ir_optimize` — pass 등록 순서.
- `src/decompiler/arm64_lifter.c:1 ir_lift_arm64` — AArch64 lifter.
- `src/decompiler/type_inference.c`, `src/decompiler/type_constraint.c` — 타입 시스템.
- `src/decompiler/structural_analysis.c`, `src/decompiler/control_flow.c`, `src/decompiler/hir_builder.c` — 구조화.
- `src/decompiler/alias_analysis.c`, `src/decompiler/stack_analysis.c` — IR 외부 분석.

### Ghidra 소스 (참고)
- `Ghidra/Features/Decompiler/src/decompile/cpp/op.hh`, `opcodes.hh` — PcodeOp, OpCode 정의.
- `Ghidra/Features/Decompiler/src/decompile/cpp/varnode.hh` — Varnode 구조 + 필드.
- `Ghidra/Features/Decompiler/src/decompile/cpp/pcoderaw.hh` — raw PCode lifter 인터페이스.
- `Ghidra/Features/Decompiler/src/decompile/cpp/typeop.hh` — opcode → C 연산자 매핑.
- `Ghidra/Features/Decompiler/src/decompile/cpp/coreaction.cc` — universalAction 조립 (공개 자료로는 파일 전체가 너무 커 deepwiki 요약에 의존; 직접 확인 권장).
- `Ghidra/Features/Decompiler/src/decompile/cpp/ruleaction.cc` — 150+ Rule.
- `Ghidra/Features/Decompiler/src/decompile/cpp/funcdata.hh` / `funcdata_varnode.cc` — Funcdata 중앙 허브.

### 웹/문서
- spinsel.dev 미러 — P-Code Reference Manual (opcode 의미 전수).
- ghidra.re ghidra_docs/api `PcodeOp` javadoc — opcode enum 목록.
- grant-h.github.io docs/ghidra/decompiler — Varnode / PcodeOp / Rule class reference.
- ghidra.re docs/languages/sleigh.html — SLEIGH 스펙.
- deepwiki NationalSecurityAgency/ghidra `2-decompiler-system` — Funcdata/Varnode/PcodeOp/Heritage 개요.
- PT SWARM "Guide to P-code Injection" — CALLOTHER 및 pcode-injection 실전.

### AURA 내부 세션 메모리 (참조만, self-contained 를 위해 본문에 중요 결론은 인라인 반영)
- `~/.claude/projects/.../memory/project_real_binary_parity_2026_04_18.md` — covered_avg 55 plateau 관측.
- `~/.claude/projects/.../memory/project_quality_bugs_session8.md` — truncated body 3-factor (function detection + CFG reconstruction + hir_builder term=NULL bail).
- `~/.claude/projects/.../memory/project_v2_3_0_rc1.md` — v2.3.0 Phase 2 로드맵.
