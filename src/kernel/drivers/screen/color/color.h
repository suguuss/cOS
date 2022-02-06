/**
 * @file color.h
 * @brief COLOR MANAGEMENT
 * @version 0.1
 * @date 03-02-2022
 */

#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>


// https://wiki.osdev.org/Text_UI

// ----------------------------------------------
// ---------------- FONT COLORS -----------------
// ----------------------------------------------
// COLOR XXXX XXXX
//       BACK FORE
// Get a full font color
#define GET_FONT_COLOR(FG, BG) ((FG) | ((BG) << 4))

// FONT - BACKGROUND OR FOREGROUND
typedef enum
{
	FB_BLACK,		  // 0
	FB_BLUE,		  // 1
	FB_GREEN,		  // 2
	FB_CYAN,		  // 3
	FB_RED,			  // 4
	FB_MAGENTA,		  // 5
	FB_BROWN,		  // 6
	FB_LIGHT_GRAY,	  // 7
	FB_LIGHT_BLACK,	  // 8
	FB_LIGHT_BLUE,	  // 9
	FB_LIGHT_GREEN,	  // 10 - A
	FB_LIGHT_CYAN,	  // 11 - B
	FB_LIGHT_RED,	  // 12 - C
	FB_LIGHT_MAGENTA, // 13 - D
	FB_YELLOW,		  // 14 - E
	FB_WHITE,		  // 15 - F
} fb_color_t;		  // Foreground or Background Color

typedef uint16_t font_color_t;

// PROTOTYPES

// FULL FONT
void	set_font_color(fb_color_t fg_color, fb_color_t bg_color);
uint8_t get_font_color();

// FOREGROUND
uint8_t get_foreground_color();
void	set_foreground_color(fb_color_t fg_color);

// BACKGROUND
uint8_t get_background_color();
void	set_background_color(fb_color_t fg_color);

#endif