include ./../common.mk

# === Targets ===
TARGET_LIB = $(LIBS_DIR)/libbint.a

# === Source files ===
BIGINT_SRC = ./bigint.c

# === Object files ===
BIGINT_OBJ = $(BUILD_DIR)/bint.o

bint: $(TARGET_LIB)

$(TARGET_LIB) : $(BIGINT_OBJ) | $(LIBS_DIR)
	ar crs $@ $^

$(BIGINT_OBJ) : $(BIGINT_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(LIBS_DIR):
	mkdir -p $@
