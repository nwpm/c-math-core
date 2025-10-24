#include "cm_matrix_double.h"
#include "../utils/cm_checkers.h"
#include "../utils/cm_utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: make NULL check or not?
// TODO: error handler
// TODO: return codes only in debug build or return codes only in some
// functiuons

#ifdef DEBUG
void _cm_matrix_double_printf(const CmMatrixDouble *matrix) {

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      printf("%f ", matrix->data[i * matrix->columns + j]);
    }
    putchar('\n');
  }
}
#else
void _cm_matrix_double_printf(const CmMatrixDouble *matrix) { (void)matrix; }
#endif

#define CM_GET_MATRIX_ELEM(matrix, row, column)                                \
  ((matrix)->data[(row) * (matrix)->columns + (column)])

static double _cm_matrix_double_det_less_3(const CmMatrixDouble *matrix) {

  double det_out = 0.;

  if (matrix->rows == 1) {
    det_out = matrix->data[0];
  } else if (matrix->rows == 2) {
    det_out = (matrix->data[0] * matrix->data[3]) -
              (matrix->data[1] * matrix->data[2]);
  } else if (matrix->rows == 3) {
    det_out = (matrix->data[0] * matrix->data[4] * matrix->data[8]) +
              (matrix->data[1] * matrix->data[5] * matrix->data[6]) +
              (matrix->data[2] * matrix->data[3] * matrix->data[7]) -
              (matrix->data[2] * matrix->data[4] * matrix->data[6]) -
              (matrix->data[1] * matrix->data[3] * matrix->data[8]) -
              (matrix->data[0] * matrix->data[5] * matrix->data[7]);
  }
  return det_out;
}

CmMatrixDouble *cm_matrix_double_alloc(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = malloc(sizeof(CmMatrixDouble));

  if (!matrix)
    return NULL;

  double *data = malloc(sizeof(double) * rows * cols);

  if (!data) {
    free(matrix);
    return NULL;
  }

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixDouble *cm_matrix_double_calloc(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = malloc(sizeof(CmMatrixDouble));

  if (!matrix)
    return NULL;

  double *data = calloc(rows * cols, sizeof(double));

  if (!data) {
    free(matrix);
    return NULL;
  }

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixDouble *cm_matrix_double_row(const CmMatrixDouble *source_matrix,
                                     size_t row) {

  if (!source_matrix || !source_matrix->data || row >= source_matrix->rows ||
      (source_matrix->columns == 0))
    return NULL;

  CmMatrixDouble *row_matrix =
      cm_matrix_double_alloc(1, source_matrix->columns);
  if (!row_matrix)
    return NULL;

  memcpy(row_matrix->data, source_matrix->data + (row * source_matrix->columns),
         sizeof(double) * source_matrix->columns);

  return row_matrix;
}

CmMatrixDouble *cm_matrix_double_col(const CmMatrixDouble *source_matrix,
                                     size_t col) {

  if (!source_matrix || !source_matrix->data || col >= source_matrix->columns ||
      (source_matrix->rows == 0))
    return NULL;

  CmMatrixDouble *col_matrix = cm_matrix_double_alloc(source_matrix->rows, 1);
  if (!col_matrix)
    return NULL;

  for (size_t i = 0; i < source_matrix->rows; ++i) {
    col_matrix->data[i] = source_matrix->data[i * source_matrix->columns + col];
  }

  return col_matrix;
}

CmMatrixDouble *cm_matrix_double_submatrix(const CmMatrixDouble *source_matrix,
                                           size_t row_start, size_t row_end,
                                           size_t col_start, size_t col_end) {

  if (!source_matrix || !source_matrix->data || row_start > row_end ||
      col_start > col_end || row_start >= source_matrix->rows ||
      row_end >= source_matrix->rows || col_start >= source_matrix->columns ||
      col_end >= source_matrix->columns)
    return NULL;

  CmMatrixDouble *submatrix =
      cm_matrix_double_alloc(row_end - row_start + 1, col_end - col_start + 1);
  if (!submatrix)
    return NULL;

  size_t k = 0;

  for (size_t i = row_start; i <= row_end; ++i, ++k) {
    size_t m = 0;

    for (size_t j = col_start; j <= col_end; ++j, ++m) {

      submatrix->data[m + k * submatrix->columns] =
          source_matrix->data[j + i * source_matrix->columns];
    }
  }

  return submatrix;
}

CmMatrixDouble *cm_matrix_create_diag(size_t size, double init_val) {

  CmMatrixDouble *diag = cm_matrix_double_calloc(size, size);
  if (!diag || !diag->data)
    return NULL;

  for (size_t i = 0; i < size; ++i) {
    diag->data[i + i * size] = init_val;
  }

  return diag;
}

// TODO: use memcpy instead for
CmMatrixDouble *
cm_matrix_double_create_from_matrix(const CmMatrixDouble *orig_matrix) {

  if (!orig_matrix || !orig_matrix->data || orig_matrix->columns == 0 ||
      orig_matrix->rows == 0)
    return NULL;

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_alloc(orig_matrix->rows, orig_matrix->columns);

  if (!copy_matrix) {
    return NULL;
  }

  for (size_t i = 0; i < copy_matrix->rows; ++i) {
    for (size_t j = 0; j < copy_matrix->columns; ++j) {
      copy_matrix->data[i * copy_matrix->columns + j] =
          orig_matrix->data[i * orig_matrix->columns + j];
    }
  }

  return copy_matrix;
}

CmMatrixDouble *cm_matrix_double_create_from_array(const double **arr,
                                                   size_t rows, size_t cols) {

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);

  if (!matrix)
    return NULL;

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      cm_matrix_double_set(matrix, i, j, arr[i][j]);
    }
  }

  return matrix;
}

CmStatusCode cm_matrix_double_swap(CmMatrixDouble **matrix_a,
                                   CmMatrixDouble **matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);

  CmMatrixDouble *tmp = *matrix_a;
  *matrix_a = *matrix_b;
  *matrix_b = tmp;

  return CM_SUCCESS;
}

// TODO: memset optimuzation
CmStatusCode cm_matrix_double_set_identity(CmMatrixDouble *matrix) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (i == j) {
        matrix->data[i * matrix->columns + j] = 1;
      } else {
        matrix->data[i * matrix->columns + j] = 0;
      }
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_set_zero(CmMatrixDouble *matrix) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  memset(matrix->data, 0, sizeof(double) * matrix->rows * matrix->columns);

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_set_all(CmMatrixDouble *matrix, double x) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  if (x == 0.) {
    cm_matrix_double_set_zero(matrix);
    return CM_SUCCESS;
  }

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    matrix->data[i] = x;
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_max(const CmMatrixDouble *matrix,
                                  double *max_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(max_out);
  CM_BUFF_NULL_CHECK(matrix);

  *max_out = matrix->data[0];
  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (matrix->data[i] > *max_out)
      *max_out = matrix->data[i];
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_min(const CmMatrixDouble *matrix,
                                  double *min_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(min_out);
  CM_BUFF_NULL_CHECK(matrix);

  *min_out = matrix->data[0];
  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (matrix->data[i] < *min_out)
      *min_out = matrix->data[i];
  }

  return CM_SUCCESS;
}

// NOTE: fine for general, but mem-heavy for large rect
CmStatusCode cm_matrix_double_transpose(CmMatrixDouble **matrix) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(*matrix);
  CM_BUFF_NULL_CHECK((*matrix));

  CmMatrixDouble *tmp_matrix =
      cm_matrix_double_alloc((*matrix)->columns, (*matrix)->rows);

  CM_ALLOC_CHECK_NULL(tmp_matrix);

  for (size_t i = 0; i < (*matrix)->rows; ++i) {
    for (size_t j = 0; j < (*matrix)->columns; ++j) {
      tmp_matrix->data[j * (*matrix)->rows + i] =
          (*matrix)->data[i * (*matrix)->columns + j];
    }
  }

  cm_matrix_double_free(*matrix);
  *matrix = tmp_matrix;

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_trace(const CmMatrixDouble *matrix,
                                    double *trace_out) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(trace_out);
  CM_BUFF_NULL_CHECK(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);

  size_t num_of_elems = matrix->rows * matrix->columns;
  *trace_out = 0.;

  for (size_t i = 0; i < matrix->rows; ++i) {
    *trace_out += matrix->data[i * matrix->columns + i];
  }

  return CM_SUCCESS;
}

// NOTE: fine for small matrix
// TODO: change get to direct data access
CmStatusCode cm_matrix_double_det(const CmMatrixDouble *matrix,
                                  double *det_out) {

  CM_CHECK_NULL(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  if (matrix->columns <= 3) {
    *det_out = _cm_matrix_double_det_less_3(matrix);
    return CM_SUCCESS;
  }

  CmMatrixDouble *copy_matrix = cm_matrix_double_create_from_matrix(matrix);
  CM_ALLOC_CHECK_NULL(copy_matrix);

  double *mult_constants = malloc(copy_matrix->columns * sizeof(double));
  if (!mult_constants) {
    cm_matrix_double_free(copy_matrix);
    return CM_ERR_ALLOC_FAILED;
  }

  int mult_const_index = 0;
  int swap_number = 0;

  for (size_t k = 0; k < copy_matrix->rows - 1; ++k) {

    double pivot = cm_matrix_double_get(copy_matrix, k, k);
    if (pivot == 0) {

      bool find_non_zero = false;

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (cm_matrix_double_get(copy_matrix, i, k) != 0) {

          find_non_zero = true;
          void *buffer = malloc(copy_matrix->columns * sizeof(double));
          if (!buffer) {
            cm_matrix_double_free(copy_matrix);
            free(mult_constants);
            return CM_ERR_ALLOC_FAILED;
          }

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);

          swap_number++;
        }
      }

      if (!find_non_zero) {
        *det_out = 0;
        cm_matrix_double_free(copy_matrix);
        free(mult_constants);
        return CM_SUCCESS;
      }
    }

    cm_matrix_double_scale_row(copy_matrix, k, (1. / pivot));

    mult_constants[mult_const_index++] = pivot;

    for (size_t i = k + 1; i < copy_matrix->rows; ++i) {
      double deleted = -cm_matrix_double_get(copy_matrix, i, k);
      for (size_t j = 0; j < copy_matrix->columns; ++j) {
        double set_elem = cm_matrix_double_get(copy_matrix, k, j) * deleted +
                          cm_matrix_double_get(copy_matrix, i, j);
        cm_matrix_double_set(copy_matrix, i, j, set_elem);
      }
    }
  }

  double mult = (swap_number % 2 == 0) ? 1 : -1;

  *det_out = mult * cm_matrix_double_get(copy_matrix, copy_matrix->rows - 1,
                                         copy_matrix->rows - 1);

  for (int i = 0; i < mult_const_index; ++i) {
    *det_out *= mult_constants[i];
  }

  cm_matrix_double_free(copy_matrix);
  free(mult_constants);

  return CM_SUCCESS;
}

// TODO: if pivot 1e-20 unstable
CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix) {

  if (!orig_matrix || !orig_matrix->data ||
      (orig_matrix->rows != orig_matrix->columns)) {
    return NULL;
  }

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_create_from_matrix(orig_matrix);
  if (!copy_matrix) {
    return NULL;
  }

  CmMatrixDouble *res_matrix =
      cm_matrix_double_alloc(orig_matrix->rows, orig_matrix->columns);
  if (!res_matrix) {
    cm_matrix_double_free(copy_matrix);
    return NULL;
  }
  cm_matrix_double_set_identity(res_matrix);

  for (size_t k = 0; k < copy_matrix->columns; ++k) {

    double pivot = copy_matrix->data[k * copy_matrix->columns + k];
    bool is_pivot_zero = _cm_double_equal(pivot, 0);

    if (is_pivot_zero) {
      bool find_non_zero = false;

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (!_cm_double_equal(copy_matrix->data[i * copy_matrix->columns + k],
                              0)) {

          find_non_zero = true;
          void *buffer = malloc(copy_matrix->columns * sizeof(double));

          if (!buffer) {
            cm_matrix_double_free(copy_matrix);
            cm_matrix_double_free(res_matrix);
            return NULL;
          }

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);

          memcpy(buffer, res_matrix->data + (i * res_matrix->columns),
                 sizeof(double) * res_matrix->columns);

          memmove(res_matrix->data + (i * res_matrix->columns),
                  res_matrix->data + (k * res_matrix->columns),
                  sizeof(double) * res_matrix->columns);

          memmove(res_matrix->data + (k * res_matrix->columns), buffer,
                  sizeof(double) * res_matrix->columns);

          free(buffer);
        }
      }

      if (!find_non_zero) {
        cm_matrix_double_free(copy_matrix);
        cm_matrix_double_free(res_matrix);
        return NULL;
      }
      pivot = copy_matrix->data[k * copy_matrix->columns + k];
    }

    cm_matrix_double_scale_row(copy_matrix, k, 1. / (pivot));
    cm_matrix_double_scale_row(res_matrix, k, 1. / (pivot));

    for (size_t j = 0; j < copy_matrix->rows; ++j) {
      if (j == k)
        continue;

      double elim_factor = copy_matrix->data[j * copy_matrix->columns + k];

      for (size_t i = 0; i < copy_matrix->columns; ++i) {
        copy_matrix->data[j * copy_matrix->columns + i] =
            (copy_matrix->data[k * copy_matrix->columns + i] * elim_factor *
             -1.) +
            copy_matrix->data[j * copy_matrix->columns + i];

        res_matrix->data[j * res_matrix->columns + i] =
            (res_matrix->data[k * res_matrix->columns + i] * elim_factor *
             -1.) +
            res_matrix->data[j * res_matrix->columns + i];
      }
    }
  }

  cm_matrix_double_free(copy_matrix);

  return res_matrix;
}

CmStatusCode cm_matrix_double_minor(const CmMatrixDouble *matrix, size_t row,
                                    size_t col, double *minor_out) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);
  CM_MATRIX_SQUARE_CHECK(matrix);

  if (matrix->rows == 0 || matrix->columns == 0)
    return CM_MATRIX_ERR_ZERO;

  if (row > matrix->rows || col > matrix->columns)
    return CM_MATRIX_ERR_WRONG_POS;

  CmMatrixDouble *block_matrix =
      cm_matrix_double_alloc(matrix->rows - 1, matrix->columns - 1);
  CM_ALLOC_CHECK_NULL(block_matrix);

  size_t block_i = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {
    if (i == row)
      continue;

    size_t block_j = 0;
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (j == col)
        continue;

      double elem = cm_matrix_double_get(matrix, i, j);
      cm_matrix_double_set(block_matrix, block_i, block_j++, elem);
    }
    ++block_i;
  }

  cm_matrix_double_det(block_matrix, minor_out);
  cm_matrix_double_free(block_matrix);

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_cofactor(const CmMatrixDouble *matrix, size_t row,
                                       size_t col, double *cofactor_out) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  double sign = ((row + col) & 0x1) ? -1 : 1;

  double minor = 0.;
  CmStatusCode res = cm_matrix_double_minor(matrix, row, col, &minor);
  if (res == CM_SUCCESS) {
    *cofactor_out = sign * minor;
    return CM_SUCCESS;
  }

  return res;
}

CmStatusCode cm_matrix_double_pow(CmMatrixDouble **matrix, unsigned exp) {

  CM_CHECK_NULL(*matrix);
  CM_MATRIX_SQUARE_CHECK((*matrix));

  if (exp == 1)
    return CM_SUCCESS;
  else if (exp == 0) {
    cm_matrix_double_set_identity(*matrix);
    return CM_SUCCESS;
  }

  CmMatrixDouble *res =
      cm_matrix_double_alloc((*matrix)->rows, (*matrix)->columns);
  CM_ALLOC_CHECK_NULL(res);

  cm_matrix_double_set_identity(res);

  CmMatrixDouble *tmp =
      cm_matrix_double_alloc((*matrix)->rows, (*matrix)->columns);
  if (!tmp) {
    cm_matrix_double_free(res);
    return CM_ERR_ALLOC_FAILED;
  }

  CmStatusCode mult_status = CM_SUCCESS;

  while (exp > 0) {
    if (exp & 0x1) {
      mult_status = cm_matrix_double_mul(res, *matrix, tmp);
      if (mult_status != CM_SUCCESS) {
        cm_matrix_double_free(tmp);
        cm_matrix_double_free(res);
        return mult_status;
      }
      cm_matrix_double_swap(&res, &tmp);
    }
    mult_status = cm_matrix_double_mul(*matrix, *matrix, tmp);
    if (mult_status != CM_SUCCESS) {
      cm_matrix_double_free(res);
      cm_matrix_double_free(tmp);
      return CM_ERR_ALLOC_FAILED;
    }
    cm_matrix_double_swap(&tmp, &(*matrix));
    exp /= 2;
  }

  memcpy((*matrix)->data, res->data, sizeof(double) * res->rows * res->columns);

  cm_matrix_double_free(res);

  return CM_SUCCESS;
}

// TODO: NaN/Inf handling weak (NaN compare false may pass as null, bad). EPS
// fixed 1e-20 arbitrary (better relative eps * max_elem or ULPs)
bool cm_matrix_double_is_null(const CmMatrixDouble *matrix) {

  if (!matrix || !matrix->data)
    return false;

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (!_cm_double_equal(matrix->data[i], 0))
      return false;
  }

  return true;
}

// TODO: NaN/Inf handling weak (NaN compare false may pass as null, bad). EPS
// fixed 1e-20 arbitrary (better relative eps * max_elem or ULPs)
bool cm_matrix_double_is_identity(const CmMatrixDouble *matrix) {

  if (!matrix || !matrix->data)
    return false;

  if ((matrix->rows) != (matrix->columns)) {
    return false;
  }

  size_t i = 0;
  size_t j = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      double current_elem = matrix->data[i * matrix->columns + j];
      if (i == j && !_cm_double_equal(current_elem, 1)) {
        return false;
      } else if (i != j && !_cm_double_equal(current_elem, 0)) {
        return false;
      }
    }
  }

  return true;
}

// TODO: NaN/Inf handling weak (NaN compare false may pass as null, bad). EPS
// fixed 1e-20 arbitrary (better relative eps * max_elem or ULPs)
bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b) {

  if (!matrix_a || !matrix_b || !matrix_a->data || !matrix_b->data)
    return false;

  if ((matrix_a->rows != matrix_b->rows) ||
      (matrix_a->columns != matrix_b->columns))
    return false;

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      double current_elem_a = matrix_a->data[i * matrix_a->columns + j];
      double current_elem_b = matrix_b->data[i * matrix_b->columns + j];
      if (!_cm_double_equal(current_elem_a, current_elem_b))
        return false;
    }
  }

  return true;
}

CmStatusCode cm_matrix_double_add(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_BUFF_NULL_CHECK(matrix_a);
  CM_BUFF_NULL_CHECK(matrix_b);
  CM_MATRIX_SIZE_MATCH(matrix_a, matrix_b);

  size_t i = 0;
  size_t j = 0;

  for (; i < matrix_a->rows;) {
    double current_elem_b = matrix_b->data[i * matrix_b->columns + j];

    matrix_a->data[i * matrix_a->columns + j] += current_elem_b;

    if (j == matrix_a->columns) {
      j = 0;
      ++i;
    } else {
      ++j;
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_sub(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b) {
  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_BUFF_NULL_CHECK(matrix_a);
  CM_BUFF_NULL_CHECK(matrix_b);
  CM_MATRIX_SIZE_MATCH(matrix_a, matrix_b);

  size_t i = 0;
  size_t j = 0;

  for (; i < matrix_a->rows;) {
    double current_elem_b = matrix_b->data[i * matrix_b->columns + j];

    matrix_a->data[i * matrix_a->columns + j] -= current_elem_b;

    if (j == matrix_a->columns) {
      j = 0;
      ++i;
    } else {
      ++j;
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_scale(CmMatrixDouble *matrix, double scale) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  if (_cm_double_equal(scale, 0)) {
    cm_matrix_double_set_zero(matrix);
    return CM_SUCCESS;
  }

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    matrix->data[i] *= scale;
  }

  return CM_SUCCESS;
}

// TODO: Get/set slow (macro bounds? overkill per inner), better direct data
// access result
// TODO: better performance
CmStatusCode cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b,
                                  CmMatrixDouble *result_matrix) {

  CM_CHECK_NULL(matrix_a);
  CM_CHECK_NULL(matrix_b);
  CM_CHECK_NULL(result_matrix);
  CM_BUFF_NULL_CHECK(matrix_a);
  CM_BUFF_NULL_CHECK(matrix_b);
  CM_BUFF_NULL_CHECK(result_matrix);
  CM_MATRIX_MULT_SIZE_MATCH(matrix_a, matrix_b);

  if ((result_matrix->rows != matrix_a->rows) ||
      (result_matrix->columns != matrix_b->columns))
    return CM_MATRIX_ERR_MULT_RES_WRONG_SIZE;

  for (size_t i = 0; i < result_matrix->rows; ++i) {
    for (size_t k = 0; k < result_matrix->columns; ++k) {
      double result_elem = 0;
      for (size_t j = 0; j < matrix_a->columns; ++j) {
        result_elem += cm_matrix_double_get(matrix_a, i, j) *
                       cm_matrix_double_get(matrix_b, j, k);
      }
      cm_matrix_double_set(result_matrix, i, k, result_elem);
    }
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_scale_row(CmMatrixDouble *matrix, size_t row,
                                        size_t scale_by) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  if (row >= matrix->rows)
    return CM_MATRIX_ERR_INVALID_ROW;

  for (size_t i = 0; i < matrix->columns; ++i) {
    matrix->data[i + row * matrix->columns] *= scale_by;
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_swap_rows(CmMatrixDouble *matrix, size_t row_a,
                                        size_t row_b) {

  CM_CHECK_NULL(matrix);

  if (row_a >= matrix->rows || row_b >= matrix->rows)
    return CM_MATRIX_ERR_INVALID_ROW;

  double *buffer = malloc(sizeof(double) * matrix->columns);
  if (!buffer)
    return CM_ERR_ALLOC_FAILED;

  size_t row_len = sizeof(double) * matrix->columns;

  memcpy(buffer, matrix->data + row_a * matrix->columns, row_len);
  memmove(matrix->data + row_a * matrix->columns,
          matrix->data + row_b * matrix->columns, row_len);
  memmove(matrix->data + row_b * matrix->columns, buffer, row_len);

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_scale_sum_rows(CmMatrixDouble *matrix,
                                             size_t row_scaled, size_t row_sum,
                                             size_t scale_by) {

  CM_CHECK_NULL(matrix);

  if (row_scaled >= matrix->rows || row_sum >= matrix->rows)
    return CM_MATRIX_ERR_INVALID_ROW;

  for (size_t i = 0; i < matrix->columns; ++i) {
    matrix->data[i + row_sum * matrix->columns] +=
        matrix->data[i + row_scaled * matrix->columns] * scale_by;
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix,
                                    double *res) {
  CM_CHECK_NULL(augmented_matrix);
  CM_CHECK_NULL(res);
  CM_BUFF_NULL_CHECK(augmented_matrix);

  if (augmented_matrix->rows != (augmented_matrix->columns - 1)) {
    return CM_MATRIX_ERR_INVALID_SIZE;
  }

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_create_from_matrix(augmented_matrix);
  if (!copy_matrix) {
    return CM_ERR_ALLOC_FAILED;
  }

  for (size_t k = 0; k < copy_matrix->columns; ++k) {

    double pivot = copy_matrix->data[k * copy_matrix->columns + k];

    if (_cm_double_equal(pivot, 0)) {
      bool find_non_zero = false;

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (!_cm_double_equal(copy_matrix->data[i * copy_matrix->columns + k],
                              0)) {

          find_non_zero = true;
          void *buffer = malloc(copy_matrix->columns * sizeof(double));

          if (!buffer) {
            cm_matrix_double_free(copy_matrix);
            return CM_ERR_ALLOC_FAILED;
          }

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);

          free(buffer);
        }
      }

      if (!find_non_zero) {
        cm_matrix_double_free(copy_matrix);
        return CM_MATRIX_ERR_GAUSS_NO_SOLUTIONS;
      }
      pivot = copy_matrix->data[k * copy_matrix->columns + k];
    }

    cm_matrix_double_scale_row(copy_matrix, k, 1. / (pivot));

    for (size_t j = 0; j < copy_matrix->rows; ++j) {
      if (j == k)
        continue;

      double elim_factor = copy_matrix->data[j * copy_matrix->columns + k];

      for (size_t i = 0; i < copy_matrix->columns; ++i) {
        copy_matrix->data[j * copy_matrix->columns + i] =
            (copy_matrix->data[k * copy_matrix->columns + i] * elim_factor *
             -1.) +
            copy_matrix->data[j * copy_matrix->columns + i];
      }
    }
  }

  for (size_t i = 0; i < copy_matrix->rows; ++i) {
    res[i] = cm_matrix_double_get(copy_matrix, i, copy_matrix->columns - 1);
  }

  cm_matrix_double_free(copy_matrix);

  return CM_SUCCESS;
}

CmMatrixDouble *cm_matrix_double_adj(const CmMatrixDouble *matrix) {

  if (!matrix || !matrix->data || (matrix->rows != matrix->columns))
    return NULL;

  CmMatrixDouble *res_matrix =
      cm_matrix_double_alloc(matrix->rows, matrix->columns);
  if (!res_matrix)
    return NULL;

  size_t i = 0;
  size_t j = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      double current_cofactor = 0.;
      CmStatusCode res =
          cm_matrix_double_cofactor(matrix, i, j, &current_cofactor);
      if (res != CM_SUCCESS) {
        cm_matrix_double_free(res_matrix);
        return NULL;
      }
      cm_matrix_double_set(res_matrix, i, j, current_cofactor);
    }
  }

  cm_matrix_double_transpose(&res_matrix);

  return res_matrix;
}

CmStatusCode cm_matrix_double_map(CmMatrixDouble *matrix, CmMatrixMapFunc map) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(map);
  CM_BUFF_NULL_CHECK(matrix);

  for (size_t i = 0; i < matrix->rows * matrix->columns; ++i) {
    matrix->data[i] = map(matrix->data[i]);
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_to_txt(const CmMatrixDouble *matrix,
                                     const char *filename) {

  CM_CHECK_NULL(matrix);
  CM_CHECK_NULL(filename);
  CM_BUFF_NULL_CHECK(matrix);

  FILE *file = fopen(filename, "w");
  if (!file)
    return CM_ERR_CREATE_FILE;

  for (size_t i = 0; i < matrix->columns * matrix->rows; ++i) {
    fprintf(file, "%lf ", matrix->data[i]);
  }

  return CM_SUCCESS;
}

CmStatusCode cm_matrix_double_free(CmMatrixDouble *matrix) {

  CM_CHECK_NULL(matrix);
  CM_BUFF_NULL_CHECK(matrix);

  free(matrix->data);
  free(matrix);

  return CM_SUCCESS;
}
