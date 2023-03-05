#ifndef STDLIB_H
#define STDLIB_H

#include <stdint.h>

// Convert base 10 integer to null-terminated string.
char* iota(int32_t value);

// Convert string into integer.
int32_t atoi(const char* str);


#endif // STDLIB_H