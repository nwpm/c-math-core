# === Compiler ===
CC     = gcc
CFLAGS = -g -O0 -fsanitize=address -Wall -Wextra -Wpedantic -std=c99

# === PATHS ===

PROJ_ROOT  = ./../..
LIB_DIR    = $(PROJ_ROOT)/lib

MATRIX_DIR = matrix
MATRIX_SRC = $(MATRIX_DIR)/cm_mat.c

MATRIX_OBJ = cm_matrix.o
CORE_LIB = $(LIB_DIR)/lib_cm_core.a

ALL_INCLUDES = $(PROJ_ROOT)/include/cm_core
INTERNAL_MATRIX = $(MATRIX_DIR)/cm_mat_internal.h

# === TARGETS ===

.PHONY: all clean install

all: $(CORE_LIB)

$(CORE_LIB): $(MATRIX_OBJ)
	ar rcs $@ $<

$(MATRIX_OBJ): $(MATRIX_SRC) $(LIB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(ALL_INCLUDES) -I$(MATRIX_DIR)

$(LIB_DIR):
	mkdir -p $@
