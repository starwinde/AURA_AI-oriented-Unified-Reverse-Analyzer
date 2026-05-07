// Copyright 2026 AURA Project Contributors
// SPDX-License-Identifier: Apache-2.0

/**
 * mapped_file.h — Memory-mapped file I/O layer (cross-platform)
 *
 * B안 2레이어 (D-10) 설계: MappedFile은 파일 I/O 전담 레이어 1이다.
 * Linux: open() + mmap(), Windows: CreateFile + CreateFileMapping + MapViewOfFile.
 */

#ifndef MAPPED_FILE_H
#define MAPPED_FILE_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * MappedFile — cross-platform memory-mapped file handle.
 */
typedef struct {
#ifdef _WIN32
    void          *hFile;     /**< HANDLE from CreateFileA (cast to void*) */
    void          *hMapping;  /**< HANDLE from CreateFileMappingA          */
    int            fd;        /**< POSIX-compat sentinel for legacy tests  */
#else
    int            fd;        /**< open() file descriptor                  */
#endif
    const uint8_t *map;       /**< mapped read-only pointer                */
    size_t         size;      /**< file size in bytes                      */
    char          *path;      /**< strdup copy, MappedFile owns            */
} MappedFile;

MappedFile *mapped_file_open(const char *path);
void mapped_file_destroy(MappedFile *mf);

#ifdef __cplusplus
}
#endif

#endif /* MAPPED_FILE_H */
