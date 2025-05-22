#ifndef MC_ALGEBRA_H
#define MC_ALGEBRA_H

static inline int mc_abs_i(int val) { return val > 0 ? val : -val; }
static inline float mc_abs_f(float val) { return val > 0.f ? val : -val; }
static inline double mc_abs_d(double val) { return val > 0. ? val : -val; }

double mc_ipow_i(int base, int exp);
double mc_ipow_f(float base, int exp);
double mc_ipow_d(double base, int exp);

int sml_least_common_divisor(int first, int second);
int sml_greatest_common_divisor(int first, int second);

#endif // MC_ALGEBRA_H
