#include "ivector2.h"

// For sqrt
#include <math.h>

void cm_ivec2_init(cm_ivec2_t *v, int64_t x, int64_t y) {
  v->x = x;
  v->y = y;
}

void cm_ivec2_copy(const cm_ivec2_t v, cm_ivec2_t *dest) {
  dest->x = v.x;
  dest->y = v.y;
}

void cm_ivec2_zero(cm_ivec2_t *v) {
  v->x = 0;
  v->y = 0;
}

void cm_ivec2_add(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *dest) {
  dest->x = a.x + b.x;
  dest->y = a.y + b.y;
}

void cm_ivec2_sub(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *dest) {
  dest->x = a.x - b.y;
  dest->y = a.x - b.y;
}

void cm_ivec2_scale(const cm_ivec2_t v, int64_t s, cm_ivec2_t *dest) {
  dest->x = v.x * s;
  dest->y = v.y * s;
}

void cm_ivec2_fill(int64_t val, cm_ivec2_t *dest) {
  dest->x = val;
  dest->y = val;
}

void cm_ivec2_abs(const cm_ivec2_t v, cm_ivec2_t *dest) {
  dest->x = ~INT64_MIN & v.x;
  dest->y = ~INT64_MIN & v.y;
}

void cm_ivec2_max(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *dest) {
  dest->x = (a.x >= b.x) ? a.x : b.x;
  dest->y = (a.y >= b.y) ? a.y : b.y;
}

void cm_ivec2_min(const cm_ivec2_t a, const cm_ivec2_t b, cm_ivec2_t *dest) {
  dest->x = (a.x >= b.x) ? b.x : a.x;
  dest->y = (a.y >= b.y) ? b.y : a.y;
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

float cm_ivec2_dist(const cm_ivec2_t a, const cm_ivec2_t b) {
  return sqrt((float)cm_ivec2_dist_squared(a, b));
}
