#include <fxd_arithmetic.h> 

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
    int32_t a = 0b11000000000000000000000000000000;
    int32_t b = 0b10000000000000000000000000100000;

    //int32_t res = fxd_add(a, b);
    int32_t res = fxd_mul(a, b);

}
