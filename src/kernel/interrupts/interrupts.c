/**
 * @file interrupts.c
 * @brief INTERRUPTS INITIALISATION
 * @version 0.1
 * @date 07-02-2022
 * Source : https://web.archive.org/web/20160327011227/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
 */

/*

	THIS FILE SETS UP THE IDT (INTERRUPT DESCRIPTOR TABLE). THE TABLE IS MADE OF 256 ENTRIES
	EACH ONE OF THEM HAS TO BE SET TO A VALUE OR NULL. IF THERE IS NO ENTRY THE PROCESSOR
	WILL PANIC AND RESET. THE FIRST 32 INTERRUPTS MUST BE MAPPED, THEY CORRESPOND TO : 

    0  - Division by zero exception
    1  - Debug exception
    2  - Non maskable interrupt
    3  - Breakpoint exception
    4  - 'Into detected overflow'
    5  - Out of bounds exception
    6  - Invalid opcode exception
    7  - No coprocessor exception
    8  - Double fault (pushes an error code)
    9  - Coprocessor segment overrun
    10 - Bad TSS (pushes an error code)
    11 - Segment not present (pushes an error code)
    12 - Stack fault (pushes an error code)
    13 - General protection fault (pushes an error code)
    14 - Page fault (pushes an error code)
    15 - Unknown interrupt exception
    16 - Coprocessor fault
    17 - Alignment check exception
    18 - Machine check exception
    19-31 - Reserved


*/

#include "interrupts.h"
#include "../stdlibs/string.h"
#include "../drivers/screen/print/print.h"
#include "../drivers/ports/ports.h"

static void idt_set_entry(idt_entry_t *entry, uint32_t base, uint16_t sel, uint8_t flags);

void isr_default()
{
	// k_cclear(FB_RED);
}

void init_idt()
{
	idt_entry_t idt_entries[256];
	idt_ptr_t 	idt_ptr;

	// SIZEOF(idt_entry_t) * 256 -1
	idt_ptr.limit = 64 * 256 - 1;
	idt_ptr.base  = (uint32_t)idt_entries;

	// Set all the idt entries to 0 to void junk. Because an entry 
	// can be set to 0 if we dont use it.
	// MAKES THE OS CRASH, DONT USE IT
	// memset(idt_entries, 0, 64 * 256);

	idt_set_entry(&idt_entries[0] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[1] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[2] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[3] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[4] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[5] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[6] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[7] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[8] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[9] , (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[10], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[11], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[12], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[13], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[14], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[15], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[16], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[17], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[18], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[19], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[20], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[21], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[22], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[23], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[24], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[25], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[26], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[27], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[28], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[29], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[30], (uint32_t)isr_default, 0x08, 0x8E);
	idt_set_entry(&idt_entries[31], (uint32_t)isr_default, 0x08, 0x8E);

	// REMAP THE PIC INTERRUPTS
	// See : https://wiki.osdev.org/PIC
	// See : https://github.com/cfenollosa/os-tutorial/tree/master/19-interrupts-irqs
	port_byte_out(0x20, 0x11);
	port_byte_out(0xA0, 0x11);
	port_byte_out(0x21, 0x20);
	port_byte_out(0xA1, 0x28);
	port_byte_out(0x21, 0x04);
	port_byte_out(0xA1, 0x02);
	port_byte_out(0x21, 0x01);
	port_byte_out(0xA1, 0x01);
	port_byte_out(0x21, 0x00);
	port_byte_out(0xA1, 0x00);

	idt_set_entry(&idt_entries[IRQ1], (uint32_t)keyboard_callback, 0x08, 0x8E);


	__asm__("lidt %0" ::"m"(idt_ptr));
}

/**
 * @brief Set an entry with values given as input.
 *
 * @param idt_entry_t* ptr to the entry to set
 * @param uint32_t address where the int will jump to
 * @param uint16_t segment selector
 * @param uint8_t flags to give to the entry
 */
static void idt_set_entry(idt_entry_t* entry, uint32_t base, uint16_t sel, uint8_t flags)
{
	entry->base_lo = base & 0xFFFF;
	entry->base_hi = base >> 16;
	entry->sel = sel;
	entry->always0 = 0;
	entry->flags = flags;
}