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

void ata_read_sector(uint32_t LBA, uint8_t sectorcount, uint8_t *out);
void ata_write_sector(uint32_t LBA, uint8_t sectorcount, uint8_t *in);

#endif
