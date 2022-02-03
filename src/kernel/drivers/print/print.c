/**
 * @file print.c
 * @brief PRINT FUNCTIONS
 * @version 0.1
 * @date 02-02-2022
 */

#include "print.h"

#include "../ports/ports.h"

/**
 * @brief Prints a string with a given color
 *
 * @param text
 * @param fg_color - Foreground color
 * @param bg_color - Background color
 */
void cprint(char* text, font_color_t fg_color, font_color_t bg_color)
{
	volatile char* buff = (volatile char*)VIDEO_ADDR;

	int cursor_pos = get_cursor(); // Cursor position
	while (*text != 0)
	{
		buff[cursor_pos]	 = *text++;
		buff[cursor_pos + 1] = CREATE_FONT_COLOR(fg_color, bg_color);
		cursor_pos += 2;
	}
	set_cursor(cursor_pos); // Divided by 2 in set because of the color
}

/**
 * @brief Prints a string to the screen
 *
 * @param text   - The string to print
 */
void print(char* text) { cprint(text, F_WHITE, F_BLACK); }

/**
 * @brief Get the cursor position
 *
 * @return int - The cursor position
 */
int get_cursor()
{
	// GET MSByte
	port_byte_out(REG_SCREEN_CTRL, 14); // SET THE REGISTER YOU WANNA READ
	uint8_t pos = port_byte_in(REG_SCREEN_DATA) << 8; // READ THE REGISTER

	// GET LSByte
	port_byte_out(REG_SCREEN_CTRL, 15);	  // SET THE REGISTER YOU WANNA READ
	pos += port_byte_in(REG_SCREEN_DATA); // READ THE REGISTER

	return pos * 2;
}

/**
 * @brief Set the cursor position
 *
 * @param pos - The position to set the cursor to
 */
void set_cursor(int pos)
{
	pos /= 2;

	// SET MSByte
	port_byte_out(REG_SCREEN_CTRL, 14);		  // SET THE REGISTER YOU WANNA READ
	port_byte_out(REG_SCREEN_DATA, pos >> 8); // SET THE REGISTER YOU WANNA READ

	// SET LSByte
	port_byte_out(REG_SCREEN_CTRL, 15); // SET THE REGISTER YOU WANNA READ
	port_byte_out(REG_SCREEN_DATA,
				  pos & 0xFF); // SET THE REGISTER YOU WANNA READ
}
