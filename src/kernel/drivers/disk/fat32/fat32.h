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
#define BYTS_PER_SEC_OFFSET		0x0B // 11 
#define SEC_PER_CLUS_OFFSET		0x0D // 13
#define RSVD_SEC_CNT_OFFSET		0x0E // 14
#define NUM_FATS_OFFSET			0x10 // 16
#define FATSZ32_OFFSET			0x24 // 36
#define ROOT_CLUS_OFFSET		0x2C // 44

// FILE ENTRY
#define NAME_OFFSET				0x00 // 00
#define ATTR_OFFSET				0x0B // 11
#define CRT_TIME_TENTH_OFFSET	0x0D // 13
#define CRT_TIME_OFFSET			0x0E // 14
#define CRT_DATE_OFFSET			0x10 // 16
#define LST_ACC_DATE_OFFSET		0x12 // 18
#define FST_CLUS_HI_OFFSET		0x14 // 20
#define WRT_TIME_OFFSET			0x16 // 22
#define WRT_DATE_OFFSET			0x18 // 24
#define FST_CLUS_LO_OFFSET		0x1A // 26
#define FILE_SIZE_OFFSET		0x1C // 28

#define FAT_MASK 0x0FFFFFFF
#define FAT_EOC  0x0FFFFFF8 // End Of Cluster mark. Means it's the last cluster of the file

// -------------- MACROS --------------
#define PARSE_INFO_INT(structure, info, buffer, offset)  memcpy(&structure.info, buffer+offset, sizeof(structure.info)); //swap_endian_int(&structure.info);
#define PARSE_INFO_LONG(structure, info, buffer, offset) memcpy(&structure.info, buffer+offset, sizeof(structure.info)); //swap_endian_long(&structure.info);
#define PARSE_INFO_CHAR(structure, info, buffer, offset) memcpy(&structure.info, buffer+offset, sizeof(structure.info));


// -------------- STRUCT --------------

// Most usefull info inside the boot sector
typedef struct 
{
	uint16_t  	byts_per_sec;		// Number of bytes per sector
	uint8_t 	sec_per_clus;		// Number of sector per clusters
	uint16_t  	rsvd_sec_cnt;		// Number of sector in the reserved region
	uint8_t 	num_FATs;			// Number of FAT Table
	uint32_t 	FATSz32;			// Size of one FAT Table
	uint32_t 	root_clus;			// Cluster number of the root dir
	uint16_t  	root_dir_sector;	// Not really in the boot sector, sector of the root dir
} BootSector_t;

// File entry descriptor (long name not supported yet)
typedef struct
{
	char		Name[11];			// Name of the file on the disk
	char 		clean_name[255];	// NOT IN THE FILE ENTRY
	uint32_t 	fst_clus;			// First cluster of the file
	uint32_t	file_size;			// Size of the file
	uint8_t		attr;				// File attributes
	uint8_t		crt_time_tenth;		// Millisecond stamp at file creation time.
	uint16_t	crt_time;			// Time file was created
	uint16_t	crt_date;			// Date file was created
	uint16_t	lst_acc_date;		// Last access date
	uint16_t	wrt_time;			// Time of last write
	uint16_t	wrt_date;			// Date of last write
} FileEntry_t;

typedef struct 
{
   uint32_t baseCluster;		// Cluster where the beginning of the file is
   uint32_t currentCluster;		// Cluster where we are curently
   uint32_t Offset;				// Offset in byte from the start of the file
   uint32_t fileSize;			// Size of the file
   uint8_t  currentSector;		// Current sector inside the cluster
} FilePointer_t;

typedef struct
{
	uint32_t size;				// Size of file in the list
	FileEntry_t *list; 			// List of file entires in the directory
} FileList_t;

// ------------ PROTOTYPES ------------

// !ABSTRACT FUNCTIONS in file "src/kernel/drivers/disk/ata/ata.c"
// uint8_t ata_read_byte(uint32_t addr, uint16_t offset);
// uint16_t ata_read_word(uint32_t addr, uint16_t offset);
// uint32_t ata_read_dword(uint32_t addr, uint16_t offset);

// void ata_write_byte(uint32_t addr, uint16_t offset, uint8_t value);
// void ata_write_word(uint32_t addr, uint16_t offset, uint16_t value);
// void ata_write_dword(uint32_t addr, uint16_t offset, uint32_t value);

// DEBUG FUNC
void fat32_dump_bs(BootSector_t bs);

void swap_endian_int(uint16_t *val);
void swap_endian_long(uint32_t *val);

BootSector_t fat32_parse_bootsector();
FileEntry_t  fat32_parse_fileentry(uint8_t *sector, uint16_t offset);

void clean_filename(char *filename, char *cleaned_filename);
FileList_t fat32_list_files(BootSector_t bs);

FilePointer_t fat32_openfile(BootSector_t bs, char *filename);

uint32_t fat32_get_next_cluster_value(BootSector_t bs);
uint32_t fat32_get_sector_from_cluster(BootSector_t bs, uint32_t cluster);
#endif