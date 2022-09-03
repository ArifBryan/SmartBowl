#include "Sensor.h"
#include "Pins.h"
#include <HX711.h>

Sensor_TypeDef sens;

HX711 LoadCell;

uint32_t loadCellSampleInterval;
uint32_t loadCellSampleTmr;

void Sensor_TypeDef::Init() {
	LoadCell.begin(HX_DATA, HX_SCK);
}

void Sensor_TypeDef::Handler() {
	if (millis() - loadCellSampleTmr >= loadCellSampleInterval) {
		loadCellSampleTmr = millis();
	}
}