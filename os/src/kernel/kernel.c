#include <stdint.h>

#include "kernel/uart.h"

/*!
 * @brief Entry point for the kernel
 * @param r0 0
 * @param r1 Machine ID
 * @param atags Start of ATAGS
 */
#if defined(AARCH_32)
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
#else
void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
#endif
{
    uart_init();
    
    uart_puts("Hello World!\n");
    
    while(1) {
        uart_putc(uart_getc());
    }
}