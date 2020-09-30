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

static int32_t test_log2();
static int32_t test_pow2();
static int32_t test_pow();

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

    // printf("%d  %lu %lu %5.20f\n", FRACTIONAL_BASE, a, flt_to_fix(-3.0f), fxd_to_dbl(d));
    // print_n(flt_to_fix(-3.0f));
    // float m = -0.99999999953433871269f;
    // printf("%5.20f\n",  m);

    // test_pow2();

    
    // test_log2();
    test_pow();
    
}

static int32_t test_pow(){
    
    int32_t a_fxd = INT32_MAX;

    double a = fxd_to_dbl(a_fxd);
    double res = 0;
    int32_t res_fxd = 0;

    for (double i = 0.5; i < 1; i = i + 0.01){
        // res_fxd = fxd_pow(a_fxd, dbl_to_fxd(i));
        res = pow(a_fxd, i);
        printf("pow(%5.10f ,%5.10f ) = %5.10f my =  %5.10f\n",a,i, res,  fxd_to_dbl(res_fxd));
        
    }
    return 0;
}


static int32_t test_log2(){
    int32_t fxd_p = 0;
    double tmp = 0;
    int32_t tmp_log = 0;

    for (uint32_t i = 0; i < 512; i++){
        fxd_p =  (i<<21) + HALF_Q31_PL;
        tmp = log2(fxd_to_dbl(fxd_p));

        printf("%d,// log2(%5.10f) = %5.10f  , %d %5.10f \n", dbl_to_fxd(tmp), fxd_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/

    }

    printf("\n+++++++++++++++++++++++check interp+++++++++++++++++++\n");
    fxd_p = HALF_Q31_PL;
    tmp = log2( fxd_to_dbl(fxd_p));
    tmp_log = fxd_log2(fxd_p);
    printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_log, fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(tmp_log));  /*, fxd_log2(dbl_to_fix(it))*/

    for(int i = 1; i  <= (1<<21); i <<= 1){
        fxd_p = HALF_Q31_PL + i;
        tmp = log2(fxd_to_dbl(fxd_p));
        tmp_log = fxd_log2(fxd_p);
        printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_log, fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(tmp_log));  /*, fxd_log2(dbl_to_fix(it))*/
    }

    // fxd_p =  (0<<21) + HALF_Q31_PL + 1;
    // tmp = log2(fxd_to_dbl(fxd_p));
    // printf("%d,// log2(%5.10f) = %5.10f  %5.10f\n", fxd_log2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    
    // fxd_p =  (1<<21) + HALF_Q31_PL + 1;
    // tmp = log2(fxd_to_dbl(fxd_p));
    // printf("%d,// log2(%5.10f) = %5.10f  %5.10f\n", fxd_log2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    
    // fxd_p =  (0<<21) + HALF_Q31_PL + 1 + 500;
    // tmp = log2(fxd_to_dbl(fxd_p));
    // printf("%d,// log2(%5.10f) = %5.10f  %5.10f\n", fxd_log2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    
    // fxd_p =  (0<<21) + HALF_Q31_PL + 1 + 15000;
    // tmp = log2(fxd_to_dbl(fxd_p));
    // printf("%d,// log2(%5.10f) = %5.10f  %5.10f\n", fxd_log2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    
    return 0;
}

static int32_t test_pow2(){
    int32_t fxd_p = 0;
    double tmp = 0;
    int32_t tmp_pow  = 0; 
    printf("\n+++++++++++++++++++++++CHECK POW+++++++++++++++++++\n");
    for (int32_t i = 512; i > 0; i--){

        fxd_p = (-i << 22);

        tmp = pow(2.0, fxd_to_dbl(fxd_p));

        printf("%d,// pow2(%5.10f) = %5.10f  , %d %5.10f\n",dbl_to_fxd(tmp), fxd_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_pow2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
        //fxd_to_dbl(fxd_pow2(fxd_p));
    }

    // for (int32_t i = 1; i < 513; i++){

    //     fxd_p = (-i << 22);

    //     tmp = pow(2.0, fxd_to_dbl(fxd_p));

    //     printf("%d,// pow2(%5.10f) = %5.10f  , %d %5.10f\n",dbl_to_fxd(tmp), fxd_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_pow2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    //     // fxd_to_dbl(fxd_pow2(fxd_p));
    // }
    printf("\n+++++++++++++++++++++++check interp+++++++++++++++++++\n");
    fxd_p = INT32_MIN ;
    tmp = pow(2.0, fxd_to_dbl(fxd_p));
    tmp_pow = fxd_pow2(fxd_p);
    printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_pow, fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(tmp_pow));  /*, fxd_log2(dbl_to_fix(it))*/
    for(int i = 1; i  <= (1<<22); i <<= 1){
        fxd_p = INT32_MIN + i;
        tmp = pow(2.0, fxd_to_dbl(fxd_p));
        tmp_pow = fxd_pow2(fxd_p);
        printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_pow, fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(tmp_pow));  /*, fxd_log2(dbl_to_fix(it))*/
    }

    // fxd_p =  (-2<<22);
    // tmp = pow(2.0, fxd_to_dbl(fxd_p));
    // printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", fxd_pow2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_pow2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/

    // fxd_p =  (-1<<22) - 500;
    // tmp = pow(2.0, fxd_to_dbl(fxd_p));
    // printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", fxd_pow2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_pow2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    
    // fxd_p =  (-1<<22)  - 15000;
    // tmp = pow(2.0, fxd_to_dbl(fxd_p));
    // printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", fxd_pow2(fxd_p), fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(fxd_pow2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    
    return 0;
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

// }