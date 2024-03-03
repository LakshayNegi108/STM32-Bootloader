#ifndef EEPROM_INC_EE24_H_
#define EEPROM_INC_EE24_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ee24Config.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

bool    ee24_isConnected(void);
bool    ee24_write(uint16_t address, uint8_t *data, size_t lenInBytes, uint32_t timeout);
bool    ee24_read(uint16_t address, uint8_t *data, size_t lenInBytes, uint32_t timeout);
bool    ee24_eraseChip(void);

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_INC_EE24_H_ */
