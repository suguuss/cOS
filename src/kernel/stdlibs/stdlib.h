/**
 * @file stdlib.h
 * @brief STANDARD LIBRARY
 * @version 0.1
 * @date 08-02-2022
 */

#ifndef _STDLIB_H_
#define _STDLIB_H_

#include <stdint.h>
#include <stdbool.h>

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

// PROTOTYPES
void uitoa(uint16_t number, char* out_str);
void itoa(int16_t number, char* out_str);
void init_heap(heap_t* heap);
block_metadata_t* init_meta_block();
void* malloc(uint32_t size);
#endif //_STDLIB_H_