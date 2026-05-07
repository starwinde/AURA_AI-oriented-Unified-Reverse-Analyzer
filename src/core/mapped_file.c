// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * mapped_file.c — Cross-platform memory-mapped file I/O
 *
 * Linux : open() + mmap()
 * Windows: CreateFileA + CreateFileMappingA + MapViewOfFile
 */

#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
  #define WIN32_LEAN_AND_MEAN
  #include <windows.h>
#else
  #include <fcntl.h>
  #include <unistd.h>
  #include <sys/mman.h>
  #include <sys/stat.h>
#endif

#include "mapped_file.h"

/* ── mapped_file_open ────────────────────────────────────────────────── */

MappedFile *mapped_file_open(const char *path)
{
    if (!path) return NULL;

    MappedFile *mf = (MappedFile *)calloc(1, sizeof(MappedFile));
    if (!mf) return NULL;

#ifdef _WIN32
    /* --- Windows path --- */
    HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        free(mf);
        return NULL;
    }

    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(hFile, &fileSize) || fileSize.QuadPart <= 0) {
        CloseHandle(hFile);
        free(mf);
        return NULL;
    }

    HANDLE hMapping = CreateFileMappingA(hFile, NULL, PAGE_READONLY,
                                          0, 0, NULL);
    if (!hMapping) {
        CloseHandle(hFile);
        free(mf);
        return NULL;
    }

    const uint8_t *view = (const uint8_t *)MapViewOfFile(
        hMapping, FILE_MAP_READ, 0, 0, 0);
    if (!view) {
        CloseHandle(hMapping);
        CloseHandle(hFile);
        free(mf);
        return NULL;
    }

    mf->hFile    = (void *)hFile;
    mf->hMapping = (void *)hMapping;
    mf->fd       = -1;
    mf->map      = view;
    mf->size     = (size_t)fileSize.QuadPart;

#else
    /* --- POSIX path --- */
    mf->fd = open(path, O_RDONLY);
    if (mf->fd < 0) {
        free(mf);
        return NULL;
    }

    struct stat st;
    if (fstat(mf->fd, &st) != 0 || st.st_size <= 0) {
        close(mf->fd);
        free(mf);
        return NULL;
    }

    mf->size = (size_t)st.st_size;
    mf->map  = (const uint8_t *)mmap(NULL, mf->size,
                                     PROT_READ, MAP_PRIVATE, mf->fd, 0);
    if (mf->map == (const uint8_t *)MAP_FAILED) {
        close(mf->fd);
        free(mf);
        return NULL;
    }
#endif

    mf->path = strdup(path);
    if (!mf->path) {
        mapped_file_destroy(mf);
        return NULL;
    }

    return mf;
}

/* ── mapped_file_destroy ─────────────────────────────────────────────── */

void mapped_file_destroy(MappedFile *mf)
{
    if (!mf) return;

#ifdef _WIN32
    if (mf->map)
        UnmapViewOfFile(mf->map);
    if (mf->hMapping)
        CloseHandle((HANDLE)mf->hMapping);
    if (mf->hFile && mf->hFile != INVALID_HANDLE_VALUE)
        CloseHandle((HANDLE)mf->hFile);
#else
    if (mf->map && mf->map != (const uint8_t *)MAP_FAILED)
        munmap((void *)mf->map, mf->size);
    if (mf->fd >= 0)
        close(mf->fd);
#endif

    free(mf->path);
    free(mf);
}
