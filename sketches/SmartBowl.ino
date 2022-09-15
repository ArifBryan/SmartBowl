#include "System.h"
#include "Bluetooth.h"
#include "UserInterface.h"
#include "Sensor.h"
#include "Config.h"
#include "Pins.h"

uint32_t dispChargeTimer;

void Startup_Handler() {
	setCpuFrequencyMhz(80);
	config.Init();
	sys.SetVbatCalValue(config.param.VbatCal);
	sens.SetCalValue(config.param.SensCal);
	ui.Init();
	sens.Init();
	if (!sys.IsCharging()) {
		bt.Init();
		ui.BootScreen();
		ui.SetBrightness(config.param.Bright);
	}
	else {
		setCpuFrequencyMhz(20);
		btStop();
	}
	if (sys.IsCharging()) {
		sys.Handler();
		ui.SetBrightness(5);
		ui.BatteryScreen();
		dispChargeTimer = millis();
		while (sys.IsCharging() || sys.IsCharged()) {
			sys.Handler();
			if (!digitalRead(BTN_PWR)) {
				ui.SetBrightness(5);
				ui.BatteryScreen();
				dispChargeTimer = millis();
			}
			if (millis() - dispChargeTimer >= 1500) {
				ui.SetBrightness(0);
			}
		}
		sys.PowerOff();
	}
}

void Shutdown_Handler() {
	ui.SetBrightness(0);
}

void setup(){
	sys.Init(Startup_Handler, Shutdown_Handler);
	if (sys.IsBattLow()) {
		ui.BatteryScreen();
		delay(1500);
		sys.PowerOff();
	}
}

void loop(){
	sys.Handler();
	bt.Handler();
	ui.Handler();
	sens.Handler();
}
