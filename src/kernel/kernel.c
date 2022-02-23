/**
 * @file kernel.c
 * @brief KERNEL entry point
 * @version 0.1
 * @date 02-02-2022
 */

// ! ---------------- INCLUDES  -----------------
#include "drivers/disk/ata/ata.h"
#include "drivers/disk/fat32/fat32.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "interrupts/interrupts.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"

#include <stdint.h>

// ! ----------------- DEFINES ------------------
#define DISPLAY_LOGO 0

// ! --------------- PROTOTYPES  ----------------
void init_kernel();


extern int main()
{
	init_kernel();

	uint8_t sector[512];

	BootSector_t bs = fat32_parse_bootsector();
	FileList_t file_list = fat32_list_files(bs);

	for (int i = 0; i < file_list.size; i++)
	{
		clean_filename(file_list.list[i].Name);
		k_print(file_list.list[i].Name);
		k_print("\n");
	}

	return 0;
}


void init_kernel()
{
	// ! HERE, PUT EVERYTHING THAT NEEDS TO BE DONE TO SETUP THE KERNEL
	init_malloc();

	// idt setup
	init_idt();
	// Disable ALL Interrupts
	port_byte_out(0x21, 0xFF);
	// Enable keyboard interupts
	init_keyboard();
	// Init timer and enable timer interrupt
	init_timer(20);
	// Enable interrupts
	asm volatile("sti");

	#if DISPLAY_LOGO == 1
	k_print(
		"            /$$$$$$   /$$$$$$		\n"
		"           /$$__  $$ /$$__  $$		\n"
		"  /$$$$$$$| $$  \\ $$| $$  \\__/	\n"
		" /$$_____/| $$  | $$|  $$$$$$ 		\n"
		"| $$      | $$  | $$ \\____  $$	\n"
		"| $$      | $$  | $$ /$$  \\ $$	\n"
		"|  $$$$$$$|  $$$$$$/|  $$$$$$/		\n"
		" \\_______/ \\______/  \\______/	\n");

	#endif
}