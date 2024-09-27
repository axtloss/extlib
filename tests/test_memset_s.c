#include <string.h>
#define USE_MEM_SECURE
#define __STDC_WANT_LIB_EXT1__ 1
#include "../src/extlib.h"

int
test_memset_s ()
{
  int errno = 0;
  char *buf = malloc (100);

  if (memset_s (buf, 100, 'a', 100) != 0)
    errno = 1;

  if (memvcmp (buf, 'a', 100) != 0)
    errno = 2;

  free_secure ((void **) &buf, 100);
  return errno;
}

struct test_t*
test_memset_s_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func = test_memset_s;
  test->test_name = "test_memset_s";
  test->test_desc = "memset_s";
  return test;
}
