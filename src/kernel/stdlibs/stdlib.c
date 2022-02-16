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

void init_heap(heap_t* heap)
{
	heap->start = (uint8_t *)0x200000;	//Heap starts at 2Mib
	heap->end = (uint8_t *)0x400000;	//Heap ends at 4Mib
}

block_metadata_t* init_meta_block()
{
	block_metadata_t block;

	block.size = 0x200000;	//Size of the heap
	block.is_free = true; 
	block.next = 0;
	block.start = (uint8_t *) (0x200000 + sizeof(block) + 1); //Start of the heap + size of the block + 1

	memcpy(0x200000, &block, sizeof(block)); //Copy the starting metadata block to the heap
	return 0x200000;
}

void* malloc(uint32_t size)
{
	//Iterate all the metadata block to find a free data block
		//Check if the block size is bigger or equivalent
			//Reduce the size and create a new metadata block for the next
			
}