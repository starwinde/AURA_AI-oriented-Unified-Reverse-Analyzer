// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm_http.c -- libcurl HTTP 공통 유틸리티
 */

#include "llm_http.h"

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ─────────────────────────────────────────────
 * 내부: curl write callback
 * ───────────────────────────────────────────── */

typedef struct {
    char  *buf;
    size_t len;
    size_t cap;
} WriteBuffer;

static size_t write_callback(char *ptr, size_t size, size_t nmemb,
                             void *userdata)
{
    WriteBuffer *wb = (WriteBuffer *)userdata;
    size_t total = size * nmemb;

    if (wb->len + total + 1 > wb->cap) {
        size_t new_cap = (wb->cap == 0) ? 4096 : wb->cap;
        while (new_cap < wb->len + total + 1)
            new_cap *= 2;
        char *tmp = (char *)realloc(wb->buf, new_cap);
        if (!tmp) return 0;
        wb->buf = tmp;
        wb->cap = new_cap;
    }
    memcpy(wb->buf + wb->len, ptr, total);
    wb->len += total;
    wb->buf[wb->len] = '\0';
    return total;
}

/* ─────────────────────────────────────────────
 * 전역 초기화 / 해제
 * ───────────────────────────────────────────── */

AuraError llm_http_global_init(void)
{
    CURLcode rc = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (rc != CURLE_OK) {
        fprintf(stderr, "[llm_http] curl_global_init failed: %s\n",
                curl_easy_strerror(rc));
        return AURA_ERR_LLM;
    }
    return AURA_OK;
}

void llm_http_global_cleanup(void)
{
    curl_global_cleanup();
}

/* ─────────────────────────────────────────────
 * JSON POST 요청
 * ───────────────────────────────────────────── */

AuraError llm_http_post_json(const char *url,
                             const char *json_body,
                             const char *auth_header,
                             int timeout_sec,
                             HttpResponse *resp)
{
    if (!url || !json_body || !resp) return AURA_ERR_INVALID_ARG;

    memset(resp, 0, sizeof(*resp));

    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "[llm_http] curl_easy_init failed\n");
        return AURA_ERR_LLM;
    }

    WriteBuffer wb = {0};
    struct curl_slist *headers = NULL;
    AuraError err = AURA_OK;

    headers = curl_slist_append(headers, "Content-Type: application/json");
    if (auth_header) {
        headers = curl_slist_append(headers, auth_header);
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_body);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wb);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, (long)timeout_sec);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);

    CURLcode rc = curl_easy_perform(curl);
    if (rc != CURLE_OK) {
        fprintf(stderr, "[llm_http] request to %s failed: %s\n",
                url, curl_easy_strerror(rc));
        free(wb.buf);
        wb.buf = NULL;
        err = AURA_ERR_LLM;
        goto cleanup;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &resp->http_status);
    resp->body = wb.buf;
    resp->body_len = wb.len;

cleanup:
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return err;
}

void llm_http_response_cleanup(HttpResponse *resp)
{
    if (!resp) return;
    free(resp->body);
    resp->body = NULL;
    resp->body_len = 0;
    resp->http_status = 0;
}
