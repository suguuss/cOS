#include <stdint.h>
#include "drivers/print/print.h"
#include "drivers/disk/ata/ata.h"

extern int main()
{
	uint8_t *text = "Welcome to the cOS Kernel !";
	// uint8_t *buffer = "ABCD";
	uint8_t buffer[512];

	// uint16_t test = ata_read_sector(97, 1, buffer);
	ata_read_sector(97, 1, buffer);

	// buffer[0] = 'A';
	// buffer[1] = 'A';
	// buffer[2] = 'A';
	// buffer[3] = 'A';
	// buffer[4] = 'D';

	print(buffer);
	// print(text);

	return 0;
}