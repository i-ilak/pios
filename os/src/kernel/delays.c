#include "kernel/delays.h"

#include "peripherals/base.h"
#include "kernel/mmio.h"


enum
{
    SYSTMR_LO   = (MMIO_BASE + 0x00003004),
    SYSTMR_HI   = (MMIO_BASE + 0x00003008),
};

void wait_cycles(uint32_t n)
{
    if(n) while(n--) { asm volatile("nop"); }
}

#if defined(MODEL_3)
void wait_msec(uint32_t n)
{
    register unsigned long f, t, r;
    // get the current counter frequency
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    // read the current counter
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));
    // calculate required count increase
    unsigned long i=((f/1000)*n)/1000;
    // loop while counter increase is less than i
    do{asm volatile ("mrs %0, cntpct_el0" : "=r"(r));}while(r-t<i);
}
#endif

uint64_t get_system_timer()
{
    unsigned int h=-1, l;
    // we must read MMIO area as two separate 32 bit reads
    h=mmio_read(SYSTMR_HI);
    l=mmio_read(SYSTMR_LO);
    // we have to repeat it if high word changed during read
    if(h!=mmio_read(SYSTMR_HI)) {
        h=mmio_read(SYSTMR_HI);
        l=mmio_read(SYSTMR_LO);
    }
    // compose long int value
    return ((uint64_t) h << 32) | l;
}

void wait_msec_st(uint32_t n)
{
    unsigned long t=get_system_timer();
    // we must check if it's non-zero, because qemu does not emulate
    // system timer, and returning constant zero would mean infinite loop
    if(t) while(get_system_timer()-t < n);
}
