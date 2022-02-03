/**
 * @file print.c
 * @brief PRINT FUNCTIONS
 * @version 0.1
 * @date 02-02-2022
 */

#include "print.h"

#include "../../ports/ports.h"
#include "../cursor/cursor.h"

/**
 * @brief Prints a string with a given color
 *
 * @param text
 * @param fg_color - Foreground color
 * @param bg_color - Background color
 */
void cprint(char* text, font_color_t fg_color, font_color_t bg_color)
{
	volatile uint16_t* buff = (volatile uint16_t*)VIDEO_ADDR;

	uint16_t cursor_pos = get_cursor(); // Cursor position
	while (*text != 0)
	{
		if (*text == '\n')
		{
			text++; // Avoid looping on itself
			// Set the cursor to the next line
			cursor_pos = ((cursor_pos / (MAX_COLS) + 1) * MAX_COLS);
		}
		else
		{
			buff[cursor_pos] = GET_COLORED_CHAR(*text++, GET_FONT_COLOR(fg_color, bg_color));
			// buff[cursor_pos] = *text++ | GET_FONT_COLOR(fg_color, bg_color);
			cursor_pos++;
		}
	}
	set_cursor(cursor_pos);
}

/**
 * @brief Prints a string to the screen
 *
 * @param text   - The string to print
 */
void print(char* text) { cprint(text, F_WHITE, F_BLACK); }
