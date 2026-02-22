include ./../common.mk

# === Targets ===
TARGET_LIB = $(LIBS_DIR)/libmat.a

# === Source files ===
MAT_SRC = ./matrix.c

# === Object files ===
MAT_OBJ = $(BUILD_DIR)/matrix.o

mat: $(TARGET_LIB)

$(TARGET_LIB) : $(MAT_OBJ)
	ar crs $@ $^

$(MAT_OBJ) : $(MAT_SRC)
	$(CC) $(CFLAGS) -c $< -o $@
