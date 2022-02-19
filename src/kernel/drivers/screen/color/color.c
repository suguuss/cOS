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

// ! ----------------------------------------------
// ! ---------------- FONT COLORS -----------------
// ! ----------------------------------------------


// ! ---------------- FULL FONT  -----------------
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
 * @brief Set the global font color
 *
 * @param fc
 */
void set_font_color_whole(font_color_t fc)
{
	g_font_color = fc;
}

/**
 * @brief Get the global font color
 */
font_color_t get_font_color()
{
	return g_font_color;
}

// ! ---------------- BACK FONT  -----------------
/**
 * @brief Get the Background component of the global font color
 */
fb_color_t get_background_color()
{
	return (g_font_color >> 4);
}

/**
 * @brief Set the Background component of the global font color
 *
 * @param bg_color
 */
void set_background_color(fb_color_t bg_color)
{
	g_font_color = (g_font_color & 0x0F) | (bg_color << 4);
}

// ! ---------------- FORE FONT  -----------------
/**
 * @brief Get the Foreground component of the global font color
 */
fb_color_t get_foreground_color()
{
	return (g_font_color & 0x0F);
}


/**
 * @brief Set the Foreground component of the global font color
 *
 * @param fg_color
 */
void set_foreground_color(fb_color_t fg_color)
{
	g_font_color = (g_font_color & 0xF0) | fg_color;
}
