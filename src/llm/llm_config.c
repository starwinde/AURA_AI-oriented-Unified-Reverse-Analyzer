// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm_config.c -- LLM 설정 관리 (Phase 7.4)
 *
 * ~/.config/aura/config.json에서 LLM 설정을 로드/저장한다.
 * API 키는 평문 저장 (MVP 기준, 암호화는 이후).
 *
 * 설계: docs/design/llm_integration.md §8, §13.4
 */

#include "llm.h"
#include "llm_config.h"

#include <cJSON.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

/* =====================================================================
 * 내부 전역 설정 상태
 * ===================================================================== */

static LlmConfig g_config;
static int g_config_loaded = 0;

/* =====================================================================
 * 헬퍼: 기본 경로
 * ===================================================================== */

static const char *default_config_path(void)
{
    static char path[512];
    const char *home = getenv("HOME");
    if (!home) home = "/tmp";
    snprintf(path, sizeof(path), "%s/.config/aura/config.json", home);
    return path;
}

static void ensure_parent_dir(const char *filepath)
{
    char dir[512];
    strncpy(dir, filepath, sizeof(dir) - 1);
    dir[sizeof(dir) - 1] = '\0';

    /* 마지막 '/' 이전까지를 디렉토리로 */
    char *last_slash = strrchr(dir, '/');
    if (!last_slash) return;
    *last_slash = '\0';

    /* 재귀적 mkdir: 간단하게 상위 -> 하위 순서 */
    char tmp[512];
    char *p = NULL;
    snprintf(tmp, sizeof(tmp), "%s", dir);
    for (p = tmp + 1; *p; p++) {
        if (*p == '/') {
            *p = '\0';
            mkdir(tmp, 0755);
            *p = '/';
        }
    }
    mkdir(tmp, 0755);
}

/* =====================================================================
 * 헬퍼: 문자열 복사
 * ===================================================================== */

static char *safe_strdup(const char *s)
{
    return s ? strdup(s) : NULL;
}

static const char *json_str(cJSON *obj, const char *key,
                            const char *fallback)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsString(item) && item->valuestring)
        return item->valuestring;
    return fallback;
}

static double json_num(cJSON *obj, const char *key, double fallback)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsNumber(item))
        return item->valuedouble;
    return fallback;
}

static int json_bool(cJSON *obj, const char *key, int fallback)
{
    cJSON *item = cJSON_GetObjectItemCaseSensitive(obj, key);
    if (cJSON_IsBool(item))
        return cJSON_IsTrue(item) ? 1 : 0;
    return fallback;
}

/* =====================================================================
 * 기본값 초기화
 * ===================================================================== */

static void config_set_defaults(LlmConfig *cfg)
{
    memset(cfg, 0, sizeof(*cfg));

    cfg->default_backend = strdup("lmstudio");

    cfg->lmstudio_url   = strdup(LLM_DEFAULT_LMSTUDIO_URL);
    cfg->lmstudio_model = strdup(LLM_DEFAULT_LMSTUDIO_MODEL);

    cfg->llamacpp_url   = strdup(LLM_DEFAULT_LLAMACPP_URL);
    cfg->llamacpp_model = strdup("default");

    cfg->openai_api_key_env = strdup("OPENAI_API_KEY");
    cfg->openai_model       = strdup("gpt-4o");

    cfg->groq_api_key_env = strdup("GROQ_API_KEY");
    cfg->groq_model       = strdup("llama-3.3-70b-versatile");

    cfg->cache_enabled = 1;
    cfg->cache_ttl_hours = 24;
    cfg->cache_dir = NULL; /* NULL → 기본 경로 */

    cfg->temperature = LLM_DEFAULT_TEMPERATURE;
    cfg->max_tokens  = LLM_DEFAULT_MAX_TOKENS;
    cfg->connect_sec  = LLM_DEFAULT_CONNECT_SEC;
    cfg->response_sec = LLM_DEFAULT_RESPONSE_SEC;
}

/* =====================================================================
 * 공개 API: 로드
 * ===================================================================== */

AuraError llm_config_load(const char *config_path)
{
    if (g_config_loaded) llm_config_cleanup();

    config_set_defaults(&g_config);
    g_config_loaded = 1;

    const char *path = config_path ? config_path : default_config_path();

    FILE *f = fopen(path, "r");
    if (!f) {
        /* 파일 없음 → 기본값 사용 (에러 아님) */
        return AURA_OK;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (len <= 0) {
        fclose(f);
        return AURA_OK;
    }

    char *buf = (char *)malloc((size_t)len + 1);
    if (!buf) {
        fclose(f);
        return AURA_ERR_NOMEM;
    }

    size_t rd = fread(buf, 1, (size_t)len, f);
    fclose(f);
    buf[rd] = '\0';

    cJSON *root = cJSON_Parse(buf);
    free(buf);
    if (!root) return AURA_OK; /* 파싱 실패 → 기본값 사용 */

    cJSON *llm = cJSON_GetObjectItemCaseSensitive(root, "llm");
    if (!cJSON_IsObject(llm)) {
        cJSON_Delete(root);
        return AURA_OK;
    }

    /* default_backend */
    const char *backend = json_str(llm, "default_backend", NULL);
    if (backend) {
        free(g_config.default_backend);
        g_config.default_backend = strdup(backend);
    }

    /* lmstudio */
    cJSON *ls = cJSON_GetObjectItemCaseSensitive(llm, "lmstudio");
    if (cJSON_IsObject(ls)) {
        const char *v;
        v = json_str(ls, "base_url", NULL);
        if (v) { free(g_config.lmstudio_url); g_config.lmstudio_url = strdup(v); }
        v = json_str(ls, "model", NULL);
        if (v) { free(g_config.lmstudio_model); g_config.lmstudio_model = strdup(v); }
    }

    /* llamacpp */
    cJSON *lc = cJSON_GetObjectItemCaseSensitive(llm, "llamacpp");
    if (cJSON_IsObject(lc)) {
        const char *v;
        v = json_str(lc, "base_url", NULL);
        if (v) { free(g_config.llamacpp_url); g_config.llamacpp_url = strdup(v); }
        v = json_str(lc, "model", NULL);
        if (v) { free(g_config.llamacpp_model); g_config.llamacpp_model = strdup(v); }
    }

    /* openai */
    cJSON *oa = cJSON_GetObjectItemCaseSensitive(llm, "openai");
    if (cJSON_IsObject(oa)) {
        const char *v;
        v = json_str(oa, "api_key_env", NULL);
        if (v) { free(g_config.openai_api_key_env); g_config.openai_api_key_env = strdup(v); }
        v = json_str(oa, "model", NULL);
        if (v) { free(g_config.openai_model); g_config.openai_model = strdup(v); }
    }

    /* groq */
    cJSON *gq = cJSON_GetObjectItemCaseSensitive(llm, "groq");
    if (cJSON_IsObject(gq)) {
        const char *v;
        v = json_str(gq, "api_key_env", NULL);
        if (v) { free(g_config.groq_api_key_env); g_config.groq_api_key_env = strdup(v); }
        v = json_str(gq, "model", NULL);
        if (v) { free(g_config.groq_model); g_config.groq_model = strdup(v); }
    }

    /* cache */
    cJSON *cache = cJSON_GetObjectItemCaseSensitive(llm, "cache");
    if (cJSON_IsObject(cache)) {
        g_config.cache_enabled = json_bool(cache, "enabled", 1);
        g_config.cache_ttl_hours = (int)json_num(cache, "ttl_hours", 24);
        const char *v = json_str(cache, "dir", NULL);
        if (v) { free(g_config.cache_dir); g_config.cache_dir = strdup(v); }
    }

    /* timeout */
    cJSON *timeout = cJSON_GetObjectItemCaseSensitive(llm, "timeout");
    if (cJSON_IsObject(timeout)) {
        g_config.connect_sec = (int)json_num(timeout, "connect_sec",
                                             LLM_DEFAULT_CONNECT_SEC);
        g_config.response_sec = (int)json_num(timeout, "response_sec",
                                              LLM_DEFAULT_RESPONSE_SEC);
    }

    g_config.temperature = json_num(llm, "temperature", LLM_DEFAULT_TEMPERATURE);
    g_config.max_tokens = (int)json_num(llm, "max_tokens", LLM_DEFAULT_MAX_TOKENS);

    cJSON_Delete(root);
    return AURA_OK;
}

/* =====================================================================
 * 공개 API: 저장
 * ===================================================================== */

AuraError llm_config_save(const char *config_path)
{
    if (!g_config_loaded) return AURA_ERR_INVALID_ARG;

    const char *path = config_path ? config_path : default_config_path();
    ensure_parent_dir(path);

    cJSON *root = cJSON_CreateObject();
    if (!root) return AURA_ERR_NOMEM;

    cJSON *llm = cJSON_AddObjectToObject(root, "llm");

    cJSON_AddStringToObject(llm, "default_backend",
                            g_config.default_backend ? g_config.default_backend : "lmstudio");

    /* lmstudio */
    cJSON *ls = cJSON_AddObjectToObject(llm, "lmstudio");
    cJSON_AddStringToObject(ls, "base_url", g_config.lmstudio_url ? g_config.lmstudio_url : "");
    cJSON_AddStringToObject(ls, "model", g_config.lmstudio_model ? g_config.lmstudio_model : "");

    /* llamacpp */
    cJSON *lc = cJSON_AddObjectToObject(llm, "llamacpp");
    cJSON_AddStringToObject(lc, "base_url", g_config.llamacpp_url ? g_config.llamacpp_url : "");
    cJSON_AddStringToObject(lc, "model", g_config.llamacpp_model ? g_config.llamacpp_model : "");

    /* openai */
    cJSON *oa = cJSON_AddObjectToObject(llm, "openai");
    cJSON_AddStringToObject(oa, "api_key_env",
                            g_config.openai_api_key_env ? g_config.openai_api_key_env : "OPENAI_API_KEY");
    cJSON_AddStringToObject(oa, "model", g_config.openai_model ? g_config.openai_model : "gpt-4o");

    /* groq */
    cJSON *gq = cJSON_AddObjectToObject(llm, "groq");
    cJSON_AddStringToObject(gq, "api_key_env",
                            g_config.groq_api_key_env ? g_config.groq_api_key_env : "GROQ_API_KEY");
    cJSON_AddStringToObject(gq, "model", g_config.groq_model ? g_config.groq_model : "llama-3.3-70b-versatile");

    /* cache */
    cJSON *cache = cJSON_AddObjectToObject(llm, "cache");
    cJSON_AddBoolToObject(cache, "enabled", g_config.cache_enabled);
    cJSON_AddNumberToObject(cache, "ttl_hours", g_config.cache_ttl_hours);
    if (g_config.cache_dir)
        cJSON_AddStringToObject(cache, "dir", g_config.cache_dir);

    /* timeout */
    cJSON *timeout = cJSON_AddObjectToObject(llm, "timeout");
    cJSON_AddNumberToObject(timeout, "connect_sec", g_config.connect_sec);
    cJSON_AddNumberToObject(timeout, "response_sec", g_config.response_sec);

    cJSON_AddNumberToObject(llm, "temperature", g_config.temperature);
    cJSON_AddNumberToObject(llm, "max_tokens", g_config.max_tokens);

    char *json_str = cJSON_Print(root);
    cJSON_Delete(root);
    if (!json_str) return AURA_ERR_NOMEM;

    FILE *f = fopen(path, "w");
    if (!f) {
        free(json_str);
        return AURA_ERR_IO;
    }

    fputs(json_str, f);
    fputc('\n', f);
    fclose(f);
    free(json_str);

    return AURA_OK;
}

/* =====================================================================
 * 공개 API: 설정 접근
 * ===================================================================== */

const char *llm_config_get_backend(void)
{
    return g_config_loaded ? g_config.default_backend : "lmstudio";
}

const char *llm_config_get_api_key(const char *backend)
{
    if (!g_config_loaded || !backend) return NULL;

    const char *env_name = NULL;
    if (strcmp(backend, "openai") == 0)
        env_name = g_config.openai_api_key_env;
    else if (strcmp(backend, "groq") == 0)
        env_name = g_config.groq_api_key_env;

    if (!env_name) return NULL;
    return getenv(env_name);
}

const char *llm_config_get_model(const char *backend)
{
    if (!g_config_loaded || !backend) return NULL;

    if (strcmp(backend, "lmstudio") == 0) return g_config.lmstudio_model;
    if (strcmp(backend, "llamacpp") == 0) return g_config.llamacpp_model;
    if (strcmp(backend, "openai") == 0)   return g_config.openai_model;
    if (strcmp(backend, "groq") == 0)     return g_config.groq_model;
    return NULL;
}

LlmClient *llm_config_create_client(void)
{
    if (!g_config_loaded) return NULL;

    const char *backend = g_config.default_backend;
    if (!backend) return NULL;

    if (strcmp(backend, "lmstudio") == 0)
        return llm_client_create_lmstudio(g_config.lmstudio_url,
                                          g_config.lmstudio_model);
    if (strcmp(backend, "llamacpp") == 0)
        return llm_client_create_llamacpp(g_config.llamacpp_url,
                                          g_config.llamacpp_model);
    if (strcmp(backend, "openai") == 0)
        return llm_client_create_openai(llm_config_get_api_key("openai"),
                                        g_config.openai_model);
    if (strcmp(backend, "groq") == 0)
        return llm_client_create_groq(llm_config_get_api_key("groq"),
                                      g_config.groq_model);

    return NULL;
}

const LlmConfig *llm_config_get(void)
{
    return g_config_loaded ? &g_config : NULL;
}

/* =====================================================================
 * 공개 API: 설정 변경 (GUI에서 호출)
 * ===================================================================== */

void llm_config_set_backend(const char *backend)
{
    if (!g_config_loaded || !backend) return;
    free(g_config.default_backend);
    g_config.default_backend = strdup(backend);
}

void llm_config_set_openai_model(const char *model)
{
    if (!g_config_loaded || !model) return;
    free(g_config.openai_model);
    g_config.openai_model = strdup(model);
}

void llm_config_set_groq_model(const char *model)
{
    if (!g_config_loaded || !model) return;
    free(g_config.groq_model);
    g_config.groq_model = strdup(model);
}

/* =====================================================================
 * 공개 API: 해제
 * ===================================================================== */

void llm_config_cleanup(void)
{
    if (!g_config_loaded) return;

    free(g_config.default_backend);
    free(g_config.lmstudio_url);
    free(g_config.lmstudio_model);
    free(g_config.llamacpp_url);
    free(g_config.llamacpp_model);
    free(g_config.openai_api_key_env);
    free(g_config.openai_model);
    free(g_config.groq_api_key_env);
    free(g_config.groq_model);
    free(g_config.cache_dir);

    memset(&g_config, 0, sizeof(g_config));
    g_config_loaded = 0;
}
