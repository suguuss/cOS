ASM=nasm
ASM_FLAGS=-f bin

BUILD_DIR=build
SRC_STAGE1=stage1
SRC_STAGE2=stage2

.PHONY: pre-build clean stage1 stage2 bootloader run

bootloader: pre-build fat stage1 

run:
	qemu-system-x86_64 $(BUILD_DIR)/os.bin

stage1: $(BUILD_DIR)/bootsector.bin
	@echo overwriting the bootsector with the bootloader...
	@dd if=$< of=$(BUILD_DIR)/os.bin conv=notrunc status=none

$(BUILD_DIR)/bootsector.bin: $(SRC_STAGE1)/bootsector.asm pre-build
	$(ASM) $(ASM_FLAGS) $< -o $@

$(BUILD_DIR)/kernel.bin: kernel/kernel.c
	i386-elf-gcc -ffreestanding -m32 -g -c kernel/kernel.c -o kernel/kernel.o
	nasm kernel/kernel_entry.asm -f elf -o kernel/kernel_entry.o
	i386-elf-ld -o $(BUILD_DIR)/kernel.bin -Ttext 0x1000 kernel/kernel_entry.o kernel/kernel.o --oformat binary
	rm kernel/*.o

fat: $(BUILD_DIR)/kernel.bin
	@echo Creating the empty FAT32 disk...
	@dd if=/dev/zero of=$(BUILD_DIR)/os.bin bs=512 count=4096 status=none
	@mkfs.fat -I -F 32 -n boot $(BUILD_DIR)/os.bin 2> /dev/null 1> /dev/null
	dd if=$(BUILD_DIR)/kernel.bin of=$(BUILD_DIR)/os.bin conv=notrunc seek=2

pre-build:
	@mkdir -p $(BUILD_DIR)

clean:
	@echo cleaning the content of : $(BUILD_DIR)
	@rm -rf $(BUILD_DIR)/*