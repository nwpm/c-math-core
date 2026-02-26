include ./../common.mk

# === Targets ===
TARGET_LIB = $(LIBS_DIR)/libivec.a

# === Source files ===
IVEC2_SRC = ./ivec2.c
IVEC3_SRC = ./ivec3.c

# === Object files ===
IVEC2_OBJ = $(BUILD_DIR)/ivec2.o
IVEC3_OBJ = $(BUILD_DIR)/ivec3.o

ivec: $(TARGET_LIB)

$(TARGET_LIB) : $(IVEC2_OBJ) $(IVEC3_OBJ) | $(LIBS_DIR)
	ar crs $@ $^

$(IVEC2_OBJ) : $(IVEC2_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(IVEC3_OBJ) : $(IVEC3_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(LIBS_DIR):
	mkdir -p $@
