#include "Sensor.h"
#include "Pins.h"
#include <HX711.h>

Sensor_TypeDef sens;

HX711 LoadCell;

void Sensor_TypeDef::Init() {
	LoadCell.begin(HX_DATA, HX_SCK);
}

void Sensor_TypeDef::Handler() {
	if (millis() - sampleTmr >= 250) {
		sampleTmr = millis();
	}
}