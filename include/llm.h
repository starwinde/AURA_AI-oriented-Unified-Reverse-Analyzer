// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm.h -- AURA LLM 연동 모듈 공개 API
 *
 * 로컬(LM Studio, llama.cpp) 및 클라우드(OpenAI, Groq) LLM 백엔드를
 * 동일한 추상화 인터페이스로 제공한다.
 *
 * 설계 근거: docs/design/llm_integration.md
 *
 * 소유권 모델:
 *   - LlmClient* : llm_client_create_*()가 heap 할당, 호출자 소유.
 *     llm_client_destroy(&client) -- T** 모델, 호출 후 *client == NULL.
 *   - LlmResponse.content : llm_client_chat()가 heap 할당, 호출자 소유.
 *     llm_response_cleanup(&resp) 호출하여 해제.
 *   - LlmRequest.messages[].content : llm_prompt_build()가 heap 할당.
 *     llm_request_cleanup(&req) 호출하여 해제.
 */

#ifndef LLM_H
#define LLM_H

#include <stddef.h>
#include "aura.h"

#ifdef __cplusplus
extern "C" {
#endif

/* =====================================================================
 * 1  상수 / 기본값
 * ===================================================================== */

#define LLM_DEFAULT_LMSTUDIO_URL   "http://localhost:1234/v1"
#define LLM_DEFAULT_LMSTUDIO_MODEL "qwen/qwen3-coder-next"
#define LLM_DEFAULT_LLAMACPP_URL   "http://localhost:8080/v1"
#define LLM_DEFAULT_TEMPERATURE    0.3
#define LLM_DEFAULT_MAX_TOKENS     1024
#define LLM_DEFAULT_CONNECT_SEC    5
#define LLM_DEFAULT_RESPONSE_SEC   60
#define LLM_ERROR_MSG_SIZE         256

/* =====================================================================
 * 2  열거형
 * ===================================================================== */

/** LLM 백엔드 종류 */
typedef enum LlmBackendType {
    LLM_BACKEND_LMSTUDIO,     /**< LM Studio (localhost:1234) */
    LLM_BACKEND_LLAMACPP,     /**< llama.cpp HTTP 서버 */
    LLM_BACKEND_OPENAI,       /**< OpenAI API */
    LLM_BACKEND_GROQ,         /**< Groq API */
} LlmBackendType;

/** 채팅 메시지 역할 */
typedef enum LlmRole {
    LLM_ROLE_SYSTEM,
    LLM_ROLE_USER,
    LLM_ROLE_ASSISTANT,
} LlmRole;

/** 프롬프트 템플릿 종류 */
typedef enum LlmPromptType {
    LLM_PROMPT_FUNC_NAME,     /**< 함수명 제안 */
    LLM_PROMPT_CODE_SUMMARY,  /**< 코드 요약 */
    LLM_PROMPT_VULN_ANALYSIS, /**< 보안 취약점 분석 (7.6) */
    LLM_PROMPT_COUNT,         /**< 센티널 (개수) */
} LlmPromptType;

/* =====================================================================
 * 3  데이터 구조체
 * ===================================================================== */

/** 단일 채팅 메시지 */
typedef struct LlmMessage {
    LlmRole  role;
    char    *content;          /**< heap 할당, 호출자 소유 */
} LlmMessage;

/** 채팅 요청 */
typedef struct LlmRequest {
    const char *model;         /**< 모델명 (NULL -> 백엔드 기본값) */
    LlmMessage *messages;      /**< 메시지 배열 */
    size_t      message_count;
    double      temperature;   /**< 0.0~2.0 (기본값: LLM_DEFAULT_TEMPERATURE) */
    int         max_tokens;    /**< 최대 응답 토큰 (기본값: LLM_DEFAULT_MAX_TOKENS) */
} LlmRequest;

/** 채팅 응답 */
typedef struct LlmResponse {
    char     *content;                       /**< 응답 텍스트 (heap, 호출자 free) */
    int       prompt_tokens;
    int       completion_tokens;
    int       total_tokens;
    AuraError error;                         /**< AURA_OK 또는 에러 코드 */
    char      error_msg[LLM_ERROR_MSG_SIZE]; /**< 에러 시 상세 메시지 */
} LlmResponse;

/* =====================================================================
 * 4  LlmClient vtable (추상 인터페이스)
 * ===================================================================== */

/** 백엔드 가상 함수 테이블 */
typedef struct LlmClientVtable {
    AuraError   (*chat)(void *impl, const LlmRequest *req, LlmResponse *resp);
    void        (*destroy)(void *impl);
    const char *(*backend_name)(void *impl);
} LlmClientVtable;

/** LLM 클라이언트 핸들 (다형성) */
typedef struct LlmClient {
    const LlmClientVtable *vt;
    void                  *impl;   /**< 백엔드별 구현 데이터 (opaque) */
} LlmClient;

/* =====================================================================
 * 5  클라이언트 생명주기
 * ===================================================================== */

/**
 * llm_client_create_lmstudio -- LM Studio 백엔드 클라이언트 생성
 *
 * @param base_url  LM Studio 서버 URL (NULL -> LLM_DEFAULT_LMSTUDIO_URL)
 * @param model     모델명 (NULL -> LLM_DEFAULT_LMSTUDIO_MODEL)
 * @return 성공 시 LlmClient*, 실패 시 NULL
 */
LlmClient *llm_client_create_lmstudio(const char *base_url, const char *model);

/**
 * llm_client_create_llamacpp -- llama.cpp 서버 백엔드 클라이언트 생성
 *
 * @param base_url  llama.cpp 서버 URL (NULL -> LLM_DEFAULT_LLAMACPP_URL)
 * @param model     모델명 (NULL -> "default")
 * @return 성공 시 LlmClient*, 실패 시 NULL
 */
LlmClient *llm_client_create_llamacpp(const char *base_url, const char *model);

/**
 * llm_client_create_openai -- OpenAI API 백엔드 클라이언트 생성
 *
 * @param api_key   API 키 (NULL -> OPENAI_API_KEY 환경변수에서 로드)
 * @param model     모델명 (NULL -> "gpt-4o")
 * @return 성공 시 LlmClient*, 실패 시 NULL
 */
LlmClient *llm_client_create_openai(const char *api_key, const char *model);

/**
 * llm_client_create_groq -- Groq API 백엔드 클라이언트 생성
 *
 * @param api_key   API 키 (NULL -> GROQ_API_KEY 환경변수에서 로드)
 * @param model     모델명 (NULL -> "llama-3.3-70b-versatile")
 * @return 성공 시 LlmClient*, 실패 시 NULL
 */
LlmClient *llm_client_create_groq(const char *api_key, const char *model);

/**
 * llm_client_chat -- 채팅 완성 요청 (추상 인터페이스)
 *
 * @param client  LLM 클라이언트 핸들
 * @param req     요청 (메시지 배열, 모델, 온도 등)
 * @param resp    응답 출력 (호출자가 llm_response_cleanup() 호출)
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_client_chat(LlmClient *client, const LlmRequest *req,
                          LlmResponse *resp);

/**
 * llm_client_backend_name -- 백엔드 이름 반환 (디버그/로깅용)
 */
const char *llm_client_backend_name(LlmClient *client);

/**
 * llm_client_destroy -- 클라이언트 리소스 해제
 *
 * T** 모델: 호출 후 *client == NULL.
 * @param client  클라이언트 포인터의 포인터 (NULL 안전)
 */
void llm_client_destroy(LlmClient **client);

/* =====================================================================
 * 6  편의 함수 (고수준)
 * ===================================================================== */

/**
 * llm_query -- 단일 프롬프트 -> 단일 응답 편의 함수
 *
 * 내부적으로 system + user 메시지 2개짜리 LlmRequest를 구성하고
 * llm_client_chat()를 호출한다.
 *
 * @param client        LLM 클라이언트 핸들
 * @param system_prompt 시스템 프롬프트 (NULL -> 생략)
 * @param user_prompt   사용자 프롬프트
 * @param resp          응답 출력
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_query(LlmClient *client, const char *system_prompt,
                    const char *user_prompt, LlmResponse *resp);

/* =====================================================================
 * 7  리소스 해제
 * ===================================================================== */

/**
 * llm_response_cleanup -- LlmResponse 내부 리소스 해제
 *
 * resp->content를 free하고 NULL로 설정한다.
 * resp 구조체 자체는 해제하지 않는다 (스택 변수 가정).
 */
void llm_response_cleanup(LlmResponse *resp);

/**
 * llm_request_cleanup -- LlmRequest 내부 리소스 해제
 *
 * req->messages[].content를 free하고 messages 배열을 free한다.
 * req 구조체 자체는 해제하지 않는다.
 */
void llm_request_cleanup(LlmRequest *req);

/* =====================================================================
 * 8  캐시 API (6.4)
 * ===================================================================== */

/**
 * llm_cache_init -- 캐시 시스템 초기화
 *
 * @param cache_dir 캐시 디렉토리 경로 (NULL -> ~/.cache/aura/llm/)
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_cache_init(const char *cache_dir);

/**
 * llm_cache_lookup -- 캐시 조회
 *
 * @param key   캐시 키 (SHA256 hex 문자열)
 * @param resp  히트 시 응답이 채워짐
 * @return AURA_OK (히트), AURA_ERR_NOT_FOUND (미스)
 */
AuraError llm_cache_lookup(const char *key, LlmResponse *resp);

/**
 * llm_cache_store -- 캐시 저장
 *
 * @param key   캐시 키
 * @param req   원본 요청 (메타데이터 저장용)
 * @param resp  저장할 응답
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_cache_store(const char *key, const LlmRequest *req,
                          const LlmResponse *resp);

/** llm_cache_destroy -- 캐시 시스템 해제 */
void llm_cache_destroy(void);

/**
 * llm_cache_make_key -- 캐시 키 생성 유틸리티
 *
 * model + system + user + temperature를 해시하여 캐시 키를 생성한다.
 *
 * @param model          모델명
 * @param system_prompt  시스템 프롬프트 (NULL 허용)
 * @param user_prompt    사용자 프롬프트
 * @param temperature    온도
 * @param out_key        출력 버퍼 (최소 32바이트)
 * @param key_sz         버퍼 크기
 */
void llm_cache_make_key(const char *model, const char *system_prompt,
                        const char *user_prompt, double temperature,
                        char *out_key, size_t key_sz);

/* =====================================================================
 * 9  프롬프트 템플릿 API (6.5)
 * ===================================================================== */

/**
 * llm_prompt_build -- 템플릿으로 LlmRequest 구성
 *
 * @param type    프롬프트 종류 (LLM_PROMPT_FUNC_NAME 등)
 * @param input   분석 입력 텍스트 (디스어셈블리 또는 Pseudo-C)
 * @param out_req 구성된 요청 (호출자가 llm_request_cleanup() 호출)
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_prompt_build(LlmPromptType type, const char *input,
                           LlmRequest *out_req);

/**
 * llm_prompt_parse_func_name -- 함수명 제안 응답 파싱
 *
 * LLM 응답에서 JSON {"name": "..."} 형식의 함수명을 추출한다.
 *
 * @param response  LLM 응답 텍스트
 * @param out_name  추출된 함수명 출력 버퍼
 * @param name_sz   버퍼 크기
 * @return AURA_OK 또는 AURA_ERR_PARSE
 */
AuraError llm_prompt_parse_func_name(const char *response,
                                     char *out_name, size_t name_sz);

/**
 * llm_prompt_parse_summary -- 코드 요약 응답 파싱
 *
 * LLM 응답 텍스트를 그대로 복사한다 (자유 텍스트).
 *
 * @param response    LLM 응답 텍스트
 * @param out_summary 출력 버퍼
 * @param summary_sz  버퍼 크기
 * @return AURA_OK 또는 AURA_ERR_PARSE
 */
AuraError llm_prompt_parse_summary(const char *response,
                                   char *out_summary, size_t summary_sz);

/**
 * llm_prompt_parse_vuln -- 취약점 분석 응답 파싱 (7.6)
 *
 * LLM 응답 텍스트를 그대로 복사한다 (자유 텍스트).
 * llm_prompt_parse_summary와 동일 동작이나 의미적 구분을 위해 별도 함수.
 */
AuraError llm_prompt_parse_vuln(const char *response,
                                char *out_report, size_t report_sz);

/* =====================================================================
 * 10  전역 초기화 / 해제
 * ===================================================================== */

/**
 * llm_global_init -- LLM 모듈 전역 초기화 (libcurl 등)
 *
 * 프로그램 시작 시 1회 호출. 스레드 안전하지 않음.
 * @return AURA_OK 또는 에러 코드
 */
AuraError llm_global_init(void);

/**
 * llm_global_cleanup -- LLM 모듈 전역 해제
 *
 * 프로그램 종료 시 1회 호출.
 */
void llm_global_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* LLM_H */
