#include "../../../include/cm_core/cm_mat.h"
#include "../utils/cm_utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef CM_DEBUG
#include <assert.h>
#endif

#ifdef CM_DEBUG
void _cm_matrix_double_printf(const cm_mat_t *matrix) {

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      printf("%f ", matrix->data[i * matrix->columns + j]);
    }
    putchar('\n');
  }
}
#endif

// TODO: cm_matrix_double_set_submatrix(dest, src, row_offset, col_offset)
// TODO: resize
// TODO: LU, QR, Cholesky
// TODO: random_matrix(rows, cols, min, max)
// TODO: fixed_matrix(3x3, 2x2, 4x4)
// TODO: cm_matrix_double_from_txt
// TODO: linear transfonmations(rotation, mirror, projection, shear, scale
// compration, expantion)

struct cm_mat_t {
  size_t rows;
  size_t columns;
  cm_real_t *data;
};
static double _cm_mat_det_less_3(const cm_mat_t *matrix) {

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

cm_mat_t *cm_mat_alloc(size_t rows, size_t cols) {

  cm_mat_t *matrix = malloc(sizeof(cm_mat_t));
  cm_real_t *data = malloc(sizeof(cm_real_t) * rows * cols);

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

cm_mat_t *cm_mat_create_zero(size_t rows, size_t cols) {

  cm_mat_t *matrix = malloc(sizeof(cm_mat_t));
  cm_real_t *data = calloc(rows * cols, sizeof(cm_real_t));

  matrix->columns = cols;
  matrix->rows = rows;
  matrix->data = data;

  return matrix;
}

cm_mat_t *cm_mat_row(const cm_mat_t *source_matrix, size_t row) {

#ifdef CM_DEBUG
  assert(!source_matrix && "Matrix argument is NULL");
  assert(!source_matrix->data && "Matrix argument data is NULL");
  assert(!source_matrix->columns && "Matrix argument has zero columns");
  assert((row >= source_matrix->rows) && "Invalid row argument");
#endif

  cm_mat_t *row_matrix = cm_mat_alloc(1, source_matrix->columns);

  memcpy(row_matrix->data, source_matrix->data + (row * source_matrix->columns),
         sizeof(cm_real_t) * source_matrix->columns);

  return row_matrix;
}

cm_mat_t *cm_mat_col(const cm_mat_t *source_matrix, size_t col) {

#ifdef CM_DEBUG
  assert(!source_matrix && "Matrix argument is NULL");
  assert(!source_matrix->data && "Matrix argument data is NULL");
  assert(!source_matrix->columns && "Matrix argument has zero columns");

  assert((col >= source_matrix->columns) && "Invalid col argument");
#endif

  cm_mat_t *col_matrix = cm_mat_alloc(source_matrix->rows, 1);

  for (size_t i = 0; i < source_matrix->rows; ++i)
    col_matrix->data[i] = source_matrix->data[i * source_matrix->columns + col];

  return col_matrix;
}

cm_mat_t *cm_mat_submat(const cm_mat_t *source_matrix, size_t row_start,
                        size_t row_end, size_t col_start, size_t col_end) {

#ifdef CM_DEBUG
  assert(!source_matrix && "Matrix argument is NULL pointer");
  assert(!source_matrix->data && "Matrix argument data is NULL pointer");

  assert((row_start > row_end || col_start > col_end ||
          row_start >= source_matrix->rows || row_end >= source_matrix->rows ||
          col_start >= source_matrix->columns ||
          col_end >= source_matrix->columns) &&
         "Invalid submatrix position");
#endif

  cm_mat_t *submatrix =
      cm_mat_alloc(row_end - row_start + 1, col_end - col_start + 1);
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

cm_mat_t *cm_mat_create_diag(size_t size, cm_real_t init_val) {

  cm_mat_t *diag = cm_mat_create_zero(size, size);

  for (size_t i = 0; i < size; ++i)
    diag->data[i + i * size] = init_val;

  return diag;
}

cm_mat_t *cm_mat_create_identity(size_t size) {
  return cm_mat_create_diag(size, 1);
}

cm_mat_t *cm_mat_create_from_matrix(const cm_mat_t *orig_matrix) {

#ifdef CM_DEBUG
  assert(!orig_matrix && "Matrix argument is NULL");
  assert(!orig_matrix->data && "Matrix argument data is NULL");
#endif

  cm_mat_t *copy_matrix = cm_mat_alloc(orig_matrix->rows, orig_matrix->columns);
  memcpy(copy_matrix->data, orig_matrix->data,
         sizeof(cm_real_t) * orig_matrix->columns * orig_matrix->rows);

  return copy_matrix;
}

cm_mat_t *cm_mat_create_from_array(const cm_real_t **arr, size_t rows,
                                   size_t cols) {

#ifdef CM_DEBUG
  assert(!arr && "cm_real_t array argument is NULL pointer");
#endif

  cm_mat_t *matrix = cm_mat_alloc(rows, cols);

  for (size_t i = 0; i < rows; ++i) {
    memcpy(matrix->data + i * matrix->columns, arr[i],
           sizeof(cm_real_t) * cols);
  }

  return matrix;
}

void cm_mat_free(cm_mat_t *matrix) {
  free(matrix->data);
  free(matrix);
}

/********************** Set matrix **********************/

void cm_mat_set_identity(cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  memset(matrix->data, 0, sizeof(cm_real_t) * matrix->columns * matrix->rows);

  for (size_t i = 0; i < matrix->rows; ++i)
    matrix->data[i + i * matrix->columns] = 1;
}

void cm_mat_set_zero(cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  memset(matrix->data, 0, sizeof(cm_real_t) * matrix->rows * matrix->columns);
}

void cm_mat_set_all(cm_mat_t *matrix, cm_real_t x) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  if (_cm_real_equal(x, 0.))
    cm_mat_set_zero(matrix);

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i)
    matrix->data[i] = x;
}

void cm_mat_set(cm_mat_t *matrix, size_t row, size_t col, cm_real_t x) {
  matrix->data[row * matrix->columns + col] = x;
}

/********************** Matrix operations **********************/

void cm_mat_scale_row(cm_mat_t *matrix, size_t row, size_t scale_by) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
  assert(row >= matrix->rows && "Invalid row argument");
#endif

  for (size_t i = 0; i < matrix->columns; ++i)
    matrix->data[i + (row - 1) * matrix->columns] *= scale_by;
}

void cm_mat_swap(cm_mat_t **matrix_a, cm_mat_t **matrix_b) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A pointer argument is NULL");
  assert(!matrix_b && "Matrix B pointer argument is NULL");

  assert(!*matrix_a && "Matrix A argument is NULL");
  assert(!*matrix_b && "Matrix B argument is NULL");
#endif

  cm_mat_t *tmp = *matrix_a;
  *matrix_a = *matrix_b;
  *matrix_b = tmp;
}

void cm_mat_mul(const cm_mat_t *matrix_a, const cm_mat_t *matrix_b,
                cm_mat_t *result_matrix) {

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
      cm_real_t result_elem = 0;
      for (size_t j = 0; j < matrix_a->columns; ++j) {
        result_elem += matrix_a->data[i * matrix_a->columns + j] *
                       matrix_b->data[j * matrix_b->columns + k];
      }
      result_matrix->data[i * result_matrix->columns + k] = result_elem;
    }
  }
}

cm_real_t cm_mat_max(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  cm_real_t max_out = matrix->data[0];
  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (matrix->data[i] > max_out)
      max_out = matrix->data[i];
  }

  return max_out;
}

cm_real_t cm_mat_min(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  cm_real_t min_out = matrix->data[0];
  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (matrix->data[i] < min_out)
      min_out = matrix->data[i];
  }

  return min_out;
}

// NOTE: fine for general, but mem-heavy for large rect
void cm_mat_transpose(cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix pointer argument is NULL");
  assert(!*matrix && "Matrix argument is NULL");
  assert(!(*matrix)->data && "Matrix argument data is NULL");
#endif

  cm_mat_t *tmp_matrix = cm_mat_alloc(matrix->columns, matrix->rows);

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

cm_real_t cm_mat_trace(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  cm_real_t trace_out = 0.;

  for (size_t i = 0; i < matrix->rows; ++i)
    trace_out += matrix->data[i * matrix->columns + i];

  return trace_out;
}

cm_real_t cm_mat_det(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  if (matrix->columns <= 3)
    return _cm_mat_det_less_3(matrix);

  cm_mat_t *copy_matrix = cm_mat_create_from_matrix(matrix);

  int sign = 1;
  cm_real_t det_out = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {

    size_t pivot = i;
    cm_real_t max_elem = _cm_real_abs(matrix->data[i + i * matrix->columns]);

    for (size_t j = i + 1; j < matrix->rows; ++j) {
      cm_real_t val = _cm_real_abs(matrix->data[i + j * matrix->columns]);
      if (val > max_elem) {
        max_elem = val;
        pivot = j;
      }
    }

    if (_cm_real_equal(max_elem, 0)) {
      cm_mat_free(copy_matrix);
      return det_out;
    }

    if (pivot != i) {
      void *buffer = malloc(copy_matrix->columns * sizeof(cm_real_t));

      memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
             sizeof(cm_real_t) * copy_matrix->columns);

      memmove(copy_matrix->data + (i * copy_matrix->columns),
              copy_matrix->data + (pivot * copy_matrix->columns),
              sizeof(cm_real_t) * copy_matrix->columns);

      memmove(copy_matrix->data + (pivot * copy_matrix->columns), buffer,
              sizeof(cm_real_t) * copy_matrix->columns);

      free(buffer);
      sign *= -sign;
    }

    for (size_t j = i + 1; j < matrix->rows; ++j) {
      cm_real_t factor = matrix->data[i + j * matrix->columns] /
                         matrix->data[i + i * matrix->columns];
      for (size_t k = i; k < matrix->columns; ++k) {
        matrix->data[k + j * matrix->columns] -=
            factor * matrix->data[k + i * matrix->columns];
      }
    }
  }

  for (size_t i = 0; i < matrix->columns; ++i) {
    det_out *= matrix->data[i + i * matrix->columns];
  }

  cm_mat_free(copy_matrix);
  return det_out * sign;
}

cm_mat_t *cm_mat_inverse(const cm_mat_t *orig_matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  cm_mat_t *copy_matrix = cm_mat_create_from_matrix(orig_matrix);
  cm_mat_t *res_matrix = cm_mat_create_identity(orig_matrix->rows);
  size_t mat_size = orig_matrix->rows;

  for (size_t i = 0; i < mat_size; ++i) {

    size_t pivot = i;
    cm_real_t max_elem = _cm_real_abs(copy_matrix->data[i + i * mat_size]);

    for (size_t j = i + 1; j < mat_size; ++j) {
      cm_real_t val = _cm_real_abs(copy_matrix->data[i + j * mat_size]);
      if (val > max_elem) {
        max_elem = val;
        pivot = j;
      }
    }

    if (_cm_real_equal(max_elem, 0)) {
      cm_mat_free(copy_matrix);
      cm_mat_free(res_matrix);
      return NULL;
    }

    if (pivot != i) {
      void *buffer = malloc(mat_size * sizeof(cm_real_t));

      memcpy(buffer, copy_matrix->data + (i * mat_size),
             sizeof(cm_real_t) * mat_size);

      memmove(copy_matrix->data + (i * mat_size),
              copy_matrix->data + (pivot * mat_size),
              sizeof(cm_real_t) * mat_size);

      memmove(copy_matrix->data + (pivot * mat_size), buffer,
              sizeof(cm_real_t) * mat_size);

      memcpy(buffer, res_matrix->data + (i * mat_size),
             sizeof(cm_real_t) * mat_size);

      memmove(res_matrix->data + (i * mat_size),
              res_matrix->data + (pivot * mat_size),
              sizeof(cm_real_t) * mat_size);

      memmove(res_matrix->data + (pivot * mat_size), buffer,
              sizeof(cm_real_t) * mat_size);

      free(buffer);
    }

    for (size_t j = 0; j < mat_size; ++j) {

      if (j == i) {
        continue;
      }

      cm_real_t factor = copy_matrix->data[j * mat_size + i] /
                         copy_matrix->data[i * mat_size + i];

      for (size_t k = 0; k < mat_size; ++k) {

        copy_matrix->data[j * mat_size + k] -=
            factor * copy_matrix->data[i * mat_size + k];

        res_matrix->data[j * res_matrix->columns + k] -=
            factor * res_matrix->data[i * mat_size + k];
      }
    }
  }

  cm_mat_free(copy_matrix);
  return res_matrix;
}

cm_real_t cm_mat_minor(const cm_mat_t *matrix, size_t row, size_t col) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  cm_mat_t *block_matrix = cm_mat_alloc(matrix->rows, matrix->columns);

  size_t block_i = 0;

  for (size_t i = 0; i < matrix->rows; ++i) {
    if (i == row)
      continue;

    size_t block_j = 0;
    for (size_t j = 0; j < matrix->columns; ++j) {
      if (j == col)
        continue;

      cm_real_t elem = matrix->data[i * matrix->columns + j];
      block_matrix->data[block_i * block_matrix->columns + (block_j++)] = elem;
    }
    ++block_i;
  }

  cm_real_t res = cm_mat_det(block_matrix);
  cm_mat_free(block_matrix);

  return res;
}

cm_real_t cm_mat_cofactor(const cm_mat_t *matrix, size_t row, size_t col) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  cm_real_t sign = ((row + col) & 0x1) ? -1 : 1;
  cm_real_t minor = cm_mat_minor(matrix, row, col);

  return sign * minor;
}

void cm_mat_pow(cm_mat_t *matrix, unsigned exp) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  if (exp == 1)
    return;
  else if (exp == 0)
    cm_mat_set_identity(matrix);

  cm_mat_t *res = cm_mat_create_identity(matrix->rows);
  cm_mat_t *tmp = cm_mat_alloc(matrix->rows, matrix->columns);

  while (exp > 0) {
    if (exp & 0x1) {
      cm_mat_mul(res, matrix, tmp);
      cm_mat_swap(&res, &tmp);
    }
    cm_mat_mul(matrix, matrix, tmp);
    cm_mat_swap(&tmp, &matrix);
    exp /= 2;
  }

  memcpy(matrix->data, res->data, sizeof(cm_real_t) * res->rows * res->columns);

  cm_mat_free(res);
  cm_mat_free(tmp);
}

bool cm_mat_is_null(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i) {
    if (!_cm_real_equal(matrix->data[i], 0))
      return false;
  }

  return true;
}

bool cm_mat_is_identity(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      cm_real_t current_elem = matrix->data[i * matrix->columns + j];
      if (i == j && !_cm_real_equal(current_elem, 1))
        return false;
      else if (i != j && !_cm_real_equal(current_elem, 0))
        return false;
    }
  }

  return true;
}

bool cm_mat_is_equal(const cm_mat_t *matrix_a, const cm_mat_t *matrix_b) {

#ifdef CM_DEBUG
  assert(!matrix_a && "Matrix A argument is NULL");
  assert(!matrix_b && "Matrix B argument is NULL");

  assert(!matrix_a->data && "Matrix A argument data is NULL");
  assert(!matrix_b->data && "Matrix B argument data is NULL");

  assert((matrix_a->rows != matrix_b->rows) &&
         (matrix_a->columns != matrix_b->columns) &&
         "Matrices must have same size");
#endif

  if ((matrix_a->rows != matrix_b->rows) ||
      (matrix_a->columns != matrix_b->columns)) {
    return false;
  }

  for (size_t i = 0; i < matrix_a->rows; ++i) {
    for (size_t j = 0; j < matrix_a->columns; ++j) {
      cm_real_t current_elem_a = matrix_a->data[i * matrix_a->columns + j];
      cm_real_t current_elem_b = matrix_b->data[i * matrix_b->columns + j];
      if (!_cm_real_equal(current_elem_a, current_elem_b))
        return false;
    }
  }

  return true;
}

void cm_mat_add(cm_mat_t *matrix_a, const cm_mat_t *matrix_b) {

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

void cm_mat_sub(cm_mat_t *matrix_a, const cm_mat_t *matrix_b) {

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

void cm_mat_scale(cm_mat_t *matrix, cm_real_t scale) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
#endif

  if (_cm_real_equal(scale, 0)) {
    cm_mat_set_zero(matrix);
    return;
  }

  size_t num_of_elems = matrix->rows * matrix->columns;

  for (size_t i = 0; i < num_of_elems; ++i)
    matrix->data[i] *= scale;
}

void cm_mat_swap_rows(cm_mat_t *matrix, size_t row_a, size_t row_b) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
  assert(row_a >= matrix->rows && "Invalid row A argument");
  assert(row_b >= matrix->rows && "Invalid row B argument");
#endif

  size_t row_len = sizeof(cm_real_t) * matrix->columns;

  cm_real_t *buffer = malloc(row_len);

  memcpy(buffer, matrix->data + (row_a - 1) * (matrix->columns - 1), row_len);
  memmove(matrix->data + (row_a - 1) * (matrix->columns - 1),
          matrix->data + (row_b - 1) * (matrix->columns - 1), row_len);
  memmove(matrix->data + (row_b - 1) * (matrix->columns - 1), buffer, row_len);

  free(buffer);
}

void cm_mat_scale_sum_rows(cm_mat_t *matrix, size_t row_scaled, size_t row_sum,
                           size_t scale_by) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");
  assert(row_scaled >= matrix->rows && "Invalid row scaled argument");
  assert(row_sum >= matrix->rows && "Invalid row sum argument");
#endif

  for (size_t i = 0; i < matrix->columns; ++i) {
    matrix->data[i + (row_sum - 1) * (matrix->columns - 1)] +=
        matrix->data[i + (row_scaled - 1) * (matrix->columns - 1)] * scale_by;
  }
}

void cm_mat_gauss(const cm_mat_t *augmented_matrix, cm_real_t *res) {

#ifdef CM_DEBUG
  assert(!augmented_matrix && "Matrix argument is NULL");
  assert(!augmented_matrix->data && "Matrix argument data is NULL");

  assert(!res && "Result array is NULL");

  assert((augmented_matrix->rows != (augmented_matrix->columns - 1)) &&
         "Invalid augmented_matrix size");
#endif

  cm_mat_t *copy_matrix = cm_mat_create_from_matrix(augmented_matrix);

  for (size_t i = 0; i < copy_matrix->rows; ++i) {

    size_t pivot = i;
    cm_real_t max_elem =
        _cm_real_abs(copy_matrix->data[i + i * copy_matrix->columns]);

    for (size_t j = i + 1; j < copy_matrix->rows; ++j) {
      cm_real_t val =
          _cm_real_abs(copy_matrix->data[i + j * copy_matrix->columns]);
      if (val > max_elem) {
        max_elem = val;
        pivot = j;
      }
    }

    if (_cm_real_equal(max_elem, 0)) {
      cm_mat_free(copy_matrix);
      res = NULL;
      return;
    }

    if (pivot != i) {

      void *buffer = malloc(copy_matrix->columns * sizeof(cm_real_t));

      memcpy(buffer, copy_matrix->data + (i * copy_matrix->columns),
             sizeof(cm_real_t) * copy_matrix->columns);

      memmove(copy_matrix->data + (i * copy_matrix->columns),
              copy_matrix->data + (pivot * copy_matrix->columns),
              sizeof(cm_real_t) * copy_matrix->columns);

      memmove(copy_matrix->data + (pivot * copy_matrix->columns), buffer,
              sizeof(cm_real_t) * copy_matrix->columns);

      free(buffer);
    }

    for (size_t j = 0; j < copy_matrix->rows; ++j) {

      if (j == i)
        continue;

      cm_real_t elim_factor = copy_matrix->data[j * copy_matrix->columns + i];

      for (size_t k = 0; k < copy_matrix->columns; ++k) {
        copy_matrix->data[j * copy_matrix->columns + i] =
            (copy_matrix->data[k * copy_matrix->columns + i] * elim_factor *
             -1.) +
            copy_matrix->data[j * copy_matrix->columns + i];
      }
    }
  }

  for (size_t i = 0; i < copy_matrix->rows; ++i) {
    res[i] = copy_matrix
                 ->data[i * copy_matrix->columns + (copy_matrix->columns - 1)];
  }

  cm_mat_free(copy_matrix);
}

cm_mat_t *cm_mat_adj(const cm_mat_t *matrix) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(matrix->rows != matrix->columns &&
         "Invalid matrix type, must be square");
#endif

  cm_mat_t *res_matrix = cm_mat_alloc(matrix->rows, matrix->columns);

  for (size_t i = 0; i < matrix->rows; ++i) {
    for (size_t j = 0; j < matrix->columns; ++j) {
      cm_real_t current_cofactor = cm_mat_cofactor(matrix, i, j);
      cm_mat_set(res_matrix, i, j, current_cofactor);
    }
  }

  cm_mat_transpose(res_matrix);

  return res_matrix;
}

void cm_mat_map(cm_mat_t *matrix, cm_mat_element_op map) {

#ifdef CM_DEBUG
  assert(!matrix && "Matrix argument is NULL");
  assert(!matrix->data && "Matrix argument data is NULL");

  assert(!map && "Map function is NULL");
#endif

  for (size_t i = 0; i < matrix->rows * matrix->columns; ++i)
    matrix->data[i] = map(matrix->data[i]);
}

cm_real_t cm_mat_get(const cm_mat_t *mat, size_t row, size_t col) {
  return mat->data[col + mat->columns * row];
}

size_t cm_mat_rows(const cm_mat_t *mat) { return mat->rows; }
size_t cm_mat_cols(const cm_mat_t *mat) { return mat->columns; }
