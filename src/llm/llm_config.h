// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * llm_config.h -- LLM 설정 관리 API (Phase 7.4)
 *
 * config.json에서 LLM 설정을 로드/저장하고,
 * 현재 설정에 기반한 LlmClient를 생성한다.
 */

#ifndef LLM_CONFIG_H
#define LLM_CONFIG_H

#include "llm.h"

#ifdef __cplusplus
extern "C" {
#endif

/** LLM 설정 구조체 (전체 config.json의 llm 섹션) */
typedef struct LlmConfig {
    char   *default_backend;    /* "lmstudio" | "llamacpp" | "openai" | "groq" */

    /* LM Studio */
    char   *lmstudio_url;
    char   *lmstudio_model;

    /* llama.cpp */
    char   *llamacpp_url;
    char   *llamacpp_model;

    /* OpenAI */
    char   *openai_api_key_env; /* 환경변수명 (기본: "OPENAI_API_KEY") */
    char   *openai_model;

    /* Groq */
    char   *groq_api_key_env;   /* 환경변수명 (기본: "GROQ_API_KEY") */
    char   *groq_model;

    /* 캐시 */
    int     cache_enabled;
    int     cache_ttl_hours;
    char   *cache_dir;          /* NULL → 기본 경로 */

    /* 공통 */
    double  temperature;
    int     max_tokens;
    int     connect_sec;
    int     response_sec;
} LlmConfig;

/** config.json에서 LLM 설정 로드 (NULL → 기본 경로) */
AuraError llm_config_load(const char *config_path);

/** config.json에 LLM 설정 저장 (NULL → 기본 경로) */
AuraError llm_config_save(const char *config_path);

/** 현재 설정으로 적절한 LlmClient 생성 */
LlmClient *llm_config_create_client(void);

/** 설정값 개별 접근 */
const char *llm_config_get_backend(void);
const char *llm_config_get_api_key(const char *backend);
const char *llm_config_get_model(const char *backend);
const LlmConfig *llm_config_get(void);

/** 설정 변경 (GUI에서 호출) */
void llm_config_set_backend(const char *backend);
void llm_config_set_openai_model(const char *model);
void llm_config_set_groq_model(const char *model);

/** 설정 리소스 해제 */
void llm_config_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* LLM_CONFIG_H */
