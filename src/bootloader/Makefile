ASM=nasm
ASM_FLAGS=-f bin

BUILD_DIR=build
SRC_STAGE1=stage1
SRC_STAGE2=stage2

.PHONY: pre-build clean stage1 stage2 bootloader run

bootloader: fat stage1

run: bootloader
	qemu-system-x86_64 $(BUILD_DIR)/fat.bin

stage1: $(BUILD_DIR)/bootsector.bin
	dd if=$< of=$(BUILD_DIR)/fat.bin conv=notrunc

$(BUILD_DIR)/bootsector.bin: $(SRC_STAGE1)/bootsector.asm pre-build
	$(ASM) $(ASM_FLAGS) $< -o $@

stage2: $(BUILD_DIR)/stage2.bin

$(BUILD_DIR)/stage2.bin: $(SRC_STAGE2)/stage2.asm pre-build
	$(ASM) $(ASM_FLAGS) $< -o $@

fat: stage2
	dd if=/dev/zero of=$(BUILD_DIR)/fat.bin bs=512 count=4096
	mkfs.fat -F 32 -n boot $(BUILD_DIR)/fat.bin
	mcopy -i $(BUILD_DIR)/fat.bin $(BUILD_DIR)/stage2.bin "::stage2.bin"
	
pre-build:
	@mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*