#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

void rand_init();
uint32_t rand(const uint32_t min, const uint32_t max);

#endif
