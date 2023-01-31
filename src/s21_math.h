#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#include <float.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define S21_EPS 1e-10
#define S21_E 2.7182818284590452354
#define S21_PI 3.14159265358979323846
#define S21_NAN __builtin_nan("")
#define S21_POS_INF __builtin_inf()
#define S21_NEG_INF -__builtin_inf()
#define is_inf __builtin_isinf
#define is_nan __builtin_isnan

int s21_abs(int x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_log(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_sqrt(double x);
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_factorial(int x);

#endif  // SRC_S21_MATH_H_
