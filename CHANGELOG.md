# Changelog
All notable changes to this project will be documented in this file.
The format is based on Keep a Changelog and this project adheres to Semantic Versioning.

## [0.1] – Initial release 22.10.25

### Added
- `CmMatrixDouble` – creation/destruction of matrices;
                     element access;
                     basic operations;
                     `map` function to apply a function to each element.
- `CmBigInt`       – initialization;
                     basic arithmetic operations.
- `CmVec2` / `CmVec3` – creation;
                        component access;
                        simple vector operations.
- `CmStatusCode` – error and status codes.
- `checkers`     – macros for pointer and buffer checks.

## [0.1.1] 23.10.25

### Added

- `cm_matrix_double_scale_row` - scale selected row by X.
- `cm_matrix_double_swap_rows` - swap selected rows.
- `cm_matrix_double_scale_sum_rows` - scale row A by X and sum with row B.
- `cm_matrix_double_to_txt`         - save current matrix in txt file.
- `_cm_double_abs`                  - double abs function.
- `_cm_double_fabs`                 - compare doubles by absolute value.
- Short info for every matrix function.

### Fixed

- `is_identity`, `is_equal` - fixed loop error

### Removed

- `matrix_scale_row` - use `cm_matrix_double_scale_row` instead

## [0.2] 29.10.25

### Added

- `cm_bigint_is_even`
- `cm_bigint_is_odd`
- `cm_bigint_num_digits`
- `cm_bigint_reserve`
- `cm_bigint_resize`
- `cm_bigint_gcd`
- `cm_bigint_to_hex_string`
- `cm_bigint_to_bin_string`
- `cm_bigint_from_bin_string`
- `cm_bigint_pow`
- short info for every function in .h file

### Removed

- `cm_bigint_resize`

### Changed

- `cm_bigint_alloc`     - set init capacity to zero.
- `cm_bigint_divide`    - renamed to div.
- `cm_bigint_to_string` - refactor.
- `cm_bigint_negate`    - changed return value to CmStatusCode;
                          add zero check.

### Fixed

- `cm_bigint_is_equal` - fixed interpretation of the memcmp result.
- `cm_bigint_less_ll`  - fixed memory leak(free for rhs_str);
                         use abs val for rhs;
                         fixed '_cm_itoa' cast from int to char.

- `cm_bigint_is_equal_ll` - fixed memory leak(free for rhs_str);
                            added NULL check for rhs_str;
                            fixed memcmp compare with zero.

- `cm_vec3_cross`      - fixed calculation of cross product.
- `_cm_is_zero_buff`   - fixed char compare.

- `_cm_calculate_mult` - fixed memset to char 0;
                         fixed multiplication bias(counter k);
                         added temp multiplication check.

- `cm_bigint_shift_left`  - fixed memset char zero.
- `cm_bigint_shift_right` - fixed set char zero;
                            fixed memmove size.

- `cm_bigint_divide/mod`  - fixed memory leak(free for remainder and quotient);
                            added NULL check for allocated remainder and quotient;
                            set correct result sign;
                            added update 'bigint_num'.

- `_cm_calculate_inc/dec`    - fixed loop end condition.
- `cm_bigint_add/subtract_ll`- fixed memory leak(free for tmp long long value).
- `cm_bigint_shrink_to_fit`  - fixed capacity update.

### Optimized

- `cm_bigint_dec` - removed compare for zero in else, use is_zero variable.

## [0.3] 04.11.2025

### Added

- Added base objects for 2D/3D geometry.
- Added alloc/create functions for 2d primitives

- Added different checkers in debug version of matrix module:
    NULL matrix ptr;
    NULL matrix data ptr;
    zero columns;
    zero rows;

- `cm_matrix_double_create_identity`
- `_cm_llong_abs`
- `_cm_long_abs`

### Removed

- `cm_checkers.h`

### Changed

- Reworked and revised the return code logic.
  Most NULL checks were moved, they used only in DEBUG mod
  to improve performance.
  Return codes are now used only where mathematical
  errors or internal memory allocation failures may occur.

- Reworked style of internal NULL checks, after memory allocations
  in matrix module.

- `cm_matrix_double_add`                - refactored matrix sum.
- `cm_matrix_double_sub`                - refactored matrix subtract.
- `cm_matrix_double_create_from_matrix` - refactored, use memcpy instead loop.

- `cm_matrix_double_transpose`,
  `cm_matrix_double_pow`                - refactored, use ptr to matrix
                                          instead double ptr;

- `_cm_long_abs`            - moved to utils module
- `cm_matrix_double_calloc` - renamed to 'cm_matrix_double_create_zero'


### Fixed

- `cm_matrix_double_set_all`   - fixed double zero check, use epsilon
                                 compare
- `cm_matrix_double_pow`       - fixed memory leak(free for tmp matrix).

- `cm_matrix_double_det`,
  `cm_matrix_double_swap_rows`- fixed memory leak(free for buffer).

### Optimized

- `cm_matrix_double_inverse`,
  `cm_matrix_double_gauss`,
  `cm_matrix_double_det`      - moved buffer allocation outside the loop.

- `cm_bigint_create_from_num` - inner buffer alloc memory equal len of number.

## [0.4]

### Added

- `cm_vec2_double_rotate`
- `cm_vec2_double_rotate_inplace`
- `cm_vec2_double_distance`
- `cm_vec2_double_sum_inplace`
- `cm_vec2_double_sub_inplace`
- `cm_vec2_double_scale_inplace`

- `cm_vec3_double_distance`
- `cm_vec3_double_sum_inplace`
- `cm_vec3_double_sub_inplace`
- `cm_vec3_double_scale_inplace`

- Added short documentation for vec2/vec3 functions

### Remowed

- Remowed heap allocation functions for vec2/vec3.

### Changed

- `cm_vec2_double_is_null`,
- `cm_vec3_double_is_null`- renamed to 'cm_vec2_double_is_zero'

### Planned

- Optimize division algorithm
- Remove all check macro and replace them by inline functions
- Make common algorithm for hex/bin string conversion
- Make common algorithm for hex/bin creation from string
- Add user data check in DEBUG mod
- Add DEBUG common data checkers
- Remove all NULL alloc checks and zero checks
- Remove all CmStatusCode
- Create simple objects on stack, heavy object allocate.
