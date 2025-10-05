#include "cm_vec2_double.h"
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
  vec_a->x += vec_b->x;
  vec_a->y += vec_b->y;
}

void cm_vec2_double_sub(CmVec2Double *vec_a, const CmVec2Double *vec_b) {
  vec_a->x -= vec_b->x;
  vec_a->y -= vec_b->y;
}

void cm_vec2_double_scale(CmVec2Double *vec, double scale) {
  vec->x *= scale;
  vec->y *= scale;
}

double cm_vec2_double_norm(const CmVec2Double *vec) {
  return sqrt(vec->x * vec->x + vec->y * vec->y);
}

double cm_vec2_double_dot(const CmVec2Double *vec_a,
                          const CmVec2Double *vec_b) {
  return vec_a->x * vec_b->x + vec_a->y * vec_b->y;
}

CmVec2Double *cm_vec2_double_normalize(const CmVec2Double *vec) {

  double vec_norm = cm_vec2_double_norm(vec);

  CmVec2Double *normalized =
      cm_vec2_double_init(vec->x / vec_norm, vec->y / vec_norm);
  if (!normalized)
    return NULL;

  return normalized;
}

