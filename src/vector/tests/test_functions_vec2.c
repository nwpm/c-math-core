#include "../../../include/cmathcore/constants.h"
#include "../../../include/cmathcore/vector2.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Dot Product Tests********************
Test(functions, dot_positive_vectors) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 23., 4));
}

Test(functions, dot_one_negative_vector) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, -2., -3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, -23., 4));
}

Test(functions, dot_one_negative_component) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, -2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 7., 4));
}

Test(functions, dot_one_zero_vector) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 0., 0.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Dot Angle Tests********************
Test(functions, dot_angle_acute_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dot_angle(a, b, 0.08673833867598511);
  cr_expect(ieee_ulp_eq(dbl, res, 23., 4));
}

Test(functions, dot_angle_right_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 1., 0.);
  cm_vec2_init(&b, 0., 1.);

  double res = cm_vec2_dot_angle(a, b, CM_HALF_PI);
  cr_expect(epsilon_eq(dbl, res, 0., 1e-15));
}

Test(functions, dot_angle_obtuse_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 3., 1.);
  cm_vec2_init(&b, -4., 2.);

  double res = cm_vec2_dot_angle(a, b, 2.35619449019234492885);
  cr_expect(ieee_ulp_eq(dbl, res, -10., 4));
}

Test(functions, dot_angle_zero_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 6.);

  double res = cm_vec2_dot_angle(a, b, 0.);
  cr_expect(ieee_ulp_eq(dbl, res, 26., 4));
}

// ********************Cross Product Tests********************
Test(functions, cross_positive_vectors) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_cross(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, -2., 4));
}

Test(functions, cross_one_negative_vector) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, -2., -3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_cross(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 2., 4));
}

Test(functions, cross_one_zero_vector) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 0., 0.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_cross(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Dist Squared Tests********************
Test(functions, dist_squared_positive_vectors) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dist_squared(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 8., 4));
}

Test(functions, dist_squared_one_zero_vector) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 0., 0.);

  double res = cm_vec2_dist_squared(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 13., 4));
}

Test(functions, dist_squared_self_distance) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  double res = cm_vec2_dist_squared(a, a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Dist Tests********************
Test(functions, dist_positive_vectors) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_dist(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, sqrt(8.), 4));
}

Test(functions, dist_one_zero_vector) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 0., 0.);

  double res = cm_vec2_dist(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, sqrt(13.), 4));
}

Test(functions, dist_self_distance) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  double res = cm_vec2_dist(a, a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Norm Tests********************
Test(functions, norm_positive_components) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  double res = cm_vec2_norm(a);
  cr_expect(ieee_ulp_eq(dbl, res, 3.60555127546398929, 4));
}

Test(functions, norm_zero_vector) {

  cm_vec2_t a;

  cm_vec2_init(&a, 0., 0.);

  double res = cm_vec2_norm(a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

Test(functions, norm_unit_vector) {

  cm_vec2_t a;

  cm_vec2_init(&a, 0., 1.);

  double res = cm_vec2_norm(a);
  cr_expect(ieee_ulp_eq(dbl, res, 1., 4));
}

// ********************Norm Squared Tests********************
Test(functions, norm_squared_positive_components) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  double res = cm_vec2_norm_squared(a);
  cr_expect(ieee_ulp_eq(dbl, res, 13., 4));
}

Test(functions, norm_squared_zero_vector) {

  cm_vec2_t a;

  cm_vec2_init(&a, 0., 0.);

  double res = cm_vec2_norm_squared(a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

Test(functions, norm_squared_unit_vector) {

  cm_vec2_t a;

  cm_vec2_init(&a, 0., 1.);

  double res = cm_vec2_norm_squared(a);
  cr_expect(ieee_ulp_eq(dbl, res, 1., 4));
}

// ********************Normalize Tests********************
Test(functions, normalize_positive_components) {

  cm_vec2_t a;
  cm_vec2_t res;

  cm_vec2_init(&a, 2., 3.);

  cm_vec2_normalize(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(res), 0.55470019622522912, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(res), 0.83205029433784368, 4));
}

Test(functions, normalize_negative_components) {

  cm_vec2_t a;
  cm_vec2_t res;

  cm_vec2_init(&a, -2., -3.);

  cm_vec2_normalize(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(res), -0.55470019622522912, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(res), -0.83205029433784368, 4));
}

Test(functions, self_normalize) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  cm_vec2_normalize(a, &a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(a), 0.55470019622522912, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(a), 0.83205029433784368, 4));
}

// ********************Normalize Inplace Tests********************
Test(functions, normalize_inplace_positive_components) {

  cm_vec2_t a;

  cm_vec2_init(&a, 2., 3.);

  cm_vec2_normalize_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(a), 0.55470019622522912, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(a), 0.83205029433784368, 4));
}

Test(functions, normalize_inplace_negative_components) {

  cm_vec2_t a;

  cm_vec2_init(&a, -2., -3.);

  cm_vec2_normalize_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(a), -0.55470019622522912, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(a), -0.83205029433784368, 4));
}

// ********************Angle Between Tests********************
Test(functions, angle_between_acute_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 5.);

  double res = cm_vec2_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, -0.086738338675985111, 4));
}

Test(functions, angle_between_right_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 1., 0.);
  cm_vec2_init(&b, 0., 1.);

  double res = cm_vec2_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, CM_HALF_PI, 4));
}

Test(functions, angle_between_obtuse_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 3., 1.);
  cm_vec2_init(&b, -4., 2.);

  double res = cm_vec2_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 2.35619449019234492, 4));
}

Test(functions, angle_between_zero_angle) {

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 2., 3.);
  cm_vec2_init(&b, 4., 6.);

  double res = cm_vec2_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}
