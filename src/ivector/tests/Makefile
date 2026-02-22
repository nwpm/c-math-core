include ../../common.mk

# === Binary Targets ===
IVEC2_TEST = $(BIN_DIR)/test_ivec2
IVEC3_TEST = $(BIN_DIR)/test_ivec3

# === Source files ===
IVEC2_TEST_SRC = ./test_ivec2.c
IVEC3_TEST_SRC = ./test_ivec3.c

# === Object Files ===
IVEC2_TEST_OBJ = $(BUILD_DIR)/test_ivec2.o
IVEC3_TEST_OBJ = $(BUILD_DIR)/test_ivec3.o
IVEC2_OBJ      = $(BUILD_DIR)/ivec2.o
IVEC3_OBJ      = $(BUILD_DIR)/ivec3.o

all: ivec2t ivec3t

ivec2t: $(IVEC2_TEST)

ivec3t: $(IVEC3_TEST)

$(IVEC2_TEST) : $(IVEC2_TEST_OBJ) $(IVEC2_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(IVEC2_TEST_OBJ) : $(IVEC2_TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(IVEC3_TEST) : $(IVEC3_TEST_OBJ) $(IVEC3_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(IVEC3_TEST_OBJ) : $(IVEC3_TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

