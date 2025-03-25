TARGETS += image image-font image-factory $(TARGETS-release)

IMAGE_NAME=$(call qstrip,$(BR2_IMAGE_NAME))
IMAGE_BUILD_DIR=$(BUILD_DIR)/image-build
MKFW=$(TOOLS_INSTALL_PATH)/mkfirmware
MKFS=$(TOOLS_INSTALL_PATH)/mkfatfs

.PHONY: image image-clean 

image-font:
	mkdir -p $(IMAGE_BUILD_DIR) $(BINARIES_DIR)
	@rm -rf $(IMAGE_BUILD_DIR)/temp.img
	cd $(SYSTEM_DIR)/home; find user0/fonts -type f | xargs -i $(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t data -f {} -p /home/{}
	@cat $(IMAGE_BUILD_DIR)/image_info >> $(IMAGE_BUILD_DIR)/temp.img
	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
		-f $(IMAGE_BUILD_DIR)/temp.img -o $(BINARIES_DIR)/fonts.img

image-manage:	
	@rm -rf $(IMAGE_BUILD_DIR)/temp.img
	@if [ -f $(SYSTEM_DIR)/home/sbin/manage.bin ]; then \
		$(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t manage -f $(SYSTEM_DIR)/home/sbin/manage.bin -p /home/sbin/manage.bin; fi
	@cat $(IMAGE_BUILD_DIR)/image_info >> $(IMAGE_BUILD_DIR)/temp.img
	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
		-f $(IMAGE_BUILD_DIR)/temp.img -o $(BINARIES_DIR)/$(IMAGE_NAME)

image-download:	
	@rm -rf $(IMAGE_BUILD_DIR)/temp.img
	@if [ -f $(SYSTEM_DIR)/home/sbin/download.bin ]; then \
		$(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t data -f $(SYSTEM_DIR)/home/sbin/download.bin -p /home/sbin/download.bin; fi
	@cat $(IMAGE_BUILD_DIR)/image_info >> $(IMAGE_BUILD_DIR)/temp.img
	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
		-f $(IMAGE_BUILD_DIR)/temp.img -o $(BINARIES_DIR)/$(IMAGE_NAME)

image-sp:	
	@rm -rf $(IMAGE_BUILD_DIR)/temp.img
	@cd $(SYSTEM_DIR)/home; find sp -type f | xargs -i $(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t sp -f {} -p /home/{}
	@cat $(IMAGE_BUILD_DIR)/image_info >> $(IMAGE_BUILD_DIR)/temp.img
	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
		-f $(IMAGE_BUILD_DIR)/temp.img -o $(BINARIES_DIR)/$(IMAGE_NAME)

image-wifi:	
	@rm -rf $(IMAGE_BUILD_DIR)/temp.img
	@cd $(SYSTEM_DIR)/home; find wifi -type f | xargs -i $(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t wifi -f {} -p /home/{}
	@cat $(IMAGE_BUILD_DIR)/image_info >> $(IMAGE_BUILD_DIR)/temp.img
	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
		-f $(IMAGE_BUILD_DIR)/temp.img -o $(BINARIES_DIR)/$(IMAGE_NAME)
		
image:
	mkdir -p $(IMAGE_BUILD_DIR) $(BINARIES_DIR)
	@rm -rf $(IMAGE_BUILD_DIR)/temp.img
	@cd $(SYSTEM_DIR)/home; find sp -type f | xargs -i $(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t sp -f {} -p /home/{}
	@cd $(SYSTEM_DIR)/home; find wifi -type f | xargs -i $(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t wifi -f {} -p /home/{}
	@if [ -f $(SYSTEM_DIR)/home/sbin/download.bin ]; then \
		$(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t data -f $(SYSTEM_DIR)/home/sbin/download.bin -p /home/sbin/download.bin; fi
	@if [ -f $(SYSTEM_DIR)/home/sbin/keyinjec.bin ]; then \
		$(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t data -f $(SYSTEM_DIR)/home/sbin/keyinjec.bin -p /home/sbin/keyinjec.bin; fi
	@if [ -f $(SYSTEM_DIR)/home/sbin/manage.bin ]; then \
		$(MKFW) -o $(IMAGE_BUILD_DIR)/temp.img -t manage -f $(SYSTEM_DIR)/home/sbin/manage.bin -p /home/sbin/manage.bin; fi
	@cat $(IMAGE_BUILD_DIR)/image_info >> $(IMAGE_BUILD_DIR)/temp.img
	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
		-f $(IMAGE_BUILD_DIR)/temp.img -o $(BINARIES_DIR)/$(IMAGE_NAME)

image-factory:
	@rm -rf $(BINARIES_DIR)/ap.flash.download.bin $(IMAGE_BUILD_DIR)/factory
	@cp -R $(SYSTEM_DIR) $(IMAGE_BUILD_DIR)/factory
	@rm -rf $(IMAGE_BUILD_DIR)/factory/home/sp $(IMAGE_BUILD_DIR)/factory/home/wifi
	$(MKFS) -8 -p $(IMAGE_BUILD_DIR)/factory -o $(BINARIES_DIR)/ap.flash.download.bin.temp
	mv $(BINARIES_DIR)/ap.flash.download.bin.temp $(BINARIES_DIR)/ap.flash.download.bin
#	$(SIGNATURE) -q -g -k mf -t firmware -V "NEW POS TECHNOLOGY LIMITED" -v "$(IMAGE_VERSION)" \
#		-f $(BINARIES_DIR)/ap.flash.download.bin.temp -o $(BINARIES_DIR)/ap.flash.download.bin
#	rm -rf $(BINARIES_DIR)/ap.flash.download.bin.temp
	
image-clean:
	rm -rf $(IMAGE_BUILD_DIR) $(BINARIES_DIR)/$(IMAGE_NAME) $(BINARIES_DIR)/fonts.img

