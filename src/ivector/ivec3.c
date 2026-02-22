#include "../../include/cmathcore/ivector3.h"

void cm_ivec3_init(cm_ivec3_t *v, int64_t x, int64_t y, int64_t z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

void cm_ivec3_copy(const cm_ivec3_t v, cm_ivec3_t *dest) {
  dest->x = v.x;
  dest->y = v.y;
  dest->z = v.z;
}

void cm_ivec3_fill(cm_ivec3_t *v, int64_t val) {
  v->x = val;
  v->y = val;
  v->z = val;
}

void cm_ivec3_set_zero(cm_ivec3_t *v) {
  v->x = 0;
  v->y = 0;
  v->z = 0;
}

void cm_ivec3_add(const cm_ivec3_t a, const cm_ivec3_t b, cm_ivec3_t *res) {
  res->x = a.x + b.x;
  res->y = a.y + b.y;
  res->z = a.z + b.z;
}

void cm_ivec3_sub(const cm_ivec3_t a, const cm_ivec3_t b, cm_ivec3_t *res) {
  res->x = a.x - b.x;
  res->y = a.y - b.y;
  res->z = a.z - b.z;
}

void cm_ivec3_scale(const cm_ivec3_t v, int64_t s, cm_ivec3_t *res) {
  res->x = v.x * s;
  res->y = v.y * s;
  res->z = v.z * s;
}

void cm_ivec3_abs(const cm_ivec3_t v, cm_ivec3_t *res) {
  res->x = (v.x == INT64_MIN) ? INT64_MIN : ((v.x < 0) ? -v.x : v.x);
  res->y = (v.y == INT64_MIN) ? INT64_MIN : ((v.y < 0) ? -v.y : v.y);
  res->z = (v.z == INT64_MIN) ? INT64_MIN : ((v.z < 0) ? -v.z : v.z);
}

void cm_ivec3_add_inplace(cm_ivec3_t *a, const cm_ivec3_t b) {
  a->x += b.x;
  a->y += b.y;
  a->z += b.z;
}

void cm_ivec3_sub_inplace(cm_ivec3_t *a, const cm_ivec3_t b) {
  a->x -= b.x;
  a->y -= b.y;
  a->z -= b.z;
}

void cm_ivec3_scale_inplace(cm_ivec3_t *v, int64_t s) {
  v->x *= s;
  v->y *= s;
  v->z *= s;
}

void cm_ivec3_abs_inplace(cm_ivec3_t *v) {
  v->x = (v->x == INT64_MIN) ? INT64_MIN : ((v->x < 0) ? -v->x : v->x);
  v->y = (v->y == INT64_MIN) ? INT64_MIN : ((v->y < 0) ? -v->y : v->y);
  v->z = (v->z == INT64_MIN) ? INT64_MIN : ((v->z < 0) ? -v->z : v->z);
}

int64_t cm_ivec3_dot(const cm_ivec3_t a, const cm_ivec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

void cm_ivec3_cross(const cm_ivec3_t a, const cm_ivec3_t b, cm_ivec3_t *res) {
  res->x = a.y * b.z - a.z * b.y;
  res->y = -(a.x * b.z - a.z * b.x);
  res->z = a.x * b.y - a.y * b.x;
}

int64_t cm_ivec3_dist_squared(const cm_ivec3_t a, const cm_ivec3_t b) {
  int64_t xd = a.x - b.x;
  int64_t yd = a.y - b.y;
  int64_t zd = a.z - b.z;
  return (xd * xd + yd * yd + zd * zd);
}
