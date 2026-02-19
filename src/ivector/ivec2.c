#include "../../include/cmathcore/ivector2.h"
#include <math.h>

void cm_ivec2_init(cm_ivec2_t *v, int64_t x, int64_t y) {
  v->x = x;
  v->y = y;
}

void cm_ivec2_copy(const cm_ivec2_t src, cm_ivec2_t *dest) {
  dest->x = src.x;
  dest->y = src.y;
}

void cm_ivec2_fill(cm_ivec2_t *res, int64_t val) {
  res->x = val;
  res->y = val;
}

void cm_ivec2_set_zero(cm_ivec2_t *v) {
  v->x = 0;
  v->y = 0;
}

void cm_ivec2_add(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *res) {
  res->x = a.x + b.x;
  res->y = a.y + b.y;
}

void cm_ivec2_sub(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *res) {
  res->x = a.x - b.x;
  res->y = a.y - b.y;
}

void cm_ivec2_scale(const cm_ivec2_t v, int64_t s, cm_ivec2_t *res) {
  res->x = v.x * s;
  res->y = v.y * s;
}

void cm_ivec2_abs(const cm_ivec2_t v, cm_ivec2_t *res) {
  res->x = (v.x == INT64_MIN) ? INT64_MIN : ((v.x < 0) ? -v.x : v.x);
  res->y = (v.y == INT64_MIN) ? INT64_MIN : ((v.y < 0) ? -v.y : v.y);
}

void cm_ivec2_add_inplace(cm_ivec2_t *a, const cm_ivec2_t b) {
  a->x += b.x;
  a->y += b.y;
}

void cm_ivec2_sub_inplace(cm_ivec2_t *a, const cm_ivec2_t b) {
  a->x -= b.x;
  a->y -= b.y;
}

void cm_ivec2_scale_inplace(cm_ivec2_t *v, int64_t s) {
  v->x *= s;
  v->y *= s;
}

void cm_ivec2_abs_inplace(cm_ivec2_t *v) {
  v->x = (v->x == INT64_MIN) ? INT64_MIN : ((v->x < 0) ? -v->x : v->x);
  v->y = (v->y == INT64_MIN) ? INT64_MIN : ((v->y < 0) ? -v->y : v->y);
}

int64_t cm_ivec2_dot(const cm_ivec2_t a, const cm_ivec2_t b) {
  return a.x * b.x + a.y * b.y;
}

int64_t cm_ivec2_cross(const cm_ivec2_t a, const cm_ivec2_t b) {
  return a.x * b.y - a.y * b.x;
}

int64_t cm_ivec2_dist_squared(const cm_ivec2_t a, const cm_ivec2_t b) {
  int64_t xd = a.x - b.x;
  int64_t yd = a.y - b.y;
  return (xd * xd + yd * yd);
}
