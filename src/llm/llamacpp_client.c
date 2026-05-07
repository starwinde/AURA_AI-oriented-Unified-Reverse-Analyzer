// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llamacpp_client.c -- llama.cpp 서버 API 클라이언트 (HTTP 기반)
 *
 * llama.cpp의 서버 모드는 OpenAI Chat Completions 호환 API를 제공한다.
 * 엔드포인트: POST {base_url}/chat/completions
 *
 * LM Studio 클라이언트와 동일한 LlmClient 인터페이스를 구현한다.
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

typedef struct LlamacppImpl {
    char *base_url;   /* "http://localhost:8080/v1" */
    char *model;      /* "default" */
} LlamacppImpl;

/* ─────────────────────────────────────────────
 * JSON 요청 빌드 (OpenAI 형식)
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
                 "Invalid JSON response from llama.cpp");
        resp->error = AURA_ERR_PARSE;
        return AURA_ERR_PARSE;
    }

    cJSON *error_obj = cJSON_GetObjectItemCaseSensitive(root, "error");
    if (error_obj && cJSON_IsObject(error_obj)) {
        cJSON *msg = cJSON_GetObjectItemCaseSensitive(error_obj, "message");
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE, "llama.cpp error: %s",
                 (msg && cJSON_IsString(msg)) ? msg->valuestring : "unknown");
        resp->error = AURA_ERR_LLM;
        cJSON_Delete(root);
        return AURA_ERR_LLM;
    }

    cJSON *choices = cJSON_GetObjectItemCaseSensitive(root, "choices");
    if (!choices || !cJSON_IsArray(choices) || cJSON_GetArraySize(choices) == 0) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "No choices in llama.cpp response");
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
                 "Empty response from llama.cpp");
        resp->error = AURA_ERR_LLM;
        cJSON_Delete(root);
        return AURA_ERR_LLM;
    }

    resp->content = strdup(content->valuestring);
    if (!resp->content) {
        cJSON_Delete(root);
        return AURA_ERR_NOMEM;
    }

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

static AuraError llamacpp_chat(void *impl, const LlmRequest *req,
                               LlmResponse *resp)
{
    LlamacppImpl *lc = (LlamacppImpl *)impl;

    char *json_body = build_chat_json(req, lc->model);
    if (!json_body) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Failed to build request JSON");
        resp->error = AURA_ERR_NOMEM;
        return AURA_ERR_NOMEM;
    }

    size_t url_len = strlen(lc->base_url) + 32;
    char *url = (char *)malloc(url_len);
    if (!url) {
        free(json_body);
        return AURA_ERR_NOMEM;
    }
    snprintf(url, url_len, "%s/chat/completions", lc->base_url);

    HttpResponse http_resp;
    AuraError err = llm_http_post_json(url, json_body, NULL,
                                       LLM_DEFAULT_RESPONSE_SEC, &http_resp);
    free(url);
    free(json_body);

    if (err != AURA_OK) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "Connection to llama.cpp server failed (is it running at %s?)",
                 lc->base_url);
        resp->error = AURA_ERR_LLM;
        return AURA_ERR_LLM;
    }

    if (http_resp.http_status != 200) {
        snprintf(resp->error_msg, LLM_ERROR_MSG_SIZE,
                 "llama.cpp server returned HTTP %ld", http_resp.http_status);
        resp->error = AURA_ERR_LLM;
        llm_http_response_cleanup(&http_resp);
        return AURA_ERR_LLM;
    }

    err = parse_chat_response(http_resp.body, resp);
    llm_http_response_cleanup(&http_resp);
    return err;
}

static void llamacpp_destroy(void *impl)
{
    if (!impl) return;
    LlamacppImpl *lc = (LlamacppImpl *)impl;
    free(lc->base_url);
    lc->base_url = NULL;
    free(lc->model);
    lc->model = NULL;
    free(lc);
}

static const char *llamacpp_backend_name(void *impl)
{
    (void)impl;
    return "llamacpp";
}

static const LlmClientVtable g_llamacpp_vtable = {
    .chat         = llamacpp_chat,
    .destroy      = llamacpp_destroy,
    .backend_name = llamacpp_backend_name,
};

/* ─────────────────────────────────────────────
 * 팩토리 함수
 * ───────────────────────────────────────────── */

LlmClient *llm_client_create_llamacpp(const char *base_url, const char *model)
{
    LlamacppImpl *impl = (LlamacppImpl *)calloc(1, sizeof(LlamacppImpl));
    if (!impl) return NULL;

    impl->base_url = strdup(base_url ? base_url : LLM_DEFAULT_LLAMACPP_URL);
    impl->model    = strdup(model ? model : "default");

    if (!impl->base_url || !impl->model) {
        free(impl->base_url);
        free(impl->model);
        free(impl);
        return NULL;
    }

    size_t len = strlen(impl->base_url);
    if (len > 0 && impl->base_url[len - 1] == '/') {
        impl->base_url[len - 1] = '\0';
    }

    LlmClient *client = (LlmClient *)calloc(1, sizeof(LlmClient));
    if (!client) {
        llamacpp_destroy(impl);
        return NULL;
    }

    client->vt = &g_llamacpp_vtable;
    client->impl = impl;
    return client;
}
