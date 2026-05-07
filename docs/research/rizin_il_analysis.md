# Rizin IL (RzIL) + 디컴파일 브리지 재분석 — 최고 ROI reference

Session #9 (2026-04-20), Phase 2-E 병렬 연구 — Task #32 (rzil-analyst).
자매 task: #30 rizin-func-analyst, #31 rizin-disasm-analyst. 삼각검증 대상: Ghidra #28 bridge-analyst.

---

## 1. Executive Summary

**RzIL 은 Ghidra PCode 의 LGPL-3 오픈소스 재구현이자 — 더 정확히는 — BAP Core Theory 기반의 "PCode 아이디어를 정제한 후계"** 이다. Ghidra PCode 가 SLEIGH 명세에서 기계어 의미를 OCaml 풍 DSL 로 풀어내는 "semantics-as-pattern" 모델인 반면, RzIL 은 **pure / effect 양분 + bitvector 정적 타입 + 명시적 VM state** 의 세 축으로 재구성되어 있다 (rizin/doc/rzil.md). AURA 가 Phase 2-E 이후 "IR 해상도" 를 근본적으로 끌어올리려 한다면, **RzIL 의 설계 조각 (opcode 집합 + effect 분리 + bitvector 타입 + opbuilder 매크로)** 을 **직접 참조** 하는 것이 — Ghidra PCode (GPLv2) 참조 대비 — **라이선스·규모·학습 곡선 모든 면에서 최고 ROI** 다.

**AURA IR vs RzIL 격차 top 3**:

1. **Opcode 해상도**: AURA 28 vs RzIL 약 **82** (70 pure + 12 effect). 불일치의 핵심은 (a) **pure/effect 양분 부재**, (b) **bitvector 폭을 타입 시스템으로 정형화 안 함 (IrType enum 14개 = discrete bucket)**, (c) **float-family 전용 opcode 전체 부재** (RzIL 은 IEEE 754 FADD/FSUB/... + IS_NAN/IS_INF/IS_FINITE 까지 ~30 opcode), (d) **carry/borrow/extract/append (PIECE) 등 bit-level primitive 부재**.
2. **Variable scope/binding 모델**: RzIL 은 **VARG (global, register 바인딩) / VARL (local, SET 로 정의) / VARLP (let-pure)** 의 3 스코프를 명시. AURA IrVal 의 `id/type/imm` 3-tuple 은 scope 개념 없음. 이 부재로 SSA rename 도중 register-bound vs stack-local 이 융합된다 (§4.3 참조).
3. **Effect 조합자 부재**: RzIL 의 `SEQ / BRANCH / REPEAT / BLK / JMP / GOTO` 는 "한 명령 = 여러 effect 를 SEQ 로 묶은 tree" 로 기술된다. AURA IR 은 **flat instruction list + basic block 경계** 로, "한 기계어 → 한 IR instr" 이 주류이고 flag/부수 효과는 버려진다. RzIL 의 SEQ-tree 모델은 **한 ADD 명령이 6 개 flag 업데이트 + 실제 덧셈 + 저장까지 SEQ6 로 한 번에 emit** 한다 (gsoc-2022-x86-il 상세).

**AURA IR 전환 전략 권고 — Option B "점진적 RzIL-shaped 확장"**:
- **clean-slate RzIL fork (Option D)** 는 8–16 세션 규모 + AURA 고유 CFG/HIR 통합이 붕괴할 위험.
- **Option B**: IR_OP_SELECT 를 A-8 에서 추가했던 전례처럼 **opcode 확장을 먼저 (Phase A, 1–2 세션) → Varnode-shaped IrVal 확장 (Phase B, 2–3 세션) → x86/arm64 lifter 재작성 (Phase C, 3–5 세션)** 으로 3 단계 분할. Ghidra #28 의 R-S1/R-S2/R-S3 와 합류.
- 각 단계마다 `covered_avg` (real binary 지표) 회귀 없이 전진. Rizin 자체가 이 점진적 경로를 2021–2025 에 걸쳐 걸어왔다는 점 (ESIL → RzIL migration 이 여전히 **v0.9 대상** 이고, Rizin 2025 summary 기준 완료 아키: SPARC/H8/MIPS) 이 현실적 증거다.

---

## 2. RzIL 설계 심층

### 2.1 Opcode 집합 (70 pure + 12 effect ≈ 82)

RzIL 의 opcode 는 `librz/include/rz_il/rz_il_opcodes.h` 에 `RZ_IL_OP_*` enum 으로 선언되며, 다음 두 계층으로 나뉜다.

**RzILOpPure — 부작용 없는 값 계산 (트리 노드, ~70개)**:

| 카테고리 | 대표 opcode | 비고 |
|----------|-------------|------|
| Boolean (4) | `B0`, `B1`, `INV`, `AND`, `OR`, `XOR` | **BOOL 전용** (1-bit 값). RzIL 은 bool 과 bitvector 를 타입 수준 분리 |
| Bitvector const/move (3) | `BITV`, `CAST`, `APPEND` | `BITV` = 폭이 명시된 상수, `CAST(w,f,v)` = 폭 `w` 로 재형, `APPEND(hi,lo)` = 두 bitvector 연결 |
| Bitvector unary (5) | `NEG`, `LOGNOT`, `MSB`, `LSB`, `IS_ZERO` | `MSB`/`LSB` 는 1-bit Bool 반환 — **flag recovery 의 기초 단위** |
| Bitvector arith (7) | `ADD`, `SUB`, `MUL`, `DIV`, `SDIV`, `MOD`, `SMOD` | unsigned 기본, `S` prefix = signed. `NEG`/`LOGNOT` 은 unary |
| Bitvector logic (3) | `LOGAND`, `LOGOR`, `LOGXOR` | bitvector 대상. BOOL 의 AND/OR/XOR 와 type 수준 분리 |
| Bitvector shift (2) | `SHIFTL(fill,v,dist)`, `SHIFTR(fill,v,dist)` | **fill 비트 parameter** 로 arithmetic/logical 구분 (`SHIFTRA` 매크로는 SHIFTR + fill=MSB(v)) |
| Bitvector compare (3) | `EQ`, `ULE`, `SLE` | 반환은 Bool. NE/UGT/UGE/SGT/SGE 는 `INV(EQ)` / `INV(SLE)` 등으로 파생 |
| Memory (2) | `LOAD`, `LOADW` | `LOAD` = 단일 바이트, `LOADW(w,addr)` = 폭 w bits — address 는 bitvector |
| Control/binding (3) | `VAR`, `ITE`, `LET` | `ITE(c,t,f)` = pure ternary, `LET(name,v,body)` = λ 식 |
| Float tests (6) | `IS_FINITE`, `IS_NAN`, `IS_INF`, `IS_FZERO`, `IS_FNEG`, `IS_FPOS` | 모두 Bool 반환 |
| Float constant/cast (5) | `FLOAT`, `FBITS`, `FCAST_INT`, `FCAST_SINT`, `FCAST_FLOAT`, `FCAST_SFLOAT`, `FCONVERT` | bit-level ↔ semantic float 변환 |
| Float arith (9) | `FADD`, `FSUB`, `FMUL`, `FDIV`, `FMOD`, `FHYPOT`, `FPOW`, `FMAD` (fused MA), `FNEG`, `FABS` | IEEE 754 semantic, 각 연산마다 rounding mode operand |
| Float unary (7) | `FSUCC`, `FPRED`, `FROUND`, `FSQRT`, `FRSQRT`, `FORDER`, `FREQUAL` | Successor/predecessor 는 IEEE 754 finite-precision 전용 |
| Float advanced (6) | `FROOTN`, `FPOWN`, `FCOMPOUND`, `FEXCEPT` | libm-level primitive |

**RzILOpEffect — VM state 전이 (12개)**:

| opcode | 의미 |
|--------|------|
| `EMPTY` / `NOP` | 무효 |
| `SET` | `SETG(name, pure)` / `SETL(name, pure)` — 변수 바인딩 갱신 |
| `JMP` | bitvector 주소로 분기 (indirect) |
| `GOTO` | label 로 분기 (structured) |
| `SEQ` | 두 effect 순차 실행 (Seq2 = `(e1; e2)`) |
| `BLK` | label 로 감싼 effect block |
| `REPEAT` | `REPEAT(c,e)` — 조건 참 동안 반복 |
| `BRANCH` | `BRANCH(c, then_e, else_e)` — 조건 분기 effect |
| `STORE` | 단일 바이트 저장 |
| `STOREW` | 폭 w 저장 |

**총계 개수 근거**: `rz_il_opcodes.h` 에서 WebFetch 로 추출한 enum 값 (§1 hardware table) 을 카테고리별 합산. 72 pure 중복 정리하면 pure ≈ 70, effect 12 = **82 opcode**. Ghidra PCode 90 과 비슷한 order-of-magnitude (PCode 은 MULTIEQUAL/INDIRECT/NEW 등 high-PCode 추가 opcode 포함 시 90+).

### 2.2 Flag / Varnode 모델링

Ghidra PCode 의 "flag = 1-bit register varnode + 소멸 최적화" 전략을 **RzIL 은 더 명시적으로 구현** 한다. x86 의 `ADD EAX, EBX` 가 RzIL 로 lift 될 때 (gsoc-2022-x86-il 블로그 기준):

```scheme
(seq6
  (setl "tmp" (add (varg "eax") (varg "ebx")))
  (setg "cf" (<carry-expr>))          ; CF = carry from MSB
  (setg "of" (<signed-overflow-expr>)) ; OF = operand-sign / result-sign XOR
  (setg "zf" (is_zero (varl "tmp")))   ; ZF = result == 0
  (setg "sf" (msb (varl "tmp")))       ; SF = MSB(result)
  (setg "pf" (<parity-expr>))          ; PF = popcount(low_8) mod 2 == 0
  (setg "af" (<aux-carry-4bit>))       ; AF = carry from bit 3
  (setg "eax" (varl "tmp")))
```

**핵심 특징 3**:
1. **1-bit Bool == flag** — BOOL 타입이 Bitvector 에서 분리되어 있어 `zf = IS_ZERO(tmp)` 는 타입 안전.
2. **각 flag 가 global var** (`SETG "cf" ...`) — 레지스터 파일과 동일 네임스페이스. Dead-flag 제거는 일반 copy/DCE 패스가 자동 수행.
3. **SEQ6 로 한 명령을 트리로 묶음** — lift 단계에서 "한 x86 ADD = 8 개 effect 의 SEQ" 로 표현되고, 실제 소비 (디컴파일러) 는 필요한 것만 남긴다.

**AURA 대비 의미**:
- AURA `last_cmp_src0/src1/id` (codegen.c:430) 는 **non-SSA 3 scalar slot** — 두 cmp 사이에 끼어든 비-flag 명령이 flag 를 덮어쓸 수 있음. RzIL 은 flag 가 SSA 변수라 그 문제가 구조적으로 소거.
- Ghidra #28 R-S2 제안 (per-block CmpStack, depth 4) 는 **타협안** — RzIL 수준 설계를 그대로 도입하면 per-flag global var (cf/of/zf/sf/pf/af 6 개) 를 SSA 로 추가하는 편이 더 일관.

### 2.3 Address space 추상화

RzIL 은 Ghidra PCode 의 5-space 모델 (register/ram/constant/unique/stack) 을 단순화했다. **RzIL 변수 3 종**:

| 종류 | 정의 | 생명주기 | 예 |
|------|------|----------|-----|
| **Global (VARG/SETG)** | 문자열로 식별, 무한 스코프. 레지스터·flag·사용자 지정 | VM lifetime | `"rax"`, `"cf"`, `"sp"` |
| **Local (VARL/SETL)** | SET 으로 정의되는 가변 바인딩. 명령 단위 스코프. 정적 타입 — 재할당 시 타입 충돌 금지 | 한 명령의 lift block 내 | `tmp`, `result` |
| **Let-pure (VARLP/LET)** | 불변, `LET(name, v, body)` 의 body 안에서만 valid | `LET` 식 한 개 | `λx. ...` |

메모리는 "bitvector 로 인덱싱되는 bitvector 배열" — 단일 mem 공간에 모두 통합되지만, **endianness 와 width 가 `LOADW(w, addr)` / `STOREW(addr, val)` 에 명시** 되어 있어 alias/size 혼동이 없다.

### 2.4 Type system (bitvector 위주)

RzIL 은 **정적 강타입** 이지만, C 구현은 OCaml-style `RzILSortPure` 로 dynamic discriminate + static 검증 (`il_validate.c`). 타입 집합:

- `Bool` — 1-bit, `B0`/`B1` 로만 생성.
- `Bitvector (width: N)` — 모든 산술 연산에 N 이 명시되어 있어야 함. `CAST(w, fill, v)` 로 폭 변환.
- `Float (format: F)` — format 은 IEEE 754 half/single/double/quad 등.
- `Memory (key_width, val_width)` — bitvector 배열.
- `Rmode` — rounding mode (float 연산용).

**AURA IrType (14 enum discrete width)** 과의 가장 큰 차이는 **RzIL 은 width 가 타입 파라미터 (`Bitvector<N>`)** 라는 점. 즉 AURA 의 INT8/INT16/INT32/INT64 가 `Bitvector<8/16/32/64>` 하나의 family. 이는 **arbitrary width operand** (24-bit MIPS load, 80-bit x87 LD) 를 자연스럽게 표현.

---

## 3. RzIL 파일 구조 + 주요 API

`librz/il/` 의 파일 구성 (Rizin dev 브랜치 기준):

```
librz/il/
├── definitions/           # RzILOpPure / RzILOpEffect 구조체 정의
├── theory_bitv.c          # Bitvector 의미 (ADD/SUB/SHL/...)
├── theory_bool.c          # Bool 연산
├── theory_effect.c        # SEQ/BRANCH/JMP/GOTO 의미
├── theory_fbasic.c        # Float 기본 연산
├── theory_mem.c           # LOAD/STORE/LOADW/STOREW
├── theory_init.c          # VM 초기화
├── il_opcodes.c           # RZ_IL_OP_* 생성자/파괴자
├── il_vm.c                # 레퍼런스 VM (RzILVM)
├── il_vm_eval.c           # VM step 루프
├── il_graph.c             # IL tree → 그래프 변환
├── il_routines.c          # 함수(라벨 블록) 관리
├── il_reg.c               # register ↔ RzIL global var 매핑
├── il_validate.c          # 정적 타입 검증
├── il_events.c            # VM step trace
├── il_export_json.c       # JSON serialize
├── il_export_string.c     # s-expression print
└── il_export_string_unicode.c
```

**주요 API**:
- `RzILOpPure *rz_il_op_new_add(RzILOpPure *a, RzILOpPure *b)` — IL tree 빌더. (rzil.md)
- `RzILOpEffect *rz_il_op_new_seq(RzILOpEffect *e1, RzILOpEffect *e2)` — effect sequence.
- `RzILVM *rz_il_vm_new(...)` — 레퍼런스 인터프리터.
- `bool rz_il_validate_pure(RzILOpPure *op, RzILSortPure *sort_out)` — 정적 타입 검증.

**opbuilder 매크로 (`rz_il_opbuilder_begin.h`)** — 리프터가 손으로 IL tree 를 짤 때 사용. 핵심 매크로:

```
ADD(x,y)      SUB(x,y)      MUL(x,y)       DIV(x,y)       SDIV(x,y)
LOGAND(x,y)   LOGOR(x,y)    LOGXOR(x,y)    LOGNOT(x)      NEG(x)
SHIFTL(f,v,d) SHIFTR(f,v,d) SHIFTRA(v,d)
AND(x,y) OR(x,y) XOR(x,y) INV(x)           IL_TRUE / IL_FALSE
EQ(x,y)  NE(x,y)  ULT ULE UGT UGE  SLT SLE SGT SGE        FEQ/FNE/FLT/...
MSB(x)   LSB(x)   IS_ZERO(x)       NON_ZERO(x)
UN(w,val) U8/U16/U32/U64     SN(w,val) S8/S16/S32/S64
CAST(w,f,v)  UNSIGNED(n,x)   SIGNED(n,x)   APPEND(hi,lo)
VARG(name)   VARL(name)      VARLP(name)
SETG(n,v)    SETL(n,v)       LET(n,v,body)
LOAD(addr)   LOADW(w,addr)   STORE(a,v)    STOREW(a,v)
ITE(c,t,f)   BRANCH(c,t,f)   REPEAT(c,b)   JMP(tgt) GOTO(lbl) NOP()
SEQ2..SEQ9   SEQN(n,...)
EXTRACT32/64  SEXTRACT32/64  DEPOSIT32/64  BSWAP16/32/64
NOT_IMPLEMENTED
```

**AURA 참조**: codegen.c 가 mnemonic 문자열 + LIFT_BINOP 매크로로 IR 를 build 하는 방식과 구조 동일. **매크로 이름까지 거의 차용 가능** (ADD/SUB/LOGAND/BRANCH 등).

---

## 4. ESIL → RzIL migration 전략 (교훈)

### 4.1 ESIL 의 문제점

Heersin (RSoC 2021 lead) 요약: **"ESIL is neither user friendly nor developer friendly."**

- 스택 기반 (PostScript 풍) — 문자열로 prefix-notation 을 evaluate → 타입 검증 없음.
- Ambiguous weak typing — 같은 토큰이 bitvector/bool 어느 쪽이든 될 수 있음.
- Rizin의 대부분 분석 모듈이 ESIL 기반이었으나, 수년간 누적된 ad-hoc 확장으로 유지 불가.

### 4.2 migration 타임라인

| 연도 | 사건 |
|------|------|
| 2021 RSoC | Heersin + Basstorm 이 RzIL integration PR #1663 착수. Brainfuck → 8051 PoC |
| 2022 GSoC | x86 / ARM32 / ARM64 / AVR / 6502 RzIL lifter 본격 추가 |
| 2023 GSoC | Hexagon, MSP430, PowerPC RzIL 확장 |
| 2024 GSoC | RISC-V Capstone auto-sync + RzIL uplifting (DMaroo), SuperH lifter |
| 2025 | SPARC (Rot127), H8/300 (billow), MIPS (deroad) 추가. Rizin v0.8 release |
| **2026 (진행중)** | v0.9 goal: "Complete migration from ESIL to RzIL for all supported architectures and features" (rizin.re/roadmap). x86 FP 은 여전히 experimental |

**관찰**: Rizin 은 **5년째** migration 중이며, v1.0 에서도 "RzIL specification documentation" 이 목표로 남아 있음. Clean-slate 가 아닌 점진적 교체는 **주요 아키 하나당 1 GSoC 분량 (3-4개월)** 소요됐다.

### 4.3 AURA 에 주는 교훈

1. **Legacy IR 을 즉시 버리지 말라** — Rizin 은 ESIL 코드 경로를 유지하면서 RzIL 을 병렬 추가. AURA 도 IrOpcode 를 union 으로 확장하되 기존 opcode 는 유지.
2. **한 아키씩 점진적** — Rizin 이 ARM → x86 → RISC-V → MIPS 순서로 옮긴 것처럼, AURA 는 **x86_64 먼저 (covered_avg 주된 타깃), 이후 AArch64** 순서.
3. **opbuilder 매크로가 lifter 개발자 경험을 결정** — Rizin 이 ADD/SUB/SETG 매크로 제공 후 lifter 기여가 가속됐다. AURA lifter 에 유사 매크로 도입 선행 권고.
4. **테스트 하네스가 필수** — Rizin `test/db/asm/` 에 arch × mnemonic 매트릭스 테스트가 있음. AURA `tests/decompiler/` 도 opcode 확장 시 fixture 선행 작성.

---

## 5. Decompiler plugins downstream 분석

### 5.1 rz-ghidra — Ghidra 디컴파일러 wrap (LGPL-3)

- **소스**: `github.com/rizinorg/rz-ghidra`
- **IR 소비 경로**: **RzIL 을 전혀 사용하지 않음**. Ghidra C++ 디컴파일러 (`decompile/cpp/`) 를 통째로 싸서, **SLEIGH** 로 직접 disassemble → PCode → Funcdata. Rizin 에서 함수 경계 + 메타정보만 가져옴.
- **출력**: `pdg` (기본 C), `pdgo` (with offsets), `pdgx` (XML), `pdgj` (JSON), `pdgs` (sleigh list).
- **라이선스**: LGPL-3 (Ghidra 는 Apache-2 이지만 plugin 통합이 LGPL-3).
- **품질**: Ghidra 와 동등 — structuring/type inference/naming 모두 Ghidra 알고리즘.
- **AURA 관점**: **RzIL 을 평가할 때 reference 아님**. 오히려 "RzIL 이 Ghidra 수준 디컴파일을 아직 하지 못한다는 증거" — Rizin 은 여전히 Ghidra 품질 필요 시 rz-ghidra 를 추천.

### 5.2 jsdec — JavaScript 디컴파일러 (BSD)

- **소스**: `github.com/rizinorg/jsdec`
- **IR 소비 경로**: **ESIL (legacy IL)** 을 파싱. JavaScript 엔진이 ESIL 토큰 트리를 C-like 의사코드로 재작성. 26개 아키 지원.
- **명령**: `pdd`, `pdda`, `pddj`.
- **Pass chain**: JavaScript 내부에 (1) ESIL parse, (2) 변수/타입 추론 (휴리스틱), (3) control-flow 복원 (pattern match), (4) 출력.
- **품질**: 간단한 함수에는 읽을만한 결과. 복잡한 구조체/루프/예외 처리에서 Ghidra 대비 떨어짐.
- **AURA 관점**: **"IR 위에 얹은 경량 pattern-match 디컴파일러"** 의 대표 사례. AURA 의 hir_emit + control_flow.c 레이어가 실제로 jsdec 과 구조 유사. RzIL 소비하지 않음 → **"ESIL 대체를 위해 만들어진 RzIL 이 정작 JavaScript 디컴파일러에는 아직 적용되지 않음"** = RzIL 의 consumer ecosystem 이 아직 얕다.

### 5.3 rzil-decompiler — 실존 여부 확인

조사 결과: **`rzil-decompiler` 라는 독립 저장소는 rizinorg 에 존재하지 않음** (2026-04-20 검색 기준). GSoC 프로젝트 제안서에는 "visual representation of the IL tree" 같은 목표가 있으나 (GSoC 2023, 2024 페이지), 본격적 RzIL → C 디컴파일러는 아직 공식 프로젝트로 없다. `rz-retdec` (RetDec wrap) 이 유일한 대안 경로.

**의미**: RzIL 은 **디컴파일러의 입력으로 쓰기 위해 설계됐으나, 실제 RzIL consumer 디컴파일러는 아직 부재**. Rizin 커뮤니티는 이를 v0.9 이후 과제로 명시. AURA 가 RzIL-shape IR + 자체 디컴파일러를 완성하면 **오히려 RzIL 보다 앞선다**.

---

## 6. AURA IR vs RzIL 비교표

| 차원 | AURA | RzIL | 격차 |
|------|------|------|------|
| opcode 총수 | 28 | ~82 (70 pure + 12 effect) | ≈ 2.9× |
| pure/effect 양분 | 없음 (모두 flat IrInstr) | 명시적 (`RzILOpPure` vs `RzILOpEffect`) | 설계 격차 |
| 값 타입 | 14 discrete enum (INT8/16/32/64/PTR/BOOL/FLOAT/DOUBLE/LONG_DOUBLE/VEC128/256/512/MMX/VOID) | 4 family (`Bool`, `Bitvector<N>`, `Float<F>`, `Memory<K,V>`, `Rmode`) | width 파라미터화 부재 |
| 변수 scope | 단일 (id) | 3 종 (VARG / VARL / VARLP) | 없음 |
| 메모리 접근 | `IR_OP_LOAD/STORE` + IrType ptr 힌트 | `LOAD` / `LOADW(w, addr)` / `STORE` / `STOREW` | width 명시 부재 |
| Flag 모델 | `last_cmp_*` 3 scalar (non-SSA) | Global BOOL var (`cf`/`of`/`zf`/...) + SET/IS_ZERO/MSB | 구조 격차 |
| Signed/unsigned 분리 | 산술 통합, 비교만 분리 (CMP_LT vs CMP_ULT) | 산술 분리 (SDIV/DIV, SMOD/MOD) + shift fill bit | 부분 격차 |
| zext/sext | 없음 (mov-family 에 묻힘) | `CAST(w, fill, v)` + `UNSIGNED`/`SIGNED` 매크로 | 완전 격차 |
| carry/overflow | 없음 | 없지만 `MSB`/`ITE` 로 휴리스틱 조합 | RzIL 도 미흡 (SEQ-expanded lifter 로 보완) |
| Append/extract | 없음 (대응 opcode 0) | `APPEND(hi,lo)`, `EXTRACT32/64`, `DEPOSIT32/64` | 완전 격차 |
| Float ops | 0 (IrType FLOAT/DOUBLE/LONG_DOUBLE 만 라벨) | 30+ (FADD/...+IS_NAN/IS_FINITE/...) | 완전 격차 |
| Control effect | BRANCH/JUMP/CALL/RET | BRANCH/JMP/GOTO/REPEAT/SEQ/BLK | REPEAT/SEQ/BLK 부재 |
| 정적 타입 검증기 | 없음 (IrType propagation 이 런타임) | `il_validate.c` — sort 일치성 정적 체크 | 완전 격차 |
| 레퍼런스 VM | 없음 (IR 는 실행 대상 아님) | `RzILVM` + `il_vm_eval.c` (emulation / symbolic execution 기반) | 완전 격차 |
| Lifter 매크로 | LIFT_BINOP (codegen.c), ADD/SUB 없음 | `rz_il_opbuilder_begin.h` 전체 세트 | 완전 격차 |

---

## 7. AURA IR 전환 비용 / 편익 분석

### 7.1 비용 총량

| 전환 단위 | 대상 파일 | LOC 영향 | 세션 수 |
|-----------|-----------|----------|---------|
| IrOpcode enum 확장 (28→90) | include/decompiler.h (+ 100 LOC enum) | +100 | 1 |
| opbuilder 매크로 도입 | 신규 `include/aura/ir_builder.h` | +300 | 1 |
| IrVal → (id, sort, imm) — sort 가 Bitvector<N>/Bool/Float<F> family | decompiler.h + 전체 소비자 | ~500 LOC diff | 1–2 |
| Flag-as-SSA-global 변환 | codegen.c 430–450, arm64_lifter.c 전체 | ~300 LOC | 1–2 |
| x86 lifter RzIL-shape 재작성 | codegen.c (2438 LOC) | ~1500 LOC rewrite | 3–4 |
| arm64 lifter 재작성 | arm64_lifter.c (1449 LOC) | ~1000 LOC rewrite | 2–3 |
| Float lifter/semantic 추가 | codegen.c + xmm 처리 | +400 LOC | 1 |
| pass chain RzIL-friendly 재구성 | pass_manager.c, codegen.c:2190 | ~300 LOC | 1 |
| 테스트 (arch × mnemonic 매트릭스) | tests/decompiler/ | +3000 LOC test | 2–3 |
| **합산** | — | **~7500 LOC** (net +3000, replace 4500) | **13–19 세션** |

이는 **"clean-slate RzIL-shape" (Option D) 비용**. Option B (점진적) 는 Phase 단위로 나눠 **8–12 세션** 에 압축 가능.

### 7.2 편익 (real binary parity 기대값)

| 편익 차원 | 정량 지표 | 기대 Δ |
|----------|-----------|--------|
| covered_avg 상승 (real binary parity) | cat 15.8% → 25%+, ls 45.1% → 55%+ | **+10% abs** |
| cmov/setcc 정확도 | arm64_lifter.c:127 silent CMP_NE fallback 제거 | **+15–20%** |
| Float 함수 커버리지 | libm 호출 많은 바이너리 (opus, ffmpeg) | **+30% 함수 커버** |
| Type inference 수렴 속도 | B-2 type_constraint 혼동 로그 감소 | **2× 빠른 수렴** |
| Symbolic execution 가능성 | 레퍼런스 VM 내장 시 fuzz/verify 가능 | **신규 capability** |

### 7.3 위험 요소

1. **IrVal struct 변경의 ABI 영향** — IR 을 인자로 받는 모든 함수 (DFG/SSA/const_prop/copy_prop/type_inference/hir_builder 등) 가 rebuild 대상. 테스트 실패 스파이크 예상.
2. **Pointee width 메커니즘 (F-1-T) 와의 충돌** — AURA 는 `dst_pointee_width` 를 IrInstr 에 붙여 C-5 plumbing 을 달성. RzIL-shape 로 옮길 때 bitvector width 로 대체하되 pointer pointee 는 별도 유지 필요.
3. **HIR 층과의 인터페이스** — hir_builder/hir_emit 가 IrOpcode 를 그대로 C 연산자로 매핑 중. 새 opcode 마다 HIR 대응 필요.
4. **LGPL-3 라이선스 위험** — **RzIL 소스 copy 금지** (Rizin 전체가 LGPL-3). AURA 는 **알고리즘·opcode 이름·설계 철학만 차용**, 구현은 scratch. WebFetch / 공개 블로그 포스트만 참조.

---

## 8. 단계적 전환 전략 (AURA 관점)

### 8.1 Phase A (1–2 세션): IrOpcode 확장 (≤ 50)

**목표**: 기존 IrOpcode (28) 을 "RzIL subset" 로 확장하되 구조는 동일.

**추가 opcode** (RzIL 명명 차용):
- 정수 산술 확장: `IR_OP_UDIV`, `IR_OP_SDIV`, `IR_OP_UREM`, `IR_OP_SREM`, `IR_OP_SAR`, `IR_OP_NEG` (별도).
- 크기 변환: `IR_OP_ZEXT(dst_width, src)`, `IR_OP_SEXT(dst_width, src)`, `IR_OP_TRUNC(dst_width, src)`.
- Bit 조작: `IR_OP_APPEND(hi, lo)`, `IR_OP_EXTRACT(offset, width, src)`.
- Boolean: `IR_OP_BOOL_AND/OR/XOR/NOT` (기존 AND/OR/XOR 는 bitvector 전용으로 재정의, BOOL 은 별도).
- Multi-output: `IR_OP_CARRY/SCARRY/SBORROW` (Ghidra #28 제안 #5 와 합류).

**DoD**:
- `include/decompiler.h` enum 28 → 48 (+20).
- 새 opcode 를 emit 하는 x86 경로 (최소한 movzx/movsx/div/idiv/sar) 가 기존 COPY fallback 을 대체.
- covered_avg 회귀 없음. type_inference 로그에서 SIZE hint 명시화 확인.

### 8.2 Phase B (2–3 세션): Varnode / Address space 도입

**목표**: IrVal 에 sort 정형화.

**구조 변경**:
```c
typedef enum { IR_SORT_BOOL, IR_SORT_BITV, IR_SORT_FLOAT, IR_SORT_MEM, IR_SORT_PTR } IrSortKind;
typedef struct {
    IrSortKind kind;
    uint16_t   width;   /* BITV: bits, FLOAT: IEEE 754 format, PTR: arch addr width */
} IrSort;
typedef struct {
    uint32_t id;
    IrSort   sort;
    int64_t  imm;
} IrVal;
```

- IrType 14-enum 은 IrSort 로 단순 매핑 (INT8 → {BITV, 8}, FLOAT → {FLOAT, 32}, …).
- **Address space 를 IrInstr 에 별도 필드 추가** (register/stack/heap/constant/unique) — Ghidra #28 R-S2 의 구조적 완성.
- Flag 를 **per-function global BOOL SSA slot 6개** (cf/of/zf/sf/pf/af on x86, nzcv 4개 on arm64) 로 승격. `last_cmp_*` 제거.

**DoD**:
- IrVal refactor 후 전체 빌드 통과.
- Flag 를 명시적으로 참조하는 setcc/cmov 경로가 silent fallback 없이 정확.

### 8.3 Phase C (3–5 세션): Lifter 재작성

**목표**: x86 + arm64 lifter 를 RzIL-shape opbuilder 매크로 패턴으로 rewrite.

**새 파일**: `include/aura/ir_builder.h` — `AURA_ADD`/`AURA_SUB`/`AURA_SETG`/`AURA_BRANCH`/... 매크로. 내부적으로 IrInstr emit + fresh SSA id 할당.

**각 기계어를 SEQ 트리로 정의**:
```c
/* x86 ADD rN, rM */
aura_lift_seq(blk,
    AURA_SETL("tmp", AURA_ADD(AURA_VARG(rN), AURA_VARG(rM))),
    AURA_SETG("cf", aura_compute_carry(rN, rM, "tmp")),
    AURA_SETG("of", aura_compute_overflow(rN, rM, "tmp")),
    AURA_SETG("zf", AURA_IS_ZERO(AURA_VARL("tmp"))),
    AURA_SETG("sf", AURA_MSB(AURA_VARL("tmp"))),
    AURA_SETG(rN, AURA_VARL("tmp")));
```

**DoD**:
- codegen.c ADD/SUB/CMP/MOV/MOVZX/MOVSX/SAR/IDIV/DIV 전부 flag-emitting.
- arm64_lifter.c CMP/ADDS/SUBS/CSEL/CSINC 전부 NZCV emit.
- covered_avg 측정: cat +5% 이상, ls +3% 이상.

### 8.4 Phase D (optional): Clean-slate RzIL fork

- **권고: 수행하지 않음**. Phase A–C 로 얻는 편익 대비 비용이 비대칭.
- Phase 6 LLM 과 결합한 실험으로만 여지 남김.

---

## 9. 3-way triangulation (Ghidra PCode + Rizin RzIL + AURA 미래)

Ghidra #28 (bridge-analyst) 의 핵심 제안과 RzIL 실증을 대조:

| Ghidra #28 제안 | RzIL 실증 | AURA 액션 |
|-----------------|-----------|-----------|
| **R-S1** IrOpcode 확장 (UDIV/SDIV/UREM/SREM/ZEXT/SEXT/SAR, carry family) | RzIL 은 SDIV/DIV/SMOD/MOD 분리, CAST(w,fill,v) 로 ZEXT/SEXT 통합, carry 는 MSB+ITE 휴리스틱 | **Phase A** 로 대응. ZEXT/SEXT 는 RzIL CAST 보다 AURA 가 분리 opcode 유지 권고 (type_inference 단순화) |
| **R-S2** per-block CmpStack (depth 4) | RzIL 은 **flag 를 global BOOL SSA** 로 올림 — 더 근본적 | **Phase B** 로 RzIL 경로 채택. CmpStack 은 intermediate step 으로만 |
| **R-S3** PTRADD/PTRSUB high opcode | RzIL 은 pure bitvector 연산만 — PTRADD 없음 (Ghidra 의 독자 아이디어) | Ghidra 권고 유지. RzIL 참조 대상 아님 |
| **R-L1** Action group 기반 pass chain | RzIL 자체에는 pass chain 없음 (IR 정의만) | Ghidra 권고 유지 |
| **R-L2** multi-IR (Low → Mid → High) | RzIL 은 **단일 layer** (high opcode 부재) | AURA 는 IR + HIR 2-layer 유지. RzIL 은 이 점에서 Ghidra 에 비해 단순 |
| **M1** opbuilder 매크로 | `rz_il_opbuilder_begin.h` — **즉시 차용 가능** | Phase C 선행 단계로 `ir_builder.h` 도입 |
| **M3** 정적 타입 검증기 | `il_validate.c` | Phase B 이후 도입 가능 |

**핵심 합의점**:
- **IrOpcode 해상도 상승은 Ghidra·RzIL 모두 일치 권고**.
- **Flag 를 SSA 로 승격** 은 RzIL 이 Ghidra 보다 명시적. AURA 가 둘 중 선택한다면 **RzIL 경로** 가 설계 복잡도 낮음.
- **PTRADD/PTRSUB** 는 Ghidra 독자 고급 기법 — AURA 가 struct recovery 수준까지 가려면 채택 필요, RzIL 은 대응 없음.
- **opbuilder 매크로는 RzIL 에서만 제공** — Ghidra 는 C++ builder 메서드 (`PcodeOpRaw::newUniqueOut(...)`) 로 더 verbose. AURA 는 RzIL 스타일 차용 권고.

---

## 10. 핵심 제안 top 5 상세 스펙 (implementation blueprint)

### 제안 #R1 — `ir_builder.h` opbuilder 매크로 도입 (Phase A 선행)

**수정 파일**:
- 신규 `include/aura/ir_builder.h` (~300 LOC 매크로 + inline helper).
- 구현 `src/decompiler/ir_builder.c` (~200 LOC) — fresh SSA id allocator + IrInstr 배열 append.

**매크로 목록 (RzIL 차용, AURA_ prefix)**:
```c
AURA_ADD(x,y)   AURA_SUB(x,y)   AURA_MUL(x,y)    AURA_UDIV/SDIV
AURA_AND/OR/XOR (bitv)   AURA_SHL/SHR/SAR
AURA_EQ/NE   AURA_ULT/ULE/UGT/UGE   AURA_SLT/SLE/SGT/SGE
AURA_MSB/LSB/IS_ZERO
AURA_VARG(reg)   AURA_VARL(name)
AURA_SETG(reg,v) AURA_SETL(name,v)
AURA_LOAD/LOADW  AURA_STORE/STOREW
AURA_BRANCH/JMP/GOTO   AURA_SEQ2..SEQ8
AURA_ZEXT(w,x)  AURA_SEXT(w,x)  AURA_TRUNC(w,x)  AURA_APPEND(hi,lo)
```

**DoD**: codegen.c 의 LIFT_BINOP 를 `AURA_SETG(dst, AURA_ADD(...))` 로 치환. 기존 테스트 통과. 일관된 리프터 문법 확보.

**예상 commits**: 2 (builder 추가 / lifter 전환).

### 제안 #R2 — Flag global SSA slot 승격 (Phase B)

**수정 파일**:
- `include/decompiler.h`: IrFunc 에 `uint32_t flag_globals[6]` (cf/of/zf/sf/pf/af on x86, nzcv + reserved on arm64) 추가.
- `src/decompiler/codegen.c`: ADD/SUB/CMP/TEST/AND/OR/XOR 에서 `AURA_SETG("zf", AURA_IS_ZERO(tmp))` 등 emit.
- `src/decompiler/arm64_lifter.c`: ADDS/SUBS/ANDS/BICS/CMP/TST 에서 NZCV SET.
- `src/decompiler/const_prop.c`, `dead_code.c`: flag-only def 가 live-out 아닐 때 자동 제거 (일반 DCE 로 sufficient).
- `tests/decompiler/`: flag-round-trip 테스트 (cmp rax, 0; jnz → IS_ZERO(rax) 트리 검증).

**DoD**: cat/ls setcc/cmov 검증 실패율 50% 감소.

**예상 commits**: 4 (x86 경로 / arm64 경로 / DCE 확인 / 회귀 fixture).

### 제안 #R3 — Bitvector sort 통합 (Phase B)

**수정 파일**:
- `include/decompiler.h`: IrType 14-enum 을 `IrSort { IrSortKind kind; uint16_t width; }` 로 refactor. 기존 IrType 은 compat typedef 로 유지하되 내부적으로 IrSort 로 대체.
- 전체 consumer (type_inference, const_prop, hir_emit 등) 는 `sort.kind == IR_SORT_BITV && sort.width == 32` 같은 체크로 교체.

**DoD**: 빌드 통과, 기존 테스트 통과, arbitrary width bitvector 표현 가능 (80-bit x87, 48-bit MIPS load).

**예상 commits**: 3 (struct refactor / consumer 업데이트 / 회귀).

### 제안 #R4 — 정적 IR validator (Phase B 이후)

**수정 파일**:
- 신규 `src/decompiler/ir_validate.c` (~400 LOC). `bool ir_validate_func(const IrFunc *f, IrValidateReport *out)` — 각 IrInstr 의 src sort 가 opcode 요구와 일치하는지 체크.
- `tests/decompiler/test_ir_validate.c` — 의도적으로 망가뜨린 IR 을 주고 올바른 오류 보고 확인.

**DoD**: lifter 변경 후 자동 호출되어 실수를 조기 발견. CI 단계 추가.

**예상 commits**: 2 (validator / 테스트).

### 제안 #R5 — x86 FP (x87/SSE/AVX) lifter RzIL-shape 도입 (Phase C 연장)

**수정 파일**:
- `include/decompiler.h`: IrOpcode 에 `IR_OP_FADD/FSUB/FMUL/FDIV/FNEG/FABS/FSQRT/FCMP_EQ/FCMP_LT` 추가 (~10개).
- `src/decompiler/codegen.c`: fld/fst/fadd/fmul/fdiv/fcom (x87), addss/subss/mulss (SSE scalar), addps/... (SSE packed) 분기.
- `src/decompiler/hir_emit.c`: FADD → `+` (operand 타입이 float) 출력.

**DoD**: FP 헤비 바이너리 (libm 링크) 의 covered_avg 측정.

**예상 commits**: 4–5 (opcode / x87 경로 / SSE 경로 / HIR emit / 회귀).

---

## 11. Cross-reference

### AURA 코드 베이스 (sort 순)
- `include/decompiler.h:79-132` — IrOpcode enum (AURA 28).
- `include/decompiler.h:149-153` — IrVal 구조.
- `src/decompiler/codegen.c:369` — `ir_lift` (x86 mnemonic 분기 + LIFT_BINOP).
- `src/decompiler/codegen.c:430-432` — `last_cmp_*` 단일 slot flag 캐시.
- `src/decompiler/codegen.c:2190` — `ir_optimize` PassManager 등록.
- `src/decompiler/arm64_lifter.c:127` — silent CMP_NE fallback.
- `src/decompiler/type_inference.c` — 2-pass meet-lattice type inference.
- `src/decompiler/hir_builder.c` — IR → HIR 구조화.

### 연관 AURA 문서
- `docs/research/ghidra_disasm_decompile_bridge_analysis.md` — Ghidra PCode + bridge 심층 (Task #28). §2–5 가 본 문서 §7–9 의 대칭.
- `docs/research/ghidra_func_detect_analysis.md` — Ghidra Funcdata pipeline (Task #26).
- `docs/research/ghidra_disasm_analysis.md` — SLEIGH + sweep (Task #27).
- `docs/research/README.md` — 3-doc triangulation index.

### 메모리
- `project_real_binary_parity_2026_04_18.md` — covered_avg 55 plateau (cat 15.8% / ls 45.1%). 본 문서 §7.2 편익 기준.
- `project_quality_bugs_session8.md` — truncated body 3-요인 복합. Phase B 이후 해결 가능성.

---

## 12. 인용

### Rizin 공식 문서
1. Rizin Handbook — [45. RzIL](https://book.rizin.re/src/disassembling/rzil.html).
2. Rizin Handbook — [54. Emulation](https://book.rizin.re/src/analysis/emulation.html) (RzILVM 실행 경로).
3. Rizin dev doc — [`doc/rzil.md`](https://github.com/rizinorg/rizin/blob/dev/doc/rzil.md).
4. Rizin roadmap — [rizin.re/roadmap](https://rizin.re/roadmap/) (v0.9 ESIL→RzIL migration goal).
5. Rizin 2025 summary — [Year 2025](https://rizin.re/posts/year-2025-summary/) (SPARC/H8/MIPS migration).

### Rizin 소스
6. `librz/include/rz_il/rz_il_opcodes.h` — [dev 브랜치](https://github.com/rizinorg/rizin/blob/dev/librz/include/rz_il/rz_il_opcodes.h) (RZ_IL_OP_* enum).
7. `librz/include/rz_il/rz_il_opbuilder_begin.h` — [opbuilder 매크로](https://github.com/rizinorg/rizin/blob/dev/librz/include/rz_il/rz_il_opbuilder_begin.h).
8. `librz/il/` 디렉토리 — [GitHub tree](https://github.com/rizinorg/rizin/tree/dev/librz/il) (theory_*.c 구성).

### Rizin 블로그
9. Heersin, [New RzIL integration PR #1663](https://github.com/rizinorg/rizin/pull/1663) (ESIL 대체 동기).
10. [RSoC 2021 Summary](https://rizin.re/posts/rsoc-2021-summary/) — BAP Core Theory 채택 + Brainfuck/8051 PoC.
11. DMaroo, [GSoC 2024 RISC-V RzIL uplifting](https://rizin.re/posts/gsoc-2024-auto-sync-sail/).
12. [GSoC 2022 x86 ISA lifting for RzIL](https://rizin.re/posts/gsoc-2022-x86-il/) — x86 ADD lifting + flag computation 예.

### BAP Core Theory (RzIL 의 이론적 기반)
13. BAP OCaml API — [Bap_core_theory](https://binaryanalysisplatform.github.io/bap/api/master/bap-core-theory/Bap_core_theory/).
14. SMT-LIB — [FixedSizeBitVectors theory](https://smt-lib.org/theories-FixedSizeBitVectors.shtml).

### Downstream 디컴파일러
15. [rizinorg/rz-ghidra](https://github.com/rizinorg/rz-ghidra) — Ghidra decompiler wrap (LGPL-3, **RzIL 미사용**).
16. [rizinorg/jsdec](https://github.com/rizinorg/jsdec) — JavaScript 디컴파일러 (ESIL 기반, RzIL 미이관).
17. [rizinorg/rz-retdec](https://github.com/rizinorg/rz-retdec) — RetDec 플러그인.

### AURA 선행 분석
18. `docs/research/ghidra_disasm_decompile_bridge_analysis.md` (Task #28, Session #9) — PCode 대비 Gap + R-S1/R-S2/R-S3 제안.
