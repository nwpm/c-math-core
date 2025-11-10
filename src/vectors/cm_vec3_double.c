#include "cm_vec3_double.h"
#include <assert.h>
#include <math.h>

void cm_vec3_double_sum_inplace(CmVec3Double *vec_a,
                                const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
  vec_a->z += vec_b->z;
}

void cm_vec3_double_sub_inplace(CmVec3Double *vec_a,
                                const CmVec3Double *vec_b) {

#ifdef CM_DEBUG
  assert(!vec_a && "Vec_a is NULL");
  assert(!vec_b && "Vec_b is NULL");
#endif

  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
  vec_a->z -= vec_b->z;
}

void cm_vec3_double_scale_inplace(CmVec3Double *vec, double scale) {

#ifdef CM_DEBUG
  assert(!vec && "Vec is NULL");
#endif

  vec->x *= scale;
  vec->y *= scale;
  vec->z *= scale;
}

CmVec3Double cm_vec3_double_sum(CmVec3Double vec_a, CmVec3Double vec_b) {
  return (CmVec3Double){vec_a.x + vec_b.x, vec_a.y + vec_b.y,
                        vec_a.z + vec_b.z};
}

CmVec3Double cm_vec3_double_sub(CmVec3Double vec_a, CmVec3Double vec_b) {
  return (CmVec3Double){vec_a.x - vec_b.x, vec_a.y - vec_b.y,
                        vec_a.z - vec_b.z};
}

CmVec3Double cm_vec3_double_scale(CmVec3Double vec, double scale) {
  return (CmVec3Double){vec.x * scale, vec.y * scale, vec.z * scale};
}

double cm_vec3_double_norm(CmVec3Double vec) {
  return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double cm_vec3_double_norm_squared(CmVec3Double vec) {
  return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

double cm_vec3_double_distance(CmVec3Double vec_a, CmVec3Double vec_b) {
  return cm_vec3_double_norm(cm_vec3_double_sub(vec_a, vec_b));
}

double cm_vec3_double_dot(CmVec3Double vec_a, CmVec3Double vec_b) {
  return vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z;
}

double cm_vec3_double_angle(CmVec3Double vec_a, CmVec3Double vec_b) {

  double norm_vec_a = cm_vec3_double_norm(vec_a);
  double norm_vec_b = cm_vec3_double_norm(vec_b);
  double dot_product = cm_vec3_double_dot(vec_a, vec_b);

  double angle = dot_product / (norm_vec_a * norm_vec_b);

  return acos(angle);
}

CmVec3Double cm_vec3_double_project(CmVec3Double proj_from,
                                    CmVec3Double proj_to) {
  double dot_product = cm_vec3_double_dot(proj_from, proj_to);
  double len_vec_to = cm_vec3_double_norm_squared(proj_to);
  double scalar = dot_product / len_vec_to;

  return (CmVec3Double){proj_to.x * scalar, proj_to.y * scalar};
}

CmVec3Double cm_vec3_double_normalize(CmVec3Double vec) {

  double vec_norm = cm_vec3_double_norm(vec);
  return (CmVec3Double){vec.x / vec_norm, vec.y / vec_norm, vec.z / vec_norm};
}

void cm_vec3_double_normalize_inplace(CmVec3Double vec) {

  double vec_norm = cm_vec3_double_norm(vec);

  vec.x /= vec_norm;
  vec.y /= vec_norm;
  vec.z /= vec_norm;
}

CmVec3Double cm_vec3_double_rotate(CmVec3Double vec, double angle) {
  return (CmVec3Double){};
}

CmVec3Double cm_vec3_double_cross(CmVec3Double vec_a, CmVec3Double vec_b) {

  double det_x = (vec_a.y * vec_b.z) - (vec_a.z * vec_b.y);
  double det_y = -((vec_a.x * vec_b.z) - (vec_a.z * vec_b.x));
  double det_z = (vec_a.x * vec_b.y) - (vec_a.y * vec_b.x);

  return (CmVec3Double){det_x, det_y, det_z};
}

bool cm_vec3_double_is_zero(CmVec3Double vec) {
  return !vec.x && !vec.y && !vec.z;
}

bool cm_vec3_double_is_equal(CmVec3Double vec_a, CmVec3Double vec_b) {
  return (vec_a.x == vec_b.x) && (vec_a.y == vec_b.y) && (vec_a.z == vec_b.z);
}
