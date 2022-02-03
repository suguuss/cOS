/**
 * @file color.h
 * @brief COLOR MANAGEMENT
 * @version 0.1
 * @date 03-02-2022
 */

#ifndef _COLOR_H_
#define _COLOR_H_


// https://wiki.osdev.org/Text_UI

// ----------------------------------------------
// ---------------- FONT COLORS -----------------
// ----------------------------------------------
#define GET_FONT_COLOR(FG, BG) ((FG) | ((BG) << 4))

// FONT - BACKGROUND OR FOREGROUND
typedef enum
{
	F_BLACK,		 // 0
	F_BLUE,			 // 1
	F_GREEN,		 // 2
	F_CYAN,			 // 3
	F_RED,			 // 4
	F_MAGENTA,		 // 5
	F_BROWN,		 // 6
	F_LIGHT_GRAY,	 // 7
	F_LIGHT_BLACK,	 // 8
	F_LIGHT_BLUE,	 // 9
	F_LIGHT_GREEN,	 // 10 - A
	F_LIGHT_CYAN,	 // 11 - B
	F_LIGHT_RED,	 // 12 - C
	F_LIGHT_MAGENTA, // 13 - D
	F_YELLOW,		 // 14 - E
	F_WHITE,		 // 15 - F
} font_color_t;

#endif