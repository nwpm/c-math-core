#ifndef CM_VEC3_DOUBLE_H
#define CM_VEC3_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

// TODO: Hide struct
typedef struct CmVec3Double {
  double x;
  double y;
  double z;
} CmVec3Double;

/* Inplace add vec B to vec A */
void cm_vec3_double_sum_inplace(CmVec3Double *vec_a, const CmVec3Double *vec_b);

/* Inplace subtract vec B from vec A */
void cm_vec3_double_sub_inplace(CmVec3Double *vec_a, const CmVec3Double *vec_b);

/* Inplace scale vec by X */
void cm_vec3_double_scale_inplace(CmVec3Double *vec, double scale);

/* Sum vec B to vec A */
CmVec3Double cm_vec3_double_sum(CmVec3Double vec_a, CmVec3Double vec_b);

/* Subtract vec B from vec A */
CmVec3Double cm_vec3_double_sub(CmVec3Double vec_a, CmVec3Double vec_b);

/* Scale vec by X */
CmVec3Double cm_vec3_double_scale(CmVec3Double vec, double scale);

/* Dot product of vec A and vec B */
double cm_vec3_double_dot(CmVec3Double vec_a, CmVec3Double vec_b);

/* Get angle between vec A and vec B */
double cm_vec3_double_angle(CmVec3Double vec_a, CmVec3Double vec_b);

/* Zero check for vec */
bool cm_vec3_double_is_zero(CmVec3Double vec);

/* Check is vectors equal */
bool cm_vec3_double_is_equal(CmVec3Double vec_a, CmVec3Double vec_b);

/* Rotate vec by X angle */
CmVec3Double cm_vec3_double_rotate(CmVec3Double vec, double angle);

/* Get cross product of vec A and vec B */
CmVec3Double cm_vec3_double_cross(CmVec3Double vec_a, CmVec3Double vec_b);

/* Get norm of vec */
double cm_vec3_double_norm(CmVec3Double vec);

/* Get squared norm of vec */
double cm_vec3_double_norm_squared(CmVec3Double vec);

/* Get distance between vec A and vec B */
double cm_vec3_double_distance(CmVec3Double vec_a, CmVec3Double vec_b);

/* Normalize vec */
CmVec3Double cm_vec3_double_normalize(CmVec3Double vec);

/* Inplace normalize vec */
void cm_vec3_double_normalize_inplace(CmVec3Double vec);

/* Project of vec A to vec B */
CmVec3Double cm_vec3_double_project(CmVec3Double proj_from,
                                    CmVec3Double proj_to);

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
