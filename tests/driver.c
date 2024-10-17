#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#include "test_driver.h"

char* success;
char* fail;

int tests_count;
struct test_t** registered_tests;

int
test_runner (struct test_t *test, int n)
{
  printf ("Test Case %d: %s -- %s\n", n, test->test_name, test->test_desc);
  int test_result = test->test_func();
  if (test_result == 0)
    printf ("Test Case %d: %s -- %s\n\n", n, test->test_name, success);
  else
    printf ("Test Case %d: %s -- %s %d\n\n", n, test->test_name, fail, test_result);
}

void
register_test (struct test_t *test)
{
  tests_count += 1;
  registered_tests = reallocarray (registered_tests, sizeof (struct test_t), tests_count);

  registered_tests[tests_count-1] = test;
}

int
main (int argc, char *argv[])
{
  success = strfmt("SUCCESS", (struct style) {.color = GREEN, .background = false, .styles = BOLD|UNDERLINE});
  fail = strfmt("FAIL", (struct style) {.color = RED, .background = false, .styles = BOLD|UNDERLINE});
  
  registered_tests = malloc (8);
  tests_entrypoint();
  for (int i = 0; i < tests_count; i++)
  {
    test_runner(registered_tests[i], i+1);
  }
  return 0;
}
