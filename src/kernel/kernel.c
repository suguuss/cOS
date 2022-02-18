#include "drivers/disk/ata/ata.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "interrupts/interrupts.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"

#include <stdint.h>

extern int main()
{
	extern heap_t heap;
	extern block_metadata_t *meta_head;

	// Init the Heap
	heap = init_heap();

	//Init the first metadata block
	// La taille disponible est la taille du heap (end - start) moins la taille du premier metablock
	meta_head = init_meta_block((uint32_t)heap.end - (uint32_t)heap.start - sizeof(block_metadata_t), 0, (uint32_t)heap.start);

	// idt setup
	// init_idt();
	// // Enable keyboard interupts
	// port_byte_out(0x21, 0xFD);
	// // Enable interrupts
	// asm volatile("sti");

	uint8_t *test = malloc(2);
	test[0] = 42;
	test[1] = 69;

	uint8_t *test2 = malloc(2);
	test2[0] = 10;
	test2[1] = 31;

	k_print("Hello Kernel!");
	k_print_number(test[0]);
	k_print_number(test[1]);
	k_print_number(test2[0]);
	k_print_number(test2[1]);
	k_print("\n");
	k_print_number((int)test);
	k_print("\n");
	k_print_number((int)test2);
	return 0;
}

