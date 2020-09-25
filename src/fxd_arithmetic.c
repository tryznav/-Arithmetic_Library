//flt_arithmetic.c

#include "fxd_arithmetic.h"

#include <math.h>
#define BITS_TYPE32     31

void binaryPrint(uint32_t num){
    uint32_t b = (1ul<<BITS_TYPE32);
                // printf("\n");
    for(int i = 0; i <= BITS_TYPE32; i++){
        if ((num & b) == b){
            printf("1");
        }else{
            printf("0");
        }
        b >>= 1;
    }
                printf("\n");
}

void print_n(my_int32_t num){
    uint32_t tmp;
    memcpy(&tmp, &num, 4);
    binaryPrint(tmp);
}

double fixed16_to_double(int32_t input)
{
    return ((double)input / (double)(1 << 31));
}

my_int32_t   fxd_add(int32_t a, int32_t b){
    my_int32_t res;

    res = a + b;

    if (!((a ^ b) & FRACTIONAL_MIN))
    {    

        if ((res ^ a) & FRACTIONAL_MIN)
        {
            res = (a < 0) ? FRACTIONAL_MIN + 1: FRACTIONAL_MAX;
        }
    }

    return res;

}

my_int32_t   fxd_add63(int64_t a, int64_t b){
    my_int32_t res;

    res = a + b;

    if (!((a ^ b) & (-1<<63)))
    {    

        if ((res ^ a) & (-1<<63))
        {
            res = (a < 0) ? (-1<<63) + 1: ((1ul<<63)-1);
        }
    }
    return res;

}





float fxt_to_flt(my_int32_t val){
    return ((float)val / (float)(1u << FRACTION_BITS));
}

double fxt_to_flt64(my_int64_t val){
    return ((double)val / (double)(1u << FRACTION_BITS));
}

my_int32_t   fxd_sub(my_int32_t a, my_int32_t b){
    int32_t res = 0;

    res = a - b;
    
    if (((a ^ b) & FRACTIONAL_MIN))
    {
        if ((res ^ a) & FRACTIONAL_MIN) 
        {
            res = (a < 0) ? FRACTIONAL_MIN : FRACTIONAL_MAX;
        }
    }

    return res;
}

my_int32_t   fxd_mul(my_int32_t a, my_int32_t b){
    my_int32_t res = 0;
    my_int64_t acum = a;

    acum *= b;
    acum += (1u << (FRACTION_BITS - 1));
    acum >>= FRACTION_BITS;
    res = (my_int32_t)acum;
    return res;

}

my_int64_t fxd_mac(my_int64_t a, my_int32_t b,  my_int32_t c){
    my_int64_t acum = a;
    acum *= b;
    acum <<= 1;
    acum = fxd_add63(acum, a); 
    return acum;
}

my_int64_t fxd_mac(my_int32_t a, my_int32_t b,  my_int32_t c){
    my_int64_t acum = a;
    acum *= b;
    acum += ((my_int64_t)c << FRACTION_BITS);

    return acum;
}

my_int32_t   fxd_msub(my_int32_t a, my_int32_t b){
    my_int32_t res = 0;
    return res;
}

my_int32_t   fxd_abs(my_int32_t a){
    if (a == FRACTIONAL_MIN) {
        return FRACTIONAL_MAX;
    }
    else {
        return (a < 0) ? -a: a;
    }

}

my_int32_t   fxd_neg(my_int32_t a){

    return (a == FRACTIONAL_MIN) ? FRACTIONAL_MAX : -a;
}