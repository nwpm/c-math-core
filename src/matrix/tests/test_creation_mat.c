#include "../../../include/cmathcore/matrix.h"
#include <criterion/alloc.h>
#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/parameterized.h>
#include <criterion/theories.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/************************** Allocation Tests ****************************/

TheoryDataPoints(creation, alloc_matrix) = {
    DataPoints(size_t, 1, 5, 50, 250, 1000),
    DataPoints(size_t, 1, 5, 50, 250, 1000),
};

Theory((size_t rows, size_t cols), creation, alloc_matrix) {

  cm_mat_t *mat = cm_mat_alloc(rows, cols);

  cr_assert_neq(mat, NULL);
  cr_assert_eq(cm_mat_rows(mat), rows);
  cr_assert_eq(cm_mat_cols(mat), cols);

  cm_mat_free(mat);
}

/************************** Create Zero Tests ****************************/
TheoryDataPoints(creation, create_zero_matrix) = {
    DataPoints(size_t, 1, 5, 50, 250, 1000),
    DataPoints(size_t, 1, 5, 50, 250, 1000),
};

Theory((size_t rows, size_t cols), creation, create_zero_matrix) {

  cm_mat_t *mat = cm_mat_create_zero(rows, cols);

  cr_assert_neq(mat, NULL);
  cr_assert_eq(cm_mat_rows(mat), rows);
  cr_assert_eq(cm_mat_cols(mat), cols);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, j), 0., 4));
    }
  }

  cm_mat_free(mat);
}

/************************** Create Identity Tests ****************************/
TheoryDataPoints(creation, create_identity_matrix) = {
    DataPoints(size_t, 1, 5, 50, 250, 1000),
};

Theory((size_t size), creation, create_identity_matrix) {

  cm_mat_t *mat = cm_mat_create_identity(size);

  for (size_t i = 0; i < size; ++i) {
    for (size_t j = 0; j < size; ++j) {
      if (i == j) {
        cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, j), 1., 4));
      } else {
        cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, j), 0., 4));
      }
    }
  }

  cm_mat_free(mat);
}

/************************** Create Diagonal Tests ****************************/
typedef struct {
  size_t size;
  double init_val;
} create_diag_params;

ParameterizedTestParameters(creation, create_diag_matrix) {
  static create_diag_params params[] = {
      {1, 2.},      {5, 1.23456},           {25, 6.54321},
      {500, 1e-10}, {1000, 1.123456789e10},
  };

  size_t params_size = sizeof(params) / sizeof(create_diag_params);
  return cr_make_param_array(create_diag_params, params, params_size);
}

ParameterizedTest(create_diag_params *param, creation, create_diag_matrix) {

  cm_mat_t *mat = cm_mat_create_diag(param->size, param->init_val);

  for (size_t i = 0; i < param->size; ++i) {
    for (size_t j = 0; j < param->size; ++j) {
      if (i == j) {
        cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, j), param->init_val, 4));
      } else {
        cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, j), 0., 4));
      }
    }
  }

  cm_mat_free(mat);
}

/************************** Copy Tests ****************************/
TheoryDataPoints(creation, create_copy_matrix) = {
    DataPoints(size_t, 1, 5, 50, 250, 1000),
    DataPoints(size_t, 1, 5, 50, 250, 1000),
};

Theory((size_t rows, size_t cols), creation, create_copy_matrix) {

  cm_mat_t *src = cm_mat_alloc(rows, cols);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cm_mat_set(src, i, j, (i + j) * 1e-16);
    }
  }

  cm_mat_t *copy = cm_mat_create_from_matrix(src);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cr_assert(
          ieee_ulp_eq(dbl, cm_mat_get(copy, i, j), cm_mat_get(src, i, j), 4));
    }
  }

  cm_mat_free(src);
  cm_mat_free(copy);
}

/******************** Create From Array Tests **********************/
typedef struct {
  size_t rows;
  size_t cols;
  double **src_array;
} create_from_array_params;

void cleanup_create_from_arr_params(struct criterion_test_params *ctp) {
  create_from_array_params *params = (create_from_array_params *)ctp->params;

  for (size_t i = 0; i < params->rows; ++i) {
    cr_free(params->src_array[i]);
  }

  cr_free(params->src_array);
}

ParameterizedTestParameters(creation, create_matrix_from_arr) {
  static create_from_array_params params[] = {
      {1, 1, NULL},     {5, 3, NULL},       {50, 150, NULL},
      {250, 300, NULL}, {1000, 1000, NULL},
  };

  size_t params_size = sizeof(params) / sizeof(create_from_array_params);

  for (size_t i = 0; i < params_size; ++i) {

    size_t rows = params[i].rows;
    size_t cols = params[i].cols;

    params[i].src_array = cr_malloc(sizeof(double *) * rows);

    for (size_t j = 0; j < rows; ++j) {
      params[i].src_array[j] = cr_malloc(sizeof(double) * cols);

      for (size_t m = 0; m < cols; ++m) {
        params[i].src_array[j][m] = (double)(j + 10) * 1e10;
      }
    }
  }

  return cr_make_param_array(create_from_array_params, params, params_size,
                             cleanup_create_from_arr_params);
}

ParameterizedTest(create_from_array_params *param, creation,
                  create_matrix_from_arr) {

  cm_mat_t *mat =
      cm_mat_create_from_array(param->src_array, param->rows, param->cols);

  size_t rows = cm_mat_rows(mat);
  size_t cols = cm_mat_cols(mat);

  cr_assert_eq(rows, param->rows);
  cr_assert_eq(cols, param->cols);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cr_assert(
          ieee_ulp_eq(dbl, cm_mat_get(mat, i, j), (double)(i + 10) * 1e10, 4));
    }
  }

  cm_mat_free(mat);
}

/************************** Create Col Tests ****************************/

typedef struct {
  size_t src_rows;
  size_t src_cols;
  size_t create_from_col;
  cm_mat_t *src_mat;
} create_col_params;

ParameterizedTestParameters(creation, create_column_matrix) {
  static create_col_params params[] = {
      {1, 1, 0, NULL},       {5, 5, 4, NULL},   {25, 10, 9, NULL},
      {500, 400, 399, NULL}, {100, 1, 0, NULL}, {1000, 1200, 500, NULL},
  };

  size_t params_size = sizeof(params) / sizeof(create_col_params);

  return cr_make_param_array(create_col_params, params, params_size);
}

ParameterizedTest(create_col_params *param, creation, create_column_matrix) {

  size_t rows = param->src_rows;
  size_t cols = param->src_cols;

  param->src_mat = cm_mat_alloc(rows, cols);

  for (size_t j = 0; j < rows; ++j) {
    for (size_t k = 0; k < cols; ++k) {
      cm_mat_set(param->src_mat, j, k, (double)(j + 10) * 1e10);
    }
  }

  cm_mat_t *mat = cm_mat_col(param->src_mat, param->create_from_col);

  size_t rows_c = cm_mat_rows(mat);
  size_t cols_c = cm_mat_cols(mat);

  cr_assert_eq(rows_c, param->src_rows);
  cr_assert_eq(cols_c, 1);

  for (size_t i = 0; i < rows; ++i) {
    cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, 0),
                          cm_mat_get(param->src_mat, i, param->create_from_col),
                          4));
  }

  cm_mat_free(mat);
  cm_mat_free(param->src_mat);
}

/************************** Create Row Tests ****************************/

typedef struct {
  size_t src_rows;
  size_t src_cols;
  size_t create_from_row;
  cm_mat_t *src_mat;
} create_row_params;

ParameterizedTestParameters(creation, create_row_matrix) {
  static create_row_params params[] = {
      {1, 1, 0, NULL},       {5, 5, 4, NULL},   {25, 10, 9, NULL},
      {500, 400, 399, NULL}, {100, 1, 0, NULL}, {1000, 1200, 500, NULL},
  };

  size_t params_size = sizeof(params) / sizeof(create_row_params);

  return cr_make_param_array(create_row_params, params, params_size);
}

ParameterizedTest(create_row_params *param, creation, create_row_matrix) {

  size_t rows = param->src_rows;
  size_t cols = param->src_cols;

  param->src_mat = cm_mat_alloc(rows, cols);

  for (size_t j = 0; j < rows; ++j) {
    for (size_t k = 0; k < cols; ++k) {
      cm_mat_set(param->src_mat, j, k, (double)(j + 10) * 1e10);
    }
  }

  cm_mat_t *mat = cm_mat_row(param->src_mat, param->create_from_row);

  size_t rows_r = cm_mat_rows(mat);
  size_t cols_r = cm_mat_cols(mat);

  cr_assert_eq(rows_r, 1);
  cr_assert_eq(cols_r, param->src_cols);

  for (size_t i = 0; i < cols; ++i) {
    cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, 0, i),
                          cm_mat_get(param->src_mat, param->create_from_row, i),
                          4));
  }

  cm_mat_free(mat);
  cm_mat_free(param->src_mat);
}

/************************** Submatrix ****************************/

typedef struct {
  size_t src_rows;
  size_t src_cols;
  size_t row_start;
  size_t row_end;
  size_t col_start;
  size_t col_end;
  cm_mat_t *src_mat;
} create_submatrix_params;

ParameterizedTestParameters(creation, create_submatrix) {

  static create_submatrix_params params[] = {
      {1, 1, 0, 0, 0, 0, NULL},           {1, 5, 0, 0, 0, 2, NULL},
      {5, 1, 0, 2, 0, 0, NULL},           {50, 50, 20, 25, 5, 10, NULL},
      {1000, 1000, 0, 999, 0, 999, NULL}, {2000, 3000, 0, 1999, 0, 1999, NULL},
  };

  size_t params_size = sizeof(params) / sizeof(create_submatrix_params);

  return cr_make_param_array(create_submatrix_params, params, params_size);
}

ParameterizedTest(create_submatrix_params *param, creation, create_submatrix) {

  size_t rows = param->src_rows;
  size_t cols = param->src_cols;

  param->src_mat = cm_mat_alloc(rows, cols);

  for (size_t j = 0; j < rows; ++j) {
    for (size_t k = 0; k < cols; ++k) {
      cm_mat_set(param->src_mat, j, k, (double)(j + 10) * 1e10);
    }
  }

  cm_mat_t *mat =
      cm_mat_submat(param->src_mat, param->row_start, param->row_end,
                    param->col_start, param->col_end);

  size_t rows_sb = cm_mat_rows(mat);
  size_t cols_sb = cm_mat_cols(mat);

  cr_assert_eq(rows_sb, param->row_end - param->row_start + 1);
  cr_assert_eq(cols_sb, param->col_end - param->col_start + 1);

  for (size_t i = 0; i < rows_sb; ++i) {
    for (size_t j = 0; j < cols_sb; ++j) {
      cr_assert(ieee_ulp_eq(dbl, cm_mat_get(mat, i, j),
                            cm_mat_get(param->src_mat, param->row_start + i,
                                       param->col_start + j),
                            4));
    }
  }

  cm_mat_free(mat);
  cm_mat_free(param->src_mat);
}
