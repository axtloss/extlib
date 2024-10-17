#include <string.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"
#include "stdbool.h"

int
test_strfmt ()
{
  int errno = 0;
  char *test_string_1 = strfmt ("meow", (struct style) {0, false, BOLD});
  printf ("\e[1mtest_strfmt\e[0m:: No Color, Bold:           %s\n", test_string_1);
  if (strcmp (test_string_1, "\e[1mmeow\e[0m") != 0)
    errno = 1;

  char *test_string_2 = strfmt ("meow", (struct style) {RED, false, 0});
  printf ("\e[1mtest_strfmt\e[0m:: Red, No style:            %s\n", test_string_2);
  if (strcmp (test_string_2, "\e[38;5;1mmeow\e[0m") != 0)
    errno = 2;

  char *test_string_3 = strfmt ("meow", (struct style) {RED, false, BOLD});
  printf ("\e[1mtest_strfmt\e[0m:: Red, Bold:                %s\n", test_string_3);
  if (strcmp (test_string_3, "\e[38;5;1m\e[1mmeow\e[0m") != 0)
    errno = 3;

  char *test_string_4 = strfmt ("meow", (struct style) {RED, true, 0});
  printf ("\e[1mtest_strfmt\e[0m:: Red background, No style: %s\n", test_string_4);
  if (strcmp (test_string_4, "\e[48;5;1mmeow\e[0m") != 0)
    errno = 4;

  char *test_string_5 = strfmt ("meow", (struct style) {RED, true, BOLD});
  printf ("\e[1mtest_strfmt\e[0m:: Red background, Bold:     %s\n", test_string_5);
  if (strcmp (test_string_5, "\e[48;5;1m\e[1mmeow\e[0m") != 0)
    errno = 5;

  free_secure ((void **) &test_string_1, strlen (test_string_1));
  free_secure ((void **) &test_string_2, strlen (test_string_2));
  free_secure ((void **) &test_string_3, strlen (test_string_3));
  free_secure ((void **) &test_string_4, strlen (test_string_4));
  free_secure ((void **) &test_string_5, strlen (test_string_5));
  return errno;
}

struct test_t*
test_strfmt_t ()
{
  struct test_t* test = malloc (sizeof (struct test_t));
  test->test_func=test_strfmt;
  test->test_name="test_strfmt";
  test->test_desc="strfmt";
  return test;
}

