#include "cm_geometry2d.h"
#include <math.h>

CmLine2D cm_line2d_from_points(CmVec2Double v1, CmVec2Double v2) {
  return (CmLine2D){v1, v2};
}

double cm_line2d_distance_point(CmLine2D l, CmVec2Double p) {

  CmVec2Double w = {p.x - l.a.x, p.y - l.a.y};
  CmVec2Double direct = {l.a.x - l.b.x, l.a.y - l.b.y};

  double dot = cm_vec2_double_dot(w, direct);
  double direct_square = cm_vec2_double_norm_squared(direct);

  CmVec2Double distance =
      cm_vec2_double_sub(w, cm_vec2_double_scale(direct, dot / direct_square));

  return cm_vec2_double_norm(distance);
}

CmVec2Double cm_line2d_direction(CmLine2D l) {
  return (CmVec2Double){l.a.x - l.b.x, l.a.y - l.b.y};
}

CmVec2Double cm_line2d_project_point(CmLine2D l, CmVec2Double p) {

  CmVec2Double w = {p.x - l.a.x, p.y - l.a.y};
  CmVec2Double direct = {l.a.x - l.b.x, l.a.y - l.b.y};

  double dot = cm_vec2_double_dot(w, direct);
  double direct_square = cm_vec2_double_norm_squared(direct);

  CmVec2Double distance =
      cm_vec2_double_sub(w, cm_vec2_double_scale(direct, dot / direct_square));

  return (CmVec2Double){p.x - distance.x, p.y - distance.y};
}

bool cm_line2d_intersect_line(CmLine2D l1, CmLine2D l2, CmVec2Double *out) {

  CmVec2Double direct1 = {l1.a.x - l1.b.x, l1.a.y - l1.b.y};
  CmVec2Double direct2 = {l2.a.x - l2.b.x, l2.a.y - l2.b.y};

  double det = (direct1.x * (-direct2.y)) - (direct1.y * (-direct2.x));
  if (!det) {
    out = NULL;
    return false;
  }

  double t = -(direct2.y * (l2.a.x - l1.a.x)) + (direct2.x * (l2.a.y - l1.a.y));

  out->x = l1.a.x + t * direct1.x;
  out->y = l1.a.y + t * direct1.y;

  return true;
}

bool cm_line2d_intersect_circle(CmLine2D l, CmCircle2D c, CmVec2Double *out1,
                                CmVec2Double *out2) {

  CmVec2Double m = {l.a.x - c.center.x, l.a.y - c.center.y};
  CmVec2Double direct = {l.a.x - l.b.x, l.a.y - l.b.y};
  double a = cm_vec2_double_dot(direct, direct);
  double b = 2 * cm_vec2_double_dot(m, direct);
  double e = cm_vec2_double_dot(m, m) - (c.radius * c.radius);
  double d = (b * b) - (4 * a * e);

  if (d < 0) {
    out1 = NULL;
    out2 = NULL;
    return false;
  }

  double t1 = (-b + sqrt(d)) / (2 * a);
  double t2 = (-b - sqrt(d)) / (2 * a);

  out1->x = l.a.x + t1 * direct.x;
  out1->y = l.a.y + t1 * direct.y;

  out2->x = l.a.x + t2 * direct.x;
  out2->y = l.a.y + t2 * direct.y;

  return true;
}

bool cm_line2d_intersect_aabb(CmAABB2D box, CmLine2D line, CmVec2Double *out1,
                              CmVec2Double *out2);


CmRay2D cm_ray2d_from_points(CmVec2Double origin, CmVec2Double through){
  return (CmRay2D){through.x - origin.x, through.y - origin.y};
}

CmVec2Double cm_ray2d_point(CmRay2D r, double t){
  CmVec2Double direct = {r.a.x - r.b.x, r.a.y - r.b.y};
  return cm_vec2_double_sum(r.a, cm_vec2_double_scale(direct, t));
}






