/* constraint_handler.c
 * SPDX-License-Identifier: BSD-3-Clause
 */


#define __STDC_WANT_LIB_EXT1__ 1
#include "extlib.h"

static constraint_handler_t *_cnstrnt_handler = NULL;

constraint_handler_t
set_constraint_handler_s (constraint_handler_t handler)
{
  constraint_handler_t *new, *old, ret;

  new = malloc (sizeof (constraint_handler_t));
  if (!new) return NULL;
  *new = handler;
  old = _cnstrnt_handler;
  _cnstrnt_handler = new;
  if (!old)
    ret = NULL;
  else {
    ret = *old;
    free (old);
  }
  return ret;
}

void
throw_constraint_handler_s (const char * restrict msg, errno_t error)
{
  constraint_handler_t ch;
  ch = _cnstrnt_handler != NULL ? *_cnstrnt_handler : NULL;
  if (ch != NULL)
    ch (msg, NULL, error);
}

void
abort_handler_s (const char *restrict msg, void * restrict ptr, errno_t error)
{
  static const char abrt_msg[] = "abort_handler: ";

  fprintf (stderr, "%s", abrt_msg);
  fprintf (stderr, "%s\n", msg);
  abort ();
}

void
ignore_handler_s (const char * restrict msg, void * restrict ptr, errno_t error)
{}
