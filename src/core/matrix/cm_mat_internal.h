#ifndef CM_MATRIX_INTERNAL_H
#define CM_MATRIX_INTERNAL_H

#include "../../../include/cm_core/cm_types.h"
#include <stddef.h>

// TODO: cm_matrix_double_set_submatrix(dest, src, row_offset, col_offset)
// TODO: resize
// TODO: LU, QR, Cholesky
// TODO: random_matrix(rows, cols, min, max)
// TODO: fixed_matrix(3x3, 2x2, 4x4)
// TODO: cm_matrix_double_from_txt
// TODO: linear transfonmations(rotation, mirror, projection, shear, scale
// compration, expantion)

/* Matrix double type */
typedef struct cm_mat_t {
  size_t rows;
  size_t columns;
  cm_real_t *data;
} cm_mat_t;

#ifdef CM_DEBUG
void _cm_matrix_double_printf(const cm_dmat_t *matrix);
#endif

#endif
