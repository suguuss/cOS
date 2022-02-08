/**
 * @file interrupts.c
 * @brief INTERRUPTS INITIALISATION
 * @version 0.1
 * @date 07-02-2022
 * Source : https://web.archive.org/web/20160327011227/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
 */

#include "interrupts.h"

static void init_idt()
{
	idt_entry_t idt_entries[256];
	idt_ptr_t 	idt_ptr;

	// SIZEOF(idt_entry_t) * 256 -1
	idt_ptr.limit = 64 * 256 - 1;


}