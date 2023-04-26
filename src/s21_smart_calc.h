#ifndef SRC_S21_SMART_CALC_H
#define SRC_S21_SMART_CALC_H

#define MAX_SIZE_STACK 255

// operation_t cmp[] = {{'+', 8, plus, NULL}};

#define is_func(c)                                                       \
  ((c) == 'l' || (c) == 'n' || (c) == 'a' || (c) == 'o' || (c) == 'i' || \
   (c) == 's' || (c) == 'c' || (c) == 't' || (c) == 'q')

typedef struct {
  char sign;
  int priority;
  double (*op)(double, double);
  double (*op_sgl)(double);
} operation_t;

typedef struct {
  double num;
  operation_t *op;
} data_t;

typedef struct stack {
  operation_t *data[MAX_SIZE_STACK];
  int size;
} stack_n;

typedef struct {
  data_t data[MAX_SIZE_STACK];
  int size;
} queue;

typedef struct {
  double data[MAX_SIZE_STACK];
  int size;
} stack_double;

enum name_of_op {
  PLUS,
  MINUS,
  MULTIPLY,
  DIVISION,
  MODM,
  POWER,
  LOGM,
  LNM,
  ATANM,
  ACOSM,
  ASINM,
  SINM,
  COSM,
  TANM,
  SQRTM,
  UNPLUS,
  UNMINUS,
  OBRACE,
  ERROR
};

extern int error;
enum type_of_error { OK, TOO_LONG_LINE, INPUT_ERROR, TOO_SHORT_LINE };

double toPostfix(char *intfixStr);

#endif
