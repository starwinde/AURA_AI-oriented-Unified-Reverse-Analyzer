// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm_client.c -- LlmClient 공통 로직 (vtable 디스패치, 편의 함수, 리소스 해제)
 */

#include "llm.h"
#include "llm_http.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ─────────────────────────────────────────────
 * vtable 디스패치
 * ───────────────────────────────────────────── */

AuraError llm_client_chat(LlmClient *client, const LlmRequest *req,
                          LlmResponse *resp)
{
    if (!client || !client->vt || !client->vt->chat || !req || !resp)
        return AURA_ERR_INVALID_ARG;

    memset(resp, 0, sizeof(*resp));
    return client->vt->chat(client->impl, req, resp);
}

const char *llm_client_backend_name(LlmClient *client)
{
    if (!client || !client->vt || !client->vt->backend_name)
        return "unknown";
    return client->vt->backend_name(client->impl);
}

void llm_client_destroy(LlmClient **client)
{
    if (!client || !*client) return;

    LlmClient *c = *client;
    if (c->vt && c->vt->destroy) {
        c->vt->destroy(c->impl);
    }
    free(c);
    *client = NULL;
}

/* ─────────────────────────────────────────────
 * 편의 함수
 * ───────────────────────────────────────────── */

AuraError llm_query(LlmClient *client, const char *system_prompt,
                    const char *user_prompt, LlmResponse *resp)
{
    if (!client || !user_prompt || !resp)
        return AURA_ERR_INVALID_ARG;

    LlmRequest req;
    memset(&req, 0, sizeof(req));

    size_t msg_count = system_prompt ? 2 : 1;
    LlmMessage *msgs = (LlmMessage *)calloc(msg_count, sizeof(LlmMessage));
    if (!msgs) return AURA_ERR_NOMEM;

    size_t idx = 0;
    if (system_prompt) {
        msgs[idx].role = LLM_ROLE_SYSTEM;
        msgs[idx].content = strdup(system_prompt);
        if (!msgs[idx].content) { free(msgs); return AURA_ERR_NOMEM; }
        idx++;
    }
    msgs[idx].role = LLM_ROLE_USER;
    msgs[idx].content = strdup(user_prompt);
    if (!msgs[idx].content) {
        for (size_t i = 0; i < idx; i++) free(msgs[i].content);
        free(msgs);
        return AURA_ERR_NOMEM;
    }

    req.messages = msgs;
    req.message_count = msg_count;
    req.temperature = LLM_DEFAULT_TEMPERATURE;
    req.max_tokens = LLM_DEFAULT_MAX_TOKENS;

    AuraError err = llm_client_chat(client, &req, resp);

    llm_request_cleanup(&req);
    return err;
}

/* ─────────────────────────────────────────────
 * 리소스 해제
 * ───────────────────────────────────────────── */

void llm_response_cleanup(LlmResponse *resp)
{
    if (!resp) return;
    free(resp->content);
    resp->content = NULL;
}

void llm_request_cleanup(LlmRequest *req)
{
    if (!req) return;
    if (req->messages) {
        for (size_t i = 0; i < req->message_count; i++) {
            free(req->messages[i].content);
            req->messages[i].content = NULL;
        }
        free(req->messages);
        req->messages = NULL;
    }
    req->message_count = 0;
}

/* ─────────────────────────────────────────────
 * 전역 초기화 / 해제
 * ───────────────────────────────────────────── */

AuraError llm_global_init(void)
{
    return llm_http_global_init();
}

void llm_global_cleanup(void)
{
    llm_http_global_cleanup();
}
