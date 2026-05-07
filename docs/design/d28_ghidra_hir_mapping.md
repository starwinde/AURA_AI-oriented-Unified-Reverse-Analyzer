# D-28: Ghidra HighFunction XML → AURA HIR Mapping (설계 turn 산출물)

> **Scope re-statement (2026-04-30 pivot)**: 본 문서가 다루는 Ghidra adapter 는 D-1 (2026-04-30 결정) 이후 **decompile co-primary 한정** 이다. analyze / disasm / trace primary 권한은 Rizin (Phase 2A) 으로 이관됐다. 본 문서의 Tier C drop / harness / ABI 논의는 **Ghidra `decompile` request 경로에 한해서만** 유효하다. Rizin canonical 은 절대 본 매핑에 등장하지 않으며, 별도 `d_rizin_skeleton.md` 에서 정의된 1 급 record (R-12) 로 변환된다.
>
> **Status**: 사용자 조건부 승인 (Session #22, 2026-04-26). 코드 변경 0. 본 문서는 D-29 (`codegen.c` 통합) 의 *binding* 입력. R2 (lossy mapping → silent wrong codegen) 차단 산출물.

> **Plan**: `~/.claude/plans/aura-harmonic-teapot.md` Risk Register R2.
>
> **Inputs**: Ghidra 12.0.4 `decompile/cpp/` (vendored at `~/Desktop/AURA-d27/third_party/ghidra-decompile/`) + AURA `include/hir.h` / `decompiler.h` / `cfg.h` / `file_format.h`.
>
> **Approval**: 사용자 5-조건 승인 (2026-04-26):
> 1. §6 3-tier 분류 강제 + Tier C 모두 diagnostic emit
> 2. §7 per-tier ≥95% (no averaging) + Tier C 발생 시 hard fail
> 3. HirFunc ABI 확장 (필수 3 + 권장 3)
> 4. 별도 branch `d28/hir-mapping-plan` 별도 PR
> 5. 진행 순서 (binding) 강제 — §14

> **Output gate**: D-29 진입 *전* 본 문서 머지 + T-5b finalize 머지 강제 (§14).

---

## §1. Executive summary

**전제**: AURA 의 IR 계층은 3-tier (CFG → IrFunc/IrBlock/IrInstr → HirFunc/HirNode). Ghidra 의 출력은 pre-structured (P-Code + BlockBasic CFG + HighVariable, **structured control flow 없음**).

**채택 mapping 경로 = Option A** (CFG/LIR/MIR layer 까지만 Ghidra extract, structuring 은 AURA 기존 hir_builder 재사용):

```
Ghidra <function>/<ast> XML
  ├── <varnodes>   →  AURA IrVal (SSA)
  ├── <block>      →  AURA IrBlock
  ├── <op>         →  AURA IrInstr (LIR)
  ├── <blockedge>  →  AURA CfgEdge
  └── <high>       →  AURA HirLocal / HirParam (variable level)
       ↓
AURA 기존 hir_builder.c (structuring + HIR_IF/WHILE/FOR/SWITCH 복원)
       ↓
AURA HirFunc / HirNode (그대로 유지, codegen.c 입력 동일)
```

**Why Option A** (vs Option B 직접 HIR 매핑 / Option C PrettyPrint 그대로):
- Ghidra HighFunction XML 은 *unstructured* CFG 만 제공 (BlockBasic + edge). HIR_IF / HIR_WHILE 등 structured tree 는 PrettyPrint 단계에서만 생성됨 (`prettyprint.cc`)
- Ghidra PrettyPrint 출력 (Option C) 을 그대로 쓰면 AURA HirFunc 생략 → GUI rename / type cast / position metadata (T-5a HirEmitPositions) 모두 깨짐
- Option A = 최소 침습 (Ghidra IR layer 만 적출, AURA structuring/emission 보존)

**Tier C critical drops** (Phase 2 blocker, §6 참조): **7 항목** — address space / type / calling_conv / indirect / param>16 / jumptable / seqnum.

---

## §2. Mapping 경계 다이어그램

```
┌─────────────────────────────────────────────────────────────────────┐
│ Ghidra subprocess (aura-decompile)                                    │
│                                                                       │
│  raw bytes ──► Sleigh lift ──► P-Code ──► Funcdata::structureReset()  │
│                                              │                         │
│                                              ▼                         │
│                                       <function> XML                   │
│                                              │                         │
└──────────────────────────────────────────────┼─────────────────────────┘
                                               │ stdout (XML)
┌──────────────────────────────────────────────▼─────────────────────────┐
│ AURA host (aura main process)                                          │
│                                                                        │
│  ▼ byte normalize first; XML parse/semantic mapping deferred           │
│                                                                        │
│  ┌─────────────── §3 Element-level mapping ───────────────────┐       │
│  │  <varnodes>  →  IrVal[]                                    │       │
│  │  <block>     →  IrBlock[]                                  │       │
│  │  <op>        →  IrInstr[]                                  │       │
│  │  <blockedge> →  CfgEdge[]                                  │       │
│  │  <high>      →  HirLocal[] / HirParam[]                    │       │
│  │  <prototype> →  HirFunc.{calling_conv, params,             │       │
│  │                  is_vararg, is_noreturn} + Tier C drops   │       │
│  │  <scope>     →  FileInfo (cross-checked, no AURA symbol    │       │
│  │                  table extension)                           │       │
│  │  <typeref>/  →  HirType (name-based, lossy)                │       │
│  │   <type>                                                   │       │
│  └────────────────────────────────────────────────────────────┘       │
│                              │                                         │
│                              ▼                                         │
│  AURA hir_builder.c (existing, structuring 재사용)                    │
│                              │                                         │
│                              ▼                                         │
│  HirFunc (기존 구조 + HirCallConv/HirStorage 확장)                     │
│                              │                                         │
│                              ▼                                         │
│  hir_emit.c → Pseudo-C 출력 + Diagnostic stream (§13)                  │
└──────────────────────────────────────────────────────────────────────┘
```

---

## §3. Element-level mapping 표 (Tier 표기 포함)

> **Tier 표기**: A = safe drop (silent OK), B = lossy tolerated (mitigation 명시), **C = critical (diagnostic emit 강제)**.

| # | Ghidra XML | AURA target | Cardinality | Mapping kind | Tier / 비고 |
|---|---|---|---|---|---|
| **3.1 Container** ||||||
| 3.1.1 | `<function>` (root) | `HirFunc` (1) + `IrFunc` (1) | 1:1 | direct | — |
| 3.1.2 | `<function @id>` | (drop) | — | drop | **A** |
| 3.1.3 | `<function @name>` | `HirFunc.name[128]` / `IrFunc.name[128]` | 1:1 | string copy | A |
| 3.1.4 | `<function @size>` | (drop) | — | drop | **A** |
| 3.1.5 | `<function @nocode>` | `HirFunc.unsupported_mnems` flag | 1:1 | flag → comment | A |
| 3.1.6 | `<function><addr>` | `HirFunc.func_addr` (AuraAddr) | 1:1 | offset only | **C** (§6.1 address space) |
| **3.2 AST / IR layer** ||||||
| 3.2.1 | `<ast>` (wrapper) | (none) | — | structural | — |
| 3.2.2 | `<varnodes>` (wrapper) | `IrFunc.next_val_id` (max@ref+1) | 1:1 | computed | — |
| 3.2.3 | `<addr>` (varnode def) | `IrVal { id=@ref, type, sort, imm }` | 1:1 | per-element | partial |
| 3.2.4 | `<addr @space>` | `IrVal.sort.kind` (heuristic) | N:1 | **lossy** | **C** (§6.1) |
| 3.2.5 | `<addr @offset>` | partial: ram → origin_addr; else drop | N:1 | partial | A |
| 3.2.6 | `<addr @size>` | `IrVal.sort.width` (bytes→bits ×8) | 1:1 | direct | A |
| 3.2.7 | `<addr @ref>` | `IrVal.id` (uint32_t) | 1:1 | direct | A |
| 3.2.8 | `<addr @grp>` | (drop) | — | drop | **B** (covermerge hint) |
| 3.2.9 | `<addr @persists\|@addrtied\|@unaff\|@volatile>` | (drop) | — | partial | **B** |
| 3.2.10 | `<addr @input>` | `HirParam.ssa_id` (entry block) | 1:1 | direct | A |
| **3.3 Block / CFG** ||||||
| 3.3.1 | `<block @index>` | `IrBlock.id` | 1:1 | direct | A |
| 3.3.2 | `<block><bhead>` | (drop, BlockGraph hierarchy not used) | — | drop | A |
| 3.3.3 | `<blockedge @index>` | `IrBlock.pred_ids[]` / `succ_ids[]` | 1:N | computed | A |
| 3.3.4 | `<edge @end @rev>` | `CfgEdge { from_block, to_block, kind }` | 1:1 | edge.kind 추정 | **B** (§5) |
| **3.4 P-Code op** ||||||
| 3.4.1 | `<op @code>` | `IrInstr.op` (IrOpcode) | 1:1 | mapping table (§4) | partial |
| 3.4.2 | `<op><seqnum @time @uniq>` | `IrInstr.origin_addr` (time만) | 1:1 | direct | **C** (§6.7 seqnum identity) |
| 3.4.3 | `<op><addr @ref>` (output) | `IrInstr.dst.id` | 1:1 | direct | A |
| 3.4.4 | `<op><void/>` (output) | `IrInstr.dst.id = IR_VAL_ID_UNDEF` | 1:1 | sentinel | A |
| 3.4.5 | `<op>` inputs | `IrInstr.srcs[]` | 1:N | direct | partial |
| 3.4.6 | `<spaceid @name>` (LOAD/STORE input[0]) | (drop) | — | drop | **C** (§6.1) |
| 3.4.7 | `<iop @value>` (CPUI_INDIRECT input[1]) | (drop, IR_OP_INDIRECT 미지원) | — | **drop** | **C** (§6.4) |
| **3.5 HighVariable / scope** ||||||
| 3.5.1 | `<high @class="local">` | `HirLocal { ssa_id, name, type }` | 1:1 | direct | A |
| 3.5.2 | `<high @class="param">` | `HirParam` (16개 한도) | 1:1 | direct | **C** (§6.5 param>16) |
| 3.5.3 | `<high @class="global">` | `FileInfo.Symbol` (cross-check) | 1:1 | external | A |
| 3.5.4 | `<high @class="constant"\|"other">` | (drop) | — | drop | **B** |
| 3.5.5 | `<high @typelock>` | (drop) | — | drop | A |
| 3.5.6 | `<high @symref @offset>` | `FileInfo.Symbol.address + offset` | 1:1 | external | A |
| 3.5.7 | `<high><addr @ref>` (instances) | name dedup → 동일 hir_var.name[] | 1:N | name dedup | A |
| **3.6 Type** ||||||
| 3.6.1 | `<typeref @id @name>` | `HirType.name[128]` | 1:1 | string copy | **C** (§6.2 type identity) |
| 3.6.2 | `<type @metatype="int">` | `HirType { name="int<size>_t", is_signed=1 }` | 1:1 | direct | A |
| 3.6.3 | `<type @metatype="uint">` | `HirType { name="uint<size>_t", is_signed=0 }` | 1:1 | direct | A |
| 3.6.4 | `<type @metatype="char">` | `HirType { name="char", size=1 }` | 1:1 | direct | A |
| 3.6.5 | `<type @metatype="float\|double">` | `HirType { name, size }` | 1:1 | direct | A |
| 3.6.6 | `<type @metatype="ptr">` | `HirType { name="<inner>*", is_ptr=1 }` | 1:1 | suffix '*' | A |
| 3.6.7 | `<type @metatype="array" @arraysize>` | `HirType { name="<inner>[N]", is_array=1 }` | 1:1 | direct | A |
| 3.6.8 | `<type @metatype="struct"><field>*` | `HirType { name="struct_<id>", is_struct=1 }` | 1:1 | name only | **C** (§6.2 struct layout) |
| 3.6.9 | `<type @metatype="union">` | `HirType { name="union_<id>" }` | 1:1 | name only | **C** (§6.2) |
| 3.6.10 | `<type @metatype="enum">` | `HirType { name="enum_<id>" }` | 1:1 | name only | **B** |
| 3.6.11 | `<field @name @offset>` | `HirNode.hir_field` (사용 시점에) | 1:1 | direct | A |
| 3.6.12 | `<type qualifier>` (const/volatile/restrict) | (drop) | — | drop | **B** |
| **3.7 Prototype** ||||||
| 3.7.1 | `<prototype @model>` | `HirFunc.calling_conv` (NEW field §6.3) | 1:1 | enum mapping | **C** (§6.3 calling_conv) |
| 3.7.2 | `<prototype @dotdotdot>` | `HirFunc.is_vararg` (NEW field §6.3) | 1:1 | bit flag | **C** (§6.3 vararg) |
| 3.7.3 | `<prototype @noreturn>` | `HirFunc.is_noreturn` (NEW field §6.3) | 1:1 | bit flag | **C** (§6.3 noreturn) |
| 3.7.4 | `<prototype @inline\|@constructor\|@destructor\|@custom>` | partial (`is_inline_hint`) | 4:1 | partial | **B** (C++ only) |
| 3.7.5 | `<prototype><returnsym>` | `HirFunc.return_type` + `return_storage` (NEW recommended) | 1:1 | direct | A (storage = 권장) |
| 3.7.6 | `<prototype><param>` | `HirFunc.params[i]` + `param_storage[i]` (NEW recommended) | 1:N | direct | **C** (>16 한도) |
| 3.7.7 | `<prototype><param @name>` | `HirParam.name[64]` | 1:1 | direct | A |
| 3.7.8 | `<prototype><param @typelock\|@namelock\|@thisptr>` | (drop) | — | drop | A |
| 3.7.9 | `<prototype><likelytrash>` | (drop) | — | drop | **B** (register kill set) |
| 3.7.10 | `<prototype><inject>` | (drop) | — | drop | A |
| **3.8 Scope / symbol** ||||||
| 3.8.1 | `<scope @name @id>` | (cross-check FileInfo.Symbol[i].name) | 1:1 | external | A |
| 3.8.2 | `<symbollist><mapsym>` | `FileInfo.Symbol[]` (existing) | 1:N | external | A |
| 3.8.3 | `<symbol @cat>` | `FileInfo.Symbol.type` (FUNC/OBJECT/IMPORT/EXPORT) | 1:1 | enum mapping | A |
| 3.8.4 | `<entry @space @offset @size>` | `FileInfo.Symbol.{address,size}` | 1:1 | direct | A |
| 3.8.5 | `<rangelist><range>` | (drop) | — | drop | A |
| **3.9 Misc** ||||||
| 3.9.1 | `<jumptablelist>` | (drop initially) | — | **deferred** | **C** (§6.6 jumptable) |
| 3.9.2 | `<override>` | (drop) | — | drop | A |

**총 항목**: 60.
- **Tier A safe drop / direct**: 39
- **Tier B lossy tolerated**: 11
- **Tier C critical (diagnostic 강제)**: 10 site → §6 의 **7 unique drop 카테고리** (address space, type identity / struct, calling_conv, vararg, noreturn, indirect, param>16, jumptable, seqnum)

---

## §4. P-Code opcode → IrOpcode mapping (3.4.1 상세)

> **출처**: `third_party/ghidra-decompile/cpp/op.cc` `OpCode` enum (74 opcodes) + AURA `decompiler.h` `IrOpcode` (48+ opcodes).

### §4.1 1:1 직접 매핑 (44/74 = 59%)

| Ghidra OpCode | AURA IrOpcode | 비고 |
|---|---|---|
| CPUI_COPY | IR_OP_COPY | — |
| CPUI_LOAD | IR_OP_LOAD | space 인자 drop (Tier C §6.1) |
| CPUI_STORE | IR_OP_STORE | space 인자 drop (Tier C §6.1) |
| CPUI_BRANCH | IR_OP_JUMP | — |
| CPUI_CBRANCH | IR_OP_BRANCH | — |
| CPUI_BRANCHIND | IR_OP_JUMP (indirect flag) | Tier C §6.4 |
| CPUI_CALL | IR_OP_CALL | — |
| CPUI_CALLIND | IR_OP_CALL (indirect flag) | Tier C §6.4 |
| CPUI_RETURN | IR_OP_RET | — |
| CPUI_INT_EQUAL | IR_OP_CMP_EQ | — |
| CPUI_INT_NOTEQUAL | IR_OP_CMP_NE | — |
| CPUI_INT_LESS | IR_OP_CMP_ULT | — |
| CPUI_INT_LESSEQUAL | IR_OP_CMP_ULE | — |
| CPUI_INT_SLESS | IR_OP_CMP_SLT | — |
| CPUI_INT_SLESSEQUAL | IR_OP_CMP_SLE | — |
| CPUI_INT_ZEXT | IR_OP_ZEXT | — |
| CPUI_INT_SEXT | IR_OP_SEXT | — |
| CPUI_INT_ADD | IR_OP_ADD | — |
| CPUI_INT_SUB | IR_OP_SUB | — |
| CPUI_INT_CARRY | IR_OP_CARRY | Phase 2-X-1 |
| CPUI_INT_SCARRY | IR_OP_SCARRY | Phase 2-X-1 |
| CPUI_INT_SBORROW | IR_OP_SBORROW | Phase 2-X-1 |
| CPUI_INT_2COMP | IR_OP_NEG | — |
| CPUI_INT_NEGATE | IR_OP_NOT | bitwise (~) |
| CPUI_INT_XOR | IR_OP_XOR | — |
| CPUI_INT_AND | IR_OP_AND | — |
| CPUI_INT_OR | IR_OP_OR | — |
| CPUI_INT_LEFT | IR_OP_SHL | — |
| CPUI_INT_RIGHT | IR_OP_LSHR | — |
| CPUI_INT_SRIGHT | IR_OP_SAR | — |
| CPUI_INT_MULT | IR_OP_MUL | — |
| CPUI_INT_DIV | IR_OP_UDIV | — |
| CPUI_INT_SDIV | IR_OP_SDIV | — |
| CPUI_INT_REM | IR_OP_UREM | — |
| CPUI_INT_SREM | IR_OP_SREM | — |
| CPUI_BOOL_NEGATE | IR_OP_NOT (bool path) | sort.kind 검사 |
| CPUI_BOOL_AND | IR_OP_AND (bool path) | — |
| CPUI_BOOL_OR | IR_OP_OR (bool path) | — |
| CPUI_BOOL_XOR | IR_OP_XOR (bool path) | — |
| CPUI_PIECE | IR_OP_APPEND | Phase 2-X-1 |
| CPUI_SUBPIECE | IR_OP_EXTRACT | Phase 2-X-1 |
| CPUI_POPCOUNT | IR_OP_POPCOUNT | — |
| CPUI_LZCOUNT | IR_OP_CLZ | — |
| CPUI_MULTIEQUAL | IR_OP_PHI | SSA φ |

### §4.2 미커버 / 변환 필요 (30/74 = 41%)

| Ghidra OpCode | 처리 | Tier |
|---|---|---|
| CPUI_INDIRECT | IR_OP_UNSUPPORTED + diagnostic | **C** §6.4 |
| CPUI_FLOAT_* (15 ops) | IR_OP_UNSUPPORTED (Phase F floating) | B (defer) |
| CPUI_CPOOLREF | IR_OP_UNSUPPORTED | A (Java/JVM only) |
| CPUI_NEW | IR_OP_UNSUPPORTED | A (Java/JVM only) |
| CPUI_INSERT / CPUI_EXTRACT | IR_OP_APPEND / EXTRACT (semantic match 검증) | B (§7 harness) |
| CPUI_SEGMENTOP | IR_OP_UNSUPPORTED | A (x86 segment) |
| CPUI_PTRADD / CPUI_PTRSUB | IR_OP_ADD / SUB (포인터 hint 손실) | B |
| CPUI_CAST | IR_OP_COPY (sort 변경) | B (§7 검증) |
| CPUI_CALLOTHER | IR_OP_UNSUPPORTED + mnemonic | A |

**커버리지 = 59% (44/74)**. 미커버는 IR_OP_UNSUPPORTED + mnemonic[16] 으로 fallthrough → `HirFunc.unsupported_mnems` 누적 → 사용자 visible. Tier C 항목 (INDIRECT) 은 추가로 §13 diagnostic emit.

---

## §5. CFG edge kind 추정 (3.3.4 상세)

Ghidra `<edge @end @rev>` 는 edge kind 정보 미포함. AURA `CfgEdge.kind` 추정 규칙:

| 상황 | 추정 kind |
|---|---|
| from_block 의 마지막 op = CPUI_BRANCH | FALLTHROUGH (단일 successor) |
| from_block 의 마지막 op = CPUI_CBRANCH, edge index 0 | BRANCH_FALSE |
| from_block 의 마지막 op = CPUI_CBRANCH, edge index 1 | BRANCH_TRUE |
| from_block 의 마지막 op = CPUI_BRANCHIND | FALLTHROUGH + Tier C diagnostic (§6.4) |
| from_block 의 마지막 op = CPUI_RETURN | (no edge — block terminal) |
| from_block 의 마지막 op = CPUI_CALL + 다음 block 존재 | FALLTHROUGH |
| Ghidra 가 edge 를 emit 했으나 위 패턴 미일치 | FALLTHROUGH (default) + Tier B harness flag |

**검증 필요**: §7 자동 diff harness 의 edge.kind match-rate ≥99%.

---

## §6. Drop classification — 3-tier (사용자 조건 1)

> **사용자 조건 1**: A (safe drop), B (lossy but tolerated), C (critical drop). Tier C 모두 diagnostic emit 강제. **silent drop 금지**.
>
> **Diagnostic emission**: §13 spec.

### §6.0 Tier 정의

**Tier A — Safe drop**
- Drop 후 codegen / GUI / type infer / SSA 가 정상 동작
- 사용자 가시 영향 없음
- silent OK
- 예: `<function @id>` (Ghidra 내부 ID)

**Tier B — Lossy but tolerated**
- 정보 손실 있으나 AURA 자체 분석으로 *부분* 복구 가능
- §7 harness 가 영향 측정 (T2/T3/T4)
- silent 허용 (단 §7 harness 통과 필요)
- 예: edge.kind 추정, type qualifier (const/volatile)

**Tier C — Critical drop**
- 정보 손실이 codegen 정합성 / 의미 보존 / 사용자 expectation 에 *직접* 영향
- **반드시 diagnostic emit** (§13):
  ```xml
  <diagnostic
    severity="critical"
    reason="<short reason key>"
    element="<Ghidra XML element/attr>"
    function_addr="<hex addr>"
    detail="<optional human-readable>"/>
  ```
- §7 harness 에서 Tier C 발생 시 **hard fail** (조건 2)
- 예: address space drop, calling convention drop, indirect ops

### §6.1 Tier C — Address Space (다중 공간 → 단일 공간)

**Ghidra**: `<addr @space="ram\|register\|stack\|unique\|const">` — 4+ 공간 구분.
**AURA**: 단일 통합 주소 공간 (`AuraAddr` = uint64).

**Drop 영향**:
- register varnode 와 stack varnode 가 동일 offset 일 때 충돌 가능
- unique space 의 임시값이 ram address 와 같은 offset 가지면 SSA id 충돌 위험

**Mitigation**:
- IrVal.id 는 Ghidra @ref 직접 매핑 → space 충돌 회피 (id 가 unique)
- §6.3 권장 ABI: HirFunc.addr_space (default address space hint) + IrVal.sort.kind 에 space hint 추가
- harness §7 = space 별 collision count 측정

**Diagnostic emit (강제)**:
```xml
<diagnostic severity="critical"
  reason="address_space_dropped"
  element="addr/@space"
  function_addr="0x..."
  detail="space=register|stack|unique encountered; AURA single-space mapping"/>
```
**발생 빈도**: 거의 모든 함수 (ram 외 space 가 일반적). harness §7 에서 발생 카운트만 측정 (count=0 강제 X). 단 register-stack id collision count = 0 강제.

### §6.2 Tier C — Type Identity & Struct/Union Layout

**Ghidra**: `<typeref @id>` 글로벌 타입 ID + `<type>` 정의에서 field offset / nested type 보존.
**AURA**: `HirType.name[128]` (string only).

**Drop 영향**:
- 동일 이름 다른 layout 구분 불가
- nested struct 재귀 표현 X
- typedef chain 평탄화 손실

**Mitigation**:
- AURA 기존 `struct_recovery.c` 재사용 + StructRecoveryResult 와 *교차 검증*
- 양쪽 layout 일치 시 신뢰, 불일치 시 §7 harness flag + 사용자 결정
- HirField AST 노드는 emit 시점 정보만 → layout 기반 추론은 별도 path

**Diagnostic emit (struct/union 만)**:
```xml
<diagnostic severity="critical"
  reason="struct_layout_dropped"
  element="type/@metatype=struct|union"
  function_addr="0x..."
  detail="ghidra type=struct_<id>, fields=<count>, struct_recovery_match=<bool>"/>
```

**필요 D-29 작업**: `codegen.c` 에서 Ghidra `<type>` 정의 → AURA struct_recovery 형식 변환 함수 추가 (~150 LOC).

### §6.3 Tier C — Function Attributes (Calling Convention / Vararg / Noreturn)

**Ghidra**: `<prototype @model="cdecl\|stdcall\|...">`, `@dotdotdot=1`, `@noreturn=1`.
**AURA 현재**: HirFunc 에 first-class field **없음**. `call_fixup.c` 의 lookup 테이블 (이름 기반) partial 처리.

**Drop 영향**:
- noreturn 부재 → CFG 후속 block 의 unreachable code 미제거 (HirEmissionStats.noreturn_truncations 영향)
- vararg 부재 → param 개수 잘못 추정
- calling convention 부재 → param register binding 잘못

**Mitigation = HirFunc ABI 확장** (사용자 조건 3 승인):

#### 필수 추가 (Phase 2 entry gate)
```c
/* include/hir.h §5 추가 */
typedef enum {
    HIR_CC_DEFAULT = 0,
    HIR_CC_CDECL,
    HIR_CC_STDCALL,
    HIR_CC_FASTCALL,
    HIR_CC_THISCALL,
    HIR_CC_SYSV_AMD64,
    HIR_CC_AAPCS,
    HIR_CC_OTHER,  /* model 이름 보존 */
} HirCallConv;

/* HirFunc 추가 fields */
HirCallConv calling_conv;       /* §6.3 필수 */
char        cc_other_name[32];  /* HIR_CC_OTHER 시 model 원본 */
uint8_t     is_vararg : 1;      /* §6.3 필수 */
uint8_t     is_noreturn : 1;    /* §6.3 필수 */
uint8_t     is_inline_hint : 1; /* B-tier, 보조 */
```

#### 권장 추가 (사용자 조건 3 권장)
```c
typedef enum {
    HIR_ADDR_RAM = 0,      /* default */
    HIR_ADDR_REGISTER,
    HIR_ADDR_STACK,
    HIR_ADDR_UNIQUE,       /* compiler temporary */
    HIR_ADDR_OTHER,
} HirAddrSpace;

typedef struct {
    HirAddrSpace space;
    char         reg_name[8];   /* "RAX"/"X0"/"R0"/...; empty if non-register */
    int32_t      stack_offset;  /* if space==STACK; else 0 */
    uint16_t     size;          /* bytes */
} HirStorage;

/* HirFunc 추가 */
HirAddrSpace addr_space;             /* §6.3 권장 — default address space hint */
HirStorage   return_storage;         /* §6.3 권장 — return value 저장 위치 */
HirStorage   param_storage[16];      /* §6.3 권장 — params[] 와 1:1 대응 */
```

**Sizeof 영향**: HirFunc 기존 ~600B → 신규 ~700B (+100B). codegen / hir_emit 에서 default value (0) 시 기존 동작 유지 (backwards-compat).

**Test plan**:
- 기존 ctest 190/191 GREEN 보존
- 신규 test: `test_hir_calling_conv.c` (Ghidra XML cdecl/stdcall fixture → HirFunc 검증)

**Diagnostic emit** (drop 발생 시 — 즉 Ghidra @model="unknown" 같은 fallback 시):
```xml
<diagnostic severity="critical"
  reason="calling_conv_unknown"
  element="prototype/@model"
  function_addr="0x..."
  detail="ghidra=unknown, aura=DEFAULT"/>
```

### §6.4 Tier C — CPUI_INDIRECT / CPUI_BRANCHIND / CPUI_CALLIND

**Ghidra**: indirect operations (jumptable / function pointer / virtual call) 명시 표현.
**AURA**: indirect 표현 없음. IR_OP_UNSUPPORTED + mnemonic fallback.

**Drop 영향**:
- indirect call (function pointer) → unresolved call site, control flow 단절
- indirect branch (jumptable) → CFG 단일 successor 만 인식

**Mitigation**:
- Ghidra `<jumptablelist>` 결과 활용 → 각 case target 을 명시 successor edge 로 추가 (§6.6 처리)
- indirect call = IR_OP_CALL + dst.id=UNDEF + srcs[0]=function pointer SSA. 새 IrOpcode 변형 도입 *없이* 기존 IR_OP_CALL 재해석
- §7 harness = indirect call 발견 시 "function pointer" annotation 출력 검증

**Diagnostic emit (강제)**:
```xml
<diagnostic severity="critical"
  reason="indirect_op"
  element="op/@code=CPUI_BRANCHIND|CPUI_CALLIND|CPUI_INDIRECT"
  function_addr="0x..."
  detail="opcode=<op>, fallback=<treatment>"/>
```

### §6.5 Tier C — Param > 16 (한도 초과)

**Ghidra**: `<param>` 무제한.
**AURA**: `HirFunc.params[16]` 고정 + (권장) `param_storage[16]` 동기.

**Drop 영향**:
- 16 초과 param 절단 → 함수 signature 불완전

**Mitigation**:
- 16 초과 시 처음 16개만 매핑
- §7 harness = 함수당 param count distribution 측정
- 실 binary 에서 16 초과 빈도 보고 (cat / ls / aura-self)

**Diagnostic emit (강제)**:
```xml
<diagnostic severity="critical"
  reason="param_truncated"
  element="prototype/internallist/param"
  function_addr="0x..."
  detail="ghidra=<count>, aura=16"/>
```

**Phase 2+ 검토**: 16 초과 함수 비율 ≥1% 시 HirFunc.params[] 동적 배열로 확장 plan.

### §6.6 Tier C — Jumptable (deferred)

**Ghidra**: `<jumptablelist>` 가 switch case → target address 명시.
**AURA**: switch 는 hir_builder structuring 단계 추정 (HIR_SWITCH 복원).

**Decision**: D-29 *초기* 에는 `<jumptablelist>` drop. 단순 switch 는 hir_builder 자체 인식 가능. 복잡 jumptable (PIC dispatch / 문자열 hashed switch) = Phase 1+ 별도 결정.

**Mitigation**: §7 harness = jumptable 미연결로 인한 missing_successor 카운터 측정. 임계 (≥10/binary) 초과 시 jumptable parse 정식 도입.

**Diagnostic emit (강제)**:
```xml
<diagnostic severity="critical"
  reason="jumptable_dropped"
  element="jumptablelist/jumptable"
  function_addr="0x..."
  detail="cases=<count>, indirect_branch_at=<addr>"/>
```

### §6.7 Tier C — SeqNum Identity

**Ghidra**: `<seqnum @time @uniq>` 가 op 단위 unique ID.
**AURA**: `IrInstr.origin_addr` (AuraAddr) 만 — 동일 address 의 multiple op 구분 불가.

**Drop 영향**:
- 동일 instruction 의 lifted P-Code 들이 origin_addr 동일 → 영속 키 (§8) 에서 op-level 구분 불가
- T-5d (영속 데이터) 의 ssa_def_site_offset 만으로는 동일 addr 의 여러 op 구분 불완전

**Mitigation**:
- origin_addr 은 *그룹 ID* 로만 사용
- 영속 키 보강: `(function_addr, origin_addr, op_index_in_block, var_role)` 4-tuple 채택
- IrBlock.instrs[] 배열 인덱스로 op 순서 보장 (SSA id 가 별도 unique)

**Diagnostic emit (강제, 필요 시)**:
```xml
<diagnostic severity="critical"
  reason="seqnum_collision"
  element="op/seqnum"
  function_addr="0x..."
  detail="origin_addr=<addr>, ops_at_addr=<count>"/>
```

### §6.8 Tier B — Lossy hints (mitigation 가능, silent OK)

| 항목 | 상실 정보 | Mitigation |
|---|---|---|
| Varnode @grp (merge group) | covermerge hint | AURA SSA 자체 merge → 정보 무관 |
| Varnode @persists / @addrtied / @unaff / @volatile | 변수 lifetime hint | AURA dataflow 자체 추론 |
| HighVariable @class="constant\|other" | 상수 / 기타 | constant = IR_OP_CONST, "other" drop |
| Type qualifier (const/volatile/restrict) | C 의미 | drop 후 codegen 정성적 emit (P1 검토) |
| LikelyTrash (call kill set) | register 손상 | AURA 자체 register tracking |
| PTRADD/PTRSUB 포인터 hint | 포인터 산술 식별 | IR_OP_ADD/SUB 평탄화 후 type infer 복구 |
| Edge kind 추정 (§5) | branch true/false 신뢰도 | §7 harness ≥99% |
| CPUI_FLOAT_* (15 ops) | 부동소수점 | Phase F (defer) |

§7 harness T2 (op coverage) / T3 (structural diff) 가 위 항목 영향 측정.

### §6.9 Tier A — Safe drops (silent OK)

**No-op drops** (codegen / GUI / type / SSA 영향 없음):
- `<function @id>` (Ghidra internal)
- `<function @size>` (AURA derives from CFG)
- `<block><bhead>` (BlockGraph hierarchy 미사용)
- `<typeref @id>` (AURA 자체 type ID 사용)
- `<prototype @inline\|@constructor\|@destructor>` (C++ only, drop 시 동작 동일)
- `<prototype><inject>` (Ghidra fixup, AURA 자체 call_fixup 사용)
- `<scope><rangelist>` (AURA 미사용)
- `<override>` (Ghidra interactive override, AURA 미적용)
- CPUI_CPOOLREF / CPUI_NEW (Java/JVM only)
- CPUI_SEGMENTOP (x86 segment, modern code rare)
- CPUI_CALLOTHER (architecture pseudo-op)

---

## §7. Automated diff harness 설계 (사용자 조건 2)

> **사용자 조건 2**: 5-tier 유지. **각 tier 별 ≥95%** (평균값 금지). **Tier C 발생 시 무조건 fail**.

### §7.1 Harness 구조

```
Input fixture binary (예: /bin/cat, ls, aura-self)
  │
  ├─ Path A: Ghidra subprocess (aura-decompile)
  │   │
  │   └─► XML output → byte normalize → future XML parse → AURA HirFunc
  │       │             ↓
  │       │     <diagnostic .../> stream (Tier C)
  │       │
  │       └─► hir_emit → Pseudo-C "A.txt"
  │
  └─ Path B: Ghidra GUI (golden, manual capture)
      │
      └─► Pseudo-C "B.txt"
      │
   Diff(A.txt, B.txt) → match-rate per-tier
   + Diagnostic stream check (Tier C 발생 시 hard fail)
```

### §7.2 Match metric — per-tier ≥95% (no averaging)

| Tier | 지표 | 임계 | 산정 방식 |
|---|---|---|---|
| **T1: Element coverage** | mapping 표 §3 의 60 항목 중 actual XML 등장 항목 비율 | **≥95%** (각 fixture 별) | 등장 element 수 / fixture 의 unique element 수 |
| **T2: Op coverage** | §4.1 1:1 매핑 44 op 중 fixture 등장 op 비율 | **≥95%** | 매핑된 op count / fixture 의 unique op count |
| **T3: AST structural diff** | block/op count 일치 | **≥95%** | 1 - abs(aura_count - ghidra_count) / ghidra_count, **per-function** |
| **T4: Variable name match** | HighVariable name → HirLocal.name 대조 | **≥95%** | matched names / total names, **per-function** |
| **T5: Pseudo-C string diff** | A.txt vs B.txt token-level (변수명 정규화) | **≥95%** | LCS-based token match ratio, **per-function** |

**Phase 2 entry gate** (5 조건 AND, 평균 금지):
- T1 ≥95% AND T2 ≥95% AND T3 ≥95% AND T4 ≥95% AND T5 ≥95%
- **AND** Tier C diagnostic count = 0 *OR* 모든 Tier C 발생 사용자 명시 승인

### §7.3 Tier C hard-fail rule (조건 2 강제)

```
for each function in fixture:
  parse_ghidra_xml → IrFunc, HirFunc, diagnostics[]
  if any diagnostic in diagnostics[] with severity="critical":
    if not user_explicitly_acknowledged(diagnostic):
      HARNESS_RESULT = FAIL
      break
```

**구현 위치**: `tools/aura-ghidra-diff` (D-29 신규 도구).

**사용자 acknowledge 메커니즘**:
- `tests/fixtures/ghidra_golden/<binary>.acknowledged_diagnostics.txt` — Tier C 항목 list (reason / function_addr 별)
- 사용자가 명시적으로 "OK to proceed despite drop" 표기한 항목만 harness 통과
- 새로 발생한 Tier C (acknowledged 목록에 없음) = 즉시 FAIL

### §7.4 Harness 구현 (D-29 부터)

신규 파일:
- `tests/integration/test_ghidra_xml_mapping.c` — XML element coverage harness (T1)
- `tests/integration/test_ghidra_op_mapping.c` — op coverage harness (T2)
- `tools/aura-ghidra-diff` — A vs B path comparator (T3-T5) + diagnostic check
- `tests/fixtures/ghidra_golden/cat.c` etc. — Ghidra GUI captured pseudo-C (수동, ≥3 binary)
- `tests/fixtures/ghidra_golden/<binary>.acknowledged_diagnostics.txt`

ctest label = `ghidra-mapping`. CI 미실행 (수동 골든 의존). D-29 머지 전 사용자 수동 실행 + match-rate 보고.

### §7.5 Critical drop 검증 매트릭스

§6.1-§6.7 각 Tier C 항목 별 specific 테스트:

| Drop | 검증 fixture | 합격 조건 |
|---|---|---|
| §6.1 Address space | x86_64 함수 with stack+register collision | IrVal.id collision = 0, diagnostic count = (acknowledged count) |
| §6.2 Type / struct layout | nested struct fixture (lib/printf.c) | AURA struct_recovery + Ghidra `<type>` field offsets 일치 ≥95% |
| §6.3 Calling conv | cdecl + stdcall mixed binary | HirFunc.calling_conv match Ghidra @model = 100% |
| §6.4 Indirect | function pointer fixture | indirect call 식별률 ≥99% |
| §6.5 Param > 16 | (현실 binary 에서 드묾) | 발생 시 정확 truncate + diagnostic |
| §6.6 Jumptable | 50+ case switch fixture | (deferred) missing_successor count ≤10 |
| §6.7 SeqNum | 동일 addr 다중 P-Code op 함수 | persistent key collision = 0 |

### §7.6 Out of harness

- Inline assembly: drop (rare in compiled C)
- Floating point full coverage: Phase F defer
- C++ specific (vtable, mangling): Phase 1+ defer
- Cross-compiler (clang vs gcc) parity: Phase 2+ defer

---

## §8. Schema migration plan (영속 데이터)

> **R4 (영속 상태 매핑 누락) 차단**: T-5b/T-5d 의 영속 키 = `(function_address, ssa_def_site_offset, var_role)`. Ghidra HighSymbol 키 = 다른 모델.

### §8.1 SSA id 안정성

**문제**: Ghidra `<addr @ref>` 는 *현재 디컴파일 세션 한정* 의 creation index. 디컴파일 다시 돌리면 ref 값 변경 가능.

**해결**: AURA 영속 키 = `(function_address, origin_addr, op_index_in_block, var_role)`.
- `function_address` = HirFunc.func_addr (안정)
- `origin_addr` = SSA def site instruction 의 machine addr (안정, 컴파일러 결정적)
- `op_index_in_block` = IrBlock.instrs[] 내 인덱스 (§6.7 seqnum collision 차단용 보강)
- `var_role` = entry-block live-in (param) / stack slot / register def / heap (분류)

**Mitigation**: D-29 시점에 Ghidra `<addr @ref>` → AURA SSA id → 영속 키 변환 함수 명시.

### §8.2 사용자 rename 보존

**시나리오**: 사용자가 var_3 → my_counter rename. 다음 세션에서 디컴파일 재실행 시 SSA id 가 var_5 로 바뀜.

**해결**: 영속 키 (위) 로 rename map 저장. 매 디컴파일 후 SSA id 재계산 + key 매칭으로 이름 복원.

**T-5b/T-5d 와의 정합**: 본 §8.1-§8.2 가 T-5b/T-5d plan (`~/.claude/plans/2-3-iterative-kazoo.md`) 과 동일 키 구조 사용 — *별도 design turn 불필요*.

---

## §9. D-29 진입 체크리스트 (사용자 조건 5 반영)

> **사용자 조건 5 binding 순서**:
> 1. D-28 문서 PR 생성 ← **본 PR 진행 중**
> 2. T-5b finalize (R6 차단 종료)
> 3. ~~D-26 governance commit (R7)~~ — **이미 PR #42 `83e40af` main 머지 완료**
> 4. ~~D-27 PR #43 머지~~ — **이미 `fe39dfd` main 머지 완료**
> 5. D-29 진입

D-28 → D-29 전제:

- [ ] **본 D-28 PR main 머지** (조건 4: `d28/hir-mapping-plan` 별도 branch / PR)
- [ ] **T-5b PR main merge** (R6 차단)
- [ ] §6 Tier C diagnostic emission 사양 (§13) 사용자 최종 검토
- [ ] §7 harness fixture (3 binary Ghidra GUI golden) 수동 capture 완료
- [ ] HirFunc ABI 신규 field (필수 3 + 권장 3) 구현 plan 수립 (D-29 내부 step)
- [x] PR #43 (D-27 Phase 0) main merge ← **`fe39dfd` 완료**
- [x] PR #42 (D-26 governance) main merge ← **`83e40af` 완료**
- [ ] D-29 plan 작성 (별도 turn) — `~/.claude/plans/d29-codegen-integration.md`

D-29 완료 시 산출물:
- `src/decompiler/codegen.c` 에 Ghidra XML parse → IrFunc/HirFunc 변환 path 추가
- `tools/aura-ghidra-diff` 골든 비교 도구
- HirFunc ABI 확장 (필수 3 + 권장 3 field)
- §7 harness ≥95% per-tier 통과 + Tier C diagnostic count = 0 (or acknowledged)

---

## §10. 후속 결정 / 미해결

- **D-29 plan turn**: 본 문서 binding 입력. 코드 작성 X. plan = `codegen.c` 변경 step + 테스트 step.
- **Phase 1**: 1 binary end-to-end IR extraction. 본 문서 §3 매핑 적용 후 첫 실 검증.
- **Phase 2 Gate**: §7 5-tier 모두 ≥95% per-tier + Tier C 0 ack 후 AURA pass 점진 폐기 시작.
- **HirFunc ABI bump**: §6.3 의 calling_conv / is_vararg / is_noreturn (필수) + addr_space / return_storage / param_storage[] (권장) 추가 = `include/hir.h` 변경 = SemVer minor (v2.5.0). v2.4.0 wrap 후 별도 release.
- **Floating point coverage** (§4.2 CPUI_FLOAT_*): Phase F (별도 미정 plan).
- **Jumptable parse** (§6.6): Phase 1+ 후 jumptable 미연결률 측정 후 정식 도입 결정.
- **>16 param 동적 배열**: 실 binary 빈도 ≥1% 시 Phase 2+ plan.

---

## §11. Cross-references

- D-26 (정책 해제): `project_d26_custom_first_lifted.md`, PR #42 `83e40af`
- D-27 (Phase 0 build/run): `project_d27_ghidra_phase0_verification.md`, PR #43 `fe39dfd`
- 본 plan 의 Risk Register: `~/.claude/plans/aura-harmonic-teapot.md` "RISK REGISTER" R1-R10
- Ghidra source: `~/Desktop/AURA-d27/third_party/ghidra-decompile/cpp/{funcdata,marshal,block,op,varnode,fspec,variable,type}.{cc,hh}`
- AURA HIR: `~/Desktop/AURA/include/{hir,decompiler,cfg,file_format,var_propagation}.h`
- AURA IR builder: `~/Desktop/AURA/src/decompiler/{hir_builder,hir_emit,codegen,var_propagation,type_constraint}.c`

---

## §12. Sign-off

**문서 status**: 사용자 조건부 승인 (Session #22, 2026-04-26). 5 조건 모두 반영.
**다음 step**: 본 PR open + 사용자 최종 검토 + main merge.
**Post-D-28**: T-5b finalize → D-29 plan turn → 코드 작성 시작.

---

## §13. Diagnostic emission 사양 (사용자 조건 1 강제)

> **위치**: AURA codegen.c (Ghidra XML parse 단계) → diagnostic stream
>
> **포맷**: AURA 자체 XML element (Ghidra schema 와 별도)

### §13.1 XML schema

```xml
<aura_diagnostics binary="<path>" timestamp="<iso8601>">
  <diagnostic
    severity="critical|warning|info"
    reason="<short_key>"
    element="<source XML element/attr path>"
    function_addr="0x<hex>"
    detail="<optional human-readable>"
    op_addr="0x<hex>"           <!-- optional: op 단위 -->
    var_id="<uint32>"           <!-- optional: varnode 단위 -->
  />
  ...
</aura_diagnostics>
```

### §13.2 Tier C reason key 사전

| reason | 발생 조건 | 추가 attr |
|---|---|---|
| `address_space_dropped` | §6.1 — addr/@space != "ram" 발견 | space, op_addr |
| `address_space_collision` | §6.1 — register-stack id 충돌 | colliding_ids |
| `struct_layout_dropped` | §6.2 — struct/union @metatype | type_id, fields |
| `type_identity_dropped` | §6.2 — typeref name 동일 layout 다름 | type_name, count |
| `calling_conv_unknown` | §6.3 — prototype @model unknown | model |
| `vararg_dropped` | §6.3 — dotdotdot=1 + AURA HIR 미적용 path | — |
| `noreturn_dropped` | §6.3 — noreturn=1 + truncation 실패 | — |
| `indirect_op` | §6.4 — INDIRECT/BRANCHIND/CALLIND | opcode, fallback |
| `param_truncated` | §6.5 — params > 16 | ghidra_count, aura_count |
| `jumptable_dropped` | §6.6 — jumptable 미파싱 | cases |
| `seqnum_collision` | §6.7 — origin_addr 다중 op 충돌 | origin_addr, ops_count |
| `op_unsupported_critical` | §4.2 — Tier C 등급 미커버 op | opcode, mnemonic |

### §13.3 Diagnostic stream 출력 경로

1. **Runtime stream** (실 디컴파일 시): `stderr` 에 한 줄씩 (line-prefixed `AURA-DIAG: `)
2. **Aggregate file** (harness §7 시): `tests/fixtures/ghidra_golden/<binary>.diagnostics.xml` 에 누적
3. **GUI surface** (Phase 1+): `HirFunc.diagnostics[]` field 에 보관 → `decompile_view.cpp` 가 visual indicator 표시

### §13.4 Acknowledge 메커니즘 (§7.3)

`tests/fixtures/ghidra_golden/<binary>.acknowledged_diagnostics.txt` 형식:
```
# reason | function_addr | (optional detail substring) | acknowledged_by | iso8601_date
address_space_dropped | 0x401000 | space=stack | starwinde | 2026-04-26
calling_conv_unknown  | 0x401200 | model=unknown | starwinde | 2026-04-26
```

harness §7 가 unacknowledged Tier C 발견 시 즉시 FAIL.

### §13.5 Severity 등급

| Severity | 사용 | 예 |
|---|---|---|
| `critical` | Tier C drop | 본 §13.2 표 모두 |
| `warning` | Tier B 발생 시 (선택적, harness 에서 측정용) | edge_kind_unclear |
| `info` | Tier A 정보성 (debug 용) | type_qualifier_dropped |

본 PR 에서는 `critical` severity 만 강제 (조건 1). warning / info 는 D-29 시점에 추가.

---

## §14. Binding sequence (사용자 조건 5)

> **본 sequence 는 plan-binding** — 변경 시 별도 governance turn 필요.

```
[현재 상태 ✅]
  ✅ D-26 (PR #42 83e40af main 머지)
  ✅ D-27 Phase 0 (PR #43 fe39dfd main 머지)

[본 turn]
  🔵 D-28 PR (이 문서)
        branch: d28/hir-mapping-plan
        target: main
        scope: 본 문서 + Tasks.md / PRD.md 메타 + MEMORY.md index

[D-28 머지 후]
  🔵 T-5b finalize (R6 제거)
        branch: phase-2.4tp/t5b-rename-propagation (existing)
        scope: vp_apply_to_hir wire-up + UU 6 파일 해소 + GUI rename 동작 검증
        DoD: PR open + main 머지

[T-5b 머지 후 — D-29 entry gate]
  🔵 §7 harness fixture capture (수동, ≥3 binary Ghidra GUI 골든)
        Phase 2 entry gate 의 사전 준비

[Gate 충족 후]
  🔵 D-29 plan turn
        plan file: ~/.claude/plans/d29-codegen-integration.md
        scope: codegen.c 변경 step + HirFunc ABI 확장 step + harness 통합 step
        코드 작성 X (plan only)

[D-29 plan 승인 후]
  🔵 D-29 구현 turn
        scope: codegen.c 통합 + HirFunc ABI + tools/aura-ghidra-diff
        ★ 첫 실 IR 데이터 flow

[D-29 머지 후]
  🔵 Phase 1 — 1 binary end-to-end IR 검증
  🔵 Phase 2 — 3 binary parity (cat / ls / aura-self)
        gate: §7 5-tier 모두 per-tier ≥95% AND Tier C ack count = total Tier C count

[Phase 2 GREEN 후]
  🔵 Phase 3+ — AURA decompile pass 점진 폐기 (47 .c 파일)
```

본 sequence 위반 시 (예: T-5b 미머지 상태로 D-29 진입) = R6 재발 / 영속 데이터 충돌 위험.
