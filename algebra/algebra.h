#ifndef ALGEBRA_H
#define ALGEBRA_H

/*Find absolute value of number*/
float sml_absolute_value(float val);

/*Square root function*/
float sml_sqrt(float val);

/*sml_pow for now find only integral exponents*/
float sml_pow(float val, int exp);

typedef struct equation_solution {
  float first_root = 0.f;
  float second_root = 0.f;
  int has_real_solution = 1;
} equation_solution;

/*Calculate quadratic equation*/
equation_solution sml_quadrtc_equation(float a, float b, float c);

/*Square root*/
float sml_decimal_pow(float num, float pow);

#endif
