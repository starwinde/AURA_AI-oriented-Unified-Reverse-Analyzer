// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm_http.h -- LLM HTTP 유틸리티 (내부 헤더)
 *
 * libcurl 기반 HTTP POST JSON 요청을 위한 공통 유틸리티.
 * src/llm/ 내부에서만 사용. include/에 노출하지 않는다.
 */

#ifndef LLM_HTTP_H
#define LLM_HTTP_H

#include "aura.h"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** HTTP 응답 구조체 */
typedef struct HttpResponse {
    char  *body;         /**< heap 할당, 호출자 free */
    size_t body_len;
    long   http_status;  /**< HTTP 상태 코드 */
} HttpResponse;

/**
 * llm_http_global_init -- libcurl 전역 초기화
 * 프로그램 당 1회 호출. 스레드 안전하지 않음.
 */
AuraError llm_http_global_init(void);

/** llm_http_global_cleanup -- libcurl 전역 해제 */
void llm_http_global_cleanup(void);

/**
 * llm_http_post_json -- JSON POST 요청 전송
 *
 * @param url          요청 URL
 * @param json_body    JSON 문자열 (Content-Type: application/json)
 * @param auth_header  Authorization 헤더 값 (NULL -> 생략)
 * @param timeout_sec  응답 타임아웃 (초)
 * @param resp         응답 출력
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_http_post_json(const char *url,
                             const char *json_body,
                             const char *auth_header,
                             int timeout_sec,
                             HttpResponse *resp);

/** llm_http_response_cleanup -- HttpResponse 내부 리소스 해제 */
void llm_http_response_cleanup(HttpResponse *resp);

#ifdef __cplusplus
}
#endif

#endif /* LLM_HTTP_H */
