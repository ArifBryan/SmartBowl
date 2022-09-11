#include "Bluetooth.h"
#include <BluetoothSerial.h>

Bluetooth_TypeDef bt;

BluetoothSerial btSerial;

bool strMatch(char *str1, const char *str2) {
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

void Bluetooth_TypeDef::Init() {
	Serial.begin(115200);
	btSerial.begin("BOWELL");
	connected = 1;
	connectTimer = millis() + 5000;
}

bool Bluetooth_TypeDef::IsConnected() {
	return connected;
}

void Bluetooth_TypeDef::Handler() {
	if (millis() - rxToutTimer >= 500 && rxBuffPtr > 0) {
		rxBuffPtr = 0;
		memset(rxBuff, 0, 200);
	}
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
		rxToutTimer = millis();
	}
	
	if (rxNewData) {
		connectTimer = millis();
		char *data = rxBuff;
		Serial.print(data);
		//ui.Text[0].DrawText(data);
		
		if (strSkim(&data, "WEIGHTRAW?")) {
			btSerial.println(sens.GetRawData());
		}
		else if (strSkim(&data, "WEIGHT?")) {
			btSerial.println(sens.GetWeight());
		}
		else if (strSkim(&data, "BATT?")) {
			btSerial.println(sys.GetBattPercentage());
		}
		else if (strSkim(&data, "BATTV?")) {
			btSerial.println(sys.GetVbat());
		}
		else if (strSkim(&data, "CHARGE?")) {
			btSerial.println(sys.IsCharging() + sys.IsCharged());
		}
		else if (strSkim(&data, "VERSION?")) {
			btSerial.print("v");
			btSerial.println(FW_VER);
		}
		else if (strSkim(&data, "WEIGHTCAL:")) {
			config.param.SensCal = atof(data);
			config.Save();
			sens.SetCalValue(config.param.SensCal);	
		}
		else if (strSkim(&data, "WEIGHTFIL:")) {
			config.param.SensFil = atof(data);
			config.Save();
			sens.SetFilCoeff(config.param.SensCal);	
		}
		else if (strSkim(&data, "BATTCAL:")) {
			config.param.VbatCal = atof(data);
			config.Save();
			sys.SetVbatCalValue(config.param.VbatCal);	
		}
		else if (strSkim(&data, "BRIGHT:")) {
			config.param.Bright = atoi(data);
			config.Save();
			ui.SetBrightness(config.param.Bright);
		}
		else if (strSkim(&data, "TEXT")) {
			int8_t n = atoi(data) - 1;
			if (n >= 0 && n < 5) {
				data += 1;
				if (strSkim(&data, ":")) {
					ui.Text[n].DrawText(data);
				}
			}
		}
		else if (strSkim(&data, "TARE")) {
			sens.Tare();
		}
		else if (strSkim(&data, "POWER:")) {
			uint8_t m = atoi(data);
			if (m == 0) {sys.PowerOff(); }
			else if (m == 1) {}
			else if (m == 2) {}
		}
		rxNewData = 0;
		memset(rxBuff, 0, 200);
	}
	
	if (millis() - connectTimer >= 5000 && connected) {
		connected = 0;
		ui.Text[0].DrawText("");
		ui.Text[1].DrawText("Open");
		ui.Text[2].DrawText("BOWELL App");
		ui.Text[3].DrawText("on Smartphone");
		ui.Text[4].DrawText("");
	}
	else if (millis() - connectTimer < 5000 && !connected) {
		connected = 1;
		ui.Text[0].DrawText("");
		ui.Text[1].DrawText("");
		ui.Text[2].DrawText("");
		ui.Text[3].DrawText("");
		ui.Text[4].DrawText("");		
	}
}
