#include "Sensor.h"
#include "Pins.h"
#include <HX711.h>

Sensor_TypeDef sens;

HX711 LoadCell;

void Sensor_TypeDef::Init() {
	LoadCell.begin(HX_DATA, HX_SCK);
}

void Sensor_TypeDef::Handler() {
	if (millis() - sampleTmr >= 100) {
		rawData = LoadCell.read();
		rawDataFiltered = (rawData + (rawDataFiltered * filterKf)) / (filterKf + 1);
		weight = (rawDataFiltered - offset) * cal;
		
		sampleTmr = millis();
	}
}
