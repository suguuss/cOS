# BOOTLOADER MAKFILE

$(BUILD_DIR)/bootloader.bin: bootsector.asm
	@echo --------- COMPILING BOOTLOADER ---------
	$(ASM) -f bin $< -o $@