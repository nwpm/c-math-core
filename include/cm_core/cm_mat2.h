#ifndef CM_MATRIX2_H
#define CM_MATRIX2_H

#include "cm_vec2.h"

typedef struct cm_mat2_t cm_mat2_t;

void cm_mat2_make(float *src, cm_mat2_t dest);
void cm_mat2_copy(cm_mat2_t mat, cm_mat2_t dest);
void cm_mat2_identity(cm_mat2_t mat);
void cm_mat2_zero(cm_mat2_t mat);

void cm_mat2_mul(cm_mat2_t m1, cm_mat2_t m2, cm_mat2_t dest);
void cm_mat2_transpose_to(cm_mat2_t mat, cm_mat2_t dest);
void cm_mat2_transpose(cm_mat2_t mat);
void cm_mat2_scale(cm_mat2_t mat, float s);

void cm_mat2_inv(cm_mat2_t mat, cm_mat2_t dest);
void cm_mat2_mulv(cm_mat2_t mat, cm_vec2_t v, cm_vec2_t dest);
void cm_mat2_swap_col(cm_mat2_t mat);
void cm_mat2_swap_row(cm_mat2_t mat);

float cm_mat2_det(cm_mat2_t mat);
float cm_mat2_trace(cm_mat2_t mat);
float cm_mat2_rmc(cm_vec2_t r, cm_mat2_t mat, cm_vec2_t c);

#endif
