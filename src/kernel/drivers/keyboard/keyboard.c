/**
 * @file keyboard.c
 * @brief KEYBOARD OPERATIONS
 * @version 0.1
 * @date 03-02-2022
 */

#include "keyboard.h"

#include "../../stdlibs/stdlib.h"
#include "../screen/print/print.h" // TO REMOVE - DEBUG ONLY
#include "ch-fr_keymap.h"

// --------- PRIVATE DEFINES ---------
// REGISTERS
#define KB_DATA_PORT		0x60
#define KB_STATUS_REGISTER	0x64 // READ
#define KB_COMMAND_REGISTER 0x64 // WRITE


// SCAN CODE INDEXED - KEY PRESSED STATUS
bool g_key_pressed[128];

// https://wiki.osdev.org/Interrupt_Service_Routines#Compiler_Specific_Interrupt_Directives
// The void* a is unused but is needed to avoid a compilation error
__attribute__((interrupt)) void keyboard_callback(void* a)
{
	uint8_t scancode = port_byte_in(KB_DATA_PORT);

	// last bit (msb) is set when released and cleared when pressed
	// Prints only when the key is pressed and not released
	if ((scancode & 0x80) == 0) // Pressed
	{
		g_key_pressed[scancode] = PRESSED;

		// Enable if you want to print the key pressed
		k_put_char(keyboard_map[scancode]);
	}
	else // Released
	{
		g_key_pressed[scancode] = RELEASED;
		// k_put_char(keyboard_map[scancode & 0x7F]);
		//  Do nothing
	}

	// End Of Interrupt (EOI)
	port_byte_out(0x20, 0x20);
}

void init_keyboard()
{
	// Enable the IRQ1
	port_byte_out(0x21, port_byte_in(0x21) & ~0x02);

	// Each bit represent an interruption, if the bit is set to 1, 
	// the interrupt is DISABLED, if the bit is set to 0 the interrupt 
	// is ENABLED

	// 1 = DISABLE
	// 0 = ENABLE

	// 00000000
	// |||||||+-- IRQ 0
	// ||||||+--- IRQ 1
	// |||||+---- IRQ 2
	// ||||+----- IRQ 3
	// |||+------ IRQ 4
	// ||+------- IRQ 5
	// |+-------- IRQ 6
	// +--------- IRQ 7
}

bool is_key_pressed(uint8_t scancode)
{
	bool tmp				= g_key_pressed[scancode];
	g_key_pressed[scancode] = NOT_PRESSED;
	return tmp;
}
