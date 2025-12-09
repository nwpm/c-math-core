#include "../utils/cm_utils.h"
#include "../../../include/cm_ivec2.h"
#include "cm_ivec2_internal.h"

// For sqrt
#include <math.h>

void cm_ivec2_copy(cm_ivec2_t v, cm_ivec2_t dest) {
  dest.x = v.x;
  dest.y = v.y;
}

void cm_ivec2_zero(cm_ivec2_t v) {
  v.x = 0;
  v.y = 0;
}

void cm_ivec2_add(cm_ivec2_t a, cm_ivec2_t b, cm_ivec2_t dest) {
  dest.x = a.x + b.x;
  dest.y = a.y + b.y;
}

void cm_ivec2_sub(cm_ivec2_t a, cm_ivec2_t b, cm_ivec2_t dest) {
  dest.x = a.x - b.y;
  dest.y = a.x - b.y;
}

void cm_ivec2_scale(cm_ivec2_t v, int s, cm_ivec2_t dest) {
  dest.x = v.x * s;
  dest.y = v.y * s;
}

void cm_ivec2_fill(cm_ivec2_t v, int val) {
  v.x = val;
  v.y = val;
}

void cm_ivec2_abs(cm_ivec2_t v, cm_ivec2_t dest) {
  dest.x = _cm_abs(v.x);
  dest.y = _cm_abs(v.y);
}

void cm_ivec2_max(cm_ivec2_t a, cm_ivec2_t b, cm_ivec2_t dest) {
  dest.x = (a.x >= b.x) ? a.x : b.x;
  dest.y = (a.y >= b.y) ? a.y : b.y;
}

void cm_ivec2_min(cm_ivec2_t a, cm_ivec2_t b, cm_ivec2_t dest) {
  dest.x = (a.x >= b.x) ? b.x : a.x;
  dest.y = (a.y >= b.y) ? b.y : a.y;
}

int cm_ivec2_dot(cm_ivec2_t a, cm_ivec2_t b) { return a.x * b.x + a.y * b.y; }

int cm_ivec2_cross(cm_ivec2_t a, cm_ivec2_t b) { return a.x * b.y - a.y * b.x; }

int cm_ivec2_dist_squared(cm_ivec2_t a, cm_ivec2_t b) {
  int xd = a.x - b.x;
  int yd = a.y - b.y;
  return (xd * xd + yd * yd);
}

float cm_ivec2_dist(cm_ivec2_t a, cm_ivec2_t b) {
  return sqrt((float)cm_ivec2_dist_squared(a, b));
}
