/* memset_s.c
 * SPDX-License-Identifier: BSD-3-Clause
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

