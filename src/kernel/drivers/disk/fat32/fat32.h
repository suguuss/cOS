/**
 * @file fat32.h
 * @brief FAT32 LIB
 * @version 0.1
 * @date 13-02-2022
 * @source FAT32 SPEC : https://www.cs.fsu.edu/~cop4610t/assignments/project3/spec/fatspec.pdf
 */

#ifndef __FAT32_H__
#define __FAT32_H__

#include <stdint.h>

// -------------- DEFINES -------------

// FAT32
// BOOT SECTOR
#define BYTSPERSEC_OFFSET		0x0B // 11 
#define SECPERCLUS_OFFSET		0x0D // 13
#define RSVDSECCNT_OFFSET		0x0E // 14
#define NUMFATS_OFFSET			0x10 // 16
#define FATSz32_OFFSET			0x24 // 36
#define ROOTCLUS_OFFSET			0x2C // 44

// FILE ENTRY
#define NAME_OFFSET				0x00 // 00
#define ATTR_OFFSET				0x0B // 11
#define CRTTIMETENTH_OFFSET		0x0D // 13
#define CRTTIME_OFFSET			0x0E // 14
#define CRTDATE_OFFSET			0x10 // 16
#define LSTACCDATE_OFFSET		0x12 // 18
#define FSTCLUSHI_OFFSET		0x14 // 20
#define WRTTIME_OFFSET			0x16 // 22
#define WRTDATE_OFFSET			0x18 // 24
#define FSTCLUSLO_OFFSET		0x1A // 26
#define FILESIZE_OFFSET			0x1C // 28


// -------------- MACROS --------------
#define PARSE_INFO_INT(structure, info, buffer, offset)  memcpy(&structure.info, buffer+offset, sizeof(structure.info)); swap_endian_int(&structure.info);
#define PARSE_INFO_LONG(structure, info, buffer, offset) memcpy(&structure.info, buffer+offset, sizeof(structure.info)); swap_endian_long(&structure.info);
#define PARSE_INFO_CHAR(structure, info, buffer, offset) memcpy(&structure.info, buffer+offset, sizeof(structure.info));


// -------------- STRUCT --------------

// Most usefull info inside the boot sector
typedef struct 
{
	uint16_t  	BytsPerSec;
	uint8_t 	SecPerClus;
	uint16_t  	RsvdSecCnt;
	uint8_t 	NumFATs;
	uint32_t 	FATSz32;
	uint32_t 	RootClus;
	uint16_t  	RootDirSector;  // Not really in the boot sector
} BootSector_t;


// File entry descriptor (long name not supported yet)
typedef struct
{
	char		Name[11];
	uint16_t	FstClusHi;
	uint16_t 	FstClusLO;
	uint32_t	fileSize;
	uint8_t		Attr;
	uint8_t		CrtTimeTenth;
	uint16_t	CrtTime;
	uint16_t	CrtDate;
	uint16_t	LstAccDate;
	uint16_t	WrtTime;
	uint16_t	WrtDate;
} FileEntry_t;
 
// ------------ PROTOTYPES ------------

// !ABSTRACT FUNCTIONS in file "src/kernel/drivers/disk/ata/ata.c"
// uint8_t ata_read_byte(uint32_t addr, uint16_t offset);
// uint16_t ata_read_word(uint32_t addr, uint16_t offset);
// uint32_t ata_read_dword(uint32_t addr, uint16_t offset);

// void ata_write_byte(uint32_t addr, uint16_t offset, uint8_t value);
// void ata_write_word(uint32_t addr, uint16_t offset, uint16_t value);
// void ata_write_dword(uint32_t addr, uint16_t offset, uint32_t value);

void swap_endian_int(uint16_t *val);
void swap_endian_long(uint32_t *val);

BootSector_t fat32_parse_bootsector();
FileEntry_t  fat32_parse_fileentry(uint8_t *sector, uint16_t offset);

uint8_t clean_filename(uint8_t *filename);
#endif