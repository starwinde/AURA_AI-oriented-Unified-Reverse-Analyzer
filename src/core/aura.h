// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * aura.h — AURA 프로젝트 공통 타입 및 에러 코드 정의
 *
 * 이 헤더는 모든 AURA 모듈이 공유하는 기반 타입과 에러 코드를 정의한다.
 * UI 레이어(gui/)를 포함한 모든 모듈에서 include할 수 있다.
 */

#ifndef AURA_H
#define AURA_H

#include <stdint.h>
#include <stddef.h>

/* ─────────────────────────────────────────────
 * 에러 코드
 * ───────────────────────────────────────────── */

typedef enum AuraError {
    AURA_OK                = 0,
    AURA_ERR_GENERIC       = -1,
    AURA_ERR_NOMEM         = -2,   /* 메모리 할당 실패 */
    AURA_ERR_IO            = -3,   /* 파일 입출력 오류 */
    AURA_ERR_INVALID_ARG   = -4,   /* 잘못된 인자 */
    AURA_ERR_NOT_SUPPORTED = -5,   /* 미지원 기능/포맷 */
    AURA_ERR_NOT_FOUND     = -6,   /* 심볼/섹션/파일 없음 */
    AURA_ERR_PARSE         = -7,   /* 파싱 실패 */
    AURA_ERR_DISASM        = -8,   /* 디스어셈블 실패 */
    AURA_ERR_LLM           = -9,   /* LLM 연동 오류 */
    AURA_ERR_PATCH         = -10,  /* 패치/인코딩 실패 */
} AuraError;

/* ─────────────────────────────────────────────
 * 공통 타입
 * ───────────────────────────────────────────── */

/** 바이너리 아키텍처 */
typedef enum AuraArch {
    AURA_ARCH_UNKNOWN = 0,
    AURA_ARCH_X86,
    AURA_ARCH_X86_64,
    AURA_ARCH_ARM,
    AURA_ARCH_ARM64,
    AURA_ARCH_MIPS,
    AURA_ARCH_PPC,
    AURA_ARCH_RISCV,
    AURA_ARCH_DALVIK,     /**< Android DEX bytecode */
    AURA_ARCH_MSIL,       /**< .NET CIL/MSIL bytecode */
} AuraArch;

/** 바이너리 파일 포맷 */
typedef enum AuraFileFormat {
    AURA_FORMAT_UNKNOWN = 0,
    AURA_FORMAT_ELF,
    AURA_FORMAT_PE,
    AURA_FORMAT_MACHO,
    AURA_FORMAT_RAW,
    AURA_FORMAT_DEX,      /**< Android DEX */
    AURA_FORMAT_DOTNET,   /**< .NET PE/CLI */
    AURA_FORMAT_FIRMWARE, /**< Raw firmware/ROM image */
} AuraFileFormat;

/** 주소 타입 (64비트 통일) */
typedef uint64_t AuraAddr;

/** 크기 타입 */
typedef uint64_t AuraSize;

#endif /* AURA_H */
