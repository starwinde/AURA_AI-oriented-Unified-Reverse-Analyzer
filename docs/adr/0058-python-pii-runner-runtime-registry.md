<!-- /autoplan restore point: C:\Users\21m15\.gstack\projects\AURA\main-autoplan-restore-20260507-162252.md -->
# ADR-0058 — Python venv PII runner and safety asset registry

- **Status**: Accepted
- **Date**: 2026-05-07
- **Related**: ADR-0054, ADR-0056, ADR-0057, PRD D-39, PRD D-42, ADR-0059
- ADR-0059 defines whether Safety UI model edits are selection edits or asset edits.

## Context

Phase 13 의 Privacy Filter 는 Rule Pack 과 Token Classification Model 의 병렬
탐지 결과를 Finding Merger 로 수렴하고, Eval Dataset 으로 Rule-only /
Model-only / Rule+Model 결과를 검증해야 한다.

이전 논의에서는 C++/ONNX runner 도 후보였지만, 현재 우선순위는 모델 검증과
통합 속도다. Python 생태계는 tokenizer, transformers, ONNX export 검증 경로가
이미 풍부하므로 초기 모델 탑재/검증에는 Python venv 기반 runner 가 더 현실적이다.

## Decision

1. Rule Pack, Eval Dataset, Token Classification Model 은 모두 runtime asset
   registry 로 관리한다.
2. 각 asset 은 `<asset-id>/manifest.json` 을 가진 디렉터리 단위다.
3. 사용자 runtime registry 는 `~/.aura/` 아래에 둔다.

   ```text
   ~/.aura/
     runners/<runner-env-id>/
     rule-packs/<pack-id>/
     eval-datasets/<dataset-id>/
     token-classification-models/<model-id>/
     safety-profiles/<profile-id>.json
   ```

4. repo 에는 작은 기본 Rule Pack, 작은 Eval Dataset, Safety Profile template,
   model manifest template 만 둔다.

   ```text
   assets/safety/
     rule-packs/
     eval-datasets/
     safety-profiles/
     token-classification-models/
   ```

5. `third_party/` 에 Rule Pack, Eval Dataset, model weight 를 두지 않는다.
6. Rule Pack v1 은 `regex + allowlisted validator` 방식이다. Rule Pack 에서
   임의 코드나 스크립트를 실행하지 않는다.
7. Eval Dataset 은 런타임 탐지기가 아니라 검증 기준 데이터다.
8. Token Classification Model Adapter v1 은 Python venv 기반 외부 CLI runner 로
   구현한다. Python 은 `aura_core` 에 embed/link 하지 않고, AURA 는 runner 를
   subprocess 로 실행해 JSON findings 만 수신한다.
9. runner protocol 은 언어 중립 JSON 으로 유지한다. 향후 C++/ONNX runner 를
   추가하더라도 AURA core 계약은 유지한다.
10. 모델 미설치, venv 누락, timeout, crash, invalid JSON 은 모델 검사 실패로
    처리한다. `default` profile 은 `degrade`, `high-security` profile 은
    `block_export` 정책을 사용한다.
11. runner 는 로컬에서만 실행한다. 원문 문자열을 외부 네트워크 API 로 보내는
    방식은 Privacy Filter 목적과 충돌하므로 금지한다.
12. PII 모델 실행은 AURA-managed Python Venv 안에서만 수행한다. v1 runner
    env id 는 `pii-python-venv`, 기본 위치는
    `~/.aura/runners/pii-python-venv/` 다. system Python 은 venv bootstrap
    후보로만 사용하며, 모델 실행 fallback 으로 직접 사용하지 않는다.
13. runner venv bootstrap 은 명시 명령으로만 수행한다. 일반 분석/export 중
    자동 venv 생성이나 package install 은 금지한다. 기본 명령은
    `aura safety bootstrap-runner --runner pii-python-venv` 이며, 네트워크 사용은
    `--allow-network` 같은 명시 옵션이 있을 때만 허용한다.
14. bootstrap 은 `tools/pii-runner/requirements.lock.txt` 를 기준으로 한다.
    lockfile 이 없으면 bootstrap 은 실패한다. `--allow-network` 가 없으면 설치를
    수행하지 않고 현재 venv 검증만 한다. lockfile 은 실제 backend dependency
    버전을 검증한 구현 slice 에서 추가하며, 검증 전 placeholder lockfile 은 두지
    않는다.
15. runner span offset 은 v1 에서 `utf8_byte` 로 고정한다. Python runner 는
    Unicode/codepoint offset 을 stdout JSON 으로 반환하지 않고 UTF-8 byte offset 으로
    변환해야 한다.
16. C++ Token Classification Model Adapter 계약은 batch scan 이다. 각 입력과
    finding 은 `text_id` 를 가져야 하며, 실패는 빈 finding 으로 뭉개지 않고
    구조화된 error result 로 반환한다.
17. `conditional.run_when` 조건 목록은 OR 로 해석한다. `required` mode 는 조건을
    보지 않고 대상 문자열에 대해 모델을 실행한다. `disabled` mode 는 모델을
    실행하지 않는다.
18. `degrade` 는 Rule Pack-only 결과로 계속 진행하되 structured warning 을 남기는
    정책이다. `block_export` 는 외부 LLM/MCP/export payload 생성을 차단하는 정책이며
    GUI 내부 표시나 로컬 분석 자체를 막지 않는다.
19. `contains_natural_language` 는 v1 에서 보수적 heuristic 으로 구현할 수 있지만
    보안 차단 근거가 아니라 모델 호출 최적화 hint 로만 사용한다.
20. raw transformers output 은 Python runner 내부의 Model Finding Normalizer 를
    거친 뒤에만 stdout 으로 나간다. C++ core 는 normalized Model Finding JSON 을
    schema/span/kind/confidence 기준으로 다시 검증한다.
21. AURA Standard Finding Kind Vocabulary v1 은 Rule Finding 과 Model Finding 이
    공유한다. v1 vocabulary 는 `email`, `phone_number`, `kr_rrn`, `api_key`,
    `token`, `url`, `ip_address`, `internal_path`, `person_name`, `address`,
    `organization`, `account_id`, `customer_id`, `unknown_sensitive` 다.
22. `max_input_chars` 를 넘는 입력은 v1 에서 silent truncate 하지 않는다. chunking 이
    구현되기 전에는 모델 검사 실패 `input_too_large` 로 처리하고 profile 정책을
    적용한다. 즉 `default` 는 Rule Pack-only + structured warning 으로 degrade 하고,
    `high-security` 는 외부 LLM/MCP/export payload 생성을 차단한다.
23. Safety model failure warning 은 기존 `AuraDiagnostics` blob 에 싣지 않는다.
    `AuraDiagnostics` 는 engine mapping-loss visibility 전용으로 유지하고, model
    failure/degrade/block_export 는 Safety Core 의 별도 `SafetyWarning`/policy result
    계층에서 표현한다. MCP 는 이를 envelope `warnings[]` 로 매핑하고, CLI/GUI 는
    같은 warning 을 사용자-facing status 로 렌더링한다.
24. CLI/bootstrap/error UX 는 문제, 원인, 다음 행동을 모두 포함해야 한다. 예:
    `runner_env_invalid` 는 어떤 runner env 가 실패했는지, 왜 실패했는지, 사용자가
    실행할 복구 명령(`aura safety bootstrap-runner --runner pii-python-venv`)을 함께
    제공한다. 실패 중 자동 package install 은 하지 않는다.

## Runner protocol v1

입력은 JSON request file 이고 출력은 stdout JSON 이다. `offset_unit` 은 v1 에서
`utf8_byte` 만 허용한다.

```json
{
  "schema_version": 1,
  "request_id": "scan-001",
  "offset_unit": "utf8_byte",
  "locale": "ko-KR",
  "texts": [
    {"text_id": "str-1", "text": "문의: hong@example.com"}
  ]
}
```

성공 출력:

```json
{
  "schema_version": 1,
  "status": "ok",
  "request_id": "scan-001",
  "offset_unit": "utf8_byte",
  "findings": [
    {
      "text_id": "str-1",
      "kind": "email",
      "start": 8,
      "end": 24,
      "confidence": 0.98,
      "detector_id": "model/openai-privacy-filter"
    }
  ]
}
```

Runner stdout 는 normalized Model Finding 만 담는다. backend raw entity, debug log,
package warning 은 stdout 에 쓰지 않는다. 필요하면 stderr 또는 diagnostics 로만 남긴다.

실패 출력:

```json
{
  "schema_version": 1,
  "status": "error",
  "request_id": "scan-001",
  "error_code": "model_timeout",
  "message": "model did not respond before timeout"
}
```

대표 `error_code` 는 `runner_unavailable`, `runner_env_invalid`,
`model_unavailable`, `model_timeout`, `runner_failed`, `invalid_runner_output`,
`invalid_model_manifest`, `input_too_large` 다.

runner 가 request 를 parse 한 뒤 실패한 경우 error 출력은 `request_id` 를 포함해야
한다. request 자체를 parse 할 수 없는 경우에만 `request_id` 를 생략할 수 있다.
runner 내부의 세부 실패(`io_error`, `invalid_json`, `invalid_request`,
`unsupported_backend` 등)는 C++ policy boundary 전에 위 canonical vocabulary 로
매핑한다. profile policy 는 runner 내부 문자열이 아니라 canonical `error_code` 에만
의존한다.

## Model manifest v1

Token Classification Model asset 은 `<model-id>/manifest.json` 을 가진다.
필수 필드는 다음과 같다.

- `schema_version`
- `model_id`
- `runner`
- `runner_env_id`
- `backend`
- `model_path`
- `tokenizer_path`
- `offset_unit`
- `normalizer.kind_map`
- `normalizer.default_threshold`

선택 필드는 `entrypoint`, `requirements_file`, `aggregation_strategy`,
`normalizer.thresholds`, `normalizer.unknown_label_action`, `max_batch_size`,
`device`, `local_files_only` 이다.

```json
{
  "schema_version": 1,
  "model_id": "openai-privacy-filter",
  "runner": "python_venv",
  "runner_env_id": "pii-python-venv",
  "backend": "transformers_token_classification",
  "entrypoint": "tools/pii-runner/aura_pii_runner.py",
  "requirements_file": "tools/pii-runner/requirements.lock.txt",
  "model_path": ".",
  "tokenizer_path": ".",
  "offset_unit": "utf8_byte",
  "aggregation_strategy": "simple",
  "max_batch_size": 16,
  "device": "auto",
  "local_files_only": true,
  "normalizer": {
    "kind_map": {
      "EMAIL": "email",
      "B-EMAIL": "email",
      "I-EMAIL": "email",
      "PHONE": "phone_number",
      "PER": "person_name",
      "PERSON": "person_name"
    },
    "default_threshold": 0.75,
    "thresholds": {
      "email": 0.80,
      "person_name": 0.85
    },
    "unknown_label_action": "drop"
  }
}
```

`backend=transformers_token_classification` 은 Hugging Face
`pipeline("token-classification")` 기반 runner 를 뜻한다. v1 기본은
`local_files_only=true` 이며, 실행 중 모델 가중치나 tokenizer 를 네트워크에서
다운로드하지 않는다.

## Adapter and policy contract

C++ adapter 는 batch scan 계약을 사용한다.

```cpp
struct ModelScanInput {
    std::string text_id;
    std::string text;
    std::string locale;
};

struct ModelScanRequest {
    std::string request_id;
    std::vector<ModelScanInput> texts;
    std::size_t max_input_chars = 4096;
};

struct ModelScanResult {
    bool ok = false;
    std::string error_code;
    std::string message;
    std::vector<Finding> findings;
};
```

`Finding` 은 batch 결과를 보존하기 위해 `text_id` 를 가져야 한다. C++ core 는
runner output 을 신뢰하지 않고 다음을 검증한다.

- `schema_version == 1`
- `offset_unit == "utf8_byte"`
- finding `text_id` 가 요청에 존재
- `start < end`
- `end <= original_text.size()`
- `kind` 가 Standard Finding Kind Vocabulary v1 에 있음
- `confidence` 가 `0.0 <= confidence <= 1.0`
- finding count 가 정책 cap 을 넘지 않음

입력 text 가 `max_input_chars` 를 넘으면 v1 adapter 는 runner 호출 전에
`input_too_large` error result 를 반환한다. v1 은 silent truncate 를 금지한다.
향후 chunking 을 추가할 경우 chunk base offset 을 보존해 `utf8_byte` span 이
원본 문자열 기준으로 유지되어야 한다.

`conditional.run_when` 은 OR 이다. `external_export` 는 MCP/LLM/export 경로에서
true, `rule_findings_empty` 는 Rule Pack 결과가 0개일 때 true,
`contains_natural_language` 는 주소/레지스터/hex/path-only noise 가 아닌 자연어성
문자열에 대한 최적화 hint 다. `external_export` 가 true 이면
`contains_natural_language=false` 라도 모델 실행 조건은 충족한다.

## Safety warning contract

`degrade` 와 `block_export` 는 finding 이 아니라 policy 결과다. 따라서 C++ Safety
Core 는 model scan 실패를 Rule Finding 으로 합성하지 않고, 별도 warning/policy
result 로 반환한다.

```json
{
  "warning_code": "model_timeout",
  "severity": "warning",
  "scope": "external_export",
  "model_id": "openai-privacy-filter",
  "action": "degrade",
  "export_blocked": false,
  "message": "Token classification model timed out; export used Rule Pack-only protection.",
  "remediation": "Run aura safety bootstrap-runner --runner pii-python-venv or switch to high-security profile for fail-closed export."
}
```

정책:

- `default` profile 의 `degrade` 는 export 를 계속하되 warning 을 남긴다.
- `high-security` profile 의 `block_export` 는 외부 LLM/MCP/export payload 생성을
  막고 error/status 로 노출한다.
- MCP 는 ADR-0057 의 envelope `warnings[]` 에 같은 warning 을 넣는다.
- CLI 는 stderr 또는 structured JSON 출력의 `warnings[]` 로 노출한다.
- GUI 는 원문 노출 없이 Safety 상태 badge/status row 로 노출한다.
- `AuraDiagnostics` 는 engine mapping-loss 전용으로 유지하며 Safety warning 과
  섞지 않는다.

대표 warning/error code 는 runner protocol `error_code` 와 같은 vocabulary 를
사용한다. UI 문구는 항상 problem/cause/fix 를 포함해야 하며, fix 가 없는 내부
오류도 "export blocked" 또는 "Rule Pack-only export" 처럼 사용자가 보는 결과를
명시해야 한다.

## Consequences

- 모델 검증과 한국어 PII 실험을 Python 생태계로 빠르게 진행할 수 있다.
- AURA core 는 Python, transformers, ONNX Runtime 에 직접 의존하지 않는다.
- Rule Pack + Model 병렬 탐지 방향은 유지된다.
- Eval Dataset 은 운영 필터가 아니라 성능/회귀 검증 기준으로 고정된다.
- 최종 배포에서 Python 의존성을 줄이고 싶으면 같은 JSON protocol 을 구현하는
  C++/ONNX runner 를 추가할 수 있다.
- 모델 자산과 runner 실행환경을 분리하므로 여러 model asset 이 같은
  `pii-python-venv` 를 재사용할 수 있다.

## AUTOPLAN REVIEW REPORT

### Scope

- CEO mode: SELECTIVE EXPANSION, but accepted changes stayed inside Phase 13.6.
- Design scope: no new screen/mockup. Safety status, warning, block/export UX only.
- Eng scope: runner protocol, manifest validation, C++ adapter boundary, policy result,
  and tests.
- DX scope: CLI/bootstrap/error message flow, MCP warning mapping, developer recovery.

### What Already Exists

- `include/aura/diagnostics.h` / `src/core/diagnostics.c`: engine mapping-loss
  diagnostics. Reused as a boundary reference, not as Safety warning storage.
- ADR-0057 MCP envelope: target mapping for Safety warnings into `warnings[]`.
- `include/aura/safety/string_safety.h`: current safety MVP API; planned replacement
  point for batch model scan and policy result.
- `tools/pii-runner/aura_pii_runner.py`: legacy dummy runner smoke path; not v1-complete.

### Decision Audit Trail

| # | Phase | Decision | Classification | Principle | Rationale | Rejected |
|---|-------|----------|----------------|-----------|-----------|----------|
| 1 | CEO/Eng | Keep Python venv runner as v1, not final architecture | Mechanical | Pragmatic | It speeds model validation while preserving JSON runner boundary for later C++/ONNX runner. | Embed/link Python into `aura_core` |
| 2 | Eng | Separate Safety warnings from `AuraDiagnostics` | Mechanical | Explicit over clever | Engine mapping-loss diagnostics and privacy policy warnings have different consumers and semantics. | Reuse `AuraDiagnostics` for model failure |
| 3 | Eng/DX | Require problem/cause/fix in bootstrap and runner error UX | Mechanical | Choose completeness | Developers need the exact recovery command when runner env or lockfile validation fails. | Generic failure text |
| 4 | Eng | Preserve `request_id` in parsed runner errors | Mechanical | Explicit over clever | Batch failures must be correlated to the original scan request. | Error output without request correlation |
| 5 | Eng | Map runner internal errors to canonical policy `error_code` | Mechanical | DRY | Profile policy should not depend on Python runner implementation strings. | Let C++ branch on raw runner codes |
| 6 | Eng | Correct ADR UTF-8 byte offset example to `8..24` | Mechanical | Choose completeness | Korean prefix `문의: ` is 8 UTF-8 bytes; `4..20` was codepoint offset. | Keep legacy dummy offset in v1 example |

### Error And Rescue Registry

| Error | User-visible outcome | Rescue |
|-------|----------------------|--------|
| `runner_env_invalid` | Model scan unavailable; default degrades, high-security blocks export | Run `aura safety bootstrap-runner --runner pii-python-venv` |
| `model_timeout` | Rule Pack-only export with warning or blocked high-security export | Increase timeout only via profile, or fix runner/model env |
| `invalid_runner_output` | Runner output ignored; policy path decides export | Inspect runner stderr/log, keep stdout normalized JSON-only |
| `invalid_model_manifest` | Model asset rejected before scan | Fix manifest v1 required fields and normalizer mapping |
| `input_too_large` | No silent truncation; default warning or high-security block | Add future chunking or reduce export scope |

### Failure Modes Registry

| Failure mode | Severity | Plan status |
|--------------|----------|-------------|
| UTF-8 byte span drift on Korean strings | Critical | ADR example corrected; runner/test gate remains in 13.6a |
| Real manifest silently using dummy runner | Critical | 13.6a/13.6b require `mode` to `backend` migration and manifest validation |
| Model failure represented as empty findings | Critical | Batch `ModelScanResult` and Safety warning/policy result required |
| Safety warning mixed into engine diagnostics | High | Explicitly rejected; separate warning contract added |
| Over-limit input silently truncated | High | `input_too_large` fail path added |
| Error code vocabulary drift | Medium | Canonical mapping requirement added |

### Review Scores

| Review | Result |
|--------|--------|
| CEO | Clear with HOLD/SELECTIVE scope discipline; no expansion outside Phase 13.6 accepted |
| Design | 7/10 for Safety Interaction UX after adding warning contract; no visual mockup needed |
| Eng | 8/10 after adding request/error/warning/test gates; implementation still pending |
| DX | 7/10 after problem/cause/fix requirement; concrete CLI examples still pending implementation |

### Test Plan Artifact

Detailed test plan:
`C:\Users\21m15\.gstack\projects\AURA\main-test-plan-20260507-163134.md`

### Not In Scope

- Actual transformers model dependency lockfile. It is added only after backend
  dependency versions are verified.
- Python runner implementation beyond design/test gates.
- GUI mockup or new Safety tab. Existing GUI/CLI/MCP surfaces consume the same Safety
  warning contract.
- Chunking over `max_input_chars`; v1 fail path is `input_too_large`.
