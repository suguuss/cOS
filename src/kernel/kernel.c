#include <stdint.h>
#include "drivers/print/print.h"
#include "drivers/disk/ata/ata.h"

extern int main()
{
	uint8_t *text = "DEBUTAAAAABBBBBCCCCCDDDDDEEEEEFFFFFGGGGGHHHHHIIIIIJJJJJKKKKKLLLLLMMMMMNNNNNFINFIN";

	print(text);

	return 0;
}