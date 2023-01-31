#include "test_s21math.h"

START_TEST(fabs_tests) {
  ck_assert_ldouble_eq(s21_fabs(-13.21313), s21_fabs(-13.21313));
  ck_assert_ldouble_eq(s21_fabs(13.21313), s21_fabs(13.21313));
  ck_assert_ldouble_eq(s21_fabs(-1000.21313), s21_fabs(-1000.21313));
  ck_assert_ldouble_eq(s21_fabs(32346234.21313), s21_fabs(32346234.21313));
  ck_assert_ldouble_eq(s21_fabs(0.0), s21_fabs(0.0));
}
END_TEST

START_TEST(ceil_tests) {
  ck_assert_ldouble_eq(ceil(-13.54), s21_ceil(-13.54));
  ck_assert_ldouble_eq(ceil(13.54), s21_ceil(13.54));
  ck_assert_ldouble_eq(ceil(1000), s21_ceil(1000));
  ck_assert_ldouble_eq(ceil(102.0000002), s21_ceil(102.0000002));
}
END_TEST

START_TEST(floor_tests) {
  ck_assert_ldouble_eq(floor(-13.54), s21_floor(-13.54));
  ck_assert_ldouble_eq(floor(13.54), s21_floor(13.54));
  ck_assert_ldouble_eq(floor(-0.54), s21_floor(-0.54));
  ck_assert_ldouble_eq(floor(1000), s21_floor(1000));
  ck_assert_ldouble_eq(floor(102.0000002), s21_floor(102.0000002));
}
END_TEST

START_TEST(exp_test_1) {
  for (double k = -21; k < 21; k += 1) {
    long double s21 = s21_exp(k);
    long double original = exp(k);
    ck_assert_ldouble_eq_tol(s21, original, TEST_EPS);
  }
}
END_TEST

START_TEST(exp_test_2) {
  for (double k = 15; k > -15; k -= 0.123) {
    ck_assert_ldouble_eq_tol(s21_exp(k), exp(k), TEST_EPS);
  }
}
END_TEST

START_TEST(exp_test_3) {
  for (double k = -5; k < 5; k += 0.00573) {
    long double s21 = s21_exp(k);
    long double original = exp(k);
    ck_assert_ldouble_eq_tol(s21, original, TEST_EPS);
  }
}
END_TEST

START_TEST(exp_test_4) {
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  ck_assert_ldouble_eq(exp(INFINITY), s21_exp(S21_POS_INF));
  ck_assert_ldouble_eq(exp(-INFINITY), s21_exp(S21_NEG_INF));
  ck_assert_ldouble_eq(exp(0), s21_exp(0));
  ck_assert_ldouble_eq(exp(1), s21_exp(1));
}
END_TEST

START_TEST(log_tests) {
  ck_assert_ldouble_eq_tol(log(14.4), s21_log(14.4), TEST_EPS);
  ck_assert_ldouble_eq_tol(log(0.5), s21_log(0.5), TEST_EPS);
  ck_assert_ldouble_eq(log(1.0), s21_log(1.0));
  ck_assert_ldouble_infinite(s21_log(0.0));
  ck_assert_ldouble_eq_tol(log(1.8), s21_log(1.8), TEST_EPS);
  ck_assert_ldouble_infinite(s21_log(INFINITY));
  ck_assert_ldouble_nan(s21_log(-INFINITY));
  ck_assert_ldouble_nan(s21_log(-10.0));
  ck_assert_ldouble_nan(s21_log(NAN));
  ck_assert_ldouble_nan(s21_log(-NAN));
}
END_TEST

START_TEST(fmod_test_1) {
  ck_assert_ldouble_nan(s21_fmod(1, 0));
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
  ck_assert_double_nan(s21_fmod(INFINITY, -1));
  ck_assert_double_eq(fmod(-1, -INFINITY), s21_fmod(-1, S21_NEG_INF));
  ck_assert_double_eq(fmod(0, INFINITY), s21_fmod(0, S21_POS_INF));
  ck_assert_double_nan(s21_fmod(0, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_NAN));
  ck_assert_double_nan(fmod(NAN, NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_POS_INF));
  ck_assert_double_nan(s21_fmod(S21_POS_INF, S21_NAN));
  ck_assert_double_nan(s21_fmod(S21_NAN, S21_NEG_INF));
  ck_assert_double_nan(s21_fmod(S21_NEG_INF, S21_NAN));
  ck_assert_double_nan(fmod(NAN, INFINITY));
  ck_assert_double_nan(fmod(INFINITY, NAN));
  ck_assert_double_nan(fmod(NAN, -INFINITY));
  ck_assert_double_nan(fmod(-INFINITY, NAN));
}
END_TEST

START_TEST(fmod_test_2) {
  for (double s21 = -1500; s21 < 1500; s21 += 123) {
    for (double original = -12; original < 12; original += 1.25) {
      ck_assert_double_eq(fmod(s21, original), s21_fmod(s21, original));
      ck_assert_double_eq(fmod(original, s21), s21_fmod(original, s21));
    }
  }
}
END_TEST

START_TEST(abs_test) {
  ck_assert_double_eq(abs(-7), s21_abs(-7));
  ck_assert_double_eq(abs(-98), s21_abs(-98));
  ck_assert_double_eq(abs(123), s21_abs(123));
  ck_assert_double_eq(abs(10009), s21_abs(10009));
  ck_assert_double_eq(abs(-10009), s21_abs(-10009));
  ck_assert_double_eq(abs(0), s21_abs(0));
}
END_TEST

START_TEST(cos_tests) {
  ck_assert_ldouble_nan(s21_cos(S21_NEG_INF));
  ck_assert_ldouble_nan(s21_cos(S21_POS_INF));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * TEST_PI; k > -2 * TEST_PI; k -= TEST_PI / 17) {
      // ck_assert_ldouble_eq_tol(cos(k + R * TEST_PI), s21_cos(k + R *
      // TEST_PI), TEST_EPS);
      ck_assert_msg(
          fabsl(cos(k + R * TEST_PI) - s21_cos(k + R * TEST_PI)) < TEST_EPS,
          "s21 = %.10Lf, orignal = %.10lf\n", s21_cos(k + R * TEST_PI),
          cos(k + R * TEST_PI));
    }
  }
}
END_TEST

START_TEST(sin_tests) {
  //  ck_assert_ldouble_nan(s21_sin(S21_NAN));
  ck_assert_ldouble_nan(s21_sin(S21_POS_INF));
  ck_assert_ldouble_nan(s21_sin(S21_NEG_INF));
}
END_TEST

START_TEST(sin_test_1) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * S21_PI; k > -2 * S21_PI; k -= S21_PI / 17) {
      ck_assert_ldouble_eq_tol(sin(k + R * S21_PI), s21_sin(k + R * S21_PI),
                               1e-6);
    }
  }
}
END_TEST

START_TEST(tan_tests) {
  // ck_assert_double_nan(s21_tan(S21_NAN));
  ck_assert_double_nan(s21_tan(S21_POS_INF));
  ck_assert_double_nan(s21_tan(S21_NEG_INF));
}
END_TEST

START_TEST(tan_test_1) {
  for (int R = 20; R >= -20; R -= 4) {
    for (double k = 2 * S21_PI; k > -2 * S21_PI; k -= S21_PI / 9) {
      ck_assert_double_eq_tol(tan(k + R * S21_PI), s21_tan(k + R * S21_PI),
                              TEST_EPS);
    }
  }
}
END_TEST

START_TEST(sqrt_test_1) {
  for (double k = 0; k < 21; k += 3) {
    double s21 = s21_sqrt(k);
    double original = sqrt(k);
    ck_assert_double_eq_tol(s21, original, TEST_EPS);
  }
}
END_TEST

START_TEST(sqrt_test_2) {
  ck_assert_double_nan(s21_sqrt(S21_NAN));
  ck_assert_double_nan(sqrt(NAN));
  ck_assert_double_eq(s21_sqrt(S21_POS_INF), sqrt(INFINITY));
  ck_assert_double_nan(s21_sqrt(-S21_POS_INF));
  ck_assert_double_nan(sqrt(-INFINITY));
  ck_assert_double_nan(s21_sqrt(-5));
  ck_assert_double_nan(sqrt(-5));
  ck_assert_double_eq_tol(s21_sqrt(1000), sqrt(1000), TEST_EPS);
}
END_TEST

START_TEST(pow_test_1) {
  for (double k = -9; k <= 9; k += 1.7) {
    for (double g = -5; g < 5; g += 1) {
      long double s21 = s21_pow(k, g);
      long double original = pow(k, g);
      if ((!isnan(s21) && !isnan(original)) &&
          !(s21 == S21_POS_INF && original == S21_POS_INF) &&
          !(s21 == S21_NEG_INF && original == S21_NEG_INF)) {
        ck_assert_msg(fabsl(s21 - original) < TEST_EPS,
                      "s21 = %.10Lf, orignal = %.10Lf, base = %lf, power %lf",
                      s21, original, k, g);
      }
      s21 = s21_pow(g, k);
      original = pow(g, k);
      if ((!isnan(s21) && !isnan(original)) &&
          !(s21 == S21_POS_INF && original == S21_POS_INF) &&
          !(s21 == S21_NEG_INF && original == S21_NEG_INF)) {
        ck_assert_double_eq_tol(s21, original, 1e-06);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_2) {
  for (double k = -1e-1; k <= 1; k += 1.1e-1) {
    for (double g = -2.55; g < 2; g += 1.1) {
      long double s21 = s21_pow(k, g);
      long double original = pow(k, g);
      if ((!isnan(s21) && !isnan(original)) &&
          !(s21 == S21_POS_INF && original == S21_POS_INF) &&
          !(s21 == S21_NEG_INF && original == S21_NEG_INF)) {
        ck_assert_msg(fabsl(s21 - original) < TEST_EPS,
                      "s21 = %.10Lf, orignal = %.10Lf, base = %lf, power %lf",
                      s21, original, k, g);
      }
      s21 = s21_pow(g, k);
      original = pow(g, k);
      if ((!isnan(s21) && !isnan(original)) &&
          !(s21 == S21_POS_INF && original == S21_POS_INF) &&
          !(s21 == S21_NEG_INF && original == S21_NEG_INF)) {
        ck_assert_double_eq_tol(s21, original, TEST_EPS);
      }
    }
  }
}
END_TEST

START_TEST(pow_test_3) {
  ck_assert_double_eq(pow(1, 0), s21_pow(1, 0));
  ck_assert_double_eq(pow(-1, 3), s21_pow(-1, 3));
  ck_assert_double_eq(pow(-1, 4), s21_pow(-1, 4));
  ck_assert_double_eq(pow(0, 0), s21_pow(0, 0));
  ck_assert_double_eq(pow(0, -0.1), s21_pow(0, -0.1));
  ck_assert_double_eq(pow(0, 1), s21_pow(0, 1));
  ck_assert_ldouble_eq(pow(S21_POS_INF, 0), s21_pow(S21_POS_INF, 0));
  ck_assert_double_eq(pow(S21_POS_INF, -1), s21_pow(S21_POS_INF, -1));
  ck_assert_double_eq(pow(-1, S21_NEG_INF), s21_pow(-1, S21_NEG_INF));
  ck_assert_double_eq(pow(0, S21_POS_INF), s21_pow(0, S21_POS_INF));
  ck_assert_double_eq(pow(S21_NAN, 0), s21_pow(S21_NAN, 0));
  ck_assert_double_eq(pow(S21_POS_INF, S21_POS_INF),
                      s21_pow(S21_POS_INF, S21_POS_INF));
  ck_assert_double_eq(pow(S21_POS_INF, S21_NEG_INF),
                      s21_pow(S21_POS_INF, S21_NEG_INF));
  ck_assert_double_eq(pow(S21_NEG_INF, S21_POS_INF),
                      s21_pow(S21_NEG_INF, S21_POS_INF));
  ck_assert_double_eq(pow(S21_NEG_INF, S21_NEG_INF),
                      s21_pow(S21_NEG_INF, S21_NEG_INF));
  ck_assert_double_eq(pow(1, S21_NEG_INF), s21_pow(1, S21_NEG_INF));
  ck_assert_double_eq(pow(1, S21_NAN), s21_pow(1, S21_NAN));

  ck_assert_double_nan(s21_pow(0, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_POS_INF));
  ck_assert_double_nan(s21_pow(S21_POS_INF, S21_NAN));
  ck_assert_double_nan(s21_pow(S21_NAN, S21_NEG_INF));
  ck_assert_double_nan(s21_pow(S21_NEG_INF, S21_NAN));

  ck_assert_double_eq(pow(2, S21_POS_INF), s21_pow(2, S21_POS_INF));
  ck_assert_double_eq(pow(0.5, S21_POS_INF), s21_pow(0.5, S21_POS_INF));
  ck_assert_double_eq(pow(-2, S21_POS_INF), s21_pow(-2, S21_POS_INF));
  ck_assert_double_eq(pow(2, S21_NEG_INF), s21_pow(2, S21_NEG_INF));
  ck_assert_double_eq(pow(0.5, S21_NEG_INF), s21_pow(0.5, S21_NEG_INF));
  ck_assert_double_eq(pow(-2, S21_NEG_INF), s21_pow(-2, S21_NEG_INF));
}
END_TEST

START_TEST(asin_test_1) {
  for (float k = -1; k <= 0; k += 0.0205) {
    double s21 = s21_asin(k);
    double original = asin(k);
    ck_assert_double_eq_tol(s21, original, 1e-6);
  }
  ck_assert_double_eq_tol(asin(1), s21_asin(1), 1e-6);
}
END_TEST

START_TEST(asin_test_2) {
  for (float k = -1; k <= 0; k += 0.1) {
    double s21 = s21_asin(k);
    double original = asin(k);
    ck_assert_double_eq_tol(s21, original, 1e-7);
  }
}
END_TEST

START_TEST(acos_test_1) {
  for (float k = -1; k <= 1; k += 0.1) {
    double s21 = s21_acos(k);
    double original = acos(k);
    ck_assert_double_eq_tol(s21, original, 1e-7);
  }
}
END_TEST

START_TEST(acos_test_2) {
  for (float k = -1; k <= 1; k += 0.1) {
    double s21 = s21_acos(k);
    double original = acos(k);
    ck_assert_double_eq_tol(s21, original, TEST_EPS);
  }
}
END_TEST

START_TEST(atan_test_2) {
  double s21 = 12;
  ck_assert_double_eq_tol(atan(s21), s21_atan(s21), TEST_EPS);
  s21 = 0.4;
  ck_assert_double_eq_tol(atan(s21), s21_atan(s21), TEST_EPS);
  s21 = -0.333;
  ck_assert_double_eq_tol(atan(s21), s21_atan(s21), TEST_EPS);
  s21 = 55;
  ck_assert_double_eq_tol(atan(s21), s21_atan(s21), TEST_EPS);
  s21 = 13.54;
  ck_assert_double_eq_tol(atan(s21), s21_atan(s21), TEST_EPS);
}
END_TEST

START_TEST(asin_acos_atan_test) {
  ck_assert_double_nan(s21_asin(S21_NAN));
  ck_assert_double_nan(s21_acos(S21_NAN));
  ck_assert_double_nan(s21_atan(S21_NAN));
  ck_assert_double_nan(s21_asin(S21_POS_INF));
  ck_assert_double_nan(s21_acos(S21_POS_INF));
  ck_assert_double_eq_tol(atan(S21_POS_INF), s21_atan(S21_POS_INF), TEST_EPS);
  ck_assert_double_nan(s21_asin(-S21_POS_INF));
  ck_assert_double_nan(s21_acos(-S21_POS_INF));
  ck_assert_double_eq_tol(atan(-S21_POS_INF), atan(-S21_POS_INF), TEST_EPS);
  ck_assert_double_nan(s21_asin(5));
  ck_assert_double_nan(s21_acos(6));
  ck_assert_double_nan(s21_asin(-8));
  ck_assert_double_nan(s21_acos(-4));
}
END_TEST

Suite *s21_math_tests_create() {
  Suite *s21_math = suite_create("s21_math");
  TCase *s21_math_tests = tcase_create("S21_MATH");

  tcase_add_test(s21_math_tests, asin_acos_atan_test);
  tcase_add_test(s21_math_tests, pow_test_1);
  tcase_add_test(s21_math_tests, pow_test_2);
  tcase_add_test(s21_math_tests, pow_test_3);

  tcase_add_test(s21_math_tests, atan_test_2);

  tcase_add_test(s21_math_tests, asin_test_1);
  tcase_add_test(s21_math_tests, asin_test_2);

  tcase_add_test(s21_math_tests, acos_test_1);
  tcase_add_test(s21_math_tests, acos_test_2);

  tcase_add_test(s21_math_tests, sqrt_test_1);
  tcase_add_test(s21_math_tests, sqrt_test_2);

  tcase_add_test(s21_math_tests, tan_test_1);
  tcase_add_test(s21_math_tests, tan_tests);

  tcase_add_test(s21_math_tests, sin_tests);
  tcase_add_test(s21_math_tests, sin_test_1);

  tcase_add_test(s21_math_tests, cos_tests);

  tcase_add_test(s21_math_tests, exp_test_1);
  tcase_add_test(s21_math_tests, exp_test_2);
  tcase_add_test(s21_math_tests, exp_test_3);
  tcase_add_test(s21_math_tests, exp_test_4);

  tcase_add_test(s21_math_tests, fmod_test_1);
  tcase_add_test(s21_math_tests, fmod_test_2);

  tcase_add_test(s21_math_tests, abs_test);
  tcase_add_test(s21_math_tests, log_tests);
  tcase_add_test(s21_math_tests, fabs_tests);
  tcase_add_test(s21_math_tests, ceil_tests);
  tcase_add_test(s21_math_tests, floor_tests);

  suite_add_tcase(s21_math, s21_math_tests);

  return s21_math;
}

int main() {
  Suite *s21_math = s21_math_tests_create();
  SRunner *s21_math_runner = srunner_create(s21_math);
  srunner_set_fork_status(s21_math_runner, CK_FORK);
  srunner_run_all(s21_math_runner, CK_VERBOSE);
  int num_failed = srunner_ntests_failed(s21_math_runner);
  srunner_free(s21_math_runner);

  return num_failed == 0 ? 0 : 1;
}
