/* extlib.h
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

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#ifdef USE_SECURE_MEM
#define free(x) error - use free_secure

/// Automatically zero out a pointer before freeing it
void free_secure (void **__ptr, size_t ptrlen);

/// DEPRECATED: use calloc
/// Automatically initialise the allocated memory with zeros
void *malloc_secure (size_t len);
#endif

#if (__STDC_WANT_LIB_EXT1__ == 1)
#define RSIZE_MAX SIZE_MAX
typedef int errno_t;
typedef size_t rsize_t;

typedef void (*constraint_handler_t) (const char *__restrict, void *__restrict, errno_t);
/// Copy the value of c (converted to an unsigned char) into each of the first n
/// characters of the object pointed to by s.
/// Conforms to ISO/IEC 9899:2011 K.3.7.4.1
errno_t memset_s (void *s, rsize_t max, int c, rsize_t n);

constraint_handler_t set_constraint_handler_s (constraint_handler_t handler);
void throw_constraint_handler_s (const char *restrict msg, errno_t error);
_Noreturn void abort_handler_s (const char * __restrict, void * __restrict,
				errno_t);
void ignore_handler_s (const char *__restrict, void *__restrict, errno_t);
#endif


/// Copy the data of one filestream to another */
void fcopy(FILE *f1, FILE *f2);

#if (_XOPEN_SOURCE == 500)
/// Recursively remove a directory pathname.
int rrmdir(char *pathname);
#endif

/// Compare the first n bytes of a memory area str to the value val.
/// Returns 0 if the values the same, any other value if they are not the same.
int memvcmp (void *str, char val, size_t n);

/// Convert a string to lowercase
char *strlwr(char *s);

/// Convert a string to uppercase
char *strupr(char *s);

/// Trim spaces from a string
char *trim (char *s, int *rem_front, int *rem_back);

/// Match string old and replace it with string replace
char *replace_str (char *s, char *old, char *replace);

