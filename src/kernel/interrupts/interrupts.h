/**
 * @file interrupts.h
 * @brief INTERRUPTS INITIALISATION
 * @version 0.1
 * @date 07-02-2022
 * Source : https://web.archive.org/web/20160327011227/http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
 */

#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <stdint.h>

// SIZEOF is 64 bytes
typedef struct idt_entry
{
	uint16_t base_lo;	// The lower 16 bits of the address to jump to when this interrupt fires.
	uint16_t sel;		// Kernel segment selector.
	uint8_t  always0;	// This must always be zero.
	uint8_t  flags;		// More flags. See documentation.
	uint16_t base_hi;	// The upper 16 bits of the address to jump to.
} __attribute__((packed)) idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
typedef struct idt_ptr
{
	uint16_t limit;
	uint32_t base; 		// The address of the first element in our idt_entry_t array.
} __attribute__((packed)) idt_ptr_t;


#endif