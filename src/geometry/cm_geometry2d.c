#include "cm_geometry2d.h"
#include "../utils/cm_utils.h"
#include <math.h>

/********************** Line **********************/

// NOTE: point A is origin and point b - a is direction
CmLine2D cm_line2d_from_points(CmVec2Double a, CmVec2Double b) {
  return (CmLine2D){a, {b.x - a.x, b.y - a.y}};
}

double cm_line2d_distance_point(CmLine2D l, CmVec2Double p) {

  CmVec2Double w = {p.x - l.origin.x, p.y - l.origin.y};

  double dot = cm_vec2_double_dot(w, l.direction);
  double direct_square = cm_vec2_double_norm_squared(l.direction);

  CmVec2Double distance = cm_vec2_double_sub(
      w, cm_vec2_double_scale(l.direction, dot / direct_square));

  return cm_vec2_double_norm(distance);
}

CmVec2Double cm_line2d_project_point(CmLine2D l, CmVec2Double p) {

  CmVec2Double w = {p.x - l.origin.x, p.y - l.origin.y};

  double dot = cm_vec2_double_dot(w, l.direction);
  double direct_square = cm_vec2_double_norm_squared(l.direction);
  double t = -(dot / direct_square);

  return (CmVec2Double){p.x + t * l.direction.x, p.y + t * l.direction.y};
}

bool cm_line2d_intersect_line(CmLine2D l1, CmLine2D l2, CmVec2Double *out) {

  double det = (l1.direction.x * (-l2.direction.y)) -
               (l1.direction.y * (-l2.direction.x));
  if (_cm_double_equal(det, 0.)) {
    out = NULL;
    return false;
  }

  double t = -(l2.direction.y * (l2.origin.x - l1.origin.x)) +
             (l2.direction.x * (l2.origin.y - l1.origin.y));

  out->x = l1.origin.x + t * l1.direction.x;
  out->y = l1.origin.y + t * l1.direction.y;

  return true;
}

bool cm_line2d_intersect_circle(CmLine2D l, CmCircle2D c, CmVec2Double *out1,
                                CmVec2Double *out2) {

  CmVec2Double m = {l.origin.x - c.center.x, l.origin.y - c.center.y};

  double a = cm_vec2_double_dot(l.direction, l.direction);
  double b = 2 * cm_vec2_double_dot(m, l.direction);
  double e = cm_vec2_double_dot(m, m) - (c.radius * c.radius);
  double d = (b * b) - (4 * a * e);

  if (d < 0) {
    out1 = NULL;
    out2 = NULL;
    return false;
  }

  double t1 = (-b + sqrt(d)) / (2 * a);
  double t2 = (-b - sqrt(d)) / (2 * a);

  out1->x = l.origin.x + t1 * l.direction.x;
  out1->y = l.origin.y + t1 * l.direction.y;

  out2->x = l.origin.x + t2 * l.direction.x;
  out2->y = l.origin.y + t2 * l.direction.y;

  return true;
}

bool cm_line2d_intersect_aabb(CmAABB2D box, CmLine2D line, CmVec2Double *out1,
                              CmVec2Double *out2);

/********************** Ray **********************/

CmRay2D cm_ray2d_from_points(CmVec2Double origin, CmVec2Double through) {
  return (CmRay2D){origin, {through.x - origin.x, through.y - origin.y}};
}

// NOTE t >= 0
CmVec2Double cm_ray2d_point(CmRay2D r, double t) {
  return cm_vec2_double_sum(r.origin, cm_vec2_double_scale(r.direction, t));
}

double cm_ray2d_distance_point(CmRay2D r, CmVec2Double p) {

  CmVec2Double w = {p.x - r.origin.x, p.y - r.origin.y};

  double dot = cm_vec2_double_dot(w, r.direction);
  double direct_square = cm_vec2_double_norm_squared(r.direction);

  CmVec2Double distance = cm_vec2_double_sub(
      w, cm_vec2_double_scale(r.direction, dot / direct_square));

  return cm_vec2_double_norm(distance);
}

bool cm_ray2d_intersect_line(CmRay2D r, CmLine2D l, CmVec2Double *out) {

  double det =
      (r.direction.y * l.direction.x) - (r.direction.x * l.direction.y);
  if (_cm_double_equal(det, 0.)) {
    out = NULL;
    return false;
  }

  double t = (-l.direction.y * (l.origin.x - r.origin.x) -
              l.direction.x * (l.origin.y - r.origin.y)) /
             det;

  if (t < 0) {
    out = NULL;
    return false;
  }

  out->x = r.origin.x + t * r.direction.x;
  out->y = r.origin.y + t * r.direction.y;

  return true;
}

bool cm_ray2d_intersect_segment(CmRay2D r, CmSegment2D s, CmVec2Double *out) {

  CmVec2Double direct_segment = {s.b.x - s.a.x, s.b.y - s.a.y};

  double det =
      (r.direction.y * direct_segment.x) - (r.direction.x * direct_segment.y);
  if (_cm_double_equal(det, 0.)) {
    out = NULL;
    return false;
  }

  double t = (-direct_segment.y * (s.a.x - r.origin.x)) +
             (direct_segment.x * (s.a.y - r.origin.y)) / det;

  double m = (-r.direction.y * (s.a.x - r.origin.x)) +
             (r.direction.x * (s.a.y - r.origin.y)) / det;

  if (t < 0 || (m > 1 || m < 0)) {
    out = NULL;
    return false;
  }

  out->x = r.origin.x + t * r.direction.x;
  out->y = r.origin.y + t * r.direction.y;

  return true;
}

bool cm_ray2d_intersect_circle(CmRay2D r, CmCircle2D c, CmVec2Double *out1,
                               CmVec2Double *out2) {

  CmVec2Double m = {r.origin.x - c.center.x, r.origin.y - c.center.y};

  double a = cm_vec2_double_dot(r.direction, r.direction);
  double b = 2 * cm_vec2_double_dot(m, r.direction);
  double e = cm_vec2_double_dot(m, m) - (c.radius * c.radius);
  double d = (b * b) - (4 * a * e);

  if (d < 0) {
    out1 = NULL;
    out2 = NULL;
    return false;
  }

  double t1 = (-b + sqrt(d)) / (2 * a);
  double t2 = (-b - sqrt(d)) / (2 * a);

  out1->x = r.origin.x + t1 * r.direction.x;
  out1->y = r.origin.y + t1 * r.direction.y;

  out2->x = r.origin.x + t2 * r.direction.x;
  out2->y = r.origin.y + t2 * r.direction.y;

  return true;
}

/********************** Segment **********************/

CmSegment2D cm_segment2d_from_points(CmVec2Double a, CmVec2Double b) {
  return (CmSegment2D){a.x - b.x, a.y - b.y};
}

double cm_segment2d_length(CmSegment2D s) {
  return cm_vec2_double_distance(s.a, s.b);
}

double cm_segment2d_distance_point(CmSegment2D s, CmVec2Double p) {

  CmVec2Double w = {p.x - s.a.x, p.y - s.a.y};
  CmVec2Double direct = {s.a.x - s.b.x, s.a.y - s.b.y};

  double dot = cm_vec2_double_dot(w, direct);
  double direct_square = cm_vec2_double_norm_squared(direct);

  CmVec2Double distance =
      cm_vec2_double_sub(w, cm_vec2_double_scale(direct, dot / direct_square));

  return cm_vec2_double_norm(distance);
}

bool cm_segment2d_intersect_segment(CmSegment2D s1, CmSegment2D s2,
                                    CmVec2Double *out) {

  CmVec2Double direct_s1 = {s1.a.x - s1.b.x, s1.a.y - s1.b.y};
  CmVec2Double direct_s2 = {s2.a.x - s2.b.x, s2.a.y - s2.b.y};

  double det = (direct_s1.y * direct_s2.x) - (direct_s1.x * direct_s2.y);
  if (_cm_double_equal(det, 0.)) {
    out = NULL;
    return false;
  }

  double t = (-direct_s2.y * (s2.a.x - s1.a.x)) +
             (direct_s2.x * (s2.a.y - s1.a.y)) / det;

  double m = (-direct_s1.y * (s2.a.x - s1.a.x)) +
             (direct_s1.x * (s2.a.y - s1.a.y)) / det;

  if ((t > 1 || t < 0) || (m > 1 || m < 0)) {
    out = NULL;
    return false;
  }

  out->x = s1.a.x + t * direct_s1.x;
  out->y = s1.a.y + t * direct_s1.y;

  return true;
}

bool cm_segment2d_intersect_circle(CmSegment2D s, CmCircle2D c,
                                   CmVec2Double *out1, CmVec2Double *out2) {

  CmVec2Double m = {s.a.x - c.center.x, s.a.y - c.center.y};
  CmVec2Double direct = {s.a.x - s.b.x, s.a.y - s.b.y};

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

  out1->x = s.a.x + t1 * direct.x;
  out1->y = s.a.y + t1 * direct.y;

  out2->x = s.a.x + t2 * direct.x;
  out2->y = s.a.y + t2 * direct.y;

  return true;
}

CmVec2Double cm_segment2d_midpoint(CmSegment2D s) {
  return (CmVec2Double){(s.a.x - s.b.y) / 2, (s.a.y - s.b.y) / 2};
}

/********************** Circle **********************/

CmCircle2D cm_circle2d_make(CmVec2Double center, double r) {
  return (CmCircle2D){center, r};
}

bool cm_circle2d_contains_point(CmCircle2D c, CmVec2Double p) {
  double v = cm_vec2_double_norm_squared(
      (CmVec2Double){p.x - c.center.x, p.y - c.center.y});
  return _cm_double_equal(v, c.radius * c.radius);
}

bool cm_circle2d_intersect_circle(CmCircle2D c1, CmCircle2D c2,
                                  CmVec2Double *out1, CmVec2Double *out2) {

  CmVec2Double centers_vec = {c1.center.x - c2.center.x,
                              c1.center.y - c2.center.y};
  double centers_vec_norm = cm_vec2_double_norm(centers_vec);

  bool not_intersect = centers_vec_norm > c1.radius + c1.radius;
  bool centers_coincide = centers_vec_norm == 0;
  bool inside = centers_vec_norm < (_cm_double_abs(c1.radius - c2.radius));

  if (not_intersect || centers_coincide || inside) {
    out1 = NULL;
    out2 = NULL;
    return false;
  }

  CmVec2Double e = cm_vec2_double_normalize(centers_vec);

  double k = ((c1.radius * c1.radius) - (c2.radius * c2.radius) +
              (centers_vec_norm * centers_vec_norm)) /
             (2 * centers_vec_norm);

  CmVec2Double p = cm_vec2_double_sum(c1.center, cm_vec2_double_scale(e, k));
  double h = sqrt(c1.radius * c1.radius - k * k);

  CmVec2Double n = {-e.y, e.x};

  *out1 = cm_vec2_double_sum(p, cm_vec2_double_scale(n, h));
  *out2 = cm_vec2_double_sub(p, cm_vec2_double_scale(n, h));

  return true;
}

/********************** Triangle **********************/

CmTriangle2D cm_triangle2d_make(CmVec2Double p1, CmVec2Double p2,
                                CmVec2Double p3) {
  return (CmTriangle2D){p1, p2, p3};
}

double cm_triangle2d_area(CmTriangle2D t) {
  return ((t.b.x * t.c.y - t.c.x * t.b.y) - (t.a.x * t.c.y - t.c.x * t.a.y) +
          (t.a.x * t.b.y - t.b.x * t.a.y)) /
         2.;
}

CmVec2Double cm_triangle2d_centroid(CmTriangle2D t) {
  return (CmVec2Double){(t.a.x + t.b.x + t.c.x) / 3,
                        (t.a.y + t.b.y + t.c.y) / 3};
}

// NOTE: Clockwise orientation
bool cm_triangle2d_contains_point(CmTriangle2D t, CmVec2Double p) {

  CmVec2Double v1 = {t.b.x - t.a.x, t.b.y - t.a.y};
  CmVec2Double v2 = {t.c.x - t.b.x, t.c.x - t.b.y};
  CmVec2Double v3 = {t.a.x - t.c.x, t.a.y - t.c.y};

  CmVec2Double pv1 = {p.x - t.a.x, p.y - t.a.y};
  CmVec2Double pv2 = {p.x - t.b.x, p.y - t.b.y};
  CmVec2Double pv3 = {p.x - t.c.x, p.y - t.c.y};

  double c1 = cm_vec2_double_cross(v1, pv1);
  double c2 = cm_vec2_double_cross(v2, pv2);
  double c3 = cm_vec2_double_cross(v3, pv3);

  if (c1 <= 0 && c2 <= 0 && c3 <= 0)
    return true;

  return false;
}

CmCircle2D cm_triangle2d_circumcircle(CmTriangle2D t) {

  double det = 2 * (t.a.x * (t.b.y - t.c.y) + t.b.x * (t.c.y - t.a.y) +
                    t.c.x * (t.a.y - t.b.y));

  double s_a = t.a.x * t.a.x + t.a.y * t.a.y;
  double s_b = t.b.x * t.b.x + t.b.y * t.b.y;
  double s_c = t.c.x * t.c.x + t.c.y * t.c.y;

  double center_x =
      (s_a * (t.b.y - t.c.y) + s_b * (t.c.y - t.a.y) + s_c * (t.a.y - t.b.y)) /
      det;

  double center_y =
      (s_a * (t.c.x - t.b.x) + s_b * (t.a.x - t.c.x) + s_c * (t.b.x - t.a.x)) /
      det;

  CmVec2Double center = {center_x, center_y};

  double rad =
      cm_vec2_double_norm((CmVec2Double){t.a.x - center.x, t.a.y - center.y});

  return (CmCircle2D){center, rad};
}

CmCircle2D cm_triangle2d_incircle(CmTriangle2D t) {

  CmVec2Double v_ab = {t.b.x - t.a.x, t.b.y - t.a.y};
  CmVec2Double v_bc = {t.c.x - t.b.x, t.c.y - t.b.y};
  CmVec2Double v_ca = {t.a.x - t.c.x, t.a.y - t.c.y};

  double len_ab = cm_vec2_double_norm(v_ab);
  double len_bc = cm_vec2_double_norm(v_bc);
  double len_ca = cm_vec2_double_norm(v_ca);
  double perim = len_ab + len_bc + len_ca;

  double center_x = (len_ab * t.a.x + len_bc * t.b.x + len_ca * t.c.x) / perim;
  double center_y = (len_ab * t.a.y + len_bc * t.b.y + len_ca * t.c.y) / perim;

  CmVec2Double center = {center_x, center_y};
  double trig_area = cm_triangle2d_area(t);
  double half_per = perim / 2.;
  double rad = trig_area / half_per;

  return (CmCircle2D){center, rad};
}

/********************** AABB **********************/

CmAABB2D cm_aabb2d_from_points(CmVec2Double a, CmVec2Double b) {
  return (CmAABB2D){a, b};
}

bool cm_aabb2d_contains_point(CmAABB2D b, CmVec2Double p) {

  if ((p.x >= b.min.x && p.x <= b.max.x) && (p.y >= b.min.y && p.y <= b.max.y))
    return true;

  return true;
}

double cm_aabb2d_area(CmAABB2D b) {

  CmVec2Double third_vert = {b.min.x, b.max.y};

  CmVec2Double edge_a = {b.max.x - third_vert.x, b.max.y - third_vert.y};
  CmVec2Double edge_b = {third_vert.x - b.min.x, third_vert.y - b.min.y};

  return cm_vec2_double_norm(edge_a) * cm_vec2_double_norm(edge_b);
}

/* NOTE:
 * 0 - bottom
 * 1 - up
 * 2 - left
 * 3 - right
 */
CmSegment2D cm_aabb2d_edge(CmAABB2D b, int index) {

  switch (index) {
  case 0:
    return (CmSegment2D){{b.max.x, b.min.y}, {b.min.x, b.min.y}};
  case 1:
    return (CmSegment2D){{b.max.x, b.max.y}, {b.min.x, b.max.y}};
  case 2:
    return (CmSegment2D){{b.min.x, b.max.y}, {b.min.x, b.min.y}};
  case 3:
    return (CmSegment2D){{b.max.x, b.max.y}, {b.max.x, b.min.y}};
  }
  return (CmSegment2D){0};
}

CmVec2Double cm_aabb2d_center(CmAABB2D b) {
  return (CmVec2Double){(b.max.x + b.min.x) / 2, (b.max.y + b.min.y) / 2};
}

void cm_aabb2d_expand(CmAABB2D b, CmVec2Double new_max){
  b.max = new_max;
}
