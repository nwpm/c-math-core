#include "../../src/matrix/cm_matrix_double.h"
#include "../Unity/src/unity.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void setUp() {}
void tearDown() {}

// TODO add corner cases for all tests

// create_from_matrix + set_all + is_equal

void check_create_from_matrix(size_t orig_rows, size_t orig_cols,
                              double init_val) {

  CmMatrixDouble *source = cm_matrix_double_alloc(orig_rows, orig_cols);
  TEST_ASSERT_NOT_NULL(source);

  cm_matrix_double_set_all(source, init_val);

  CmMatrixDouble *copy = cm_matrix_double_create_from_matrix(source);
  TEST_ASSERT_NOT_NULL(copy);

  TEST_ASSERT_TRUE(cm_matrix_double_is_equal(source, copy));

  cm_matrix_double_free(source);
  cm_matrix_double_free(copy);
}

void test_create_from_matrix_rows_1_cols_1() {
  check_create_from_matrix(1, 1, 5.);
}
void test_create_from_matrix_rows_1_cols_5() {
  check_create_from_matrix(1, 5, 5.);
}
void test_create_from_matrix_rows_5_cols_1() {
  check_create_from_matrix(5, 1, 5.);
}
void test_create_from_matrix_rows_100_cols_100() {
  check_create_from_matrix(100, 100, 5.);
}

// Set Identity + is identity

void check_set_identity(size_t orig_rows, size_t orig_cols,
                        CmMatrixCode end_status) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(orig_rows, orig_cols);
  TEST_ASSERT_NOT_NULL(matrix);

  CmMatrixCode res_code = cm_matrix_double_set_identity(matrix);

  TEST_ASSERT_EQUAL(end_status, res_code);

  if (end_status == CM_SUCCESS) {
    TEST_ASSERT_TRUE(cm_matrix_double_is_identity(matrix));
  }

  cm_matrix_double_free(matrix);
}

void test_set_identity_rows_1_cols_1() { check_set_identity(1, 1, CM_SUCCESS); }
void test_set_identity_rows_5_cols_5() { check_set_identity(5, 5, CM_SUCCESS); }
void test_set_identity_rows_25_cols_25() {
  check_set_identity(25, 25, CM_SUCCESS);
}
void test_set_identity_rows_100_cols_100() {
  check_set_identity(100, 100, CM_SUCCESS);
}
void test_set_identity_rows_12_cols_5() {
  check_set_identity(12, 5, CM_ERR_MATRIX_NOT_SQUARE);
}
void test_set_identity_null_check() {
  TEST_ASSERT_EQUAL(CM_ERR_NULL_POINTER, cm_matrix_double_set_identity(NULL));
}

// set_zero + is zero matrix

void check_set_zero(size_t orig_rows, size_t orig_cols,
                    CmMatrixCode end_status) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(orig_rows, orig_cols);
  TEST_ASSERT_NOT_NULL(matrix);

  CmMatrixCode res_code = cm_matrix_double_set_zero(matrix);
  TEST_ASSERT_EQUAL(end_status, res_code);
  TEST_ASSERT_TRUE(cm_matrix_double_is_null(matrix));

  cm_matrix_double_free(matrix);
}

void test_set_zero_rows_1_cols_1() { check_set_zero(1, 1, CM_SUCCESS); }
void test_set_zero_rows_5_cols_5() { check_set_zero(5, 5, CM_SUCCESS); }
void test_set_zero_rows_15_cols_5() { check_set_zero(5, 5, CM_SUCCESS); }
void test_set_zero_rows_25_cols_25() { check_set_zero(25, 25, CM_SUCCESS); }
void test_set_zero_rows_55_cols_15() { check_set_zero(55, 15, CM_SUCCESS); }
void test_set_zero_rows_100_cols_100() { check_set_zero(100, 100, CM_SUCCESS); }
void test_set_zero_null_check() {
  TEST_ASSERT_EQUAL(CM_ERR_NULL_POINTER, cm_matrix_double_set_zero(NULL));
}

// swap + get

void check_swap(size_t matrix_a_rows, size_t matrix_a_cols,
                size_t matrix_b_rows, size_t matrix_b_cols, double init_a,
                double init_b) {

  CmMatrixDouble *matrix_a =
      cm_matrix_double_alloc(matrix_a_rows, matrix_a_cols);
  TEST_ASSERT_NOT_NULL(matrix_a);

  cm_matrix_double_set_all(matrix_a, init_a);

  CmMatrixDouble *matrix_b =
      cm_matrix_double_alloc(matrix_b_rows, matrix_b_cols);
  TEST_ASSERT_NOT_NULL(matrix_b);

  cm_matrix_double_set_all(matrix_b, init_b);

  cm_matrix_double_swap(&matrix_a, &matrix_b);

  TEST_ASSERT_EQUAL_size_t(matrix_a_rows, matrix_b->rows);
  TEST_ASSERT_EQUAL_size_t(matrix_a_cols, matrix_b->columns);

  TEST_ASSERT_EQUAL_size_t(matrix_b_rows, matrix_a->rows);
  TEST_ASSERT_EQUAL_size_t(matrix_b_cols, matrix_a->columns);

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(init_b, cm_matrix_double_get(matrix_a, i, j));
    }
  }

  for (size_t i = 0; i < matrix_b->rows; ++i) {
    for (size_t j = 0; j < matrix_b->columns; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(init_a, cm_matrix_double_get(matrix_b, i, j));
    }
  }

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
}

void test_swap_matrix_a_rows_8_cols_1_matrix_b_rows_5_cols_10() {
  check_swap(8, 1, 5, 10, 3., 9.);
}
void test_swap_matrix_a_rows_14_cols_23_matrix_b_rows_3_cols_44() {
  check_swap(14, 23, 3, 44, 10., 23.);
}
void test_swap_matrix_a_rows_10_cols_10_matrix_b_rows_10_cols_10() {
  check_swap(10, 10, 10, 10, 3., 3.);
}
void test_swap_matrix_a_rows_113_cols_133_matrix_b_rows_144_cols_244() {
  check_swap(113, 133, 144, 244, 0., 43.);
}
void test_swap_matrix_a_rows_410_cols_410_matrix_b_rows_510_cols_510() {
  check_swap(410, 410, 510, 510, 100., 500.);
}

// transpose

void check_transpose(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  double init_val = 1.;
  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      cm_matrix_double_set(matrix, i, j, init_val++);
    }
  }

  cm_matrix_double_transpose(&matrix);

  init_val = 1.;
  for (size_t i = 0; i < matrix->columns; ++i) {
    for (size_t j = 0; j < matrix->rows; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(init_val, cm_matrix_double_get(matrix, j, i));
      init_val++;
    }
  }

  cm_matrix_double_free(matrix);
}

void test_transpose_rows_1_cols_1() { check_transpose(1, 1); }
void test_transpose_rows_5_cols_5() { check_transpose(5, 5); }
void test_transpose_rows_2_cols_3() { check_transpose(2, 3); }
void test_transpose_rows_15_cols_7() { check_transpose(15, 7); }
void test_transpose_rows_65_cols_97() { check_transpose(65, 97); }
void test_transpose_rows_239_cols_432() { check_transpose(239, 432); }

// max

void check_max(size_t rows, size_t cols, double max_elem, size_t max_elem_row,
               size_t max_elem_col) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);
  cm_matrix_double_set(matrix, max_elem_row, max_elem_col, max_elem);

  double max_current = 0.;
  cm_matrix_double_max(matrix, &max_current);

  TEST_ASSERT_EQUAL_DOUBLE(max_elem, max_current);
  cm_matrix_double_free(matrix);
}

void test_max_rows_3_cols_3_expected_100() { check_max(3, 3, 100., 0, 1); }
void test_max_rows_10_cols_5_expected_100() { check_max(10, 5, 100., 4, 3); }
void test_max_rows_25_cols_25_expected_100() {
  check_max(25, 25, 100., 11, 17);
}
void test_max_rows_90_cols_120_expected_100() {
  check_max(90, 120, 100., 39, 71);
}
void test_max_rows_150_cols_150_expected_100() {
  check_max(150, 150, 100., 100, 120);
}

// min

void check_min(size_t rows, size_t cols, double min_elem, size_t min_elem_row,
               size_t min_elem_col) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);
  cm_matrix_double_set(matrix, min_elem_row, min_elem_col, min_elem);

  double min_current = 0.;
  cm_matrix_double_min(matrix, &min_current);

  TEST_ASSERT_EQUAL_DOUBLE(min_elem, min_current);
  cm_matrix_double_free(matrix);
}

void test_min_rows_3_cols_3_expected_minus_10() { check_min(3, 3, -10., 0, 1); }
void test_min_rows_10_cols_5_expected_minus_10() {
  check_min(10, 5, -10., 4, 3);
}
void test_min_rows_25_cols_25_expected_minus_10() {
  check_min(25, 25, -10., 11, 17);
}
void test_min_rows_90_cols_120_expected_minus_10() {
  check_min(90, 120, -10., 39, 71);
}
void test_min_rows_150_cols_150_expected_minus_10() {
  check_min(150, 150, -10., 100, 120);
}

// trace

void check_trace(size_t rows, size_t cols, double res,
                 CmMatrixCode end_status) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);

  double trace = 0.;
  CmMatrixCode res_code = cm_matrix_double_trace(matrix, &trace);
  TEST_ASSERT_EQUAL(res_code, end_status);

  TEST_ASSERT_EQUAL_DOUBLE(res, trace);
  cm_matrix_double_free(matrix);
}

void test_trace_rows_3_cols_3() { check_trace(3, 3, 3, CM_SUCCESS); }
void test_trace_rows_10_cols_10() { check_trace(10, 10, 10, CM_SUCCESS); }
void test_trace_rows_25_cols_25() { check_trace(25, 25, 25, CM_SUCCESS); }
void test_trace_rows_120_cols_120() { check_trace(120, 120, 120, CM_SUCCESS); }
void test_trace_rows_150_cols_150() { check_trace(150, 150, 150, CM_SUCCESS); }
void test_trace_rows_5_cols_15() {
  check_trace(5, 15, 0, CM_ERR_MATRIX_NOT_SQUARE);
}

// det
void check_det(size_t rows, size_t cols, double res, double *init_data) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  size_t k = 0;
  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      cm_matrix_double_set(matrix, i, j, init_data[k++]);
    }
  }

  double det_current = 0.;
  cm_matrix_double_det(matrix, &det_current);

  TEST_ASSERT_EQUAL_DOUBLE(res, det_current);
  cm_matrix_double_free(matrix);
}

void check_det_identity(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_identity(matrix);

  double det_current = 0.;
  cm_matrix_double_det(matrix, &det_current);

  TEST_ASSERT_EQUAL_DOUBLE(1, det_current);
  cm_matrix_double_free(matrix);
}

void check_det_zero(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_zero(matrix);

  double det_current = 0.;
  cm_matrix_double_det(matrix, &det_current);

  TEST_ASSERT_EQUAL_DOUBLE(0, det_current);
  cm_matrix_double_free(matrix);
}

void test_det_identity_size_2x2() { (check_det_identity(2, 2)); }
void test_det_identity_size_3x3() { (check_det_identity(3, 3)); }
void test_det_identity_size_4x4() { (check_det_identity(4, 4)); }
void test_det_identity_size_5x5() { (check_det_identity(5, 5)); }

void test_det_zero_size_2x2() { (check_det_zero(2, 2)); }
void test_det_zero_size_3x3() { (check_det_zero(3, 3)); }
void test_det_zero_size_4x4() { (check_det_zero(4, 4)); }
void test_det_zero_size_5x5() { (check_det_zero(5, 5)); }

void test_det_rows_1_cols_1() {
  double init_data[] = {5.};
  check_det(1, 1, 5., init_data);
}
void test_det_rows_2_cols_2() {
  double init_data[] = {5., 11., 28., -10.};
  check_det(2, 2, -358., init_data);
}
void test_det_rows_3_cols_3() {
  double init_data[] = {2., -4., 1., 7., 11., -5., 1., 9., 3.};
  check_det(3, 3, 312., init_data);
}
void test_det_rows_4_cols_4() {
  double init_data[] = {2., -4., 1., 8.,  7., 11., -5., -1.,
                        1., 9.,  3., 16., 3., -8., 10., 4};
  check_det(4, 4, -12901, init_data);
}
void test_det_rows_5_cols_5() {
  double init_data[] = {
      2.,  -4., 1., 8.,  3.,  7., 11., -5., -1., 8., 1., 9., 3.,
      16., -4., 3., -8., 10., 4., 0.,  -6., 3.,  7., 5., 0.,
  };
  check_det(5, 5, -165350, init_data);
}

// add

void check_add(size_t rows_a, size_t cols_a, size_t rows_b, size_t cols_b,
               double init_val_a, double init_val_b, CmMatrixCode end_status) {

  CmMatrixDouble *matrix_a = cm_matrix_double_alloc(rows_a, cols_a);
  TEST_ASSERT_NOT_NULL(matrix_a);

  CmMatrixDouble *matrix_b = cm_matrix_double_alloc(rows_b, cols_b);
  TEST_ASSERT_NOT_NULL(matrix_b);

  cm_matrix_double_set_all(matrix_a, init_val_a);
  cm_matrix_double_set_all(matrix_b, init_val_b);

  CmMatrixCode res = cm_matrix_double_add(matrix_a, matrix_b);
  TEST_ASSERT_EQUAL(end_status, res);

  if (end_status == CM_SUCCESS) {
    double res_val = init_val_a + init_val_b;
    for (size_t i = 0; i < rows_a; ++i) {
      for (size_t j = 0; j < cols_b; ++j) {
        TEST_ASSERT_EQUAL_DOUBLE(res_val, cm_matrix_double_get(matrix_a, i, j));
      }
    }
  }

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
}

void test_add_rows_2_cols_4() { check_add(2, 4, 2, 4, 5., 10., CM_SUCCESS); }
void test_add_rows_10_cols_10() {
  check_add(10, 10, 10, 10, 12., 34., CM_SUCCESS);
}
void test_add_rows_57_cols_11() {
  check_add(57, 11, 57, 11, 32., 90., CM_SUCCESS);
}
void test_add_rows_142_cols_384() {
  check_add(142, 384, 142, 384, 129., 341., CM_SUCCESS);
}
void test_add_diff_size() {
  check_add(12, 12, 2, 2, 9., 4., CM_ERR_SIZE_MISMATCH);
}

// diff

void check_sub(size_t rows_a, size_t cols_a, size_t rows_b, size_t cols_b,
               double init_val_a, double init_val_b, CmMatrixCode end_status) {

  CmMatrixDouble *matrix_a = cm_matrix_double_alloc(rows_a, cols_a);
  TEST_ASSERT_NOT_NULL(matrix_a);

  CmMatrixDouble *matrix_b = cm_matrix_double_alloc(rows_b, cols_b);
  TEST_ASSERT_NOT_NULL(matrix_b);

  cm_matrix_double_set_all(matrix_a, init_val_a);
  cm_matrix_double_set_all(matrix_b, init_val_b);

  CmMatrixCode res = cm_matrix_double_sub(matrix_a, matrix_b);
  TEST_ASSERT_EQUAL(end_status, res);

  if (end_status == CM_SUCCESS) {
    double res_val = init_val_a - init_val_b;
    for (size_t i = 0; i < rows_a; ++i) {
      for (size_t j = 0; j < cols_b; ++j) {
        TEST_ASSERT_EQUAL_DOUBLE(res_val, cm_matrix_double_get(matrix_a, i, j));
      }
    }
  }

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
}

void test_sub_rows_2_cols_4() { check_sub(2, 4, 2, 4, 5., 10., CM_SUCCESS); }
void test_sub_rows_10_cols_10() {
  check_sub(10, 10, 10, 10, 12., 34., CM_SUCCESS);
}
void test_sub_rows_57_cols_11() {
  check_sub(57, 11, 57, 11, 32., 90., CM_SUCCESS);
}
void test_sub_rows_142_cols_384() {
  check_sub(142, 384, 142, 384, 129., 341., CM_SUCCESS);
}
void test_sub_diff_size() {
  check_sub(12, 12, 2, 2, 9., 4., CM_ERR_SIZE_MISMATCH);
}

// scale

void check_scale(size_t rows, size_t cols, double init_val, double scale_val) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);
  TEST_ASSERT_NOT_NULL(matrix);

  cm_matrix_double_set_all(matrix, init_val);

  cm_matrix_double_scale(matrix, scale_val);

  double res_val = init_val * scale_val;
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(res_val, cm_matrix_double_get(matrix, i, j));
    }
  }

  cm_matrix_double_free(matrix);
}

void test_scale_rows_2_cols_4() { check_scale(2, 4, 5, 2); }
void test_scale_rows_10_cols_10() { check_scale(10, 10, 10, 9); }
void test_scale_rows_57_cols_11() { check_scale(57, 11, 48, 3); }
void test_scale_rows_142_cols_384() { check_scale(142, 384, 124, 9); }
void test_scale_rows_441_cols_507() { check_scale(441, 507, 29, 0); }

// mul

void check_mul_hand(size_t rows_a, size_t cols_a, size_t rows_b, size_t cols_b,
                    double *init_data_a, double *init_data_b,
                    double *res_data) {

  CmMatrixDouble *matrix_a = cm_matrix_double_alloc(rows_a, cols_a);
  TEST_ASSERT_NOT_NULL(matrix_a);

  CmMatrixDouble *matrix_b = cm_matrix_double_alloc(rows_b, cols_b);
  TEST_ASSERT_NOT_NULL(matrix_b);

  size_t k = 0;
  for (size_t i = 0; i < rows_a; ++i) {
    for (size_t j = 0; j < cols_a; ++j) {
      cm_matrix_double_set(matrix_a, i, j, init_data_a[k++]);
    }
  }

  k = 0;
  for (size_t i = 0; i < rows_b; ++i) {
    for (size_t j = 0; j < cols_b; ++j) {
      cm_matrix_double_set(matrix_b, i, j, init_data_b[k++]);
    }
  }

  CmMatrixDouble *matrix_res = cm_matrix_double_mul(matrix_a, matrix_b);
  TEST_ASSERT_NOT_NULL(matrix_res);
  TEST_ASSERT_EQUAL_size_t(rows_a, matrix_res->rows);
  TEST_ASSERT_EQUAL_size_t(cols_b, matrix_res->columns);

  k = 0;
  for (size_t i = 0; i < matrix_res->rows; ++i) {
    for (size_t j = 0; j < matrix_res->columns; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(res_data[k],
                               cm_matrix_double_get(matrix_res, i, j));
      k++;
    }
  }

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
  cm_matrix_double_free(matrix_res);
}

void check_mul_auto(size_t rows_a, size_t cols_a, size_t rows_b, size_t cols_b,
                    double init_val_a, double init_val_b, double res_val) {

  CmMatrixDouble *matrix_a = cm_matrix_double_alloc(rows_a, cols_a);
  TEST_ASSERT_NOT_NULL(matrix_a);

  CmMatrixDouble *matrix_b = cm_matrix_double_alloc(rows_b, cols_b);
  TEST_ASSERT_NOT_NULL(matrix_b);

  cm_matrix_double_set_all(matrix_a, init_val_a);
  cm_matrix_double_set_all(matrix_b, init_val_b);

  CmMatrixDouble *matrix_res = cm_matrix_double_mul(matrix_a, matrix_b);
  TEST_ASSERT_NOT_NULL(matrix_res);
  TEST_ASSERT_EQUAL_size_t(rows_a, matrix_res->rows);
  TEST_ASSERT_EQUAL_size_t(cols_b, matrix_res->columns);

  size_t k = 0;
  for (size_t i = 0; i < matrix_res->rows; ++i) {
    for (size_t j = 0; j < matrix_res->columns; ++j) {
      TEST_ASSERT_EQUAL_DOUBLE(res_val, cm_matrix_double_get(matrix_res, i, j));
      k++;
    }
  }

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
  cm_matrix_double_free(matrix_res);
}

void test_mul_mat_a_rows_2_cols_2_mat_b_rows_2_cols_2() {
  double arr_a[] = {3., 4., 1., 9.};
  double arr_b[] = {8., 13., 6., 2.};
  double res[] = {48., 47., 62., 31.};

  check_mul_hand(2, 2, 2, 2, arr_a, arr_b, res);
}

void test_mul_mat_a_rows_2_cols_4_mat_b_rows_4_cols_3() {
  double arr_a[] = {
      3., 4., 1., 9., 15., 19., 3., 17.,
  };
  double arr_b[] = {
      8., 13., 6., 2., 11., 16., 9., 14., 5., 17., 1., 0.,
  };
  double res[] = {194., 106., 87., 474., 463., 409};

  check_mul_hand(2, 4, 4, 3, arr_a, arr_b, res);
}

void test_mul_mat_a_rows_3_cols_3_mat_b_rows_3_cols_3() {
  double arr_a[] = {
      12., 2., 32., -25., -19., 6., 17., -10., 1.,
  };
  double arr_b[] = {
      -1., 14., 41., 18., -9., 7., 15., 37., -11.,
  };
  double res[] = {
      504., 1334., 154., -227., 43., -1224., -182., 365., 616.,
  };

  check_mul_hand(3, 3, 3, 3, arr_a, arr_b, res);
}
void test_mul_auto_mat_a_rows_2_cols_2_mat_b_rows_2_cols_2() {
  check_mul_auto(2, 2, 2, 2, 2, 3, 12);
}

void test_mul_auto_mat_a_rows_3_cols_3_mat_b_rows_3_cols_3() {
  check_mul_auto(3, 3, 3, 3, 5, 7, 105);
}

void test_mul_auto_mat_a_rows_4_cols_4_mat_b_rows_4_cols_4() {
  check_mul_auto(4, 4, 4, 4, 10, 11, 440);
}

void test_mul_auto_mat_a_rows_5_cols_5_mat_b_rows_5_cols_5() {
  check_mul_auto(5, 5, 5, 5, 23, 15, 1725);
}

void test_mul_auto_mat_a_rows_3_cols_3_mat_b_identity() {
  double arr_a[] = {
      12., 2., 32., -25., -19., 6., 17., -10., 1.,
  };
  double arr_b[] = {
      1., 0., 0., 0., 1., 0., 0., 0., 1.,
  };

  check_mul_hand(3, 3, 3, 3, arr_a, arr_b, arr_a);
}

void test_mul_auto_mat_a_rows_5_cols_5_mat_b_zero() {
  check_mul_auto(5, 5, 5, 5, 3, 0, 0);
}

void test_mul_size_mismatch() {

  CmMatrixDouble *matrix_a = cm_matrix_double_alloc(5, 10);
  TEST_ASSERT_NOT_NULL(matrix_a);

  CmMatrixDouble *matrix_b = cm_matrix_double_alloc(5, 10);
  TEST_ASSERT_NOT_NULL(matrix_b);

  TEST_ASSERT_NULL(cm_matrix_double_mul(matrix_a, matrix_b));

  cm_matrix_double_free(matrix_a);
  cm_matrix_double_free(matrix_b);
}
int main() {

  UNITY_BEGIN();

  puts("\nCreate_from_matrix + set_all + is_equal\n");
  RUN_TEST(test_create_from_matrix_rows_1_cols_1);
  RUN_TEST(test_create_from_matrix_rows_1_cols_5);
  RUN_TEST(test_create_from_matrix_rows_5_cols_1);
  RUN_TEST(test_create_from_matrix_rows_100_cols_100);

  puts("\nSet identity + is identity\n");
  RUN_TEST(test_set_identity_rows_1_cols_1);
  RUN_TEST(test_set_identity_rows_5_cols_5);
  RUN_TEST(test_set_identity_rows_25_cols_25);
  RUN_TEST(test_set_identity_rows_100_cols_100);
  RUN_TEST(test_set_identity_rows_12_cols_5);
  RUN_TEST(test_set_identity_null_check);

  puts("\nSet zero + is zero\n");
  RUN_TEST(test_set_zero_rows_1_cols_1);
  RUN_TEST(test_set_zero_rows_5_cols_5);
  RUN_TEST(test_set_zero_rows_15_cols_5);
  RUN_TEST(test_set_zero_rows_25_cols_25);
  RUN_TEST(test_set_zero_rows_55_cols_15);
  RUN_TEST(test_set_zero_rows_100_cols_100);

  puts("\nswap + get\n");
  RUN_TEST(test_swap_matrix_a_rows_8_cols_1_matrix_b_rows_5_cols_10);
  RUN_TEST(test_swap_matrix_a_rows_410_cols_410_matrix_b_rows_510_cols_510);
  RUN_TEST(test_swap_matrix_a_rows_10_cols_10_matrix_b_rows_10_cols_10);
  RUN_TEST(test_swap_matrix_a_rows_113_cols_133_matrix_b_rows_144_cols_244);
  RUN_TEST(test_swap_matrix_a_rows_14_cols_23_matrix_b_rows_3_cols_44);

  puts("\ntranspose\n");
  RUN_TEST(test_transpose_rows_1_cols_1);
  RUN_TEST(test_transpose_rows_2_cols_3);
  RUN_TEST(test_transpose_rows_5_cols_5);
  RUN_TEST(test_transpose_rows_15_cols_7);
  RUN_TEST(test_transpose_rows_65_cols_97);
  RUN_TEST(test_transpose_rows_239_cols_432);

  puts("\nmax\n");
  RUN_TEST(test_max_rows_3_cols_3_expected_100);
  RUN_TEST(test_max_rows_10_cols_5_expected_100);
  RUN_TEST(test_max_rows_25_cols_25_expected_100);
  RUN_TEST(test_max_rows_90_cols_120_expected_100);
  RUN_TEST(test_max_rows_150_cols_150_expected_100);

  puts("\nmin\n");
  RUN_TEST(test_min_rows_3_cols_3_expected_minus_10);
  RUN_TEST(test_min_rows_10_cols_5_expected_minus_10);
  RUN_TEST(test_min_rows_25_cols_25_expected_minus_10);
  RUN_TEST(test_min_rows_90_cols_120_expected_minus_10);
  RUN_TEST(test_min_rows_150_cols_150_expected_minus_10);

  puts("\ntrace\n");
  RUN_TEST(test_trace_rows_3_cols_3);
  RUN_TEST(test_trace_rows_10_cols_10);
  RUN_TEST(test_trace_rows_25_cols_25);
  RUN_TEST(test_trace_rows_120_cols_120);
  RUN_TEST(test_trace_rows_150_cols_150);
  RUN_TEST(test_trace_rows_5_cols_15);

  puts("\ndet\n");
  RUN_TEST(test_det_identity_size_2x2);
  RUN_TEST(test_det_identity_size_3x3);
  RUN_TEST(test_det_identity_size_4x4);
  RUN_TEST(test_det_identity_size_5x5);

  RUN_TEST(test_det_zero_size_2x2);
  RUN_TEST(test_det_zero_size_3x3);
  RUN_TEST(test_det_zero_size_4x4);
  RUN_TEST(test_det_zero_size_5x5);

  RUN_TEST(test_det_rows_1_cols_1);
  RUN_TEST(test_det_rows_2_cols_2);
  RUN_TEST(test_det_rows_3_cols_3);
  RUN_TEST(test_det_rows_4_cols_4);
  RUN_TEST(test_det_rows_5_cols_5);

  puts("\nadd\n");
  RUN_TEST(test_add_rows_2_cols_4);
  RUN_TEST(test_add_rows_10_cols_10);
  RUN_TEST(test_add_rows_57_cols_11);
  RUN_TEST(test_add_rows_142_cols_384);
  RUN_TEST(test_add_diff_size);

  puts("\nsub\n");
  RUN_TEST(test_sub_rows_2_cols_4);
  RUN_TEST(test_sub_rows_10_cols_10);
  RUN_TEST(test_sub_rows_57_cols_11);
  RUN_TEST(test_sub_rows_142_cols_384);
  RUN_TEST(test_sub_diff_size);

  puts("\nscale\n");
  RUN_TEST(test_scale_rows_2_cols_4);
  RUN_TEST(test_scale_rows_10_cols_10);
  RUN_TEST(test_scale_rows_57_cols_11);
  RUN_TEST(test_scale_rows_142_cols_384);
  RUN_TEST(test_scale_rows_441_cols_507);

  puts("\nmul\n");
  RUN_TEST(test_mul_mat_a_rows_2_cols_2_mat_b_rows_2_cols_2);
  RUN_TEST(test_mul_mat_a_rows_2_cols_4_mat_b_rows_4_cols_3);
  RUN_TEST(test_mul_mat_a_rows_3_cols_3_mat_b_rows_3_cols_3);
  RUN_TEST(test_mul_auto_mat_a_rows_2_cols_2_mat_b_rows_2_cols_2);
  RUN_TEST(test_mul_auto_mat_a_rows_3_cols_3_mat_b_rows_3_cols_3);
  RUN_TEST(test_mul_auto_mat_a_rows_4_cols_4_mat_b_rows_4_cols_4);
  RUN_TEST(test_mul_auto_mat_a_rows_5_cols_5_mat_b_rows_5_cols_5);
  RUN_TEST(test_mul_auto_mat_a_rows_3_cols_3_mat_b_identity);
  RUN_TEST(test_mul_auto_mat_a_rows_5_cols_5_mat_b_zero);
  RUN_TEST(test_mul_size_mismatch);

  return UNITY_END();
}
