#include "cm_vec2_double.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

CmVec2Double *cm_vec2_double_alloc() {

  CmVec2Double *vec = malloc(sizeof(CmVec2Double));
  if (!vec)
    return NULL;

  return vec;
}

CmVec2Double *cm_vec2_double_init(double x, double y) {

  CmVec2Double *vec = cm_vec2_double_alloc();
  if (!vec)
    return NULL;

  vec->x = x;
  vec->y = y;

  return vec;
}

CmVec2Double *cm_vec2_double_create_from_vec(CmVec2Double *orig_vec) {

  CmVec2Double *vec = cm_vec2_double_alloc();
  if (!vec)
    return NULL;

  vec->x = orig_vec->x;
  vec->y = orig_vec->y;

  return vec;
}

void cm_vec2_double_free(CmVec2Double *vec) { free(vec); }

void cm_vec2_double_sum(CmVec2Double *vec_a, const CmVec2Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
}

void cm_vec2_double_sub(CmVec2Double *vec_a, const CmVec2Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
}

void cm_vec2_double_scale(CmVec2Double *vec, double scale) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  vec->x *= scale;
  vec->y *= scale;
}

double cm_vec2_double_norm(const CmVec2Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  return sqrt(vec->x * vec->x + vec->y * vec->y);
}

double cm_vec2_double_norm_squared(const CmVec2Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  return vec->x * vec->x + vec->y * vec->y;
}

double cm_vec2_double_dot(const CmVec2Double *vec_a,
                          const CmVec2Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  return vec_a->x * vec_b->x + vec_a->y * vec_b->y;
}

double cm_vec2_double_angle(const CmVec2Double *vec_a,
                            const CmVec2Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  double norm_vec_a = cm_vec2_double_norm(vec_a);
  double norm_vec_b = cm_vec2_double_norm(vec_b);
  double dot_product = cm_vec2_double_dot(vec_a, vec_b);

  double angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

CmVec2Double *cm_vec2_double_project(const CmVec2Double *proj_from,
                                     const CmVec2Double *proj_to) {

#ifdef CM_DEBUG
  assert(!proj_from && "proj_from is NULL");
  assert(!proj_to && "proj_to is NULL");
#endif

  CmVec2Double *res = cm_vec2_double_alloc();
  if (!res)
    return NULL;

  double dot_product = cm_vec2_double_dot(proj_from, proj_to);
  double len_vec_to = cm_vec2_double_norm_squared(proj_to);

  double scalar = dot_product / len_vec_to;
  cm_vec2_double_scale(res, scalar);

  return res;
}

CmVec2Double *cm_vec2_double_normalize(const CmVec2Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double vec_norm = cm_vec2_double_norm(vec);

  CmVec2Double *normalized =
      cm_vec2_double_init(vec->x / vec_norm, vec->y / vec_norm);
  if (!normalized)
    return NULL;

  return normalized;
}

void cm_vec2_double_normalize_inplace(CmVec2Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double vec_norm = cm_vec2_double_norm(vec);
  cm_vec2_double_scale(vec, 1. / vec_norm);
}

bool cm_vec2_double_is_null(const CmVec2Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  return !vec->x && !vec->y;
}

bool cm_vec2_double_is_equal(const CmVec2Double *vec_a,
                             const CmVec2Double *vec_b) {
#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif
  return (vec_a->x == vec_b->x) && (vec_a->y == vec_b->y);
}
