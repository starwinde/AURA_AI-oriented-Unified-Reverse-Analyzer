// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * groq_client.c -- Groq API 클라이언트 구현 (Phase 7.3)
 *
 * Groq는 OpenAI 호환 API를 제공하므로 openai_compat_chat()를 재사용한다.
 *
 * 설계: docs/design/llm_integration.md §13.3
 */

#include "llm.h"
#include "openai_compat.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* =====================================================================
 * 내부 구현 데이터
 * ===================================================================== */

typedef struct GroqImpl {
    char *base_url;   /* "https://api.groq.com/openai/v1" */
    char *api_key;    /* heap 복사본 */
    char *model;      /* "llama-3.3-70b-versatile" 등 */
} GroqImpl;

#define GROQ_DEFAULT_URL   "https://api.groq.com/openai/v1"
#define GROQ_DEFAULT_MODEL "llama-3.3-70b-versatile"

/* =====================================================================
 * vtable 구현
 * ===================================================================== */

static AuraError groq_chat(void *impl, const LlmRequest *req,
                           LlmResponse *resp)
{
    GroqImpl *gi = (GroqImpl *)impl;
    return openai_compat_chat(gi->base_url, gi->api_key, gi->model,
                              "Groq", req, resp);
}

static void groq_destroy(void *impl)
{
    GroqImpl *gi = (GroqImpl *)impl;
    if (!gi) return;
    free(gi->base_url);
    free(gi->api_key);
    free(gi->model);
    free(gi);
}

static const char *groq_backend_name(void *impl)
{
    (void)impl;
    return "groq";
}

static const LlmClientVtable groq_vtable = {
    .chat         = groq_chat,
    .destroy      = groq_destroy,
    .backend_name = groq_backend_name,
};

/* =====================================================================
 * 팩토리 함수
 * ===================================================================== */

LlmClient *llm_client_create_groq(const char *api_key, const char *model)
{
    /* API 키 해석 */
    const char *key = api_key;
    if (!key) key = getenv("GROQ_API_KEY");
    if (!key || key[0] == '\0') {
        fprintf(stderr, "[groq] API key not provided. "
                "Set GROQ_API_KEY or pass api_key parameter.\n");
        return NULL;
    }

    GroqImpl *impl = (GroqImpl *)calloc(1, sizeof(GroqImpl));
    if (!impl) return NULL;

    impl->base_url = strdup(GROQ_DEFAULT_URL);
    impl->api_key  = strdup(key);
    impl->model    = strdup(model ? model : GROQ_DEFAULT_MODEL);

    if (!impl->base_url || !impl->api_key || !impl->model) {
        groq_destroy(impl);
        return NULL;
    }

    LlmClient *client = (LlmClient *)calloc(1, sizeof(LlmClient));
    if (!client) {
        groq_destroy(impl);
        return NULL;
    }

    client->vt   = &groq_vtable;
    client->impl = impl;
    return client;
}
