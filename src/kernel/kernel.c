#include "drivers/color/color.h"
#include "drivers/disk/ata/ata.h"
#include "drivers/print/print.h"

#include <stdint.h>

extern int main()
{
	char* msg1 = "Oh GRAHAM, receive my soul!";
	char* msg2 = "Thanks GRAHAM, You're the best!";

	print(msg1);
	cprint(msg2, F_RED, F_BLACK);

	return 0;
}