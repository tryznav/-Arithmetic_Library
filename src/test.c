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

    // int64_t m = 
}

int sat(uint8_t a, uint8_t b){
    int8_t re = INT8_MAX - b;
    printf("re = %d\n", re);
    if(a < re){
        printf("sat YES\n");
    }else
    {
        printf("sat NO = %d\n",a);
    }
    return 0;
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

     int32_t a = 0b01111111111111111111111111111111;
    // int32_t b = 0b11111111111111111111111111111111;
    int32_t d =  0b10000000000000000000000000000000;

    // uint64_t m = INT32_MAX ;
    // m *= INT32_MAX ;
    // printf("%lli  %x  %dn", m, (unsigned int)m, INT32_MAX) ;

    printf("%d  %lu %lu %5.20f\n", FRACTIONAL_BASE, a, flt_to_fix(-3.0f), fxd_to_dbl(d));
    print_n(flt_to_fix(-3.0f));
    float m = -0.99999999953433871269f;
    printf("%5.20f\n",  m);

    //int32_t res = fxd_add(a, b);
    // int32_t res = fxd_mul(a, b);
    // printf("%d\n ", res);
    // printf("%9.31f\n ", fxd_to_flt(res));
    // flt_NewRaphAlg();
    // fxd_NewRaphAlg_doub();
    double intr = 1.0  / 512;
    double it = 1;//intr;
    double tmp = 0;
    // int8_t n = INT8_MAX;
    // int8_t k = -126;
    // // k *= -1;
    // printf("%d\n", k);  
    // n -= k; 
    // printf("%d\n", n );   
    // // flt_div(1.0f, 2.0f);
    for (int i = 0; i < 512; i++){
        tmp = log2(it);
        printf("%d, // %f, %f  %d ", dbl_to_fix(tmp), it, tmp , fxd_log2(dbl_to_fix(it)));
        // printf("%d %8.10f\n", POW2_FXD[i], fxd_to_dbl(POW2_FXD[i]));
        it = it - intr;
        //it = it + intr;
    }
    
}



////// chek pow2
// double intr = 1.0  / 512;
// double it = 0 ;//intr;
// double tmp = 0;
// // int8_t n = INT8_MAX;
// // int8_t k = -126;
// // // k *= -1;
// // printf("%d\n", k);  
// // n -= k; 
// // printf("%d\n", n );   
// // // flt_div(1.0f, 2.0f);
// for (int i = 0; i < 512; i++){
//     tmp = pow(2, it);
//     printf("%d, // %f, %f  %d ", dbl_to_fix(tmp), it, tmp , fxd_pow2(dbl_to_fix(it)));
//     printf("%d %8.10f\n", POW2_FXD[i], fxd_to_dbl(POW2_FXD[i]));
//     it = it - intr;
//     //it = it + intr;
// }