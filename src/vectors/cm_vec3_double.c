#include "cm_vec3_double.h"
#include "../utils/cm_checkers.h"
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

  CmVec3Double *vec = cm_vec3_double_alloc();
  if (!vec)
    return NULL;

  vec->x = orig_vec->x;
  vec->y = orig_vec->y;
  vec->z = orig_vec->z;

  return vec;
}

void cm_vec3_double_free(CmVec3Double *vec) { free(vec); }

CmStatusCode cm_vec3_double_sum(CmVec3Double *vec_a,
                                const CmVec3Double *vec_b) {
  CM_CHECK_NULL(vec_a);
  CM_CHECK_NULL(vec_b);

  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
  vec_a->z += vec_b->z;

  return CM_SUCCESS;
}

CmStatusCode cm_vec3_double_sub(CmVec3Double *vec_a,
                                const CmVec3Double *vec_b) {
  CM_CHECK_NULL(vec_a);
  CM_CHECK_NULL(vec_b);

  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
  vec_a->z -= vec_b->z;

  return CM_SUCCESS;
}

CmStatusCode cm_vec3_double_scale(CmVec3Double *vec, double scale) {

  CM_CHECK_NULL(vec);

  vec->x *= scale;
  vec->y *= scale;
  vec->z *= scale;

  return CM_SUCCESS;
}

CmStatusCode cm_vec3_double_norm(const CmVec3Double *vec, double *norm_res) {

  CM_CHECK_NULL(vec);
  CM_CHECK_NULL(norm_res);

  *norm_res = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);

  return CM_SUCCESS;
}

CmStatusCode cm_vec3_double_norm_squared(const CmVec3Double *vec,
                                         double *norm_res) {

  CM_CHECK_NULL(vec);
  CM_CHECK_NULL(norm_res);

  *norm_res = vec->x * vec->x + vec->y * vec->y + vec->z * vec->z;

  return CM_SUCCESS;
}

CmStatusCode cm_vec3_double_dot(const CmVec3Double *vec_a,
                                const CmVec3Double *vec_b, double *norm_res) {
  CM_CHECK_NULL(vec_a);
  CM_CHECK_NULL(vec_b);
  CM_CHECK_NULL(norm_res);

  *norm_res = vec_a->x * vec_b->x + vec_a->y * vec_b->y + vec_a->z * vec_b->z;

  return CM_SUCCESS;
}

CmStatusCode cm_vec3_double_angle(const CmVec3Double *vec_a,
                                  const CmVec3Double *vec_b, double *angle) {

  CM_CHECK_NULL(vec_a);
  CM_CHECK_NULL(vec_b);
  CM_CHECK_NULL(angle);

  double dot_product = 0.;
  double norm_vec_a = 0.;
  double norm_vec_b = 0.;
  cm_vec3_double_norm(vec_a, &norm_vec_a);
  cm_vec3_double_norm(vec_b, &norm_vec_b);
  cm_vec3_double_dot(vec_a, vec_b, &dot_product);

  *angle = dot_product / (norm_vec_a * norm_vec_b);
  *angle = acos(*angle);

  return CM_SUCCESS;
}

CmVec3Double *cm_vec3_double_project(const CmVec3Double *proj_from,
                                     const CmVec3Double *proj_to) {

  CmVec3Double *res = cm_vec3_double_alloc();
  if (!res)
    return NULL;

  double dot_product = 0.;
  double len_vec_to = 0.;
  cm_vec3_double_norm_squared(proj_to, &len_vec_to);
  cm_vec3_double_dot(proj_from, proj_to, &dot_product);

  double scalar = dot_product / len_vec_to;

  cm_vec3_double_scale(res, scalar);

  return res;
}

CmVec3Double *cm_vec3_double_normalize(const CmVec3Double *vec) {

  if (!vec)
    return NULL;

  double vec_norm = 0.;
  cm_vec3_double_norm(vec, &vec_norm);

  CmVec3Double *normalized = cm_vec3_double_init(
      vec->x / vec_norm, vec->y / vec_norm, vec->z / vec_norm);
  if (!normalized)
    return NULL;

  return normalized;
}

CmStatusCode cm_vec3_double_normalize_inplace(CmVec3Double *vec) {

  CM_CHECK_NULL(vec);

  double vec_norm = 0.;
  cm_vec3_double_norm(vec, &vec_norm);
  cm_vec3_double_scale(vec, 1. / vec_norm);

  return CM_SUCCESS;
}

CmVec3Double *cm_vec3_double_cross(const CmVec3Double *vec_a,
                                   const CmVec3Double *vec_b) {

  if (!vec_a || !vec_b)
    return NULL;

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

  if (!vec)
    return false;

  return !vec->x && !vec->y && !vec->z;
}

bool cm_vec3_double_is_equal(const CmVec3Double *vec_a,
                             const CmVec3Double *vec_b) {
  if (!vec_a || !vec_b)
    return false;

  return (vec_a->x == vec_b->x) && (vec_a->y == vec_b->y) &&
         (vec_a->z == vec_b->z);
}
