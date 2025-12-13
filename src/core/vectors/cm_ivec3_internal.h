#ifndef CM_IVEC3_INTERNAL_H
#define CM_IVEC3_INTERNAL_H

#define CM_GET_ZERO_IVEC3 ((cm_ivec3_t){0, 0, 0})
#define CM_GET_E1_IVEC3 ((cm_ivec3_t){1, 0, 0})
#define CM_GET_E2_IVEC3 ((cm_ivec3_t){0, 1, 0})
#define CM_GET_E3_IVEC3 ((cm_ivec3_t){0, 0, 1})

typedef struct cm_ivec3_t{
  int x, y;
} cm_ivec3_t;

#endif
