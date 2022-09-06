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
		
		Serial.print(rxBuff);
		rxNewData = 0;
		memset(rxBuff, 0, 200);
	}
}

bool IsCommand(char **str, const char *m) {
	char abr[11];
	uint8_t abrl = 0;
	for (uint8_t i = 0; m[i]; i++) {
		if (!islower(m[i])) {
			abr[abrl++] = m[i];
		}
	}
	abr[abrl] = 0;
	
	return strSkim(str, m) || strSkim(str, abr);
}

bool strMatch(const char *str1, const char *str2) {
	bool s = strncmp(str1, str2, strlen(str2)) == 0;
	return s;
}
bool strSkim(char **str1, const char *str2) {
	bool s = strncmp(*str1, str2, strlen(str2)) == 0;
	if (s) {
		*str1 += strlen(str2);
	}
	return s;
}