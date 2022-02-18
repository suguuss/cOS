/**
 * @file stdlib.c
 * @brief STANDARD LIBRARY
 * @version 0.1
 * @date 08-02-2022
 */

#include "stdlib.h"
#include "string.h"

heap_t heap;
block_metadata_t *meta_head;
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

heap_t init_heap()
{
	heap_t heap;

	heap.start = (uint8_t *)0x200000;	//Heap starts at 2Mib
	heap.end = (uint8_t *)0x400000;	//Heap ends at 4Mib

	return heap;
}

/**
 * @breif Init a metadata block and copy it in the heap
 * @param size
 * @param next_block
 * @param meta_start
 */
block_metadata_t* init_meta_block(uint32_t size, block_metadata_t* next_block, uint32_t meta_start)
{
	block_metadata_t block;

	block.size = size;
	block.is_free = true; 
	block.next = next_block;
	block.start = (uint8_t *) (meta_start + sizeof(block)); //Start of the heap + size of the block + 1

	memcpy((uint8_t *)meta_start, &block, sizeof(block)); //Copy the starting metadata block to the heap
	
	return (block_metadata_t *)meta_start;
}

void* malloc(uint32_t size)
{
	block_metadata_t *tmp = meta_head;

	// Loop while block is not free and there is enough space
	while (!(tmp->is_free && tmp->size >= (size + sizeof(block_metadata_t))))
	{
		if (tmp->next != 0)
		{
			// Check the next block
			tmp = tmp->next;
		}
		else
		{
			return 0; // Memory cannot be allocated (No free space)
		}
	}
	
	
	block_metadata_t *tmp_next = 0;
	if (tmp->next != 0)
	{
		// If there is a block after the one we create, 
		// keep it's address in a variable.
		// Otherwise, use a null address (declaration before the if)
		tmp_next = tmp->next;
	}

	block_metadata_t *new_block = init_meta_block(tmp->size - size - sizeof(block_metadata_t), tmp_next, (uint32_t)tmp->start + size);

	tmp->size = size;
	tmp->next = new_block;
	tmp->is_free = false;

	return tmp->start;
}