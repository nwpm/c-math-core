#ifndef CM_GEOMETRY3D_H
#define CM_GEOMETRY3D_H

#include "../vectors/cm_vec3_double.h"

/* Line defined by 2 radius vectors */
typedef struct CmLine3D{

  CmVec3Double a;
  CmVec3Double b;

} CmLine3D;

typedef struct CmRay3D{

  CmVec3Double a;
  CmVec3Double b;

} CmRay3D;

typedef struct CmSegment3D{

  CmVec3Double a;
  CmVec3Double b;

} CmSegment3D;

typedef struct CmPlane3D{

  CmVec3Double normal;
  double d;

} CmPlane3D;

typedef struct CmSphere3D{

  CmVec3Double center;
  double radius;

} CmSphere3D;

typedef struct CmAABB3D{

  CmVec3Double min;
  CmVec3Double max;

} CmAABB3D;

typedef struct CmTriangle3D{

  CmVec3Double a;
  CmVec3Double b;
  CmVec3Double c;

} CmTriangle3D;


#endif

