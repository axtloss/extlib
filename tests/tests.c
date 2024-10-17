#include "test_driver.h"
#include "test_fcopy.c"
#include "test_join_str.c"
#include "test_malloc_free_secure.c"
#include "test_memset_s.c"
#include "test_min_max_cap.c"
#include "test_replace_str.c"
#include "test_strlwr_strupr.c"
#include "test_trim.c"
#include "test_strfmt.c"

inline void
tests_entrypoint ()
{
  register_test (test_fcopy_t ());
  register_test (test_join_str_t( ));
  register_test (test_malloc_free_secure_t ());
  register_test (test_memset_s_t ());
  register_test (test_min_max_cap_t ());
  register_test (test_replace_str_t ());
  register_test (test_strlwr_strupr_t ());
  register_test (test_trim_t ());
  register_test (test_strfmt_t ());
}
