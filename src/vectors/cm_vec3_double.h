#ifndef CM_VEC3_DOUBLE_H
#define CM_VEC3_DOUBLE_H

typedef enum CmVec3Code {

  CM_SUCCESS = 0,
  CM_FAIL,
  CM_ERR_NULL_POINTER,
  CM_ERR_SIZE_MISMATCH,
  CM_ERR_ALLOC_FAILED,
  CM_ERR_INVALID_SIZE,
  CM_ERR_INVALID_ARGUMENT,

} CmMatrixCode;

typedef struct CmVec3Double {
  double x;
  double y;
  double z;
} CmVec3Double;

void cm_vec3_double_sum(const CmVec3Double *vec_a, const CmVec3Double *vec_b);
void cm_vec3_double_sub(const CmVec3Double *vec_a, const CmVec3Double *vec_b);
void cm_vec3_double_scale(CmVec3Double *vec, double scale);
double cm_vec3_double_norm(const CmVec3Double *vec);
double cm_vec3_double_dot(const CmVec3Double *vec_a, const CmVec3Double *vec_b);
CmVec3Double *cm_vec3_double_normalize(const CmVec3Double *vec);

#endif
