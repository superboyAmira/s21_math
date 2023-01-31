/*
  A main part of s21_math.h Library
  Powered by norinede, jodeedal, sapphire, superboy
*/

#include "s21_math.h"

// long double s21_check(double x) {
//    for (; x < -2 * S21_PI || 2 * S21_PI < x;) { // значения в обозначенных
//    промежутках максимально аппроксимированы к реальным
//        if (x > 2 * S21_PI) { // если х выходит за обозначенный промежуток, то
//        мы возвращаем его внутрь, потому что значения идентичны
//            x -= 2 * S21_PI;
//        } else {
//            x += 2 * S21_PI;
//        }
//    }
//    return x;
// }

long double s21_factorial(int N) {
  if (N == 0 || N == 1) {
    return 1;
  } else {
    return N * s21_factorial(N - 1);
  }
}

long double s21_log(double x) {  // разложение по методу Галея
  int ex_pow = 0;  // сколько раз можем х разделить на экспоненту
  long double res = 0;
  double compare = 0;

  if (x == 0) {
    res = S21_NEG_INF;
  } else if (x == S21_POS_INF) {
    res = S21_POS_INF;
  } else if (x == 1) {
    res = 0.0;
  } else if (x < 0.0 || x == S21_NAN || x == -S21_NAN || x == -S21_NEG_INF) {
    res = S21_NAN;
  } else {
    for (; x > S21_E; x /= S21_E, ex_pow++)
      continue;  // чтобы поизменялось ex_pow
    for (int i = 0; i < 200; i++) {
      compare = res;
      res = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
    res += ex_pow;
  }
  return res;
}

long double s21_fmod(double x, double y) {  // остаток от деления
  long double result = 0.0;
  int flag_minus = FALSE;
  if (y == 0.0 || x == S21_POS_INF || x == S21_NEG_INF || x == S21_NAN ||
      is_nan(y)) {
    result = S21_NAN;
  } else if (x == 0.0) {
    result = 0.0;
  } else if (y == S21_NEG_INF || y == S21_POS_INF) {
    result = x;
  } else {
    if (x < 0.0) {
      x = -x;
      flag_minus = TRUE;
    }
    if (y < 0.0) {
      y = -y;
    }
    while (TRUE) {
      x -= y;
      if (x < 0.0) {  // мы постепенно вычитаем из делимого делитель, пока
                      // остаток не стане меньше нуля
        if (flag_minus) {
          result = -(x + y);
        } else {
          result = x + y;
        }
        break;
      }
    }
  }
  return result;
}

long double s21_floor(double x) {  // округление
  long double result = 0.0;

  if (x > 0.0) {
    for (double i = 0.0; i <= x + 1.0; i += 1.0) {
      if (i == x) {
        result = x;
        break;
      } else if (i > x) {
        result = --i;
        break;
      }
    }
  } else {
    for (double i = 0.0; i >= x - 1.0; i -= 1.0) {
      if (i == x) {
        result = x;
        break;
      } else if (i < x) {
        result = i;
        break;
      }
    }
  }
  return result;
}

long double s21_fabs(double x) {
  long double result = 0.0;
  if (x < 0.0) {
    result = -x;
  } else {
    result = x;
  }
  return result;
}

long double s21_exp(double x) {  // ряд тейлора для Е
  //    long double numerator = x; // числитель
  long double middle = 1.0;  // промежуточное значение
  double count = 1.0;
  long double result = 1.0;
  if (x == S21_NAN) {
    result = S21_NAN;
  } else if (x == S21_POS_INF) {
    result = S21_POS_INF;
  } else if (x == S21_NEG_INF) {
    result = 0.0;
  } else if (x == 0.0) {
    result = 1.0;
  } else if (x == 1.0) {
    result = S21_E;
  } else {
    while (s21_fabs(middle) > 1e-15) {
      //  for (int count = 1; count < 500; count++) {
      //      result += numerator / s21_factorial(count);
      //      numerator *= x;
      middle *= x / count;
      result += middle;
      count++;
    }
  }
  return result;
}

long double s21_cos(double x) {
  double result = 0.0;
  if (!is_inf(x) && !is_nan(x)) {
    x = s21_fmod(x, 2 * S21_PI);
    double count = 1.0;
    double step = 1.0;
    double middle = 1.0;
    result = 1;
    while (s21_fabs(step) > S21_EPS) {
      middle *= x * x;
      step = s21_pow(-1, count) / (s21_factorial(2 * count)) * middle;
      result += step;
      count++;
    }
  } else {
    result = S21_NAN;
  }
  return result;
}

int s21_abs(int x) {
  if (x & (1 << ((sizeof(x) * 8) - 1))) {
    x = -x;
  }
  return x;
}

long double s21_sin(double x) {
  x = s21_fmod(x, 2 * S21_PI);
  int count = 1;
  double chislitel = x;
  double znamenatel = 1.0;
  double sumMember = 100.0;
  double result = x;
  if (is_nan(x) || is_inf(x)) {
    result = S21_NAN;
  } else {
    while (s21_fabs(sumMember) > S21_EPS) {
      znamenatel *=
          ((count << 1) *
           ((count << 1) + 1));  // -6 20 // замена факториалу с помощью
                                 // побитового сдвига для ускорения вычисления
      chislitel *=
          -1 * x *
          x;  // -x^3 x^5 // один из мноителей ряда тейлора, просто без степени
      sumMember = chislitel / znamenatel;
      result += sumMember;
      count++;
    }
  }
  return result;
}

long double s21_acos(double x) {
  long double result = S21_PI / 2;
  if (x != 0) {
    if (0 < x && x <= 1)
      result = s21_atan(s21_sqrt(1 - x * x) / x);
    else if (-1 <= x && x < 0)
      result = s21_atan(s21_sqrt(1 - x * x) / x) + S21_PI;
    else
      result = S21_NAN;
  }
  return result;
}

long double s21_atan(double x) {
  long double result = x;
  long double addVal = x;
  long double c = 0.0;
  if (x == S21_NAN) {
    result = S21_NAN;
  } else if (x == S21_POS_INF) {
    result = S21_PI / 2.0;
  } else if (x == S21_NEG_INF) {
    result = -S21_PI / 2.0;
  } else {
    if (s21_fabs(x) <= 1) {
      while (s21_fabs(addVal) >= S21_EPS) {
        addVal = -addVal;
        addVal *= ((x * x * (1 + 2 * c)) / (3 + 2 * c));
        result += addVal;
        c++;
      }
    } else if (s21_fabs(x) > 1) {
      result = 1 / x;
      addVal = 1 / x;
      while (s21_fabs(addVal) >= S21_EPS) {
        addVal = -addVal;
        addVal *= ((1 + 2 * c) / (x * x * (3 + 2 * c)));
        result += addVal;
        c++;
      }
      result = S21_PI * s21_fabs(x) / (2 * x) - result;
    }
  }
  return result;
}

long double s21_asin(double x) {
  long double result = 0;
  if (s21_fabs(x) > 1) {
    result = S21_NAN;
  } else if (s21_fabs(x) != 1) {
    result = s21_atan(x / (s21_sqrt(1 - x * x)));
  } else if (x == 1) {
    result = S21_PI / 2;
  } else {
    result = -S21_PI / 2;
  }
  return result;
}

long double s21_ceil(double x) {
  long double result = 0;
  if (x == -1.0 / 0.0 || x == 1.0 / 0.0 || x == S21_NAN || x == DBL_MAX ||
      x == -DBL_MAX) {
    result = x;
  } else if (x <= 0 || s21_fabs((long int)x - x) < 1e-69) {
    result = (long int)x;
  } else {
    result = (long int)x + 1;
  }
  return result;
}

long double s21_pow(double base, double power) {
  long double result;
  long double copy = base;
  int exception = FALSE;
  if (power == 1) {
    result = base;
    exception = TRUE;
  }
  if ((is_nan(base) && power != 0.0) || (is_nan(power) && base != 1.0)) {
    result = S21_NAN;
    exception = TRUE;
  } else if ((base == 1.0) ||
             (base == -1 && (power == S21_NEG_INF || power == S21_POS_INF)) ||
             (power == 0.0)) {
    result = 1.0;
    exception = TRUE;
  } else if (power == S21_NEG_INF && base < 1.0 && base > -1.0) {
    result = S21_POS_INF;
    exception = TRUE;
  } else if (((base == S21_NEG_INF || base == S21_POS_INF) && power < 0) ||
             (power == S21_NEG_INF) || (base != -1 && power == S21_NEG_INF) ||
             (base == 0 && power >= 0 && (base != power))) {
    result = 0.0;
    exception = TRUE;
  } else if (power == S21_POS_INF && base < 1.0 && base > -1.0) {
    result = 0.0;
    exception = TRUE;
  } else if (((base == S21_NEG_INF || base == S21_POS_INF) && power > 0) ||
             (power == S21_POS_INF)) {
    result = S21_POS_INF;
    exception = TRUE;
  }
  if (!exception) {
    if (base < 0) {  // если основание отрицательное, то
      copy *= -1;  // его нужно преобразовать
      result = s21_exp(power * s21_log(copy));
      if (s21_fmod(power, 2) != 0) {  // для проверки четной / нечетной степени
        result *=
            -1;  // если число изначально отрицательное и степень отрицательная,
                 // то ответ также должен быть отрицательный
      }
    } else {
      result = s21_exp(power * s21_log(base));
    }
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result = 0;
  if (x == S21_NAN || x == S21_NEG_INF || x < 0)
    result = S21_NAN;  // невозможно вычислить корень из отрицательного числа
  else if (x == S21_POS_INF)
    result = S21_POS_INF;
  else if (x == 0.0)
    result = x;
  else
    result = s21_pow(x, 0.5);  // степень 1/2 приравнивается к корню
  return result;
}

long double s21_tan(double x) {
  long double tan = 0;
  if (x == S21_POS_INF || x == S21_NEG_INF || x == S21_NAN) {
    tan = S21_NAN;
  } else if (x == 0.0) {
    tan = x;
  } else {
    tan = s21_sin(x) / s21_cos(x);
  }
  return tan;
}
