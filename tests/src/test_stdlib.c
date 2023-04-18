#include "include/test_stdlib.h"

#include "../os/include/common/stdlib.h"

void test_div(void **state)
{
    assert_int_equal(0, div(1, 2));
    assert_int_equal(46, div(234, 5));
}

void test_divmod(void **state)
{
    divmod_t res = divmod(234, 5);
    assert_int_equal(res.div, 46);
    assert_int_equal(res.mod, 4);
}

void test_itoa(void **state)
{
    assert_string_equal("26", itoa(26, 10));
    assert_string_equal("-26", itoa(-26, 10));
    assert_string_equal("0b11010", itoa(26, 2));
    assert_string_equal("-0b11010", itoa(-26, 2));
    assert_string_equal("0x1a", itoa(26, 16));
}

void test_atoi(void **state)
{
    assert_int_equal(26, atoi("26"));
    assert_int_equal(-26, atoi("-26"));
}

void test_memset(void **state)
{
    char str[50] = "I need a sentence to test this!";
    memset(str + 5, '.', 8);
    assert_string_equal(str, "I nee........ence to test this!");

    int32_t arr[10];
    for(int32_t i = 0; i < 10; i++)
        arr[i] = 1;
    memset(arr, 0, 4 * 10);
    for(int32_t i = 0; i < 10; i++)
        assert_int_equal(0, arr[i]);
}

void test_bzero(void **state)
{
    int32_t arr[10];
    for(int32_t i = 0; i < 10; i++)
        arr[i] = 1;
    for(int32_t i = 0; i < 10; i++)
        assert_int_not_equal(0, arr[i]);
    bzero(arr, 4 * 10);
    for(int32_t i = 0; i < 10; i++)
        assert_int_equal(0, arr[i]);
}

void test_memcpy(void **state)
{
    int32_t arr[10];
    for(int32_t i = 0; i < 10; i++)
        arr[i] = 1;

    int32_t comp[10];
    for(int32_t i = 0; i < 10; i++)
        comp[i] = 0;

    for(int32_t i = 0; i < 10; i++)
        assert_int_not_equal(comp[i], arr[i]);

    memcpy(comp, arr, 4 * 10);

    for(int32_t i = 0; i < 10; i++)
        assert_int_equal(comp[i], arr[i]);
}