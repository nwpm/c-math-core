# === Compiler ===
CC     = gcc
CFLAGS = -g -O0 -fsanitize=address -Wall -Wextra -Wpedantic -std=c99

# === PATHS ===

PROJ_ROOT  = ./../..
LIB_DIR    = $(PROJ_ROOT)/lib
BUILD_DIR  = $(PROJ_ROOT)/build

MATRIX_DIR = matrix
MATRIX_SRC = $(MATRIX_DIR)/cm_mat.c

MATRIX_OBJ = $(BUILD_DIR)/cm_matrix.o
CORE_LIB = $(LIB_DIR)/libcm_core.a

ALL_INCLUDES = $(PROJ_ROOT)/include/cm_core

# === TARGETS ===

.PHONY: all clean install

all: $(CORE_LIB)

$(CORE_LIB): $(MATRIX_OBJ)
	ar rcs $@ $<

$(MATRIX_OBJ): $(MATRIX_SRC) $(LIB_DIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(ALL_INCLUDES)

$(LIB_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@
