

PRE_KCONFIG_TARGET+=.library-pre-kconfig

# Do not use kconfig variable
.library-pre-kconfig:
	$(TOPDIR)/support/scripts/wrapper.sh BR2_BUILDCONFIG_CONFIG_ $(WORKSPACE)/library $(WRAPPER_DIR)/library_wrapper.in 
