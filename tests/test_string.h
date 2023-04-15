#ifndef TEST_STRING_H
#define TEST_STRING_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../os/include/common/string.h"

static void test_str_len(void** state) {
  assert_int_equal(2, strlen("th"));
  assert_int_equal(0, strlen(""));
  assert_int_equal(1, strlen("\n"));
  assert_int_equal(0, strlen("\0"));
}

static void test_str_compare(void** state) {
  assert_int_equal(0, strcmp("", ""));
  assert_int_equal(1, strcmp("1", ""));
  assert_int_equal(-1, strcmp("", "a"));
}

static void test_str_copy(void** state) {
  char test0[] = "test";
  char dest0[5];
  assert_string_equal(test0, strcpy(dest0, test0));
  char test1[] = "";
  char dest1[0];
  assert_string_equal(test1, strcpy(dest1, test1));
  char test2[] = "a\0";
  char dest2[2];
  assert_string_equal(test2, strcpy(dest2, test2));
  char test3[] = "will this work\0";
  char dest3[3];
  assert_string_equal(test3, strcpy(dest3, test3));
}

static void test_str_concat(void** state){
  char result0[] = "Hello World!";
  char dest0[] = "Hello "; 
  assert_string_equal(result0, strcat(dest0, "World!"));
  char result1[] = "World!\0";
  char dest1[] = "\0"; 
  assert_string_equal(result1, strcat(dest1, "World!"));
  char result2[] = "\0";
  char dest2[] = "\0"; 
  assert_string_equal(result2, strcat(dest2, "\0"));
}

static void test_str_reverse(void** state){
  char result[] = "Hello World!";
  char dest[] = "!dlroW olleH";
  strrev(dest);
  assert_string_equal(result, dest);
}

#endif // TEST_STRING_H