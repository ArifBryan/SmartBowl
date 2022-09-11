#pragma once

#include "Arduino.h"

struct Bluetooth_TypeDef {
	void Init();
	void Handler();
	bool IsConnected();
	
private:
	char rxBuff[200];
	uint8_t rxBuffPtr;
	bool rxNewData;
	bool connected;
	uint32_t rxToutTimer;
	uint32_t connectTimer;
};

extern Bluetooth_TypeDef bt;