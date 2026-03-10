#include "../../include/cmathcore/numerical.h"
#include "../utils/utils.h"

double cm_lerp(double a, double b, double t) { 
  return a + t * (b - a);
}

double cm_sqrt(double x) {

  double eps = 1e-12;

  double x_0 = x / 2.;
  double x_1 = 0.;
  while (_cm_double_abs(x_1 * x_1 - x) > eps) {
    x_1 = (x_0 * x_0 + x) / (2 * x_0);
    x_0 = x_1;
  }

  return x_1;
}

double cm_rsqrt(double x) { return 1 / cm_sqrt(x); }
