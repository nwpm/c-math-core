#ifndef CM_MATRIX2_INTERNAL_H
#define CM_MATRIX2_INTERNAL_H

#define CM_GET_IDENTITY_MAT2 ((cm_mat2_t){0.f, 1.f, 0.f, 1.f})
#define CM_GET_ZERO_MAT2 ((cm_mat2_t){0.f, 0.f, 0.f, 0.f})

/* TODO:
 */

/*
 * Matrix data position
 * | data[0] data[1]|
 * | data[2] data[3]|
 *
 */
typedef struct cm_mat2_t {
  float m00, m01;
  float m10, m11;
} cm_mat2_t;


#endif
