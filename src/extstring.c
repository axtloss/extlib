/* extstring.c
 * SPDX-License-Identifier: BSD-3-Clause
 */

#define USE_SECURE_MEM
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "extlib.h"

enum gfxnums {
  num_BOLD = 1,
  num_DIM,
  num_ITALIC,
  num_UNDERLINE,
  num_BLINKING,
  num_INVERSE,
  num_HIDDEN,
  num_STRIKETHROUGH,
};

char *
strlwr (char *s)
{
    unsigned char *p = (unsigned char *) s;

    while (*p)
    {
        *p = tolower ((unsigned char) *p);
        p++;
    }

    return s;
}

char *
strupr (char *s)
{
    unsigned char *p = (unsigned char *) s;

    while (*p)
    {
        *p = toupper ((unsigned char) *p);
        p++;
    }

    return s;

}

char *
trim (char *s, int *rem_front, int *rem_back)
{
    char *result = strdup (s);
    char *end;

    while (isspace ((unsigned char) *result))
    {
        result++;
        if (rem_front)
            *rem_front += 1;
    }

    if (*result == 0)
        return result;

    end = result + strlen (result) - 1;
    while (end > result && isspace ((unsigned char) *end))
    {
        end--;
        if (rem_back)
            *rem_back += 1;
    }

    end[1] = '\0';

    return result;
}

char *
replace_str (char *s, char *old, char *replace)
{
    char *result;
    int i, cnt = 0;
    size_t new_size = strlen (replace);
    size_t old_size = strlen (old);

    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr (&s[i], old) == &s[i])
        {
            cnt++;
            i += old_size - 1;
        }
    }

    result = (char *) malloc (i + cnt * (new_size - old_size) + 1);

    i = 0;
    while (*s)
    {
        if (strstr (s, old) == s)
        {
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

char *
join_str (char **s, size_t len, char *delim)
{
    char *ret = strdup (s[0]);
    size_t ret_len = strlen (delim) * len + strlen (ret) + 1;
    size_t old_ret_len = ret_len;

    for (int i = 1; i < len; i++)
    {
      char *ret_tmp = malloc (ret_len + strlen (s[i])); // i should use realloc here but that breaks on musl so malloc it is :3
      ret_len += strlen (s[i]) + 1;
      if (ret_tmp != NULL) {
	sprintf (ret_tmp, "%s%s%s", ret, delim, s[i]);
	free_secure ((void **) &ret, strlen (ret));
	ret = ret_tmp;
      }
    }

    return ret;
}

// all freed strings in this function dont contain confidential data
// so free_secure isnt necessary
#undef free
void
append_gfxsqnc (char **escape_sqnc, size_t *sqnc_size, int gfx_num)
{
  size_t gfxbase_len = strlen ("\e[XXm")+1;
  char *tmp_sqnc = malloc (*sqnc_size + gfxbase_len);
  *sqnc_size += gfxbase_len;
  sprintf (tmp_sqnc, "%s\e[%dm", *escape_sqnc, gfx_num);
  free (*escape_sqnc);
  *escape_sqnc = tmp_sqnc;
}

char *
strfmt (char *s, struct style fmt)
{
  size_t gfxbase_len = strlen ("\e[XXm")+1;
  size_t sqnc_size = strlen ("\e[0m") + strlen (s)+1;
  char *escape_sqnc = strdup ("");
  if (fmt.color > 0) {
    char *tmp_sqnc = malloc (sqnc_size + strlen ("\e[38;5;m")+4);
    sqnc_size += strlen ("\e[38;5;m")+4;
    sprintf (tmp_sqnc, "%s\e[%d;5;%dm", escape_sqnc, fmt.background ? 48 : 38, fmt.color);
    free (escape_sqnc);
    escape_sqnc = tmp_sqnc;
  }

  if ((fmt.styles & BOLD))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_BOLD);

  if ((fmt.styles & DIM))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_DIM);

  if ((fmt.styles & ITALIC))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_ITALIC);

  if ((fmt.styles & UNDERLINE))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_UNDERLINE);

  if ((fmt.styles & BLINKING))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_BLINKING);

  if ((fmt.styles & INVERSE))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_INVERSE);
  
  if ((fmt.styles & HIDDEN))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_HIDDEN);

  if ((fmt.styles & STRIKETHROUGH))
    append_gfxsqnc (&escape_sqnc, &sqnc_size, num_STRIKETHROUGH);

  if (strlen (escape_sqnc) <= 2) {
    free (escape_sqnc);
    return strdup (s);
  }
  
  sprintf (escape_sqnc, "%s%s\e[0m", escape_sqnc, s);  
  return escape_sqnc;
}
