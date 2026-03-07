#include "../../../include/cmathcore/matrix.h"
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>

/************************** Scale Row Tests ****************************/

typedef struct {
  size_t rows;
  size_t cols;
  size_t scale_row;
  double scale_val;
} scale_row_params;

ParameterizedTestParameters(row_operations, scale_row) {
  static scale_row_params params[] = {
      {1, 1, 0, 0.5},    {10, 3, 9, 1e-5},    {25, 25, 0, 0},
      {50, 50, 25, 1e5}, {100, 150, 99, 4e5}, {1000, 1000, 999, 1e-5},
  };

  size_t params_size = sizeof(params) / sizeof(scale_row_params);

  return cr_make_param_array(scale_row_params, params, params_size);
}

ParameterizedTest(scale_row_params *param, row_operations, scale_row) {

  size_t rows = param->rows;
  size_t cols = param->cols;

  cm_mat_t *orig_mat = cm_mat_alloc(rows, cols);

  for (size_t j = 0; j < rows; ++j) {
    for (size_t k = 0; k < cols; ++k) {
      cm_mat_set(orig_mat, j, k, (double)(j + 10) * 1e10);
    }
  }

  cm_mat_t *scaled_mat = cm_mat_create_from_matrix(orig_mat);
  cm_mat_scale_row(scaled_mat, param->scale_row, param->scale_val);

  for (size_t i = 0; i < cols; ++i) {
    double expected_val =
        cm_mat_get(orig_mat, param->scale_row, i) * param->scale_val;

    cr_assert(ieee_ulp_eq(dbl, cm_mat_get(scaled_mat, param->scale_row, i),
                          expected_val, 4));
  }

  cm_mat_free(scaled_mat);
  cm_mat_free(orig_mat);
}

/************************** Swap Rows Tests ****************************/
typedef struct {
  size_t rows;
  size_t cols;
  size_t row_a;
  size_t row_b;
} swap_rows_params;

ParameterizedTestParameters(row_operations, swap_rows) {
  static swap_rows_params params[] = {
      {1, 1, 0, 0},      {10, 10, 0, 9},         {50, 25, 9, 24},
      {100, 150, 99, 0}, {1000, 1000, 999, 999},
  };

  size_t params_size = sizeof(params) / sizeof(swap_rows_params);

  return cr_make_param_array(swap_rows_params, params, params_size);
}

ParameterizedTest(swap_rows_params *param, row_operations, swap_rows) {

  size_t rows = param->rows;
  size_t cols = param->cols;

  cm_mat_t *orig_mat = cm_mat_alloc(rows, cols);

  for (size_t j = 0; j < rows; ++j) {
    for (size_t k = 0; k < cols; ++k) {
      cm_mat_set(orig_mat, j, k, (double)(j + 10) * 1e10);
    }
  }

  cm_mat_t *scaled_mat = cm_mat_create_from_matrix(orig_mat);
  cm_mat_swap_rows(scaled_mat, param->row_a, param->row_b);

  for (size_t i = 0; i < cols; ++i) {
    cr_assert(ieee_ulp_eq(dbl, cm_mat_get(scaled_mat, param->row_b, i),
                          cm_mat_get(orig_mat, param->row_a, i), 4));
    cr_assert(ieee_ulp_eq(dbl, cm_mat_get(scaled_mat, param->row_a, i),
                          cm_mat_get(orig_mat, param->row_b, i), 4));
  }

  cm_mat_free(orig_mat);
  cm_mat_free(scaled_mat);
}

/************************** Scale Sum Rows Tests ****************************/

typedef struct {
  size_t rows;
  size_t cols;
  size_t row_scaled;
  size_t row_sum;
  double scale_by;
} scale_sum_rows_params;

ParameterizedTestParameters(row_operations, scale_sum_rows) {
  static scale_sum_rows_params params[] = {
      {1, 1, 0, 0, 10.12345},      {10, 10, 0, 9, 0.123456},
      {50, 25, 9, 24, 4.2e-10},    {100, 150, 99, 0, 3.1415e5},
      {1000, 1000, 999, 999, 0.1},
  };

  size_t params_size = sizeof(params) / sizeof(scale_sum_rows_params);

  return cr_make_param_array(scale_sum_rows_params, params, params_size);
}

ParameterizedTest(scale_sum_rows_params *param, row_operations,
                  scale_sum_rows) {

  size_t rows = param->rows;
  size_t cols = param->cols;

  cm_mat_t *orig_mat = cm_mat_alloc(rows, cols);

  for (size_t j = 0; j < rows; ++j) {
    for (size_t k = 0; k < cols; ++k) {
      cm_mat_set(orig_mat, j, k, (double)(j + 10) * 1e10);
    }
  }

  cm_mat_t *scaled_mat = cm_mat_create_from_matrix(orig_mat);
  cm_mat_scale_sum_rows(scaled_mat, param->row_scaled, param->row_sum,
                        param->scale_by);

  for (size_t i = 0; i < cols; ++i) {
    double expected_val =
        cm_mat_get(orig_mat, param->row_scaled, i) * param->scale_by +
        cm_mat_get(orig_mat, param->row_sum, i);

    cr_assert(ieee_ulp_eq(dbl, cm_mat_get(scaled_mat, param->row_sum, i),
                          expected_val, 4));
  }

  cm_mat_free(orig_mat);
  cm_mat_free(scaled_mat);
}
