#include "Bluetooth.h"
#include <BluetoothSerial.h>

Bluetooth_TypeDef bt;

BluetoothSerial btSerial;

bool strMatch(const char *str1, const char *str2) {
	bool s = strncmp(str1, str2, strlen(str2)) == 0;
	return s;
}
bool strSkim(char *str1, const char *str2) {
	bool s = strncmp(str1, str2, strlen(str2)) == 0;
	if (s) {
		*str1 += strlen(str2);
	}
	return s;
}

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
		Serial.print(rxBuff);
		if (strSkim(rxBuff, "ADCRAW?")) {
			btSerial.println(123);
		}
		rxNewData = 0;
		memset(rxBuff, 0, 200);
	}
}
