CORE_DIR = src/core
CORE_TEST_DIR = test/core

.PHONY: core tests

core:
	$(MAKE) -C $(CORE_DIR)

tests:
	$(MAKE) -C $(CORE_TEST_DIR)

