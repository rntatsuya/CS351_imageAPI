/*
 * Tatsuya Yokota
 * math_aprox.c
 * math approximation functions, found from various sources
 */

#include "math_aprox.h"

// Source: https://dsp.stackexchange.com/questions/17269/what-approximation-techniques-exist-for-computing-the-square-root
float __sqrt(register float x) {
  if (x > 5.877471754e-39) {
    register float accumulator, xPower;
    register long intPart;
    register union {float f; long i;} xBits;

    xBits.f = x;

    intPart = ((xBits.i)>>23);                  /* get biased exponent */
    intPart -= 127;                             /* unbias it */

    x = (float)(xBits.i & 0x007FFFFF);          /* mask off exponent leaving 0x800000*(mantissa - 1) */
    x *= 1.192092895507812e-07;                 /* divide by 0x800000 */

    accumulator =  1.0 + 0.49959804148061*x;
    xPower = x*x;
    accumulator += -0.12047308243453*xPower;
    xPower *= x;
    accumulator += 0.04585425015501*xPower;
    xPower *= x;
    accumulator += -0.01076564682800*xPower;

    if (intPart & 0x00000001) {
      accumulator *= ROOT2;                   /* an odd input exponent means an extra sqrt(2) in the output */
    }

    xBits.i = intPart >> 1;                     /* divide exponent by 2, lose LSB */
    xBits.i += 127;                             /* rebias exponent */
    xBits.i <<= 23;                             /* move biased exponent into exponent bits */

    return accumulator * xBits.f;
  }
  else {
    return 0.0;
  }
}