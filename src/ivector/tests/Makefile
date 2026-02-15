include ../../common.mk

# === Binary Targets ===
IVEC2_TEST = ../../../bin/test_ivec2

# === Source files ===
IVEC2_TEST_SRC = ./test_ivec2.c

# === Object Files ===
IVEC2_TEST_OBJ = ../../../build/test_ivec2.o
# TODO: make separate target for it
IVEC2_OBJ      = ../../../build/ivec2.o

ivec2t: $(IVEC2_TEST)

$(IVEC2_TEST) : $(IVEC2_TEST_OBJ) $(IVEC2_OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lm

$(IVEC2_TEST_OBJ) : $(IVEC2_TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@
