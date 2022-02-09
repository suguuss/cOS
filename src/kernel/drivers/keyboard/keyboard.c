/**
 * @file keyboard.c
 * @brief KEYBOARD OPERATIONS
 * @version 0.1
 * @date 03-02-2022
 */

#include "keyboard.h"

#include "../screen/print/print.h" // TO REMOVE - DEBUG ONLY

// --------- PRIVATE DEFINES ---------
// REGISTERS
#define DATA_PORT		 0x60
#define STATUS_REGISTER	 0x64 // READ
#define COMMAND_REGISTER 0x64 // WRITE

// BITS
#define BUFFER_STATUS_OUT 0x01
#define BUFFER_STATUS_IN  0x02

void keyboard_callback()
{
	// End Of Interrupt (EOI)
	port_byte_out(0x20, 0x20);

	uint8_t scancode = port_byte_in(0x60);
	k_print(scancode);
}