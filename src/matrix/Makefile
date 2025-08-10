# === Compiler ===
CC     = gcc
CFLAGS = -DDEBUG -g -Wall -Wextra -O0 -fsanitize=address

# === Paths ===

BUILD_DIR  = ../../build/matrix

MATRIX_SRC     = cm_matrix_int.c
MATRIX_OBJ     = $(BUILD_DIR)/libmatrix.o
MATRIX_TARGET  = $(BUILD_DIR)/libmatrix.a

# ===Targets===
.PHONY: matrix install uninstall clean

matrix: $(MATRIX_TARGET) 

install:

uninstall:

clean :
	rm -rf $(BUILD_DIR)/*

# ===Build rules===

$(MATRIX_TARGET) : $(MATRIX_OBJ)
	ar rcs $@ $<
	rm $(MATRIX_OBJ)

$(MATRIX_OBJ) : $(MATRIX_SRC) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@
