#include <stdint.h>

#include "common/stdlib.h"
#include "common/string.h"

#include "kernel/atag.h"
#include "kernel/gpu.h"
#include "kernel/kerio.h"
#include "kernel/memory.h"
#include "kernel/uart.h"

/*!
 * @brief Entry point for the kernel
 * @param r0 0
 * @param r1 Machine ID
 * @param atags Start of ATAGS
 */
#if defined(AARCH_32)
void kernel_main(uint32_t r0, uint32_t arm_m_type, uint32_t atags)
#else
void kernel_main(uint64_t dtb_ptr32, uint64_t x0, uint64_t x1, uint64_t x3)
#endif
{
    (void)r0;
    (void)arm_m_type;

    // assume if atags not specified then they are at 0x100
    if(atags == 0x0)
        atags = 0x100;

    mem_init((atag_t *)atags);
    // uart_init();
    gpu_init();

    puts("Welcome to piOS!\n----------------\n\n");

    uint32_t mem_size = get_mem_size((atag_t *)atags);
    printf("RAM size:     %d MB\n\n", mem_size / 1024 / 1024);

#ifdef AARCH_32
    printf("Architecture: AARCH_%d\n\n", 32);
#else
    printf("Architecture: AARCH_%d\n\n", 64);
#endif

    print_atags(atags);

    while(1)
    {
        putc(getc());
    }
}