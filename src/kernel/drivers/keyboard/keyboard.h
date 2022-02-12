/**
 * @file keyboard.h
 * @brief KEYBOARD OPERATIONS
 * @version 0.1
 * @date 03-02-2022
 */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include "../ports/ports.h"

__attribute__((interrupt)) void keyboard_callback(void *a);

#endif