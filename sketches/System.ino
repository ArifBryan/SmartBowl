#include "System.h"
#include "Pins.h"

System_TypeDef sys;

void System_TypeDef::Init(void(*Startup_Callback)(void), void(*Shutdown_Callback)(void)) {
	Shutdown_Handler = Shutdown_Callback;
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