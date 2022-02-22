/**
 * @file kernel.c
 * @brief KERNEL entry point
 * @version 0.1
 * @date 02-02-2022
 */

// ! ---------------- INCLUDES  -----------------
#include "drivers/disk/ata/ata.h"
#include "drivers/disk/fat32/fat32.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "interrupts/interrupts.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"

#include <stdint.h>

// ! --------------- PROTOTYPES  ----------------
void init_kernel();


extern int main()
{
	init_kernel();

	uint8_t sector[512];

	BootSector_t bs = fat32_parse_bootsector();
	FileList_t file_list = fat32_list_files(bs);

	k_print(file_list.list[0].Name);
	k_print_number(bs.root_clus);
	return 0;
}


void init_kernel()
{
	extern heap_t			 heap;
	extern block_metadata_t* meta_head;

	// ! HERE, PUT EVERYTHING THAT NEEDS TO BE DONE TO SETUP THE KERNEL
	// Init the Heap
	heap = init_heap();

	// Init first metadata block
	// To get the size of the first data block,
	// You need to get the whole heap size (end - start) minus the size of the first metadata block
	meta_head = init_meta_block((uint32_t)heap.end - (uint32_t)heap.start - sizeof(block_metadata_t), 0, (uint32_t)heap.start);

	// idt setup
	init_idt();
	// Disable ALL Interrupts
	port_byte_out(0x21, 0xFF);
	// Enable keyboard interupts
	init_keyboard();
	// Init timer and enable timer interrupt
	init_timer(20);
	// Enable interrupts
	asm volatile("sti");
}