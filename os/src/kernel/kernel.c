#include <stdint.h>

#include "common/stdlib.h"
#include "common/string.h"

#include "kernel/memory.h"
#include "kernel/uart.h"
#include "kernel/atag.h"

/*!
 * @brief Entry point for the kernel
 * @param r0 0
 * @param r1 Machine ID
 * @param atags Start of ATAGS
 */
#if defined(AARCH_32)
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
#else
void kernel_main(uint64_t dtb_ptr32, uint64_t x0, uint64_t x1, uint64_t x3)
#endif
{

    mem_init((atag_t *)atags);
    uart_init();

    uart_puts("Welcome to piOS!\n");

    uint32_t mem_size = get_mem_size((atag_t *)atags);
    uart_puts(strcat("RAM size: ", itoa(mem_size/1024/1024)));
    
    while(1) {
        uart_putc(uart_getc());
    }
}