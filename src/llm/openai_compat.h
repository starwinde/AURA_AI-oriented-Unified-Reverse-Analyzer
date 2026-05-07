// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * openai_compat.h -- OpenAI 호환 API 공통 헬퍼 (내부 헤더)
 *
 * OpenAI와 Groq 클라이언트가 공유하는 JSON 빌드/파싱 로직.
 * src/llm/ 내부에서만 사용. include/에 노출하지 않는다.
 */

#ifndef OPENAI_COMPAT_H
#define OPENAI_COMPAT_H

#include "llm.h"
#include "llm_http.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * openai_compat_chat -- OpenAI 호환 API chat 요청 실행
 *
 * @param base_url       API base URL (예: "https://api.openai.com/v1")
 * @param api_key        API 키
 * @param default_model  기본 모델명
 * @param backend_name   백엔드 이름 (에러 메시지용)
 * @param req            LLM 요청
 * @param resp           LLM 응답 출력
 * @return AURA_OK 또는 에러 코드
 */
AuraError openai_compat_chat(const char *base_url,
                             const char *api_key,
                             const char *default_model,
                             const char *backend_name,
                             const LlmRequest *req,
                             LlmResponse *resp);

#ifdef __cplusplus
}
#endif

#endif /* OPENAI_COMPAT_H */
