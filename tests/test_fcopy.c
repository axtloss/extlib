#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#undef free

int
test_fcopy ()
{
  int errno = 0;
  char *buf_a;
  char *buf_b;
  size_t len_a;
  size_t len_b;
  FILE *file_test_a = open_memstream (&buf_a, &len_a);
  FILE *file_test_b = open_memstream (&buf_b, &len_b);

  fprintf (file_test_a, "meow");
  fflush (file_test_a);
  fclose (file_test_a);
  file_test_a = fmemopen (buf_a, len_a, "r");

  fcopy (file_test_a, file_test_b);
  fclose (file_test_b);

  if (memcmp (buf_a, buf_b, len_a) != 0)
    errno = 1;

  free_secure ((void **) &buf_a, len_a);
  free_secure ((void **) &buf_b, len_b);
  return errno;
}

struct test_t*
test_fcopy_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_fcopy;
  test->test_name="test_fcopy";
  test->test_desc="fcopy";
  return test;
}
