#include <stdint.h>

#include "common/stdlib.h"
#include "common/string.h"

#include "kernel/memory.h"
#include "kernel/kerio.h"
#include "kernel/atag.h"
#include "kernel/gpu.h"
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
void kernel_main(uint64_t dtb_ptr32, uint64_t x0, uint64_t x1, uint64_t x3)
#endif
{

    mem_init((atag_t *)atags);
    gpu_init();

    puts("Welcome to piOS!\n\n");

    uint32_t mem_size = get_mem_size((atag_t *)atags);
    printf("RAM size: %d\n", mem_size/1024/1024);

    puts("I han d Lea gern!");
    
    while(1) {
        putc(getc());
    }
}