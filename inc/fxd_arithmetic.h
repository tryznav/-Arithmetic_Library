#ifndef __FXD_ARITHMETIC_H__
#define __FXD_ARITHMETIC_H__
#include <assert.h>
#include <stdint.h>
#define FRACTION_BITS           31


#define M_E         2.71828182845904523536028747135266250

#include <stdio.h>
#include <string.h>

typedef int32_t my_int32_t;
typedef int64_t my_int64_t;

#define FRACTIONAL_BASE     (1u<<FRACTION_BITS)

#define FRACTIONAL_MAX      ((1ul<<FRACTION_BITS)-1)
#define FRACTIONAL_MIN      (-1<<FRACTION_BITS)

my_int32_t  fxd_add(my_int32_t a, my_int32_t b);

my_int32_t  fxd_sub(my_int32_t a, my_int32_t b);

my_int32_t  fxd_mul(my_int32_t a, my_int32_t b);

my_int64_t  fxd_mac(my_int64_t acum, my_int32_t b,  my_int32_t c);

my_int64_t   fxd_msub(my_int64_t a, my_int32_t b,  my_int32_t c);

my_int32_t  fxd_abs(my_int32_t a);

my_int32_t  fxd_neg(my_int32_t a);

my_int32_t   fxd_lshift(my_int32_t a , uint32_t n);

my_int32_t   fxd_rshift(my_int32_t a , uint32_t n);


float fxd_to_flt(my_int32_t val);

double fxd_to_flt64(my_int64_t val);

my_int32_t float_to_fixed(double input);

const my_int32_t POW2_1_31[512];


#endif /* colors.h */