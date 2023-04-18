#ifndef TEST_STRING_H
#define TEST_STRING_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_str_len(void** state);

void test_str_compare(void** state);

void test_str_copy(void** state);

void test_str_concat(void** state);

void test_str_reverse(void** state);

#endif // TEST_STRING_H