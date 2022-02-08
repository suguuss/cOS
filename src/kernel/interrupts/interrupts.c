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

static void idt_set_entry(idt_entry_t *entry, uint32_t base, uint16_t sel, uint8_t flags);

void init_idt()
{
	idt_entry_t idt_entries[256];
	idt_ptr_t 	idt_ptr;

	// SIZEOF(idt_entry_t) * 256 -1
	idt_ptr.limit = 64 * 256 - 1;
	idt_ptr.base  = (uint32_t)idt_entries;

	// Set all the idt entries to 0 to void junk. Because an entry 
	// can be set to 0 if we dont use it.
	memset(idt_entries, 0, 64 * 256);

	idt_set_entry(&idt_entries[0], 0, 0x08, 0x8E);
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