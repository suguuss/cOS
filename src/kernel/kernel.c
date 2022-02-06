#include "drivers/disk/ata/ata.h"
#include "drivers/screen/color/color.h"
#include "drivers/screen/print/print.h"

#include <stdint.h>
extern int main()
{
	char* msg1 = "GRAHAM THE BG\n\n";
	char* msg2 = "Thanks GRAHAM, You're the best!";

	volatile uint16_t* buff = (volatile uint16_t*)VIDEO_ADDR;

	k_print_at(msg2, 1, 1);
	set_foreground_color(FB_GREEN);

	k_print_at(msg2, 1, 2);
	set_background_color(FB_WHITE);

	k_print_at(msg2, 1, 3);

	return 0;
}