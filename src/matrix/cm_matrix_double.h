#ifndef CM_MATRIX_INT_H
#define CM_MATRIX_INT_H

#include <stdbool.h>
#include <stddef.h>

#include "../utils/cm_err_codes.h"

// TODO: cm_matrix_double_set_submatrix(dest, src, row_offset, col_offset)
// TODO: row_op(main row operation)
// TODO: resize
// TODO: LU, QR, Cholesky
// TODO: cm_matrix_double_equals_eps(a, b, eps)
// TODO: random_matrix(rows, cols, min, max)
// TODO: fixed_matrix(3x3, 2x2, 4x4)
// TODO: cm_matrix_double_from_file
// TODO: cm_matrix_double_to_file

typedef struct CmMatrixDouble {
  size_t rows;
  size_t columns;
  double *data;
} CmMatrixDouble;

typedef double(*CmMatrixMapFunc)(double x);

/* Allocations */

/* Allocate row matrix with size Rows * Cols */
CmMatrixDouble *cm_matrix_double_alloc(size_t rows, size_t cols);

/* Allocate zero matrix with size Rows * Cols */
CmMatrixDouble *cm_matrix_double_calloc(size_t rows, size_t cols);

/* Create copy of source matrix */
CmMatrixDouble *
cm_matrix_double_create_from_matrix(const CmMatrixDouble *orig_matrix);

/* Create matrix from double array */
CmMatrixDouble *cm_matrix_double_create_from_array(const double **arr,
                                                   size_t rows, size_t cols);

/* Create row vector from source matrix row */
CmMatrixDouble *cm_matrix_double_row(const CmMatrixDouble *source_matrix,
                                     size_t row);

/* Create column vector from source matrix col */
CmMatrixDouble *cm_matrix_double_col(const CmMatrixDouble *source_matrix,
                                     size_t col);

/* Extract submatrix from source matrix */
CmMatrixDouble *cm_matrix_double_submatrix(const CmMatrixDouble *source_matrix,
                                           size_t row_start, size_t row_end,
                                           size_t col_start, size_t col_end);

/* Create diagonal matrix with size, and init by val */
CmMatrixDouble *cm_matrix_create_diag(size_t size, double init_val);

/* Free allocated matrix */
CmStatusCode cm_matrix_double_free(CmMatrixDouble *matrix);

/* Operations */

CmStatusCode cm_matrix_double_set_identity(CmMatrixDouble *matrix);
CmStatusCode cm_matrix_double_set_zero(CmMatrixDouble *matrix);
CmStatusCode cm_matrix_double_set_all(CmMatrixDouble *matrix, double x);
CmStatusCode cm_matrix_double_swap(CmMatrixDouble **matrix_a,
                                   CmMatrixDouble **matrix_b);
CmStatusCode cm_matrix_double_transpose(CmMatrixDouble **matrix);

CmStatusCode cm_matrix_double_max(const CmMatrixDouble *matrix,
                                  double *max_out);
CmStatusCode cm_matrix_double_min(const CmMatrixDouble *matrix,
                                  double *min_out);
CmStatusCode cm_matrix_double_trace(const CmMatrixDouble *matrix,
                                    double *trace_out);
CmStatusCode cm_matrix_double_det(const CmMatrixDouble *matrix,
                                  double *det_out);

bool cm_matrix_double_is_null(const CmMatrixDouble *matrix);
bool cm_matrix_double_is_identity(const CmMatrixDouble *matrix);
bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b);

CmStatusCode cm_matrix_double_add(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b);
CmStatusCode cm_matrix_double_sub(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b);
CmStatusCode cm_matrix_double_scale(CmMatrixDouble *matrix_a, double scale);
CmStatusCode cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b,
                                  CmMatrixDouble *result_matrix);

CmStatusCode cm_matrix_double_pow(CmMatrixDouble **matrix, unsigned exp);

/* Apply function to all elements of the matrix */
CmStatusCode cm_matrix_double_map(CmMatrixDouble *matrix, CmMatrixMapFunc map);

/* Inverse */
CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix);

/* Minor */
CmStatusCode cm_matrix_double_minor(const CmMatrixDouble *matrix, size_t row,
                                    size_t col, double *minor_out);

/* Cofactor */
CmStatusCode cm_matrix_double_cofactor(const CmMatrixDouble *matrix, size_t row,
                                       size_t col, double *cofactor_out);

/* Adjacency matrix */
CmMatrixDouble *cm_matrix_double_adj(const CmMatrixDouble *matrix);

/* Gauss-Jordan */
CmStatusCode cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix,
                                    double *res);

/* Getter/Setter */

static inline double cm_matrix_double_get(const CmMatrixDouble *matrix,
                                          size_t row, size_t col) {
  return matrix->data[row * matrix->columns + col];
}

static inline void cm_matrix_double_set(CmMatrixDouble *matrix, size_t row,
                                        size_t col, double x) {
  matrix->data[row * matrix->columns + col] = x;
}

/* Debug */
void _cm_matrix_double_printf(const CmMatrixDouble *matrix);

#endif
