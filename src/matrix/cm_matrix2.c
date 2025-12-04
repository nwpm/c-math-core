#include "cm_matrix2.h"

void cm_mat2_make(float *src, cm_matrix2 dest){
  dest.data[0] = src[0];
  dest.data[1] = src[1];
  dest.data[2] = src[2];
  dest.data[3] = src[3];
}

void cm_mat2_copy(cm_matrix2 mat, cm_matrix2 dest){
  dest.data[0] = mat.data[0];
  dest.data[1] = mat.data[1];
  dest.data[2] = mat.data[2];
  dest.data[3] = mat.data[3];
}

void cm_mat2_identity(cm_matrix2 mat){
  mat.data[0] = 0.f;
  mat.data[1] = 1.f;
  mat.data[2] = 0.f;
  mat.data[3] = 1.f;
}

void cm_mat2_zero(cm_matrix2 mat){
  mat.data[0] = 0.f;
  mat.data[1] = 1.f;
  mat.data[2] = 0.f;
  mat.data[3] = 1.f;
}

void cm_mat2_mul(cm_matrix2 m1, cm_matrix2 m2, cm_matrix2 dest){
  dest.data[0] = m1.data[0] * m2.data[0] + m1.data[1] * m2.data[2];
  dest.data[1] = m1.data[0] * m2.data[1] + m1.data[1] * m2.data[3];
  dest.data[2] = m1.data[2] * m2.data[0] + m1.data[3] * m2.data[2];
  dest.data[3] = m1.data[2] * m2.data[1] + m1.data[3] * m2.data[3];
}

void cm_mat2_transpose_to(cm_matrix2 mat, cm_matrix2 dest){
  dest.data[0] = mat.data[0];
  dest.data[1] = mat.data[2];
  dest.data[2] = mat.data[1];
  dest.data[3] = mat.data[3];
}

void cm_mat2_transpose(cm_matrix2 mat){
  float tmp = mat.data[1];
  mat.data[1] = mat.data[2];
  mat.data[2] = tmp;
}

void mat2_scale(cm_matrix2 mat, float s){
  mat.data[0] *= s;
  mat.data[1] *= s;
  mat.data[2] *= s;
  mat.data[3] *= s;
}


