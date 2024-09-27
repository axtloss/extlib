#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#undef free

int
test_malloc_free_secure ()
{
  size_t size = 12;
  char *mall_test = malloc_secure (size);
  if (!mall_test)
    return 1;
  if (memvcmp (mall_test, 0, size) != 0)
    return 2;
  free_secure ((void **) &mall_test, size);
  if (mall_test)
    return 3;
  return 0;
}

struct test_t*
test_malloc_free_secure_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_malloc_free_secure;
  test->test_name="test_malloc_free_secure";
  test->test_desc="malloc_secure free_secure";
  return test;
}
