#include "System.h"
#include "Pins.h"

#define VBAT_FILTER_KF	10

System_TypeDef sys;

void System_TypeDef::Init(void(*Startup_Callback)(void), void(*Shutdown_Callback)(void)) {
	Shutdown_Handler = Shutdown_Callback;
	pinMode(CHG_CON, INPUT_PULLUP);
	pinMode(CHG_STA, INPUT_PULLUP);
	pinMode(BTN_PWR, INPUT_PULLUP);
	pinMode(PWR_LATCH, OUTPUT);
	pwrBtnTmr = millis();
	while (1) {
		if (!digitalRead(BTN_PWR) || !digitalRead(CHG_CON)) {
			if (millis() - pwrBtnTmr >= 200) {
				if (!digitalRead(CHG_CON)) {
					chgStatus = 1;
				}
				break;
			}
		}
		else {
			pwrBtnTmr = millis();
		}
	}
	digitalWrite(PWR_LATCH, HIGH);
	delay(1);
	Startup_Callback();
	vBat = analogRead(VBAT_SENSE) * vBatCal; 
	delay(100);
	pwrBtnTmr = millis();
	while (!digitalRead(BTN_PWR)) {
		if (millis() - pwrBtnTmr >= 2000) {
			config.RestoreDefault();
			PowerOff();
		}
	}
	pwrBtnTmr = millis();
	powerOffTimer = millis();
}

void System_TypeDef::Handler() {
	if (vBat == 0) {
		vBat = analogRead(VBAT_SENSE) * vBatCal; 
	}
	if (!digitalRead(BTN_PWR)) {
		if (millis() - pwrBtnTmr >= 1000) {
			PowerOff();
		}
	}
	else {
		pwrBtnTmr = millis();
	}
	
	if (!digitalRead(CHG_CON)) {
		if (!digitalRead(CHG_STA)) {
			// Charging
			chgStatus = 1;
//			if (vBat >= 4200) {
//				chgStatus = 2;
//			}
		}
		else {
			// Charged
			chgStatus = 2;
		}
	}
	else {
		// Not charging
		chgStatus = 0;
	}
	
	if (millis() - sysTimer >= 500) {
		vBat = (analogRead(VBAT_SENSE) * vBatCal + (vBat * VBAT_FILTER_KF)) / (VBAT_FILTER_KF + 1);
		
		if (bt.IsConnected() || chgStatus) {
			powerOffTimer = millis();
		}
		
		if ((IsBattLow() || millis() - powerOffTimer >= 50000) && chgStatus == 0) {
			PowerOff();
		}
		
		sysTimer = millis();
	}
}

void System_TypeDef::PowerOff() {
	Shutdown_Handler();
	digitalWrite(PWR_LATCH, LOW);
	while (!digitalRead(BTN_PWR)) ;
	ESP.restart();
}