# KERNEL MAKFILE

K_BUILD_DIR = build

.PHONY: pre-build clean 

OBJECTS_TO_LINK += $(K_BUILD_DIR)/kernel_entry.o # NEEDS TO BE FIRST
OBJECTS_TO_LINK += $(K_BUILD_DIR)/kernel.o
OBJECTS_TO_LINK += $(K_BUILD_DIR)/print.o
OBJECTS_TO_LINK += $(K_BUILD_DIR)/ports.o
OBJECTS_TO_LINK += $(K_BUILD_DIR)/ata.o

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


# ------------ KERNEL ------------
$(K_BUILD_DIR)/kernel.o: kernel.c
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $@

# ------------ PRINT -------------
$(K_BUILD_DIR)/print.o: drivers/print/print.c drivers/print/print.h
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $@

# ------------ PORTS -------------
$(K_BUILD_DIR)/ports.o: drivers/ports/ports.c drivers/ports/ports.h
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $@

# ------------- ATA --------------
$(K_BUILD_DIR)/ata.o: drivers/disk/ata/ata.c drivers/disk/ata/ata.h
	$(TARGET_CC) $(TARGET_CFLGAS) -c $< -o $@


pre-build:
	@mkdir -p $(K_BUILD_DIR)

clean:
	rm -rf $(K_BUILD_DIR)/*
	@echo --------- CLEANED KERNEL BUILD ---------