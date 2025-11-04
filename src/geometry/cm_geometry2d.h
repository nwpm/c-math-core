#ifndef CM_GEOMETRY2D_H
#define CM_GEOMETRY2D_H

#include "../vectors/cm_vec2_double.h"

/* Line defined by 2 radius vectors */
typedef struct CmLine2D {

  CmVec2Double a;
  CmVec2Double b;

} CmLine2D;

typedef struct CmRay2D {

  CmVec2Double a;
  CmVec2Double b;

} CmRay3D;

typedef struct CmSegment2D {

  CmVec2Double a;
  CmVec2Double b;

} CmSegment3D;

typedef struct CmCircle2D {

  CmVec2Double center;
  double radius;

} CmCircle2D;

typedef struct CmAABB2D {

  CmVec2Double min;
  CmVec2Double max;

} CmAABB2D;

typedef struct CmTriangle2D {

  CmVec2Double a;
  CmVec2Double b;
  CmVec2Double c;
} CmTriangle2D;

/* Line */

/* Allocate row line object */
CmLine2D *cm_geom2d_line_alloc();

/* Create 2d line with 2 radius vectors */
CmLine2D *cm_geom2d_line_create(const CmVec2Double *v1, const CmVec2Double *v2);

/* Create copy for 2d line */
CmLine2D *cm_geom2d_line_copy(const CmLine2D *source_line);

/* Free allocated 2d line */
void cm_geom2d_line_free(CmLine2D *line);
/* Circle */

/* Allocate row circle object */
CmCircle2D *cm_geom2d_circle_alloc();

/* Create circle with current center and radius */
CmCircle2D *cm_geom2d_circle_create(const CmVec2Double *center, double radius);

/* Create copy for circle */
CmCircle2D *cm_geom2d_circle_copy(const CmCircle2D *source_circle);

/* Free allocated circle */
void cm_geom2d_circle_free(CmCircle2D *circle);

/* Triangle */

/* Allocate row triangle object */
CmTriangle2D *cm_geom2d_triangle_alloc();

/* Create triangle with a, b, c verticies */
CmTriangle2D *cm_geom2d_triangle_create(const CmVec2Double *a,
                                        const CmVec2Double *b,
                                        const CmVec2Double *c);

/* Create copy for 2d triangle */
CmTriangle2D *cm_geom2d_triangle_copy(const CmTriangle2D *source_triangle);

/* Free allocated 2d triangle */
void cm_geom2d_triangle_free(CmTriangle2D *triangle);

/* Axis-aligned bounding box */

/* Allocate row axis-aligned bounding box object */
CmAABB2D *cm_geom2d_aabb_lloc();

/* Create axis-aligned bounding box */
CmAABB2D *cm_geom2d_aabb_create(const CmVec2Double *min,
                                const CmVec2Double *max);

/* Create copy for 2d axis-aligned bounding box*/
CmAABB2D *cm_geom2d_aabb_copy(const CmAABB2D *source_aabb);

/* Free allocated 2d axis-aligned bounding box */
void cm_geom2d_aabb_free(CmAABB2D *aabb);

#endif
