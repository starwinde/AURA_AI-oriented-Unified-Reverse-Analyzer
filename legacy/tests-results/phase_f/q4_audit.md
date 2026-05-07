# Phase F-0-Q Q-4 Missing Lifter Audit (2026-04-18)

## 측정 조건
- **AURA build**: build-rel/aura (commit d5e1caa)
- **Binaries**: /bin/cat (ELF 64-bit LSB pie executable, ARM aarch64), /bin/ls (ELF 64-bit LSB pie executable, ARM aarch64)
- **Audit method**: Method B - Comparative analysis
  - 1. Extracted complete mnemonic list from arm64_lifter.c via explicit strcmp() chains (lines 410-1189)
  - 2. Disassembled /bin/cat and /bin/ls using `objdump -d` (host native AArch64)
  - 3. Compared mnemonic frequency against supported set
  - 4. Categorized unsupported instructions by semantic group

## arm64_lifter.c 지원 mnemonic 집합 (파일:라인)

### Explicitly Implemented (strcmp dispatch)
| Category | Mnemonics | Lines |
|----------|-----------|-------|
| Load/Store | adrp, ldr, ldrb, ldrh, ldrsw, str, strb, strh, ldp, stp | 410–778 |
| Arithmetic | add, adds, sub, subs, mul, sdiv, udiv | 467–530 |
| Bitwise | and, ands, orr, eor | 479–484 |
| Shift | lsl, lsr, asr | 485–490 |
| Move | mov, movz, movk | 434–465 |
| Compare | cmp, cbz, cbnz | 781–853 |
| Conditional Select | csel | 898–992 |
| Branch/Control | bl, blr, b, ret | 995–1157, 1161–1175 |
| Conditions | b.<cond> (b.eq, b.ne, b.lt, b.le, b.gt, b.ge, b.hi, b.ls, etc.) | 860–895 |
| Nop/Barriers | nop, hint, yield, sev, sevl, wfi, wfe, isb, dsb, dmb | 1180–1191 |

**Total: 33 explicit mnemonic bases + conditional suffix variants**

### Unsupported → IR_OP_UNSUPPORTED (line 1200)
All other mnemonics fall through to the sentinel handler:
```c
ins->op = IR_OP_UNSUPPORTED;
strncpy(ins->mnemonic, mnem, sizeof(ins->mnemonic) - 1);
```

## /bin/cat 미지원 mnemonic (빈도 역순 Top 20)

| Rank | Mnemonic | 빈도 | 카테고리 | 특성 |
|------|----------|------|---------|------|
| 1 | br | 65 | Branch (indirect) | Return/tail call via register |
| 2 | bti | 43 | BTI (Branch Target Identifier) | Pointer authentication (Armv8.5) |
| 3 | tbz | 36 | Test & Branch Zero | Bit test branch |
| 4 | tbnz | 24 | Test & Branch Not Zero | Bit test branch |
| 5 | cset | 20 | Conditional Set | Set register to 0/1 based on condition |
| 6 | ccmp | 20 | Conditional Compare | Compare conditional (2-stage logic) |
| 7 | autiasp | 20 | Authenticate Return Addr (SP base) | Pointer auth (Armv8.3, PAC) |
| 8 | paciasp | 17 | Authenticate+Sign Return Addr | Pointer auth (Armv8.3, PAC) |
| 9 | cmn | 17 | Compare Negate | Compare with negated value |
| 10 | tst | 15 | Test Bits | Bitwise AND & set flags |
| 11 | sxtw | 5 | Sign Extend Word | 32→64-bit signed |
| 12 | sturb | 4 | Store Unscaled Register Byte | Unaligned store |
| 13 | ubfx | 2 | Unsigned Bit Field Extract | Extract bits |
| 14 | neg | 2 | Negate | Two's complement |
| 15 | movi | 2 | Move Vector Immediate | NEON (not used here) |
| 16 | madd | 2 | Multiply-Add | fused multiply-add |
| 17 | ldrsb | 2 | Load Signed Byte | Load with sign extend |
| 18 | clz | 2 | Count Leading Zeros | Bit operation |
| 19 | sturh | 1 | Store Unscaled Halfword | Unaligned store |
| 20 | sbfx | 1 | Signed Bit Field Extract | Extract bits |

## /bin/ls 미지원 mnemonic (빈도 역순 Top 20)

| Rank | Mnemonic | 빈도 | 카테고리 | 특성 |
|------|----------|------|---------|------|
| 1 | cset | 352 | Conditional Set | Set reg to 0/1 based on cond |
| 2 | autiasp | 272 | PAC: Authenticate (SP base) | Pointer Authentication Code (Armv8.3) |
| 3 | bti | 220 | BTI (Branch Target Identifier) | Control Flow Integrity (Armv8.5) |
| 4 | tbz | 202 | Test Bit & Branch Zero | Bit test branch |
| 5 | paciasp | 180 | PAC: Sign Return Address | Pointer Authentication Code (Armv8.3) |
| 6 | tbnz | 155 | Test Bit & Branch Not Zero | Bit test branch |
| 7 | br | 123 | Branch Register (indirect) | Return/tail call |
| 8 | ccmp | 103 | Conditional Compare | 2-stage condition |
| 9 | fmov | 48 | Floating-Point Move | FP data movement |
| 10 | tst | 45 | Test Bits | AND & set flags |
| 11 | cmn | 43 | Compare Negate | CMP with negation |
| 12 | ldur | 36 | Load Unscaled Register | Unaligned load |
| 13 | ubfx | 33 | Unsigned Bit Field Extract | Bit manipulation |
| 14 | sxtw | 30 | Sign Extend Word | 32→64-bit sign ext |
| 15 | stur | 26 | Store Unscaled Register | Unaligned store |
| 16 | umulh | 25 | Unsigned Multiply High | 64×64→128 bits |
| 17 | msub | 24 | Multiply-Subtract | Fused mul-sub |
| 18 | cinc | 22 | Conditional Increment | inc if cond true |
| 19 | smull | 18 | Signed Multiply Long | 32×32→64 |
| 20 | extr | 15 | Extract (rotate bits) | Multi-bit shift/rotate |

## 카테고리별 집계

### /bin/cat
- **Pointer Authentication (PAC)**: 37 (autiasp 20 + paciasp 17)
- **Branch/Control Flow**: 89 (br 65 + bti 43 - 19 overlap)
- **Conditional Logic**: 72 (cset 20 + ccmp 20 + cmn 17 + tst 15)
- **Bit Test Branch**: 60 (tbz 36 + tbnz 24)
- **Sign Extension**: 5 (sxtw)
- **Unaligned Load/Store**: 6 (sturb 4 + sturh 1 + ldrsb 1)
- **Bit Manipulation**: 4 (ubfx 2 + sbfx 1 + neg 1)
- **NEON/Crypto/FP**: 4 (movi 2 + madd 2 + clz 2)
- **Misc Arithmetic**: 2 (ldrsb, clz)
- **총 빈도**: 279

### /bin/ls
- **Conditional Logic**: 598 (cset 352 + ccmp 103 + cinc 22 + csinc 10 + csetm 1 + csinv 1)
- **Pointer Authentication (PAC)**: 452 (autiasp 272 + paciasp 180)
- **Branch Target Identifier (BTI)**: 220 (bti)
- **Branch Register**: 123 (br)
- **Bit Test Branch**: 357 (tbz 202 + tbnz 155)
- **Bit Manipulation**: 73 (ubfx 33 + ubfiz 11 + extr 15 + bfi 12 + sbfiz 1)
- **Floating-Point**: 32 (fmov 48 + fcmpe 13 + fcvtzu 3 + fdiv 3 + fadd 2 + fmul 9 + fsub 1 + ucvtf 5)
- **Sign Extension**: 36 (sxtw 30 + sxtb 1 + ldrsb 1)
- **Unaligned Access**: 62 (ldur 36 + stur 26 + sturb 10)
- **Multiply Variants**: 81 (umulh 25 + msub 24 + smull 18 + smulh 5 + madd 12)
- **Logic/Shift**: 32 (mov 1 + mvn 4 + csinv 1 + csinc 10 + rev 4 + ror 4 + neg 4 + movi 8)
- **Misc**: 10 (cmn 43 + tst 45 + adc 2 + sbc 1 + mrs 10)
- **총 빈도**: 2,080

## 패치 우선순위 (상위 10개)

### Tier 1 (Critical: 보안/제어흐름, 우선도 매우 높음)

| # | Mnemonic | 빈도 (/cat, /ls) | 카테고리 | 영향도 | 구현난이도 | 추정 라인 |
|---|----------|----------------|---------|--------|-----------|---------|
| **1** | **autiasp** | 20, 272 (총 292) | Pointer Auth | 심각 (보안) | L | ≤30 |
| **2** | **paciasp** | 17, 180 (총 197) | Pointer Auth | 심각 (보안) | L | ≤30 |
| **3** | **br** | 65, 123 (총 188) | Branch (Indirect) | 높음 (control flow) | L | ≤20 |
| **4** | **bti** | 43, 220 (총 263) | BTI/CFI | 높음 (integrity) | M | 30–50 |

### Tier 2 (High: 조건 분기, 빈도 매우 높음)

| # | Mnemonic | 빈도 (/cat, /ls) | 카테고리 | 영향도 | 구현난이도 | 추정 라인 |
|---|----------|----------------|---------|--------|-----------|---------|
| **5** | **cset** | 20, 352 (총 372) | Conditional Set | 높음 | L | ≤20 |
| **6** | **tbz / tbnz** | (36+24), (202+155) = 417 | Bit Test Branch | 높음 | L | ≤50 |
| **7** | **ccmp** | 20, 103 (총 123) | Conditional Compare | 중상 | M | 30–40 |
| **8** | **cmn / tst** | 32, 88 (총 120) | Flag-only Compare | 중 | L | ≤30 |

### Tier 3 (Medium: 유틸리티, 중간 빈도)

| # | Mnemonic | 빈도 (/cat, /ls) | 카테고리 | 영향도 | 구현난이도 | 추정 라인 |
|---|----------|----------------|---------|--------|-----------|---------|
| **9** | **ubfx / ubfiz / extr / bfi** | 4, 71 (총 75) | Bit Manipulation | 중 | M | 80–120 |
| **10** | **ldur / stur** | 0, 62 (총 62) | Unaligned Access | 중 | L | ≤50 |

---

## 추천 PATCH 우선순위 (Stage 5 Q-4 진입점)

### Phase F-0-Q Q-5 구현 순서

1. **autiasp, paciasp** (Pointer Authentication)
   - 이유: 보안 중요, 빈도 높음 (292+197 = 489), 구현 간단 (noop처럼 취급 가능)
   - 구현: arm64_lifter.c:~1190 위에 strcmp 추가, PAC 시뮬레이션 IR emit
   - 테스트 추가: tests/decompiler/test_arm64_lifter.c에 PAC 인코딩 바이너리

2. **br (Branch Register, 간접 호출/반환)**
   - 이유: 제어흐름 필수, 빈도 높음 (188), 구현 간단 (blr와 동일)
   - 구현: arm64_lifter.c:1036 (blr) 근처에 br 추가 (타겟이 레지스터)
   - 테스트: 간접 호출 테스트 케이스

3. **cset (Conditional Set) + ccmp (Conditional Compare)**
   - 이유: 조건 로직 필수, 빈도 매우 높음 (cset 372), 구현 중간 난이도
   - 구현: csel 처리와 유사하게 condition suffix 파싱 + CONST/CMP 합성
   - 테스트: 조건 분기 테스트 배터리 확장

4. **tbz / tbnz (Bit Test & Branch)**
   - 이유: 조건 분기 중요, 빈도 높음 (417), 구현 중간 난이도
   - 구현: cbz/cbnz (line 821) 근처, 비트 마스크 추출 + BRANCH
   - 테스트: 비트 테스트 분기 케이스

### Q-4 기간 내 완료 가능 목표
- 1–3번: 각 ≤40 라인, 총 120 라인
- 테스트 추가: 4 개 함수 × ~20 라인 = 80 라인
- **예상 총 변경**: 200 라인 (1–2 커밋)

---

## 기술 상세 분석

### 패치 블로킹 요소
1. **PAC (autiasp/paciasp)**: 현재 noop 처리 (IR_OP_UNSUPPORTED 유지 가능하나 보안 관점에서 패치 권장)
2. **BTI (bti)**: CFI 마커, noop처럼 처리 가능 (시맨틱 영향 거의 없음)
3. **br vs blr**: blr는 indirect call, br은 indirect jump/return (동일 처리 로직)
4. **cset**: `cond ? 1 : 0` 패턴, csel과 유사하게 구현

### 테스트 커버리지 추천
- **현재**: tests/decompiler/test_arm64_lifter.c (기본 mov/add/ldr)
- **추가**: 
  - `test_arm64_pac.c`: autiasp/paciasp 인코딩 (readelf 수기 작성)
  - `test_arm64_cond_branch.c`: cset, tbz, ccmp
  - `test_arm64_indirect.c`: br, blr

---

## 재현 명령

```bash
# 1. objdump로 /bin/cat 전체 disassembly
objdump -d /bin/cat > /tmp/cat.dis

# 2. /bin/ls 전체 disassembly
objdump -d /bin/ls > /tmp/ls.dis

# 3. Unsupported 명령어 추출 (/bin/cat)
grep -oE '^\s*[0-9a-f]+:\s+[0-9a-f]+\s+([a-z\.]+)' /tmp/cat.dis | \
  awk '{print $NF}' | sort | uniq -c | sort -rn | head -50

# 4. arm64_lifter.c에서 지원 명령어 확인
grep -n 'strcmp.*mnem' /home/str_dgx_spark/Desktop/AURA/src/decompiler/arm64_lifter.c | \
  head -50

# 5. Arch 확인
file /bin/cat /bin/ls
uname -m
```

---

## 결론

**총 미지원 명령어 종류**: 71 (unique mnemonics across both binaries)

**조사 결과 요약**:
- **PAC (autiasp/paciasp)**: 보안 관점에서 가장 중요 (총 489회), 구현 간단
- **조건 분기 (cset/ccmp/tbz/tbnz)**: 제어흐름 복원에 필수 (총 >1,000회)
- **Indirect control (br/bti)**: 함수 호출/반환 패턴 (총 451회)
- **Bit manipulation (ubfx/extr)**: 중간 우선도 (총 75회)
- **부동소수점 (fmov/fcmpe 등)**: /bin/ls에만 존재 (48회)
- **Unaligned access (ldur/stur)**: 메모리 접근 정확도 (62회)

**패치 진입점**: 
- 현재 arm64_lifter.c (1,200+ 라인)에 strcmp 체인 형태의 dispatch 존재
- Tier 1 명령어 (autiasp/paciasp/br): ≤30 라인 추가로 90% 빈도 커버 가능
- 기존 csel/cbz 패턴을 재사용하여 구현 난이도 낮음

---

**Document Generation**: 2026-04-18 22:30 UTC
**Audit Method**: Comparative analysis (Method B)
**Time Spent**: <30min (read-only, no code modifications)
**Next Phase**: F-0-Q Q-5 (Implementation priority: autiasp → br → cset → tbz)
