

PRE_KCONFIG_TARGET+=.usrlib-pre-kconfig

# Do not use kconfig variable
.usrlib-pre-kconfig:
	$(TOPDIR)/support/scripts/wrapper.sh BR2_CONFIG_USER_LIBRARY_ $(WORKSPACE)/usrlib $(WRAPPER_DIR)/usrlib_wrapper.in 
