#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_bank_calc.h"

void deposit(deposit_calc_i *dataInp, deposit_calc_o *dataOut) {
  if (!dataInp->typeCap) {
    dataOut->accruedInterest =
        dataInp->depositSum * dataInp->interestRate * dataInp->term / 1200;
    dataOut->finalPayout = dataInp->depositSum + dataOut->accruedInterest;
  } else {
    switch (dataInp->freqCap) {
      case 0:
        dataOut->finalPayout =
            dataInp->depositSum *
            pow((1 + dataInp->interestRate / 36500), (dataInp->term * 30.43));
        break;
      case 1:
        dataOut->finalPayout =
            dataInp->depositSum *
            pow((1 + dataInp->interestRate / 1200), dataInp->term);
        break;
      case 2:
        dataOut->finalPayout =
            dataInp->depositSum *
            pow((1 + dataInp->interestRate / 400), dataInp->term / 3);
        break;
    }
    dataOut->accruedInterest = dataOut->finalPayout - dataInp->depositSum;
  }

  double no_tax_sum;
  no_tax_sum = NON_TAX_INC * (int)(dataInp->term / 12);
  if (no_tax_sum && dataOut->accruedInterest > no_tax_sum) {
    dataOut->tax =
        (dataOut->accruedInterest - no_tax_sum) * dataInp->taxRate / 100;
  }
}

// int main() {
//     deposit_calc_i depositInp = {0};
//     deposit_calc_o depositOut = {0};
//     depositInp.depositSum = 350000;
//     depositInp.interestRate = 4.7;
//     depositInp.term = 9;
//     depositInp.freqCap = 1;
//     depositInp.typeCap = 0;
//     depositInp.taxRate = 13;
//     deposit(&depositInp, &depositOut);
//     printf("%lf", depositOut.accruedInterest);
// }
