#include "../../include/algebra/mc_algebra.h"

#include <stddef.h>

//////////////////// Auxiliary functions
float _sml_pow(float val, float exp) {
  float result = val;
  for (int i = 1; i < exp; ++i) {
    result *= val;
  }
  return result;
}

int _sml_greatest_value(int first, int second) {

  if ((first == second) || (first > second)) {
    return first;
  }

  return second;
}

int _sml_lesser_value(int first, int second) {

  if ((first == second) || (first > second)) {
    return second;
  }

  return first;
}

///////////////////

double mc_ipow_i(int base, int exp) {

  if (exp == 0) {
    return 1;
  }

  double result = 1;
  size_t mod_exp = mc_abs_i(exp);

  for (size_t i = 1; i <= mod_exp; ++i) {
    result *= base;
  }

  return (exp < 0) ? 1. / result : result;
}

/*
float mc_ipow_f(float base, int exp) { 
  return 0.f; 
}

double mc_ipow_d(double base, int exp) { 
  return 0.; 
}
*/

// More tests for lcm and gcd?
int sml_least_common_multiple(int first, int second) {

  // Add this block in sprt function
  if (first <= 0 || second <= 0) {
    return -1;
  } else if (first == second) {
    return first;
  }

  int gcd = sml_greatest_common_divisor(first, second);
  return (first * second) / gcd;
}

int sml_greatest_common_divisor(int first, int second) {

  // Add this block in sprt function
  if (first <= 0 || second <= 0) {
    return -1;
  } else if (first == second) {
    return first;
  }

  int greatest_val = _sml_greatest_value(first, second);
  int lesser_val = _sml_lesser_value(first, second);
  int division_result = 1;

  while (division_result) {
    division_result = greatest_val % lesser_val;
    greatest_val = lesser_val;
    lesser_val = division_result;
  }

  return greatest_val;
}
