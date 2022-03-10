/**
 * @file string.h
 * @brief STRING LIB
 * @version 0.1
 * @date 08-02-2022
 */

#ifndef __STRING_H__
#define __STRING_H__

#include <stdint.h>

// --------------------------------------------------
// ---------------------- SPLIT ---------------------
// --------------------------------------------------
typedef struct
{
	int	   nb_tok;
	char** tokens;
} splitted_tokens;
splitted_tokens* str_split(const char* str, const char delim);


void memset(void* addr, uint8_t v, uint32_t n);
void memcpy(void* dest, const void* src, uint32_t size);
int	 strlen(const char* str);


#endif