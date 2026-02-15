# === Compiler Settings ===
CC           ?= gcc
BUILD_TYPE   ?= debug
CFLAGS        = -Werror -Wall -Wextra
DEBUG_FLAGS   = -O0 -g -fsanitize=address -fsanitize=undefined
RELEASE_FLAGS = -O2

ifeq ($(BUILD_TYPE), debug)
	CFLAGS += $(DEBUG_FLAGS)
else
	CFLAGS += $(RELEASE_FLAGS)
endif

