#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * aura_demangle — C++ mangled 심볼을 demangled 문자열로 반환.
 *
 * @param mangled  입력 심볼 이름 (NULL 허용)
 * @return         demangled 문자열 (heap 할당, 호출자가 free() 책임)
 *                 실패하거나 C 심볼이면 NULL 반환
 */
char *aura_demangle(const char *mangled);

#ifdef __cplusplus
}
#endif
