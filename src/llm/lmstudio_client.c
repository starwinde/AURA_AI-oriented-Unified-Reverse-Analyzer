// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * lmstudio_client.c -- LM Studio API 클라이언트 (OpenAI 호환)
 *
 * LM Studio가 제공하는 OpenAI Chat Completions 호환 REST API를 사용한다.
 * 엔드포인트: POST {base_url}/chat/completions
 *
 * D-4 확정: 로컬 LM Studio (localhost:1234/v1), 모델 qwen/qwen3-coder-next
 */

#include "llm.h"
#include "llm_http.h"

#include <cJSON.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ─────────────────────────────────────────────
 * 내부 구현 데이터
 * ───────────────────────────────────────────── */

typedef struct LmstudioImpl {
    char *base_url;   /* "http://localhost:1234/v1" */
    char *model;      /* "qwen/qwen3-coder-next" */
    char *api_key;    /* LM_API_TOKEN 환경변수에서 로드 (NULL 허용) */
} LmstudioImpl;

/* ─────────────────────────────────────────────
 * JSON 요청 빌드
 * ───────────────────────────────────────────── */

static char *build_chat_json(const LlmRequest *req, const char *model)
{
    cJSON *root = cJSON_CreateObject();
    if (!root) return NULL;

    cJSON_AddStringToObject(root, "model",
                            req->model ? req->model : model);
    cJSON_AddNumberToObject(root, "temperature", req->temperature);
    cJSON_AddNumberToObject(root, "max_tokens",
                            req->max_tokens > 0 ? req->max_tokens
                                                : LLM_DEFAULT_MAX_TOKENS);

    cJSON *messages = cJSON_AddArrayToObject(root, "messages");
    if (!messages) { cJSON_Delete(root); return NULL; }

    for (size_t i = 0; i < req->message_count; i++) {
        cJSON *msg = cJSON_CreateObject();
        if (!msg) { cJSON_Delete(root); return NULL; }

        const char *role_str = "user";
        switch (req->messages[i].role) {
        case LLM_ROLE_SYSTEM:    role_str = "system";    break;
        case LLM_ROLE_USER:      role_str = "user";      break;
        case LLM_ROLE_ASSISTANT: role_str = "assistant";  break;
        }
        cJSON_AddStringToObject(msg, "role", role_str);
        cJSON_AddStringToObject(msg, "content",
                                req->messages[i].content ? req->messages[i].content : "");
        cJSON_AddItemToArray(messages, msg);
    }

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_str;
}

/* ─────────────────────────────────────────────
 * JSON 응답 파싱
 * ───────────────────────────────────────────── */

static AuraError parse_chat_response(const char *body, LlmResponse *resp)
{
    if (!body || !resp) return AURA_ERR_INVALID_ARG;

    cJSON *root = cJSON_Parse(body);
    if (!root) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Invalid JSON response from LLM");
        resp->error = AURA_ERR_PARSE;
        return AURA_ERR_PARSE;
    }

    /* Check for error in response */
    cJSON *error_obj = cJSON_GetObjectItemCaseSensitive(root, "error");
    if (error_obj && cJSON_IsObject(error_obj)) {
        cJSON *msg = cJSON_GetObjectItemCaseSensitive(error_obj, "message");
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE, "LLM error: %s",
                 (msg && cJSON_IsString(msg)) ? msg->valuestring : "unknown");
        resp->error = AURA_ERR_LLM;
        cJSON_Delete(root);
        return AURA_ERR_LLM;
    }

    /* Extract content from choices[0].message.content */
    cJSON *choices = cJSON_GetObjectItemCaseSensitive(root, "choices");
    if (!choices || !cJSON_IsArray(choices) || cJSON_GetArraySize(choices) == 0) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "No choices in LLM response");
        resp->error = AURA_ERR_LLM;
        cJSON_Delete(root);
        return AURA_ERR_LLM;
    }

    cJSON *first = cJSON_GetArrayItem(choices, 0);
    cJSON *message = cJSON_GetObjectItemCaseSensitive(first, "message");
    cJSON *content = message ?
        cJSON_GetObjectItemCaseSensitive(message, "content") : NULL;

    if (!content || !cJSON_IsString(content) || !content->valuestring) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Empty response from LLM");
        resp->error = AURA_ERR_LLM;
        cJSON_Delete(root);
        return AURA_ERR_LLM;
    }

    resp->content = strdup(content->valuestring);
    if (!resp->content) {
        cJSON_Delete(root);
        return AURA_ERR_NOMEM;
    }

    /* Extract usage tokens (optional) */
    cJSON *usage = cJSON_GetObjectItemCaseSensitive(root, "usage");
    if (usage && cJSON_IsObject(usage)) {
        cJSON *pt = cJSON_GetObjectItemCaseSensitive(usage, "prompt_tokens");
        cJSON *ct = cJSON_GetObjectItemCaseSensitive(usage, "completion_tokens");
        cJSON *tt = cJSON_GetObjectItemCaseSensitive(usage, "total_tokens");
        if (pt && cJSON_IsNumber(pt)) resp->prompt_tokens = pt->valueint;
        if (ct && cJSON_IsNumber(ct)) resp->completion_tokens = ct->valueint;
        if (tt && cJSON_IsNumber(tt)) resp->total_tokens = tt->valueint;
    }

    resp->error = AURA_OK;
    cJSON_Delete(root);
    return AURA_OK;
}

/* ─────────────────────────────────────────────
 * vtable 구현
 * ───────────────────────────────────────────── */

static AuraError lmstudio_chat(void *impl, const LlmRequest *req,
                               LlmResponse *resp)
{
    LmstudioImpl *ls = (LmstudioImpl *)impl;

    char *json_body = build_chat_json(req, ls->model);
    if (!json_body) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Failed to build request JSON");
        resp->error = AURA_ERR_NOMEM;
        return AURA_ERR_NOMEM;
    }

    /* Build URL: {base_url}/chat/completions */
    size_t url_len = strlen(ls->base_url) + 32;
    char *url = (char *)malloc(url_len);
    if (!url) {
        free(json_body);
        return AURA_ERR_NOMEM;
    }
    snprintf(url, url_len, "%s/chat/completions", ls->base_url);

    /* Build auth header if API key is set */
    char *auth_header = NULL;
    if (ls->api_key && ls->api_key[0] != '\0') {
        size_t ah_len = strlen("Authorization: Bearer ") + strlen(ls->api_key) + 1;
        auth_header = (char *)malloc(ah_len);
        if (auth_header)
            snprintf(auth_header, ah_len, "Authorization: Bearer %s", ls->api_key);
    }

    HttpResponse http_resp;
    AuraError err = llm_http_post_json(url, json_body, auth_header,
                                       LLM_DEFAULT_RESPONSE_SEC, &http_resp);
    free(url);
    free(json_body);
    free(auth_header);

    if (err != AURA_OK) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Connection to LM Studio failed (is it running at %s?)",
                 ls->base_url);
        resp->error = AURA_ERR_LLM;
        return AURA_ERR_LLM;
    }

    /* Check HTTP status */
    if (http_resp.http_status != 200) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "LM Studio returned HTTP %ld", http_resp.http_status);
        resp->error = AURA_ERR_LLM;
        llm_http_response_cleanup(&http_resp);
        return AURA_ERR_LLM;
    }

    err = parse_chat_response(http_resp.body, resp);
    llm_http_response_cleanup(&http_resp);
    return err;
}

static void lmstudio_destroy(void *impl)
{
    if (!impl) return;
    LmstudioImpl *ls = (LmstudioImpl *)impl;
    free(ls->base_url);
    ls->base_url = NULL;
    free(ls->model);
    ls->model = NULL;
    free(ls->api_key);
    ls->api_key = NULL;
    free(ls);
}

static const char *lmstudio_backend_name(void *impl)
{
    (void)impl;
    return "lmstudio";
}

static const LlmClientVtable g_lmstudio_vtable = {
    .chat         = lmstudio_chat,
    .destroy      = lmstudio_destroy,
    .backend_name = lmstudio_backend_name,
};

/* ─────────────────────────────────────────────
 * 팩토리 함수
 * ───────────────────────────────────────────── */

LlmClient *llm_client_create_lmstudio(const char *base_url, const char *model)
{
    LmstudioImpl *impl = (LmstudioImpl *)calloc(1, sizeof(LmstudioImpl));
    if (!impl) return NULL;

    impl->base_url = strdup(base_url ? base_url : LLM_DEFAULT_LMSTUDIO_URL);
    impl->model    = strdup(model ? model : LLM_DEFAULT_LMSTUDIO_MODEL);

    /* LM Studio API 토큰 (환경변수, 선택적) */
    const char *token = getenv("LM_API_TOKEN");
    if (token && token[0] != '\0')
        impl->api_key = strdup(token);

    if (!impl->base_url || !impl->model) {
        lmstudio_destroy(impl);
        return NULL;
    }

    /* Remove trailing slash from base_url if present */
    size_t len = strlen(impl->base_url);
    if (len > 0 && impl->base_url[len - 1] == '/') {
        impl->base_url[len - 1] = '\0';
    }

    LlmClient *client = (LlmClient *)calloc(1, sizeof(LlmClient));
    if (!client) {
        lmstudio_destroy(impl);
        return NULL;
    }

    client->vt = &g_lmstudio_vtable;
    client->impl = impl;
    return client;
}
