# ADR-0054 — Safety filter runtime assets and registries

- **Status**: Accepted
- **Date**: 2026-05-07
- **Related**: ADR-0037, ADR-0038, ADR-0053, PRD D-39, PRD D-41

## Context

AURA Phase 13 는 외부 LLM/MCP 경로로 문자열 분석 데이터를 전달하기 전에
민감정보를 탐지하고 마스킹해야 한다. 지금까지 방향은 "PII 특화 모델과
데이터셋 기반 탐지"였지만, `model` 이라는 단어만 쓰면 생성형 LLM, 전처리
모델, token classification 모델이 섞여 설명된다.

또한 `openai/privacy-filter` 같은 모델 가중치와 평가 데이터셋은 크고 교체
가능한 런타임 자산이다. Rizin/rz-ghidra 같은 외부 RE 엔진/플러그인과 달리
repository 의 `third_party/` 에 직접 넣으면 저장소 용량, 배포 라이선스, 업데이트
정책이 불명확해진다.

## Decision

1. AURA 는 민감 문자열 탐지용 모델을 **Token Classification Model** 이라고 부른다.
   기본 후보는 `openai/privacy-filter` 이며, 생성형 LLM 으로 설명하지 않는다.
2. 기본 런타임 자산 위치는 사용자 홈 아래 `~/.aura/` 이다.

   ```text
   ~/.aura/
     token-classification-models/
       openai-privacy-filter/
     rule-packs/
       korean-sensitive/
       secret-api-key/
     eval-datasets/
       safety-default/
       korean-sensitive/
     safety-profiles/
       default.json
   ```

3. Repository 에는 작은 기본 Rule Pack, 작은 Eval Dataset, Safety Profile
   template, manifest/download 문서만 둔다. 큰 model weight 는 Git 에 넣지 않는다.
4. `third_party/` 는 외부 RE 엔진, 플러그인, SDK 처럼 빌드/실행에 직접 연결되는
   소프트웨어 구성 요소에 사용한다. Token Classification Model 과 Eval Dataset 은
   `third_party/` 가 아니라 runtime asset registry 로 관리한다.
5. Safety Profile 은 다음을 함께 고른다.
   - Token Classification Model
   - Rule Pack 목록
   - Eval Dataset 목록
   - Masking policy (`label_numbered`, same-value-same-mask 등)
6. Safety Profile 은 탐지 로직, 모델, rule pack, dataset 자체가 아니라
   **configuration** 이다. Safety Profile Loader 는 JSON schema 를 검증하고
   runtime asset 경로를 resolve 한 뒤 선택 목록을 반환한다. 탐지/마스킹 실행은
   Rule Pack Engine, Token Classification Adapter, Mask Token Allocator 의 책임이다.
7. Rule Pack 은 민감정보 탐지를 위한 정규식, 후처리 조건, confidence 기준,
   allowlist/denylist, 테스트 샘플을 묶은 **규칙 데이터**다. Rule Pack 은 모델도
   탐지 결과도 아니며, 실행 코드는 Rule Pack Engine, 실행 결과는 Rule Finding 으로
   구분한다.
8. Rule Finding 은 Rule Pack Engine 이 문자열에 Rule Pack 을 적용한 결과로 생성한
   민감정보 후보이며, 원본 문자열을 직접 바꾸지 않는다. 최소 필드는
   `detector_id`, `source=rule`, `finding_kind`, `start_offset`, `end_offset`,
   `confidence`, `mask_token` 후보이다. Token Classification Model 의 실행 결과는
   Model Finding 으로 부르고 `source=model` 을 사용한다. 두 finding 계층은
   Finding Merger 와 Mask Token Allocator 이후에만 표시/전달 치환에 반영된다.
9. Eval Dataset 은 민감정보 탐지/마스킹 성능을 검증하기 위한 입력 샘플과 기대
   탐지 결과의 묶음이다. 학습용 training dataset 이 아니라 AURA 필터의
   모델만/rule pack 만/model+rule 결합 탐지율, 오탐률, 마스킹 일관성을 측정하는
   테스트셋이다. 실행 코드는 Eval Runner, 결과물은 Eval Report 로 구분한다.
10. Finding Merger 는 Rule Finding 과 Model Finding 을 하나의 최종 후보 목록으로
    병합하는 단계다. 겹치는 span 병합, 더 긴 span 우선, confidence/source 우선순위,
    같은 원문/같은 위치 중복 제거, finding_kind 정규화를 수행한다. 원본 문자열을
    바꾸거나 최종 마스킹 문자열을 만들지 않으며, 결과 후보 목록을 Mask Token
    Allocator 에 전달한다.
11. Mask Token Allocator 는 Finding Merger 가 남긴 후보에 label-numbered 방식의
    Mask Token 을 부여한다. 기본 정책은 same-value-same-mask 이며, 실제 표시/전달
    치환은 Protected String View 생성 시 수행한다.

## Consequences

- 기본 설치 설명은 "`openai/privacy-filter` + 한국형/Secret Rule Pack" 으로
  단순하게 유지하면서, 사용자는 모델/룰셋/데이터셋을 교체할 수 있다.
- Git 저장소와 `third_party/` 크기가 커지는 문제를 피한다.
- 발표/문서에서 "2개 LLM" 오해를 줄이고, AURA 의 보안 계층이 생성형 LLM 이 아니라
  Token Classification Model + Rule Pack + Policy Gateway 임을 명확히 한다.
- 향후 CLI 는 사용자-facing option 으로 `--pii-model` 같은 짧은 이름을 제공할 수
  있지만, 문서와 내부 registry 용어는 `Token Classification Model` 로 고정한다.
