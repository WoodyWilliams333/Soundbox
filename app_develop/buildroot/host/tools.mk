
TARGETS += tools

ifeq ($(BR2_PACKAGE_TOOLS),y)

TOOLS_DIR=$(BUILD_DIR)/host
TOOLS_SOURCE_PATH=$(call qstrip,$(BR2_TOOLS_SOURCE_PATH))
TOOLS_INSTALL_PATH=$(call qstrip,$(BR2_TOOLS_INSTALL_PATH))
TOOLS_NDK_PATH=$(BR2_TOOLCHAIN_INSTALL_PATH)/ndk

TOOLS_SUBDIR_LIST=$(shell ls $(TOOLS_SOURCE_PATH))
TOOLS_CONFIG_SUBDIRS = $(foreach f,$(TOOLS_SUBDIR_LIST),$(if $(BR2_CONFIG_TOOLS_$(shell echo $f | tr a-z- A-Z_)),$(f),))

TOOLS_SUBDIR_ENV=SYSAPP_INSTALL_PATH=$(SYSAPP_INSTALL_PATH) \
		   LIBRARY_INSTALL_PATH=$(LIBRARY_INSTALL_PATH) \
                   SYSAPP_INSTALL_PATH=$(SYSAPP_INSTALL_PATH) \
                   FIRMWARE_INSTALL_PATH=$(FIRMWARE_INSTALL_PATH) \
                   TOOLS_INSTALL_PATH=$(TOOLS_INSTALL_PATH) \
                   CROSS_COMPILE=$(TARGET_CROSS) \
                   SDK_INSTALL_PATH=$(SDK_PATH) \
		   SYSTEM_PATH=$(SYSTEM_DIR) \
		   RECOVERY_DIR=$(RECOVERY_DIR) \
		   NDK_BUILD_FLAGS="-j$(PARALLEL_JOBS)"


TOOLS_JOIN_LIST=$(patsubst %,tools-%,$(TOOLS_CONFIG_SUBDIRS))
TOOLS_JOIN_LIST_CLEAN=$(patsubst %,%-clean,$(TOOLS_JOIN_LIST))
TOOLS_JOIN_LIST_INSTALL=$(patsubst %,%-install,$(TOOLS_JOIN_LIST))

define ALONE_TOOLS_BUILD
	@$(call MESSAGE,"Host tool $(1) building ...")
	$(Q)test -d $(TOOLS_DIR)/$(1) || mkdir -p $(TOOLS_DIR)/$(1)
	$(Q)$(TARGET_MAKE_ENV) $(TOOLS_SUBDIR_ENV) $(MAKE) -C $(TOOLS_SOURCE_PATH)/$(1) NDK_PATH=$(TOOLS_NDK_PATH) O=$(TOOLS_DIR)/$(1) $(2)
endef

.tools_related_dir:
	@test -d $(TOOLS_INSTALL_PATH) || mkdir -p $(TOOLS_INSTALL_PATH)
	@test -d $(TOOLS_DIR) || mkdir -p $(TOOLS_DIR)

host tools: .tools_related_dir
	@test -d $(TOOLS_DIR) || mkdir -p $(TOOLS_DIR)
	$(foreach d,$(TOOLS_CONFIG_SUBDIRS),$(call ALONE_TOOLS_BUILD,$(d),)$(sep))

host-clean tools-clean:
	rm -rf $(TOOLS_DIR)

$(TOOLS_JOIN_LIST): .tools_related_dir
	$(call ALONE_TOOLS_BUILD,$(patsubst tools-%,%,$@),)

$(TOOLS_JOIN_LIST_CLEAN):
	rm -rf $(TOOLS_DIR)/$(patsubst tools-%-clean,%,$(@))

.PHONY: host host-clean tools tools-clean

endif
