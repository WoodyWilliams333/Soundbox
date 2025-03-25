
TARGETS += usrapp

ifeq ($(BR2_PACKAGE_USRAPP),y)


USRAPP_DIR=$(BUILD_DIR)/usrapp
USRAPP_SOURCE_PATH=$(call qstrip,$(BR2_USRAPP_SOURCE_PATH))
USRAPP_INSTALL_PATH=$(SYSTEM_DIR)/home/user0
USRAPP_NDK_PATH=$(BR2_TOOLCHAIN_INSTALL_PATH)/ndk
USRAPP_SUBDIR_LIST=$(shell ls $(USRAPP_SOURCE_PATH))
USRAPP_CONFIG_SUBDIRS = $(foreach f,$(USRAPP_SUBDIR_LIST),$(if $(BR2_CONFIG_USRAPP_$(shell echo $f | tr a-z- A-Z_)),$(f),))
	   
USRAPP_SUBDIR_ENV=$(EXPORT_ENV)

USRAPP_JOIN_LIST=$(patsubst %,usrapp-%,$(USRAPP_CONFIG_SUBDIRS))
USRAPP_JOIN_LIST_CLEAN=$(patsubst %,%-clean,$(USRAPP_JOIN_LIST))
USRAPP_JOIN_LIST_INSTALL=$(patsubst %,%-install,$(USRAPP_JOIN_LIST))

define ALONE_USRAPP_BUILD
	@$(call MESSAGE,"Usrapp $(1) building ...")
	$(Q)test -d $(USRAPP_DIR)/$(1) || mkdir -p $(USRAPP_DIR)/$(1)
	$(Q)$(TARGET_MAKE_ENV) $(USRAPP_SUBDIR_ENV) $(MAKE) -C $(USRAPP_SOURCE_PATH)/$(1) NDK_PATH=$(USRAPP_NDK_PATH) O=$(USRAPP_DIR)/$(1) $(2)
endef

.usrapp_related_dir:
	@test -d $(USRAPP_INSTALL_PATH) || mkdir -p $(USRAPP_INSTALL_PATH)
	@test -d $(USRAPP_DIR) || mkdir -p $(USRAPP_DIR)

usrapp: $(USRAPP_JOIN_LIST)

usrapp-clean:
	rm -rf $(USRAPP_DIR)

$(USRAPP_JOIN_LIST): .usrapp_related_dir
	$(call ALONE_USRAPP_BUILD,$(patsubst usrapp-%,%,$@),)

$(USRAPP_JOIN_LIST_CLEAN):
	rm -rf $(USRAPP_DIR)/$(patsubst usrapp-%-clean,%,$(@))

.PHONY: usrapp usrapp-clean

endif
