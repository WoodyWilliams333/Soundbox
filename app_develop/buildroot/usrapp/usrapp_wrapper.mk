

PRE_KCONFIG_TARGET+=.usrapp-pre-kconfig

# Do not use kconfig variable
.usrapp-pre-kconfig:
	$(TOPDIR)/support/scripts/wrapper.sh BR2_CONFIG_USRAPP_ $(WORKSPACE)/usrapp $(WRAPPER_DIR)/usrapp_wrapper.in 
