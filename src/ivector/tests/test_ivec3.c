#include "../../../include/cmathcore/ivector3.h"
#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Init tests
void test_init_stack_one_elem(int64_t a, int64_t b, int64_t c) {

  cm_ivec3_t v;
  cm_ivec3_init(&v, a, b, c);

  assert(a == cm_ivec3_get_x(v));
  assert(b == cm_ivec3_get_y(v));
  assert(c == cm_ivec3_get_z(v));

  printf("Init stack one element: v(%ld, %ld, %ld) -> OK\n", a, b, c);
}

void test_init_stack_array(int64_t a, int64_t b, int64_t c, int64_t size) {

  cm_ivec3_t arr[size];
  for (int64_t i = 0; i < size; ++i) {
    cm_ivec3_init(arr + i, a + i, b + i, c + i);

    assert((a + i) == cm_ivec3_get_x(arr[i]));
    assert((b + i) == cm_ivec3_get_y(arr[i]));
    assert((c + i) == cm_ivec3_get_z(arr[i]));
  }
  printf("Init stack array size(%ld): v(%ld, %ld, %ld) -> OK\n", size, a, b, c);
}

void test_init_heap_one_elem(int64_t a, int64_t b, int64_t c) {

  cm_ivec3_t *v = malloc(sizeof(cm_ivec3_t));
  cm_ivec3_init(v, a, b, c);

  assert(a == cm_ivec3_get_x(*v));
  assert(b == cm_ivec3_get_y(*v));
  assert(c == cm_ivec3_get_z(*v));

  free(v);

  printf("Init heap one element: v(%ld, %ld, %ld) -> OK\n", a, b, c);
}

void test_init_heap_array(int64_t a, int64_t b, int64_t c, int64_t size) {

  cm_ivec3_t *arr = malloc(sizeof(cm_ivec3_t) * size);
  for (int64_t i = 0; i < size; ++i) {
    cm_ivec3_init(arr + i, a + i, b + i, c + i);

    assert((a + i) == cm_ivec3_get_x(arr[i]));
    assert((b + i) == cm_ivec3_get_y(arr[i]));
    assert((c + i) == cm_ivec3_get_z(arr[i]));
  }

  free(arr);
  printf("Init heap array size(%ld): v(%ld, %ld, %ld) -> OK\n", size, a, b, c);
}

void run_init_tests() {
  printf("********************Init Tests********************\n");
  test_init_stack_one_elem(10, 10, 10);
  test_init_stack_array(1, 1, 1, 100);
  test_init_heap_one_elem(30, 300, 30);
  test_init_heap_array(10, 10, 10, 1000);
  printf("Init tests: OK\n\n");
}

// Copy tests
void test_copy(int64_t a, int64_t b, int64_t c) {

  cm_ivec3_t src;
  cm_ivec3_t dest;
  cm_ivec3_init(&src, a, b, c);
  cm_ivec3_copy(src, &dest);

  assert(cm_ivec3_get_x(src) == cm_ivec3_get_x(dest));
  assert(cm_ivec3_get_y(src) == cm_ivec3_get_y(dest));
  assert(cm_ivec3_get_z(src) == cm_ivec3_get_z(dest));

  printf("Copy: v(%ld, %ld, %ld) -> OK\n", a, b, c);
}

void run_copy_tests() {
  printf("********************Copy Tests********************\n");
  test_copy(100, 150, 100);
  printf("Copy tests: OK\n\n");
}

// Fill tests
void test_fill(int64_t val) {

  cm_ivec3_t v;
  cm_ivec3_fill(&v, val);

  assert(cm_ivec3_get_x(v) == val);
  assert(cm_ivec3_get_y(v) == val);
  assert(cm_ivec3_get_z(v) == val);

  printf("Fill with value %ld -> OK\n", val);
}

void run_fill_tests() {
  printf("********************Fill Tests********************\n");
  test_fill(3);
  printf("Fill tests: OK\n\n");
}

// Set zero tests
void run_set_zero_tests() {

  printf("********************Zero Tests********************\n");

  cm_ivec3_t v;
  cm_ivec3_set_zero(&v);

  assert(cm_ivec3_get_x(v) == 0);
  assert(cm_ivec3_get_y(v) == 0);
  assert(cm_ivec3_get_z(v) == 0);

  printf("Set zero tests: OK\n\n");
}

// Add tests
void test_add(int64_t a1, int64_t b1, int64_t c1, int64_t a2, int64_t b2,
              int64_t c2, int64_t ra, int64_t rb, int64_t rc) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_t res;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  cm_ivec3_add(v1, v2, &res);

  assert(cm_ivec3_get_x(res) == ra);
  assert(cm_ivec3_get_y(res) == rb);
  assert(cm_ivec3_get_z(res) == rc);

  printf("Add: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1, c1, a2,
         b2, c2);
}

void run_add_tests() {
  printf("********************Add Tests********************\n");
  test_add(1, 1, 1, 1, 1, 1, 2, 2, 2);
  test_add(340, 120, 350, 60, 80, 50, 400, 200, 400);
  test_add(1000000, 3400000, 2000000, 1500000, 600000, 2000000, 2500000,
           4000000, 4000000);
  printf("Add tests: OK\n\n");
}

// Sub tests
void test_sub(int64_t a1, int64_t b1, int64_t c1, int64_t a2, int64_t b2,
              int64_t c2, int64_t ra, int64_t rb, int64_t rc) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_t res;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  cm_ivec3_sub(v1, v2, &res);

  assert(cm_ivec3_get_x(res) == ra);
  assert(cm_ivec3_get_y(res) == rb);
  assert(cm_ivec3_get_z(res) == rc);

  printf("Sub: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1, c1, a2,
         b2, c2);
}

void run_sub_tests() {
  printf("********************Sub Tests********************\n");
  test_sub(1, 1, 1, 1, 1, 1, 0, 0, 0);
  test_sub(340, 120, 40, 60, 80, 80, 280, 40, -40);
  test_sub(1000000, 3400000, 700000, 1500000, 600000, 700000, -500000, 2800000,
           0);
  printf("Sub tests: OK\n\n");
}

// Scale tests
void test_scale(int64_t a, int64_t b, int64_t c, int64_t s, int64_t ra,
                int64_t rb, int64_t rc) {

  cm_ivec3_t v;
  cm_ivec3_t res;
  cm_ivec3_init(&v, a, b, c);

  cm_ivec3_scale(v, s, &res);

  assert(cm_ivec3_get_x(res) == ra);
  assert(cm_ivec3_get_y(res) == rb);
  assert(cm_ivec3_get_z(res) == rc);

  printf("Scale with %ld: v(%ld, %ld, %ld) -> OK\n", s, a, b, c);
}

void run_scale_tests() {
  printf("********************Scale Tests********************\n");
  test_scale(1, 1, 1, 10, 10, 10, 10);
  test_scale(100, 100, 100, 10, 1000, 1000, 1000);
  test_scale(-100, -100, -100, -1, 100, 100, 100);
  printf("Scale tests: OK\n\n");
}

// Abs tests
void test_abs(int64_t a, int64_t b, int64_t c, int64_t ra, int64_t rb,
              int64_t rc) {

  cm_ivec3_t v;
  cm_ivec3_t res;
  cm_ivec3_init(&v, a, b, c);

  cm_ivec3_abs(v, &res);

  assert(cm_ivec3_get_x(res) == ra);
  assert(cm_ivec3_get_y(res) == rb);
  assert(cm_ivec3_get_z(res) == rc);

  printf("Abs: v(%ld, %ld, %ld) -> OK\n", a, b, c);
}

void run_abs_tests() {
  printf("********************Abs Tests********************\n");
  test_abs(1, 1, 1, 1, 1, 1);
  test_abs(0, 0, 0, 0, 0, 0);
  test_abs(-1, 1, -1, 1, 1, 1);
  test_abs(-1, -1, 1, 1, 1, 1);
  test_abs(INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN);
  test_abs(INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX);
  printf("Abs tests: OK\n\n");
}

// Add inplace tests
void test_add_inplace(int64_t a1, int64_t b1, int64_t c1, int64_t a2,
                      int64_t b2, int64_t c2, int64_t ra, int64_t rb,
                      int64_t rc) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  cm_ivec3_add_inplace(&v1, v2);

  assert(cm_ivec3_get_x(v1) == ra);
  assert(cm_ivec3_get_y(v1) == rb);
  assert(cm_ivec3_get_z(v1) == rc);

  printf("Add inplace: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1,
         c1, a2, b2, c2);
}

void run_add_inplace_tests() {
  printf("********************Add Inplace Tests********************\n");
  test_add_inplace(1, 1, 1, 1, 1, 1, 2, 2, 2);
  test_add_inplace(340, 120, 400, 60, 80, 50, 400, 200, 450);
  test_add_inplace(1000000, 3400000, 200000, 1500000, 600000, -200000, 2500000,
                   4000000, 0);
  printf("Add inplace tests: OK\n\n");
}

// Sub inplace tests
void test_sub_inplace(int64_t a1, int64_t b1, int64_t c1, int64_t a2,
                      int64_t b2, int64_t c2, int64_t ra, int64_t rb,
                      int64_t rc) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  cm_ivec3_sub_inplace(&v1, v2);

  assert(cm_ivec3_get_x(v1) == ra);
  assert(cm_ivec3_get_y(v1) == rb);
  assert(cm_ivec3_get_z(v1) == rc);

  printf("Sub inplace: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1,
         c1, a2, b2, c2);
}

void run_sub_inplace_tests() {
  printf("********************Sub Inplace Tests********************\n");
  test_sub_inplace(1, 1, 1, 1, 1, 1, 0, 0, 0);
  test_sub_inplace(340, 120, 30, 60, 80, 90, 280, 40, -60);
  test_sub_inplace(1000000, 3400000, 450000, 1500000, 600000, 50000, -500000,
                   2800000, 400000);
  printf("Sub inplace tests: OK\n\n");
}

// Scale inplace tests
void test_scale_inplace(int64_t a, int64_t b, int64_t c, int64_t s, int64_t ra,
                        int64_t rb, int64_t rc) {

  cm_ivec3_t v;
  cm_ivec3_init(&v, a, b, c);

  cm_ivec3_scale_inplace(&v, s);

  assert(cm_ivec3_get_x(v) == ra);
  assert(cm_ivec3_get_y(v) == rb);
  assert(cm_ivec3_get_z(v) == rc);

  printf("Scale inplace with %ld: v(%ld, %ld, %ld) -> OK\n", s, a, b, c);
}

void run_scale_inplace_tests() {
  printf("********************Scale Inplace Tests********************\n");
  test_scale_inplace(1, 1, 1, 10, 10, 10, 10);
  test_scale_inplace(100, 100, 100, 10, 1000, 1000, 1000);
  test_scale_inplace(-100, -100, -100, -1, 100, 100, 100);
  printf("Scale inplace tests: OK\n\n");
}

// Abs inplace tests
void test_abs_inplace(int64_t a, int64_t b, int64_t c, int64_t ra, int64_t rb,
                      int64_t rc) {

  cm_ivec3_t v;
  cm_ivec3_init(&v, a, b, c);

  cm_ivec3_abs_inplace(&v);

  assert(cm_ivec3_get_x(v) == ra);
  assert(cm_ivec3_get_y(v) == rb);
  assert(cm_ivec3_get_z(v) == rc);

  printf("Abs inplace: v(%ld, %ld, %ld) -> OK\n", a, b, c);
}

void run_abs_inplace_tests() {
  printf("********************Abs Inplace Tests********************\n");
  test_abs_inplace(1, 1, 1, 1, 1, 1);
  test_abs_inplace(0, 0, 0, 0, 0, 0);
  test_abs_inplace(-1, 1, -1, 1, 1, 1);
  test_abs_inplace(-1, -1, 1, 1, 1, 1);
  test_abs_inplace(INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN, INT64_MIN,
                   INT64_MIN);
  test_abs_inplace(INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX, INT64_MAX,
                   INT64_MAX);
  printf("Abs inplace tests: OK\n\n");
}

// Dot tests
void test_dot(int64_t a1, int64_t b1, int64_t c1, int64_t a2, int64_t b2,
              int64_t c2, int64_t res) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  int64_t dot = cm_ivec3_dot(v1, v2);
  assert(res == dot);
  printf("Dot: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1, c1, a2,
         b2, c2);
}

void run_dot_tests() {
  printf("********************Dot Tests********************\n");
  test_dot(1, 1, 1, 3, 3, 3, 9);
  test_dot(0, 1, 3, 1, 3, 3, 12);
  test_dot(0, 0, 0, 3, 3, 3, 0);
  test_dot(-1, -1, 4, 3, 3, 3, 6);
  printf("Dot tests: OK\n\n");
}

// Cross tests
void test_cross(int64_t a1, int64_t b1, int64_t c1, int64_t a2, int64_t b2,
                int64_t c2, int64_t ra, int64_t rb, int64_t rc) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_t cross;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  cm_ivec3_cross(v1, v2, &cross);

  assert(cm_ivec3_get_x(cross) == ra);
  assert(cm_ivec3_get_y(cross) == rb);
  assert(cm_ivec3_get_z(cross) == rc);

  printf("Cross: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1, c1, a2,
         b2, c2);
}

void run_cross_tests() {
  printf("********************Cross Tests********************\n");
  test_cross(1, 1, 1, 3, 3, 3, 0, 0, 0);
  test_cross(0, 1, 3, 1, 3, 3, -6, 3, -1);
  test_cross(0, 0, 0, 3, -3, 3, 0, 0, 0);
  test_cross(1, 1, -3, 3, 4, 2, 14, -11, 1);
  printf("Cross tests: OK\n\n");
}

// Dist squared
void test_dist_squared(int64_t a1, int64_t b1, int64_t c1, int64_t a2,
                       int64_t b2, int64_t c2, int64_t res) {

  cm_ivec3_t v1;
  cm_ivec3_t v2;
  cm_ivec3_init(&v1, a1, b1, c1);
  cm_ivec3_init(&v2, a2, b2, c2);

  int64_t dist = cm_ivec3_dist_squared(v1, v2);
  assert(res == dist);
  printf("Dist: v1(%ld, %ld, %ld), v2(%ld, %ld, %ld) -> OK\n", a1, b1, c1, a2,
         b2, c2);
}

void run_dist_tests() {
  printf("********************Dist Tests********************\n");
  test_dist_squared(1, 3, 2, 0, 5, 4, 9);
  test_dist_squared(0, 0, 0, 0, 0, 0, 0);
  test_dist_squared(-3, -1, -3, 2, 4, 2, 75);
  test_dist_squared(4, 4, 4, 4, 4, 4, 0);
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
  printf("\nAll tests passed.\n");
  return 0;
}
