#include <fxd_arithmetic.h>
#include <math.h>
#include <inttypes.h>
#include "flt_arithmetic.h"

// #define M_E         2.71828182845904523536028747135266250

int64_t   fxd_NewRaphAlg_doub(){
    double  P = 32;
    int32_t  N = -800;
    int32_t  D = 15;
    
    int64_t  Dsh = D * INT16_MAX / 13;
    int64_t  Nsh =  N * INT16_MAX / 13;
    int64_t Xn =  48ll * INT16_MAX / 17;
    int64_t Xm =  32ll * INT16_MAX / 17;
    int64_t x = Xn - Xm * Dsh /INT16_MAX;

    // printf("Dsh = %f\n", pow(2, M_E + 1));
    // printf("%f\n", log2((P + 1.0)/log2(17)));
    for(int i = 0; i < 3; i++){
        x = x + x*(INT16_MAX - Dsh * x / INT16_MAX)/INT16_MAX;
            // printf("%lli\n",x );
           printf("%" PRId64 "\n", x);
    }
    printf("%lli\n",(x * Nsh)/INT16_MAX/INT16_MAX);
    return x;
}



int main(){
                                    //
    // int32_t a = 0b00000000000000001000010000000000;
    // int32_t b = 0b00000000000000001000100000000000;

    // int32_t a = 0b00000000000000001000010000000000;
    // int32_t b = 0b00000000000000001000100000000000;

    // int32_t a = 0b01111111111111110000000000000000;
    // int32_t b = 0b01111111111111110000000000000000;

    // int32_t a = 0b11111111111111110000000000000001;
    // int32_t b = 0b11111111111111110000000000000000;

    // int32_t a = 0b01111111111111111111111111111111;
    // int32_t b = 0b01111111111111111111111111111111;

    // int32_t a = 0b11111111111111111111111111111111;
    // int32_t b = 0b11111111111111111111111111111111;

    // int32_t a = 0b01111111111111111111111111111111;
    // int32_t b = 0b11111111111111111111111111111111;
    int32_t a = 0b01000000000000000000000000000000;
    int32_t b = 0b01000000000000000000000000000010;

    //int32_t res = fxd_add(a, b);
    // int32_t res = fxd_mul(a, b);
    // printf("%d\n ", res);
    // printf("%9.31f\n ", fxd_to_flt(res));
    // flt_NewRaphAlg();
    // fxd_NewRaphAlg_doub();
    double intr = 1.0  / 512;
    double it = -1;//intr;
    double tmp = 0;
    flt_div(1.0f, 2.0f);
    for (int i = 0; i < 512; i++){
        tmp = pow(2, it);
        printf("%d, // %f, %f\n", float_to_fixed(tmp), it, tmp);

        // tmp = log2(it);
        // printf("%d, // %f, %f\n",float_to_fixed(tmp), it, tmp);
        it = it + intr;
    }
    
}
