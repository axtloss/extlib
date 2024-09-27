#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#undef free

int
test_join_str ()
{
  int errno = 0;
  char **test_string = malloc (sizeof (char *) * 4);
  for (int i = 0; i < 3; i++)
    test_string[i] = strdup ("hello");

  char *joined_string = join_str (test_string, 3, " && ");

  if (strcmp (joined_string, "hello && hello && hello") != 0)
    errno = 1;

  free_secure ((void **) &test_string[0], strlen (test_string[0]));
  free_secure ((void **) &test_string[1], strlen (test_string[1]));
  free_secure ((void **) &test_string[2], strlen (test_string[2]));
  free (test_string);
  free_secure ((void **) &joined_string, strlen (joined_string));
  return errno;
}

struct test_t*
test_join_str_t()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_join_str;
  test->test_name="test_join_str";
  test->test_desc="join_str";
  return test;
}
