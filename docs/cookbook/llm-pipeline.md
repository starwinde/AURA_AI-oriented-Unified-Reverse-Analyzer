# Cookbook — `aura llm-context` → OpenAI-compat LLM endpoint

> **Phase 11.2 e2e gate**: 본 문서의 transcript 1건이 ADR-0033 의
> "GUI bootstrap = CLI v1 + LLM e2e 1건 검증" 조건을 충족한다.
>
> **Captured**: 2026-05-03, qwen/qwen3.6-35b-a3b @ remote LM Studio
> (`http://122.43.160.242:1234`).

## 원칙: AURA 는 LLM 을 호출하지 않는다

`aura llm-context` 는 **payload JSON 만** stdout 으로 emit. 호출/모델/
prompt 는 사용자 책임. 이 분리가 ADR-0033 의 *additive* 원칙
("LLM 없이도 AURA 는 동작") 의 실천. 본 cookbook 은 사용자가 어떻게 그
payload 를 LLM 에 wrap 하는지의 표준 예시.

Phase 13 의 제품 방향은 **1개 생성형 LLM + PII 특화 모델·데이터셋 기반
Privacy Filter & Policy Gateway**다. 즉, AURA 가 중간에 두 번째 생성형
LLM verifier 를 상시 배치하지 않는다. 향후 `aura-mcp` 는 생성형 LLM
모델이 아니라 gateway 로 동작하며, 현재 문자열 기반 MVP 에서 시작해 PII
특화 탐지 모델과 데이터셋 기반 탐지를 결합한 민감정보 마스킹 시스템으로
확장한다. 이 gateway 는 binary path/token/API key/secret/민감 문자열
마스킹, 길이 제한, tool allowlist, 사용자 승인, audit logging 을 적용한
뒤 LLM 이 볼 수 있는 payload 를 제한한다.

## 환경

- AURA CLI: `aura` (Phase 11.1, commit `e61fa879` 이상)
- Reference engine: Rizin 0.8.0 shared64 + rz-ghidra 0.8.0
  (e.g. `third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin`)
- LLM endpoint: OpenAI-compatible chat completions (`/v1/chat/completions`)
- 본 transcript 의 endpoint: `http://122.43.160.242:1234` (LM Studio)
- 본 transcript 의 모델: `qwen/qwen3.6-35b-a3b` (reasoning 모델)

## Service / Model 자유 전환 — env var convention (Phase 11.2.1)

AURA 코드는 LLM endpoint 를 **모르고 알 필요 없음** (additive 원칙).
사용자 wrapper (`scripts/llm-rename.sh`) 가 다음 환경변수를 읽어 어느
OpenAI-compatible endpoint 든 동작:

| Env | 의미 | 예시 |
|-----|------|------|
| `AURA_LLM_BASE_URL` | OpenAI-compat base (`/v1` 까지) | `http://localhost:1234/v1`, `https://api.openai.com/v1` |
| `AURA_LLM_MODEL` | endpoint 가 인식하는 model id | `qwen/qwen3.6-35b-a3b`, `gpt-4o-mini`, `llama3.2:3b` |
| `AURA_LLM_API_KEY` | bearer token (cloud endpoint 만) | `sk-...` |
| `AURA_LLM_MAX_TOKENS` | default 1024 (reasoning 모델 권장) | `2048` |

### 즉시 전환 가능 (env 1줄 export)

```sh
# LM Studio (로컬 또는 remote)
export AURA_LLM_BASE_URL=http://122.43.160.242:1234/v1
export AURA_LLM_MODEL=qwen/qwen3.6-35b-a3b

# OpenAI
export AURA_LLM_BASE_URL=https://api.openai.com/v1
export AURA_LLM_MODEL=gpt-4o-mini
export AURA_LLM_API_KEY=sk-...

# Ollama (로컬)
export AURA_LLM_BASE_URL=http://localhost:11434/v1
export AURA_LLM_MODEL=llama3.2:3b

# Groq
export AURA_LLM_BASE_URL=https://api.groq.com/openai/v1
export AURA_LLM_MODEL=llama-3.3-70b-versatile
export AURA_LLM_API_KEY=gsk_...

# vLLM / TGI / Together / Fireworks / DeepInfra — 동일 패턴
```

후 동일 명령:

```sh
./scripts/llm-rename.sh tests/fixtures/bin/elf_smoke.x86_64 0x40117b
```

### 별도 wrapper 필요 (네이티브 API 가 OpenAI-compat 아님)

| 플랫폼 | 이유 | 우회 |
|--------|------|------|
| Anthropic native (`/messages`) | endpoint shape 다름, system prompt 위치 다름 | per-service wrapper 추가 또는 [LiteLLM](https://github.com/BerriAI/litellm) proxy 띄워서 OpenAI-compat 으로 변환 |
| Google Gemini native | 완전 다른 schema | 동일 |
| Cohere native | 완전 다른 schema | 동일 |

**LiteLLM 권장 패턴**: `litellm --model anthropic/claude-3-5-sonnet-20240620` 같이 띄우고 `AURA_LLM_BASE_URL=http://localhost:4000/v1` 으로 가리키면 모든 cloud LLM 이 OpenAI-compat 으로 통합 — AURA / wrapper 둘 다 무변경.

## 시나리오: 함수 rename 제안

### 1. AURA payload 생성

```sh
AURA_RIZIN_BIN="$PWD/third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/bin/rizin" \
SLEIGHHOME="$PWD/third_party/rizin/0.8.0-shared/rizin-win-installer-clang_cl-64/lib/rizin/plugins/rz_ghidra_sleigh" \
  ./build/src/cli/aura --compact llm-context \
    tests/fixtures/bin/elf_smoke.x86_64 --func 0x40117b \
  > payload.json
```

`payload.json` 내용 (369 bytes):

```json
{
  "aura_schema": 1,
  "command": "llm-context",
  "binary": "tests/fixtures/bin/elf_smoke.x86_64",
  "mode": "function",
  "function": {
    "function_id": 12,
    "name": "dbg.main",
    "entry": 4198779,
    "size": 93,
    "provenance": { "source": "rizin", "confidence": 0.9, "completeness": 1 },
    "callers": [],
    "callees": ["sym.imp.printf",
                "dbg.aura_helper_add",
                "dbg.aura_helper_mul",
                "dbg.aura_helper_sub"]
  }
}
```

### 2. Chat completion request 작성

`jq` 또는 python 으로 wrap. 본 cookbook 은 python 사용 (jq 의 `tojson`
으로도 동등 가능).

```py
import json
p = json.load(open("payload.json"))
req = {
    "model": "qwen/qwen3.6-35b-a3b",
    "messages": [
        {"role": "system",
         "content": "You are a reverse-engineering assistant. Given a "
                    "JSON payload describing a function (name, address, "
                    "size, callers, callees, provenance), suggest one "
                    "concise descriptive identifier (snake_case, "
                    "<=32 chars) based on the signals. Reply with ONLY "
                    "the identifier."},
        {"role": "user", "content": json.dumps(p, ensure_ascii=False)}
    ],
    "temperature": 0.2,
    "max_tokens": 1024
}
json.dump(req, open("req.json", "w"))
```

> **주의: reasoning 모델은 `max_tokens` 큰 예산 필요.** 첫 시도에서
> `max_tokens=64` 로 보냈더니 모델이 thinking 만으로 64 token 을 모두
> 소진하고 `content` 가 빈 채 `finish_reason="length"` 로 종료. **1024
> 로 늘리고 재시도** 했더니 821 token reasoning + 5 token output 으로
> 정상 응답. non-reasoning 모델은 64 정도로도 충분하므로 모델 종류에
> 따라 조정.

### 3. Endpoint 호출

```sh
curl -s --max-time 180 http://122.43.160.242:1234/v1/chat/completions \
  -H "Content-Type: application/json" \
  --data-binary @req.json \
  > resp.json
```

### 4. 응답 (실 캡처)

```json
{
  "id": "chatcmpl-e5wpkgc92b9x3z09xqivb",
  "object": "chat.completion",
  "model": "qwen/qwen3.6-35b-a3b",
  "choices": [{
    "index": 0,
    "message": {
      "role": "assistant",
      "content": "\n\ndbg_main",
      "reasoning_content": "Here's a thinking process: ...
        (821 tokens of reasoning trace, captured in transcript files)"
    },
    "finish_reason": "stop"
  }],
  "usage": {
    "prompt_tokens": 225,
    "completion_tokens": 826,
    "total_tokens": 1051,
    "completion_tokens_details": { "reasoning_tokens": 821 }
  },
  "system_fingerprint": "qwen/qwen3.6-35b-a3b"
}
```

**Suggested identifier**: `dbg_main` (모델 출력 trim 후).

### 5. 표준 wrapper (`scripts/llm-rename.sh`)

위 5 단계 (payload 생성 + request 작성 + curl + 응답 추출) 를 **하나의
스크립트** 로 묶은 것이 `scripts/llm-rename.sh`. 위 env var convention
을 그대로 사용:

```sh
AURA_LLM_BASE_URL=http://122.43.160.242:1234/v1 \
AURA_LLM_MODEL=qwen/qwen3.6-35b-a3b \
AURA_LLM_MAX_TOKENS=1024 \
  ./scripts/llm-rename.sh tests/fixtures/bin/elf_smoke.x86_64 0x40117b
# → dbg_main
```

내부 구현은 위 1~4 단계 그대로. 차이는 사용자가 매번 inline python /
curl 을 작성할 필요 없음. `aura llm-context` 의 stdout 을
`/v1/chat/completions` 으로 wrap → POST → trimmed assistant content
출력. 응답이 malformed (예: 모델 unloaded, API key 만료) 면 stderr 로
원본 응답 + 이유 출력 후 exit 1.

### 6. 다음 단계 (Phase 11.4 의 작업, v1 범위 외)

향후 `aura override put <bin> --func 0x40117b --rename dbg_main` 로
이 응답을 SQLite override store 에 영속화 — 그때 LLM → override
round-trip 이 닫힘. 본 cookbook 의 가치는 거기까지의 entry point
(payload 가 실제 endpoint 와 형식 호환됨) 검증.

## 검증된 사실

- ✅ AURA `llm-context` payload 가 OpenAI-compatible chat completion
  request 의 `messages[].content` 로 직접 wrap 가능 (escaping 외
  변환 없이).
- ✅ Remote endpoint (LM Studio) 가 payload 를 정상 수신, HTTP 200,
  `finish_reason="stop"` 으로 자연 종료.
- ✅ 모델이 payload 의 signals (`name`, `callees`, `provenance`) 를
  추론에 사용 — reasoning_content 에서 명시적으로 각 필드를 인용
  ("`name: "dbg.main"`", "`callees: [...]`", ...).
- ✅ 응답이 system prompt 의 제약 (snake_case, <=32 chars,
  identifier-only) 을 준수.

## 알려진 한계

- 본 transcript 의 fixture 는 단순 (4 helpers + main) 이라 모델 응답이
  base name 을 sanitize 한 수준 (`dbg.main` → `dbg_main`) — 더 정보가
  많은 함수에서 모델의 인지 가치가 더 크게 노출. 본 cookbook 은 *e2e
  형식 호환* 만 단언, *응답 품질* 을 단언하지 않음.
- LLM 호출은 비결정적 (모델 무작위성, endpoint 가용성) 이라 본 transcript
  를 byte-equal 회귀 테스트로 사용 불가. 결정론적 검증 = `cli_smoke`
  의 `llm-context` schema TC.
- `--with-decompile` 시 Rizin 의 디컴파일 backend 부재 시 `decompile`
  필드 생략 (graceful degrade) — payload 정보량이 줄어들 뿐 호출 자체는
  정상.

## Reference

- ADR-0033 — Frontend topology + LLM additive 원칙
- `docs/cli.md` — `aura llm-context` 의 단일 reference
- `tests/integration/cli_smoke/cli_smoke.cpp` — schema TC (TC4)
