/**
 * @file ports.c
 * @brief PORT IN AND OUT COMMUNICATION 
 * @version 0.1
 * @date 02-02-2022
 * Source : https://github.com/dhavalhirdhav/LearnOS/blob/master/drivers/ports.c
 */

#include "ports.h"

uint8_t port_byte_in (uint16_t port) {
    uint8_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (uint16_t port, uint8_t data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}


uint16_t port_word_in (uint16_t port) {
    uint16_t result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (uint16_t port, uint16_t data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}


void port_long_out(uint32_t port, uint32_t value) {
	   __asm__ __volatile__("outl %%eax,%%dx"::"d" (port), "a" (value));
};

uint32_t port_long_in(uint32_t port) {
    uint32_t result;
    __asm__ __volatile__("inl %%dx,%%eax":"=a" (result):"d"(port));
    return result;
}