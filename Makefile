# === Directories ===
ROOT_DIR       := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
BUILD_DIR      := $(ROOT_DIR)/build
TESTS_DIR      := $(ROOT_DIR)/test
LIBS_DIR       := $(BUILD_DIR)/lib
BIN_DIR        := $(BUILD_DIR)/bin
THIRDPARTY_DIR := $(BUILD_DIR)/thirdparty
SRC_DIR        := $(ROOT_DIR)/src

IVEC_DIR       := $(SRC_DIR)/ivector
VEC_DIR        := $(SRC_DIR)/vector
MAT_DIR        := $(SRC_DIR)/matrix
BIGINT_DIR     := $(SRC_DIR)/bigint

IVEC_TEST_DIR   := $(IVEC_DIR)/tests
VEC_TEST_DIR    := $(VEC_DIR)/tests
MAT_TEST_DIR    := $(MAT_DIR)/tests
BIGINT_TEST_DIR := $(BIGINT_DIR)/tests

export ROOT_DIR
export BUILD_DIR
export LIBS_DIR
export BIN_DIR
export THIRDPARTY_DIR

export IVEC_DIR
export VEC_DIR
export MAT_DIR
export BIGINT_DIR

export VEC_TEST_DIR

.PHONY: mat vec ivec tests clean

all: ivec vec mat bigint ivectest vectest mattest binttest

ivec:
	$(MAKE) -C $(IVEC_DIR)

vec:
	$(MAKE) -C $(VEC_DIR)

mat:
	$(MAKE) -C $(MAT_DIR)

bigint:
	$(MAKE) -C $(BIGINT_DIR)

ivectest:
	$(MAKE) -C $(IVEC_TEST_DIR)

vectest:
	$(MAKE) -C $(VEC_TEST_DIR)

clean:
	rm -rf $(BUILD_DIR)/*
