# AURA Phase 4 — 심볼릭 실행 엔진 설계

> 작성일: 2026-03-29
> 상태: ✅ 확정 (2026-03-29)
> 목적: Phase 4 심볼릭 실행 모듈의 구조체, 소유권, 공개 API, 스레드 모델의 단일 기준

---

## §1 확정 결정 목록

| 결정 | 내용 | 일자 |
|------|------|------|
| D-7 분석 결과 영속 캐시 | 캐시 미사용 — Phase 4~5는 항상 재분석. 성능 문제 확인 시 post-v1.0 재결정 | 2026-03-29 |
| D-9 스레드 모델 | 단일 스레드 코어 + 큐 인터페이스 준비. 멀티스레드 전환 시 dispatcher.c만 교체 | 2026-03-29 |
| 모듈 경로 | `src/symbolic/` — core/parser/disasm과 독립된 분석 계층 | 2026-03-29 |
| 입력 인터페이스 | `FileInfo*` + `DisasmContext*` — 파서/디스어셈블러 공개 API만 소비 | 2026-03-29 |
| 추상 값 표현 | Tagged union: `{CONCRETE, uint64_t}` / `{SYMBOLIC, expr_id}` | 2026-03-29 |
| 경로 조건 저장 | 연결 리스트 (`SymConstraint`), 분기 시 복사 | 2026-03-29 |
| 상태 관리 | `SymState` — 레지스터 파일(32개) + 경로 조건 연결 리스트 + PC | 2026-03-29 |
| 소유권 계약 | `sym_engine_create/destroy` T** 모델 (parser.md 동일 패턴) | 2026-03-29 |
| Phase 4 경로 폭발 대응 | 깊이 제한(depth limit) 적용, SMT solver 미사용 | 2026-03-29 |

---

## §2 구조체 정의

### 2.1 SymVal — 추상 값

레지스터 및 메모리 셀의 값을 나타낸다. 구체적 상수이거나 심볼릭 식 ID다.

```c
/* 추상 값 종류 */
typedef enum {
    SYM_VAL_CONCRETE,   /* 구체적 상수값 */
    SYM_VAL_SYMBOLIC    /* 심볼릭 식 (향후 SMT solver 연동) */
} SymValKind;

/* 추상 값 — concrete 또는 symbolic */
typedef struct {
    SymValKind kind;
    union {
        uint64_t concrete;   /* 구체적 값 (SYM_VAL_CONCRETE) */
        uint32_t expr_id;    /* 심볼릭 식 ID (SYM_VAL_SYMBOLIC) */
    };
} SymVal;
```

**불변 조건:**
- `kind == SYM_VAL_CONCRETE`이면 `concrete` 필드가 유효하다
- `kind == SYM_VAL_SYMBOLIC`이면 `expr_id` 필드가 유효하다
- `expr_id`의 실제 식 트리는 `SymEngine` 내부 테이블이 소유한다 (4.2 구현 시 세부 확정)

### 2.2 SymConstraint — 경로 조건 노드

분기 시 선택한 조건을 연결 리스트로 누적한다.

```c
typedef struct SymConstraint {
    SymVal               cond;   /* 이 분기에서 참(true)으로 가정한 조건 */
    struct SymConstraint *next;  /* 이전 조건 (역방향 연결) */
} SymConstraint;
```

**소유권:**
- `SymState`가 `path` 포인터를 소유한다
- `sym_state_clone()`은 연결 리스트 노드를 전체 복사한다
- `sym_state_destroy()`는 모든 노드를 해제한다

### 2.3 SymState — 실행 상태

단일 실행 경로의 전체 상태를 보유한다. 분기 시 `sym_state_clone()`으로 복사한다.

```c
typedef struct {
    SymVal         regs[32];    /* 범용 레지스터 (x86_64: 16, ARM64: 31, 여유분 포함) */
    SymConstraint *path;        /* 경로 조건 연결 리스트 (헤드, NULL 허용) */
    uint64_t       pc;          /* 프로그램 카운터 (다음 실행 명령어 주소) */
    /* 메모리 맵: 4.2 구현 시 세부 확정 (희소 해시 테이블 예정) */
} SymState;
```

**레지스터 인덱스 (4.2 구현 시 매크로로 확정):**
- x86_64: RAX=0, RCX=1, RDX=2, RBX=3, RSP=4, RBP=5, RSI=6, RDI=7, R8~R15=8~15
- ARM64: X0~X30=0~30, SP=31
- 미지원 아키텍처: `AURA_ERR_NOT_SUPPORTED` 반환

### 2.4 SymEngine — 엔진 핸들 (opaque)

엔진 내부 상태를 숨기는 불투명 핸들이다. 호출자는 포인터만 보유한다.

```c
typedef struct SymEngine SymEngine;
```

내부 구현 (4.2에서 `src/symbolic/symbolic_engine.c`에 정의):
- 아키텍처 종류
- 작업 큐 (단일 스레드: 링 버퍼 또는 동적 배열)
- 심볼릭 식 테이블 (향후 SMT solver 연동 지점)

---

## §3 공개 API

`include/symbolic.h`에 선언. `aura.h`와 `disasm.h`만 의존한다.

### 3.1 엔진 생성/해제

```c
/* 엔진 생성: 아키텍처별 초기화 */
SymEngine *sym_engine_create(AuraArch arch);

/* 엔진 해제: T** 모델, *eng = NULL 보장 */
void sym_engine_destroy(SymEngine **eng);
```

**계약:**
- `sym_engine_create()`는 힙 할당 후 반환한다. 반환값 NULL이면 NOMEM
- `sym_engine_destroy(&eng)` 호출 후 `eng == NULL` 보장
- `sym_engine_destroy(NULL)` 및 `sym_engine_destroy(&NULL)` 안전 처리

### 3.2 실행 상태 생성/해제

```c
/* 상태 생성: 레지스터 전체 symbolic로 초기화, path = NULL, pc = 0 */
SymState *sym_state_create(void);

/* 상태 해제: T** 모델, *st = NULL 보장 */
void sym_state_destroy(SymState **st);

/* 상태 복사: 분기 시 호출. path 연결 리스트 전체 복사 */
SymState *sym_state_clone(const SymState *src);
```

**계약:**
- `sym_state_create()` 초기 상태: `regs[i].kind = SYM_VAL_SYMBOLIC`, `pc = 0`, `path = NULL`
- `sym_state_clone(src)` — `src`의 소유권을 가져가지 않는다 (borrow)
- `sym_state_destroy()` 호출 시 `path` 연결 리스트 전체 해제

### 3.3 단일 명령어 실행

```c
/* 단일 명령어 실행: st를 in-place 업데이트 */
AuraError sym_step(SymEngine *eng, SymState *st, const DisasmResult *insn);
```

**계약:**
- `insn`은 borrow (소유권 이전 없음)
- 분기 명령어: `st`를 한쪽 경로로 업데이트. 나머지 경로는 호출자가 `sym_state_clone()` 후 처리
- 전역 상태 없음: 동일 입력 → 동일 출력 (순수 함수에 준함)
- 미지원 명령어: `AURA_ERR_NOT_SUPPORTED` 반환, `st`는 변경하지 않음

### 3.4 작업 큐 (dispatcher 교체 지점)

```c
/* 분석할 함수 주소를 큐에 추가 */
AuraError sym_queue_push(SymEngine *eng, uint64_t func_addr);

/* 큐 처리: 단일 스레드 루프 실행 (D-9) */
AuraError sym_queue_run(SymEngine *eng);
```

**계약:**
- `sym_queue_push()` — 동일 주소 중복 추가 허용 (중복 처리는 엔진 내부에서 방지)
- `sym_queue_run()` — 큐가 빌 때까지 루프 실행 후 반환
- 멀티스레드 전환 시 이 두 함수의 구현(`dispatcher.c`)만 교체. 엔진/상태/step은 변경 없음

---

## §4 스레드 모델 (D-9)

### 4.1 현재: 단일 스레드

```
[호출자]
  │
  ├─ sym_queue_push(func_addr_1)
  ├─ sym_queue_push(func_addr_2)
  │
  └─ sym_queue_run()
       │
       └─ 내부 루프:
            while (!queue_empty) {
                addr = queue_pop();
                state = sym_state_create();
                while (depth < MAX_DEPTH) {
                    insn = next_insn(addr);
                    sym_step(eng, state, insn);
                }
                sym_state_destroy(&state);
            }
```

### 4.2 향후: 멀티스레드 전환

dispatcher.c만 교체. `sym_engine`, `sym_state`, `sym_step`은 변경 없음.

```
[호출자]
  │
  ├─ sym_queue_push(...)   (변경 없음)
  │
  └─ sym_queue_run()       ← dispatcher.c 교체
       │
       └─ thread_pool_dispatch(worker_fn, queue)
            │
            └─ 각 worker: sym_state_create() → sym_step() 반복
               (sym_step()은 전역 상태 없음 → thread-safe)
```

**엔진 설계 원칙:**
- `sym_step()`은 `SymEngine` 내부 공유 상태를 변경하지 않는다 (read-only 접근만)
- 공유 가변 상태가 필요해질 경우 atomic 또는 mutex로 보호 (4.2 구현 시 검토)
- `SymState`는 각 경로/스레드가 독립적으로 소유한다

---

## §5 파서·디스어셈블러 연결

심볼릭 엔진은 파서/디스어셈블러의 공개 API만 소비한다. 내부 헤더 참조 금지.

### 5.1 입력 흐름

```
FileInfo *fi          (file_format.h 공개 타입)
    │
    ├─ fi->arch       → sym_engine_create(fi->arch)
    ├─ fi->sections   → .text 섹션 식별 → Section.data, Section.vaddr
    └─ fi->symbols    → 함수 경계 인식 (4.5: func_detect)

DisasmContext *dc     (disasm.h 공개 타입)
    │
    └─ disasm_run(dc, section.data, section.size, section.vaddr, results, max)
           │
           └─ DisasmResult[] → sym_step(eng, state, &results[i])
```

### 5.2 아키텍처 매핑

| `fi->arch` | `sym_engine_create()` 동작 |
|------------|--------------------------|
| `AURA_ARCH_X86_64` | x86_64 레지스터 매핑 초기화 |
| `AURA_ARCH_ARM64` | ARM64 레지스터 매핑 초기화 |
| `AURA_ARCH_X86` | x86 32비트 모드 (4.2 구현 시 검토) |
| `AURA_ARCH_ARM` | ARM 32비트 (4.2 구현 시 검토) |
| `AURA_ARCH_UNKNOWN` | `AURA_ERR_NOT_SUPPORTED` 반환 |

---

## §6 리스크 및 대응

| 리스크 | 대응 |
|--------|------|
| 경로 폭발 (Path Explosion) | Phase 4: 깊이 제한(`MAX_DEPTH`) 적용. SMT solver 미사용. 경로 수 상한 설정 |
| 메모리 맵 크기 | 희소 해시 테이블 사용, 미접근 주소 lazy 초기화 (4.2 구현 시 세부 확정) |
| `SymState` 복사 비용 | 분기 시점에만 `sym_state_clone()` 호출. 직선 실행은 in-place 업데이트 |
| 재귀 함수 무한 루프 | 방문한 `(func_addr, depth)` 쌍 추적, 재방문 시 중단 |
| 미지원 명령어 | `AURA_ERR_NOT_SUPPORTED` 반환 후 skip. 분석 결과에 미처리 명령어 수 기록 |

---

## §7 Phase 4 산출물 목록

| 태스크 | 파일 | 내용 |
|--------|------|------|
| 4.1 | `docs/design/symbolic_exec.md` | 이 문서 |
| 4.1 | `include/symbolic.h` | 공개 API 헤더 |
| 4.2 | `src/symbolic/symbolic_engine.c` | 엔진 구현 + 단일 명령어 step |
| 4.2 | `tests/core/test_symbolic.c` | 단위 테스트 |
| 4.3 | `src/symbolic/cfg.c` | CFG 구성, CLI `--cfg` |
| 4.4 | `src/symbolic/dfg.c` | DFG 구성 |
| 4.5 | `src/symbolic/func_detect.c` | 함수 경계 탐지, CLI `--functions` |
| 4.T | `tests/results/4.T_symbolic.txt` | Phase 4 종합 테스트 결과 |

`src/symbolic/` 디렉터리는 4.2에서 첫 소스 파일과 함께 생성한다.
