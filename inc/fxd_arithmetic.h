#ifndef __FXD_ARITHMETIC_H__
#define __FXD_ARITHMETIC_H__

#include <stdint.h>
#define FRACTION_BITS           31

#include <stdio.h>
#include <string.h>

typedef int32_t my_int32_t;
typedef int64_t my_int64_t;

#define FRACTIONAL_BASE     (1<<FRACTION_BITS)

#define FRACTIONAL_MAX      ((1ul<<FRACTION_BITS)-1)
#define FRACTIONAL_MIN      (-1<<FRACTION_BITS)

my_int32_t   fxd_add(my_int32_t a, my_int32_t b);

my_int32_t   fxd_sub(my_int32_t a, my_int32_t b);

my_int32_t   fxd_mul(my_int32_t a, my_int32_t b);

my_int32_t   fxd_mac(my_int32_t a, my_int32_t b);

my_int32_t   fxd_msub(my_int32_t a, my_int32_t b);

my_int32_t   fxd_abs(my_int32_t a);

my_int32_t   fxd_neg(my_int32_t a);

#endif /* colors.h */