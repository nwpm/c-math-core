# Changelog

## [0.1] – Initial release 22.10.25

### Added
- `CmMatrixDouble` – creation/destruction of matrices, element access, basic operations, `map` function to apply a function to each element.
- `CmBigInt` – initialization, basic arithmetic operations.
- `CmVec2` / `CmVec3` – creation, component access, simple vector operations.
- `CmStatusCode` – error and status codes.
- `checkers` – macros for pointer and buffer checks.

## [0.1.1] 23.10.25

### Added

- `cm_matrix_double_scale_row` - scale selected row by X
- `cm_matrix_double_swap_rows` - swap selected rows
- `cm_matrix_double_scale_sum_rows` - scale row A by X and sum with row B
- `cm_matrix_double_to_txt` - save current matrix in txt file
- `_cm_double_abs` - double abs function
- `_cm_double_fabs` - double compare function
- Short info for every matrix function

### Fixed

- `is_identity`, `is_equal` - fix loop error

### Removed

- `matrix_scale_row` - use `cm_matrix_double_scale_row` instead

