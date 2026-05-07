# D-Rizin: Rizin Primary Skeleton (Phase 2A / 2B 설계)

> **Status**: 설계 문서 신규 (2026-04-30). 코드 변경 0. Phase 2A (analyze) / 2B (decompile) 진입 전 binding 문서.
>
> **결정 근거**: PRD §9 D-1 (2026-04-30 결정), D-27 (subprocess-only), D-28 (co-primary 사용자 선택). rules R-1 / R-8 / R-10 / R-11 / R-12.
>
> **Inputs**:
> - Phase 1 어댑터 계약 — [include/engine_request.h](../../include/engine_request.h), [include/engine_subprocess.h](../../include/engine_subprocess.h), [include/engine_manifest.h](../../include/engine_manifest.h), [include/orchestrator.h](../../include/orchestrator.h)
> - third_party_hub skeleton — [include/third_party_hub/](../../include/third_party_hub/), [src/third_party_hub/](../../src/third_party_hub/), `docs/design/third_party_hub.md`
> - Rizin vendored — [third_party/rizin/](../../third_party/rizin/) (LGPL-3.0)
> - 기존 Ghidra adapter 패턴 — [src/adapter/ghidra/](../../src/adapter/ghidra/) (Phase 2C 로 이관)

---

## §1. 경계 한 줄 요약

- **Rizin = `disasm` / `analyze` / `decompile` / `trace` primary** (Phase 2A: analyze, Phase 2B: decompile, disasm/trace 는 후속).
- IPC = **stateless subprocess + bulk JSON extraction**. **librz 정적/동적 링크 절대 금지** (D-27 / R-10).
- 출력 = **immutable raw snapshot + normalized snapshot 2-layer**. normalized 의 모든 record 에 **provenance** (R-11) + **1 급 record 분해** (R-12).
- Rizin canonical 은 `include/third_party_hub/rizin_canonical.h` 내부 mirror 타입으로만 격리. AURA core / GUI 는 보지 않는다 (R-10).
- **AURA 내부에서 CFG / type / call graph / function boundary 자체 생성 금지** (R-9). 모든 분석 정보는 Rizin stdout JSON 에서만 유래.

---

## §2. 디렉토리·파일 매핑

```
include/
├── third_party_hub/
│   └── rizin_canonical.h        # Rizin canonical mirror 타입 (격리, R-10)
└── aura/
    └── normalized_records.h     # 1 급 record 정의 (R-12)
                                 #   FunctionRecord / BlockRecord / EdgeRecord
                                 #   VariableRecord / TypeFactRecord / CallEdgeRecord
                                 #   SymbolRecord / XrefRecord
                                 # 각 struct 첫 필드 = AuraProvenance provenance (R-11)

src/
├── adapter/
│   └── rizin/
│       ├── rizin_subprocess.{h,c}     # Phase 1 engine_subprocess 위에 argv 조립 + exit-code 매핑
│       ├── rizin_command_set.{h,c}    # bulk JSON command catalog (§4)
│       ├── rizin_framing.{h,c}        # stdout 의 command별 raw_json 분리 (§5)
│       ├── rizin_snapshot.{h,c}       # raw JSON immutable 보존 + cJSON 트리
│       ├── rizin_decompile.{h,c}      # Phase 2B: pdgj/pddj plugin 호출
│       └── rizin_adapter.{h,c}        # AuraEngineAdapter vtable (init/request/shutdown)
├── third_party_hub/
│   └── rizin_to_aura.{h,c}            # rizin_canonical → AURA normalized record 변환
│                                      #   record 1 급 분해 (R-12) + provenance 부착 (R-11)
└── core/
    └── normalized_records.c           # record 컬렉션 컨테이너 + ID 발급 + R-11/R-12 reject 로직

tests/
└── adapter/
    └── rizin/
        ├── test_rizin_subprocess.c        # spawn/timeout/SIGTERM→SIGKILL
        ├── test_rizin_framing.c           # delimiter/command_id 분리
        ├── test_rizin_command_set.c       # 카탈로그 unit
        ├── test_rizin_analyze_e2e.c       # Phase 2A e2e
        ├── test_rizin_decompile_e2e.c     # Phase 2B e2e
        ├── test_rizin_provenance.c        # R-11 provenance 누락 reject
        ├── test_rizin_record_shape.c      # R-12 record 1 급화 강제 (FunctionRecord 부속 필드 부재)
        └── test_rizin_isolation.c         # R-10 — RzCore/RzAnalysis 가 hub 외부 0 건
```

---

## §3. 통신 모델 (Subprocess + Bulk JSON)

### §3.1 호출 형태

```
rizin -q0 -c "<command1>; <command2>; ...; <commandN>; q" <binary_path>
```

- `-q` = quiet (banner 억제)
- `-0` = NULL 종료 모드 (단일 호출)
- `-c "..."` = 파이프 명령
- `q` = quit (보장)
- argv 조립은 `rizin_subprocess.c` 가 담당, spawn / drain / timeout / wait / SIGTERM→SIGKILL 격리는 Phase 1 `engine_subprocess` 재사용.

### §3.2 격리 규칙 (R-2 / R-10 / D-27)

- librz 헤더 include / 정적 / 동적 링크 **금지**.
- Rizin 바이너리는 **PATH lookup 또는 manifest exec_path 명시** 로 발견 (벤더된 `third_party/rizin/` 의 사용자-빌드 결과 또는 시스템 설치).
- 자식 프로세스 stdin / stdout / stderr 만 접촉. 공유 메모리 / dlopen / RPATH 트릭 금지.
- 한 request 당 1 spawn. batch (다수 함수 한 번에) 는 Phase 후속에서 검토.

---

## §4. Bulk JSON Command Catalog

### §4.1 analyze 경로 (Phase 2A)

| command | 출력 | 1 급 record 매핑 |
|---|---|---|
| `aaa` | (분석 트리거, 출력 없음) | — |
| `aflj` | function list (JSON array) | `FunctionRecord[]` |
| `agfj <addr>` | function CFG (basic blocks + edges) | `BlockRecord[]` + `EdgeRecord[]` (per function) |
| `isj` | symbol list | `SymbolRecord[]` |
| `iij` | imports | `SymbolRecord[]` (kind=IMPORT) |
| `izj` | strings | `SymbolRecord[]` (kind=STRING) |
| `axtj <addr>` | xrefs to address | `XrefRecord[]` + `CallEdgeRecord[]` (call-targeted xref) |
| `afvj <addr>` | function locals/args | `VariableRecord[]` |
| `aftj <addr>` | function type signature | `TypeFactRecord[]` (return + params) |
| `tj` | global types | `TypeFactRecord[]` |

### §4.2 decompile 경로 (Phase 2B)

| command | 전제 plugin | 출력 | 매핑 |
|---|---|---|---|
| `pdgj <addr>` | rz-ghidra | Ghidra-backed Pseudo-C JSON | decompile body + line↔addr map → record |
| `pddj <addr>` | jsdec | jsdec Pseudo-C JSON | 동일 (대체 plugin) |

Plugin 가용성은 어댑터 init 시 `rizin -e cmd.pdg=?` 로 검사. 둘 다 부재 → manifest `decompile` 비트 OFF (graceful degrade).

### §4.3 trace 경로 (후속)

| command | 매핑 |
|---|---|
| `axtj <addr>` (역방향), `axfj <addr>` (정방향) | def↔use 관계 → `XrefRecord` 그래프 view |

---

## §5. Stdout Framing 정책

### §5.1 문제

`rizin -c "aflj; agfj 0x401000; isj"` 는 **stdout 에 JSON 덩어리들이 그대로 이어붙는다**. `]` 다음 바로 `[` 가 와서 cJSON 단일 파싱 불가 + 어느 command 의 출력인지 혼동.

### §5.2 해결: 명시 delimiter framing

각 command 사이에 `?e` (echo) 명령으로 **명시 delimiter line** 을 끼운다:

```
rizin -q0 -c "
  ?e ===AURA-BEGIN:aflj===;
  aflj;
  ?e ===AURA-END:aflj===;
  ?e ===AURA-BEGIN:isj===;
  isj;
  ?e ===AURA-END:isj===;
  q
" <binary>
```

`rizin_framing.c` 가 stdout buffer 를 라인 단위로 스캔하여:

```c
typedef struct {
    char       command_id[32];       /* "aflj" / "isj" / "agfj@0x401000" 등 */
    const char *raw_json;            /* delimiter 사이 본문, immutable view */
    size_t      raw_json_len;
} AuraRizinFrame;

typedef struct {
    AuraRizinFrame *frames;
    size_t          frame_count;
    char           *raw_buffer;      /* 전체 stdout 보존 (R-4) */
    size_t          raw_buffer_len;
} AuraRizinSnapshot;     /* immutable raw snapshot */
```

### §5.3 framing 정책 강제

- 모든 command 출력은 `===AURA-BEGIN:<id>===` ↔ `===AURA-END:<id>===` 사이에만 인정.
- delimiter 누락 / 짝맞지 않음 → ingestion reject (R-11 provenance.completeness 0 으로 표시).
- delimiter 충돌 회피: Rizin escape 처리 — binary path 나 사용자 입력에 delimiter 문자열 등장 금지 (어댑터 측에서 sanitize).
- command_id = 사용자 코드 (본 문서 §4.1 표 key) + 인자 hash. 동일 command 가 여러 함수에 호출될 때 unique 보장.

### §5.4 raw_buffer = R-4 보존

`AuraRizinSnapshot.raw_buffer` 는 **stdout 원본 전체** 를 그대로 저장한다 (delimiter 포함). framing 분리는 view 만 — 원본 변형 / 일부 폐기 금지 (R-4).

---

## §6. 2-Layer Snapshot 구조

```
                   Rizin subprocess
                          │
                          │ stdout (delimited bulk JSON)
                          ▼
              ┌──────────────────────────┐
              │  AuraRizinSnapshot       │  ← immutable raw snapshot (R-4)
              │   .raw_buffer (stdout)   │
              │   .frames[] (views)      │
              └────────────┬─────────────┘
                           │
                           │ rizin_to_aura.normalize()
                           ▼
              ┌──────────────────────────┐
              │  AuraNormalizedSnapshot  │  ← normalized snapshot (R-11/R-12)
              │   .functions[]           │     FunctionRecord with provenance
              │   .blocks[]              │     BlockRecord with provenance
              │   .edges[]               │     EdgeRecord with provenance
              │   .variables[]           │     VariableRecord with provenance
              │   .type_facts[]          │     TypeFactRecord with provenance
              │   .call_edges[]          │     CallEdgeRecord with provenance
              │   .symbols[]             │     SymbolRecord with provenance
              │   .xrefs[]               │     XrefRecord with provenance
              └────────────┬─────────────┘
                           │
                           ▼
                AuraEngineResponse {
                    .body = normalized,
                    .raw  = raw_snapshot
                }
```

### §6.1 record 1 급 분해 (R-12)

`FunctionRecord` 는 다음 부속 필드를 **갖지 않는다** (위반 시 ingestion reject):

```c
/* 금지 — R-12 위반 */
struct FunctionRecord_BAD {
    AuraAddr        entry;
    char            name[256];
    VariableRecord  variables[/* ... */];   /* ✗ 평탄화 */
    TypeFactRecord  types[/* ... */];       /* ✗ */
    CallEdgeRecord  calls[/* ... */];       /* ✗ */
    BlockRecord     blocks[/* ... */];      /* ✗ */
};
```

올바른 형태:

```c
typedef struct {
    AuraAddr     entry;
    uint32_t     function_id;       /* 안정 ID — record 간 참조 키 */
    char         name[256];
    /* 부속 정보 일체 없음 — 별도 컬렉션에서 function_id 로 조회 */
    AuraProvenance provenance;
} FunctionRecord;

typedef struct {
    uint32_t     block_id;
    uint32_t     function_id;       /* FK */
    AuraAddr     start_addr;
    AuraAddr     end_addr;
    AuraProvenance provenance;
} BlockRecord;

typedef struct {
    uint32_t     edge_id;
    uint32_t     from_block_id;
    uint32_t     to_block_id;
    AuraEdgeKind kind;              /* engine 에서 직접 유래 — AURA 추정 금지 (R-9) */
    AuraProvenance provenance;
} EdgeRecord;

typedef struct {
    uint32_t     var_id;
    uint32_t     function_id;       /* FK */
    char         name[64];
    uint32_t     type_fact_id;      /* FK to TypeFactRecord */
    AuraProvenance provenance;
} VariableRecord;

typedef struct {
    uint32_t     type_fact_id;
    uint32_t     subject_kind;      /* 0=variable, 1=return, 2=field, 3=global */
    uint32_t     subject_id;        /* var_id 또는 function_id 또는 ... */
    char         type_str[256];     /* engine 에서 받은 타입 문자열 그대로 */
    AuraProvenance provenance;
} TypeFactRecord;

typedef struct {
    uint32_t     call_edge_id;
    uint32_t     caller_function_id;
    AuraAddr     call_site_addr;
    AuraAddr     callee_addr;
    uint32_t     callee_function_id;    /* 0 if external */
    AuraProvenance provenance;
} CallEdgeRecord;

typedef struct {
    uint32_t     symbol_id;
    AuraAddr     addr;
    char         name[256];
    AuraSymbolKind kind;            /* FUNCTION / IMPORT / EXPORT / STRING / GLOBAL */
    AuraProvenance provenance;
} SymbolRecord;

typedef struct {
    uint32_t     xref_id;
    AuraAddr     from_addr;
    AuraAddr     to_addr;
    AuraXrefKind kind;              /* CALL / JUMP / DATA / ... — engine 직접 유래 */
    AuraProvenance provenance;
} XrefRecord;
```

### §6.2 Provenance schema (R-11)

```c
typedef struct {
    char    source[16];          /* engine_id, e.g. "rizin", "ghidra", "retdec" */
    float   confidence;          /* 0.0 ~ 1.0 — engine 이 명시한 경우 직접 사용,
                                    아닌 경우 engine 별 default (rizin aaa = 0.85,
                                    aaaa = 0.95, raw = 0.5 등). hub 내부 격리. */
    float   completeness;        /* 0.0 ~ 1.0 — 해당 record 가 engine 응답에서
                                    완전히 채워졌는지 (필수 필드 누락 = <1.0).
                                    delimiter 깨짐 / OOM 등 = 0.0. */
} AuraProvenance;
```

- record 단위로 부착 (개별 필드 단위 아님).
- ingestion 단계에서 `source` 누락 = reject. `confidence` / `completeness` 가 0 인 record 는 normalized snapshot 에 포함되되 GUI 가 시각적으로 구분 표시.

### §6.3 record 컬렉션 컨테이너

```c
typedef struct {
    FunctionRecord  *functions;
    size_t           function_count;
    BlockRecord     *blocks;
    size_t           block_count;
    EdgeRecord      *edges;
    size_t           edge_count;
    VariableRecord  *variables;
    size_t           variable_count;
    TypeFactRecord  *type_facts;
    size_t           type_fact_count;
    CallEdgeRecord  *call_edges;
    size_t           call_edge_count;
    SymbolRecord    *symbols;
    size_t           symbol_count;
    XrefRecord      *xrefs;
    size_t           xref_count;
} AuraNormalizedSnapshot;
```

각 컬렉션은 별도 배열로 분리 — `FunctionRecord` 안에 `variables[]` 포인터로 임베드 금지 (R-12). 관계는 `function_id` / `block_id` / `var_id` 등 안정 ID 로만 표현.

---

## §7. third_party_hub 통합점

### §7.1 변환 layer

```c
/* src/third_party_hub/rizin_to_aura.h */
int rizin_to_aura_normalize(
    const AuraRizinSnapshot     *raw_in,        /* immutable */
    AuraNormalizedSnapshot      *normalized_out, /* alloc'd by caller, populated here */
    const char                  *source_engine_id /* "rizin" */
);
```

- 입력: §5 의 framed raw snapshot
- 출력: §6 의 record 컬렉션
- 변환 중 record 1 급화 (R-12) + provenance 부착 (R-11) 강제. 위반 시 즉시 reject.

### §7.2 `AURA_ENABLE_RIZIN_HUB` CMake 옵션

- 현재 default = **OFF** (third_party_hub.md §5 skeleton 그대로).
- Phase 2A e2e GREEN 후 default → ON 전환 결정 = **D-29 미결**. 본 문서는 default 변경을 강제하지 않는다.

### §7.3 Hub mirror 타입은 hub 외부에서 보이지 않는다 (R-10)

- `include/third_party_hub/rizin_canonical.h` 의 `aura_tp_function_t` / `aura_tp_op_t` / `aura_tp_section_t` 등은 hub 안에서만 사용.
- core / GUI / Unified IR 의 `#include` 그래프에 위 헤더가 등장 금지 — CI grep guard 추가 권장 (Phase 2A.9).

---

## §8. 검증 계획

### §8.1 Phase 2A 단위·통합 테스트

| Test | 목적 | 통과 조건 |
|---|---|---|
| `test_rizin_subprocess` | spawn / timeout / SIGTERM→SIGKILL | Phase 1 `engine_subprocess` conformance + rizin exit-code 매핑 |
| `test_rizin_framing` | delimiter 분리 정확성 + 깨짐 reject | 정상 case ≥10 + 깨짐 case ≥5 모두 예상 동작 |
| `test_rizin_command_set` | catalog 호출 인자 sanitize | 인자에 delimiter 문자열 등장 시 reject |
| `test_rizin_analyze_e2e` | 작은 ELF 1 개로 full ingestion | `tests/data/elf/hello` 함수 ≥3, CFG ≥1, 심볼 ≥1, 모든 record provenance 채워짐 |
| `test_rizin_provenance` | R-11 강제 | provenance 누락 record 생성 시 reject |
| `test_rizin_record_shape` | R-12 강제 | `offsetof` static assert (provenance must be first, all 8 records) + runtime size budget ceiling / member-shape guard (FunctionRecord 에 variables·calls·types 부속 배열·포인터 미존재). `_Static_assert(sizeof)` 단독 방식 아님. |
| `test_rizin_isolation` | R-10 강제 | grep `RzCore\\|RzAnalysis` 가 `src/adapter/rizin/`, `include/third_party_hub/rizin_canonical.h` 외부에 0 건. `nm build-rel/aura` 에 librz 심볼 0 건 |

### §8.2 Conformance 통합

기존 `tests/orchestrator/test_orchestrator_dispatch.c::case_isolation` 에 rizin fake adapter 추가:
- request type guard (R-7) — 미지원 type reject
- crash isolation — fake rizin SIGSEGV → 다른 엔진 / AURA 본체 영향 0

### §8.3 Phase 2B 단위·통합 테스트

| Test | 목적 | 통과 조건 |
|---|---|---|
| `test_rizin_decompile_e2e` | `pdgj` 또는 `pddj` 1 함수 | Pseudo-C 본문 비어있지 않음 + 라인↔주소 매핑 ≥90% |
| `test_orchestrator_dual_decompile_primary` | decompile co-primary 동작 | rizin / ghidra 동시 등록 가능, 명시 engine_id 선택 100% 정확 |
| `test_ghidra_decompile_regression` | 기존 Ghidra decompile 회귀 0 | 2C 이관 후 manifest scope 축소 + 기존 e2e 동등 |

### §8.4 CLI 검증

```bash
# Phase 2A
build-rel/aura --engine=rizin --analyze tests/data/elf/hello
# → 함수 목록 / CFG 노드 수 / provenance summary

# Phase 2B
build-rel/aura --engine=rizin --decompile tests/data/elf/hello --addr 0x401000
# → Pseudo-C 본문

# Phase 2C 회귀
build-rel/aura --engine=ghidra --decompile tests/data/elf/hello --addr 0x401000
# → 기존 출력 동등

# Dual primary 사용자 default
build-rel/aura --decompile tests/data/elf/hello --addr 0x401000
# → settings.decompile.preferred_engine 에 따라 rizin 또는 ghidra (D-28)
```

### §8.5 R-10 / R-11 / R-12 정적 검증

```bash
# R-10 — Rizin canonical leak 검사
grep -rE "RzCore|RzAnalysis|Rz[A-Z][a-zA-Z]+" src/core src/gui include \
  | grep -v "include/third_party_hub/rizin_canonical.h" \
  | grep -v "src/adapter/rizin/" \
  | grep -v "src/third_party_hub/rizin_to_aura"
# → 0 건

# librz 링크 0 건
nm build-rel/aura 2>/dev/null | grep -E "rz_core_|rz_analysis_" | head
# → 0 건

# R-11 / R-12 — 컴파일 타임
# include/aura/normalized_records.h 안의 _Static_assert 가 부속 배열 부재 강제
```

---

## §9. 준수 매트릭스 (R-1 ~ R-12)

| 규칙 | 본 설계의 준수 방식 |
|---|---|
| R-1 (자체 구현 금지) | Rizin stdout JSON 만 ingestion. AURA 측 명령어 해석 / 분석 패스 0. |
| R-2 (Stateless subprocess) | 한 request 당 1 spawn, 상태는 AURA snapshot 에 보관. |
| R-3 (Adapter 격리) | Rizin 코드는 `src/adapter/rizin/` 만. core / GUI 무관. |
| R-4 (Output non-discard) | `AuraRizinSnapshot.raw_buffer` 에 stdout 원본 전체 보존. delimiter 포함, 변형 0. |
| R-5 (Override 불변성) | 본 phase 범위 외 (Phase 4). adapter 가 raw 변형 안 함. |
| R-6 (UI ↛ Engine 직통 금지) | UI 는 Orchestrator API 만 호출. rizin spawn 은 adapter 책임. |
| R-7 (Request type 표준) | 4 종 (`disasm`/`analyze`/`decompile`/`trace`) 외 정의 없음. |
| R-8 (Type-별 primary 집합) | Rizin = `disasm`/`analyze`/`trace` 단독 primary, `decompile` = Ghidra 와 동률 co-primary. secondary 가 덮어쓰지 않음. |
| R-9 (파생 분석 금지) | edge.kind / call_edge 등 모두 Rizin 응답에서 직접 채움. AURA 추정 0. |
| R-10 (Engine canonical leak 금지) | librz 링크 금지 (D-27). canonical mirror 는 `include/third_party_hub/rizin_canonical.h` 안에만. CI grep guard. |
| R-11 (Provenance 강제) | 모든 normalized record 에 `{source, confidence, completeness}` 부착. 누락 = reject. |
| R-12 (Record 1 급화) | 8 종 record (Function/Block/Edge/Variable/TypeFact/CallEdge/Symbol/Xref) 독립 컬렉션. `FunctionRecord` 부속 배열 / 포인터 0. compile-time `_Static_assert`. |

---

## §10. 미해결 / 후속 결정

1. **Plugin 1 차 선택** — Phase 2B 의 `pdgj` (rz-ghidra) vs `pddj` (jsdec). rz-ghidra 가 Ghidra 12.0.4 와 결과 형식 정렬 측면에서 우세 추정. 1 binary fixture 비교 후 결정.
2. **Confidence default 표** — Rizin command 별 default confidence (예: `aaa`=0.85, `aaaa`=0.95) 구체값. 1 차 hardcode 후 Phase 7 multi-engine compare 시점에 조정.
3. **Disasm / trace primary 도입 시점** — Phase 2A/2B 는 analyze + decompile. disasm primary 와 trace primary 는 후속 (Phase 2D / 2E 후보) — request type 추가 시점 결정 필요.
4. **`AURA_ENABLE_RIZIN_HUB` default 전환** — D-29 미결. Phase 2A e2e GREEN 후 결정.
5. **rizin 바이너리 발견 정책** — 시스템 PATH lookup vs `third_party/rizin/build/binrz/rizin/rizin` 명시 vs manifest exec_path 사용자 설정. 빌드 / CI / 사용자 환경 모두 커버하는 fallback 순서 정의 필요.
6. **Batch mode** — 한 spawn 으로 N 함수 decompile. 성능 이점 vs framing 복잡도. Phase 8 (Performance) 에서 결정.

---

## §11. Cross-references

- PRD §9 D-1 / D-27 / D-28 / D-29 — 본 설계의 결정 source
- rules R-1 / R-8 / R-9 / R-10 / R-11 / R-12 — 본 설계가 강제하는 규칙
- Tasks Phase 2A / 2B / 2C — 본 설계가 binding 입력
- `docs/design/third_party_hub.md` — Rizin canonical mirror 격리 정책 (수정 후)
- `docs/design/pipeline_flows.md` — 파이프라인 다이어그램 (수정 후)
- `docs/design/d28_ghidra_hir_mapping.md` / `d29b_semantic_mapping.md` — Ghidra co-primary scope (decompile only) 로 재해석
- Phase 1 산출물 — [include/engine_request.h](../../include/engine_request.h), [include/engine_subprocess.h](../../include/engine_subprocess.h), [src/core/orchestrator.c](../../src/core/orchestrator.c)
- 기존 패턴 reference — [src/adapter/ghidra/ghidra_adapter.c](../../src/adapter/ghidra/ghidra_adapter.c)
- Vendored — [third_party/rizin/](../../third_party/rizin/)

---

## §12. Sign-off

본 문서는 D-1 (Rizin primary, 2026-04-30) / D-27 (subprocess-only) / D-28 (decompile co-primary 사용자 선택) 결정의 **binding 설계 산출물**이다. Phase 2A / 2B 진입은 본 문서 main merge 후 시작된다. 본 설계 변경 시 PRD §9 별도 D-결정 등재 + rules / Tasks 동기 갱신 필요.
