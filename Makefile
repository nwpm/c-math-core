# === Directories ===
ROOT_DIR    := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
BUILD_DIR   := $(ROOT_DIR)/build
LIBS_DIR    := $(ROOT_DIR)/lib
BIN_DIR     := $(ROOT_DIR)/bin
SRC_DIR     := $(ROOT_DIR)/src

export ROOT_DIR
export BUILD_DIR
export LIBS_DIR
export BIN_DIR

IVEC_DIR      = $(SRC_DIR)/ivector
IVEC_TEST_DIR = $(IVEC_DIR)/tests

VEC_DIR      = $(SRC_DIR)/vector
VEC_TEST_DIR = $(VEC_DIR)/tests

.PHONY: vectest vec ivectest ivec clean

ivec:
	$(MAKE) -C $(IVEC_DIR)

ivectest:
	$(MAKE) -C $(IVEC_TEST_DIR)

vec:
	$(MAKE) -C $(VEC_DIR)

vectest:
	$(MAKE) -C $(VEC_TEST_DIR)

clean:
	rm -r ./bin/*
	rm -r ./build/*
	rm -r ./lib/*
