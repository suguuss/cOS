#include "drivers/color/color.h"
#include "drivers/disk/ata/ata.h"
#include "drivers/print/print.h"

#include <stdint.h>
extern int main()
{
	char* msg1
	  = "0000000\n00000000000000000000000000000000000000000000000000000000000000000000000000"
		"000000000\n\n\n00000000\n\n\n\n\n00";
	char* msg2 = "Thanks GRAHAM, You're the best!";

	volatile uint16_t* buff = (volatile uint16_t*)VIDEO_ADDR;

	// set_cursor(300);
	print(msg1);

	return 0;
}