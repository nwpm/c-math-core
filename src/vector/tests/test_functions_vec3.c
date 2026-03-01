#include "../../../include/cmathcore/constants.h"
#include "../../../include/cmathcore/vector3.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Dot Product Tests********************
Test(functions, dot_positive_vectors) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 47., 4));
}

Test(functions, dot_one_negative_vector) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, -2., -3., -4.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, -47., 4));
}

Test(functions, dot_one_negative_component) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, -2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6);

  double res = cm_vec3_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 31., 4));
}

Test(functions, dot_one_zero_vector) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 0., 0., 0.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_dot(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Dot Angle Tests********************
Test(functions, dot_angle_acute_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_dot_angle(a, b, 0.10385856086697870);
  cr_expect(ieee_ulp_eq(dbl, res, 47., 4));
}

Test(functions, dot_angle_right_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 1., 0., 0.);
  cm_vec3_init(&b, 0., 1., 0.);

  double res = cm_vec3_dot_angle(a, b, CM_HALF_PI);
  cr_expect(epsilon_eq(dbl, res, 0., 1e-15));
}

Test(functions, dot_angle_obtuse_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 3., 1., 4.);
  cm_vec3_init(&b, -4., -2., 1.);

  double res = cm_vec3_dot_angle(a, b, 2.01303129691253294);
  cr_expect(ieee_ulp_eq(dbl, res, -10., 4));
}

Test(functions, dot_angle_zero_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 1.);
  cm_vec3_init(&b, 4., 6., 2.);

  double res = cm_vec3_dot_angle(a, b, 0.);
  cr_expect(ieee_ulp_eq(dbl, res, 28., 4));
}

// ********************Cross Product Tests********************
Test(functions, cross_positive_vectors) {

  cm_vec3_t a;
  cm_vec3_t b;
  cm_vec3_t res;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  cm_vec3_cross(a, b, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), -2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 4., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), -2., 4));
}

Test(functions, cross_one_negative_vector) {

  cm_vec3_t a;
  cm_vec3_t b;
  cm_vec3_t res;

  cm_vec3_init(&a, -2., -3., -4);
  cm_vec3_init(&b, 4., 5., 6.);

  cm_vec3_cross(a, b, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), -4., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 2., 4));
}

Test(functions, cross_one_zero_vector) {

  cm_vec3_t a;
  cm_vec3_t b;
  cm_vec3_t res;

  cm_vec3_init(&a, 0., 0., 0.);
  cm_vec3_init(&b, 4., 5., 6.);

  cm_vec3_cross(a, b, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 0., 4));
}

// ********************Dist Squared Tests********************
Test(functions, dist_squared_positive_vectors) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_dist_squared(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 12., 4));
}

Test(functions, dist_squared_one_zero_vector) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 0., 0., 0.);

  double res = cm_vec3_dist_squared(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 29., 4));
}

Test(functions, dist_squared_self_distance) {

  cm_vec3_t a;

  cm_vec3_init(&a, 2., 3., 4.);

  double res = cm_vec3_dist_squared(a, a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Dist Tests********************
Test(functions, dist_positive_vectors) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_dist(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 3.46410161513775458, 4));
}

Test(functions, dist_one_zero_vector) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 0., 0., 0.);

  double res = cm_vec3_dist(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 5.38516480713450403, 4));
}

Test(functions, dist_self_distance) {

  cm_vec3_t a;

  cm_vec3_init(&a, 2., 3., 4.);

  double res = cm_vec3_dist(a, a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

// ********************Norm Tests********************
Test(functions, norm_positive_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, 2., 3., 4.);

  double res = cm_vec3_norm(a);
  cr_expect(ieee_ulp_eq(dbl, res, 5.38516480713450403, 4));
}

Test(functions, norm_zero_vector) {

  cm_vec3_t a;

  cm_vec3_init(&a, 0., 0., 0.);

  double res = cm_vec3_norm(a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

Test(functions, norm_unit_vector) {

  cm_vec3_t a;

  cm_vec3_init(&a, 0., 1., 0.);

  double res = cm_vec3_norm(a);
  cr_expect(ieee_ulp_eq(dbl, res, 1., 4));
}

// ********************Norm Squared Tests********************
Test(functions, norm_squared_positive_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, 2., 3., 4.);

  double res = cm_vec3_norm_squared(a);
  cr_expect(ieee_ulp_eq(dbl, res, 29., 4));
}

Test(functions, norm_squared_zero_vector) {

  cm_vec3_t a;

  cm_vec3_init(&a, 0., 0., 0.);

  double res = cm_vec3_norm_squared(a);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}

Test(functions, norm_squared_unit_vector) {

  cm_vec3_t a;

  cm_vec3_init(&a, 0., 1., 0.);

  double res = cm_vec3_norm_squared(a);
  cr_expect(ieee_ulp_eq(dbl, res, 1., 4));
}

// ********************Normalize Tests********************
Test(functions, normalize_positive_components) {

  cm_vec3_t a;
  cm_vec3_t res;

  cm_vec3_init(&a, 2., 3., 4.);

  cm_vec3_normalize(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 0.37139067635410372, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 0.55708601453115558, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 0.74278135270820745, 4));
}

Test(functions, normalize_negative_components) {

  cm_vec3_t a;
  cm_vec3_t res;

  cm_vec3_init(&a, -2., -3., -4.);

  cm_vec3_normalize(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), -0.37139067635410372, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), -0.55708601453115558, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), -0.74278135270820745, 4));
}

Test(functions, self_normalize) {

  cm_vec3_t a;

  cm_vec3_init(&a, 2., 3., 4.);

  cm_vec3_normalize(a, &a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 0.37139067635410372, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 0.55708601453115558, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 0.74278135270820745, 4));
}

// ********************Normalize Inplace Tests********************
Test(functions, normalize_inplace_positive_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, 2., 3., 4.);

  cm_vec3_normalize_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 0.37139067635410372, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 0.55708601453115558, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 0.74278135270820745, 4));
}

Test(functions, normalize_inplace_negative_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, -2., -3., -4.);

  cm_vec3_normalize_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), -0.37139067635410372, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), -0.55708601453115558, 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), -0.74278135270820745, 4));
}

// ********************Angle Between Tests********************
Test(functions, angle_between_acute_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  double res = cm_vec3_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 0.10385856086697870, 4));
}

Test(functions, angle_between_right_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 1., 0., 0.);
  cm_vec3_init(&b, 0., 1., 0.);

  double res = cm_vec3_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, CM_HALF_PI, 4));
}

Test(functions, angle_between_obtuse_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 3., 1., 2.);
  cm_vec3_init(&b, -4., -2., 1.);

  double res = cm_vec3_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 2.34598970010525792, 4));
}

Test(functions, angle_between_zero_angle) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 6., 8.);

  double res = cm_vec3_angle_between(a, b);
  cr_expect(ieee_ulp_eq(dbl, res, 0., 4));
}
