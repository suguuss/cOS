/**
 * @file print.h
 * @brief PRINT FUNCTIONS
 * @version 0.1
 * @date 02-02-2022
 */

#ifndef __PRINT_H__
#define __PRINT_H__

#include "../color/color.h"

#include <stdint.h>


// DEFINES
#define VIDEO_ADDR 0xB8000 // https://wiki.osdev.org/Memory_Map_(x86)
#define MAX_ROWS   25
#define MAX_COLS   80

// CONTROL REGISTER VGA
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

// ----------------------------------------------
// ------------------- PRINT --------------------
// ----------------------------------------------
#define GET_COLORED_CHAR(CHAR, COLOR) ((CHAR) | ((COLOR) << 8))

void cprint(char* text, font_color_t fg_color, font_color_t bg_color);
void print(char* text);

int	 get_cursor();
void set_cursor(int pos);

#endif // PRINT_H