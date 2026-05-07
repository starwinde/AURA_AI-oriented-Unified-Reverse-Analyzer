# `third_party/` — AURA 외부 의존성 카탈로그

본 디렉토리는 AURA 가 정적 링크하는(또는 시스템 fallback 으로 동적 링크하는) 외부 라이브러리의 소스/서브모듈을 보관한다.

> **벤더링 정책** (`.claude/CLAUDE.md` §외부 의존성 채택 기준):
> 라이선스 호환 (Apache 2.0 / MIT / BSD / Public Domain / zlib) + foundational commodity + AURA 차별점 아님 = extract 우선. Differentiation (LLM, UX, project DB, AI rename) = 커스텀 유지.

> **신규 의존성 추가 전 사용자 확인 필수** (`rules.md §10`).

---

## 2.1 현재 사용/통합됨

| 디렉토리 | 라이브러리 | 역할 (한 줄) | 라이선스 | 벤더링 방식 | CMake target | wrapper / 호출부 |
|----------|-----------|-------------|---------|------------|--------------|----------------|
| `capstone/` | Capstone ≥ 5.0 | x86/x86_64/ARM/AArch64 디스어셈블 | BSD-3-Clause | submodule + 사전빌드 정적 import | `capstone_static` (IMPORTED) | `src/disasm/capstone_wrapper.c` |
| `zydis/` | Zydis ≥ 4.0 (+zycore) | x86/x86_64 어셈블·인코딩 (바이너리 패치) | MIT | submodule, 정적 import | `zydis_static`, `zycore_static` (IMPORTED) | `src/disasm/zydis_wrapper.c` |
| `cjson/` | cJSON | JSON 파싱 (LLM 응답·collab 메시지) | MIT | 소스 드롭 (`cJSON.c`/`cJSON.h`) | `cjson` (STATIC) | 직접 `#include <cJSON.h>` |
| `sqlite/` | SQLite amalgamation | GUI 프로젝트·collab 저장 (D-13) | Public Domain | 소스 드롭 (`sqlite3.c`/`sqlite3.h`) | `sqlite3` (STATIC, `-w` 경고 억제) | 직접 `#include <sqlite3.h>`, `src/collab/` |
| `curl/` | libcurl ≥ 7.0 | HTTP 클라이언트 (LLM API) | MIT-style (curl) | system `find_package(CURL)` 우선 + 헤더 fallback | `CURL::libcurl` | `src/llm/llm_http.c` 직접 호출 |
| `ghidra-decompile/` | Ghidra decompile (vendored) | 디컴파일 백엔드 (D-27) | Apache-2.0 | `add_subdirectory` (`AURA_BUILD_GHIDRA_DECOMPILE=ON` default) | (서브디렉토리에서 정의) | `src/decompiler/ghidra_subprocess.c`, `ghidra_xml_normalize.c`, `ghidra_xml_to_hir.cpp` |
| `tinyxml2/` | tinyxml2 | Ghidra subprocess 출력 XML 파싱 | zlib | `add_subdirectory` | `tinyxml2` (via `tinyxml2_static`) | `src/decompiler/ghidra_xml_normalize.c` |
| `yara/` | YARA | 바이너리 패턴 룰 엔진 (옵션 빌드) | BSD-3-Clause | `add_subdirectory` (`AURA_BUILD_YARA=ON` default) | (서브디렉토리에서 정의) | `src/scan/` (미존재 — 호출부 예정) |
| `sigdb/` | (placeholder) | FLIRT-like 시그니처 DB | — | 자체 (외부 의존성 없음) | — | `src/flirt/` (미존재 — placeholder 상태) |

---

## 2.2 벤더됨, 미통합

트리는 존재하지만 CMake 에 통합되지 않았고 AURA 호출부가 없다. 채택 여부는 별도 D-항목으로 결정한다.

| 디렉토리 | 라이선스 | 벤더링 상태 | AURA 통합 상태 | 메모 |
|----------|---------|-----------|--------------|------|
| `llvm-project/` | Apache-2.0 with LLVM Exception (`LICENSE.TXT`) — third-party notices 별도 검토 필요 | 풀 트리 벤더됨 | CMake 미통합, 호출부 0 | 채택 여부 D-항목 미결 |
| `retdec/` | `LICENSE` (MIT 기반), `LICENSE-PELIB`, `LICENSE-THIRD-PARTY` — **다중 라이선스 별도 검토 필요** | 풀 트리 벤더됨 | CMake 미통합, 호출부 0 | upstream 자체 "limited maintenance mode" 명시 |
| `rizin/` | LGPL-3.0 (`COPYING`, `COPYING.LESSER`) — **정적 링크 호환성 별도 검토 필요** | 풀 트리 벤더됨 | adapter 없음, integration pending | 정규화 허브(§4) 1차 후보 |

---

## 2.3 Skeleton 머지됨 (어댑터 마이그레이션 보류)

| 항목 | 상태 | 메모 |
|------|------|------|
| `third_party_hub` (헤더·구현) | **Skeleton 머지됨 (2026-04-30)** | `include/third_party_hub/`, `src/third_party_hub/` 트리에 존재. CMake 옵션 `AURA_ENABLE_RIZIN_HUB=OFF` default. surface 테스트 `test_tp_hub_surface_{types,vec,registry,dispatch}` 통과. 실제 어댑터 마이그레이션(Capstone/Zydis/Ghidra/YARA)은 별도 D-항목으로 분리. |

---

## 입출력 계층 매트릭스

**대상**: §2.1 현재 통합된 라이브러리만. wrapper/호출부에서 실제 확인 가능한 자료형 기준. 라이브러리 일반 사양이 아닌 AURA 호출 계층 기준으로 기재한다.

§2.2(`llvm-project`, `retdec`, `rizin`) 는 현재 미사용(adapter 없음, integration pending) 이므로 이 표에서 의도적으로 제외한다.

| 라이브러리 | 입력 (AURA → TP) | 변환 엔진 (실제 호출) | 출력 (TP → AURA) | 어댑터 |
|-----------|-----------------|---------------------|-----------------|--------|
| Capstone | `uint8_t* code, size_t len, uint64_t va, cs_arch, cs_mode` | `cs_open` + `cs_disasm` | `cs_insn[]` → `DisasmResult[]` | `src/disasm/capstone_wrapper.c` |
| Zydis | asm 텍스트 + VA (`ZydisMachineMode` LONG_64 등) | `ZydisEncoderRequest` → `ZydisEncoderEncodeInstruction` | `uint8_t bytes[≤15] + len` → `PatchResult` | `src/disasm/zydis_wrapper.c` |
| cJSON | UTF-8 JSON 문자열 | `cJSON_Parse` | `cJSON*` 트리 (직접 사용) | adapter 없음 |
| SQLite | SQL 문자열 + 바인딩 | `sqlite3_prepare_v2` / `sqlite3_step` | row 커서 (직접 사용) | adapter 없음 |
| libcurl | URL + headers + body (`curl_easy_setopt`) | `curl_easy_perform` | response 바이트 버퍼 + HTTP 상태 코드 | adapter 없음 (호출부: `src/llm/llm_http.c`) |
| Ghidra-decompile | 바이너리 경로 + 함수 VA (subprocess stdin/args) | Ghidra decompile 백엔드 (`ghidra_subprocess.c` 경유) → XML stdout | XML → tinyxml2 정규화 → HIR (`ghidra_xml_to_hir.cpp`) | `src/decompiler/ghidra_subprocess.c`, `ghidra_xml_normalize.c`, `ghidra_xml_to_hir.cpp` |
| tinyxml2 | XML 텍스트 (Ghidra 출력) | `XMLDocument::Parse` | `XMLDocument*` → AURA decompile struct | `src/decompiler/ghidra_xml_normalize.c` |
| YARA | 바이트버퍼 + 컴파일된 룰 | `yr_rules_scan_mem` (match 콜백) | match 결과 → AURA scan 이벤트 (예정) | `src/scan/` (미존재 — CMake 통합됨, 호출부 예정) |
| sigdb | 현재 미사용 — placeholder | 미정 | 미정 | adapter 없음 |

---

## 정규화 허브 — Skeleton 머지됨 (어댑터 마이그레이션 보류)

> **2026-04-30 부**: `include/third_party_hub/` (헤더 5종) 와 `src/third_party_hub/` (구현 4종) skeleton 이 머지됐다. 본 시점 hub 자체는 어떤 어댑터도 등록하지 않는다 — 실제 어댑터 마이그레이션은 별도 D-항목으로 진행한다.

새 third-party 가 추가될 때마다 `pipeline.c` 와 결과 자료형을 따로 깎는 비용을 제거하기 위해, AURA 는 **Rizin 이 정의하는 공통 자료형** (`RzCore` / `RzAnalysisOp` / `RzBinSection`) 을 mirror 하는 어댑터 허브 도입을 계획한다.

머지된 skeleton 구성:
- 헤더: `include/third_party_hub/{tp_types,tp_binary,tp_disasm,tp_layout,tp_adapter}.h`
- 구현: `src/third_party_hub/{tp_vec,tp_binary,tp_registry,tp_hub}.c`
- CMake 옵션: `-DAURA_ENABLE_RIZIN_HUB=ON` (default OFF — 활성화 시 `aura_core` 에 hub 컴파일됨)
- 테스트: `ctest -R test_tp_hub_surface` — 4 케이스 (`types` / `vec` / `registry` / `dispatch`) 통과 확인됨

어댑터 마이그레이션 후보 (도입 결정 시 순서 예시): Capstone → Zydis → Ghidra-decompile → YARA.

실제 Rizin 트리(`third_party/rizin/`) 통합 전에 LGPL-3.0 정적 링크 호환성 검토가 선행되어야 한다 (§2.2 참조).

자세한 설계: `docs/design/third_party_hub.md`.

---

## 신규 라이브러리 추가 절차

1. **사용자 승인** — `rules.md §10` 에 따라 `PRD.md §7 Open Decisions` 에 D-항목으로 기록 후 사용자 confirm.
2. **라이선스 점검** — Apache 2.0 / MIT / BSD / Public Domain / zlib 만 자동 OK. LGPL/GPL 은 정적 링크 호환성 별도 분석.
3. **벤더링 방식** — 원본 트리 크기·빌드 시스템·CI 영향 고려해서 결정 (submodule / amalgamation / system-find).
4. **CMake 통합** — 본 README 표에 row 1 개 추가 + `CMakeLists.txt` 에 add_library/add_subdirectory 등록.
5. **AURA 측 어댑터** — `include/third_party_hub/` 기반 `aura_tp_adapter_t` 로 등록 (허브 도입 전까지는 직접 wrapper 작성).
6. **README 갱신 (본 파일)** — 같은 PR 에서 표 갱신. 누락 시 PR review 차단.
7. **통합 상태 분류** — §2.1 / §2.2 / §2.3 중 정확히 한 곳에 등록한다. 상태가 섞이지 않게 한다.
8. **입출력 매트릭스 등재** — §2.1(통합됨)으로 분류된 경우 §"입출력 계층 매트릭스" 표에도 동시에 등재한다 (입력·변환 엔진·출력·어댑터 4컬럼).
