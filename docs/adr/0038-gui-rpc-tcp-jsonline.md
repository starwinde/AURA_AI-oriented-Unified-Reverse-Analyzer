# ADR-0038 — GUI RPC server (TCP localhost + JSON-line) (Phase 11.3.3)

**Status**: Accepted
**Date**: 2026-05-03
**Deciders**: 사용자 (project owner)
**Related**: ADR-0033 (frontend topology), ADR-0035/0036/0037 (GUI v1
~ v1.2), Phase 11.4 (CLI override)

---

## Context

ADR-0033 의 co-equal CLI + GUI 설계는 두 frontend 를 같은 `aura_core`
위에 두지만, 두 frontend 사이의 **자동화 가교** 는 부재. 결과:
1. 사용자가 떠있는 GUI 를 외부에서 스크립트로 조작 불가.
2. CI / e2e 테스트가 GUI 의 visual flow 를 검증 불가 (ctest 의
   gui_smoke 는 같은 프로세스의 MainWindow API 를 직접 호출하므로 진짜
   "사용자 시나리오" 가 아님).
3. Claude Code (또는 다른 자동화 에이전트) 가 GUI 와 상호작용 불가 →
   사용자 자료 (Easy_CrackMe.exe 등) 의 자동 RE 검증 차단.

이전 grilling 라운드 (Phase 11.3.2 직전) 에서 IPC 는 ROI 낮음으로
defer 결정. 사용자 검토 결과 **Easy_CrackMe.exe 실증 e2e 테스트의
prereq** 로 reactivate. 핵심 수요 = "사용자가 직접 클릭하지 않고도
GUI 의 동작을 외부에서 trigger + 결과 확인 가능".

## Decision

GUI RPC = **TCP localhost JSON-line server**, opt-in (default OFF).

### v1 표면 (확정)

| 영역 | 결정 |
|------|------|
| 전송 매체 | TCP localhost (127.0.0.1), 사용자 지정 포트 (default 9001) |
| 활성화 | `aura-gui --rpc-port <N>` 또는 env `AURA_GUI_RPC_PORT=<N>`. default OFF (보안). |
| 바인딩 | **127.0.0.1 only** (절대 0.0.0.0 거부) — 외부 공격 surface 0 |
| 인증 | 옵션 token via env `AURA_GUI_RPC_TOKEN`. 미설정 시 기동 시 random 32바이트 hex 를 stdout 출력. 클라이언트는 매 명령에 `"token": "<hex>"` 포함. |
| 프로토콜 | **JSON-line** — 한 줄 = 한 요청 또는 응답, `\n` 구분. HTTP/JSON-RPC envelope 거부 (오버헤드 + envelope 결정 비용). |
| 요청 형식 | `{"method":"<name>","params":{...},"token":"<hex>"}` |
| 응답 형식 | `{"ok":bool,"result":...,"error":"..."}` |
| 명령 set v1 | `open_project` / `add_binary` / `analyze` / `decompile` / `rename` / `reset_name` / `function_list` / `quit` |
| Threading | Qt main thread only (`QTcpServer` 시그널 → 직접 호출). single-client 가정. |
| 클라이언트 | `aura gui-rpc <method> [json-args]` CLI 서브커맨드 (Phase 11.3.3 Slice F) |
| 동시 클라이언트 | v1 = 1개만 허용 (이후 연결은 reject). v2+ 가능. |
| Long-running 명령 | 동기 처리 (analyze 30s+ → 클라이언트도 30s 대기). v2 에서 async 옵션. |

### 명령 명세 (v1)

| method | params | result on ok | 비고 |
|--------|--------|-------------|------|
| `open_project` | `{"path":"foo.aura.db"}` | `{"binary_count":N}` | 새 / 기존 모두 OK |
| `add_binary` | `{"path":"foo.exe"}` | `{"fingerprint":"<hex>","size":N}` | sha256 자동 |
| `analyze` | `{"row":0,"level":"full"\|"quick"}` | `{"function_count":N}` | 동기 |
| `decompile` | `{"function_row":N}` | `{"backend":"rizin/pdf","text":"..."}` | 캐시 자동 |
| `rename` | `{"function_row":N,"new_name":"foo"}` | `{"display_name":"foo"}` | |
| `reset_name` | `{"function_row":N}` | `{"display_name":"<original>"}` | |
| `function_list` | `{}` | `{"functions":[{"row":N,"name":"...","entry":"0x...","size":N,"source":"..."}]}` | 페이징 v2 |
| `quit` | `{}` | `{}` | 응답 후 GUI 종료 |

### v2+ 로 분리 (의도적 누락)

- 다중 동시 클라이언트
- Async 명령 (long-running 분석에 progress 콜백)
- 양방향 push (analyze 진행률, 사용자 클릭 이벤트 외부 통지)
- WebSocket / HTTP API
- 페이징 / 스트리밍 (function_list 가 큰 binary 에서 수만 행)
- TLS

## Rationale

### TCP localhost vs DBus / Named Pipe / Unix Socket

- DBus = Linux 한정 + 시스템 버스 의존 + 권한 복잡. WSL→Windows 호환성
  의문.
- Named Pipe = Windows 한정.
- Unix Socket = WSL 안에서만 동작, Windows native MSVC 에서 X.
- **TCP** = Linux + Windows MSVC + WSL 모두 일관, libcurl 코드 자산
  공유 (LLM HTTP client 와 동일 IO 패턴).

### JSON-line vs HTTP / JSON-RPC 2.0

- HTTP = 헤더 / 메소드 / status code = 결정 라운드 폭증.
- JSON-RPC 2.0 = `id` / `jsonrpc` / `method` envelope = single-user
  single-connection 에 과잉.
- JSON-line = `nc localhost 9001` 으로 직접 명령 가능 = 디버깅 자연스러움.

### 인증 = localhost 바인딩 + 옵션 token

- 0.0.0.0 바인딩 = 네트워크 노출 = 인증 필수. 거부.
- 127.0.0.1 = 같은 머신의 다른 프로세스만 접근 가능 = 일반 사용자
  workstation 에서는 충분히 안전.
- Token = 같은 머신의 다른 사용자 (multi-user 서버) 차단. opt-in
  (env 설정) 또는 자동 (기동 시 random 출력).

### Single-thread Qt main loop

- 별도 thread = AURA core API 호출 시 GUI 와 race. AURA 의 orchestrator
  / override_store 는 single-threaded 가정.
- Qt main thread = `QTcpServer::newConnection` 시그널 → slot 에서
  명령 파싱 → MainWindow API 직접 호출 → 응답 송신. UI freeze
  potential = 분석 동안 GUI 멈춤, but **이미 ADR-0035 의 분석 정책
  과 일관** (분석 중 status bar progress + Analyze disable, 비차단
  스피너 없음).

### Default OFF

- IPC = attack surface. 사용자가 명시적으로 켤 때만 동작.
- CI / 일반 사용자 영향 0.

## Consequences

### Positive

- Claude / 스크립트 / e2e 테스트가 진짜 사용자 시나리오 검증 가능.
- Easy_CrackMe.exe 등 사용자 자료의 자동 RE 검증 가능.
- AURA 의 자동화 surface = LLM 통합 + 외부 도구 + IPC 조합으로 차별점
  강화.

### Negative

- 새 코드 surface (~600 LOC 추정: server + protocol + client +
  ctest).
- 보안 책임 — token / localhost 바인딩 검증 / 부적절 사용 시 데이터
  유출 위험.
- v1 single-client = 다중 client 시 reject 하는 동작이 "왜 안 되지?"
  사용자 혼란 가능.

### Neutral

- HTTP 클라이언트 (libcurl) 와 별개 — RPC 는 server. 코드 공유 없음
  (libcurl 은 client only).

## Alternatives Considered

### Headless GUI driver 바이너리 (ADR-0036 amend)

거부. headless = 실제 GUI 창 안 뜸. 사용자가 보는 화면 검증 불가.
RPC 는 같은 GUI 인스턴스에 여러 client 가 명령 가능 = visual + 자동화
양립.

### Embedded scripting (Lua / Python)

거부. v1 scope 폭증 (interpreter 임베드 + 바인딩 정의 + 보안). RPC
는 외부 client 책임 분리.

### gRPC / protobuf

거부. 빌드 의존성 (protoc) + .proto 파일 + 코드 생성 = scope 폭증.
v3+ 에서 다중 언어 client / 고성능 streaming 필요 시 고려.

## Implementation

Slice 단위:
- **A** — ADR-0038 + ROADMAP + CONTEXT (본 커밋)
- **B** — `src/gui/rpc_server.{h,cpp}` — `QTcpServer` + JSON-line +
  명령 dispatch + token check
- **C** — `MainWindow` 통합: `--rpc-port` CLI flag + RPC 서버 인스턴스
  + 기동 / 종료
- **D** — 명령 핸들러 구현 (8개 method)
- **E** — `aura gui-rpc <method> [json-args]` CLI 클라이언트
- **F** — gui_rpc_smoke ctest (offscreen GUI + RPC client e2e)
- **G** — 보안 검증 (127.0.0.1 only / token / 잘못된 token reject)
- **H** — Easy_CrackMe.exe e2e 자동 검증 (RPC 로 GUI 조작 → 결과
  추출)

## References

- ADR-0033 — Frontend topology
- ADR-0035 / 0036 / 0037 — GUI v1 ~ v1.2 표면
- Phase 11.4 — CLI override (RPC 클라이언트 통합 패턴 reference)
