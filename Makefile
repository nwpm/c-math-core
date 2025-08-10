# === PATHS ===

BUILD_DIR  = build
BIN_DIR    = bin

# === TARGETS ===

.PHONY: matrix mtest bclean

matrix:
	$(MAKE) -C src/matrix

mtest:
	$(MAKE) -C test/matrix

bclean:
	rm -r $(BUILD_DIR)/*
