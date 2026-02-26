include ./../common.mk

# === Targets ===
TARGET_LIB = $(LIBS_DIR)/libvec.a

# === Source files ===
VEC2_SRC = ./vec2.c
VEC3_SRC = ./vec3.c

# === Object files ===
VEC2_OBJ = $(BUILD_DIR)/vec2.o
VEC3_OBJ = $(BUILD_DIR)/vec3.o

vec: $(TARGET_LIB)

$(TARGET_LIB) : $(VEC2_OBJ) $(VEC3_OBJ) | $(LIBS_DIR)
	ar crs $@ $^

$(VEC2_OBJ) : $(VEC2_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(VEC3_OBJ) : $(VEC3_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(LIBS_DIR):
	mkdir -p $@
