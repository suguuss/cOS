#include "drivers/disk/ata/ata.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"
#include "interrupts/interrupts.h"
#include "stdlibs/stdlib.h"
#include "stdlibs/string.h"

#include <stdint.h>
extern int main()
{
	// init_idt();
	// char* msg1 = "This is a test string, fuck graham";

	// memset(msg1, 'F', 4); // Testing the memset

	// k_print(msg1);

	// asm volatile("int $0x3");

	char str_num[15];

	uitoa(15647, str_num);

	k_print(str_num);

	return 0;
}