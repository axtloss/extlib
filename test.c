#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <extlib.h>
#include <assert.h>

void print_hex(const char *s)
{
  while(*s)
    printf("%02x", (unsigned int) *s++);
  printf("\n");
}

int
main(void) {
  char *test = malloc_secure (9);
  sprintf (test, "meowmeow");
  assert (strcmp (test, "meowmeow") == 0);
  puts ("Test 1 passed");
  char *upper = strupr (test);
  assert (strcmp (upper, "MEOWMEOW") == 0);
  puts ("Test 2 passed");
  char *lower = strlwr (test);
  assert (strcmp (lower, "meowmeow") == 0);
  puts ("Test 3 passed");
  free_secure (lower, strlen (lower));
}
