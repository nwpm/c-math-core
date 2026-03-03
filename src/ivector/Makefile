include ./../common.mk

# === Targets ===
TARGET_LIB = $(LIBS_DIR)/libivec.a

# === Source files ===
IVEC_SRCS = $(wildcard $(IVEC_DIR)/*.c)

# === Object files ===
IVEC_OBJS = $(patsubst $(IVEC_DIR)/%.c, $(BUILD_DIR)/%.o, $(IVEC_SRCS))

ivec: $(TARGET_LIB)

$(TARGET_LIB) : $(IVEC_OBJS)
	@mkdir -p $(LIBS_DIR)
	ar crs $@ $^

$(IVEC_OBJS) : $(BUILD_DIR)/%.o : $(IVEC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
