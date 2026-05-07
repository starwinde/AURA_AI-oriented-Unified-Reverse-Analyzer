# AURA Decompiler v2 — 개선 설계 문서

> 작성일: 2026-04-05
> Phase 5: Decompiler Quality Enhancement (formerly Phase 13)

---

## 1. 현재 상태 요약

| 항목 | 현재 값 |
|------|--------|
| IR 레벨 | 단일 SSA IR (22 opcodes, 13 types) |
| 최적화 패스 | 3개 (SCCP, copy prop, DCE) |
| 제어 흐름 구조화 | 패턴 매칭 (if/while/switch) |
| 타입 추론 | 휴리스틱 (레지스터 크기 기반) |
| 아키텍처 리프터 | 6개 (수동 C 코드) |
| 코드 규모 | ~9,400 LOC / 20 모듈 |

### 핵심 문제

1. **최적화 깊이 부족**: 3개 패스로는 중복 변수, 불필요 복사, 복잡한 조건식이 Pseudo-C에 그대로 노출
2. **제어 흐름 구조화 한계**: 패턴 매칭은 간단한 구조만 처리. 복잡한 중첩/goto는 미처리
3. **타입 추론 정확도**: 휴리스틱은 모호한 케이스(같은 레지스터의 다중 용도)에서 실패
4. **단일 IR 한계**: 기계어 수준과 고급 언어 수준을 하나의 IR로 표현하면 양쪽 모두 최적이 아님

---

## 2. 설계 목표

| 목표 | 측정 지표 |
|------|----------|
| Pseudo-C 가독성 향상 | 변수 수 50% 감소, 표현식 깊이 30% 감소 |
| goto 제거 | goto 출현율 < 5% (현재 ~20%) |
| 타입 정확도 향상 | 구조체 필드 정확도 60% → 80% |
| 최적화 패스 | 3개 → 15개+ |
| 확장성 | 새 패스 추가 시 기존 코드 수정 불필요 |

---

## 3. 아키텍처 설계

### 3.1 최적화 패스 매니저

```
typedef struct PassManager PassManager;

// 패스 인터페이스
typedef struct {
    const char *name;
    AuraError (*run)(IrFunc *func);
    bool (*should_run)(const IrFunc *func);  // 선택적 gate
} IrPass;

// API
PassManager *pass_manager_create(void);
void pass_manager_add(PassManager *pm, const IrPass *pass);
AuraError pass_manager_run(PassManager *pm, IrFunc *func);
void pass_manager_destroy(PassManager **pm);
```

기본 패스 파이프라인:
```
1. SCCP (상수 전파)
2. Copy Propagation
3. Expression Simplification
4. CSE (공통 부분식 제거)
5. Condition Simplification
6. Dead Code Elimination
7. Dead Store Elimination
8. --- 반복 (fixpoint 도달까지, 최대 5회) ---
9. Phi Elimination (out-of-SSA)
10. Register Coalescing
11. Expression Reassociation
12. Loop Detection
13. Control Flow Structuring
14. Goto Elimination
15. Final Cleanup
```

### 3.2 핵심 최적화 패스

#### Copy Propagation (강화)
```
// 현재: 기본 COPY 전파만
// 개선: 체인 전파 + PHI 통과 전파
v2 = COPY v1
v3 = ADD v2, v4    →    v3 = ADD v1, v4
```

#### Expression Simplification
```
x + 0 → x
x * 1 → x
x * 0 → 0
x - x → 0
x & 0 → 0
x | 0 → x
x ^ x → 0
x << 0 → x
(x + c1) + c2 → x + (c1+c2)
-(- x) → x
```

#### CSE (Common Subexpression Elimination)
```
v1 = ADD a, b
v2 = ADD a, b    →    v2 = COPY v1
```
해시 기반 value numbering (GVN-lite).

#### Condition Simplification
```
if (x != 0) → if (x)
if (!(x == y)) → if (x != y)
if (x == 1 && x == 2) → if (false)
!(a && b) → !a || !b  (De Morgan)
```

### 3.3 제어 흐름 구조화 (Structural Analysis)

현재: 패턴 매칭 (if → while → switch 순서)
개선: **Interval 기반 구조적 분석**

```
1. Natural loop detection (back-edge 기반)
2. Loop body 식별 (loop header의 dominator tree 하위)
3. Loop 유형 분류:
   - pre-test (while) : header에 조건, body 후 back-edge
   - post-test (do-while) : body 후 조건
   - counted (for) : 인덕션 변수 + 경계 조건
4. If/else 구조화: 즉시 post-dominator까지의 region
5. Switch: 점프 테이블 + 비교 체인 통합
6. Goto 제거: 구조화 불가능한 edge만 goto로 남김
```

### 3.4 제약 기반 타입 추론 (TIE-inspired)

```
// 제약 수집
x = LOAD [ptr]           →  typeof(x) ⊆ deref(typeof(ptr))
y = ADD x, 4             →  typeof(x) = typeof(y) = integer
z = CALL printf, fmt, x  →  typeof(x) matches format spec
STORE [base+8], val      →  base is struct, field@+8 has typeof(val)

// 제약 해결 (단순 unification)
solve(constraints) → type assignment for each SSA value
```

### 3.5 High-level IR (Level 1) — 설계만

Phase 5 (formerly Phase 13) 에서는 **설계 문서만** 작성. 구현은 후속 마일스톤.

```
// Level 0 (현재): Machine-close SSA
IR_OP_ADD, IR_OP_LOAD, IR_OP_BRANCH, IR_OP_PHI ...

// Level 1 (설계): Structured IR
HIR_IF { cond, then_body, else_body }
HIR_WHILE { cond, body }
HIR_FOR { init, cond, step, body }
HIR_SWITCH { expr, cases[] }
HIR_RETURN { expr }
HIR_ASSIGN { lhs, rhs }
HIR_FIELD_ACCESS { base, field_name, offset }
HIR_ARRAY_INDEX { base, index, elem_size }
HIR_CALL { func, args[], ret_type }
```

---

## 4. 의존성 지도

```
5.22 (Pass Manager)
  → 5.23 (Copy Prop), 5.24 (Expr Simplify), 5.25 (CSE),
    5.26 (Cond Simplify), 5.35 (Dead Store), 5.37 (LICM), 5.38 (Strength Red)

5.23 + 5.24 + 5.25 + 5.26
  → 5.31 (Phi Elimination)
    → 5.32 (Register Coalescing)
      → 5.34 (Expr Reassociation)

5.27 (Loop Detection)
  → 5.28 (Structural Analysis)
    → 5.29 (Goto Elimination)
      → 5.30 (Switch Enhancement)

5.33 (Type Inference) ← independent

5.39 (HIR Design) ← independent
  → 5.40 (Structured IR Nodes)
    → 5.41 (Aggregate Types)
      → 5.42 (HIR Emission)

5.43 (Metrics) ← independent
5.44 (Round-trip Test) ← 5.42
5.T ← all
```

---

## 5. 기대 효과

| Before (baseline) | After (Decompiler v2, Phase 5) |
|-------------------|------------------|
| `int v3 = v1; int v4 = v3 + 5;` | `int v4 = v1 + 5;` |
| `if (v2 != 0) { goto L1; }` | `if (v2) {` |
| `goto L_loop_head;` | `while (i < n) {` |
| `int v7; v7 = *(int*)(v1 + 8);` | `x->field_8` |
| 변수 15개/함수 | 변수 7개/함수 |
