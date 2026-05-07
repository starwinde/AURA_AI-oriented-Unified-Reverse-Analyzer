# AURA Phase 6/7 — LLM 연동 모듈 설계

> 작성일: 2026-04-04
> 상태: 확정 (2026-04-04)
> 목적: LLM 연동 모듈의 추상화 인터페이스, 로컬/클라우드 구현 전략, 캐시, 프롬프트 관리의 단일 기준

---

## 1 확정 결정 목록

| 결정 | 내용 | 근거 |
|------|------|------|
| LLM 런타임 (D-4) | API 기반. 로컬: LM Studio `localhost:1234/v1`. 클라우드: OpenAI 호환 API | PRD D-4 |
| 연동 모드 (D-12) | 모드 A(AURA->LLM) + 모드 B(LLM->AURA CLI) | PRD D-12 |
| HTTP 클라이언트 | libcurl (C 네이티브) | PRD 4.2 |
| JSON 파싱 | cJSON (단일 파일, `third_party/cjson/`) | PRD 4.2 |
| 설정 파일 (D-5) | `~/.config/aura/config.json` | PRD D-5 |
| 캐시 위치 (D-3) | `~/.cache/aura/llm/` (XDG 표준) | PRD D-3 권고안 |
| 추상화 레이어 | `LlmClient` vtable 패턴 (C 다형성) | 로컬/클라우드 동일 인터페이스 |
| 모듈 경로 | `src/llm/`, 공개 헤더 `include/llm.h` | CLAUDE.md 프로젝트 구조 |

---

## 2 아키텍처 개요

```
                  include/llm.h (공개 API)
                       |
            +----------+-----------+
            |                      |
      LlmClient vtable       LlmPrompt / LlmCache
      (추상 인터페이스)        (프롬프트 & 캐시)
            |
    +-------+-------+-------+
    |               |       |
lmstudio_client  llamacpp  openai_client
(6.2)            (6.3)     (7.2)
    |               |       |
    +-------+-------+-------+
            |
      libcurl HTTP layer
      (공통 HTTP 유틸리티)
```

### 2.1 모듈 파일 구조

```
src/llm/
  llm_client.c          -- LlmClient 공통 로직 (생성/파괴, vtable 디스패치)
  llm_http.c            -- libcurl HTTP 공통 유틸리티 (POST, 헤더, 타임아웃)
  llm_http.h            -- HTTP 유틸리티 내부 헤더
  lmstudio_client.c     -- LM Studio API 구현체 (6.2)
  llamacpp_client.c     -- llama.cpp 서버 API 구현체 (6.3)
  openai_client.c       -- OpenAI API 구현체 (7.2)
  groq_client.c         -- Groq API 구현체 (7.3)
  llm_cache.c           -- 파일 기반 응답 캐시 (6.4)
  prompt_templates.c    -- 프롬프트 템플릿 및 응답 파서 (6.5)
  llm_config.c          -- config.json 로드/저장 (7.4)

include/
  llm.h                 -- 공개 API (LlmClient, LlmMessage, LlmResponse 등)

third_party/cjson/
  cJSON.h, cJSON.c      -- JSON 파싱 라이브러리
```

---

## 3 핵심 타입

### 3.1 LlmClient (vtable 추상화)

C에서 다형성을 구현하기 위해 함수 포인터 테이블(vtable) 패턴을 사용한다.
각 백엔드(LM Studio, llama.cpp, OpenAI, Groq)는 동일한 vtable을 구현한다.

```c
typedef struct LlmClientVtable {
    AuraError (*chat)(void *impl, const LlmRequest *req, LlmResponse *resp);
    void      (*destroy)(void *impl);
    const char *(*backend_name)(void *impl);
} LlmClientVtable;

typedef struct LlmClient {
    const LlmClientVtable *vt;
    void                  *impl;  // 백엔드별 구현 데이터
} LlmClient;
```

- `chat()` — 채팅 완성 요청. 메시지 배열 입력, 응답 텍스트 출력.
- `destroy()` — 백엔드 리소스 해제.
- `backend_name()` — 디버그/로깅용 백엔드 이름 반환.

### 3.2 LlmMessage / LlmRequest / LlmResponse

OpenAI Chat Completions API 형식을 표준으로 채택한다.
LM Studio, llama.cpp 서버, Groq 모두 이 형식과 호환된다.

```c
typedef enum LlmRole {
    LLM_ROLE_SYSTEM,
    LLM_ROLE_USER,
    LLM_ROLE_ASSISTANT,
} LlmRole;

typedef struct LlmMessage {
    LlmRole  role;
    char    *content;   // heap 할당, 호출자 소유
} LlmMessage;

typedef struct LlmRequest {
    const char      *model;         // 모델명 (nullable → 설정 기본값 사용)
    LlmMessage      *messages;      // 메시지 배열
    size_t           message_count;
    double           temperature;   // 0.0~2.0 (기본값: 0.3)
    int              max_tokens;    // 최대 응답 토큰 (기본값: 1024)
} LlmRequest;

typedef struct LlmResponse {
    char    *content;        // 응답 텍스트 (heap, 호출자가 free)
    int      prompt_tokens;  // 프롬프트 토큰 수
    int      completion_tokens;
    int      total_tokens;
    AuraError error;         // AURA_OK 또는 에러 코드
    char     error_msg[256]; // 에러 시 상세 메시지
} LlmResponse;
```

### 3.3 LlmBackendType

```c
typedef enum LlmBackendType {
    LLM_BACKEND_LMSTUDIO,    // LM Studio (localhost:1234)
    LLM_BACKEND_LLAMACPP,    // llama.cpp 서버
    LLM_BACKEND_OPENAI,      // OpenAI API
    LLM_BACKEND_GROQ,        // Groq API
} LlmBackendType;
```

---

## 4 공개 API 설계

### 4.1 클라이언트 생명주기

```c
// 백엔드별 팩토리 함수
LlmClient *llm_client_create_lmstudio(const char *base_url, const char *model);
LlmClient *llm_client_create_llamacpp(const char *base_url, const char *model);
LlmClient *llm_client_create_openai(const char *api_key, const char *model);
LlmClient *llm_client_create_groq(const char *api_key, const char *model);

// 추상 인터페이스
AuraError   llm_client_chat(LlmClient *client, const LlmRequest *req, LlmResponse *resp);
const char *llm_client_backend_name(LlmClient *client);
void        llm_client_destroy(LlmClient **client);  // T** 모델
```

### 4.2 편의 함수 (고수준)

```c
// 단일 프롬프트 → 단일 응답 (메시지 배열 구성 불필요)
AuraError llm_query(LlmClient *client, const char *system_prompt,
                    const char *user_prompt, LlmResponse *resp);
```

### 4.3 응답 리소스 해제

```c
void llm_response_cleanup(LlmResponse *resp);  // resp->content를 free
```

---

## 5 HTTP 공통 레이어

### 5.1 설계 근거

모든 백엔드가 HTTP POST + JSON 형식을 사용하므로, 공통 HTTP 유틸리티를 분리한다.
이 레이어는 `src/llm/llm_http.h` (내부 헤더)에 정의하며 공개 API에 노출하지 않는다.

### 5.2 내부 API

```c
// src/llm/llm_http.h

typedef struct HttpResponse {
    char   *body;          // heap, 호출자 free
    size_t  body_len;
    long    http_status;   // HTTP 상태 코드
} HttpResponse;

// JSON POST 요청
AuraError llm_http_post_json(const char *url,
                             const char *json_body,
                             const char *auth_header,  // nullable
                             int timeout_sec,
                             HttpResponse *resp);

void llm_http_response_cleanup(HttpResponse *resp);

// libcurl 전역 초기화/해제 (프로그램 당 1회)
AuraError llm_http_global_init(void);
void      llm_http_global_cleanup(void);
```

### 5.3 타임아웃 정책

| 항목 | 기본값 | 설정 가능 |
|------|--------|-----------|
| 연결 타임아웃 | 5초 | config.json |
| 응답 타임아웃 | 60초 | config.json |
| LM Studio 재시도 | 0회 | 고정 (MVP) |

---

## 6 캐시 시스템 (6.4)

### 6.1 캐시 키

```
SHA256(model_name + "\0" + system_prompt + "\0" + user_prompt + "\0" + temperature_str)
```

- 온도(temperature)가 다르면 다른 캐시 항목으로 취급한다.
- `max_tokens`는 캐시 키에 포함하지 않는다 (같은 입력이면 동일 응답 기대).

### 6.2 캐시 저장소

```
~/.cache/aura/llm/
  <hex_sha256_prefix_16>.json     -- 캐시 엔트리
```

각 캐시 파일은 cJSON 형식:

```json
{
  "model": "qwen/qwen3-coder-next",
  "system": "...",
  "user": "...",
  "temperature": 0.3,
  "response": "...",
  "created_at": 1712200000,
  "ttl_hours": 24
}
```

### 6.3 캐시 API

```c
AuraError llm_cache_init(const char *cache_dir);  // NULL → 기본 경로
AuraError llm_cache_lookup(const char *key, LlmResponse *resp);  // 히트 시 AURA_OK
AuraError llm_cache_store(const char *key, const LlmRequest *req,
                          const LlmResponse *resp);
void      llm_cache_destroy(void);
```

---

## 7 프롬프트 템플릿 (6.5)

### 7.1 분석 목적별 템플릿

| ID | 목적 | 시스템 프롬프트 | 사용자 입력 | 기대 출력 |
|---|------|----------------|-------------|-----------|
| `func_name` | 함수명 제안 | "Analyze the disassembly and suggest a descriptive function name." | 디스어셈블리 텍스트 | JSON `{"name": "..."}` |
| `code_summary` | 코드 요약 | "Summarize what this function does in one paragraph." | Pseudo-C 코드 | 자유 텍스트 |
| `vuln_scan` | 취약점 탐지 | "Identify potential vulnerabilities in this code." | Pseudo-C 코드 | JSON 배열 (Task 7.6) |

### 7.2 템플릿 API

```c
typedef enum LlmPromptType {
    LLM_PROMPT_FUNC_NAME,
    LLM_PROMPT_CODE_SUMMARY,
    LLM_PROMPT_COUNT,  // 센티널
} LlmPromptType;

// 템플릿으로 LlmRequest 구성
AuraError llm_prompt_build(LlmPromptType type, const char *input,
                           LlmRequest *out_req);

// LLM 응답에서 결과 추출
AuraError llm_prompt_parse_func_name(const char *response, char *out_name, size_t name_sz);
AuraError llm_prompt_parse_summary(const char *response, char *out_summary, size_t summary_sz);

// LlmRequest 리소스 해제
void llm_request_cleanup(LlmRequest *req);
```

---

## 8 설정 구조 (D-5)

`~/.config/aura/config.json` 내 LLM 섹션:

```json
{
  "llm": {
    "default_backend": "lmstudio",
    "lmstudio": {
      "base_url": "http://localhost:1234/v1",
      "model": "qwen/qwen3-coder-next"
    },
    "llamacpp": {
      "base_url": "http://localhost:8080/v1",
      "model": "default"
    },
    "openai": {
      "api_key_env": "OPENAI_API_KEY",
      "model": "gpt-4o"
    },
    "groq": {
      "api_key_env": "GROQ_API_KEY",
      "model": "llama-3.3-70b-versatile"
    },
    "cache": {
      "enabled": true,
      "ttl_hours": 24,
      "dir": "~/.cache/aura/llm"
    },
    "timeout": {
      "connect_sec": 5,
      "response_sec": 60
    },
    "temperature": 0.3,
    "max_tokens": 1024
  }
}
```

---

## 9 모드 A vs 모드 B (D-12)

### 모드 A: AURA -> LLM

AURA의 분석 결과(디스어셈블리, Pseudo-C)를 LLM API에 전송하여 네이밍/요약을 수신한다.
이 모듈(Phase 6/7)이 직접 구현하는 핵심 경로다.

```
사용자 → GUI "Analyze with LLM" → llm_query() → HTTP POST → LLM 서버 → 응답 파싱
```

### 모드 B: LLM -> AURA CLI

LLM 에이전트가 AURA CLI를 도구로 호출한다.
이를 위해 모든 CLI 명령에 `--json` 출력을 지원한다 (Phase 5 완료).
Phase 6 모듈이 직접 구현할 부분은 없으며, CLI의 JSON 출력 호환성이 핵심이다.

---

## 10 소유권 모델

| 타입 | 할당 주체 | 해제 주체 | 해제 함수 |
|------|-----------|-----------|-----------|
| `LlmClient*` | `llm_client_create_*()` | 호출자 | `llm_client_destroy(&client)` |
| `LlmResponse.content` | `llm_client_chat()` | 호출자 | `llm_response_cleanup(&resp)` |
| `LlmRequest.messages[].content` | `llm_prompt_build()` | 호출자 | `llm_request_cleanup(&req)` |
| `HttpResponse.body` | `llm_http_post_json()` | 호출자 | `llm_http_response_cleanup(&resp)` |

---

## 11 빌드 의존성

| 라이브러리 | 용도 | CMake 설정 |
|-----------|------|-----------|
| libcurl | HTTP 클라이언트 | `find_package(CURL REQUIRED)` |
| cJSON | JSON 파싱 | `add_library(cjson STATIC third_party/cjson/cJSON.c)` |

LLM 모듈은 `aura_core`와 별도의 정적 라이브러리 `aura_llm`으로 빌드하여 GUI에서만 링크한다.
CLI(`aura`)는 LLM 모듈을 링크하지 않는다 (모드 B는 CLI 자체가 도구 역할).

---

## 12 에러 처리 전략

| 상황 | 처리 |
|------|------|
| LM Studio 미실행 | `AURA_ERR_LLM` + "Connection refused" 메시지. 프로그램 정상 동작 유지 |
| 타임아웃 | `AURA_ERR_LLM` + "Request timed out" 메시지 |
| HTTP 4xx/5xx | `AURA_ERR_LLM` + HTTP 상태 코드 포함 메시지 |
| JSON 파싱 실패 | `AURA_ERR_PARSE` + "Invalid JSON response" |
| API 키 누락 (클라우드) | `AURA_ERR_INVALID_ARG` + 환경변수명 안내 |
| 빈 응답 | `AURA_ERR_LLM` + "Empty response from LLM" |

---

## 13 클라우드 API 통합 설계 (Phase 7)

> 작성: llm-cloud-dev, 2026-04-04
> Phase 6 `LlmClient` 인터페이스 확인 및 클라우드 구현 전략 확정

### 13.1 설계 확인: LlmClient vtable이 클라우드 API를 수용하는가

OpenAI Chat Completions API와 Groq API는 모두 동일한 요청/응답 형식을 사용한다:
- **요청**: `POST /v1/chat/completions` + JSON body (model, messages, temperature, max_tokens)
- **응답**: JSON (choices[0].message.content, usage.prompt_tokens 등)

`include/llm.h`의 `LlmClient` vtable 패턴은 이 형식을 완전히 수용한다:

| vtable 함수 | 클라우드 구현 동작 |
|---|---|
| `chat(impl, req, resp)` | HTTP POST → OpenAI/Groq 엔드포인트, JSON 파싱 후 resp 채움 |
| `destroy(impl)` | 내부 URL/API 키 문자열 free |
| `backend_name(impl)` | `"openai"` 또는 `"groq"` 반환 |

**결론**: 인터페이스 변경 불필요. 기존 vtable 그대로 클라우드 백엔드 구현 가능.

### 13.2 OpenAI API 클라이언트 (7.2: `src/llm/openai_client.c`)

**엔드포인트:** `https://api.openai.com/v1/chat/completions`

**인증:**
```
Authorization: Bearer <OPENAI_API_KEY>
```

**내부 구현 데이터:**
```c
typedef struct OpenaiImpl {
    char *base_url;   // "https://api.openai.com/v1" (커스텀 가능)
    char *api_key;    // heap 복사본, destroy 시 free
    char *model;      // "gpt-4o" 등
} OpenaiImpl;
```

**팩토리:** `llm_client_create_openai(api_key, model)`
- `api_key == NULL` → `getenv("OPENAI_API_KEY")` 시도, 없으면 `NULL` 반환
- `model == NULL` → `"gpt-4o"` 기본값

**요청 빌드 (chat vtable):**
1. cJSON으로 요청 JSON 구성: `{"model": ..., "messages": [...], "temperature": ..., "max_tokens": ...}`
2. `llm_http_post_json()` 호출 (auth_header = `"Authorization: Bearer <key>"`)
3. 응답 JSON에서 `choices[0].message.content`, `usage.*` 추출
4. HTTP 에러 처리: 401 → API 키 오류, 429 → Rate limit, 500 → 서버 오류

**에러 처리:**
| HTTP 상태 | 에러 코드 | 메시지 |
|---|---|---|
| 401 | `AURA_ERR_INVALID_ARG` | "Invalid OpenAI API key" |
| 429 | `AURA_ERR_LLM` | "OpenAI rate limit exceeded" |
| 500+ | `AURA_ERR_LLM` | "OpenAI server error (HTTP <code>)" |
| 연결 실패 | `AURA_ERR_LLM` | "Connection to OpenAI failed" |

### 13.3 Groq API 클라이언트 (7.3: `src/llm/groq_client.c`)

**엔드포인트:** `https://api.groq.com/openai/v1/chat/completions`

**인증:** OpenAI와 동일 (`Authorization: Bearer <GROQ_API_KEY>`)

**내부 구현 데이터:**
```c
typedef struct GroqImpl {
    char *base_url;   // "https://api.groq.com/openai/v1"
    char *api_key;    // heap 복사본
    char *model;      // "llama-3.3-70b-versatile" 등
} GroqImpl;
```

**팩토리:** `llm_client_create_groq(api_key, model)`
- `api_key == NULL` → `getenv("GROQ_API_KEY")` 시도
- `model == NULL` → `"llama-3.3-70b-versatile"` 기본값

**OpenAI 클라이언트와의 차이점:**
| 항목 | OpenAI | Groq |
|---|---|---|
| 기본 URL | `https://api.openai.com/v1` | `https://api.groq.com/openai/v1` |
| 환경변수 | `OPENAI_API_KEY` | `GROQ_API_KEY` |
| 기본 모델 | `gpt-4o` | `llama-3.3-70b-versatile` |
| Rate limit | 비교적 관대 | 공격적 (RPM/TPM 제한) |
| 응답 형식 | OpenAI 표준 | OpenAI 호환 |

> **코드 재사용 전략**: OpenAI와 Groq의 JSON 요청 빌드 및 응답 파싱 로직은 동일하므로,
> `src/llm/openai_client.c`에 공통 내부 함수를 두고 Groq이 URL/키/모델만 다르게 설정하여
> 동일 로직을 호출하는 구조로 구현한다. 별도의 추상 레이어를 만들지 않고
> 두 파일이 같은 내부 헬퍼를 공유하는 방식을 취한다.

### 13.4 API 키 관리 및 설정 UI (7.4)

**키 로드 우선순위:**
1. 팩토리 함수에 직접 전달된 `api_key` 파라미터
2. 환경변수 (`OPENAI_API_KEY` / `GROQ_API_KEY`)
3. `~/.config/aura/config.json`의 `llm.openai.api_key_env` / `llm.groq.api_key_env`에 지정된 환경변수명

**GUI 설정 다이얼로그 (`src/gui/settings_dialog.cpp`):**
- API 키 입력 필드 (QLineEdit, echoMode=Password → 마스킹 표시)
- 백엔드 선택 콤보박스 (lmstudio / llamacpp / openai / groq)
- 모델명 입력 필드
- "Test Connection" 버튼 (llm_query로 간단 요청 → 성공/실패 표시)
- 저장 시 `config.json`에 기록 (평문 저장, MVP 기준)

**`src/llm/llm_config.c` API:**
```c
// config.json에서 LLM 설정 로드
AuraError llm_config_load(const char *config_path);  // NULL → 기본 경로

// 현재 설정으로 적절한 LlmClient 생성
LlmClient *llm_config_create_client(void);

// 설정값 개별 접근
const char *llm_config_get_backend(void);
const char *llm_config_get_api_key(const char *backend);
const char *llm_config_get_model(const char *backend);

// 설정 저장
AuraError llm_config_save(const char *config_path);
void llm_config_cleanup(void);
```

### 13.5 클라우드 캐싱 확장 (7.5)

Phase 6.4의 캐시 시스템을 클라우드 API에 동일하게 적용한다.

**변경 없음:** 캐시 키 = SHA256(model + system + user + temperature). 로컬/클라우드 구분 없이 동일.

**TTL 차이:**
- 기본 TTL: 24시간 (config.json의 `llm.cache.ttl_hours`)
- 클라우드 API 호출은 비용이 발생하므로 캐시 히트율이 중요
- 캐시 만료 시간 설정 가능 (config.json에서 변경)

**구현 방식:** `llm_cache_lookup()` / `llm_cache_store()` 그대로 사용.
클라우드 클라이언트의 `chat()` 구현 내부에서 캐시 조회/저장을 호출한다.

### 13.6 테스트 전략 (7.T)

| 테스트 항목 | 방법 |
|---|---|
| API 키 미설정 | `OPENAI_API_KEY` 미설정 상태에서 팩토리 호출 → NULL 반환 확인 |
| mock API 서버 | 로컬 HTTP 서버로 OpenAI 응답 형식 에뮬레이션 → 정상 파싱 확인 |
| 에러 응답 처리 | mock에서 401/429/500 반환 → 적절한 에러 코드 확인 |
| 백엔드 전환 | config.json의 `default_backend` 변경 → 클라이언트 전환 확인 |
| 캐시 히트 | 동일 요청 2회 → 두 번째는 캐시에서 반환 (< 10ms) |
| ASAN | 메모리 오류 0건 |
