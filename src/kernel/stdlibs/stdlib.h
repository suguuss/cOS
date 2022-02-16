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
typedef struct heap heap_t;
typedef struct block_metadata block_metadata_t;

// PROTOTYPES
void uitoa(uint16_t number, char* out_str);
void itoa(int16_t number, char* out_str);
void init_heap(heap_t* heap);

#endif //_STDLIB_H_