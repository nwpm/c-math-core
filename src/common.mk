# === Paths ===
ROOT_DIR    = ./..
BUILD_DIR   = $(ROOT_DIR)/build
LIBS_DIR    = $(ROOT_DIR)/lib
BIN_DIR     = $(ROOT_DIR)/bin

# === Compiler Settings ===
CC         ?= gcc
BUILD_TYPE ?= debug
CFLAGS      = -Werror -Wall -Wextra
DEBUG_FLAGS   = -O0 -g -fsanitize=address -fsanitize=undefined
RELEASE_FLAGS = -O2

ifeq ($(BUILD_TYPE), debug)
	CFLAGS += $(DEBUG_FLAGS)
else
	CFLAGS += $(RELEASE_FLAGS)
endif

