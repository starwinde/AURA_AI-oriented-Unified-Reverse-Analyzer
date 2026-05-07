# Phase D-1 RED Tests — Irreducible CFG

> **Status**: RED design only. Implementation deferred until `ir_build_ssa`
> multi-block hardening (v1.1.x-R triage) completes.
>
> **Origin**: Codex Step C review (agentId `ac596efee19ddc1e0`, 2026-04-17)
> — "GO for Step E with RED tests only, no implementation".
>
> **Prerequisite**: v1.1.x-R 회귀 4건 (ir_build_ssa / HIR multi-block / stripped
> func_detect) 해소. 선행 없이 D-1 구현 시 취약점 중첩으로 원인 분리 불가.

---

## 1. 목적

Irreducible CFG (복수 진입점 loop) 를 decompile 하면 구조화된 pseudo-C 로 환원
불가능 → `goto` 로 emit 해야 한다 (Ghidra 동작 참조). 현재 AURA 는 structured
transformation 를 시도하여 loop header 가 복수 predecessor 를 가지는 경우
dominance 계산이 불안정. RED 테스트는 다음 3 유형의 취약한 동작을 수집한다.

## 2. 테스트 시나리오

### RED-1: Basic 2-entry loop (goto 가 필요한 classic case)

어셈블리 (AArch64 synthetic):
```
0x1000: mov x0, #0
0x1004: b   #0x1010          ; jumps into the middle of the "loop"
0x1008: add x0, x0, #1        ; loop body start
0x100C: b   #0x1010
0x1010: cmp x0, #10           ; loop condition (2 incoming edges)
0x1014: b.lt #0x1008          ; back edge
0x1018: ret
```

**기대 출력**: `goto` 문 포함된 pseudo-C. Loop header 가 2 predecessor
(0x1004, 0x100C) 를 가져 reducible 분석 불가.

**현재 예상 증상**:
- (a) SSA 구축 성공하되 HIR 가 empty if/else 출력
- (b) 또는 `ir_build_ssa` SIGSEGV (v1.1.x-R R-1 과 동일 경로)

**assertion**: 디컴파일 결과 문자열에 `goto` 또는 명시적 "irreducible" marker.

### RED-2: Nested loop with shared tail

```
0x2000: mov x0, #0
0x2004: b.eq #0x2010          ; outer entry
0x2008: add x0, x0, #1        ; outer body
0x200C: b   #0x2010           ; falls into inner-shared tail
0x2010: cmp x0, #100          ; shared by 2 loop structures
0x2014: b.lt #0x2008
0x2018: b.ne #0x2004
0x201C: ret
```

**기대**: Ghidra 대응 출력 (nested structured + trailing `goto`).
**현재**: dominance 미정의 영역 가능성.

### RED-3: Switch with fall-through (goto inevitable)

```
0x3000: cmp  w0, #1
0x3004: b.eq #0x3020
0x3008: cmp  w0, #2
0x300C: b.eq #0x3030
0x3010: b    #0x3040
0x3020: add  w1, w1, #10      ; case 1
0x3024: b    #0x3030          ; fall through to case 2
0x3030: add  w1, w1, #20      ; case 2
0x3034: b    #0x3040
0x3040: ret
```

**기대**: `switch` 나 `if-else-if` 체인 + `break` 누락으로 fall-through.
**현재**: HIR 가 case 분기 식별 실패 가능성.

## 3. 테스트 파일 배치 (Phase D-1 구현 시점)

```
tests/decompiler/test_irreducible_cfg.c   (신규, 현재 미생성)
  ├─ test_red1_basic_2entry_loop()
  ├─ test_red2_nested_shared_tail()
  └─ test_red3_switch_fallthrough()

tests/CMakeLists.txt
  └─ add_aura_test(test_irreducible_cfg ...)  (현재 미추가)
```

구현 시점 기대 assertion:
- `cfg_build` 가 crash 없이 다중 블록 CFG 생성
- `ir_build_ssa` 가 valid SSA 생성 (dominance 포함)
- HIR 가 pseudo-C 로 emit (구조화 불가 시 `goto` label 포함)
- 출력 syntax parse 가능 (`gcc -fsyntax-only` 통과)

## 4. 현재 디컴파일러 도달 범위 (예상)

| Stage | RED-1 | RED-2 | RED-3 |
|-------|-------|-------|-------|
| disasm_run | ✅ | ✅ | ✅ |
| cfg_build (Step A 이후) | ✅ | ✅ | ✅ |
| ir_lift_arm64 | 🟡 블록 수는 맞되 edge 누락 가능 | 🟡 | 🟡 |
| ir_build_ssa | ⚠️ R-1 SSA crash 가능 | ⚠️ | 🟡 부분 성공 |
| hir_build | ❌ | ❌ | ⚠️ case 분기 누락 |
| hir_emit_pseudoc | ❌ empty if/else | ❌ | ⚠️ fall-through 생략 |

## 5. 선결 작업 (implementation prerequisites)

Phase D-1 구현 전 v1.1.x-R 에서 해소되어야 하는 항목:
- **R-1**: `ir_build_ssa` dominance 계산이 forward-edge multi-block 에서 안정화
- **R-2**: HIR builder 가 BRANCH 조건이 cmp_id 인 경우 if-body 식별 정확도
- **R-3**: stripped `func_detect` 병합 취약점 (irreducible 과 별건이나 corpus 영향)

## 6. Phase D-1 DoD (Codex 참조)

`gap_analyzer.sh ... phaseD.json` 후 AURA-covered 평균 ≥ 80/100.
control_flow + naming 부분점수가 Phase C 대비 각 5점 이상 상승.

본 RED 시나리오가 Phase D-1 GREEN 판정의 기초 케이스.

## 7. 향후 활성화 체크리스트

- [ ] v1.1.x-R 해소 (R-1~R-4)
- [ ] `tests/decompiler/test_irreducible_cfg.c` 생성 + CMake 등록
- [ ] 본 문서 3 시나리오를 C 테스트로 이식 (make_insn 기반)
- [ ] RED 상태 ctest 확인 (3/3 FAIL 기대)
- [ ] D-1 구현 → GREEN 전환
- [ ] Codex D-7 review

---

**참고 커밋** (context):
- `5a06f3d` v1.1.x Post-release Maintenance 섹션 (V1.1.x-R triage 등록)
- `af2e37c` Step A cfg.c ARM64 — irreducible CFG 구축 가능 조건 마련
- `5227ea7` Step A' pipeline.c trim — cross-function 오염 방지 선행
