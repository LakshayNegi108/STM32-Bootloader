/*
 * app_bootloader.h
 *
 *  Created on: Mar 2, 2024
 *      Author: Lakshay
 */

#ifndef APP_BOOTLOADER_INC_APP_BOOTLOADER_H_
#define APP_BOOTLOADER_INC_APP_BOOTLOADER_H_

#include "stm32f4xx_hal.h"
#include "main.h"
#include "stdint.h"

//version 1.0
#define BL_VERSION 0x10

#define FLASH_ADDR_BL	0x08000000U
#define FLASH_ADDR_APP	0x0800C000U

/*Some Start and End addresses of different memories of STM32F446xx MCU */
/*Change this according to your MCU */
#define SRAM1_SIZE             64*1024     // STM32F446RE has 112KB of SRAM1
#define SRAM1_END              (SRAM1_BASE + SRAM1_SIZE)
#define FLASH_SIZE             128*1024     // STM32F401RB has 128KB of Flash
#define FLASH_BL_SIZE          48*1024

uint8_t get_bootloader_version(void);
uint16_t get_mcu_chip_id(void);
uint8_t get_flash_rdp_level(void);
uint8_t verify_address(uint32_t go_address);

uint8_t execute_mem_write(uint8_t *pBuffer, uint32_t mem_address, uint32_t len);
uint8_t execute_flash_erase(uint8_t sector_number, uint8_t number_of_sector);

#endif /* APP_BOOTLOADER_INC_APP_BOOTLOADER_H_ */
