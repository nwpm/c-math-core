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

// TODO: Hide struct
typedef struct CmVec2Double {
  double x;
  double y;
} CmVec2Double;

/* Allocation */
CmVec2Double *cm_vec2_double_alloc();
CmVec2Double *cm_vec2_double_init(double x, double y);
CmVec2Double *cm_vec2_double_create_from_vec(CmVec2Double *orig_vec);

void cm_vec2_double_free(CmVec2Double *vec);

/* Operations */
void cm_vec2_double_sum(CmVec2Double *vec_a, const CmVec2Double *vec_b);
void cm_vec2_double_sub(CmVec2Double *vec_a, const CmVec2Double *vec_b);
void cm_vec2_double_scale(CmVec2Double *vec, double scale);
double cm_vec2_double_norm(const CmVec2Double *vec);
double cm_vec2_double_dot(const CmVec2Double *vec_a, const CmVec2Double *vec_b);

/* Normalize */
CmVec2Double *cm_vec2_double_normalize(const CmVec2Double *vec);

/* Setter */
static inline void cm_vec2_double_set_x(CmVec2Double *vec, double x_val){
  vec->x = x_val;
}

static inline void cm_vec2_double_set_y(CmVec2Double *vec, double y_val){
  vec->x = y_val;
}

/* Getter */
static inline double cm_vec2_double_get_x(CmVec2Double *vec){
  return vec->x;
}

static inline double cm_vec2_double_get_y(CmVec2Double *vec){
  return vec->y;
}

#endif
