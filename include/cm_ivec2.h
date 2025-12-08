#ifndef CM_IVEC2_H
#define CM_IVEC2_H

#include <stdbool.h>

typedef struct cm_ivec2 cm_ivec2;

void cm_ivec2_copy(cm_ivec2 v, cm_ivec2 dest);
void cm_ivec2_zero(cm_ivec2 v);
void cm_ivec2_add(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest);
void cm_ivec2_sub(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest);

void cm_ivec2_scale(cm_ivec2 v, int s, cm_ivec2 dest);
void cm_ivec2_fill(cm_ivec2 v, int val);
void cm_ivec2_abs(cm_ivec2 v, cm_ivec2 dest);
void cm_ivec2_max(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest);

void cm_ivec2_min(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest);

int cm_ivec2_dot(cm_ivec2 a, cm_ivec2 b);
int cm_ivec2_cross(cm_ivec2 a, cm_ivec2 b);
int cm_ivec2_dist_squared(cm_ivec2 a, cm_ivec2 b);

float cm_ivec2_dist(cm_ivec2 a, cm_ivec2 b);

#endif
