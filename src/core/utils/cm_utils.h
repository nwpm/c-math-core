#ifndef CM_UTILS_H
#define CM_UTILS_H

#include "../../../include/cm_core/cm_types.h"
#include <stdbool.h>

#define CM_EPS 1.0e-20

static inline cm_real_t _cm_real_abs(cm_real_t x) {
  return x >= 0 ? x : -1. * x;
}
static inline long _cm_long_abs(long x) { return x >= 0 ? x : -1. * x; }
static inline long long _cm_llong_abs(long long x) {
  return x >= 0 ? x : -1. * x;
}
static inline int _cm_abs(int x) { return x >= 0 ? x : -1. * x; }

static inline bool _cm_real_equal(cm_real_t x, cm_real_t y) {
  return _cm_real_abs(x - y) < CM_EPS;
}

#endif
