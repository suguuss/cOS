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

// LBA (28bits)	-> Sector address
// sectorcount 	-> nb of sector to read?
// *in			-> Pointer to the input buffer
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

/**
 * @brief Read one byte from a sector of the disk
 * 
 * @param addr address of the block (LBA)
 * @param offset offset of the byte in the block
 * 
 * @return byte read
 */
uint8_t ata_read_byte(uint32_t addr, uint16_t offset)
{
	uint8_t sector[512];
	ata_read_sector(addr, 1, sector);

	return sector[offset];
}

/**
 * @brief Read one word (16 bits) from a sector of the disk
 * 
 * @param addr address of the block (LBA)
 * @param offset offset of the byte in the block
 * 
 * @return word read
 */
uint16_t ata_read_word(uint32_t addr, uint16_t offset)
{
	uint8_t sector[512];
	uint16_t tmp;

	// Read the whole sector
	ata_read_sector(addr, 1, sector);

	// Read the two bytes and convert from little endian to big endian
	tmp  = sector[offset];
	tmp |= sector[offset + 1] << 8;

	return tmp;
}

/**
 * @brief Read one double word (32 bits) from a sector of the disk
 * 
 * @param addr address of the block (LBA)
 * @param offset offset of the byte in the block
 * 
 * @return dword read
 */
uint32_t ata_read_dword(uint32_t addr, uint16_t offset)
{
	uint8_t sector[512];
	uint32_t tmp;

	// Read the whole sector
	ata_read_sector(addr, 1, sector);

	// Read the two bytes and convert from little endian to big endian
	tmp  = sector[offset];
	tmp |= sector[offset + 1] << 8;
	tmp |= sector[offset + 2] << 16;
	tmp |= sector[offset + 3] << 24;

	return tmp;
}

/**
 * @brief Write one byte to a sector on the disk
 * 
 * @param addr address of the block (LBA)
 * @param offset offset of the byte in the block
 * @param value value to write
 * 
 */
void ata_write_byte(uint32_t addr, uint16_t offset, uint8_t value)
{
	uint8_t sector[512];

	// Read the sector
	ata_read_sector(addr, 1, sector);
	
	// Modify the byte
	sector[offset] = value;

	// Write the modified sector to the disk
	ata_write_sector(addr, 1, sector);
}

/**
 * @brief Write one word (16 bits) to a sector on the disk
 * 
 * @param addr address of the block (LBA)
 * @param offset offset of the word in the block
 * @param value value to write
 * 
 */
void ata_write_word(uint32_t addr, uint16_t offset, uint16_t value)
{
	uint8_t sector[512];

	// Read the sector
	ata_read_sector(addr, 1, sector);
	
	// Modify the byte
	// Need to write it as little endian
	sector[offset]     = value;
	sector[offset + 1] = value >> 8;

	// Write the modified sector to the disk
	ata_write_sector(addr, 1, sector);
}

/**
 * @brief Write one dword (32 bits) to a sector on the disk
 * 
 * @param addr address of the block (LBA)
 * @param offset offset of the dword in the block
 * @param value value to write
 * 
 */
void ata_write_dword(uint32_t addr, uint16_t offset, uint32_t value)
{
	uint8_t sector[512];

	// Read the sector
	ata_read_sector(addr, 1, sector);
	
	// Modify the byte
	// Need to write it as little endian
	sector[offset]     = value;
	sector[offset + 1] = value >> 8;
	sector[offset + 2] = value >> 16;
	sector[offset + 3] = value >> 24;

	// Write the modified sector to the disk
	ata_write_sector(addr, 1, sector);
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