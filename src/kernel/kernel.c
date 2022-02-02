#include <stdint.h>
#include "drivers/print/print.h"
#include "drivers/disk/ata/ata.h"

extern int main()
{
	uint8_t *text = "Welcome to the cOS Kernel !";
	uint8_t buffer[512];


	ata_write_sector(98, 1, text);
	ata_read_sector(98, 1, buffer);


	print(buffer);

	return 0;
}