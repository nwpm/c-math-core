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

/**
 * @brief Sets the matrix to the identity matrix.
 *
 * @param mat Pointer to the matrix to modify.
 */
void cm_mat_set_identity(cm_mat_t *mat);

/**
 * @brief Sets all elements of the matrix to zero.
 *
 * @param mat Pointer to the matrix to modify.
 */
void cm_mat_set_zero(cm_mat_t *mat);

/**
 * @brief Sets all elements of the matrix to the given value.
 *
 * @param mat Pointer to the matrix to modify.
 * @param x   Value assigned to all matrix elements.
 */
void cm_mat_set_all(cm_mat_t *mat, cm_real_t x);

/**
 * @brief Swaps two matrix pointers.
 *
 * @param mat_a Pointer to the first matrix pointer.
 * @param mat_b Pointer to the second matrix pointer.
 *
 * @note Only the pointers are swapped; matrix data is not copied.
 */
void cm_mat_swap(cm_mat_t **mat_a, cm_mat_t **mat_b);

/**
 * @brief Transposes the matrix in place.
 *
 * @param mat Pointer to the matrix.
 *
 */
void cm_mat_transpose(cm_mat_t *mat);

/**
 * @brief Returns the maximum element of the matrix.
 *
 * @param mat Pointer to the matrix.
 * @return The largest element of the matrix.
 */
cm_real_t cm_mat_max(const cm_mat_t *mat);

/**
 * @brief Returns the minimum element of the matrix.
 *
 * @param mat Pointer to the matrix.
 * @return The smallest element of the matrix.
 */
cm_real_t cm_mat_min(const cm_mat_t *mat);

/**
 * @brief Computes the trace of the matrix.
 *
 * @param mat Pointer to the matrix.
 * @return The trace of the matrix.
 */
cm_real_t cm_mat_trace(const cm_mat_t *mat);

/**
 * @brief Calculates the determinant of the matrix.
 *
 * @param mat Pointer to the matrix.
 * @return The determinant of the matrix.
 *
 */
cm_real_t cm_mat_det(const cm_mat_t *mat);

/**
 * @brief Checks whether the matrix is a null (zero) matrix.
 *
 * @param mat Pointer to the matrix.
 * @return true if all elements are zero, false otherwise.
 */
bool cm_mat_is_null(const cm_mat_t *mat);

/**
 * @brief Checks whether the matrix is an identity matrix.
 *
 * @param mat Pointer to the matrix.
 * @return true if the matrix is identity, false otherwise.
 */
bool cm_mat_is_identity(const cm_mat_t *mat);

/**
 * @brief Checks whether two matrices are equal.
 *
 * @param mat_a Pointer to the first matrix.
 * @param mat_b Pointer to the second matrix.
 * @return true if matrices have the same size and equal elements, false
 * otherwise.
 */
bool cm_mat_is_equal(const cm_mat_t *mat_a, const cm_mat_t *mat_b);

/**
 * @brief Adds matrix B to matrix A.
 *
 * @param mat_a Pointer to the first matrix (modified in place).
 * @param mat_b Pointer to the second matrix.
 *
 * @note Matrices must have the same dimensions.
 */
void cm_mat_add(cm_mat_t *mat_a, const cm_mat_t *mat_b);

/**
 * @brief Subtracts matrix B from matrix A.
 *
 * @param mat_a Pointer to the first matrix (modified in place).
 * @param mat_b Pointer to the second matrix.
 *
 * @note Matrices must have the same dimensions.
 */
void cm_mat_sub(cm_mat_t *mat_a, const cm_mat_t *mat_b);

/**
 * @brief Scales all elements of the matrix by the given factor.
 *
 * @param mat_a Pointer to the matrix.
 * @param scale Scaling factor.
 */
void cm_mat_scale(cm_mat_t *mat_a, cm_real_t scale);

/**
 * @brief Multiplies two matrices.
 *
 * @param mat_a Pointer to the left matrix.
 * @param mat_b Pointer to the right matrix.
 * @param result_mat Pointer to the result matrix.
 *
 * @note Result matrix must have appropriate dimensions.
 */
void cm_mat_mul(const cm_mat_t *mat_a, const cm_mat_t *mat_b,
                cm_mat_t *result_mat);

/**
 * @brief Raises the matrix to the given power.
 *
 * @param mat Pointer to the matrix (modified in place).
 * @param exp Non-negative integer exponent.
 *
 * @note Matrix must be square.
 */
void cm_mat_pow(cm_mat_t *mat, unsigned exp);

/**
 * @brief Scales a matrix row by the given factor.
 *
 * @param mat Pointer to the matrix.
 * @param row Row index.
 * @param scale_by Scaling factor.
 */
void cm_mat_scale_row(cm_mat_t *mat, size_t row, size_t scale_by);

/**
 * @brief Swaps two rows of the matrix.
 *
 * @param mat Pointer to the matrix.
 * @param row_a Index of the first row.
 * @param row_b Index of the second row.
 */
void cm_mat_swap_rows(cm_mat_t *mat, size_t row_a, size_t row_b);

/**
 * @brief Scales one row and adds it to another row.
 *
 * @param mat Pointer to the matrix.
 * @param row_scaled Index of the row to be scaled.
 * @param row_sum Index of the row to which the result is added.
 * @param scale_by Scaling factor.
 *
 * @note Performs: row_sum += row_scaled * scale_by.
 */
void cm_mat_scale_sum_rows(cm_mat_t *mat, size_t row_scaled, size_t row_sum,
                           size_t scale_by);

/**
 * @brief Applies a function to each element of the matrix.
 *
 * @param mat Pointer to the matrix.
 * @param map Function applied to each matrix element.
 *
 * @note map is a pointer to a function.
 */
void cm_mat_map(cm_mat_t *mat, cm_mat_element_op map);

/**
 * @brief Computes the inverse of a matrix.
 *
 * @param orig_mat Pointer to the source matrix.
 * @return A newly allocated inverse matrix.
 *
 * @note Matrix must be square and non-singular.
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_inverse(const cm_mat_t *orig_mat);

/**
 * @brief Computes the minor of a matrix element.
 *
 * @param mat Pointer to the matrix.
 * @param row Row index of the element.
 * @param col Column index of the element.
 * @return The minor corresponding to (row, col).
 *
 * @note Matrix must be square.
 */
cm_real_t cm_mat_minor(const cm_mat_t *mat, size_t row, size_t col);

/**
 * @brief Computes the cofactor of a matrix element.
 *
 * @param mat Pointer to the matrix.
 * @param row Row index of the element.
 * @param col Column index of the element.
 * @return The cofactor corresponding to (row, col).
 *
 * @note Matrix must be square.
 */
cm_real_t cm_mat_cofactor(const cm_mat_t *mat, size_t row, size_t col);

/**
 * @brief Computes the adjugate (adjoint) matrix.
 *
 * @param mat Pointer to the source matrix.
 * @return A newly allocated adjugate matrix.
 *
 * @note Matrix must be square.
 * @note Allocates memory for a new matrix.
 */
cm_mat_t *cm_mat_adj(const cm_mat_t *mat);

/**
 * @brief Solves a linear system using the Gauss–Jordan elimination method.
 *
 * @param augmented_mat Pointer to the augmented matrix.
 * @param res Pointer to the array where the solution will be stored.
 *
 * @note The augmented matrix must have a valid form for the system.
 * @note If the system has no solutions 'res' - NULL.
 */
void cm_mat_gauss(const cm_mat_t *augmented_mat, cm_real_t *res);

/**
 * @brief Gets an element of the matrix by indices.
 *
 * @param mat Pointer to the matrix.
 * @param row Row index.
 * @param col Column index.
 * @return Value of the matrix element at (row, col).
 */
cm_real_t cm_mat_get(const cm_mat_t *mat, size_t row, size_t col);

/**
 * @brief Sets an element of the matrix to a given value.
 *
 * @param mat Pointer to the matrix.
 * @param row Row index.
 * @param col Column index.
 * @param x New value of the matrix element.
 */
void cm_mat_set(cm_mat_t *mat, size_t row, size_t col, cm_real_t x);

#endif
