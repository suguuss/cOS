/**
 * @file keyboard.c
 * @brief KEYBOARD OPERATIONS
 * @version 0.1
 * @date 03-02-2022
 */

#include "keyboard.h"

//#include "../screen/print/print.h" // TO REMOVE - DEBUG ONLY

// --------- PRIVATE DEFINES ---------
// REGISTERS
#define DATA_PORT		 0x60
#define STATUS_REGISTER	 0x64 // READ
#define COMMAND_REGISTER 0x64 // WRITE

// BITS
#define BUFFER_STATUS_OUT 0x01
#define BUFFER_STATUS_IN  0x02

// -------- PRIVATE PROTOTYPE --------
static void wait_for_output();
static void wait_for_input();


/**
 * @brief Waits before reading an output from the
 * keyboard controler
 */
static void wait_for_output()
{
	while (port_byte_in(STATUS_REGISTER) & BUFFER_STATUS_OUT)
	{
		// print("c");
	}
}

/**
 * @brief Waits before writing to the keyboard controler
 */
static void wait_for_input()
{
	while (port_byte_in(STATUS_REGISTER) & BUFFER_STATUS_IN)
		;
}