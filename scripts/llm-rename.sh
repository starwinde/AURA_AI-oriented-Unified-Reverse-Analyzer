#!/usr/bin/env bash
# llm-rename.sh — wrap `aura llm-context` output for any OpenAI-compatible
# chat-completions endpoint. AURA itself does NOT call LLMs (additive
# principle, ADR-0033). This script is a *user tool*: read environment
# config, build the chat-completions request, POST, print the trimmed
# identifier suggestion.
#
# Usage:
#   AURA_LLM_BASE_URL=http://122.43.160.242:1234/v1 \
#   AURA_LLM_MODEL=qwen/qwen3.6-35b-a3b \
#   ./scripts/llm-rename.sh tests/fixtures/bin/elf_smoke.x86_64 0x40117b
#
# Required env:
#   AURA_LLM_BASE_URL   OpenAI-compat base (http://host:port/v1)
#   AURA_LLM_MODEL      model id understood by the endpoint
# Optional env:
#   AURA_LLM_API_KEY    bearer token (OpenAI / Groq / ...)
#   AURA_LLM_MAX_TOKENS default 1024 (raise for reasoning models)
#   AURA_RIZIN_BIN      rizin binary (else PATH)
#   AURA_BIN            path to aura (else PATH or build*/src/cli/aura)
set -euo pipefail

if [[ $# -ne 2 ]]; then
    echo "usage: $0 <binary> <func_addr_hex>" >&2
    exit 2
fi
BINARY="$1"
ADDR="$2"

: "${AURA_LLM_BASE_URL:?env AURA_LLM_BASE_URL required (e.g. http://host:port/v1)}"
: "${AURA_LLM_MODEL:?env AURA_LLM_MODEL required}"
MAX_TOKENS="${AURA_LLM_MAX_TOKENS:-1024}"

AURA="${AURA_BIN:-}"
if [[ -z "$AURA" ]]; then
    if command -v aura >/dev/null 2>&1; then
        AURA="$(command -v aura)"
    elif [[ -x "build/src/cli/aura" ]]; then
        AURA="build/src/cli/aura"
    elif [[ -x "build-smoke/src/cli/aura" ]]; then
        AURA="build-smoke/src/cli/aura"
    else
        echo "error: aura not found (set AURA_BIN or add to PATH)" >&2
        exit 3
    fi
fi

PY=""
for cand in python3 python py; do
    if command -v "$cand" >/dev/null 2>&1 && "$cand" --version >/dev/null 2>&1; then
        PY="$cand"; break
    fi
done
[[ -z "$PY" ]] && { echo "error: no python interpreter found" >&2; exit 3; }

PAYLOAD="$("$AURA" --compact llm-context "$BINARY" --func "$ADDR")"

REQUEST="$(AURA_LLM_MODEL="$AURA_LLM_MODEL" \
           AURA_LLM_MAX_TOKENS="$MAX_TOKENS" \
           AURA_PAYLOAD="$PAYLOAD" \
           "$PY" -c '
import json, os
payload = json.loads(os.environ["AURA_PAYLOAD"])
req = {
  "model": os.environ["AURA_LLM_MODEL"],
  "messages": [
    {"role": "system",
     "content": ("You are a reverse-engineering assistant. Given a JSON "
                 "payload describing a function (name, address, size, "
                 "callers, callees, provenance), suggest one concise "
                 "descriptive identifier (snake_case, <=32 chars) based "
                 "on the signals. Reply with ONLY the identifier.")},
    {"role": "user", "content": json.dumps(payload, ensure_ascii=False)}
  ],
  "temperature": 0.2,
  "max_tokens": int(os.environ["AURA_LLM_MAX_TOKENS"])
}
print(json.dumps(req, ensure_ascii=False))
')"

CURL_ARGS=(-s --max-time 180 -H "Content-Type: application/json")
if [[ -n "${AURA_LLM_API_KEY:-}" ]]; then
    CURL_ARGS+=(-H "Authorization: Bearer ${AURA_LLM_API_KEY}")
fi

RESP="$(printf '%s' "$REQUEST" | curl "${CURL_ARGS[@]}" \
    "${AURA_LLM_BASE_URL%/}/chat/completions" --data-binary @-)"

AURA_RESP="$RESP" "$PY" -c '
import json, os, sys
raw = os.environ["AURA_RESP"]
try:
    r = json.loads(raw)
    print(r["choices"][0]["message"]["content"].strip())
except Exception as e:
    sys.stderr.write("llm-rename: malformed response (%s)\n" % e)
    sys.stderr.write(raw + "\n")
    sys.exit(1)
'
