#include "../../../include/cmathcore/vector3.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Init Tests********************
Test(creation, init_positive_components){

  cm_vec3_t v;
  cm_vec3_init(&v, 1., 5., 2.);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(v), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(v), 5., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(v), 2., 4));
}

// ********************Copy Tests********************
Test(creation, copy_positive_components){

  cm_vec3_t src;
  cm_vec3_t dest;
  cm_vec3_init(&src, 1., 5., 2.);
  cm_vec3_copy(src, &dest);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(dest), cm_vec3_get_x(src), 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(dest), cm_vec3_get_y(src), 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(dest), cm_vec3_get_z(src), 4));
}

Test(creation, self_copy){

  cm_vec3_t src;
  cm_vec3_init(&src, 1., 5., 2.);
  cm_vec3_copy(src, &src);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(src), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(src), 5., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(src), 2., 4));
}

// ********************Fill Tests********************
Test(creation, fill_positive_components){

  cm_vec3_t v;
  cm_vec3_fill(&v, 1.);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(v), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(v), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(v), 1., 4));
}

// ********************Set Zero Tests********************
Test(creation, default_set_zero){

  cm_vec3_t v;
  cm_vec3_set_zero(&v);

  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_x(v), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_y(v), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec3_get_z(v), 0., 4));
}


