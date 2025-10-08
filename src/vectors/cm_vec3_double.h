#ifndef CM_VEC3_DOUBLE_H
#define CM_VEC3_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

// TODO: forward declarations from err codes
#include "../utils/cm_err_codes.h"

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
CmStatusCode cm_vec3_double_sum(CmVec3Double *vec_a, const CmVec3Double *vec_b);
CmStatusCode cm_vec3_double_sub(CmVec3Double *vec_a, const CmVec3Double *vec_b);
CmStatusCode cm_vec3_double_scale(CmVec3Double *vec, double scale);

CmStatusCode cm_vec3_double_dot(const CmVec3Double *vec_a,
                                const CmVec3Double *vec_b, double *dot_res);
CmStatusCode cm_vec3_double_angle(const CmVec3Double *vec_a,
                                  const CmVec3Double *vec_b, double *angle);

bool cm_vec3_double_is_null(const CmVec3Double *vec);
bool cm_vec3_double_is_equal(const CmVec3Double *vec_a,
                             const CmVec3Double *vec_b);

CmVec3Double *cm_vec3_double_perpendicular(const CmVec3Double *vec);
CmVec3Double *cm_vec3_double_rotate(const CmVec3Double *vec, double angle);
CmVec3Double *cm_vec3_double_cross(const CmVec3Double *vec_a,
                                   const CmVec3Double *vec_b);

/* Norm */
CmStatusCode cm_vec3_double_norm(const CmVec3Double *vec, double *norm_res);
CmStatusCode cm_vec3_double_norm_squared(const CmVec3Double *vec, double *norm_res);
double cm_vec3_double_distance(const CmVec3Double *vec_a,
                               const CmVec3Double *vec_b);

/* Normalize */
CmVec3Double *cm_vec3_double_normalize(const CmVec3Double *vec);

/* Project */
CmVec3Double *cm_vec3_double_project(const CmVec3Double *proj_from,
                                     const CmVec3Double *proj_to);

/* Reflect */
CmVec3Double *cm_vec3_double_reflect(const CmVec3Double *vec);

/* Lerp */
CmVec3Double *cm_vec3_double_lerp(const CmVec3Double *start,
                                  const CmVec3Double *end, double t);

/* Setter */
static inline void cm_vec3_double_set_x(CmVec3Double *vec, double x_val) {
  vec->x = x_val;
}

static inline void cm_vec3_double_set_y(CmVec3Double *vec, double y_val) {
  vec->y = y_val;
}

/* Getter */
static inline double cm_vec3_double_get_x(CmVec3Double *vec) { return vec->x; }

static inline double cm_vec3_double_get_y(CmVec3Double *vec) { return vec->y; }

#endif
