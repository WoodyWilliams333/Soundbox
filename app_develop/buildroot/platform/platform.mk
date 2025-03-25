
TARGETS += buildconfig
TARGETS += firmwareid
TARGETS += firmware-info

PRODUCT_NAME=$(call qstrip,$(BR2_PRODUCT_NAME))

BUILDCONFIG_SOURCE_CODE_DIR=$(WORKSPACE)/buildroot/support/scripts
BUILDCONFIG_INPUT_CONFIG_FILE=$(CONFIG_DIR)/.config
BUILDCONFIG_GEN_CONFIG_FILE=$(CONFIG_DIR)/.config.header
BUILDCONFIG_OUTPUT_BASE_DIR=$(BUILD_DIR)/build_config
BUILDCONFIG_HEANDER_FILE=$(BUILDCONFIG_OUTPUT_BASE_DIR)/buildconfig.h
BUILDCONFIG_MK_FILE=$(BUILDCONFIG_OUTPUT_BASE_DIR)/buildconfig.mk
export BUILDCONFIG_HEANDER_FILE
export BUILDCONFIG_MK_FILE
BUILDCONFIG_LIBRARY_INCLUDE_DIR=$(SDK_PATH)/include

FIRMWAREID_OUTPUT_DIR=$(BUILDCONFIG_OUTPUT_BASE_DIR)
export FIRMWAREID_OUTPUT_DIR
IMAGE_BUILD_DIR=$(BUILD_DIR)/image-build
KEYS_HASH_FILE=$(IMAGE_BUILD_DIR)/key_hash_file
ATTACHED_INFO_FILE=$(IMAGE_BUILD_DIR)/attached_info.ini
SIGNATURE_MACHINE_MS=$(call qstrip,$(BR2_MS_SIGNATURE_IP)):$(call qstrip,$(BR2_MS_SIGNATURE_PORT))
SIGNATURE_MACHINE_MF=$(call qstrip,$(BR2_MF_SIGNATURE_IP)):$(call qstrip,$(BR2_MF_SIGNATURE_PORT))
SIGNATURE_TOOL=support/scripts/signature

#IMAGE_VERSION_FORMAT=$(shell echo "$(BR2_IMAGE_VERSION)" | awk -F. '{printf "%02d%02d%02d", $$1,$$2,$$3}')
IMAGE_VERSION_FORMAT=$(BR2_UPTS_VERSION)
IMAGE_VERSION_INT=$(shell echo "$(BR2_IMAGE_VERSION)" | awk -F. '{printf "0x%02d%02d%02d", $$1,$$2,$$3}')
FIRMWARE_VERSION="2.6-$(IMAGE_VERSION_FORMAT)-Secure"
WORKSPACE_VERSION_SVN=$(shell LC_ALL=C svn info $(WORKSPACE) 2>/dev/null | grep '^Last Changed Rev' | awk '{print $$NF}')
FIRMWARE_VERSION_SVN=$(shell LC_ALL=C svn info $(WORKSPACE)/secure/mh1902 2>/dev/null | grep '^Last Changed Rev' | awk '{print $$NF}')

SIGNATURE=$(TOPDIR)/support/scripts/signature -c $(call qstrip,$(BR2_MF_SIGNATURE_IP)):$(call qstrip,$(BR2_MF_SIGNATURE_PORT))
SIGNATURE_V2=$(TOPDIR)/support/scripts/signv2.sh $(TOPDIR)/support/scripts/signature \
	$(call qstrip,$(BR2_MF_SIGNATURE_IP)):$(call qstrip,$(BR2_MF_SIGNATURE_PORT)) AS0 

buildconfig:	
	@$(call MESSAGE,"Building buildconfig ...")
	test -f $(BUILDCONFIG_INPUT_CONFIG_FILE) || (echo "$(CONFIG_DIR)/.config file not exist" && exit 1)
	cat $(BUILDCONFIG_INPUT_CONFIG_FILE) > $(BUILDCONFIG_GEN_CONFIG_FILE)
	
	#add custom DEFINITION here or in Config.in
	echo "BR2_BUILDCONFIG_CFG_FIRMWARE_VERSION=\"$(FIRMWARE_VERSION)\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_IMAGE_VERSION=$(IMAGE_VERSION_INT)" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_IMAGE_VERSION_STRING=\"$(BR2_IMAGE_VERSION)\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_COMPILE_NAME=\"$(shell whoami)\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_COMPILE_TIME=\"$(shell date +'%Y-%m-%d %T')\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_COMPILE_SVN=\"$(WORKSPACE_VERSION_SVN)\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_FIRMWARE_SVN=\"$(FIRMWARE_VERSION_SVN)\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	echo "BR2_BUILDCONFIG_CFG_CUSTOMER_TYPE=\"$(BR2_CUSTOMER_TYPE)\"" >> $(BUILDCONFIG_GEN_CONFIG_FILE)
	$(call GENERATE_BUILDCONFIG,)


define GENERATE_BUILDCONFIG
	test -d $(BUILDCONFIG_OUTPUT_BASE_DIR) || mkdir -p $(BUILDCONFIG_OUTPUT_BASE_DIR)
	python $(BUILDCONFIG_SOURCE_CODE_DIR)/buildconfig.py -h $(BUILDCONFIG_GEN_CONFIG_FILE) $(BUILDCONFIG_HEANDER_FILE)
	python $(BUILDCONFIG_SOURCE_CODE_DIR)/buildconfig.py -mk $(BUILDCONFIG_GEN_CONFIG_FILE) $(BUILDCONFIG_MK_FILE)

	@$(if $(shell test -d $(BUILDCONFIG_LIBRARY_INCLUDE_DIR) && \
				 echo "EXSIT"), \
		echo "build_config library include dir existed", mkdir -p $(BUILDCONFIG_LIBRARY_INCLUDE_DIR))
	@cp $(BUILDCONFIG_HEANDER_FILE) $(BUILDCONFIG_LIBRARY_INCLUDE_DIR)
endef

firmwareid: firmware-id
	@echo "#ifndef __FIRMWARE_INFO_H__" > $(FIRMWAREID_OUTPUT_DIR)/$@.h
	@echo "#define __FIRMWARE_INFO_H__" >> $(FIRMWAREID_OUTPUT_DIR)/$@.h
	@echo "#define FIRMWAREID   \"`cat $(KEYS_HASH_FILE)`\"" >> $(FIRMWAREID_OUTPUT_DIR)/$@.h
	@echo "#endif" >> $(FIRMWAREID_OUTPUT_DIR)/$@.h

define create_attached_info
	@echo "[Attached Information]" > $(ATTACHED_INFO_FILE)
	@echo "Platform=SC6531" >> $(ATTACHED_INFO_FILE)
	@echo "Customer=$(BR2_CUSTOMER_TYPE)" >> $(ATTACHED_INFO_FILE)
	@echo "Build_Model=NEW7220" >> $(ATTACHED_INFO_FILE)
	@echo "HW_Version=V01" >> $(ATTACHED_INFO_FILE)
endef

# Get key from signature server
# Argument 1: key name
# Argument 2: signature server ip & port
# Argument 3: output path
define get_key
	@echo "Generate $(1).pem from $(2)"	
	@$(SIGNATURE_TOOL) -q -l -k $(1) -c $(2) -o $(3)/$(1).pem
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

firmware-info: keys-hash
	@echo "Making the information for image "
	@echo "$(IMAGE_BUILD_DIR)/image_info"
	@echo "0120" | xxd -r -plain > $(IMAGE_BUILD_DIR)/image_info
	@cat $(IMAGE_BUILD_DIR)/key_hash >> $(IMAGE_BUILD_DIR)/image_info
	@echo "0207" | xxd -r -plain >> $(IMAGE_BUILD_DIR)/image_info
	@echo -n "NEW7220" >> $(IMAGE_BUILD_DIR)/image_info
	@echo "002B" | xxd -r -plain >> $(IMAGE_BUILD_DIR)/image_info
	@echo -n "IMG:0001" >> $(IMAGE_BUILD_DIR)/image_info
