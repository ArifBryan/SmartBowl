#include "Sensor.h"
#include "Pins.h"
#include <HX711.h>

#define SENSOR_FILTER_KF	5

Sensor_TypeDef sens;

HX711 LoadCell;

void Sensor_TypeDef::Init() {
	LoadCell.begin(HX_DATA, HX_SCK);
}

void Sensor_TypeDef::Handler() {
	if (millis() - sampleTmr >= 200) {
		rawData = LoadCell.read();
		rawDataFiltered = (rawData + (rawDataFiltered * SENSOR_FILTER_KF)) / (SENSOR_FILTER_KF + 1);
		weight = rawDataFiltered * cal;
		
		sampleTmr = millis();
	}
}
