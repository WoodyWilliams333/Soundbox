
TARGETS += sdk
TARGETS-release += sdk-release

SDK_PATH=$(BASE_DIR)/sdk
SDK_USER_PATH=$(SDK_PATH)/usr
SDK_BUILD_DIR=$(BUILD_DIR)/sdk-build
SDK_UPLOAD_DEST="10.1.40.23:/opt/www/pub/sdk/$(PRODUCT_NAME)"

PRODUCT_NAME_UPPER=$(shell echo $(PRODUCT_NAME) | tr a-z- A-Z_)

.PHONY: sdk sdk-clean

# link script for app
SYSAPP_EXEC_BASE=-DTEXT_BASE=0x00260000 -DDATA_BASE=0x04314000 -DTEXT_SIZE=0x000a0000 -DDATA_SIZE=0x00020000
USRAPP_EXEC_BASE=-DTEXT_BASE=0x00300000 -DDATA_BASE=0x04334000 -DTEXT_SIZE=0x00100000 -DDATA_SIZE=0x000a0000 

.ldscript: .sdk-dir
	@test -f $(SDK_USER_PATH)/lib/gcc_application.ld || echo "generate gcc_application.lds & finfo.c"
	@test -f $(SDK_PATH)/lib/gcc_application.ld || \
		cpp -Wp,-P $(SYSAPP_EXEC_BASE) support/ldscript/gcc_application.lds $(SDK_PATH)/lib/gcc_application.ld
	@test -f $(SDK_USER_PATH)/lib/gcc_application.ld || \
		cpp -Wp,-P $(USRAPP_EXEC_BASE) support/ldscript/gcc_application.lds $(SDK_USER_PATH)/lib/gcc_application.ld
	@test -f $(SDK_PATH)/include/finfo.c || sed \ 's/TEXT_BASE/0x00260000/g;s/DATA_BASE/0x04314000/g;s/TEXT_SIZE/0x000a0000/g;s/DATA_SIZE/0x00020000/g;s/CFG_MAIN_STACK_SIZE/8*1024/g;s/CFG_APP_TYPE/0x01010101/g;' support/ldscript/finfo.c > $(SDK_PATH)/include/finfo.c
	@test -f $(SDK_USER_PATH)/include/finfo.c || sed \ 's/TEXT_BASE/0x00300000/g;s/DATA_BASE/0x04334000/g;s/TEXT_SIZE/0x00100000/g;s/DATA_SIZE/0x000a0000/g;s/CFG_MAIN_STACK_SIZE/32*1024/g;s/CFG_APP_TYPE/0x02020202/g;' support/ldscript/finfo.c > $(SDK_USER_PATH)/include/finfo.c

.sdk-dir:
	@test -e $(SDK_PATH)/lib     || mkdir -p $(SDK_PATH)/lib
	@test -e $(SDK_PATH)/include || mkdir -p $(SDK_PATH)/include
	@test -e $(SDK_USER_PATH)/lib     || mkdir -p $(SDK_USER_PATH)/lib
	@test -e $(SDK_USER_PATH)/include || mkdir -p $(SDK_USER_PATH)/include
	@test -e $(SDK_BUILD_DIR) || mkdir -p $(SDK_BUILD_DIR)
	
sdk: .sdk-dir .ldscript

sdk-clean:
	rm -rf $(SDK_PATH) $(SDK_USER_PATH) $(SDK_TEMP_DIR) 
	
sdk-doc: sdk
	@echo "create sdk"
	@rm -rf $(SDK_BUILD_DIR)/sdk
	@cp -rf $(SDK_USER_PATH) $(SDK_BUILD_DIR)/sdk
	@echo "translate header files from UTF-8 to GB18030"
	@cd $(SDK_USER_PATH)/include; \
		for file in `find . -type f -name "*.h"` ; \
		do iconv -s -f UTF-8 -t GB18030 $$file -o $(SDK_BUILD_DIR)/sdk/include/$$file $(if $(Q),>/dev/null 2>&1,)  \
			|| cp -f $$file $(SDK_BUILD_DIR)/sdk/include/$$file; \
		done
	@echo "doxygen to generate sdk doc"
	@cp -f $(TOPDIR)/sdk/default/Doxyfile $(SDK_BUILD_DIR)/sdk/include/Doxyfile
	@sed -i "/PROJECT_NAME/s/=.*/= $(PRODUCT_NAME_UPPER)/" $(SDK_BUILD_DIR)/sdk/include/Doxyfile
	@sed -i "/PROJECT_NUMBER/s/=.*/= $(BR2_IMAGE_VERSION)/" $(SDK_BUILD_DIR)/sdk/include/Doxyfile
	@cd $(SDK_BUILD_DIR)/sdk/include; doxygen $(if $(Q),>/dev/null 2>&1,)
	@rm -rf $(SDK_BUILD_DIR)/sdk/doc/latex $(SDK_BUILD_DIR)/sdk/include/Doxyfile
	@echo -e '<script language="javascript" type="text/javascript">\n window.location.href="html/index.html";\n</script>' > $(SDK_BUILD_DIR)/sdk/doc/manual.html

sdk-release: sdk-doc
	@echo "generate sdk.tar.bz2"
	@cd $(SDK_BUILD_DIR)/sdk; tar jcf $(BINARIES_DIR)/$(PRODUCT_NAME)-sdk-$(BR2_IMAGE_VERSION).tar.bz2 * 

sdk-upload: sdk-release
	@rm -rf $(SDK_BUILD_DIR)/upload
	@mkdir -p $(SDK_BUILD_DIR)/upload
	cp $(BINARIES_DIR)/$(PRODUCT_NAME)-sdk-$(BR2_IMAGE_VERSION).tar.bz2 $(SDK_BUILD_DIR)/upload
	cp $(BINARIES_DIR)/$(PRODUCT_NAME)-sdk-$(BR2_IMAGE_VERSION).tar.bz2 $(SDK_BUILD_DIR)/upload/lastest
	scp -r $(SDK_BUILD_DIR)/upload/. $(SDK_UPLOAD_DEST)
	