/**
 * @file print.h
 * @brief PRINT FUNCTIONS 
 * @version 0.1
 * @date 02-02-2022
 */

#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdint.h>

#define VIDEO_ADDR 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F
#define RED_ON_WHITE 0x4F

//
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

//PROTOTYPES
void print(uint8_t *text);
int get_cursor();
void set_cursor(int pos);

#endif // PRINT_H