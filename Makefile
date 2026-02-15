# === Directories ===
IVEC_DIR      = src/ivector
IVEC_TEST_DIR = $(IVEC_DIR)/tests

ROOT_DIR    := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
BUILD_DIR   := $(ROOT_DIR)/build
LIBS_DIR    := $(ROOT_DIR)/lib
BIN_DIR     := $(ROOT_DIR)/bin

export ROOT_DIR
export BUILD_DIR
export LIBS_DIR
export BIN_DIR

.PHONY: ivectest ivec clean

ivec:
	$(MAKE) -C $(IVEC_DIR)

ivectest:
	$(MAKE) -C $(IVEC_TEST_DIR)

clean:
	rm ./bin/*
	rm ./build/*
	rm ./lib/*
