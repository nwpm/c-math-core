#ifndef CM_IVEC3_H
#define CM_IVEC3_H

typedef struct cm_ivec3_t cm_ivec3_t;

void cm_ivec2_copy(cm_ivec3_t v, cm_ivec3_t dest);
void cm_ivec2_zero(cm_ivec3_t v);
void cm_ivec2_add(cm_ivec3_t a, cm_ivec3_t b, cm_ivec3_t dest);
void cm_ivec2_sub(cm_ivec3_t a, cm_ivec3_t b, cm_ivec3_t dest);

void cm_ivec2_scale(cm_ivec3_t v, int s, cm_ivec3_t dest);
void cm_ivec2_fill(cm_ivec3_t v, int val);
void cm_ivec2_abs(cm_ivec3_t v, cm_ivec3_t dest);
void cm_ivec2_max(cm_ivec3_t a, cm_ivec3_t b, cm_ivec3_t dest);

void cm_ivec2_min(cm_ivec3_t a, cm_ivec3_t b, cm_ivec3_t dest);

int cm_ivec2_dot(cm_ivec3_t a, cm_ivec3_t b);
int cm_ivec2_cross(cm_ivec3_t a, cm_ivec3_t b);
int cm_ivec2_dist_squared(cm_ivec3_t a, cm_ivec3_t b);

float cm_ivec2_dist(cm_ivec3_t a, cm_ivec3_t b);

#endif
