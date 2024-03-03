/*
 * app_IOT_AT.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Engineering
 */

#ifndef APP_IOT_AT_INC_APP_IOT_AT_H_
#define APP_IOT_AT_INC_APP_IOT_AT_H_

#include "usart.h"
#include "stdint.h"
#include "stdbool.h"
#include "app_eeprom.h"

typedef enum {
	isUnknownAT,
	isAT,
	isGetInfo,
	isGetBLUpdateStat,
	isSetBLUpdateStat,
	isGetBLFileName,
	isSetBLFileName,
	isGetDEVID,
	isSetDEVID,
	isGetPUBTOPIC,
	isSetPUBTOPIC,
	isGetSUBTOPIC,
	isSetSUBTOPIC,
	isGetBKRADDR,
	isSetBKRADDR,
	isGetBKRPORT,
	isSetBKRPORT,
	isGetCLIENTID,
	isSetCLIENTID,
	isGetUSERID,
	isSetUSERID,
	isGetPASSWORD,
	isSetPASSWORD,
	isGetRECDSetPoints,
	isSetRECDPressurePt,
	isSetRECDTempPt,
	isSetTAmb,
	isSetEB1,
	isSetSLNCR_BP,
	isSetP_OEM,
	isResetIOT,
} iot_atcmdtypedef;

typedef struct {
	iot_atcmdtypedef iotATCMD;
	char atCmd[100];
	uint8_t len;
} iot_atdatatypedef;

extern iot_atdatatypedef IOT_AT_DATA;

extern bool IOT_AT_REC_FLAG;

bool extractValueFromAT(const char *input, const char *command, char *value);
void iotATConfig(char *command, uint8_t len);
void SetDEVID(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetPUBTOPIC(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetBKRADDR(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetBKRPORT(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetCLIENTID(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetUSERID(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetPASSWORD(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot);
void SetPointTemp(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts);
void SetPointPressure(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts);
void SetTAMB(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts);
void SetEB1(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts);
void SetSLNCRBP(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts);
void SetPOEM(iot_atdatatypedef *IOT_AT, recdCPointsTypedef *recdconstpts);
void iotATHandler(iot_atdatatypedef *IOT_AT, iotParam_Typedef *iot,
		recdCPointsTypedef *recdconstpts);
void SetBLUpdateStatus(iot_atdatatypedef *IOT_AT) ;
void GetBLUpdateStatus(void);
void SetBLFileName(iot_atdatatypedef *IOT_AT);
void GetBLFileName(void);

void UART_AT_IT_EN();

#endif /* APP_IOT_AT_INC_APP_IOT_AT_H_ */
