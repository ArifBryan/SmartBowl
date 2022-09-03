#include "Bluetooth.h"
#include <BluetoothSerial.h>

Bluetooth_TypeDef bt;

BluetoothSerial btSerial;

void Bluetooth_TypeDef::Init() {
	Serial.begin(115200);
	btSerial.begin("BOWELL");
}

void Bluetooth_TypeDef::Handler() {
	while (btSerial.available()) {
		char data = btSerial.read();
		if (data == '\n') {
			rxBuff[rxBuffPtr++] = data;
			rxNewData = 1;
			rxBuffPtr = 0;
			break;
		}
		else if (rxBuffPtr < 200) {
			rxBuff[rxBuffPtr++] = data;			
		}
	}
	
	if (rxNewData) {
		rxNewData = 0;
		Serial.print(rxBuff);
		memset(rxBuff, 0, 200);
	}
}