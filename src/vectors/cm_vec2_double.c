#include "cm_vec2_double.h"
#include <assert.h>
#include <math.h>

void cm_vec2_double_sum_inplace(CmVec2Double *vec_a,
                                const CmVec2Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
}

void cm_vec2_double_sub_inplace(CmVec2Double *vec_a,
                                const CmVec2Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
}

void cm_vec2_double_scale_inplace(CmVec2Double *vec, double scale) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  vec->x *= scale;
  vec->y *= scale;
}

CmVec2Double cm_vec2_double_sum(CmVec2Double vec_a, CmVec2Double vec_b) {
  return (CmVec2Double){vec_a.x + vec_b.x, vec_a.y + vec_b.y};
}

CmVec2Double cm_vec2_double_sub(CmVec2Double vec_a, CmVec2Double vec_b) {
  return (CmVec2Double){vec_a.x - vec_b.x, vec_a.y - vec_b.y};
}

CmVec2Double cm_vec2_double_scale(CmVec2Double vec, double scale) {
  return (CmVec2Double){vec.x * scale, vec.y * scale};
}

double cm_vec2_double_norm(CmVec2Double vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double cm_vec2_double_norm_squared(CmVec2Double vec) {
  return vec.x * vec.x + vec.y * vec.y;
}

double cm_vec2_double_dot(CmVec2Double vec_a, CmVec2Double vec_b) {
  return vec_a.x * vec_b.x + vec_a.y * vec_b.y;
}

double cm_vec2_double_angle(CmVec2Double vec_a, CmVec2Double vec_b) {

  double norm_vec_a = cm_vec2_double_norm(vec_a);
  double norm_vec_b = cm_vec2_double_norm(vec_b);
  double dot_product = cm_vec2_double_dot(vec_a, vec_b);

  double angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

CmVec2Double cm_vec2_double_project(CmVec2Double proj_from,
                                    CmVec2Double proj_to) {

  double dot_product = cm_vec2_double_dot(proj_from, proj_to);
  double len_vec_to = cm_vec2_double_norm_squared(proj_to);
  double scalar = dot_product / len_vec_to;

  return (CmVec2Double){proj_to.x * scalar, proj_to.y * scalar};
}

CmVec2Double cm_vec2_double_normalize(CmVec2Double vec) {

  double vec_norm = cm_vec2_double_norm(vec);
  return (CmVec2Double){vec.x / vec_norm, vec.y / vec_norm};
}

void cm_vec2_double_normalize_inplace(CmVec2Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double vec_norm = cm_vec2_double_norm(*vec);
  vec->x /= vec_norm;
  vec->y /= vec_norm;
}

bool cm_vec2_double_is_zero(const CmVec2Double vec) { return !vec.x && !vec.y; }

CmVec2Double cm_vec2_double_rotate(CmVec2Double vec, double angle) {
  double t_c = cos(angle);
  double t_s = sin(angle);
  return (CmVec2Double){vec.x * t_c - vec.y * t_s, vec.x * t_s + vec.y * t_c};
}

void cm_vec2_double_rotate_inplace(CmVec2Double *vec, double angle) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double t_c = cos(angle);
  double t_s = sin(angle);
  vec->x = vec->x * t_c - vec->y * t_s;
  vec->y = vec->x * t_s + vec->y * t_c;
}

double cm_vec2_double_distance(CmVec2Double vec_a, CmVec2Double vec_b) {
  return cm_vec2_double_norm(cm_vec2_double_sub(vec_a, vec_b));
}

bool cm_vec2_double_is_equal(CmVec2Double vec_a, CmVec2Double vec_b) {
  return (vec_a.x == vec_b.x) && (vec_a.y == vec_b.y);
}
