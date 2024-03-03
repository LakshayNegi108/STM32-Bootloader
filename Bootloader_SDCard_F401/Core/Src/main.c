/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdarg.h"
#include "SDCard.h"
#include "app_bootloader.h"
#include "ee24.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

const char deffileName[30] = "Project1.bin";
char fileName[30] = { 0 };
uint8_t binData[1000] = { 0 };

sdcard_t SDCard = { 0 };
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void print(const char *fmt, ...) {
	static char buffer[256];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);

	uint16_t len = strlen(buffer);
	HAL_UART_Transmit(&huart2, buffer, len, 500);
}

bool checkFileSizeOk(uint32_t sz);

bool bootloader_upload_firmware(void);
void jump_to_user_application_code(void);

bool ee_getBLUpdateStatus(uint8_t* blust);
bool ee_setBLUpdateStatus(uint8_t blust);
bool ee_getBLFileNameLen(uint8_t *len);
bool ee_getBLFileName(char *str);
bool ee_setBLFileName(char *str, size_t len);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_SDIO_SD_Init();
	MX_USART2_UART_Init();
	MX_FATFS_Init();
	MX_I2C1_Init();
	/* USER CODE BEGIN 2 */
	print("Success: Working\n");
	print("Log: Now Entering in Bootloader.....\r\n");

	HAL_Delay(100);
	uint8_t bl_stat = 0;
	if (ee_getBLUpdateStatus(&bl_stat)) {
		if (bl_stat) {
			print("Log: New update found.\r\n");
			if(!ee_getBLFileName(fileName)){
				strncpy(fileName, deffileName, strlen(deffileName));
				print("Error: Couldn't fetch file name from eeprom.\r\nUsing Default File Name '%s'", fileName);
			}
			if(ee_setBLUpdateStatus(0)){
				print("Log: New Firmware Update in Progress.........\r\n");
				if (sd_mount(&SDCard, "/")) {
					SDCard.mounted = 1;
					print("Log: Mounted Successfully (%i)\r\n", SDCard.fres);
					if(!bootloader_upload_firmware()){
						ee_setBLUpdateStatus(1);
					}
					print("Log: Resetting MCU\r\n");
					NVIC_SystemReset();
				} else {
					SDCard.mounted = 0;
					print("ERROR: Mounting ERROR (%i)\r\n", SDCard.fres);
					ee_setBLUpdateStatus(1);
				}
			}
			else{
				goto user_app;
			}
		} else {
			print("Log: No update found.\r\n");
			print("Log: Jumping to application Code.........\r\n");
			jump_to_user_application_code();
		}
	} else {
		goto user_app;
	}
user_app:
	print("ERROR: Some Problem in reading Data from EEPROM.\r\n");
	print("Log: Jumping to application Code.........\r\n");
	jump_to_user_application_code();

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 16;
	RCC_OscInitStruct.PLL.PLLN = 192;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

void jump_to_user_application_code(void) {
	//just a function pointer to hold the address of the reset handler of the user app.
	void (*app_reset_handler)(void);

	print("Log: bootloader_jump_to_user_app\n");

	// 1. configure the MSP by reading the value from the base address of the sector 2
	uint32_t msp_value = *(volatile uint32_t*) FLASH_ADDR_APP;
	print("Log: MSP value : %#x\n", msp_value);

	//This function comes from CMSIS.
	__set_MSP(msp_value);

	//SCB->VTOR = FLASH_SECTOR1_BASE_ADDRESS;

	/* 2. Now fetch the reset handler address of the user application
	 * from the location FLASH_SECTOR2_BASE_ADDRESS+4
	 */
	uint32_t resethandler_address =
			*(volatile uint32_t*) (FLASH_ADDR_APP + 4);

	app_reset_handler = (void*) resethandler_address;

//	print("BL_DEBUG_MSG: app reset handler addr : %#x\n", app_reset_handler);

	//3. jump to reset handler of the user application
	app_reset_handler();
}

bool bootloader_upload_firmware(void) {
	if (sd_fileExists(&SDCard, fileName)) {
		sd_getFileInfo(&SDCard, fileName);
		uint32_t noBytes = SDCard.fno.fsize;
		print("Log: Total Size of File is : %d\r\n", noBytes);
		if(!checkFileSizeOk(noBytes)){
			print("Error: File Size exceed the flash by %d.\r\n", noBytes - FLASH_SIZE - FLASH_BL_SIZE);
			return false;
		}
		if(!execute_flash_erase(3, 2)){
			print("Error: Could not erase flash memory.\r\n");
			return false;
		}
		else{
			print("Log: Erasing Flash Memory from 0x%X to 0x%X.\r\n", FLASH_ADDR_APP, FLASH_ADDR_APP + FLASH_SIZE - FLASH_BL_SIZE - 1);
		}

		uint32_t seekPtr = 0;
		while (noBytes) {
			seekPtr = SDCard.fil.fptr;
			if (noBytes >= 1000)
				if (sd_fileseekread(&SDCard, fileName, seekPtr, binData,
						1000)) {
					noBytes -= SDCard.br;
					print("Log: Data Reading Success at Addr: %X, %d\r\n",
							SDCard.fil.fptr, SDCard.fil.fptr);
				} else {
					print("ERROR: Data Reading Failed at Addr: %X, %d\r\n",
							SDCard.fil.fptr, SDCard.fil.fptr);
				}
			else if (sd_fileseekread(&SDCard, fileName, seekPtr, binData,
					noBytes)) {
				noBytes -= SDCard.br;
				print("Log: Data Reading Success at Addr: %X, %d\r\n",
						SDCard.fil.fptr, SDCard.fil.fptr);
			} else {
				print("Error: Data Reading Failed at Addr: %X, %d\r\n",
						SDCard.fil.fptr, SDCard.fil.fptr);
			}
//			print("Log: Loc Addr: 0x%X\r\n", FLASH_ADDR_APP + seekPtr);
			if(execute_mem_write(binData, FLASH_ADDR_APP + seekPtr, SDCard.br)){
				print("Success: Data written to flash at addr: 0x%X.\r\n", FLASH_ADDR_APP + seekPtr);
			}
			else{
				print("Error: Could not write to flash at addr: 0x%X.\r\n", FLASH_ADDR_APP + seekPtr);
				return false;
			}
			memset(binData, 0, sizeof(binData));
		}
		return true;
	}
		return false;
}

bool ee_getBLUpdateStatus(uint8_t *blust) {
	if (ee24_isConnected()) {
		if (ee24_read(0, blust, 1, 200)) {
			return true;
		}
	}
	return false;
}

bool ee_setBLUpdateStatus(uint8_t blust) {
	if (ee24_isConnected()) {
		if (ee24_write(0, &blust, 1, 500)) {
			return true;
		}
	}
	return false;
}

bool ee_getBLFileNameLen(uint8_t *len) {
	if (ee24_isConnected()) {
		if (ee24_read(21, len, 1, 200)) {
			return true;
		}
	}
	return false;
}

bool ee_getBLFileName(char *str) {
	if (ee24_isConnected()) {
		uint8_t flen = 0;
		if (ee_getBLFileNameLen(&flen)) {
			if (ee24_read(1, str, flen, 200)) {
				return true;
			}
		}
	}
	return false;
}

bool ee_setBLFileName(char *str, size_t len) {

	if (ee24_isConnected()) {
		if (!ee24_write(1, str, len, 200)) {
			return false;
		}
		if (!ee24_write(21, &len, 1, 200)) {
			return false;
		}
		return true;
	}
	return false;
}

bool checkFileSizeOk(uint32_t sz){
	if((FLASH_SIZE - FLASH_BL_SIZE) > sz){
		return true;
	}
	else{
		return false;
	}
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
