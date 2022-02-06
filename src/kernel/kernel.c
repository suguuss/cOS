#include "drivers/disk/ata/ata.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"

#include <stdint.h>
extern int main()
{
	char* msg1 = "GRAHAM THE BG\n\n";
	char* msg2 = "Thanks GRAHAM, You're the best!";

	volatile uint16_t* buff = (volatile uint16_t*)VIDEO_ADDR;

	// set_cursor(300);
	k_print(msg1);
	// print(msg2);
	k_cprint(msg2, FB_LIGHT_MAGENTA, FB_BLACK);

	return 0;
}