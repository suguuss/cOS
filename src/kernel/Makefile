# KERNEL MAKFILE

K_BUILD_DIR = build

.PHONY: pre-build clean 

$(BUILD_DIR)/kernel.bin: pre-build kernel.c kernel_entry.asm
	@echo ----------- COMPILING KERNEL -----------
	$(TARGET_CC) $(TARGET_CFLGAS) -c $(word 2, $^) -o $(K_BUILD_DIR)/kernel.o
	$(ASM) $(word 3, $^) -f elf -o $(K_BUILD_DIR)/kernel_entry.o
	$(TARGET_LD) -o $(BUILD_DIR)/kernel.bin -Ttext 0x1000 $(K_BUILD_DIR)/kernel_entry.o $(K_BUILD_DIR)/kernel.o --oformat binary

pre-build:
	@mkdir -p $(K_BUILD_DIR)

clean:
	rm -rf $(K_BUILD_DIR)/*
	@echo --------- CLEANED KERNEL BUILD ---------