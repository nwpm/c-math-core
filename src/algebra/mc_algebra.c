#include "../../include/algebra/mc_algebra.h"

#include <stdbool.h>
#include <stddef.h>

double mc_ipow_i(int base, int exp) {

  if (exp == 0) {
    return 1.;
  }

  double result = 1;
  size_t mod_exp = mc_abs_i(exp);

  for (size_t i = 1; i <= mod_exp; ++i) {
    result *= base;
  }

  return (exp < 0) ? 1. / result : result;
}

double mc_ipow_ll(long long base, int exp) {

  if (exp == 0) {
    return 1.;
  }

  double result = 1;
  size_t mod_exp = mc_abs_i(exp);

  for (size_t i = 1; i <= mod_exp; ++i) {
    result *= base;
  }

  return (exp < 0) ? 1. / result : result;
}

double mc_ipow_f(float base, int exp) {

  if (exp == 0) {
    return 1.;
  }

  double result = 1;
  size_t mod_exp = mc_abs_i(exp);

  for (size_t i = 1; i <= mod_exp; ++i) {
    result *= base;
  }

  return (exp < 0) ? 1. / result : result;
}

double mc_ipow_d(double base, int exp) {

  if (exp == 0) {
    return 1.;
  }

  double result = 1;
  size_t mod_exp = mc_abs_i(exp);

  for (size_t i = 1; i <= mod_exp; ++i) {
    result *= base;
  }

  return (exp < 0) ? 1. / result : result;
}

int mc_lcm_i(int n1, int n2) {

  int abs_n1 = mc_abs_i(n1);
  int abs_n2 = mc_abs_i(n2);

  if (abs_n1 == 0 && abs_n2 == 0) {
    return 0;
  }

  int gcd = mc_gcd_i(n1, n2);
  return (n1 * n2) / gcd;
}

long long mc_lcm_ll(long long n1, long long n2) {

  long long abs_n1 = mc_abs_ll(n1);
  long long abs_n2 = mc_abs_ll(n2);

  if (abs_n1 == 0ll && abs_n2 == 0ll) {
    return 0ll;
  }

  long long gcd = mc_gcd_ll(n1, n2);
  return (n1 * n2) / gcd;
}

int mc_gcd_i(int n1, int n2) {

  int abs_n1 = mc_abs_i(n1);
  int abs_n2 = mc_abs_i(n2);

  if (abs_n1 == 0 && abs_n2 == 0) {
    return 0;
  } else if (abs_n1 == 0) {
    return abs_n2;
  } else if (abs_n2 == 0) {
    return abs_n1;
  }

  int greater_num = (n1 >= n2) ? n1 : n2;
  int smaller_num = (n1 >= n2) ? n2 : n1;
  int div_result = 1;

  while (div_result) {
    div_result = greater_num % smaller_num;
    greater_num = smaller_num;
    smaller_num = div_result;
  }

  return greater_num;
}

long long mc_gcd_ll(long long n1, long long n2) {

  long long abs_n1 = mc_abs_ll(n1);
  long long abs_n2 = mc_abs_ll(n2);

  if (abs_n1 == 0ll && abs_n2 == 0ll) {
    return 0ll;
  } else if (abs_n1 == 0ll) {
    return abs_n2;
  } else if (abs_n2 == 0ll) {
    return abs_n1;
  }

  long long greater_num = (n1 >= n2) ? n1 : n2;
  long long smaller_num = (n1 >= n2) ? n2 : n1;
  long long div_result = 1;

  while (div_result) {
    div_result = greater_num % smaller_num;
    greater_num = smaller_num;
    smaller_num = div_result;
  }

  return greater_num;
}

float mc_fsum_ap(unsigned int start, unsigned int end, float n_start,
                 float n_end) {

  if (start > end) {
    return -1.f;
  }

  return ((n_start + n_end) / 2.f) * (end - start + 1.f);
}

double mc_dsum_ap(unsigned int start, unsigned int end, double n_start,
                  double n_end) {

  if (start > end) {
    return -1.;
  }

  return ((n_start + n_end) / 2.) * (end - start + 1.);
}
