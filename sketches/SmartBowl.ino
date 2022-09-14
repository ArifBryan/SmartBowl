#include "System.h"
#include "Bluetooth.h"
#include "UserInterface.h"
#include "Sensor.h"
#include "Config.h"

void Startup_Handler() {
	config.Init();
	sys.SetVbatCalValue(config.param.VbatCal);
	sens.SetCalValue(config.param.SensCal);
	ui.Init();
	if (!sys.IsCharging()) {
		sens.Init();
		bt.Init();
		ui.BootScreen();
	}
	ui.SetBrightness(config.param.Bright);
	if (sys.IsCharging()) {
		while (sys.IsCharging() || sys.IsCharged()) {
			sys.Handler();
			ui.BatteryScreen();
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
