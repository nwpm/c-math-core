#ifndef CM_GEOMETRY2D_H
#define CM_GEOMETRY2D_H

#include "../vectors/cm_vec2_double.h"

/* Line defined by 2 radius vectors */
typedef struct CmLine2D{

  CmVec2Double a;
  CmVec2Double b;

} CmLine2D;

typedef struct CmCircle2D{

  CmVec2Double center;
  double radius;

} CmCircle2D;

typedef struct CmAABB2D{

  CmVec2Double min;
  CmVec2Double max;

} CmAABB2D;

typedef struct CmTriangle2D{

  CmVec2Double a;
  CmVec2Double b;
  CmVec2Double c;
} CmTriangle2D;


#endif
