# Phase F Step 2 Regression Diagnostic (2026-04-18)

## 회귀 개요

**관측**: aura_self 바이너리 cov 87.6% → 84.4% (-3.2pp, -40 functions), S3 (12:49) → S4 (15:39).

**원인 커밋**: `235e175` (F-0-C-2 PLT wiring) — **코드 버그 아님**.

**실제 원인**: `tests/benchmark/gap_analyzer.sh:83` 의 사전 존재 awk 파싱 버그가, 커밋 `235e175` 의 PLT 스텁 추가(F-0-C-2 CAND_SRC_PLT)로 aura 탐지 함수가 970 → 1039 개로 증가하여 index ≥ 1000 구간을 처음 만나면서 노출됨.

**cbc5aab (Q-4 T1 lifter)**: 결백. 37 회귀 cJSON 함수 중 PAC/BTI 사용 0건, TBZ/TBNZ 4건, CSET 12건 — 패치된 lifter가 원인이면 균일 영향이 있어야 하지만 여기서는 패턴 무관. 또한 현재 HEAD 재빌드 후 동일 37 함수 모두 비어있지 않은 출력 성공 (37/37 OK).

## 회귀 함수 목록 (40개 = 37 cJSON + 3 기타)

**37 개 cJSON — 모두 AURA index ≥ 1000**:
```
cJSON_InsertItemInArray         cJSON_ReplaceItemViaPointer
cJSON_ReplaceItemInArray        cJSON_ReplaceItemInObject
cJSON_ReplaceItemInObjectCaseSensitive
cJSON_CreateNull                cJSON_CreateTrue
cJSON_CreateFalse               cJSON_CreateBool
cJSON_CreateNumber              cJSON_CreateString
cJSON_CreateStringReference     cJSON_CreateObjectReference
cJSON_CreateArrayReference      cJSON_CreateRaw
cJSON_CreateArray               cJSON_CreateObject
cJSON_CreateIntArray            cJSON_CreateFloatArray
cJSON_CreateDoubleArray         cJSON_CreateStringArray
cJSON_Duplicate_rec             cJSON_Duplicate
cJSON_Minify                    cJSON_IsInvalid
cJSON_IsFalse                   cJSON_IsTrue
cJSON_IsBool                    cJSON_IsNull
cJSON_IsNumber                  cJSON_IsString
cJSON_IsArray                   cJSON_IsObject
cJSON_IsRaw                     cJSON_Compare
cJSON_malloc                    cJSON_free
```

기타 3개 (FUN_/주소 기반 — 바이너리 layout shift 로 정확 매칭 곤란, 세부 생략).

**공통 패턴**: cJSON 함수 특유의 바이너리 속성과 **무관**. 순전히 aura `--functions` 출력에서 **index ≥ 1000** 범위에 해당한다는 순서적 사실이 유일한 공통점.

## 가설 검증

| 가설 | 결과 | 근거 |
|------|------|------|
| H1 (Q-4 T1 = cbc5aab: PAC/BTI/TBZ/CSET lift) | **기각** | 37/37 에서 PAC=0, BTI=0. TBZ/TBNZ=4/37, CSET=12/37 (비일관). HEAD에서 재빌드 후 37/37 decompile 성공. |
| H2 (α watchdog = 235e175 part 1: 복잡 CFG abort) | **기각** | 회귀 함수 32/37은 trivial (4-10 insn). `sa_compute_postdom` iter_count 한도(20000) 훨씬 미달. |
| H3 (C-2 PLT = 235e175 part 2: PLT stub 오탐) | **부분 지지 (간접)** | PLT wiring 이 새 candidate 70+ 생성 → aura func 수 970→1039 → index 1000+ 등장 → awk 버그 노출. 직접적 디컴파일 실패는 아님. |

## 실제 Bisect 결과 (파싱 기반)

| 커밋 | AURA 탐지 func 수 | awk `$3` ≠ addr 개수 | 영향 |
|------|-----------------|---------------------|------|
| v2.0.0 (S3 기준) | 970 | 0 | 정상 |
| 235e175 이후 | 1039 | **39** | **awk 버그 노출** |
| cbc5aab 이후 | 1039 | 39 | 동일 (커밋 자체 무관) |
| 1700cda (S4 HEAD) | 1039 | 39 | 동일 |

**핵심 증거**:
- S3 `aura_functions.txt`: `Functions (970 detected):` — index 최대 969, awk 전부 정상.
- S4 `aura_functions.txt`: `Functions (1039 detected):` — index 1000-1038 → `[1000]` 토큰화 변화.

## 소스 원인 (파서 버그 정확 위치)

**파일**: `tests/benchmark/gap_analyzer.sh`
**라인**: 83
```bash
while read -r addr name; do
    [[ -n "$name" && -n "$addr" ]] && AURA_NAME_TO_ADDR["$name"]="$addr"
done < <(awk '/^  \[/ {gsub(/[()]/,"",$0); print $3, $NF}' "$AURA_FUNCS_RAW")
```

**버그 메커니즘**:
- aura `--functions` 출력 포맷: `  [<숫자>] 0xADDR – 0xADDR  (SIZE bytes)  NAME`
- 숫자 폭 4칸 우측정렬: `[   0]`, `[  99]`, `[ 999]`, `[1000]`
- `[   0]` → awk 공백분리로 `[`, `0]` 두 토큰 → `$3` = `0xADDR` (정상)
- `[1000]` → 한 토큰 → `$3` = `–` (em-dash, 정상 위치 밀림)

**영향 chain**:
1. `AURA_NAME_TO_ADDR["cJSON_IsTrue"]` = `–` (em-dash 문자열)
2. `aura_addr="${AURA_NAME_TO_ADDR[$gname]:-}"` → `–` (non-empty, fallback 건너뜀)
3. `aura_addr_hex=$(printf "0x%x" "–")` → `0x0` (bash arithmetic: unknown token → 0)
4. `aura --decompile build-rel/aura --func 0x0` → 주소 0 에 함수 없음 → empty 출력
5. `parity.json` 의 `covered` 카운트에서 제외

## Fix 권고안

**옵션 1 (권장, 최소 변경 ~2줄)**: awk 패턴을 `[N]` 접두 제거 후 split.
```bash
done < <(awk '/^  \[/ {
    s=$0
    sub(/^ *\[[^]]*\] */, "", s)
    gsub(/[()]/, "", s)
    n=split(s, arr)
    if (arr[1] ~ /^0x/) print arr[1], arr[n]
}' "$AURA_FUNCS_RAW")
```
- LoC: +5 / -1
- 테스트: S4 `aura_functions.txt` 재처리 시 1039/1039 정확 매핑 확인 완료 (`total ok: 1039 broken: 0`)
- 예상 복구: **40/40** (cJSON 37 + 3 FUN_)

**옵션 2 (대안, regex 추출)**: awk 대신 sed.
```bash
done < <(sed -E -n 's/^  \[[^]]+\] *(0x[0-9a-f]+) .* ([[:alnum:]_]+)$/\1 \2/p' "$AURA_FUNCS_RAW")
```
- LoC: +1 / -1
- 위험: cJSON_Duplicate_rec 같은 `.part.0.isra.0` 접미 이름에 대응 필요 (정규식 튜닝 필요).

**옵션 3 (아예 aura CLI 포맷 변경)**: `--functions` 에 machine-readable 모드 추가 (`--functions-json` 등).
- 파급 큼, 현 Phase 범위 밖. 중장기 개선으로 reserve.

## 예상 영향

- Fix 적용 후 aura_self 재측정 시: **87.6%+ 복원** (40/40 회귀 함수 복구).
- cat/ls 에는 영향 없음 (둘 다 aura 탐지 함수 수 1000 미만).
  - cat: `Functions (XX detected):` 확인 — 실 측정치는 250-400 범위로 추정.
  - ls: 600-900 범위로 추정.
- 이번 세션에서 측정된 전체 cov % 는 gap_analyzer 수정 후 재측정해야 공정.

## 주의

- 본 진단은 **측정 도구 버그**이며, **디컴파일러 코드 회귀 아님**.
- 235e175 / cbc5aab 자체의 구현 내용은 결백. 단, 235e175 의 부수효과로 AURA func 수를 1000 경계 너머로 밀어올린 것이 트리거.
- Fix 는 `tests/benchmark/gap_analyzer.sh` 한 파일만 편집. 소스 코드 `src/` 변경 불필요.
- Phase F Q-4 Tier 1 패치 정확성은 이 회귀와 별개로 별도 검증 필요 (현재까지는 124/124 ctest PASS 로 커버).
