/**
 * @file fat32.c
 * @brief FAT32 LIB
 * @version 0.1
 * @date 13-02-2022
 */

#include "fat32.h"
#include "../ata/ata.h"
#include "../../../stdlibs/string.h"
#include "../../../stdlibs/stdlib.h"
#include "../../screen/print/print.h"

uint32_t g_current_dir_sector = 0;
uint32_t g_current_cluster_value = 0;

/**
 * @brief Change the endiannes of a value (16 bits)
 * @param uin16_t The value to modify
 */
void swap_endian_int(uint16_t *val)
{
	*val = (*val << 8) | (*val >> 8);
}

/**
 * @brief Change the endiannes of a value (32 bits)
 * @param uin32_t The value to modify
 */
void swap_endian_long(uint32_t *val)
{
	*val = (*val << 24) | ((*val << 8) & 0x00ff0000) | ((*val >> 8) & 0x0000ff00) | (*val >> 24);
}

/**
 * @brief Parse the boot sector and stores the most important
 * informations inside a BootSector struct
 * 
 * @return BootSector_t information
 */
BootSector_t fat32_parse_bootsector()
{
	BootSector_t bs;

	bs.byts_per_sec 	= ata_read_word(0, BYTS_PER_SEC_OFFSET);
	bs.sec_per_clus 	= ata_read_byte(0, SEC_PER_CLUS_OFFSET);
	bs.rsvd_sec_cnt 	= ata_read_word(0, RSVD_SEC_CNT_OFFSET);
	bs.num_FATs 		= ata_read_byte(0, NUM_FATS_OFFSET);
	bs.FATSz32 		= ata_read_dword(0, FATSZ32_OFFSET);
	bs.root_clus 	= ata_read_dword(0, ROOT_CLUS_OFFSET);

	bs.root_dir_sector = bs.rsvd_sec_cnt + (bs.num_FATs * bs.FATSz32);

	g_current_dir_sector = bs.root_dir_sector;
	g_current_cluster_value = bs.root_clus;

	return bs;
}

/**
 * @brief Parse a file entry and return a struct with the infos
 * @param uint8_t* Pointer to the sector of the disk where the entry is
 * @param uint16_t offset of the entry from the begining of the sector (must be multiple of 32)
 * @return FileEntry_t File entry informations
 */
FileEntry_t fat32_parse_fileentry(uint8_t *sector, uint16_t offset)
{
	FileEntry_t tmpEntry;

	PARSE_INFO_CHAR(tmpEntry, Name,         sector, NAME_OFFSET + offset)
	PARSE_INFO_CHAR(tmpEntry, attr, sector, ATTR_OFFSET + offset)
	PARSE_INFO_CHAR(tmpEntry, crt_time_tenth, sector, CRT_TIME_TENTH_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, crt_time,      sector, CRT_TIME_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, crt_date,      sector, CRT_DATE_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, lst_acc_date,   sector, LST_ACC_DATE_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, fst_clus_hi,    sector, FST_CLUS_HI_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, wrt_time,      sector, WRT_TIME_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, wrt_date,      sector, WRT_DATE_OFFSET + offset)
	PARSE_INFO_INT (tmpEntry, fst_clus_lo,    sector, FST_CLUS_LO_OFFSET + offset)
	PARSE_INFO_LONG(tmpEntry, file_size,     sector, FILE_SIZE_OFFSET + offset)

	return tmpEntry;
}

/**
 * @brief Change the filename read on the disk to make it more readable
 * TEXT    TXT --> text.txt
 * @param uint8_t* Pointer to the sector of the disk where the entry is
 * @return uint8_t Number of char in the cleaned filename
 */
uint8_t clean_filename(uint8_t* filename)
{
	uint8_t tmpChar;
	uint8_t cleanCharCnt = 0;

	// CLEAN THE NAME OF THE FILE
	for (uint8_t i = 0; i < 11; i++)
	{
		// ADDS THE . ONCE WE'VE CLEANED THE NAME
		if (i == 8)
		{
			filename[cleanCharCnt] = '.';
			cleanCharCnt++;
		}

		tmpChar = filename[i];

		// Make the char lowercase if it's a letter
		if ((tmpChar >= 'A') && (tmpChar <= 'Z') )
		{
			tmpChar  += 0x20;
		}

		// If the char is not a space add it to the final filename
		if (tmpChar != ' ')
		{
			filename[cleanCharCnt] = tmpChar;
			cleanCharCnt++;
		}
	}

	// Add the zero terminal
	filename[cleanCharCnt] = 0;
	return cleanCharCnt;
}

/**
 * @brief Returns a list of all the files in the current directory
 * @param BootSector_t* Bootsector struct
 * @return FileEntry_t* List of file entries
 */
FileList_t fat32_list_files(BootSector_t bs)
{
	uint8_t *sector = malloc(512);
	uint16_t entry_offset = 0;
	uint16_t file_count = 0;
	// Allocate enough space for 16 files. Realloc if needed
	FileEntry_t *file_list_array = malloc(sizeof(FileEntry_t) * (bs.byts_per_sec / 32));

	// TODO : ADD MULTI CLUSTER SUPPORT

	// Iterates all the sector inside a cluster
	for (uint32_t sec = 0; sec < bs.sec_per_clus; sec++)
	{
		ata_read_sector(g_current_dir_sector + sec, 1, sector);

		// The first entry of the Root Directory is not a real entry and needs to be skipped
		if (g_current_dir_sector + sec == bs.root_dir_sector) {entry_offset = 32;}

		for (entry_offset; entry_offset < bs.byts_per_sec; entry_offset+=32)
		{
			file_list_array[file_count] = fat32_parse_fileentry(sector, entry_offset);

			if (file_list_array[file_count].Name[0] == 0x00) 
			{
				file_list_array = realloc(file_list_array, sizeof(FileEntry_t) * file_count);
				FileList_t list;
				list.list = file_list_array;
				list.size = file_count;
				return list;
			}
			else if (file_list_array[file_count].Name[0] == 0xE5);	// Deleted file
			else if (file_list_array[file_count].Name[2] == 0x00);	// Long file entry not supported
			else {file_count++;}									// Valid file
		}
	}
}

/**
 * @brief Checks the FAT Table and returns the next cluster value (of g_current_cluster_value)
 * @param BootSector_t bs
 * @return uint32_t
 */
uint32_t fat32_get_next_cluster_value(BootSector_t bs)
{
	uint32_t fat_offset = g_current_cluster_value * 4;
	return FAT_MASK & ata_read_dword(bs.rsvd_sec_cnt + (fat_offset / bs.byts_per_sec), fat_offset % bs.byts_per_sec);
}