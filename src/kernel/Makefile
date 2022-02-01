$(BUILD_DIR)/kernel.bin: kernel.c kernel_entry.asm
	@echo COMPILING KERNEL
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $(BUILD_DIR)/kernel.o
	$(ASM) $(word 2, $^) -f elf -o $(BUILD_DIR)/kernel_entry.o
	$(TARGET_LD) -o $(BUILD_DIR)/kernel.bin -Ttext 0x1000 $(BUILD_DIR)/kernel_entry.o $(BUILD_DIR)/kernel.o --oformat binary

	