/**
 * @file stdlib.c
 * @brief STANDARD LIBRARY
 * @version 0.1
 * @date 08-02-2022
 */

#include "stdlib.h"
#include "string.h"

// STRUCTS
typedef struct heap 
{
	volatile uint8_t *start;
	volatile uint8_t *end;
} heap_t;

typedef struct block_metadata 
{
	uint32_t size;	//Block size
	bool is_free;	//Block state (Allocated or not)
	struct block_metadata *next;	//Pointer to the next metadata block
	uint8_t *start;	//Pointer to the start of the allocated block
} block_metadata_t;


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

void init_heap(heap_t* heap)
{
	heap->start = (uint8_t *)0x200000;	//Heap starts at 2Mib
	heap->end = (uint8_t *)0x400000;	//Heap ends at 4Mib
}
