#include "../../include/cmathcore/vector3.h"
#include "../utils/cm_utils.h"

#include <math.h>

void cm_vec3_init(cm_vec3_t *v, double x, double y, double z) {
  v->x = x;
  v->y = y;
  v->z = z;
}

void cm_vec3_copy(const cm_vec3_t src, cm_vec3_t *dest) {
  dest->x = src.x;
  dest->y = src.y;
  dest->z = src.z;
}

void cm_vec3_fill(cm_vec3_t *v, double val) {
  v->x = val;
  v->y = val;
  v->z = val;
}

void cm_vec3_set_zero(cm_vec3_t *v) {
  v->x = 0;
  v->y = 0;
  v->z = 0;
}

void cm_vec3_add(const cm_vec3_t a, const cm_vec3_t b, cm_vec3_t *res) {
  res->x = a.x + b.x;
  res->y = a.y + b.y;
  res->z = a.z + b.z;
}

void cm_vec3_sub(const cm_vec3_t a, const cm_vec3_t b, cm_vec3_t *res) {
  res->x = a.x - b.x;
  res->y = a.y - b.y;
  res->z = a.z - b.z;
}

void cm_vec3_scale(const cm_vec3_t v, double s, cm_vec3_t *res) {
  res->x = v.x * s;
  res->y = v.y * s;
  res->z = v.z * s;
}

void cm_vec3_abs(const cm_vec3_t v, cm_vec3_t *res) {
  res->x = (v.x < 0.) ? -v.x : v.x;
  res->y = (v.y < 0.) ? -v.y : v.y;
  res->z = (v.z < 0.) ? -v.z : v.z;
}

void cm_vec3_add_inplace(cm_vec3_t *a, const cm_vec3_t b) {
  a->x += b.x;
  a->y += b.y;
  a->z += b.z;
}

void cm_vec3_sub_inplace(cm_vec3_t *a, const cm_vec3_t b) {
  a->x -= b.x;
  a->y -= b.y;
  a->z -= b.z;
}

void cm_vec3_scale_inplace(cm_vec3_t *v, double s) {
  v->x *= s;
  v->y *= s;
  v->z *= s;
}

void cm_vec3_abs_inplace(cm_vec3_t *v) {
  v->x *= (v->x < 0.) ? -1. : 1.;
  v->y *= (v->y < 0.) ? -1. : 1.;
  v->z *= (v->z < 0.) ? -1. : 1.;
}

double cm_vec3_dot(const cm_vec3_t a, const cm_vec3_t b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double cm_vec3_dot_angle(const cm_vec3_t a, const cm_vec3_t b, double angle) {
  return cm_vec3_norm(a) * cm_vec3_norm(b) * cos(angle);
}

void cm_vec3_cross(const cm_vec3_t a, const cm_vec3_t b, cm_vec3_t *res) {
  res->x = a.y * b.z - a.z * b.y;
  res->y = -(a.x * b.z - a.z * b.x);
  res->z = a.x * b.y - a.y * b.x;
}

double cm_vec3_dist_squared(const cm_vec3_t a, const cm_vec3_t b) {
  double xd = a.x - b.x;
  double yd = a.y - b.y;
  double zd = a.z - b.z;
  return xd * xd + yd * yd + zd * zd;
}

double cm_vec3_dist(const cm_vec3_t a, const cm_vec3_t b) {
  return sqrt(cm_vec3_dist_squared(a, b));
}

void cm_vec3_normalize(const cm_vec3_t v, cm_vec3_t *res) {
  double vec_norm = cm_vec3_norm(v);
  res->x = v.x / vec_norm;
  res->y = v.y / vec_norm;
  res->z = v.z / vec_norm;
}

void cm_vec3_normalize_inplace(cm_vec3_t *v) {
  double vec_norm = cm_vec3_norm(*v);
  v->x /= vec_norm;
  v->y /= vec_norm;
  v->z /= vec_norm;
}

double cm_vec3_angle_between(const cm_vec3_t a, const cm_vec3_t b) {

  double dot = cm_vec3_dot(a, b);
  cm_vec3_t cross;
  cm_vec3_cross(a, b, &cross);
  double area = cm_vec3_norm(cross);

  return atan2(area, dot);
}

double cm_vec3_norm(const cm_vec3_t v) {
  return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double cm_vec3_norm_squared(const cm_vec3_t v) {
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

bool cm_vec3_is_zero(const cm_vec3_t v) {
  return _cm_double_is_equal(v.x, 0.) && _cm_double_is_equal(v.y, 0.) &&
         _cm_double_is_equal(v.z, 0.);
}

bool cm_vec3_is_equal(const cm_vec3_t a, const cm_vec3_t b) {
  return _cm_double_is_equal(a.x, b.x) && _cm_double_is_equal(a.y, b.y) &&
         _cm_double_is_equal(a.z, b.z);
}
