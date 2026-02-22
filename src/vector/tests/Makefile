include ../../common.mk

# === Binary Targets ===
VEC2_TEST = $(BIN_DIR)/test_vec2
VEC3_TEST = $(BIN_DIR)/test_vec3

# === Source files ===
VEC2_TEST_SRC = ./test_vec2.c
VEC3_TEST_SRC = ./test_vec3.c

# === Object Files ===
VEC2_TEST_OBJ = $(BUILD_DIR)/test_vec2.o
VEC3_TEST_OBJ = $(BUILD_DIR)/test_vec3.o
VEC2_OBJ      = $(BUILD_DIR)/vec2.o
VEC3_OBJ      = $(BUILD_DIR)/vec3.o

all: vec2t vec3t

vec2t: $(VEC2_TEST)

vec3t: $(VEC3_TEST)

$(VEC2_TEST) : $(VEC2_TEST_OBJ) $(VEC2_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(VEC2_TEST_OBJ) : $(VEC2_TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(VEC3_TEST) : $(VEC3_TEST_OBJ) $(VEC3_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(VEC3_TEST_OBJ) : $(VEC3_TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@
