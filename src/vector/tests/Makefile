include ../../common.mk

# === Include Libs ===
INCLUDE_LIBS   := -L$(LIBS_DIR) -lvec -lm -lcriterion

# === Source files ===
VEC_TEST_SRCS := $(wildcard $(VEC_TEST_DIR)/test_*.c)

# === Object Files ===
VEC_TEST_OBJS := $(patsubst $(VEC_TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(VEC_TEST_SRCS))

# TODO: replace hardcoded objs
VEC2_OBJ       := $(BUILD_DIR)/vec2.o
VEC3_OBJ       := $(BUILD_DIR)/vec3.o

# === Binary Targets ===
VEC_TEST_BINS = $(patsubst $(VEC_TEST_DIR)%.c, $(BIN_DIR)/%, $(VEC_TEST_SRCS))

all: vec2t

vec2t: $(VEC_TEST_OBJS) $(VEC_TEST_BINS)

$(VEC_TEST_BINS) : $(BIN_DIR)/% : $(BUILD_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE_LIBS)

$(VEC_TEST_OBJS) : $(BUILD_DIR)/%.o : $(VEC_TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
