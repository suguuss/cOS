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

// The void* a is unused but is needed to avoid a compilation error
__attribute__((interrupt)) void keyboard_callback(void* a)
{
	uint8_t scancode = port_byte_in(KB_DATA_PORT);

	// last bit (msb) is set when released and cleared when pressed
	// Prints only when the key is pressed and not released
	if ((scancode & 0x80) == 0) // Pressed
	{
		k_put_char(keyboard_map[scancode]);
	}
	else // Released
	{
		// k_put_char(keyboard_map[scancode & 0x7F]);
		//  Do nothing
	}

	// End Of Interrupt (EOI)
	port_byte_out(0x20, 0x20);
}