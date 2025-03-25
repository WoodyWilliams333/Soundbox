
TARGETS += sysapp

ifeq ($(BR2_PACKAGE_SYSAPP),y)

SYSAPP_DIR=$(BUILD_DIR)/sysapp
SYSAPP_SOURCE_PATH=$(call qstrip,$(BR2_SYSAPP_SOURCE_PATH))
SYSAPP_INSTALL_PATH=$(SYSTEM_DIR)/home/sbin
SYSAPP_NDK_PATH=$(BR2_TOOLCHAIN_INSTALL_PATH)/ndk
SYSAPP_SUBDIR_LIST=$(shell ls $(SYSAPP_SOURCE_PATH))
SYSAPP_CONFIG_SUBDIRS = $(foreach f,$(SYSAPP_SUBDIR_LIST),$(if $(BR2_CONFIG_SYSAPP_$(shell echo $f | tr a-z- A-Z_)),$(f),))

SYS_VERSION=$(call qstrip,$(BR2_IMAGE_VERSION))

SYSAPP_SUBDIR_ENV=$(EXPORT_ENV) 

SYSAPP_JOIN_LIST=$(patsubst %,sysapp-%,$(SYSAPP_CONFIG_SUBDIRS))
SYSAPP_JOIN_LIST_CLEAN=$(patsubst %,%-clean,$(SYSAPP_JOIN_LIST))
SYSAPP_JOIN_LIST_INSTALL=$(patsubst %,%-install,$(SYSAPP_JOIN_LIST))

define ALONE_SYSAPP_BUILD
	@$(call MESSAGE,"Sysapp $(1) building ...")
	$(Q)test -d $(SYSAPP_DIR)/$(1) || mkdir -p $(SYSAPP_DIR)/$(1)
	$(Q)$(TARGET_MAKE_ENV) $(SYSAPP_SUBDIR_ENV) $(MAKE) -C $(SYSAPP_SOURCE_PATH)/$(1) NDK_PATH=$(SYSAPP_NDK_PATH) O=$(SYSAPP_DIR)/$(1) $(2)
endef

.sysapp_related_dir:
	@test -d $(SYSAPP_INSTALL_PATH) || mkdir -p $(SYSAPP_INSTALL_PATH)
	@test -d $(SYSAPP_DIR) || mkdir -p $(SYSAPP_DIR)

sysapp: $(SYSAPP_JOIN_LIST)

sysapp-clean:
	rm -rf $(SYSAPP_DIR)

$(SYSAPP_JOIN_LIST): .sysapp_related_dir
	$(call ALONE_SYSAPP_BUILD,$(patsubst sysapp-%,%,$@),)

$(SYSAPP_JOIN_LIST_CLEAN):
	rm -rf $(SYSAPP_DIR)/$(patsubst sysapp-%-clean,%,$(@))
#	$(call ALONE_SYSAPP_BUILD,$(patsubst sysapp-%-clean,%,$(@)),clean)

# $(SYSAPP_JOIN_LIST_INSTALL):%-install:%
#	$(call ALONE_SYSAPP_BUILD,$(patsubst sysapp-%-install,%,$(@)),install)

.PHONY: sysapp sysapp-clean

endif
