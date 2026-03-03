#include "../../../include/cmathcore/ivector3.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Dot Tests********************
Test(function, dot_positive_components_up_to_10) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, 1, 1, 1);
  cm_ivec3_init(&b, 3, 3, 3);

  int64_t res = cm_ivec3_dot(a, b);

  cr_expect(eq(i64, res, 9));
}

Test(function, dot_positive_components_up_to_10_one_zero) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, 0, 1, 3);
  cm_ivec3_init(&b, 1, 3, 3);

  int64_t res = cm_ivec3_dot(a, b);

  cr_expect(eq(i64, res, 12));
}

Test(function, dot_positive_components_up_to_10_one_zero_vec) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, 0, 0, 0);
  cm_ivec3_init(&b, 3, 3, 3);

  int64_t res = cm_ivec3_dot(a, b);

  cr_expect(eq(i64, res, 0));
}

Test(function, dot_positive_components_up_to_10_one_neg_vec) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, -1, -1, 4);
  cm_ivec3_init(&b, 3, 3, 3);

  int64_t res = cm_ivec3_dot(a, b);

  cr_expect(eq(i64, res, 6));
}

// ********************Cross Tests********************
Test(function, cross_positive_components_up_to_10) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_t res;
  cm_ivec3_init(&a, 1, 1, 1);
  cm_ivec3_init(&b, 3, 3, 3);

  cm_ivec3_cross(a, b, &res);

  cr_expect(eq(i64, cm_ivec3_get_x(res), 0));
  cr_expect(eq(i64, cm_ivec3_get_y(res), 0));
  cr_expect(eq(i64, cm_ivec3_get_z(res), 0));
}

Test(function, cross_positive_components_up_to_10_one_zero) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_t res;
  cm_ivec3_init(&a, 0, 1, 3);
  cm_ivec3_init(&b, 1, 3, 3);

  cm_ivec3_cross(a, b, &res);

  cr_expect(eq(i64, cm_ivec3_get_x(res), -6));
  cr_expect(eq(i64, cm_ivec3_get_y(res), 3));
  cr_expect(eq(i64, cm_ivec3_get_z(res), -1));
}

Test(function, cross_positive_components_up_to_10_one_zero_vec) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_t res;
  cm_ivec3_init(&a, 0, 0, 0);
  cm_ivec3_init(&b, 1, 3, 3);

  cm_ivec3_cross(a, b, &res);

  cr_expect(eq(i64, cm_ivec3_get_x(res), 0));
  cr_expect(eq(i64, cm_ivec3_get_y(res), 0));
  cr_expect(eq(i64, cm_ivec3_get_z(res), 0));
}

// ********************Dist Squared Tests********************
Test(function, dist_squared_positive_components_up_to_10) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, 1, 3, 2);
  cm_ivec3_init(&b, 0, 5, 4);

  int64_t res = cm_ivec3_dist_squared(a, b);

  cr_expect(eq(i64, res, 9));
}

Test(function, dist_squared_zero_vectors) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, 0, 0, 0);
  cm_ivec3_init(&b, 0, 0, 0);

  int64_t res = cm_ivec3_dist_squared(a, b);

  cr_expect(eq(i64, res, 0));
}

Test(function, dist_squared_positive_components_up_to_10_one_neg_vec) {

  cm_ivec3_t a;
  cm_ivec3_t b;
  cm_ivec3_init(&a, -3, -1, -3);
  cm_ivec3_init(&b, 2, 4, 2);

  int64_t res = cm_ivec3_dist_squared(a, b);

  cr_expect(eq(i64, res, 75));
}
