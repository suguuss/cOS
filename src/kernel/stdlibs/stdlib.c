/**
 * @file stdlib.c
 * @brief STANDARD LIBRARY
 * @version 0.1
 * @date 08-02-2022
 */

#include "stdlib.h"
#include "string.h"

// ------------------------------------------
//            VARIABLES GLOBALES
// ------------------------------------------

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

/**
 * @brief Initialise the heap memory
 * @return heap_t
 */
heap_t init_heap()
{
	heap_t heap;

	heap.start = (uint8_t *)0x200000;	//Heap starts at 2Mib
	heap.end = (uint8_t *)0x400000;	//Heap ends at 4Mib

	return heap;
}

/**
 * @brief Init a metadata block and copy it in the heap
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

/**
 * @brief Allocates memory dynamically from the heap
 * @param size number of bytes to allocate
 * @return void* Pointer to the newly allocated memory
 */
void* malloc(uint32_t size)
{
	block_metadata_t *tmp = meta_head;

	// Loop while block is not free and there is enough space
	// while (!(tmp->is_free && tmp->size >= (size + sizeof(block_metadata_t)))) bakcup
	while (!(tmp->is_free && tmp->size >= size))
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
	
	if (tmp->size - size > sizeof(block_metadata_t))
	{
		// In this case we create a new metadata block, thus breaking a big free block in two
		
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
	}
	else 
	{
		// In this case we give a whole block without creating a new metablock even if there is a 
		// few bytes more than what he asked
		tmp->is_free = false;
	}

	return tmp->start;
}

/**
 * @brief Free memory allocated by malloc from the heap
 * @param void* Pointer to the allocated memory
 */
void free(void* ptr)
{
	block_metadata_t *tmp = meta_head;

	while (tmp->start != ptr)
	{
		if (tmp->next == 0)
		{
			// TODO: MAYBE HANDLE THIS ERROR ?
			return;
		}
		tmp = tmp->next;
	}

	tmp->is_free = true;
	// clean_heap();
}

/**
 * @brief Cleans the heap by fusing all the free neighbours block together
 */
void clean_heap()
{
	block_metadata_t *tmp        = meta_head;
	block_metadata_t *tmp_before = 0;
	
	while (tmp->next != 0)
	{
		tmp_before = tmp;
		tmp = tmp->next;

		if (tmp->is_free == true && tmp_before->is_free == true)
		{
			tmp_before->next = tmp->next;
			tmp_before->size = tmp_before->size + tmp->size + sizeof(block_metadata_t);
			tmp = tmp_before;
		}
	}
}