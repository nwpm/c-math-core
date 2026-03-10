#ifndef CM_NUMERICAL_H
#define CM_NUMERICAL_H

#include "constants.h"

#include <stdbool.h>
#include <stddef.h>

static inline double cm_abs(double x) { return x >= 0 ? x : -x; }
static inline double cm_sign(double x) { return x >= 0 ? 1 : -1; }
static inline double cm_clamp(double x, double min, double max) {
  return (x < min) ? min : ((x > max) ? max : x);
}
static inline double cm_min(double x, double y) { return x > y ? y : x; }
static inline double cm_max(double x, double y) { return x > y ? x : y; }
static inline double cm_deg2rad(double deg) { return (CM_PI * deg) / 180; };
static inline double cm_rad2deg(double rad) { return (180 * rad) / CM_PI; };

double cm_lerp(double a, double b, double t);
double cm_sqrt(double x);
double cm_rsqrt(double x);

double cm_sin(double x);
double cm_cos(double x);
double cm_tan(double x);
double cm_cot(double x);
double cm_sec(double x);
double cm_csc(double x);
double cm_asin(double x);
double cm_acos(double x);
double cm_atan(double x);
double cm_acot(double x);
double cm_atan2(double y, double x);

double cm_safe_div(double a, double b, double fallback);
double cm_finite_diff(double (*f)(double), double x, double h);
double cm_integrate_trap(double (*f)(double), double a, double b, size_t n);
double cm_integrate_simpson(double (*f)(double), double a, double b, size_t n);
double cm_root_bisection(double (*f)(double), double a, double b, double eps);
double cm_root_newton(double (*f)(double), double (*fprime)(double), double x0,
                      double eps, size_t max_iter);
double cm_smoothstep(double edge0, double edge1, double x);
double cm_step(double edge, double x);

double cm_exp(double x);
double cm_log(double x);
double cm_log10(double x);
double cm_pow(double x, double y);

bool cm_is_zero(double x, double eps);
bool cm_is_equal(double a, double b, double eps);

#endif
