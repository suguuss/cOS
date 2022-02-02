# KERNEL MAKFILE

K_BUILD_DIR = build

.PHONY: pre-build clean 

OBJECTS_TO_LINK += $(K_BUILD_DIR)/kernel_entry.o # NEEDS TO BE FIRST
OBJECTS_TO_LINK += $(K_BUILD_DIR)/kernel.o
OBJECTS_TO_LINK += $(K_BUILD_DIR)/print.o

# --------------------------------------------------
# --------------- LINKING OBJECTS ------------------
# --------------------------------------------------
$(BUILD_DIR)/kernel.bin: pre-build $(OBJECTS_TO_LINK)
	@echo ----------- COMPILING KERNEL -----------	
	$(TARGET_LD) -o $(BUILD_DIR)/kernel.bin -Ttext 0x1000 $(OBJECTS_TO_LINK) --oformat binary

# --------------------------------------------------
# --------------- GETTING OBJECTS ------------------
# --------------------------------------------------
$(K_BUILD_DIR)/kernel_entry.o: kernel_entry.asm
	$(ASM) $< -f elf -o $@

$(K_BUILD_DIR)/kernel.o: kernel.c
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $@

$(K_BUILD_DIR)/print.o: print.c
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $@




pre-build:
	@mkdir -p $(K_BUILD_DIR)

clean:
	rm -rf $(K_BUILD_DIR)/*
	@echo --------- CLEANED KERNEL BUILD ---------