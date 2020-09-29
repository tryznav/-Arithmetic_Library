#ifndef __FXD_ARITHMETIC_H__
#define __FXD_ARITHMETIC_H__

#include "flt_arithmetic.h"

#include <assert.h>
#include <stdint.h>
#define FRACTION_BITS           31


#define M_E         2.71828182845904523536028747135266250

#include <stdio.h>
#include <string.h>

typedef int32_t fxd_q31_t;
typedef int64_t fxd_q63_t;

#define FRACTIONAL_BASE     (1u<<FRACTION_BITS)

#define FRACTIONAL_MAX      ((1ul<<FRACTION_BITS)-1)
#define FRACTIONAL_MIN      (-1<<FRACTION_BITS)

fxd_q31_t  fxd_add(fxd_q31_t a, fxd_q31_t b);

fxd_q31_t  fxd_sub(fxd_q31_t a, fxd_q31_t b);

fxd_q31_t  fxd_mul(fxd_q31_t a, fxd_q31_t b);

fxd_q63_t  fxd_mac(fxd_q63_t acum, fxd_q31_t b,  fxd_q31_t c);

fxd_q63_t   fxd_msub(fxd_q63_t a, fxd_q31_t b,  fxd_q31_t c);

fxd_q31_t  fxd_abs(fxd_q31_t a);

fxd_q31_t  fxd_neg(fxd_q31_t a);

fxd_q31_t   fxd_lshift(fxd_q31_t a , uint32_t n);

fxd_q31_t   fxd_rshift(fxd_q31_t a , uint32_t n);

float fxd_to_flt(fxd_q31_t val);

double fxd_to_flt64(fxd_q63_t val);

fxd_q31_t float_to_fixed(double input);

const fxd_q31_t POW2_1_31[512];


#endif /* colors.h */