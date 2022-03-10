/**
 * @file string.c
 * @brief STRING LIB
 * @version 0.1
 * @date 08-02-2022
 */

#include "string.h"

#include "../drivers/screen/print/print.h"
#include "stdlib.h"

/**
 * @brief copies a value v starting at address addr for n bytes
 *
 * @param addr starting address
 * @param v value to copy
 * @param n number of bytes to copy
 */
void memset(void* addr, uint8_t v, uint32_t n)
{
	while (n--)
	{
		*((uint8_t*)addr++) = v;
	}
}

/**
 * @brief copies values from a source address to a destination address
 *
 * @param dest destination address
 * @param src source address
 * @param n number of bytes to copy
 */
void memcpy(void* dest, const void* src, uint32_t size)
{
	while (size--)
	{
		*((uint8_t*)dest++) = *((uint8_t*)src++);
	}
}

/**
 * @brief Get the lenght of a given string
 *
 * @param str
 * @return int
 */
int strlen(const char* str)
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
splitted_tokens* str_split(const char* str, const char delim)
{
	splitted_tokens* sk			= malloc(sizeof(splitted_tokens));
	int				 input_size = strlen(str);
	sk->tokens					= malloc(sizeof(char*) * input_size / 2); // cannot be more
	char buff_token[input_size];
	int	 index	   = 0;
	int	 index_tok = 0; // index of token being built
	sk->nb_tok	   = 0; // index of token in tokens array

	while (index < input_size + 1) // While last char not reached
	{
		if ((str[index] != delim) && (str[index] != '\0'))
		{
			buff_token[index_tok++] = str[index];
		}
		else
		{
			// PUT THE BUFFERED TOKEN IN FINAL ARRAY
			buff_token[index_tok] = '\0';
			int tok_size		  = strlen(buff_token);
			// k_print_number(tok_size);
			// k_print(buff_token);
			// k_print("\n");
			sk->tokens[sk->nb_tok]			 = malloc(sizeof(char) * tok_size + 1); // Allocate enough space + 1 for \0
			sk->tokens[sk->nb_tok][tok_size] = '\0';
			memcpy(sk->tokens[sk->nb_tok], buff_token, tok_size);

			// MANAGEMENT COUNTERS
			index_tok = 0;
			sk->nb_tok++;
		}
		index++;
	}
	return sk;
}

 * @brief compares the string pointed to, by str1 to the string pointed to by str2.
 *
 * @param const char *str1
 * @param const char *str2
 * @return int
 * 
 * - if Return value < 0 then it indicates str1 is less than str2.
 * - if Return value > 0 then it indicates str2 is less than str1.
 * - if Return value = 0 then it indicates str1 is equal to str2.
 */
int strcmp(const char *str1, const char *str2)
{
	while (*str1)
	{
		// Loops through all the chars and adds the diff
		// between them to the tot variable.

		if (*str1 != *str2){break;}
		str1++;
		str2++;
	}

	return *str1 - *str2;
}
