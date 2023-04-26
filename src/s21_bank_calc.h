#ifndef SRC_S21_BANK_CALC_H
#define SRC_S21_BANK_CALC_H

enum { NON_TAX_INC = 75000 };

typedef struct {
  double mounthly_payment[61];
  double overpayment_credit;
  double sum;
  double a;
} credit_calc;

typedef struct {
  int typeCap;
  int freqCap;
  double term;
  double depositSum;
  double interestRate;
  double taxRate;
  double periodOfPay;
  double capitalOfInt;
  double listOfDeposit;
  double listOfWithdrawals;
} deposit_calc_i;

typedef struct {
  double accruedInterest;
  double tax;
  double finalPayout;
} deposit_calc_o;

void ann_credit(double creditSum, double interestRateY, int countMonth,
                credit_calc *credit_c);
void diff_credit(double creditSum, double interestRateY, int countMonth,
                 credit_calc *credit_c);
void deposit(deposit_calc_i *dataInp, deposit_calc_o *dataOut);

#endif
