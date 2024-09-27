#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#undef free

int
test_min_max_cap ()
{
  int val = 5;
  int max_v = 10;
  int min_v = 1;
  if (cap(val, min_v, max_v) != 5)
    return 1;
  if (max(val, max_v) != 5)
    return 2;
  if (min(val, min_v) != 5)
    return 3;

  val = 11;
  if (cap(val, min_v, max_v) != 10)
    return 4;
  if (max(val, max_v) != 10)
    return 5;
  if (min(val, min_v) != 11)
    return 6;

  val = 0;
  if (cap(val, min_v, max_v) != 1)
    return 7;
  if (max(val, max_v) != 0)
    return 8;
  if (min(val, min_v) != 1)
    return 9;

  return 0;
}


struct test_t*
test_min_max_cap_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_min_max_cap;
  test->test_name="test_min_max_cap";
  test->test_desc="min max cap";
  return test;
}
