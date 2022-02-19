/**
 * @file timer.h
 * @brief Harware timer driver - Programmable Interval Timer (PIT)
 * @version 0.1
 * @date 13-02-2022
 */


#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdbool.h>
#include <stdint.h>

// DEFINES
#define TIMER_CHAN_0_DIV 0x40 // Divisor
#define TIMER_CHAN_1_DIV 0x41
#define TIMER_CHAN_2_DIV 0x42
#define TIMER_COMMAND	 0x43

void init_timer(uint32_t);
bool ticker_ticked();
void reset_ticker();
void timer_callback(void*);


#endif /* __TIMER_H__ */