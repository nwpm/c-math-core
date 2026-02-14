#ifndef CM_GEOMETRY3D_H
#define CM_GEOMETRY3D_H

#include "../vectors/cm_vec3_double.h"

/* Line defined by 2 radius vectors */
typedef struct CmLine3D {

  CmVec3Double a;
  CmVec3Double b;

} CmLine3D;

typedef struct CmRay3D {

  CmVec3Double a;
  CmVec3Double b;

} CmRay3D;

typedef struct CmSegment3D {

  CmVec3Double a;
  CmVec3Double b;

} CmSegment3D;

typedef struct CmPlane3D {

  CmVec3Double normal;
  double d;

} CmPlane3D;

typedef struct CmSphere3D {

  CmVec3Double center;
  double radius;

} CmSphere3D;

typedef struct CmAABB3D {

  CmVec3Double min;
  CmVec3Double max;

} CmAABB3D;

typedef struct CmTriangle3D {

  CmVec3Double a;
  CmVec3Double b;
  CmVec3Double c;

} CmTriangle3D;

/* Allocate row line object */
CmLine3D *cm_geom3d_line_alloc();

/* Create 3d line with 2 radius vectors */
CmLine3D *cm_geom3d_line_create(const CmVec3Double *v1, const CmVec3Double *v2);

/* Create copy for 3d line */
CmLine3D *cm_geom3d_line_copy(const CmLine3D *source_line);

/* Free allocated 3d line */
void cm_geom3d_line_free(CmLine3D *line);

#endif
