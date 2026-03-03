#include "../../../include/cmathcore/ivector2.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Add Tests********************
Test(operation, add_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 1, 1);
  cm_ivec2_init(&b, 1, 1);

  cm_ivec2_add(a, b, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 2));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 2));
}

Test(operation, add_positive_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 340, 120);
  cm_ivec2_init(&b, 60, 80);

  cm_ivec2_add(a, b, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 400));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 200));
}

Test(operation, add_positive_components_up_to_10000000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 1000000, 3400000);
  cm_ivec2_init(&b, 1500000, 600000);

  cm_ivec2_add(a, b, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 2500000));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 4000000));
}

Test(operation, self_add_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_add(a, a, &a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 2));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 2));
}

// ********************Sub Tests********************
Test(operation, sub_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 1, 1);
  cm_ivec2_init(&b, 1, 1);

  cm_ivec2_sub(a, b, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 0));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 0));
}

Test(operation, sub_positive_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 340, 120);
  cm_ivec2_init(&b, 60, 80);

  cm_ivec2_sub(a, b, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 280));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 40));
}

Test(operation, sub_positive_components_up_to_10000000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 1000000, 3400000);
  cm_ivec2_init(&b, 1500000, 600000);

  cm_ivec2_sub(a, b, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), -500000));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 2800000));
}

Test(operation, self_sub_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_sub(a, a, &a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 0));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 0));
}

// ********************Scale Tests********************
Test(operation, scale_10_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_scale(a, 10, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 10));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 10));
}

Test(operation, scale_10_positive_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 100, 100);

  cm_ivec2_scale(a, 10, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 1000));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 1000));
}

Test(operation, scale_minus_1_negative_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, -500, -600);

  cm_ivec2_scale(a, -1, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 500));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 600));
}

Test(operation, self_scale_10_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_scale(a, 10, &a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 10));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 10));
}

// ********************Abs Tests********************
Test(operation, abs_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_abs(a, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 1));
}

Test(operation, abs_zero_components) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, 0, 0);

  cm_ivec2_abs(a, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 0));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 0));
}

Test(operation, abs_negative_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, -1, -1);

  cm_ivec2_abs(a, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(res), 1));
}

Test(operation, abs_int64_min) {

  cm_ivec2_t a;
  cm_ivec2_t res;
  cm_ivec2_init(&a, INT64_MIN, INT64_MIN);

  cm_ivec2_abs(a, &res);

  cr_expect(eq(i64, cm_ivec2_get_x(res), INT64_MIN));
  cr_expect(eq(i64, cm_ivec2_get_y(res), INT64_MIN));
}

Test(operation, self_abs) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, -1, -1);

  cm_ivec2_abs(a, &a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 1));
}

// ********************Add Inplace Tests********************
Test(operation, add_inplace_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1, 1);
  cm_ivec2_init(&b, 1, 1);

  cm_ivec2_add_inplace(&a, b);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 2));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 2));
}

Test(operation, add_inplace_positive_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 340, 120);
  cm_ivec2_init(&b, 60, 80);

  cm_ivec2_add_inplace(&a, b);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 400));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 200));
}

Test(operation, add_inplace_positive_components_up_to_10000000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1000000, 3400000);
  cm_ivec2_init(&b, 1500000, 600000);

  cm_ivec2_add_inplace(&a, b);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 2500000));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 4000000));
}

// ********************Sub Inplace Tests********************
Test(operation, sub_inplace_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1, 1);
  cm_ivec2_init(&b, 1, 1);

  cm_ivec2_sub_inplace(&a, b);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 0));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 0));
}

Test(operation, sub_inplace_positive_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 340, 120);
  cm_ivec2_init(&b, 60, 80);

  cm_ivec2_sub_inplace(&a, b);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 280));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 40));
}

Test(operation, sub_inplace_positive_components_up_to_10000000) {

  cm_ivec2_t a;
  cm_ivec2_t b;
  cm_ivec2_init(&a, 1000000, 3400000);
  cm_ivec2_init(&b, 1500000, 600000);

  cm_ivec2_sub_inplace(&a, b);

  cr_expect(eq(i64, cm_ivec2_get_x(a), -500000));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 2800000));
}

// ********************Scale Inplace Tests********************
Test(operation, scale_inplace_10_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_scale_inplace(&a, 10);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 10));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 10));
}

Test(operation, scale_inplace_2_positive_components_up_to_1000) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, 100, 200);

  cm_ivec2_scale_inplace(&a, 2);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 200));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 400));
}

Test(operation, scale_inplace_minus_1_negative_components_up_to_100) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, -50, -40);

  cm_ivec2_scale_inplace(&a, -1);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 50));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 40));
}

// ********************Abs Inplace Tests********************
Test(operation, abs_inplace_positive_components_up_to_10) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, 1, 1);

  cm_ivec2_abs_inplace(&a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 1));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 1));
}

Test(operation, abs_inplace_negative_components_up_to_100) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, -50, -40);

  cm_ivec2_abs_inplace(&a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), 50));
  cr_expect(eq(i64, cm_ivec2_get_y(a), 40));
}

Test(operation, abs_inplace_int64_min) {

  cm_ivec2_t a;
  cm_ivec2_init(&a, INT64_MIN, INT64_MIN);

  cm_ivec2_abs_inplace(&a);

  cr_expect(eq(i64, cm_ivec2_get_x(a), INT64_MIN));
  cr_expect(eq(i64, cm_ivec2_get_y(a), INT64_MIN));
}
