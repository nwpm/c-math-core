# === Compiler ===
CC     = gcc
CFLAGS = -g -O0 -fsanitize=address -Wall -Wextra -pedantic -std=gnu99

# === Paths ===

PROJ_ROOT    = ../..
ALL_INCLUDES = $(PROJ_ROOT)/include/cm_core
LIB_DIR      = $(PROJ_ROOT)/lib
BIN_DIR      = $(PROJ_ROOT)/bin
BUILD_DIR    = $(PROJ_ROOT)/build
TEST_MAT_DIR = ./matrix

CORE_LIB = $(LIB_DIR)/libcm_core.a

MAT_TEST_OBJ = $(BUILD_DIR)/test_matrix.o
MAT_TEST_BIN = $(BIN_DIR)/test_matrix
MAT_TEST_CREATE_SRC = $(TEST_MAT_DIR)/test_create.c

# === Unity ===

UNITY_DIR = ../Unity
UNITY_SRC = ../Unity/src

UNITY_OBJ = $(BUILD_DIR)/unity.o
UNITY_LIB = $(LIB_DIR)/libunity.a

# === Targets ===

.PHONY: tests

tests: $(UNITY_LIB) $(MAT_TEST_BIN)

# === Build rules ===

$(MAT_TEST_BIN): $(MAT_TEST_OBJ)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lcm_core -lunity

$(MAT_TEST_OBJ) : $(MAT_TEST_CREATE_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(ALL_INCLUDES) -c $< -o $@

$(UNITY_LIB): $(UNITY_OBJ)
	ar rcs $@ $<

$(UNITY_OBJ): $(UNITY_SRC)/unity.c $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(UNITY_SRC)

$(BIN_DIR):
	mkdir -p $@

$(LIB_DIR):
	mkdir -p $@
