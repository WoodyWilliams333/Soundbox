

PRE_KCONFIG_TARGET+=.firmware-pre-kconfig

# Do not use kconfig variable
.firmware-pre-kconfig:
	$(TOPDIR)/support/scripts/wrapper.sh BR2_CONFIG_FIRMWARE_ $(WORKSPACE)/secure $(WRAPPER_DIR)/firmware_wrapper.in
