#include "cm_vec3_double.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>

CmVec3Double *cm_vec3_double_alloc() {

  CmVec3Double *vec = malloc(sizeof(CmVec3Double));
  if (!vec)
    return NULL;

  return vec;
}

CmVec3Double *cm_vec3_double_init(double x, double y, double z) {

  CmVec3Double *vec = cm_vec3_double_alloc();
  if (!vec)
    return NULL;

  vec->x = x;
  vec->y = y;
  vec->z = z;

  return vec;
}

CmVec3Double *cm_vec3_double_create_from_vec(CmVec3Double *orig_vec) {

#ifdef CM_DEBUG
  assert(!orig_vec && "Vec is NULL");
#endif

  CmVec3Double *vec = cm_vec3_double_alloc();
  if (!vec)
    return NULL;

  vec->x = orig_vec->x;
  vec->y = orig_vec->y;
  vec->z = orig_vec->z;

  return vec;
}

void cm_vec3_double_free(CmVec3Double *vec) { free(vec); }

void cm_vec3_double_sum(CmVec3Double *vec_a, const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
  vec_a->z += vec_b->z;
}

void cm_vec3_double_sub(CmVec3Double *vec_a, const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
  vec_a->z -= vec_b->z;
}

void cm_vec3_double_scale(CmVec3Double *vec, double scale) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  vec->x *= scale;
  vec->y *= scale;
  vec->z *= scale;
}

double cm_vec3_double_norm(const CmVec3Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

double cm_vec3_double_norm_squared(const CmVec3Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  return vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;
}

double cm_vec3_double_dot(const CmVec3Double *vec_a,
                          const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  return vec_a->x * vec_b->x + vec_a->y * vec_b->y + vec_a->z * vec_b->z;
}

double cm_vec3_double_angle(const CmVec3Double *vec_a,
                            const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  double norm_vec_a = cm_vec3_double_norm(vec_a);
  double norm_vec_b = cm_vec3_double_norm(vec_b);
  double dot_product = cm_vec3_double_dot(vec_a, vec_b);

  double angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

CmVec3Double *cm_vec3_double_project(const CmVec3Double *proj_from,
                                     const CmVec3Double *proj_to) {

#ifdef CM_DEBUG
  assert(!proj_from && "proj_from is NULL");
  assert(!proj_to && "proj_to is NULL");
#endif

  CmVec3Double *res = cm_vec3_double_alloc();
  if (!res)
    return NULL;

  double dot_product = cm_vec3_double_dot(proj_from, proj_to);
  double len_vec_to = cm_vec3_double_norm_squared(proj_to);
  double scalar = dot_product / len_vec_to;

  cm_vec3_double_scale(res, scalar);

  return res;
}

CmVec3Double *cm_vec3_double_normalize(const CmVec3Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double vec_norm = cm_vec3_double_norm(vec);

  CmVec3Double *normalized = cm_vec3_double_init(
      vec->x / vec_norm, vec->y / vec_norm, vec->z / vec_norm);
  if (!normalized)
    return NULL;

  return normalized;
}

void cm_vec3_double_normalize_inplace(CmVec3Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  double vec_norm = cm_vec3_double_norm(vec);
  cm_vec3_double_scale(vec, 1. / vec_norm);
}

CmVec3Double *cm_vec3_double_cross(const CmVec3Double *vec_a,
                                   const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  CmVec3Double *res_vec = cm_vec3_double_alloc();
  if (!res_vec)
    return NULL;

  double det_x = (vec_a->y * vec_b->z) - (vec_a->z * vec_b->y);
  double det_y = -((vec_a->x * vec_b->z) - (vec_a->z * vec_b->x));
  double det_z = (vec_a->x * vec_b->y) - (vec_a->y * vec_b->x);

  res_vec->x = det_x;
  res_vec->y = det_y;
  res_vec->z = det_z;

  return res_vec;
}

bool cm_vec3_double_is_null(const CmVec3Double *vec) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  return !vec->x && !vec->y && !vec->z;
}

bool cm_vec3_double_is_equal(const CmVec3Double *vec_a,
                             const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  return (vec_a->x == vec_b->x) && (vec_a->y == vec_b->y) &&
         (vec_a->z == vec_b->z);
}
