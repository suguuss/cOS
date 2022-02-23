/**
 * @file string.c
 * @brief STRING LIB
 * @version 0.1
 * @date 08-02-2022
 */

#include "string.h"
#include "stdlib.h"

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

/**
 * @brief copies values from a source address to a destination address
 *
 * @param dest destination address
 * @param src source address
 * @param n number of bytes to copy
 */
void memcpy(void *dest, const void *src, uint32_t size)
{
	while (size--)
	{
		*((uint8_t *)dest++) = *((uint8_t *)src++);
	}
}

/**
 * @brief Get the lenght of a given string
 *
 * @param str
 * @return int
 */
int strlen(const char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return i;
}

/**
 * @brief Get every substrings separated by a delimiter
 *
 * @param str
 * @param delim
 * @return char**
 */
char **str_split(char *str, const char delim)
{
	int input_size = str_len(str);
	char **out_tab = malloc(sizeof(char) * input_size / 2); // cannot be more
	char buff_token[input_size];
	char current_char;
	int index;

	while (index < input_size) // While last char not reached
	{
		// Get the next token
		for (int i = index; i < input_size; i++)
		{
			current_char = str[index];

			if (current_char == delim)
			{
				break;
			}
		}
	}
}
