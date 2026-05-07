#pragma once

/*
 * Compiler compatibility macros.
 *
 * AURA_WEAK   — weak symbol definition / declaration.
 *   GCC/Clang: __attribute__((weak))  — undefined weak ref resolves to NULL.
 *   MSVC:      empty — all deps must be present in the link unit.
 *              Weak stub function *definitions* must be guarded with
 *              #ifndef _MSC_VER to avoid ODR violations when the strong
 *              definition is also in the same link unit.
 *
 * AURA_UNUSED — suppress unused-variable/parameter warning on a declaration.
 *   GCC/Clang: __attribute__((unused))
 *   MSVC:      empty (MSVC warning C4100/C4101 is /W4-only, not /WX by default).
 */

#ifdef _MSC_VER
#  define AURA_WEAK
#  define AURA_UNUSED
#else
#  define AURA_WEAK   __attribute__((weak))
#  define AURA_UNUSED __attribute__((unused))
#endif

/*
 * POSIX I/O compatibility.
 * MSVC exposes dup/dup2/fileno/close/open under _ prefixed names in <io.h>.
 * Include <unistd.h> on POSIX platforms instead.
 *
 * AURA_DEV_NULL — platform null device path for stdout suppression.
 */
#ifdef _MSC_VER
#  include <stdlib.h>
#  include <string.h>
#  include <stdio.h>
#  include <stdint.h>
#  include <errno.h>
#  include <time.h>
#  include <io.h>
#  include <fcntl.h>
#  include <process.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#  ifndef ssize_t
typedef intptr_t ssize_t;
#  endif
#  ifndef R_OK
#    define R_OK 4
#  endif
#  ifndef STDOUT_FILENO
#    define STDOUT_FILENO 1
#  endif
#  ifndef CLOCK_MONOTONIC
#    define CLOCK_MONOTONIC 1
#  endif
#  ifndef strdup
#    define strdup          _strdup
#  endif
#  ifndef strcasecmp
#    define strcasecmp      _stricmp
#  endif
#  ifndef strncasecmp
#    define strncasecmp     _strnicmp
#  endif
#  ifndef strndup
#    define strndup         aura_strndup_inline
#  endif
#  ifndef aligned_alloc
#    define aligned_alloc   aura_aligned_alloc_inline
#  endif
#  ifndef fmemopen
#    define fmemopen        aura_fmemopen_inline
#  endif
#  ifndef mkstemp
#    define mkstemp         aura_mkstemp_inline
#  endif
#  ifndef realpath
#    define realpath        aura_realpath_inline
#  endif
#  ifndef setenv
#    define setenv          aura_setenv_inline
#  endif
#  ifndef unsetenv
#    define unsetenv        aura_unsetenv_inline
#  endif
#  ifndef getpid
#    define getpid          _getpid
#  endif
#  ifndef clock_gettime
#    define clock_gettime   aura_clock_gettime_inline
#  endif
#  ifndef dup
#    define dup(fd)         _dup(fd)
#  endif
#  ifndef dup2
#    define dup2(a, b)      _dup2((a), (b))
#  endif
#  ifndef fileno
#    define fileno(f)       _fileno(f)
#  endif
#  ifndef close
#    define close(fd)       _close(fd)
#  endif
#  ifndef open
#    define open            _open
#  endif
#  ifndef write
#    define write           _write
#  endif
#  ifndef read
#    define read            _read
#  endif
#  ifndef access
#    define access          _access
#  endif
#  ifndef unlink
#    define unlink          _unlink
#  endif
#  define AURA_DEV_NULL     "nul"

static inline char *aura_strndup_inline(const char *s, size_t n)
{
    size_t len = 0;
    char *out = NULL;

    if (!s) return NULL;
    while (len < n && s[len]) {
        len++;
    }

    out = (char *)malloc(len + 1);
    if (!out) return NULL;
    if (len > 0) {
        memcpy(out, s, len);
    }
    out[len] = '\0';
    return out;
}

static inline void *aura_aligned_alloc_inline(size_t alignment, size_t size)
{
    (void)alignment;
    return malloc(size);
}

static inline FILE *aura_fmemopen_inline(void *buf, size_t size, const char *mode)
{
    FILE *f = NULL;

    if (!buf && size > 0) return NULL;
    f = tmpfile();
    if (!f) return NULL;

    if (mode && (mode[0] == 'r' || mode[0] == 'a')) {
        if (size > 0 && fwrite(buf, 1, size, f) != size) {
            fclose(f);
            return NULL;
        }
        rewind(f);
    }
    return f;
}

static inline int aura_mkstemp_inline(char *tmpl)
{
    size_t len;

    if (!tmpl) return -1;
    len = strlen(tmpl) + 1;
    if (_mktemp_s(tmpl, len) != 0) {
        return -1;
    }
    return _open(tmpl, _O_CREAT | _O_EXCL | _O_RDWR | _O_BINARY,
                 _S_IREAD | _S_IWRITE);
}

static inline char *aura_realpath_inline(const char *path, char *resolved)
{
    return _fullpath(resolved, path, 0);
}

static inline int aura_setenv_inline(const char *name, const char *value, int overwrite)
{
    if (!name || !*name || strchr(name, '=')) return -1;
    if (!overwrite && getenv(name)) return 0;
    return _putenv_s(name, value ? value : "");
}

static inline int aura_unsetenv_inline(const char *name)
{
    if (!name || !*name || strchr(name, '=')) return -1;
    return _putenv_s(name, "");
}

static inline int aura_clock_gettime_inline(int clock_id, struct timespec *ts)
{
    (void)clock_id;
    if (!ts) return -1;
    timespec_get(ts, TIME_UTC);
    return 0;
}
#else
#  include <unistd.h>
#  define AURA_DEV_NULL     "/dev/null"
#endif
