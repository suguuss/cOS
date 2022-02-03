/**
 * @file ata.c
 * @brief DISK READ AND WRITE
 * @version 0.1
 * @date 02-02-2022
 */

// We're using LBA Addressing, you can read more about it here :
// https://fr.wikipedia.org/wiki/Logical_block_addressing

// Everything is based on the ATA_PIO page from the osdev wiki :
// https://wiki.osdev.org/ATA_PIO_Mode#28_bit_PIO

// Driver works in polling mode.

#include "ata.h"

static void wait_while_BSY();
static void wait_while_DRQ();

#define DATA_REG   0x1F0
#define STATUS_REG 0x1F7
#define DRQ_BIT	   0x08
#define BSY_BIT	   0x80

// LBA (28bits)	-> Sector address
// sectorcount 	-> nb of sector to read?
// *out			-> Pointer to the output buffer
void ata_read_sector(uint32_t LBA, uint8_t sectorcount, uint8_t* out)
{
	uint16_t tmp; // asasd

	wait_while_BSY();

	// Send 0xE0 for "master" ORed with highest 4 bits of LBA to port 0x1F6
	port_byte_out(0x1F6, 0xE0 | (LBA >> 24 & 0x0F));
	// Send the sectorcount to port 0x1F2
	port_byte_out(0x1F2, sectorcount);
	// Send the low  8 bits of the LBA to port 0x1F3
	port_byte_out(0x1F3, (uint8_t)LBA);
	// Send the next 8 bits of the LBA to port 0x1F4
	port_byte_out(0x1F4, (uint8_t)(LBA >> 8));
	// Send the next 8 bits of the LBA to port 0x1F5
	port_byte_out(0x1F5, (uint8_t)(LBA >> 16));
	// Send the read sector command (0x20) to port 0x1F7
	port_byte_out(0x1F7, 0x20);

	// Copy all the bytes in the buffer
	for (uint8_t i = 0; i < sectorcount; i++)
	{
		wait_while_BSY();
		wait_while_DRQ();

		// We receive 256 16 bits value per sector
		for (uint16_t j = 0; j < 256; j++)
		{
			tmp	   = port_word_in(DATA_REG);
			*out++ = (uint8_t)tmp;
			*out++ = (uint8_t)(tmp >> 8);
		}
	}
}

void ata_write_sector(uint32_t LBA, uint8_t sectorcount, uint8_t* in)
{
	uint16_t tmp; // asasd

	wait_while_BSY();

	// Send 0xE0 for "master" ORed with highest 4 bits of LBA to port 0x1F6
	port_byte_out(0x1F6, 0xE0 | (LBA >> 24 & 0x0F));
	// Send the sectorcount to port 0x1F2
	port_byte_out(0x1F2, sectorcount);
	// Send the low  8 bits of the LBA to port 0x1F3
	port_byte_out(0x1F3, (uint8_t)LBA);
	// Send the next 8 bits of the LBA to port 0x1F4
	port_byte_out(0x1F4, (uint8_t)(LBA >> 8));
	// Send the next 8 bits of the LBA to port 0x1F5
	port_byte_out(0x1F5, (uint8_t)(LBA >> 16));
	// Send the write sector command (0x30) to port 0x1F7
	port_byte_out(0x1F7, 0x30);

	// Copy all the bytes in the buffer
	for (uint8_t i = 0; i < sectorcount; i++)
	{
		wait_while_BSY();
		wait_while_DRQ();

		// We receive 256 16 bits value per sector
		for (uint16_t j = 0; j < 256; j++)
		{
			tmp = *in++;
			tmp |= *in++ << 8;
			port_word_out(DATA_REG, tmp);
		}
	}
}


static void wait_while_BSY()
{
	while (port_byte_in(STATUS_REG) & BSY_BIT)
		;
}

static void wait_while_DRQ()
{
	while (!(port_byte_in(STATUS_REG) & DRQ_BIT))
		;
}