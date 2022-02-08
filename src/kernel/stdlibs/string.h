/**
 * @file string.h
 * @brief STRING LIB
 * @version 0.1
 * @date 08-02-2022
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <stdint.h>

void memset(void* addr, uint8_t v, uint32_t n);
int	 strlen(const char* str);
#endif