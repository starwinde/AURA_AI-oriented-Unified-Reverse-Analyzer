# ADR-0049 — Phase 2.5.1 Real subprocess `AuraCommandRunner` (POSIX + Windows)

- **Status**: Accepted (closeout)
- **Date**: 2026-05-05
- **Related**: ADR-0031 (reference engine policy), ADR-0032 (external tool
  acquisition pattern), rules.md §1 (cross-platform subprocess guard,
  2026-05-05).
  Code: [src/engine/probe/command_runner.h](../../src/engine/probe/command_runner.h),
  [src/engine/probe/command_runner_subprocess.{h,c}](../../src/engine/probe/command_runner_subprocess.c),
  [tests/unit/probe/subprocess_runner_unit.cpp](../../tests/unit/probe/subprocess_runner_unit.cpp).
  Phase 2.5.1 commits `435036c7`, `7d22b233`, `a09b5d8a`.

## Context

Phase 2.5 코어 (Slices 1-60) 가 probe library 를 abstract `AuraCommandRunner`
인터페이스 위에 구축했지만 production backend 가 부재했다. 모든 probe 단위
테스트는 `FakeCommandRunner` (`probe_unit.cpp` 의 inline mock) 만 사용했다.
production CLI path (`aura --probe-engines`, Phase 2.5.1 X.4) 가 진입할 때
"실제 OS subprocess 를 spawn 해서 stdout/stderr 캡처 + exit code 보고 + timeout
강제" 하는 backend 가 필요했다.

요구사항:
- abstract 인터페이스 (`command_runner.h`) 와 동일 contract
  (rc=0=spawn ok / rc=-1=spawn fail / `timed_out` flag)
- POSIX (Linux WSL Tier 1) + Windows MSVC Tier 1 양쪽 지원
- pipe deadlock 가드 (Codex review #1 지적 — child 가 pipe buffer 보다 많이
  출력해도 정상 종료해야 함)
- 외부 의존성 0 (libuv 등 금지) — 표준 POSIX/Win32 API 만 사용

## Decisions

### D1 — POSIX 분기: pipe + fork + execvp + poll-based deadline drain

POSIX implementation (`#else /* POSIX */` 블록):
- `pipe(2)` x2 (stdout, stderr)
- `fork(2)` + child 에서 `dup2(2)` + `execvp(2)`
- 부모는 read end 를 `O_NONBLOCK` 으로 설정 후 `poll(2)` + `read(2)` 루프
- `waitpid(WNOHANG)` 로 reap 시도, deadline 초과 시 `kill(SIGKILL)` + blocking `waitpid`

**핵심 결정** (Codex review #1 응답): drain-while-waiting.
Child 가 종료되기를 먼저 기다리고 그 다음 drain 하는 구조는 pipe deadlock
취약. wait loop 내부에서 매 iteration `drain_available()` 를 호출해 pipe 를
incremental 하게 비움. `poll()` 의 timeout 은 100ms 로 cap 해 descendant 가
pipe 잡고 있어도 (POLLHUP 안 옴) waitpid 재확인을 100ms 마다 보장.

`drain_available()` 자체도 reads-per-call cap (64회) 으로 fairness 보장 —
`yes` 같은 fast producer 가 EAGAIN 안 도달해도 wait loop 가 timer 체크 가능.

execvp 실패 (child 가 exit 127 로 종료) 는 spawn failure (rc=-1) 로 매핑.
caller 가 ENGINE_MISSING 으로 자연스럽게 분류 가능.

### D2 — Windows 분기: CreatePipe + CreateProcessA + per-pipe reader threads

Windows implementation (`#ifdef _WIN32` 블록):
- `CreatePipe()` x2, write end 만 inheritable
- `CreateProcessA()` with redirected stdin/stdout/stderr
- **stdout/stderr 각각 dedicated reader thread** (`pipe_reader_thread`) 가
  `ReadFile()` 로 drain 하면서 `WaitForSingleObject(process)` 와 병행
- timeout 시 `TerminateProcess()` → child 종료 → pipes close → reader threads
  EOF 받고 자연 종료 → `WaitForSingleObject(thread, INFINITE)` 로 join

**왜 thread 인가**: Windows 의 anonymous pipe 는 nonblocking IO 가 까다롭고
overlapped IO 는 명시 setup 필요. 2개 reader thread 가 코드 단순도 + 정확성
양면에서 우위.

argv → command line 변환은 `build_cmdline()` 에서 quoting 처리 (공백/따옴표
포함 인자 wrapping). MSVC `CommandLineToArgvW` 역연산 규칙 부분 구현.

### D3 — 인터페이스 안정성: caller 는 추상 contract 만 봄

`command_runner.h` 의 `AuraCommandResult` (4096B stdout/stderr 버퍼 + exit_code
+ timed_out flag) 는 production / fake 양쪽이 동일 채움. caller (5 probe 함수)
는 `AuraCommandRunner *runner` 만 받아 `runner->run(...)` 호출 — production
인지 fake 인지 모름.

Buffer 가득 차면 silent truncate (existing contract). drain 은 buffer 가
가득 찬 후에도 pipe 를 계속 비움 (child 가 SIGPIPE / write 차단 안 당하게).

### D4 — 회귀 테스트: 9 cases 양 OS 동일 검증

`tests/unit/probe/subprocess_runner_unit.cpp` (Slice X.7):
- 4 happy path (echo / nonzero exit / missing program / stderr 분리)
- 1 large output (≥128KB stdout) — pipe deadlock 회귀 가드
- 1 simultaneous stdout + stderr — concurrent pressure
- 1 timeout while streaming — deadline 동작
- 1 stderr timeout diagnostic 보존
- 1 background descendant (POSIX-only) — orphan pipe holder 시나리오

Cross-platform child commands: POSIX `/bin/sh -c "..."`, Windows `cmd /c "..."`.
실제 RE engine binary 의존성 0.

## Out of scope

1. **Stdin 입력 전송** — 현재 모든 probe 는 인자만 사용. stdin pipe 전달은
   미래 (예: ghidra-decomp 가 XML 입력 받을 때) 별도 ADR.
2. **Streaming output callback** — 4096B 버퍼 + 종료 후 일괄 반환 모델.
   장기 실행 도구 (analyzeHeadless 가 GB log 토할 때) 는 별도 SessionManager
   (Phase 11.5) 에서 처리.
3. **Process group 관리 (POSIX setpgid + Windows JOB_OBJECT)** — 현재
   descendant leak 은 hang 안 일으키지만 zombie 가능. 미래 probe 가 손자
   spawn 하는 도구 호출 시 처리. Codex review #3 high "spin forever" 는
   review #4 에서 정정 (실제는 leak, not hang) — 현 구현 ship 가능.
4. **CI smoke under non-ASCII path** — Codex review #6 medium. Phase 9
   platform coverage 에서 처리.

## Verification

Slice X.7 회귀 테스트 9/9 GREEN (양 OS).
Phase 2.5.1 + 2.5.2 통합 verification:
- Windows MSVC (한글 경로) : `aura.exe` 빌드 + `aura --probe-engines` envelope
  emit + `probe_engines_smoke` GREEN
- Linux WSL Ubuntu 24.04 : ctest 5/5 suites GREEN

Codex 5-round adversarial review cycle (review #1~#6) 모두 high finding
닫힘, 최종 verdict: APPROVE.
