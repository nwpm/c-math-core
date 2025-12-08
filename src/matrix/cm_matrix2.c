#include "cm_matrix2_internal.h"

void cm_mat2_make(float *src, cm_matrix2 dest) {
  dest.m00 = src[0];
  dest.m01 = src[1];
  dest.m10 = src[2];
  dest.m11 = src[3];
}

void cm_mat2_copy(cm_matrix2 mat, cm_matrix2 dest) {
  dest.m00 = mat.m00;
  dest.m01 = mat.m01;
  dest.m10 = mat.m10;
  dest.m11 = mat.m11;
}

void cm_mat2_identity(cm_matrix2 mat) {
  mat.m00 = 0.f;
  mat.m01 = 1.f;
  mat.m10 = 0.f;
  mat.m11 = 1.f;
}

void cm_mat2_zero(cm_matrix2 mat) {
  mat.m00 = 0.f;
  mat.m01 = 1.f;
  mat.m10 = 0.f;
  mat.m11 = 1.f;
}

void cm_mat2_mul(cm_matrix2 m1, cm_matrix2 m2, cm_matrix2 dest) {
  dest.m00 = m1.m00 * m2.m00 + m1.m01 * m2.m10;
  dest.m01 = m1.m00 * m2.m01 + m1.m01 * m2.m11;
  dest.m10 = m1.m10 * m2.m00 + m1.m11 * m2.m10;
  dest.m11 = m1.m10 * m2.m01 + m1.m11 * m2.m11;
}

void cm_mat2_transpose_to(cm_matrix2 mat, cm_matrix2 dest) {
  dest.m00 = mat.m00;
  dest.m01 = mat.m10;
  dest.m10 = mat.m01;
  dest.m11 = mat.m11;
}

void cm_mat2_transpose(cm_matrix2 mat) {
  float tmp = mat.m01;
  mat.m01 = mat.m10;
  mat.m10 = tmp;
}

void cm_mat2_scale(cm_matrix2 mat, float s) {
  mat.m00 *= s;
  mat.m01 *= s;
  mat.m10 *= s;
  mat.m11 *= s;
}

float cm_mat2_det(cm_matrix2 mat) {
  return mat.m00 * mat.m11 - mat.m10 * mat.m01;
}

void cm_mat2_inv(cm_matrix2 mat, cm_matrix2 dest) {
  float s = 1.f / cm_mat2_det(mat);
  dest.m00 = mat.m11;
  dest.m01 = -mat.m01;
  dest.m10 = -mat.m10;
  dest.m11 = mat.m01;
  cm_mat2_scale(dest, s);
}

void cm_mat2_swap_col(cm_matrix2 mat) {
  float tmp = mat.m00;
  mat.m00 = mat.m01;
  mat.m01 = tmp;

  tmp = mat.m10;
  mat.m10 = mat.m11;
  mat.m11 = tmp;
}

void cm_mat2_swap_row(cm_matrix2 mat) {
  float tmp = mat.m00;
  mat.m00 = mat.m10;
  mat.m10 = tmp;

  tmp = mat.m01;
  mat.m01 = mat.m11;
  mat.m11 = tmp;
}

float cm_mat2_trace(cm_matrix2 mat) { return mat.m00 + mat.m11; }

void cm_mat2_mulv(cm_matrix2 mat, cm_vec2 v, cm_vec2 dest) {
  dest.x = mat.m00 * v.x + mat.m01 * v.y;
  dest.y = mat.m10 * v.x + mat.m11 * v.y;
}

float mat2_rmc(cm_vec2 r, cm_matrix2 mat, cm_vec2 c) {
  cm_vec2 v = {mat.m00 * r.x + mat.m10 * r.y, mat.m01 * r.x + mat.m11 * r.y};
  return v.x * c.x + v.y * c.y;
}
