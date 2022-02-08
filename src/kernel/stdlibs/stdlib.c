/**
 * @file stdlib.c
 * @brief STANDARD LIBRARY
 * @version 0.1
 * @date 08-02-2022
 */

#include "stdlib.h"

#include "string.h"

/**
 * @breif Put a uint number into a string
 * STRING NEEDS TO BE LONG ENOUGH TO PUT THE NUMBER
 * @param number
 * @param out_str
 */
void uitoa(uint16_t number, char* out_str)
{
	if (number < 10)
	{
		out_str[0] = number + '0';
		out_str[1] = '\0';
	}
	else
	{
		uitoa(number / 10, out_str);
		uitoa(number % 10, out_str + strlen(out_str));
	}
}

/**
 * @brief Put a int number into a string
 * 	STRING NEEDS TO BE LONG ENOUGH TO PUT THE NUMBER
 * @param number
 * @param out_str
 */
void itoa(int16_t number, char* out_str)
{
	// If the number is nagative
	if (number < 0)
	{
		// Put a minus sign and convert the inverse of the number
		out_str[0] = '-';
		uitoa(-number, out_str + 1);
	}
	else
	{
		uitoa(number, out_str);
	}
}
