#ifndef CM_VEC2_DOUBLE_H
#define CM_VEC2_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct cm_dvec2_t cm_dvec2_t;

/* Inplace add vec B to vec A */
void cm_vec2_double_sum_inplace(cm_dvec2_t *vec_a, const cm_dvec2_t *vec_b);

/* Inplace subtract vec B from vec A */
void cm_vec2_double_sub_inplace(cm_dvec2_t *vec_a, const cm_dvec2_t *vec_b);

/* Inplace scale vec by X */
void cm_vec2_double_scale_inplace(cm_dvec2_t *vec, double scale);

/* Sum vec B to vec A */
cm_dvec2_t cm_vec2_double_sum(cm_dvec2_t vec_a, cm_dvec2_t vec_b);

/* Subtract vec B from vec A */
cm_dvec2_t cm_vec2_double_sub(cm_dvec2_t vec_a, cm_dvec2_t vec_b);

/* Scale vec by X */
cm_dvec2_t cm_vec2_double_scale(cm_dvec2_t vec, double scale);

/* Dot product of vec A and vec B */
double cm_vec2_double_dot(cm_dvec2_t vec_a, cm_dvec2_t vec_b);

/* Get angle between vec A and vec B */
double cm_vec2_double_angle(cm_dvec2_t vec_a, cm_dvec2_t vec_b);

/* Zero check for vec */
bool cm_vec2_double_is_zero(cm_dvec2_t vec);

/* Check is vectors equal */
bool cm_vec2_double_is_equal(cm_dvec2_t vec_a, cm_dvec2_t vec_b);

/* Rotate vec by X angle */
cm_dvec2_t cm_vec2_double_rotate(cm_dvec2_t vec, double angle);

/* Inplace rotate vec by X angle */
void cm_vec2_double_rotate_inplace(cm_dvec2_t *vec, double angle);

/* Get norm of vec */
double cm_vec2_double_norm(cm_dvec2_t vec);

/* Get squared norm of vec */
double cm_vec2_double_norm_squared(cm_dvec2_t vec);

/* Get 2d vec cross product len */
double cm_vec2_double_cross(cm_dvec2_t v1, cm_dvec2_t v2);

/* Get distance between vec A and vec B */
double cm_vec2_double_distance(cm_dvec2_t vec_a, cm_dvec2_t vec_b);

/* Normalize vec */
cm_dvec2_t cm_vec2_double_normalize(cm_dvec2_t vec);

/* Inplace normalize vec */
void cm_vec2_double_normalize_inplace(cm_dvec2_t *vec);

/* Project of vec A to vec B */
cm_dvec2_t cm_vec2_double_project(cm_dvec2_t proj_from,
                                    cm_dvec2_t proj_to);

/* Find the orthononal vec */
cm_dvec2_t cm_vec2_double_perp(cm_dvec2_t vec);

/* TODO: Reflect */
cm_dvec2_t *cm_vec2_double_reflect(const cm_dvec2_t *vec);

/* TODO: Lerp */
cm_dvec2_t *cm_vec2_double_lerp(const cm_dvec2_t *start,
                                  const cm_dvec2_t *end, double t);

/* Setter */
void cm_vec2_double_set_x(cm_dvec2_t *vec, double x_val);
void cm_vec2_double_set_y(cm_dvec2_t *vec, double y_val);

/* Getter */
double cm_vec2_double_get_x(cm_dvec2_t *vec);
double cm_vec2_double_get_y(cm_dvec2_t *vec);

#endif
