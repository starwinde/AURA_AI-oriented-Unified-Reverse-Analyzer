#pragma once

/*
 * Minimal MSVC compatibility shim for project/test files that still include
 * <unistd.h>. The real POSIX header is used on non-MSVC toolchains.
 */
#ifdef _MSC_VER
#include "aura_compat.h"
#else
#include_next <unistd.h>
#endif
