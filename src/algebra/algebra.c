#include "algebra.h"

float sml_absolute_value(float val) { return val > 0.0 ? val : (-1.0 * val); }

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

float sml_pow(float val, int exp) {

  if (exp == 0) {
    return 0.f;
  }

  int abs_exp = sml_absolute_value(exp);
  float result = _sml_pow(val, abs_exp);

  if (exp < 0) {
    result = 1.f / result;
  }

  return result;
}

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

// 0.f and 0.f gave -0 result
float sml_distance(float first, float second) {
  float result = sml_absolute_value(first - second);
  return result;
}
