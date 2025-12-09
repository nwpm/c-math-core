#ifndef CM_UTILS_H
#define CM_UTILS_H

#include <stdbool.h>

#define CM_EPS 1.0e-20

static inline double _cm_double_abs(double x) { return x >= 0 ? x : -1. * x; }
static inline long _cm_long_abs(long x) { return x >= 0 ? x : -1. * x; }
static inline long long _cm_llong_abs(long long x) { return x >= 0 ? x : -1. * x; }
static inline int _cm_abs(int x) { return x >= 0 ? x : -1. * x; }

static inline bool _cm_double_equal(double x, double y) {
  return _cm_double_abs(x - y) < CM_EPS;
}

#endif
