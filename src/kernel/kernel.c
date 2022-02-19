/**
 * @file kernel.c
 * @brief KERNEL 
 * @version 0.1
 * @date 02-02-2022
 */

// ! ---------------- INCLUDES  -----------------
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "drivers/disk/fat32/fat32.h"
#include "interrupts/interrupts.h"
#include "drivers/disk/ata/ata.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"

#include <stdint.h>

// ! --------------- PROTOTYPES  ----------------
void init_kernel();



extern int main()
{
    init_kernel();

    uint8_t sector[512];

    BootSector_t bs = fat32_parse_bootsector();
    ata_read_sector(bs.RootDirSector, 1, sector);
    FileEntry_t fe = fat32_parse_fileentry(sector, 32);
    
    k_print(fe.Name);
    clean_filename(fe.Name);
    k_print(fe.Name);
    
    return 0;
}




void init_kernel()
{
    extern heap_t heap;
    extern block_metadata_t *meta_head;

    // ! PUT HERE EVERYTHING THAT NEED TO BE DONE TO SETUP THE KERNEL
    // Init the Heap
    heap = init_heap();

    //Init the first metadata block
    // La taille disponible est la taille du heap (end - start) moins la taille du premier metablock
    meta_head = init_meta_block((uint32_t)heap.end - (uint32_t)heap.start - sizeof(block_metadata_t), 0, (uint32_t)heap.start);

    // idt setup
    init_idt();
    // Enable keyboard interupts
    port_byte_out(0x21, 0xFD);
    // Enable interrupts
    asm volatile("sti");
}