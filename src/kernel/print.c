#include "print.h"

/**
 * @brief Prints a string to the screen
 *
 * @param text   - The string to print
 */
void print(uint8_t *text)
{
	volatile uint8_t *buff = (volatile uint8_t *)0xb8000;

	while (*text != 0)
	{
		*buff++ = *text++;
		*buff++ = 0x02;
	}
	return;
}