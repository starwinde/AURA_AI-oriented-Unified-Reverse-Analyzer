# x64dbg 분석 — AURA 교차 영역 한정

> Session #9 (2026-04-20), Task #33. x64dbg (GPL-3, https://github.com/x64dbg/x64dbg) 는 Windows 동적 debugger 로 AURA 정적 RE 와 scope 크게 다름.
> 본 문서는 AURA 에 참조 가치 있는 **4개 교차 영역** (pattern scan / PDB symbol / CLI / Disasm UX) 에만 집중하며 runtime debugger 기능(breakpoint, stepping, memory manipulation)은 의도적으로 제외한다.

---

## 1. Executive Summary

x64dbg 는 Microsoft Windows x86/x64 사용자-모드 동적 debugger 로, AURA 의 정적 RE 관심사와는 기본 축이 다르다. 그러나 x64dbg 코드베이스는 **4개 subsystem** 이 AURA 의 현재 혹은 향후 개선 목표와 정확히 겹친다:

1. **Pattern scanning** (`patternfind.cpp`) — byte-mask wildcard 포맷 + literal-first 최적화 loop. Ghidra `BulkPatternSearcher` 와 동일 목표를 훨씬 간결하게 구현한 실례.
2. **PDB / Symbol server 로더** (`symbolinfo.cpp`) — `msdl.microsoft.com/download/symbols` 프로토콜, 2-level cache 구조, partial lazy load.
3. **CLI / command dispatcher** (`command.cpp` + `commands/cmd-*.cpp`) — 카테고리별 파일 분리 + 중앙 registry (`cmd-all.h`), `cmdsplit`/`cmdexeccallback` 파이프라인, expression-evaluator fallback.
4. **Qt 기반 disassembly view** (`gui/Src/Disassembler/`) — `Zydis` (AURA 가 이미 확정) + `ZydisTokenizer` + `TokenColor` 체계. AURA Qt6 GUI 와 기술 스택 완전 일치.

**핵심 격차 3**: (a) AURA 는 runtime pattern DSL 이 전무 — x64dbg 의 `PatternByte{data,mask}` 2-byte 구조만 차용해도 즉시 scan 가능. (b) AURA PDB loader 는 local file 전용 — symbol server 자동 다운로드 없음. (c) AURA CLI 는 카테고리 파일 분리 안 됨 (`src/cli/decompile_all.c` 단일 파일) — x64dbg 의 `cmd-*` 패턴이 scale reference.

**단기 추천 3**: [S-x-1] `patternfind` 이식 (200 LOC, ~1 세션, +recall on known sigs) / [S-x-2] Symbol server client — libcurl 이미 의존 (~1-2 세션) / [S-x-3] ZydisTokenizer 이식 검토 (AURA disasm view 가 존재한다면, ~1 세션).

---

## 2. Scope 제한 정당화

### 2.1 AURA 와 x64dbg 의 기본 축 차이

| 축 | AURA | x64dbg |
|----|------|--------|
| 분석 대상 | static binary (ELF/PE/Mach-O) | running process (Windows) |
| 실행 시점 | offline | live attach/spawn |
| 분석 출력 | 디컴파일 / HIR / report | register state / stepping trace |
| OS scope | cross-platform | Windows only |
| 언어 | C11/C++17 | C++ (Windows API 강결합) |

→ breakpoint / stepping / thread control / DLL injection / anti-debug evasion 은 **AURA 에 이식 불가능하거나 가치 없음**. 동적 실행이 AURA 설계 원칙 밖.

### 2.2 교차 가치가 있는 4 영역 선정 근거

1. **Pattern scan**: Ghidra `BulkPatternSearcher` (#26 S-1/M-1) 와 Rizin zignatures (#30 Z-1) 의 세 번째 독립 구현 예시 — **triangulation 의 핵심**. YARA-유사 관심사가 세 도구에서 모두 나타나면 AURA 도입 정당성 강화.
2. **PDB loader**: AURA `src/parser/pdb_parser.c` 이미 존재 (Phase 3.12 complete). 그러나 symbol server 다운로드는 없음 → recall 개선 여지.
3. **CLI dispatcher**: AURA `build-rel/aura` CLI 가 E-3 `--decompile-all` 추가 중 (#25). 향후 command set 확장 시 `cmd-*.cpp` 분리 패턴 reference.
4. **Disassembly view UX**: AURA GUI 는 Qt6 확정 (D-1) + Zydis 확정 (D-x). x64dbg GUI 는 두 기술을 가장 오래 결합 운영 — UX pattern 가치 최고.

---

## 3. YARA-like Pattern Scanning

### 3.1 x64dbg 의 구현 (2-byte `PatternByte` 모델)

`src/dbg/patternfind.cpp` 가 핵심. 놀라울 만큼 단순하다:

```cpp
struct PatternByte {
    unsigned char data;   // actual byte value
    unsigned char mask;   // 0xFF = literal, 0x00 = wildcard
};

bool patterntransform(const string& patterntext,
                      vector<PatternByte>& pattern);

size_t patternfind(const unsigned char* data, size_t datasize,
                   const vector<PatternByte>& pattern);
```

**텍스트 포맷**:
- 16진 리터럴: `48 8B`
- 니블 wildcard: `4?` (상위 니블만 매칭)
- 바이트 wildcard: `??`
- 공백 stripped
- 제약: "reject wildcard only patterns" — 적어도 하나의 리터럴 바이트 필요.

**핵심 최적화**: 먼저 mask `0xFF` (fully literal) 바이트만 추출 → `std::find` 로 빠르게 anchor 위치를 찾음 → 그 지점에서 나머지 partially-masked 바이트 검증. x64dbg 주석: *"maximizing time inside std::find, minimizing time checking bytes."*

### 3.2 Command layer (`cmd-searching.cpp`)

- `cbInstrFind` — 단일 매치, `$result` 변수에 offset 저장.
- `cbInstrFindAll` — 영역 내 모든 매치, reference view 에 주소 + disasm 덤프. `maxFindResults=5000` 상한.
- `cbInstrFindAllMem` — 모듈 필터 (user/system/all) + `MemFindInMap()`. `&data&` 플래그로 raw hex 출력 vs disasm 출력 선택.
- `cbInstrFindAsm` — 명령어 니모닉 매칭 (assemble → mnemonic 추출 → code search).
- `cbRefFind` / `cbRefStr` / `cbRefFuncPtr` — 오퍼랜드 value range 참조 탐색.

이 command 들은 **expression 평가** (`$result` 변수) + **reference view** (GUI table) 와 통합되어 있어 AURA 에는 command 부분만 이식 대상.

### 3.3 Ghidra #26 / Rizin #30 과의 triangulation

| 축 | Ghidra (#26) | Rizin (#30) | x64dbg (#33) |
|----|--------------|-------------|-------------|
| Pattern encoding | XML DSL (`<data bits="10011000..."/>`) — **runtime** 로드 | FLIRT `.pat`/`.sig` bytes-CRC + zignatures key-value | C++ `PatternByte{data,mask}` 텍스트 → 벡터 |
| Wildcard 단위 | bit-level (XML `totalbits/postbits`) | byte-level + variable-bytes CRC | nibble-level (`4?`) + byte-level (`??`) |
| 외부화 가능 | ✅ XML runtime | ✅ sigdb dir | ❌ textual pattern at call site |
| Pre/post context | ✅ `<prepatterns>/<postpatterns>` | ❌ body-only | ❌ body-only |
| Normalization | `InstructionSkipper` per-processor | FLIRT CRC-based | 없음 |
| 현업 사용 | Ghidra 함수 탐지 핵심 | Rizin 기본 `aa` 기반 | 사용자 수동 탐색 도구 |

**발견**:
- 세 도구 모두 "wildcarded byte matching" 을 **공통 primitive** 로 가지고 있다 → AURA 에도 base primitive 로 도입 정당화.
- x64dbg 는 **단순함** (단일 파일, <300 LOC) 에서 가장 간결. Ghidra/Rizin 이식보다 AURA 가 먼저 x64dbg `patternfind.cpp` 를 이식하고, 이후 Ghidra 의 XML 외부화를 덧쓰는 것이 incremental 로드맵으로 합리적.
- Pre/post context (Ghidra M-1) 은 **x64dbg 에 없음** — x64dbg 는 runtime 사용자가 수동 스캔. AURA 가 자동 함수 탐지에 쓰려면 Ghidra 스타일의 pre/post 제약 필수 (x64dbg 단독으로는 불충분).

### 3.4 AURA 포팅 가능성 및 예상 +Δ

**[S-x-1] `patternfind` 이식** (1 세션, ~200 LOC `src/analysis/patternfind.c`):

```c
// AURA 스타일 C 구현
typedef struct {
    uint8_t data;
    uint8_t mask;
} aura_pattern_byte;

int aura_pattern_transform(const char* text, aura_pattern_byte** out, size_t* nout);
ssize_t aura_pattern_find(const uint8_t* data, size_t datasize,
                          const aura_pattern_byte* pat, size_t patlen);
```

- x64dbg 의 literal-first 최적화 그대로 이식.
- 즉시 `func_detect.c` 에서 hardcoded prologue 검사를 **외부 pattern 배열** 로 리팩터 가능.
- **예상 +Δ**: 단독으로는 +0 (행동 변화 없음), 그러나 S-x-1 + Ghidra S-1 (pre-pattern gate) 이 결합되면 Precision +3~5%p (research/README §1 참조).

**중기 [M-x-1] XML 외부화** — Ghidra pattern XML 이식 (`docs/research/ghidra_func_detect_analysis.md` §7 M-1) 이 x64dbg primitive 위에 올라감. 이 경우 x64dbg 의 byte-mask 가 parser 의 leaf node 역할.

---

## 4. PDB / Symbol Server Loading

### 4.1 x64dbg 의 구현

`src/dbg/symbolinfo.cpp` — API:

```cpp
bool SymDownloadSymbol(duint Base, const char* SymbolStore);
void SymDownloadAllSymbols(const char* SymbolStore);
bool SymAddrFromName(const char* Name, duint* Address);
bool SymbolFromAddressExact(duint address, SYMBOLINFO* info);
bool SymbolFromAddressExactOrLower(duint address, SYMBOLINFO* info);
bool SymEnum(duint Base, CBSYMBOLENUM cb, void* ud, duint beginRva, duint endRva, uint mask);
bool SymGetSourceLine(duint Cip, char* FileName, int* Line, duint* disp);
```

### 4.2 Microsoft Symbol Server protocol

- **Default URL**: `https://msdl.microsoft.com/download/symbols`
- **Path 규약**: `{cache}/{pdbname.pdb}/{signature}/{pdbname.pdb}` — signature 는 GUID + age 복합 해시.
- **다운로드**: `downslib_download()` (x64dbg 내부 small http client) + progress callback.
- **Cache 관리**: 로컬 존재 확인 → 0-byte 파일 삭제 (retry 활성화) → `modInfo->loadSymbols()`.

### 4.3 다층 해결 전략 (Symbol resolution)

x64dbg 는 심볼을 해결할 때 **4-tier lookup**:

1. Loaded debug symbols (PDB / DWARF)
2. Module exports table
3. Module entry-point pseudo-symbol
4. Import Address Table (IAT) entries

`SymbolFromAddressExactOrLower` 는 stack walking 용 nearest-or-below 검색.

### 4.4 AURA Phase 3.12 와의 격차

AURA 는 `src/parser/pdb_parser.c` + `src/decompiler/pdb_types.c` 로 PDB 파싱 자체는 완료 (local file 경로 전달 시). 격차:

| 기능 | AURA 현재 | x64dbg |
|------|----------|--------|
| Local PDB parse | ✅ | ✅ |
| Symbol server download | ❌ | ✅ msdl.microsoft.com |
| 2-level cache dir | ❌ | ✅ `{cache}/{name}/{sig}/` |
| Partial lazy load | ❌ (전체 load) | ✅ mod base on demand |
| 4-tier fallback | Exports + IAT 부재 | ✅ |
| `SymAddrFromName` API | ❌ | ✅ name → addr 역방향 |

### 4.5 단기/중기 제안

**[S-x-2] Symbol server client** (1-2 세션, ~300 LOC):

- 의존: libcurl 이미 사용 중 (PRD §기술 스택) → **추가 의존성 0**.
- Cache path: `~/.cache/aura/symbols/{pdbname}/{sig}/{pdbname}`
- CLI flag: `--sym-server https://msdl.microsoft.com/download/symbols` (opt-in, 보안 고려).
- 기대 효과: Windows PE 바이너리 리버싱 시 stripped PDB 자동 확보 → recall 개선 (현재 AURA 는 명시적 path 필요).

**[M-x-1] Partial lazy PDB load** — 현재 AURA 는 PDB 전체 파싱. 대형 PDB (수백 MB, Windows kernel) 시 TTFR (time-to-first-result) 저하. x64dbg 스타일 lazy base-on-demand 로 개선 가능 — 설계 추정 2-3 세션, Phase 3.12 강화.

**[L-x-1] 4-tier symbol fallback** — exports + IAT 를 symbol DB 로 승격. AURA `func_id.c` 에 이름 부여 로직 추가. Rizin autoname (#30) 과 유사 (triangulation).

---

## 5. CLI / Command Engine

### 5.1 x64dbg 의 구조

**파일 분리 (`src/dbg/commands/cmd-*.cpp`)**:

| 카테고리 | 파일 |
|----------|------|
| Analysis | `cmd-analysis.cpp/h` |
| Script Execution | `cmd-script.cpp/h` |
| Pattern Search | `cmd-searching.cpp/h` |
| Symbol/Type | `cmd-types.cpp/h`, `cmd-user-database.cpp/h` |
| GUI integration | `cmd-gui.cpp/h` |
| Utilities | `cmd-general-purpose.cpp/h`, `cmd-misc.cpp/h` |
| Plugin | `cmd-plugins.cpp/h` |
| 중앙 registry | `cmd-all.h` |

(AURA scope 외 제외: `cmd-debug-control`, `cmd-tracing`, `cmd-thread-control`, `cmd-conditional-breakpoint-control`.)

### 5.2 Dispatcher (`src/dbg/command.cpp`)

- **등록**: `cmdinit()`, `cmdnew(name, callback, debugonly)`, `cmdfind()`.
- **Parse**: `cmdsplit()` — `;` 구분자로 multi-command 분리, quoted string 인지.
- **Execute**: `cmdloop()` → `cmdget()` → `Command` 클래스 argv parse → `cmdexeccallback()`.
- **Fallback**: 등록된 command 아님 → `ExpressionParser` 로 expression 평가 (예: `eax+4`).

### 5.3 Script 엔진

`cmd-script.cpp` 는 x64dbg 의 DSL 엔진. 제어 흐름 (`if`/`ret`/`call`), 변수 (`$0`..`$9`), label. **단, 이는 runtime debug scripting 이라 AURA scope 외** — 다만 command 구조 패턴 자체는 참조 가치.

### 5.4 AURA CLI 현황

- `src/cli/decompile_all.c` (신규, E-3 진행 중) + AURA main CLI (아마도 `src/core/cli_main.c` 등).
- **카테고리 분리 없음** — 모든 command 옵션이 main arg parser 에서 직접 dispatch (Phase 11.4 이전, 의도적 MVP 설계).

### 5.5 AURA 에 대한 시사점

**단기 scope 외** (AURA rules.md §8 스코프 통제) — 현재 AURA 는 `getopt_long` 기반 flag 로 충분. 그러나:

- **향후 Phase 2-E E-3 이후 `--decompile-all` 류 확장** 시 command set 가 30+ 증가할 것으로 예상.
- 그 시점에 **x64dbg `cmd-*` 파일 분리 패턴** 도입 검토 가치 — 단일 파일 비대화 방지.
- Expression evaluator fallback 은 AURA 에 **불필요** (runtime register 없음).

**예상 ROI**: **0 단기** (지금 필요 없음). 중기 (Phase 8+ UI 통합 단계) reference.

### 5.6 Findasm / 패턴 스캔 CLI 패턴

AURA 가 향후 `aura --find-pattern "48 8B ??" binary.exe` 를 추가한다면 x64dbg `cbInstrFindAllMem` 인터페이스가 직접 참고 대상:
- 모듈 필터 (user/system/all) → AURA 섹션 필터 (`.text`/`.rdata`/all).
- `&data&` flag → AURA `--raw-bytes` 옵션.
- `$result` return → AURA exit code + stdout JSON (E-3 방식과 정합).

---

## 6. Disassembly View UX (Qt)

### 6.1 x64dbg 디렉토리 구성 (`src/gui/Src/Disassembler/`)

- `Architecture.cpp/h` — 아키텍처별 instruction set.
- `QZydis.cpp/h` — **Zydis 엔진 Qt 래퍼**. AURA 가 결정한 Zydis 와 동일 엔진.
- `ZydisTokenizer.cpp/h` — 디스어셈블 결과 → 의미 토큰 분해.

(AURA `src/gui/disasm_view.cpp` 는 현재 리포에 없어 추정.)

### 6.2 `ZydisTokenizer::TokenType` enum

x64dbg 가 정의한 **32개+ 토큰 타입**:

```
// Filling
Comma, Space, ArgumentSpace, MemoryOperatorSpace

// Instruction parts
Prefix, Uncategorized

// Mnemonics (9 분류)
MnemonicNormal, MnemonicPushPop, MnemonicCall, MnemonicRet,
MnemonicCondJump, MnemonicUncondJump, MnemonicNop,
MnemonicFar, MnemonicInt3, MnemonicUnusual

// Values
Address, Value, TraceNewValue

// Memory operands
MemorySize, MemorySegment, MemoryBrackets, MemoryStackBrackets,
MemoryBaseRegister, MemoryIndexRegister, MemoryScale, MemoryOperator

// Registers (6 분류)
GeneralRegister, FpuRegister, MmxRegister,
XmmRegister, YmmRegister, ZmmRegister
```

### 6.3 `TokenColor` 구조

```cpp
struct TokenColor {
    RichTextPainter::CustomRichTextFlags flags;
    QColor color;
    QColor backgroundColor;
    TokenColor(QString color, QString backgroundColor);
};
```

- 각 TokenType 에 독립 TokenColor — 사용자가 theme 으로 per-token 색상 커스터마이즈 가능.
- `RichTextPainter` 는 x64dbg 자체 rich-text 렌더러 (Qt QTextEdit 대비 성능 최적화).

### 6.4 AURA Qt6 GUI 와의 alignment

AURA `src/gui/` 에 `cfg_view.cpp`, `callgraph_view.cpp`, `disasm_column_config.cpp` 가 이미 존재. Disassembly view 는 `disasm_column_config` 수준 (열 구성만) — tokenizer + per-token coloring 여부는 **확인 필요**.

### 6.5 단기/중기 제안

**[S-x-3] ZydisTokenizer 이식 검토** (~1 세션):

- AURA 가 이미 Zydis 를 의존하므로 x64dbg `ZydisTokenizer` 는 **drop-in 가능성 높음**.
- `TokenType` enum + `TokenColor` 구조 + `RichTextPainter` 대응 (Qt6 에서 `QTextCharFormat`/`QSyntaxHighlighter` 로 치환 가능).
- 예상 효과: disasm view UX 가 Ghidra/IDA 급 coloring → 사용자 가독성 향상, 기능 탐지 버그 찾기 쉬워짐 (regression 검증에도 기여).

**중기 [M-x-2] Row height / annotation overlay** — x64dbg 는 RichTextPainter 를 통해 주소 + 바이트 + disasm + comment 를 4-column 가변 높이로 렌더. AURA GUI (Phase 8.4+) 에서 동일 패턴 적용 시 reference.

### 6.6 AURA scope 외 (참고용)

x64dbg GUI 전체 (Register view / Stack view / Memory view) 는 AURA 에 가치 없음 — 정적 분석은 runtime register 개념이 없음. 단 **Token coloring** 만 국소 이식 대상.

---

## 7. 4-Way Triangulation (Ghidra × Rizin × x64dbg × AURA)

### 7.1 Pattern matching / signature 기능 비교

| 도구 | Pattern format | 외부화 | Pre/Post context | 정규화 |
|------|----------------|--------|------------------|--------|
| **Ghidra** (#26) | XML bit-level | ✅ runtime | ✅ pre/post pattern | `InstructionSkipper` per-proc |
| **Rizin** (#30) | FLIRT `.pat`/`.sig` + zignatures SDB | ✅ sigdb dir | ❌ | FLIRT CRC variable-byte |
| **x64dbg** (#33) | `PatternByte{data,mask}` 텍스트 | ❌ inline | ❌ | 없음 |
| **AURA** (현재) | C-hardcoded prologue only | ❌ | ❌ | 없음 |

**공통점**: 네 도구 모두 **wildcarded byte matching** 을 기본 primitive 로 인정.

**차이점**:
- Ghidra 가 **가장 정교** (bit-level + pre/post + normalization).
- Rizin 이 **가장 생태계 풍부** (IDA FLIRT 호환, 수백 MB 공개 sigdb).
- x64dbg 가 **가장 단순** (`patternfind.cpp` 단일 파일, literal-first 최적화 우수).
- AURA 는 네 도구 중 유일하게 runtime 확장성 없음 → **도입 1 순위**.

### 7.2 Symbol loading 비교

| 도구 | Local PDB | Symbol server | Partial load | Fallback tiers |
|------|-----------|---------------|--------------|----------------|
| **Ghidra** | ✅ | Microsoft + community | ✅ | 5+ (PDB/exports/IAT/FID/defaults) |
| **Rizin** | ✅ | ❌ (수동 DL) | ✅ | 3 (imports/exports/heuristic names) |
| **x64dbg** | ✅ | ✅ (msdl.microsoft.com) | ✅ | 4 (PDB/exports/entry/IAT) |
| **AURA** | ✅ (Phase 3.12) | ❌ | ❌ (전체 load) | 미명시 |

**AURA 격차 2**: symbol server + partial load. 둘 다 x64dbg 참조로 해소 가능.

### 7.3 CLI / command 구조

| 도구 | 파일 분리 | Registry | Expression evaluator |
|------|-----------|----------|---------------------|
| **Ghidra** | N/A (GUI 중심) | — | — |
| **Rizin** | ✅ `rizin/cmd-*.c` | ✅ radare2 descendant | ✅ `?` expression |
| **x64dbg** | ✅ `cmd-*.cpp/h` | ✅ `cmd-all.h` | ✅ `ExpressionParser` |
| **AURA** | ❌ (MVP 단일 main) | ❌ | ❌ (불필요) |

AURA 의 현재 단순 CLI 구조는 **의도적 MVP** (PRD §5, rules.md §1) → 격차 아님. Phase 11.4 이후 확장 시 x64dbg/Rizin 의 파일 분리 패턴을 기본으로.

---

## 8. 개선 제안 (AURA 관점, 우선순위)

### 8.1 단기 (1 세션 규모)

| ID | 작업 | 예상 +Δ | 세션 | 선행 |
|----|------|---------|------|------|
| **S-x-1** | `patternfind.c` 이식 (PatternByte + literal-first loop) | +0 단독, +3~5%p precision (S-x-1 + Ghidra S-1 결합 시) | 1 | 없음 |
| **S-x-2** | Symbol server client (libcurl + msdl.microsoft.com) | Windows PE recall 개선 | 1-2 | libcurl |
| **S-x-3** | ZydisTokenizer 이식 (AURA disasm view 에 GUI syntax coloring) | UX 품질 향상 (정성적) | 1 | AURA disasm view 존재 확인 필요 |

### 8.2 중기 (2-5 세션)

| ID | 작업 | 근거 | 세션 |
|----|------|------|------|
| **M-x-1** | PDB partial lazy load (Phase 3.12 강화) | x64dbg `modInfo->loadSymbols` on-demand | 2-3 |
| **M-x-2** | Row height / annotation overlay GUI pattern | x64dbg RichTextPainter + Qt6 `QSyntaxHighlighter` | 2 |

### 8.3 스코프 외 (rules.md §8 준수)

- **Runtime stepping / breakpoint** — AURA 정적 RE scope 위반 → 금지.
- **DLL injection / anti-debug** — 마찬가지.
- **CLI 파일 분리 리팩터** — 현재 MVP 로 충분, Phase 11.4 이후에만 재평가.

---

## 9. Cross-Reference

### 9.1 기존 연구 문서

- **#26** `docs/research/ghidra_func_detect_analysis.md` §3.2 (BulkPatternSearcher + XML) + §7 (S-1 pre-pattern gate / M-1 XML loader).
- **#27** `docs/research/ghidra_disasm_analysis.md` §7 (M-1 PCode Low-IR — x64dbg 의 Zydis 래핑 전략과 유사하나 깊이 차이 큼).
- **#28** `docs/research/ghidra_disasm_decompile_bridge_analysis.md` — 본 문서와 직접 교차 없음.
- **#30** `docs/research/rizin_func_detect_analysis.md` §4 (zignatures + FLIRT) + §5 (F-1 FLIRT loader 제안).
- **#31** `docs/research/rizin_disasm_analysis.md` — Rizin 파일 로더 비교.
- **#32** `docs/research/rizin_il_analysis.md` — RzIL 비교.

### 9.2 AURA 코드 참조점

- `src/parser/pdb_parser.c` — Phase 3.12 PDB 로더. S-x-2 symbol server 확장 대상.
- `src/decompiler/pdb_types.c` — PDB 타입 인덱스.
- `src/analysis/func_detect.c` (추정 위치) — S-x-1 patternfind primitive 도입 대상.
- `src/cli/decompile_all.c` — E-3 진행 중, CLI 확장 시 x64dbg `cmd-*` 패턴 reference (현 시점 불필요).
- `src/gui/disasm_column_config.cpp` — S-x-3 ZydisTokenizer 이식 검토 대상.

---

## 10. 인용

### 10.1 x64dbg 소스

- `src/dbg/patternfind.cpp` — `PatternByte`, `patterntransform`, `patternfind`, `patternwrite`, `patternsnr`.
- `src/dbg/commands/cmd-searching.cpp` — `handlePatternArgument`, `cbInstrFind`, `cbInstrFindAll`, `cbInstrFindAllMem`, `cbInstrFindAsm`, `cbRefFind`, `cbRefStr`, `cbRefFuncPtr`, `cbGUIDFind`.
- `src/dbg/command.cpp` — `cmdinit`, `cmdnew`, `cmdfind`, `cmdsplit`, `cmdloop`, `cmdexeccallback`.
- `src/dbg/symbolinfo.cpp` — `SymDownloadSymbol`, `SymDownloadAllSymbols`, `SymAddrFromName`, `SymbolFromAddressExact`, `SymbolFromAddressExactOrLower`, `SymEnum`, `SymGetSourceLine`.
- `src/dbg/patches.cpp` — `PATCHINFO`, `PatchSet/Get/DelRange/File/Enum` (참고: 실제 pattern matching 은 여기 아님 — `patternfind.cpp` 에 있음).
- `src/gui/Src/Disassembler/` — `Architecture.{cpp,h}`, `QZydis.{cpp,h}`, `ZydisTokenizer.{cpp,h}`.

### 10.2 공식 docs

- https://x64dbg.com/ — 공식 사이트.
- https://help.x64dbg.com/ — 사용자 매뉴얼.
- https://github.com/x64dbg/x64dbg — GPL-3 소스.
- https://msdl.microsoft.com/download/symbols — Microsoft Symbol Server (x64dbg 기본 URL).

### 10.3 블로그 포스트 (아키텍처 관련 3)

1. *"Type System and Modernization"* (2025-06-30) — CMake + VS2022 빌드 현대화.
2. *"Analysis at Scale with x64dbg Automate"* (2025-03-04) — Python 자동화 클라이언트.
3. *"Fun with Self-Decryption"* (2018-02-25) — 튜토리얼 (아키텍처 비관련).

### 10.4 메타데이터

- **작성 시점**: 2026-04-20, Session #9 (v2.3.0 Phase 2-E 병렬 연구).
- **도구**: WebFetch (7+ successful / 5 failed due to 403/404 on deep blob paths — 핵심 파일은 커버됨).
- **scope**: 의도적 제한 (runtime debugger 기능 제외).
- **예상 LOC**: ~360 LOC (제한 scope 반영).
- **Author**: researcher-x64dbg (Team v2-3-0-phase-2b).
- **License**: x64dbg GPL-3 — AURA 가 코드를 **그대로 복사하면 GPL 전이**. 따라서 이식 시 **algorithm 참조 + clean-room 재구현** 원칙 준수.
