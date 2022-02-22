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
#define byts_per_sec_OFFSET		0x0B // 11 
#define sec_per_clus_OFFSET		0x0D // 13
#define rsvd_sec_cnt_OFFSET		0x0E // 14
#define num_FATs_OFFSET			0x10 // 16
#define FATSz32_OFFSET			0x24 // 36
#define root_clus_OFFSET			0x2C // 44

// FILE ENTRY
#define NAME_OFFSET				0x00 // 00
#define attr_OFFSET				0x0B // 11
#define crt_time_tenth_OFFSET		0x0D // 13
#define crt_time_OFFSET			0x0E // 14
#define crt_date_OFFSET			0x10 // 16
#define lst_acc_date_OFFSET		0x12 // 18
#define fst_clus_hi_OFFSET		0x14 // 20
#define wrt_time_OFFSET			0x16 // 22
#define wrt_date_OFFSET			0x18 // 24
#define fst_clus_lo_OFFSET		0x1A // 26
#define file_size_OFFSET			0x1C // 28


// -------------- MACROS --------------
#define PARSE_INFO_INT(structure, info, buffer, offset)  memcpy(&structure.info, buffer+offset, sizeof(structure.info)); swap_endian_int(&structure.info);
#define PARSE_INFO_LONG(structure, info, buffer, offset) memcpy(&structure.info, buffer+offset, sizeof(structure.info)); swap_endian_long(&structure.info);
#define PARSE_INFO_CHAR(structure, info, buffer, offset) memcpy(&structure.info, buffer+offset, sizeof(structure.info));


// -------------- STRUCT --------------

// Most usefull info inside the boot sector
typedef struct 
{
	uint16_t  	byts_per_sec;
	uint8_t 	sec_per_clus;
	uint16_t  	rsvd_sec_cnt;
	uint8_t 	num_FATs;
	uint32_t 	FATSz32;
	uint32_t 	root_clus;
	uint16_t  	root_dir_sector;  // Not really in the boot sector
} BootSector_t;


// File entry descriptor (long name not supported yet)
typedef struct
{
	char		Name[11];
	uint16_t	fst_clus_hi;
	uint16_t 	fst_clus_lo;
	uint32_t	file_size;
	uint8_t		attr;
	uint8_t		crt_time_tenth;
	uint16_t	crt_time;
	uint16_t	crt_date;
	uint16_t	lst_acc_date;
	uint16_t	wrt_time;
	uint16_t	wrt_date;
} FileEntry_t;

typedef struct
{
	uint32_t size;
	FileEntry_t *list;
} FileList_t;

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
FileList_t fat32_list_files(BootSector_t bs);
#endif