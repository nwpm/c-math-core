include ./../common.mk

# === Targets ===
TARGET_LIB = $(LIBS_DIR)/libvec.a

# === Source files ===
VEC_SRCS = $(wildcard $(VEC_DIR)/*.c)

# === Object files ===
VEC_OBJS = $(patsubst $(VEC_DIR)/%.c, $(BUILD_DIR)/%.o, $(VEC_SRCS))

vec: $(TARGET_LIB)

$(TARGET_LIB) : $(VEC_OBJS)
	@mkdir -p $(LIBS_DIR)
	ar crs $@ $^

$(VEC_OBJS) : $(BUILD_DIR)/%.o : $(VEC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
