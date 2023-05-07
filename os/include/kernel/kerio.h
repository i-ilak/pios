#ifndef STDIO_H
#define STDIO_H

/**
 * @file kerio.h
 * @brief This file contains the definitions for the standard input/output.
 *
 * This file contains the definitions for the standard input/output. It is
 * based on the C standard library.
 */

/**
 * @brief Reads a character from the standard input.
 *
 * Note that what exactly standerd input is depends on the implementation.
 */
char getc();

/**
 * @brief Writes a character to the standard output.
 *
 * Note that what exactly standerd output is depends on the implementation. In
 * particular, during developemnt it has proved usefull to redirect the output
 * to UART0.
 *
 * @param c The character to write.
 */
void putc(char c);

/**
 * @brief Writes a string to the standard output.
 *
 * This function calls internally @a putc to write the string, so please
 * consider the documentation of that function.
 *
 * @param s The string to write.
 */
void puts(const char *s);

/**
 * @brief Reads a string from the standard input.
 *
 * This function reads a string from the standard input. The string is stored
 * in the buffer @a buf. The buffer is guaranteed to be null-terminated. The
 * maximum number of characters read is @a buflen - 1. The newline character
 * is not stored in the buffer.
 *
 * @param buf The buffer to store the string in.
 * @param buflen The maximum number of characters to read.
 */
void gets(char *buf, int buflen);

/**
 * @brief Writes a formatted string to the standard output.
 *
 * This function writes a formatted string to the standard output. The
 * formatting is done in the same way as in the C standard library.
 *
 * @param fmt The format string.
 * @param ... The arguments to the format string.
 */
void printf(const char *fmt, ...);

#endif