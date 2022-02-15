/**
 * @file fat32.h
 * @brief FAT32 LIB
 * @version 0.1
 * @date 13-02-2022
 */

#ifndef __FAT32_H__
#define __FAT32_H__

#include <stdint.h>

// -------------- DEFINES -------------

// FAT32
// BOOT SECTOR
#define BYTSPERSEC_OFFSET	0x0B // 11 
#define SECPERCLUS_OFFSET	0x0D // 13
#define RSVDSECCNT_OFFSET	0x0E // 14
#define NUMFATS_OFFSET		0x10 // 16
#define FATSz32_OFFSET		0x24 // 36
#define ROOTCLUS_OFFSET		0x2C // 44


// -------------- STRUCT --------------

// Most usefull info inside the boot sector
// Size : 16 bytes
typedef struct 
{
	uint16_t  	BytsPerSec;
	uint8_t 	SecPerClus;
	uint16_t  	RsvdSecCnt;
	uint8_t 	NumFATs;
	uint32_t 	FATSz32;
	uint32_t 	RootClus;
	uint16_t  	RootDirSector;  // Not really in the boot sector
} BootSector;


// ------------ PROTOTYPES ------------
// Abstraction functions in file "src/kernel/drivers/disk/ata/ata.c"
// uint8_t ata_read_byte(uint32_t addr, uint16_t offset);
// uint16_t ata_read_word(uint32_t addr, uint16_t offset);
// uint32_t ata_read_dword(uint32_t addr, uint16_t offset);

// void ata_write_byte(uint32_t addr, uint16_t offset, uint8_t value);
// void ata_write_word(uint32_t addr, uint16_t offset, uint16_t value);
// void ata_write_dword(uint32_t addr, uint16_t offset, uint32_t value);

BootSector fat32_parse_bootsector();

#endif