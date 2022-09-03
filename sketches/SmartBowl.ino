#include "System.h"
#include "Bluetooth.h"
#include "UserInterface.h"
#include "Sensor.h"

void Startup_Handler() {
	ui.Init();
	sens.Init();
	bt.Init();
}

void Shutdown_Handler() {
	
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
