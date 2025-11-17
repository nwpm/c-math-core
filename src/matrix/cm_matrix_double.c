#include "cm_matrix_double.h"
#include "../utils/cm_utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CM_DEBUG
#include <assert.h>
#endif

// TODO: make NULL check or not?
// TODO: error handler
// TODO: return codes only in debug build or return codes only in some
// functiuons

#ifdef CM_DEBUG
void _cm_matrix_double_printf(const CmMatrixDouble *matrix) {

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      printf("%f ", matrix->data[i * matrix->columns + j]);
    }
    putchar('\n');
  }
}
#endif

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
  double *data = malloc(sizeof(double) * rows * cols);

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixDouble *cm_matrix_double_create_zero(size_t rows, size_t cols) {

  CmMatrixDouble *matrix = malloc(sizeof(CmMatrixDouble));
  double *data = calloc(rows * cols, sizeof(double));

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

CmMatrixDouble *cm_matrix_double_row(const CmMatrixDouble *source_matrix,
                                     size_t row) {

#ifdef CM_DEBUG
  assert(!source_matrix && "Matrix argument is NULL");
  assert(!source_matrix->data && "Matrix argument data is NULL");
  assert(!source_matrix->columns && "Matrix argument has zero columns");

  assert((row >= source_matrix->rows) && "Invalid row argument");
#endif

  CmMatrixDouble *row_matrix =
      cm_matrix_double_alloc(1, source_matrix->columns);

  memcpy(row_matrix->data, source_matrix->data + (row * source_matrix->columns),
         sizeof(double) * source_matrix->columns);

  return row_matrix;
}

CmMatrixDouble *cm_matrix_double_col(const CmMatrixDouble *source_matrix,
                                     size_t col) {

#ifdef CM_DEBUG
  assert(!source_matrix && "Matrix argument is NULL");
  assert(!source_matrix->data && "Matrix argument data is NULL");
  assert(!source_matrix->columns && "Matrix argument has zero columns");

  assert((col >= source_matrix->columns) && "Invalid col argument");
#endif

  CmMatrixDouble *col_matrix = cm_matrix_double_alloc(source_matrix->rows, 1);

  for (size_t i = 0; i < source_matrix->rows; ++i)
    col_matrix->data[i] = source_matrix->data[i * source_matrix->columns + col];

  return col_matrix;
}

CmMatrixDouble *cm_matrix_double_submatrix(const CmMatrixDouble *source_matrix,
                                           size_t row_start, size_t row_end,
                                           size_t col_start, size_t col_end) {

#ifdef CM_DEBUG
  assert(!source_matrix && "Matrix argument is NULL pointer");
  assert(!source_matrix->data && "Matrix argument data is NULL pointer");

  assert((row_start > row_end || col_start > col_end ||
          row_start >= source_matrix->rows || row_end >= source_matrix->rows ||
          col_start >= source_matrix->columns ||
          col_end >= source_matrix->columns) &&
         "Invalid submatrix position");
#endif

  CmMatrixDouble *submatrix =
      cm_matrix_double_alloc(row_end - row_start + 1, col_end - col_start + 1);

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

CmMatrixDouble *cm_matrix_double_create_diag(size_t size, double init_val) {

  CmMatrixDouble *diag = cm_matrix_double_create_zero(size, size);

  for (size_t i = 0; i < size; ++i)
    diag->data[i + i * size] = init_val;

  return diag;
}

CmMatrixDouble *cm_matrix_double_create_identity(size_t size) {

  CmMatrixDouble *identity = cm_matrix_double_create_zero(size, size);

  for (size_t i = 0; i < identity->rows; ++i) {
    for (size_t j = 0; j < identity->columns; ++j) {
      if (i == j)
        identity->data[i * identity->columns + j] = 1;
      else
        identity->data[i * identity->columns + j] = 0;
    }
  }

  return identity;
}

CmMatrixDouble *
cm_matrix_double_create_from_matrix(const CmMatrixDouble *orig_matrix) {

#ifdef CM_DEBUG
  assert(!orig_matrix && "Matrix argument is NULL");
  assert(!orig_matrix->data && "Matrix argument data is NULL");
#endif

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_alloc(orig_matrix->rows, orig_matrix->columns);

  for (size_t i = 0; i < copy_matrix->rows; ++i) {
    memcpy(copy_matrix->data + copy_matrix->columns * i,
           orig_matrix->data + orig_matrix->columns * i,
           sizeof(double) * orig_matrix->columns);
  }

  return copy_matrix;
}

CmMatrixDouble *cm_matrix_double_create_from_array(const double **arr,
                                                   size_t rows, size_t cols) {

#ifdef CM_DEBUG
  assert(!arr && "Double array argument is NULL pointer");
#endif

  CmMatrixDouble *matrix = cm_matrix_double_alloc(rows, cols);

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j)
      cm_matrix_double_set(matrix, i, j, arr[i][j]);
  }

  return matrix;
}

void cm_matrix_double_swap(CmMatrixDouble **matrix_a,
                           CmMatrixDouble **matrix_b) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A pointer argument is NULL");
  assert(!matrix_b && "Matrix B pointer argument is NULL");

  assert(!*matrix_a && "Matrix A argument is NULL");
  assert(!*matrix_b && "Matrix B argument is NULL");
#endif

  CmMatrixDouble *tmp = *matrix_a;
  *matrix_a = *matrix_b;
  *matrix_b = tmp;
}

void cm_matrix_double_set_identity(CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (i == j)
        matrix->data[i * matrix->columns + j] = 1.;
      else
        matrix->data[i * matrix->columns + j] = 0.;
    }
  }
}

void cm_matrix_double_set_zero(CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  memset(matrix->data, 0, sizeof(double) * matrix->rows * matrix->columns);
}

void cm_matrix_double_set_all(CmMatrixDouble *matrix, double x) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  if (_cm_double_equal(x, 0.))
    cm_matrix_double_set_zero(matrix);

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i)
    matrix->data[i] = x;
}

double cm_matrix_double_max(const CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  double max_out = matrix->data[0];
  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (matrix->data[i] > max_out)
      max_out = matrix->data[i];
  }

  return max_out;
}

double cm_matrix_double_min(const CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  double min_out = matrix->data[0];
  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (matrix->data[i] < min_out)
      min_out = matrix->data[i];
  }

  return min_out;
}

// NOTE: fine for general, but mem-heavy for large rect
void cm_matrix_double_transpose(CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix pointer argument is NULL");
  assert(!*matrix && "Matrix argument is NULL");
  assert(!(*matrix)->data && "Matrix argument data is NULL");
#endif

  CmMatrixDouble *tmp_matrix =
      cm_matrix_double_alloc(matrix->columns, matrix->rows);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      tmp_matrix->data[j * matrix->rows + i] =
          matrix->data[i * matrix->columns + j];
    }
  }

  free(matrix->data);
  matrix->data = tmp_matrix->data;
  free(tmp_matrix);
}

double cm_matrix_double_trace(const CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  double trace_out = 0.;

  for (size_t i = 0; i < matrix->rows; ++i)
    trace_out += matrix->data[i * matrix->columns + i];

  return trace_out;
}

// NOTE: fine for small matrix
// TODO: change get to direct data access
double cm_matrix_double_det(const CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  if (matrix->columns <= 3)
    return _cm_matrix_double_det_less_3(matrix);

  CmMatrixDouble *copy_matrix = cm_matrix_double_create_from_matrix(matrix);
  double *mult_constants = malloc(copy_matrix->columns * sizeof(double));

  int mult_const_index = 0;
  int swap_number = 0;

  for (size_t k = 0; k < copy_matrix->rows - 1; ++k) {

    double pivot = cm_matrix_double_get(copy_matrix, k, k);

    if (pivot == 0) {

      bool find_non_zero = false;
      void *buffer = malloc(copy_matrix->columns * sizeof(double));

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (cm_matrix_double_get(copy_matrix, i, k) != 0) {

          find_non_zero = true;

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

      free(buffer);

      if (!find_non_zero) {
        cm_matrix_double_free(copy_matrix);
        free(mult_constants);
        return 0.;
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

  double det_out = 0.;
  double mult = (swap_number % 2 == 0) ? 1 : -1;
  det_out = mult * cm_matrix_double_get(copy_matrix, copy_matrix->rows - 1,
                                        copy_matrix->rows - 1);

  for (int i = 0; i < mult_const_index; ++i)
    det_out *= mult_constants[i];

  cm_matrix_double_free(copy_matrix);
  free(mult_constants);

  return det_out;
}

// TODO: if pivot 1e-20 unstable
CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_create_from_matrix(orig_matrix);
  CmMatrixDouble *res_matrix =
      cm_matrix_double_create_identity(orig_matrix->rows);

  for (size_t k = 0; k < copy_matrix->columns; ++k) {

    double pivot = copy_matrix->data[k * copy_matrix->columns + k];
    bool is_pivot_zero = _cm_double_equal(pivot, 0);

    if (is_pivot_zero) {
      bool find_non_zero = false;

      void *buffer = malloc(copy_matrix->columns * sizeof(double));

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (!_cm_double_equal(copy_matrix->data[i * copy_matrix->columns + k],
                              0)) {

          find_non_zero = true;

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
        }
      }

      free(buffer);

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

double cm_matrix_double_minor(const CmMatrixDouble *matrix, size_t row,
                              size_t col) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  CmMatrixDouble *block_matrix =
      cm_matrix_double_alloc(matrix->rows - 1, matrix->columns - 1);

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

  double res = cm_matrix_double_det(block_matrix);
  cm_matrix_double_free(block_matrix);

  return res;
}

double cm_matrix_double_cofactor(const CmMatrixDouble *matrix, size_t row,
                                 size_t col) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  double sign = ((row + col) & 0x1) ? -1 : 1;
  double minor = cm_matrix_double_minor(matrix, row, col);

  return sign * minor;
}

void cm_matrix_double_pow(CmMatrixDouble *matrix, unsigned exp) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  if (exp == 1)
    return;
  else if (exp == 0)
    cm_matrix_double_set_identity(matrix);

  CmMatrixDouble *res = cm_matrix_double_create_identity(matrix->rows);
  CmMatrixDouble *tmp = cm_matrix_double_alloc(matrix->rows, matrix->columns);

  while (exp > 0) {
    if (exp & 0x1) {
      cm_matrix_double_mul(res, matrix, tmp);
      cm_matrix_double_swap(&res, &tmp);
    }
    cm_matrix_double_mul(matrix, matrix, tmp);
    cm_matrix_double_swap(&tmp, &matrix);
    exp /= 2;
  }

  memcpy(matrix->data, res->data, sizeof(double) * res->rows * res->columns);

  cm_matrix_double_free(res);
  cm_matrix_double_free(tmp);
}

// TODO: NaN/Inf handling weak (NaN compare false may pass as null, bad). EPS
// fixed 1e-20 arbitrary (better relative eps * max_elem or ULPs)
bool cm_matrix_double_is_null(const CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

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

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  size_t i = 0;
  size_t j = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      double current_elem = matrix->data[i * matrix->columns + j];
      if (i == j && !_cm_double_equal(current_elem, 1))
        return false;
      else if (i != j && !_cm_double_equal(current_elem, 0))
        return false;
    }
  }

  return true;
}

// TODO: NaN/Inf handling weak (NaN compare false may pass as null, bad). EPS
// fixed 1e-20 arbitrary (better relative eps * max_elem or ULPs)
bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A argument is NULL");
  assert(!matrix_b && "Matrix B argument is NULL");

  assert(!matrix_a->data && "Matrix A argument data is NULL");
  assert(!matrix_b->data && "Matrix B argument data is NULL");

  assert((matrix_a->rows != matrix_b->rows) &&
         (matrix_a->columns != matrix_b->columns) &&
         "Matrices must have same size");
#endif

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

void cm_matrix_double_add(CmMatrixDouble *matrix_a,
                          const CmMatrixDouble *matrix_b) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A argument is NULL");
  assert(!matrix_b && "Matrix B argument is NULL");

  assert(!matrix_a->data && "Matrix A argument data is NULL");
  assert(!matrix_b->data && "Matrix B argument data is NULL");

  assert((matrix_a->rows != matrix_b->rows) &&
         (matrix_a->columns != matrix_b->columns) &&
         "Matrices must have same size");
#endif

  size_t num_of_elems = matrix_a->columns * matrix_b->rows;

  for (size_t i = 0; i < num_of_elems; ++i)
    matrix_a->data[i] += matrix_b->data[i];
}

void cm_matrix_double_sub(CmMatrixDouble *matrix_a,
                          const CmMatrixDouble *matrix_b) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A argument is NULL");
  assert(!matrix_b && "Matrix B argument is NULL");

  assert(!matrix_a->data && "Matrix A argument data is NULL");
  assert(!matrix_b->data && "Matrix B argument data is NULL");

  assert((matrix_a->rows != matrix_b->rows) &&
         (matrix_a->columns != matrix_b->columns) &&
         "Matrices must have same size");
#endif

  size_t num_of_elems = matrix_a->columns * matrix_b->rows;

  for (size_t i = 0; i < num_of_elems; ++i)
    matrix_a->data[i] -= matrix_b->data[i];
}

void cm_matrix_double_scale(CmMatrixDouble *matrix, double scale) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  if (_cm_double_equal(scale, 0)) {
    cm_matrix_double_set_zero(matrix);
    return;
  }

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i)
    matrix->data[i] *= scale;
}

void cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                          const CmMatrixDouble *matrix_b,
                          CmMatrixDouble *result_matrix) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A argument is NULL");
  assert(!matrix_b && "Matrix B argument is NULL");
  assert(!result_matrix && "Result matrix argument is NULL");

  assert(!matrix_a->data && "Matrix A argument data is NULL");
  assert(!matrix_b->data && "Matrix B argument data is NULL");
  assert(!result_matrix->data && "Result matrix argument data is NULL");

  assert(matrix_a->columns != matrix_b->rows &&
         "Incorrect size for matrix multiplication(Columns A != Rows B)");

  assert(((result_matrix->rows != matrix_a->rows) ||
          (result_matrix->columns != matrix_b->columns)) &&
         "Invalid result matrix size");
#endif

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
}

void cm_matrix_double_scale_row(CmMatrixDouble *matrix, size_t row,
                                size_t scale_by) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
  assert(row >= matrix->rows && "Invalid row argument");
#endif

  for (size_t i = 0; i < matrix->columns; ++i)
    matrix->data[i + row * matrix->columns] *= scale_by;
}

void cm_matrix_double_swap_rows(CmMatrixDouble *matrix, size_t row_a,
                                size_t row_b) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
  assert(row_a >= matrix->rows && "Invalid row A argument");
  assert(row_b >= matrix->rows && "Invalid row B argument");
#endif

  size_t row_len = sizeof(double) * matrix->columns;

  double *buffer = malloc(row_len);

  memcpy(buffer, matrix->data + row_a * matrix->columns, row_len);
  memmove(matrix->data + row_a * matrix->columns,
          matrix->data + row_b * matrix->columns, row_len);
  memmove(matrix->data + row_b * matrix->columns, buffer, row_len);

  free(buffer);
}

void cm_matrix_double_scale_sum_rows(CmMatrixDouble *matrix, size_t row_scaled,
                                     size_t row_sum, size_t scale_by) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
  assert(row_scaled >= matrix->rows && "Invalid row scaled argument");
  assert(row_sum >= matrix->rows && "Invalid row sum argument");
#endif

  for (size_t i = 0; i < matrix->columns; ++i) {
    matrix->data[i + row_sum * matrix->columns] +=
        matrix->data[i + row_scaled * matrix->columns] * scale_by;
  }
}

void cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix,
                            double *res) {

#ifdef CM_DEBUG
  assert(!augmented_matrix && "Matrix argument is NULL");
  assert(!augmented_matrix->data && "Matrix argument data is NULL");

  assert(!res && "Result array is NULL");

  assert((augmented_matrix->rows != (augmented_matrix->columns - 1)) &&
         "Invalid augmented_matrix size");
#endif

  CmMatrixDouble *copy_matrix =
      cm_matrix_double_create_from_matrix(augmented_matrix);

  for (size_t k = 0; k < copy_matrix->columns; ++k) {

    double pivot = copy_matrix->data[k * copy_matrix->columns + k];

    if (_cm_double_equal(pivot, 0)) {
      bool find_non_zero = false;

      void *buffer = malloc(copy_matrix->columns * sizeof(double));

      for (size_t i = k + 1; i < copy_matrix->rows && !find_non_zero; ++i) {
        if (!_cm_double_equal(copy_matrix->data[i * copy_matrix->columns + k],
                              0)) {

          find_non_zero = true;

          memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
                 sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (i * copy_matrix->columns),
                  copy_matrix->data + (k * copy_matrix->columns),
                  sizeof(double) * copy_matrix->columns);

          memmove(copy_matrix->data + (k * copy_matrix->columns), buffer,
                  sizeof(double) * copy_matrix->columns);
        }
      }

      free(buffer);

      if (!find_non_zero) {
        cm_matrix_double_free(copy_matrix);
        res = NULL;
        return;
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

  for (size_t i = 0; i < copy_matrix->rows; ++i)
    res[i] = cm_matrix_double_get(copy_matrix, i, copy_matrix->columns - 1);

  cm_matrix_double_free(copy_matrix);
}

CmMatrixDouble *cm_matrix_double_adj(const CmMatrixDouble *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  CmMatrixDouble *res_matrix =
      cm_matrix_double_alloc(matrix->rows, matrix->columns);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      double current_cofactor = cm_matrix_double_cofactor(matrix, i, j);
      cm_matrix_double_set(res_matrix, i, j, current_cofactor);
    }
  }

  cm_matrix_double_transpose(res_matrix);

  return res_matrix;
}

void cm_matrix_double_map(CmMatrixDouble *matrix, CmMatrixMapFunc map) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(!map && "Map function is NULL");
#endif

  for (size_t i = 0; i < matrix->rows * matrix->columns; ++i)
    matrix->data[i] = map(matrix->data[i]);
}

void cm_matrix_double_to_txt(const CmMatrixDouble *matrix,
                             const char *filename) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(!filename && "Filename is NULL");
#endif

  FILE *file = fopen(filename, "w");

  for (size_t i = 0; i < matrix->columns * matrix->rows; ++i)
    fprintf(file, "%lf ", matrix->data[i]);
}

void cm_matrix_double_free(CmMatrixDouble *matrix) {
  free(matrix->data);
  free(matrix);
}
