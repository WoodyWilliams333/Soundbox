

PRE_KCONFIG_TARGET+=.prebuilt-pre-kconfig

# Do not use kconfig variable
.prebuilt-pre-kconfig:
	$(TOPDIR)/support/scripts/wrapper.sh BR2_CONFIG_PREBUILT_ $(WORKSPACE)/prebuilt $(WRAPPER_DIR)/prebuilt_wrapper.in 
