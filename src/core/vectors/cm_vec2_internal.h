#ifndef CM_VEC2_INTERNAL_H
#define CM_VEC2_INTERNAL_H

#include <stdbool.h>

#define CM_GET_ZERO_VEC2 ((cm_vec2_t){0, 0})
#define CM_GET_E1_VEC2 ((cm_vec2_t){1, 0})
#define CM_GET_E2_VEC2 ((cm_vec2_t){0, 1})

typedef struct cm_vec2_t {
  float x, y;
} cm_vec2_t;

#endif
