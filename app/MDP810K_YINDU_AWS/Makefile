
TARGET = HindiAws
DISPNAME = HindiAws

#CPU_ABI ?= armelf
CPU_ABI ?= armeabi-v7a-hard
O ?= ../output/$(TARGET)
NDK_PATH ?= ../../../app_develop/toolchain/ndk

ECHO ?= echo
#OBJDUMP ?= $(NDK_PATH)/toolchains/arm-unknown-eabi-4.9.4/prebuilt/linux-x86/bin/arm-unknown-eabi-objdump
OBJDUMP ?= $(NDK_PATH)/toolchains/arm-none-eabi-hf7.2.1/prebuilt/linux-x86/bin/arm-none-eabi-objdump
ifeq ($(V), 1)
Q ?= 
else
Q ?= @
endif
CUR_YEAR=$(shell date +%Y)
EXP_YEAR_BEFORE=$(shell expr $(CUR_YEAR) - 20)
EXP_YEAR=$(shell expr $(CUR_YEAR) + 20)
MONTH=$(shell date +%m)
DAY=$(shell date +%d)
CURRENT_TIME=$(EXP_YEAR_BEFORE)$(MONTH)$(DAY)
EXPIRED_TIME=$(EXP_YEAR)$(MONTH)$(DAY)

all: 
	$(NDK_PATH)/ndk-build $(NDK_BUILD_FLAGS) APP_ABI=$(CPU_ABI) NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=./Android.mk NDK_OUT=$(O)/obj NDK_LIBS_OUT=$(O)/libs \
		SDK_PATH=$(SDK_PATH) NDK_CFLAGS="$(NDK_CFLAGS)" APP_WIRELESS_FLAG="$(APP_WIRELESS_FLAG)" MODULE_NAME=$(TARGET)
	$(Q)mv $(O)/obj/local/$(CPU_ABI)/$(TARGET) $(O)/obj/local/$(CPU_ABI)/$(TARGET).elf
	$(Q)$(OBJDUMP) -l -x -d "$(O)/obj/local/$(CPU_ABI)/$(TARGET).elf" > $(O)/obj/local/$(CPU_ABI)/$(TARGET).dmp
	$(Q)$(TOOLS_PATH)/fixsize -a $(DISPNAME) $(O)/obj/local/$(CPU_ABI)/$(TARGET).bin	
	
	test -d $(INSTALL_PATH) || mkdir -p $(INSTALL_PATH)
	cp -dprf $(O)/obj/local/$(CPU_ABI)/$(TARGET).bin $(INSTALL_PATH) 

	@$(ECHO) "APP_WIRELESS_FLAG : $(APP_WIRELESS_FLAG)"
	@$(ECHO) ""
	@$(ECHO) "+---------------------------------------------------"
	@$(ECHO) "|"
	@$(ECHO) "|   Finished building target: $(TARGET).bin"
	@$(ECHO) "|"
	@$(ECHO) "+---------------------------------------------------"
	@$(ECHO) ""

clean:
	rm -rf $(O)
