
.PHONY: sp-mh-clean .sp-mh-boot .sp-mh-kernel sp-mh-boot-clean sp-mh-kernel-clean .sp_pub_key

TOOLCHAIN_MH1902_PATH=$(call qstrip,$(BR2_SP_MH1902_TOOLCHAIN_INSTALL_PATH))
TARGET_CROSS_MH1902=$(TOOLCHAIN_MH1902_PATH)/$(call qstrip,$(BR2_SP_MH1902_TOOLCHAIN_PREFIX))
MH_SRC_DIR=$(WORKSPACE)/secure/mh1902
MH_BUILD_DIR=$(BUILD_DIR)/mh1902/
SP_BOOT_VERSION=$(call qstrip,$(BR2_SP_BOOT_VERSION))
SP_KERNEL_VERSION=$(call qstrip,$(BR2_SP_KERNEL_VERSION))
SP_FIRMWARE_SVN=$(call qstrip,$(FIRMWARE_VERSION_SVN))
SP_BOOT_IMG_NAME=$(call qstrip,$(BR2_SP_BOOT_IMG_NAME))
SP_KERNEL_IMG_NAME=$(call qstrip,$(BR2_SP_KERNEL_IMG_NAME))


SP_FLASH_START_OFFSET = $(shell echo $(BR2_SP_CHIPFLASH_START_ADDR) | sed 's/0x//')
SP_KERNEL_FLASH_ADDR  = $(shell echo $(BR2_SP_KERNEL_FLASH_OFFSET_ADDR) | sed 's/0x//')
SP_KERNEL_BINIMAGE_OFFSET = $(shell echo "obase=10;ibase=16;$(SP_KERNEL_FLASH_ADDR) - $(SP_FLASH_START_OFFSET)" | bc)



MH_BOOT_PART_OFFSET=0 # HEX in size
MH_KERNEL_PART_OFFSET=40000 # HEX in size
MH_BOOT_PARTITION_SIZE=$(shell printf "%d" 0x$(MH_KERNEL_PART_OFFSET)) #Bytes

toolchain-mh1902:
	@echo "toolchain mh1902 building"
	test -e $(TOOLCHAIN_MH1902_PATH) || \
	(wget --output-document=$(DL_DIR)/toolchain-mh1902.bin $(BR2_SP_MH1902_TOOLCHAIN_URL) && \
	mkdir -p $(TOOLCHAIN_MH1902_PATH) && \
	$(TAR) $(TAR_STRIP_COMPONENTS)=1 -C $(TOOLCHAIN_MH1902_PATH) $(TAR_OPTIONS) $(DL_DIR)/toolchain-mh1902.bin)
	rm -rf $(DL_DIR)/toolchain-mh1902.bin
	
.mh1902_bin_output_dir:
	@test -d $(SYSTEM_DIR)/home/sp || mkdir -p $(SYSTEM_DIR)/home/sp
	@test -d $(MH_BUILD_DIR)/boot/include/generated || mkdir -p $(MH_BUILD_DIR)/boot/include/generated
	@test -d $(MH_BUILD_DIR)/kernel/include/generated || mkdir -p $(MH_BUILD_DIR)/kernel/include/generated

.sp_pub_key:
	@echo "generate mf_pub_key.h and mk_pub_key.h"
	@support/scripts/signature -q -l -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT) -k ms -o $(MH_BUILD_DIR)/boot/ms.pem
	@support/scripts/signature -q -g -c $(BR2_SBI_SIGNATURE_MACHINE):$(BR2_SBI_SIGNATURE_PORT) \
        -t mkey -V "NEW POS TECHNOLOGY LIMITED" -v 1.0.0 -f $(MH_BUILD_DIR)/boot/ms.pem -o $(MH_BUILD_DIR)/boot/ms_puk
	@echo -n "const " > $(MH_BUILD_DIR)/boot/include/generated/ms_pub_key.h
	@(cd $(MH_BUILD_DIR)/boot/; xxd -c 16 -i ms_puk >> $(MH_BUILD_DIR)/boot/include/generated/ms_pub_key.h)
	@support/scripts/signature -q -l -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT) -k mf -o $(MH_BUILD_DIR)/boot/mf.pem
	@support/scripts/signature -q -g -c $(BR2_SBI_SIGNATURE_MACHINE):$(BR2_SBI_SIGNATURE_PORT) \
        -t mkey -V "NEW POS TECHNOLOGY LIMITED" -v 1.0.0 -f $(MH_BUILD_DIR)/boot/mf.pem -o $(MH_BUILD_DIR)/boot/mf_puk
	@echo -n "const " > $(MH_BUILD_DIR)/boot/include/generated/mf_pub_key.h
	@(cd $(MH_BUILD_DIR)/boot/; xxd -c 16 -i mf_puk >> $(MH_BUILD_DIR)/boot/include/generated/mf_pub_key.h)
	
	
	@support/scripts/signature -q -l -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT) -k mk -o $(MH_BUILD_DIR)/boot/mk.pem
	@support/scripts/signature -q -g -c $(BR2_SBI_SIGNATURE_MACHINE):$(BR2_SBI_SIGNATURE_PORT) \
        -t mkey -V "NEW POS TECHNOLOGY LIMITED" -v 1.0.0 -f $(MH_BUILD_DIR)/boot/mk.pem -o $(MH_BUILD_DIR)/boot/mk_puk
	@echo -n "const " > $(MH_BUILD_DIR)/boot/include/generated/mk_pub_key.h
	@(cd $(MH_BUILD_DIR)/boot/; xxd -c 16 -i mk_puk >> $(MH_BUILD_DIR)/boot/include/generated/mk_pub_key.h)
	
	@cp $(MH_BUILD_DIR)/boot/include/generated/mf_pub_key.h $(MH_BUILD_DIR)/kernel/include/generated/mf_pub_key.h
	@cp $(MH_BUILD_DIR)/boot/include/generated/ms_pub_key.h $(MH_BUILD_DIR)/kernel/include/generated/ms_pub_key.h
	@cp $(MH_BUILD_DIR)/boot/include/generated/mk_pub_key.h $(MH_BUILD_DIR)/kernel/include/generated/mk_pub_key.h

.sp-mh-kernel: .mh1902_bin_output_dir toolchain-mh1902 .sp_pub_key
	@echo "mh1902 kernel building"
	cd $(MH_SRC_DIR)/kernel; \
	$(TARGET_MAKE_ENV) $(MAKE) CROSS_COMPILE=$(TARGET_CROSS_MH1902) O=$(MH_BUILD_DIR)/kernel $(if $(BR2_CUSTOMER_PCI),CFG_PCI_COMPLY=y) $(if $(BR2_CUSTOMER_UMS),CFG_UPTS_COMPLY=y) $(if $(BR2_CUSTOMER_UPTS),CFG_UPTS_COMPLY=y) $(if $(BR2_CUSTOMER_UPTS),CFG_PCI_COMPLY=y) CFG_KERNEL_OFFSET_ADDR=$(BR2_SP_KERNEL_FLASH_OFFSET_ADDR) CFG_FLASH_START_ADDR=$(BR2_SP_CHIPFLASH_START_ADDR) CFG_SP_KERNEL_VERSION=V$(BR2_SP_KERNEL_VERSION) TEE_IMPL_VERSION=$(SP_FIRMWARE_SVN) CFG_FIRMWARE_VERSION=V$(BR2_SP_FIRMWARE_VERSION) CFG_BOOT_IMG_NAME=$(SP_BOOT_IMG_NAME)
	./support/scripts/mark $(MH_BUILD_DIR)/kernel/kernel.bin  $(MH_BUILD_DIR)/kernel/kernel.bin.tmp   -C
	support/scripts/signature -q -g -k mf -t firmware -f $(MH_BUILD_DIR)/kernel/kernel.bin.tmp  \
        -o $(MH_BUILD_DIR)/kernel/kernel.bin.tmp.sig -V "NEW POS TECHNOLOGY LIMITED" \
		-c $(call qstrip,$(BR2_SIGNATURE_MACHINE)):$(call qstrip,$(BR2_SIGNATURE_PORT)) \
        -v $(if $(SP_KERNEL_VERSION),$(SP_KERNEL_VERSION),\
		`cat $(MH_BUILD_DIR)/kernel/include/generated/version.h | awk -NF\" /KERNEL_VERSION/'{print $$2}' | cut -b 2-`)

################
# debug: quickly generate kernel download directly image
#
##############
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/kernel/kernel.bin.tmp -o $(MH_BUILD_DIR)/kernel/be_signing_data.tmp -h $(MH_BUILD_DIR)/kernel/boot_hd_data.tmp
	./support/scripts/signature  -n  -k ms -f $(MH_BUILD_DIR)/kernel/be_signing_data.tmp -o $(MH_BUILD_DIR)/kernel/signed_data.tmp -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT) 
	./support/scripts/download_format.exe -b $(MH_BUILD_DIR)/kernel/kernel.bin.tmp  -f $(MH_BUILD_DIR)/kernel/signed_data.tmp -s -o $(MH_BUILD_DIR)/kernel_download_sig_$(shell date +%Y-%m-%d).bin 
	rm   $(MH_BUILD_DIR)/kernel/boot_hd_data.tmp $(MH_BUILD_DIR)/kernel/be_signing_data.tmp $(MH_BUILD_DIR)/kernel/signed_data.tmp 
.sp-mh-boot: .mh1902_bin_output_dir toolchain-mh1902 .sp_pub_key
	@echo "mh1902 boot building"
	cd $(MH_SRC_DIR)/boot; \
	$(TARGET_MAKE_ENV) $(MAKE) CROSS_COMPILE=$(TARGET_CROSS_MH1902) O=$(MH_BUILD_DIR)/boot   CFG_FLASH_START_ADDR=$(BR2_SP_CHIPFLASH_START_ADDR) CFG_KERNEL_OFFSET_ADDR=$(BR2_SP_KERNEL_FLASH_OFFSET_ADDR) CFG_KERNEL_IMG_NAME=$(SP_KERNEL_IMG_NAME)
#support/scripts/signature -q -g -k mf -t firmware -f $(MH_BUILD_DIR)/boot/boot.bin  \
        -o $(MH_BUILD_DIR)/boot/boot.bin.sig -V "NEW POS TECHNOLOGY LIMITED" \
		-c $(call qstrip,$(BR2_SIGNATURE_MACHINE)):$(call qstrip,$(BR2_SIGNATURE_PORT)) \
        -v $(if $(SP_KERNEL_VERSION),$(SP_KERNEL_VERSION),\
		`cat $(MH_BUILD_DIR)/boot/include/generated/version.h | awk -NF\" /BOOT_VERSION/'{print $$2}' | cut -b 2-`)
	./support/scripts/mark $(MH_BUILD_DIR)/boot/boot.bin $(MH_BUILD_DIR)/boot/boot.bin.tmp -C
	mv  $(MH_BUILD_DIR)/boot/boot.bin.tmp  $(MH_BUILD_DIR)/boot/boot.bin 
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/boot/boot.bin  -o $(MH_BUILD_DIR)/boot/be_signing_data.tmp -h $(MH_BUILD_DIR)/boot/boot_hd_data.tmp
	cat $(MH_BUILD_DIR)/boot/boot.bin  $(MH_BUILD_DIR)/boot/boot_hd_data.tmp  $(MH_BUILD_DIR)/boot/be_signing_data.tmp  > $(MH_BUILD_DIR)/boot/boot_image.bin.tmp
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/boot/boot_image.bin.tmp  -o $(MH_BUILD_DIR)/boot/be_signing_data.tmp -h $(MH_BUILD_DIR)/boot/boot_hd_data.tmp
	./support/scripts/download_format.exe -b  $(MH_BUILD_DIR)/boot/boot_image.bin.tmp  -f $(MH_BUILD_DIR)/boot/be_signing_data.tmp  -o $(MH_BUILD_DIR)/boot_download_$(shell date +%Y-%m-%d).bin 		
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/boot/boot.bin  -o $(MH_BUILD_DIR)/boot/be_signing_data.tmp -h $(MH_BUILD_DIR)/boot/boot_hd_data.tmp
	./support/scripts/signature  -n  -k ms -f  $(MH_BUILD_DIR)/boot/be_signing_data.tmp -o $(MH_BUILD_DIR)/boot/signed_data.tmp -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT) 
	cat $(MH_BUILD_DIR)/boot/boot.bin  $(MH_BUILD_DIR)/boot/boot_hd_data.tmp  $(MH_BUILD_DIR)/boot/signed_data.tmp  > $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig.add_tail
	support/scripts/signature -q -g -k mf -t firmware -f $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig.add_tail  \
        -o $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig -V "NEW POS TECHNOLOGY LIMITED" \
		-c $(call qstrip,$(BR2_SIGNATURE_MACHINE)):$(call qstrip,$(BR2_SIGNATURE_PORT)) \
        -v $(if $(SP_BOOT_VERSION),$(SP_BOOT_VERSION),\
		`cat $(MH_BUILD_DIR)/boot/include/generated/version.h | awk -NF\" /BOOT_VERSION/'{print $$2}' | cut -b 2-`)
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig -o $(MH_BUILD_DIR)/boot/be_signing_data.tmp -h $(MH_BUILD_DIR)/boot/boot_hd_data.tmp
	./support/scripts/signature  -n  -k ms -f  $(MH_BUILD_DIR)/boot/be_signing_data.tmp -o $(MH_BUILD_DIR)/boot/signed_data.tmp -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT) 
	./support/scripts/download_format.exe -b $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig  -f $(MH_BUILD_DIR)/boot/signed_data.tmp -s -o $(MH_BUILD_DIR)//boot_download_sig_$(shell date +%Y-%m-%d).bin 
	rm  $(MH_BUILD_DIR)/boot/boot_hd_data.tmp $(MH_BUILD_DIR)/boot/be_signing_data.tmp $(MH_BUILD_DIR)/boot/signed_data.tmp $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig.add_tail

#
# convert mh1902 and flash new image
#
sp-mh-download: .sp-mh-boot .sp-mh-kernel
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/boot/boot.bin  -o $(MH_BUILD_DIR)/be_signing_data.tmp -h $(MH_BUILD_DIR)/boot_hd_data.tmp
	./support/scripts/signature  -n -k ms -f  $(MH_BUILD_DIR)/be_signing_data.tmp -o  $(MH_BUILD_DIR)/signed_data.tmp -c $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT)
	cat   $(MH_BUILD_DIR)/boot/boot.bin $(MH_BUILD_DIR)/boot_hd_data.tmp  $(MH_BUILD_DIR)/be_signing_data.tmp > $(MH_BUILD_DIR)/boot_$(shell date +%Y-%m-%d).bin.tmp 
	cat   $(MH_BUILD_DIR)/boot/boot.bin $(MH_BUILD_DIR)/boot_hd_data.tmp $(MH_BUILD_DIR)/signed_data.tmp >  $(MH_BUILD_DIR)/boot_sig_$(shell date +%Y-%m-%d).bin.tmp
	dd if=$(MH_BUILD_DIR)/boot_sig_$(shell date +%Y-%m-%d).bin.tmp    of=$(MH_BUILD_DIR)/$@.tmp.sig
	dd if=$(MH_BUILD_DIR)/boot_$(shell date +%Y-%m-%d).bin.tmp  of=$(MH_BUILD_DIR)/$@.tmp
	dd if=$(MH_BUILD_DIR)/kernel/kernel.bin.tmp.sig of=$(MH_BUILD_DIR)/$@.tmp.sig  bs=1 seek=$(SP_KERNEL_BINIMAGE_OFFSET) 
	dd if=$(MH_BUILD_DIR)/kernel/kernel.bin.tmp.sig  of=$(MH_BUILD_DIR)/$@.tmp  bs=1 seek=$(SP_KERNEL_BINIMAGE_OFFSET) 
	   
	./support/scripts//gen_be_signing_data.exe -b $(MH_BUILD_DIR)/$@.tmp.sig -o $(MH_BUILD_DIR)/be_signing_data.tmp -h $(MH_BUILD_DIR)/flash_hd_data.tmp
	./support/scripts/signature -n  -k ms  -f $(MH_BUILD_DIR)/be_signing_data.tmp -o  $(MH_BUILD_DIR)/signed_data.tmp -c  $(BR2_SIGNATURE_MACHINE):$(BR2_SIGNATURE_PORT)	
	./support/scripts/download_format.exe -b $(MH_BUILD_DIR)/$@.tmp.sig   -f $(MH_BUILD_DIR)/signed_data.tmp -s -o $(MH_BUILD_DIR)/$@_sig_$(shell date +%Y-%m-%d).bin 
	./support/scripts/gen_be_signing_data.exe -b $(MH_BUILD_DIR)/$@.tmp -o $(MH_BUILD_DIR)/be_signing_data.tmp -h $(MH_BUILD_DIR)/flash_hd_data.tmp			
	./support/scripts/download_format.exe -b $(MH_BUILD_DIR)/$@.tmp  -f $(MH_BUILD_DIR)/be_signing_data.tmp  -o $(MH_BUILD_DIR)/$@_$(shell date +%Y-%m-%d).bin 	
	rm  $(MH_BUILD_DIR)/boot_hd_data.tmp $(MH_BUILD_DIR)/be_signing_data.tmp $(MH_BUILD_DIR)/signed_data.tmp $(MH_BUILD_DIR)/flash_hd_data.tmp

sp-mh-boot: .sp-mh-boot
	mv $(MH_BUILD_DIR)/boot/boot_image.bin.tmp.sig $(SYSTEM_DIR)/home/sp/$(SP_BOOT_IMG_NAME)
sp-mh-kernel: .sp-mh-kernel
	mv $(MH_BUILD_DIR)/kernel/kernel.bin.tmp.sig $(SYSTEM_DIR)/home/sp/$(SP_KERNEL_IMG_NAME)
sp-mh-boot-clean:
	rm -rf $(MH_BUILD_DIR)/boot

sp-mh-kernel-clean:
	rm -rf $(MH_BUILD_DIR)/kernel

sp-mh-clean:
	@echo "clean all sp building"
	rm -rf $(MH_BUILD_DIR)
