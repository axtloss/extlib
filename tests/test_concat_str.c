#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"

int
test_concat_str (void)
{
  int errno = 0;
  char *test_string1 = "hello ";
  char *test_string2 = "world";

  char *concatenated_string = concat_str (test_string1, test_string2);

  if (strcmp (concatenated_string, "hello world") != 0)
    errno = 1;

  free_secure ((void **) &concatenated_string, strlen (concatenated_string)-1);
  return errno;
}

struct test_t*
test_concat_str_t()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_concat_str;
  test->test_name="test_concat_str";
  test->test_desc="concat_str";
  return test;
}
