
.PHONY: .sp-ccore-boot .sp-ccore-kernel

SP_CUSTOMER_TYPE=$(call qstrip,$(BR2_CUSTOMER_TYPE))
SP_FIRMWARE_TYPE=$(call qstrip,$(BR2_FIRMWARE_TYPE))
CCORE_SRC_DIR=$(WORKSPACE)/secure/ccore
CCORE_BUILD_DIR=$(BUILD_DIR)/ccore/
CCORE_BUILDROOT_DEFCONFIG=new7220-$(SP_CUSTOMER_TYPE)-$(SP_FIRMWARE_TYPE)_defconfig

SP_BOOT_VERSION=$(call qstrip,$(BR2_SP_BOOT_VERSION))
SP_KERNEL_VERSION=$(call qstrip,$(BR2_SP_KERNEL_VERSION))
SP_FIRMWARE_SVN=$(call qstrip,$(FIRMWARE_VERSION_SVN))
SP_BOOT_IMG_NAME=$(call qstrip,$(BR2_SP_BOOT_IMG_NAME))
SP_KERNEL_IMG_NAME=$(call qstrip,$(BR2_SP_KERNEL_IMG_NAME))

SP_FLASH_START_OFFSET = $(shell echo $(BR2_SP_CHIPFLASH_START_ADDR) | sed 's/0x//')
SP_KERNEL_FLASH_ADDR  = $(shell echo $(BR2_SP_KERNEL_FLASH_OFFSET_ADDR) | sed 's/0x//')
SP_KERNEL_BINIMAGE_OFFSET = $(shell echo "obase=10;ibase=16;$(SP_KERNEL_FLASH_ADDR) - $(SP_FLASH_START_OFFSET)" | bc)

CC_BUILD_DIR=$(BUILD_DIR)/ccore/

.ccore_bin_output_dir:
	@test -d $(SYSTEM_DIR)/home/sp || mkdir -p $(SYSTEM_DIR)/home/sp
	test -d $(CCORE_BUILD_DIR)/build/firmware/kernel/include/generated || mkdir -p $(CCORE_BUILD_DIR)/build/firmware/kernel/include/generated
	test -d $(CCORE_BUILD_DIR)/build/firmware/boot/include/generated || mkdir -p $(CCORE_BUILD_DIR)/build/firmware/boot/include/generated

sp-ccore: .ccore_bin_output_dir .firwareid
	@$(call MESSAGE,"Building Product $(@)")
	$(Q)(cd $(CCORE_SRC_DIR)/buildroot; \
		make O=$(CCORE_BUILD_DIR) $(CCORE_BUILDROOT_DEFCONFIG) ; \
		make O=$(CCORE_BUILD_DIR) world )
		cp -f $(CC_BUILD_DIR)/system/bin/scpd.bin $(SYSTEM_DIR)/home/sp/$(SP_KERNEL_IMG_NAME)
		cp -f $(CC_BUILD_DIR)/system/bin/scpd.flash.download.bin $(BINARIES_DIR)/sp.flash.download.bin
	@echo "============================="
	@echo "build ccore images successfullly"
	@echo "============================="

sp-ccore-menuconfig:
	$(Q)(cd $(CCORE_SRC_DIR)/buildroot; \
		make O=$(CCORE_BUILD_DIR) $(CCORE_BUILDROOT_DEFCONFIG) ; \
		make O=$(CCORE_BUILD_DIR) menuconfig )
	cp -f $(CCORE_BUILD_DIR)/.config $(CCORE_SRC_DIR)/buildroot/configs/$(CCORE_BUILDROOT_DEFCONFIG)
	
sp-ccore-clean:
	@echo "clean all ccore building"
	rm -rf $(CCORE_BUILD_DIR)
	
sp-ccore-%:
	$(Q)(cd $(CCORE_SRC_DIR)/buildroot; \
		make O=$(CCORE_BUILD_DIR) $(CCORE_BUILDROOT_DEFCONFIG); \
		make O=$(CCORE_BUILD_DIR) $(patsubst sp-ccore-%,%,$@))
		
.firwareid:
	cp $(FIRMWAREID_OUTPUT_DIR)/firmwareid.h $(CCORE_BUILD_DIR)/build/firmware/boot/include/generated
	cp $(FIRMWAREID_OUTPUT_DIR)/firmwareid.h $(CCORE_BUILD_DIR)/build/firmware/kernel/include/generated
#cp $(BUILDCONFIG_HEANDER_FILE) $(CCORE_BUILD_DIR)/build/firmware/boot/include/generated
#cp $(BUILDCONFIG_HEANDER_FILE) $(CCORE_BUILD_DIR)/build/firmware/kernel/include/generated
