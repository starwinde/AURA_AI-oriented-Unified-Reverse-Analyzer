# AURA High-level IR (HIR) — Level 1 설계 문서

> 작성일: 2026-04-04
> Task 5.39 | Phase 5: Decompiler Quality Enhancement (formerly Task 13.18 / Phase 13)
> 상태: 설계 문서 (구현은 5.40~5.42)

---

## 1. 동기 및 목표

### 1.1 현재 단일 IR의 한계

AURA의 현재 IR은 단일 레벨 SSA IR이다 (`decompiler.h` §1~§6`).
기계어 수준의 LOAD/STORE/BRANCH 연산과 고급 언어의 if/while/struct 표현을
하나의 표현 계층에서 처리하려 하므로 다음 문제가 발생한다:

| 문제 | 현상 |
|------|------|
| 구조 정보 손실 | `cf_emit_structured()`가 IR 위를 재귀 순회하며 **매번** 패턴 매칭을 수행. 결과를 저장하지 않아 후속 패스에서 재사용 불가 |
| goto 과다 | 패턴 매칭 실패 시 즉시 goto로 전락. 구조화 결과를 재시도할 수 없음 |
| 타입 표현 부재 | `ptr->field`, `arr[i]` 같은 고급 접근을 IR 수준에서 표현할 수 없음. `struct_recovery.c`의 `SrStruct`/`SrArray` 결과가 IR에 통합되지 못함 |
| Pseudo-C 품질 | `control_flow.c`가 구조 분석과 코드 출력을 동시에 수행하여 관심사 분리 실패 |

### 1.2 HIR 도입 목표

| 목표 | 측정 지표 |
|------|----------|
| 구조 정보를 IR 노드로 영속화 | HIR 트리에서 if/while/for/switch가 명시적 노드 |
| 집합체 타입 접근 표현 | `HIR_FIELD_ACCESS`, `HIR_ARRAY_INDEX` 노드 |
| 코드 생성 단순화 | HIR → Pseudo-C는 트리 순회만으로 완료 (패턴 매칭 불필요) |
| 기존 IR 비파괴 | SSA IR (Level 0)은 그대로 유지. HIR은 SSA IR **위에** 구축 |

---

## 2. 아키텍처 개요

```
Machine Code
    │
    ▼
┌─────────────────────────────────────────────────┐
│  Level 0: SSA IR  (IrFunc / IrBlock / IrInstr)  │  ← 현재 존재
│  opcodes: ADD, SUB, LOAD, STORE, BRANCH, PHI... │
└─────────────────────────────────────────────────┘
    │  (1) structural_analysis (5.28)
    │  (2) loop_detect (5.27)
    │  (3) type_constraint (5.33)
    │  (4) struct_recovery (5.16)
    │  (5) phi_elimination (5.31)
    ▼
┌─────────────────────────────────────────────────┐
│  Level 1: HIR  (HirFunc / HirNode tree)         │  ← 신규
│  nodes: HIR_IF, HIR_WHILE, HIR_FOR, HIR_SWITCH, │
│         HIR_RETURN, HIR_ASSIGN, HIR_CALL,        │
│         HIR_FIELD_ACCESS, HIR_ARRAY_INDEX, ...   │
└─────────────────────────────────────────────────┘
    │
    ▼
┌─────────────────────────────────────────────────┐
│  Pseudo-C Emission  (hir_emit.c)                │
│  HIR 트리 → 들여쓰기 + 중괄호 + 연산자 텍스트   │
└─────────────────────────────────────────────────┘
```

**핵심 원칙**: SSA IR은 변경하지 않는다. HIR은 SSA IR의 정보를 소비하여
별도의 트리 구조로 재구성한 것이다. SSA IR → HIR 변환은 단방향이며,
HIR은 읽기 전용 최종 표현이다.

---

## 3. HIR 노드 정의

### 3.1 노드 종류 (HirNodeKind)

```c
typedef enum {
    /* 제어 흐름 */
    HIR_SEQ,            /* 문장 시퀀스 (body) */
    HIR_IF,             /* if / if-else */
    HIR_WHILE,          /* while (pre-test loop) */
    HIR_DO_WHILE,       /* do-while (post-test loop) */
    HIR_FOR,            /* for (init; cond; step) */
    HIR_SWITCH,         /* switch-case */
    HIR_GOTO,           /* 구조화 불가 edge (최후 수단) */
    HIR_LABEL,          /* goto 대상 라벨 */
    HIR_BREAK,          /* loop/switch 탈출 */
    HIR_CONTINUE,       /* loop 재진입 */

    /* 문장 */
    HIR_ASSIGN,         /* lhs = rhs */
    HIR_RETURN,         /* return expr */
    HIR_CALL,           /* func(args...) — 문장 위치일 때 */

    /* 표현식 (문장 내부에서 사용) */
    HIR_EXPR_VAR,       /* SSA 변수 참조 */
    HIR_EXPR_CONST,     /* 정수/부동소수점 리터럴 */
    HIR_EXPR_BINOP,     /* lhs op rhs */
    HIR_EXPR_UNOP,      /* op expr (-, ~, !, *deref, &addr) */
    HIR_EXPR_CALL,      /* func(args...) — 표현식 위치일 때 */
    HIR_EXPR_CAST,      /* (type)expr */
    HIR_FIELD_ACCESS,   /* base->field_name */
    HIR_ARRAY_INDEX,    /* base[index] */
} HirNodeKind;
```

### 3.2 노드 구조체 (HirNode)

HIR은 태그드 유니온 트리로 표현한다. 모든 노드는 동일한 `HirNode` 구조체이고
`kind` 필드로 어떤 variant인지 판별한다.

```c
typedef struct HirNode HirNode;

/* 타입 정보 (HIR 수준) */
typedef struct {
    char     name[128];     /* C 타입 문자열: "int", "struct_0*", ... */
    uint32_t size;          /* 바이트 크기 (0 = 알 수 없음) */
    uint8_t  is_ptr;        /* 포인터 여부 */
    uint8_t  is_signed;     /* 부호 여부 */
    uint8_t  is_struct;     /* 구조체 여부 */
    uint8_t  is_array;      /* 배열 여부 */
} HirType;

/* switch case 엔트리 */
typedef struct {
    int64_t   value;        /* case 값 (is_default=1이면 무시) */
    uint8_t   is_default;   /* default case 여부 */
    HirNode  *body;         /* case 본문 (HIR_SEQ) */
} HirSwitchCase;

struct HirNode {
    HirNodeKind kind;
    HirType     type;       /* 표현식 노드의 결과 타입 */
    AuraAddr    origin;     /* 원래 기계어 주소 (역추적용, 0 = 불명) */

    union {
        /* HIR_SEQ */
        struct {
            HirNode **stmts;
            uint32_t  stmt_count;
            uint32_t  stmt_cap;
        } seq;

        /* HIR_IF */
        struct {
            HirNode *cond;       /* 조건 표현식 */
            HirNode *then_body;  /* then 브랜치 (HIR_SEQ) */
            HirNode *else_body;  /* else 브랜치 (HIR_SEQ, NULL이면 if-only) */
        } hir_if;

        /* HIR_WHILE */
        struct {
            HirNode *cond;
            HirNode *body;       /* HIR_SEQ */
        } hir_while;

        /* HIR_DO_WHILE */
        struct {
            HirNode *cond;
            HirNode *body;       /* HIR_SEQ */
        } hir_do_while;

        /* HIR_FOR */
        struct {
            HirNode *init;       /* 초기화 문장 (HIR_ASSIGN, NULL 가능) */
            HirNode *cond;       /* 조건 표현식 */
            HirNode *step;       /* 증감 문장 (HIR_ASSIGN, NULL 가능) */
            HirNode *body;       /* HIR_SEQ */
        } hir_for;

        /* HIR_SWITCH */
        struct {
            HirNode       *expr;        /* switch 대상 표현식 */
            HirSwitchCase *cases;       /* case 배열 */
            uint32_t       case_count;
            uint32_t       case_cap;
        } hir_switch;

        /* HIR_GOTO */
        struct {
            uint32_t label_id;          /* 대상 라벨 ID */
        } hir_goto;

        /* HIR_LABEL */
        struct {
            uint32_t label_id;
        } hir_label;

        /* HIR_ASSIGN */
        struct {
            HirNode *lhs;              /* 대상 (VAR, FIELD_ACCESS, ARRAY_INDEX) */
            HirNode *rhs;              /* 값 표현식 */
        } hir_assign;

        /* HIR_RETURN */
        struct {
            HirNode *expr;             /* 반환 표현식 (NULL = void return) */
        } hir_return;

        /* HIR_CALL (문장) + HIR_EXPR_CALL (표현식) */
        struct {
            char     func_name[128];   /* 함수 이름 ("sub_<hex>" or 심볼) */
            uint64_t target_addr;      /* callee 주소 (0 = 간접) */
            HirNode **args;
            uint32_t  arg_count;
            uint32_t  arg_cap;
        } hir_call;

        /* HIR_EXPR_VAR */
        struct {
            uint32_t ssa_id;           /* SSA 값 ID (IrVal.id) */
            char     name[64];         /* 표시 이름 (v0, argc, ptr, ...) */
        } hir_var;

        /* HIR_EXPR_CONST */
        struct {
            int64_t  int_val;
            double   fp_val;           /* float/double일 때 사용 */
            uint8_t  is_fp;
        } hir_const;

        /* HIR_EXPR_BINOP */
        struct {
            HirNode *lhs;
            HirNode *rhs;
            IrOpcode op;               /* SSA IR opcode 재사용 (ADD, SUB, CMP_EQ, ...) */
        } hir_binop;

        /* HIR_EXPR_UNOP */
        struct {
            HirNode *operand;
            enum {
                HIR_UNOP_NEG,          /* -x */
                HIR_UNOP_NOT,          /* ~x (bitwise) */
                HIR_UNOP_LNOT,        /* !x (logical) */
                HIR_UNOP_DEREF,       /* *x */
                HIR_UNOP_ADDR,        /* &x */
            } op;
        } hir_unop;

        /* HIR_EXPR_CAST */
        struct {
            HirNode *operand;
            HirType  target_type;
        } hir_cast;

        /* HIR_FIELD_ACCESS */
        struct {
            HirNode *base;             /* base 포인터 표현식 */
            char     field_name[64];   /* 필드 이름 ("field_8", 또는 DWARF/PDB 이름) */
            int64_t  offset;           /* base로부터 바이트 오프셋 */
            uint8_t  is_arrow;         /* 1: ptr->field, 0: val.field */
        } hir_field;

        /* HIR_ARRAY_INDEX */
        struct {
            HirNode *base;             /* 배열 base 표현식 */
            HirNode *index;            /* 인덱스 표현식 */
            uint32_t elem_size;        /* 원소 크기 (바이트) */
        } hir_array;
    };
};
```

### 3.3 함수 컨테이너 (HirFunc)

```c
typedef struct {
    /* 함수 메타데이터 */
    char      name[128];           /* 함수 이름 */
    AuraAddr  func_addr;           /* 기계어 시작 주소 */
    HirType   return_type;         /* 반환 타입 */

    /* 파라미터 */
    struct {
        char    name[64];
        HirType type;
    } params[16];
    uint32_t   param_count;

    /* 지역 변수 테이블 */
    struct {
        uint32_t ssa_id;           /* 원래 SSA ID */
        char     name[64];        /* 표시 이름 */
        HirType  type;
    } *locals;
    uint32_t   local_count;
    uint32_t   local_cap;

    /* 함수 본문 */
    HirNode   *body;               /* 최상위 HIR_SEQ */
} HirFunc;
```

### 3.4 노드별 의미 요약

| 노드 | 자식 | 의미 |
|------|------|------|
| `HIR_SEQ` | `stmts[]` | 순차 문장 블록. 중첩 가능. `{ stmt; stmt; ... }` |
| `HIR_IF` | `cond`, `then_body`, `else_body?` | `if (cond) { then } else { else }` |
| `HIR_WHILE` | `cond`, `body` | `while (cond) { body }` |
| `HIR_DO_WHILE` | `cond`, `body` | `do { body } while (cond);` |
| `HIR_FOR` | `init?`, `cond`, `step?`, `body` | `for (init; cond; step) { body }` |
| `HIR_SWITCH` | `expr`, `cases[]` | `switch (expr) { case V: body; ... }` |
| `HIR_GOTO` | `label_id` | `goto L_N;` (최후 수단) |
| `HIR_LABEL` | `label_id` | `L_N:` |
| `HIR_BREAK` | — | `break;` |
| `HIR_CONTINUE` | — | `continue;` |
| `HIR_ASSIGN` | `lhs`, `rhs` | `lhs = rhs;` |
| `HIR_RETURN` | `expr?` | `return expr;` 또는 `return;` |
| `HIR_CALL` | `func_name`, `args[]` | `func(a, b, c);` (문장) |
| `HIR_EXPR_VAR` | `ssa_id`, `name` | 변수 참조: `v3`, `argc` |
| `HIR_EXPR_CONST` | `int_val` / `fp_val` | 리터럴: `42`, `3.14` |
| `HIR_EXPR_BINOP` | `lhs`, `rhs`, `op` | 이항 연산: `a + b` |
| `HIR_EXPR_UNOP` | `operand`, `op` | 단항 연산: `-x`, `!x`, `*ptr` |
| `HIR_EXPR_CALL` | `func_name`, `args[]` | 함수 호출 (표현식): `y = func(x)` |
| `HIR_EXPR_CAST` | `operand`, `target_type` | 타입 캐스트: `(int32_t)x` |
| `HIR_FIELD_ACCESS` | `base`, `field_name`, `offset` | 필드 접근: `ptr->field_8` |
| `HIR_ARRAY_INDEX` | `base`, `index`, `elem_size` | 배열 접근: `arr[i]` |

---

## 4. SSA IR → HIR 변환 전략

### 4.1 변환 파이프라인

```
입력: IrFunc (SSA IR, 최적화 완료)
       + StructuralAnalysis 결과 (5.28)
       + LoopInfo 결과 (5.27)
       + StructRecoveryResult (5.16)
       + TypeConstraintResult (5.33, 있을 경우)

단계 1: Phi Elimination (5.31) — SSA → 일반 변수
단계 2: 변수 이름 할당 (5.32 register coalescing 결과 활용)
단계 3: 표현식 트리 구축 (단일 사용 def를 인라인)
단계 4: 구조적 분석 결과를 HIR 제어 흐름 노드로 변환
단계 5: 집합체 접근 패턴을 HIR_FIELD_ACCESS / HIR_ARRAY_INDEX로 변환
단계 6: 최종 HIR 트리 정리 (빈 SEQ 제거, 단일문 SEQ 평탄화)

출력: HirFunc
```

### 4.2 단계 3 — 표현식 트리 구축

SSA IR에서 각 값은 정확히 한 번 정의된다. 단일 사용(use-count == 1)인
중간 값은 별도의 대입문 대신 사용 지점에 인라인할 수 있다.

```
SSA IR:
  v3 = CONST 5
  v4 = ADD v1, v3
  v5 = CMP_LT v4, v2

HIR (인라인 후):
  HIR_EXPR_BINOP(CMP_LT,
      HIR_EXPR_BINOP(ADD, HIR_EXPR_VAR(v1), HIR_EXPR_CONST(5)),
      HIR_EXPR_VAR(v2))

Pseudo-C:
  (v1 + 5) < v2
```

**인라인 규칙**:
- use-count == 1이고 def와 use가 동일 블록 내에 있으면 인라인
- LOAD/STORE/CALL은 부작용이 있으므로 인라인하지 않음 (순서 보존)
- PHI 결과는 인라인하지 않음

### 4.3 단계 4 — 제어 흐름 노드 변환

구조적 분석(5.28)은 각 region에 대해 구조 유형을 결정한다.
HIR 빌더는 이 결과를 소비하여 대응하는 HIR 노드를 생성한다.

| 구조적 분석 결과 | HIR 노드 | 비고 |
|-----------------|----------|------|
| `REGION_IF` | `HIR_IF` | then/else 서브리전을 재귀 변환 |
| `REGION_IF_THEN` | `HIR_IF` (else_body=NULL) | 단순 if |
| `REGION_WHILE` | `HIR_WHILE` | header 조건 → cond, body 리전 → body |
| `REGION_DO_WHILE` | `HIR_DO_WHILE` | latch 조건 → cond |
| `REGION_FOR` | `HIR_FOR` | induction var init/step 분리 |
| `REGION_SWITCH` | `HIR_SWITCH` | case 값 + body 리전 매핑 |
| `REGION_SEQ` | `HIR_SEQ` | 직선 코드 |
| unstructured edge | `HIR_GOTO` + `HIR_LABEL` | 최후 수단 |

**for 루프 인식 (REGION_WHILE → HIR_FOR 승격)**:

while 루프가 다음 조건을 만족하면 for로 승격한다:
1. induction variable 존재 (정수, 루프 내 단조 증가/감소)
2. 루프 직전에 초기화 대입이 존재
3. 루프 body 마지막에 증감 대입이 존재

```
// REGION_WHILE:
v0 = 0;                     // init
while (v0 < 10) {           // cond
    body...
    v0 = v0 + 1;            // step
}

// HIR_FOR로 승격:
for (v0 = 0; v0 < 10; v0 = v0 + 1) {
    body...
}
```

### 4.4 단계 5 — 집합체 접근 변환

`struct_recovery.c`의 `StructRecoveryResult`를 활용하여
LOAD/STORE 패턴을 고급 접근 노드로 치환한다.

**구조체 필드 접근**:
```
SSA IR:
  v5 = ADD v1, CONST(8)     // base + offset
  v6 = LOAD v5              // *(base + 8)

sr_analyze() 결과:
  SrStruct { base=v1, fields=[{offset=8, size=4, type=INT32}] }

HIR:
  HIR_FIELD_ACCESS { base=v1, field="field_8", offset=8, is_arrow=1 }

Pseudo-C:
  v1->field_8
```

**배열 접근**:
```
SSA IR:
  v7 = MUL v3, CONST(4)     // index * elem_size
  v8 = ADD v1, v7            // base + index * elem_size
  v9 = LOAD v8

sr_analyze() 결과:
  SrArray { base=v1, elem_size=4, elem_type=INT32 }

HIR:
  HIR_ARRAY_INDEX { base=v1, index=v3, elem_size=4 }

Pseudo-C:
  v1[v3]
```

**DWARF/PDB 디버그 정보가 있을 경우**:
`debug_types.h`의 `DbgVarTable`에서 실제 필드 이름을 가져와
`field_name`을 `"field_8"` 대신 `"count"` 등으로 대체한다.

### 4.5 SSA 값 → HIR 변수 매핑

| SSA 특성 | HIR 표현 |
|----------|----------|
| 함수 인자 (ABI 레지스터 기반) | `HirFunc.params[]` — `a0`, `a1`, ... 또는 디버그 이름 |
| phi-eliminated 변수 | `HirFunc.locals[]` — 동일 레지스터 기반 coalescing 후 단일 변수 |
| 단일 사용 중간값 | 인라인 표현식 (별도 변수 없음) |
| 다중 사용 중간값 | `HirFunc.locals[]` — `v<N>` |

---

## 5. HIR → Pseudo-C 방출 전략

### 5.1 설계 원칙

HIR은 Pseudo-C와 거의 1:1 대응하도록 설계되었으므로,
Pseudo-C 생성은 HIR 트리의 단순 순회(recursive descent)로 구현한다.
패턴 매칭, 구조 분석은 이 단계에서 **일절 수행하지 않는다**.

### 5.2 방출 알고리즘

```
hir_emit(node, out, indent):
    switch (node.kind):
        case HIR_SEQ:
            for stmt in node.seq.stmts:
                hir_emit(stmt, out, indent)

        case HIR_IF:
            emit_indent(indent)
            emit("if (")
            hir_emit_expr(node.hir_if.cond, out)
            emit(") {\n")
            hir_emit(node.hir_if.then_body, out, indent + 1)
            if (node.hir_if.else_body):
                emit_indent(indent)
                emit("} else {\n")
                hir_emit(node.hir_if.else_body, out, indent + 1)
            emit_indent(indent)
            emit("}\n")

        case HIR_WHILE:
            emit_indent(indent)
            emit("while (")
            hir_emit_expr(node.hir_while.cond, out)
            emit(") {\n")
            hir_emit(node.hir_while.body, out, indent + 1)
            emit_indent(indent)
            emit("}\n")

        case HIR_FOR:
            emit_indent(indent)
            emit("for (")
            hir_emit_expr(node.hir_for.init, out)   // init 없으면 생략
            emit("; ")
            hir_emit_expr(node.hir_for.cond, out)
            emit("; ")
            hir_emit_expr(node.hir_for.step, out)   // step 없으면 생략
            emit(") {\n")
            hir_emit(node.hir_for.body, out, indent + 1)
            emit_indent(indent)
            emit("}\n")

        case HIR_SWITCH:
            emit_indent(indent)
            emit("switch (")
            hir_emit_expr(node.hir_switch.expr, out)
            emit(") {\n")
            for case in node.hir_switch.cases:
                emit_indent(indent)
                if case.is_default:
                    emit("default:\n")
                else:
                    emit("case %d:\n", case.value)
                hir_emit(case.body, out, indent + 1)
                emit_indent(indent + 1)
                emit("break;\n")
            emit_indent(indent)
            emit("}\n")

        case HIR_ASSIGN:
            emit_indent(indent)
            hir_emit_expr(node.hir_assign.lhs, out)
            emit(" = ")
            hir_emit_expr(node.hir_assign.rhs, out)
            emit(";\n")

        case HIR_RETURN:
            emit_indent(indent)
            if node.hir_return.expr:
                emit("return ")
                hir_emit_expr(node.hir_return.expr, out)
            else:
                emit("return")
            emit(";\n")

        case HIR_CALL:
            emit_indent(indent)
            emit("%s(", node.hir_call.func_name)
            emit_args(node.hir_call.args, node.hir_call.arg_count, out)
            emit(");\n")

        case HIR_GOTO:
            emit_indent(indent)
            emit("goto L_%u;\n", node.hir_goto.label_id)

        case HIR_LABEL:
            emit("L_%u:\n", node.hir_label.label_id)

        case HIR_BREAK:
            emit_indent(indent)
            emit("break;\n")

        case HIR_CONTINUE:
            emit_indent(indent)
            emit("continue;\n")
```

### 5.3 표현식 방출 (hir_emit_expr)

```
hir_emit_expr(node, out):
    switch (node.kind):
        case HIR_EXPR_VAR:
            emit("%s", node.hir_var.name)

        case HIR_EXPR_CONST:
            if node.hir_const.is_fp:
                emit("%g", node.hir_const.fp_val)
            else:
                emit_int_literal(node.hir_const.int_val, node.type)

        case HIR_EXPR_BINOP:
            need_parens = parent_precedence > op_precedence(node.hir_binop.op)
            if need_parens: emit("(")
            hir_emit_expr(node.hir_binop.lhs, out)
            emit(" %s ", op_str(node.hir_binop.op))
            hir_emit_expr(node.hir_binop.rhs, out)
            if need_parens: emit(")")

        case HIR_EXPR_UNOP:
            emit("%s", unop_str(node.hir_unop.op))
            hir_emit_expr(node.hir_unop.operand, out)

        case HIR_EXPR_CALL:
            emit("%s(", node.hir_call.func_name)
            emit_args(node.hir_call.args, node.hir_call.arg_count, out)
            emit(")")

        case HIR_EXPR_CAST:
            emit("(%s)", node.hir_cast.target_type.name)
            hir_emit_expr(node.hir_cast.operand, out)

        case HIR_FIELD_ACCESS:
            hir_emit_expr(node.hir_field.base, out)
            if node.hir_field.is_arrow:
                emit("->%s", node.hir_field.field_name)
            else:
                emit(".%s", node.hir_field.field_name)

        case HIR_ARRAY_INDEX:
            hir_emit_expr(node.hir_array.base, out)
            emit("[")
            hir_emit_expr(node.hir_array.index, out)
            emit("]")
```

### 5.4 연산자 우선순위

괄호 최소화를 위해 C 표준 연산자 우선순위 테이블을 사용한다.

| 우선순위 (높음→낮음) | 연산 |
|---------------------|------|
| 14 | `[]`, `->`, `.` |
| 13 | 단항 `-`, `~`, `!`, `*`, `&`, cast |
| 12 | `*`, `/` |
| 11 | `+`, `-` |
| 10 | `<<`, `>>` |
| 9 | `<`, `<=`, `>`, `>=` |
| 8 | `==`, `!=` |
| 7 | `&` (bitwise) |
| 6 | `^` |
| 5 | `\|` |
| 4 | `&&` |
| 3 | `\|\|` |
| 2 | `=` |

### 5.5 변수 선언 방출

함수 본문 앞에 `HirFunc.locals[]`를 순회하여 변수 선언을 출력한다.

```c
// 출력 예시:
int64_t v0;
int32_t *ptr;
struct_0 *v3;
```

### 5.6 정수 리터럴 형식

| 조건 | 출력 형식 | 예시 |
|------|----------|------|
| 값 < 10 | 10진수 | `5` |
| 값 ≥ 0x100 | 16진수 | `0x1234` |
| 포인터 타입 | 16진수 | `0x401000` |
| INT64 | LL 접미사 | `42LL` |
| 음수 | 부호 유지 | `-1` |

---

## 6. 기존 IR과의 호환성

### 6.1 비파괴 전환

HIR 도입은 기존 코드를 파괴하지 않는다.

| 기존 코드 | 변경 | 비고 |
|-----------|------|------|
| `decompiler.h` (IrFunc, IrBlock, IrInstr) | 변경 없음 | Level 0 IR 유지 |
| `codegen.c` (ir_lift, ir_build_ssa, ir_optimize) | 변경 없음 | SSA 파이프라인 유지 |
| `control_flow.c` (cf_emit_structured) | 유지 (fallback) | HIR 미생성 시 기존 경로 |
| `ir_emit_pseudoc()` | 분기 추가 | HIR 있으면 HIR 경로, 없으면 기존 경로 |
| `struct_recovery.c` | 소비자 추가 | `SrStruct`/`SrArray` → HIR 변환 |

### 6.2 점진적 전환 전략

```
Task 5.40: HirNode 구조체 + hir_builder 구현
           SSA IR → HIR 변환 (제어 흐름만)
           → ir_emit_pseudoc()에서 HIR 경로 선택 가능

Task 5.41: HirType + HIR_FIELD_ACCESS + HIR_ARRAY_INDEX
           StructRecoveryResult → HIR 타입 통합

Task 5.42: hir_emit_pseudoc() 구현
           HIR 트리 → 최종 Pseudo-C 출력
           → ir_emit_pseudoc() 내부에서 HIR 경로가 기본값으로 전환
```

### 6.3 API 경계

```c
/* include/hir.h — 신규 공개 API */

/* HIR 생성 (Task 5.40) */
HirFunc *hir_build(const IrFunc *ssa_func,
                   const void *structural_result,   /* 5.28 결과 */
                   const void *loop_info,            /* 5.27 결과 */
                   const StructRecoveryResult *sr);  /* 5.16 결과, NULL 허용 */

/* HIR 파괴 */
void hir_func_destroy(HirFunc **func);

/* HIR → Pseudo-C 출력 (Task 5.42) */
AuraError hir_emit_pseudoc(const HirFunc *func, FILE *out);

/* HIR 디버그 덤프 (Task 5.40) */
AuraError hir_dump(const HirFunc *func, FILE *out);
```

`hir_build()`의 `structural_result`와 `loop_info` 매개변수는
5.28과 5.27의 구체적 타입이 확정된 후 정확한 타입으로 교체한다.
현재는 `const void*`로 설계하여 의존성을 최소화한다.

### 6.4 기존 ir_emit_pseudoc() 통합 방안

```c
/* codegen.c — ir_emit_pseudoc() 수정 (5.42에서 구현) */

AuraError ir_emit_pseudoc(const IrFunc *func, FILE *out)
{
    /* ... 기존 전처리 (변수 선언, 함수 시그니처) ... */

    /* HIR 경로 시도 */
    HirFunc *hir = hir_build(func, NULL, NULL, NULL);
    if (hir) {
        AuraError err = hir_emit_pseudoc(hir, out);
        hir_func_destroy(&hir);
        return err;
    }

    /* HIR 실패 시 기존 cf_emit_structured() fallback */
    return cf_emit_structured(func, out);
}
```

---

## 7. 메모리 소유권

| 구조체 | 소유자 | 해제 |
|--------|--------|------|
| `HirFunc` | `hir_build()` 호출자 | `hir_func_destroy(&func)` |
| `HirNode` (트리 전체) | `HirFunc` | `hir_func_destroy` 재귀 해제 |
| `HirSwitchCase.body` | 부모 `HirNode` | 트리 재귀 해제 |
| `HirFunc.locals[]` | `HirFunc` | `hir_func_destroy` 해제 |
| `IrFunc` (입력) | 호출자 유지 | HIR은 borrow (비소유) |

`hir_func_destroy(HirFunc **func)`:
- T** 모델 (`*func = NULL` 보장)
- 재귀적으로 모든 `HirNode` 하위 트리 해제
- `locals[]` 배열 해제

---

## 8. 제한사항 및 향후 확장

### 8.1 Phase 5 범위 제한 (formerly Phase 13)

- **HIR은 읽기 전용**: HIR 위의 최적화 패스는 post-v1.0 에서 고려
- **집합체 타입은 단층**: 중첩 구조체 (`a->b->c`)는 체인으로 표현하되 타입 시스템에서 내포 관계는 추적하지 않음
- **부동소수점**: 기본 지원하되 벡터 타입(VEC128~VEC512)의 HIR 표현은 미정

### 8.2 Post-v1.0 확장 후보

| 확장 | 설명 |
|------|------|
| HIR 최적화 패스 | HIR 수준 상수 전파, 공통 부분식 제거 |
| 패턴 매칭 고도화 | `memcpy`, `strlen` 등 관용구 인식 → 라이브러리 호출로 치환 |
| 포인터 산술 정규화 | `*(base + 4*i)` → 배열 접근 자동 추론 강화 |
| 소스 맵핑 | HIR 노드 ↔ 바이너리 주소 역방향 추적 UI |

---

## 9. 변환 예시 (End-to-End)

### 9.1 간단한 if-else 함수

```
// 기계어 (x86_64)
sub_1000:
  cmp  edi, 0
  jle  .L2
  mov  eax, edi
  add  eax, 1
  ret
.L2:
  mov  eax, 0
  ret
```

```
// Level 0: SSA IR
block_0:
  v0 = ARG(rdi)                    // a0
  v1 = CONST 0
  v2 = CMP_LE v0, v1
  BRANCH v2, block_2, block_1

block_1:
  v3 = CONST 1
  v4 = ADD v0, v3
  RET v4

block_2:
  v5 = CONST 0
  RET v5
```

```
// Level 1: HIR
HirFunc {
  name: "sub_1000"
  params: [{ name: "a0", type: int32_t }]
  return_type: int32_t
  body: HIR_SEQ [
    HIR_IF {
      cond: HIR_EXPR_BINOP(CMP_LE, HIR_EXPR_VAR("a0"), HIR_EXPR_CONST(0))
      then_body: HIR_SEQ [
        HIR_RETURN { expr: HIR_EXPR_CONST(0) }
      ]
      else_body: HIR_SEQ [
        HIR_RETURN { expr: HIR_EXPR_BINOP(ADD, HIR_EXPR_VAR("a0"), HIR_EXPR_CONST(1)) }
      ]
    }
  ]
}
```

```c
// Pseudo-C 출력
int32_t sub_1000(int32_t a0) {
    if (a0 <= 0) {
        return 0;
    } else {
        return a0 + 1;
    }
}
```

### 9.2 for 루프 + 배열 접근

```
// Level 0: SSA IR
block_0:
  v0 = ARG(rdi)                    // arr ptr
  v1 = ARG(rsi)                    // n
  v2 = CONST 0                     // sum = 0
  v3 = CONST 0                     // i = 0
  JUMP block_1

block_1:                            // loop header
  v4 = PHI(v3:block_0, v8:block_2) // i
  v5 = PHI(v2:block_0, v9:block_2) // sum
  v6 = CMP_LT v4, v1
  BRANCH v6, block_2, block_3

block_2:                            // loop body
  v7_addr = MUL v4, CONST(4)
  v7_ptr  = ADD v0, v7_addr
  v7      = LOAD v7_ptr            // arr[i]
  v9      = ADD v5, v7             // sum += arr[i]
  v8      = ADD v4, CONST(1)       // i++
  JUMP block_1

block_3:
  RET v5
```

```
// Level 1: HIR (for 승격 후)
HirFunc {
  name: "sub_2000"
  params: [{ name: "arr", type: int32_t* }, { name: "n", type: int64_t }]
  locals: [{ name: "sum", type: int32_t }, { name: "i", type: int64_t }]
  return_type: int32_t
  body: HIR_SEQ [
    HIR_ASSIGN { lhs: VAR("sum"), rhs: CONST(0) },
    HIR_FOR {
      init: HIR_ASSIGN { lhs: VAR("i"), rhs: CONST(0) },
      cond: HIR_EXPR_BINOP(CMP_LT, VAR("i"), VAR("n")),
      step: HIR_ASSIGN { lhs: VAR("i"), rhs: BINOP(ADD, VAR("i"), CONST(1)) },
      body: HIR_SEQ [
        HIR_ASSIGN {
          lhs: VAR("sum"),
          rhs: BINOP(ADD, VAR("sum"), HIR_ARRAY_INDEX(VAR("arr"), VAR("i"), 4))
        }
      ]
    },
    HIR_RETURN { expr: VAR("sum") }
  ]
}
```

```c
// Pseudo-C 출력
int32_t sub_2000(int32_t *arr, int64_t n) {
    int32_t sum;
    int64_t i;
    sum = 0;
    for (i = 0; i < n; i = i + 1) {
        sum = sum + arr[i];
    }
    return sum;
}
```

### 9.3 구조체 필드 접근

```
// Level 0: SSA IR
block_0:
  v0 = ARG(rdi)                     // struct ptr
  v1 = ADD v0, CONST(8)
  v2 = LOAD v1                      // ptr->field_8
  v3 = ADD v0, CONST(16)
  v4 = LOAD v3                      // ptr->field_16
  v5 = ADD v2, v4
  RET v5
```

```
// StructRecoveryResult:
//   SrStruct { base=v0, fields=[
//     {offset=8,  size=4, type=INT32},
//     {offset=16, size=4, type=INT32}
//   ]}

// Level 1: HIR
HIR_SEQ [
  HIR_RETURN {
    expr: BINOP(ADD,
      HIR_FIELD_ACCESS(VAR("a0"), "field_8",  offset=8,  arrow=1),
      HIR_FIELD_ACCESS(VAR("a0"), "field_16", offset=16, arrow=1))
  }
]
```

```c
// Pseudo-C 출력
int32_t sub_3000(struct_0 *a0) {
    return a0->field_8 + a0->field_16;
}
```
