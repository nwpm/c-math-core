#ifndef CM_MATRIX_DOUBLE_H
#define CM_MATRIX_DOUBLE_H

#include <stdbool.h>
#include <stddef.h>

/* Matrix double type */
typedef struct cm_dmat_t cm_dmat_t;
typedef double (*cm_dmat_map_func)(double x);

/* Allocate row matrix with size Rows * Cols */
cm_dmat_t *cm_matrix_double_alloc(size_t rows, size_t cols);

/* Allocate zero matrix with size Rows * Cols */
cm_dmat_t *cm_matrix_double_create_zero(size_t rows, size_t cols);

/* Create copy of source matrix */
cm_dmat_t *
cm_matrix_double_create_from_matrix(const cm_dmat_t *orig_matrix);

/* Create matrix from double array */
cm_dmat_t *cm_matrix_double_create_from_array(const double **arr,
                                                   size_t rows, size_t cols);

/* Create row vector from source matrix row */
cm_dmat_t *cm_matrix_double_row(const cm_dmat_t *source_matrix,
                                     size_t row);

/* Create column vector from source matrix col */
cm_dmat_t *cm_matrix_double_col(const cm_dmat_t *source_matrix,
                                     size_t col);

/* Extract submatrix from source matrix */
cm_dmat_t *cm_matrix_double_submatrix(const cm_dmat_t *source_matrix,
                                           size_t row_start, size_t row_end,
                                           size_t col_start, size_t col_end);

/* Create diagonal matrix with size, and init by val */
cm_dmat_t *cm_matrix_double_create_diag(size_t size, double init_val);

/* Create identity matrix with size */
cm_dmat_t *cm_matrix_double_create_identity(size_t size);

/* Free allocated matrix */
void cm_matrix_double_free(cm_dmat_t *matrix);

/* Set current matrix identity */
void cm_matrix_double_set_identity(cm_dmat_t *matrix);

/* Set current matrix zero */
void cm_matrix_double_set_zero(cm_dmat_t *matrix);

/* Set all elements of matrix - X */
void cm_matrix_double_set_all(cm_dmat_t *matrix, double x);

/* Swap pointers of matrices */
void cm_matrix_double_swap(cm_dmat_t **matrix_a,
                           cm_dmat_t **matrix_b);

/* Transpose current matrix */
void cm_matrix_double_transpose(cm_dmat_t *matrix);

/* Find max element of matrix */
double cm_matrix_double_max(const cm_dmat_t *matrix);

/* Find min element of matrix */
double cm_matrix_double_min(const cm_dmat_t *matrix);

/* Calculate matrix trace */
double cm_matrix_double_trace(const cm_dmat_t *matrix);

/* Calculate matrix determinant */
double cm_matrix_double_det(const cm_dmat_t *matrix);

/* Check is null matrix */
bool cm_matrix_double_is_null(const cm_dmat_t *matrix);

/* Check is identity matrix */
bool cm_matrix_double_is_identity(const cm_dmat_t *matrix);

/* Check is equal matrices */
bool cm_matrix_double_is_equal(const cm_dmat_t *matrix_a,
                               const cm_dmat_t *matrix_b);

/* Sum matrix A and B */
void cm_matrix_double_add(cm_dmat_t *matrix_a,
                          const cm_dmat_t *matrix_b);
/* Subtract matrix A and B */
void cm_matrix_double_sub(cm_dmat_t *matrix_a,
                          const cm_dmat_t *matrix_b);

/* Scale current matrix by X */
void cm_matrix_double_scale(cm_dmat_t *matrix_a, double scale);

/* Multiply matrix A and B */
void cm_matrix_double_mul(const cm_dmat_t *matrix_a,
                          const cm_dmat_t *matrix_b,
                          cm_dmat_t *result_matrix);

/* Calculate matrix A pow */
void cm_matrix_double_pow(cm_dmat_t *matrix, unsigned exp);

/* Scale row by X */
void cm_matrix_double_scale_row(cm_dmat_t *matrix, size_t row,
                                size_t scale_by);

/* Swap rows A and B */
void cm_matrix_double_swap_rows(cm_dmat_t *matrix, size_t row_a,
                                size_t row_b);

/* Scale row A by X and sum with row B */
void cm_matrix_double_scale_sum_rows(cm_dmat_t *matrix, size_t row_scaled,
                                     size_t row_sum, size_t scale_by);

/* Apply function to all elements of the matrix */
void cm_matrix_double_map(cm_dmat_t *matrix, cm_dmat_map_func map);

/* Find inverse matrix */
cm_dmat_t *cm_matrix_double_inverse(const cm_dmat_t *orig_matrix);

/* Calculate minor of current matrix */
double cm_matrix_double_minor(const cm_dmat_t *matrix, size_t row,
                              size_t col);

/* Calculate cofactor of current matrix */
double cm_matrix_double_cofactor(const cm_dmat_t *matrix, size_t row,
                                 size_t col);

/* Find adjacency matrix */
cm_dmat_t *cm_matrix_double_adj(const cm_dmat_t *matrix);

/* Gauss-Jordan */
void cm_matrix_double_gauss(const cm_dmat_t *augmented_matrix,
                            double *res);

/* Save current matrix to txt file */
void cm_matrix_double_to_txt(const cm_dmat_t *matrix,
                             const char *filename);

/* Getter/Setter */

/* Get element of matrix */
double cm_matrix_double_get(const cm_dmat_t *matrix, size_t row,
                            size_t col);
/* Set element of matrix to X */
void cm_matrix_double_set(cm_dmat_t *matrix, size_t row, size_t col,
                          double x);
#endif
