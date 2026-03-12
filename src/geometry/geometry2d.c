#include "../../include/cmathcore/geometry2d.h"
#include "../utils/utils.h"
#include <math.h>

// TODO: cm_ray_intersect_aabb
// TODO: cm_segment_intersect_aabb
// TODO: cm_circle_distance_point
// TODO: cm_circle_aabb
// TODO: cm_triangle_aabb
// TODO: cm_triangle_intersect_circle
// TODO: cm_triangle_intersect_segment
// TODO: cm_aabb_intersect_aabb
// TODO: cm_aabb_intersect_circle
// TODO: cm_aabb_merge

/********************** Line **********************/

// NOTE: point A is origin and point b - a is direction
void cm_line2d_from_points(cm_vec2_t a, cm_vec2_t b, cm_line2d_t *res) {

  res->origin.x = a.x;
  res->origin.y = a.y;

  res->direction.x = b.x - a.x;
  res->direction.y = b.y - a.y;
}

double cm_line2d_distance_point(cm_line2d_t l, cm_vec2_t p) {

  cm_vec2_t w = {p.x - l.origin.x, p.y - l.origin.y};
  cm_vec2_t proj_w;
  cm_vec2_t distance;

  double dot = cm_vec2_dot(w, l.direction);
  double direct_square = cm_vec2_norm_squared(l.direction);
  cm_vec2_scale(l.direction, dot / direct_square, &proj_w);

  cm_vec2_sub(w, proj_w, &distance);

  return cm_vec2_norm(distance);
}

void cm_line2d_project_point(cm_line2d_t l, cm_vec2_t p, cm_vec2_t *res) {

  cm_vec2_t w = {p.x - l.origin.x, p.y - l.origin.y};

  double dot = cm_vec2_dot(w, l.direction);
  double direct_square = cm_vec2_norm_squared(l.direction);
  double t = dot / direct_square;

  res->x = l.origin.x + t * l.direction.x;
  res->y = l.origin.y + t * l.direction.y;
}

bool cm_line2d_intersect_line(cm_line2d_t l1, cm_line2d_t l2, cm_vec2_t *out) {

  double det = (l1.direction.x * (-l2.direction.y)) -
               (l1.direction.y * (-l2.direction.x));

  if (_cm_double_is_equal(det, 0.)) {
    return false;
  }

  double t = (-(l2.direction.y * (l2.origin.x - l1.origin.x)) +
              (l2.direction.x * (l2.origin.y - l1.origin.y))) /
             det;

  out->x = l1.origin.x + t * l1.direction.x;
  out->y = l1.origin.y + t * l1.direction.y;

  return true;
}

bool cm_line2d_intersect_circle(cm_line2d_t l, cm_circle2d_t c, cm_vec2_t *out1,
                                cm_vec2_t *out2) {

  cm_vec2_t m = {l.origin.x - c.center.x, l.origin.y - c.center.y};

  double a = cm_vec2_dot(l.direction, l.direction);
  double b = 2 * cm_vec2_dot(m, l.direction);
  double e = cm_vec2_dot(m, m) - (c.radius * c.radius);
  double d = (b * b) - (4. * a * e);

  if (d < 0.) {
    return false;
  }

  double t1 = (-b + sqrt(d)) / (2. * a);
  double t2 = (-b - sqrt(d)) / (2. * a);

  out1->x = l.origin.x + t1 * l.direction.x;
  out1->y = l.origin.y + t1 * l.direction.y;

  out2->x = l.origin.x + t2 * l.direction.x;
  out2->y = l.origin.y + t2 * l.direction.y;

  return true;
}

bool cm_line2d_intersect_aabb(cm_aabb2d_t box, cm_line2d_t line,
                              cm_vec2_t *out1, cm_vec2_t *out2);

/********************** Ray **********************/

void cm_ray2d_from_points(cm_vec2_t origin, cm_vec2_t through,
                          cm_ray2d_t *res) {
  res->origin.x = origin.x;
  res->origin.y = origin.y;

  res->direction.x = through.x - origin.x;
  res->direction.y = through.y - origin.y;
}

// NOTE t >= 0
void cm_ray2d_point(cm_ray2d_t r, double t, cm_vec2_t *res) {

  res->x = r.origin.x + t * r.direction.x;
  res->y = r.origin.y + t * r.direction.y;
}

double cm_ray2d_distance_point(cm_ray2d_t r, cm_vec2_t p) {

  cm_vec2_t w = {p.x - r.origin.x, p.y - r.origin.y};
  cm_vec2_t proj;
  cm_vec2_t distance;

  double dot = cm_vec2_dot(w, r.direction);
  double direct_square = cm_vec2_norm_squared(r.direction);
  double t = dot / direct_square;

  cm_vec2_init(&proj, t * r.direction.x, t * r.direction.y);
  cm_vec2_sub(w, proj, &distance);

  return cm_vec2_norm(distance);
}

bool cm_ray2d_intersect_line(cm_ray2d_t r, cm_line2d_t l, cm_vec2_t *out) {

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

bool cm_ray2d_intersect_segment(cm_ray2d_t r, CmSegment2D s, cm_vec2_t *out) {

  cm_vec2_t direct_segment = {s.b.x - s.a.x, s.b.y - s.a.y};

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

bool cm_ray2d_intersect_circle(cm_ray2d_t r, cm_circle2d_t c, cm_vec2_t *out1,
                               cm_vec2_t *out2) {

  cm_vec2_t m = {r.origin.x - c.center.x, r.origin.y - c.center.y};

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

CmSegment2D cm_segment2d_from_points(cm_vec2_t a, cm_vec2_t b) {
  return (CmSegment2D){a.x - b.x, a.y - b.y};
}

double cm_segment2d_length(CmSegment2D s) {
  return cm_vec2_double_distance(s.a, s.b);
}

double cm_segment2d_distance_point(CmSegment2D s, cm_vec2_t p) {

  cm_vec2_t w = {p.x - s.a.x, p.y - s.a.y};
  cm_vec2_t direct = {s.a.x - s.b.x, s.a.y - s.b.y};

  double dot = cm_vec2_double_dot(w, direct);
  double direct_square = cm_vec2_double_norm_squared(direct);

  cm_vec2_t distance =
      cm_vec2_double_sub(w, cm_vec2_double_scale(direct, dot / direct_square));

  return cm_vec2_double_norm(distance);
}

bool cm_segment2d_intersect_segment(CmSegment2D s1, CmSegment2D s2,
                                    cm_vec2_t *out) {

  cm_vec2_t direct_s1 = {s1.a.x - s1.b.x, s1.a.y - s1.b.y};
  cm_vec2_t direct_s2 = {s2.a.x - s2.b.x, s2.a.y - s2.b.y};

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

bool cm_segment2d_intersect_circle(CmSegment2D s, cm_circle2d_t c,
                                   cm_vec2_t *out1, cm_vec2_t *out2) {

  cm_vec2_t m = {s.a.x - c.center.x, s.a.y - c.center.y};
  cm_vec2_t direct = {s.a.x - s.b.x, s.a.y - s.b.y};

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

cm_vec2_t cm_segment2d_midpoint(CmSegment2D s) {
  return (cm_vec2_t){(s.a.x - s.b.y) / 2, (s.a.y - s.b.y) / 2};
}

/********************** Circle **********************/

cm_circle2d_t cm_circle2d_make(cm_vec2_t center, double r) {
  return (cm_circle2d_t){center, r};
}

bool cm_circle2d_contains_point(cm_circle2d_t c, cm_vec2_t p) {
  double v = cm_vec2_double_norm_squared(
      (cm_vec2_t){p.x - c.center.x, p.y - c.center.y});
  return _cm_double_equal(v, c.radius * c.radius);
}

bool cm_circle2d_intersect_circle(cm_circle2d_t c1, cm_circle2d_t c2,
                                  cm_vec2_t *out1, cm_vec2_t *out2) {

  cm_vec2_t centers_vec = {c1.center.x - c2.center.x,
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

  cm_vec2_t e = cm_vec2_double_normalize(centers_vec);

  double k = ((c1.radius * c1.radius) - (c2.radius * c2.radius) +
              (centers_vec_norm * centers_vec_norm)) /
             (2 * centers_vec_norm);

  cm_vec2_t p = cm_vec2_double_sum(c1.center, cm_vec2_double_scale(e, k));
  double h = sqrt(c1.radius * c1.radius - k * k);

  cm_vec2_t n = {-e.y, e.x};

  *out1 = cm_vec2_double_sum(p, cm_vec2_double_scale(n, h));
  *out2 = cm_vec2_double_sub(p, cm_vec2_double_scale(n, h));

  return true;
}

/********************** Triangle **********************/

CmTriangle2D cm_triangle2d_make(cm_vec2_t p1, cm_vec2_t p2, cm_vec2_t p3) {
  return (CmTriangle2D){p1, p2, p3};
}

double cm_triangle2d_area(CmTriangle2D t) {
  return ((t.b.x * t.c.y - t.c.x * t.b.y) - (t.a.x * t.c.y - t.c.x * t.a.y) +
          (t.a.x * t.b.y - t.b.x * t.a.y)) /
         2.;
}

cm_vec2_t cm_triangle2d_centroid(CmTriangle2D t) {
  return (cm_vec2_t){(t.a.x + t.b.x + t.c.x) / 3, (t.a.y + t.b.y + t.c.y) / 3};
}

// NOTE: Clockwise orientation
bool cm_triangle2d_contains_point(CmTriangle2D t, cm_vec2_t p) {

  cm_vec2_t v1 = {t.b.x - t.a.x, t.b.y - t.a.y};
  cm_vec2_t v2 = {t.c.x - t.b.x, t.c.x - t.b.y};
  cm_vec2_t v3 = {t.a.x - t.c.x, t.a.y - t.c.y};

  cm_vec2_t pv1 = {p.x - t.a.x, p.y - t.a.y};
  cm_vec2_t pv2 = {p.x - t.b.x, p.y - t.b.y};
  cm_vec2_t pv3 = {p.x - t.c.x, p.y - t.c.y};

  double c1 = cm_vec2_double_cross(v1, pv1);
  double c2 = cm_vec2_double_cross(v2, pv2);
  double c3 = cm_vec2_double_cross(v3, pv3);

  if (c1 <= 0 && c2 <= 0 && c3 <= 0)
    return true;

  return false;
}

cm_circle2d_t cm_triangle2d_circumcircle(CmTriangle2D t) {

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

  cm_vec2_t center = {center_x, center_y};

  double rad =
      cm_vec2_double_norm((cm_vec2_t){t.a.x - center.x, t.a.y - center.y});

  return (cm_circle2d_t){center, rad};
}

cm_circle2d_t cm_triangle2d_incircle(CmTriangle2D t) {

  cm_vec2_t v_ab = {t.b.x - t.a.x, t.b.y - t.a.y};
  cm_vec2_t v_bc = {t.c.x - t.b.x, t.c.y - t.b.y};
  cm_vec2_t v_ca = {t.a.x - t.c.x, t.a.y - t.c.y};

  double len_ab = cm_vec2_double_norm(v_ab);
  double len_bc = cm_vec2_double_norm(v_bc);
  double len_ca = cm_vec2_double_norm(v_ca);
  double perim = len_ab + len_bc + len_ca;

  double center_x = (len_ab * t.a.x + len_bc * t.b.x + len_ca * t.c.x) / perim;
  double center_y = (len_ab * t.a.y + len_bc * t.b.y + len_ca * t.c.y) / perim;

  cm_vec2_t center = {center_x, center_y};
  double trig_area = cm_triangle2d_area(t);
  double half_per = perim / 2.;
  double rad = trig_area / half_per;

  return (cm_circle2d_t){center, rad};
}

/********************** AABB **********************/

cm_aabb2d_t cm_aabb2d_from_points(cm_vec2_t a, cm_vec2_t b) {
  return (cm_aabb2d_t){a, b};
}

bool cm_aabb2d_contains_point(cm_aabb2d_t b, cm_vec2_t p) {

  if ((p.x >= b.min.x && p.x <= b.max.x) && (p.y >= b.min.y && p.y <= b.max.y))
    return true;

  return true;
}

double cm_aabb2d_area(cm_aabb2d_t b) {

  cm_vec2_t third_vert = {b.min.x, b.max.y};

  cm_vec2_t edge_a = {b.max.x - third_vert.x, b.max.y - third_vert.y};
  cm_vec2_t edge_b = {third_vert.x - b.min.x, third_vert.y - b.min.y};

  return cm_vec2_double_norm(edge_a) * cm_vec2_double_norm(edge_b);
}

/* NOTE:
 * 0 - bottom
 * 1 - up
 * 2 - left
 * 3 - right
 */
CmSegment2D cm_aabb2d_edge(cm_aabb2d_t b, int index) {

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

cm_vec2_t cm_aabb2d_center(cm_aabb2d_t b) {
  return (cm_vec2_t){(b.max.x + b.min.x) / 2, (b.max.y + b.min.y) / 2};
}

void cm_aabb2d_expand(cm_aabb2d_t b, cm_vec2_t new_max) { b.max = new_max; }
