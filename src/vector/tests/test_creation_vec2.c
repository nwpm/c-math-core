#include "../../../include/cmathcore/vector2.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>

// ********************Init Tests********************
Test(creation, init_positive_components) {

  cm_vec2_t v;
  cm_vec2_init(&v, 1., 5.);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(v), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(v), 5., 4));
}

// ********************Copy Tests********************
Test(creation, copy_positive_components) {

  cm_vec2_t src;
  cm_vec2_t dest;
  cm_vec2_init(&src, 1., 5.);
  cm_vec2_copy(src, &dest);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(dest), cm_vec2_get_x(src), 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(dest), cm_vec2_get_y(src), 4));
}

Test(creation, self_copy) {

  cm_vec2_t src;
  cm_vec2_init(&src, 1., 5.);
  cm_vec2_copy(src, &src);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(src), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(src), 5., 4));
}

// ********************Fill Tests********************
Test(creation, fill_positive_components) {

  cm_vec2_t v;
  cm_vec2_fill(&v, 1.);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(v), 1., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(v), 1., 4));
}

// ********************Set Zero Tests********************
Test(creation, default_set_zero) {

  cm_vec2_t v;
  cm_vec2_set_zero(&v);

  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_x(v), 0., 4));
  cr_expect(ieee_ulp_eq(dbl, cm_vec2_get_y(v), 0., 4));
}
