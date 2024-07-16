/*
 * extlib.c
 *
 * Copyright 2024 axtlos <axtlos@disroot.org>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#define _XOPEN_SOURCE 500
#define USE_SECURE_MEM
#define __STDC_WANT_LIB_EXT1__ 1
#include <ftw.h>

#include "extlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef free
#undef malloc

void
free_secure (void **__ptr, size_t ptrlen)
{
    memset_s (*__ptr, ptrlen + 1, 0, ptrlen);
    free (*__ptr);
    *__ptr = NULL;
    return;
}

void *
malloc_secure (size_t len)
{
    void *mem = calloc (1, len);
    return mem;
}

int
memvcmp (void *str, char val, size_t n)
{
    char str2[n];
    memset (str2, val, n);
    return memcmp (str, str2, n);
}

size_t
fcopy (FILE *src, FILE *dst)
{
    char buffer[BUFSIZ];
    size_t n, copied = 0;

    if (src == NULL || dst == NULL)
        return -1;

    while ((n = fread (buffer, sizeof (char), sizeof (buffer), src)) > 0)
    {
        if (fwrite (buffer, sizeof (char), n, dst) != n)
        {
            fprintf (stderr, "Failed to copy data");
            return -1;
        }
        fflush (dst);
        copied += n;
    }
    return copied;
}

int
rmfile (const char *fpath,
        const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
    int err = remove (fpath);
    if (err < 0)
        return err;
    return 0;
}

int
rrmdir (char *pathname)
{
    int err = nftw (pathname, rmfile, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS);
    if (err < 0)
        return err;
    return 0;
}
