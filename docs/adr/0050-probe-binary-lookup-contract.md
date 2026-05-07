# ADR-0050 — Phase 2.5.2 Probe binary lookup contract (env → vendored → PATH)

- **Status**: Accepted (closeout)
- **Date**: 2026-05-05
- **Related**: ADR-0049 (subprocess runner), ADR-0031 (reference engine
  policy), ADR-0032 (external tool acquisition pattern), rules.md §1
  (cross-platform subprocess guard).
  Code: [src/engine/probe/engine_probe.{h,c}](../../src/engine/probe/engine_probe.c),
  [src/cli/main.cpp](../../src/cli/main.cpp) `run_probe_engines`,
  [tests/unit/probe/probe_unit.cpp](../../tests/unit/probe/probe_unit.cpp).
  Phase 2.5.2 commits `e24c984b`, `caeb9413`, `6722a602`.

## Context

Phase 2.5 코어 의 5 probe 함수 (rizin / ghidra-decomp / ghidra-full / angr /
retdec) 는 도구를 PATH 의 단순 이름 (`"rizin"`, `"java"`, `"python3"`, ...) 으로만
spawn 시도. 두 가지 자기-모순 발생:

**모순 1 — CLI ↔ probe 불일치**
CLI `build_orchestrator` (`src/cli/main.cpp:96-103`) 는 ANALYZE/DISASM 등
실행 경로에 `--rizin` flag + `AURA_RIZIN_BIN` env var 우선 인식. 같은 사용자가
- `aura analyze foo.exe` → AURA_RIZIN_BIN 통해 성공 ✅
- `aura --probe-engines` → "rizin ENGINE_MISSING" ❌

같은 binary 인데 두 명령이 다른 verdict.

**모순 2 — install_hint ↔ probe 불일치**
ENGINE_MISSING 시 emit 되는 install_hint:
```
"expected at third_party/ghidra-decomp/bin/ghidra-decomp
 (run scripts/bootstrap_ghidra_decomp.{sh,ps1})"
```
사용자가 안내대로 `third_party/ghidra-decomp/` 에 bootstrap 해도 → probe 가
그 위치를 안 봄 → 여전히 ENGINE_MISSING. **rules.md §1 자기-일관성 강제 위반**.

Phase 2.5.2 가 두 모순을 동시에 해소하는 lookup contract 을 도입.

## Decisions

### D1 — 단일 헬퍼 `aura_probe_resolve_binary` 도입

```c
int aura_probe_resolve_binary(
    const char *env_var,        /* "AURA_RIZIN_BIN" 등, NULL 가능 */
    const char *vendored_rel,   /* "third_party/rizin/0.8.0-shared/.../bin/rizin" 등 */
    const char *default_name,   /* "rizin" — PATH fallback, 필수 */
    char       *out_buf,
    size_t      out_cap);
```

3-tier 우선순위 (return 값 1/2/3 으로 어느 tier 가 win 했는지 통보):
1. **env var override** — 사용자가 `AURA_RIZIN_BIN=/opt/rizin` 설정 시 무조건
   그 값 사용. stat() 검증 안 함 (사용자 explicit choice 는 명확 에러로
   surface 되어야 함, silent fallback 금지).
2. **vendored repo path** — `AURA_REPO_ROOT` env 가 가리키는 디렉토리 +
   `vendored_rel` 결합. `stat()` 으로 파일 존재 확인 후 사용. 부재 시 silent
   skip (PATH fallback 진행).
3. **PATH default** — `default_name` 을 그대로 spawn (OS PATH resolution).

### D2 — Env var 이름 체계

| Engine | Env var | Vendored path (POSIX / Windows) |
|--------|---------|----------------------------------|
| rizin | `AURA_RIZIN_BIN` (기존) | `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin{,.exe}` |
| ghidra-decomp | `AURA_GHIDRA_DECOMP_BIN` (신규) | `third_party/ghidra-decomp/bin/ghidra-decomp{,.exe}` |
| ghidra-full / java | `AURA_JAVA_BIN` (신규) | `(none)` — JRE 는 host 의존 |
| ghidra-full / analyzeHeadless | `AURA_GHIDRA_FULL_ANALYZE_HEADLESS` (신규) | `third_party/ghidra-full/support/analyzeHeadless{,.bat}` |
| angr / python | `AURA_ANGR_PYTHON_BIN` (신규) | `third_party/angr/venv/{bin,Scripts}/python{,.exe}` |
| retdec | `AURA_RETDEC_DECOMPILER_BIN` (신규) | `third_party/retdec/bin/retdec-decompiler{,.exe}` |

Vendored path 는 cross-platform `#ifdef _WIN32` 분기로 .exe / .bat suffix 처리
(rules.md §1 cross-platform 가드 준수).

> **2026-05-06 기준 보강**: ADR-0052 에 따라 Rizin vendored tier 는
> `0.8.0-shared` shared64 bundle 을 기준으로 한다. 이 기준은
> `SLEIGHHOME=third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/lib/rizin/plugins/rz_ghidra_sleigh`
> 와 함께 적용되어야 rz-ghidra `pdgj` pseudo-C 경로가 안정적으로 동작한다.

### D3 — angr 의 fallback chain 보존 + override 우선

angr 는 cross-platform Python interpreter 이름 차이 (POSIX `python3` /
Windows `python`) 때문에 기존 Phase 2.5.1 X.1 에서 fallback chain 도입.
Phase 2.5.2 통합:

```
hit = aura_probe_resolve_binary(env, vendored, default_first, ...)
if hit == 1 OR hit == 2:
    /* env 또는 vendored — 단일 시도, fallback chain 우회.
     * 사용자/repo 의 explicit choice 는 명확한 실패로 보고. */
    runner->run(resolved_path, ...)
else:
    /* PATH fallback — OS-preferred name 부터 alternate 까지 chain */
    for candidate in {python3, python} (POSIX) or {python, python3} (Windows):
        runner->run(candidate, ...)
        if rc == 0: break
```

### D4 — `AURA_REPO_ROOT` 자동 seed (production CLI path)

Probe library 의 resolver 는 `AURA_REPO_ROOT` env 가 set 되어야 vendored tier
도달. 사용자가 `aura --probe-engines` 직접 실행할 때 env var 미설정 시 vendored
무용지물. Codex review #4 high #1 응답:

`run_probe_engines` (CLI handler) 가 probe 호출 직전 `AURA_REPO_ROOT` seed:
```c
const char *cur = std::getenv("AURA_REPO_ROOT");
if (!cur || !*cur) {  // unset OR empty — 둘 다 seed 대상 (review #5 high)
    static std::string root = repo_root_for_cli();
    setenv("AURA_REPO_ROOT", root.c_str(), 1);  /* POSIX */
    /* Windows: _putenv_s */
}
```

`repo_root_for_cli()` 헬퍼 (기존 `aura engines` 명령에서 사용) 재활용. 사용자가
이미 non-empty 값으로 export 한 경우 보존.

### D5 — 회귀 테스트: resolver + per-probe env + per-probe vendored

`probe_unit.cpp` 에 18 신규 테스트 (X.8 + X.8.1):

**Resolver helper** (4 cases):
- env override wins (rc=1)
- empty env → PATH default (rc=3)
- vendored present → rc=2
- vendored absent → rc=3

**Per-probe env override** (5 cases, 1 per engine):
- FakeRunner 가 explicit overridden absolute path 만 script. 회귀로 PATH 만
  시도하면 unscript 호출 → ENGINE_MISSING 으로 catch.

**Per-probe vendored path** (5 cases, 1 per engine):
- `VendoredRoot` RAII 가 temp dir 에 expected file 생성 + AURA_REPO_ROOT 세팅.
- FakeRunner 가 absolute resolved path 만 script. 회귀로 vendored 우회하면
  ENGINE_MISSING 으로 catch.

**Cross-platform path normalization**: `std::filesystem::path::generic_string()`
사용 (forward slash 통일). resolver 는 `snprintf("%s/%s")` 로 forward slash
출력. Windows 의 native `\` 형태와 mismatch 방지.

**ScopedEnv RAII**: 테스트 격리 — env 변경 후 destructor 가 이전 값 복원
또는 unset.

## Out of scope

1. **install_hint 메시지 갱신** — 현재 hint 는 vendored 경로만 안내. env var
   옵션 (예: "또는 `AURA_RIZIN_BIN=/path/to/rizin` 설정") 추가는 별도
   enhancement (Phase 2.5.3 X.9 후보, ~30 줄).
2. **CLI 의 ANALYZE/DISASM dispatch path 통일** — 현재 CLI build_orchestrator
   의 lookup 은 별도 (rizin 만 cover). probe resolver 와 합치는 작업은 별도
   ADR (CLI orchestrator refactor) 필요.
3. **Vendored binary stat() vs runtime probe** — 현재 vendored 가 file 존재만
   확인하고 실행 가능성/architecture 검증 없음. 잘못된 binary (예: ARM 이
   vendored 됐는데 host 가 x86) 는 spawn 실패로 surface — 충분.
4. **Symlink/junction 처리** — POSIX symlink 는 `stat()` 가 자동 follow.
   Windows junction/symlink 는 별도 검증 안 함.
5. **CI smoke under non-ASCII repo path** — Codex review #6 medium. Phase 9
   platform coverage 에서 처리.

## Verification

`probe_unit` 58 cases / 248 assertions GREEN (양 OS).
End-to-end `aura --probe-engines` 실행 결과 envelope JSON 정확:
```json
{"aura_schema":1,"command":"probe-engines","body":{"engines":[
  {"engine_id":"rizin","status":"ENGINE_MISSING",...},
  ...
]}}
```

Codex 5-round review (review #3~#6) 모든 HIGH finding 닫힘. 최종 verdict
APPROVE.
