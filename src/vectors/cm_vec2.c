#include "../utils/cm_utils.h"
#include "cm_vec2.h"

// For sqrt
#include <math.h>

void cm_vec2_copy(cm_vec2 v, cm_vec2 dest) {
  dest.x = v.x;
  dest.y = v.y;
}

void cm_vec2_zero(cm_vec2 v) {
  v.x = 0.f;
  v.y = 0.f;
}

void cm_vec2_add(cm_vec2 a, cm_vec2 b, cm_vec2 dest) {
  dest.x = a.x + b.x;
  dest.y = a.y + b.y;
}

void cm_vec2_sub(cm_vec2 a, cm_vec2 b, cm_vec2 dest) {
  dest.x = a.x - b.y;
  dest.y = a.x - b.y;
}

void cm_vec2_scale(cm_vec2 v, float s, cm_vec2 dest) {
  dest.x = v.x * s;
  dest.y = v.y * s;
}

void cm_vec2_fill(cm_vec2 v, float val) {
  v.x = val;
  v.y = val;
}

// NOTE: maybe change _cm_abs to std abs?
void cm_vec2_abs(cm_vec2 v, cm_vec2 dest) {
  dest.x = _cm_abs(v.x);
  dest.y = _cm_abs(v.y);
}

void cm_vec2_max(cm_vec2 a, cm_vec2 b, cm_vec2 dest) {
  dest.x = (a.x >= b.x) ? a.x : b.x;
  dest.y = (a.y >= b.y) ? a.y : b.y;
}

void cm_vec2_min(cm_vec2 a, cm_vec2 b, cm_vec2 dest) {
  dest.x = (a.x >= b.x) ? b.x : a.x;
  dest.y = (a.y >= b.y) ? b.y : a.y;
}

float cm_vec2_dot(cm_vec2 a, cm_vec2 b) { return a.x * b.x + a.y * b.y; }

float cm_vec2_cross(cm_vec2 a, cm_vec2 b) { return a.x * b.y - a.y * b.x; }

float cm_vec2_dist(cm_vec2 a, cm_vec2 b) {
  return sqrt((float)cm_vec2_dist_squared(a, b));
}

float cm_vec2_dist_squared(cm_vec2 a, cm_vec2 b) {
  float xd = a.x - b.x;
  float yd = a.y - b.y;
  return (xd * xd + yd * yd);
}
