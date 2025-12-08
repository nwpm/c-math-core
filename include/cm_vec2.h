#ifndef CM_VEC2_H
#define CM_VEC2_H

#include <stdbool.h>

typedef struct cm_vec2 cm_vec2;

void cm_vec2_copy(cm_vec2 v, cm_vec2 dest);
void cm_vec2_zero(cm_vec2 v);
void cm_vec2_add(cm_vec2 a, cm_vec2 b, cm_vec2 dest);
void cm_vec2_sub(cm_vec2 a, cm_vec2 b, cm_vec2 dest);

void cm_vec2_scale(cm_vec2 v, float s, cm_vec2 dest);
void cm_vec2_fill(cm_vec2 v, float val);
void cm_vec2_abs(cm_vec2 v, cm_vec2 dest);
void cm_vec2_max(cm_vec2 a, cm_vec2 b, cm_vec2 dest);
void cm_vec2_min(cm_vec2 a, cm_vec2 b, cm_vec2 dest);

float cm_vec2_dot(cm_vec2 a, cm_vec2 b);
float cm_vec2_cross(cm_vec2 a, cm_vec2 b);
float cm_vec2_dist_squared(cm_vec2 a, cm_vec2 b);
float cm_vec2_dist(cm_vec2 a, cm_vec2 b);

#endif
