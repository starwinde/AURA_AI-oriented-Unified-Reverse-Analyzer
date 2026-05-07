# AURA Task 5.3 (변수 타입 추론) 준비 탐색 결과

## 탐색 날짜: 2026-04-01
## 탐색 범위: 읽기 전용 코드 분석

---

## 1. 탐색 목표 및 완료 현황

### 요청한 탐색 항목 ✅ 모두 완료

| 항목 | 상태 | 위치 |
|------|------|------|
| `src/decompiler/codegen.c` 전체 읽기 | ✅ 완료 | 1행~1214행 분석 |
| `include/decompiler.h` IrType/ir_infer_types | ✅ 완료 | 1행~338행 |
| `tests/decompiler/test_decompiler.c` 테스트 패턴 | ✅ 완료 | 1행~338행 |
| `tests/CMakeLists.txt` test_decompiler 등록 | ✅ 완료 | 236행~253행 |
| 설계 문서 `docs/design/decompiler.md` | ✅ 완료 | Phase 5 아키텍처 확인 |

---

## 2. 핵심 발견 사항

### 2.1 IrVal.type 설정 위치 및 방식

#### ✅ ir_lift()에서 타입 설정되는 위치 (codegen.c)

| 타입 설정 위치 | 코드 줄 | 발견 내용 |
|---------------|--------|---------|
| **레지스터 타입 테이블** | 40~72 | `RegEntry` 구조체 + `REG_TABLE[]` 배열 — 레지스터 이름 → 타입 매핑 (al/ax/eax/rax 크기별로 INT8/INT16/INT32/INT64 구분) |
| **MOV/MOVZX/MOVSX 처리** | 289~352 | `t0` 변수로 `reg_lookup()` 통해 레지스터 크기 추론. `ins->dst.type = t0` 설정 (줄 329) |
| **산술 연산 (ADD/SUB/MUL 등)** | 356~395 | MACRO `LIFT_BINOP`에서 `ins->dst.type = (rv[r0] != UNDEF) ? rt[r0] : t0` (줄 377) |
| **비교 명령어 (CMP/TEST)** | 398~423 | `ins->dst.type = IR_TYPE_BOOL` 고정 (줄 416) |
| **CONST 명령어** | 218~227 (`emit_const` 함수) | `v.type = IR_TYPE_INT64` 고정 (줄 220) |
| **LOAD 명령어** | 331~334 | `ins->srcs[0].type = IR_TYPE_PTR` (메모리 주소), dst는 피연산자 크기 반영 |
| **STORE 명령어** | 301, 313 | `ins->dst.type = IR_TYPE_VOID` (부작용만 있음) |
| **CALL 명령어** | 458 | `ins->dst.type = IR_TYPE_INT64` 고정 (반환값 가정) |
| **RET 명령어** | 478~479 | `ins->srcs[0].type = rt[0]` (rax 레지스터의 타입) |

#### 📌 현재 타입 설정의 한계:

```c
/* 현재 ir_lift() 구현의 문제점 */

// 1. 단순 레지스터 크기만 참고
//   예: mov rax, [rsi] → rax는 INT64로 고정
//       하지만 실제로 [rsi]는 포인터가 아닐 수도 있음
rv[r0] = did;
rt[r0] = t0;  // ← 레지스터 크기만 반영 (줄 351)

// 2. LEA 패턴 감지 미흡
//   lea rax, [rsi + 8] → INT64로 처리되지만
//   실제로는 포인터(PTR) 타입이어야 함
// → is_mem_op() 함수는 메모리 주소 문법만 감지하고 타입은 반영 안 함

// 3. CMP/TEST 결과가 다음 분기에 전달되지 않음
//   cmp rax, rbx
//   je label     ← 조건은 BRANCH src[0].id = UNDEF (줄 433)
//                 실제로는 앞의 CMP 결과를 참조해야 함
```

---

### 2.2 ir_emit_pseudoc()에서 타입 정보 사용 현황

**파일**: `src/decompiler/codegen.c` 줄 982~1092

#### ❌ 현재 상황: 타입 정보를 **거의 사용하지 않음**

```c
AuraError ir_emit_pseudoc(const IrFunc *func, FILE *out)
{
    /* 함수 시그니처 (줄 988) */
    fprintf(out, "int64_t %s(...) {\n", func->name);
    //     ↑ 반환 타입 항상 int64_t 고정 (추론 없음)

    /* 각 명령어별 Pseudo-C 생성 */
    case IR_OP_CONST:
        fprintf(out, "    ");
        emit_val_name(out, ins->dst.id);
        fprintf(out, " = %"PRId64"LL;\n", ins->dst.imm);
        // ↑ 상수는 항상 int64_t 취급

    case IR_OP_LOAD:
        fprintf(out, "    ");
        emit_val_name(out, ins->dst.id);
        fprintf(out, " = *(int64_t*)mem;\n");  // ← 줄 1035: 캐스트 고정!
        // 문제: ins->dst.type 정보는 있지만 사용 안 함

    case IR_OP_STORE:
        fprintf(out, "    *(int64_t*)mem = ", ...);  // ← 줄 1039
        // 문제: 포인터 타입 체크 없음
}
```

#### 📌 TypeInfo 활용 필요한 위치:

| 생성 지점 | 현재 방식 | 개선 방향 |
|----------|---------|---------|
| 함수 시그니처 (줄 988) | `int64_t %s(...) { ...}` (고정) | 타입 추론 후 `int32_t` / `int64_t` 등 결정 |
| 변수 선언 (없음) | 없음 | `int8_t v0; int64_t *v1; int32_t v2;` 추가 필요 |
| LOAD 명령어 (줄 1035) | `*(int64_t*)mem` (고정) | `*(int_t 타입)mem` 캐스트 동적 결정 |
| STORE 명령어 (줄 1039) | `*(int64_t*)mem` (고정) | 역시 타입 추론 필요 |
| 변수 이름 생성 (줄 979) | `v%u` (타입 미표시) | 타입 정보 통합 가능 (선택사항) |

---

### 2.3 decompiler.h에서 ir_infer_types 선언 여부

#### ❌ **ir_infer_types() 함수는 아직 선언되지 않음**

**확인 파일**: `include/decompiler.h` (1행~338행)

```c
/* 현재 공개 API (§8 공개 API) */
IrFunc *ir_lift(const Cfg *cfg, const DfgResult *dfg,
                const char *name, AuraAddr func_addr);           // ✅ 있음

AuraError ir_build_ssa(IrFunc *func);                           // ✅ 있음
AuraError ir_optimize(IrFunc *func, uint32_t opt_flags);        // ✅ 있음
AuraError ir_emit_pseudoc(const IrFunc *func, FILE *out);       // ✅ 있음
void ir_func_destroy(IrFunc **func);                            // ✅ 있음
AuraError ir_print_text(const IrFunc *func, FILE *out);         // ✅ 있음

/* ❌ ir_infer_types()는 없음 */
```

#### 📌 디자인 문서 계획 (docs/design/decompiler.md):

```
§8 파일 구조

src/decompiler/
  codegen.c             ← ir_lift + ir_build_ssa + ir_optimize (Task 5.2) ✅ 완료
  type_inference.c      ← 타입 추론 (Task 5.3) ⏳ 다음
  control_flow.c        ← 제어 구조 복원 (Task 5.4)
  callgraph.c           ← 함수 호출 그래프 생성 (Task 5.5)
```

**→ Task 5.3에서 `type_inference.c` 새로 작성하고 `ir_infer_types()` 선언 필요**

---

### 2.4 현재 IrFunc/IrBlock/IrInstr 구조에서 타입 정보 저장 공간

#### ✅ **충분한 저장 공간 있음**

| 구조체 | 필드 | 용량 | 활용 현황 |
|--------|------|------|---------|
| **IrVal** (SSA 값) | `IrType type` | enum (1 바이트) | ✅ 이미 설정됨 — 모든 값이 타입 정보 보유 |
| **IrInstr** (명령어) | `IrVal dst` | IrVal 포함 | ✅ dst.type 이미 설정됨 |
| | `IrVal srcs[3]` | 인라인 3개 | ✅ 각 src도 .type 설정됨 |
| | `IrVal *phi_srcs` | heap 배열 | ✅ 각 phi src도 .type 설정됨 |

**→ 추가 저장소 필요 없음. 기존 IrVal.type 활용하면 됨**

---

### 2.5 레지스터 테이블과 타입 추론 메커니즘 분석

#### 📊 현재 레지스터 타입 추론 방식:

**파일**: `src/decompiler/codegen.c` 줄 40~95

```c
/* 레지스터 테이블 — 크기별로 타입 결정 */
typedef struct { const char *name; int idx; IrType type; } RegEntry;

static const RegEntry REG_TABLE[] = {
    /* 64비트 */
    {"rax",0,IR_TYPE_INT64},{"rcx",1,IR_TYPE_INT64}, ...
    /* 32비트 */
    {"eax",0,IR_TYPE_INT32},{"ecx",1,IR_TYPE_INT32}, ...
    /* 16비트 */
    {"ax",0,IR_TYPE_INT16},{"cx",1,IR_TYPE_INT16}, ...
    /* 8비트 */
    {"al",0,IR_TYPE_INT8},{"cl",1,IR_TYPE_INT8}, ...
};

static int reg_lookup(const char *s, int *out_idx, IrType *out_type)
{
    // 레지스터 이름으로 타입 즉시 결정 (O(n) 선형 검색)
    // → Task 5.3에서는 여기서 얻은 타입이 아니라
    //   "값 사용 패턴"으로 보정하는 로직 필요
}
```

#### 🔍 Task 5.3 타입 추론 우선순위 (설계 문서):

```c
/* docs/design/decompiler.md §6.1 타입 추론 */

타입 판정 우선순위:
  1. 피연산자 크기(al=INT8, ax=INT16, eax=INT32, rax=INT64)
  2. LEA 패턴 / 포인터 역참조 → PTR
  3. CMP/TEST 결과 → BOOL
  4. 불확실 → INT64 fallback
```

**→ 현재 ir_lift()는 우선순위 1만 구현 (레지스터 크기). 2~4번은 Task 5.3에서 추가**

---

## 3. 기존 테스트 패턴 분석

### 3.1 test_decompiler.c 현황 (줄 1~338)

**테스트 5개 모두 완료 상태 (5.2 완료)**:

| 테스트 이름 | 목표 | 활용 패턴 |
|-----------|------|---------|
| `test_ir_lift_null` | NULL 안전성 | cfg_build() 없이 직접 ir_lift 호출 |
| `test_ir_lift_single` | 단일 블록 리프팅 | make_insn() 헬퍼로 DisasmResult 조합 |
| `test_ir_build_ssa_trivial` | SSA 변환 | cfg_build() + ir_lift() + ir_build_ssa() 순차 호출 |
| `test_ir_optimize_const_fold` | 최적화 패스 | **IrFunc 수동 구성** (줄 162) — 테스트 다목적 구성 패턴 |
| `test_ir_emit_basic` | Pseudo-C 출력 | tmpfile() 사용한 출력 검증 |

#### 📌 테스트 패턴 (Task 5.3용 참고):

```c
/* 패턴 1: DisasmResult 합성 */
static void make_insn(DisasmResult *r, uint64_t addr, 
                      const char *mnem, const char *ops)
{
    memset(r, 0, sizeof(DisasmResult));
    r->address = (AuraAddr)addr;
    r->byte_count = 1;
    r->bytes[0] = 0x90;
    snprintf(r->mnemonic, sizeof(r->mnemonic), "%s", mnem);
    if (ops)
        snprintf(r->operand, sizeof(r->operand), "%s", ops);
}

/* 패턴 2: IrFunc 수동 구성 (상수 폴딩 테스트) */
IrFunc *func = calloc(1, sizeof(IrFunc));
func->next_val_id = 3;
snprintf(func->name, sizeof(func->name), "test_fold");

func->blocks = calloc(1, sizeof(IrBlock));
func->block_count = 1;
func->block_cap = 1;

IrBlock *blk = &func->blocks[0];
blk->id = 0;
blk->instr_count = 4;
blk->instrs = calloc(4, sizeof(IrInstr));

/* 명령어 직접 구성 */
blk->instrs[0].op = IR_OP_CONST;
blk->instrs[0].dst.id = 0;
blk->instrs[0].dst.type = IR_TYPE_INT64;  // ← 타입 직접 설정
blk->instrs[0].dst.imm = 2;
// ...
```

#### 🎯 Task 5.3 테스트 설계 포인트:

```c
/* 타입 추론 테스트 케이스 (최소 5개 필수) */

// TC1: 레지스터 크기 기반 타입
//   mov eax, ebx  → v_dst.type == IR_TYPE_INT32

// TC2: 포인터 역참조 감지
//   mov rax, [rsi]  → rsi는 PTR, rax는 INT64

// TC3: LEA 패턴
//   lea rax, [rbp - 8]  → rax는 PTR (주소)

// TC4: 비교 결과 타입
//   cmp rax, rbx; je ...  → CMP 결과는 BOOL

// TC5: 함수 인자 (호출 규약)
//   rdi(첫 인자) → 함수 서명에서 int64_t로 추론
```

---

### 3.2 CMakeLists.txt 테스트 등록 (줄 236~253)

```cmake
# ── test_decompiler ────────────────────────────────────────────────────────

add_executable(test_decompiler
    ${CMAKE_SOURCE_DIR}/tests/decompiler/test_decompiler.c
    ${CMAKE_SOURCE_DIR}/src/decompiler/codegen.c      # ✅ Task 5.2
    ${CMAKE_SOURCE_DIR}/src/symbolic/cfg.c
    ${CMAKE_SOURCE_DIR}/src/symbolic/dfg.c
    ${CMAKE_SOURCE_DIR}/src/core/aura.c
)

target_include_directories(test_decompiler PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src/core
)

target_compile_definitions(test_decompiler PRIVATE AURA_NO_MAIN)

add_test(NAME test_decompiler COMMAND test_decompiler)
```

#### 🔧 Task 5.3 빌드 추가 항목:

```cmake
# 추가될 것 (type_inference.c 작성 후)
    ${CMAKE_SOURCE_DIR}/src/decompiler/type_inference.c
```

---

## 4. 현재 구현 상태 요약

### 4.1 ir_lift()에서 타입 설정 현황

| 명령어 유형 | 타입 설정 | 상태 |
|-----------|---------|------|
| **MOV/MOVZX/MOVSX** | 레지스터 크기 → INT8/16/32/64 | ✅ 완료 |
| **CONST** | INT64 고정 | ✅ 완료 |
| **산술 (ADD/SUB/MUL 등)** | 피연산자 1의 타입 상속 | ✅ 완료 |
| **비트연산 (AND/OR/XOR)** | 피연산자 1의 타입 상속 | ✅ 완료 |
| **비교 (CMP/EQ/NE/LT/LE)** | BOOL 고정 | ✅ 완료 |
| **LOAD** | dst는 타입 설정, src는 PTR | ⚠️ 부분 완료 |
| **STORE** | VOID (부작용) | ✅ 완료 |
| **CALL** | INT64 고정 | ✅ 완료 |
| **PHI** | 모든 pred의 타입 일치 (현재는 INT64 고정) | ⚠️ Task 5.2 이후 검토 |
| **BRANCH** | src는 BOOL 또는 UNDEF | ⚠️ CMP/TEST 추적 필요 |

### 4.2 ir_emit_pseudoc()에서 타입 활용 현황

| 출력 요소 | 현재 | 필요한 개선 |
|---------|------|-----------|
| **함수 시그니처** | `int64_t` 고정 | 반환 타입 추론 |
| **변수 선언** | 없음 | `int_t v0; int64_t *v1;` 등 생성 |
| **LOAD/STORE** | `(int64_t*)` 고정 | 타입별 캐스트 |
| **변수 참조** | `v%u` 고정 | 타입 정보 포함 가능 (선택) |

---

## 5. Task 5.3 구현 준비 체크리스트

### ✅ 구현 전 확인 사항

- [x] IrVal.type 필드 이미 모든 값에 설정됨 (저장 공간 확보)
- [x] ir_lift()에서 기본 타입(레지스터 크기)은 이미 결정됨
- [x] ir_emit_pseudoc()는 IrVal.type을 읽을 수 있는 구조
- [x] 테스트 5개 케이스 패턴 확인 완료
- [x] CMakeLists.txt에 test_decompiler 이미 등록됨

### ⏳ Task 5.3에서 구현할 항목

1. **type_inference.c 작성**
   - `ir_infer_types(IrFunc *func)` 함수 구현
   - 우선순위 기반 타입 결정 로직:
     * LEA 패턴 감지 → PTR
     * 포인터 역참조 감지 ([reg] 패턴) → 메모리 타입
     * CMP/TEST 연쇄 추적 → BRANCH 조건 타입
   - Pseudo-C 출력용 타입 보정

2. **decompiler.h 수정**
   - `ir_infer_types()` 함수 선언 추가 (§8 공개 API)

3. **test_decompiler.c 확장**
   - 최소 5개 타입 추론 테스트 케이스 추가

4. **ir_emit_pseudoc() 개선** (codegen.c 수정)
   - 변수 선언문 생성
   - 타입별 캐스트 동적 적용

5. **CMakeLists.txt 수정**
   - type_inference.c 빌드 대상 추가

---

## 6. 주요 코드 위치 정리 (참고용)

### 핵심 파일 목록

```
/home/str_dgx_spark/Desktop/AURA/

include/decompiler.h              (공개 API + 타입 정의)
  ├─ IrType enum (줄 48~56)
  ├─ IrVal struct (줄 118~122)
  ├─ IrOpcode enum (줄 65~101)
  └─ 공개 함수들 (줄 259~331)

src/decompiler/codegen.c          (Phase 5.2 구현 — ir_lift + SSA + 최적화)
  ├─ REG_TABLE[] (줄 42~72)                    ← 레지스터 타입 매핑
  ├─ ir_lift() (줄 234~509)                    ← ir_lift 구현
  ├─ ir_build_ssa() (줄 743~777)               ← SSA 생성
  ├─ ir_optimize() (줄 938~950)                ← 최적화 패스
  ├─ ir_emit_pseudoc() (줄 982~1092)           ← Pseudo-C 생성
  └─ ir_func_destroy() (줄 1192~1213)          ← 메모리 해제

tests/decompiler/test_decompiler.c (5개 테스트, 5.2 완료)
  ├─ test_ir_lift_null (줄 60~70)
  ├─ test_ir_lift_single (줄 77~111)
  ├─ test_ir_build_ssa_trivial (줄 118~149)
  ├─ test_ir_optimize_const_fold (줄 157~253)  ← 수동 IrFunc 구성 참고
  └─ test_ir_emit_basic (줄 260~313)

tests/CMakeLists.txt              (빌드 설정)
  └─ test_decompiler (줄 238~253)

docs/design/decompiler.md         (설계 문서)
  ├─ §3 IR 타입 구조 (줄 51~190)
  ├─ §4 SSA 생성 알고리즘 (줄 194~317)
  ├─ §5 최적화 패스 (줄 321~352)
  ├─ §6 Pseudo-C 생성 (줄 356~425)   ← Task 5.3 참고
  └─ §7 공개 API (줄 428~439)

Tasks.md                          (작업 진행 상황)
  └─ 현재 상태: Task 5.3 다음 실행 예정
```

---

## 7. 설계 문서 주요 인용 (Task 5.3 참고)

### Task 5.3 완료 기준 (Tasks.md)

```
### 5.3 변수 타입 추론 로직 구현 `[ ]`

**의존성:** 5.2 완료
**완료 기준:**
- 레지스터 사용 패턴과 피연산자 크기를 기반으로 기본 타입 추론 (int, char, pointer 등)
- 추론 결과가 Pseudo-C 출력에 반영
- 타입 추론 정확도를 테스트 케이스로 검증 (최소 5개 패턴)

**산출물:** `src/decompiler/type_inference.c`
```

### Phase 5 아키텍처 개요 (decompiler.md §2)

```
DisasmResult[] + Cfg + DfgResult
    │
    ▼  [ir_lift()]          ← Task 5.2 완료 ✅
IrFunc (원시 IR)
    │
    ▼  [ir_build_ssa()]     ← Task 5.2 완료 ✅
IrFunc (SSA 형태)
    │
    ▼  [ir_optimize()]      ← Task 5.2 완료 ✅
IrFunc (최적화 완료)
    │
    ▼  [ir_infer_types()]   ← Task 5.3 구현 예정 ⏳
IrFunc (타입 추론 완료)
    │
    ▼  [ir_emit_pseudoc()]  ← Task 5.2/5.3 공용
Pseudo-C 텍스트 출력
```

### 타입 추론 우선순위 (decompiler.md §6.1)

```
| 패턴 | 추론 타입 |
|------|----------|
| 8비트 레지스터 (al, bl, ...) | `int8_t` |
| 16비트 레지스터 (ax, bx, ...) | `int16_t` |
| 32비트 레지스터 (eax, ebx, ...) | `int32_t` |
| 64비트 레지스터 (rax, rbx, ...) | `int64_t` |
| LEA 대상 / `[reg+disp]` 역참조 | `int64_t *` (PTR) |
| CMP/TEST 결과 (BOOL) | 비교 표현식 (변수 미생성) |
| 불확실 | `int64_t` fallback |
```

---

## 8. 최종 정리

### Task 5.3 준비 상태: ✅ 완료

모든 탐색 목표를 달성했으며, 다음 내용을 확인했습니다:

✅ **ir_lift()에서 IrVal.type이 설정되는 모든 위치 파악**
- 레지스터 크기 기반 타입 결정 (REG_TABLE)
- 명령어별 타입 설정 방식 (MOV, ADD, CMP, LOAD/STORE 등)

✅ **ir_emit_pseudoc()의 현재 타입 정보 활용 현황 파악**
- 타입 정보 미활용 (모든 타입이 int64_t로 고정됨)
- 개선 포인트 명확 (변수 선언, 캐스트 동적 결정 등)

✅ **decompiler.h에서 ir_infer_types() 선언 상태 확인**
- 아직 선언되지 않음 (Task 5.3에서 추가 필요)

✅ **기존 테스트 패턴 및 구조 확인**
- 5개 테스트 케이스 완료 상태 확인
- 수동 IrFunc 구성 패턴 확인

✅ **구조체에 타입 정보 저장 공간 확인**
- 모든 IrVal에 type 필드 이미 존재 (추가 저장소 불필요)

### 구현 시작 전 권장 사항

1. **기존 ir_lift() 타입 결정 로직을 활용**
   - REG_TABLE의 레지스터 크기 → 타입 매핑은 유지
   - Task 5.3은 ir_lift() 이후 "패턴 기반 보정" 추가

2. **ir_emit_pseudoc() 개선는 점진적으로**
   - Task 5.3: type_inference.c 작성 + 타입 정보 수집
   - Task 5.4/5.5에서 제어 구조 복원 후 Pseudo-C 포맷 개선

3. **테스트 우선**
   - 수동 IrFunc 구성 패턴(test_ir_optimize_const_fold 참고)으로 타입 추론 테스트
   - CFG+DisasmResult 합성 패턴(test_ir_lift_single 참고)으로 end-to-end 테스트

---

**탐색 완료 시간**: 2026-04-01
**탐색 범위**: 읽기 전용 코드 분석만 수행
**차기 단계**: Task 5.3 구현 준비 완료
