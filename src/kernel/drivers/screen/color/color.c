/**
 * @file color.c
 * @brief
 * @version 0.1
 * @date 06-02-2022
 */

#include "color.h"

#include "../../ports/ports.h"
#include "../cursor/cursor.h"

// ! GLOBAL SETTABLE FONT COLOR
font_color_t g_font_color = GET_FONT_COLOR(FB_RED, FB_BLACK);

// ----------------------------------------------
// ---------------- FONT COLORS -----------------
// ----------------------------------------------

/**
 * @brief Set the global font color
 *
 * @param fg_color
 * @param bg_color
 */
void set_font_color(fb_color_t fg_color, fb_color_t bg_color)
{
	g_font_color = GET_FONT_COLOR(fg_color, bg_color);
}

/**
 * @brief Get the global font color
 *
 * @param fg_color
 * @param bg_color
 */
uint8_t get_font_color()
{
	return g_font_color;
}

/**
 * @brief Get the Background component of the global font color
 *
 * @param fg_color
 * @param bg_color
 */
uint8_t get_background_color()
{
	return g_font_color >> 4;
}

/**
 * @brief Get the Foreground component of the global font color
 *
 * @param fg_color
 * @param bg_color
 */
uint8_t get_foreground_color()
{
	return g_font_color & 0x0F;
}

/**
 * @brief Set the Background component of the global font color
 *
 * @param fg_color
 * @param bg_color
 */
void set_background_color(fb_color_t bg_color)
{
	g_font_color = (g_font_color & 0x0F) | (bg_color << 4);
}

/**
 * @brief Set the Foreground component of the global font color
 *
 * @param fg_color
 * @param bg_color
 */
void set_foreground_color(fb_color_t fg_color)
{
	g_font_color = (g_font_color & 0xF0) | fg_color;
}
