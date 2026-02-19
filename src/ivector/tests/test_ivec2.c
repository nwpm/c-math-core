#include "../../../include/cmathcore/ivector2.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Init tests
void test_init_stack_one_elem(int64_t a, int64_t b) {

  cm_ivec2_t v;
  cm_ivec2_init(&v, a, b);

  assert(a == cm_ivec2_get_x(v));
  assert(b == cm_ivec2_get_y(v));
  printf("Init stack one element: v(%ld, %ld) -> OK\n", a, b);
}

void test_init_stack_array(int64_t a, int64_t b, int64_t size) {

  cm_ivec2_t arr[size];
  for (int64_t i = 0; i < size; ++i) {
    cm_ivec2_init(arr + i, a + i, b + i);

    assert((a + i) == cm_ivec2_get_x(arr[i]));
    assert((b + i) == cm_ivec2_get_y(arr[i]));
  }
  printf("Init stack array size(%ld): v(%ld, %ld) -> OK\n", size, a, b);
}

void test_init_heap_one_elem(int64_t a, int64_t b) {

  cm_ivec2_t *v = malloc(sizeof(cm_ivec2_t));
  cm_ivec2_init(v, a, b);

  assert(a == cm_ivec2_get_x(*v));
  assert(b == cm_ivec2_get_y(*v));

  free(v);

  printf("Init heap one element: v(%ld, %ld) -> OK\n", a, b);
}

void test_init_heap_array(int64_t a, int64_t b, int64_t size) {

  cm_ivec2_t *arr = malloc(sizeof(cm_ivec2_t) * size);
  for (int64_t i = 0; i < size; ++i) {
    cm_ivec2_init(arr + i, a + i, b + i);

    assert((a + i) == cm_ivec2_get_x(arr[i]));
    assert((b + i) == cm_ivec2_get_y(arr[i]));
  }

  free(arr);
  printf("Init heap array size(%ld): v(%ld, %ld) -> OK\n", size, a, b);
}

void run_init_tests() {
  printf("********************Init Tests********************\n");
  test_init_stack_one_elem(10, 10);
  test_init_stack_array(1, 1, 100);
  test_init_heap_one_elem(20, 200);
  test_init_heap_array(10, 10, 1000);
  printf("Init tests: OK\n\n");
}

// Copy tests
void test_copy(int64_t a, int64_t b) {

  cm_ivec2_t src;
  cm_ivec2_t dest;
  cm_ivec2_init(&src, a, b);
  cm_ivec2_copy(src, &dest);

  assert(cm_ivec2_get_x(src) == cm_ivec2_get_x(dest));
  assert(cm_ivec2_get_y(src) == cm_ivec2_get_y(dest));

  printf("Copy: v(%ld, %ld) -> OK\n", a, b);
}

void run_copy_tests() {
  printf("********************Copy Tests********************\n");
  test_copy(100, 150);
  printf("Copy tests: OK\n\n");
}

// Fill tests
void test_fill(int64_t val) {

  cm_ivec2_t v;
  cm_ivec2_fill(&v, val);

  assert(cm_ivec2_get_x(v) == val);
  assert(cm_ivec2_get_y(v) == val);

  printf("Fill with value %ld -> OK\n", val);
}

void run_fill_tests() {
  printf("********************Fill Tests********************\n");
  test_fill(2);
  printf("Fill tests: OK\n\n");
}

// Set zero tests
void run_set_zero_tests() {

  printf("********************Zero Tests********************\n");

  cm_ivec2_t v;
  cm_ivec2_set_zero(&v);

  assert(cm_ivec2_get_x(v) == 0);
  assert(cm_ivec2_get_y(v) == 0);

  printf("Set zero tests: OK\n\n");
}

// Add tests
void test_add(int64_t a1, int64_t b1, int64_t a2, int64_t b2, int64_t ra,
              int64_t rb) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_t res;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  cm_ivec2_add(v1, v2, &res);

  assert(cm_ivec2_get_x(res) == ra);
  assert(cm_ivec2_get_y(res) == rb);

  printf("Add: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_add_tests() {
  printf("********************Add Tests********************\n");
  test_add(1, 1, 1, 1, 2, 2);
  test_add(340, 120, 60, 80, 400, 200);
  test_add(1000000, 3400000, 1500000, 600000, 2500000, 4000000);
  printf("Add tests: OK\n\n");
}

// Sub tests
void test_sub(int64_t a1, int64_t b1, int64_t a2, int64_t b2, int64_t ra,
              int64_t rb) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_t res;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  cm_ivec2_sub(v1, v2, &res);

  assert(cm_ivec2_get_x(res) == ra);
  assert(cm_ivec2_get_y(res) == rb);

  printf("Sub: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_sub_tests() {
  printf("********************Sub Tests********************\n");
  test_sub(1, 1, 1, 1, 0, 0);
  test_sub(340, 120, 60, 80, 280, 40);
  test_sub(1000000, 3400000, 1500000, 600000, -500000, 2800000);
  printf("Sub tests: OK\n\n");
}

// Scale tests
void test_scale(int64_t a, int64_t b, int64_t s, int64_t ra, int64_t rb) {

  cm_ivec2_t v;
  cm_ivec2_t res;
  cm_ivec2_init(&v, a, b);

  cm_ivec2_scale(v, s, &res);

  assert(cm_ivec2_get_x(res) == ra);
  assert(cm_ivec2_get_y(res) == rb);

  printf("Scale with %ld: v(%ld, %ld) -> OK\n", s, a, b);
}

void run_scale_tests() {
  printf("********************Scale Tests********************\n");
  test_scale(1, 1, 10, 10, 10);
  test_scale(100, 100, 10, 1000, 1000);
  test_scale(-100, -100, -1, 100, 100);
  printf("Scale tests: OK\n\n");
}

// Abs tests
void test_abs(int64_t a, int64_t b, int64_t ra, int64_t rb) {

  cm_ivec2_t v;
  cm_ivec2_t res;
  cm_ivec2_init(&v, a, b);

  cm_ivec2_abs(v, &res);

  assert(res.x == ra);
  assert(res.y == rb);

  printf("Abs: v(%ld, %ld) -> OK\n", a, b);
}

void run_abs_tests() {
  printf("********************Abs Tests********************\n");
  test_abs(1, 1, 1, 1);
  test_abs(0, 0, 0, 0);
  test_abs(-1, 1, 1, 1);
  test_abs(-1, -1, 1, 1);
  test_abs(INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN);
  test_abs(INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX);
  printf("Abs tests: OK\n\n");
}

// Add inplace tests
void test_add_inplace(int64_t a1, int64_t b1, int64_t a2, int64_t b2,
                      int64_t ra, int64_t rb) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  cm_ivec2_add_inplace(&v1, v2);

  assert(cm_ivec2_get_x(v1) == ra);
  assert(cm_ivec2_get_y(v1) == rb);

  printf("Add inplace: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_add_inplace_tests() {
  printf("********************Add Inplace Tests********************\n");
  test_add_inplace(1, 1, 1, 1, 2, 2);
  test_add_inplace(340, 120, 60, 80, 400, 200);
  test_add_inplace(1000000, 3400000, 1500000, 600000, 2500000, 4000000);
  printf("Add inplace tests: OK\n\n");
}

// Sub inplace tests
void test_sub_inplace(int64_t a1, int64_t b1, int64_t a2, int64_t b2,
                      int64_t ra, int64_t rb) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  cm_ivec2_sub_inplace(&v1, v2);

  assert(cm_ivec2_get_x(v1) == ra);
  assert(cm_ivec2_get_y(v1) == rb);

  printf("Sub inplace: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_sub_inplace_tests() {
  printf("********************Sub Inplace Tests********************\n");
  test_sub_inplace(1, 1, 1, 1, 0, 0);
  test_sub_inplace(340, 120, 60, 80, 280, 40);
  test_sub_inplace(1000000, 3400000, 1500000, 600000, -500000, 2800000);
  printf("Sub inplace tests: OK\n\n");
}

// Scale inplace tests
void test_scale_inplace(int64_t a, int64_t b, int64_t s, int64_t ra,
                        int64_t rb) {

  cm_ivec2_t v;
  cm_ivec2_init(&v, a, b);

  cm_ivec2_scale_inplace(&v, s);

  assert(cm_ivec2_get_x(v) == ra);
  assert(cm_ivec2_get_y(v) == rb);

  printf("Scale inplace with %ld: v(%ld, %ld) -> OK\n", s, a, b);
}

void run_scale_inplace_tests() {
  printf("********************Scale Inplace Tests********************\n");
  test_scale_inplace(1, 1, 10, 10, 10);
  test_scale_inplace(100, 100, 10, 1000, 1000);
  test_scale_inplace(-100, -100, -1, 100, 100);
  printf("Scale inplace tests: OK\n\n");
}

// Abs inplace tests
void test_abs_inplace(int64_t a, int64_t b, int64_t ra, int64_t rb) {

  cm_ivec2_t v;
  cm_ivec2_init(&v, a, b);

  cm_ivec2_abs_inplace(&v);

  assert(v.x == ra);
  assert(v.y == rb);

  printf("Abs inplace: v(%ld, %ld) -> OK\n", a, b);
}

void run_abs_inplace_tests() {
  printf("********************Abs Inplace Tests********************\n");
  test_abs_inplace(1, 1, 1, 1);
  test_abs_inplace(0, 0, 0, 0);
  test_abs_inplace(-1, 1, 1, 1);
  test_abs_inplace(-1, -1, 1, 1);
  test_abs_inplace(INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN);
  test_abs_inplace(INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX);
  printf("Abs inplace tests: OK\n\n");
}

// Dot tests
void test_dot(int64_t a1, int64_t b1, int64_t a2, int64_t b2, int64_t res) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  int64_t dot = cm_ivec2_dot(v1, v2);
  assert(res == dot);
  printf("Dot: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_dot_tests() {
  printf("********************Dot Tests********************\n");
  test_dot(1, 1, 2, 2, 4);
  test_dot(0, 1, 2, 2, 2);
  test_dot(0, 0, 2, 2, 0);
  test_dot(-1, -1, 2, 2, -4);
  printf("Dot tests: OK\n\n");
}

// Cross tests
void test_cross(int64_t a1, int64_t b1, int64_t a2, int64_t b2, int64_t res) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  int64_t cross = cm_ivec2_cross(v1, v2);
  assert(res == cross);
  printf("Cross: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_cross_tests() {
  printf("********************Cross Tests********************\n");
  test_cross(1, 1, 2, 2, 0);
  test_cross(0, 1, 2, 2, -2);
  test_cross(-3, 4, -2, 2, 2);
  test_cross(1, 1, -2, 2, 4);
  printf("Cross tests: OK\n\n");
}

// Dist squared
void test_dist_squared(int64_t a1, int64_t b1, int64_t a2, int64_t b2,
                       int64_t res) {

  cm_ivec2_t v1;
  cm_ivec2_t v2;
  cm_ivec2_init(&v1, a1, b1);
  cm_ivec2_init(&v2, a2, b2);

  int64_t dist = cm_ivec2_dist_squared(v1, v2);
  assert(res == dist);
  printf("Dist: v1(%ld, %ld), v2(%ld, %ld) -> OK\n", a1, b1, a2, b2);
}

void run_dist_tests() {
  printf("********************Dist Tests********************\n");
  test_dist_squared(1, 1, 2, 2, 2);
  test_dist_squared(0, 1, 2, 2, 5);
  test_dist_squared(-3, 4, -2, 2, 5);
  test_dist_squared(1, 1, -2, 2, 10);
  printf("Dist tests: OK\n\n");
}

int main() {
  run_init_tests();
  run_copy_tests();
  run_fill_tests();
  run_set_zero_tests();
  run_add_tests();
  run_sub_tests();
  run_scale_tests();
  run_abs_tests();
  run_add_inplace_tests();
  run_sub_inplace_tests();
  run_scale_inplace_tests();
  run_abs_inplace_tests();
  run_dot_tests();
  run_cross_tests();
  run_dist_tests();
  return 0;
}
