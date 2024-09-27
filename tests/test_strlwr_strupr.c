#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"

int
test_strlwr_strupr ()
{
  int errno = 0;
  char *test_string = strdup ("meow");

  char *uppr_string = strupr (test_string);
  if (strcmp (uppr_string, "MEOW") != 0)
    errno = 1;

  char *lower_string = strlwr (uppr_string);
  if (strcmp (lower_string, "meow") != 0)
    errno = 2;

  free_secure ((void **) &test_string, strlen (test_string));
  return errno;
}

struct test_t*
test_strlwr_strupr_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_strlwr_strupr;
  test->test_name="test_strlwr_strupr";
  test->test_desc="strlwr strupr";
  return test;
}

