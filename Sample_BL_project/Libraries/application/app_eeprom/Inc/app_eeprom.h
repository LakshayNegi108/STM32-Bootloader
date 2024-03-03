#ifndef APP_EEPROM_INC_APP_EEPROM_H_
#define APP_EEPROM_INC_APP_EEPROM_H_

#include "ee24.h"
#include "ee24Config.h"

typedef enum{
	eeAddr_eepromStart = 0x00,
	eeAddr_blUpdateStatus = eeAddr_eepromStart,
	eeAddr_blFileName = eeAddr_blUpdateStatus + 0x01,
	eeAddr_blfileNameLen = eeAddr_blFileName + 0x14,
	eeAddr_deviceID = eeAddr_blfileNameLen + 0x01,
	eeAddr_deviceIDLen = eeAddr_deviceID + 0x33,
	eeAddr_flsMax = eeAddr_deviceIDLen + 0x01,
	eeAddr_flsMin = eeAddr_flsMax + 0x02,
	eeAddr_mqttBrokerPort = eeAddr_flsMin + 0x02,
	eeAddr_mqttBrokerAddress = eeAddr_mqttBrokerPort + 0x02,
	eeAddr_mqttBrokerAddressLen = eeAddr_mqttBrokerAddress + 0x33,
	eeAddr_mqttClientID = eeAddr_mqttBrokerAddressLen + 0x01,
	eeAddr_mqttClientIDLen = eeAddr_mqttClientID + 0x14,
	eeAddr_mqttUserID = eeAddr_mqttClientIDLen + 0x01,
	eeAddr_mqttUserIDLen = eeAddr_mqttUserID + 0x14,
	eeAddr_mqttUserPassword = eeAddr_mqttUserIDLen + 0x01,
	eeAddr_mqttUserPasswordLen = eeAddr_mqttUserPassword + 0x14,
	eeAddr_topicPublish_1 = eeAddr_mqttUserPasswordLen + 0x01,
	eeAddr_topicPublish_1_Len = eeAddr_topicPublish_1 + 0x33,
	eeAddr_topicSubscribe = eeAddr_topicPublish_1_Len + 0x01,
	eeAddr_topicSubscribeLen = eeAddr_topicSubscribe + 0x33,
	eeAddr_headCommit = eeAddr_topicPublish_1_Len + 0x01,
	eeAddr_headCommitLen = eeAddr_headCommit + 0x32,
	eeAddr_currentBranch = eeAddr_headCommitLen + 0x01,
	eeAddr_currentBranchLen = eeAddr_currentBranch + 0x14,
	eeAddr_commitDate = eeAddr_currentBranchLen + 0x01,
	eeAddr_commitDateLen = eeAddr_commitDate + 0x14,
	eeAddr_projectName = eeAddr_commitDateLen + 0x01,
	eeAddr_projectNameLen = eeAddr_projectName + 0x14,
	eeAddr_mqttMsgFreq = eeAddr_projectNameLen + 0x04,
	eeAddr_recdConstPointStruct = eeAddr_mqttMsgFreq + 0x3F
}eepromAddr_e;

typedef struct{
	char BrokerAddress[51];
	uint8_t BROKER_ADDRESS_LEN;
	uint16_t brokerPort;
	char ClientID[21];
	uint8_t CLIENT_ID_LEN;
	char userID[21];
	uint8_t USER_ID_LEN;
	char userPassword[21];
	uint8_t USER_PASSWORD_LEN;
	char topicPublish[5][51];
	uint8_t TOPIC_PUBLISH_LEN[5];
	char topicSubscribe[51];
	uint8_t TOPIC_SUBSCRIBE_LEN;
	uint32_t messageFreq;
}mqttParam_Typedef;

typedef struct{
	char deviceID[50];
	uint8_t DEVICE_ID_LEN;
	mqttParam_Typedef mqtt;
} iotParam_Typedef;

typedef struct{
	char headCommit[50];
	char currentBranch[20];
	char commitDate[20];
	char projectName[20];
	uint8_t dataLen[4];
} gitDataTypedef;

typedef struct {
	uint16_t setPointP[2];
	uint16_t setPointT[2];
	uint16_t T_Amb;
	uint16_t EB1;
	uint16_t SLNCR_BP;
	uint16_t P_OEM;
} recdCPointsTypedef;

extern iotParam_Typedef iot;
extern gitDataTypedef gitData;
extern recdCPointsTypedef recdcp;

bool configIOTParameters(iotParam_Typedef *iot);
bool configRECDConstantPointSets(recdCPointsTypedef* recdcps);
void eeprom_git_data_reading();

bool ee_getDeviceID(char *str, size_t len);
bool ee_getDeviceIDLen(size_t *len);
bool ee_setDeviceID(char *str, size_t len);
bool ee_getBrokerPort(uint16_t *brokerPort);
bool ee_setBrokerPort(uint16_t brokerPort);
bool ee_getBrokerAddress(char *str, size_t len);
bool ee_getBrokerAddressLen(size_t *len);
bool ee_setBrokerAddress(char *str, size_t len);
bool ee_getMqttClientID(char *str, size_t len);
bool ee_getMqttClientIDLen(size_t *len);
bool ee_setMqttClientID(char *str, size_t len);
bool ee_getMqttUserID(char *str, size_t len);
bool ee_getMqttUserIDLen(size_t *len);
bool ee_setMqttUserID(char *str, size_t len);
bool ee_getMqttUserPassword(char *str, size_t len);
bool ee_getMqttUserPasswordLen(size_t *len);
bool ee_setMqttUserPassword(char *str, size_t len);
bool ee_getTopicPublish1(char *str, size_t len);
bool ee_getTopicPublish1Len(size_t *len);
bool ee_setTopicPublish1(char *str, size_t len);
bool ee_getTopicSubscribe(char *str, size_t len);
bool ee_getTopicSubscribeLen(size_t *len);
bool ee_setTopicSubscribe(char *str, size_t len);
bool ee_getMqttMsgFreq(uint32_t *freq);
bool ee_setMqttMsgFreq(uint32_t freq);
bool ee_setrecdcpStruct(recdCPointsTypedef *recdcp);
bool ee_getrecdcpStruct(recdCPointsTypedef *recdcp);

bool ee_getBLUpdateStatus(uint8_t* blust);
bool ee_setBLUpdateStatus(uint8_t blust);
bool ee_getBLFileNameLen(uint8_t *len);
bool ee_getBLFileName(char *str);
bool ee_setBLFileName(char *str, size_t len);

bool eeprom_iot_param_set(iotParam_Typedef *iot, char* devid, uint16_t devid_len, char* pub_topic, uint16_t pub_topic_len, uint32_t mqttFreq);

#endif /* APP_EEPROM_INC_APP_EEPROM_H_ */
