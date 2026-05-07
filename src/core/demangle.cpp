// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * demangle.cpp — C++ symbol demangling (cross-platform)
 *
 * Linux/GCC : __cxa_demangle (cxxabi.h)
 * MSVC      : UnDecorateSymbolName (DbgHelp)
 */

#include "demangle.h"
#include <cstdlib>
#include <cstring>

#ifdef _MSC_VER
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
  #include <dbghelp.h>
  #pragma comment(lib, "Dbghelp.lib")
#else
  #include <cxxabi.h>
#endif

extern "C" char *aura_demangle(const char *mangled)
{
    if (!mangled || mangled[0] == '\0') return nullptr;

#ifdef _MSC_VER
    /* MSVC decorated names start with '?' */
    char buf[1024];
    DWORD len = UnDecorateSymbolName(mangled, buf, sizeof(buf),
                                      UNDNAME_COMPLETE);
    if (len == 0 || strcmp(buf, mangled) == 0)
        return nullptr;  /* demangling failed or no change */
    return strdup(buf);
#else
    int status = 0;
    char *result = abi::__cxa_demangle(mangled, nullptr, nullptr, &status);
    if (status != 0) {
        free(result);
        return nullptr;
    }
    return result; /* caller frees */
#endif
}
