#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#undef free

int
test_trim ()
{
  int errno = 0;
  char *test_string = strdup ("\t\thi\t\t");
  int rem_front = 0;
  int rem_back = 0;
  char *trimmed_string = trim (test_string, &rem_front, &rem_back);
  if (strstr (trimmed_string, "\t") != NULL)
  {
    errno = 1;
  }
  else if (rem_front != 2 && rem_back != 2)
  {
    errno = 2;
  }

  free (trimmed_string - rem_front);
  free_secure ((void **) &test_string, strlen (test_string));
  return errno;
}

struct test_t*
test_trim_t ()
{
  struct test_t *test = malloc (sizeof (struct test_t));
  test->test_func = test_trim;
  test->test_name = "test_trim";
  test->test_desc = "trim";
  return test;
}
