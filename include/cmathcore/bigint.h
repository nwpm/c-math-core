#ifndef CM_BIG_INT_H
#define CM_BIG_INT_H

#include <stdbool.h>
#include <stddef.h>

typedef struct cm_bigint_t cm_bigint_t;

/* Allocate row bigint num */
cm_bigint_t *cm_bigint_alloc();

/* Create bigint num from X */
cm_bigint_t *cm_bigint_create_from_num(long long src_num);

/* Create bigint num from c-string */
cm_bigint_t *cm_bigint_create_from_cstr(const char *src_cstr);

/* Create copy of bigint num */
cm_bigint_t *cm_bigint_create_copy(const cm_bigint_t *src_num);

/* Reserve N bytes for bigint data */
void cm_bigint_reserve(cm_bigint_t *bigint_num, size_t size);

/* Free bigint object */
void cm_bigint_free(cm_bigint_t *bigint_num);

/* lhs < rhs bigint compare result */
bool cm_bigint_less(const cm_bigint_t *lhs, const cm_bigint_t *rhs);

/* lhs <= rhs bigint compare result */
bool cm_bigint_less_or_equal(const cm_bigint_t *lhs, const cm_bigint_t *rhs);

/* lhs > rhs bigint compare result */
bool cm_bigint_greater(const cm_bigint_t *lhs, const cm_bigint_t *rhs);

/* lhs >= rhs bigint compare result */
bool cm_bigint_greater_or_equal(const cm_bigint_t *lhs, const cm_bigint_t *rhs);

/* lhs = rhs bigint compare result */
bool cm_bigint_is_equal(const cm_bigint_t *lhs, const cm_bigint_t *rhs);

/* lhs < rhs bigint and long long compare result */
bool cm_bigint_less_ll(const cm_bigint_t *lhs, long long rhs);

/* lhs <= rhs bigint and long long compare result */
bool cm_bigint_less_or_equal_ll(const cm_bigint_t *lhs, long long rhs);

/* lhs > rhs bigint and long long compare result */
bool cm_bigint_greater_ll(const cm_bigint_t *lhs, long long rhs);

/* lhs >= rhs bigint and long long compare result */
bool cm_bigint_greater_or_equal_ll(const cm_bigint_t *lhs, long long rhs);

/* lhs = rhs bigint and long long compare result */
bool cm_bigint_is_equal_ll(const cm_bigint_t *lhs, long long rhs);

/* Adds addend to bigint_num and stores the result in bigint_num. */
void cm_bigint_add(cm_bigint_t *bigint_num, const cm_bigint_t *addend);

/* Subtract value from bigint_num and stores the result in bigint_num */
void cm_bigint_sub(cm_bigint_t *bigint_num, const cm_bigint_t *subtrc);
void cm_bigint_mult(cm_bigint_t *bigint_num, const cm_bigint_t *multiplier);
void cm_bigint_div(cm_bigint_t *bigint_num, const cm_bigint_t *divider);

void cm_bigint_inc(cm_bigint_t *bigint_num);
void cm_bigint_dec(cm_bigint_t *bigint_num);

void cm_bigint_add_ll(cm_bigint_t *bigint_num, long long addend);
void cm_bigint_sub_ll(cm_bigint_t *bigint_num, long long subtrc);

void cm_bigint_mod(cm_bigint_t *bigint_num, const cm_bigint_t *divider);
void cm_bigint_div_mod(cm_bigint_t *quotient, cm_bigint_t *remainder,
                       const cm_bigint_t *dividend, const cm_bigint_t *divider);

cm_bigint_t *cm_bigint_gcd(const cm_bigint_t *bigint_a, const cm_bigint_t *bigint_b);

/* Calculate num^(exp) */
void cm_bigint_pow(cm_bigint_t *bigint_num, unsigned long long exp);

/* Check */
bool cm_bigint_is_positive(const cm_bigint_t *bigint_num);
bool cm_bigint_is_zero(const cm_bigint_t *bigint_num);

/* Check is bigint num odd */
bool cm_bigint_is_even(const cm_bigint_t *bigint_num);

/* Check is bigint num even */
bool cm_bigint_is_odd(const cm_bigint_t *bigint_num);

/* Shifts */
void cm_bigint_shift_left(cm_bigint_t *bigint_num, size_t k);
void cm_bigint_shift_right(cm_bigint_t *bigint_num, size_t k);

/* Convert */
char *cm_bigint_to_string(const cm_bigint_t *bigint_num);

/* Setters */
void cm_bigint_set(cm_bigint_t *bigint_num, const cm_bigint_t *setter);
void cm_bigint_set_long(cm_bigint_t *bigint_num, long long setter);

/* Other */
void cm_bigint_negate(cm_bigint_t *bigint_num);
void cm_bigint_abs(cm_bigint_t *bigint_num);

void cm_bigint_shrink_to_fit(cm_bigint_t *bigint_num);
size_t cm_bigint_num_digits(const cm_bigint_t *bigint_num);

/* Alloc hex c-string from bigint num */
char *cm_bigint_to_hex_string(const cm_bigint_t *bigint_num);

/* Alloc bin c-string from bigint num */
char *cm_bigint_to_bin_string(const cm_bigint_t *bigint_num);

/* Create bigint num from c-string */
cm_bigint_t *cm_bigint_from_bin_string(const char *str);

#endif
