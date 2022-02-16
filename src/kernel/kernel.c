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
	heap_t heap;
	init_heap(&heap);

	//Init the first metadata block
	block_metadata_t *meta_head;
	meta_head = init_meta_block();

	// idt setup
	init_idt();
	// Enable keyboard interupts
	port_byte_out(0x21, 0xFD);
	// Enable interrupts
	asm volatile("sti");

	for (int i = 0; i < MAX_ROWS; i++)
	{
		k_print_number(i);
		k_put_char('\n');
	}
	k_print_at("0123456789ABCDEF", 0, 0);
	k_put_char('H');
	k_put_char_at('A', 15, 10);

	return 0;
}