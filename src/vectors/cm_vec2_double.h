#ifndef CM_Vec2_DOUBLE_H
#define CM_Vec2_DOUBLE_H

typedef enum CmVec2Code {

  CM_SUCCESS = 0,
  CM_FAIL,
  CM_ERR_NULL_POINTER,
  CM_ERR_SIZE_MISMATCH,
  CM_ERR_ALLOC_FAILED,
  CM_ERR_INVALID_SIZE,
  CM_ERR_INVALID_ARGUMENT,

} CmMatrixCode;

typedef struct CmVec2Double {
  double x;
  double y;
  double z;
} CmVec2Double;

void cm_Vec2_double_sum(const CmVec2Double *vec_a, const CmVec2Double *vec_b);
void cm_Vec2_double_sub(const CmVec2Double *vec_a, const CmVec2Double *vec_b);
void cm_Vec2_double_scale(CmVec2Double *vec, double scale);
double cm_Vec2_double_norm(const CmVec2Double *vec);
double cm_Vec2_double_dot(const CmVec2Double *vec_a, const CmVec2Double *vec_b);
CmVec2Double *cm_Vec2_double_normalize(const CmVec2Double *vec);

#endif
