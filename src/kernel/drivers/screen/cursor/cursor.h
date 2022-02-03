/**
 * @file cursor.h
 * @brief CURSOR MANAGEMENT
 * @version 0.1
 * @date 03-02-2022
 */


#ifndef __CURSOR_H__
#define __CURSOR_H__

// CONTROL REGISTER VGA
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

int	 get_cursor();
void set_cursor(int pos);

#endif // CURSOR_H