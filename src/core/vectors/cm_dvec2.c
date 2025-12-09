#include "cm_dvec2_internal.h"
#include "../../../include/cm_dvec2.h"
#include <assert.h>
#include <math.h>

void cm_vec2_double_sum_inplace(cm_dvec2_t *vec_a,
                                const cm_dvec2_t *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
}

void cm_vec2_double_sub_inplace(cm_dvec2_t *vec_a,
                                const cm_dvec2_t *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
}

void cm_vec2_double_scale_inplace(cm_dvec2_t *vec, double scale) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  vec->x *= scale;
  vec->y *= scale;
}

cm_dvec2_t cm_vec2_double_sum(cm_dvec2_t vec_a, cm_dvec2_t vec_b) {
  return (cm_dvec2_t){vec_a.x + vec_b.x, vec_a.y + vec_b.y};
}

cm_dvec2_t cm_vec2_double_sub(cm_dvec2_t vec_a, cm_dvec2_t vec_b) {
  return (cm_dvec2_t){vec_a.x - vec_b.x, vec_a.y - vec_b.y};
}

cm_dvec2_t cm_vec2_double_scale(cm_dvec2_t vec, double scale) {
  return (cm_dvec2_t){vec.x * scale, vec.y * scale};
}

double cm_vec2_double_norm(cm_dvec2_t vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y);
}

double cm_vec2_double_norm_squared(cm_dvec2_t vec) {
  return vec.x * vec.x + vec.y * vec.y;
}

double cm_vec2_double_dot(cm_dvec2_t vec_a, cm_dvec2_t vec_b) {
  return vec_a.x * vec_b.x + vec_a.y * vec_b.y;
}

double cm_vec2_double_angle(cm_dvec2_t vec_a, cm_dvec2_t vec_b) {

  double norm_vec_a = cm_vec2_double_norm(vec_a);
  double norm_vec_b = cm_vec2_double_norm(vec_b);
  double dot_product = cm_vec2_double_dot(vec_a, vec_b);

  double angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

double cm_vec2_double_cross(cm_dvec2_t v1, cm_dvec2_t v2){
  return v1.x * v2.y - v1.y * v2.x;
}

cm_dvec2_t cm_vec2_double_project(cm_dvec2_t proj_from,
                                    cm_dvec2_t proj_to) {

  double dot_product = cm_vec2_double_dot(proj_from, proj_to);
  double len_vec_to = cm_vec2_double_norm_squared(proj_to);
  double scalar = dot_product / len_vec_to;

  return (cm_dvec2_t){proj_to.x * scalar, proj_to.y * scalar};
}

cm_dvec2_t cm_vec2_double_normalize(cm_dvec2_t vec) {

  double vec_norm = cm_vec2_double_norm(vec);
  return (cm_dvec2_t){vec.x / vec_norm, vec.y / vec_norm};
}

void cm_vec2_double_normalize_inplace(cm_dvec2_t *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double vec_norm = cm_vec2_double_norm(*vec);
  vec->x /= vec_norm;
  vec->y /= vec_norm;
}

bool cm_vec2_double_is_zero(const cm_dvec2_t vec) { return !vec.x && !vec.y; }

cm_dvec2_t cm_vec2_double_rotate(cm_dvec2_t vec, double angle) {
  double t_c = cos(angle);
  double t_s = sin(angle);
  return (cm_dvec2_t){vec.x * t_c - vec.y * t_s, vec.x * t_s + vec.y * t_c};
}

cm_dvec2_t cm_vec2_double_perp(cm_dvec2_t vec){
  return (cm_dvec2_t){(-vec.y * vec.y) / vec.x, vec.y};
}

void cm_vec2_double_rotate_inplace(cm_dvec2_t *vec, double angle) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double t_c = cos(angle);
  double t_s = sin(angle);
  vec->x = vec->x * t_c - vec->y * t_s;
  vec->y = vec->x * t_s + vec->y * t_c;
}

double cm_vec2_double_distance(cm_dvec2_t vec_a, cm_dvec2_t vec_b) {
  return cm_vec2_double_norm(cm_vec2_double_sub(vec_a, vec_b));
}

bool cm_vec2_double_is_equal(cm_dvec2_t vec_a, cm_dvec2_t vec_b) {
  return (vec_a.x == vec_b.x) && (vec_a.y == vec_b.y);
}
