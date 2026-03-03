#include "../../../include/cmathcore/ivector2.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Dot Tests********************
Test(function, dot_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1, 1);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_dot(a, b);

  cr_expect(eq(i64, res, 4));
}

Test(function, dot_positive_components_up_to_10_one_zero) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 0, 1);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_dot(a, b);

  cr_expect(eq(i64, res, 2));
}

Test(function, dot_positive_components_up_to_10_one_zero_vec) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 0, 0);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_dot(a, b);

  cr_expect(eq(i64, res, 0));
}

Test(function, dot_positive_components_up_to_10_one_neg_vec) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, -1, -1);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_dot(a, b);

  cr_expect(eq(i64, res, -4));
}

// ********************Cross Tests********************
Test(function, cross_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1, 1);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_cross(a, b);

  cr_expect(eq(i64, res, 0));
}

Test(function, cross_positive_components_up_to_10_one_zero) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 0, 1);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_cross(a, b);

  cr_expect(eq(i64, res, -2));
}

Test(function, cross_positive_components_up_to_10_one_neg_vec) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, -3, -4);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_cross(a, b);

  cr_expect(eq(i64, res, 2));
}

// ********************Dist Squared Tests********************
Test(function, dist_squared_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1, 2);
  cm_ivec2_init(&b, 2, 2);

  int64_t res = cm_ivec2_dist_squared(a, b);

  cr_expect(eq(i64, res, 1));
}

Test(function, dist_squared_zero_vectors) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 0, 0);
  cm_ivec2_init(&b, 0, 0);

  int64_t res = cm_ivec2_dist_squared(a, b);

  cr_expect(eq(i64, res, 0));
}

Test(function, dist_squared_positive_components_up_to_10_one_neg_vec) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, -3, -1);
  cm_ivec2_init(&b, 2, 4);

  int64_t res = cm_ivec2_dist_squared(a, b);

  cr_expect(eq(i64, res, 50));
}
