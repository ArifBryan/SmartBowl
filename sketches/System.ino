#include "System.h"
#include "Pins.h"

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
	delay(100);
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
		}
		else {
			// Charged
		}
	}
	else {
		// Not charging
	}
}

void System_TypeDef::PowerOff() {
	Shutdown_Handler();
	digitalWrite(PWR_LATCH, LOW);
	while (!digitalRead(BTN_PWR)) ;
	ESP.restart();
}