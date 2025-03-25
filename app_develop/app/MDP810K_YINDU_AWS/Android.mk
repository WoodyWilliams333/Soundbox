
LOCAL_PATH := $(call my-dir)

include $(BUILDCONFIG_MK_FILE)

include $(CLEAR_VARS)
LOCAL_MODULE := $(MODULE_NAME)
LOCAL_LDFLAGS_LIB = -lsyscall  -Wl,--whole-archive -lwnet -Wl,--no-whole-archive  -lzint -lseos -lposts -lnptms -lwolfssl -lpahomqtt -lsysupdate -lgzip -Wl,--whole-archive  -lpos  -Wl,--no-whole-archive  
LOCAL_LDFLAGS_LIB += -L$(LOCAL_PATH)/lib/

LOCAL_SRC_FILES := $(call all-c-files-under,lib)
LOCAL_SRC_FILES += $(call all-c-files-under,src) 

#add your source path in C-include path
USRAPP_INCDIR := $(shell find $(LOCAL_PATH) -type d)
NDK_CFLAGS += $(patsubst %,-I%,$(USRAPP_INCDIR))


#add include conf.h
LOCAL_CFLAGS 	 += -include $(LOCAL_PATH)/config/conf.h

LOCAL_C_INCLUDES += $(SDK_PATH)/include
LOCAL_C_INCLUDES += $(APP_C_SDK_PATH)/include
LOCAL_C_INCLUDES += $(APP_C_SDK_PATH)/newemv/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/src/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include/
LOCAL_C_INCLUDES += $(USRAPP_INCDIR)
LOCAL_CFLAGS  += $(NDK_CFLAGS) -DCFG_APP_NAME=\"$(MODULE_NAME)\" -DCFG_APP_PATH=\"/home/user0/$(MODULE_NAME)/\" -DPOSIX_INTERFACE_OK
LOCAL_CFLAGS  += -DCFG_DEVELOPMENT_TEST
#LOCAL_CFLAGS  += -DCFG_LOGGER_ON
#LOCAL_CFLAGS  += -DCFG_EMVCL_ON
LOCAL_CFLAGS  += -DOFFLINE_DEMO
LOCAL_CFLAGS += -DDYNAMICPARAM
LOCAL_CFLAGS += -DNEW6260
LOCAL_CFLAGS  += $(APP_WIRELESS_FLAG)

LOCAL_SRC_FILES += $(SDK_PATH)/include/finfo.c
LOCAL_LDFLAGS += -nostartfiles -Wl,--build-id=none,--cref,--no-warn-mismatch
LOCAL_LDFLAGS += -Wl,-Map="$(NDK_OUT)/local/$(APP_ABI)/$(LOCAL_MODULE).map"
LOCAL_LDFLAGS += -T "$(LOCAL_PATH)/gcc_application.ld"
LOCAL_LDFLAGS += -L"$(SDK_PATH)/lib" -L"$(APP_C_SDK_PATH)/lib" -L"$(APP_C_SDK_PATH)/newemv/lib" -Wl,--whole-archive $(LOCAL_LDFLAGS_LIB) -Wl,--no-whole-archive

include $(BUILD_EXECUTABLE_BINARY)
