#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"

int
test_replace_str ()
{
  int errno = 0;
  char *test_string = strdup ("replace world!");
  char *replaced_string = replace_str (test_string, "replace", "hello");
  if (strcmp (replaced_string, "hello world!") != 0)
    errno = 1;

  free_secure ((void **) &test_string, strlen (test_string));
  free_secure ((void **) &replaced_string, strlen (replaced_string));
  return errno;
}

struct test_t*
test_replace_str_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func = test_replace_str;
  test->test_name = "test_replace_str";
  test->test_desc = "replace_str";
}
