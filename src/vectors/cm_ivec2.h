#ifndef CM_IVEC2_H
#define CM_IVEC2_H

#define CM_GET_ZERO_IVEC2 ((cm_ivec2){0, 0})
#define CM_GET_E1_IVEC2 ((cm_ivec2){1, 0})
#define CM_GET_E2_IVEC2 ((cm_ivec2){0, 1})

typedef struct cm_ivec2{
  int x, y;
} cm_ivec2;

void cm_ivec2_copy(cm_ivec2 v, cm_ivec2 dest);
void cm_ivec2_zero(cm_ivec2 v);
void cm_ivec2_add(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest);
void cm_ivec2_sub(cm_ivec2 a, cm_ivec2 b, cm_ivec2 dest);

#endif
