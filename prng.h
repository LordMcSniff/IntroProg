#ifndef PRNG_H
#define PRNG_H

#include <stdint.h>

uint64_t seed = 42;

uint64_t randu64() {
  seed ^= (seed << 13);
  seed ^= (seed >> 7);
  seed ^= (seed << 17);
  return seed;
}

#endif