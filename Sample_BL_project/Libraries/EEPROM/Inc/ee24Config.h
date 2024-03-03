/*
 * ee24Config.h
 *
 *  Created on: May 16, 2023
 *      Author: hp
 */

#ifndef EEPROM_INC_EE24CONFIG_H_
#define EEPROM_INC_EE24CONFIG_H_

#define		_EEPROM_SIZE_KBIT							32
#define		_EEPROM_I2C   								hi2c1
#define		_EEPROM_USE_FREERTOS          0
#define		_EEPROM_ADDRESS               0xA0
#define		_EEPROM_USE_WP_PIN            1

#if (_EEPROM_USE_WP_PIN==1)
#define		_EEPROM_WP_GPIO								EE_WP_GPIO_Port
#define		_EEPROM_WP_PIN								EE_WP_Pin
#endif

#endif /* EEPROM_INC_EE24CONFIG_H_ */
