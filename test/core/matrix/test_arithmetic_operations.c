#include "../../../include/cm_core/cm_mat.h"
#include "../../Unity/src/unity.h"
#include "../../Unity/src/unity_internals.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// NOTE: test float version of matrix
/* Functions for test
 *
 * void cm_mat_transpose(cm_mat_t *mat);
 * cm_real_t cm_mat_trace(const cm_mat_t *mat);
 * cm_real_t cm_mat_det(const cm_mat_t *mat);
 * void cm_mat_add(cm_mat_t *mat_a, const cm_mat_t *mat_b);
 * void cm_mat_sub(cm_mat_t *mat_a, const cm_mat_t *mat_b);
 * void cm_mat_scale(cm_mat_t *mat_a, cm_real_t scale);
 * void cm_mat_mul(const cm_mat_t *mat_a, const cm_mat_t *mat_b,
                cm_mat_t *result_mat);
 * void cm_mat_pow(cm_mat_t *mat, unsigned exp);
 * cm_real_t cm_mat_minor(const cm_mat_t *mat, size_t row, size_t col);
 * cm_real_t cm_mat_cofactor(const cm_mat_t *mat, size_t row, size_t col);
 *
 *
 */

void setUp() {}
void tearDown() {}

int main() {

  UNITY_BEGIN();

  puts("Hello");

  return UNITY_END();
}
