# D-29B: Ghidra XML → AURA HIR Semantic Mapping (설계 turn 산출물)

> **Scope re-statement (2026-04-30 pivot)**: 본 문서의 Ghidra → HirFunc 변환은 D-1 (2026-04-30 결정) 이후 **decompile co-primary 한정** 이다 (Rizin 와 동률, 사용자 선택). analyze / disasm / trace primary 는 Rizin (Phase 2A). 본 문서의 §3 Tier A 매핑은 Ghidra **decompile request 응답 XML** 에 한해 유효하며, Rizin 결과의 Unified Model ingestion 은 별도 `d_rizin_skeleton.md` 정책 (R-11 provenance + R-12 1 급 record) 을 따른다. 본 문서가 정의한 `HirFunc` ABI 는 Ghidra co-primary 경로의 출력 형태이며, AURA 정규화 record set (`FunctionRecord` / `BlockRecord` / ...) 의 1 entry source 이다.
>
> **Status**: 사용자 승인 (2026-04-27). 코드 변경 0. D-28 mapping table을 *실 구현 가능한 단위*로 분해한 binding 문서.
>
> **승인 결정** (§2 권장안 전부 채택):
> - §2.1 = **A** — Step A1 첫 commit 에서 AuraGhirFunc 폐기 (chore commit)
> - §2.2 = **P1** — D-28 verbatim (Tier C diagnostic + Tier B silent unsupported_mnems)
> - §2.3 = **G1** — step별 누적 gate
> - §2.4 = 설계서 §3-§4 (Tier A/B IN-scope) + §9 (D-29C+ OUT-scope) 기준 유지
> - §3.4 Step A4 ABI = **D-28b `AuraCallingConv` (7 enum, main `74808ab`) 기준** — D-28 §6.3 의 `HirCallConv` (8 enum) 설계는 superseded
> - §9 OUT 분리 = `addr_space` / `return_storage` / `param_storage[16]` ABI 는 **D-29B 제외, D-29C+ 별도 turn 또는 v2.5.0 release** 에서 도입
>
> **Inputs**:
> - D-28 매핑 표 — `docs/design/d28_ghidra_hir_mapping.md` (834 LOC, main `40b0e47`)
> - D-29A bridge skeleton — `include/ghidra_subprocess.h` / `ghidra_xml_normalize.h` / `ghidra_xml_to_hir.h` (main `3ec7af9`)
> - HirFunc 현재 ABI — `include/hir.h` (D-28b 머지 후, calling_conv/is_vararg/is_noreturn 추가됨)
> - Ghidra opcodes — `third_party/ghidra-decompile/cpp/opcodes.hh` (73 unique CPUI_*)
> - AURA IrOpcode — `include/decompiler.h` (51 IR_OP_*)
>
> **Output gate**: D-29B 본 turn 사용자 승인 → D-29B Step A1 RED-first 진입.

---

## §1. Executive summary

D-29A bridge skeleton(turns #2-#7)는 **structural** mapping만 마쳤다 — `<doc>/<function>/<block>/<op>` 4 element를 `AuraGhirFunc{name?, blocks[], ops[]}` bridge-local 구조로 변환. semantic 의미는 0.

D-29B는 D-28 매핑 표(60 element / 74 P-Code op)의 **Tier A 핵심 + Tier B CFG**를 실 구현으로 전환한다. Tier C critical drop은 *fix* 가 아닌 *diagnostic emission framework* 만 도입 — 실제 fix는 D-29C 이후로 분리.

**경계 한 줄 요약**:
- D-29B = "Ghidra XML 의미를 AURA HirFunc로 정상 변환" + "critical drop을 silent으로 두지 않음"
- D-29C+ = "critical drop 자체를 해소" (jumptable parse, struct layout cross-verify, indirect call resolution, PE/Mach-O, batch mode)

---

## §2. 사용자 결정 매트릭스 (4 항목)

> 본 §2의 모든 결정은 D-29B 진입 전 사용자 명시 승인 필요.

### §2.1 결정 1: AuraGhirFunc → HirFunc 통합 시점

**Context**: D-29A 가 의도적으로 production HirFunc를 우회하고 bridge-local `AuraGhirFunc` 만 산출한 이유 = "structure 검증 우선, semantic 침범 금지". D-29B는 semantic을 시작하므로 통합이 필요하다.

| Option | 설명 | Pros | Cons |
|---|---|---|---|
| **A — Step A1과 동시 통합** (권장) | 첫 RED부터 IrFunc/HirFunc 직접 산출. AuraGhirFunc는 D-29B 종료 시 폐기. | D-28 §2 다이어그램과 1:1 일치 / 중복 layer 없음 / 영속 키 (§8) 통합 즉시 적용 | D-29A 4-element mapper 코드 즉시 폐기 (단, 60 LOC 미만 — 비용 작음) |
| **B — Tier A 종료 시 일괄 통합** | A1-A5 동안 AuraGhirFunc 유지, 종료 시 변환 함수로 일괄 lift | D-29A 결과 보존 | 두 layer 동시 유지 → 영속 키 충돌 위험 / Tier A 검증이 AuraGhirFunc 단위 → HirFunc 단위 재검증 필요 |
| **C — 영구 parallel** | AuraGhirFunc + HirFunc 양쪽 유지 | rollback 용이 | 영구 기술부채 / 영속 키 둘 |

**권장 = Option A**. 사유: AuraGhirFunc는 *structure proof* 단발 산출물 — D-29B 진입과 동시에 그 역할이 끝남. parallel 유지 시 D-28 §8 영속 키 (function_addr / origin_addr / op_index_in_block / var_role) 가 두 layer 사이에서 분기.

**물리적 영향**:
- `src/decompiler/ghidra_xml_to_hir.cpp` (D-29A turn #7, 161 LOC) → 폐기
- `include/ghidra_xml_to_hir.h` (D-29A turn #7) → 폐기
- `tests/decompiler/test_ghidra_xml_to_hir.c` (D-29A turn #7) → 폐기
- ctest 4 cases 폐기 (regression count −4)
- 신규 mapper는 `src/decompiler/ghidra_to_aura_ir.cpp` (Step A1) 로 출발 → IrFunc 직출

**대안 mitigation** (Option A 우려 시): AuraGhirFunc는 *Step A1 RED 단계의 reference oracle* 로 잠시 유지 후 Step A2 진입 시 폐기. 단 PR 한 개 이상 차이 두지 않음.

### §2.2 결정 2: 미지원 opcode 처리 정책

**Context**: D-28 §4.2 = 30 opcode 미커버 (74 중). 미커버 = (a) Tier C critical (INDIRECT/BRANCHIND/CALLIND), (b) Tier B floats (15 op), (c) Tier A safe (Java/JVM/segment/CALLOTHER).

| Policy | (a) Tier C | (b) Tier B | (c) Tier A |
|---|---|---|---|
| **P1 — D-28 verbatim** (권장) | IR_OP_UNSUPPORTED + diagnostic critical + harness hard fail | IR_OP_UNSUPPORTED + `unsupported_mnems` 누적 (silent) | 동일 (silent) |
| **P2 — Hard fail any unsupported** | abort 전체 | abort 전체 | abort 전체 |
| **P3 — Silent skip** | silent | silent | silent |

**권장 = P1**. D-28 §4.2 + §13 표 그대로. P2는 Phase 1 entry조차 차단 (실 binary는 항상 부동소수점 함수 포함). P3는 사용자 가시성 박탈.

**Diagnostic 발생 시 sink** (D-28 §13.3):
- runtime: `stderr` line-prefixed `AURA-DIAG: <reason> @<func_addr>`
- aggregate: `tests/fixtures/ghidra_golden/<binary>.diagnostics.xml` 누적
- GUI: `HirFunc.diagnostics[]` field (D-29B 신규 필드)

**HirFunc.diagnostics[] 신규 필드** (Step A4 또는 별도 commit):
```c
typedef struct {
    char     reason[32];       /* §13.2 reason key */
    AuraAddr func_addr;
    AuraAddr op_addr;          /* 0 = function-level */
    char     detail[128];
} HirDiagnostic;

/* HirFunc 추가 */
HirDiagnostic *diagnostics;
uint32_t       diagnostic_count;
uint32_t       diagnostic_cap;
```

**OOM 정책**: diagnostic 배열 alloc 실패 시 *해당 diagnostic만* drop, 함수 변환은 계속. 최후 옵션으로 `unsupported_mnems` 끝에 `<DIAG-OOM>` 표시.

### §2.3 결정 3: ≥95% coverage gate 적용 방식

**Context**: D-28 §7 = T1-T5 per-tier ≥95% (평균 금지) + Tier C ack count = total. 본 절은 *D-29B 진행 중* gate 적용 단위 결정.

| Granularity | 설명 | Pros | Cons |
|---|---|---|---|
| **G1 — Step별 gate** (권장) | A1 종료 = T1만 ≥95%, A2 종료 = T2 추가, ... 누적 | 점진 검증 / 회귀 즉시 발견 / merge 단위 작음 | 초기 step에서는 일부 gate 미적용 |
| **G2 — D-29B 종료 시 일괄 gate** | 전 step 머지 후 T1-T5 일괄 측정 | 한 번에 명확한 verdict | 회귀 발견 늦음 / merge 단위 큼 |
| **G3 — PR별 gate** | PR마다 T1-T5 모두 측정 | 가장 엄격 | 초기 step PR이 못 통과 (가용 fixture 부족) |

**권장 = G1 (step별 누적 gate)**. 사유: D-29A turn 단위 PR 패턴(#46) 유지. 각 step PR은 *해당 step이 활성화하는 tier*만 검증. 모든 tier는 Step B2 종료 시점 (D-29B 마지막 step) 에 일괄 검증.

**Step별 gate 매핑**:
| Step | Activates | Gate |
|---|---|---|
| A1 (varnode → IrVal) | T1 element | T1 ≥95% on `<varnodes>` subtree |
| A2 (op → IrInstr) | T2 op | T2 ≥95% on `<op>` |
| A3 (highsymbol → HirLocal/Param) | T4 var name | T4 ≥95% (3 fixture) |
| A4 (prototype → HirFunc.cc/vararg/noreturn) | per-fixture verify | calling_conv match 100% on fixture |
| A5 (typeref → HirType) | T1 element | T1 ≥95% on `<type>`/`<typeref>` |
| B1 (block → CFG edge) | edge.kind | edge.kind heuristic ≥99% (D-28 §5) |
| B2 (terminator → CFG terminator) | T3 + T5 | T3 ≥95% + T5 ≥95% |
| **D-29B 종료 gate** | All | T1∧T2∧T3∧T4∧T5 ≥95% AND Tier C unacknowledged = 0 |

### §2.4 결정 4: Tier A/B/C 경계 확정 (D-29B IN/OUT)

**Context**: D-28 §3 매핑 표는 60 element를 Tier A/B/C로 분류. D-29B는 *어떤 Tier 항목까지 fix 하고 어떤 항목을 D-29C+ 로 defer 하는지* 명시 필요.

#### IN-scope (D-29B 필수)

**Tier A core mapping** (D-28 §3.1-3.5):
- 3.1.1, 3.1.3, 3.1.5 (`<function>` container + name + nocode flag)
- 3.2.3-3.2.7 (`<addr>` varnode definition: id/sort/size/ref)
- 3.2.10 (`<addr @input>` → HirParam.ssa_id)
- 3.3.1, 3.3.3 (`<block @index>` + `<blockedge>`)
- 3.4.1 (Step A2: `<op @code>` → IR_OP_*)
- 3.4.3-3.4.5 (`<op>` dst/srcs)
- 3.5.1-3.5.3 (`<high @class="local|param|global">`)
- 3.5.7 (`<high><addr>` instances → name dedup)

**Tier A type mapping** (D-28 §3.6.1-3.6.7):
- typeref/typeref id (string copy with diagnostic)
- int/uint/char/float/double/ptr/array — name 변환 + size

**Tier A prototype** (D-28 §3.7.1-3.7.3):
- @model → calling_conv (D-28b ABI 활용)
- @dotdotdot → is_vararg
- @noreturn → is_noreturn

**Tier B CFG edge** (D-28 §3.3.4 + §5):
- edge.kind heuristic (FALLTHROUGH / BRANCH_TRUE / BRANCH_FALSE / RETURN-no-edge)

**Tier C diagnostic (mitigation only)**:
- 7 critical drop 카테고리 모두 diagnostic emission framework 도입 (§2.2 P1)
- 실제 fix는 D-29C+

#### OUT-scope (D-29C+ 정식 분리 — frozen)

**Tier C critical fix**:
- §6.1 register-stack id collision *complete* mitigation (D-29B 는 collision count만)
- §6.2 struct layout cross-verify with `struct_recovery.c`
- §6.4 indirect call → function pointer resolution
- §6.6 `<jumptablelist>` parse + switch successor enumeration

**Architecture extension**:
- PE / Mach-O input
- Multi-segment ELF
- batch mode (한 번 spawn 으로 여러 함수)
- PLT / external symbol resolution beyond name-based lookup

**Float / C++ specific**:
- CPUI_FLOAT_* (15 op) full coverage — Phase F 별도 plan
- Vtable / mangling — Phase 1+ 별도 plan

---

## §3. Tier A 5-step 분해

### §3.1 Step A1 — `<varnode>` → IrVal

**XML 입력** (fixture trivial.xml 발췌):
```xml
<varnodes>
  <addr space="const" offset="0x0" size="8" ref="0x5"/>
  <addr space="const" offset="0x2a" size="8" ref="0x1"/>
  <addr space="register" offset="0x4000" size="8" ref="0x0"/>
</varnodes>
```

**AURA target** (`include/decompiler.h` IrVal):
```c
typedef struct {
    uint32_t id;          /* @ref */
    IrType   type;        /* size*8 -> width bits */
    IrValSort sort;       /* kind/imm — heuristic from @space */
    uint64_t imm;         /* @offset for space="const" */
} IrVal;
```

**매핑 규칙**:
- `id = @ref`
- `type.width = @size * 8` (bits)
- `@space="const"` → `sort.kind = IR_VAL_CONST` + `imm = @offset`
- `@space="register"` → `sort.kind = IR_VAL_REG` + register name lookup (Tier C diagnostic — register name 누락은 critical)
- `@space="ram"` → `sort.kind = IR_VAL_MEM` + `imm = @offset`
- `@space="unique"` → `sort.kind = IR_VAL_TEMP` (compiler 임시값)
- `@space="stack"` → `sort.kind = IR_VAL_STACK` + signed `@offset`

**RED test**:
- `tests/decompiler/test_ghidra_varnode_lift.c` — fixture XML → IrVal[] 검증
- 3 fixture (trivial 3 varnode / branch ~10 / external_call ~6) ground truth (수동 확인 후 fixture에 .expected.txt 추가)

**Gate**: T1 element coverage ≥95% on `<varnodes>` subtree (D-28 §7.2 T1)

**Diagnostic emit**:
- register space 등장 + register name 미해석 → `address_space_dropped` + space=register
- unique space 등장 → silent (Tier B implicit)

**예상 LOC**: impl ~150, test ~100

### §3.2 Step A2 — `<op @code>` → IrOpcode + IrInstr

**XML 입력**:
```xml
<op code="1">                          <!-- CPUI_COPY -->
  <seqnum space="ram" offset="0x40010c" uniq="0x0"/>
  <addr ref="0x0"/>                    <!-- dst -->
  <addr ref="0x1"/>                    <!-- src0 -->
</op>
<op code="10">                         <!-- CPUI_RETURN -->
  <seqnum space="ram" offset="0x400110" uniq="0x2"/>
  <void/>                              <!-- no dst -->
  <addr ref="0x5"/>
  <addr ref="0x0"/>
</op>
```

**AURA target** (`include/decompiler.h` IrInstr):
```c
typedef struct {
    IrOpcode op;
    IrVal   *dst;
    IrVal  **srcs;
    uint16_t  src_count;
    AuraAddr  origin_addr;
} IrInstr;
```

**핵심 lookup table** (`src/decompiler/ghidra_op_table.c` 신규):
```c
static const IrOpcode CPUI_TO_IR[74] = {
    [CPUI_COPY]          = IR_OP_COPY,
    [CPUI_LOAD]          = IR_OP_LOAD,
    [CPUI_STORE]         = IR_OP_STORE,
    [CPUI_BRANCH]        = IR_OP_JUMP,
    [CPUI_CBRANCH]       = IR_OP_BRANCH,
    [CPUI_BRANCHIND]     = IR_OP_JUMP,        /* + indirect diag (Tier C) */
    [CPUI_CALL]          = IR_OP_CALL,
    [CPUI_CALLIND]       = IR_OP_CALL,        /* + indirect diag (Tier C) */
    [CPUI_RETURN]        = IR_OP_RET,
    [CPUI_INT_EQUAL]     = IR_OP_CMP_EQ,
    /* ... 44 entries total per D-28 §4.1 ... */
    [CPUI_INDIRECT]      = IR_OP_UNSUPPORTED, /* + diag (Tier C) */
    [CPUI_FLOAT_ADD]     = IR_OP_UNSUPPORTED, /* + mnem accumulate */
    /* ... */
};
```

**Tier C 강제 sites** (table에서 분기 처리):
- CPUI_INDIRECT / CPUI_BRANCHIND / CPUI_CALLIND → diagnostic `indirect_op` (D-28 §13.2)
- CPUI_LOAD / CPUI_STORE 의 space arg drop → diagnostic `address_space_dropped`

**RED test**:
- `tests/decompiler/test_ghidra_op_lift.c` — 73 CPUI op 모두 enum 매핑 verify (44 mapped + 30 UNSUPPORTED)
- 3 fixture op count ground truth match

**Gate**: T2 op coverage ≥95% (44 매핑 op 등장률) — D-28 §7.2 T2

**예상 LOC**: lookup table ~120, ingest ~200, test ~150

### §3.3 Step A3 — `<high>` → HirLocal / HirParam

**XML 입력**:
```xml
<highlist>
  <high repref="0x5" class="constant">
    <typeref name="xunknown8" id="0xf56e6b6d6e22171b"/>
    <addr ref="0x5"/>
  </high>
  <high repref="0x0" class="other">
    <typeref name="xunknown8" id="0xf56e6b6d6e22171b"/>
    <addr ref="0x0"/>
  </high>
</highlist>
```

**AURA target**:
- `class="local"` → `HirLocal { ssa_id, name, type }`
- `class="param"` → `HirParam { name, type, ssa_id }` (16 한도)
- `class="global"` → `FileInfo.Symbol[]` cross-check (no HIR field)
- `class="constant"|"other"` → drop (Tier B implicit)

**param > 16 처리**: 17+ 절단 + diagnostic `param_truncated` (D-28 §6.5)

**Name dedup**: 같은 `repref` + 다중 `<addr ref>` instance → 동일 `hir_var.name[]`

**Gate**: T4 variable name match ≥95% (3 fixture × Ghidra GUI 골든 비교)

**Pre-req for Gate**: §7 harness fixture (≥3 binary Ghidra GUI capture) 필요 — D-29A merge 후 별도 사전 capture 필요 (D-28 §9 entry checklist 항목)

**예상 LOC**: impl ~200, test ~120

### §3.4 Step A4 — `<prototype>` → HirFunc ABI 필드

**XML 입력**:
```xml
<prototype model="__cdecl" extrapop="0">
  <returnsym>
    <addr space="register" offset="0x4000" size="8"/>
    <typeref name="xunknown8" id="0xf56e6b6d6e22171b"/>
  </returnsym>
</prototype>
```

**AURA target** (D-28b 머지 후 이미 존재):
```c
HirFunc.calling_conv     /* AuraCallingConv enum */
HirFunc.is_vararg        /* bool */
HirFunc.is_noreturn      /* bool */
```

**Model → enum 매핑**:
| Ghidra @model | AuraCallingConv |
|---|---|
| `__cdecl` / `default` (x86_64 SysV) | `AURA_CC_CDECL` |
| `__stdcall` | `AURA_CC_STDCALL` |
| `__fastcall` | `AURA_CC_FASTCALL` |
| `__thiscall` | `AURA_CC_THISCALL` |
| `__regcall*` / unknown | `AURA_CC_UNKNOWN` + diagnostic `calling_conv_unknown` |

**주의**: D-28 §6.3은 별도의 `HirCallConv` (HIR_CC_*) 8개 enum을 제안했지만, D-28b 머지 결과는 `AuraCallingConv` (AURA_CC_*) 7개. **D-29B는 D-28b 실제 enum을 기준**으로 하며 D-28 §6.3 설계는 superseded. D-28b 의 `AURA_CC_SYSCALL` ↔ D-28 §6.3 의 `HIR_CC_SYSV_AMD64`/`HIR_CC_AAPCS` 의 매핑 차이는 본 step 의 lookup 표 안에서 흡수.

**`addr_space` / `return_storage` / `param_storage[16]` 권장 ABI**: D-29B 는 미도입. D-29C 또는 별도 ABI bump turn 으로 분리 (HirFunc 크기 변화 = SemVer minor 충돌 회피).

**Gate**: 3 fixture 의 `<prototype @model>` → calling_conv 변환 100% 일치 (수동 비교)

**예상 LOC**: impl ~80, test ~60

### §3.5 Step A5 — `<typeref>` / `<type>` → HirType

**XML 입력**:
```xml
<typeref name="xunknown8" id="0xf56e6b6d6e22171b"/>
```

**AURA target** (`include/hir.h` HirType):
```c
typedef struct {
    char     name[128];
    uint32_t size;
    uint8_t  is_ptr;
    uint8_t  is_signed;
    uint8_t  is_struct;
    uint8_t  is_array;
} HirType;
```

**Metatype → AURA 변환**:
| @metatype | name | flags |
|---|---|---|
| int | `intN_t` (N = size*8) | is_signed=1 |
| uint | `uintN_t` | — |
| char | `char` | size=1 |
| float / double | `float` / `double` | size=4/8 |
| ptr | `<inner>*` (재귀) | is_ptr=1 |
| array | `<inner>[N]` | is_array=1 |
| struct / union | `struct_<id>` / `union_<id>` | is_struct=1 + diagnostic `struct_layout_dropped` (Tier C) |
| enum | `enum_<id>` | (Tier B drop, silent) |

**Type qualifier drop** (Tier B implicit): const/volatile/restrict 모두 silent drop (D-28 §3.6.12).

**`xunknown<N>`** (Ghidra placeholder): `intN_t` 로 변환 + Tier B silent drop. 단 빈도 ≥30%일 시 Step A5 종료 시 사용자 확인 (수동 review).

**Gate**: T1 element coverage ≥95% on `<type>`/`<typeref>` subtree

**예상 LOC**: impl ~180 (재귀 ptr/array 처리), test ~100

---

## §4. Tier B 2-step 분해

### §4.1 Step B1 — `<block>` → CFG edge 복원

**XML 입력**:
```xml
<block index="0">
  <rangelist><range space="ram" first="0x40010c" last="0x400110"/></rangelist>
  <op code="1">...</op>
  <op code="10">...</op>
  <blockedge>
    <edge end="0x1" rev="0"/>
    <edge end="0x2" rev="1"/>
  </blockedge>
</block>
```

**AURA target** (`include/cfg.h` CfgEdge):
```c
typedef struct {
    uint32_t from_block;
    uint32_t to_block;
    CfgEdgeKind kind;   /* FALLTHROUGH / BRANCH_TRUE / BRANCH_FALSE / RETURN */
} CfgEdge;
```

**Edge kind heuristic** (D-28 §5):
| from_block 마지막 op | edge index 0 | edge index 1 |
|---|---|---|
| CPUI_BRANCH | FALLTHROUGH | (n/a, 단일 successor) |
| CPUI_CBRANCH | BRANCH_FALSE | BRANCH_TRUE |
| CPUI_BRANCHIND | FALLTHROUGH + diagnostic `indirect_op` | (n/a) |
| CPUI_RETURN | (no edge — 종단) | — |
| CPUI_CALL + 다음 block 존재 | FALLTHROUGH | — |
| 위 패턴 미일치 | FALLTHROUGH (default) + Tier B harness flag | — |

**Gate**: edge.kind heuristic ≥99% (D-28 §5 + §7.5)

**RED test**:
- `tests/decompiler/test_ghidra_cfg_edge.c` — 3 fixture × edge ground truth (branch.xml 4 block, ~6 edges)

**예상 LOC**: impl ~150, test ~100

### §4.2 Step B2 — Terminator op → CFG terminator + 종단 검증

**Context**: Step A2 가 op enum lookup만 처리. Step B2 는 BRANCH/CBRANCH/RETURN/CALL 등 terminator op 가 IrBlock 의 successor 정보와 정합한지 검증.

**검증 규칙**:
- IrBlock 의 마지막 instr 이 IR_OP_RET → block.succ_count == 0
- 마지막 instr 이 IR_OP_BRANCH → block.succ_count == 2 (true/false)
- 마지막 instr 이 IR_OP_JUMP → block.succ_count == 1
- 마지막 instr 이 IR_OP_CALL + 다음 block 존재 → block.succ_count == 1 (FALLTHROUGH)
- 어긋남 시 → diagnostic `terminator_mismatch` (신규 reason key)

**Gate**: T3 (AST structural diff, block/op count 일치) ≥95% AND T5 (Pseudo-C string diff) ≥95%

**예상 LOC**: impl ~120, test ~80

---

## §5. AuraGhirFunc → IrFunc/HirFunc 통합 sequence (결정 1 = Option A)

### §5.1 변환 다이어그램

```
[D-29A turn #7 폐기 시점]
  ┌──────────────────────────────┐
  │ AuraGhirFunc{name?, blocks[],│  ← bridge-local, D-29A 산출
  │              ops[]}          │
  └──────────────────────────────┘
                X (delete)
[D-29B Step A1 진입 시점]
  ┌──────────────────────────────┐
  │ src/decompiler/              │
  │   ghidra_to_aura_ir.cpp      │  ← 신규, Step A1-A2-A3 누적
  │     ↓                        │
  │ IrFunc{vals[], blocks[],     │
  │        instrs[]}             │  ← AURA production IR
  └──────────────────────────────┘
                ↓
[Step A3-A4-A5 종료]
  ┌──────────────────────────────┐
  │ hir_build(IrFunc, pdom,      │  ← 기존 src/decompiler/hir_builder.c 재사용
  │           loops, fi, params) │     (Option A 핵심)
  │     ↓                        │
  │ HirFunc{name, params[],      │
  │         calling_conv, ...,   │
  │         body, diagnostics[]} │
  └──────────────────────────────┘
                ↓
[Step B1-B2 종료]
  hir_emit_pseudoc → Pseudo-C
```

### §5.2 폐기 commit (Step A1 첫 commit)

```
chore(D-29B Step A1 prep): retire AuraGhirFunc bridge-local mapper

- include/ghidra_xml_to_hir.h         (D-29A turn #7) → delete
- src/decompiler/ghidra_xml_to_hir.cpp (D-29A turn #7) → delete
- tests/decompiler/test_ghidra_xml_to_hir.c (D-29A turn #7) → delete
- CMakeLists.txt: remove ghidra_xml_to_hir.cpp from AURA_CORE_SOURCES
- tests/CMakeLists.txt: remove 4 test_ghidra_xml_to_hir cases

ctest 213/213 → 209/209 (4 cases 폐기, 회귀 0)
```

### §5.3 IrFunc 직접 산출 entry point

**신규 API** (`include/ghidra_to_aura_ir.h`):
```c
typedef enum {
    AURA_GTA_OK         = 0,
    AURA_GTA_ERR_PARSE  = 1,
    AURA_GTA_ERR_SHAPE  = 2,
    AURA_GTA_ERR_OOM    = 3,
    AURA_GTA_ERR_TIER_C = 4,  /* unacknowledged Tier C diagnostic */
} AuraGtaStatus;

typedef struct {
    AuraGtaStatus status;
    IrFunc       *ir;          /* malloc'd, caller free via ir_func_destroy */
    HirDiagnostic *diagnostics;
    uint32_t       diagnostic_count;
} AuraGtaResult;

AuraGtaStatus aura_ghidra_xml_to_ir(
    const char *xml,
    size_t      xml_len,
    AuraGtaResult *result);
```

이후 `hir_build()` 호출은 caller 측 (codegen.c 또는 신규 통합 path)이 담당. D-29B Step A 종료까지는 IrFunc 까지만, Step B 종료시점에 HirFunc 까지 가는 end-to-end test 추가.

### §5.4 wrapper(D-29A turn #5) 와의 연결

`aura_ghidra_decompile_at()` 의 `result->xml` (post-normalize) 를 `aura_ghidra_xml_to_ir()` 에 그대로 넘김. wrapper 코드는 변경 없음.

```c
AuraGhidraDecompileResult dr;
aura_ghidra_decompile_at(&cfg, path, addr, NULL, &dr);
if (dr.status == AURA_GHIDRA_OK) {
    AuraGtaResult gr;
    aura_ghidra_xml_to_ir(dr.xml, dr.xml_len, &gr);
    /* gr.ir 사용 */
}
```

---

## §6. Diagnostic emission framework (Tier C mitigation, §2.2 P1)

### §6.1 신규 모듈

- `include/aura_diagnostic.h` — HirDiagnostic struct + reason key constants
- `src/decompiler/aura_diagnostic.c` — emit / aggregate / format

### §6.2 Reason key 사전 (D-28 §13.2 verbatim + 1 신규)

| reason key | step where emitted |
|---|---|
| `address_space_dropped` | Step A1 |
| `address_space_collision` | Step A1 (id collision detect) |
| `struct_layout_dropped` | Step A5 |
| `type_identity_dropped` | Step A5 |
| `calling_conv_unknown` | Step A4 |
| `vararg_dropped` | Step A4 (현 ABI는 fully supported, 따라서 actual emit 없음) |
| `noreturn_dropped` | Step A4 (동일) |
| `indirect_op` | Step A2, B1 |
| `param_truncated` | Step A3 |
| `jumptable_dropped` | (deferred to D-29C) |
| `seqnum_collision` | Step A2 (origin_addr 다중 op 검출) |
| `op_unsupported_critical` | Step A2 |
| **`terminator_mismatch`** (신규) | Step B2 |

### §6.3 Acknowledge 메커니즘 (D-28 §7.3 + §13.4)

- `tests/fixtures/ghidra_golden/<binary>.acknowledged_diagnostics.txt` 형식 변경 없음
- D-29B 종료 gate: 모든 fixture × 모든 등장 Tier C reason 이 ack 파일에 기록되어야 함

### §6.4 Runtime 출력

- Default: `stderr` line `AURA-DIAG: <reason> @<func_addr> <detail>`
- Aggregate: `--diag-out <path>` CLI 옵션 (Step B2 이후 도입)
- GUI sink (Phase 1+ defer): `HirFunc.diagnostics[]` 만 채움 (출력 안 함)

---

## §7. Coverage gate per step (결정 3 = G1 누적)

| Step | New gate | 누적 gate (전 step + 신규) |
|---|---|---|
| A1 | T1 ≥95% on `<varnodes>` | T1(varnodes) |
| A2 | T2 ≥95% on `<op>` | T1(varnodes) + T2 |
| A3 | T4 ≥95% (3 fixture) | T1(varnodes) + T2 + T4 |
| A4 | per-fixture cc match 100% | T1 + T2 + T4 + cc100 |
| A5 | T1 ≥95% on `<type>`/`<typeref>` | T1(varnodes+type) + T2 + T4 + cc100 |
| B1 | edge.kind ≥99% | T1 + T2 + T4 + cc100 + edge99 |
| B2 | T3 ≥95% AND T5 ≥95% | **All T1-T5 ≥95% AND Tier C ack count = total** |

각 step PR 머지 전 *해당 step 의 신규 gate* 만 검증. B2 머지 시 D-29B 종료 gate 일괄 검증.

### §7.1 Pre-requisite (D-29B 진입 전 사용자 작업)

D-28 §9 entry checklist 미해결 항목 — D-29B 시작 전 해결 필요:
- [ ] §7 harness fixture (수동, ≥3 binary Ghidra GUI golden) capture
  - 권장 binary: `/bin/cat`, `/bin/ls`, `aura-self` (build-rel/aura)
  - 수동 capture: Ghidra 12.0.4 GUI 에서 동일 binary 디컴파일 → Pseudo-C 텍스트 export → `tests/fixtures/ghidra_golden/<binary>.expected.txt`
  - 수동 작업 ~1시간 / binary
- [ ] T-5b PR main 머지 — **이미 PR #41 `5127713` 머지 완료** (2026-04-26 Session #22)

### §7.2 Harness 위치

- `tests/integration/test_ghidra_xml_mapping.c` — T1 (Step A1, A5)
- `tests/integration/test_ghidra_op_mapping.c` — T2 (Step A2)
- `tools/aura-ghidra-diff` — T3/T4/T5 (Step A3 onwards) — **D-29B Step A3 합류 시 신규 도구 도입**
  - LOC 예상 ~800 (XML parser 재사용 + diff 알고리즘 + 사용자 ack 체크)

---

## §8. 구현 순서 (atomic step 단위)

> 각 step = 1 PR. PR-based workflow 준수 (PR-based AURA convention).

### §8.1 Sequence

```
[D-29B 진입 전]
  S0  branch d29b/semantic-mapping 생성, ~/Desktop/AURA-d29b worktree
      §7.1 fixture 3-binary Ghidra GUI golden capture
      D-29B 본 설계 문서 main merge

[D-29B Step A]
  S1  Step A1 prep: AuraGhirFunc 폐기 (chore commit)
        → ctest 213 → 209
  S2  Step A1: <varnode> → IrVal lift
        → +test_ghidra_varnode_lift, T1(varnodes) ≥95%
        → ctest 209 → 210+
        → PR #N1 main merge
  S3  Step A2: <op @code> → IrOpcode + IrInstr
        → +test_ghidra_op_lift (74 op enum), T2 ≥95%
        → +ghidra_op_table.c (lookup table)
        → +diagnostic framework introduction (aura_diagnostic.c/h)
        → PR #N2 main merge
  S4  Step A3: <high> → HirLocal/HirParam + name dedup
        → +test_ghidra_highsymbol_lift, T4 ≥95% (3 fixture × Ghidra GUI 골든)
        → +tools/aura-ghidra-diff (T3/T4/T5 harness)
        → PR #N3 main merge
  S5  Step A4: <prototype> → HirFunc.cc/vararg/noreturn
        → +test_ghidra_prototype_lift, cc match 100%
        → PR #N4 main merge
  S6  Step A5: <typeref>/<type> → HirType (재귀 ptr/array)
        → +test_ghidra_type_lift, T1 누적 (varnodes+type) ≥95%
        → PR #N5 main merge

[D-29B Step B]
  S7  Step B1: <block>/<blockedge> → CfgEdge + edge.kind heuristic
        → +test_ghidra_cfg_edge, edge.kind ≥99%
        → PR #N6 main merge
  S8  Step B2: terminator op verify + end-to-end Pseudo-C diff
        → +test_ghidra_e2e_pseudoc, T3 ≥95% AND T5 ≥95%
        → D-29B 종료 gate (T1-T5 모두 ≥95% + Tier C ack count = total)
        → PR #N7 main merge

[D-29B 완료]
  S9  Tasks.md / PRD.md / MEMORY.md 갱신
  S10 D-29C plan turn entry
```

### §8.2 PR 단위 LOC 예상

| Step | impl LOC | test LOC | 기타 | 총 LOC |
|---|---|---|---|---|
| S1 (chore) | -300 (delete) | -226 | -36 (CMake) | -562 |
| S2 (Step A1) | ~150 | ~100 | ~30 | ~280 |
| S3 (Step A2) | ~320 | ~150 | diag ~80 | ~550 |
| S4 (Step A3) | ~200 | ~120 | tools ~800 | ~1120 |
| S5 (Step A4) | ~80 | ~60 | — | ~140 |
| S6 (Step A5) | ~180 | ~100 | — | ~280 |
| S7 (Step B1) | ~150 | ~100 | — | ~250 |
| S8 (Step B2) | ~120 | ~80 | e2e ~150 | ~350 |
| **D-29B 합계** | **~1200** | **~710** | **~1024** | **~2,400 net** |

### §8.3 회귀 영향 추정

- ctest baseline (D-29A 머지 후 main): 213/213 GREEN
- S1 후: 209/209 (-4 폐기)
- S2~S8 누적: 209 → ~250+ (Tier A/B 신규 test cases)
- 기존 ghidra-bridge label tests (15 turn #2-#6 cases) 유지

---

## §9. Frozen OUT-scope (D-29C+ 분리 — 변경 시 plan 갱신 필요)

**D-29B 동안 *건드리지 않는*** 영역:

| OUT 항목 | D-29C+ 처리 | 사유 |
|---|---|---|
| `<jumptablelist>` parse | D-29C-1 | switch successor 누락 빈도 측정 후 도입 |
| struct layout cross-verify | D-29C-2 | `struct_recovery.c` 통합 별도 design turn 필요 |
| indirect call → fn ptr resolution | D-29C-3 | call graph 의존, scope 큼 |
| PE / Mach-O input | D-29C-4 | aura-decompile vendor 확장 필요 |
| Multi-segment ELF | D-29C-5 | ELF parser 의존, 별도 |
| Batch mode (1 spawn → N func) | D-29C-6 | wrapper API 변경 필요 |
| CPUI_FLOAT_* full coverage | Phase F | floating analysis 신규 plan |
| C++ vtable / mangling | Phase 1+ | language scope 변경 |
| Cross-compiler (clang vs gcc) | Phase 2+ | parity infrastructure 별도 |
| `addr_space` / `return_storage` / `param_storage[16]` ABI | 별도 ABI bump turn | SemVer minor 충돌 회피 (현재 v2.5.0 미배정) |

**D-28 §6.3 권장 ABI 미도입 이유**: HirFunc struct grow → 영속 상태 / GUI 의존 / SemVer 모두 영향. D-29B 안에 묶으면 PR scope 폭주. 별도 ABI bump turn (D-29B 와 D-29C 사이 또는 v2.5.0 release 시점) 으로 분리.

---

## §10. Risk register (D-29B 진행 중 차단 요소)

| ID | Risk | Severity | Mitigation |
|---|---|---|---|
| D29B-R1 | §7.1 Ghidra GUI 골든 fixture 누락 → T3/T4/T5 측정 불가 | 🔴 high | S0 단계에서 사용자 수동 capture 강제 (3 binary, ~3시간 1회 비용) |
| D29B-R2 | Step A1 register name 누락 빈도 ≥30% → register varnode 식별 불가 | 🟡 medium | Ghidra `<addr @space="register" @offset>` 의 offset → register name lookup 표 (Phase 0 시점 vendored sleigh 의 register definition) 도입 |
| D29B-R3 | Step A2 lookup table에서 IR_OP_UNSUPPORTED 가 차지하는 비율 ≥50% on real binary → T2 ≥95% 미달 | 🟡 medium | Tier B float ops (15 op) 가 real binary 빈도 의외 낮으면 통과. ≥50% 시 D-29B 중단 + Phase F entry 우선순위 재조정 |
| D29B-R4 | Step A3 name dedup 알고리즘이 Ghidra Funcdata::deindirect 결과와 어긋남 → T4 ≥95% 미달 | 🔴 high | `<high><addr ref>` 다중 instance 의 ssa_id 그룹화 알고리즘 = Ghidra HighVariable.getInstance() 결과 그대로 따르기 (XML에서 직접 읽음) |
| D29B-R5 | Step A4 `__cdecl`/`default` 구분이 architecture별로 모호 → calling_conv 매핑 일치 100% 미달 | 🟢 low | architecture 별 default → enum 직접 매핑 표 (x86_64 → CDECL, aarch64 → CDECL since AAPCS not in AuraCallingConv) |
| D29B-R6 | Step A5 nested struct/typedef 재귀 처리 시 stack overflow | 🟢 low | 재귀 depth 한도 (32) + 한도 초과 → fallback `intN_t` + diagnostic |
| D29B-R7 | Step B1 edge.kind 추정이 unstructured CFG (irreducible) 에서 ≥99% 미달 | 🟡 medium | irreducible CFG 함수 빈도 측정 (real binary). ≥5% 시 fallback path 강화 |
| D29B-R8 | Step B2 end-to-end Pseudo-C diff (T5) 가 변수명 정규화 후에도 ≥95% 미달 | 🟡 medium | T5 측정 알고리즘에서 whitespace / 변수명 / 임시 var 모두 정규화 후 측정 |

---

## §11. Cross-references

- D-26 정책 해제: `project_d26_custom_first_lifted.md`, PR #42 `83e40af`
- D-27 Phase 0 build/run: `project_d27_ghidra_phase0_verification.md`, PR #43 `fe39dfd`
- D-28 mapping table: `docs/design/d28_ghidra_hir_mapping.md`, PR #44 `40b0e47`
- D-28b HirFunc ABI: `74808ab`, PR #45
- D-29A bridge skeleton: PR #46 `3ec7af9`
  - turn #2 argv mode: `f7370b9`
  - turn #3 fixture: `93db219`
  - turn #4 ctest lock: `ff51f15`
  - turn #5 wrapper: `2118ffe`
  - turn #6 normalize: `08cbb59`
  - turn #7 4-element mapper: `d0ef084`
- Risk register (cross-cut): `~/.claude/plans/aura-harmonic-teapot.md`
- Ghidra source: `third_party/ghidra-decompile/cpp/{funcdata,marshal,block,op,varnode,fspec,variable,type}.{cc,hh}`
- AURA HIR/IR: `include/{hir,decompiler,cfg,file_format,var_propagation}.h`
- AURA hir_builder: `src/decompiler/hir_builder.c` (Option A 의 핵심 — 본 모듈 변경 없음)

---

## §12. Sign-off

**문서 status**: 사용자 승인 (4 + 2 결정 모두 권장안 채택, 2026-04-27).

**완료된 step**:
- ✅ 4 결정 (§2.1-§2.4) 승인
- ✅ Step A4 ABI = D-28b `AuraCallingConv` 기준 supersede
- ✅ §9 OUT 분리 = `addr_space` / `return_storage` / `param_storage[16]` D-29C+ 분리

**다음 step (PR 머지 후)**:
1. §7.1 fixture capture (사용자 수동 ~3시간) — Ghidra 12.0.4 GUI 에서 `/bin/cat`, `/bin/ls`, `aura-self` 디컴파일 → Pseudo-C export → `tests/fixtures/ghidra_golden/<binary>.expected.txt`
2. `tests/fixtures/ghidra_golden/<binary>.acknowledged_diagnostics.txt` template 사전 배치 (S0 sub-step, code 변경 X — fixture 디렉터리 + README 만)
3. Step A1 prep (AuraGhirFunc 폐기 chore commit) → S2-S8 진행

**금지 사항** (본 design turn 한정):
- 코드 변경 0
- 본 설계 문서 외 산출물 추가 X (S0 fixture 디렉터리 skeleton 은 본 PR 미포함 — 별도 S0 turn 에서)
- D-29A 구조 변경 X (S1 chore commit 은 D-29B 진입 *후* 별도 turn)

---

**End of D-29B design document.**
