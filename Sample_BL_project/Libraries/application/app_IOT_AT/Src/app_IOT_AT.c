#include "app_IOT_AT.h"

iot_atdatatypedef IOT_AT_DATA;

#define configRxBufLen  250
char configRxBuf[configRxBufLen] = { 0 };

bool IOT_AT_REC_FLAG = false;

#define IOT_AT_UART	huart2

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size) {
	if (huart->Instance == IOT_AT_UART.Instance) {
//		HAL_UART_Transmit(&IOT_AT_UART, configRxBuf, Size, 1000);
		iotATConfig(configRxBuf, Size);
		memset(configRxBuf, '\0', configRxBufLen);
		IOT_AT_REC_FLAG = true;
		/* start the IT again */
		HAL_UARTEx_ReceiveToIdle_IT(&IOT_AT_UART, configRxBuf, configRxBufLen);
	}
}

bool extractValueFromAT(const char *input, const char *command, char *value) {
	// Find the position of the command in the input string
	const char *start = strstr(input, command);
	if (start != NULL) {
		// Move the pointer to the first character after the command
		start += strlen(command) + 1;
		// Find the position of the double quote (")
		const char *end = strchr(start, '"');
		if (end != NULL) {
			// Calculate the length of the value
			size_t length = end - start;

			// Check if the length is within bounds
			if (length > 0 && length < 256) { // Adjust the upper bound as needed
			// Copy the value to the buffer and null-terminate it
				strncpy(value, start, length);
				value[length] = '\0';

				return true; // Successful extraction
			}
		}
	}
	return false; // Extraction failed
}

void iotATConfig(char *command, uint8_t len) {
	strncpy(IOT_AT_DATA.atCmd, command, len);
	IOT_AT_DATA.len = len;
	if (strcmp(command, "AT\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isAT;
	} else if (strcmp(command, "AT+BLUP?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetBLUpdateStat;
	} else if (strncmp(command, "AT+BLUP=", 8) == 0) {
		IOT_AT_DATA.iotATCMD = isSetBLUpdateStat;
	} else if (strcmp(command, "AT+BLFLN?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetBLFileName;
	} else if (strncmp(command, "AT+BLFLN=", 9) == 0) {
		IOT_AT_DATA.iotATCMD = isSetBLFileName;
	} else if (strcmp(command, "AT+DEVID?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetDEVID;
	} else if (strncmp(command, "AT+DEVID=", 9) == 0) {
		IOT_AT_DATA.iotATCMD = isSetDEVID;
	} else if (strcmp(command, "AT+PUBTOPIC?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetPUBTOPIC;
	} else if (strncmp(command, "AT+PUBTOPIC=", 12) == 0) {
		IOT_AT_DATA.iotATCMD = isSetPUBTOPIC;
	} else if (strcmp(command, "AT+BKRADDR?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetBKRADDR;
	} else if (strncmp(command, "AT+BKRADDR=", 11) == 0) {
		IOT_AT_DATA.iotATCMD = isSetBKRADDR;
	} else if (strcmp(command, "AT+BKRPORT?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetBKRPORT;
	} else if (strncmp(command, "AT+BKRPORT=", 11) == 0) {
		IOT_AT_DATA.iotATCMD = isSetBKRPORT;
	} else if (strcmp(command, "AT+CLNTID?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetCLIENTID;
	} else if (strncmp(command, "AT+CLNTID=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetCLIENTID;
	} else if (strcmp(command, "AT+MUID?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetUSERID;
	} else if (strncmp(command, "AT+MUID=", 8) == 0) {
		IOT_AT_DATA.iotATCMD = isSetUSERID;
	} else if (strcmp(command, "AT+MUPWD?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetPASSWORD;
	} else if (strncmp(command, "AT+MUPWD=", 9) == 0) {
		IOT_AT_DATA.iotATCMD = isSetPASSWORD;
	} else if (strcmp(command, "AT+SUBTOPIC?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetSUBTOPIC;
	} else if (strncmp(command, "AT+SUBTOPIC=", 9) == 0) {	//
		IOT_AT_DATA.iotATCMD = isSetSUBTOPIC;
	} else if (strcmp(command, "AT+RECDSETPOINTS?\r\n") == 0) {
		IOT_AT_DATA.iotATCMD = isGetRECDSetPoints;
	} else if (strncmp(command, "AT+SETCTP=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetRECDPressurePt;
	} else if (strncmp(command, "AT+SETCTT=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetRECDTempPt;
	} else if (strncmp(command, "AT+SETTAMB=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetTAmb;
	} else if (strncmp(command, "AT+SETEB1=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetEB1;
	} else if (strncmp(command, "AT+SETSLNCRBP=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetSLNCR_BP;
	} else if (strncmp(command, "AT+SETP_OEM=", 10) == 0) {
		IOT_AT_DATA.iotATCMD = isSetP_OEM;
	} else if (strcmp(command, "AT+RESET\r\n") == 0) {		// Reset
		IOT_AT_DATA.iotATCMD = isResetIOT;
	} else {
		IOT_AT_DATA.iotATCMD = isUnknownAT;
	}
}

void SetDEVID(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+DEVID=\"%50[^\"]\"", iot->deviceID);
	if (result == 1) {
		iot->DEVICE_ID_LEN = strlen(iot->deviceID);
		if (ee_setDeviceID(iot->deviceID, iot->DEVICE_ID_LEN)) {
			sprintf(txBuffer, "'%s' successfully set as Device ID\r\nOK\r\n",
					iot->deviceID);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
			char mbuf[50];
			snprintf(mbuf, 7 + iot->DEVICE_ID_LEN + 1, "device/%s",
					iot->deviceID);
			if (ee_setTopicSubscribe(mbuf, strlen(mbuf))) {
				sprintf(txBuffer,
						"'%s'is updated as topic subscribed by device\r\nOK\r\n",
						mbuf);
				HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer),
						200);
				snprintf(iot->mqtt.topicSubscribe, strlen(mbuf) + 1, "%s",
						mbuf);
			} else {
				sprintf(txBuffer,
						"Could not update Topic Subscribe\r\nERROR\r\n");
				HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer),
						200);
			}
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetPUBTOPIC(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+PUBTOPIC=\"%50[^\"]\"",
			iot->mqtt.topicPublish);
	if (result == 1) {
		if (ee_setTopicPublish1(iot->mqtt.topicPublish,
				iot->mqtt.TOPIC_PUBLISH_LEN[0])) {
			iot->mqtt.TOPIC_PUBLISH_LEN[0] = strlen(iot->mqtt.topicPublish);
			sprintf(txBuffer,
					"'%s' successfully set Topic to publish\r\nOK\r\n",
					iot->mqtt.topicPublish);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetSUBTOPIC(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+SUBTOPIC=\"%50[^\"]\"",
			iot->mqtt.topicSubscribe);
	if (result == 1) {
		iot->mqtt.TOPIC_SUBSCRIBE_LEN = strlen(iot->mqtt.topicSubscribe);
		if (ee_setTopicSubscribe(iot->mqtt.topicSubscribe,
				iot->mqtt.TOPIC_SUBSCRIBE_LEN)) {
			sprintf(txBuffer,
					"'%s' successfully set Topic to subscribe\r\nOK\r\n",
					iot->mqtt.topicSubscribe);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetBKRADDR(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+BKRADDR=\"%50[^\"]\"",
			iot->mqtt.BrokerAddress);
	if (result == 1) {
		iot->mqtt.BROKER_ADDRESS_LEN = strlen(iot->mqtt.BrokerAddress);
		if (ee_setBrokerAddress(iot->mqtt.BrokerAddress,
				iot->mqtt.BROKER_ADDRESS_LEN)) {
			sprintf(txBuffer,
					"'%s' successfully set as Broker Address\r\nOK\r\n",
					iot->mqtt.BrokerAddress);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetBKRPORT(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+BKRPORT=\"%d\"",
			&iot->mqtt.brokerPort);
	if (result == 1) {
		if (ee_setBrokerPort(iot->mqtt.brokerPort)) {
			sprintf(txBuffer, "'%d' successfully set as Broker Port\r\nOK\r\n",
					iot->mqtt.brokerPort);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetCLIENTID(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+CLNTID=\"%50[^\"]\"",
			iot->mqtt.ClientID);
	if (result == 1) {
		iot->mqtt.CLIENT_ID_LEN = strlen(iot->mqtt.ClientID);
		if (ee_setMqttClientID(iot->mqtt.ClientID, iot->mqtt.CLIENT_ID_LEN)) {
			sprintf(txBuffer, "'%s' successfully set as Client ID\r\nOK\r\n",
					iot->mqtt.ClientID);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetUSERID(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+MUID=\"%20[^\"]\"",
			iot->mqtt.userID);
	if (result == 1) {
		iot->mqtt.USER_ID_LEN = strlen(iot->mqtt.userID);
		if (ee_setMqttUserID(iot->mqtt.userID, iot->mqtt.USER_ID_LEN)) {
			sprintf(txBuffer, "'%s' successfully set as User ID\r\nOK\r\n",
					iot->mqtt.userID);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetPASSWORD(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+MUPWD=\"%20[^\"]\"",
			iot->mqtt.userPassword);
	if (result == 1) {
		iot->mqtt.USER_PASSWORD_LEN = strlen(iot->mqtt.userPassword);
		if (ee_setMqttUserPassword(iot->mqtt.userPassword,
				iot->mqtt.USER_PASSWORD_LEN)) {
			sprintf(txBuffer,
					"'%s' successfully set as User Password\r\nOK\r\n",
					iot->mqtt.userPassword);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetPointTemp(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	uint16_t data1 = 0, data2 = 0;
	int result = sscanf(IOT_AT->atCmd, "AT+SETCTT=\"%d,%d\"", &data1, &data2);
	if (result == 2) {
		recdconstpts->setPointT[0] = data1;
		recdconstpts->setPointT[1] = data2;
		if (ee_setrecdcpStruct(recdconstpts)) {
			sprintf(txBuffer,
					"'%d and %d' successfully set as 'T01' and 'T02'\r\nOK\r\n",
					data1, data2);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nError\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetPointPressure(iot_atdatatypedef *IOT_AT,
		recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	uint16_t data1 = 0, data2 = 0;
	int result = sscanf(IOT_AT->atCmd, "AT+SETCTP=\"%d,%d\"", &data1, &data2);
	if (result == 2) {
		recdconstpts->setPointP[0] = data1;
		recdconstpts->setPointP[1] = data2;
		if (ee_setrecdcpStruct(recdconstpts)) {
			sprintf(txBuffer,
					"'%d and %d' successfully set as 'P01' and 'P02'\r\nOK\r\n",
					data1, data2);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nError\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetTAMB(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+SETTAMB=\"%d\"",
			&recdconstpts->T_Amb);
	if (result == 1) {
		if (ee_setrecdcpStruct(recdconstpts)) {
			sprintf(txBuffer, "'%d' successfully set as T_Amb\r\nOK\r\n",
					recdconstpts->T_Amb);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetEB1(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+SETEB1=\"%d\"", &recdconstpts->EB1);
	if (result == 1) {
		if (ee_setrecdcpStruct(recdconstpts)) {
			sprintf(txBuffer, "'%d' successfully set as EB1\r\nOK\r\n",
					recdconstpts->EB1);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetSLNCRBP(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+SETSLNCRBP=\"%d\"",
			&recdconstpts->SLNCR_BP);
	if (result == 1) {
		if (ee_setrecdcpStruct(recdconstpts)) {
			sprintf(txBuffer, "'%d' successfully set as SLNCR_BP\r\nOK\r\n",
					recdconstpts->SLNCR_BP);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetPOEM(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	int result = sscanf(IOT_AT->atCmd, "AT+SETP_OEM=\"%d\"",
			&recdconstpts->P_OEM);
	if (result == 1) {
		if (ee_setrecdcpStruct(recdconstpts)) {
			sprintf(txBuffer, "'%d' successfully set as P_OEM\r\nOK\r\n",
					recdconstpts->P_OEM);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetBLUpdateStatus(iot_atdatatypedef *IOT_AT) {
	char txBuffer[250];
	uint8_t BLupStat = 0;
	int result = sscanf(IOT_AT->atCmd, "AT+BLUP=\"%d\"", &BLupStat);
	if (result == 1) {
		if (ee_setBLUpdateStatus(BLupStat)) {
			sprintf(txBuffer, "'%d' successfully Bootload Mode.\r\nOK\r\n",
					BLupStat);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void GetBLUpdateStatus(void) {
	char txBuffer[250];
	uint8_t stat = 0;
	if(ee_getBLUpdateStatus(&stat)){
		sprintf(txBuffer, "'%d' is the state of bootloader on Bootup.\r\nOK\r\n", stat);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
	else{
		sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void SetBLFileName(iot_atdatatypedef *IOT_AT) {
	char txBuffer[250];
	char blfln[20];
	uint8_t flen = 0;
	int result = sscanf(IOT_AT->atCmd, "AT+BLFLN=\"%20[^\"]\"", blfln);
	if (result == 1) {
		flen = strlen(blfln);
		if (ee_setBLFileName(blfln, flen)) {
			sprintf(txBuffer, "'%s' successfully set as Bootup file name.\r\nOK\r\n",
					blfln);
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		} else {
			sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
			HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		}
	} else {
		sprintf(txBuffer, "Incorrect Command\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void GetBLFileName(void) {
	char txBuffer[250];
	char flchr[20] = { 0 };
	uint8_t flen = 0;
	if (ee_getBLFileName(flchr)) {
		sprintf(txBuffer, "'%s' is the name of Bootup file name.\r\nOK\r\n", flchr);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
	else{
		sprintf(txBuffer, "EEPROM not responding\r\nERROR\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
	}
}

void iotATHandler(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot,
		recdCPointsTypedef *recdconstpts) {
	char txBuffer[250];
	char extractedVal[50];
	IOT_AT_REC_FLAG = false;
	switch (IOT_AT->iotATCMD) {
	case isAT:
		sprintf(txBuffer, "AT\r\nOK\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isGetBLFileName:
		GetBLFileName();
		break;
	case isSetBLFileName:
		SetBLFileName(IOT_AT);
		break;
	case isGetBLUpdateStat:
		GetBLUpdateStatus();
		break;
	case isSetBLUpdateStat:
		SetBLUpdateStatus(IOT_AT);
		break;
	case isGetDEVID:
		sprintf(txBuffer, "Current Device ID: %s\r\nOK\r\n", iot->deviceID);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetDEVID:
		SetDEVID(IOT_AT, iot);
		break;
	case isGetPUBTOPIC:
		sprintf(txBuffer, "Publishing at Topic: \"%s\"\r\nOK\r\n",
				iot->mqtt.topicPublish);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetPUBTOPIC:
		SetPUBTOPIC(IOT_AT, iot);
		break;
	case isGetSUBTOPIC:
		sprintf(txBuffer, "Subscribed at Topic: \"%s\"\r\nOK\r\n",
				iot->mqtt.topicSubscribe);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetSUBTOPIC:
		SetSUBTOPIC(IOT_AT, iot);
		break;
	case isGetBKRADDR:
		sprintf(txBuffer, "Broker Address is: \"%s\"\r\nOK\r\n",
				iot->mqtt.BrokerAddress);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetBKRADDR:
		SetBKRADDR(IOT_AT, iot);
		break;
	case isGetBKRPORT:
		sprintf(txBuffer, "Broker Port is: \"%d\"\r\nOK\r\n",
				iot->mqtt.brokerPort);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetBKRPORT:
		SetBKRPORT(IOT_AT, iot);
		break;
	case isGetCLIENTID:
		sprintf(txBuffer, "Client ID is: \"%s\"\r\nOK\r\n", iot->mqtt.ClientID);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetCLIENTID:
		SetCLIENTID(IOT_AT, iot);
		break;
	case isGetUSERID:
		sprintf(txBuffer, "MQTT User ID is: \"%s\"\r\nOK\r\n",
				iot->mqtt.userID);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetUSERID:
		SetUSERID(IOT_AT, iot);
		break;
	case isGetPASSWORD:
		sprintf(txBuffer, "MQTT User Password is: \"%s\"\r\nOK\r\n",
				iot->mqtt.userPassword);
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		break;
	case isSetPASSWORD:
		SetPASSWORD(IOT_AT, iot);
		break;
	case isGetRECDSetPoints:
		char txBigBuffer[1000];
		sprintf(txBigBuffer,
				"RECD Data: \nP01-%d, P02-%d\nT01-%d, T02-%d\nT_Amb-%d, EB1-%d, SLNCR_BP-%d, P_OEM-%d\r\nOK\r\n",
				recdconstpts->setPointP[0], recdconstpts->setPointP[1],
				recdconstpts->setPointT[0], recdconstpts->setPointT[1],
				recdconstpts->T_Amb, recdconstpts->EB1, recdconstpts->SLNCR_BP,
				recdconstpts->P_OEM);
		HAL_UART_Transmit(&IOT_AT_UART, txBigBuffer, strlen(txBigBuffer), 500);
		break;
	case isSetRECDPressurePt:
		SetPointPressure(IOT_AT, recdconstpts);
		break;
	case isSetRECDTempPt:
		SetPointTemp(IOT_AT, recdconstpts);
		break;
	case isSetTAmb:
		SetTAMB(IOT_AT, recdconstpts);
		break;
	case isSetEB1:
		SetEB1(IOT_AT, recdconstpts);
		break;
	case isSetSLNCR_BP:
		SetSLNCRBP(IOT_AT, recdconstpts);
		break;
	case isSetP_OEM:
		SetPOEM(IOT_AT, recdconstpts);
		break;
	case isResetIOT:
		sprintf(txBuffer, "Resetting IOT\r\n");
		HAL_UART_Transmit(&IOT_AT_UART, txBuffer, strlen(txBuffer), 200);
		NVIC_SystemReset();
		break;
	case isUnknownAT:
		HAL_UART_Transmit(&IOT_AT_UART, "Unknown AT command\r\n", 20, 100);
		break;
	default:
		HAL_UART_Transmit(&IOT_AT_UART, "Error in command\r\n", 18, 100);
		break;
	}
}

void UART_AT_IT_EN() {
	HAL_UARTEx_ReceiveToIdle_IT(&IOT_AT_UART, configRxBuf, configRxBufLen);
}
