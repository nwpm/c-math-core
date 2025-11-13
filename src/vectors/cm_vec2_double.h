#ifndef CM_VEC2_DOUBLE_H
#define CM_VEC2_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct CmVec2Double {
  double x;
  double y;
} CmVec2Double;

/* Inplace add vec B to vec A */
void cm_vec2_double_sum_inplace(CmVec2Double *vec_a, const CmVec2Double *vec_b);

/* Inplace subtract vec B from vec A */
void cm_vec2_double_sub_inplace(CmVec2Double *vec_a, const CmVec2Double *vec_b);

/* Inplace scale vec by X */
void cm_vec2_double_scale_inplace(CmVec2Double *vec, double scale);

/* Sum vec B to vec A */
CmVec2Double cm_vec2_double_sum(CmVec2Double vec_a, CmVec2Double vec_b);

/* Subtract vec B from vec A */
CmVec2Double cm_vec2_double_sub(CmVec2Double vec_a, CmVec2Double vec_b);

/* Scale vec by X */
CmVec2Double cm_vec2_double_scale(CmVec2Double vec, double scale);

/* Dot product of vec A and vec B */
double cm_vec2_double_dot(CmVec2Double vec_a, CmVec2Double vec_b);

/* Get angle between vec A and vec B */
double cm_vec2_double_angle(CmVec2Double vec_a, CmVec2Double vec_b);

/* Zero check for vec */
bool cm_vec2_double_is_zero(CmVec2Double vec);

/* Check is vectors equal */
bool cm_vec2_double_is_equal(CmVec2Double vec_a, CmVec2Double vec_b);

/* Rotate vec by X angle */
CmVec2Double cm_vec2_double_rotate(CmVec2Double vec, double angle);

/* Inplace rotate vec by X angle */
void cm_vec2_double_rotate_inplace(CmVec2Double *vec, double angle);

/* Get norm of vec */
double cm_vec2_double_norm(CmVec2Double vec);

/* Get squared norm of vec */
double cm_vec2_double_norm_squared(CmVec2Double vec);

/* Get distance between vec A and vec B */
double cm_vec2_double_distance(CmVec2Double vec_a, CmVec2Double vec_b);

/* Normalize vec */
CmVec2Double cm_vec2_double_normalize(CmVec2Double vec);

/* Inplace normalize vec */
void cm_vec2_double_normalize_inplace(CmVec2Double *vec);

/* Project of vec A to vec B */
CmVec2Double cm_vec2_double_project(CmVec2Double proj_from,
                                    CmVec2Double proj_to);

/* Find the orthononal vec */
CmVec2Double cm_vec2_double_perp(CmVec2Double vec);

/* TODO: Reflect */
CmVec2Double *cm_vec2_double_reflect(const CmVec2Double *vec);

/* TODO: Lerp */
CmVec2Double *cm_vec2_double_lerp(const CmVec2Double *start,
                                  const CmVec2Double *end, double t);

/* Setter */
static inline void cm_vec2_double_set_x(CmVec2Double *vec, double x_val) {
  vec->x = x_val;
}

static inline void cm_vec2_double_set_y(CmVec2Double *vec, double y_val) {
  vec->y = y_val;
}

/* Getter */
static inline double cm_vec2_double_get_x(CmVec2Double *vec) { return vec->x; }

static inline double cm_vec2_double_get_y(CmVec2Double *vec) { return vec->y; }

#endif
