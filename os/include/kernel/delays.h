#ifndef DELAYS_H
#define DELAYS_H

#include <stdint.h>

void wait_cycles(uint32_t n);

#if defined(MODEL_3)
void wait_msec(uint32_t n);
#endif

void wait_msec_st(uint32_t n);

uint64_t get_system_timer();

#endif // DELAYS_H
