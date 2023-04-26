#ifndef SRC_UNIT_TESTS_UNIT_TESTS_H_
#define SRC_UNIT_TESTS_UNIT_TESTS_H_
#include <check.h>
#include <stdio.h>
#include <unistd.h>

#include "s21_smart_calc.h"
Suite *suite_smart_calc(void);

void run_test(void);
void run_testcase(Suite *testcase);
double get_rand(double min, double max);
#endif
