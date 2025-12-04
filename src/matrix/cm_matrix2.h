#ifndef CM_MATRIX2_H
#define CM_MATRIX2_H

#define CM_GET_IDENTITY_MAT2 ((cm_matrix2){0.f, 1.f, 0.f, 1.f})
#define CM_GET_ZERO_MAT2 ((cm_matrix2){0.f, 0.f, 0.f, 0.f})

/* TODO:
   void  mat2_identity_array(mat2 * restrict mats, size_t count)
   void  mat2_mul(mat2 m1, mat2 m2, mat2 dest)
   void  mat2_mulv(mat2 m, vec2 v, vec2 dest)
   void  mat2_transpose_to(mat2 mat, mat2 dest)
   void  mat2_transpose(mat2 m)
   void  mat2_scale(mat2 m, float s)
   void  mat2_inv(mat2 mat, mat2 dest)
   void  mat2_swap_col(mat2 mat, int col1, int col2)
   void  mat2_swap_row(mat2 mat, int row1, int row2)
   float mat2_det(mat2 m)
   float mat2_trace(mat2 m)
   float mat2_rmc(vec2 r, mat2 m, vec2 c)
*/

typedef struct cm_matrix2 {

  float m00, m01;
  float m10, m11;

} cm_matrix2;

void cm_mat2_make(float *src, cm_matrix2 dest);
void cm_mat2_copy(cm_matrix2 mat, cm_matrix2 dest);
void cm_mat2_identity(cm_matrix2 mat);
void cm_mat2_zero(cm_matrix2 mat);

#endif
