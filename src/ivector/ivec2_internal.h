#ifndef CM_IVEC2_INTERNAL_H
#define CM_IVEC2_INTERNAL_H

#define CM_GET_ZERO_IVEC2 ((cm_ivec2_t){0, 0})
#define CM_GET_E1_IVEC2 ((cm_ivec2_t){1, 0})
#define CM_GET_E2_IVEC2 ((cm_ivec2_t){0, 1})

typedef struct cm_ivec2_t{
  int x, y;
} cm_ivec2_t;

#endif
