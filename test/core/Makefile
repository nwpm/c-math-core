# === Compiler ===
CC     = gcc
CFLAGS = -g -O0 -fsanitize=address -Wall -Wextra -pedantic -std=gnu99

# === Paths ===

PROJ_ROOT    = ../..
ALL_INCLUDES = $(PROJ_ROOT)/include/cm_core
LIB_DIR      = $(PROJ_ROOT)/lib/
BIN_DIR      = $(PROJ_ROOT)/bin
BUILD_DIR    = $(PROJ_ROOT)/build
TEST_MAT_DIR = ./matrix

CORE_LIB = $(LIB_DIR)/libcm_core.a

MAT_TEST_OBJ = $(BUILD_DIR)/test_matrix.o
MAT_TEST_BIN = $(BIN_DIR)/test_matrix
MAT_TEST_CREATE_SRC = $(TEST_MAT_DIR)/test_create.c

# === Targets ===

.PHONY: mtest

mtest: $(MAT_TEST_BIN)

# === Build rules ===

$(MAT_TEST_BIN): $(MAT_TEST_OBJ)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lcm_core

$(MAT_TEST_OBJ) : $(MAT_TEST_CREATE_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(ALL_INCLUDES) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@
