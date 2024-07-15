#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#define USE_SECURE_MEM
#include "../src/extlib.h"

int
test_malloc_free_secure (size_t size)
{
  char *mall_test = malloc_secure (size);
  if (!mall_test)
    return 1;
  if (memvcmp (mall_test, 0, size) != 0)
    return 2;
  free_secure ((void **)&mall_test, size);
  if (mall_test)
    return 3;
  return 0;
}

int
test_fcopy()
{
	int errno = 0;
  char *buf_a;
  char *buf_b;
  size_t len_a;
  size_t len_b;
  FILE *file_test_a = open_memstream (&buf_a, &len_a);
  FILE *file_test_b = open_memstream (&buf_b, &len_b);

  fprintf (file_test_a, "hello");
  fflush (file_test_a);
  fclose (file_test_a);
  file_test_a = fmemopen(buf_a, len_a, "r");

  fcopy (file_test_a, file_test_b);
  fclose (file_test_b);

  if (memcmp(buf_a, buf_b, len_a) != 0)
    errno = 1;

  free_secure ((void**)&buf_a, len_a);
  free_secure ((void **)&buf_b, len_b);
  return errno;
}

int
test_strlwr_strupr ()
{
	int errno = 0;
  char *test_string = strdup ("hello");
  char *uppr_string = strupr (test_string);
  char *lower_string = strlwr (uppr_string);

  if (strcmp (uppr_string, "HELLO") != 0)
		errno = 1;

  if (strcmp (lower_string, "hello") != 0)
		errno = 2;

 EXIT:
  free_secure ((void **)&test_string, strlen (test_string));
  return errno;
}

int
test_trim()
{
#undef free
	int errno = 0;
  char *test_string = strdup ("\t\thi\t\t");
  int rem_front = 0;
  int rem_back = 0;
  char *trimmed_string = trim (test_string, &rem_front, &rem_back);
  if (strstr (trimmed_string, "\t") != NULL) {
		errno = 1;
		goto EXIT;
  }
  if (rem_front != 2 && rem_back != 2) {
		errno = 2;
		goto EXIT;
  }

 EXIT:
  free (trimmed_string-rem_front);
  free_secure ((void**)&test_string, strlen (test_string));
  return errno;
}

int
test_replace_str ()
{
	int errno = 0;
  char *test_string = strdup ("replace world!");
  char *replaced_string = replace_str (test_string, "replace", "hello");
  if (strcmp (replaced_string, "hello world!") != 0)
    errno = 1;

  free_secure ((void**)&test_string, strlen (test_string));
  free_secure ((void**)&replaced_string, strlen (replaced_string));
  return errno;
}

int
test_join_str ()
{
	int errno = 0;
	char **test_string = malloc (sizeof (char*) * 4);
	for (int i = 0; i < 3; i++)
		test_string [i] = strdup ("hello");

	char *joined_string = join_str (test_string, 3, ' ');

	if (strcmp (joined_string, "hello hello hello") != 0)
		errno = 1;

	free_secure ((void**)&test_string[0], strlen (test_string[0]));
	free_secure ((void**)&test_string[1], strlen (test_string[1]));
	free_secure ((void**)&test_string[2], strlen (test_string[2]));
	free (test_string);
	free_secure ((void**)&joined_string, strlen (joined_string));
	return errno;
}

int
main (void)
{
  printf ("=== extlib unit tests ===\n");
  printf ("\n");

  printf ("Test Case 1: test_malloc_free_secure -- malloc_secure free_secure memvcmp\n");
  int test_1_result = test_malloc_free_secure (12);
  if (test_1_result == 0)
    printf ("Test Case 1: test_malloc_free_secure -- SUCCESS\n\n");
  else
    printf ("Test Case 1: test_malloc_free_secure -- FAILED %d\n\n", test_1_result);

  printf ("Test Case 2: test_fcopy -- fcopy\n");
  int test_2_result = test_fcopy ();
  if (test_2_result == 0)
    printf ("Test Case 2: test_fcopy -- SUCCESS\n\n");
  else
    printf ("Test Case 2: test_fcopy -- FAILED %d\n\n", test_2_result);

  printf ("Test Case 3: test_strlwr_strupr -- strlwr strupr\n");
  int test_3_result = test_strlwr_strupr ();
  if (test_2_result == 0)
    printf ("Test Case 3: test_strlwr_strupr -- SUCCESS\n\n");
  else
    printf ("Test Case 3: test_strlwr_strupr -- FAILED %d\n\n", test_3_result);

  printf ("Test Case 4: test_trim -- trim\n");
  int test_4_result = test_trim ();
  if (test_4_result == 0)
    printf ("Test Case 4: test_trim -- SUCCESS\n\n");
  else
    printf ("Test Case 4: test_trim -- FAILED %d\n\n", test_4_result);

  printf ("Test Case 5: test_replace_str -- replace_str\n");
  int test_5_result = test_replace_str();
  if (test_5_result == 0)
    printf ("Test Case 5: test_replace_str -- SUCCESS\n\n");
  else
    printf ("Test Case 5: test_replace_str -- FAILED %d\n\n", test_5_result);

	printf ("Test Case 6: test_join_str -- join_str\n");
	int test_6_result = test_join_str();
	if (test_6_result == 0)
		printf ("Test Case 6: test_join_str -- SUCCESS\n\n");
	else
		printf ("Test Case 6: test_join_str -- FAILED %d\n\n", test_6_result);
  return 0;
}
