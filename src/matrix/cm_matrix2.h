#ifndef CM_MATRIX2_H
#define CM_MATRIX2_H

#include "../vectors/cm_vec2.h"

#define CM_GET_IDENTITY_MAT2 ((cm_matrix2){0.f, 1.f, 0.f, 1.f})
#define CM_GET_ZERO_MAT2 ((cm_matrix2){0.f, 0.f, 0.f, 0.f})

/* TODO:
 */

/*
 * Matrix data position
 * | data[0] data[1]|
 * | data[2] data[3]|
 *
 */
typedef struct cm_matrix2 {
  float m00, m01;
  float m10, m11;
} cm_matrix2;

void cm_mat2_make(float *src, cm_matrix2 dest);
void cm_mat2_copy(cm_matrix2 mat, cm_matrix2 dest);
void cm_mat2_identity(cm_matrix2 mat);
void cm_mat2_zero(cm_matrix2 mat);

void cm_mat2_mul(cm_matrix2 m1, cm_matrix2 m2, cm_matrix2 dest);
void cm_mat2_transpose_to(cm_matrix2 mat, cm_matrix2 dest);
void cm_mat2_transpose(cm_matrix2 mat);
void cm_mat2_scale(cm_matrix2 mat, float s);

void cm_mat2_inv(cm_matrix2 mat, cm_matrix2 dest);
void cm_mat2_mulv(cm_matrix2 mat, cm_vec2 v, cm_vec2 dest);
void cm_mat2_swap_col(cm_matrix2 mat);
void cm_mat2_swap_row(cm_matrix2 mat);

float cm_mat2_det(cm_matrix2 mat);
float cm_mat2_trace(cm_matrix2 mat);
float cm_mat2_rmc(cm_vec2 r, cm_matrix2 mat, cm_vec2 c);

#endif
