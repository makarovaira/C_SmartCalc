#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_bank_calc.h"

void ann_credit(double creditSum, double interestRateY, int countMonth,
                credit_calc *credit_c) {
  double interestRateM = interestRateY / 1200.0;
  double ak = interestRateM * pow(1 + interestRateM, countMonth) /
              (pow(1 + interestRateM, countMonth) - 1);
  credit_c->a = round(creditSum * ak * 100) / 100;
  credit_c->sum = credit_c->a * countMonth;
  credit_c->overpayment_credit = credit_c->sum - creditSum;
}

void diff_credit(double creditSum, double interestRateY, int countMonth,
                 credit_calc *credit_c) {
  double c_sum = creditSum;
  double mp_real = c_sum / countMonth;
  int i = 0;
  while (countMonth != 0) {
    double mp = mp_real + (c_sum * interestRateY / 1200.0);
    credit_c->mounthly_payment[i] = round(mp * 100) / 100;
    c_sum -= mp_real;
    countMonth--;
    credit_c->sum += credit_c->mounthly_payment[i];
    i++;
  }
  credit_c->overpayment_credit = credit_c->sum - creditSum;
}

// int main() {
//     long double creditSum = 300000.0;
//     long double interestRateY = 8.5;
//     int countMonth = 24;
//     credit_calc cr = {{0}, 0, 0, 0};
//     diff_credit(creditSum, interestRateY, countMonth, &cr);
//     for (int i = 0; i < countMonth;i++) {
//         printf("%lf\n", cr.mounthly_payment[i]);
//     }
//     printf("%lf, %lf", cr.overpayment_credit, cr.sum);
//     //printf("%Lf", overpayment_credit_a(creditSum, interestRateY,
//     countMonth));
// }
