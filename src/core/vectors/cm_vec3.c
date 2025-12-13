#include "../../../include/cm_core/cm_vec3.h"
#include "../utils/cm_utils.h"
#include "cm_vec3_internal.h"
#include <math.h>

void cm_vec3_copy(cm_vec3_t v, cm_vec3_t dest) {
  dest.x = v.x;
  dest.y = v.y;
  dest.z = v.z;
}

void cm_vec3_zero(cm_vec3_t v) {
  v.x = 0;
  v.y = 0;
  v.z = 0;
}

void cm_vec3_add(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest) {
  dest.x = a.x + b.x;
  dest.y = a.y + b.y;
  dest.z = a.z + b.z;
}

void cm_vec3_sub(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest) {
  dest.x = a.x - b.y;
  dest.y = a.x - b.y;
  dest.z = a.z - b.z;
}

void cm_vec3_scale(cm_vec3_t v, cm_real_t s, cm_vec3_t dest) {
  dest.x = v.x * s;
  dest.y = v.y * s;
  dest.z = v.z * s;
}

void cm_vec3_fill(cm_vec3_t v, cm_real_t val) {
  v.x = val;
  v.y = val;
  v.z = val;
}

// NOTE: maybe change _cm_abs to std abs?
void cm_vec3_abs(cm_vec3_t v, cm_vec3_t dest) {
  dest.x = _cm_abs(v.x);
  dest.y = _cm_abs(v.y);
}

void cm_vec3_max(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest) {
  dest.x = (a.x >= b.x) ? a.x : b.x;
  dest.y = (a.y >= b.y) ? a.y : b.y;
  dest.z = (a.z >= b.z) ? a.z : b.z;
}

void cm_vec3_min(cm_vec3_t a, cm_vec3_t b, cm_vec3_t dest) {
  dest.x = (a.x >= b.x) ? b.x : a.x;
  dest.y = (a.y >= b.y) ? b.y : a.y;
  dest.z = (a.z >= b.z) ? b.z : a.z;
}

// NOTE: counterclockwise axis rotation, right-hand space
void cm_vec3_rotate_x(cm_vec3_t vec, cm_real_t angle, cm_vec3_t dest) {
  cm_real_t t_s = sin(angle);
  cm_real_t t_c = cos(angle);

  dest.x = vec.x;
  dest.y = vec.y * t_c - vec.z * t_s;
  dest.z = vec.y * t_s + vec.z * t_c;
}

void cm_vec3_rotate_y(cm_vec3_t vec, cm_real_t angle, cm_vec3_t dest) {
  cm_real_t t_s = sin(angle);
  cm_real_t t_c = cos(angle);

  dest.x = vec.x * t_c + vec.z * t_s;
  dest.y = vec.y;
  dest.z = -vec.x * t_s + vec.z * t_c;
}

void cm_vec3_rotate_z(cm_vec3_t vec, cm_real_t angle, cm_vec3_t dest) {
  cm_real_t t_s = sin(angle);
  cm_real_t t_c = cos(angle);

  dest.x = vec.x * t_c - vec.y * t_s;
  dest.y = vec.x * t_s + vec.y * t_c;
  dest.z = vec.z;
}

void cm_vec3_normalize(cm_vec3_t vec, cm_vec3_t dest) {

  cm_real_t vec_norm = cm_vec3_norm(vec);
  dest.x /= vec_norm;
  dest.y /= vec_norm;
  dest.z /= vec_norm;
}

cm_real_t cm_vec3_norm(cm_vec3_t vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

cm_real_t cm_vec3_norm_squared(cm_vec3_t vec) {
  return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

cm_real_t cm_vec3_dist_squared(cm_vec3_t a, cm_vec3_t b) {
  cm_real_t xd = a.x - b.x;
  cm_real_t yd = a.y - b.y;
  cm_real_t zd = a.z - b.z;
  return (xd * xd + yd * yd + zd * zd);
}

cm_real_t cm_vec3_dist(cm_vec3_t a, cm_vec3_t b) {
  return sqrt(cm_vec3_dist_squared(a, b));
}

cm_real_t cm_vec3_dot(cm_vec3_t vec_a, cm_vec3_t vec_b) {
  return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}

cm_real_t cm_vec3_angle(cm_vec3_t vec_a, cm_vec3_t vec_b) {

  cm_real_t norm_vec_a = cm_vec3_norm(vec_a);
  cm_real_t norm_vec_b = cm_vec3_norm(vec_b);
  cm_real_t dot_product = cm_vec3_dot(vec_a, vec_b);

  cm_real_t angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

void cm_vec3_project(cm_vec3_t proj_from, cm_vec3_t proj_to, cm_vec3_t dest) {

  cm_real_t dot_product = cm_vec3_dot(proj_from, proj_to);
  cm_real_t len_vec_to = cm_vec3_norm_squared(proj_to);
  cm_real_t scalar = dot_product / len_vec_to;

  dest.x = proj_to.x * scalar;
  dest.y = proj_to.y * scalar;
  dest.z = proj_to.z * scalar;
}

void cm_vec3_cross(cm_vec3_t vec_a, cm_vec3_t vec_b, cm_vec3_t dest) {

  cm_real_t det_x = (vec_a.y * vec_b.z) - (vec_a.z * vec_b.y);
  cm_real_t det_y = -((vec_a.x * vec_b.z) - (vec_a.z * vec_b.x));
  cm_real_t det_z = (vec_a.x * vec_b.y) - (vec_a.y * vec_b.x);

  dest.x = det_x;
  dest.y = det_y;
  dest.z = det_z;
}

bool cm_vec3_is_zero(cm_vec3_t vec) { return !vec.x && !vec.y && !vec.z; }

bool cm_vec3_is_equal(cm_vec3_t vec_a, cm_vec3_t vec_b) {
  return (vec_a.x == vec_b.x) && (vec_a.y == vec_b.y) && (vec_a.z == vec_b.z);
}
