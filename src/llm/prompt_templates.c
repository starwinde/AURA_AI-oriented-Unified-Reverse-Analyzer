// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * prompt_templates.c -- LLM 프롬프트 템플릿 및 응답 파서 (Phase 6.5)
 *
 * 분석 목적별 프롬프트를 구성하고, LLM 응답에서 결과를 추출한다.
 *
 * 템플릿 목록:
 *   - LLM_PROMPT_FUNC_NAME:    함수명 제안 (디스어셈블리 → JSON {"name": "..."})
 *   - LLM_PROMPT_CODE_SUMMARY: 코드 요약 (Pseudo-C → 자유 텍스트)
 */

#include "llm.h"

#include <cJSON.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* =====================================================================
 * 시스템 프롬프트 상수
 * ===================================================================== */

static const char *FUNC_NAME_SYSTEM =
    "You are a reverse engineering assistant. "
    "Analyze the given x86/x86_64 disassembly code and suggest a single "
    "descriptive function name that captures the function's purpose. "
    "Respond ONLY with a JSON object in this exact format: "
    "{\"name\": \"suggested_function_name\"}\n"
    "Use snake_case naming. Do not include any other text.";

static const char *CODE_SUMMARY_SYSTEM =
    "You are a reverse engineering assistant. "
    "Summarize what the given decompiled function does in one concise paragraph. "
    "Focus on the function's purpose, key operations, and any notable patterns "
    "(e.g., string manipulation, memory allocation, file I/O, cryptographic operations). "
    "Keep the summary under 200 words.";

static const char *VULN_ANALYSIS_SYSTEM =
    "You are a security vulnerability analyst specializing in binary reverse engineering. "
    "Analyze the given disassembly or decompiled code for security vulnerabilities. "
    "For each vulnerability found, provide:\n"
    "1. **Vulnerability type** (e.g., buffer overflow, format string, use-after-free, "
    "integer overflow, command injection, race condition)\n"
    "2. **Severity** (Critical / High / Medium / Low)\n"
    "3. **Location** — which instructions or lines are affected\n"
    "4. **Description** — what the vulnerability is and how it could be exploited\n"
    "5. **Recommendation** — how to fix or mitigate it\n\n"
    "If no vulnerabilities are found, state that explicitly. "
    "Be concise but thorough. Focus on real, exploitable issues rather than theoretical ones.";

/* =====================================================================
 * llm_prompt_build
 * ===================================================================== */

AuraError llm_prompt_build(LlmPromptType type, const char *input,
                           LlmRequest *out_req)
{
    if (!input || !out_req || type >= LLM_PROMPT_COUNT)
        return AURA_ERR_INVALID_ARG;

    memset(out_req, 0, sizeof(*out_req));

    const char *system_prompt = NULL;
    switch (type) {
    case LLM_PROMPT_FUNC_NAME:
        system_prompt = FUNC_NAME_SYSTEM;
        break;
    case LLM_PROMPT_CODE_SUMMARY:
        system_prompt = CODE_SUMMARY_SYSTEM;
        break;
    case LLM_PROMPT_VULN_ANALYSIS:
        system_prompt = VULN_ANALYSIS_SYSTEM;
        break;
    default:
        return AURA_ERR_INVALID_ARG;
    }

    LlmMessage *msgs = (LlmMessage *)calloc(2, sizeof(LlmMessage));
    if (!msgs) return AURA_ERR_NOMEM;

    msgs[0].role = LLM_ROLE_SYSTEM;
    msgs[0].content = strdup(system_prompt);
    if (!msgs[0].content) {
        free(msgs);
        return AURA_ERR_NOMEM;
    }

    msgs[1].role = LLM_ROLE_USER;
    msgs[1].content = strdup(input);
    if (!msgs[1].content) {
        free(msgs[0].content);
        free(msgs);
        return AURA_ERR_NOMEM;
    }

    out_req->messages = msgs;
    out_req->message_count = 2;
    out_req->temperature = LLM_DEFAULT_TEMPERATURE;
    out_req->max_tokens = LLM_DEFAULT_MAX_TOKENS;

    return AURA_OK;
}

/* =====================================================================
 * llm_prompt_parse_func_name
 *
 * LLM 응답에서 JSON {"name": "..."} 형식의 함수명을 추출한다.
 * JSON 파싱 실패 시, 응답 텍스트에서 JSON 부분을 찾아 재시도한다.
 * ===================================================================== */

AuraError llm_prompt_parse_func_name(const char *response,
                                     char *out_name, size_t name_sz)
{
    if (!response || !out_name || name_sz == 0)
        return AURA_ERR_INVALID_ARG;

    out_name[0] = '\0';

    /* 1차: 전체 응답을 JSON으로 파싱 */
    cJSON *root = cJSON_Parse(response);

    /* 2차: JSON이 아닌 경우, 응답 내에서 '{' ~ '}' 블록을 찾아 재시도 */
    if (!root) {
        const char *brace = strchr(response, '{');
        if (brace) {
            root = cJSON_Parse(brace);
        }
    }

    if (!root) {
        return AURA_ERR_PARSE;
    }

    cJSON *name = cJSON_GetObjectItemCaseSensitive(root, "name");
    if (!name || !cJSON_IsString(name) || !name->valuestring ||
        name->valuestring[0] == '\0') {
        cJSON_Delete(root);
        return AURA_ERR_PARSE;
    }

    snprintf(out_name, name_sz, "%s", name->valuestring);
    cJSON_Delete(root);
    return AURA_OK;
}

/* =====================================================================
 * llm_prompt_parse_summary
 *
 * 코드 요약은 자유 텍스트이므로 응답을 그대로 복사한다.
 * 앞뒤 공백만 제거한다.
 * ===================================================================== */

AuraError llm_prompt_parse_summary(const char *response,
                                   char *out_summary, size_t summary_sz)
{
    if (!response || !out_summary || summary_sz == 0)
        return AURA_ERR_INVALID_ARG;

    out_summary[0] = '\0';

    /* 앞뒤 공백 제거 */
    const char *start = response;
    while (*start == ' ' || *start == '\n' || *start == '\r' || *start == '\t')
        start++;

    if (*start == '\0')
        return AURA_ERR_PARSE;

    const char *end = start + strlen(start) - 1;
    while (end > start &&
           (*end == ' ' || *end == '\n' || *end == '\r' || *end == '\t'))
        end--;

    size_t len = (size_t)(end - start) + 1;
    if (len >= summary_sz)
        len = summary_sz - 1;

    memcpy(out_summary, start, len);
    out_summary[len] = '\0';

    return AURA_OK;
}

/* =====================================================================
 * llm_prompt_parse_vuln
 *
 * 취약점 분석 응답은 자유 텍스트 — 그대로 복사 (7.6)
 * ===================================================================== */

AuraError llm_prompt_parse_vuln(const char *response,
                                char *out_report, size_t report_sz)
{
    /* 동일 로직: 앞뒤 공백 제거 후 복사 */
    return llm_prompt_parse_summary(response, out_report, report_sz);
}
