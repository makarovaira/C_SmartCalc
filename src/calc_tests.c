#include "calc_tests.h"

START_TEST(s21_test_0) {
  double x = 0;
  double orig = 10;
  char str[255] = "5 + 5";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_1) {
  double x = 0;
  double orig = 162;
  char str[255] = "   4 * 5 * 2 * 2 * 2 + 2";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_2) {
  double x = 0;
  double orig = 180;
  char str[255] =
      "3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+"
      "3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3+3";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_3) {
  double x = 0;
  double orig = 20;
  char str[255] = "  150 / 10 + 5 * 2 / 2";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_4) {
  double x = 0;
  double orig = 9;
  char str[255] = "  5 + 5 - 2 * 3 / 6";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_5) {
  double x = 0;
  double orig = 69;
  char str[255] = "2+(5 * 5 * 5 + 5 + 2 * 2) / (2)";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(s21_test_6) {
  double x = 0;
  double orig = 11.958851;
  char str[255] = "5 + (3 + sin(8/2 - 3.5)) *2";
  x = toPostfix(str);
  ck_assert_double_eq_tol(x, orig, 1e-7);
}
END_TEST

START_TEST(s21_test_7) {
  char *str = "24*4 -3 * 2";
  double orig = 90;
  double value = toPostfix(str);
  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(s21_test_8) {
  double orig = 4;
  char *str = "2 - (-2)";
  double value = toPostfix(str);
  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(s21_test_9) {
  double orig = -0.41211848524;
  char *str = "-sin(9)";
  double value = toPostfix(str);
  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(s21_test_10) {
  double orig = 2.41211848524;
  char *str = "sin(9)-(-2)";
  double value = toPostfix(str);

  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(s21_test_11) {
  double orig = 0.91113026188;
  char *str = "-cos(9)";
  double value = toPostfix(str);
  ck_assert_int_eq(value, orig);
}
END_TEST

START_TEST(calc_test) {
  {
    char src[100] = "123+0.456";
    double result = toPostfix(src);
    double real_result = 123.456;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-3 failed");
  }
  {
    char src[100] = "log(-2)";
    double result = toPostfix(src);
    ck_assert_msg(result == result, "test-4 failed");
  }
  {
    char src[100] = "-(-1)";
    double result = toPostfix(src);
    double real_result = 1;
    ck_assert_msg(result == real_result, "test-5 failed");
  }
  {
    char src[100] = "cos(10 mod 2.2)";
    double result = toPostfix(src);
    double real_result = 0.362358;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-6 failed");
  }
  {
    char src[100] = "sqrt(ln(10))";
    double result = toPostfix(src);
    double real_result = 1.517427;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-7 failed");
  }
  {
    char src[100] = "atan(10)+sin(10)";
    double result = toPostfix(src);
    double real_result = 1.644775;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-8 failed");
  }
  {
    char src[100] = "asin(1)";
    double result = toPostfix(src);
    double real_result = 1.570796;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001, "test-9 failed");
  }
  {
    char src[100] = "10-20*(-10)";
    double result = toPostfix(src);
    double real_result = -210;
    ck_assert_msg(fabs(result) - fabs(real_result) <= 0.00001,
                  "test-10 failed");
  }
}
END_TEST

START_TEST(plus_t) {
  double my = toPostfix("(-2)+2");
  ck_assert_float_eq(my, 0);
}
END_TEST

START_TEST(minus_t) {
  double my = toPostfix("(-2.2)-2.2");
  ck_assert_float_eq(my, -4.4);
}
END_TEST

START_TEST(mult_t) {
  double my = toPostfix("(-2.2)*(+2.2)");
  ck_assert_float_eq(my, -4.84);
}
END_TEST

START_TEST(division_t) {
  double my = toPostfix("(-2.2)/2.2");
  ck_assert_float_eq(my, -1);
}
END_TEST

START_TEST(degr_t) {
  double my = toPostfix("(2.2)^(-2.2)");
  ck_assert_double_eq_tol(my, 0.17647, 0.17647);
}
END_TEST

START_TEST(sin_t) {
  double my = toPostfix("sin(2)");
  ck_assert_double_eq(my, sin(2));
}
END_TEST

START_TEST(cos_t) {
  long double my = toPostfix("cos(2)");
  ck_assert_double_eq_tol(my, cos(2), 1e-7);
}
END_TEST

START_TEST(tan_t) {
  long double my = toPostfix("tan(2)");
  ck_assert_ldouble_eq(my, tan(2));
}
END_TEST

START_TEST(asin_t) {
  long double my = toPostfix("asin(1)");
  ck_assert_ldouble_eq(my, asin(1));
}
END_TEST

START_TEST(acos_t) {
  long double my = toPostfix("acos(1)");
  ck_assert_ldouble_eq(my, acos(1));
}
END_TEST

START_TEST(atan_t) {
  long double my = toPostfix("atan(1)");
  ck_assert_ldouble_eq(my, atan(1));
}
END_TEST

START_TEST(ln_t) {
  long double my = toPostfix("log(1)");
  ck_assert_ldouble_eq(my, log(1));
}
END_TEST

START_TEST(log_t) {
  long double my = toPostfix("log(1)");
  ck_assert_ldouble_eq(my, log10(1));
}
END_TEST

START_TEST(sqrt_t) {
  long double my = toPostfix("sqrt(1)");
  ck_assert_ldouble_eq(my, sqrt(1));
}
END_TEST

START_TEST(mod_t) {
  long double my = toPostfix("4mod8");
  ck_assert_ldouble_eq(my, 4);
}
END_TEST

START_TEST(pow_t) {
  long double my = toPostfix("4^8");
  ck_assert_ldouble_eq(pow(4, 8), my);
}
END_TEST

START_TEST(bracket_t) {
  double x = 0;
  double orig = 30;
  char str[255] = "5+(4+5+6)*2-5";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(lnn_t) {
  long double my = toPostfix("ln(1)");
  ck_assert_ldouble_eq(my, log(1));
}

START_TEST(double_bracket_t) {
  double orig = 35;
  double x;
  char str[255] = "(5+(4+5+6))*2-5";
  x = toPostfix(str);
  ck_assert_double_eq(x, orig);
}
END_TEST

START_TEST(unar_minus) {
  long double my = toPostfix("-7 + 5");
  ck_assert_ldouble_eq(my, -2);
}
END_TEST

START_TEST(unar_plus) {
  long double my = toPostfix("+7 + 5");
  ck_assert_ldouble_eq(my, 12);
}
END_TEST

START_TEST(double_plus) {
  long double my = toPostfix("0.06 + 0.05");
  ck_assert_double_eq(my, 0.11);
}
END_TEST

START_TEST(double_sin) {
  long double my = toPostfix("sin(-1)");
  ck_assert_double_eq(my, sin(-1));
}
END_TEST

Suite *suite_toPostfix(void) {
  Suite *s = suite_create("suite_toPostfix");
  TCase *tc = tcase_create("suite_toPostfix");

  tcase_add_test(tc, s21_test_0);
  tcase_add_test(tc, s21_test_1);
  tcase_add_test(tc, s21_test_2);
  tcase_add_test(tc, s21_test_3);
  tcase_add_test(tc, s21_test_4);
  tcase_add_test(tc, s21_test_5);
  tcase_add_test(tc, s21_test_6);
  tcase_add_test(tc, s21_test_7);
  tcase_add_test(tc, s21_test_8);
  tcase_add_test(tc, s21_test_9);
  tcase_add_test(tc, s21_test_10);
  tcase_add_test(tc, s21_test_11);
  tcase_add_test(tc, calc_test);

  tcase_add_test(tc, plus_t);
  tcase_add_test(tc, minus_t);
  tcase_add_test(tc, division_t);
  tcase_add_test(tc, mult_t);
  tcase_add_test(tc, degr_t);
  tcase_add_test(tc, sin_t);
  tcase_add_test(tc, cos_t);
  tcase_add_test(tc, tan_t);
  tcase_add_test(tc, asin_t);
  tcase_add_test(tc, acos_t);
  tcase_add_test(tc, atan_t);
  tcase_add_test(tc, ln_t);
  tcase_add_test(tc, log_t);
  tcase_add_test(tc, sqrt_t);
  tcase_add_test(tc, mod_t);
  tcase_add_test(tc, pow_t);
  tcase_add_test(tc, bracket_t);
  tcase_add_test(tc, lnn_t);
  tcase_add_test(tc, double_bracket_t);
  tcase_add_test(tc, unar_minus);
  tcase_add_test(tc, unar_plus);
  tcase_add_test(tc, double_plus);
  tcase_add_test(tc, double_sin);
  tcase_add_test(tc, calc_test);

  suite_add_tcase(s, tc);
  return s;
}

void run_tests(void) {
  Suite *list_cases[] = {suite_toPostfix(), NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main(void) {
  run_tests();
  return 0;
}