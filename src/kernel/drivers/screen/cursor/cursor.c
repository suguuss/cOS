/**
 * @file cursor.c
 * @brief CURSOR MANAGEMENT
 * @version 0.1
 * @date 03-02-2022
 */

#include "cursor.h"

#include "../../ports/ports.h"


/**
 * @brief Get the cursor position
 *
 * @return int - The cursor position
 */
int get_cursor()
{
	// GET MSByte
	port_byte_out(REG_SCREEN_CTRL, 14);			  // SET THE REGISTER YOU WANNA READ
	int pos = port_byte_in(REG_SCREEN_DATA) << 8; // READ THE REGISTER

	// GET LSByte
	port_byte_out(REG_SCREEN_CTRL, 15);	  // SET THE REGISTER YOU WANNA READ
	pos += port_byte_in(REG_SCREEN_DATA); // READ THE REGISTER

	return pos;
}

/**
 * @brief Set the cursor position
 *
 * @param pos - The position to set the cursor to
 */
void set_cursor(int pos)
{
	// SET MSByte
	port_byte_out(REG_SCREEN_CTRL, 14);		  // SET THE REGISTER YOU WANNA READ
	port_byte_out(REG_SCREEN_DATA, pos >> 8); // SET THE REGISTER YOU WANNA READ

	// SET LSByte
	port_byte_out(REG_SCREEN_CTRL, 15); // SET THE REGISTER YOU WANNA READ
	port_byte_out(REG_SCREEN_DATA,
				  pos & 0xFF); // SET THE REGISTER YOU WANNA READ
}
