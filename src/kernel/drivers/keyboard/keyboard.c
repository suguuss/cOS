/**
 * @file keyboard.c
 * @brief KEYBOARD OPERATIONS
 * @version 0.1
 * @date 03-02-2022
 */

#include "keyboard.h"

#include "../screen/print/print.h" // TO REMOVE - DEBUG ONLY
#include "../../stdlibs/stdlib.h"
#include "ch-fr_keymap.h"
// --------- PRIVATE DEFINES ---------
// REGISTERS
#define DATA_PORT		 0x60
#define STATUS_REGISTER	 0x64 // READ
#define COMMAND_REGISTER 0x64 // WRITE

// BITS
#define BUFFER_STATUS_OUT 0x01
#define BUFFER_STATUS_IN  0x02

// The void* a is unused but is needed to avoid a compilation error
__attribute__((interrupt)) void keyboard_callback(void* a)
{
	char code[2];

	uint8_t scancode = port_byte_in(DATA_PORT);

	// Prints only when the key is pressed and not released
	if ((scancode & 0x80) == 0)
	{
		code[0] = keyboard_map[scancode];
		code[1] = 0;
		k_print(code);
	}

	// End Of Interrupt (EOI)
	port_byte_out(0x20, 0x20);
}