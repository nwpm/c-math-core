# === Compiler ===
CC     = gcc
CFLAGS = -g -O0 -fsanitize=address -Wall -Wextra -pedantic -std=gnu99

# === Paths ===

INCLUDE     = ../../src/matrix
BIN_DIR     = ../../bin/matrix
BUILD_DIR   = ../../build
LIB_DIR     = $(BUILD_DIR)/matrix

LIB         = $(LIB_DIR)/libvector.a

TEST_SRC = test_matrix.c
TEST_OBJ = test_matrix.o

TEST_BIN = $(BIN_DIR)/test_matrix

# === Targets ===

.PHONY: mtest

mtest: $(TEST_BIN)

# === Build rules ===

$(TEST_BIN): $(TEST_OBJ)
	$(CC) $(CFLAGS) $< -o $@ -L$(LIB_DIR) -lmatrix
	rm $(TEST_OBJ)

$(TEST_OBJ) : $(TEST_SRC) $(BIN_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@
