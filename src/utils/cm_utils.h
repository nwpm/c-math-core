#ifndef CM_UTILS_H
#define CM_UTILS_H

#include <stdbool.h>

#define CM_EPS 1.0e-20

inline double _cm_double_abs(double x) { return x >= 0 ? x : -1. * x; }
inline bool _cm_double_equal(double x, double y) {
  return _cm_double_abs(x - y) < CM_EPS;
}

#endif
