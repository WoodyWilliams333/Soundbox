

PRE_KCONFIG_TARGET+=.tools-pre-kconfig

# Do not use kconfig variable
.tools-pre-kconfig:
	$(TOPDIR)/support/scripts/wrapper.sh BR2_CONFIG_TOOLS_ $(WORKSPACE)/host $(WRAPPER_DIR)/tools_wrapper.in 
