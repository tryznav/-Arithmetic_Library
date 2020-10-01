#include <fxd_arithmetic.h>
#include <math.h>
#include <inttypes.h>
#include "flt_arithmetic.h"

// #define M_E         2.71828182845904523536028747135266250

#define BASE_BITS   20
#define CONV1       (FRACTION_BITS - BASE_BITS)
#define CONV        (BASE_BITS + BASE_BITS - FRACTION_BITS)
#define ONE         ((1ll<<BASE_BITS))
#define coef        ((1ll<<BASE_BITS))
#define Xn          ((48ll<<BASE_BITS)/17)
#define Xm          ((32ll<<BASE_BITS)/17)

double fxd33_31_to_dbl(int64_t val){
    return ((double)val / (double)(1u << BASE_BITS));
}

double fxd_cc_to_dbl(int64_t val){
    return ((double)val / (double)(1u << 31));
}





int64_t div_mul(int64_t a, int64_t b){
    return ((a * b) >> BASE_BITS);
}

fxd_q31_t  fxd_div(fxd_q31_t N, fxd_q31_t D){
    assert(D != 0);
    int64_t  Dsh = fxd_abs(D) >> CONV1;
    int64_t  Nsh = fxd_abs(N) >> CONV1;
    int64_t x = Xn - div_mul(Xm, Dsh);

    for(int i = 0; i < 3; i++){
        x = x + div_mul(x, (ONE - div_mul(Dsh, x)));
    }
    x = (Nsh * x) >> CONV;
    x = saturation(x);
    if((N ^ D) & FRACTIONAL_MIN){
        x = fxd_neg((fxd_q31_t)x);
    }
    return  (fxd_q31_t)x;
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

static int32_t test_div();
static int32_t test_log2();
static int32_t test_pow2();
static int32_t test_pow();
static int32_t test_log2_q4_27();
static int32_t test_pow2_q4_27();

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
    test_pow2_q4_27();
    // test_pow2_q4_27();

    // test_log2();
    // test_pow();
    
}


static int32_t test_div(){
    int32_t res_q31 = 0;
    for(double i = -1.0; i < 1.0; i = i + 0.1){
        if(i == 0){
            break;
        }
        res_q31 = fxd_div(-HALF_Q31_PL, dbl_to_fxd(i));
        flt_div(0.5f, (float)i);
        // break;
        printf("0.5/%f  %5.10f  %5.10f myres %5.10f\n", i, -0.5/i, flt_div(-0.5f, (float)i), fxd_to_dbl(res_q31) );
    }
    return 0;
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


double fxd4_27_to_dbl(int32_t val){
    return ((double)val / (double)(1u << 26));
}

fxd_q31_t   dbl_to_fxd4_27(double input)
{
    return (fxd_q31_t)(input * (1u << 26));
}

static int32_t test_log2_q4_27(){
    int32_t fxd_p = 0;
    double tmp = 0;
    int32_t tmp_log = 0;
    
    for (int32_t i = 0; i <= 511; i++){
        fxd_p = (i<<22) + 1;
        tmp_log = fxd_log2_q27(fxd_p);
        tmp = log2(fxd_to_dbl(fxd_p));
        printf("%d,// log2(%5.10f) = %5.10f my  %5.10f\n",  dbl_to_fxd4_27(tmp), fxd_to_dbl(fxd_p),  log2(fxd_to_dbl(fxd_p)),   fxd4_27_to_dbl(tmp_log));
       // printf("%d,// log2(%5.10f) = %5.10f  , %d %5.10f \n", dbl_to_fxd(tmp), fxd_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    }
    printf("\n+++++++++++++++++++++++MAX+++++++++++++++++++\n");
    fxd_p = INT32_MAX;
    tmp_log = fxd_log2_q27(fxd_p);
    tmp = log2(fxd_to_dbl(fxd_p));
    printf("%d,// log2(%5.10f) = %5.10f my  %5.10f\n",  dbl_to_fxd4_27(tmp), fxd_to_dbl(fxd_p),  log2(fxd_to_dbl(fxd_p)),   fxd4_27_to_dbl(tmp_log));
    printf("\n+++++++++++++++++++++++check interp+++++++++++++++++++\n");
    fxd_p = (1<<22) - 1;
    tmp_log = fxd_log2_q27(fxd_p);
    tmp = log2(fxd_to_dbl(fxd_p));
    printf("%d,// log2(%5.10f) = %5.10f my  %5.10f\n",  dbl_to_fxd4_27(tmp), fxd_to_dbl(fxd_p),  log2(fxd_to_dbl(fxd_p)),   fxd4_27_to_dbl(tmp_log));
    for(int i = 1; i  <= (1<<22); i <<= 1){
        fxd_p = (1<<22) + i - 1;
        tmp_log = fxd_log2_q27(fxd_p);
        tmp = log2(fxd_to_dbl(fxd_p));
        printf("%d,// log2(%5.10f) = %5.10f my  %5.10f\n",  dbl_to_fxd4_27(tmp), fxd_to_dbl(fxd_p),  log2(fxd_to_dbl(fxd_p)),   fxd4_27_to_dbl(tmp_log));
    }
    return 0;
}

static int32_t test_pow2_q4_27(){
 int32_t fxd_p = 0;
    double tmp = 0;
    int32_t tmp_pow  = 0; 
    printf("\n+++++++++++++++++++++++CHECK POW+++++++++++++++++++\n");
    for (int32_t i = 512; i > 0; i--){

        fxd_p = (-i << 22);

        tmp = pow(2.0, fxd4_27_to_dbl(fxd_p));

        printf("%d,// pow2(%5.10f) = %5.10f  , %d %5.10f\n", dbl_to_fxd(tmp), fxd4_27_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_pow2_q27(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
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
        // tmp = pow(2.0, fxd_to_dbl(fxd_p));
        tmp = log2(fxd_to_dbl(1 << 22));
        tmp_pow = fxd_pow2(fxd_p);
        printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_pow, fxd_to_dbl(1 << 22), tmp , fxd_to_dbl(tmp_pow));  /*, fxd_log2(dbl_to_fix(it))*/
    }
    return 0;
}

static int32_t test_log2(){
    int32_t fxd_p = 0;
    double tmp = 0;
    int32_t tmp_log = 0;
    
    for (uint32_t i = 1; i < 512; i++){
        fxd_p = (i << 22);
        tmp = log2(fxd_to_dbl(fxd_p));
        printf("%d,// log2(%5.10f) = %5.10f", dbl_to_fxd(tmp),fxd_to_dbl(fxd_p), log2(fxd_to_dbl(fxd_p)));
       // printf("%d,// log2(%5.10f) = %5.10f  , %d %5.10f \n", dbl_to_fxd(tmp), fxd_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/
    }

    // for (uint32_t i = 0; i < 512; i++){
    //     fxd_p =  (i<<21) + HALF_Q31_PL;
    //     tmp = log2(fxd_to_dbl(fxd_p));

    //     printf("%d,// log2(%5.10f) = %5.10f  , %d %5.10f \n", dbl_to_fxd(tmp), fxd_to_dbl(fxd_p), tmp , i, fxd_to_dbl(fxd_log2(fxd_p)));  /*, fxd_log2(dbl_to_fix(it))*/

    // }

    // printf("\n+++++++++++++++++++++++check interp+++++++++++++++++++\n");
    // fxd_p = HALF_Q31_PL;
    // tmp = log2( fxd_to_dbl(fxd_p));
    // tmp_log = fxd_log2(fxd_p);
    // printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_log, fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(tmp_log));  /*, fxd_log2(dbl_to_fix(it))*/

    // for(int i = 1; i  <= (1<<21); i <<= 1){
    //     fxd_p = HALF_Q31_PL + i;
    //     tmp = log2(fxd_to_dbl(fxd_p));
    //     tmp_log = fxd_log2(fxd_p);
    //     printf("%d,// pow2(%5.10f) = %5.10f  %5.10f\n", tmp_log, fxd_to_dbl(fxd_p), tmp , fxd_to_dbl(tmp_log));  /*, fxd_log2(dbl_to_fix(it))*/
    // }

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
