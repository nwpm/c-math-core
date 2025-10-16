#include "cm_bigint.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/cm_checkers.h"

static bool _cm_is_valid_cstr(const char *cstr) {

  size_t i = 0;

  while (cstr[i] != '\0') {
    if (cstr[i] < '0' || cstr[i] > '9') {
      return false;
    }
    i++;
  }

  return true;
}

static bool _cm_is_zero_buff(const char *buff, size_t size) {

  for (size_t i = 0; i < size; ++i) {
    if (buff[i] != 0)
      return false;
  }

  return true;
}

static size_t _cm_calc_capacity(size_t size) {
  if (size < 100) {
    return size * 2;
  } else if (size < 10000) {
    return size + size / 2;
  } else if (size < 1000000) {
    return size + size / 10;
  }
  return size + (size / 20);
}

static char *_cm_itoa(long long num, size_t size) {

  char *num_str = calloc(size, sizeof(char));
  if (!num_str)
    return NULL;

  size_t i = 0;

  do {
    int current_digit = num % 10;
    num_str[i++] = current_digit;
  } while (num / 10);

  return num_str;
}

static inline long long _cm_long_abs(long long num) {
  return (num < 0) ? -num : num;
}

static size_t _cm_long_digit_count(long long num) {

  if (num >= 0 && num < 10)
    return 1;

  long long result = 1;

  while (num /= 10)
    result++;

  return result;
}

static bool _cm_ensure_capacity(CmBigInt *bigint_num, size_t max_size) {

  if (bigint_num->capacity < max_size) {

    bigint_num->capacity = _cm_calc_capacity(max_size);
    void *new_buffer = realloc(bigint_num->buffer, bigint_num->capacity);
    if (!new_buffer) {
      return false;
    }

    bigint_num->buffer = new_buffer;
  }
  return true;
}

static bool _cm_bigint_create_from_cstr(CmBigInt *n, const char *cstr,
                                        char sign) {

  if (!_cm_is_valid_cstr(cstr)) {
    return false;
  }

  size_t cstr_len = strlen(cstr);

  if (cstr_len >= n->capacity) {
    n->capacity = _cm_calc_capacity(cstr_len);
  }

  char *alloc_buffer = malloc(n->capacity);
  if (!alloc_buffer)
    return false;

  size_t j = 0;
  size_t i = cstr_len;
  while (i-- > 0) {
    alloc_buffer[j++] = cstr[i];
  }

  n->buffer = alloc_buffer;
  n->size = cstr_len;
  n->sign = sign;

  return 0;
}

// Duplicates the buffer of CmBigInt, copying num->size bytes into a new buffer
// of size num->capacity.
static char *_buff_dup(const CmBigInt *num) {

  char *copy_buff = malloc(num->capacity);

  if (!copy_buff)
    return NULL;

  memcpy(copy_buff, num->buffer, num->size);

  return copy_buff;
}

static int _cm_bigint_abs_compare(const CmBigInt *lhs, const CmBigInt *rhs) {

  if (lhs->size != rhs->size) {
    return (lhs->size > rhs->size) ? 1 : -1;
  }

  for (size_t i = lhs->size; i > 0; i--) {
    if (lhs->buffer[i - 1] > rhs->buffer[i - 1])
      return 1;
    else if (lhs->buffer[i - 1] < rhs->buffer[i - 1])
      return -1;
  }

  return 0;
}

static char _cm_calculate_res_sign(const CmBigInt *lhs, const CmBigInt *rhs,
                                   char operation) {

  int compare_res = _cm_bigint_abs_compare(lhs, rhs);

  if (operation == '+') {
    if (compare_res == 0) {
      return (lhs->sign == '-' && rhs->sign == '-') ? '-' : '+';
    } else if (compare_res == 1) {
      return (lhs->sign == '-') ? '-' : '+';
    } else if (compare_res == -1) {
      return (rhs->sign == '+') ? '+' : '-';
    }
  }

  if (compare_res == 1) {
    return (lhs->sign == '-') ? '-' : '+';
  } else if (compare_res == -1) {
    return (rhs->sign == '+') ? '-' : '+';
  }

  return (lhs->sign == '-' && rhs->sign == '+') ? '-' : '+';
}

static CmStatusCode _cm_calculate_sum(CmBigInt *bigint_num,
                                      const CmBigInt *addend, char res_sign) {

  int compare_res = _cm_bigint_abs_compare(bigint_num, addend);

  const CmBigInt *smaller_abs_num = (compare_res >= 0) ? addend : bigint_num;
  const CmBigInt *greater_abs_num = (compare_res >= 0) ? bigint_num : addend;

  size_t max_size = greater_abs_num->size + 1;

  if (!_cm_ensure_capacity(bigint_num, max_size))
    return CM_ERR_ALLOC_FAILED;

  int add_part = 0;
  size_t i = 0;

  while (i < smaller_abs_num->size) {
    int digit_greater = greater_abs_num->buffer[i] - '0';
    int digit_smaller = smaller_abs_num->buffer[i] - '0';
    int sum = (digit_greater + digit_smaller + add_part);

    if (sum > 9) {
      sum -= 10;
      add_part = 1;
    } else {
      add_part = 0;
    }

    bigint_num->buffer[i++] = sum + '0';
  }

  while (i < greater_abs_num->size) {
    int digit_greater = greater_abs_num->buffer[i] - '0';
    int sum = digit_greater + add_part;

    if (sum > 9) {
      sum -= 10;
      add_part = 1;
    } else {
      add_part = 0;
    }

    bigint_num->buffer[i++] = sum + '0';
  }

  if (add_part) {
    bigint_num->buffer[i++] = add_part + '0';
  }

  bigint_num->size = i;
  bigint_num->sign = res_sign;

  return CM_SUCCESS;
}

static CmStatusCode _cm_calculate_inc(CmBigInt *bigint_num, char res_sign) {

  CM_CHECK_NULL(bigint_num);
  size_t max_size = bigint_num->size + 1;

  if (!_cm_ensure_capacity(bigint_num, max_size))
    return CM_ERR_ALLOC_FAILED;

  int add_part = 1;
  size_t i = 0;
  size_t j = bigint_num->size;

  do {

    int bigint_digit = bigint_num->buffer[i] - '0';
    int sum = bigint_digit + add_part;

    if (sum > 9) {
      sum -= 10;
      add_part = 1;
    } else {
      add_part = 0;
    }

    bigint_num->buffer[i++] = sum + '0';

  } while (add_part && j--);

  if (add_part) {
    bigint_num->buffer[i] = add_part + '0';
    bigint_num->size++;
  }

  bigint_num->sign = res_sign;

  return CM_SUCCESS;
}

static CmStatusCode _cm_calculate_dec(CmBigInt *bigint_num, char res_sign) {

  int substr_part = 1;
  size_t i = 0;
  size_t j = bigint_num->size;

  do {

    int bigint_digit = bigint_num->buffer[i] - '0';
    int substr = bigint_digit - substr_part;

    if (substr < 0) {
      substr += 10;
      substr_part = 1;
    } else {
      substr_part = 0;
    }
    bigint_num->buffer[i++] = substr + '0';

  } while (substr_part && j--);

  while (bigint_num->size > 1 &&
         bigint_num->buffer[bigint_num->size - 1] == '0') {
    bigint_num->size--;
  }

  bigint_num->sign = res_sign;

  return CM_SUCCESS;
}

static CmStatusCode _cm_calculate_dif(CmBigInt *bigint_num,
                                      const CmBigInt *substr, char res_sign) {

  int compare_res = _cm_bigint_abs_compare(bigint_num, substr);

  const CmBigInt *smaller_abs_num = (compare_res >= 0) ? substr : bigint_num;
  const CmBigInt *greater_abs_num = (compare_res >= 0) ? bigint_num : substr;

  if (!_cm_ensure_capacity(bigint_num, greater_abs_num->size))
    return CM_ERR_ALLOC_FAILED;

  int substr_part = 0;
  size_t i = 0;

  while (i < smaller_abs_num->size) {
    int digit_greater = greater_abs_num->buffer[i] - '0';
    int digit_smaller = smaller_abs_num->buffer[i] - '0';
    int substr = (digit_greater - digit_smaller) - substr_part;

    if (substr < 0) {
      substr += 10;
      substr_part = 1;
    } else {
      substr_part = 0;
    }
    bigint_num->buffer[i++] = substr + '0';
  }

  while (i < greater_abs_num->size) {
    int digit_greater = greater_abs_num->buffer[i] - '0';
    int substr = digit_greater - substr_part;

    if (substr < 0) {
      substr += 10;
      substr_part = 1;
    } else {
      substr_part = 0;
    }
    bigint_num->buffer[i++] = substr + '0';
  }

  bigint_num->size = i;

  while (bigint_num->size > 1 &&
         bigint_num->buffer[bigint_num->size - 1] == '0') {
    bigint_num->size--;
  }

  bigint_num->sign = res_sign;

  return CM_SUCCESS;
}

static CmStatusCode _cm_calculate_mult(CmBigInt *bigint_num,
                                       const CmBigInt *multiplier) {

  int compare_res = _cm_bigint_abs_compare(bigint_num, multiplier);

  const CmBigInt *smaller_abs_num =
      (compare_res >= 0) ? multiplier : bigint_num;
  const CmBigInt *greater_abs_num =
      (compare_res >= 0) ? bigint_num : multiplier;

  size_t max_size = greater_abs_num->size + smaller_abs_num->size;

  CmBigInt *res_of_mult = cm_bigint_alloc();
  if (!res_of_mult)
    return CM_ERR_ALLOC_FAILED;

  CmBigInt *temp = cm_bigint_alloc();
  if (!temp)
    return CM_ERR_ALLOC_FAILED;

  if (!_cm_ensure_capacity(temp, max_size))
    return CM_ERR_ALLOC_FAILED;

  for (size_t i = 0; i < smaller_abs_num->size; ++i) {
    int digit_smaller = smaller_abs_num->buffer[i] - '0';
    int mult_part = 0;
    size_t k = 0;

    memset(temp->buffer, 0, temp->capacity);

    for (size_t j = 0; j < greater_abs_num->size; ++j) {
      int digit_greater = greater_abs_num->buffer[j] - '0';

      int mult = (digit_smaller * digit_greater) + mult_part;

      if (mult > 10) {
        mult_part = mult / 10;
        mult %= 10;
      } else {
        mult_part = 0;
      }
      temp->buffer[k++] = mult + '0';
    }
    if (mult_part) {
      temp->buffer[k++] = mult_part + '0';
    }

    temp->size = k;

    cm_bigint_add(res_of_mult, temp);
  }

  res_of_mult->sign = (bigint_num->sign == multiplier->sign) ? '+' : '-';

  free(bigint_num->buffer);
  bigint_num->buffer = res_of_mult->buffer;
  bigint_num->size = res_of_mult->size;
  bigint_num->sign = res_of_mult->sign;
  bigint_num->capacity = res_of_mult->capacity;
  free(res_of_mult);

  cm_bigint_free(temp);

  return CM_SUCCESS;
}

// Shift-subtract
// TODO: Knuth D
static CmStatusCode _cm_calculate_div(const CmBigInt *dividend,
                                      const CmBigInt *divider,
                                      CmBigInt *remainder, CmBigInt *quotient) {

  if (_cm_is_zero_buff(divider->buffer, divider->size))
    return CM_ERR_ZERO_DIVISION;

  if (cm_bigint_less(dividend, divider) ||
      _cm_is_zero_buff(dividend->buffer, dividend->size)) {
    return CM_SUCCESS;
  }

  CmBigInt *divider_copy = cm_bigint_create_copy(divider);
  CmBigInt *one = cm_bigint_create_from_num(1);

  while (cm_bigint_greater_or_equal(remainder, divider_copy)) {
    size_t shift = 0;

    cm_bigint_shift_left(divider_copy, shift + 1);
    while (cm_bigint_less_or_equal(divider_copy, remainder)) {
      cm_bigint_shift_left(divider_copy, shift);
      shift++;
    }
    cm_bigint_shift_right(divider_copy, shift);
    cm_bigint_subtract(remainder, divider_copy);

    cm_bigint_shift_left(one, shift);
    cm_bigint_add(quotient, one);

    cm_bigint_shift_right(one, shift);
  }

  cm_bigint_free(one);
  cm_bigint_free(divider_copy);

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_shift_left(CmBigInt *bigint_num, size_t k) {

  CM_CHECK_NULL(bigint_num);

  if (!_cm_ensure_capacity(bigint_num, bigint_num->size + k))
    return CM_ERR_ALLOC_FAILED;

  memmove(bigint_num->buffer + k, bigint_num->buffer, bigint_num->size);
  memset(bigint_num->buffer, 0, k);
  bigint_num->size += k;

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_shift_right(CmBigInt *bigint_num, size_t k) {

  CM_CHECK_NULL(bigint_num);

  if (k >= bigint_num->size) {
    bigint_num->buffer[0] = 0;
    bigint_num->size = 1;
    bigint_num->sign = '+';
    return CM_SUCCESS;
  }

  memmove(bigint_num->buffer, bigint_num->buffer + k, bigint_num->size);
  bigint_num->size -= k;

  return CM_SUCCESS;
}

CmBigInt *cm_bigint_alloc() {

  CmBigInt *bigint_num = malloc(sizeof(CmBigInt));

  if (!bigint_num)
    return NULL;

  bigint_num->size = 0;
  bigint_num->sign = '+';
  bigint_num->buffer = NULL;
  bigint_num->capacity = CM_BIGINT_START_CAPACITY;

  return bigint_num;
}

CmBigInt *cm_bigint_create_copy(const CmBigInt *src_num) {

  if (!src_num)
    return NULL;

  CmBigInt *new_num = cm_bigint_alloc();

  if (!new_num)
    return NULL;

  new_num->size = src_num->size;
  new_num->sign = src_num->sign;
  new_num->capacity = src_num->capacity;

  if (!src_num->buffer) {
    new_num->buffer = NULL;
    return new_num;
  }

  new_num->buffer = _buff_dup(src_num);

  if (!new_num->buffer) {
    free(new_num);
    return NULL;
  }

  return new_num;
}

CmBigInt *cm_bigint_create_from_num(long long src_num) {

  CmBigInt *bigint_num = cm_bigint_alloc();

  if (!bigint_num)
    return NULL;

  long long abs_num = _cm_long_abs(src_num);

  bigint_num->sign = (src_num < 0) ? '-' : '+';
  bigint_num->size = _cm_long_digit_count(abs_num);
  bigint_num->capacity = _cm_calc_capacity(bigint_num->size);

  char *alloc_buffer = malloc(bigint_num->capacity);
  if (!alloc_buffer)
    return NULL;

  for (size_t i = 0; i < bigint_num->size; ++i) {
    alloc_buffer[i] = (abs_num % 10) + '0';
    abs_num /= 10;
  }

  bigint_num->buffer = alloc_buffer;

  return bigint_num;
}

CmBigInt *cm_bigint_create_from_cstr(const char *cstr) {

  if (!cstr)
    return NULL;

  CmBigInt *bigint_num = cm_bigint_alloc();

  if (!bigint_num)
    return NULL;

  bool is_created = false;

  if (cstr[0] == '-' || cstr[0] == '+') {
    const char *magnitude = cstr + 1;
    is_created = _cm_bigint_create_from_cstr(bigint_num, magnitude, cstr[0]);
  } else {
    is_created = _cm_bigint_create_from_cstr(bigint_num, cstr, '+');
  }

  if (!is_created) {
    free(bigint_num);
    return NULL;
  }

  return bigint_num;
}

bool cm_bigint_less(const CmBigInt *lhs, const CmBigInt *rhs) {

  if (lhs->sign == '+' && rhs->sign == '-') {
    return false;
  } else if (lhs->sign == '-' && rhs->sign == '+') {
    return true;
  }

  bool is_negative = (lhs->sign == '-');
  if (lhs->size != rhs->size) {
    return is_negative ? (lhs->size > rhs->size) : (lhs->size < rhs->size);
  }

  for (size_t i = lhs->size; i > 0; i--) {
    if (lhs->buffer[i - 1] != rhs->buffer[i - 1]) {
      return is_negative ? (lhs->buffer[i - 1] > rhs->buffer[i - 1])
                         : (lhs->buffer[i - 1] < rhs->buffer[i - 1]);
    }
  }

  return false;
}

bool cm_bigint_less_or_equal(const CmBigInt *lhs, const CmBigInt *rhs) {

  if (!cm_bigint_is_equal(lhs, rhs)) {
    if (!cm_bigint_less(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_greater(const CmBigInt *lhs, const CmBigInt *rhs) {
  return !cm_bigint_less_or_equal(lhs, rhs);
}

bool cm_bigint_greater_or_equal(const CmBigInt *lhs, const CmBigInt *rhs) {

  if (!cm_bigint_is_equal(lhs, rhs)) {
    if (cm_bigint_less(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_is_equal(const CmBigInt *lhs, const CmBigInt *rhs) {

  if (lhs->size == rhs->size) {
    if (lhs->sign == rhs->sign) {
      if (memcmp(lhs->buffer, rhs->buffer, lhs->size))
        return true;
    }
  }

  return false;
}

bool cm_bigint_is_positive(const CmBigInt *bigint_num) {
  return bigint_num->sign == '+';
}

bool cm_bigint_less_ll(const CmBigInt *lhs, long long rhs) {

  bool rhs_is_positive = rhs >= 0;
  bool lhs_is_positive = cm_bigint_is_positive(lhs);

  if (!lhs_is_positive && rhs_is_positive) {
    return true;
  } else if (lhs_is_positive && !rhs_is_positive) {
    return false;
  }

  size_t rhs_digit_number = _cm_long_digit_count(rhs);

  if (lhs->size != rhs_digit_number) {
    return !lhs_is_positive ? (lhs->size > rhs_digit_number)
                            : (lhs->size < rhs_digit_number);
  }

  const char *rhs_str = _cm_itoa(rhs, rhs_digit_number);

  for (size_t i = lhs->size; i > 0; i--) {
    if (lhs->buffer[i - 1] != rhs_str[i - 1]) {
      return !lhs_is_positive ? (lhs->buffer[i - 1] > rhs_str[i - 1])
                              : (lhs->buffer[i - 1] < rhs_str[i - 1]);
    }
  }

  return true;
}

bool cm_bigint_is_equal_ll(const CmBigInt *lhs, long long rhs) {

  size_t rhs_digit_number = _cm_long_digit_count(rhs);
  const char *rhs_str = _cm_itoa(rhs, rhs_digit_number);
  char rhs_sign = (rhs >= 0) ? '+' : '-';

  if (lhs->size == rhs_digit_number) {
    if (lhs->sign == rhs_sign) {
      if (memcmp(lhs->buffer, rhs_str, lhs->size))
        return true;
    }
  }

  return false;
}

bool cm_bigint_less_or_equal_ll(const CmBigInt *lhs, long long rhs) {

  if (!cm_bigint_is_equal_ll(lhs, rhs)) {
    if (!cm_bigint_less_ll(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_greater_ll(const CmBigInt *lhs, long long rhs) {
  return !cm_bigint_less_or_equal_ll(lhs, rhs);
}

bool cm_bigint_greater_or_equal_ll(const CmBigInt *lhs, long long rhs) {

  if (!cm_bigint_is_equal_ll(lhs, rhs)) {
    if (cm_bigint_less_ll(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_is_zero(const CmBigInt *bigint_num) {
  return _cm_is_zero_buff(bigint_num->buffer, bigint_num->size);
}

CmStatusCode cm_bigint_add(CmBigInt *bigint_num, const CmBigInt *addend) {

  CM_CHECK_NULL(bigint_num);
  CM_CHECK_NULL(addend);

  CmStatusCode res_code;
  char res_sign = _cm_calculate_res_sign(bigint_num, addend, '+');

  if (bigint_num->sign == addend->sign) {
    res_code = _cm_calculate_sum(bigint_num, addend, res_sign);
  } else {
    res_code = _cm_calculate_dif(bigint_num, addend, res_sign);
  }

  return res_code;
}

CmStatusCode cm_bigint_add_ll(CmBigInt *bigint_num, long long addend) {

  CM_CHECK_NULL(bigint_num);

  CmBigInt *bigint_addend = cm_bigint_create_from_num(addend);
  if (!bigint_addend)
    return CM_ERR_ALLOC_FAILED;

  return cm_bigint_add(bigint_num, bigint_addend);
}

CmStatusCode cm_bigint_sub_ll(CmBigInt *bigint_num, long long subtrc) {

  CM_CHECK_NULL(bigint_num);

  CmBigInt *bigint_subtrc = cm_bigint_create_from_num(subtrc);
  if (!bigint_subtrc)
    return CM_ERR_ALLOC_FAILED;

  return cm_bigint_subtract(bigint_num, bigint_subtrc);
}

CmStatusCode cm_bigint_subtract(CmBigInt *bigint_num, const CmBigInt *substr) {

  CM_CHECK_NULL(bigint_num);
  CM_CHECK_NULL(substr);

  CmStatusCode res_code;
  char res_sign = _cm_calculate_res_sign(bigint_num, substr, '-');

  if (bigint_num->sign == substr->sign) {
    res_code = _cm_calculate_dif(bigint_num, substr, res_sign);
  } else {
    res_code = _cm_calculate_sum(bigint_num, substr, res_sign);
  }

  return res_code;
}

CmStatusCode cm_bigint_multiply(CmBigInt *bigint_num,
                                const CmBigInt *multiplier) {

  CM_CHECK_NULL(bigint_num);
  CM_CHECK_NULL(multiplier);

  return _cm_calculate_mult(bigint_num, multiplier);
}

CmStatusCode cm_bigint_divide(CmBigInt *bigint_num, const CmBigInt *divider) {

  CM_CHECK_NULL(bigint_num);
  CM_CHECK_NULL(divider);

  CmBigInt *remainder = cm_bigint_alloc();
  CM_CHECK_NULL(remainder);

  CmBigInt *quotient = cm_bigint_alloc();
  CM_CHECK_NULL(quotient);

  return cm_bigint_div_mod(quotient, remainder, bigint_num, divider);
}

CmStatusCode cm_bigint_mod(CmBigInt *bigint_num, const CmBigInt *divider) {

  CM_CHECK_NULL(bigint_num);
  CM_CHECK_NULL(divider);

  CmBigInt *remainder = cm_bigint_alloc();
  CM_CHECK_NULL(remainder);

  CmBigInt *quotient = cm_bigint_alloc();
  CM_CHECK_NULL(quotient);

  return cm_bigint_div_mod(quotient, remainder, bigint_num, divider);
}

CmStatusCode cm_bigint_div_mod(CmBigInt *quotient, CmBigInt *remainder,
                               const CmBigInt *dividend,
                               const CmBigInt *divider) {

  CM_CHECK_NULL(quotient);
  CM_CHECK_NULL(remainder);
  CM_CHECK_NULL(dividend);
  CM_CHECK_NULL(divider);

  cm_bigint_set(remainder, dividend);
  cm_bigint_set_long(quotient, 0);

  return _cm_calculate_div(dividend, divider, remainder, quotient);
}

CmStatusCode cm_bigint_inc(CmBigInt *bigint_num) {
  CM_CHECK_NULL(bigint_num);

  CmStatusCode res_code;

  if (bigint_num->sign == '+') {
    res_code = _cm_calculate_inc(bigint_num, '+');
  } else {
    char res_sign =
        cm_bigint_is_equal_ll(bigint_num, -1) ? '+' : bigint_num->sign;
    res_code = _cm_calculate_dec(bigint_num, res_sign);
  }

  return res_code;
}

CmStatusCode cm_bigint_dec(CmBigInt *bigint_num) {

  CM_CHECK_NULL(bigint_num);

  CmStatusCode res_code;
  bool is_zero = cm_bigint_is_zero(bigint_num);

  if (bigint_num->sign == '-' || is_zero) {
    res_code = _cm_calculate_inc(bigint_num, '-');
  } else {
    char res_sign =
        cm_bigint_is_equal_ll(bigint_num, 0) ? '-' : bigint_num->sign;
    res_code = _cm_calculate_dec(bigint_num, res_sign);
  }

  return res_code;
}

CmStatusCode cm_bigint_set(CmBigInt *bigint_num, const CmBigInt *setter) {

  CM_CHECK_NULL(bigint_num);
  CM_CHECK_NULL(setter);

  char *new_buffer = malloc(setter->size);
  if (!new_buffer)
    return NULL;

  free(bigint_num->buffer);
  bigint_num->buffer = new_buffer;
  bigint_num->size = setter->size;
  bigint_num->capacity = setter->size;
  bigint_num->sign = setter->sign;
  memcpy(bigint_num->buffer, setter->buffer, setter->size);

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_set_long(CmBigInt *bigint_num, long long setter) {

  CM_CHECK_NULL(bigint_num);

  long long abs_num = _cm_long_abs(setter);

  bigint_num->sign = (setter < 0) ? '-' : '+';
  bigint_num->size = _cm_long_digit_count(abs_num);
  if (!_cm_ensure_capacity(bigint_num, bigint_num->size)) {
    return CM_ERR_ALLOC_FAILED;
  }

  for (size_t i = 0; i < bigint_num->size; ++i) {
    bigint_num->buffer[i] = (abs_num % 10) + '0';
    abs_num /= 10;
  }

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_shrink_to_fit(CmBigInt *bigint_num) {

  CM_CHECK_NULL(bigint_num);

  if (bigint_num->capacity > bigint_num->size) {
    void *new_buffer = realloc(bigint_num->buffer, bigint_num->size);
    if (!new_buffer) {
      return CM_ERR_ALLOC_FAILED;
    }

    bigint_num->buffer = new_buffer;
  }

  return CM_SUCCESS;
}

CmBigInt *cm_bigint_abs(CmBigInt *bigint_num) {

  if (!bigint_num)
    return NULL;

  bigint_num->sign = '+';

  return bigint_num;
}

CmBigInt *cm_bigint_negate(CmBigInt *bigint_num) {

  if (!bigint_num)
    return NULL;

  bigint_num->sign = (bigint_num->sign == '+') ? '-' : '+';

  return bigint_num;
}

char *cm_bigint_to_string(const CmBigInt *bigint_num) {

  if (!bigint_num)
    return NULL;

  char *str = malloc(bigint_num->size);
  if (!str)
    return NULL;

  memcpy(str, bigint_num->buffer, bigint_num->size);
  return str;
}

void cm_bigint_free(CmBigInt *bigint_num) {
  free(bigint_num->buffer);
  free(bigint_num);
}
