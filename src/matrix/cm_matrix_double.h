#ifndef CM_MATRIX_DOUBLE_H
#define CM_MATRIX_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

#include "../utils/cm_err_codes.h"

// TODO: cm_matrix_double_set_submatrix(dest, src, row_offset, col_offset)
// TODO: resize
// TODO: LU, QR, Cholesky
// TODO: random_matrix(rows, cols, min, max)
// TODO: fixed_matrix(3x3, 2x2, 4x4)
// TODO: cm_matrix_double_from_file

/* Matrix double type */
typedef struct CmMatrixDouble {
  size_t rows;
  size_t columns;
  double *data;
} CmMatrixDouble;

typedef double (*CmMatrixMapFunc)(double x);

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

/* Set current matrix identity */
CmStatusCode cm_matrix_double_set_identity(CmMatrixDouble *matrix);

/* Set current matrix zero */
CmStatusCode cm_matrix_double_set_zero(CmMatrixDouble *matrix);

/* Set all elements of matrix - X */
CmStatusCode cm_matrix_double_set_all(CmMatrixDouble *matrix, double x);

/* Swap pointers of matrices */
CmStatusCode cm_matrix_double_swap(CmMatrixDouble **matrix_a,
                                   CmMatrixDouble **matrix_b);

/* Transpose current matrix */
CmStatusCode cm_matrix_double_transpose(CmMatrixDouble **matrix);

/* Find max element of matrix */
CmStatusCode cm_matrix_double_max(const CmMatrixDouble *matrix,
                                  double *max_out);

/* Find min element of matrix */
CmStatusCode cm_matrix_double_min(const CmMatrixDouble *matrix,
                                  double *min_out);

/* Calculate matrix trace */
CmStatusCode cm_matrix_double_trace(const CmMatrixDouble *matrix,
                                    double *trace_out);

/* Calculate matrix determinant */
CmStatusCode cm_matrix_double_det(const CmMatrixDouble *matrix,
                                  double *det_out);

/* Check is null matrix */
bool cm_matrix_double_is_null(const CmMatrixDouble *matrix);

/* Check is identity matrix */
bool cm_matrix_double_is_identity(const CmMatrixDouble *matrix);

/* Check is equal matrices */
bool cm_matrix_double_is_equal(const CmMatrixDouble *matrix_a,
                               const CmMatrixDouble *matrix_b);

/* Sum matrix A and B */
CmStatusCode cm_matrix_double_add(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b);
/* Subtract matrix A and B */
CmStatusCode cm_matrix_double_sub(CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b);

/* Scale current matrix by X */
CmStatusCode cm_matrix_double_scale(CmMatrixDouble *matrix_a, double scale);

/* Multiply matrix A and B */
CmStatusCode cm_matrix_double_mul(const CmMatrixDouble *matrix_a,
                                  const CmMatrixDouble *matrix_b,
                                  CmMatrixDouble *result_matrix);

/* Calculate matrix A pow */
CmStatusCode cm_matrix_double_pow(CmMatrixDouble **matrix, unsigned exp);

/* Scale row by X */
CmStatusCode cm_matrix_double_scale_row(CmMatrixDouble *matrix, size_t row,
                                        size_t scale_by);

/* Swap rows A and B */
CmStatusCode cm_matrix_double_swap_rows(CmMatrixDouble *matrix, size_t row_a,
                                        size_t row_b);

/* Scale row A by X and sum with row B */
CmStatusCode cm_matrix_double_scale_sum_rows(CmMatrixDouble *matrix,
                                             size_t row_scaled, size_t row_sum,
                                             size_t scale_by);

/* Apply function to all elements of the matrix */
CmStatusCode cm_matrix_double_map(CmMatrixDouble *matrix, CmMatrixMapFunc map);

/* Find inverse matrix */
CmMatrixDouble *cm_matrix_double_inverse(const CmMatrixDouble *orig_matrix);

/* Calculate minor of current matrix */
CmStatusCode cm_matrix_double_minor(const CmMatrixDouble *matrix, size_t row,
                                    size_t col, double *minor_out);

/* Calculate cofactor of current matrix */
CmStatusCode cm_matrix_double_cofactor(const CmMatrixDouble *matrix, size_t row,
                                       size_t col, double *cofactor_out);

/* Find adjacency matrix */
CmMatrixDouble *cm_matrix_double_adj(const CmMatrixDouble *matrix);

/* Gauss-Jordan */
CmStatusCode cm_matrix_double_gauss(const CmMatrixDouble *augmented_matrix,
                                    double *res);

/* Save current matrix to txt file */
CmStatusCode cm_matrix_double_to_txt(const CmMatrixDouble *matrix,
                                     const char *filename);

/* Getter/Setter */

/* Get element of matrix */
static inline double cm_matrix_double_get(const CmMatrixDouble *matrix,
                                          size_t row, size_t col) {
  return matrix->data[row * matrix->columns + col];
}

/* Set element of matrix to X */
static inline void cm_matrix_double_set(CmMatrixDouble *matrix, size_t row,
                                        size_t col, double x) {
  matrix->data[row * matrix->columns + col] = x;
}

/* Debug */
void _cm_matrix_double_printf(const CmMatrixDouble *matrix);

#endif
