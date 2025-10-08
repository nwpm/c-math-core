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

// TODO: Hide struct
typedef struct CmVec3Double {
  double x;
  double y;
  double z;
} CmVec3Double;

/* Allocation */
CmVec3Double *cm_vec3_double_alloc();
CmVec3Double *cm_vec3_double_init(double x, double y, double z);
CmVec3Double *cm_vec3_double_create_from_vec(CmVec3Double *orig_vec);

void cm_vec3_double_free(CmVec3Double *vec);

/* Operations */
void cm_vec3_double_sum(CmVec3Double *vec_a, const CmVec3Double *vec_b);
void cm_vec3_double_sub(CmVec3Double *vec_a, const CmVec3Double *vec_b);
void cm_vec3_double_scale(CmVec3Double *vec, double scale);
double cm_vec3_double_norm(const CmVec3Double *vec);
double cm_vec3_double_dot(const CmVec3Double *vec_a, const CmVec3Double *vec_b);

/* Normalize */
CmVec3Double *cm_vec3_double_normalize(const CmVec3Double *vec);

/* Setter */
static inline void cm_vec3_double_set_x(CmVec3Double *vec, double x_val) {
  vec->x = x_val;
}

static inline void cm_vec3_double_set_y(CmVec3Double *vec, double y_val) {
  vec->y = y_val;
}

static inline void cm_vec3_double_set_z(CmVec3Double *vec, double z_val) {
  vec->z = z_val;
}

/* Getter */
static inline double cm_vec3_double_get_x(CmVec3Double *vec) { return vec->x; }

static inline double cm_vec3_double_get_y(CmVec3Double *vec) { return vec->y; }

static inline double cm_vec3_double_get_z(CmVec3Double *vec) { return vec->z; }

#endif
