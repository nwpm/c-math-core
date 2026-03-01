#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include "../../../include/cmathcore/vector3.h"

// ********************Is Zero Tests********************
Test(compare, is_zero_non_zero_vector){

  cm_vec3_t a;

  cm_vec3_init(&a, 3., 3., 1.);

  bool res = cm_vec3_is_zero(a);
  cr_expect(eq(int, res, false));
}

Test(compare, is_zero_zero_vector){

  cm_vec3_t a;

  cm_vec3_init(&a, 0., 0., 0.);

  bool res = cm_vec3_is_zero(a);
  cr_expect(eq(int, res, true));
}

// ********************Is Equal Tests********************
Test(compare, is_equal_non_equal_vectors){

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 4., 5., 6.);

  bool res = cm_vec3_is_equal(a, b);
  cr_expect(eq(int, res, false));
}

Test(compare, is_equal_equal_vectors){

  cm_vec3_t a;
  cm_vec3_t b;

  cm_vec3_init(&a, 2., 3., 4.);
  cm_vec3_init(&b, 2., 3., 4.);

  bool res = cm_vec3_is_equal(a, b);
  cr_expect(eq(int, res, true));
}
