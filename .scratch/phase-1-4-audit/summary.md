# Phase 1~4 재점검 — 종합 리포트

**점검일**: 2026-05-03
**Baseline**: HEAD `b0c625c1` (`feat(phase-4d/4e.1): rendering-time overrides + conservative resolve pass`)
**규율**: B + X (read-only audit + halt on third_party/ touch)
**범위**: Phase 1.1 ~ Phase 4E.2 (Tasks.md 기준)

---

## TL;DR

| 항목 | 결과 |
|---|---|
| **Phase 1~4 구현 자체** | ✅ **GREEN on Linux WSL** (claimed baseline). 75개 sub-step 모두 코드/테스트/명세 일치 |
| **Windows MSVC 빌드** | 🔴 **RED**. open_memstream, weak attribute 미해결 |
| **프로세스/문서 무결성** | ⚠️ **다수 결함**. AUTOMATION_ROADMAP.md 부재, Tasks.md 상태 표 불일치, 미커밋 WIP DIFF |
| **R-1/R-4/R-5/R-9/R-10 등 정책** | ✅ **모든 Phase에서 준수** |

**총 결함 7건**. 모두 Phase **구현 결함이 아닌 프로세스/플랫폼 결함**.

---

## Phase별 상태

### Phase 1 — Engine Adapter Contract / Orchestrator Layer  ✅ GREEN

| sub-step | 상태 | 비고 |
|---|---|---|
| 1.1 Subprocess 추상 | ✅ | `include/engine_subprocess.h` + ghidra/rizin 위임 확인 |
| 1.2 Request Types | ✅ | `engine_request.h:44-49` enum + R-7 mask |
| 1.3 IPC schema | ✅ | type 필수 + body/raw/diagnostics 분리 |
| 1.4 Engine Manifest | ✅ | validate 함수가 R-7 비표준 비트 거부 |
| 1.5 Adapter vtable | ✅ | init/request/shutdown 단일 진입점 |
| 1.6 Orchestrator | ✅ | type 기반 라우팅 + NULL-first 정책 |
| 1.7 Crash isolation | ✅ | `case_isolation` cross-engine non-propagation 단언 |
| 1.8 Source-of-truth (R-4) | ✅ | ghidra raw XML 무가공 detach |

**Cross-cutting**: legacy/ 격리 확인, header pollution 0건, self-contained.

### Phase 2 — Rizin Adapter + Ghidra Co-primary  ✅ GREEN

| sub-phase | 항목 수 | 결과 |
|---|---|---|
| 2A (Rizin Analyze) | 11 | ✅ all verified |
| 2B (Rizin Decompile) | 7 | ✅ all verified |
| 2C (Ghidra Decompile) | 6 | ✅ all verified |

**핵심 verifications**:
- 2A.4: 8종 1급 record (R-11 provenance + R-12 1급화) `test_rizin_record_widen` 8 cases
- 2B.5: WSL ctest GREEN — backend=PDGJ, body_len=177, line_map=4
- 2C.3: Ghidra manifest scope DECOMPILE-only (commit `11a2b2e2`), ANALYZE→ERR_NOT_FOUND routing
- 2C.6: status mapping 11종 R-7 합성 확인
- R-10 isolation: `RzCore`/`RzAnalysis*` leak 0건 (third_party_hub 외부)

### Phase 3 — Unified Model Ingestion  ✅ GREEN

| sub-phase | 항목 수 | 결과 |
|---|---|---|
| 3A (Body Schema Contract) | 4 | ✅ |
| 3B (Rizin v0.8.2 baseline 정정) | 4 | ✅ |
| 3C (Ghidra IR Artifact, 재정의) | 5 | ✅ |
| 3D (Ghidra Analyze 보류) | 3 | ✅ |
| 3E (Tier C Diagnostic Stream) | 4 | ✅ |
| 3F (Mapping Conformance Tests) | 3 | ✅ |

**핵심 verifications**:
- 3B.3: stable v0.8.2 baseline — `aftj` 제거, framing `@` → `_`, agf json/afvlj 매핑
- 3C: pseudo-C view 채움이 정식으로 Phase 4+ backlog (3C2)로 이관, R-9 enforcement (IR→pseudo-C 합성 코드 0건)
- 3E: `AuraDiagnosticsHeader` magic 0xAFAA3E01, severity CRITICAL만, 6개 reason key 정의
- 3F: `test_unified_ingestion` 3 sub-case — Rizin analyze GREEN / Ghidra body=NULL 단언 / Rizin decompile capability-gated SKIP
- 용어 제한 ("정규화 분석기" / "analysis") 위반 0건. legacy 문서 (high_level_ir.md, d29b_semantic_mapping.md) 새 코드에서 미참조

### Phase 4 — Override Layer  ✅ GREEN (4A·4B·4C·4D·4E.1) / 4E.2 Phase 5 이관

| sub-phase | 항목 수 | 결과 |
|---|---|---|
| 4A (Stable Identity Contract) | 4 | ✅ 완료 (2026-05-01) |
| 4B (SQLite Store) | 3 | ✅ 완료 (2026-05-02) |
| 4C (Overlay Apply) | 3 | ✅ 완료 (2026-05-02) |
| 4D (Rename/Type Layering, scope-confined) | 4 | ✅ 2 완료 + 2 deferred |
| 4E (Re-analysis Pipeline) | 2 | ✅ 4E.1 완료 + 4E.2 Phase 5 이관 |

**핵심 verifications**:
- 4A: `AuraOverrideKey` 16 TC, EXACT/STRONG/WEAK/MISSING confidence
- 4B: PK = (sha256, engine_id, request_type, function_stable_id, target_kind, target_stable_id) — 4A 키와 일치
- 4C.2: APPLY/CONFLICT/ORPHAN 게이트 11 TC
- 4E.1: variable target → ORPHAN (4D 후속 의존 의도된 동작) TC-07 시연
- R-5 (engine output immutable): override_view.c / override_pipeline.c에 engine response 변형 0건
- R-9 (no new analysis): pipeline에 CFG/type inference/name fallback 0건
- D-2 (SQLite row-oriented): `third_party/sqlite/` amalgamation 사용

**테스트 합계**: 4A(16) + 4B(11) + 4C(10+11) + 4E.1(11) = **59 TCs all PASS**

---

## 발견 사항 7건

| # | 제목 | Severity | Phase 영향 | Triage |
|---|---|---|---|---|
| 01 | AUTOMATION_ROADMAP.md missing from repo root | HIGH | cross-cutting | ready-for-human |
| 02 | MSVC `open_memstream` 마이그레이션 미완성 | CRITICAL | Phase 4 baseline | ready-for-agent |
| 03 | MSVC `__attribute__((weak))` 미지원 | CRITICAL | Phase 1+2 tests | ready-for-agent |
| 04 | 미커밋 DIFF가 WIP 상태로 방치됨 | HIGH | Phase 4 GREEN 주장 무효화 | ready-for-human |
| 05 | 알려진 MSVC 부채가 추적 시스템에 등재되지 않음 | MEDIUM | cross-cutting | ready-for-human |
| 06 | `MappedFile.fd` 처리에 두 경쟁 접근 공존 | MEDIUM | Phase 1 (parser) | ready-for-agent |
| 07 | Tasks.md 상태 표가 sub-phase 실 상태와 불일치 | LOW | Phase 4 추적 | ready-for-agent |

상세는 `issues/01-*.md` ~ `issues/07-*.md` 참조.

---

## 핵심 통찰

### 1. **Phase 1~4 구현은 견고하다**

Tasks.md의 모든 sub-step claim이 실제 코드/테스트/문서와 일치. 누락된 구현 0건. 엔진 정책(R-1, R-4, R-5, R-9, R-10, R-11, R-12) 위반 0건. legacy 문서 잘못된 재사용 0건.

### 2. **결함은 모두 "플랫폼" 또는 "프로세스" 카테고리**

- **플랫폼 (issue 02, 03, 06)**: Windows MSVC 지원 미완성. 작성자가 인지하고 있었으며 (Tasks.md L84~92, L207) "별도 작업으로 분리"라 기록했지만, **추적 시스템에 등재되지 않음 (issue 05)**.
- **프로세스 (issue 01, 04, 05, 07)**: 추적 도구 부재, WIP 방치, 표기 불일치. 코드 품질과 무관, 자동화 세션 주기에서 누적된 부채.

### 3. **"Phase 4 GREEN baseline" 주장은 환경 특정**

직전 commit `1b52c2ff`의 메시지는 "Phase 4 GREEN baseline"이지만 그 시점에도 MSVC는 RED였을 가능성이 매우 높음 (해당 커밋이 추가한 MSVC compat shim들이 여전히 미완성 — issue 02, 03). **GREEN의 환경 컨텍스트가 명시되지 않음**이 issue 05의 본질.

### 4. **B+X 점검 규율은 깔끔하게 작동했다**

- 코드 0건 수정
- third_party/ 0건 접근
- 모든 발견을 `.scratch/phase-1-4-audit/issues/`로 라우팅
- 미커밋 DIFF는 baseline의 일부로 분석만 수행, 정리 없음

---

## 권장 후속 액션

### 즉시 처리 (ready-for-agent — 자동화 가능)

| 우선순위 | 작업 | 영향 |
|---|---|---|
| P0 | issue 03: `WEAK_STUB` 매크로를 `aura_compat.h`로 분기 | MSVC 빌드 일부 회복 |
| P0 | issue 02: `open_memstream` 헬퍼를 공유 헤더로 추출 + 30 callsite 마이그레이션 | MSVC 빌드 회복 |
| P1 | issue 06: G6 vs G7 모순 해소 (G6 채택, G7 폐기 권장) | DIFF 무결성 |
| P2 | issue 07: Tasks.md L38 상태 `[ ]` → `[-]` | 추적 정확도 |

### 사용자 결정 필요 (ready-for-human)

| 우선순위 | 작업 | 결정 사안 |
|---|---|---|
| P0 | issue 01: AUTOMATION_ROADMAP.md 처리 | promote / 통합 / 신규 작성 중 택일 |
| P0 | issue 04: 미커밋 DIFF 처리 | P1/P2/P3/P4 중 택일 |
| P1 | issue 05: 환경 baseline 정책 | "MSVC도 정식 지원" vs "Linux WSL only" |

### 본 점검 결과 자체

- ✅ Phase 1~4 **구현 baseline은 신뢰 가능** (Linux WSL 환경 가정).
- 🔴 **MSVC 환경**은 별도 작업 필요 — Phase 8 또는 신규 Phase로 정식 등재 권장.
- ⚠️ **프로세스 위생** 개선 필요 — AUTOMATION_ROADMAP.md, Tasks.md 표기 일관성, WIP 정책.

---

## DoD (본 점검의)

- [x] `issues/` 에 발견 항목 7개 등재
- [x] 종합 리포트 `summary.md` 작성
- [x] Tasks.md `[x]` 표기와 실제 상태의 괴리 항목 식별 (issue 07)
- [x] 안전 노이즈(.claude, scheduled_tasks.lock 등) 제외, 본질적 결함만 추출
- [x] B+X 규율 위반 0건 (코드 미수정, third_party/ 미접촉)

**점검 종료 시각**: 2026-05-03
