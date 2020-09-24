//flt_arithmetic.c

#include "fxd_arithmetic.h"

#define BITS_TYPE32     31
my_int32_t OveResflow;


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

my_int32_t   fxd_add(int32_t a, int32_t b){
    my_int32_t res;
    print_n(a);
        printf("%d\n", a);
    print_n(b);
            printf("%d\n", b);
    res = a + b;
     printf("SUMM\n");
    print_n(res);
    print_n(FRACTIONAL_MIN);
    printf("%d\n", FRACTIONAL_MIN);
    if (((a ^ b) & FRACTIONAL_MIN) == 0)
    {    
    printf("(a ^ b)\n");
    print_n((a ^ b));
    print_n(((a ^ b) & FRACTIONAL_MIN));
    printf("%d\n", FRACTIONAL_MIN);
    printf("(res ^ a)\n");
    print_n((res ^ a));
    print_n((res ^ a) & FRACTIONAL_MIN);
    printf("%d\n", FRACTIONAL_MIN);
    print_n(FRACTIONAL_MIN);
        if (((res ^ a) & FRACTIONAL_MIN))
        {

            res = (a < 0) ? FRACTIONAL_MIN : FRACTIONAL_MAX;
            print_n(FRACTIONAL_MIN);
            print_n(res);
            printf("%d\n", FRACTIONAL_MIN);
            OveResflow = 1;
        }
    }

    return res;

}

my_int32_t   fxd_sub(my_int32_t a, my_int32_t b){
    int32_t res;

    res = a - b;
    printf("SUB\n");
    print_n(res);
    print_n(FRACTIONAL_MIN);
    printf("%d\n", FRACTIONAL_MIN);

    if (((a ^ b) & FRACTIONAL_MIN) != 0) 
    {
        if ((res ^ a) & FRACTIONAL_MIN) 
        {
            res = (a < 0) ? FRACTIONAL_MIN : FRACTIONAL_MAX;
            OveResflow = 1;
        }
    }

    return res;
}

my_int32_t   fxd_mul(my_int32_t a, my_int32_t b){
    my_int32_t res = 0;
    return res;

}

my_int32_t   fxd_mac(my_int32_t a, my_int32_t b){
    my_int32_t res = 0;
    return res;
}

my_int32_t   fxd_msub(my_int32_t a, my_int32_t b){
        my_int32_t res = 0;
    return res;
}

my_int32_t   fxd_abs(my_int32_t a){
    my_int32_t res;

    if (a == FRACTIONAL_MIN) {
        res = FRACTIONAL_MAX;
    }
    else 
    {
       if (a < 0)
            res = -a;
       else
            res = a;
    }

    return res;
}

my_int32_t   fxd_neg(my_int32_t a){
    my_int32_t res;

    res = (a == FRACTIONAL_MIN) ? FRACTIONAL_MAX : -a;
    return res;
}