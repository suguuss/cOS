/**
 * @file ata.h
 * @brief DISK READ AND WRITE 
 * @version 0.1
 * @date 02-02-2022
 */

#ifndef __ATA_H__
#define __ATA_H__

#include <stdint.h>
#include "../../ports/ports.h"

#define DATA_REG	0x1F0
#define STATUS_REG 	0x1F7
#define DRQ_BIT 	0x08
#define BSY_BIT 	0x80

void ata_read_sector(uint32_t LBA, uint8_t sectorcount, uint8_t *out);

#endif
