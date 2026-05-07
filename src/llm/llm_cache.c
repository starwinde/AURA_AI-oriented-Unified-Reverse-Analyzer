// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm_cache.c -- LLM 응답 캐시 시스템 (Phase 6.4 + 7.5)
 *
 * 파일 기반 JSON 캐시. 로컬과 클라우드 백엔드 모두에서 사용.
 * 캐시 키 = SHA256(model + system + user + temperature).
 * TTL 기반 만료 (기본 24시간).
 *
 * 설계: docs/design/llm_integration.md §6
 */

#include "llm.h"

#include <cJSON.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>

/* =====================================================================
 * 내부 상태
 * ===================================================================== */

static char g_cache_dir[512] = {0};
static int  g_cache_initialized = 0;
static int  g_cache_ttl_hours = 24;

/* =====================================================================
 * 헬퍼: 디렉토리 생성
 * ===================================================================== */

static void ensure_dir(const char *dir)
{
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
 * 헬퍼: 간단한 SHA256-like 해시 (djb2 × 2)
 *
 * MVP용 경량 해시. 보안이 아닌 캐시 키 용도이므로 충돌 허용.
 * 진정한 SHA256은 MVP 이후 외부 라이브러리 추가 시 전환.
 * ===================================================================== */

static void cache_hash(const char *s1, const char *s2, const char *s3,
                       const char *s4, char *out_hex, size_t hex_sz)
{
    /* djb2 해시 두 개로 16바이트 해시 생성 */
    unsigned long h1 = 5381;
    unsigned long h2 = 0x1505;

    const char *parts[] = {s1, s2, s3, s4};
    for (int p = 0; p < 4; p++) {
        if (!parts[p]) continue;
        for (const char *c = parts[p]; *c; c++) {
            h1 = ((h1 << 5) + h1) + (unsigned char)*c;
            h2 = ((h2 << 5) + h2) ^ (unsigned char)*c;
        }
        /* 구분자 */
        h1 = ((h1 << 5) + h1);
        h2 = ((h2 << 5) + h2);
    }

    snprintf(out_hex, hex_sz, "%08lx%08lx", h1, h2);
}

/* =====================================================================
 * 헬퍼: 캐시 파일 경로
 * ===================================================================== */

static void cache_filepath(const char *key, char *out, size_t out_sz)
{
    snprintf(out, out_sz, "%s/%s.json", g_cache_dir, key);
}

/* =====================================================================
 * 공개 API
 * ===================================================================== */

AuraError llm_cache_init(const char *cache_dir)
{
    if (cache_dir) {
        snprintf(g_cache_dir, sizeof(g_cache_dir), "%s", cache_dir);
    } else {
        const char *home = getenv("HOME");
        if (!home) home = "/tmp";
        snprintf(g_cache_dir, sizeof(g_cache_dir),
                 "%s/.cache/aura/llm", home);
    }

    ensure_dir(g_cache_dir);
    g_cache_initialized = 1;
    return AURA_OK;
}

AuraError llm_cache_lookup(const char *key, LlmResponse *resp)
{
    if (!g_cache_initialized || !key || !resp)
        return AURA_ERR_INVALID_ARG;

    char path[1024];
    cache_filepath(key, path, sizeof(path));

    FILE *f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "[llm_cache] MISS: %s\n", key);
        return AURA_ERR_NOT_FOUND;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (len <= 0) {
        fclose(f);
        return AURA_ERR_NOT_FOUND;
    }

    char *buf = (char *)malloc((size_t)len + 1);
    if (!buf) { fclose(f); return AURA_ERR_NOMEM; }

    size_t rd = fread(buf, 1, (size_t)len, f);
    fclose(f);
    buf[rd] = '\0';

    cJSON *root = cJSON_Parse(buf);
    free(buf);
    if (!root) return AURA_ERR_NOT_FOUND;

    /* TTL 확인 */
    cJSON *created = cJSON_GetObjectItemCaseSensitive(root, "created_at");
    cJSON *ttl = cJSON_GetObjectItemCaseSensitive(root, "ttl_hours");
    if (cJSON_IsNumber(created) && cJSON_IsNumber(ttl)) {
        time_t now = time(NULL);
        time_t expiry = (time_t)created->valuedouble +
                        (time_t)(ttl->valuedouble * 3600);
        if (now > expiry) {
            cJSON_Delete(root);
            fprintf(stderr, "[llm_cache] EXPIRED: %s\n", key);
            remove(path);
            return AURA_ERR_NOT_FOUND;
        }
    }

    /* 응답 추출 */
    cJSON *response = cJSON_GetObjectItemCaseSensitive(root, "response");
    if (!cJSON_IsString(response) || !response->valuestring) {
        cJSON_Delete(root);
        return AURA_ERR_NOT_FOUND;
    }

    memset(resp, 0, sizeof(*resp));
    resp->content = strdup(response->valuestring);
    resp->error = AURA_OK;

    fprintf(stderr, "[llm_cache] HIT: %s\n", key);

    cJSON_Delete(root);
    return resp->content ? AURA_OK : AURA_ERR_NOMEM;
}

AuraError llm_cache_store(const char *key, const LlmRequest *req,
                          const LlmResponse *resp)
{
    if (!g_cache_initialized || !key || !req || !resp || !resp->content)
        return AURA_ERR_INVALID_ARG;

    cJSON *root = cJSON_CreateObject();
    if (!root) return AURA_ERR_NOMEM;

    /* 메타데이터 */
    if (req->model)
        cJSON_AddStringToObject(root, "model", req->model);

    /* 시스템/유저 프롬프트 저장 (디버그용) */
    for (size_t i = 0; i < req->message_count; i++) {
        if (req->messages[i].role == LLM_ROLE_SYSTEM && req->messages[i].content)
            cJSON_AddStringToObject(root, "system", req->messages[i].content);
        if (req->messages[i].role == LLM_ROLE_USER && req->messages[i].content)
            cJSON_AddStringToObject(root, "user", req->messages[i].content);
    }

    cJSON_AddNumberToObject(root, "temperature", req->temperature);
    cJSON_AddStringToObject(root, "response", resp->content);
    cJSON_AddNumberToObject(root, "created_at", (double)time(NULL));
    cJSON_AddNumberToObject(root, "ttl_hours", g_cache_ttl_hours);

    char *json = cJSON_Print(root);
    cJSON_Delete(root);
    if (!json) return AURA_ERR_NOMEM;

    char path[1024];
    cache_filepath(key, path, sizeof(path));

    FILE *f = fopen(path, "w");
    if (!f) {
        free(json);
        return AURA_ERR_IO;
    }

    fputs(json, f);
    fputc('\n', f);
    fclose(f);
    free(json);

    return AURA_OK;
}

void llm_cache_destroy(void)
{
    g_cache_initialized = 0;
    g_cache_dir[0] = '\0';
}

/* =====================================================================
 * 유틸: 캐시 키 생성
 * ===================================================================== */

void llm_cache_make_key(const char *model, const char *system_prompt,
                        const char *user_prompt, double temperature,
                        char *out_key, size_t key_sz)
{
    char temp_str[32];
    snprintf(temp_str, sizeof(temp_str), "%.2f", temperature);
    cache_hash(model ? model : "",
               system_prompt ? system_prompt : "",
               user_prompt ? user_prompt : "",
               temp_str,
               out_key, key_sz);
}
