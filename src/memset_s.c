/* memset_s.c
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


#define __STDC_WANT_LIB_EXT1__ 1
#include "extlib.h"
#include <errno.h>


errno_t
memset_s(void *s, rsize_t smax, int c, rsize_t n)
{
  volatile unsigned char *dest = (unsigned char *) s;
  errno_t ret = EINVAL;
  rsize_t limit = n < smax ? n : smax;

  if (!s)
    throw_constraint_handler_s("memset_s: s = NULL", ret);
  else if (n > RSIZE_MAX)
    throw_constraint_handler_s("memset_s: n > RSIZE_MAX", ret);
  else if (smax > RSIZE_MAX)
    throw_constraint_handler_s("memset_s: smax > RSIZE_MAX", ret);
  else if (n > smax)
    throw_constraint_handler_s("memset_s: n > smax", ret);
  else {
    while (limit > 0)
      dest[--limit] = (unsigned char)c;
    ret = 0;
  }
  return ret;
}

