include ../../common.mk

# === Include Libs ===
INCLUDE_LIBS   := -L$(LIBS_DIR) -livec -lm -lcriterion

# === Source files ===
IVEC_TEST_SRCS := $(wildcard $(IVEC_TEST_DIR)/*.c)

# === Object Files ===
IVEC_TEST_OBJS := $(patsubst $(IVEC_TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(IVEC_TEST_SRCS))

# === Binary Targets ===
IVEC_TEST_BINS := $(patsubst $(IVEC_TEST_DIR)/%.c, $(BIN_DIR)/%, $(IVEC_TEST_SRCS))

ivect: $(IVEC_TEST_OBJS) $(IVEC_TEST_BINS)

$(IVEC_TEST_BINS) : $(BIN_DIR)/% : $(BUILD_DIR)/%.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE_LIBS)

$(IVEC_TEST_OBJS) : $(BUILD_DIR)/%.o : $(IVEC_TEST_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
