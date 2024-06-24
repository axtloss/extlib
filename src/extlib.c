/* extlib.c
 *
 * Copyright 2024 axtlos <axtlos@disroot.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * SPDX-License-Identifier: LGPL-3.0-only
 */

#include "extlib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef free
#undef malloc

void
free_secure(void **__ptr, size_t ptrlen)
{
  memset (*__ptr, 0, ptrlen);
  free (*__ptr);
  *__ptr = NULL;
  return;
}

void *
malloc_secure (size_t len)
{
  void *mem = malloc (len);
  memset (mem, 0, len);
  return mem;
}

int
memvcmp (void *str,
	 char val,
	 size_t n)
{
  char str2[n];
  memset (str2, val, n);
  return memcmp (str, str2, n);
}

void
fcopy(FILE *f1, FILE *f2)
{
  char buffer[BUFSIZ];
  size_t n;

  while ((n = fread (buffer, sizeof (char), sizeof (buffer), f1)) > 0)
  {
    if (fwrite (buffer, sizeof (char), n, f2) != n) {
      fprintf (stderr, "Failed to copy data");
      return;
    }
    fflush (f2);
  }
}
