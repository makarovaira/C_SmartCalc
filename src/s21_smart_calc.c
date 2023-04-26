#include "s21_smart_calc.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(stack_n *stack, operation_t *op);
operation_t *pop(stack_n *stack);
int isNum(char x);
char *getIndexFunc(char *s, int *ans);
void getIndexOp(char last_op, char *s, int *ans);
void fromStackToQueue(stack_n *stack, queue *q);
void pushOpToQueue(queue *q, operation_t *op);
char *pushNumToQueue(queue *q, char *str);
void OpFromStackToQueue(stack_n *stack, queue *q, operation_t *op);
double countNotation(queue q);
double popStackD(stack_double *stackDouble);
void pushStackD(stack_double *stackDouble, double x);

int error;

static double plus(double a, double b) { return a + b; }

static double minus(double a, double b) { return a - b; }

static double multiply(double a, double b) { return a * b; }

static double division(double a, double b) { return a / b; }

static double modm(double a, double b) { return fmod(a, b); }

static double power(double a, double b) { return pow(a, b); }

static double logm(double a) { return log10(a); }

static double lnm(double a) { return log(a); }

static double atanm(double a) { return atan(a); }

static double acosm(double a) { return acos(a); }

static double asinm(double a) { return asin(a); }

static double sinm(double a) { return sin(a); }

static double cosm(double a) { return cos(a); }

static double tanm(double a) { return tan(a); }

static double sqrtm(double a) { return sqrt(a); }

static double unPlus(double a) { return a; }

static double unMinus(double a) { return -a; }

void push(stack_n *stack, operation_t *op) {
  if (stack->size < MAX_SIZE_STACK) {
    stack->data[stack->size] = op;
    stack->size++;
  } else {
    error = TOO_LONG_LINE;
  }
}

operation_t *pop(stack_n *stack) {
  operation_t *ans = NULL;
  if (stack->size > 0) {
    stack->size--;
    ans = stack->data[stack->size];
  } else {
    error = TOO_SHORT_LINE;
  }
  return ans;
}

double popStackD(stack_double *stackDouble) {
  double ans = 0;
  if (stackDouble->size > 0) {
    stackDouble->size--;
    ans = stackDouble->data[stackDouble->size];
  } else {
    error = TOO_SHORT_LINE;
  }
  return ans;
}

void pushStackD(stack_double *stackDouble, double x) {
  if (stackDouble->size < MAX_SIZE_STACK) {
    stackDouble->data[stackDouble->size] = x;
    stackDouble->size++;
  } else {
    error = TOO_LONG_LINE;
  }
}

void pushOpToQueue(queue *q, operation_t *op) {
  if (q->size < MAX_SIZE_STACK) {
    q->data[q->size++].op = op;
  } else {
    error = TOO_LONG_LINE;
  }
}

char *pushNumToQueue(queue *q, char *str) {
  char *end = NULL;
  if (q->size < MAX_SIZE_STACK) {
    q->data[q->size++].num = strtod(str, &end);
  } else {
    error = INPUT_ERROR;
  }
  if (str == end) {
    error = INPUT_ERROR;
  } else {
    str = end;
  }
  return str;
}

double toPostfix(char *intfixStr) {
  error = 0;
  stack_n stack = {0};
  operation_t operatersArr[] = {
      {'+', 1, plus, NULL},     {'-', 1, minus, NULL},
      {'*', 2, multiply, NULL}, {'/', 2, division, NULL},
      {'%', 2, modm, NULL},     {'^', 3, power, NULL},
      {'l', 3, NULL, logm},     {'n', 3, NULL, lnm},
      {'a', 3, NULL, atanm},    {'o', 3, NULL, acosm},
      {'i', 3, NULL, asinm},    {'s', 3, NULL, sinm},
      {'c', 3, NULL, cosm},     {'t', 3, NULL, tanm},
      {'q', 3, NULL, sqrtm},    {'+', 4, NULL, unPlus},
      {'-', 4, NULL, unMinus},  {'(', 0, NULL, NULL},
      {')', 0, NULL, NULL}};
  int index = ERROR;
  char last_op = 'X';
  queue postfixStr = {{{0}}, 0};
  while (!error && *intfixStr != '\0') {
    switch (*intfixStr) {
      case '0' ... '9':
        intfixStr = pushNumToQueue(&postfixStr, intfixStr);
        if (!last_op || error) {
          error = INPUT_ERROR;
          break;
        } else {
          last_op = '\0';
        }
        continue;
      case 'm':
        intfixStr++;
        if (!strncmp(intfixStr, "od", 2)) {
          intfixStr++;
        } else {
          error = INPUT_ERROR;
          break;
        }
        /* fall through */
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
        getIndexOp(last_op, intfixStr, &index);
        if (!error) {
          OpFromStackToQueue(&stack, &postfixStr, &operatersArr[index]);
          last_op = *intfixStr;
        }
        break;
      case 'l':
      case 'a':
      case 's':
      case 'c':
      case 't':
      case '(':
        intfixStr = getIndexFunc(intfixStr, &index);
        if (!error) {
          push(&stack, &operatersArr[index]);
        }
        break;
      case ')':
        fromStackToQueue(&stack, &postfixStr);
        break;
      case ' ':
      case '\t':
      case '\r':
        break;
      default:
        error = INPUT_ERROR;
        break;
    }
    intfixStr++;
  }
  while (!error && stack.size) {
    pushOpToQueue(&postfixStr, pop(&stack));
  }
  double ans = 0;
  if (!error) {
    ans = countNotation(postfixStr);
  }
  return ans;
}

// /4

char *getIndexFunc(char *s, int *ans) {
  switch (*s) {
    case 'l':
      s++;
      if (*s == 'n') {
        *ans = LNM;
      } else if (!(strncmp(s, "og", 2))) {
        s++;
        *ans = LOGM;
      }
      break;
    case 'a':
      s++;
      if (!strncmp(s, "tan", 3)) {
        *ans = ATANM;
      } else if (!strncmp(s, "cos", 3)) {
        *ans = ACOSM;
      } else if (!strncmp(s, "sin", 3)) {
        *ans = ASINM;
      }
      s += 2;
      break;
    case 's':
      s++;
      if (!strncmp(s, "in", 2)) {
        *ans = SINM;
        s += 1;
      } else if (!strncmp(s, "qrt", 3)) {
        *ans = SQRTM;
        s += 2;
      }
      break;
    case 'c':
      s++;
      if (!strncmp(s, "os", 2)) {
        *ans = COSM;
        s += 1;
      }
      break;
    case 't':
      s++;
      if (!strncmp(s, "an", 2)) {
        *ans = TANM;
        s += 1;
      }
      break;
    case '(':
      *ans = OBRACE;
      break;
    default:
      error = INPUT_ERROR;
      break;
  }
  return s;
}

void getIndexOp(char last_op, char *s, int *ans) {
  if (!last_op || *s == '+' || *s == '-') {
    switch (*s) {
      case '+':
        *ans = (last_op) ? UNPLUS : PLUS;
        break;
      case '-':
        *ans = (last_op) ? UNMINUS : MINUS;
        break;
      case '*':
        *ans = MULTIPLY;
        break;
      case '/':
        *ans = DIVISION;
        break;
      case '%':
        *ans = MODM;
        break;
      case '^':
        *ans = POWER;
        break;
      case 'd':
        *ans = MODM;
        break;
      default:
        error = INPUT_ERROR;
        break;
    }
  }
}

void fromStackToQueue(stack_n *stack, queue *q) {
  while (!error) {
    if (stack->size == 0) {
      break;
    }
    operation_t *elem = pop(stack);
    if (elem->sign == '(') {
      break;
    } else {
      pushOpToQueue(q, elem);
    }
  }
  if (stack->size >= 1) {
    if (is_func(stack->data[stack->size - 1]->sign)) {
      operation_t *elem = pop(stack);
      pushOpToQueue(q, elem);
    }
  }
}

void OpFromStackToQueue(stack_n *stack, queue *q, operation_t *op) {
  if (stack->size) {
    operation_t *elem = stack->data[stack->size - 1];
    while (!error && elem->priority >= op->priority && stack->size) {
      elem = pop(stack);
      pushOpToQueue(q, elem);
      if (stack->size) {
        elem = stack->data[stack->size - 1];
      }
    }
  }
  push(stack, op);
}

int isNum(char x) {
  int ans = 0;
  if (x >= 48 && x <= 57) {
    ans = 1;
  }
  return ans;
}

double countNotation(queue q) {
  stack_double stackD = {{0}, 0};
  for (int i = 0; !error && i < q.size; i++) {
    if (!q.data[i].op) {
      pushStackD(&stackD, q.data[i].num);
    } else {
      if (q.data[i].op->op_sgl) {
        double r = q.data[i].op->op_sgl(popStackD(&stackD));
        if (error || isnan(r) || isinf(r)) {
          error = INPUT_ERROR;
        } else {
          pushStackD(&stackD, r);
        }
      } else if (q.data[i].op->op) {
        double r1 = popStackD(&stackD);
        double r2 = popStackD(&stackD);
        double op = q.data[i].op->op(r2, r1);
        if (isnan(op) || isinf(op)) {
          error = INPUT_ERROR;
        } else {
          pushStackD(&stackD, op);
        }
      } else {
        error = INPUT_ERROR;
      }
    }
  }
  double ret = (!error) ? stackD.data[0] : 0;
  return ret;
}
