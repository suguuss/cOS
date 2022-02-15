/**
 * @file fat32.c
 * @brief FAT32 LIB
 * @version 0.1
 * @date 13-02-2022
 */

#include "fat32.h"
#include "../ata/ata.h"


/**
 * @brief Parse the boot sector and stores the most important
 * informations inside a BootSector struct
 * 
 * @return BootSector information
 */
BootSector fat32_parse_bootsector()
{
	BootSector bs;

	bs.BytsPerSec 	= ata_read_word(0, BYTSPERSEC_OFFSET);
	bs.SecPerClus 	= ata_read_byte(0, SECPERCLUS_OFFSET);
	bs.RsvdSecCnt 	= ata_read_word(0, RSVDSECCNT_OFFSET);
	bs.NumFATs 		= ata_read_byte(0, NUMFATS_OFFSET);
	bs.FATSz32 		= ata_read_dword(0, FATSz32_OFFSET);
	bs.RootClus 	= ata_read_dword(0, ROOTCLUS_OFFSET);

	bs.RootDirSector = bs.RsvdSecCnt + (bs.NumFATs * bs.FATSz32);

	return bs;
}


