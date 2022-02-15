# export allow access from the lower makefiles 
export CC 				= gcc
export CFLAGS			= 
export ASM 				= nasm

export TARGET 			= i386-elf
export TARGET_CC		= $(TARGET)-gcc
export TARGET_CFLGAS	= -ffreestanding -m32 -g
export TARGET_LD		= $(TARGET)-ld

CURRENT_DIR 			= $(shell pwd)
export BUILD_DIR 		= $(CURRENT_DIR)/build
export BUILD_DIR 		= $(CURRENT_DIR)/build

export KERNEL_ADDR		= 0x8000

.PHONY: all run os bootloader kernel pre-build clean

all: clean os

run: clean os
	qemu-system-x86_64 -d int -drive format=raw,file=$(BUILD_DIR)/os.bin,index=0 2>qemu.log

# ---------------------------------------------------
# ----------------- CREATING DISK -------------------
# ---------------------------------------------------
# ------------- BUILDING THE WHOLE OS ---------------
# ---------------------------------------------------
os: $(BUILD_DIR)/os.bin

$(BUILD_DIR)/os.bin: pre-build bootloader kernel
	@echo ------------ BUILDING IMAGE ------------
	@dd if=/dev/zero of=$@ bs=512 count=4096 status=none
	@mkfs.fat -I -F 32 -n boot $@ 2>/dev/null 1>/dev/null

	@# --- ADD A FILE IN THE ROOT DIR (TEST PURPOSE ONLY) ---
	@echo "Hello World!" > test.txt
	@mcopy -i $@ test.txt ::test.txt
	@rm test.txt
	@# --- ADD A FILE IN THE ROOT DIR (TEST PURPOSE ONLY) ---

	@dd if=$(BUILD_DIR)/kernel.bin of=$@ conv=notrunc seek=1 status=none
	@dd if=$(BUILD_DIR)/bootloader.bin of=$@ conv=notrunc status=none

# --------------------------------------------------
# ------------------ BOOTLOADER --------------------
# --------------------------------------------------
bootloader: $(BUILD_DIR)/bootloader.bin

$(BUILD_DIR)/bootloader.bin:
	@$(MAKE) -s -C src/bootloader


# --------------------------------------------------
# -------------------- KERNEL ----------------------
# --------------------------------------------------
kernel: $(BUILD_DIR)/kernel.bin

$(BUILD_DIR)/kernel.bin: src/kernel/kernel.c
	@$(MAKE) -s -C src/kernel


# --------------------------------------------------
# --------------------- UTILS ----------------------
# --------------------------------------------------

pre-build: 
	@mkdir -p $(BUILD_DIR)

clean:
	@$(MAKE) -s -C src/kernel clean
	@rm  -rf $(BUILD_DIR)/*
	@echo ---------- CLEANED MAIN BUILD ----------
