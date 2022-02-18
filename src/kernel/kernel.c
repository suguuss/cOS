#include "drivers/disk/ata/ata.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "interrupts/interrupts.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"

#include <stdint.h>
extern int main()
{
	// Init the Heap
	heap_t heap = init_heap();

	//Init the first metadata block
	block_metadata_t *meta_head = init_meta_block((uint32_t)heap.end - (uint32_t)heap.start, 0, (uint32_t)heap.start);

	// idt setup
	// init_idt();
	// // Enable keyboard interupts
	// port_byte_out(0x21, 0xFD);
	// // Enable interrupts
	// asm volatile("sti");

	k_print_number((uint32_t)heap.end - (uint32_t)heap.start);

	return 0;
}