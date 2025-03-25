
TARGETS += library

ifeq ($(BR2_PACKAGE_LIBRARY),y)

LIBRARY_DIR=$(BUILD_DIR)/library
LIBRARY_SOURCE_PATH=$(call qstrip,$(BR2_LIBRARY_SOURCE_PATH))
LIBRARY_INSTALL_PATH=$(call qstrip,$(BR2_LIBRARY_INSTALL_PATH))
LIB_NDK_PATH=$(BR2_TOOLCHAIN_INSTALL_PATH)/ndk

LIBRARY_COMPILE_ORDER = syscall syscall-manage utility sysfs scpd nfc verify ped
LIBRARY_COMPILE_ORDER_LAST = barcode pos

LIBRARY_ALL_SUBDIRS:=$(shell test -e $(LIBRARY_SOURCE_PATH) && ls $(LIBRARY_SOURCE_PATH))
LIBRARY_ALL_SUBDIRS_WITH_ORDER:=$(LIBRARY_COMPILE_ORDER) \
                                $(filter-out $(LIBRARY_COMPILE_ORDER) $(LIBRARY_COMPILE_ORDER_LAST),$(LIBRARY_ALL_SUBDIRS)) \
                                $(LIBRARY_COMPILE_ORDER_LAST)
LIBRARY_SUBDIR_LIST:=$(filter $(LIBRARY_ALL_SUBDIRS),$(LIBRARY_ALL_SUBDIRS_WITH_ORDER))

LIBRARY_CONFIG_SUBDIRS = $(foreach f,$(LIBRARY_SUBDIR_LIST),$(if $(BR2_BUILDCONFIG_CONFIG_$(shell echo $f | tr a-z- A-Z_)),$(f),))

LIBRARY_SUBDIR_ENV=$(EXPORT_ENV)

LIBRARY_JOIN_LIST=$(patsubst %,library-%,$(LIBRARY_CONFIG_SUBDIRS))
LIBRARY_JOIN_LIST_CLEAN=$(patsubst %,%-clean,$(LIBRARY_JOIN_LIST))
LIBRARY_JOIN_LIST_INSTALL=$(patsubst %,%-install,$(LIBRARY_JOIN_LIST))

define ALONE_LIBRARY_BUILD
	@$(call MESSAGE,"Library $(1) building ...")
	$(Q)test -d $(LIBRARY_DIR)/$(1) || mkdir -p $(LIBRARY_DIR)/$(1)
	$(Q)$(TARGET_MAKE_ENV) $(LIBRARY_SUBDIR_ENV) $(MAKE) -C $(LIBRARY_SOURCE_PATH)/$(1) NDK_PATH=$(LIB_NDK_PATH) O=$(LIBRARY_DIR)/$(1) $(2)
endef

.library_related_dir: sdk
	@test -d $(SYSAPP_INSTALL_PATH) || mkdir -p $(SYSAPP_INSTALL_PATH)
	@test -d $(LIBRARY_DIR)         || mkdir -p $(LIBRARY_DIR)
	@test -d $(SDK_PATH)/lib        || mkdir -p $(SDK_PATH)/lib
	@test -d $(SDK_PATH)/include    || mkdir -p $(SDK_PATH)/include

library: $(LIBRARY_JOIN_LIST)

library-clean:
	rm -rf $(LIBRARY_DIR)

$(LIBRARY_JOIN_LIST): .library_related_dir
	$(call ALONE_LIBRARY_BUILD,$(patsubst library-%,%,$@),)

$(LIBRARY_JOIN_LIST_CLEAN):
	rm -rf $(LIBRARY_DIR)/$(patsubst library-%-clean,%,$(@))

library-pos: sysapp-manage

.PHONY: library library-clean

endif
