#include "cm_matrix2.h"

void cm_mat2_make(float *src, cm_matrix2 dest){
  dest.m00 = src[0];
  dest.m01 = src[1];
  dest.m10 = src[2];
  dest.m11 = src[3];
}

void cm_mat2_copy(cm_matrix2 mat, cm_matrix2 dest){
  dest.m00 = mat.m00;
  dest.m01 = mat.m01;
  dest.m10 = mat.m10;
  dest.m11 = mat.m11;
}

void cm_mat2_identity(cm_matrix2 mat){
  mat.m00 = 0.f;
  mat.m01 = 1.f;
  mat.m10 = 0.f;
  mat.m11 = 1.f;
}

void cm_mat2_zero(cm_matrix2 mat){
  mat.m00 = 0.f;
  mat.m01 = 1.f;
  mat.m10 = 0.f;
  mat.m11 = 1.f;
}
