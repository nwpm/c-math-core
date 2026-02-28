#include <criterion/criterion.h>
#include "../../../include/cmathcore/vector2.h"

// ********************Add Tests********************

Test(operation, add_positive_components){

  cm_vec2_t a;
  cm_vec2_t b;
  cm_vec2_t res;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_init(&b, 3., 1.);

  cm_vec2_add(a, b, &res);

  cr_expect_float_eq(cm_vec2_get_x(res), 4., 4);
  cr_expect_float_eq(cm_vec2_get_y(res), 3., 4);

}

Test(operation, self_add){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_add(a, a, &a);

  cr_expect_float_eq(cm_vec2_get_x(a), 2., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 4., 4);

}

// ********************Sub Tests********************

Test(operation, sub_positive_components){

  cm_vec2_t a;
  cm_vec2_t b;
  cm_vec2_t res;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_init(&b, 3., 1.);

  cm_vec2_sub(a, b, &res);

  cr_expect_float_eq(cm_vec2_get_x(res), -2., 4);
  cr_expect_float_eq(cm_vec2_get_y(res), 1., 4);

}

Test(operation, self_sub){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_add(a, a, &a);

  cr_expect_float_eq(cm_vec2_get_x(a), 0., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 0., 4);

}

// ********************Scale Tests********************

Test(operation, scale_positive_components_and_scalar){

  cm_vec2_t a;
  cm_vec2_t res;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_scale(a, 10., &res);

  cr_expect_float_eq(cm_vec2_get_x(res), 10., 4);
  cr_expect_float_eq(cm_vec2_get_y(res), 20., 4);

}

Test(operation, self_scale){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_scale(a, 10., &a);

  cr_expect_float_eq(cm_vec2_get_x(a), 10., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 20., 4);

}

// ********************Abs Tests********************

Test(operation, abs_positive_components){

  cm_vec2_t a;
  cm_vec2_t res;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_abs(a, &res);

  cr_expect_float_eq(cm_vec2_get_x(res), 1., 4);
  cr_expect_float_eq(cm_vec2_get_y(res), 2., 4);

}

Test(operation, abs_negative_components){

  cm_vec2_t a;
  cm_vec2_t res;

  cm_vec2_init(&a, -1., -2.);
  cm_vec2_abs(a, &res);

  cr_expect_float_eq(cm_vec2_get_x(res), 1., 4);
  cr_expect_float_eq(cm_vec2_get_y(res), 2., 4);

}

Test(operation, abs_zero_components){

  cm_vec2_t a;
  cm_vec2_t res;

  cm_vec2_init(&a, 0., 0.);
  cm_vec2_abs(a, &res);

  cr_expect_float_eq(cm_vec2_get_x(res), 0., 4);
  cr_expect_float_eq(cm_vec2_get_y(res), 0., 4);

}

Test(operation, self_abs_negative_components){

  cm_vec2_t a;

  cm_vec2_init(&a, -1., -2.);
  cm_vec2_abs(a, &a);

  cr_expect_float_eq(cm_vec2_get_x(a), 1., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 2., 4);

}

// ********************Add Inplace Tests********************

Test(operation, add_inplace_positive_components){

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_init(&b, 3., 1.);

  cm_vec2_add_inplace(&a, b);

  cr_expect_float_eq(cm_vec2_get_x(a), 4., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 3., 4);

}

Test(operation, self_inplace_add){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_add_inplace(&a, a);

  cr_expect_float_eq(cm_vec2_get_x(a), 2., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 4., 4);

}

// ********************Sub Inplace Tests********************

Test(operation, sub_inplace_positive_components){

  cm_vec2_t a;
  cm_vec2_t b;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_init(&b, 3., 1.);

  cm_vec2_sub_inplace(&a, b);

  cr_expect_float_eq(cm_vec2_get_x(a), -2., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 1., 4);

}

Test(operation, self_inplace_sub){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_sub_inplace(&a, a);

  cr_expect_float_eq(cm_vec2_get_x(a), 0., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 0., 4);

}

// ********************Scale Inplace Tests********************

Test(operation, scale_inplace_positive_components_and_scalar){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_scale_inplace(&a, 10.);

  cr_expect_float_eq(cm_vec2_get_x(a), 10., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 20., 4);

}

// ********************Abs Inplace Tests********************

Test(operation, abs_inplace_positive_components){

  cm_vec2_t a;

  cm_vec2_init(&a, 1., 2.);
  cm_vec2_abs_inplace(&a);

  cr_expect_float_eq(cm_vec2_get_x(a), 1., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 2., 4);

}

Test(operation, abs_inplace_negative_components){

  cm_vec2_t a;

  cm_vec2_init(&a, -1., -2.);
  cm_vec2_abs_inplace(&a);

  cr_expect_float_eq(cm_vec2_get_x(a), 1., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 2., 4);

}

Test(operation, abs_inplace_zero_components){

  cm_vec2_t a;

  cm_vec2_init(&a, 0., 0.);
  cm_vec2_abs_inplace(&a);

  cr_expect_float_eq(cm_vec2_get_x(a), 0., 4);
  cr_expect_float_eq(cm_vec2_get_y(a), 0., 4);

}
