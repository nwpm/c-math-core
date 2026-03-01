#include "../../include/cmathcore/vector2.h"
#include "../utils/cm_utils.h"

#include <math.h>

void cm_vec2_init(cm_vec2_t *v, double x, double y) {
  v->x = x;
  v->y = y;
}

void cm_vec2_copy(const cm_vec2_t src, cm_vec2_t *dest) {
  dest->x = src.x;
  dest->y = src.y;
}

void cm_vec2_fill(cm_vec2_t *v, double val) {
  v->x = val;
  v->y = val;
}

void cm_vec2_set_zero(cm_vec2_t *v) {
  v->x = 0;
  v->y = 0;
}

void cm_vec2_add(const cm_vec2_t a, const cm_vec2_t b, cm_vec2_t *res) {
  res->x = a.x + b.x;
  res->y = a.y + b.y;
}

void cm_vec2_sub(const cm_vec2_t a, const cm_vec2_t b, cm_vec2_t *res) {
  res->x = a.x - b.x;
  res->y = a.y - b.y;
}

void cm_vec2_scale(const cm_vec2_t v, double s, cm_vec2_t *res) {
  res->x = v.x * s;
  res->y = v.y * s;
}

void cm_vec2_abs(const cm_vec2_t v, cm_vec2_t *res) {
  res->x = (v.x < 0.) ? -v.x : v.x;
  res->y = (v.y < 0.) ? -v.y : v.y;
}

void cm_vec2_add_inplace(cm_vec2_t *a, const cm_vec2_t b) {
  a->x += b.x;
  a->y += b.y;
}

void cm_vec2_sub_inplace(cm_vec2_t *a, const cm_vec2_t b) {
  a->x -= b.x;
  a->y -= b.y;
}

void cm_vec2_scale_inplace(cm_vec2_t *v, double s) {
  v->x *= s;
  v->y *= s;
}

void cm_vec2_abs_inplace(cm_vec2_t *v) {
  v->x *= (v->x < 0.) ? -1. : 1.;
  v->y *= (v->y < 0.) ? -1. : 1.;
}

double cm_vec2_dot(const cm_vec2_t a, const cm_vec2_t b) {
  return a.x * b.x + a.y * b.y;
}

double cm_vec2_dot_angle(const cm_vec2_t a, const cm_vec2_t b, double angle) {
  return sqrt(cm_vec2_norm_squared(a) * cm_vec2_norm_squared(b)) * cos(angle);
}

double cm_vec2_cross(const cm_vec2_t a, const cm_vec2_t b) {
  return a.x * b.y - a.y * b.x;
}

double cm_vec2_dist_squared(const cm_vec2_t a, const cm_vec2_t b) {
  double xd = a.x - b.x;
  double yd = a.y - b.y;
  return xd * xd + yd * yd;
}

double cm_vec2_dist(const cm_vec2_t a, const cm_vec2_t b) {
  return sqrt(cm_vec2_dist_squared(a, b));
}

void cm_vec2_normalize(const cm_vec2_t v, cm_vec2_t *res) {
  double vec_norm = cm_vec2_norm(v);
  res->x = v.x / vec_norm;
  res->y = v.y / vec_norm;
}

void cm_vec2_normalize_inplace(cm_vec2_t *v) {
  double vec_norm = cm_vec2_norm(*v);
  v->x /= vec_norm;
  v->y /= vec_norm;
}

double cm_vec2_angle_between(const cm_vec2_t a, const cm_vec2_t b) {

  double dot = cm_vec2_dot(a, b);
  double det = cm_vec2_cross(a, b);

  return atan2(det, dot);
}

double cm_vec2_norm(const cm_vec2_t v) { return sqrt(v.x * v.x + v.y * v.y); }

double cm_vec2_norm_squared(const cm_vec2_t v) { return v.x * v.x + v.y * v.y; }

bool cm_vec2_is_zero(const cm_vec2_t v) {
  return _cm_double_is_equal(v.x, 0.) && _cm_double_is_equal(v.y, 0.);
}

bool cm_vec2_is_equal(const cm_vec2_t a, const cm_vec2_t b) {
  return _cm_double_is_equal(a.x, b.x) && _cm_double_is_equal(a.y, b.y);
}
