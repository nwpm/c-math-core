#include "algebra.h"

float sml_absolute_value(float val) { return val > 0.0 ? val : (-1.0 * val); }

float _sml_pow(float val, float exp) {
  float result = val;
  for (int i = 1; i < exp; ++i) {
    result *= val;
  }
  return result;
}

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
