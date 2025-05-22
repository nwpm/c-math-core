# === Project Info===
PROJECT_NAME = cmcore

# === Paths ===

SRC_DIR     = src
INCLUDE_DIR = include
TEST_DIR    = tests

SRC_ALG = $(SRC_DIR)/algebra/mc_algebra.c
INC_ALG = $(INCLUDE_DIR)/algebra

# === Compiler ===
CC     = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11

DEBUG_CFLAGS   = -g -O0 -fsanitize=address
RELEASE_CFLAGS = -O2

# === Build Type ===
BUILD_TYPE ?= debug

ifeq ($(BUILD_TYPE), debug)
	CFLAGS    += $(DEBUG_FLAGS)
	BUILD_PATH = bin/debug
else ifeq ($(BUILD_TYPE), release)
	CLAGSS    += $(RELEASE_CFLAGS)
	BUILD_PATH = bin/release
else
	$(error Unknown build type: $(BUILD_TYPE))
endif

ALG_DIR    = $(BUILD_PATH)/algebra
ALG_OBJ    = $(ALG_DIR)/lib$(PROJECT_NAME)_alg.o
ALG_TARGET = $(ALG_DIR)/lib$(PROJECT_NAME)_alg.a

SRC_TEST = $(TEST_DIR)/test_bin.c
TEST_OBJ = $(BUILD_PATH)/lib$(PROJECT_NAME)_test.o
TEST_BIN = $(BUILD_PATH)/lib$(PROJECT_NAME)_test

# === Targets ===
.PHONY: debug test clean

alg: $(ALG_TARGET)

test: $(TEST_BIN)

debug:
	$(MAKE) BUILD_TYPE=debug

clean:
	rm -rf $(BUILD_PATH)/*

# === Build Rules ===

# === Test Binary ===
$(TEST_BIN): $(TEST_OBJ) $(ALG_TARGET) | $(BUILD_PATH)
	$(CC) $(CFLAGS) $^ -o $@
	rm $(TEST_OBJ)

$(TEST_OBJ) : $(SRC_TEST) | $(BUILD_PATH)
	$(CC) $(CFLAGS) -I$(INC_ALG) -c $< -o $@

# ===Build Algebra===
$(ALG_TARGET): $(ALG_OBJ) | $(ALG_DIR)
	ar rcs $@ $^

$(ALG_OBJ): $(SRC_ALG) $(BUILD_PATH) $(ALG_DIR) | $(ALG_DIR)
	$(CC) $(CFLAGS) -I$(INC_ALG) -c $< -o $@

$(ALG_DIR):
	mkdir -p $@

$(BUILD_PATH):
	mkdir -p $@











