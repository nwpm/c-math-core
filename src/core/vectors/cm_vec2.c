#include "../../../include/cm_core/cm_vec2.h"
#include "../utils/cm_utils.h"
#include "cm_vec2_internal.h"

// For sqrt
#include <math.h>

void cm_vec2_copy(cm_vec2_t v, cm_vec2_t dest) {
  dest.x = v.x;
  dest.y = v.y;
}

void cm_vec2_zero(cm_vec2_t v) {
  v.x = 0.f;
  v.y = 0.f;
}

void cm_vec2_add(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest) {
  dest.x = a.x + b.x;
  dest.y = a.y + b.y;
}

void cm_vec2_sub(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest) {
  dest.x = a.x - b.y;
  dest.y = a.x - b.y;
}

void cm_vec2_scale(cm_vec2_t v, cm_real_t s, cm_vec2_t dest) {
  dest.x = v.x * s;
  dest.y = v.y * s;
}

void cm_vec2_fill(cm_vec2_t v, cm_real_t val) {
  v.x = val;
  v.y = val;
}

// NOTE: maybe change _cm_abs to std abs?
void cm_vec2_abs(cm_vec2_t v, cm_vec2_t dest) {
  dest.x = _cm_abs(v.x);
  dest.y = _cm_abs(v.y);
}

void cm_vec2_max(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest) {
  dest.x = (a.x >= b.x) ? a.x : b.x;
  dest.y = (a.y >= b.y) ? a.y : b.y;
}

void cm_vec2_min(cm_vec2_t a, cm_vec2_t b, cm_vec2_t dest) {
  dest.x = (a.x >= b.x) ? b.x : a.x;
  dest.y = (a.y >= b.y) ? b.y : a.y;
}

void cm_vec2_rotate(cm_vec2_t vec, cm_real_t angle, cm_vec2_t dest) {
  cm_real_t t_c = cos(angle);
  cm_real_t t_s = sin(angle);
  dest.x = vec.x * t_c - vec.y * t_s;
  dest.y = vec.x * t_s + vec.y * t_c;
}

void cm_vec2_normalize(cm_vec2_t vec, cm_vec2_t dest) {
  cm_real_t vec_norm = cm_vec2_norm(vec);
  dest.x /= vec_norm;
  dest.y /= vec_norm;
}

void cm_vec2_perp(cm_vec2_t vec, cm_vec2_t dest) {
  dest.x = (-vec.y * vec.y) / vec.x;
  dest.y = vec.y;
}

void cm_vec2_project(cm_vec2_t proj_from, cm_vec2_t proj_to, cm_vec2_t dest) {

  cm_real_t dot_product = cm_vec2_dot(proj_from, proj_to);
  cm_real_t len_vec_to = cm_vec2_norm_squared(proj_to);
  cm_real_t scalar = dot_product / len_vec_to;

  dest.x = proj_to.x * scalar;
  dest.y = proj_to.y * scalar;
}

cm_real_t cm_vec2_norm(cm_vec2_t vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y);
}

cm_real_t cm_vec2_norm_squared(cm_vec2_t vec) {
  return vec.x * vec.x + vec.y * vec.y;
}

cm_real_t cm_vec2_angle(cm_vec2_t vec_a, cm_vec2_t vec_b) {

  cm_real_t norm_vec_a = cm_vec2_norm(vec_a);
  cm_real_t norm_vec_b = cm_vec2_norm(vec_b);
  cm_real_t dot_product = cm_vec2_dot(vec_a, vec_b);

  cm_real_t angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

cm_real_t cm_vec2_dot(cm_vec2_t a, cm_vec2_t b) { return a.x * b.x + a.y * b.y; }

cm_real_t cm_vec2_cross(cm_vec2_t a, cm_vec2_t b) { return a.x * b.y - a.y * b.x; }

cm_real_t cm_vec2_dist_squared(cm_vec2_t a, cm_vec2_t b) {
  cm_real_t xd = a.x - b.x;
  cm_real_t yd = a.y - b.y;
  return (xd * xd + yd * yd);
}

cm_real_t cm_vec2_dist(cm_vec2_t a, cm_vec2_t b) {
  return sqrt((cm_real_t)cm_vec2_dist_squared(a, b));
}

bool cm_vec2_is_equal(cm_vec2_t vec_a, cm_vec2_t vec_b) {
  return (vec_a.x == vec_b.x) && (vec_a.y == vec_b.y);
}

bool cm_vec2_is_zero(const cm_vec2_t vec) { return !vec.x && !vec.y; }
