/* extstring.c
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

#define USE_SECURE_MEM
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "extlib.h"

char *
strlwr (char *s)
{
  unsigned char *p = (unsigned char *) s;

  while (*p) {
     *p = tolower ((unsigned char)*p);
      p++;
  }

  return s;
}

char *
strupr (char *s)
{
  unsigned char *p = (unsigned char *) s;

  while (*p) {
     *p = toupper ((unsigned char)*p);
      p++;
  }

  return s;

}

char *
trim (char *s, int *rem_front, int *rem_back)
{
  char *result = strdup (s);
  char *end;

  while (isspace ((unsigned char)*result)) {
    result++;
    if (rem_front) *rem_front += 1;
  }

  if (*result == 0)
    return result;

  end = result + strlen (result) - 1;
  while (end > result && isspace ((unsigned char)*end)) {
    end--;
    if (rem_back) *rem_back +=1;
  }

  end[1] = '\0';

  return result;
}

char *
replace_str (char *s,
	    char *old,
	    char *replace)
{
  char* result;
  int i, cnt = 0;
  size_t new_size = strlen (replace);
  size_t old_size = strlen (old);

  for (i = 0; s[i] != '\0'; i++) {
    if (strstr (&s[i], old) == &s[i]) {
      cnt++;
      i += old_size - 1;
    }
  }

  result = (char*)malloc_secure (i + cnt * (new_size - old_size) + 1);

  i = 0;
  while (*s) {
    if (strstr (s, old) == s) {
      strcpy (&result[i], replace);
      i += new_size;
      s += old_size;
    }
    else
      result[i++] = *s++;
  }

  result[i] = '\0';
  return result;
};
