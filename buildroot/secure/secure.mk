

TARGETS += sp

.PHONY: sp sp-clean

BR2_SIGNATURE_MACHINE=$(call qstrip,$(BR2_MF_SIGNATURE_IP))
BR2_SIGNATURE_PORT=$(call qstrip,$(BR2_MF_SIGNATURE_PORT))
BR2_SBI_SIGNATURE_MACHINE=$(call qstrip,$(BR2_MS_SIGNATURE_IP))
BR2_SBI_SIGNATURE_PORT=$(call qstrip,$(BR2_MS_SIGNATURE_PORT))

ifeq ($(BR2_MH190X_PROCESSOR),y)
sp: sp-mh-boot sp-mh-kernel
	@echo "============================="
	@echo "build sp images successfullly"
	@echo "============================="

sp-clean: sp-mh-clean

include secure/mh1902/mh1902.mk
endif

ifeq ($(BR2_CCORE_PROCESSOR),y)
sp: sp-ccore
        
sp-clean: sp-ccore-clean
include secure/ccore/ccore.mk
endif

