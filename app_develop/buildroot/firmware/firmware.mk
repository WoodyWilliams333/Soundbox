
TARGETS += firmware

IMAGE_BUILD_DIR=$(BUILD_DIR)/image-build
KEYS_HASH_FILE=$(IMAGE_BUILD_DIR)/key_hash_file
ATTACHED_INFO_FILE=$(IMAGE_BUILD_DIR)/attached_info.ini
BOOT_PARTITION_SIZE=131072 # 128k Bytes
BINARIES_DIR=$(call qstrip,$(BR2_FIRMWARE_INSTALL_PATH))
FIRMWARE_DIR=$(BUILD_DIR)/firmware
FIRMWARE_PUB_DIR=$(FIRMWARE_DIR)/pub
FIRMWARE_SOURCE_PATH=$(WORKSPACE)/secure
FIRMWARE_INSTALL_PATH=$(call qstrip,$(BR2_FIRMWARE_INSTALL_PATH))
IMAGE_VERSION=$(call qstrip,$(BR2_IMAGE_VERSION))
FIRMWARE_TYPE=$(call qstrip,$(BR2_FIRMWARE_TYPE))
FIRMWARE_SUFFIX=$(call qstrip,$(BR2_FIRMWARE_SUFFIX))
IMAGE_FILE_NAME=$(call qstrip,$(BR2_IMAGE_NAME)-v$(IMAGE_VERSION))
FIRMWARE_CUSTOMER=$(call qstrip,$(BR2_CUSTOMER_TYPE))
SIGNATURE_MACHINE_MS=$(call qstrip,$(BR2_MS_SIGNATURE_IP)):$(call qstrip,$(BR2_MS_SIGNATURE_PORT))
SIGNATURE_MACHINE_MF=$(call qstrip,$(BR2_MF_SIGNATURE_IP)):$(call qstrip,$(BR2_MF_SIGNATURE_PORT))
SIGNATURE_TOOL=support/scripts/signature

FIRMWARE_SUBDIR_LIST=$(shell ls $(FIRMWARE_SOURCE_PATH))
FIRMWARE_CONFIG_SUBDIRS = $(foreach f,$(FIRMWARE_SUBDIR_LIST),$(if $(BR2_CONFIG_FIRMWARE_$(shell echo $f | tr a-z- A-Z_)),$(f),))

FIRMWARE_SUBDIR_ENV=SYSAPP_INSTALL_PATH=$(SYSAPP_INSTALL_PATH) \
		   LIBRARY_INSTALL_PATH=$(LIBRARY_INSTALL_PATH) \
           SYSAPP_INSTALL_PATH=$(SYSAPP_INSTALL_PATH) \
           FIRMWARE_INSTALL_PATH=$(FIRMWARE_INSTALL_PATH) \
           FIRMWARE_VERSION=$(FIRMWARE_VERSION) \
           FIRMWARE_TYPE=$(FIRMWARE_TYPE) \
           FIRMWARE_SUFFIX=$(FIRMWARE_SUFFIX) \
           FIRMWARE_PCI_COMPLY=$(FIRMWARE_PCI_COMPLY) \
           FIRMWARE_CUSTOMER=$(FIRMWARE_CUSTOMER) \
           IMAGE_VERSION=$(IMAGE_VERSION) \
           TOOLS_INSTALL_PATH=$(TOOLS_INSTALL_PATH) \
           CROSS_COMPILE=$(TARGET_CROSS) \
           SDK_INSTALL_PATH=$(SDK_PATH) \
		   SYSTEM_PATH=$(SYSTEM_DIR) \
		   RECOVERY_DIR=$(RECOVERY_DIR) \
		   M0_PATCH_PATH="$(BUILD_DIR)/firmware/kernel/M0/" \
		   DOWNLOAD_BINARY_FILE="$(BUILD_DIR)/sysapp/download/obj/local/cortexm/download.bin"


FIRMWARE_JOIN_LIST=$(patsubst %,firmware-%,$(FIRMWARE_CONFIG_SUBDIRS))
FIRMWARE_JOIN_LIST_CLEAN=$(patsubst %,%-clean,$(FIRMWARE_JOIN_LIST))
FIRMWARE_JOIN_LIST_INSTALL=$(patsubst %,%-install,$(FIRMWARE_JOIN_LIST))

define ALONE_FIRMWARE_BUILD
	test -d $(FIRMWARE_DIR)/$(1)/include/generated/ || mkdir -p $(FIRMWARE_DIR)/$(1)/include/generated/
	@cp $(FIRMWARE_PUB_DIR)/mf_pub_key.h $(FIRMWARE_DIR)/$(1)/include/generated/mf_pub_key.h
	@cp $(FIRMWARE_PUB_DIR)/mk_pub_key.h $(FIRMWARE_DIR)/$(1)/include/generated/mk_pub_key.h
	@cp $(FIRMWARE_PUB_DIR)/key_hash.h $(FIRMWARE_DIR)/$(1)/include/generated/key_hash.h
	$(TARGET_MAKE_ENV) $(FIRMWARE_SUBDIR_ENV) $(MAKE) -C $(FIRMWARE_SOURCE_PATH)/$(1) O=$(FIRMWARE_DIR)/$(1) $(2)
	$(TOOLS_INSTALL_PATH)/fixsize $(FIRMWARE_DIR)/$(1)/$(1).bin
	if [ "$(1)" == "boot" ]; then \
		$(SIGNATURE_TOOL) -l -k ms -c $(SIGNATURE_MACHINE_MS) -o $(FIRMWARE_DIR)/$(1)/c2.pub.pem ;\
		$(FIRMWARE_SOURCE_PATH)/$(1)/secimage/sign-sbi.sh $(FIRMWARE_SOURCE_PATH)/$(1)/secimage/secimage \
			$(FIRMWARE_SOURCE_PATH)/$(1)/secimage/lynx_unauth.cfg \
			$(FIRMWARE_DIR)/$(1)/c2.pub.pem \
			$(SIGNATURE_TOOL) $(SIGNATURE_MACHINE_MS) \
			$(FIRMWARE_DIR)/$(1)/$(1).bin $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp ;\
		\
		$(SIGNATURE_TOOL) -q -g -k mf -t boot -f $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp  \
	        -o $(FIRMWARE_DIR)/$(1)/$(1).bin.sig -V "NEW POS TECHNOLOGY LIMITED" \
			-c $(SIGNATURE_MACHINE_MF) \
			-v $(if $(BR2_BUILD_DEBUG),$(BR2_SP_BOOT_VERSION),`cat $(FIRMWARE_DIR)/$(1)/include/generated/version.h | awk -NF\" /KERNEL_VERSION/'{print $$2}' | cut -b 2-`) ;\
		cp -rf $(FIRMWARE_DIR)/$(1)/$(1).bin.sig $(BINARIES_DIR)/sp.bcm.boot ;\
		rm -f $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp ;\
	else \
		$(FIRMWARE_SOURCE_PATH)/$(1)/padding.py $(FIRMWARE_DIR)/$(1)/$(1).bin ;\
		$(SIGNATURE_TOOL) -q -g -k mf -t kernel -f $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp  \
	        -o $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp.sig -V "NEW POS TECHNOLOGY LIMITED" \
			-c $(SIGNATURE_MACHINE_MF) \
	        -v $(if $(BR2_BUILD_DEBUG),$(BR2_SP_KERNEL_VERSION),`cat $(FIRMWARE_DIR)/$(1)/include/generated/version.h | awk -NF\" /KERNEL_VERSION/'{print $$2}' | cut -b 2-`) ;\
		$(FIRMWARE_SOURCE_PATH)/$(1)/mkaai.py $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp.sig ;\
		cp -rf $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp.sig.noxip $(BINARIES_DIR)/sp.bcm.kernel ;\
		rm -f $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp $(FIRMWARE_DIR)/$(1)/$(1).bin.tmp.sig ;\
	fi
endef

# Get key from signature server
# Argument 1: key name
# Argument 2: signature server ip & port
# Argument 3: output path
define get_key
	@echo "Generate $(1).pem from $(2)"	
	@$(SIGNATURE_TOOL) -q -l -k $(1) -c $(2) -o $(3)/$(1).pem
endef

$(FIRMWARE_PUB_DIR)/ms.pem:
	$(call get_key,ms,$(SIGNATURE_MACHINE_MS),$(FIRMWARE_PUB_DIR))

$(FIRMWARE_PUB_DIR)/mf.pem:
	$(call get_key,mf,$(SIGNATURE_MACHINE_MF),$(FIRMWARE_PUB_DIR))

$(FIRMWARE_PUB_DIR)/mk.pem:
	$(call get_key,mk,$(SIGNATURE_MACHINE_MF),$(FIRMWARE_PUB_DIR))

$(FIRMWARE_PUB_DIR)/mf_pub_key.h: $(FIRMWARE_PUB_DIR)/mf.pem
	@$(SIGNATURE_TOOL) -q -g -c $(SIGNATURE_MACHINE_MS) \
        -t mkey -V "NEW POS TECHNOLOGY LIMITED" -v 1.0.0 -f$(FIRMWARE_PUB_DIR)/mf.pem -o $(FIRMWARE_PUB_DIR)/mf_puk
	@(cd $(FIRMWARE_PUB_DIR)/; echo -n "const " > $@; xxd -c 16 -i mf_puk >> $@)
	
$(FIRMWARE_PUB_DIR)/key_hash.h: firmware-id 
	@echo "#ifndef __FIRMWARE_INFO_H__" > $@
	@echo "#define __FIRMWARE_INFO_H__" >> $@
	@echo "#define FIRMWAREID  \"`cat $(KEYS_HASH_FILE)`\"" >> $@
	@echo "#endif" >> $@

$(FIRMWARE_PUB_DIR)/mk_pub_key.h: $(FIRMWARE_PUB_DIR)/mk.pem
	@$(SIGNATURE_TOOL) -q -g -c $(SIGNATURE_MACHINE_MS) \
        -t mkey -V "NEW POS TECHNOLOGY LIMITED" -v 1.0.0 -f $(FIRMWARE_PUB_DIR)/mk.pem -o $(FIRMWARE_PUB_DIR)/mk_puk
	@(cd $(FIRMWARE_PUB_DIR)/; echo -n "const " > $@; xxd -c 16 -i mk_puk >> $@)
	
.firmware_related_dir:
	@test -d $(FIRMWARE_INSTALL_PATH) || mkdir -p $(FIRMWARE_INSTALL_PATH)
	@test -d $(FIRMWARE_DIR) || mkdir -p $(FIRMWARE_DIR)
	@test -d $(FIRMWARE_PUB_DIR) || mkdir -p $(FIRMWARE_PUB_DIR)

define create_attached_info
	@test -e $(FIRMWARE_PUB_DIR) || mkdir -p $(FIRMWARE_PUB_DIR)
	@echo "[Attached Information]" > $(ATTACHED_INFO_FILE)
	@echo "Platform=BCM58101" >> $(ATTACHED_INFO_FILE)
	@echo "Customer=$(BR2_CUSTOMER_TYPE)" >> $(ATTACHED_INFO_FILE)
	@echo "Build_Model=c2" >> $(ATTACHED_INFO_FILE)
	@echo "HW_Version=V01" >> $(ATTACHED_INFO_FILE)
endef

# Generate keys hash file
define create_keys_hash_file
	@echo "Create Keys Hash here"
	$(call get_key,ms,$(SIGNATURE_MACHINE_MS),$(IMAGE_BUILD_DIR))
	$(call get_key,mf,$(SIGNATURE_MACHINE_MF),$(IMAGE_BUILD_DIR))
	$(call get_key,mk,$(SIGNATURE_MACHINE_MF),$(IMAGE_BUILD_DIR))
	$(call create_attached_info)
	@cd $(IMAGE_BUILD_DIR) && cat ms.pem mf.pem mk.pem $(ATTACHED_INFO_FILE) > keys.pem && \
		sha256sum --tag keys.pem | awk '{print $$4}' > $(KEYS_HASH_FILE) && \
	rm ms.pem mf.pem mk.pem keys.pem $(ATTACHED_INFO_FILE)
endef

keys-hash:
	@echo "Calculate Keys Hash here"
	@test -e $(IMAGE_BUILD_DIR) || mkdir -p $(IMAGE_BUILD_DIR)
	$(call create_keys_hash_file)
	@cat $(KEYS_HASH_FILE) | xxd -r -plain > $(IMAGE_BUILD_DIR)/key_hash
		
firmware-id: keys-hash
	@echo "get firmware-id here"
	@cat $(KEYS_HASH_FILE)	
		
firmware-info:
	@echo "Making the information for image "
	@echo "$(IMAGE_BUILD_DIR)/image_info"
	@echo "0120" | xxd -r -plain > $(IMAGE_BUILD_DIR)/image_info
	@cat $(IMAGE_BUILD_DIR)/key_hash >> $(IMAGE_BUILD_DIR)/image_info
	@echo "0207" | xxd -r -plain >> $(IMAGE_BUILD_DIR)/image_info
	@echo -n "NEWPO28" >> $(IMAGE_BUILD_DIR)/image_info
	@echo "002B" | xxd -r -plain >> $(IMAGE_BUILD_DIR)/image_info
	@echo -n "IMG:0001" >> $(IMAGE_BUILD_DIR)/image_info
firmware-download: firmware-info
	rm -rf $(BINARIES_DIR)/c2.download.tmp
	for i in {1..$(call qstrip,$(BOOT_PARTITION_SIZE))} ; do echo -n "FF" ; done | xxd -ps -r > $(BINARIES_DIR)/c2.download.tmp
	dd if=$(BINARIES_DIR)/sp.bcm.boot of=$(BINARIES_DIR)/c2.download.tmp bs=1024 conv=notrunc,nocreat
	dd if=$(BINARIES_DIR)/sp.bcm.kernel of=$(BINARIES_DIR)/c2.download.tmp bs=1024 oflag=append conv=notrunc
	mv $(BINARIES_DIR)/c2.download.tmp $(BINARIES_DIR)/$(IMAGE_FILE_NAME)-flash.bin
	$(TOOLS_INSTALL_PATH)/mkfirmware -o $(BINARIES_DIR)/c2.download.tmp -f $(BINARIES_DIR)/sp.bcm.boot -t boot -b 0
	$(TOOLS_INSTALL_PATH)/mkfirmware -o $(BINARIES_DIR)/c2.download.tmp -f $(BINARIES_DIR)/sp.bcm.kernel -t kernel -k 20000
	#for i in {1..16} ; do echo -n "FF" ; done | xxd -ps -r >> $(BINARIES_DIR)/c2.download.tmp
	cat $(IMAGE_BUILD_DIR)/image_info >> $(BINARIES_DIR)/c2.download.tmp
	$(SIGNATURE_TOOL) -q -g -t firmware \
	    -f $(BINARIES_DIR)/c2.download.tmp  \
	    -o $(BINARIES_DIR)/$(IMAGE_FILE_NAME)-firmware.bin \
	    -V "NEW POS TECHNOLOGY LIMITED" \
	    -c $(SIGNATURE_MACHINE_MF) \
	    -v "$(IMAGE_VERSION)" ;\
	rm -rf $(BINARIES_DIR)/c2.download.tmp $(BINARIES_DIR)/sp.bcm.boot $(BINARIES_DIR)/sp.bcm.kernel
	
firmware: .firmware_related_dir $(FIRMWARE_PUB_DIR)/key_hash.h  $(FIRMWARE_PUB_DIR)/mf_pub_key.h $(FIRMWARE_PUB_DIR)/mk_pub_key.h
	@test -d $(FIRMWARE_DIR) || mkdir -p $(FIRMWARE_DIR)
	$(foreach d,$(FIRMWARE_CONFIG_SUBDIRS),$(call ALONE_FIRMWARE_BUILD,$(d),)$(sep))
	$(MAKE) firmware-download

firmware-clean:
	rm -rf $(FIRMWARE_DIR)

$(FIRMWARE_JOIN_LIST): .firmware_related_dir $(FIRMWARE_PUB_DIR)/mf_pub_key.h $(FIRMWARE_PUB_DIR)/mk_pub_key.h
	$(call ALONE_FIRMWARE_BUILD,$(patsubst firmware-%,%,$@),)

$(FIRMWARE_JOIN_LIST_CLEAN):
	rm -rf $(FIRMWARE_DIR)/$(patsubst firmware-%-clean,%,$(@))
#	$(call ALONE_FIRMWARE_BUILD,$(patsubst firmware-%-clean,%,$(@)),clean)

.PHONY: firmware firmware-clean

