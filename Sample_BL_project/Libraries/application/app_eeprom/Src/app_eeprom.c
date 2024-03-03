#include "app_eeprom.h"

bool ee_getDeviceID(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_deviceID, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getDeviceIDLen(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_deviceIDLen, len, 1, 200)){				//TODO: Replace 1 with size_t
			return true;
		}
	}
	return false;
}

bool ee_setDeviceID(char *str, size_t len){
//	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_deviceID, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_deviceIDLen, &len, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getBrokerPort(uint16_t *brokerPort){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttBrokerPort, brokerPort, 2, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setBrokerPort(uint16_t brokerPort){
	if(ee24_isConnected()){
		if(ee24_write(eeAddr_mqttBrokerPort, &brokerPort, 2, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getBrokerAddress(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttBrokerAddress, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getBrokerAddressLen(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttBrokerAddressLen, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setBrokerAddress(char *str, size_t len){
	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_mqttBrokerAddress, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_mqttBrokerAddressLen, setLen, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getMqttClientID(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttClientID, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getMqttClientIDLen(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttClientIDLen, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setMqttClientID(char *str, size_t len){
	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_mqttClientID, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_mqttClientIDLen, setLen, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getMqttUserID(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttUserID, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getMqttUserIDLen(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttUserIDLen, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setMqttUserID(char *str, size_t len){
	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_mqttUserID, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_mqttUserIDLen, setLen, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getMqttUserPassword(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttUserPassword, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getMqttUserPasswordLen(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttUserPasswordLen, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setMqttUserPassword(char *str, size_t len){
	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_mqttUserPassword, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_mqttUserPasswordLen, setLen, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getTopicPublish1(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_topicPublish_1, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getTopicPublish1Len(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_topicPublish_1_Len, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setTopicPublish1(char *str, size_t len){
	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_topicPublish_1, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_topicPublish_1_Len, setLen, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getTopicSubscribe(char *str, size_t len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_topicSubscribe, str, len, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getTopicSubscribeLen(size_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_topicSubscribeLen, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setTopicSubscribe(char *str, size_t len){
//	size_t *setLen = &len;
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_topicSubscribe, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_topicSubscribeLen, &len, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_getMqttMsgFreq(uint32_t *freq){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_mqttMsgFreq, freq, 4, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setMqttMsgFreq(uint32_t freq){
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_mqttMsgFreq, &freq, 4, 200)){
			return false;
		}
		return true;
	}
	return false;
}

bool ee_setrecdcpStruct(recdCPointsTypedef *recdcp){
	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_recdConstPointStruct, (uint8_t*)recdcp, sizeof(recdCPointsTypedef), 500)){
			return false;
		}
		return true;
	}
}

bool ee_getrecdcpStruct(recdCPointsTypedef *recdcp){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_recdConstPointStruct, (uint8_t*)recdcp, sizeof(recdCPointsTypedef), 500)){
			return true;
		}
	}
	return false;
}

bool ee_getBLUpdateStatus(uint8_t* blust){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_blUpdateStatus, blust, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_setBLUpdateStatus(uint8_t blust){
	if(ee24_isConnected()){
		if(ee24_write(eeAddr_blUpdateStatus, &blust, 1, 500)){
			return true;
		}
	}
	return false;
}

bool ee_getBLFileNameLen(uint8_t *len){
	if(ee24_isConnected()){
		if(ee24_read(eeAddr_blfileNameLen, len, 1, 200)){
			return true;
		}
	}
	return false;
}

bool ee_getBLFileName(char *str){
	if(ee24_isConnected()){
		uint8_t flen = 0;
		if(ee_getBLFileNameLen(&flen)){
			if(ee24_read(eeAddr_blFileName, str, flen, 200)){
				return true;
			}
		}
	}
	return false;
}

bool ee_setBLFileName(char *str, size_t len){

	if(ee24_isConnected()){
		if(!ee24_write(eeAddr_blFileName, str, len, 200)){
			return false;
		}
		if(!ee24_write(eeAddr_blfileNameLen, &len, 1, 200)){
			return false;
		}
		return true;
	}
	return false;
}


bool configIOTParameters(iotParam_Typedef *iot){
	if (ee24_isConnected()) {
		ee_getDeviceIDLen(&(iot->DEVICE_ID_LEN));
		ee_getMqttClientIDLen(&(iot->mqtt.CLIENT_ID_LEN));
		ee_getMqttUserIDLen(&(iot->mqtt.USER_ID_LEN));
		ee_getMqttUserPasswordLen(&(iot->mqtt.USER_PASSWORD_LEN));
		ee_getBrokerAddressLen(&(iot->mqtt.BROKER_ADDRESS_LEN));
		ee_getBrokerPort(&(iot->mqtt.brokerPort));
		ee_getTopicPublish1Len(&(iot->mqtt.TOPIC_PUBLISH_LEN[0]));
		ee_getTopicSubscribeLen(&(iot->mqtt.TOPIC_SUBSCRIBE_LEN));

		ee_getDeviceID(&(iot->deviceID), iot->DEVICE_ID_LEN);
		ee_getMqttClientID(&(iot->mqtt.ClientID), iot->mqtt.CLIENT_ID_LEN);
		ee_getMqttUserID(&(iot->mqtt.userID), iot->mqtt.USER_ID_LEN);
		ee_getMqttUserPassword(&(iot->mqtt.userPassword), iot->mqtt.USER_PASSWORD_LEN);
		ee_getBrokerAddress(&(iot->mqtt.BrokerAddress), iot->mqtt.BROKER_ADDRESS_LEN);
		ee_getTopicPublish1(&(iot->mqtt.topicPublish[0]), iot->mqtt.TOPIC_PUBLISH_LEN[0]);
		ee_getTopicSubscribe(&(iot->mqtt.topicSubscribe), iot->mqtt.TOPIC_SUBSCRIBE_LEN);
		ee_getMqttMsgFreq(&(iot->mqtt.messageFreq));

		return true;
	}
	else{
		iot->DEVICE_ID_LEN = 9;
		iot->mqtt.brokerPort = 15334;
		iot->mqtt.CLIENT_ID_LEN = 16;
		iot->mqtt.USER_ID_LEN = 9;
		iot->mqtt.USER_PASSWORD_LEN = 9;
		iot->mqtt.BROKER_ADDRESS_LEN = 35;
		iot->mqtt.TOPIC_PUBLISH_LEN[0] = 8;
		iot->mqtt.TOPIC_SUBSCRIBE_LEN = 7 + iot->DEVICE_ID_LEN + 1;

		snprintf(iot->deviceID, iot->DEVICE_ID_LEN, "Dummy-ID");
		snprintf(iot->mqtt.BrokerAddress, iot->mqtt.BROKER_ADDRESS_LEN, "o1707366.ap-southeast-1.emqx.cloud");
		snprintf(iot->mqtt.ClientID, iot->mqtt.CLIENT_ID_LEN, "cfe874tfhge4r39");
		snprintf(iot->mqtt.userID, iot->mqtt.USER_ID_LEN, "12345678");
		snprintf(iot->mqtt.userPassword, iot->mqtt.USER_PASSWORD_LEN, "12345678");
		char mbuf[50];
		snprintf(mbuf, iot->mqtt.TOPIC_SUBSCRIBE_LEN, "device/%s", iot->deviceID);
		snprintf(iot->mqtt.topicSubscribe, iot->mqtt.TOPIC_SUBSCRIBE_LEN, mbuf);
		snprintf(iot->mqtt.topicPublish[0], 8, "Testing");
		snprintf(iot->mqtt.topicPublish[1], 8, "recd");

		return false;
	}
}

bool configRECDConstantPointSets(recdCPointsTypedef* recdcps){
	if (ee24_isConnected()) {
		ee_getrecdcpStruct(recdcps);
		return true;
	}
	else{
		recdcps->setPointP[0] = 10;
		recdcps->setPointP[1] = 30;
		recdcps->setPointP[2] = 40;
		recdcps->setPointP[3] = 50;
		recdcps->setPointP[4] = 60;
		recdcps->setPointP[5] = 70;
		recdcps->setPointP[6] = 20;
		recdcps->setPointP[7] = 30;
		recdcps->setPointP[8] = 40;
		recdcps->setPointP[9] = 50;
		recdcps->setPointP[10] = 60;
		recdcps->setPointP[11] = 70;

		recdcps->setPointT[0] = 100;
		recdcps->setPointT[1] = 200;
		recdcps->setPointT[2] = 300;
		recdcps->setPointT[3] = 400;
		recdcps->setPointT[4] = 500;
		recdcps->setPointT[5] = 600;
		recdcps->setPointT[6] = 700;

		recdcps->T_Amb = 80;
		recdcps->EB1 = 32;
		recdcps->SLNCR_BP = 3;
		recdcps->P_OEM = 67;
		return false;
	}
}

bool eeprom_recdcp_param_set(recdCPointsTypedef* recdcps){
	if (ee24_isConnected()) {
		recdcps->setPointP[0] = 10;
		recdcps->setPointP[1] = 30;
		recdcps->setPointP[2] = 40;
		recdcps->setPointP[3] = 50;
		recdcps->setPointP[4] = 60;
		recdcps->setPointP[5] = 70;
		recdcps->setPointP[6] = 20;
		recdcps->setPointP[7] = 30;
		recdcps->setPointP[8] = 40;
		recdcps->setPointP[9] = 50;
		recdcps->setPointP[10] = 60;
		recdcps->setPointP[11] = 70;

		recdcps->setPointT[0] = 100;
		recdcps->setPointT[1] = 200;
		recdcps->setPointT[2] = 300;
		recdcps->setPointT[3] = 400;
		recdcps->setPointT[4] = 500;
		recdcps->setPointT[5] = 600;
		recdcps->setPointT[6] = 700;

		recdcps->T_Amb = 80;
		recdcps->EB1 = 32;
		recdcps->SLNCR_BP = 3;
		recdcps->P_OEM = 67;
		ee_setrecdcpStruct(recdcps);
		return true;
	}
	return false;
}


bool eeprom_iot_param_set(iotParam_Typedef *iot, char* devid, uint16_t devid_len, char* pub_topic, uint16_t pub_topic_len, uint32_t mqttFreq){
	if (ee24_isConnected()) {
		ee_setDeviceID(devid, devid_len);
		randClientIDGenerate();
		ee_setMqttClientID(iot->mqtt.ClientID, 16);
		ee_setMqttUserID("12345678", 9);
		ee_setMqttUserPassword("12345678", 9);
		ee_setBrokerAddress("o1707366.ap-southeast-1.emqx.cloud", 35);
		ee_setBrokerPort(15334);
		char mbuf[50];
		snprintf(mbuf, 7 + devid_len + 1, "device/%s", devid);
		ee_setTopicSubscribe(mbuf, strlen(mbuf));
		ee_setTopicPublish1(pub_topic, pub_topic_len);
		ee_setMqttMsgFreq(mqttFreq);
		return true;
	}
	return false;
}

void eeprom_git_param_set(gitDataTypedef gitData){
	if (ee24_isConnected()) {
			//TODO: EEPROM should contain GIT data or not?
		return true;
	}
	return false;
}
