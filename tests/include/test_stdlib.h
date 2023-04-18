#ifndef TEST_STDLIB_H
#define TEST_STDLIB_H

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

void test_div(void **state);

void test_divmod(void **state);

void test_itoa(void **state);

void test_atoi(void **state);

void test_memset(void **state);

void test_bzero(void **state);

void test_memcpy(void **state);

#endif // TEST_STDLIB_H