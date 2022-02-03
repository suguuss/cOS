#include "drivers/color/color.h"
#include "drivers/disk/ata/ata.h"
#include "drivers/print/print.h"

#include <stdint.h>
extern int main()
{
	char* msg1 = "GRAHAM THE BG\n\n";
	char* msg2 = "Thanks GRAHAM,\n\n\n\n\n You're the best!";

	volatile uint16_t* buff = (volatile uint16_t*)VIDEO_ADDR;

	// set_cursor(300);
	print(msg1);

	return 0;
}