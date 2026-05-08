<!-- /autoplan restore point: C:\Users\21m15\.gstack\projects\AURA\main-autoplan-restore-20260507-162252.md -->
# ADR-0059 — Safety model UI edit semantics (selection vs asset management)

- **Status**: Accepted
- **Date**: 2026-05-08
- **Related**: ADR-0058

## Decision

1. Safety Settings dialog의 "모델 추가/삭제"는 현재 자산의 생성/삭제가 아니라,
   이미 레지스트리에 노출된 모델 자산의 활성/비활성 선택만을 의미한다.
2. 모델 자산의 실제 추가/삭제(새 manifest 디렉터리 등록, 삭제, 이동)는
   별도 명령/워크플로우로 분리한다.
3. 선택을 변경하더라도 `~/.aura/token-classification-models` 트리는 건드리지 않는다.
4. `saveSafetyProfile()`은 변경된 선택만 저장하며, 최소한의 동작 보존을 위해
   기존 모델이 비어 있으면 안전하게 모델 비활성화 상태를 저장한다.

