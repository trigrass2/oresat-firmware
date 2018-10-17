#ifndef _SIN_LUT_H_
#define _SIN_LUT_H_

#include <unistd.h>

#define LUT_SIZE 512

typedef uint16_t dutycycle_t;

static const dutycycle_t sin_lut[LUT_SIZE];

#endif
