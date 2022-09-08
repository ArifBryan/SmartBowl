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
	sens.Init();
	bt.Init();
	ui.BootScreen();
	ui.SetBrightness(config.param.Bright);
}

void Shutdown_Handler() {
	ui.SetBrightness(0);
}

void setup(){
	sys.Init(Startup_Handler, Shutdown_Handler);
}

void loop(){
	sys.Handler();
	bt.Handler();
	ui.Handler();
	sens.Handler();
}
