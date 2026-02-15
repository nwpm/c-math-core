MODULES = ivec

# === Source files ===
IVEC_SRC = src/ivector

.PHONY: ivec clean

ivec:
	$(MAKE) -C $(IVEC_SRC)

tests:
	$(MAKE) -C $(CORE_TEST_DIR)

