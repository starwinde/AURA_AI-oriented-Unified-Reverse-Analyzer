# AURA Phase 5 — 디컴파일러 설계 (SSA 기반 IR)

> 작성일: 2026-03-31
> 상태: ✅ 확정 (2026-03-31)
> 목적: Phase 5 디컴파일러 모듈의 IR 구조, SSA 생성 알고리즘, 최적화 패스, Pseudo-C 생성 전략의 단일 기준

---

## §1 확정 결정 목록

| 결정 | 내용 | 일자 |
|------|------|------|
| IR 방향 | **SSA 기반** — Ghidra(P-code+SSA), IDA Pro(Microcode maturity 8), Binary Ninja(LLIL/MLIL/HLIL) 모두 SSA 채택. AURA 동일 방향 | 2026-03-31 |
| IR 계층 수 | **1계층** — SSA IR 단일 표현. Binary Ninja 다계층 방식은 post-v1.0 고려 | 2026-03-31 |
| 최적화 패스 범위 | **3개 (MVP)** — 상수 폴딩, 복사 전파, DCE. GVN/LICM 등은 Phase 5 고도화 패스 (5.37 LICM 등) | 2026-03-31 |
| 타입 추론 방식 | 피연산자 크기 기반 + LEA/역참조 패턴 — 외부 타입 분석 라이브러리 미사용 | 2026-03-31 |
| 제어 구조 복원 | CFG 패턴 매칭 — 단일 후계자, 두 후계자+수렴, 역방향 엣지, 점프 테이블 | 2026-03-31 |
| 호출 규약 | x86_64 System V ABI + Windows x64 ABI 지원 (Phase 5.5) | 2026-03-31 |
| 모듈 경로 | `src/decompiler/` — symbolic/ 계층 위의 독립 분석 계층 | 2026-03-31 |
| 입력 인터페이스 | `Cfg*` + `DfgResult*` + `FuncDetectResult*` — Phase 4 공개 API만 소비 | 2026-03-31 |
| 소유권 계약 | `ir_func_destroy` T** 모델 (cfg/dfg 동일 패턴) | 2026-03-31 |
| ARM64 패치 (D-8) | x86/x86_64 전용 (Zydis). ARM64 패치는 MVP 이후 별도 추가 | 2026-03-31 |

---

## §2 SSA IR 파이프라인 개요

```
DisasmResult[] + Cfg + DfgResult
    │
    ▼  [ir_lift()]
IrFunc (원시 IR — 버전 없는 임시 SSA 변수)
    │
    ▼  [ir_build_ssa()]
IrFunc (SSA 형태 — φ-function 삽입 + 변수 버전 부여)
    │
    ▼  [ir_optimize()]
IrFunc (최적화 완료 — 상수 폴딩, 복사 전파, DCE)
    │
    ▼  [ir_emit_pseudoc()]
Pseudo-C 텍스트 출력 (FILE*)
```

Phase 4 산출물과의 연계:
- `cfg.h` : BasicBlock 블록 구조 + CfgEdge 제어 흐름
- `dfg.h` : 레지스터 Def/Use 비트셋 (IR 리프팅 시 def/use 정보 활용)
- `func_detect.h` : 함수 경계 + 인자 추론 보조

---

## §3 IR 타입 구조

### 3.1 IrType — 피연산자 타입

```c
typedef enum {
    IR_TYPE_VOID,
    IR_TYPE_INT8,
    IR_TYPE_INT16,
    IR_TYPE_INT32,
    IR_TYPE_INT64,
    IR_TYPE_PTR,    /* 포인터 — 크기는 아키텍처 주소 폭(x86_64: 64비트) */
    IR_TYPE_BOOL,   /* 비교 결과 — 조건 분기 조건값 */
} IrType;
```

타입 판정 우선순위:
1. 피연산자 크기: `al/bl` → INT8, `ax/bx` → INT16, `eax/ebx` → INT32, `rax/rbx` → INT64
2. LEA 패턴 또는 포인터 역참조(`[reg]`) → PTR
3. CMP/TEST 결과 → BOOL
4. 불확실한 경우 → INT64 fallback

### 3.2 IrOpcode — 명령어 연산 코드

```c
typedef enum {
    /* 값 이동 */
    IR_OP_COPY,         /* dst = src0                  (mov reg, reg) */
    IR_OP_CONST,        /* dst = imm (IrVal.imm 참조)  (mov reg, imm) */

    /* 산술 */
    IR_OP_ADD,          /* dst = src0 + src1 */
    IR_OP_SUB,          /* dst = src0 - src1 */
    IR_OP_MUL,          /* dst = src0 * src1 */
    IR_OP_DIV,          /* dst = src0 / src1 */

    /* 비트 연산 */
    IR_OP_AND,          /* dst = src0 & src1 */
    IR_OP_OR,           /* dst = src0 | src1 */
    IR_OP_XOR,          /* dst = src0 ^ src1 */
    IR_OP_SHL,          /* dst = src0 << src1 */
    IR_OP_SHR,          /* dst = src0 >> src1 (논리 우시프트) */

    /* 비교 — 결과는 IR_TYPE_BOOL */
    IR_OP_CMP_EQ,       /* dst = (src0 == src1) */
    IR_OP_CMP_NE,       /* dst = (src0 != src1) */
    IR_OP_CMP_LT,       /* dst = (src0 <  src1) */
    IR_OP_CMP_LE,       /* dst = (src0 <= src1) */

    /* 메모리 접근 */
    IR_OP_LOAD,         /* dst = mem[src0]             (mov reg, [reg]) */
    IR_OP_STORE,        /* mem[src0] = src1            (mov [reg], reg) */

    /* 제어 흐름 */
    IR_OP_BRANCH,       /* if(src0) goto true_blk else goto false_blk */
    IR_OP_JUMP,         /* goto blk                    (jmp) */
    IR_OP_CALL,         /* dst = call src0(src1,...) */
    IR_OP_RET,          /* return src0                 (ret) */

    /* SSA 전용 */
    IR_OP_PHI,          /* dst = φ(val_from_pred0, val_from_pred1, ...) */
} IrOpcode;
```

### 3.3 IrVal — SSA 변수 (불변값)

```c
#define IR_VAL_ID_UNDEF  UINT32_MAX  /* 미정의 SSA 값 센티넬 */

typedef struct {
    uint32_t id;     /* 함수 내 전역 유일 ID. IR_VAL_ID_UNDEF = 미정의 */
    IrType   type;
    int64_t  imm;    /* IR_OP_CONST일 때만 유효한 상수 값 */
} IrVal;
```

SSA 불변 규칙:
- 각 `id`는 정확히 하나의 def(정의 지점)를 가진다
- 동일 `id`는 두 번 def되지 않는다 (SSA 형태 불변 조건)
- phi 이전 원시 단계에서는 `id = IR_VAL_ID_UNDEF` 사용

### 3.4 IrInstr — SSA 명령어

```c
#define IR_MAX_INLINE_SRCS  3   /* CALL 외 명령어의 인라인 소스 수 상한 */

typedef struct {
    IrOpcode  op;
    IrVal     dst;                      /* 정의(def) — IR_OP_STORE/JUMP/RET는 dst 미사용 */
    IrVal     srcs[IR_MAX_INLINE_SRCS]; /* 소스 피연산자 (src_count 개만 유효) */
    uint32_t  src_count;

    /* φ-function 전용 (op == IR_OP_PHI일 때만 유효) */
    IrVal    *phi_srcs;       /* heap (phi_count 크기). 각 predecessor 블록의 기여 값 */
    uint32_t *phi_pred_ids;   /* phi_srcs[i]가 유래한 predecessor IrBlock.id */
    uint32_t  phi_count;

    /* 분기/점프 전용 (op == IR_OP_BRANCH / IR_OP_JUMP일 때만 유효) */
    uint32_t  true_block_id;  /* BRANCH의 taken 방향 블록 id */
    uint32_t  false_block_id; /* BRANCH의 fallthrough 방향 블록 id */

    /* 원래 기계어 주소 (DOT 출력 / 디버그 / 역추적용) */
    AuraAddr  origin_addr;
} IrInstr;
```

### 3.5 IrBlock — IR BasicBlock

```c
typedef struct {
    uint32_t  id;
    IrInstr  *instrs;       /* heap, IrBlock 소유 */
    uint32_t  instr_count;
    uint32_t  instr_cap;    /* 내부 realloc용 */

    /* 제어 흐름 */
    uint32_t *pred_ids;     /* heap, predecessor IrBlock.id 배열 */
    uint32_t  pred_count;
    uint32_t *succ_ids;     /* heap, successor IrBlock.id 배열 */
    uint32_t  succ_count;

    /* 지배 트리 (ir_build_ssa 단계에서 채워짐) */
    uint32_t  idom_id;           /* immediate dominator 블록 id. entry는 자기 자신 */
    uint32_t *dom_front_ids;     /* heap, dominance frontier 집합 */
    uint32_t  dom_front_count;
} IrBlock;
```

### 3.6 IrFunc — IR 함수 단위

```c
typedef struct {
    IrBlock  *blocks;        /* heap, IrFunc 소유 */
    uint32_t  block_count;
    uint32_t  block_cap;
    uint32_t  next_val_id;   /* SSA value ID 발급 카운터 (단조 증가) */
    AuraAddr  func_addr;     /* 원래 기계어 함수 시작 주소 */
    char      name[128];     /* 함수 이름 (심볼 또는 "sub_<hex>") */
} IrFunc;
```

---

## §4 SSA 생성 알고리즘

### 4.1 단계 1 — IR 리프팅 (`ir_lift`)

입력: `Cfg*` + `DfgResult*` + 함수 이름 + 함수 주소
출력: 원시 IrFunc (버전 없는 임시 SSA 변수)

변환 규칙:

| x86_64 명령어 패턴 | IR 변환 |
|-------------------|---------|
| `mov dst_reg, src_reg` | `IR_OP_COPY` |
| `mov dst_reg, imm` | `IR_OP_CONST` |
| `add dst_reg, src` | `IR_OP_ADD` |
| `sub dst_reg, src` | `IR_OP_SUB` |
| `and/or/xor dst, src` | `IR_OP_AND/OR/XOR` |
| `shl/shr dst, cnt` | `IR_OP_SHL/SHR` |
| `cmp reg, reg/imm` (je/jne/jl/jle 뒤에서) | `IR_OP_CMP_*` |
| `mov dst, [reg]` | `IR_OP_LOAD` |
| `mov [reg], src` | `IR_OP_STORE` |
| `call target` | `IR_OP_CALL` |
| `ret` | `IR_OP_RET` |
| `jcc target` | `IR_OP_BRANCH` |
| `jmp target` | `IR_OP_JUMP` |

DfgResult 활용:
- `dfg_get_def(block, insn)` → IrInstr.dst 타입 결정 보조
- `dfg_get_use(block, insn)` → IrInstr.srcs 식별 보조

### 4.2 단계 2 — 지배 트리 계산

알고리즘: **Cooper et al. "A Simple, Fast Dominance Algorithm" (2001)**
- 단순 반복(iterative) 방식. Lengauer-Tarjan보다 구현 단순.
- RPO(Reverse Post-Order) 순서로 블록 처리.
- 수렴 조건: idom 배열 변화 없음.

```
idom[entry] = entry
for all other blocks b: idom[b] = UNDEF

repeat until no change:
    for b in RPO (excluding entry):
        new_idom = first processed predecessor of b
        for all other predecessors p of b:
            if idom[p] != UNDEF:
                new_idom = intersect(p, new_idom)
        if idom[b] != new_idom:
            idom[b] = new_idom

intersect(b1, b2):
    while b1 != b2:
        while RPO_num[b1] > RPO_num[b2]: b1 = idom[b1]
        while RPO_num[b2] > RPO_num[b1]: b2 = idom[b2]
    return b1
```

### 4.3 단계 3 — 지배 경계 계산

알고리즘: **Cytron et al. (1991)**

```
for each block b:
    dom_front[b] = {}

for each block b with |pred(b)| >= 2:
    for each predecessor p of b:
        runner = p
        while runner != idom[b]:
            dom_front[runner] ∪= {b}
            runner = idom[runner]
```

### 4.4 단계 4 — φ-function 삽입

레지스터별로 def 블록 집합을 구해 DF+ 클로저 반복:

```
for each register r:
    def_blocks[r] = blocks where r is defined

    worklist = def_blocks[r]
    visited = {}
    while worklist not empty:
        b = pop(worklist)
        for y in dom_front[b]:
            if y not in visited:
                insert PHI for r at start of y
                visited ∪= {y}
                if y not in def_blocks[r]:
                    push(worklist, y)
```

### 4.5 단계 5 — 변수 이름 부여 (Renaming)

DFS 방식으로 지배 트리 순회:

```
stacks[r] = [] for each register r

rename(block b):
    for each phi in b:
        new_id = next_val_id++
        phi.dst = IrVal{id=new_id, ...}
        push(stacks[phi.register], new_id)

    for each non-phi instruction in b:
        for each use operand op:
            replace op with top of stacks[op.register]
        if instruction defines a register r:
            new_id = next_val_id++
            replace def with IrVal{id=new_id, ...}
            push(stacks[r], new_id)

    for each successor s of b:
        for each phi in s where b is a predecessor:
            phi.phi_srcs[b_index] = top of stacks[phi.register]

    for each child c of b in dominator tree:
        rename(c)

    // pop 스택 복구
    for each definition made in b:
        pop(stacks[defined_register])
```

---

## §5 최적화 패스

MVP 범위: 3개 패스. 플래그 비트로 개별 활성화.

### 5.1 상수 폴딩 (Constant Folding, `IR_OPT_CONST_FOLD`)

```
IR_OP_ADD  dst = CONST(a) + CONST(b)  →  dst = CONST(a+b)
IR_OP_SUB  dst = CONST(a) - CONST(b)  →  dst = CONST(a-b)
IR_OP_MUL  dst = CONST(a) * CONST(b)  →  dst = CONST(a*b)
IR_OP_XOR  dst = v ^ v                →  dst = CONST(0)   (동일 값 XOR)
IR_OP_AND  dst = v & CONST(0)         →  dst = CONST(0)
IR_OP_OR   dst = v | CONST(-1)        →  dst = CONST(-1)
```

### 5.2 복사 전파 (Copy Propagation, `IR_OPT_COPY_PROP`)

```
IR_OP_COPY  vN = vM
→ 이후 vN의 모든 use를 vM으로 치환
→ vN 정의 삭제 (dead가 되면 DCE 대상)
```

### 5.3 데드코드 제거 (Dead Code Elimination, `IR_OPT_DCE`)

```
vN을 use하는 명령어가 없고 (side-effect 없는 op이면):
→ vN을 정의하는 명령어 삭제
side-effect 있는 op: IR_OP_STORE, IR_OP_CALL, IR_OP_RET, IR_OP_BRANCH, IR_OP_JUMP
```

반복 적용 순서: CONST_FOLD → COPY_PROP → DCE (연쇄 전파를 위해 수렴까지 반복)

---

## §6 Pseudo-C 생성 전략

### 6.1 타입 추론 (Task 5.3)

| 패턴 | 추론 타입 |
|------|----------|
| 8비트 레지스터 (al, bl, ...) | `int8_t` |
| 16비트 레지스터 (ax, bx, ...) | `int16_t` |
| 32비트 레지스터 (eax, ebx, ...) | `int32_t` |
| 64비트 레지스터 (rax, rbx, ...) | `int64_t` |
| LEA 대상 / `[reg+disp]` 역참조 | `int64_t *` (PTR) |
| CMP/TEST 결과 (BOOL) | 비교 표현식 (변수 미생성) |
| 불확실 | `int64_t` fallback |

호출 규약에서 인자 타입 결정:
- x86_64 System V ABI: RDI, RSI, RDX, RCX, R8, R9 → `a0`~`a5`
- Windows x64 ABI: RCX, RDX, R8, R9 → `a0`~`a3`
- 6번째 이상 인자 → 스택 (`a6`, `a7`, ...)

### 6.2 제어 구조 복원 (Task 5.4)

CFG 토폴로지 패턴 매칭:

```
패턴 1 — 직선 코드
  B0 → B1  (단일 후계자, IR_OP_JUMP)
  → 순차 구문 병합

패턴 2 — if / if-else
  B0 →(true) B1, B0 →(false) B2, B1/B2 → B3(수렴)
  → if (cond) { B1 } else { B2 }
  B2가 수렴 블록이면: if (cond) { B1 }

패턴 3 — while 루프
  역방향 엣지(back edge) 존재: B1 → B0, B0이 loop header
  → while (cond) { body }

패턴 4 — do-while 루프
  body → cond_check →(true) body
  → do { body } while (cond)

패턴 5 — switch-case
  단일 블록에서 N개의 직접 분기 (점프 테이블 패턴)
  → switch (expr) { case N: ... }
```

### 6.3 Pseudo-C 출력 형식

```c
/* 생성 예시 */
int64_t sub_401000(int64_t a0, int64_t a1) {
    int64_t v2;
    int64_t v3;
    if (a0 > 0LL) {
        v2 = a0 + a1;
    } else {
        v2 = a1;
    }
    v3 = v2 * 2LL;
    return v3;
}
```

출력 규칙:
- 들여쓰기: 공백 4칸
- 변수명: 인자 `a0`~`aN`, 지역 변수 `v0`~`vN` (SSA ID 순서)
- 정수 리터럴: `LL` 접미사 (INT64), 포인터 캐스트 명시
- 알 수 없는 함수 호출: `sub_<hex>(arg0, arg1, ...)`
- 반환 타입: 추론 결과 or `int64_t` fallback

---

## §7 공개 API 요약

자세한 시그니처는 `include/decompiler.h` 참조.

| 함수 | 역할 | 단계 |
|------|------|------|
| `ir_lift()` | CFG → 원시 IrFunc | 5.2 |
| `ir_build_ssa()` | 원시 IR → SSA 형태 | 5.2 |
| `ir_optimize()` | 최적화 패스 적용 | 5.2 |
| `ir_emit_pseudoc()` | SSA IR → Pseudo-C 텍스트 | 5.2~5.4 |
| `ir_func_destroy()` | IrFunc 메모리 해제 (T** 모델) | — |
| `ir_print_text()` | SSA IR 텍스트 덤프 (디버그) | — |

---

## §8 파일 구조

```
include/
  decompiler.h          ← 공개 API 및 타입 정의 (Task 5.1)

src/decompiler/
  codegen.c             ← ir_lift + ir_build_ssa + ir_optimize (Task 5.2)
  type_inference.c      ← 타입 추론 (Task 5.3)
  control_flow.c        ← 제어 구조 복원 (Task 5.4)
  callgraph.c           ← 함수 호출 그래프 생성 (Task 5.5)

tests/decompiler/
  test_decompiler.c     ← 단위 테스트 (Task 5.2~5.5 각자 추가)
tests/pipeline/
  test_5T_decompiler.c  ← Phase 5 종합 통합 테스트 (Task 5.T)
tests/results/
  5.1_decompiler_design.txt
  5.2_codegen.txt
  ...
  5.T_decompiler.txt
```

---

## §9 의존성

```
Phase 4 (완료)
  ├── cfg.h / cfg.c     → BasicBlock, Cfg, CfgEdge
  ├── dfg.h / dfg.c     → DfgResult, def/use 비트셋
  └── func_detect.h/c   → FuncEntry, 호출 규약 인자 추론 보조

Phase 5 (이번 Phase)
  └── decompiler.h      → IrType, IrOpcode, IrVal, IrInstr, IrBlock, IrFunc
        └── codegen.c   → ir_lift, ir_build_ssa, ir_optimize, ir_emit_pseudoc
```
