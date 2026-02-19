include ../../common.mk

# === Binary Targets ===
IVEC2_TEST = $(BIN_DIR)/test_ivec2

# === Source files ===
IVEC2_TEST_SRC = ./test_ivec2.c

# === Object Files ===
IVEC2_TEST_OBJ = $(BUILD_DIR)/test_ivec2.o
IVEC2_OBJ      = $(BUILD_DIR)/ivec2.o

ivec2t: $(IVEC2_TEST)

$(IVEC2_TEST) : $(IVEC2_TEST_OBJ) $(IVEC2_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(IVEC2_TEST_OBJ) : $(IVEC2_TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@
