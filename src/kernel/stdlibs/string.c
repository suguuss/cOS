/**
 * @file string.c
 * @brief STRING LIB
 * @version 0.1
 * @date 08-02-2022
 */

#include "string.h"

/**
 * @brief copies a value v starting at address addr for n bytes
 *
 * @param addr starting address
 * @param v value to copy
 * @param n number of bytes to copy
 */
void memset(void *addr, uint8_t v, uint32_t n)
{
	while (n--)
	{
		*((uint8_t *)addr++) = v;
	}
}