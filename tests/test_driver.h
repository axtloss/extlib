struct test_t {
  int (*test_func)(void);
  char *test_name;
  char *test_desc;
};

void register_test (struct test_t *test);
void tests_entrypoint ();
