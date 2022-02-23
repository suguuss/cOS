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
#define TAB_SIZE	4

// ----------------------------------------------
// ------------------- PRINT --------------------
// ----------------------------------------------
#define GET_COLORED_CHAR(CHAR, COLOR) ((CHAR) | ((COLOR) << 8))

void k_put_char(char c);
void k_put_char_at(char c, uint16_t x, uint16_t y);
void k_cprint(char* text, fb_color_t fg_color, fb_color_t bg_color);
void k_print(char* text);
void k_print_at(char* text, uint16_t x, uint16_t y);
void k_cclear(fb_color_t bg_color);

void k_print_number(int32_t number);
void k_print_number_at(int number, uint16_t x, uint16_t y);
#endif // PRINT_H