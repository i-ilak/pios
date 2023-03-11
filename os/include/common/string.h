#ifndef STRING_H
#define STRING_H

#include <stddef.h>         // defines NULL and size_t
#include <stdint.h>

void* memset(void* s, int c, size_t n);
void* memcpy(void* dest, const void* src, size_t n);

uint32_t strlen(char* str);

int32_t strcmp(const char* s1, const char* s2);

char* strcpy(char* dest, const char* src);
char* strcat(char* dest, const char* src);

void strrev(char* str);

#endif // STRING_H