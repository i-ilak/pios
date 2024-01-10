#include <stdint.h>

#include "common/stdlib.h"
#include "common/string.h"
#include "kernel/kerio.h"
#include "kernel/uart.h"
#include "kernel/delays.h"
#include "kernel/power.h"

#if defined(AARCH_32)

#include "kernel/atag.h"
#include "kernel/gpu.h"
#include "kernel/memory.h"
#include "kernel/random.h"

/*!
 * @brief Entry point for the kernel
 * @param r0 0
 * @param r1 Machine ID
 * @param atags Start of ATAGS
 */
void kernel_main(uint32_t r0, uint32_t arm_m_type, uint32_t atags)
{
    (void)r0;
    (void)arm_m_type;

    // assume if atags not specified then they are at 0x100
    if(atags == 0x0)
        atags = 0x100;

    mem_init((atag_t *)atags);
#if UART_MODE
    uart_init();
    printf("ATTENTION YOU ARE IN UART MODE\n\n");
#else
    gpu_init();
#endif

    puts("Welcome to piOS!\n----------------\n\n");
    printf("Wait for 5 secs if it works!\n");
    usleep(5000000);

    printf("%d\n", rand(100, 500));
    
    uint32_t mem_size = get_mem_size((atag_t *)atags);
    printf("RAM size:     %d MB\n\n", mem_size / 1024 / 1024);

    print_atags(atags);

    char c;

    while(1) {
            uart_puts(" 1 - power off\n 2 - reset\nChoose one: ");
            c=getc();
            putc(c);
            puts("\n\n");
            if(c=='1') power_off();
            if(c=='2') reset();
        }
}
#else

#include "kernel/random.h"

void kernel_main(uint64_t dtb_ptr32, uint64_t x0, uint64_t x1, uint64_t x3)
{
    printf("ATTENTION YOU ARE IN UART MODE\n\n");
    uart_init();
    printf("Wait for 5 secs if it works!\n");
    wait_msec(5000000);
    printf("Architecture: AARCH_%d\n\n", 64);
    rand_init();
    printf("%d\n", rand(100, 500));
    while(1)
    {
        putc(getc());
    }
}
#endif
