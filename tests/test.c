#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

static void test_integers(void** state) {
  assert_int_equal(1,1);
}

int main(int argc, char* argv[]) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_integers),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}