/**
 * @file kernel.c
 * @brief Kernel entry point
 * @version 0.1
 */

#include "drivers/disk/ata/ata.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "drivers/timer/timer.h"
#include "interrupts/interrupts.h"
#include "pong/pong.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"

#include <stdint.h>
extern int main()
{
	// IDT
	init_idt();

	// KEYBOARD
	// init_keyboard();
	// port_byte_out(0x21, 0xFD);

	// TIMER
	init_timer(10);

	// Enable interrupts
	asm volatile("sti"); // Set Interrupt Flag

	// fb_color_t test = GET_FONT_COLOR(FB_CYAN, FB_WHITE);
	// set_font_color_whole(test);
	//// set_font_color(FB_RED, FB_WHITE);
	// k_print_at("Hello World!", 0, 0);

	// --------------------------------
	// ------------- PONG -------------
	// --------------------------------
	pong_run();

	// while (1)
	//{
	//	if (is_key_pressed(30))
	//	{
	//		reset_ticker();
	//		k_print("a");
	//	}
	// }

	return 0;
}