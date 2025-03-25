#应用编译说明#
#	应用库
#		1.lib-xxx编译老版的库，编译后生成目录为/toolchain/appsdk/lib/lib(include) 
#		2.lib-c-xxx编译新版的库，编译后生成目录为/toolchain/appsdk/lib-c/lib(include)
#		3.lib-c/libwent比较特殊，分两个版本：支持ssl和不支持ssl
#			lib-c-wnet编译不支持ssl
#			lib-c-wnet-ssl编译支持ssl(生成的库名为libwnetssl.a)
#			编译后生成目录都为/toolchain/appsdk/lib-c/lib(include)
#			注意由于make在编译未改动下，是不会重新编译文件的，因此单独编译这两个库前需要先lib-c-wnet-clean清除wnet库！	
# 	应用编译
#		app-xx编译应用即可

SHELL=/bin/bash

PRODUCT_NAME=new7220

TOPDIR=$(shell pwd)
TOOLCHAIN_PATH=$(TOPDIR)/toolchain
NDK_PATH=$(TOPDIR)/toolchain/ndk
SDK_PATH=$(TOPDIR)/toolchain/sdk/
APP_SDK_PATH=$(TOPDIR)/toolchain/app_sdk/
APP_C_SDK_PATH=$(TOPDIR)/toolchain/app_c_sdk/
TOOLS_PATH=$(TOPDIR)/toolchain/tools
BUILD_DIR=$(TOPDIR)/output/build
SYSTEM_DIR=$(TOPDIR)/output/system

#SDK_DOWNLOAD_URL="http://10.1.40.23/pub/sdk/$(PRODUCT_NAME)/lastest"
#BR2_TOOLCHAIN_URL="http://10.1.40.23/pub/toolchain/ndk/ndk-toolchains-all.tar.bz2"

NDK_CFLAGS="-fno-short-enums"
TARGET_MAKE_ENV=\
		CPU_ABI=armeabi-v7a-hard \
		NDK_PATH=$(NDK_PATH) \
		SDK_PATH=$(SDK_PATH) \
		APP_SDK_PATH=$(APP_SDK_PATH) \
		APP_C_SDK_PATH=$(APP_C_SDK_PATH) \
		TOOLS_PATH=$(TOOLS_PATH) \
		INSTALL_PATH=$(SYSTEM_DIR) \
		NDK_CFLAGS=$(NDK_CFLAGS)

help:

####### library targets
LIBRARY_DIR=$(BUILD_DIR)/lib
LIBRARY_SOURCE_PATH=$(TOPDIR)/lib
LIBRARY_C_DIR=$(BUILD_DIR)/lib-c
LIBRARY_SOURCE_C_PATH=$(TOPDIR)/lib-c
LIBRARY_SUBDIR_LIST= seos wolfssl $(shell ls $(LIBRARY_SOURCE_PATH) --hide=seos --hide=wolfssl) #Make sure the seos library is the first library to be compiled.
$(warning LIBRARY_SUBDIR_LIST= $(LIBRARY_SUBDIR_LIST))
LIBRARY_CONFIG_SUBDIR=$(LIBRARY_SUBDIR_LIST)
LIBRARY_C_SUBDIR_LIST= seos wolfssl $(shell ls $(LIBRARY_SOURCE_C_PATH) --hide=seos --hide=wolfssli) #Make sure the seos library is the first library to be compiled.
$(warning LIBRARY_C_SUBDIR_LIST= $(LIBRARY_C_SUBDIR_LIST))
LIBRARY_CONFIG_SUBDIR=$(LIBRARY_SUBDIR_LIST)
LIBRARY_C_CONFIG_SUBDIR=$(LIBRARY_C_SUBDIR_LIST)
LIBRARY_TARGETS=$(patsubst %,lib-%,$(LIBRARY_CONFIG_SUBDIR))
LIBRARY_TARGETS_CLEAN=$(patsubst %,lib-%-clean,$(LIBRARY_CONFIG_SUBDIR))
LIBRARY_TARGETS_C=$(patsubst %,lib-c-%,$(LIBRARY_C_CONFIG_SUBDIR))
LIBRARY_TARGETS_C_SSL=$(patsubst %,lib-c-%-ssl,$(LIBRARY_C_CONFIG_SUBDIR))
LIBRARY_TARGETS_C_CLEAN=$(patsubst %,lib-c-%-clean,$(LIBRARY_C_CONFIG_SUBDIR))
LIBRARY_TARGETS_C_SSL_CLEAN=$(patsubst %,lib-c-ssl-%-clean,$(LIBRARY_C_CONFIG_SUBDIR))
LIBRARY_UPTS_TARGETS=$(patsubst %,lib-upts-%,$(LIBRARY_CONFIG_SUBDIR))
LIBRARY_UPTS_TARGETS_CLEAN=$(patsubst %,lib-upts-%-clean,$(LIBRARY_CONFIG_SUBDIR))
LIBRARY_UPTS_FLAGS="-DCFG_UPTS_COMPLY"
LIBRARY_SSL_FLAGS="-DENABLE_SSL"
APP_WIRELESS_FLAG="-DCFG_4G_FLAG"
APP_8850_FLAG="-DCFG_8850_FLAG"

define ALONE_LIBRARY_BUILD
	@$(call MESSAGE, build library $(1))
	@test -d $(LIBRARY_DIR)/$(1) || mkdir -p $(LIBRARY_DIR)/$(1)
	@$(TARGET_MAKE_ENV) $(MAKE) --no-print-directory -C $(LIBRARY_SOURCE_PATH)/$(1) APP_WIRELESS_FLAG=$(APP_WIRELESS_FLAG) APP_WIRELESS_FLAG+=$(APP_8850_FLAG) O=$(LIBRARY_DIR)/$(1) $(2)
endef

define ALONE_LIBRARY_UPTS_BUILD
	@$(call MESSAGE, build library $(1) [UPTS version])
	@test -d $(LIBRARY_DIR)/$(1) || mkdir -p $(LIBRARY_DIR)/$(1)
	@$(TARGET_MAKE_ENV) $(MAKE) --no-print-directory -C $(LIBRARY_SOURCE_PATH)/$(1) LIBRARY_UPTS_FLAGS=$(LIBRARY_UPTS_FLAGS) APP_WIRELESS_FLAG=$(APP_WIRELESS_FLAG) APP_WIRELESS_FLAG+=$(APP_8850_FLAG) O=$(LIBRARY_DIR)/$(1) $(2)
endef

define ALONE_LIBRARY_C_BUILD
	@$(call MESSAGE, build library $(1) $(2))
	@test -d $(LIBRARY_C_DIR)/$(1) || mkdir -p $(LIBRARY_C_DIR)/$(1)
	@$(TARGET_MAKE_ENV) $(MAKE) --no-print-directory -C $(LIBRARY_SOURCE_C_PATH)/$(1) APP_WIRELESS_FLAG=$(APP_WIRELESS_FLAG) APP_WIRELESS_FLAG+=$(APP_8850_FLAG) O=$(LIBRARY_C_DIR)/$(1) $(2)
endef

define ALONE_LIBRARY_C_SSL_BUILD
	@$(call MESSAGE, build library $(1) $(2))
	@test -d $(LIBRARY_C_DIR)/$(1) || mkdir -p $(LIBRARY_C_DIR)/$(1)
	@$(TARGET_MAKE_ENV) $(MAKE) --no-print-directory -C $(LIBRARY_SOURCE_C_PATH)/$(1) LIBRARY_UPTS_FLAGS=$(LIBRARY_SSL_FLAGS) APP_WIRELESS_FLAG=$(APP_WIRELESS_FLAG) APP_WIRELESS_FLAG+=$(APP_8850_FLAG) O=$(LIBRARY_C_DIR)/$(1) $(2)
endef

info:
	@echo LIBRARY_TARGETS=$(LIBRARY_TARGETS)
	@echo LIBRARY_TARGETS_CLEAN=$(LIBRARY_TARGETS_CLEAN)
	@echo LIBRARY_UPTS_TARGETS=$(LIBRARY_UPTS_TARGETS)
	@echo LIBRARY_UPTS_TARGETS_CLEAN=$(LIBRARY_UPTS_TARGETS_CLEAN)
	@echo LIBRARY_TARGETS_C=$(LIBRARY_TARGETS_C)
	@echo LIBRARY_TARGETS_C_CLEAN=$(LIBRARY_TARGETS_C_CLEAN)
	
.applib-dirs:
	test -e $(APP_SDK_PATH) || mkdir $(APP_SDK_PATH)
	test -e $(APP_SDK_PATH)/lib || mkdir $(APP_SDK_PATH)/lib
	test -e $(APP_SDK_PATH)/include || mkdir $(APP_SDK_PATH)/include
	test -e $(APP_C_SDK_PATH) || mkdir $(APP_C_SDK_PATH)
	test -e $(APP_C_SDK_PATH)/lib || mkdir $(APP_C_SDK_PATH)/lib
	test -e $(APP_C_SDK_PATH)/include || mkdir $(APP_C_SDK_PATH)/include
	
lib: .applib-dirs $(LIBRARY_TARGETS)

lib-c: .applib-dirs $(LIBRARY_TARGETS_C)
	
$(LIBRARY_TARGETS): .dirs
	$(call ALONE_LIBRARY_BUILD,$(patsubst lib-%,%,$(@)),)

$(LIBRARY_TARGETS_CLEAN):
	rm -rf $(LIBRARY_DIR)/$(patsubst lib-%-clean,%,$(@))

$(LIBRARY_TARGETS_C): .dirs
	@echo "LIBRARY_TARGETS_C"
	$(call ALONE_LIBRARY_C_BUILD,$(patsubst lib-c-%,%,$(@)),)

$(LIBRARY_TARGETS_C_SSL): .dirs
	@echo "LIBRARY_TARGETS_C_SSL"
	$(call ALONE_LIBRARY_C_SSL_BUILD,$(patsubst lib-c-%-ssl,%,$(@)),)

$(LIBRARY_TARGETS_C_CLEAN):
	rm -rf $(LIBRARY_C_DIR)/$(patsubst lib-c-%-clean,%,$(@))
	
$(LIBRARY_UPTS_TARGETS): .dirs
	$(call ALONE_LIBRARY_UPTS_BUILD,$(patsubst lib-upts-%,%,$(@)),)

$(LIBRARY_UPTS_TARGETS_CLEAN):
	rm -rf $(LIBRARY_DIR)/$(patsubst lib-upts-%-clean,%,$(@))

####### app targets
USRAPP_DIR=$(BUILD_DIR)/app
USRAPP_SOURCE_PATH=$(TOPDIR)/app
USRAPP_SUBDIR_LIST=$(shell ls $(USRAPP_SOURCE_PATH))
USRAPP_CONFIG_LIST=$(USRAPP_SUBDIR_LIST)
USRAPP_TARGETS=$(patsubst %,app-%,$(USRAPP_CONFIG_LIST))
USRAPP_TARGETS_CLEAN=$(patsubst %,app-%-clean,$(USRAPP_CONFIG_LIST))
USRAPP_MAKE_DIR=make_8850

export LC_ALL=C

define ALONE_USRAPP_BUILD
	@$(call MESSAGE, build application $(1))
#	test ! -f $(USRAPP_SOURCE_PATH)/$(1)/Makefile || rm -rf $(USRAPP_SOURCE_PATH)/$(1)/Makefile
#	test ! -f $(USRAPP_SOURCE_PATH)/$(1)/gcc_application.ld || rm -rf $(USRAPP_SOURCE_PATH)/$(1)/gcc_application.ld
#	test ! -f $(USRAPP_SOURCE_PATH)/$(1)/Android.mk || rm -rf $(USRAPP_SOURCE_PATH)/$(1)/Android.mk
#	@cp $(USRAPP_SOURCE_PATH)/$(1)/$(USRAPP_MAKE_DIR)/* $(USRAPP_SOURCE_PATH)/$(1)/
	@$(TARGET_MAKE_ENV) $(MAKE) --no-print-directory -C $(USRAPP_SOURCE_PATH)/$(1) APP_WIRELESS_FLAG=$(APP_WIRELESS_FLAG) APP_WIRELESS_FLAG+=$(APP_8850_FLAG) O=$(USRAPP_DIR)/$(1) $(2)
endef

app: $(USRAPP_TARGETS)

$(USRAPP_TARGETS): .dirs
	$(call ALONE_USRAPP_BUILD,$(patsubst app-%,%,$(@)),)

$(USRAPP_TARGETS_CLEAN):
	rm -rf $(USRAPP_DIR)/$(patsubst app-%-clean,%,$(@))

####### prepare SDK & TOOLCHAIN
toolchain:
	@echo "toolchain building"
	#@mkdir -p $(TOOLCHAIN_PATH)
	test -e $(TOOLCHAIN_PATH)/.ndk_download || \
	#(wget --output-document=$(TOOLCHAIN_PATH)/toolchain-cross.tar.bz2 $(BR2_TOOLCHAIN_URL) && \
		tar --strip-components=0 -C $(TOOLCHAIN_PATH) -xf $(TOOLCHAIN_PATH)/toolchain-cross.tar.bz2 && \
		touch $(TOOLCHAIN_PATH)/.ndk_download )
	#rm -rf $(TOOLCHAIN_PATH)/toolchain-cross.tar.bz2

sdk-update: 
	#@rm -rf $(TOOLCHAIN_PATH)/sdk-lastest.tar.bz2
	#wget --output-document=$(TOOLCHAIN_PATH)/sdk-lastest.tar.bz2 $(SDK_DOWNLOAD_URL)
	#@rm -rf $(SDK_PATH)
	#@mkdir -p $(SDK_PATH)
	#tar -C $(SDK_PATH) -xf $(TOOLCHAIN_PATH)/sdk-lastest.tar.bz2
	#@rm -rf $(TOOLCHAIN_PATH)/sdk-lastest.tar.bz2

sdk: toolchain sdk-update
	@echo ""
	@echo "successful"
	@echo ""

####### the whole target
all: lib app

all-c: lib-c app

.dirs:
	@test -d $(SYSTEM_DIR) || mkdir -p $(SYSTEM_DIR)

lib-clean:
	rm -rf $(LIBRARY_DIR)

lib-c-clean:
	rm -rf $(LIBRARY_C_DIR)
	
app-clean:
	rm -rf $(USRAPP_DIR)	
	
clean:
	rm -rf $(TOPDIR)/output
	
help:
	@echo -e "Usage:"
	@echo -e "  sdk\t\t\t -download Toolchain and the lastest SDK package"
	@$(foreach t,$(LIBRARY_TARGETS),echo -e "  $(t)\t\t -build library $(patsubst lib-%,%,$(t))" && ) echo -n ""
	@$(foreach t,$(LIBRARY_UPTS_TARGETS),echo -e "  $(t)\t\t -build (UPTS) library $(patsubst lib-upts-%,%,$(t))" && ) echo -n ""
	@$(foreach t,$(LIBRARY_TARGETS_C),echo -e "  $(t)\t\t -build library $(patsubst lib-c-%,%,$(t))" && ) echo -n ""
	@$(foreach t,$(USRAPP_TARGETS),echo -e "  $(t)\t\t -build application $(patsubst app-%,%,$(t))" && ) echo -n ""
	@echo -e "  clean\t\t\t -make clean all libraries and applications"
	@echo -e "  all\t\t\t -make all libraries and applications"
	@echo ""
	
####### utils function
MESSAGE     = echo "$(TERM_BOLD)>>> $(1)$(TERM_RESET)"
TERM_BOLD  := $(shell tput smso)
TERM_RESET := $(shell tput rmso)

PHONY: all all-c clean lib-clean lib-c-clean app-clean help app lib lib-c lib-c-ssl sdk sdk-update toolchain info .applib-dirs .dirs
