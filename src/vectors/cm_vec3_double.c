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

double cm_vec3_double_norm(const CmVec3Double *vec) {
  return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

CmStatusCode cm_vec3_double_dot(const CmVec3Double *vec_a,
                                const CmVec3Double *vec_b, double *res) {
  CM_CHECK_NULL(vec_a);
  CM_CHECK_NULL(vec_b);
  CM_CHECK_NULL(res);

  *res = vec_a->x * vec_b->x + vec_a->y * vec_b->y + vec_a->z * vec_b->z;

  return CM_SUCCESS;
}

CmVec3Double *cm_vec3_double_normalize(const CmVec3Double *vec) {

  double vec_norm = cm_vec3_double_norm(vec);

  CmVec3Double *normalized = cm_vec3_double_init(
      vec->x / vec_norm, vec->y / vec_norm, vec->z / vec_norm);
  if (!normalized)
    return NULL;

  return normalized;
}
