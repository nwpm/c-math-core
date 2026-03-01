#include "../../../include/cmathcore/vector3.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Add Tests********************

Test(operation, add_positive_components) {

  cm_vec3_t a;
  cm_vec3_t b;
  cm_vec3_t res;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_init(&b, 3., 1., 4.);

  cm_vec3_add(a, b, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 4., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 3., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 7., 4));
}

Test(operation, self_add) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_add(a, a, &a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 4., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 6., 4));
}

// ********************Sub Tests********************

Test(operation, sub_positive_components) {

  cm_vec3_t a;
  cm_vec3_t b;
  cm_vec3_t res;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_init(&b, 3., 1., 4.);

  cm_vec3_sub(a, b, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), -2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), -1., 4));
}

Test(operation, self_sub) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_sub(a, a, &a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 0., 4));
}

// ********************Scale Tests********************

Test(operation, scale_positive_components_and_scalar) {

  cm_vec3_t a;
  cm_vec3_t res;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_scale(a, 10., &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 10., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 20., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 30., 4));
}

Test(operation, self_scale) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_scale(a, 10., &a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 10., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 20., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 30., 4));
}

// ********************Abs Tests********************

Test(operation, abs_positive_components) {

  cm_vec3_t a;
  cm_vec3_t res;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_abs(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 3., 4));
}

Test(operation, abs_negative_components) {

  cm_vec3_t a;
  cm_vec3_t res;

  cm_vec3_init(&a, -1., -2., -3.);
  cm_vec3_abs(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 3., 4));
}

Test(operation, abs_zero_components) {

  cm_vec3_t a;
  cm_vec3_t res;

  cm_vec3_init(&a, 0., 0., 0.);
  cm_vec3_abs(a, &res);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(res), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(res), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(res), 0., 4));
}

Test(operation, self_abs_negative_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, -1., -2., -3.);
  cm_vec3_abs(a, &a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 3., 4));
}

// ********************Add Inplace Tests********************

Test(operation, add_inplace_positive_components) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_init(&b, 3., 1., 4.);

  cm_vec3_add_inplace(&a, b);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 4., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 3., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 7., 4));
}

Test(operation, self_inplace_add) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_add_inplace(&a, a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 4., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 6., 4));
}

// ********************Sub Inplace Tests********************

Test(operation, sub_inplace_positive_components) {

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_init(&b, 3., 1., 4.);

  cm_vec3_sub_inplace(&a, b);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), -2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), -1., 4));
}

Test(operation, self_inplace_sub) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_sub_inplace(&a, a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 0., 4));
}

// ********************Scale Inplace Tests********************

Test(operation, scale_inplace_positive_components_and_scalar) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_scale_inplace(&a, 10.);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 10., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 20., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 30., 4));
}

// ********************Abs Inplace Tests********************

Test(operation, abs_inplace_positive_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, 1., 2., 3.);
  cm_vec3_abs_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 3., 4));
}

Test(operation, abs_inplace_negative_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, -1., -2., -3.);
  cm_vec3_abs_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 2., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 3., 4));
}

Test(operation, abs_inplace_zero_components) {

  cm_vec3_t a;

  cm_vec3_init(&a, 0., 0., 0.);
  cm_vec3_abs_inplace(&a);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(a), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(a), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(a), 0., 4));
}
