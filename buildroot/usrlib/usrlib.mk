
TARGETS += usrlib

ifeq ($(BR2_PACKAGE_USER_LIBRARY),y)

USER_LIBRARY_DIR=$(BUILD_DIR)/usrlib
USER_LIBRARY_SOURCE_PATH=$(call qstrip,$(BR2_USER_LIBRARY_SOURCE_PATH))
USER_LIBRARY_INSTALL_PATH=$(call qstrip,$(BR2_USER_LIBRARY_INSTALL_PATH))
LIB_NDK_PATH=$(BR2_TOOLCHAIN_INSTALL_PATH)/ndk
USER_LIBRARY_SUBDIR_LIST= mercury wolfssl emv tms $(shell ls $(USER_LIBRARY_SOURCE_PATH) --hide=mercury --hide=wolfssl --hide=emv --hide=tms)

USER_LIBRARY_CONFIG_SUBDIRS = $(foreach f,$(USER_LIBRARY_SUBDIR_LIST),$(if $(BR2_CONFIG_USER_LIBRARY_$(shell echo $f | tr a-z- A-Z_)),$(f),))

USER_LIBRARY_SUBDIR_ENV=$(EXPORT_ENV)

USER_LIBRARY_JOIN_LIST=$(patsubst %,usrlib-%,$(USER_LIBRARY_CONFIG_SUBDIRS))
USER_LIBRARY_JOIN_LIST_CLEAN=$(patsubst %,%-clean,$(USER_LIBRARY_JOIN_LIST))
USER_LIBRARY_JOIN_LIST_INSTALL=$(patsubst %,%-install,$(USER_LIBRARY_JOIN_LIST))

define ALONE_USER_LIBRARY_BUILD
	@$(call MESSAGE,"Usrlib $(1) building ...")
	$(Q)test -d $(USER_LIBRARY_DIR)/$(1) || mkdir -p $(USER_LIBRARY_DIR)/$(1)
	$(Q)$(TARGET_MAKE_ENV) $(USER_LIBRARY_SUBDIR_ENV) $(MAKE) -C $(USER_LIBRARY_SOURCE_PATH)/$(1) NDK_PATH=$(LIB_NDK_PATH) O=$(USER_LIBRARY_DIR)/$(1) $(2)
endef

.usrlib_related_dir:
	@test -d $(SYSAPP_INSTALL_PATH) || mkdir -p $(SYSAPP_INSTALL_PATH)
	@test -d $(USER_LIBRARY_DIR)        || mkdir -p $(USER_LIBRARY_DIR)
	@test -d $(SDK_PATH)/usr/lib        || mkdir -p $(SDK_PATH)/usr/lib
	@test -d $(SDK_PATH)/usr/include    || mkdir -p $(SDK_PATH)/usr/include

usrlib: $(USER_LIBRARY_JOIN_LIST) .usrlib_related_dir

usrlib-clean:
	rm -rf $(USER_LIBRARY_DIR)

$(USER_LIBRARY_JOIN_LIST): .usrlib_related_dir
	$(call ALONE_USER_LIBRARY_BUILD,$(patsubst usrlib-%,%,$@),)

$(USER_LIBRARY_JOIN_LIST_CLEAN):
	rm -rf $(USER_LIBRARY_DIR)/$(patsubst usrlib-%-clean,%,$(@))

.PHONY: usrlib usrlib-clean

endif
