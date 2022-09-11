#include "System.h"
#include "Pins.h"

#define VBAT_FILTER_KF	10

System_TypeDef sys;

void System_TypeDef::Init(void(*Startup_Callback)(void), void(*Shutdown_Callback)(void)) {
	Shutdown_Handler = Shutdown_Callback;
	pwrBtnTmr = millis();
	while (1) {
		if (!digitalRead(BTN_PWR) || !digitalRead(CHG_CON)) {
			if (millis() - pwrBtnTmr >= 500) {
				if (!digitalRead(BTN_PWR)) {
					powerOnCause = POWERON_CAUSE_BTN;
				}
				else if (!digitalRead(CHG_CON)) {
					powerOnCause = POWERON_CAUSE_CHG;
				}
				break;
			}
		}
		else {
			pwrBtnTmr = millis();
		}
	}
	pinMode(PWR_LATCH, OUTPUT);
	digitalWrite(PWR_LATCH, HIGH);
	delay(1);
	pinMode(CHG_CON, INPUT_PULLUP);
	pinMode(CHG_STA, INPUT_PULLUP);
	pinMode(BTN_PWR, INPUT_PULLUP);
	Startup_Callback();
	vBat = analogRead(VBAT_SENSE) * vBatCal;
	delay(100);
	pwrBtnTmr = millis();
	while (!digitalRead(BTN_PWR)) {
		if (millis() - pwrBtnTmr >= 2000) {
			config.RestoreDefault();
		}
	}
	pwrBtnTmr = millis();
}

void System_TypeDef::Handler() {
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
		
		sysTimer = millis();
	}
}

void System_TypeDef::PowerOff() {
	Shutdown_Handler();
	digitalWrite(PWR_LATCH, LOW);
	while (!digitalRead(BTN_PWR)) ;
	ESP.restart();
}