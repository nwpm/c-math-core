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

### Planned

- Optimize division algorithm
- Remove all check macro and replace them by inline functions
- Make common algorithm for hex/bin string conversion
- Make common algorithm for hex/bin creation from string
