
TARGETS += toolchain

.PHONY: toolchain toolchain-clean

TOOLCHAIN_PATH=$(call qstrip,$(BR2_TOOLCHAIN_INSTALL_PATH))
TARGET_CROSS=$(TOOLCHAIN_PATH)/$(call qstrip,$(BR2_TOOLCHAIN_PREFIX))
NDK_CFLAGS="-fno-short-enums -include $(BUILDCONFIG_HEANDER_FILE)"

toolchain:
	@echo "toolchain building $(TOOLCHAIN_PATH)"
	test -e $(TOOLCHAIN_PATH)/ndk || \
	(wget --output-document=$(DL_DIR)/toolchain-cross.bin $(BR2_TOOLCHAIN_URL) && \
	mkdir -p $(TOOLCHAIN_PATH) && \
	$(TAR) $(TAR_STRIP_COMPONENTS)=0 -C $(TOOLCHAIN_PATH) $(TAR_OPTIONS) $(DL_DIR)/toolchain-cross.bin)
	rm -rf $(DL_DIR)/toolchain-cross.bin

toolchain-clean:
	@echo "toolchain-clean"
	rm -rf $(TOOLCHAIN_PATH)

