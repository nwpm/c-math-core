# === Directories ===
ROOT_DIR    := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
BUILD_DIR   := $(ROOT_DIR)/build
TESTS_DIR   := $(ROOT_DIR)/test
LIBS_DIR    := $(BUILD_DIR)/lib
BIN_DIR     := $(BUILD_DIR)/bin
SRC_DIR     := $(ROOT_DIR)/src

export ROOT_DIR
export BUILD_DIR
export LIBS_DIR
export BIN_DIR

IVEC_DIR      = $(SRC_DIR)/ivector
IVEC_TEST_DIR = $(IVEC_DIR)/tests

VEC_DIR      = $(SRC_DIR)/vector
VEC_TEST_DIR = $(VEC_DIR)/tests

MAT_DIR      = $(SRC_DIR)/matrix
MAT_TEST_DIR = $(MAT_DIR)/tests

BIGINT_DIR      = $(SRC_DIR)/bigint
BIGINT_TEST_DIR = $(BIGINT_DIR)/tests

.PHONY: mat vec ivec tests clean

all: ivec vec mat bigint

ivec:
	$(MAKE) -C $(IVEC_DIR)

vec:
	$(MAKE) -C $(VEC_DIR)

mat:
	$(MAKE) -C $(MAT_DIR)

bigint:
	$(MAKE) -C $(BIGINT_DIR)

tests:
	$(MAKE) -C $(TESTS_DIR)

clean:
	rm -rf $(BUILD_DIR)/*
