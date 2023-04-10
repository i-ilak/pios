/**
 * @file
 * @brief Implement basic functionality of the stdint-C-library.
 */

#include <stddef.h>         // defines NULL and size_t
#include <stdint.h>
#ifndef STDLIB_H
#define STDLIB_H

#define MIN(x,y) ((x < y ? x : y))
#define MAX(x,y) ((x < y ? y : x))

typedef struct divmod_result {
    uint32_t div;
    uint32_t mod;
} divmod_t;

divmod_t divmod(uint32_t dividend, uint32_t divisor);
uint32_t div(uint32_t dividend, uint32_t divisor);

/**
 * @brief Fills the first @a n bytes of the memory area pointed to by @a s with the constant byte @a c.
 * @return A pointer to the memory area s.
 */
void* memset(void * dest, int c, unsigned int bytes);

/**
 * @brief Copies @a n bytes from memory area @a src to memory area @a dest. The memory areas must not overlap.
 * @return A pointer to dest.
 */
void* memcpy(void * dest, const void * src, unsigned int bytes);

/**
 * @brief int -> str(int) 
 * 
 * Converts an int (Only base 10 supported for now)
 * to a null-terminated string using the specified base.
 * @param value Value to be converted to a string.
 * @return A pointer to the resulting null-terminated string.
 */
char* itoa(int value, int base);


/**
 * @brief str -> int 
 * 
 * Converts a string to an int
 * @param str This is the string representation of an integral number.
 * @return The converted integral number as an int value.
 * 	If no valid conversion could be performed, it returns zero.
 */
int atoi(char* str);


/**
 * @brief Zero out the section [dest, dest+bytes]
 * 
 * @param dest 
 * @param bytes 
 */
void bzero(void * dest, int bytes);

#endif // STDLIB_H