# AURA Rules — AI 행동 지침

> 본 문서는 [PRD.md](./PRD.md), [AUTOMATION_ROADMAP.md](./AUTOMATION_ROADMAP.md),
> [Tasks.md](./Tasks.md) 와 함께 읽는다.
> 권위 계층은 §11 을 따른다.

---

## 1. 코드 작성

- **언어 (2026-05-02 갱신)**: AURA core / UI / CLI 는 C (C11) / C++ (C++17). **외부 도구 (서드파티 엔진) 의 런타임은 그 도구가 요구하는 것을 그대로 사용** — Ghidra 처럼 JVM 이 필요하면 호스트에 JVM 설치를 가정한다. **호스트에 런타임이 없을 경우** 해당 기능은 "사용 불가" 로 표기하고 *이유 + 요구 런타임 + 설치 안내* 를 노출해야 한다 (silent disable 금지). AURA 코어 로직 자체를 인터프리터 언어로 작성하는 것은 여전히 금지.
- **지원 플랫폼 (2026-05-03 갱신, ADR-0030)**: AURA 는 **Tier 1** 환경으로 **Linux WSL (Ubuntu 24.04)** + **Windows MSVC (latest stable)** 양립 지원. 매 PR 양 환경에서 빌드 + ctest GREEN 의무. **macOS** 는 Tier 3 (best-effort, unverified) — Mac 하드웨어/CI 확보 후 승급 예정. 신규 코드는 portable 작성 (`#ifdef _MSC_VER` / POSIX 분기 일관). 플랫폼 의존 함수는 `include/aura_compat.h` 또는 `include/aura/aura_io.h` 의 shim 경유.
- **들여쓰기**: 공백 4칸. 인코딩 UTF-8, 줄 끝 LF, 최대 120자.
- **네이밍**: 함수 `snake_case`, 타입 `PascalCase`, 상수 `UPPER_SNAKE_CASE`, 전역 `g_snake_case`, 파일 `snake_case.{c,h,cpp}`.
- **에러 처리**: 모든 실패 가능 함수는 반환값으로 실패를 알린다. NULL / 음수 에러 코드 일관 사용. `exit()` / `abort()` 는 초기화 실패 외 금지.
- **메모리**: `malloc` ↔ `free` 쌍 보장. 모듈마다 `_init()` / `_destroy()` 제공. `free` 후 `NULL` 초기화.
- **외부 명령 호출 cross-platform 가드 (2026-05-05 추가, Codex review 반영)**: AURA 는 외부 RE 도구 오케스트레이터 (CLAUDE.md §원칙 1) 이므로 subprocess spawn 코드가 핵심 경로다. 다음 패턴 의무 — Tier 1 양 OS (Linux WSL + Windows MSVC) 동등 동작 보장.
  - **명령 이름 OS 차이 표 (도입 시점에 조사·갱신)**:
    | 도구 | Linux/macOS | Windows |
    |------|------------|---------|
    | Python 3 | `python3` | `python` (또는 `python.exe`) |
    | Java JRE | `java` | `java` (보통 동일) |
    | 셸 | `sh` / `bash` | `cmd.exe` / `powershell.exe` |
    | 패키지 매니저 | `apt` / `dnf` / `brew` | `winget` / `choco` |
    | 줄바꿈 | LF (`\n`) | CRLF (`\r\n`) — 파일 I/O 는 binary mode 명시 |
    | 홈 디렉토리 env | `HOME` | `USERPROFILE` — `aura_io.h` shim 경유 |
    | 경로 구분자 | `/` | `\` 또는 `/` 둘 다 인식 — 코드에서는 `/` 사용 |
  - **Fallback chain 패턴** (OS 별로 이름이 다른 명령):
    ```c
    #ifdef _WIN32
    static const char *python_candidates[] = {"python", "python3", NULL};
    #else
    static const char *python_candidates[] = {"python3", "python", NULL};
    #endif
    for (int i = 0; python_candidates[i]; ++i) {
        if (try_spawn(python_candidates[i]) == 0) break;
    }
    ```
  - **install_hint ↔ probe 명령 자기-일관성 강제**: 특정 OS 의 `install_hint` 가 안내하는 명령 이름과 동일 OS 에서 probe 가 spawn 시도하는 명령 이름이 **일치해야 한다**. 일치 안 하면 사용자가 안내대로 설치해도 probe 가 못 찾는 자기 모순 버그 발생. 테스트로 가드 — `install_hint` 토큰과 probe `argv[0]` 의 OS 별 매칭 검증.
  - **Windows 빌드 검증 의무**: 외부 명령 호출 코드를 추가/변경하면 `AURA_ENABLE_RIZIN=ON` + Windows MSVC 빌드 + 해당 코드를 실행하는 테스트가 GREEN 임을 PR 머지 전 확인. CI 에서 자동화 안 됐다면 로컬 검증 결과를 PR 본문에 명시.
  - **금지**: hardcoded `python3` / `bash` / POSIX-only env var 직접 호출 + Windows 분기 부재. `#ifdef _WIN32` 없이 OS 별 동작이 다른 코드는 ingestion reject.

---

## 2. 엔진 / 아키텍처 규칙

본 규칙은 PRD §1 (정체성) + §7 (디자인 원칙) 의 직접 강제판이다.

| 규칙 | 내용 |
|------|------|
| R-1 | **엔진 자체 구현 금지** — 디컴파일러 / 디스어셈블러 / 타입 추론 / 아키텍처별 명령어 해석은 외부 엔진 사용 (**Rizin primary 4 종 + Ghidra decompile co-primary**, RetDec / Capstone secondary). **부분 구현 금지** (일부 함수만 자체 처리도 불가). **간단한 분석 로직 금지** (간이 CFG / 타입 후처리 / branch 해석 포함). **엔진 결과 보정 금지** (오탐 패치, fallback 합성, "정정" 모두 위반). |
| R-2 | **Stateless subprocess** — 모든 엔진은 외부 프로세스. 상태는 AURA 가 보관. |
| R-3 | **Adapter 격리** — 엔진별 코드는 `src/adapter/<engine>/` 에만 존재. Orchestrator / Unified IR 코드는 엔진 무관. |
| R-4 | **Output non-discard** — 엔진 출력은 모두 Unified IR 로 저장. 일부 폐기 / 임의 변형 금지. |
| R-5 | **Override 불변성** — 사용자 수정은 override layer 에만 누적. 엔진 출력 자체를 수정하지 않는다. |
| R-6 | **UI ↛ Engine 직통 금지** — UI 는 Orchestrator API 만 호출. 엔진 spawn 은 Orchestrator 책임. |
| R-7 | **Engine Request 표준화** — 모든 엔진 호출은 다음 request type 중 하나로만 수행한다: `disasm`, `analyze`, `decompile`, `trace` (optional), `symbolic` (D-34). `symbolic` 은 angr 외부 runner 결과 요청 타입이며 AURA 내부 symbolic execution 구현을 뜻하지 않는다. 각 adapter 는 위 request type 을 그대로 구현해야 하며, 임의의 새 request type 정의 / 변형 / 별칭 금지. |
| R-8 | **Type-별 Primary 집합** — 엔진 primary 권한은 request type 마다 별도 집합으로 정의된다. `disasm` primary = `{rizin}`, `analyze` primary = `{rizin}`, `decompile` primary = `{rizin, ghidra}` (동률, 사용자 선택), `trace` primary = `{rizin}`, `symbolic` primary = `{angr}`. secondary engine (RetDec / Capstone 등) 은 어떤 type 에서도 primary 집합을 덮어쓰거나 대체하지 못한다. Secondary 결과는 비교 / 보조 / cross-check 용도로만 사용한다. Primary 누락 시 결과 자체가 누락이며, secondary 로 채우지 않는다. decompile co-primary 동률 시 사용자 default (D-28) 또는 명시 engine_id 로 선택한다. `symbolic` 은 secondary/fallback 없이 angr 결과만 사용한다. |
| R-9 | **파생 분석 금지** — AURA 내부에서 CFG / IR / 타입 / 데이터 흐름 / 호출 그래프 / 함수 경계 등을 새로 생성하는 로직 금지. 모든 분석 정보는 외부 엔진 결과에서만 유래해야 한다. AURA 가 하는 일은 **수집·정렬·표시·override 누적** 뿐이다. |
| R-10 | **Engine canonical type AURA core leak 금지** — 엔진 adapter 의 raw / canonical 자료형 (`RzCore *`, `RzAnalysisFunction *`, Ghidra `<function>` XML, RetDec LLVM IR 등) 이 `src/core/`, `include/` (단, `include/third_party_hub/` 내부 mirror 는 예외), Unified IR, GUI 코드에 직접 등장 금지. 엔진 헤더 직접 include 금지. third_party_hub 정규화 허브 통과 후 AURA normalized record (R-12) 만 core 로 전달한다. **Rizin 의 경우 librz 정적/동적 링크 자체 금지** (D-27) — 별도 프로세스 stdout JSON 만 허용. |
| R-11 | **Snapshot Provenance 강제** — adapter 출력은 (a) immutable raw snapshot + (b) normalized snapshot 의 2-layer 구조다. normalized snapshot 의 모든 record (function/block/edge/symbol/type/variable/xref/call_edge/type_fact) 는 `{source: engine_id, confidence: 0..1, completeness: 0..1}` provenance 메타 필수. record 단위로 부착 (개별 필드 단위 아님). 누락 시 ingestion reject. |
| R-12 | **Normalized Record 1 급화** — 엔진 결과를 `FunctionRecord` 부속 필드 (e.g. `function.types[]`, `function.calls[]`, `function.variables[]`) 로 뭉개기 금지. 다음을 독립 record 로 분해한다: `FunctionRecord`, `BlockRecord`, `EdgeRecord`, `VariableRecord`, `TypeFactRecord`, `CallEdgeRecord`, `SymbolRecord`, `XrefRecord`. 각 record 는 자신의 provenance (R-11) 를 가진다. record 간 관계는 안정 ID 참조 (`function_id` / `block_id` / `var_id` / `addr` 등) 로 표현한다. 깊은 타입 전파·call graph 분석을 가능케 하는 구조 조건이며, 위반 시 ingestion reject. |

> **Capstone 역할 명시** — Capstone 은 **disasm secondary** 어댑터다 (disasm primary 는 Rizin). Decompile / analyze 비교 대상이 아니며, primary 의 decompile 결과를 Capstone 으로 cross-check 하거나 보정하지 않는다 (R-8 + R-9 의 자연 따름). Decompile 의 secondary 후보는 Rizin co-primary 외에 RetDec 이며 Capstone 이 아니다.

> **Rizin 실행 기준 (ADR-0052)** — 현재 approved baseline 은 **Rizin 0.8.0 shared64 + rz-ghidra 0.8.0** 이다. 코드/테스트/문서의 기본 vendored path 는 `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/...` 를 기준으로 한다. CLI/GUI 는 `SLEIGHHOME` 이 비어 있고 vendored `rz_ghidra_sleigh` 가 존재하면 해당 경로를 자동 설정한다. 0.8.2 계열은 신규 decompile 시연/테스트 기준으로 사용하지 않는다.

> **보안 제품 경고 처리 (ADR-0052)** — Windows Defender / SmartScreen / EDR 이 AURA, Rizin, rz-ghidra 를 cyber security risk 로 표시할 수 있다. 이는 RE 도구가 외부 analyzer, plugin DLL, 임의 바이너리 분석을 수행하기 때문에 예상 가능한 경고다. 코드에서 경고를 우회하거나 비활성화하지 않는다. 허용되는 대응은 출처/버전/경로/해시 문서화, 로컬 분석 원칙, LLM 자동 전송 없음 명시, 사용자의 로컬 보안 정책 기반 allow-list 뿐이다.

---

## 3. 디렉토리 구조

```
src/
  ├─ core/              # Orchestrator, Unified IR, Override Layer
  ├─ adapter/
  │   ├─ rizin/         # Rizin subprocess + bulk JSON (Phase 2 complete — analyze + decompile primary)
  │   ├─ ghidra/        # Ghidra subprocess + XML 파싱 (decompile co-primary)
  │   ├─ retdec/        # (Phase 6+, decompile secondary)
  │   └─ capstone/      # (Phase 6+, disasm secondary / fallback)
  ├─ third_party_hub/   # 정규화 허브 — Rizin canonical mirror 격리 + AURA normalized record 변환 (R-10/R-11/R-12)
  ├─ gui/               # Qt6 UI (core 만 import — engine canonical 미접촉)
  └─ llm/               # LLM HTTP 클라이언트 (옵션, 기본 구조 = 1 LLM + policy gateway)

include/                # 공개 헤더
tests/                  # ctest 등록 단위
third_party/            # 외부 라이브러리 (Ghidra vendor 포함)
docs/design/            # 살아있는 설계 문서
legacy/                 # v2.x 격리 (참조용, 빌드 영향 없음)
```

- `gui/` 는 `core/` 를 import 가능. 역방향 금지.
- 새 엔진 어댑터는 `src/adapter/<engine>/` 에 신규 디렉토리로 시작.
- LLM 보안 경계는 두 번째 생성형 LLM 모델이 아니라 Privacy Filter &
  Policy Gateway 로 둔다. 기본 제품 구조에서 2개 생성형 LLM 상시 배치는
  금지한다. Privacy Filter 는 문자열 기반 MVP 에서 시작하고, 목표 구조는
  PII 특화 모델과 데이터셋 기반 탐지를 결합한 민감정보 마스킹 시스템이다.

---

## 4. 작업 흐름

- 한 번에 하나의 Phase 항목에 집중. `[ ]` → `[-]` (구현 중) → `[x]` (완료).
- 작은 단위 PR / 단일 책임 / git history 깔끔.
- TDD 권장 (강제 X). 외부 엔진 wire 변경마다 통합 테스트 1 건 이상.
- 새 동작에는 대응 테스트가 있어야 한다. 문서/설정만 변경은 면제.

---

## 5. 멈춤 조건

다음 상황에서는 즉시 작업을 중단하고 사용자 확인을 요청한다.

| 상황 | 예시 |
|------|------|
| 새 외부 의존성 도입 시도 | 새 라이브러리, 새 엔진 어댑터 후보, 새 빌드 도구 |
| PRD 정체성 위반 의심 | 디컴파일러/디스어셈블러/타입 추론 자체 구현 유혹, 엔진 출력 임의 변형 |
| 엔진 결과 폐기 의심 | Ghidra 출력의 일부를 "정정" 하는 코드 |
| Override 불변성 위반 | 엔진 원본을 수정해 결과를 바꾸는 코드 |
| Phase 의존성 충돌 | 선행 Phase 완료 전에 후행 Phase 항목 요청 |
| 파괴적 변경 | 대규모 재작성, 기존 어댑터 삭제 |
| request type 위반 (R-7) | adapter 가 `disasm`/`analyze`/`decompile`/`trace` 외의 request type 을 정의 / 별칭 / 합성 |
| primary/secondary 혼용 (R-8) | type 별 primary 집합을 벗어나는 사용 — `disasm`/`analyze`/`trace` 에 Ghidra 결과를 primary 로 사용, RetDec/Capstone 으로 primary 결과 덮어쓰기, secondary 로 primary 누락분 메우기 |
| 파생 분석 시도 (R-9) | CFG / HIR / Type / call graph / 함수 경계 등을 AURA 내부에서 새로 생성, 엔진 결과 위에 자체 패스 추가 |
| Engine canonical leak (R-10) | `RzCore *` / `RzAnalysisFunction *` / Ghidra `<function>` XML 등이 `src/core/` 또는 GUI 에 직접 등장, 엔진 헤더 직접 include, librz 링크 |
| Provenance 누락 (R-11) | normalized record 가 `{source, confidence, completeness}` 메타 없이 ingestion |
| Record 평탄화 (R-12) | `FunctionRecord.types[]` / `.calls[]` / `.variables[]` 같이 함수에 부속 정보 뭉개기. 1 급 record 분해 미준수 |
| OS 명령 이름 가정 위반 (§1) | `python3` 만 spawn 시도, Windows fallback 없음. `install_hint` 가 안내한 명령과 probe 가 실제 시도하는 명령이 같은 OS 에서 불일치 (예: install_hint=`winget install Python.Python.3.12` 로 `python.exe` 설치되지만 probe 는 `python3` 만 spawn). hardcoded POSIX-only 명령/env 직접 호출 |

---

## 6. 커밋 / PR

- 커밋 메시지: `<type>(<scope>): <subject>` 형식 권장 (`feat`, `fix`, `refactor`, `test`, `docs`, `build`, `chore`).
- main 머지는 항상 PR 기반. 직접 push 금지.
- 사용자 승인 없이 PR 생성 / 머지 금지.
- 새 의존성 추가는 PRD §5 표 갱신 + PRD §9 신규 D 결정 등재 후 승인.

### 6.1. Codex adversarial review 워크플로 (2026-05-05 Phase 2.5 closeout 정착)

대규모 closeout / production-critical 코드 (subprocess runner, IPC layer, lookup contract 등) 머지 전 다음 패턴 적용:

- **검토는 슬래시 커맨드만**: `/codex:adversarial-review` 또는 `/codex:review` 사용. 코드 수정/조사는 `codex:codex-rescue` 별도. 두 역할 섞지 말 것.
- **Round 패턴**: review → fix → review 반복. 각 round 별 모든 HIGH finding 닫힐 때까지 진행 (MEDIUM 은 별도 결정).
  - **Round 종료 기준**: Codex verdict = `approve` (HIGH 0건). MEDIUM 잔여는 별도 backlog.
  - **HIGH 가 reachable 한지 의심 시 재검토 round** (Codex 자체 false alarm 가능성 — 환경 제약, partial code 읽기 등).
- **참고 사례**: Phase 2.5.1 + 2.5.2 = 5-round cycle 로 9 HIGH finding 모두 닫힘 (review #2~#6, 최종 APPROVE).
- **결정 trail 의무**: 각 round 의 fix commit 메시지에 `Codex review #N` 인용. 영향 큰 결정은 ADR 작성 (R-rule 변경 / 새 production 인터페이스 / phase 번호 재배정 등).
- **머지 후 doc sync 의무**: ADR / PRD §9 (D-N) / Tasks.md / ROADMAP / Plan 4-way 일관성 확보 후 세션 종료.

---

## 7. 금지 사항

- 엔진 자체 구현 (R-1) — 부분 구현 / 간단 분석 / 결과 보정 포함
- 엔진 출력 임의 변형 / 폐기 (R-4)
- 표준 외 request type 정의 (R-7)
- type 별 primary 집합 위반 — `disasm`/`analyze`/`trace` primary 자리에 Rizin 외 엔진을 primary 로 둠, secondary 가 primary 결과 덮어쓰기 / 누락 보충 (R-8)
- AURA 내부 파생 분석 (CFG / IR / Type / call graph / 함수 경계 자체 생성) (R-9)
- Engine canonical 자료형 / 헤더의 AURA core / GUI leak, librz 링크 (R-10)
- Provenance 메타 없는 normalized record 생성 (R-11)
- `FunctionRecord` 부속 필드로 type / call / variable 뭉개기 — 1 급 record 분해 위반 (R-12)
- AURA 코어 로직을 인터프리터 언어로 작성 (§1) — 외부 도구의 자체 런타임은 해당하지 않음
- 외부 도구 런타임 부재 시 "사용 불가" 표기 + 이유 + 설치 안내 누락 (§1, 2026-05-02)
- 외부 명령 호출 시 OS 별 이름 차이 미고려 (§1, 2026-05-05) — Tier 1 양 OS (Linux WSL + Windows MSVC) 동작 보장 의무. `install_hint` 와 probe 명령의 OS-별 자기-일관성 불일치도 위반.
- 사용자 승인 없는 새 의존성 도입 (§6)
- 사용자 승인 없는 PR 머지 / 직접 push (§6)
- `[ ]` → `[x]` 직접 전환 (DoD 미충족 상태에서)
- 멈춤 조건 도달 시 임의 진행 (§5)

---

## 8. 거버넌스

- 본 규칙이 코드 결정과 충돌하면 §11 문서 계층을 따른다.
- v2.x 의 거버넌스 (TDD 강제 hook, phase-rule, acceptance-rule, arch-rule) 는 본 pivot 에서 슬림화됨. 핵심은 R-1~R-12 + §5 멈춤 조건.
- 본 규칙 자체의 변경은 사용자 명시 승인 후 본 파일 직접 편집.

---

## 9. Request Type 변경 게이트

현재 표준 request type 은 `disasm` / `analyze` / `decompile` / `trace` / `symbolic` 이다 (R-7).
새 request type 은 곧바로 구현할 수 없으며, 아래 절차를 모두 거친 뒤 착수한다.

- PRD §9 에 신규 D 결정 추가 또는 기존 D 결정 개정.
- rules.md R-7 / R-8 갱신: 새 request type 이름, primary 집합, secondary/fallback 금지 범위 명시.
- `include/engine_request.h` enum / mask / manifest validation 갱신.
- Tasks.md / AUTOMATION_ROADMAP.md 에 의존성 및 DoD 반영.
- 사용자 명시 승인.

예: Phase 7.1 의 angr `symbolic` 은 D-34 로 정책 승인되었다. 다만 실제 코드 계약
(`include/engine_request.h` enum / mask / manifest validation) 은 Phase 7.1 구현에서 갱신해야 한다.

---

## 10. 새 의존성 / 외부 도구 승인

새 라이브러리, 새 엔진 어댑터, 새 빌드 도구, 새 런타임 요구사항은 사용자 승인 전 도입하지 않는다.

- PRD §5 의존성 표 갱신.
- PRD §9 신규 D 결정 또는 기존 결정 갱신.
- 라이선스 / 배포 의무 / Tier 1 동작 방식 기록.
- probe / install_hint / env override 가 필요한 경우 rules.md §1 의 자기-일관성 테스트를 추가.
- Tasks.md / AUTOMATION_ROADMAP.md 에 phase 의존성 반영.

---

## 11. 문서 계층

### 11.1 Live canonical

`AUTOMATION_ROADMAP.md` 는 현재 진행 중인 phase/step, 다음 세션 진입점, 핸드오프 로그의
live canonical 이다. Tasks.md 와 진행 상태가 충돌하면 ROADMAP 의 현재 상태를 우선한다.

### 11.2 Release snapshot

`Tasks.md` 는 릴리스 경계와 phase별 DoD 상태를 보존하는 release snapshot 이다.
세부 진행 상황은 ROADMAP 이 우선하지만, phase 정의와 완료 범위는 Tasks.md 에 남긴다.

### 11.3 제품/규칙 권위

- 제품 정체성, 범위, 외부 의존성, Open Decision 은 `PRD.md` 가 최우선이다.
- AI 행동 규칙, 금지 사항, 멈춤 조건, 코드 작성 규칙은 `rules.md` 가 최우선이다.
- 라이브 진행 상태는 `AUTOMATION_ROADMAP.md` 가 `Tasks.md` 보다 우선한다.
- 오래된 agent 컨텍스트(`CLAUDE.md`) 또는 메모리는 위 세 문서와 충돌하면 갱신 대상이다.
