# === Compiler Settings ===
CC    ?= gcc
CFLAGS = -Werror -Wall -Wextra -O0 -g -fsanitize=address -fsanitize=undefined

.PHONY: unity tivec tvec tmat

all: unity tivec tvec

unity:
	cmake -S ./Unity -B ../build/third_party/ -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(abspath ../build/third_party/)
	$(MAKE) -C ../build/third_party/

tivec:
	$(MAKE) -C ../src/ivector/tests/

tvec:
	$(MAKE) -C ../src/vector/tests/

tmat:
	$(MAKE) -C ../src/matrix/tests/


