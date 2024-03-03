//Just returns the macro value .
#include "app_bootloader.h"

uint8_t get_bootloader_version(void) {
	return (uint8_t) BL_VERSION;
}

//Read the chip identifier or device Identifier
uint16_t get_mcu_chip_id(void) {
	/*
	 The STM32F446xx MCUs integrate an MCU ID code. This ID identifies the ST MCU partnumber
	 and the die revision. It is part of the DBG_MCU component and is mapped on the
	 external PPB bus (see Section 33.16 on page 1304). This code is accessible using the
	 JTAG debug pCat.2ort (4 to 5 pins) or the SW debug port (two pins) or by the user software.
	 It is even accessible while the MCU is under system reset. */
	uint16_t cid;
	cid = (uint16_t) (DBGMCU->IDCODE) & 0x0FFF;
	return cid;

}

/*This function reads the RDP ( Read protection option byte) value
 *For more info refer "Table 9. Description of the option bytes" in stm32f446xx RM
 */
uint8_t get_flash_rdp_level(void) {

	uint8_t rdp_status = 0;
#if 1
	FLASH_OBProgramInitTypeDef ob_handle;
	HAL_FLASHEx_OBGetConfig(&ob_handle);
	rdp_status = (uint8_t) ob_handle.RDPLevel;
#else

 	 volatile uint32_t *pOB_addr = (uint32_t*) 0x1FFFC000;
 	 rdp_status =  (uint8_t)(*pOB_addr >> 8) ;
 #endif

	return rdp_status;

}

//verify the address sent by the host .
uint8_t verify_address(uint32_t go_address) {
	//so, what are the valid addresses to which we can jump ?
	//can we jump to system memory ? yes
	//can we jump to sram1 memory ?  yes
	//can we jump to sram2 memory ? yes
	//can we jump to backup sram memory ? yes
	//can we jump to peripheral memory ? its possible , but dont allow. so no
	//can we jump to external memory ? yes.

	//incomplete -poorly written .. optimize it
	if (go_address >= SRAM1_BASE && go_address <= SRAM1_END) {
		return 1;
	} else if (go_address >= FLASH_BASE && go_address <= FLASH_END) {
		return 1;
	} else
		return 0;
}

uint8_t execute_mem_write(uint8_t *pBuffer, uint32_t mem_address, uint32_t len) {
	uint8_t status = HAL_OK;

	//We have to unlock flash module to get control of registers
	HAL_FLASH_Unlock();

	for (uint32_t i = 0; i < len; i++) {
		//Here we program the flash byte by byte
		status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, mem_address + i,
				pBuffer[i]);
	}

	HAL_FLASH_Lock();

	return (status == HAL_OK) ? 1 : 0;
}

uint8_t execute_flash_erase(uint8_t sector_number, uint8_t number_of_sector) {
	uint8_t totalSectors = 5;
	//we have totally 8 sectors in STM32F446RE mcu .. sector[0 to 7]
	//number_of_sector has to be in the range of 0 to 7
	// if sector_number = 0xff , that means mass erase !
	//Code needs to modified if your MCU supports more flash sectors
	FLASH_EraseInitTypeDef flashErase_handle;
	uint32_t sectorError;
	HAL_StatusTypeDef status;

	if (number_of_sector > totalSectors)
		return 0;

	if ((sector_number == 0xff) || (sector_number <= totalSectors - 1)) {
		if (sector_number == (uint8_t) 0xff) {
			flashErase_handle.TypeErase = FLASH_TYPEERASE_MASSERASE;
		} else {
			/*Here we are just calculating how many sectors needs to erased */
			uint8_t remanining_sector = totalSectors - sector_number;
			if (number_of_sector > remanining_sector) {
				number_of_sector = remanining_sector;
			}
			flashErase_handle.TypeErase = FLASH_TYPEERASE_SECTORS;
			flashErase_handle.Sector = sector_number; // this is the initial sector
			flashErase_handle.NbSectors = number_of_sector;
		}
		flashErase_handle.Banks = FLASH_BANK_1;

		/*Get access to touch the flash registers */
		HAL_FLASH_Unlock();
		flashErase_handle.VoltageRange = FLASH_VOLTAGE_RANGE_3; // our mcu will work on this voltage range
		status = (uint8_t) HAL_FLASHEx_Erase(&flashErase_handle, &sectorError);
		HAL_FLASH_Lock();

		return (status == HAL_OK) ? 1 : 0;
	}

	return 0;
}
