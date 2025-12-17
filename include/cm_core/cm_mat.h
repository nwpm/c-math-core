#ifndef CM_MATRIX_H
#define CM_MATRIX_H

#include "cm_types.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct cm_mat_t cm_mat_t;
typedef cm_real_t (*cm_mat_element_op)(cm_real_t x);

/**
 * @brief Allocates an uninitialized matrix of size rows × cols.
 *
 * @param rows Number of rows.
 * @param cols Number of cols.
 * @return A new matrix of size rows × cols.
 *
 * @note Elements of the matrix are uninitialized.
 */
cm_mat_t *cm_mat_alloc(size_t rows, size_t cols);

/**
 * @brief Creates a zero matrix of size rows × cols.
 *
 * @param rows Number of rows.
 * @param cols Number of columns.
 * @return A new zero matrix of size rows × cols
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_create_zero(size_t rows, size_t cols);

/**
 * @brief Creates a copy of the source matrix.
 *
 * @param source The matrix to copy.
 * @return A new matrix that is a copy of the source matrix.
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_create_from_matrix(const cm_mat_t *source);

/**
 * @brief Create a new matrix from a 2D array of real numbers.
 *
 * @param arr Pointer to a 2D pointers array of real numbers.
 * @param rows Number of rows in the array.
 * @param cols Number of columns in the array.
 * @return A new matrix created from the array.
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_create_from_array(const cm_real_t **arr, size_t rows,
                                   size_t cols);

/**
 * @brief Creates a row matrix from a specific row of the source matrix.
 *
 * @param source The source matrix.
 * @param row Index of the row to extract.
 * @return A new matrix corresponding to the specified row.
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_row(const cm_mat_t *source, size_t row);

/**
 * @brief Creates a column matrix from a specific column of the source matrix.
 *
 * @param source The source matrix.
 * @param col Index of the column to extract.
 * @return A new matrix corresponding to the specified column.
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_col(const cm_mat_t *source, size_t col);

/**
 * @brief Creates a matrix from a submatrix of the source matrix.
 *
 * @param source The source matrix.
 * @param row_start Index of the first row of the submatrix.
 * @param row_end Index of the last row of the submatrix.
 * @param col_start Index of the first column of the submatrix.
 * @param col_end Index of the last column of the submatrix.
 * @return A new matrix corresponding to the specified submatrix.
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_submat(const cm_mat_t *source, size_t row_start,
                        size_t row_end, size_t col_start, size_t col_end);

/**
 * @brief Create a diagonal matrix of size n × n.
 *
 * @param n Number of rows and columns of the matrix.
 * @param init_val Value to set on the main diagonal.
 * @return A new diagonal matrix of size n × n.
 *
 * @note Allocates memory for a new matrix
 */
cm_mat_t *cm_mat_create_diag(size_t n, cm_real_t init_val);

/**
 * @brief Creates an identity matrix of size n × n.
 *
 * @param n Number of rows and columns of the matrix.
 * @return A new identity matrix of size n × n.
 *
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_create_identity(size_t n);

/**
 * @brief Free the allocated matrix.
 *
 * @param mat Pointer to the matrix to free.
 *
 */
void cm_mat_free(cm_mat_t *mat);

/* Set current matrix identity */
void cm_mat_set_identity(cm_mat_t *mat);

/* Set current matrix zero */
void cm_mat_set_zero(cm_mat_t *mat);

/* Set all elements of matrix - X */
void cm_mat_set_all(cm_mat_t *mat, cm_real_t x);

/* Swap pointers of matrices */
void cm_mat_swap(cm_mat_t **mat_a, cm_mat_t **mat_b);

/* Transpose current matrix */
void cm_mat_transpose(cm_mat_t *mat);

/* Find max element of matrix */
cm_real_t cm_mat_max(const cm_mat_t *mat);

/* Find min element of matrix */
cm_real_t cm_mat_min(const cm_mat_t *mat);

/* Calculate matrix trace */
cm_real_t cm_mat_trace(const cm_mat_t *mat);

/* Calculate matrix determinant */
cm_real_t cm_mat_det(const cm_mat_t *mat);

/* Check is null matrix */
bool cm_mat_is_null(const cm_mat_t *mat);

/* Check is identity matrix */
bool cm_mat_is_identity(const cm_mat_t *mat);

/* Check is equal matrices */
bool cm_mat_is_equal(const cm_mat_t *mat_a, const cm_mat_t *mat_b);

/* Sum matrix A and B */
void cm_mat_add(cm_mat_t *mat_a, const cm_mat_t *mat_b);
/* Subtract matrix A and B */
void cm_mat_sub(cm_mat_t *mat_a, const cm_mat_t *mat_b);

/* Scale current matrix by X */
void cm_mat_scale(cm_mat_t *mat_a, cm_real_t scale);

/* Multiply matrix A and B */
void cm_mat_mul(const cm_mat_t *mat_a, const cm_mat_t *mat_b,
                cm_mat_t *result_mat);

/* Calculate matrix A pow */
void cm_mat_pow(cm_mat_t *mat, unsigned exp);

/* Scale row by X */
void cm_mat_scale_row(cm_mat_t *mat, size_t row, size_t scale_by);

/* Swap rows A and B */
void cm_mat_swap_rows(cm_mat_t *mat, size_t row_a, size_t row_b);

/* Scale row A by X and sum with row B */
void cm_mat_scale_sum_rows(cm_mat_t *mat, size_t row_scaled, size_t row_sum,
                           size_t scale_by);

/* Apply function to all elements of the matrix */
void cm_mat_map(cm_mat_t *mat, cm_mat_element_op map);

/* Find inverse matrix */
cm_mat_t *cm_mat_inverse(const cm_mat_t *orig_mat);

/* Calculate minor of current matrix */
cm_real_t cm_mat_minor(const cm_mat_t *mat, size_t row, size_t col);

/* Calculate cofactor of current matrix */
cm_real_t cm_mat_cofactor(const cm_mat_t *mat, size_t row, size_t col);

/* Find adjacency matrix */
cm_mat_t *cm_mat_adj(const cm_mat_t *mat);

/* Gauss-Jordan */
void cm_mat_gauss(const cm_mat_t *augmented_mat, cm_real_t *res);

/* Save current matrix to txt file */
void cm_mat_to_txt(const cm_mat_t *mat, const char *filename);

/* Getter/Setter */

/* Get element of matrix */
cm_real_t cm_mat_get(const cm_mat_t *mat, size_t row, size_t col);
/* Set element of matrix to X */
void cm_mat_set(cm_mat_t *mat, size_t row, size_t col, cm_real_t x);
#endif
