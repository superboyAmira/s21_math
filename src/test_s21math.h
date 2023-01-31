#ifndef SRC_TEST_S21MATH_H_
#define SRC_TEST_S21MATH_H_

#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "s21_math.h"
#define TEST_EPS 1e-6
#define TEST_PI 3.1415926535

Suite *s21_math_tests_create();

#endif  // SRC_TEST_S21MATH_H_
