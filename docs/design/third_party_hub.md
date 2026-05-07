# Third-Party I/O Hub — Design

> Status: **Skeleton only** (introduced 2026-04-29). Default-OFF CMake option `AURA_ENABLE_RIZIN_HUB`. Adapter migration tracked as follow-up D-decisions.

## 1. 동기 (Why)

현 시점 AURA 는 7 개 third-party 를 각자 다른 어댑터 패턴으로 wrap 한다:

| 라이브러리 | 어댑터 진입 | 입력 자료형 | 출력 자료형 |
|-----------|-----------|-----------|-----------|
| Capstone  | `disasm_run(ctx, bytes, size, base, results[], max)` | raw `uint8_t*` + base VA | `DisasmResult[]` |
| Zydis     | `patch_encode(asm_str, vaddr, &out)` | C string + VA | `PatchResult { bytes[15], len }` |
| Ghidra    | subprocess → XML → `ghidra_xml_to_hir` | 함수 단위 사전 추출 | `AuraGhirFunc` (4-요소 트리) |
| YARA      | (별도 매칭 fn) | mmap'd bytes | match 콜백 |

각 어댑터가 독립적으로 `pipeline.c` 에 진입하고 결과를 따로 가공한다. 새 third-party (예: Rizin) 가 합류하면 `pipeline.c` 와 결과 자료형을 또 한 번 깎아야 한다. **공통 입출력 자료형이 없다.**

해결: Rizin 의 canonical 자료형 (`RzCore` / `RzAnalysisOp` / `RzBinSection` / `RzAnalysisFunction`) 을 **`include/third_party_hub/` 내부 격리 mirror 타입** 으로 도입한다 (R-10 — engine canonical 은 AURA core / GUI 로 leak 금지). 모든 third-party 어댑터는 (a) 자기 엔진 캐노니컬을 hub 내부 mirror 로 받아들인 뒤, (b) **AURA normalized record (`FunctionRecord` / `BlockRecord` / `EdgeRecord` / `VariableRecord` / `TypeFactRecord` / `CallEdgeRecord` / `SymbolRecord` / `XrefRecord`) 로 변환** 후 core 에 전달한다 (R-11 provenance + R-12 1 급 record). AURA 의 핵심 IR (`HirFunc`) / Unified Model 은 허브 boundary 너머에 그대로 유지 — 허브는 어댑터 ↔ pipeline 사이의 **격리된 변환 표면**이다.

> **명시**: Rizin canonical / mirror 타입은 third_party_hub 내부 격리 타입이며 AURA 의 정규화 표준이 아니다. AURA 정규화 표준 = `include/aura/normalized_records.h` 의 record set. Rizin 도입 정책은 D-27 (subprocess-only / no librz) 을 따른다.

본 PR 은 **스켈레톤** — Rizin canonical mirror 채움 + AURA normalized record 변환 layer 는 Phase 2A (D-1) 에서 진행.

## 2. 정규화 자료형

| Rizin 원본 | AURA mirror | 헤더 |
|-----------|------------|------|
| `ut64` | `aura_tp_addr_t` (`uint64_t`) | `tp_types.h` |
| `RzCore *` | `aura_tp_binary_t *` (opaque, mmap-backed) | `tp_binary.h` |
| `RzList *` | `aura_tp_vec_t` (contiguous, type-erased) | `tp_types.h` |
| `RzAnalysisOp` | `aura_tp_op_t` | `tp_disasm.h` |
| `RzBinSection` | `aura_tp_section_t` | `tp_layout.h` |
| `RzAnalysisFunction` | `aura_tp_function_t` | `tp_layout.h` |

모든 자료형은 `aura_tp_source_t source` 필드를 갖는다 — payload 가 어떤 어댑터에서 채워졌는지 추적 가능 (`AURA_TP_SOURCE_CAPSTONE`, `_ZYDIS`, `_GHIDRA`, `_YARA`, `_RIZIN`, `_RETDEC`, `_AURA_NATIVE`). 본 source 필드는 hub 내부 격리 추적용이며, AURA normalized record 의 R-11 provenance (`{source, confidence, completeness}`) 는 별도로 변환 단계에서 부착된다.

Rizin 헤더는 **절대 직접 include 하지 않는다** (R-10 + D-27). librz 정적/동적 링크 금지. Rizin 은 별도 프로세스로 실행되며 stdout JSON 만 hub 안에서 cJSON 트리 → mirror 타입으로 채운다. AURA 자체 헤더로 mirror 하여, hub 외부 (core / GUI) 가 이 mirror 타입을 보지 않도록 한다 (R-10 격리).

## 3. 어댑터 계약

```c
typedef struct aura_tp_adapter {
    const char       *name;
    aura_tp_source_t  source;
    uint32_t          caps;     /* OR of aura_tp_caps_t */

    int (*open)(aura_tp_binary_t *bin, void **ctx_out);
    int (*close)(void *ctx);

    int (*disasm_range)(void *ctx, aura_tp_addr_t va, size_t len,
                        aura_tp_vec_t *out_ops);
    int (*list_functions)(void *ctx, aura_tp_vec_t *out_funcs);
    int (*list_sections)(void *ctx, aura_tp_vec_t *out_sections);
} aura_tp_adapter_t;
```

**계약 원칙**:
- 음수 = error (`AURA_TP_E_*`), 0 = OK, 양수 = 부분 성공 (op 수 등).
- `aura_tp_vec_t` 소유권은 호출자 — `aura_tp_vec_init/free` 는 호출자 책임.
- `caps` 가 선언한 capability 만 구현. 미구현 fn-ptr 은 NULL.
- 어댑터는 **immutable static global** 로 등록 (`aura_tp_register_adapter`). 등록 후 fn-ptr 변경 금지.

## 4. 디스패치 정책

```c
int aura_tp_hub_disasm_range(aura_tp_binary_t *bin,
                             aura_tp_source_t  preferred,   /* AUTO 가능 */
                             aura_tp_addr_t va, size_t len,
                             aura_tp_vec_t *out_ops);
```

- `preferred != AUTO`: 정확히 그 source 의 어댑터 lookup. 없거나 caps 미달 시 `E_NOTSUP`.
- `preferred == AUTO`: 고정 우선순위 (`AURA_NATIVE → RIZIN → CAPSTONE → ZYDIS → GHIDRA → YARA`) 로 첫 매칭. 향후 cost-model 도입 가능.

## 5. 본 PR 범위 (skeleton)

### IN
- 헤더 5 종 (`include/third_party_hub/`)
- 스텁 4 종 (`src/third_party_hub/`) — vec / binary (mmap reuse) / registry / hub dispatch
- CMake option `AURA_ENABLE_RIZIN_HUB` (default OFF)
- Surface 테스트 (`tests/third_party_hub/test_skeleton_surface.c`)
- 카탈로그 `third_party/README.md`
- 본 설계 문서

### OUT (별도 D-결정 후보)
1. **D-?? Rizin 벤더링** — submodule / amalgamation / system-find. LGPL-3.0 정적 링크 호환성 분석.
2. **D-?? Capstone 어댑터 마이그레이션** — `disasm_run` → `aura_tp_adapter_t.disasm_range` 매핑. 가장 작은 어댑터부터 dogfood.
3. **D-?? Zydis 어댑터 마이그레이션** — patch capability.
4. **D-?? Ghidra 어댑터 마이그레이션** — decompile capability + AuraGhirFunc 출력 경로 유지.
5. **D-?? `pipeline.c` 가 hub 를 1 차 입력 경로로 사용** — 정규화 자료형이 HIR boundary 에 도달.
6. **D-?? AUTO dispatch cost-model** — 단순 fixed-order → 비용 기반.

## 6. 비목표

- HIR / IR 변경 — 허브는 입력 boundary 에서만 정의, HIR 구조 자체 무수정.
- LLM / GUI / collab — 도메인 외 라이브러리 (cJSON, SQLite, libcurl) 는 직접 사용 유지. 허브로 끌어올리지 않는다.
- 신규 의존성 자동 도입 — 본 PR 은 Rizin 트리 자체를 들여오지 않는다.

## 7. 검증

```bash
# default (OFF) 빌드는 변경 없음
cmake -B build-rel -DCMAKE_BUILD_TYPE=Release
cmake --build build-rel
ctest --test-dir build-rel

# hub ON 빌드 — surface 테스트 1 개 추가
cmake -B build-hub -DAURA_ENABLE_RIZIN_HUB=ON
cmake --build build-hub
ctest --test-dir build-hub -R test_tp_hub_surface
```

surface 테스트는 다음을 보장한다:
- POD 자료형 size/필드 안정성 (drift guard)
- `aura_tp_vec_t` push/grow/free round-trip
- registry 중복 source 거부 + lookup 정확성
- hub dispatch: 미등록/미지원 시 `AURA_TP_E_NOTSUP`, NULL 입력 `E_INVAL`
