# AURA — Reverse Engineering Tool Development Tasks

> **실행 전 필독**: [rules.md](./rules.md) | **설계 기준**: [PRD.md](./PRD.md)
> 각 태스크는 `완료 기준(DoD)`을 **모두** 충족해야 `[x]`로 표시한다.
>
> **태스크 상태 기호**
> | 기호 | 의미 |
> |------|------|
> | `[ ]` | 미시작 |
> | `[-]` | 구현 완료, DoD 검증 진행 중 |
> | `[x]` | 모든 완료 기준 충족, 완전 완료 |

---

## 현재 진행 상태

| 항목 | 내용 |
|------|------|
| **버전** | **v2.3.0 released** (Session #19, 2026-04-25, Option A, tag `v2.3.0` `1b12e6c`). 다음 release = `v2.4.0` Type Propagation (Session #21 picking, 2026-04-25). v2.4.0 Phase 2.4-TP `[-]` active. 이전 v2.4.0/v2.5.0 기획 항목들은 **v3.0+ Reservoir** 잔존 (방향성 초석/잔해, 즉시 실행 X). rc tag chain: `v2.3.0-rc1` → `rc1.1` → `rc2~rc6` → `v2.3.0` final. |
| **현재 페이즈** | **v2.4.0 Phase 2.4-TP: Type Propagation `[-]`**. Session #21~22 (2026-04-25). 사용자 결정 = "v2.4 = 타입 전파 기능 구현 + GUI Rename/Type Cast wire-back". 8 sub-task: TP-1 [x] (PR #39) + T-5a [x] (PR #40 `bee5286`) + **T-5b [-] active** + TP-4/TP-2/(TP-3+T-5c 통합)/T-5d [ ] + wrap. **active task = T-5b** (Variable Rename propagation — `vp_apply_to_hir` bridge + FileLoader rename map + GUI wire). PR-based workflow 강제 (squash merge, kill-switch `AURA_TYPE_ENGINE=heuristic` 1 release window). Reservoir B.2 E-4 / B.4 H-FU-3 = TP-3 으로 흡수 (재실행 금지). T-5c 는 TP-3 와 단일 PR 통합 (cross-fn cascade 보장). |
| **v1.0 상태** | Phase 0~8 전체 구현 완료. R.6 (v1.0.0 git tag/Release) 사용자 결정으로 보류 → v1.0.1로 통합 발행 예정 |
| **완료된 Phase** | Phase 0~8, v1.0 R.1~R.5+R.T, v1.0.1 P.1~P.19+P.T, v1.1 V1.1-1~V1.1-T, v1.1.x-1~v1.1.x-6 |
| **테스트 상태** | **ctest 173/173 GREEN** (2026-04-21 Session #12, post Session #10/#11 Phase 2-X 13 PR merge, HEAD `a547b31`). Advanced harness 20/20 PASS. R-1 / R-4 / R-1-asan / R-2a / R-2b / R-3 / R-5 / R-6 전부 해소. 잔존: **R-7 플러그인 시스템 해체** (v2.3.0 Phase 2-G 로 재배치; 사용자 결정으로 v2.3 bucket 내 breaking 으로 처리). |
| **Ghidra Analyzer Parity (entry-point 기준)** | 12/28 ✅ DONE / 8 🟡 PARTIAL / 8 ❌ MISSING — v1.0.1에서 PARTIAL+MISSING 16개 모두 보강. v1.1.x 에서 Phase C + δ 로 추가 강화. **Session #10/#11 Phase 2-X-1~12 병렬 track 으로 parity 추정 ~55-60 → ~75-100+** (MASTER_ROADMAP §2 범위 도달, 상세 섹션 `## v2.3.0 Phase 2-X` 참조). |
| **함수 탐지율** | Stripped AArch64 기준 80.5% Recall, F1 0.866 |
| **v1.1 진행** | V1.1-1~T `[x]` (**v1.1 완료**) · v1.1.x-1~6 `[x]` · **V1.1.x-R `[x]`** (R-1/R-4/R-1-asan/R-2a/R-2b/R-3/R-5/R-6 전부 해소, δ-RC tracking subsection 에 follow-up 2건 추적) · V1.1.x-N `[ ]` (NH). **v2.0.0 major bump (R-6 aura_python 제거 = SemVer breaking)** 로 v1.1.x post-release maintenance 종결. |
| **Live canonical** | `AUTOMATION_ROADMAP.md` (실시간) / `Tasks.md` = 릴리스 스냅샷 (rules.md §11) |
| **마지막 업데이트** | 2026-04-26 Session #22 D-28 신규 (Ghidra HighFunction XML → AURA HIR Mapping 설계, design turn, 코드 변경 0, 산출물 = `docs/design/d28_ghidra_hir_mapping.md` 834 LOC, 사용자 5-조건 승인: 3-tier 분류 + diagnostic emit / per-tier ≥95% + Tier C hard fail / HirFunc ABI 확장 / 별도 branch `d28/hir-mapping-plan` 별도 PR / binding sequence). 60 element 매핑 + 74 P-Code op → 48 IrOpcode (커버리지 59%). Tier C critical 7 항목 (address space / type·struct / calling conv·vararg·noreturn / indirect / param>16 / jumptable / seqnum). HirFunc ABI = 필수 calling_conv/is_vararg/is_noreturn + 권장 addr_space/return_storage/param_storage[] (v2.5.0 SemVer minor). 다음 = T-5b finalize → D-29 plan turn. plan: `~/.claude/plans/aura-harmonic-teapot.md`. 이전: 2026-04-26 Session #22 D-27 Phase 0 GREEN (Ghidra decompile 빌드/실행 검증, PR #43 `fe39dfd` main 머지). branch `d27/phase0-ghidra-build` (worktree `~/Desktop/AURA-d27`). vendor: Ghidra 12.0.4 `decompile/cpp/` (~46K LOC, Apache 2.0) + `decompile/zlib/` headers + Processors x86/AARCH64 spec + tinyxml2 11.0.0 (zlib license). build artifacts: `aura-decompile` 4.7M aarch64 PIE + `aura-sleigh-compile` 1.1M + `x86-64.sla` 488KB. 신규 build-time dep: bison 3.8.2 / flex 2.6.4 (사용자 §10 승인). libbfd 회피 (decomp_dbg / loadimage_bfd / bfd_arch / analyzesigs / codedata / sleighexample 빌드 제외). smoke test: `tests/integration/test_ghidra_subprocess.c` 0.05s GREEN (LABELS=ghidra-subprocess). AURA 메인 코드 변경 0. 후속 결정 대기: D-28 (HIR 매핑 설계), D-29 (codegen.c 통합 경계). plan: `~/.claude/plans/aura-harmonic-teapot.md`. 본 결정 근거: `COMPETITOR_GAP_ANALYSIS.md` (covered_avg 55 vs Ghidra 99 격차). 이전: 2026-04-26 Session #22 D-26 신규 (커스텀 구현 우선 정책 해제, governance only, 코드 변경 0, PR #42 `83e40af` main 머지, plan: `~/.claude/plans/aura-harmonic-teapot.md`). 본 결정 근거 = `COMPETITOR_GAP_ANALYSIS.md` (동일 세션, 496 LOC). T-5b 작업은 본 governance turn 동안 보류 (branch `phase-2.4tp/t5b-rename-propagation` 손대지 않음). 이전: 2026-04-25 Session #22 T-5a [x] 머지 (PR #40 `bee5286`, ctest 187→190 GREEN, 3 신규 test: test_hir_emit_positions/test_decompile_positions/test_decompile_menu_target) + T-5b [-] 시작 (branch `phase-2.4tp/t5b-rename-propagation`). 사용자 요구 = "Rename Variable 실제 동작". 핵심 산출물 = `vp_apply_to_hir(VarPropCtx*, HirFunc*)` bridge helper (`vp_propagate` 의 `names[]` ↔ `hir_var.name[]` 사이 자동 write-back 누락 해소) + FileLoader rename map + main_window QInputDialog wire. plan: `~/.claude/plans/2-3-iterative-kazoo.md` (T-5b 실행 상세 + 6-commit 시퀀스 + 파국 차단 체크리스트 8 항목). 이전: 2026-04-25 Session #21 TP-1 [x] 머지 (PR #39 `a610466`) + T-5a [-] 시작. 사용자 추가 요구 = "변수 클릭 후 우클릭 메뉴로 Rename + Type Cast" + "Ghidra cascade 실패 시나리오 회피". v2.4.0 sub-task 4 → 8 확장 (T-5a/T-5b/T-5c/T-5d 추가, T-5c 는 TP-3 와 단일 PR 통합). plan: `~/.claude/plans/2-3-iterative-kazoo.md` (10 항 파국 시나리오 분석 + 11 항 PR 머지 전 체크리스트 추가). 이전: 2026-04-25 Session #21 v2.4.0 Phase 2.4-TP picking + TP-1 시작. 사용자 결정 "v2.4 = 타입 전파 기능 구현 + PR-based workflow". v2.4.0 빈 placeholder → 4 sub-task (TP-1 ~ TP-4) + wrap 정식 entry 화. TP-1 in-progress (`tc_infer_types` 기본 path 통합 + dispatch shim `type_dispatch.c` + env kill-switch `AURA_TYPE_ENGINE`). 4 production call site 교체. RED test `test_tc_default_path.c` 8/8 GREEN. ctest build-rel **187/187 GREEN** (185 baseline + 2 신규: test_tc_default_path + test_func_detect_gap stale auto-count). PRD D-24 신규 등록. plan: `~/.claude/plans/2-3-iterative-kazoo.md`. branch `phase-2.4tp/t1-tc-default`, PR open 대기. (이전: Session #20 v2.4+ → v3.0+ Reservoir reorg. v2.4.0 (35) + v2.5.0 (5) 기획 항목 모두 v3.0+ Reservoir 로 이전. PRD D-23 신규. 코드 변경 0 (governance only). 이전: Session #19 ls spot-check + G-D Pass + Phase 2-D `[x]` + v2.3.0 final tag Option A 즉시 발행 + v2.3.0 umbrella `[x]`. ls spot-check (`tests/results/v2_3_0_rc6_covered_avg/ls_regression_spotcheck.md`) 가 −2 covered_avg 를 coverage expansion artifact 로 입증: baseline covered 186/301 (61.8%) → rc6 covered 299/301 (99.3%), +113 함수 신규 decompile, 점수 합 +5,730 (+55%). 공통 함수 n=189 의 mem mean −1.39 / ctrl mean −0.78 small drift 는 v2.4 TRACK-1/2 이관. v2.3.0 umbrella `[-]` 유지 = final tag 결정 사용자 입력 대기 (Phase 2.5). (이전: Session #18 D-T 완료 + governance reorg v2.4/v2.5 분리. D-T 3-binary covered_avg 측정 (`tests/results/v2_3_0_rc6_covered_avg/`): cat 54→56 (+2 ✅), ls 56→54 (−2 ⚠️), aura_self 55→51 (−4 ⚠️) — 모두 stop 임계 −5 pt 이내. mean total Δ (component): cat +41.57 / ls +19.14 / aura_self −8.0 (n=1 sparse name match). Phase 2-D 4/4 sub-task `[x]` 이나 G-D 판정 = 사용자 후속 결정 (보류) 으로 umbrella `[-]` 유지. (이전: PR #33 분기점 복구, main `bc3c93a`, ctest build-rel 185/185 GREEN. D-1 `45aaf32` / D-2 `9aa0c13` / D-3 `9e0e811` 모두 main 머지. rc4→rc6 정량 효과: cap_hits_512 82→68, indirect skip 0→260.) |

> **v1.0 Scope**: Phase 0~8 전체. 이전 버전의 Phase 9~13 (통합 테스트, 문서/배포, 확장 기능, Ghidra Parity, 디컴파일러 v2)은 모두 Phase 1~8 내 하위 태스크로 재분류되었다.
>
> **v1.0.1 Scope**: (a) Generic Analyzer Registry 인프라(P.1, P.2), (b) PARTIAL 8개 정형화(P.3~P.9, P.18 일부), (c) MISSING 8개 신규 구현(P.10~P.16, P.19), (d) v1.1 Lazy Analysis 작업물 통합 커밋(P.18), (e) Wiring Contracts 일괄(P.17), (f) 종합 검증(P.T), (g) CHANGELOG + GitHub Release(R.6 재정의). v1.0.0 git tag는 생성하지 않고 첫 공식 tag = v1.0.1.

---

## 페이즈 의존성 지도

```
Phase 0 (프로젝트 설정)
  └─► Phase 1 (인프라 + 플러그인/CLI)
        ├─► Phase 2 (디스어셈블러 + Xref + 재귀)
        │     └─► Phase 3 (파일 파서 + DWARF/PDB + 디버그 정보)
        │           └─► Phase 4 (심볼릭 + 고급 분석)
        │                 └─► Phase 5 (디컴파일러 + HIR + 최적화 15패스)
        └─► Phase 8 (GUI + 협업 서버)
              ├─ 2.x 통합 ◄─ Phase 2 완료 후
              └─ 5.x 통합 ◄─ Phase 5 완료 후

Phase 6 (LLM 로컬) + Phase 7 (LLM 클라우드 + 고급 기능)
  ▶ Phase 1 완료 후 병렬 진행 가능

Phase 0~8 모두 완료 ──► v1.0 Release
```

---

## Archived Releases (Tasks_archive/)

> 종결 릴리스는 `Tasks_archive/` 로 이전되었다. 본 섹션은 stub 인덱스다.
> 원본 복원/조회 시 각 파일을 직접 참조. rules.md §11.5 에 따라 archived 엔트리는 상태 전환 금지 (frozen).

| 릴리스 / 페이즈 | 파일 | 범위 |
|----------------|------|------|
| Phase 0~8 (v1.0 baseline) | [phase_0_8.md](./Tasks_archive/phase_0_8.md) | 185 태스크 (Phase 0~8) |
| v1.0 Release | [v1_0.md](./Tasks_archive/v1_0.md) | R.1~R.T (7 태스크) |
| v1.0.1 Release | [v1_0_1.md](./Tasks_archive/v1_0_1.md) | P.1~P.19 + P.T (20 태스크) |
| v1.1 Release | [v1_1.md](./Tasks_archive/v1_1.md) | V1.1-1~V1.1-T (4 태스크, Function Detection 강화) |
| v1.1.x Post-release Maintenance | [v1_1_x_post_release.md](./Tasks_archive/v1_1_x_post_release.md) | v1.1.x-1~6 + V1.1.x-R + V1.1.x-N + V2.0.x-F + V2.0.x-F-1 (v2.1.0 shipped Session #5) |
| v2.2.0 Phase G + H | [v2_2_0.md](./Tasks_archive/v2_2_0.md) | G-1~G-4 + H-1~H-4 (Session #6, HEAD 711c4e8) |

**통합 현황**: 6 archive 파일 / 합계 ~2580 줄. Tasks.md 본체는 active/pending 릴리스 (v2.3.0 현재, v1.2 예정) + 현재 상태 표 + 통계 + 핸드오프 로그만 유지.

---

## v2.3.0 CFG Quality Improvement (scope-reduced) `[x]` — Sessions #7 ~ #19, released 2026-04-25

> **목표**: CFG construction + analysis 품질 핵심 — 계측 (2-A) + 가시성 (2-B) + default-on promotion (2-D) 만 유지한다.
> **Scope 축소 결정 (2026-04-25)**: 2-C / 2-E / 2-T / 2-F / 2-H / 2-X → **v2.4.0 bucket** 으로 이전. 2-G plugin removal → **v2.5.0 bucket** (SemVer bend 해제, 정상 SemVer 분리). 본 섹션은 A + B + D 만 추적한다.
> **Plan 원본**: `~/.claude/plans/g-h-bright-ullman.md` (session-local, canonical 아님) + `~/.claude/plans/linked-jumping-rose.md` (scope 축소 plan, 2026-04-25 사용자 승인) + `~/.claude/plans/2-3-iterative-kazoo.md` (Session #19 G-D Pass plan). 본 섹션이 release snapshot canonical (rules.md §11.1).
> **Release tag chain**: `v2.3.0-rc1` → `rc1.1` → `rc2` → `rc3` → `rc4` → `rc5` → `rc6` (`bc3c93a`, 2026-04-25) → **`v2.3.0` final** (Option A 즉시 발행, Session #19, 2026-04-25, minimal smoke + ctest 185/185 GREEN).
> **Current state (2026-04-25)**: **v2.3.0 released** (Session #19, Option A, tag `1b12e6c`). Phase 2-A `[x]` + Phase 2-B `[x]` + Phase 2-D `[x]` + v2.3.0 umbrella `[x]`. ctest build-rel 185/185 GREEN. **Session #20 reorg**: v2.4.0 (35) + v2.5.0 (5) 기획 항목 → v3.0+ Reservoir 이전. 다음 release `v2.4.0` = TBD (reservoir picking 대기, 사용자 한 task 씩 결정).

### v2.3.0 Phase 2-A: Instrumentation `[x]` — Session #7, 2026-04-19

> 계측 전용. 행동 변경 없음. baseline JSON 생성 (후속 Decision gate 의 판단 근거).

**완료 기준 (5/5 충족):**
- [x] **A-1**: cfg_metrics foundation — `src/core/cfg_metrics.{c,h}` struct (`cap_hits_512`, `indirect_call_skipped`, `indirect_jmp_skipped`, `funcs_built`) + accessor + unit tests. (commit `c9f7cc1`)
- [x] **A-2-pre**: frozen aura_self snapshot — `tests/fixtures/frozen_binaries/aura_self_v2_1_0` (5.1MB, v2.1.0 anchor `031cf9c`). smoke target 을 live `build-rel/aura` 에서 frozen binary 로 전환 (target-drift 와 decompiler-quality 분리). (commit `e72e0bd`)
- [x] **A-2**: CFG cap + indirect skip + funcs_built 카운터 배선. `src/core/pipeline.c:550,858,983` cap_hits, `src/core/recursive_disasm.c:178/205/224` indirect skip, `src/symbolic/cfg.c:322` funcs_built. (commit `106351f`)
- [x] **A-3**: postdom abort 카운터 + `AURA_LOG_W` 승격. `src/decompiler/structural_analysis.c:194-249` `s_sa_aborts` / `s_sa_funcs` + `sa_postdom_stats()`. (commit `b7f5d53`)
- [x] **A-4**: HIR goto emission 카운터. `src/decompiler/hir_builder.c:871-874` per-func goto flag + global accumulator + `hir_emission_stats()`. (commit `c13ae68`)
- [x] **A-5**: `--decompile-metrics` JSON CLI (`src/cli/decompile_metrics.c`) + 90-func corpus harness (`tests/tooling/collect_cfg_metrics.sh`) + rc1 baseline JSON (`tests/results/cfg_metrics/v2_2_1_baseline.json`). (commit `80baeb3`)

**rc1 baseline 실측 (88 funcs, aarch64 host)**:
| 카운터 | 값 | 비율 | 의미 |
|--------|----|----|------|
| `cfg.cap_hits_512` | 82 | 93% | D-1 cap 상향 default-on 근거 확고 (threshold 30% 3배 초과) |
| `cfg.indirect_call_skipped` | 0 | — | aarch64 host 제약 (parser x86 전용) — C-1 측정은 x86 corpus 필요 |
| `cfg.indirect_jmp_skipped` | 0 | — | 동일 |
| `cfg.funcs_built` | 88 | — | 배선 검증 |
| `sa.aborts` | 0 | 0% | Cooper watchdog 미점화 → E-1 CHK postdom 긴급도 급감. D-1 cap 상향 후 재측정 필수 |
| `hir.gotos_emitted` | 20 | 23% | B-1 (postdom aborted annotation) 효용 큼. 이전 추정 0.21% 의 100배 |

**검증**: build-rel 131/131 + build-asan 131/131 + smoke 90/90 GREEN. `v2.3.0-rc1` tag annotated, origin push 완료.

**Session #8 실적 (rc1 → rc1.1 CI hotfix)**: `845f515` fixture frozen pinning (`/bin/cat` 하드코딩 → `aura_self_v2_1_0` + `AURA_TEST_FIXTURE_AURA_SELF` CMake 주입), `b2f61e2` shell test `build-rel/` 하드코딩 교체 (`$<TARGET_FILE:aura>` generator expression + layered fallback). CI PR #10 6/6 GREEN → main merge (`fc858cc`) → `v2.3.0-rc1.1` tag annotated.

**DoD 판정**: 5/5 충족 + Decision gate G-A (unconditional advance) 통과 → Phase 2-B 진입 가능.

### v2.3.0 Phase 2-B: Visibility & silent-failure fixes `[x]` — Session #9, 2026-04-20

> 가시성 개선. annotation/logging 만 — 새 행동 없음. **B-1~B-4 구현 완료, 커밋 batch 대기 (Fix-3).**

**완료 기준:**
- [x] **B-1**: `PostDomInfo.aborted` respect in `src/decompiler/hir_builder.c:871-874` — `ctx->pdom->aborted` 일 때 `sa_find_join` skip + `HIR_COMMENT /* aborted postdom */` emit. **(구현 완료, 커밋 예정)**
- [x] **B-2**: 남은 6 stage INFO 로그 (`cfg.c`, `dfg.c`, `param_id.c`, `calling_conv.c`, `loop_detect.c`, `type_inference.c`) — stage 당 1 summary 라인 (`stack_analysis.c:792` 스타일). **(구현 완료, 커밋 예정)**
- [x] **B-3**: `src/decompiler/hir_emit.c:545-562` noreturn 트렁케이션 카운터 — `stmt_is_noreturn_call → break` 발화 횟수 + `hir_emission_stats()` 노출. **(구현 완료, 커밋 예정)**
- [x] **B-4**: rc2 corpus harness 재실행 + `tests/results/cfg_metrics/v2_3_0_rc2.json` 커밋. **(구현 완료, 커밋 예정; commit 필드는 Fix-4 에서 post-commit 갱신)**

**Decision gate G-B**: smoke 90/90 GREEN + abort 카운터 rc1 대비 동일 + `AURA_LOG_LEVEL=INFO` 출력에서 **고유 stage 토큰 ≥6** (AND 조건으로 총 INFO 라인 ≥9 권장) → Phase 2-C 진입.
<!-- reviewer M-3: 원 "INFO 라인 ≥9" 단독 기준은 loop_detect 3회/calling_conv 2회 중복 호출 리팩터 시 9라인 임계가 깨질 위험. 고유 stage 토큰 집합 기반으로 재정의. -->

**산출물**: `v2.3.0-rc2` tag 후보.

### v2.3.0 Phase 2-D: Default-on promotion `[x]` — Session #11~19 (다중 세션, 2026-04-22 ~ 2026-04-25)

> G-C data 기반 조건부 default-on. rc1 baseline 이미 D-1 근거 확보. D-1/D-2/D-3 모두 main 에 머지됨, D-T 측정 + G-D Pass 완료 (Session #19).

**완료 기준:**
- [x] **D-1**: CFG cap 512 → 4096 **default-on** — main `45aaf32` (Phase 2-D D-1 flip). Session #16 monitoring DoD 5/5 + rc4→rc6 `cap_hits_512` 82→68 (-17%) 정량 확인.
- [x] **D-2**: DWARF noreturn default-on — main `9aa0c13` (`call_fixup.c:166-168`, `=0`+`=no` opt-out superset). Session #17 contract-pin tests + rc6 baseline 후속. PR #33 의 stale base 본체는 close, 부가 가치 #34/#35/(#PR3) 으로 분리.
- [x] **D-3**: `indirect_resolver` default-on — main `9e0e811` (rc4 remeasure 195 sites / 88 funcs / 22% indirect 근거). rc6 의 `cfg.indirect_call_skipped` 0→56 / `cfg.indirect_jmp_skipped` 0→204 = audit chain (`a6ff6dc` wire fix) + flip 효과 정량 확인.
- [x] **D-T**: 3-binary real-binary harness 재측정 완료 (Session #18, 2026-04-25). 결과: `tests/results/v2_3_0_rc6_covered_avg/` (cat / ls / aura_self per-binary parity.json + delta.json + delta_summary.md + summary.md). **covered_avg vs phase_f_step3_f1g baseline**: cat 54→**56** (Δ +2 ✅), ls 56→**54** (Δ −2 ⚠️), aura_self 55→**51** (Δ −4 ⚠️). 모두 stop 조건 (≥−5 pt 회귀) 미해당. mean total Δ (component sum): cat +41.57 / ls +19.14 / aura_self −8.0 (n=1 sparse name match). **G-D = Pass** (Session #19, 2026-04-25): ls spot-check (`tests/results/v2_3_0_rc6_covered_avg/ls_regression_spotcheck.md`) 가 −2 covered_avg 의 dominant 원인을 **coverage expansion artifact** 로 입증 (baseline covered=186/301 → rc6 covered=299/301, +113 함수 신규 decompile, 점수 합 +5,730 (+55%), 신규 covered 함수 평균 50.7 < baseline 평균 56 → avg 희석). 공통 점수 함수 n=189 의 mem mean −1.39 / ctrl mean −0.78 small drift 는 v2.4 추적 항목 TRACK-1/2 로 이관.

**Decision gate G-D**: ✅ **Pass (Session #19, 2026-04-25)** — smoke 90/90 GREEN + 3-binary `covered_avg` stop 조건 (≥−5pt) 미해당 + ls spot-check 로 −2 의 coverage expansion artifact 입증. Phase 2-D `[x]` 승격 완료. v2.3.0 final tag 결정은 별개 user decision (Phase 2.5).

**산출물**: rc6 baseline (main `bc3c93a`, post-D-flips smoke 89-func). 후속 rc tag 는 D-T 결과에 따라 결정.

---

## v3.0+ Reservoir — deferred from v2.4.0 / v2.5.0 (사용자 결정 2026-04-25 Session #20)

> **목적**: 2026-04-25 Session #20 두 번째 거버넌스 reorg. v2.3.0 (released `1b12e6c`, Session #19) 직후 사용자 결정으로 v2.4.0 (35) + v2.5.0 (5) 의 모든 기획 항목을 본 reservoir 로 이전. **방향성의 초석 / 잔해 보존**. 즉시 실행 금지. 향후 사용자가 한 task 씩 골라 새 release version 으로 picking.
> **Plan 원본**: `~/.claude/plans/2-3-iterative-kazoo.md` (사용자 승인 2026-04-25 Session #20).
> **이전 plan 인용**: `~/.claude/plans/linked-jumping-rose.md` (2026-04-25 첫 reorg, v2.3.0 → A+B+D 축소 + v2.4/v2.5 신설).
> **SemVer 정책**: v2.3.0 다음 release 명명은 reservoir picking 결과에 따라 결정 (additive-only → v2.4.x minor, breaking 포함 → v3.0.0 major).
> **Subsection A** = 이미 main 에 머지된 코드 (v2.3.0 tag `1b12e6c` anchor). release-notes 매핑만 reservoir. **재실행 금지**.
> **Subsection B** = pending entry, 미실행. 향후 picking 대상.

### Subsection A — Code-on-main (released as part of v2.3.0, no re-execution)

> 본 subsection 의 항목들은 main HEAD `1b12e6c` (v2.3.0 tag) 에 이미 anchor 되어 있다. 머지 anchor 는 evidence 로 보존, **코드 작업 재실행 금지**. 향후 reservoir 에서 picking 시 "이미 구현 완료" 로 명시 후 release-notes 만 새 version 에 매핑.

#### A.1 v2.4-X retrospective (Session #10/#11 Phase 2-X parallel worker 머지 결과)

> Session #10/#11 에서 Phase 2-X-1~12 병렬 워커 트랙으로 구현·병합된 parity/quality 보강 결과. 13 PR (11 main + 2 follow-up) 모두 main 머지 완료. 상세 핸드오프는 `AUTOMATION_ROADMAP.md` Session #10/#11/#12 항목 참조. 계획 원본: `MASTER_ROADMAP.md` §Phase 2-X-1~12.
> **Ghidra parity trajectory**: ~55-60 → ~75-100+ (MASTER_ROADMAP §2 목표 범위 도달 추정).

**머지 완료 (acceptance evidence):**
- [x] **2-X-1** IrOpcode 28→48 확장 + CMP printer fix — PR #16, merge `8335729`, 2026-04-21.
- [x] **2-X-2** ARM `$a`/`$t`/`$d` mapping + AArch64 adrp+ldr+br Jump Table — PR #17, merge `d335481`, 2026-04-21.
- [x] **2-X-3** FlagCache 6-slot + IR validator + JumpModel 2-class — PR #19, merge `6f33a87`, 2026-04-21.
- [x] **2-X-4** Pre-pattern gate + Prologue triple + NoReturn DB 35→122 — PR #15, merge `6ca339b`, 2026-04-21.
- [x] **2-X-5** PLT x86_64 + PE IAT + FLIRT IDA + sigdb 12-sig — PR #21, merge `1f36380`, 2026-04-21. (PRD D-21 FLIRT sigdb 소스 전략 ✅ Decided 근거 구현.)
- [x] **2-X-6** Nucleus CFG-first (clean-room Andriesse) — PR #24, merge `a547b31`, 2026-04-21.
- [x] **2-X-7 Stages 1-2** IrSort helpers + Flag exit snapshot — PR #22, merge `ea7f8ad`, 2026-04-21. Stage 3-5 는 Subsection B.
- [x] **2-X-9** PDB partial + PE forwarder + Ordinal + dual-name — PR #14, merge `f2613c9`, 2026-04-21.
- [x] **2-X-12** `.eh_frame` → `CFG_EDGE_EXCEPTION` + Win64 UNWIND_CODE — PR #20, merge `ad3ab6f`, 2026-04-21.
- [x] **2-X-12 follow-up 1 (CFI VM)** CFI VM partial + step/mem caps + 6-case fuzz — PR #25, merge `c692ab5`, 2026-04-21.
- [x] **2-X-12 follow-up 3 (UnwindInfo)** Unified UnwindInfo EH+PE layering refactor — PR #23, merge `2921548`, 2026-04-21.

**Acceptance evidence**: 13 PR all merged to `main` at HEAD `a547b31` → 후속 v2.3.0 tag `1b12e6c` (Session #19) anchor. Post-merge ctest 173/173 → **185/185 GREEN** (Session #19 재확인). 각 PR 머지 직전 CI 개별 GREEN.

#### A.2 v2.4-H Session sweep — H-SW-1

- [x] **H-SW-1** Session #9 sweep — `cmake -S -B` 호출 통일 (부분 완료분 잔여 파일 정리) + benchmark path 통일 (완료분 재확인 후 close-out 문서화). 코드 머지 main anchor.

### Subsection B — Pending (deferred, no execution)

> **본 subsection 의 항목들은 미실행 상태**. 향후 사용자가 새 release version 에 picking 후 정식 진입. 항목별 DoD 블록 + Decision gate 보존 (rules.md §11.4 acceptance-rule Rule 11 entry preservation 만족).

#### B.1 v2.4-C: Opt-in capability expansion `[ ]` — (이전: v2.3.0 Phase 2-C, 사용자 결정 2026-04-25)

> 모든 신규 기능은 `AURA_*` 환경변수 flag 뒤. Default-off. flag 전환 근거 데이터 수집.

**완료 기준:**
- [ ] **C-1**: `src/disasm/indirect_resolver.c` wiring into `recursive_disasm.c` — `AURA_INDIRECT_RESOLVE=1` opt-in. 측정은 x86 corpus 필요 (aarch64 host 제약).
- [ ] **C-2**: DWARF-derived noreturn 힌트 — `AURA_DWARF_NORETURN=1`.
- [ ] **C-3**: Symbol-heuristic noreturn — `AURA_SYM_NORETURN=1`. v2.4.0 default-on 금지 (사용자 결정, 2026-04-19).
- [ ] **C-4**: CFG cap flag — `AURA_CFG_DISASM_MAX=<N>` 런타임 override.
- [ ] **C-5**: CHK postdom (Cooper-Harvey-Kennedy) 대체 — `AURA_POSTDOM_ALGO=chk`. v2.4.0 opt-in only (사용자 결정).
- [ ] **C-6**: Exception flow (`.eh_frame`) plumbing — `AURA_EH_FLOW=1`, policy 변경 없음 (plumbing only).
- [ ] **C-7**: abort-heavy corpus 추가 — `noreturn_truncations=0` 탈피. abort/exit/`__stack_chk_fail` 빈번 binary 선택 (reviewer M-4).

**Decision gate G-2.4-C**: smoke 90/90 GREEN + 각 flag on/off 데이터 수집 완료 → Phase 2.4-C `[x]`.

#### B.2 v2.4-E: Architectural prep `[ ]` — (이전: v2.3.0 Phase 2-E, 사용자 결정 2026-04-25)

> 아키텍처 준비. 공개 API 추가는 허용 (additive only), breaking 금지.

**완료 기준:**
- [ ] **E-1**: CHK postdom validation — `AURA_POSTDOM_ALGO=chk` 대비 aborts/goto 카운터 비교. rc1 data (aborts 0%) 로 urgency 급감 확인됨. D-1 cap 상향 후 재측정 필수. v2.5.0 default-on 후보 (또는 v2.4.0 내 default-on 결정 보류).
- [ ] **E-2**: EH flow plumbing 완결 (plumbing only, no policy change).
- [ ] **E-3**: `--decompile-all` public API 추가 (additive only).
- [ ] **E-4**: 의미론적 depth 레버 확장 — pointer-aliasing-aware struct recovery, cross-function type propagation 등.
- [ ] **E-T**: Phase 2.4-E 종합 테스트.

**Decision gate G-2.4-E**: 전 서브-DoD 충족 + smoke 100% + 3-binary 회귀 0 → Phase 2.4-E `[x]`.

#### B.3 v2.4-F: Windows 크로스플랫폼 `[ ]` — (이전: v2.3.0 Phase 2-F + v1.2 Release 흡수, 사용자 결정 2026-04-25)

> **목적**: Windows 크로스플랫폼 빌드 + MSI 배포 패키지. Linux 기능 100% 대등.
> **추정**: 20-30h, 2-3 세션.

**완료 기준:**
- [ ] **W.1** 플랫폼 추상화 레이어: `src/core/mapped_file.c` → `mapped_file_posix.c` + `mapped_file_win.c` 분리, `mmap()` → `CreateFileMapping()`/`MapViewOfFile()` 호환 구현, 기존 `MappedFile` API 변경 없음 (소비자 코드 무수정), 조건부 컴파일 (`#ifdef _WIN32`) 또는 CMake 소스 선택.
- [ ] **W.2** Windows CI 빌드: `.github/workflows/build-windows.yml` 신규, MSVC 또는 MinGW-w64 빌드 성공, Capstone/Zydis/Qt6 Windows 정적·동적 링크, `ctest` 전체 PASS (Windows 환경).
- [ ] **W.3** Win32 호환성 패치: POSIX 전용 API (`<unistd.h>`, `<dlfcn.h>`, `<sys/mman.h>` 등) 호환 처리, 파일 경로 구분자 (`/` vs `\`) 통일, `~/.config/aura/` → `%APPDATA%\AURA\` 경로 매핑, 기존 Linux 테스트 전부 PASS 유지 (회귀 없음).
- [ ] **W.4** Qt6 Windows 배포: `windeployqt` 실행 → 필요한 DLL 자동 수집, 포터블 ZIP 빌드 동작 확인, GUI 기능 Linux 대등 (디스어셈블리, 디컴파일, LLM 패널).
- [ ] **W.5** MSI 패키지 생성: WiX Toolset 또는 CPack WIX 제너레이터로 `.msi` 생성, 설치 시 PATH 등록 + 시작 메뉴 바로가기 + 파일 연관 (`.elf`, `.pe`, `.bin`), 프로그램 추가/제거에 등록, 업그레이드 시 이전 버전 자동 제거, `ctest` 설치 후 PASS.
- [ ] **W.6** 코드 서명 (선택): Windows SmartScreen 경고 없이 설치 가능, EV 코드 서명 인증서 적용 (또는 사용자 결정으로 보류).
- [ ] **W.T** 종합 검증: Windows 11 + Linux Ubuntu 24.04 양쪽 전체 테스트 PASS, MSI 설치 → CLI + GUI 동작 → 제거 → 잔여 파일 없음, 벤치마크 회귀 하네스 Windows 에서도 동작 (aura_stripped x86_64 픽스처 추가).

**Decision gate G-2.4-F**: W.1~W.5 + W.T 충족 (W.6 선택) + Windows/Linux 양쪽 smoke 및 ctest GREEN → Phase 2.4-F `[x]`.

#### B.4 v2.4-H: Session sweep + Phase H follow-up + V1.1.x-N `[ ]` — (이전: v2.3.0 Phase 2-H, 사용자 결정 2026-04-25)

> **목적**: (a) v2.2.0 Phase H 에서 이연된 follow-up, (b) v1.1.x-N (NH-1~3) 통합. **H-SW-1 은 main 머지 완료 (Subsection A.2 참조)**, 본 subsection 은 잔여 pending 만.
> **추정**: 10-15h.

**완료 기준:**
- [ ] **H-SW-2** `tests/benchmark/resolve_aura_bin.*` — `AURA_BIN=<nonexec>` 인 경우 경고 메시지 출력 + graceful fallback (reviewer L-1).
- [ ] **H-FU-1** H-2 codegen plumbing — Phase H-2 에서 이연된 codegen 연결 잔여 (pointer-aliasing struct recovery prerequisite).
- [ ] **H-FU-2** Step 9 full 3-binary 측정 — cat 21-pair sample 을 3-binary (cat / ls / aura_self) 로 확장, covered_avg delta 기록.
- [ ] **H-FU-3** pointer-aliasing-aware struct recovery — Phase 2.4-E E-4 와 겹치나 H 출신 스코프 별도 추적, 중복 시 E-4 로 통합 처리.
- [ ] **NH-1** `src/core/pipeline.c` func_detect 중복 호출 통합 — 현재 경로 분기 2곳 호출을 1곳으로 병합.
- [ ] **NH-2** `branch_classify` table-driven 테스트 — 분기 분류 규칙 테이블 + 입력·기대값 매트릭스 단위 테스트.
- [ ] **NH-3** x86 flag-only provenance — flag-only consumer path provenance 전파 검증 + 단위 테스트.

**Decision gate G-2.4-H**: H-SW-1 + H-FU-1~3 + NH-1~3 충족 + ctest build-rel + build-asan 전체 PASS + smoke 90/90 GREEN → Phase 2.4-H `[x]`.

#### B.5 v2.4-X Pending tracks `[ ]` — Phase 2-X 잔여 (이연된 track 만, 머지된 11 PR + 2 follow-up 은 Subsection A.1 참조)

> Phase 2-X 의 11 PR + 2 follow-up 은 **이미 main 머지 완료** (Subsection A.1). 본 entry 는 머지되지 않은 2 pending track 만.

**완료 기준:**
- [ ] **2-X-7 Stage 3-5** flag phi pass 잔여 — 별도 세션, `phase-2x-7-stage3` 브랜치.
- [ ] **2-X-8** HIR label emission track — 별도 세션.

**Decision gate G-2.4-X (pending portion)**: Stage 3-5 + 2-X-8 merge + ctest 185/185 이상 유지 → Phase 2.4-X 본체 `[x]` 승격 + trajectory 실측 교정.

#### B.6 v2.4-T: 종합 검증 `[ ]` — (이전: v2.3.0 Phase 2-T, 사용자 결정 2026-04-25)

> 향후 release final tag 발행 전 종합 검증 umbrella. picking 시 활성 release version 기준 재정의.

**완료 기준:**
- [ ] ctest build-rel + build-asan 양쪽 전체 PASS.
- [ ] 3-binary smoke 90/90 GREEN.
- [ ] v2.3.0 rc1~rc6 baseline JSON 6개 + v2.4.0 rc baseline JSON 모두 `tests/results/cfg_metrics/` 커밋.
- [ ] `CHANGELOG.md` `## [2.3.0]` 섹션 (scope-reduced) + `## [2.4.0]` 섹션 완성.
- [ ] `AUTOMATION_ROADMAP.md` 에 v2.3.0 Phase 2-A/2-B/2-D + v2.4.0 Phase 2.4-C/E/F/H/X 섹션 backfill.

**Guiding principles (모든 commit 준수)**:
1. Data before code. 계측 데이터 없는 행동 변경 금지.
2. Flag-gated → default-on (with data). default-on 승격은 후속 release.
3. Real-binary smoke 는 매 commit 경계의 release gate.
4. 공개 API additive only. v2.4.0 bucket = additive minor release.
5. Single Active Task (rules.md §1). Tasks.md 에 동시 `[-]` 1건만.
6. No force-push, no amend.

**Decision gate G-2.4 (picking 시 적용)**: 전 picking 된 서브 entry `[x]` + smoke 90/90 + ctest GREEN → 활성 release version final tag (v2.4.x / v3.0.0 등 picking 결과에 따름).

**산출물 (picking 시 적용)**: 활성 release version tag + GitHub Release.

#### B.7 v2.5-G: R-7 Plugin 시스템 해체 `[ ]` (breaking) — (이전: v2.3.0 Phase 2-G, 사용자 결정 2026-04-25)

> **목적**: PRD §4.1 "플러그인 시스템 MVP 이후 유보" 위반 제거. `aura_plugin.h` + `plugin_loader.c` + `plugins/example/` 디렉터리 제거.
> **SemVer**: breaking — picking 시 v3.0.0 major 또는 별도 breaking minor 로 진행 결정.
> **추정**: 4-6h.

**완료 기준:**
- [ ] **G-1**: `include/aura_plugin.h` + `src/core/plugin_loader.{c,h}` + `plugins/example/` 제거 및 연관 CMake/Targets 정리.
- [ ] **G-2**: `src/cli/` + `src/gui/` + `src/core/pipeline.c` 등 호출부 참조 제거 (dlopen/dlsym 경로 포함).
- [ ] **G-3**: `docs/`, `PRD.md`, `README`, `AURA_MCP_플러그인_가이드.md` 에서 plugin 레퍼런스 정리 (유지 vs 제거 구분 후 일괄).
- [ ] **G-4**: ctest build-rel + build-asan 전체 PASS, smoke 90/90 GREEN, 신규 회귀 0.
- [ ] **G-5**: `CHANGELOG.md` `## [2.5.0]` 섹션에 "Removed: plugin system (R-7 breaking change)" 항목 + SemVer 정상 분리 사유 명시.

**Decision gate G-2.5 (picking 시 적용)**: G-1~G-5 충족 + smoke 90/90 GREEN + ctest GREEN → 활성 breaking release version final tag (v3.0.0 major 또는 별도 breaking minor — picking 시 결정).

**산출물 (picking 시 적용)**: 활성 breaking release tag + GitHub Release.

---

## v2.4.0 Phase 2.4-TP: Type Propagation `[-]` — Sessions #21~ (2026-04-25 시작)

> **상태**: Active (Session #21, 2026-04-25). v2.3.0 (released `1b12e6c`) 다음 release. 사용자 결정 (Session #21): "v2.4 = 타입 전파 기능 구현".
> **현재 scope**: 4 sub-task (TP-1 ~ TP-4) — `tc_infer_types` 기본 path 통합 + DWARF/PDB 시드 + cross-function 전파 + HIR emit 강화.
> **PR-based workflow**: 모든 sub-task = feature branch + squash merge to main. annotated tag = wrap stage 발행.
> **Plan 원본**: `~/.claude/plans/2-3-iterative-kazoo.md` (Session #21 picking).
> **흡수된 reservoir entry**: B.2 E-4 (cross-function type propagation) + B.4 H-FU-3 (pointer-aliasing struct recovery) → 본 plan TP-3 으로 통합. Reservoir entry 는 cross-ref 만 보존, 재실행 금지.

### v2.4.0 TP-1: `tc_infer_types` 기본 path 통합 `[x]` — Session #21 PR #39 머지 (`a610466`, 2026-04-25)

기존 자산 (884 LOC `src/decompiler/type_constraint.c`, Task 5.33 완료) 을 디컴파일 파이프라인의 기본 path 로 승격. dispatch shim (`type_dispatch.c`) + env kill-switch (`AURA_TYPE_ENGINE=heuristic|tc|both`, default=tc) 도입. 3 production call site (`pipeline.c`, `main_window.cpp`, `file_loader.cpp`) + 1 integration test (`test_llm_integration.c`) 를 dispatch 로 교체.

**완료 기준:** ✅ 모두 충족
- ✅ `aura_type_infer_dispatch(IrFunc*)` public API + `AuraTypeEngine` enum (`include/decompiler.h`)
- ✅ `src/decompiler/type_dispatch.c` (~85 LOC) — env 분기 + engine 선택 + stage log 보존
- ✅ 4 call site 교체 (production 3 + integration test 1)
- ✅ `tests/decompiler/test_tc_default_path.c` (~250 LOC) — 8 test (NULL safety, 4 engine 선택, unknown fallback, default TC PTR 추론, heuristic 완료) 모두 GREEN
- ✅ ctest build-rel 187/187 GREEN (185 baseline + 신규 2)
- ✅ `test_stage_logs` 의 `stage=type_infer` token 보존 (engine-agnostic dispatcher emit 으로 마이그레이션)
- ✅ PR #39 squash merge to main, branch auto-delete

### v2.4.0 T-5a: GUI decompile context menu + position metadata `[x]` — Session #21~22 PR #40 머지 (`bee5286`, 2026-04-25)

`m_decompileView` (Pseudo-C 패널) 에 우클릭 컨텍스트 메뉴 인프라 구축 + `hir_emit.c` 에 HirNode → byte offset range 메타데이터 추가. T-5b (Rename) / TP-3+T-5c 통합 PR (Type Cast cascade) 의 공유 전제. 사용자 추가 요구 (Session #21): "변수 클릭 후 우클릭 메뉴". Session #22 button-clickability bug fix (WordUnderCursor fallback + 인라인 cache-miss path 의 `m_decompileFuncAddr` 갱신) 포함.

**완료 기준:** ✅ 모두 충족
- ✅ `src/decompiler/hir_emit.c` `hir_emit_pseudoc_with_positions()` API + `HirEmitPositions` 구조체 (~250 LOC)
- ✅ `src/gui/file_loader.{h,cpp}` 에 `FuncCacheEntry::positions` + `decompilePositionsFor()` accessor 노출
- ✅ `m_decompileView->setContextMenuPolicy(Qt::CustomContextMenu)` + `customContextMenuRequested` 핸들러
- ✅ `src/gui/decompile_menu_target.{h,cpp}` (pure helper) — positions index hit → WordUnderCursor fallback → disabled 3-step 결정 로직
- ✅ 우클릭 메뉴 stub action: "Rename Variable..." / "Edit Type..." (실제 동작은 T-5b/TP-3+T-5c)
- ✅ `updateDecompileView()` re-emit 후 cursor / scroll 보존 (`DecompileViewState` 헬퍼, F-4 차단)
- ✅ 3 RED test: `test_hir_emit_positions.c` (5 case), `test_decompile_positions.cpp` (1 case), `test_decompile_menu_target.cpp` (7 case) 전부 GREEN
- ✅ ctest build-rel 187 → 190/190 GREEN (3 신규 test)
- ✅ PR #40 squash merge to main (`bee5286`, 2026-04-25)

### v2.4.0 T-5b: Variable Rename propagation `[-]` — Session #22 시작 (2026-04-25)

우클릭 "Rename Variable..." → 새 이름 입력 → `vp_seed_name(ctx, val_id, new_name)` → `vp_propagate()` → **신규 `vp_apply_to_hir(ctx, hir)` bridge** (Critical gap, Session #22 탐색) → `updateDecompileView()` 자동 갱신 → 모든 SSA occurrence 반영. 기존 `src/decompiler/var_propagation.c` API (Task 5.18) 활용 + bridge helper 신설.

**Critical bridge gap (Session #22)**: `vp_propagate` 는 `VarPropCtx.names[]` 만 채우고, `hir_emit.c` 는 `HirNode.hir_var.name[]` 을 읽음. 두 저장소 사이 자동 write-back 없음 → bridge helper `vp_apply_to_hir` 가 T-5b 핵심 산출물.

**완료 기준:**
- `include/var_propagation.h` (신설, public 헤더) + `vp_apply_to_hir(VarPropCtx*, HirFunc*)` 구현 (~80 LOC)
- `src/gui/rename_validate.{h,cpp}` (pure C identifier validator, ~50 LOC) — regex + C 예약어 reject + 함수 param 충돌 reject + length ≤ 63
- `src/gui/file_loader.{h,cpp}` 에 rename map (`QHash<uint64_t, QHash<uint32_t, QString>> m_renames`) + `setRename`/`renamesFor`/`clearRenames` API + `decompileFor()` 가 emit 직전 vp_seed+propagate+apply_to_hir 호출 (~90 LOC)
- `src/gui/main_window.cpp` 우클릭 핸들러 stub 교체: `QInputDialog::getText` + `validate_var_name` + `setRename` + `invalidateFuncCaches` + `updateDecompileView` + view state 보존 + `QShortcut(N)` 단축키 (~80 LOC)
- 3 RED test (모두 GUI 의존 0):
  - `tests/decompiler/test_vp_apply_to_hir.c` — COPY + PHI 전파 occurrence ≥ 2 (~120 LOC)
  - `tests/gui/test_rename_validate.cpp` — 16+ case (알파벳/underscore/숫자시작/keyword/길이/빈/vN/param 충돌) (~80 LOC)
  - `tests/gui/test_file_loader_rename.cpp` — 실 ELF 1차→setRename→2차→clearRenames→3차 (~150 LOC)
- ctest build-rel 190 → 193/193 GREEN
- PR-based merge (LOC ≤ 500 hard cap, 단일 PR)
- 단축키 default = `N` (IDA 호환)

**비실행 (T-5b 범위 밖)**:
- ssa_id == UINT32_MAX (WordUnderCursor fallback) 케이스 = Rename action **disabled** (safe-by-default)
- Cross-function rename (TP-3 의존)
- Rename undo/redo (T-5d 후)
- Ghidra-style "preview before apply" (사용자 추가 요구 시 별 PR)

### v2.4.0 TP-2: DWARF/PDB → SSA seed `[ ]` — 미시작

DWARF/PDB reader (`dwarf_types.c` / `pdb_types.c`) 가 추출한 함수 signature + struct 정의를 `tc_infer_types()` 의 seed phase 에 주입. ABI register → param node 매핑 (System V x86_64). seed 우선순위: DWARF > PDB > heuristic. `--no-debug-types` CLI 플래그.

**완료 기준:**
- `tc_infer_types_with_signature(IrFunc*, const FuncSignature*)` overload (~150 LOC type_constraint.c)
- DWARF/PDB accessor 노출 (~80 LOC)
- `tests/decompiler/test_tc_dwarf_seed.c` (~200 LOC) — DWARF 픽스처 caller 의 첫 인자 `int*` 추론 GREEN
- ctest GREEN, ASAN GREEN
- PR-based merge

### v2.4.0 TP-3 + T-5c: Cross-function propagation + Type Cast cascade `[ ]` — 미시작 (reservoir B.2 E-4 / B.4 H-FU-3 흡수, **단일 통합 PR**)

**사용자 결정 (Session #21)**: TP-3 (백엔드 cross-fn) + T-5c (GUI Type Cast cascade) 를 단일 PR 로 묶음. Ghidra 가 실패하는 cascade ("`int` → `UserStruct*` retype 시 모든 caller/callee 인자 자동 갱신") 를 v2.4.0 에서 완전 보장.

Call graph 위에서 caller 의 ARG slot 타입과 callee 의 param 타입이 양방향 unify + callee return type 이 caller `IR_OP_CALL` 결과 IrVal 에 전파. 2-pass fixpoint (top-down + bottom-up, max 5 iter). DWARF hard-fix / 없으면 soft-merge. 사용자 manual type pin = TC 의 highest-priority seed (DWARF 보다 위) → cascade 자동 활성. 우선순위: **user pin > DWARF > PDB > heuristic**.

**완료 기준:**
- **Backend (T-3)**: 신규 `src/decompiler/type_xfunc.c` (~350 LOC) + `tc_infer_types_module()` API
- **Backend (T-5c seed API)**: `type_constraint.c` override seed API (~50 LOC) — `type_override_map[val_id → IrType]`
- **GUI (T-5c)**: `main_window.cpp` 우클릭 "Edit Type..." 핸들러 + `TypeEditDialog` 실 변수명/타입 wire (~200 LOC), updateDecompileView() trigger
- `tests/decompiler/test_tc_xfunc.c` (~250 LOC) — A→B→C chain 역전파 GREEN
- `tests/test_type_cast_propagation.c` (~150 LOC) — case 1 intra-fn cascade + case 2 cross-fn cascade (DWARF 픽스처)
- F-1 false-positive 차단: cascade 가 unify 된 변수만 영향 (strict assert)
- F-9 우선순위 검증: user pin > DWARF priority test
- F-10 ARM64 lifter UAF 격리: asan job GREEN 필수
- ctest GREEN, fixpoint 5-iter cap 도달 0%
- pipeline 의 function-by-function 호출이 module-level 호출로 wrap
- PR 내부 4 commit 분할 (backend / override seed API / GUI wire / RED test) — bisect-safe
- PR-based merge

### v2.4.0 TP-4: HIR emit 강화 `[ ]` — 미시작

`hir_emit.c:901-915` 의 `int64_t*` rewrite 제거, signed/unsigned 분리 출력 (`HirType.is_signed` 활용), struct field/array 패턴 정확도 향상. 21-pair benchmark covered_avg 무회귀 + emit fallback hit rate 0.

**완료 기준:**
- `hir_emit.c` 수정 (~100 LOC) — fallback 5 군데 정리, signed/unsigned split
- `tests/decompiler/test_hir_emit_types.c` (~200 LOC) — golden diff
- 21-pair benchmark rebaseline (covered_avg ±0.5)
- emit fallback hit rate 0 (telemetry counter)
- PR-based merge

### v2.4.0 T-5d: SQLite renames/types persistence `[ ]` — 미시작

프로젝트 reopen 시 사용자 rename + type override 자동 복원. 기존 `renames` 테이블 활용 + 신규 `types` 테이블 (`function_address`, `ssa_def_site_offset`, `var_role`, `type_string`, `who`, `ts`). val_id 직접 영속 금지 (F-5 차단 — SSA val_id 는 매 분석 run 마다 재할당됨).

**완료 기준:**
- `src/gui/project.cpp` 에 `types` 테이블 신설 + `renames` 영속 wire (~100 LOC)
- 영속 키 = `(function_address, ssa_def_site_offset, var_role)` (val_id 직접 사용 금지)
- 프로젝트 close → reopen → vp_seed_name + type pin 자동 replay
- `tests/test_persist_rename_type.c` (~150 LOC) — close/reopen 변경 유지 검증
- `schema_version` column (migration 가능)
- ctest GREEN
- PR-based merge

### v2.4.0 Phase 2.4-TP wrap: umbrella `[x]` + benchmark + tag `[ ]` — 미시작

TP-1~4 + T-5a~d 완료 후 umbrella 처리. annotated tag `v2.4.0` 발행, GitHub Release 작성 (CHANGELOG 본문 import).

**완료 기준:**
- TP-1~4 + T-5a~d 모두 `[x]` (Rule 11 acceptance evidence)
- ctest 195+/195+ GREEN (8 신규 test 추가 후)
- 21-pair benchmark rebaseline 산물
- annotated tag + GitHub Release

---

## 통계

| 항목 | 값 |
|------|----|
| 총 태스크 수 | **302개** (archived 253 + v2.3.0 13 released + v3.0+ Reservoir 40 + v2.4.0 0 placeholder; Session #20 reorg 2026-04-25 으로 기존 v2.4.0 35 + v2.5.0 5 가 v3.0+ Reservoir 로 통합 이전, 새 v2.4.0 = 빈 placeholder. 합계 변동 없음). archived 상세는 `Tasks_archive/` 참조. |
| v2.3.0 태스크 (released) | **13개** — Phase 2-A 5 (A-1~A-5 `[x]`) + Phase 2-B 4 (B-1~B-4 `[x]`) + Phase 2-D 4 (D-1/D-2/D-3 `[x]` main 머지 + D-T `[x]` Session #18). **완료 13/13** + **v2.3.0 umbrella `[x]` released** (Session #19, 2026-04-25, Option A 즉시 발행, tag `v2.3.0` `1b12e6c`, ctest 185/185 GREEN). |
| **v3.0+ Reservoir** (deferred, Session #20 reorg) | **40 entry** — Subsection A (code-on-main, released as part of v2.3.0): 2-X retrospective 11 PR + 2 follow-up `[x]` (12 entry, 머지 anchor 보존) + H-SW-1 `[x]` (1 entry) = **13 [x] entry**. Subsection B (pending, no execution): 2.4-C 7 + 2.4-E 5 + 2.4-F 7 + 2.4-H 6 (H-SW-2 + H-FU-1~3 + NH-1~3) + 2.4-X pending 2 (Stage 3-5 + 2-X-8) + 2.4-T 1 umbrella + 2.5-G 5 = **27 [ ] entry**. **재실행 금지** (A) / **picking 대기** (B). |
| **v2.4.0 태스크 (Phase 2.4-TP Type Propagation, active)** | **8 entry** — TP-1 `[x]` (PR #39 머지 `a610466`, Session #21) + **T-5a `[-]`** (active, GUI 인프라) + T-5b/TP-4/TP-2/(TP-3+T-5c 통합)/T-5d `[ ]` + wrap `[ ]`. T-5c 는 TP-3 와 단일 PR 통합 (cascade 보장). Reservoir B.2 E-4 + B.4 H-FU-3 흡수 (재실행 금지, cross-ref 만 보존). PR-based workflow. plan: `~/.claude/plans/2-3-iterative-kazoo.md`. |
| v1.0 완료 태스크 | 191개 (`[x]`) |
| v1.0 미완료 (v1.0.1로 통합) | 1개 (`R.6` — v1.0.1로 재정의) |
| **v1.0.1 태스크** | **20개** (P.1~P.19, P.T) — 20/20 완료 (`[x]`) |
| **v1.1.x 태스크** | **8개** (V1.1.x-1~6 `[x]`, V1.1.x-R `[x]` 전체 해소, V1.1.x-N `[ ]` NH) |
| **v2.0.x Phase F 태스크** | **4개** (F-0-Q / F-0-C / F-0-α `[x]` breadth/stability 배선 완료, F-1 재설정. Session #4 실측 covered_avg 54.5/56.2/55.3 — DoD 70+ F-1 승계) |
| **v2.0.x Phase F-1 태스크** | **8개** (F-1-C-3 / F-1-M / F-1-O / F-1-T / F-1-N / F-1-P / F-1-F / F-1-G **8/8 `[x]`** Session #5, 2026-04-18, HEAD `031cf9c`). v2.1.0 DoD **breadth-centric 재정의** (fair cov% ≥99 + covered_avg ≥50) 로 6/6 충족. 원 depth 70+ 타깃은 scorer-bound ceiling 으로 Phase G (parity_score overhaul) / v2.2.0 이관. |
| **v2.2.0 Phase G + Phase H 태스크** | **8개 + 2 release artifacts** (G-1/G-2/G-3/G-4 `[x]` + H-1/H-2/H-3/H-4 `[x]` + Step 9 cat 21-pair sample + Step 10 release prep). Session #6, 2026-04-19, 18 commits, HEAD `711c4e8`. ctest 127/127 + ASAN 127/127 + 4/4 C++ ast_diff + 24/24 Python parity. Step 9 실측: 평균 legacy +1.05 / ast_total +0.95. **AURA runtime 의존성 0 추가** (libclang-18-dev 는 `tools/ast_diff/` 빌드 전용 dev dep). Tag/main PR 사용자 승인 대기. |
| 테스트 통과율 (v1.0.1) | 88/88 (Release) · 86/87 (ASAN; libpython leak caveat 은 R-6 `aura_python` 제거로 해소 — v1.0.1 당시 historical 표기) |
| **테스트 통과율 (v1.1.x, 2026-04-17)** | **122/122 (Release) + 122/122 (ASAN)** — V1.1.x-R 전체 해소 (R-1/R-4/R-1-asan/R-2a/R-2b/R-3/R-5/R-6). Advanced harness 20/20. 신규 회귀 0. v2.0.0 major bump (aura_python 제거 SemVer breaking). |
| 디컴파일러 최적화 패스 | 16개 |
| 지원 아키텍처 | **프로덕션 pipeline 배선**: x86, x86_64, AArch64. **lifter 존재하나 CLI/GUI pipeline 미배선 (test-only)**: ARM, MIPS, PowerPC, RISC-V, Dalvik, MSIL |
| 지원 파일 포맷 | ELF, PE, Mach-O, DEX, .NET, Firmware |
| LLM 백엔드 | LM Studio, llama.cpp, OpenAI, Groq |
| 함수 탐지율 (stripped AArch64) | Recall 80.5%, Precision 93.6%, F1 0.866 |
| Ghidra Analyzer Parity (entry-point 기준, v1.0 baseline) | 12/28 ✅ DONE / 8 🟡 PARTIAL / 8 ❌ MISSING |
| Ghidra Analyzer Parity (entry-point 기준, v1.0.1 목표) | 27/28 (P.3~P.16, P.19 신규 구현 + 기존 12 DONE 유지. `noreturn_discovered` 1건은 v1.1+ 이연) |

---

## 자동화 핸드오프

> 24/7 자동화 세션 간 상태 전달. 상세 로드맵: `AUTOMATION_ROADMAP.md`

| 날짜 | 완료 | 다음 | 차단 |
|------|------|------|------|
| 2026-04-15 | v1.1 완료(4/4), v1.0.1 릴리스, corpus 6/8 L2, decompiler 10패턴, harness 10수정 | AUTOMATION_ROADMAP A-1 | 없음 |
| 2026-04-17 | v1.1.x 1-6 완료 (Phase C + δ 번들 + Step A/A'/B). Codex Step C Conditional Approve (ac596efee19ddc1e0). ctest 117/122. 본 δ 신규 회귀 0. | V1.1.x-R triage (ir_build_ssa + stripped func_detect) + Phase D-1 RED (Step E) | exposed pre-existing defects 4건 — 본 릴리스 차단 아님 |
| 2026-04-17 | **Session #1 완료**: R-1/R-4 (ir_build_ssa unreachable block crash) 해소. compute_dominators 끝에 idom=0 정착 + compute_dom_frontier defense-in-depth (a4f7e07). ctest 117/122→**120/122** (+3 복구: stripped x2, llm_integration). Codex APPROVE (aa85897d71c566f78). | Session #1-extra: R-1-asan arm64_lifter.c:594 UAF (realloc-after-borrow). Codex 권고 다음 우선순위. | R-2 (syntax), R-3 (func_detect merge), R-5 (ehframe) 잔존 |
| 2026-04-17 | **Session #1-extra 완료**: R-1-asan (arm64_lifter realloc-after-borrow UAF) 해소. 4 handler (LDR/STR/LDP/STP) index 재접근 방식 적용. TDD 4 cycle (`test_arm64_{ldr,str,ldp,stp}_many_realloc_safe`). ASAN ctest 105/114 → **111/114** (+6 복구). build-rel 120/122 유지 (신규 회귀 0). | R-2 (real_binary_advanced syntax) + R-3 (stripped func_detect merge) + R-5 (ehframe) triage 또는 Phase D-1 RED | R-2/R-3/R-5/R-6 모두 R-1-asan 범위 외 pre-existing |
| 2026-04-19 | **Session #7 완료**: v2.3.0 Phase 2-A `[x]` 완주 (A-1~A-5 7 commits). cfg_metrics foundation + CFG cap/indirect skip/funcs_built 카운터 + postdom abort 카운터 + HIR goto 카운터 + `--decompile-metrics` CLI + rc1 baseline JSON. `v2.3.0-rc1` tag annotated + origin push. rc1 baseline: cap_hits 93% / gotos 23% / sa_aborts 0. | Session #8 Phase 2-B (B-1~B-4) | aarch64 host 제약 (indirect skip 0건) — x86 corpus 필요 |
| 2026-04-19 | **Session #8 완료**: rc1 CI hotfix 2 commits (`845f515` fixture frozen pinning, `b2f61e2` `$<TARGET_FILE:aura>` generator expression). PR #10 6/6 GREEN → main merge (`fc858cc`) → `v2.3.0-rc1.1` tag annotated. | Session #9 Phase 2-B 본체 (B-1 postdom aborted annotation / B-2 6 stage INFO / B-3 noreturn counter / B-4 rc2 baseline) | Tasks.md v2.3.0 섹션 backfill 지연 (Session #9 에서 해소) |
| 2026-04-20 | **Session #9 governance sweep**: rules.md §11 namespace prefix + RC boundary + 이중 방어 규정, `aura-acceptance-rule` Rule 11 (태스크 엔트리 선행 검사) 추가, Tasks.md 편집 PostToolUse hook 배선 (`.claude/hooks/tasks-md-acceptance-reminder.sh`), Tasks.md v2.3.0 섹션 backfill (2-A `[x]` + 2-B~E `[ ]`), `.github/workflows/tag-gate.yml` CI gate | Phase 2-B 실행 또는 backlog TASK-ARCHIVAL 처리 | 없음 |
| 2026-04-21 | **Session #10 — Phase 2-X 병렬 워커 트랙 개시**: Session #9 MASTER_ROADMAP §Phase 2-X-1~12 research 를 기반으로 TeamCreate + 명명 teammate orchestration (feedback_aura_orchestration_mode.md 준수). Phase 2-X-1 ~ 2-X-4, 2-X-9, 2-X-12 등 다수 PR draft 생성. 상세 PR 리스트 및 merge 결과는 Session #11 핸드오프에 통합 기록 (Session #10 중 merge 미진행 — Session #11 Part A 에서 일괄 merge). | Session #11 Phase 2-X 잔여 PR 생성 + merge | 없음 |
| 2026-04-21 | **Session #11 Part A + Part B — Phase 2-X 13 PR 머지 완주**: Session #10/#11 Phase 2-X 트랙 전체를 main 에 머지. Part A 머지: PR #14 2-X-9 PDB/forwarder (merge `f2613c9`), PR #15 2-X-4 NoReturn DB 35→122 (`6ca339b`), PR #16 2-X-1 IrOpcode 28→48 (`8335729`), PR #17 2-X-2 ARM mapping+JT (`d335481`), PR #19 2-X-3 FlagCache+validator (`6f33a87`), PR #20 2-X-12 `.eh_frame`/Win64 unwind (`ad3ab6f`), PR #21 2-X-5 PLT+IAT+FLIRT+sigdb (`1f36380`). Part B 머지: PR #22 2-X-7 Stages 1-2 IrSort+Flag snapshot (`ea7f8ad`), PR #23 2-X-12 follow-up 3 UnwindInfo unified (`2921548`), PR #24 2-X-6 Nucleus CFG-first (`a547b31`), PR #25 2-X-12 follow-up 1 CFI VM (`c692ab5`). 총 11 PR + 2 follow-up = **13 PR all merged**. Post-merge ctest **173/173 GREEN**. HEAD `a547b31`. Ghidra parity 추정 ~55-60 → ~75-100+ (MASTER_ROADMAP §2 범위 도달). Teammate worktree isolation 적용 (feedback_aura_teammate_worktree_isolation.md). | Session #12 spec backfill + 2-X-7 Stage 3-5 dispatch (`phase-2x-7-stage3` 브랜치) | 2-X-7 Stage 3-5 / 2-X-8 HIR label / 2-X-10/11 이연 track |
| 2026-04-21 | **Session #12 — spec backfill + Stage 3 dispatch**: Session #10/#11 Phase 2-X 13 PR 머지 후 spec docs (Tasks.md / AUTOMATION_ROADMAP.md / PRD.md) 드리프트 해소. docs-only PR (`docs/spec-backfill-session-10-11`) 로 분리 — 코드 변경 0, ctest 변동 0 (173/173 유지). Post-merge HEAD `a547b31`. PRD §7 D-21 FLIRT sigdb 소스 전략 `✅ Decided` 편입 (PR #21 근거). 병행: `stage3-worker` teammate 가 `phase-2x-7-stage3` 브랜치에서 2-X-7 Stage 3-5 dispatch. | Phase 2-X Stage 3-5 merge + 2-X-8 HIR label 착수 | 없음 |
| 2026-04-25 | **Governance reorg — v2.3.0 scope 축소 결정**: 사용자 결정으로 v2.3.0 의 2-C/E/T/F/H/X 를 v2.4.0 bucket 으로, 2-G plugin removal 을 v2.5.0 bucket 으로 분리. SemVer bend 해제 (정상 SemVer 분리). v2.3.0 = A `[x]` + B `[x]` + D `[-]` (D-T 잔여) 만 유지, final tag 는 v2.4 종합 검증과 함께 처리 또는 minimal smoke 후 발행. 코드 변경 0 — Tasks.md / PRD.md / CHANGELOG.md / AUTOMATION_ROADMAP.md 거버넌스 동기화만. plan: `~/.claude/plans/linked-jumping-rose.md`. | Phase 2-D D-T 3-binary covered_avg 재측정 → G-D decision gate | 없음 |
| 2026-04-25 | **Session #18 — D-T 실행 완료 (Phase 2-D 4/4)**: `tests/benchmark/gap_analyzer.sh` 로 3-binary covered_avg 측정. 결과 `tests/results/v2_3_0_rc6_covered_avg/{cat,ls,aura_self}/` (parity.json + delta.json + delta_summary.md) + summary.md. covered_avg vs phase_f_step3_f1g baseline: cat 54→56 (+2 ✅), ls 56→54 (−2 ⚠️), aura_self 55→51 (−4 ⚠️) — 모두 stop 임계 −5 pt 이내. mean total Δ: cat +41.57 / ls +19.14 / aura_self −8.0 (n=1 sparse). userland coverage: cat 85/85, ls 299/301, aura_self 1125/1134. Tasks.md D-T `[x]` + 통계 13/13 갱신. Phase 2-D umbrella `[-]` 유지 = G-D 판정 사용자 후속 결정 (Rule 9 조건 4 Open Decision 미해소). plan: `~/.claude/plans/linked-jumping-rose.md`. | G-D 판정 (사용자 결정 대기) → Phase 2-D `[x]` 승격 → v2.3.0 final tag 결정 | 없음 |
| 2026-04-25 | **Session #19 — ls spot-check + G-D Pass + Phase 2-D `[x]` 승격 + v2.3.0 final tag (Option A)**: D-T ls −2 covered_avg 의 원인을 분류하기 위해 `tests/results/v2_3_0_rc6_covered_avg/ls/{delta.json,parity.json}` + baseline `tests/results/phase_f_step3_f1g/ls/parity.json` 를 ad-hoc Python 분석. 결과: timeout 가설 기각 (baseline `aura_timeouts=3` → rc6 `=2` 오히려 −1), 회귀 123 함수 모두 real component regression (cur>0, base>0), mem 97 함수 / ctrl 77 함수 음수가 driver. 그러나 dominant 원인 = **coverage expansion artifact** — baseline covered=186/301 (61.8%) → rc6 covered=299/301 (99.3%), +113 함수 신규 decompile, 점수 합 ≈10,416 → ≈16,146 (**+5,730, +55%**), 신규 covered 함수 평균 ≈50.7 < baseline 평균 56 → avg 56→54 희석. 공통 점수 함수 n=189 의 mem mean −1.39 / ctrl mean −0.78 small drift 는 v2.4 추적 항목 TRACK-1 (component drift 진단) / TRACK-2 (회귀 top 10 샘플 디컴파일 비교) 으로 이관. 보고서: `tests/results/v2_3_0_rc6_covered_avg/ls_regression_spotcheck.md` 신규. **사용자 G-D 판정 = Pass (Recommended)** → Phase 2-D umbrella `[x]` 승격. **사용자 final tag 결정 = Option A 즉시 발행** → v2.3.0 umbrella `[x]` released. aura-acceptance-rule Rule 9 조건 1-4 충족 (필수 sub-phase 3 (2-A/2-B/2-D) `[x]` + 종합 테스트 ctest 185/185 GREEN + 문서 갱신 + 차단 Open Decision 없음). Tasks.md L19 버전 / L20 현재 페이즈 / L28 마지막 업데이트 / L75 v2.3.0 헤더 + Current state / L126 Phase 2-D 헤더 / L134 D-T 엔트리 / L136 Decision gate G-D / L290 통계 / L316~ 핸드오프 + summary.md G-D 섹션 + AUTOMATION_ROADMAP.md Session #19 항목 + CHANGELOG.md `## v2.3.0` 섹션 (released, G-D Pass, TRACK-1/2 이관) 갱신. 코드 변경 0 — pure governance + analysis. plan: `~/.claude/plans/2-3-iterative-kazoo.md`. | Stage B/C/D 실행 (commit + push + PR + merge to main + tag `v2.3.0` + GitHub Release). 다음 페이즈 = v2.4.0 (additive) 또는 v2.5.0 (breaking) 사용자 결정. | 없음 |
| 2026-04-25 | **Session #20 — v2.4+ → v3.0+ Reservoir reorg**: v2.3.0 출하 직후 사용자 두 번째 거버넌스 결정 — v2.4.0 (35) + v2.5.0 (5) 의 모든 기획 항목을 단일 v3.0+ Reservoir 섹션으로 이전. **방향성의 초석 / 잔해 보존**, 즉시 실행 금지. Reservoir 구조: Subsection A (code-on-main, released as part of v2.3.0) = Phase 2-X 11 PR + 2 follow-up + H-SW-1 = 13 `[x]` entry 머지 anchor 보존, 재실행 금지. Subsection B (pending, no execution) = 2.4-C 7 + 2.4-E 5 + 2.4-F 7 + 2.4-H 6 (H-SW-2 + H-FU + NH) + 2.4-X pending 2 (Stage 3-5 + 2-X-8) + 2.4-T 1 + 2.5-G 5 = 27 `[ ]` entry, 사용자 picking 대기. 새 v2.4.0 = TBD 빈 placeholder, "한 task 씩 결정". Phase prefix (2.4-C / 2.5-G 등) 현행 유지 (commit / plan / MASTER_ROADMAP cross-reference 안정성). 갱신: Tasks.md L19 버전 / L20 현재 페이즈 / L28 마지막 업데이트 / L81 Current state / L142~ v3.0+ Reservoir 섹션 신설 + B.1~B.7 demote / 통계 표 v2.4/v2.5 → v3.0+ Reservoir 재분할 + v2.4.0 0 placeholder + 본 핸드오프 행 + PRD.md D-19/D-20/D-22 갱신 + D-23 신규 + §8 갱신 + CHANGELOG.md ## v2.4.0 + ## v2.5.0 placeholder → ## v3.0+ Reservoir 통합 + 새 ## v2.4.0 — TBD + AUTOMATION_ROADMAP.md Session #20 항목. 코드 변경 0 (governance only, src/ tests/ diff 0). ctest 영향 0. v2.3.0 tag (`1b12e6c`) 그대로. plan: `~/.claude/plans/2-3-iterative-kazoo.md` (사용자 승인). | 사용자가 reservoir Subsection B 27 entry 중 picking 또는 신규 task 정의 → 새 v2.4.0 첫 task 결정. picking 후 별도 plan 으로 정식 진입. | 없음 |
| 2026-04-25 | **Session #21 — v2.4.0 Phase 2.4-TP picking + TP-1 시작**: 사용자 결정 "v2.4 = 타입 전파 기능 구현 + 모든 작업 PR 기반". 빈 v2.4.0 placeholder → 5 entry 정식 등록 (TP-1 ~ TP-4 sub-task + wrap). Reservoir B.2 E-4 / B.4 H-FU-3 = TP-3 으로 흡수 (재실행 금지, cross-ref 만 보존). plan: `~/.claude/plans/2-3-iterative-kazoo.md` (사용자 승인). **TP-1 in progress**: `tc_infer_types` 기본 path 통합 — 신규 `src/decompiler/type_dispatch.c` (~85 LOC) + `aura_type_infer_dispatch()` shim + `AuraTypeEngine` enum + env kill-switch `AURA_TYPE_ENGINE=heuristic\|tc\|both` (default=tc). 4 production call site 교체 (`pipeline.c:1204` / `main_window.cpp:1506` / `file_loader.cpp:301` / `test_llm_integration.c:274`). RED test 신규 `tests/decompiler/test_tc_default_path.c` (~250 LOC, 8 test) 8/8 GREEN. `stage=type_infer` log 마커 dispatcher 로 마이그레이션 (engine-agnostic, `test_stage_logs` 보존). ctest build-rel **187/187 GREEN** (185 baseline + test_tc_default_path 1 신규 + 1 auto-count). branch `phase-2.4tp/t1-tc-default` 생성, PR open 대기 (Stage 0 governance + Stage 1 T-1 단일 PR). | TP-1 PR open + squash merge to main → TP-4 (HIR emit hardening) 또는 TP-2 (DWARF/PDB seed) 사용자 picking | 없음 |
