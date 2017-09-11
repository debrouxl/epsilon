#ifndef LIBA_MATH_H
#define LIBA_MATH_H

#include "private/macros.h"
#include <float.h>

LIBA_BEGIN_DECLS

#define NAN __builtin_nanf("")
#define INFINITY __builtin_inff()
#define M_E 2.71828182845904523536028747135266250
#define M_PI 3.14159265358979323846264338327950288
#define M_PI_2 1.57079632679489661923132169163975144
#define M_PI_4 0.78539816339744830961566084581987572
#define M_SQRT2 1.41421356237309504880168872420969808

#define FP_INFINITE 0x01
#define FP_NAN 0x02
#define FP_NORMAL 0x04
#define FP_SUBNORMAL 0x08
#define FP_ZERO 0x10

/* The C99 standard requires isinf and isnan to be defined as macros that can
 * handle arbitrary precision float numbers. The names of the functions called
 * by those macros (depending on the argument size) are not standardized though.
 * We're chosing isinff/isnanf for single-precision functions, and isinfd/isnand
 * for double-precision functions. */

#define isinff(x) __builtin_isinff(x)
#define isinfd(x) __builtin_isinf(x)
#define isinf(x) (sizeof(x) == sizeof(float) ? isinff(x) : isinfd(x))
/*int isinff(float x);
int isinfd(double d);
#define isinf(x) (sizeof(x) == sizeof(float) ? isinff(x) : isinfd(x))*/
#define isnanf(x) __builtin_isnanf(x)
#define isnand(x) __builtin_isnan(x)
#define isnan(x) (sizeof(x) == sizeof(float) ? isnanf(x) : isnand(x))
/*int isnanf(float x);
int isnand(double x);
#define isnan(x) (sizeof(x) == sizeof(float) ? isnanf(x) : isnand(x))*/
#define fpclassify(x) __builtin_fpclassify(FP_NAN, FP_INFINITE, FP_NORMAL, FP_SUBNORMAL, FP_ZERO, x)
/*int __fpclassifyf(float x);
int __fpclassify(double x);
#define fpclassify(x) ((sizeof (x) == sizeof (float)) ? __fpclassifyf(x) :  __fpclassify(x))*/

#define acosf(x) __builtin_acosf(x)
#define acoshf(x) __builtin_acoshf(x)
#define asinf(x) __builtin_asinf(x)
#define asinhf(x) __builtin_asinhf(x)
#define tan(x) __builtin_tan(x)
#define tanh(x) __builtin_tanh(x)
#define atanf(x) __builtin_atanf(x)
#define atan2f(y,x) __builtin_atan2f(y,x)
#define atanhf(x) __builtin_atanhf(x)
#define ceilf(x) __builtin_ceilf(x)
#define copysignf(x,y) __builtin_copysignf(x,y)
#define cosf(x) __builtin_cosf(x)
#define coshf(x) __builtin_coshf(x)
#define expf(x) __builtin_expf(x)
#define expm1f(x) __builtin_expm1f(x)
#define fabsf(x) __builtin_fabsf(x)
#define floorf(x) __builtin_floorf(x)
#define fmodf(x,y) __builtin_fmodf(x,y)
#define lgammaf(x) __builtin_lgammaf(x)
#define lgammaf_r(x,signgamp) __builtin_lgammaf_r(x,signgamp)
#define log1pf(x) __builtin_log1pf(x)
#define log10f(x) __builtin_log10f(x)
#define logf(x) __builtin_logf(x)
#define nanf(s) __builtin_nanf(s)
#define nearbyintf(x) __builtin_nearbyintf(x)
#define powf(x,y) __builtin_powf(x,y)
#define roundf(x) __builtin_roundf(x)
#define scalbnf(x,n) __builtin_scalbnf(x,n)
#define sinf(x) __builtin_sinf(x)
#define sinhf(x) __builtin_sinhf(x)
#define sqrtf(x) __builtin_sqrtf(x)
#define tanf(x) __builtin_tanf(x)
#define tanhf(x) __builtin_tanhf(x)

#define acos(x) __builtin_acos(x)
#define acosh(x) __builtin_acosh(x)
#define asin(x) __builtin_asin(x)
#define asinh(x) __builtin_asinh(x)
#define atan(x) __builtin_atan(x)
#define atanh(x) __builtin_atanh(x)
#define ceil(x) __builtin_ceil(x)
#define copysign(x,y) __builtin_copysign(x,y)
#define cos(x) __builtin_cos(x)
#define cosh(x) __builtin_cosh(x)
#define exp(x) __builtin_exp(x)
#define expm1(x) __builtin_expm1(x)
#define fabs(x) __builtin_fabs(x)
#define floor(x) __builtin_floor(x)
#define lgamma(x) __builtin_lgamma(x)
#define lgamma_r(x,signgamp) __builtin_lgamma_r(x,signgamp)
#define log1p(x) __builtin_log1p(x)
#define log10(x) __builtin_log10(x)
#define log(x) __builtin_log(x)
#define pow(x,y) __builtin_pow(x,y)
#define round(x) __builtin_round(x)
#define scalbn(x,n) __builtin_scalbn(x,n)
#define sin(x) __builtin_sin(x)
#define sinh(x) __builtin_sinh(x)
#define sqrt(x) __builtin_sqrt(x)
#define tan(x) __builtin_tan(x)
#define tanh(x) __builtin_tanh(x)

LIBA_END_DECLS

#endif
