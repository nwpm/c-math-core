# === PATHS ===

BUILD_DIR  = build
BIN_DIR    = bin

UNITY_DIR   = test/Unity
UNITY_BUILD = $(BUILD_DIR)/unity

# === TARGETS ===

.PHONY: matrix mtest unity bclean

matrix:
	$(MAKE) -C src/matrix

mtest:
	$(MAKE) -C test/matrix

unity: $(UNITY_BUILD)
	cd $(UNITY_BUILD) && cmake ../../$(UNITY_DIR)
	cd $(UNITY_BUILD) && make
	find build/unity -mindepth 1 ! -name 'libunity.a' -exec rm -rf {} +

bclean:
	rm -r $(BUILD_DIR)/*

# === RULES ===

$(UNITY_BUILD):
	mkdir -p $@
