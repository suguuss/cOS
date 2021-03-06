/**
 * @file keyboard.h
 * @brief KEYBOARD OPERATIONS
 * @version 0.1
 * @date 03-02-2022
 */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "../ports/ports.h"

#include <stdbool.h>

// SCANC CODES
#define KEY_W	0x11
#define KEY_A	0x1E
#define KEY_S	0x1F
#define KEY_D	0x20
#define KEY_ESC 0x01

// DEFINES
#define PRESSED		true
#define RELEASED	false
#define NOT_PRESSED false

void keyboard_callback(void* a);
void init_keyboard();
bool is_key_pressed(uint8_t scancode);

#endif