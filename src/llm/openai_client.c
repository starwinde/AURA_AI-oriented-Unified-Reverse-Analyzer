// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * openai_client.c -- OpenAI API 클라이언트 구현 (Phase 7.2)
 *
 * OpenAI Chat Completions API 호환 클라이언트.
 * Groq 등 OpenAI 호환 API에서도 재사용 가능한 내부 헬퍼를 제공한다.
 *
 * 설계: docs/design/llm_integration.md §13.2
 */

#include "llm.h"
#include "llm_http.h"
#include "openai_compat.h"

#include <cJSON.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* =====================================================================
 * 내부 구현 데이터
 * ===================================================================== */

typedef struct OpenaiImpl {
    char *base_url;   /* "https://api.openai.com/v1" */
    char *api_key;    /* heap 복사본 */
    char *model;      /* "gpt-4o" 등 */
} OpenaiImpl;

#define OPENAI_DEFAULT_URL   "https://api.openai.com/v1"
#define OPENAI_DEFAULT_MODEL "gpt-4o"

/* =====================================================================
 * 내부 헬퍼: OpenAI 호환 JSON 요청 빌드
 * ===================================================================== */

/**
 * openai_compat_build_json -- OpenAI Chat Completions 형식 JSON 빌드
 *
 * OpenAI와 Groq 모두 동일한 형식을 사용하므로 공통 함수로 구현한다.
 *
 * @param model     모델명
 * @param req       LLM 요청
 * @return cJSON 문자열 (heap, 호출자 free). 실패 시 NULL.
 */
static char *openai_compat_build_json(const char *model,
                                      const LlmRequest *req)
{
    cJSON *root = cJSON_CreateObject();
    if (!root) return NULL;

    const char *use_model = req->model ? req->model : model;
    cJSON_AddStringToObject(root, "model", use_model);

    cJSON *messages = cJSON_AddArrayToObject(root, "messages");
    if (!messages) { cJSON_Delete(root); return NULL; }

    for (size_t i = 0; i < req->message_count; i++) {
        cJSON *msg = cJSON_CreateObject();
        if (!msg) { cJSON_Delete(root); return NULL; }

        const char *role_str;
        switch (req->messages[i].role) {
        case LLM_ROLE_SYSTEM:    role_str = "system";    break;
        case LLM_ROLE_ASSISTANT: role_str = "assistant";  break;
        default:                 role_str = "user";       break;
        }
        cJSON_AddStringToObject(msg, "role", role_str);
        cJSON_AddStringToObject(msg, "content",
                                req->messages[i].content ? req->messages[i].content : "");
        cJSON_AddItemToArray(messages, msg);
    }

    double temp = req->temperature;
    if (temp < 0.0) temp = LLM_DEFAULT_TEMPERATURE;
    cJSON_AddNumberToObject(root, "temperature", temp);

    int max_tok = req->max_tokens;
    if (max_tok <= 0) max_tok = LLM_DEFAULT_MAX_TOKENS;
    cJSON_AddNumberToObject(root, "max_tokens", max_tok);

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_str;
}

/* =====================================================================
 * 내부 헬퍼: OpenAI 호환 JSON 응답 파싱
 * ===================================================================== */

/**
 * openai_compat_parse_response -- OpenAI Chat Completions 응답 파싱
 *
 * @param http_resp    HTTP 응답
 * @param resp         LLM 응답 출력
 * @param backend_name 백엔드 이름 (에러 메시지용)
 * @return AURA_OK 또는 에러 코드
 */
static AuraError openai_compat_parse_response(const HttpResponse *http_resp,
                                              LlmResponse *resp,
                                              const char *backend_name)
{
    /* HTTP 에러 처리 */
    if (http_resp->http_status == 401) {
        resp->error = AURA_ERR_INVALID_ARG;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Invalid %s API key (HTTP 401)", backend_name);
        return AURA_ERR_INVALID_ARG;
    }
    if (http_resp->http_status == 429) {
        resp->error = AURA_ERR_LLM;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "%s rate limit exceeded (HTTP 429)", backend_name);
        return AURA_ERR_LLM;
    }
    if (http_resp->http_status >= 500) {
        resp->error = AURA_ERR_LLM;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "%s server error (HTTP %ld)", backend_name,
                 http_resp->http_status);
        return AURA_ERR_LLM;
    }
    if (http_resp->http_status != 200) {
        resp->error = AURA_ERR_LLM;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "%s unexpected HTTP status %ld", backend_name,
                 http_resp->http_status);
        return AURA_ERR_LLM;
    }

    /* JSON 파싱 */
    if (!http_resp->body || http_resp->body_len == 0) {
        resp->error = AURA_ERR_LLM;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Empty response from %s", backend_name);
        return AURA_ERR_LLM;
    }

    cJSON *root = cJSON_Parse(http_resp->body);
    if (!root) {
        resp->error = AURA_ERR_PARSE;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Invalid JSON response from %s", backend_name);
        return AURA_ERR_PARSE;
    }

    /* API 에러 객체 확인 */
    cJSON *error_obj = cJSON_GetObjectItemCaseSensitive(root, "error");
    if (cJSON_IsObject(error_obj)) {
        cJSON *err_msg = cJSON_GetObjectItemCaseSensitive(error_obj, "message");
        resp->error = AURA_ERR_LLM;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "%s API error: %s", backend_name,
                 cJSON_IsString(err_msg) ? err_msg->valuestring : "unknown");
        cJSON_Delete(root);
        return AURA_ERR_LLM;
    }

    /* choices[0].message.content 추출 */
    cJSON *choices = cJSON_GetObjectItemCaseSensitive(root, "choices");
    if (!cJSON_IsArray(choices) || cJSON_GetArraySize(choices) == 0) {
        resp->error = AURA_ERR_PARSE;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "No choices in %s response", backend_name);
        cJSON_Delete(root);
        return AURA_ERR_PARSE;
    }

    cJSON *first_choice = cJSON_GetArrayItem(choices, 0);
    cJSON *message = cJSON_GetObjectItemCaseSensitive(first_choice, "message");
    cJSON *content = cJSON_GetObjectItemCaseSensitive(message, "content");

    if (!cJSON_IsString(content) || !content->valuestring) {
        resp->error = AURA_ERR_PARSE;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Missing content in %s response", backend_name);
        cJSON_Delete(root);
        return AURA_ERR_PARSE;
    }

    resp->content = strdup(content->valuestring);
    if (!resp->content) {
        cJSON_Delete(root);
        return AURA_ERR_NOMEM;
    }

    /* usage 토큰 카운트 추출 */
    cJSON *usage = cJSON_GetObjectItemCaseSensitive(root, "usage");
    if (cJSON_IsObject(usage)) {
        cJSON *pt = cJSON_GetObjectItemCaseSensitive(usage, "prompt_tokens");
        cJSON *ct = cJSON_GetObjectItemCaseSensitive(usage, "completion_tokens");
        cJSON *tt = cJSON_GetObjectItemCaseSensitive(usage, "total_tokens");
        if (cJSON_IsNumber(pt)) resp->prompt_tokens = pt->valueint;
        if (cJSON_IsNumber(ct)) resp->completion_tokens = ct->valueint;
        if (cJSON_IsNumber(tt)) resp->total_tokens = tt->valueint;
    }

    resp->error = AURA_OK;
    cJSON_Delete(root);
    return AURA_OK;
}

/* =====================================================================
 * 내부 헬퍼: OpenAI 호환 chat 요청 실행
 * ===================================================================== */

/**
 * openai_compat_chat -- OpenAI 호환 API chat 요청 실행
 *
 * base_url, api_key, default_model, backend_name을 파라미터로 받아
 * OpenAI와 Groq 모두에서 사용한다.
 */
AuraError openai_compat_chat(const char *base_url,
                                    const char *api_key,
                                    const char *default_model,
                                    const char *backend_name,
                                    const LlmRequest *req,
                                    LlmResponse *resp)
{
    /* URL 빌드: base_url + "/chat/completions" */
    size_t url_len = strlen(base_url) + 32;
    char *url = (char *)malloc(url_len);
    if (!url) return AURA_ERR_NOMEM;
    snprintf(url, url_len, "%s/chat/completions", base_url);

    /* JSON 요청 빌드 */
    char *json_body = openai_compat_build_json(default_model, req);
    if (!json_body) {
        free(url);
        return AURA_ERR_NOMEM;
    }

    /* Authorization 헤더 빌드 */
    size_t auth_len = strlen("Authorization: Bearer ") + strlen(api_key) + 1;
    char *auth_header = (char *)malloc(auth_len);
    if (!auth_header) {
        free(url);
        free(json_body);
        return AURA_ERR_NOMEM;
    }
    snprintf(auth_header, auth_len, "Authorization: Bearer %s", api_key);

    /* HTTP POST */
    HttpResponse http_resp;
    AuraError err = llm_http_post_json(url, json_body, auth_header,
                                       LLM_DEFAULT_RESPONSE_SEC, &http_resp);

    free(url);
    free(json_body);
    free(auth_header);

    if (err != AURA_OK) {
        resp->error = AURA_ERR_LLM;
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Connection to %s failed", backend_name);
        return err;
    }

    /* 응답 파싱 */
    err = openai_compat_parse_response(&http_resp, resp, backend_name);
    llm_http_response_cleanup(&http_resp);
    return err;
}

/* =====================================================================
 * OpenAI vtable 구현
 * ===================================================================== */

static AuraError openai_chat(void *impl, const LlmRequest *req,
                             LlmResponse *resp)
{
    OpenaiImpl *oi = (OpenaiImpl *)impl;
    return openai_compat_chat(oi->base_url, oi->api_key, oi->model,
                              "OpenAI", req, resp);
}

static void openai_destroy(void *impl)
{
    OpenaiImpl *oi = (OpenaiImpl *)impl;
    if (!oi) return;
    free(oi->base_url);
    free(oi->api_key);
    free(oi->model);
    free(oi);
}

static const char *openai_backend_name(void *impl)
{
    (void)impl;
    return "openai";
}

static const LlmClientVtable openai_vtable = {
    .chat         = openai_chat,
    .destroy      = openai_destroy,
    .backend_name = openai_backend_name,
};

/* =====================================================================
 * 팩토리 함수
 * ===================================================================== */

LlmClient *llm_client_create_openai(const char *api_key, const char *model)
{
    /* API 키 해석 */
    const char *key = api_key;
    if (!key) key = getenv("OPENAI_API_KEY");
    if (!key || key[0] == '\0') {
        fprintf(stderr, "[openai] API key not provided. "
                "Set OPENAI_API_KEY or pass api_key parameter.\n");
        return NULL;
    }

    OpenaiImpl *impl = (OpenaiImpl *)calloc(1, sizeof(OpenaiImpl));
    if (!impl) return NULL;

    impl->base_url = strdup(OPENAI_DEFAULT_URL);
    impl->api_key  = strdup(key);
    impl->model    = strdup(model ? model : OPENAI_DEFAULT_MODEL);

    if (!impl->base_url || !impl->api_key || !impl->model) {
        openai_destroy(impl);
        return NULL;
    }

    LlmClient *client = (LlmClient *)calloc(1, sizeof(LlmClient));
    if (!client) {
        openai_destroy(impl);
        return NULL;
    }

    client->vt   = &openai_vtable;
    client->impl = impl;
    return client;
}
