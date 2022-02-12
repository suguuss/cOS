/**
 * @file print.c
 * @brief PRINT FUNCTIONS
 * @version 0.1
 * @date 02-02-2022
 */

#include "print.h"

#include "../../ports/ports.h"
#include "../color/color.h"
#include "../cursor/cursor.h"


/**
 * @brief Prints a string at cursor position
 *		  Increments the cursor position
 * @param text
 * @param fg_color - Foreground color
 * @param bg_color - Background color
 */
void k_cprint(char* text, fb_color_t fg_color, fb_color_t bg_color)
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
			// Create a char with a given color and pass it to the 16 bits buffer
			buff[cursor_pos] = GET_COLORED_CHAR(*text++, GET_FONT_COLOR(fg_color, bg_color));
			cursor_pos++;
		}
	}
	set_cursor(cursor_pos);
}

/**
 * @brief Prints a string to the screen with global color
 *  	  Increments the cursor position
 *
 * @param text   - The string to print
 */
void k_print(char* text)
{
	k_cprint(text, get_foreground_color(), get_background_color());
}

/**
 * @brief Print a string at a given position
 *
 * @param text
 * @param x
 * @param y
 */
void k_print_at(char* text, uint16_t x, uint16_t y)
{
	set_cursor(x + (y * MAX_COLS));
	k_print(text);
}

/**
 * @brief Clears the screen and sets a background color
 *
 * @param color
 */
void k_cclear(fb_color_t bg_color)
{
	fb_color_t fore = get_foreground_color();
	fb_color_t back = get_background_color();
	set_font_color(bg_color, bg_color);

	set_cursor(0);
	for (uint16_t i = 0; i < MAX_ROWS * MAX_COLS; i++)
	{
		k_print(" ");
	}
	set_cursor(0);

	set_font_color(fore, back);
}
