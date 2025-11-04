#include "cm_bigint.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/cm_utils.h"

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
    if (buff[i] != '0')
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

  char *num_str = malloc(size * sizeof(char));
  if (!num_str)
    return NULL;

  size_t i = 0;

  do {
    int current_digit = num % 10;
    num_str[i++] = current_digit + '0';
  } while (num / 10);

  return num_str;
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
    void *new_buffer = realloc(bigint_num->data, bigint_num->capacity);
    if (!new_buffer) {
      return false;
    }

    bigint_num->data = new_buffer;
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

  n->data = alloc_buffer;
  n->size = cstr_len;
  n->sign = sign;

  return true;
}

// Duplicates the buffer of CmBigInt, copying num->size bytes into a new buffer
// of size num->capacity.
static char *_buff_dup(const CmBigInt *num) {

  char *copy_buff = malloc(num->capacity);

  if (!copy_buff)
    return NULL;

  memcpy(copy_buff, num->data, num->size);

  return copy_buff;
}

static int _cm_bigint_abs_compare(const CmBigInt *lhs, const CmBigInt *rhs) {

  if (lhs->size != rhs->size) {
    return (lhs->size > rhs->size) ? 1 : -1;
  }

  for (size_t i = lhs->size; i > 0; i--) {
    if (lhs->data[i - 1] > rhs->data[i - 1])
      return 1;
    else if (lhs->data[i - 1] < rhs->data[i - 1])
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

// TODO: refactor
static char _cm_char_decimal_hex_convert(char *num, size_t size) {

  if (size == 1)
    return num[0];

  int decimal_num = 10;
  decimal_num += num[1] - '0';

  char hex_nums[] = "0123456789ABCDEF";
  return hex_nums[decimal_num];
}

static char _cm_char_hex_decimal_convert(char num) {
  if (num >= '0' || num <= '9')
    return num - '0';

  return (num - 'A') + 10;
}

static void _cm_reverse_str(char *str) {
  int end_index = strlen(str) - 1;

  for (int start_index = 0; start_index <= end_index;
       ++start_index, --end_index) {
    char tmp = str[start_index];
    str[start_index] = str[end_index];
    str[end_index] = tmp;
  }
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
    int digit_greater = greater_abs_num->data[i] - '0';
    int digit_smaller = smaller_abs_num->data[i] - '0';
    int sum = (digit_greater + digit_smaller + add_part);

    if (sum > 9) {
      sum -= 10;
      add_part = 1;
    } else {
      add_part = 0;
    }

    bigint_num->data[i++] = sum + '0';
  }

  while (i < greater_abs_num->size) {
    int digit_greater = greater_abs_num->data[i] - '0';
    int sum = digit_greater + add_part;

    if (sum > 9) {
      sum -= 10;
      add_part = 1;
    } else {
      add_part = 0;
    }

    bigint_num->data[i++] = sum + '0';
  }

  if (add_part) {
    bigint_num->data[i++] = add_part + '0';
  }

  bigint_num->size = i;
  bigint_num->sign = res_sign;

  return CM_SUCCESS;
}

static CmStatusCode _cm_calculate_inc(CmBigInt *bigint_num, char res_sign) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  size_t max_size = bigint_num->size + 1;

  if (!_cm_ensure_capacity(bigint_num, max_size))
    return CM_ERR_ALLOC_FAILED;

  int add_part = 1;
  size_t i = 0;
  size_t j = bigint_num->size;

  do {

    int bigint_digit = bigint_num->data[i] - '0';
    int sum = bigint_digit + add_part;

    if (sum > 9) {
      sum -= 10;
      add_part = 1;
    } else {
      add_part = 0;
    }

    bigint_num->data[i++] = sum + '0';

  } while (add_part && i < j);

  if (add_part) {
    bigint_num->data[i] = add_part + '0';
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

    int bigint_digit = bigint_num->data[i] - '0';
    int substr = bigint_digit - substr_part;

    if (substr < 0) {
      substr += 10;
      substr_part = 1;
    } else {
      substr_part = 0;
    }
    bigint_num->data[i++] = substr + '0';

  } while (substr_part && i < j);

  while (bigint_num->size > 1 &&
         bigint_num->data[bigint_num->size - 1] == '0') {
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
    int digit_greater = greater_abs_num->data[i] - '0';
    int digit_smaller = smaller_abs_num->data[i] - '0';
    int substr = (digit_greater - digit_smaller) - substr_part;

    if (substr < 0) {
      substr += 10;
      substr_part = 1;
    } else {
      substr_part = 0;
    }
    bigint_num->data[i++] = substr + '0';
  }

  while (i < greater_abs_num->size) {
    int digit_greater = greater_abs_num->data[i] - '0';
    int substr = digit_greater - substr_part;

    if (substr < 0) {
      substr += 10;
      substr_part = 1;
    } else {
      substr_part = 0;
    }
    bigint_num->data[i++] = substr + '0';
  }

  bigint_num->size = i;

  while (bigint_num->size > 1 &&
         bigint_num->data[bigint_num->size - 1] == '0') {
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
    int digit_smaller = smaller_abs_num->data[i] - '0';
    int mult_part = 0;
    size_t k = i;

    memset(temp->data, '0', temp->capacity);

    for (size_t j = 0; j < greater_abs_num->size; ++j) {
      int digit_greater = greater_abs_num->data[j] - '0';

      int mult = (digit_smaller * digit_greater) + mult_part;

      if (mult >= 10) {
        mult_part = mult / 10;
        mult %= 10;
      } else {
        mult_part = 0;
      }
      temp->data[k++] = mult + '0';
    }

    if (mult_part) {
      temp->data[k++] = mult_part + '0';
    }

    temp->size = k;

    cm_bigint_add(res_of_mult, temp);
  }

  res_of_mult->sign = (bigint_num->sign == multiplier->sign) ? '+' : '-';

  free(bigint_num->data);
  bigint_num->data = res_of_mult->data;
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

  if (_cm_is_zero_buff(divider->data, divider->size))
    return CM_ERR_ZERO_DIVISION;

  if (cm_bigint_less(dividend, divider) ||
      _cm_is_zero_buff(dividend->data, dividend->size)) {
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

  quotient->sign = (dividend->sign == divider->sign) ? '+' : '-';

  cm_bigint_free(one);
  cm_bigint_free(divider_copy);

  return CM_SUCCESS;
}

CmBigInt *cm_bigint_alloc() {

  CmBigInt *bigint_num = malloc(sizeof(CmBigInt));

  if (!bigint_num)
    return NULL;

  bigint_num->size = 0;
  bigint_num->sign = '+';
  bigint_num->data = NULL;
  bigint_num->capacity = 0;

  return bigint_num;
}

CmBigInt *cm_bigint_create_copy(const CmBigInt *src_num) {

#ifdef CM_DEBUG
  assert(!src_num && "Bigint num argument is NULL");
  assert(!src_num->data && "Bigint num argument data is NULL");
#endif

  CmBigInt *new_num = cm_bigint_alloc();
  if (!new_num)
    return NULL;

  new_num->size = src_num->size;
  new_num->sign = src_num->sign;
  new_num->capacity = src_num->capacity;

  if (!src_num->data) {
    new_num->data = NULL;
    return new_num;
  }

  new_num->data = _buff_dup(src_num);

  if (!new_num->data) {
    free(new_num);
    return NULL;
  }

  return new_num;
}

// LLONG_MIN case
CmBigInt *cm_bigint_create_from_num(long long src_num) {

  long long abs_num = _cm_llong_abs(src_num);
  size_t num_len = _cm_long_digit_count(abs_num);

  CmBigInt *bigint_num = cm_bigint_alloc();
  char *alloc_buffer = malloc(num_len);
  if (!bigint_num || !alloc_buffer) {
    cm_bigint_free(bigint_num);
    free(alloc_buffer);
    return NULL;
  }

  bigint_num->sign = (src_num < 0) ? '-' : '+';
  bigint_num->size = num_len;
  bigint_num->capacity = _cm_calc_capacity(bigint_num->size);

  for (size_t i = 0; i < bigint_num->size; ++i) {
    alloc_buffer[i] = (abs_num % 10) + '0';
    abs_num /= 10;
  }

  bigint_num->data = alloc_buffer;

  return bigint_num;
}

CmBigInt *cm_bigint_create_from_cstr(const char *cstr) {

#ifdef CM_DEBUG
  assert(!cstr && "C-string is NULL");
#endif

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

CmStatusCode cm_bigint_reserve(CmBigInt *bigint_num, size_t size) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  void *new_buffer = realloc(bigint_num->data, size);
  if (!new_buffer) {
    return CM_ERR_ALLOC_FAILED;
  }

  if (bigint_num->size > size) {
    bigint_num->size = size;
  }

  bigint_num->data = new_buffer;
  bigint_num->capacity = size;

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_shift_left(CmBigInt *bigint_num, size_t k) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (!_cm_ensure_capacity(bigint_num, bigint_num->size + k))
    return CM_ERR_ALLOC_FAILED;

  memmove(bigint_num->data + k, bigint_num->data, bigint_num->size);
  memset(bigint_num->data, '0', k);
  bigint_num->size += k;

  return CM_SUCCESS;
}

void cm_bigint_shift_right(CmBigInt *bigint_num, size_t k) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (k >= bigint_num->size) {
    bigint_num->data[0] = '0';
    bigint_num->size = 1;
    bigint_num->sign = '+';
    return;
  }

  memmove(bigint_num->data, bigint_num->data + k, bigint_num->size - k);
  bigint_num->size -= k;
}

// TODO: after execution, some unused memory remains
char *cm_bigint_to_hex_string(const CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (cm_bigint_is_zero(bigint_num)) {
    char *zero_str = malloc(2);
    if (!zero_str)
      return NULL;
    zero_str[0] = '0';
    zero_str[1] = '\0';
    return zero_str;
  }

  bool is_negative = (bigint_num->sign == '-');

  size_t alloc_size = bigint_num->size + 1 + (is_negative ? 1 : 0);

  char *res_str = malloc(alloc_size);
  CmBigInt *copy_bigint = cm_bigint_create_copy(bigint_num);
  CmBigInt *divider = cm_bigint_create_from_num(16);
  CmBigInt *remainder = cm_bigint_alloc();
  CmBigInt *quotient = cm_bigint_alloc();

  if (!res_str || !copy_bigint || !divider || !remainder || !quotient) {
    free(res_str);
    cm_bigint_free(copy_bigint);
    cm_bigint_free(divider);
    cm_bigint_free(remainder);
    cm_bigint_free(quotient);
    return NULL;
  }

  size_t i = 0;
  CmStatusCode div_res;
  cm_bigint_abs(copy_bigint);

  while (!cm_bigint_is_zero(copy_bigint)) {

    div_res = cm_bigint_div_mod(quotient, remainder, copy_bigint, divider);
    if (div_res != CM_SUCCESS) {
      free(res_str);
      cm_bigint_free(copy_bigint);
      cm_bigint_free(divider);
      cm_bigint_free(remainder);
      cm_bigint_free(quotient);
      return NULL;
    }
    cm_bigint_set(copy_bigint, quotient);

    char hex_num =
        _cm_char_decimal_hex_convert(remainder->data, remainder->size);
    res_str[i++] = hex_num;
  }

  if (is_negative) {
    res_str[i++] = '-';
  }

  res_str[i] = '\0';
  _cm_reverse_str(res_str);

  cm_bigint_free(copy_bigint);
  cm_bigint_free(divider);
  cm_bigint_free(remainder);
  cm_bigint_free(quotient);

  return res_str;
}

char *cm_bigint_to_bin_string(const CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (cm_bigint_is_zero(bigint_num)) {
    char *zero_str = malloc(2);
    if (!zero_str)
      return NULL;
    zero_str[0] = '0';
    zero_str[1] = '\0';
    return zero_str;
  }

  bool is_negative = (bigint_num->sign == '-');

  size_t alloc_size = bigint_num->size + 1 + (is_negative ? 1 : 0);

  char *res_str = malloc(alloc_size);
  CmBigInt *copy_bigint = cm_bigint_create_copy(bigint_num);
  CmBigInt *divider = cm_bigint_create_from_num(2);
  CmBigInt *remainder = cm_bigint_alloc();
  CmBigInt *quotient = cm_bigint_alloc();

  if (!res_str || !copy_bigint || !divider || !remainder || !quotient) {
    free(res_str);
    cm_bigint_free(copy_bigint);
    cm_bigint_free(divider);
    cm_bigint_free(remainder);
    cm_bigint_free(quotient);
    return NULL;
  }

  size_t i = 0;
  CmStatusCode div_res;
  cm_bigint_abs(copy_bigint);

  while (!cm_bigint_is_zero(copy_bigint)) {

    div_res = cm_bigint_div_mod(quotient, remainder, copy_bigint, divider);
    if (div_res != CM_SUCCESS) {
      free(res_str);
      cm_bigint_free(copy_bigint);
      cm_bigint_free(divider);
      cm_bigint_free(remainder);
      cm_bigint_free(quotient);
      return NULL;
    }
    cm_bigint_set(copy_bigint, quotient);

    char bin_num = cm_bigint_is_zero(remainder) ? 0 : 1;
    res_str[i++] = bin_num;
  }

  if (is_negative) {
    res_str[i++] = '-';
  }

  res_str[i] = '\0';
  _cm_reverse_str(res_str);

  cm_bigint_free(copy_bigint);
  cm_bigint_free(divider);
  cm_bigint_free(remainder);
  cm_bigint_free(quotient);

  return res_str;
}

CmBigInt *cm_bigint_from_bin_string(const char *str) {

#ifdef CM_DEBUG
  assert(!str && "Binary string is NULL");
#endif

  CmBigInt *res = cm_bigint_alloc();
  CmBigInt *two_base = cm_bigint_create_from_num(2);
  if (!res || !two_base) {
    cm_bigint_free(res);
    cm_bigint_free(two_base);
    return NULL;
  }

  size_t str_len = strlen(str);

  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] == '1') {
      cm_bigint_pow(two_base, str_len - 1);
      cm_bigint_add(res, two_base);
      cm_bigint_set_long(two_base, 2);
    }
  }

  cm_bigint_free(two_base);
  return res;
}

CmBigInt *cm_bigint_from_hex_string(const char *str) {

#ifdef CM_DEBUG
  assert(!str && "Hex string is NULL");
#endif

  CmBigInt *res = cm_bigint_alloc();
  CmBigInt *hex_base = cm_bigint_create_from_num(16);
  CmBigInt *tmp = cm_bigint_alloc();
  if (!res || !hex_base || !tmp) {
    cm_bigint_free(res);
    cm_bigint_free(hex_base);
    cm_bigint_free(tmp);
    return NULL;
  }

  size_t str_len = strlen(str);

  for (size_t i = 0; str[i] != '\0'; ++i) {
    if (str[i] != '0') {
      cm_bigint_pow(hex_base, str_len - 1);
      cm_bigint_set_long(tmp, str[i] - '0');
      cm_bigint_multiply(tmp, hex_base);

      cm_bigint_add(res, tmp);

      cm_bigint_set_long(hex_base, 2);
    }
  }

  cm_bigint_free(hex_base);
  cm_bigint_free(tmp);
  return res;
}

bool cm_bigint_less(const CmBigInt *lhs, const CmBigInt *rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");

  assert(!rhs && "Rhs num argument is NULL");
  assert(!rhs->data && "Rhs num argument data is NULL");
#endif

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
    if (lhs->data[i - 1] != rhs->data[i - 1]) {
      return is_negative ? (lhs->data[i - 1] > rhs->data[i - 1])
                         : (lhs->data[i - 1] < rhs->data[i - 1]);
    }
  }

  return false;
}

bool cm_bigint_less_or_equal(const CmBigInt *lhs, const CmBigInt *rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");

  assert(!rhs && "Rhs num argument is NULL");
  assert(!rhs->data && "Rhs num argument data is NULL");
#endif

  if (!cm_bigint_is_equal(lhs, rhs)) {
    if (!cm_bigint_less(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_greater(const CmBigInt *lhs, const CmBigInt *rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");

  assert(!rhs && "Rhs num argument is NULL");
  assert(!rhs->data && "Rhs num argument data is NULL");
#endif

  return !cm_bigint_less_or_equal(lhs, rhs);
}

bool cm_bigint_greater_or_equal(const CmBigInt *lhs, const CmBigInt *rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");

  assert(!rhs && "Rhs num argument is NULL");
  assert(!rhs->data && "Rhs num argument data is NULL");
#endif

  if (!cm_bigint_is_equal(lhs, rhs)) {
    if (cm_bigint_less(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_is_equal(const CmBigInt *lhs, const CmBigInt *rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");

  assert(!rhs && "Rhs num argument is NULL");
  assert(!rhs->data && "Rhs num argument data is NULL");
#endif

  if (lhs->size == rhs->size) {
    if (lhs->sign == rhs->sign) {
      if (memcmp(lhs->data, rhs->data, lhs->size) == 0)
        return true;
    }
  }

  return false;
}

bool cm_bigint_is_positive(const CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  return bigint_num->sign == '+';
}

bool cm_bigint_less_ll(const CmBigInt *lhs, long long rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");
#endif

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

  char *rhs_str = _cm_itoa(_cm_long_abs(rhs), rhs_digit_number);
  if (!rhs_str)
    return false;

  for (size_t i = lhs->size; i > 0; i--) {
    if (lhs->data[i - 1] != rhs_str[i - 1]) {
      return !lhs_is_positive ? (lhs->data[i - 1] > rhs_str[i - 1])
                              : (lhs->data[i - 1] < rhs_str[i - 1]);
    }
  }

  free(rhs_str);

  return false;
}

bool cm_bigint_is_equal_ll(const CmBigInt *lhs, long long rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");
#endif

  size_t rhs_digit_number = _cm_long_digit_count(rhs);
  char *rhs_str = _cm_itoa(_cm_long_abs(rhs), rhs_digit_number);
  if (!rhs_str)
    return false;

  char rhs_sign = (rhs >= 0) ? '+' : '-';

  if (lhs->size == rhs_digit_number) {
    if (lhs->sign == rhs_sign) {
      if (memcmp(lhs->data, rhs_str, lhs->size) == 0)
        return true;
    }
  }

  free(rhs_str);

  return false;
}

bool cm_bigint_less_or_equal_ll(const CmBigInt *lhs, long long rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");
#endif

  if (!cm_bigint_is_equal_ll(lhs, rhs)) {
    if (!cm_bigint_less_ll(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_greater_ll(const CmBigInt *lhs, long long rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");
#endif

  return !cm_bigint_less_or_equal_ll(lhs, rhs);
}

bool cm_bigint_greater_or_equal_ll(const CmBigInt *lhs, long long rhs) {

#ifdef CM_DEBUG
  assert(!lhs && "Lhs num argument is NULL");
  assert(!lhs->data && "Lhs num argument data is NULL");
#endif

  if (!cm_bigint_is_equal_ll(lhs, rhs)) {
    if (cm_bigint_less_ll(lhs, rhs))
      return false;
  }

  return true;
}

bool cm_bigint_is_zero(const CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  return _cm_is_zero_buff(bigint_num->data, bigint_num->size);
}

CmStatusCode cm_bigint_add(CmBigInt *bigint_num, const CmBigInt *addend) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");

  assert(!addend && "Addend num argument is NULL");
  assert(!addend->data && "Addent num argument data is NULL");
#endif

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

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  CmBigInt *bigint_addend = cm_bigint_create_from_num(addend);
  if (!bigint_addend)
    return CM_ERR_ALLOC_FAILED;

  CmStatusCode add_res = cm_bigint_add(bigint_num, bigint_addend);
  cm_bigint_free(bigint_addend);

  return add_res;
}

CmStatusCode cm_bigint_sub_ll(CmBigInt *bigint_num, long long subtrc) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  CmBigInt *bigint_subtrc = cm_bigint_create_from_num(subtrc);
  if (!bigint_subtrc)
    return CM_ERR_ALLOC_FAILED;

  CmStatusCode sub_res = cm_bigint_subtract(bigint_num, bigint_subtrc);
  cm_bigint_free(bigint_subtrc);

  return sub_res;
}

CmStatusCode cm_bigint_subtract(CmBigInt *bigint_num, const CmBigInt *substr) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");

  assert(!substr && "Substr num argument is NULL");
  assert(!substr->data && "Substr num argument data is NULL");
#endif

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

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");

  assert(!multiplier && "Multiplier num argument is NULL");
  assert(!multiplier->data && "Multiplier num argument data is NULL");
#endif

  return _cm_calculate_mult(bigint_num, multiplier);
}

CmStatusCode cm_bigint_pow(CmBigInt *bigint_num, unsigned long long exp) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (exp == 0) {
    cm_bigint_set_long(bigint_num, 1);
    return CM_SUCCESS;
  }

  if (exp == 1) {
    return CM_SUCCESS;
  }

  CmBigInt *res = cm_bigint_create_from_num(1);
  if (!res) {
    cm_bigint_free(res);
    return CM_ERR_ALLOC_FAILED;
  }

  while (exp > 0) {
    if (exp & 0x1) {
      cm_bigint_multiply(res, bigint_num);
    }
    cm_bigint_multiply(bigint_num, bigint_num);
    exp /= 2;
  }

  cm_bigint_set(bigint_num, res);
  cm_bigint_free(res);

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_div(CmBigInt *bigint_num, const CmBigInt *divider) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");

  assert(!divider && "divider num argument is NULL");
  assert(!divider->data && "divider num argument data is NULL");
#endif

  CmBigInt *remainder = cm_bigint_alloc();
  CmBigInt *quotient = cm_bigint_alloc();
  if (!remainder || !quotient) {
    cm_bigint_free(remainder);
    cm_bigint_free(quotient);
    return CM_ERR_ALLOC_FAILED;
  }

  CmStatusCode div_res =
      cm_bigint_div_mod(quotient, remainder, bigint_num, divider);

  cm_bigint_set(bigint_num, quotient);

  cm_bigint_free(remainder);
  cm_bigint_free(quotient);

  return div_res;
}

CmStatusCode cm_bigint_mod(CmBigInt *bigint_num, const CmBigInt *divider) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");

  assert(!divider && "divider num argument is NULL");
  assert(!divider->data && "divider num argument data is NULL");
#endif

  CmBigInt *remainder = cm_bigint_alloc();
  CmBigInt *quotient = cm_bigint_alloc();
  if (!remainder || !quotient) {
    cm_bigint_free(remainder);
    cm_bigint_free(quotient);
    return CM_ERR_ALLOC_FAILED;
  }

  CmStatusCode mod_res =
      cm_bigint_div_mod(quotient, remainder, bigint_num, divider);

  cm_bigint_set(bigint_num, remainder);

  cm_bigint_free(remainder);
  cm_bigint_free(quotient);

  return mod_res;
}

CmStatusCode cm_bigint_gcd(const CmBigInt *bigint_a, const CmBigInt *bigint_b,
                           CmBigInt *res) {

#ifdef CM_DEBUG
  assert(!bigint_a && "Bigint A num argument is NULL");
  assert(!bigint_a->data && "Bigint A num argument data is NULL");

  assert(!bigint_b && "Bigint B num argument is NULL");
  assert(!bigint_b->data && "Bigint B num argument data is NULL");

  assert(!res && "Res num argument is NULL");
  assert(!res->data && "Res num argument data is NULL");
#endif

  CmBigInt *copy_a = cm_bigint_create_copy(bigint_a);
  CmBigInt *copy_b = cm_bigint_create_copy(bigint_b);
  CmBigInt *tmp = cm_bigint_alloc();
  if (!tmp || !copy_a || !copy_b) {
    cm_bigint_free(copy_a);
    cm_bigint_free(copy_b);
    cm_bigint_free(tmp);
    return CM_ERR_ALLOC_FAILED;
  }

  CmStatusCode div_status;

  while (!cm_bigint_is_zero(copy_b)) {

    div_status = cm_bigint_div_mod(NULL, tmp, copy_a, copy_b);
    if (div_status != CM_SUCCESS) {
      cm_bigint_free(copy_a);
      cm_bigint_free(copy_b);
      cm_bigint_free(tmp);
      return div_status;
    }

    cm_bigint_set(copy_a, copy_b);
    cm_bigint_set(copy_b, tmp);
  }

  cm_bigint_set(res, copy_a);
  res->sign = '+';

  cm_bigint_free(copy_a);
  cm_bigint_free(copy_b);
  cm_bigint_free(tmp);

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_div_mod(CmBigInt *quotient, CmBigInt *remainder,
                               const CmBigInt *dividend,
                               const CmBigInt *divider) {

#ifdef CM_DEBUG
  assert(!quotient && "Quotient num argument is NULL");
  assert(!quotient->data && "Quotient num argument data is NULL");

  assert(!remainder && "Remainder num argument is NULL");
  assert(!remainder->data && "Remainder num argument data is NULL");

  assert(!dividend && "Dividend num argument is NULL");
  assert(!dividend && "Dividend num argument data is NULL");

  assert(!divider && "Divider num argument is NULL");
  assert(!divider && "Divider num argument data is NULL");
#endif

  cm_bigint_set(remainder, dividend);
  cm_bigint_set_long(quotient, 0);

  return _cm_calculate_div(dividend, divider, remainder, quotient);
}

CmStatusCode cm_bigint_inc(CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

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

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  CmStatusCode res_code;
  bool is_zero = cm_bigint_is_zero(bigint_num);

  if (bigint_num->sign == '-' || is_zero) {
    res_code = _cm_calculate_inc(bigint_num, '-');
  } else {
    char res_sign = is_zero ? '-' : bigint_num->sign;
    res_code = _cm_calculate_dec(bigint_num, res_sign);
  }

  return res_code;
}

CmStatusCode cm_bigint_set(CmBigInt *bigint_num, const CmBigInt *setter) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");

  assert(!setter && "Setter num argument is NULL");
  assert(!setter && "Setter num argument data is NULL");
#endif

  char *new_buffer = malloc(setter->size);
  if (!new_buffer)
    return CM_ERR_ALLOC_FAILED;

  free(bigint_num->data);
  bigint_num->data = new_buffer;
  bigint_num->size = setter->size;
  bigint_num->capacity = setter->size;
  bigint_num->sign = setter->sign;
  memcpy(bigint_num->data, setter->data, setter->size);

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_set_long(CmBigInt *bigint_num, long long setter) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  long long abs_num = _cm_long_abs(setter);

  bigint_num->sign = (setter < 0) ? '-' : '+';
  bigint_num->size = _cm_long_digit_count(abs_num);
  if (!_cm_ensure_capacity(bigint_num, bigint_num->size)) {
    return CM_ERR_ALLOC_FAILED;
  }

  for (size_t i = 0; i < bigint_num->size; ++i) {
    bigint_num->data[i] = (abs_num % 10) + '0';
    abs_num /= 10;
  }

  return CM_SUCCESS;
}

CmStatusCode cm_bigint_shrink_to_fit(CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (bigint_num->capacity > bigint_num->size) {
    void *new_buffer = realloc(bigint_num->data, bigint_num->size);
    if (!new_buffer) {
      return CM_ERR_ALLOC_FAILED;
    }

    bigint_num->data = new_buffer;
    bigint_num->capacity = bigint_num->size;
  }

  return CM_SUCCESS;
}

void cm_bigint_abs(CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  bigint_num->sign = '+';
}

void cm_bigint_negate(CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  if (cm_bigint_is_zero(bigint_num))
    return;

  bigint_num->sign = (bigint_num->sign == '+') ? '-' : '+';
}

bool cm_bigint_is_odd(const CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  return (bigint_num->data[0] - '0') & 0x1;
}

bool cm_bigint_is_even(const CmBigInt *bigint_num) {
  return !cm_bigint_is_odd(bigint_num);
}

char *cm_bigint_to_string(const CmBigInt *bigint_num) {

#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  bool is_negative = (bigint_num->sign == '-');

  size_t alloc_size = bigint_num->size + 1 + (is_negative ? 1 : 0);

  char *str = malloc(alloc_size);
  if (!str)
    return NULL;

  if (is_negative) {
    str[0] = '-';
  }

  size_t i = bigint_num->size;
  size_t j = 0;
  for (; i-- > 0;) {
    str[j++] = bigint_num->data[i];
  }

  str[j] = '\0';

  return str;
}

size_t cm_bigint_num_digits(const CmBigInt *bigint_num) {
#ifdef CM_DEBUG
  assert(!bigint_num && "Bigint num argument is NULL");
  assert(!bigint_num->data && "Bigint num argument data is NULL");
#endif

  return bigint_num->size;
}

void cm_bigint_free(CmBigInt *bigint_num) {
  free(bigint_num->data);
  free(bigint_num);
}
