/**
 * @file
 * @brief Implement basic functionality of the stdint-C-library.
 */

#include <stddef.h> // defines NULL and size_t
#include <stdint.h>
#ifndef STDLIB_H
#define STDLIB_H /**< STDLIB_H */

#define MIN(x, y) ((x < y ? x : y)) /**< Find minimum of x and y */
#define MAX(x, y) ((x < y ? y : x)) /**< Find maximum of x and y */

/**
 * @brief Result of divmod function
 *
 * The Raspberry Pi 1 does not have the instruction to perform a division. This
 * struct is used to return the result of a division and the remainder.
 */
typedef struct divmod_result
{
    uint32_t div; /**< Result of the division */
    uint32_t mod; /**< Remainder of the division */
} divmod_t;       /**< Typedef for divmod_result */

/**
 * @brief Performs a division and returns the result and the remainder
 *
 * @param dividend The dividend
 * @param divisor The divisor
 * @return divmod_t The result of the division and the remainder
 */
divmod_t divmod(uint32_t dividend, uint32_t divisor);

/**
 * @brief Performs a division and returns the result
 *
 * @param dividend The dividend
 * @param divisor The divisor
 * @return uint32_t The result of the division.
 */
uint32_t div(uint32_t dividend, uint32_t divisor);

/**
 * @brief Fills the first @a n bytes of the memory area pointed to by @a s with
 * the constant byte @a c.
 * @return A pointer to the memory area s.
 */
void *memset(void *dest, int c, unsigned long bytes);

/**
 * @brief Copies @a n bytes from memory area @a src to memory area @a dest. The
 * memory areas must not overlap.
 * @return A pointer to dest.
 */
void *memcpy(void *dest, const void *src, unsigned long bytes);

/**
 * @brief int -> str(int)
 *
 * Converts an int (Only base 10 supported for now)
 * to a null-terminated string using the specified base.
 * @param value Value to be converted to a string.
 * @param base Numerical base used to represent the value as a string,
 * between 2 and 36, where 10 means decimal base, 16 hexadecimal, 8 octal,
 * and 2 binary.
 * @return A pointer to the resulting null-terminated string.
 */
char *itoa(int value, int base);

/**
 * @brief str -> int
 *
 * Converts a string to an int
 * @param num This is the string representation of an integral number.
 * @return The converted integral number as an int value.
 * 	If no valid conversion could be performed, it returns zero.
 */
int atoi(const char *num);

/**
 * @brief Zero out the section [dest, dest+bytes]
 *
 * @param dest
 * @param bytes
 */
void bzero(void *dest, unsigned long bytes);

#endif // STDLIB_H