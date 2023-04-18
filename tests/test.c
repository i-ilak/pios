#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>

#include "include/test_string.h"
#include "include/test_stdlib.h"
#include "include/test_atags.h"

int main(int argc, char *argv[])
{
  const struct CMUnitTest tests_string[] = {
    cmocka_unit_test(test_str_len),     cmocka_unit_test(test_str_compare),
    cmocka_unit_test(test_str_copy),    cmocka_unit_test(test_str_concat),
    cmocka_unit_test(test_str_reverse),
  };

  const struct CMUnitTest tests_stdlib[] = {
    cmocka_unit_test(test_div),    cmocka_unit_test(test_divmod),
    cmocka_unit_test(test_itoa),   cmocka_unit_test(test_atoi),
    cmocka_unit_test(test_memset), cmocka_unit_test(test_bzero),
    cmocka_unit_test(test_memcpy),
  };

  const struct CMUnitTest tests_atags[] = {
    cmocka_unit_test(test_atags),
  };

  int first = cmocka_run_group_tests(tests_string, NULL, NULL);
  printf("\n");
  int second = cmocka_run_group_tests(tests_stdlib, NULL, NULL);
  printf("\n");
  int third = cmocka_run_group_tests(tests_atags, NULL, NULL);

  return first && second && third;
}