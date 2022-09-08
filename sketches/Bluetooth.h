#pragma once

#include "Arduino.h"

struct Bluetooth_TypeDef {
	void Init();
	void Handler();
	
private:
	char rxBuff[200];
	uint8_t rxBuffPtr;
	bool rxNewData;
	uint32_t rxToutTimer;
};

extern Bluetooth_TypeDef bt;