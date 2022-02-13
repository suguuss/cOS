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

uint8_t ata_read_byte(uint32_t addr, uint16_t offset);
uint16_t ata_read_word(uint32_t addr, uint16_t offset);
uint32_t ata_read_dword(uint32_t addr, uint16_t offset);

#endif
