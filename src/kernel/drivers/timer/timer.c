/**
 * @file timer.c
 * @brief Hardware timer driver - Programmable Interval Timer (PIT)
 * @version 0.1
 * @date 13-02-2022
 * Sources:
 * https://wiki.osdev.org/Programmable_Interval_Timer
 * https://github.com/cfenollosa/os-tutorial/blob/master/20-interrupts-timer
 */

#include "timer.h"

#include "../../drivers/ports/ports.h"
#include "../../drivers/screen/print/print.h"

int g_timer_ticks = 0;


/**
 * @brief Timer Callback - Called every period of frequency set at init
 * The void* a is unused but is needed to avoid a compilation error
 *
 */
__attribute__((interrupt)) void timer_callback(void* a)
{
	k_print_number(g_timer_ticks++);
	k_print(" ");

	// READING CONFIRMATION (EOI)
	port_byte_out(0x20, 0x20);
}

/**
 * @brief Initializes the PIT - Programmable Interval Timer
 *
 * @param freq in Hz
 */
void init_timer(uint32_t freq)
{
	// ------------- PIT - Programmable Interval Timer -------------
	// The idea is to trigger a callback at a Given period
	// It works by dividing a base hardware clock @ 1193180 Hz
	// We actually set a reload value of a counter counting backwards
	// and triggering a callback when it reaches 0

	// 1193180 for the 1.193180 MHz
	// random fucking clock because of random old stuff again
	uint32_t div = 1193180 / freq;

	// https://wiki.osdev.org/Programmable_Interval_Timer#I.2FO_Ports
	// 0x36 - 0011 0110
	// 7-6 CHANNEL 0
	// 4-5 ACESS MODE LOW AND HIGH BYTE - SENDING DATA TO THE CHANNEL IN TWO GOES
	// 1-3 OPERATION MODE 3 - SQUARE WAVE GENERATOR
	// 0   BINARY MODE / BCD MODE
	port_byte_out(TIMER_COMMAND, 0x36);
	port_byte_out(TIMER_CHAN_0_DIV, (uint8_t)(div & 0xFF));		   // LOW BYTE
	port_byte_out(TIMER_CHAN_0_DIV, (uint8_t)((div >> 8) & 0xFF)); // HIGH BYTE
}
